
#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include <algorithm>
#include <vector>
#include <twl/twl_Include.hpp>

namespace objnaut {

    using namespace twl;
    
    constexpr Result ResultTextListTextCountMismatch = 0xb200;

    constexpr Result ResultDictionaryDetailMeaningMismatch = 0xb201;
    constexpr Result ResultDictionaryWordCountOverflow = 0xb202;
    constexpr Result ResultDictionaryCharacterOverflow = 0xb203;
    constexpr Result ResultDictionaryWordEntryOverflow = 0xb204;
    constexpr Result ResultDictionaryCharacterTableMismatch = 0xb205;
    constexpr Result ResultDictionaryWordEntrySizeMismatch = 0xb206;

    constexpr Result ResultFileSystemInvalidCompressionType = 0xb207;

    constexpr Result ResultObjectModifyAtrRepListTagMismatch = 0xb208;
    constexpr Result ResultObjectInvalidActionType = 0xb209;
    constexpr Result ResultObjectInvalidTriggerType = 0xb20a;
    constexpr Result ResultObjectInvalidFrameType = 0xb20b;
    constexpr Result ResultObjectGenericTagMismatch = 0xb20c;
    constexpr Result ResultObjectMovementTagMismatch = 0xb20d;
    constexpr Result ResultObjectAiTagMismatch = 0xb20e;
    constexpr Result ResultObjectContainerTagMismatch = 0xb20f;
    constexpr Result ResultObjectElectricityTagMismatch = 0xb210;
    constexpr Result ResultObjectPlacementTagMismatch = 0xb211;
    constexpr Result ResultObjectPhysicsTagMismatch = 0xb212;
    constexpr Result ResultObjectTemperatureTagMismatch = 0xb213;
    constexpr Result ResultObjectTriggersActionsTagMismatch = 0xb214;
    constexpr Result ResultObjectFramesTagMismatch = 0xb215;
    constexpr Result ResultObjectAudioTagMismatch = 0xb216;
    constexpr Result ResultObjectAttackTagMismatch = 0xb217;

    constexpr ResultDescriptionEntry ResultDescriptionTable[] = {
        { ResultTextListTextCountMismatch, "Invalid" },

        { ResultDictionaryDetailMeaningMismatch, "Invalid" },
        { ResultDictionaryWordCountOverflow, "Invalid" },
        { ResultDictionaryCharacterOverflow, "Invalid" },
        { ResultDictionaryWordEntryOverflow, "Invalid" },
        { ResultDictionaryCharacterTableMismatch, "Invalid" },
        { ResultDictionaryWordEntrySizeMismatch, "Invalid" },

        { ResultFileSystemInvalidCompressionType, "Invalid" },

        { ResultObjectModifyAtrRepListTagMismatch, "Invalid" },
        { ResultObjectInvalidActionType, "Invalid" },
        { ResultObjectInvalidTriggerType, "Invalid" },
        { ResultObjectInvalidFrameType, "Invalid" },
        { ResultObjectGenericTagMismatch, "Invalid" },
        { ResultObjectMovementTagMismatch, "Invalid" },
        { ResultObjectAiTagMismatch, "Invalid" },
        { ResultObjectContainerTagMismatch, "Invalid" },
        { ResultObjectElectricityTagMismatch, "Invalid" },
        { ResultObjectPlacementTagMismatch, "Invalid" },
        { ResultObjectPhysicsTagMismatch, "Invalid" },
        { ResultObjectTemperatureTagMismatch, "Invalid" },
        { ResultObjectTriggersActionsTagMismatch, "Invalid" },
        { ResultObjectFramesTagMismatch, "Invalid" },
        { ResultObjectAudioTagMismatch, "Invalid" },
        { ResultObjectAttackTagMismatch, "Invalid" },
    };

    inline constexpr Result GetResultDescription(const Result rc, std::string &out_desc) {
        TWL_R_TRY(twl::GetResultDescription(rc, out_desc));

        for(u32 i = 0; i < std::size(ResultDescriptionTable); i++) {
            if(ResultDescriptionTable[i].first.value == rc.value) {
                out_desc = ResultDescriptionTable[i].second;
                TWL_R_SUCCEED(); 
            }
        }

        TWL_R_FAIL(ResultUnknownResult);
    }

    inline std::string FormatResult(const Result rc) {
        std::string desc = "<unknown error: " + std::to_string(rc.value) + ">";
        objnaut::GetResultDescription(rc, desc);
        return desc;
    }

    using s8 = i8;
    using s16 = i16;
    using s32 = i32;
    using s64 = i64;

    using fx32 = s32;

    #define OBJNAUT_ENUM_BIT_OPERATORS(enum_type, base_type) \
    inline constexpr enum_type operator|(enum_type lhs, enum_type rhs) { \
        return static_cast<enum_type>(static_cast<base_type>(lhs) | static_cast<base_type>(rhs)); \
    } \
    inline constexpr enum_type operator&(enum_type lhs, enum_type rhs) { \
        return static_cast<enum_type>(static_cast<base_type>(lhs) & static_cast<base_type>(rhs)); \
    }

    #define OBJNAUT_BITMASK(n) (1 << n)

    #define OBJNAUT_PACKED __attribute__((packed))

}
