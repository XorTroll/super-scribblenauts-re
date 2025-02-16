
#pragma once
#include <twl/twl_Include.hpp>

#include <memory>
#include <optional>
#include <algorithm>

namespace objnaut {

    using namespace twl;

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
