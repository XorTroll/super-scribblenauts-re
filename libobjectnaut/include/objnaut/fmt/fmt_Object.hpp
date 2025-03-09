
#pragma once
#include <objnaut/objnaut_Object.hpp>
#include <twl/fs/fs_FileFormat.hpp>

namespace objnaut::fmt {

    struct Object : public objnaut::Object, public twl::fs::FileFormat {
        Object() {}
        Object(const Object&) = delete;
        Object(Object&&) = default;

        inline Result ReadValidateFrom(twl::fs::File&) override {
            TWL_R_SUCCEED();
        }

        Result ReadAllFrom(twl::fs::File &rf) override;
        Result WriteTo(twl::fs::File &wf) override;
    };

}
