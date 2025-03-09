#include <objnaut/io/io_FileSystem.hpp>
#include <twl/util/util_Compression.hpp>

namespace objnaut::io {

    Result FileSystem::ReadFrom(fs::File &rf_index, fs::File &rf_package) {
        this->files.clear();

        u32 file_count;
        TWL_R_TRY(rf_index.Read(file_count));

        // The offset table has actually "count + 1" offsets, where the last two ones are probably always equal

        auto file_offsets = new u32[file_count + 1]();
        ScopeGuard cleanup([&]() {
            delete[] file_offsets;
        });
        
        TWL_R_TRY(rf_index.ReadBuffer(file_offsets, (file_count + 1) * sizeof(u32)));

        for(u32 i = 0; i < file_count; i++) {
            const auto file_offset = file_offsets[i];

            // Since there are "count + 1" offsets, this is always fine
            const auto file_size = file_offsets[i + 1] - file_offsets[i];

            auto &file = this->files.emplace_back();

            // There are multiple empty files in the table, actually...
            if(file_size > 0) {
                TWL_R_TRY(rf_package.SetAbsoluteOffset(file_offset));

                auto file_buf = new u8[file_size]();
                TWL_R_TRY(rf_package.ReadBuffer(file_buf, file_size));

                // Non-LZ-compressed files always end with an extra "0x00" byte, and compressed ones end with an extra "0x01" byte
                // LZ-compressed files always end with an extra "0x01" byte, to distinguish them from compressed ones
                const auto file_type = *(file_buf + file_size - 1);
                if(file_type == 0) {
                    // Exclude the ending "file-type" byte
                    file.buf.CreateFrom(file_buf, file_size - sizeof(u8), true);
                    file.was_compressed = false;
                }
                else if(file_type == 1) {
                    // Time to decompress
                    u8 *dec_file_buf;
                    size_t dec_file_size;
                    TWL_R_TRY(util::LzDecompress(file_buf, dec_file_buf, dec_file_size));

                    delete[] file_buf;

                    file.buf.CreateFrom(dec_file_buf, dec_file_size, true);
                    file.was_compressed = true;
                }
                else {
                    TWL_R_TRY(ResultFileSystemInvalidCompressionType);
                }
            }
        }

        TWL_R_SUCCEED();
    }

    Result FileSystem::WriteTo(fs::File &wf_index, fs::File &wf_package) {
        TWL_R_TRY(wf_index.Write<u32>(this->files.size()));
        
        size_t cur_offset;
        u32 i = 0;
        for(auto &file: this->files) {
            TWL_R_TRY(wf_package.GetOffset(cur_offset));
            TWL_R_TRY(wf_index.Write<u32>(cur_offset));

            if(file.buf.IsValid()) {
                if(file.was_compressed) {
                    u8 *comp_file_buf;
                    size_t comp_file_size;
                    TWL_R_TRY(util::LzCompressV10((const u8*)file.buf.GetBuffer(), file.buf.GetBufferSize(), comp_file_buf, comp_file_size));

                    TWL_R_TRY(wf_package.WriteBuffer(comp_file_buf, comp_file_size));
                    TWL_R_TRY(wf_package.Write<u8>(0x01));

                    delete[] comp_file_buf;
                }
                else {
                    TWL_R_TRY(wf_package.WriteBuffer(file.buf.GetBuffer(), file.buf.GetBufferSize()));
                    TWL_R_TRY(wf_package.Write<u8>(0x00));
                }
            }

            i++;
        }

        TWL_R_TRY(wf_package.GetOffset(cur_offset));
        TWL_R_TRY(wf_index.Write<u32>(cur_offset));
        TWL_R_SUCCEED();
    }

}
