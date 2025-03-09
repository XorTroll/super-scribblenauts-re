
#pragma once
#include <objnaut/objnaut_Base.hpp>

namespace objnaut::bh2p {

    // Slightly different from base DS(i) system language values

    enum class Language {
        English = 0,
        Dutch = 1,
        French = 2,
        German = 3,
        Italian = 4,
        Spanish = 5,

        Count,

        UnkSpecial = 6
    };

}
