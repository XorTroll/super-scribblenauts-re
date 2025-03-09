#pragma once
#include <objnaut/bh2p/bh2p_Base.hpp>
#include <objnaut/def/def_TextList.hpp>

namespace objnaut::bh2p::def {

    using TextListDefinition = objnaut::def::TextListDefinition<Language>;

    constexpr TextListDefinition DataRwFailureTextList = { .file_id = 273 };
    constexpr TextListDefinition ActionsTextList = { .file_id = 272 };
    // 275, 276, 277, 278?
    constexpr TextListDefinition LevelEditorTextList = { .file_id = 279 };
    constexpr TextListDefinition LevelEditor2TextList = { .file_id = 71 };
    constexpr TextListDefinition MeritsTextList = { .file_id = 281 };
    constexpr TextListDefinition FriendWfcTextList = { .file_id = 285 };
    constexpr TextListDefinition MiscTextList = { .file_id = 280 };
    constexpr TextListDefinition Misc2TextList = { .file_id = 29065 };

}
