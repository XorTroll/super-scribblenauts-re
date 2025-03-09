#pragma once
#include <objnaut/fmt/fmt_TextList.hpp>
#include <objnaut/io/io_FileSystem.hpp>

namespace objnaut::def {

    template<class L>
    struct TextListDefinition {
        u16 file_id;

        inline Result ReadFrom(io::FileSystem &fs, fmt::TextList<L> &list) const {
            auto &text_list_file = fs.GetFile(this->file_id);
            TWL_R_TRY(text_list_file.OpenRead(fs::FileCompression::None));
            ScopeGuard list_file_close([&]() {
                text_list_file.Close();
            });

            TWL_R_TRY(list.ReadFrom(text_list_file));
            TWL_R_SUCCEED();
        }
    
    };

}
