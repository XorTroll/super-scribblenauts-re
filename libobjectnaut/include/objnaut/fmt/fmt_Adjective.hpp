
#pragma once
#include <objnaut/objnaut_Adjective.hpp>
#include <twl/fs/fs_FileFormat.hpp>

namespace objnaut::fmt {

    struct Adjective : public objnaut::Adjective, public twl::fs::FileFormat {
        Adjective() {}
        Adjective(const Adjective&) = delete;
        Adjective(Adjective&&) = default;

        inline Result ReadValidateFrom(twl::fs::File&) override {
            TWL_R_SUCCEED();
        }

        Result ReadAllFrom(twl::fs::File &rf) override;
        Result WriteTo(twl::fs::File &wf) override;
    };

}
