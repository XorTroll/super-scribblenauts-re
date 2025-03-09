
#pragma once
#include <objnaut/fmt/fmt_Dictionary.hpp>
#include <objnaut/io/io_FileSystem.hpp>

namespace objnaut::def {

    struct DictionaryDefinition {
        u16 dict_file_id;
        u16 jump_table_file_id;
        u16 word_table_file_id;
        std::optional<u16> details_file_id;
    
        inline Result ReadFrom(io::FileSystem &fs, fmt::Dictionary &dict) const {
            auto &dict_file = fs.GetFile(this->dict_file_id);
            TWL_R_TRY(dict_file.OpenRead(fs::FileCompression::None));
            ScopeGuard dict_file_close([&]() {
                dict_file.Close();
            });
    
            auto &jump_table_file = fs.GetFile(this->jump_table_file_id);
            TWL_R_TRY(jump_table_file.OpenRead(fs::FileCompression::None));
            ScopeGuard jump_table_file_close([&]() {
                jump_table_file.Close();
            });
    
            auto &word_table_file = fs.GetFile(this->word_table_file_id);
            TWL_R_TRY(word_table_file.OpenRead(fs::FileCompression::None));
            ScopeGuard word_table_file_close([&]() {
                word_table_file.Close();
            });
            
            std::optional<std::reference_wrapper<fs::File>> details_file = {};
            if(this->details_file_id.has_value()) {
                details_file = std::reference_wrapper<fs::File>(fs.GetFile(this->details_file_id.value()));
                TWL_R_TRY(details_file.value().get().OpenRead(fs::FileCompression::None));
            }
            ScopeGuard details_file_close([&]() {
                if(this->details_file_id.has_value()) {
                    details_file.value().get().Close();
                }
            });
    
            TWL_R_TRY(dict.ReadFrom(dict_file, jump_table_file, word_table_file, details_file));
            TWL_R_SUCCEED();
        }

        inline Result WriteTo(io::FileSystem &fs, fmt::Dictionary &dict) const {
            auto &dict_file = fs.GetFile(this->dict_file_id);
            TWL_R_TRY(dict_file.OpenWrite());
            ScopeGuard dict_file_close([&]() {
                dict_file.Close();
            });
    
            auto &jump_table_file = fs.GetFile(this->jump_table_file_id);
            TWL_R_TRY(jump_table_file.OpenWrite());
            ScopeGuard jump_table_file_close([&]() {
                jump_table_file.Close();
            });
    
            auto &word_table_file = fs.GetFile(this->word_table_file_id);
            TWL_R_TRY(word_table_file.OpenWrite());
            ScopeGuard word_table_file_close([&]() {
                word_table_file.Close();
            });
            
            std::optional<std::reference_wrapper<fs::File>> details_file = {};
            if(this->details_file_id.has_value()) {
                details_file = std::reference_wrapper<fs::File>(fs.GetFile(this->details_file_id.value()));
                TWL_R_TRY(details_file.value().get().OpenWrite());
            }
            ScopeGuard details_file_close([&]() {
                if(this->details_file_id.has_value()) {
                    details_file.value().get().Close();
                }
            });
    
            TWL_R_TRY(dict.WriteTo(dict_file, jump_table_file, word_table_file, details_file));
            TWL_R_SUCCEED();
        }
    };

}
