#include <objnaut/fmt/fmt_Dictionary.hpp>

namespace objnaut::fmt {

    namespace {

        struct WordMeaningDetailEntry {
            u16 unk3_object_id;
            std::string detail_text;
        };
        
        struct WordDetailEntry {
            std::string word_name;
            std::vector<WordMeaningDetailEntry> details;
        };

    }

    Result Dictionary::ReadFrom(twl::fs::File &rf_dict, twl::fs::File &rf_jump_table, twl::fs::File &rf_word_table, std::optional<std::reference_wrapper<twl::fs::File>> &rf_details) {
        u8 dict_char_dict_count;
        TWL_R_TRY(rf_dict.Read(dict_char_dict_count));

        TWL_R_TRY(rf_dict.MoveOffset(dict_char_dict_count));

        u32 word_count;
        TWL_R_TRY(rf_dict.Read(word_count));

        this->words.clear();
        this->words.reserve(word_count);

        // Skip 2D table (we don't make use of it)
        TWL_R_TRY(rf_dict.MoveOffset(dict_char_dict_count * dict_char_dict_count * sizeof(u32)));

        std::vector<WordDetailEntry> detail_entries;
        if(rf_details.has_value()) {
            auto &rf_details_v = rf_details.value();

            u8 details_dict_char_dict_count;
            TWL_R_TRY(rf_details_v.get().Read(details_dict_char_dict_count));

            TWL_R_TRY(rf_details_v.get().MoveOffset(details_dict_char_dict_count));

            TWL_R_TRY(rf_details_v.get().MoveOffset(details_dict_char_dict_count * sizeof(u32)));

            while(true) {
                u8 word_name_len;
                if(rf_details_v.get().Read(word_name_len).IsFailure()) {
                    break;
                }

                auto &detail_entry = detail_entries.emplace_back();

                auto word_name_buf = new char[word_name_len + 1]();
                ScopeGuard word_name_buf_delete([&]() {
                    delete[] word_name_buf;
                });
                TWL_R_TRY(rf_details_v.get().ReadBuffer(word_name_buf, word_name_len));
                word_name_buf_delete.Cancel();
                detail_entry.word_name.assign(word_name_buf);
                delete[] word_name_buf;

                u8 word_meaning_count;
                TWL_R_TRY(rf_details_v.get().Read(word_meaning_count));

                detail_entry.details.reserve(word_meaning_count);

                for(u32 i = 0; i < word_meaning_count; i++) {
                    auto &detail = detail_entry.details.emplace_back();

                    u16 unk3_object_id;
                    TWL_R_TRY(rf_details_v.get().Read(unk3_object_id));

                    detail.unk3_object_id = unk3_object_id;
                }

                for(u32 i = 0; i < word_meaning_count; i++) {
                    auto &detail = detail_entry.details.at(i);

                    u8 detail_text_len;
                    TWL_R_TRY(rf_details_v.get().Read(detail_text_len));

                    auto detail_text_buf = new char[detail_text_len + 1]();
                    ScopeGuard detail_text_buf_delete([&]() {
                        delete[] detail_text_buf;
                    });
                    TWL_R_TRY(rf_details_v.get().ReadBuffer(detail_text_buf, detail_text_len));
                    detail.detail_text.assign(detail_text_buf);
                }
            }
        }

        std::vector<size_t> word_start_offsets;
        for(u32 i = 0; i < word_count; i++) {
            auto word = std::make_shared<Word>();

            size_t word_start_offset;
            TWL_R_TRY(rf_dict.GetOffset(word_start_offset));
            word_start_offsets.push_back(word_start_offset);

            u8 word_total_size;
            TWL_R_TRY(rf_dict.Read(word_total_size));

            u8 word_name_len;
            TWL_R_TRY(rf_dict.Read(word_name_len));

            auto word_name_buf = new char[word_name_len + 1]();
            ScopeGuard word_name_buf_delete([&]() {
                delete[] word_name_buf;
            });
            TWL_R_TRY(rf_dict.ReadBuffer(word_name_buf, word_name_len));
            word_name_buf_delete.Cancel();
            word->name.assign(word_name_buf);
            delete[] word_name_buf;

            u16 word_id;
            TWL_R_TRY(rf_dict.Read(word_id));
            word->word_id = word_id;

            u16 unk1_zero;
            TWL_R_TRY(rf_dict.Read(unk1_zero));
            word->unk1_zero = unk1_zero;

            u8 meaning_count;
            TWL_R_TRY(rf_dict.Read(meaning_count));

            word->meanings.reserve(meaning_count);
            for(u32 i = 0; i < meaning_count; i++) {
                auto &meaning = word->meanings.emplace_back();

                u16 file_id;
                TWL_R_TRY(rf_dict.Read(file_id));

                meaning.file_id = file_id;
            }

            for(auto &meaning: word->meanings) {
                u16 adj_obj_id;
                TWL_R_TRY(rf_dict.Read(adj_obj_id));

                meaning.adj_obj_id = adj_obj_id;
            }

            for(auto &meaning: word->meanings) {
                u16 unk2;
                TWL_R_TRY(rf_dict.Read(unk2));

                meaning.unk2 = unk2;
            }

            for(const auto &detail_entry: detail_entries) {
                if(detail_entry.word_name == word->name) {
                    if(detail_entry.details.size() != meaning_count) {
                        TWL_R_FAIL(ResultDictionaryDetailMeaningMismatch);
                    }

                    for(u32 i = 0; i < meaning_count; i++) {
                        auto &meaning = word->meanings.at(i);
                        auto &detail = detail_entry.details.at(i);
                        meaning.obj_detail_text = detail.detail_text;
                        meaning.unk3_object_id = detail.unk3_object_id;
                    }

                    break;
                }
            }

            this->words.push_back(std::move(word));
        }

        for(auto &word: this->words) {
            for(auto &meaning: word->meanings) {
                TWL_R_TRY(rf_jump_table.SetAbsoluteOffset(meaning.adj_obj_id * sizeof(u32)));

                u32 jump_word_offset;
                TWL_R_TRY(rf_jump_table.Read(jump_word_offset));

                auto it = std::find(word_start_offsets.begin(), word_start_offsets.end(), jump_word_offset);
                const auto jump_word_idx = std::distance(word_start_offsets.begin(), it);
                auto jump_word = this->words.at(jump_word_idx);
                if(jump_word != word) {
                    meaning.redir_word = jump_word;
                }
            }
        }

        TWL_R_SUCCEED();
    }

    namespace {

        inline void SortCharacterList(std::vector<char> &char_list) {
            std::sort(char_list.begin(), char_list.end(), [](char a, char b) {
                return static_cast<unsigned char>(a) < static_cast<unsigned char>(b);
            });
        }

    }

    Result Dictionary::WriteTo(twl::fs::File &wf_dict, twl::fs::File &wf_jump_table, twl::fs::File &wf_word_table, std::optional<std::reference_wrapper<twl::fs::File>> &wf_details) {
        // Ensure word list is sorted, word table expects it
        std::sort(this->words.begin(), this->words.end(), [](const auto &a, const auto &b) {
            const auto min_name_len = std::min(a->name.length(), b->name.length());
            for(u32 i = 0; i < min_name_len; i++) {
                if(static_cast<unsigned char>(a->name.at(i)) < static_cast<unsigned char>(b->name.at(i))) {
                    return true;
                }
                else if(static_cast<unsigned char>(a->name.at(i)) > static_cast<unsigned char>(b->name.at(i))) {
                    return false;
                }
            }

            return false;
        });
        
        const auto word_count = this->words.size();
        if(word_count > UINT32_MAX) {
            TWL_R_FAIL(ResultDictionaryWordCountOverflow);
        }

        // Space character is special only for this list
        std::vector<char> dict_char_dict = { ' ' };
        std::vector<char> details_char_dict;
        for(const auto &word: this->words) {
            if(word->name.length() >= 1) {
                const auto ch0 = word->name.at(0);

                if(std::find(dict_char_dict.begin(), dict_char_dict.end(), ch0) == dict_char_dict.end()) {
                    dict_char_dict.push_back(ch0);
                    SortCharacterList(dict_char_dict);
                }

                if(word->name.length() >= 2) {
                    const auto ch1 = word->name.at(1);

                    if(std::find(dict_char_dict.begin(), dict_char_dict.end(), ch1) == dict_char_dict.end()) {
                        dict_char_dict.push_back(ch1);
                        SortCharacterList(dict_char_dict);
                    }
                }

                if(word->meanings.size() > 1) {
                    if(std::find(details_char_dict.begin(), details_char_dict.end(), ch0) == details_char_dict.end()) {
                        details_char_dict.push_back(ch0);
                        SortCharacterList(details_char_dict);
                    }
                }
            }
        }

        const auto dict_char_dict_count = dict_char_dict.size();
        if(dict_char_dict_count > UINT8_MAX) {
            TWL_R_FAIL(ResultDictionaryCharacterOverflow);
        }

        u32 dict_char_dict_empty_ch_idx = UINT32_MAX;
        for(u32 i = 0; i < dict_char_dict.size(); i++) {
            if(dict_char_dict[i] == ' ') {
                dict_char_dict_empty_ch_idx = i;
                break;
            }
        }

        TWL_R_TRY(wf_dict.Write<u8>(dict_char_dict_count));
        TWL_R_TRY(wf_dict.WriteVector(dict_char_dict));
        
        TWL_R_TRY(wf_dict.Write<u32>(word_count));

        size_t dict_offsets_table_offset;
        TWL_R_TRY(wf_dict.GetOffset(dict_offsets_table_offset));

        auto dict_offsets_table_buf = new u32[dict_char_dict_count * dict_char_dict_count]();
        ScopeGuard dict_offsets_table_buf_delete([&]() {
            delete[] dict_offsets_table_buf;
        });

        TWL_R_TRY(wf_dict.MoveOffset(dict_char_dict_count * dict_char_dict_count * sizeof(u32)));

        size_t details_dict_char_dict_count;
        size_t details_offsets_table_offset;
        u32 *details_offsets_table_buf = nullptr;
        ScopeGuard details_offsets_table_buf_delete([&]() {
            if(details_offsets_table_buf != nullptr) {
                delete[] details_offsets_table_buf;
            }
        });
        if(wf_details.has_value()) {
            details_dict_char_dict_count = details_char_dict.size();

            auto &wf_details_v = wf_details.value();

            TWL_R_TRY(wf_details_v.get().Write<u8>(details_dict_char_dict_count));
            TWL_R_TRY(wf_details_v.get().WriteVector(details_char_dict));

            details_offsets_table_buf = new u32[details_dict_char_dict_count]();

            TWL_R_TRY(wf_details_v.get().GetOffset(details_offsets_table_offset));

            TWL_R_TRY(wf_details_v.get().MoveOffset(details_dict_char_dict_count * sizeof(u32)));
        }

        std::vector<size_t> dict_word_start_offsets;
        for(const auto &word: this->words) {
            size_t word_start_offset;
            TWL_R_TRY(wf_dict.GetOffset(word_start_offset));
            dict_word_start_offsets.push_back(word_start_offset);

            const auto meaning_count = word->meanings.size();
            const size_t word_total_size = sizeof(u8) // u8 word_total_size
                                    + sizeof(u8) // u8 name_len
                                    + word->name.length() * sizeof(char) // char name[name_len]
                                    + sizeof(u16) // u16 word_id
                                    + sizeof(u16) // u16 unk1_zero
                                    + sizeof(u8) // u8 meaning_count
                                    + meaning_count * (
                                        sizeof(u16) // u16 file_id
                                        + sizeof(u16) // u16 adj_obj_id
                                        + sizeof(u16) // u16 unk2
                                    );

            if(word_total_size > UINT8_MAX) {
                TWL_R_FAIL(ResultDictionaryWordEntryOverflow);
            }

            TWL_R_TRY(wf_word_table.SetAbsoluteOffset(word->word_id * sizeof(u32)));
            TWL_R_TRY(wf_word_table.Write<u32>(word_start_offset));

            if(word->name.length() >= 2) {
                const auto ch0 = word->name.at(0);
                const auto ch1 = word->name.at(1);
                u32 ch0_idx = UINT32_MAX;
                u32 ch1_idx = UINT32_MAX;
                for(u32 i = 0; i < dict_char_dict.size(); i++) {
                    const auto dict_ch_i = dict_char_dict.at(i);
                    if(dict_ch_i == ch0) {
                        ch0_idx = i;
                    }
                    if(dict_ch_i == ch1) {
                        ch1_idx = i;
                    }
                }

                if((ch0_idx == UINT32_MAX) || (ch1_idx == UINT32_MAX)) {
                    TWL_R_FAIL(ResultDictionaryCharacterTableMismatch);
                }

                // For instance, for a word starting with 'AB', set both 'A ' and 'AB' offsets
                const auto cur_off = dict_offsets_table_buf[ch1_idx + ch0_idx * dict_char_dict_count];
                if(cur_off == 0) {
                    dict_offsets_table_buf[ch1_idx + ch0_idx * dict_char_dict_count] = word_start_offset;
                }

                const auto cur_off_e = dict_offsets_table_buf[dict_char_dict_empty_ch_idx + ch0_idx * dict_char_dict_count];
                if(cur_off_e == 0) {
                    dict_offsets_table_buf[dict_char_dict_empty_ch_idx + ch0_idx * dict_char_dict_count] = word_start_offset;
                }
            }

            TWL_R_TRY(wf_dict.Write<u8>(word_total_size));
            TWL_R_TRY(wf_dict.Write<u8>(word->name.length()));
            TWL_R_TRY(wf_dict.WriteString(word->name));
            TWL_R_TRY(wf_dict.Write(word->word_id));
            TWL_R_TRY(wf_dict.Write(word->unk1_zero));
            TWL_R_TRY(wf_dict.Write<u8>(meaning_count));

            for(const auto &meaning: word->meanings) {
                TWL_R_TRY(wf_dict.Write(meaning.file_id));
            }
            for(const auto &meaning: word->meanings) {
                TWL_R_TRY(wf_dict.Write(meaning.adj_obj_id));
            }
            for(const auto &meaning: word->meanings) {
                TWL_R_TRY(wf_dict.Write(meaning.unk2));
            }

            size_t input_entry_end_offset;
            TWL_R_TRY(wf_dict.GetOffset(input_entry_end_offset));

            if((input_entry_end_offset - word_start_offset) != word_total_size) {
                TWL_R_FAIL(ResultDictionaryWordEntrySizeMismatch);
            }

            if(wf_details.has_value()) {
                auto &wf_details_v = wf_details.value();
    
                if(meaning_count > 1) {
                    size_t detail_entry_start_offset;
                    TWL_R_TRY(wf_details_v.get().GetOffset(detail_entry_start_offset));
                    
                    if(word->name.length() >= 1) {
                        const auto ch0 = word->name.at(0);
                        u32 ch0_idx = UINT32_MAX;
                        for(u32 i = 0; i < details_char_dict.size(); i++) {
                            const auto dict_ch_i = details_char_dict.at(i);
                            if(dict_ch_i == ch0) {
                                ch0_idx = i;
                                break;
                            }
                        }

                        if(ch0_idx == UINT32_MAX) {
                            TWL_R_FAIL(ResultDictionaryCharacterTableMismatch);
                        }
        
                        const auto cur_off = details_offsets_table_buf[ch0_idx];
                        if(cur_off == 0) {
                            details_offsets_table_buf[ch0_idx] = detail_entry_start_offset;
                        }
                    }

                    TWL_R_TRY(wf_details_v.get().Write<u8>(word->name.length()));
                    TWL_R_TRY(wf_details_v.get().WriteString(word->name));

                    TWL_R_TRY(wf_details_v.get().Write<u8>(meaning_count));

                    for(const auto &meaning: word->meanings) {
                        TWL_R_TRY(wf_details_v.get().Write(meaning.unk3_object_id));
                    }

                    for(const auto &meaning: word->meanings) {
                        TWL_R_TRY(wf_details_v.get().Write<u8>(meaning.obj_detail_text.length()));
                        TWL_R_TRY(wf_details_v.get().WriteString(meaning.obj_detail_text));
                    }
                }
            }
        }

        // Construct the jump table
        for(const auto &word: this->words) {
            for(const auto &meaning: word->meanings) {
                TWL_R_TRY(wf_jump_table.SetAbsoluteOffset(meaning.adj_obj_id * sizeof(u32)));

                auto base_word = (meaning.redir_word != nullptr) ? meaning.redir_word : word;
                auto it = std::find(this->words.begin(), this->words.end(), base_word);
                const auto base_word_offset_i = std::distance(this->words.begin(), it);
                const auto base_word_start_offset = dict_word_start_offsets.at(base_word_offset_i);
                TWL_R_TRY(wf_jump_table.Write<u32>(base_word_start_offset));
            }
        }

        TWL_R_TRY(wf_dict.SetAbsoluteOffset(dict_offsets_table_offset));
        TWL_R_TRY(wf_dict.WriteBuffer(dict_offsets_table_buf, dict_char_dict_count * dict_char_dict_count * sizeof(u32)));
        
        if(wf_details.has_value()) {
            auto &wf_details_v = wf_details.value();

            TWL_R_TRY(wf_details_v.get().SetAbsoluteOffset(details_offsets_table_offset));
            TWL_R_TRY(wf_details_v.get().WriteBuffer(details_offsets_table_buf, details_dict_char_dict_count * sizeof(u32)));
        }

        TWL_R_SUCCEED();
    }

}
