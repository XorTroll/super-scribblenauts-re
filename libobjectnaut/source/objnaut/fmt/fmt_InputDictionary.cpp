#include <objnaut/fmt/fmt_InputDictionary.hpp>

#include <iostream>

namespace objnaut::fmt {

    namespace {

        struct MatchDescriptionEntry {
            u16 unk3;
            std::string desc;
        };
        
        struct MatchDescription {
            std::string input_text;
            std::vector<MatchDescriptionEntry> descs;
        };

    }

    Result InputDictionary::ReadFrom(twl::fs::File &rf_list, twl::fs::File &rf_match_offset_list, twl::fs::File &rf_lookup_offset_list, std::optional<std::reference_wrapper<twl::fs::File>> &rf_match_desc_list) {
        u8 char_dict_count;
        TWL_R_TRY(rf_list.Read(char_dict_count));

        TWL_R_TRY(rf_list.MoveOffset(char_dict_count));

        u32 input_count;
        TWL_R_TRY(rf_list.Read(input_count));

        this->inputs.clear();
        this->inputs.reserve(input_count);

        // Skip 2D table
        TWL_R_TRY(rf_list.MoveOffset(char_dict_count * char_dict_count * sizeof(u32)));

        std::vector<MatchDescription> match_descs;
        if(rf_match_desc_list.has_value()) {
            auto &match_desc_file = rf_match_desc_list.value();

            u8 match_char_dict_count;
            TWL_R_TRY(match_desc_file.get().Read(match_char_dict_count));

            TWL_R_TRY(match_desc_file.get().MoveOffset(match_char_dict_count));

            TWL_R_TRY(match_desc_file.get().MoveOffset(match_char_dict_count * sizeof(u32)));

            while(true) {
                u8 match_desc_entry_input_text_len;
                if(match_desc_file.get().Read(match_desc_entry_input_text_len).IsFailure()) {
                    break;
                }

                auto &desc = match_descs.emplace_back();

                auto match_desc_entry_input_text_buf = new char[match_desc_entry_input_text_len + 1]();
                ScopeGuard match_desc_entry_input_text_buf_delete([&]() {
                    delete[] match_desc_entry_input_text_buf;
                });
                TWL_R_TRY(match_desc_file.get().ReadBuffer(match_desc_entry_input_text_buf, match_desc_entry_input_text_len));
                match_desc_entry_input_text_buf_delete.Cancel();
                desc.input_text.assign(match_desc_entry_input_text_buf);
                delete[] match_desc_entry_input_text_buf;

                u8 match_desc_count;
                TWL_R_TRY(match_desc_file.get().Read(match_desc_count));

                desc.descs.reserve(match_desc_count);

                for(u32 i = 0; i < match_desc_count; i++) {
                    auto &entry = desc.descs.emplace_back();

                    u16 unk3;
                    TWL_R_TRY(match_desc_file.get().Read(unk3));

                    entry.unk3 = unk3;
                }

                for(u32 i = 0; i < match_desc_count; i++) {
                    auto &entry = desc.descs.at(i);

                    u8 alt_desc_len;
                    TWL_R_TRY(match_desc_file.get().Read(alt_desc_len));

                    auto alt_desc_buf = new char[alt_desc_len + 1]();
                    ScopeGuard alt_desc_buf_delete([&]() {
                        delete[] alt_desc_buf;
                    });
                    TWL_R_TRY(match_desc_file.get().ReadBuffer(alt_desc_buf, alt_desc_len));
                    entry.desc.assign(alt_desc_buf);
                }
            }
        }

        std::vector<size_t> input_entry_start_offsets;
        for(u32 i = 0; i < input_count; i++) {
            auto in = std::make_shared<Input>();

            size_t input_entry_start_offset;
            TWL_R_TRY(rf_list.GetOffset(input_entry_start_offset));
            input_entry_start_offsets.push_back(input_entry_start_offset);

            u8 input_size;
            TWL_R_TRY(rf_list.Read(input_size));

            u8 input_text_len;
            TWL_R_TRY(rf_list.Read(input_text_len));

            auto input_text_buf = new char[input_text_len + 1]();
            ScopeGuard input_text_buf_delete([&]() {
                delete[] input_text_buf;
            });
            TWL_R_TRY(rf_list.ReadBuffer(input_text_buf, input_text_len));
            input_text_buf_delete.Cancel();
            in->input_text.assign(input_text_buf);
            delete[] input_text_buf;

            u16 lookup_list_idx;
            TWL_R_TRY(rf_list.Read(lookup_list_idx));
            in->lookup_list_idx = lookup_list_idx;

            u16 unk1;
            TWL_R_TRY(rf_list.Read(unk1));
            in->unk1 = unk1;

            u8 match_count;
            TWL_R_TRY(rf_list.Read(match_count));

            in->matches.reserve(match_count);
            for(u32 i = 0; i < match_count; i++) {
                auto &match = in->matches.emplace_back();

                u16 file_id;
                TWL_R_TRY(rf_list.Read(file_id));

                match.file_id = file_id;
            }

            for(auto &match: in->matches) {
                u16 match_list_idx;
                TWL_R_TRY(rf_list.Read(match_list_idx));

                match.match_list_idx = match_list_idx;
            }

            for(auto &match: in->matches) {
                u16 unk2;
                TWL_R_TRY(rf_list.Read(unk2));

                match.unk2 = unk2;
            }

            for(const auto &desc: match_descs) {
                if(desc.input_text == in->input_text) {
                    if(desc.descs.size() != match_count) {
                        TWL_R_FAIL(ResultUnknownResult);
                    }

                    for(u32 i = 0; i < match_count; i++) {
                        auto &match = in->matches.at(i);
                        auto &entry = desc.descs.at(i);
                        match.description = entry.desc;
                        match.unk3 = entry.unk3;
                    }

                    break;
                }
            }

            this->inputs.push_back(in);
        }

        for(auto &in: this->inputs) {
            for(auto &match: in->matches) {
                TWL_R_TRY(rf_match_offset_list.SetAbsoluteOffset(match.match_list_idx * sizeof(u32)));

                u32 redir_input_offset;
                TWL_R_TRY(rf_match_offset_list.Read(redir_input_offset));

                auto it = std::find(input_entry_start_offsets.begin(), input_entry_start_offsets.end(), redir_input_offset);
                const auto redir_input_i = std::distance(input_entry_start_offsets.begin(), it);
                auto redir_in = this->inputs.at(redir_input_i);
                if(redir_in != in) {
                    match.redir_input = redir_in;
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

    Result InputDictionary::WriteTo(twl::fs::File &wf_list, twl::fs::File &wf_match_offset_list, twl::fs::File &wf_lookup_offset_list, std::optional<std::reference_wrapper<twl::fs::File>> &wf_match_desc_list) {
        const auto input_count = this->inputs.size();
        if(input_count > UINT32_MAX) {
            TWL_R_FAIL(ResultUnknownResult);
        }

        // Space character is special only for this list
        std::vector<char> list_char_dict = { ' ' };
        std::vector<char> match_desc_list_char_dict;
        for(const auto &in: this->inputs) {
            if(in->input_text.length() >= 1) {
                const auto ch0 = in->input_text.at(0);

                if(std::find(list_char_dict.begin(), list_char_dict.end(), ch0) == list_char_dict.end()) {
                    list_char_dict.push_back(ch0);
                    SortCharacterList(list_char_dict);
                }

                if(in->input_text.length() >= 2) {
                    const auto ch1 = in->input_text.at(1);

                    if(std::find(list_char_dict.begin(), list_char_dict.end(), ch1) == list_char_dict.end()) {
                        list_char_dict.push_back(ch1);
                        SortCharacterList(list_char_dict);
                    }
                }

                if(in->matches.size() > 1) {
                    if(std::find(match_desc_list_char_dict.begin(), match_desc_list_char_dict.end(), ch0) == match_desc_list_char_dict.end()) {
                        match_desc_list_char_dict.push_back(ch0);
                        SortCharacterList(match_desc_list_char_dict);
                    }
                }
            }
        }

        const auto char_dict_count = list_char_dict.size();
        if(char_dict_count > UINT8_MAX) {
            TWL_R_FAIL(ResultUnknownResult);
        }

        u32 ch_empty_idx = UINT32_MAX;
        for(u32 i = 0; i < list_char_dict.size(); i++) {
            if(list_char_dict[i] == ' ') {
                ch_empty_idx = i;
                break;
            }
        }

        TWL_R_TRY(wf_list.Write<u8>(char_dict_count));
        TWL_R_TRY(wf_list.WriteVector(list_char_dict));
        
        TWL_R_TRY(wf_list.Write<u32>(input_count));

        size_t offsets_table_offset;
        TWL_R_TRY(wf_list.GetOffset(offsets_table_offset));

        auto offsets_table_buf = new u32[char_dict_count * char_dict_count]();
        ScopeGuard offsets_table_buf_delete([&]() {
            delete[] offsets_table_buf;
        });

        TWL_R_TRY(wf_list.MoveOffset(char_dict_count * char_dict_count * sizeof(u32)));

        size_t match_char_dict_count;
        size_t match_desc_offsets_table_offset;
        u32 *match_desc_offsets_table_buf = nullptr;
        ScopeGuard match_desc_offsets_table_buf_delete([&]() {
            if(match_desc_offsets_table_buf != nullptr) {
                delete[] match_desc_offsets_table_buf;
            }
        });
        if(wf_match_desc_list.has_value()) {
            match_char_dict_count = match_desc_list_char_dict.size();

            auto &match_desc_list_file = wf_match_desc_list.value();

            TWL_R_TRY(match_desc_list_file.get().Write<u8>(match_char_dict_count));
            TWL_R_TRY(match_desc_list_file.get().WriteVector(match_desc_list_char_dict));

            match_desc_offsets_table_buf = new u32[match_char_dict_count]();

            TWL_R_TRY(match_desc_list_file.get().GetOffset(match_desc_offsets_table_offset));

            TWL_R_TRY(match_desc_list_file.get().MoveOffset(match_char_dict_count * sizeof(u32)));
        }

        std::vector<size_t> input_start_offsets;
        for(const auto &in: this->inputs) {
            size_t input_entry_start_offset;
            TWL_R_TRY(wf_list.GetOffset(input_entry_start_offset));
            input_start_offsets.push_back(input_entry_start_offset);

            const auto match_count = in->matches.size();
            const size_t input_size = sizeof(u8) // u8 input_size
                                    + sizeof(u8) // u8 input_text_len
                                    + in->input_text.length() * sizeof(char) // char input_text[input_text_len]
                                    + sizeof(u16) // u16 lookup_list_idx
                                    + sizeof(u16) // u16 unk1
                                    + sizeof(u8) // u8 match_count
                                    + match_count * (
                                        sizeof(u16) // u16 file_id
                                        + sizeof(u16) // u16 match_list_idx
                                        + sizeof(u16) // u16 unk2
                                    );

            if(input_size > UINT8_MAX) {
                TWL_R_FAIL(ResultUnknownResult);
            }

            TWL_R_TRY(wf_lookup_offset_list.SetAbsoluteOffset(in->lookup_list_idx * sizeof(u32)));
            TWL_R_TRY(wf_lookup_offset_list.Write<u32>(input_entry_start_offset));

            if(in->input_text.length() >= 2) {
                const auto ch0 = in->input_text.at(0);
                const auto ch1 = in->input_text.at(1);
                u32 ch0_idx = UINT32_MAX;
                u32 ch1_idx = UINT32_MAX;
                for(u32 i = 0; i < list_char_dict.size(); i++) {
                    const auto dict_ch_i = list_char_dict.at(i);
                    if(dict_ch_i == ch0) {
                        ch0_idx = i;
                    }
                    if(dict_ch_i == ch1) {
                        ch1_idx = i;
                    }
                }

                if((ch0_idx == UINT32_MAX) || (ch1_idx == UINT32_MAX)) {
                    std::cout << "chars not in dict...? " << in->input_text << ": " << ch0 << ", " << ch1 << std::endl;
                    TWL_R_FAIL(ResultUnknownResult);
                }

                // For instance, for a word starting with 'AB', set both 'A ' and 'AB' offsets

                const auto cur_off = offsets_table_buf[ch1_idx + ch0_idx * char_dict_count];
                if(cur_off == 0) {
                    offsets_table_buf[ch1_idx + ch0_idx * char_dict_count] = input_entry_start_offset;
                }

                const auto cur_off_e = offsets_table_buf[ch_empty_idx + ch0_idx * char_dict_count];
                if(cur_off_e == 0) {
                    offsets_table_buf[ch_empty_idx + ch0_idx * char_dict_count] = input_entry_start_offset;
                }
            }

            TWL_R_TRY(wf_list.Write<u8>(input_size));
            TWL_R_TRY(wf_list.Write<u8>(in->input_text.length()));
            TWL_R_TRY(wf_list.WriteString(in->input_text));
            TWL_R_TRY(wf_list.Write(in->lookup_list_idx));
            TWL_R_TRY(wf_list.Write(in->unk1));
            TWL_R_TRY(wf_list.Write<u8>(match_count));

            for(const auto &match: in->matches) {
                TWL_R_TRY(wf_list.Write(match.file_id));
            }
            for(const auto &match: in->matches) {
                TWL_R_TRY(wf_list.Write(match.match_list_idx));
            }
            for(const auto &match: in->matches) {
                TWL_R_TRY(wf_list.Write(match.unk2));
            }

            size_t input_entry_end_offset;
            TWL_R_TRY(wf_list.GetOffset(input_entry_end_offset));

            if((input_entry_end_offset - input_entry_start_offset) != input_size) {
                std::cout << "bad input entry! " << input_size << " vs " << (input_entry_end_offset - input_entry_start_offset) << std::endl;
                TWL_R_FAIL(ResultUnknownResult);
            }

            if(wf_match_desc_list.has_value()) {
                auto &match_desc_list_file = wf_match_desc_list.value();
    
                if(match_count > 1) {
                    size_t match_desc_entry_start_offset;
                    TWL_R_TRY(match_desc_list_file.get().GetOffset(match_desc_entry_start_offset));
                    
                    if(in->input_text.length() >= 1) {
                        const auto ch0 = in->input_text.at(0);
                        u32 ch0_idx = UINT32_MAX;
                        for(u32 i = 0; i < match_desc_list_char_dict.size(); i++) {
                            const auto dict_ch_i = match_desc_list_char_dict.at(i);
                            if(dict_ch_i == ch0) {
                                ch0_idx = i;
                                break;
                            }
                        }

                        if(ch0_idx == UINT32_MAX) {
                            std::cout << "char not in match desc dict...? " << in->input_text << ": " << ch0 << std::endl;
                            TWL_R_FAIL(ResultUnknownResult);
                        }
        
                        const auto cur_off = match_desc_offsets_table_buf[ch0_idx];
                        if(cur_off == 0) {
                            match_desc_offsets_table_buf[ch0_idx] = match_desc_entry_start_offset;
                        }
                    }

                    TWL_R_TRY(match_desc_list_file.get().Write<u8>(in->input_text.length()));
                    TWL_R_TRY(match_desc_list_file.get().WriteString(in->input_text));

                    TWL_R_TRY(match_desc_list_file.get().Write<u8>(match_count));

                    for(const auto &match: in->matches) {
                        TWL_R_TRY(match_desc_list_file.get().Write(match.unk3));
                    }

                    for(const auto &match: in->matches) {
                        TWL_R_TRY(match_desc_list_file.get().Write<u8>(match.description.length()));
                        TWL_R_TRY(match_desc_list_file.get().WriteString(match.description));
                    }
                }
            }
        }

        for(const auto &in: this->inputs) {
            for(const auto &match: in->matches) {
                TWL_R_TRY(wf_match_offset_list.SetAbsoluteOffset(match.match_list_idx * sizeof(u32)));

                auto base_in = (match.redir_input != nullptr) ? match.redir_input : in;
                auto it = std::find(this->inputs.begin(), this->inputs.end(), base_in);
                const auto offset_i = std::distance(this->inputs.begin(), it);
                const auto input_entry_start_offset = input_start_offsets.at(offset_i);
                TWL_R_TRY(wf_match_offset_list.Write<u32>(input_entry_start_offset));
            }
        }

        TWL_R_TRY(wf_list.SetAbsoluteOffset(offsets_table_offset));
        TWL_R_TRY(wf_list.WriteBuffer(offsets_table_buf, char_dict_count * char_dict_count * sizeof(u32)));
        
        if(wf_match_desc_list.has_value()) {
            auto &match_desc_list_file = wf_match_desc_list.value();

            TWL_R_TRY(match_desc_list_file.get().SetAbsoluteOffset(match_desc_offsets_table_offset));
            TWL_R_TRY(match_desc_list_file.get().WriteBuffer(match_desc_offsets_table_buf, match_char_dict_count * sizeof(u32)));
        }

        TWL_R_SUCCEED();
    }

}
