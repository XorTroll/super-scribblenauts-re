
#pragma once
#include <objnaut/objnaut_Base.hpp>
#include <twl/fs/fs_FileFormat.hpp>

namespace objnaut::fmt {

    template<class L>
    struct TextList : public fs::FileFormat {
        static constexpr char TextDelimiter = '\n';
        static constexpr size_t Count = static_cast<size_t>(L::Count);

        std::vector<std::string> lang_texts[Count];

        TextList() {}
        TextList(const TextList&) = delete;
        TextList(TextList&&) = default;

        inline size_t GetCount() {
            return this->lang_texts[0].size();
        }

        inline std::string &Get(const L lang, const u32 text_i) {
            return this->lang_texts[static_cast<size_t>(lang)].at(text_i);
        }

        inline void Set(const L lang, const u32 text_i, const std::string &text) {
            this->lang_texts[static_cast<size_t>(lang)].at(text_i) = text;
        }

        inline Result ReadValidateFrom(fs::File&) override {
            TWL_R_SUCCEED();
        }

        Result ReadAllFrom(fs::File &rf) override;
        Result WriteTo(fs::File &wf) override;
    };

    template<class L>
    Result TextList<L>::ReadAllFrom(fs::File &rf) {
        u8 text_count_per_lang;
        TWL_R_TRY(rf.Read(text_count_per_lang));

        for(u32 i = 0; i < static_cast<u32>(L::Count); i++) {
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

    template<class L>
    Result TextList<L>::WriteTo(fs::File &wf) {
        const auto text_count_per_lang = this->lang_texts[0].size();
        for(u32 i = 1; i < static_cast<u32>(L::Count); i++) {
            if(this->lang_texts[i].size() != text_count_per_lang) {
                TWL_R_FAIL(ResultTextListTextCountMismatch);
            }
        }

        if(text_count_per_lang > 0xFF) {
            TWL_R_FAIL(ResultTextListTextCountMismatch);
        }

        TWL_R_TRY(wf.Write<u8>(text_count_per_lang));

        for(u32 i = 0; i < static_cast<u32>(L::Count); i++) {
            auto &lang_text_list = this->lang_texts[i];

            for(const auto &text: lang_text_list) {
                TWL_R_TRY(wf.WriteString(text));
                TWL_R_TRY(wf.Write<u8>(TextDelimiter));
            }
        }

        TWL_R_SUCCEED();
    }

}
