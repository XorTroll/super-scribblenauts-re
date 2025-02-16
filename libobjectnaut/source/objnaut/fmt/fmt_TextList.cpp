#include <objnaut/fmt/fmt_TextList.hpp>

namespace objnaut::fmt {

    Result TextList::ReadAllFrom(fs::File &rf) {
        u8 text_count_per_lang;
        TWL_R_TRY(rf.Read(text_count_per_lang));

        for(u32 i = 0; i < static_cast<u32>(Language::Count); i++) {
            auto &lang_text_list = this->lang_texts[i];

            lang_text_list.clear();
            lang_text_list.reserve(text_count_per_lang);
            for(u32 j = 0; j < text_count_per_lang; j++) {
                std::string cur_text;
                TWL_R_TRY(rf.ReadTerminatedString(cur_text, TextDelimiter));
                lang_text_list.push_back(cur_text);
            }
        }

        TWL_R_SUCCEED();
    }

    Result TextList::WriteTo(fs::File &wf) {
        const auto text_count_per_lang = this->lang_texts[0].size();
        for(u32 i = 1; i < static_cast<u32>(Language::Count); i++) {
            if(this->lang_texts[i].size() != text_count_per_lang) {
                // TODO: error!
                TWL_R_FAIL(ResultUnknownResult);
            }
        }

        if(text_count_per_lang > 0xFF) {
            TWL_R_FAIL(ResultUnknownResult);
        }

        TWL_R_TRY(wf.Write<u8>(text_count_per_lang));

        for(u32 i = 0; i < static_cast<u32>(Language::Count); i++) {
            auto &lang_text_list = this->lang_texts[i];

            for(const auto &text: lang_text_list) {
                TWL_R_TRY(wf.WriteString(text));
                TWL_R_TRY(wf.Write<u8>(TextDelimiter));
            }
        }

        TWL_R_SUCCEED();
    }

}
