
#pragma once
#include <objnaut/base.hpp>
#include <twl/fs/fs_FileFormat.hpp>

namespace objnaut::fmt {

    struct TextList : public twl::fs::FileFormat {
        static constexpr char TextDelimiter = '\n';

        std::vector<std::string> lang_texts[static_cast<u32>(Language::Count)];

        TextList() {}
        TextList(const TextList&) = delete;
        TextList(TextList&&) = default;

        inline size_t GetCount() {
            return this->lang_texts[0].size();
        }

        inline std::string &Get(const Language lang, const u32 text_i) {
            return this->lang_texts[static_cast<u32>(lang)].at(text_i);
        }

        inline void Set(const Language lang, const u32 text_i, const std::string &text) {
            this->lang_texts[static_cast<u32>(lang)].at(text_i) = text;
        }

        inline Result ReadValidateFrom(twl::fs::File &rf) override {
            TWL_R_SUCCEED();
        }

        Result ReadAllFrom(twl::fs::File &rf) override;
        Result WriteTo(twl::fs::File &wf) override;
    };

}
