
#pragma once
#include <objnaut/objnaut_Base.hpp>
#include <twl/fs/fs_File.hpp>

namespace objnaut::io {

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

        Result ReadFrom(fs::File &rf_index, fs::File &rf_package);
        Result WriteTo(fs::File &wf_index, fs::File &wf_package);

        inline void Dispose() {
            for(auto &file: this->files) {
                file.Dispose();
            }

            this->files.clear();
        }

        inline twl::fs::BufferFile &GetFile(const u16 file_id) {
            return this->files.at(file_id).buf;
        }

        inline bool HasFile(const u16 file_id) {
            return this->files.size() > file_id && this->files.at(file_id).IsValid();
        }
    };

}
