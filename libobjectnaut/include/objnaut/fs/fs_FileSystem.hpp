
#pragma once
#include <objnaut/base.hpp>
#include <twl/fs/fs_File.hpp>

namespace objnaut::fs {

    struct File {
        twl::fs::BufferFile buf;
        bool was_compressed;

        inline bool IsValid() {
            return this->buf.IsValid();
        }

        inline void Dispose() {
            this->buf.Dispose();
        }

        constexpr File() : buf(), was_compressed(false) {}
    };

    struct FileSystem {
        std::vector<File> files;

        Result ReadFrom(twl::fs::File &rf_1i, twl::fs::File &rf_1p);
        Result WriteTo(twl::fs::File &wf_1i, twl::fs::File &wf_1p);

        inline void Dispose() {
            for(auto &file: this->files) {
                file.Dispose();
            }

            this->files.clear();
        }

        inline twl::fs::BufferFile &GetFile(const u16 file_id) {
            return this->files.at(file_id).buf;
        }
    };

}
