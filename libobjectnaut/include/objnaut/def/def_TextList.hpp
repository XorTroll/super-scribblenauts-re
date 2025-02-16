#pragma once
#include <objnaut/fmt/fmt_TextList.hpp>
#include <objnaut/fs/fs_FileSystem.hpp>

namespace objnaut::def {

    struct TextListEntry {
        u16 file_id;

        inline Result ReadFrom(objnaut::fs::FileSystem &fs, fmt::TextList &list) const {
            auto &text_list_file = fs.GetFile(this->file_id);
            TWL_R_TRY(text_list_file.OpenRead(twl::fs::FileCompression::None));
            ScopeGuard list_file_close([&]() {
                text_list_file.Close();
            });

            TWL_R_TRY(list.ReadFrom(text_list_file));
            TWL_R_SUCCEED();
        }
    
    };

    constexpr TextListEntry DataRwFailureTextList = { .file_id = 273 };
    constexpr TextListEntry ActionsTextList = { .file_id = 272 };
    // 275, 276, 277, 278?
    constexpr TextListEntry LevelEditorTextList = { .file_id = 279 };
    constexpr TextListEntry LevelEditor2TextList = { .file_id = 71 };
    constexpr TextListEntry MeritsTextList = { .file_id = 281 };
    constexpr TextListEntry FriendWfcTextList = { .file_id = 285 };
    constexpr TextListEntry MiscTextList = { .file_id = 280 };
    constexpr TextListEntry Misc2TextList = { .file_id = 29065 };

}
