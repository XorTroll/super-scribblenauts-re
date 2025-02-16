
#pragma once
#include <objnaut/fmt/fmt_InputDictionary.hpp>
#include <objnaut/fs/fs_FileSystem.hpp>

namespace objnaut::def {

    struct InputDictionaryEntry {
        u16 list_file_id;
        u16 match_offset_list_file_id;
        u16 lookup_offset_list_file_id;
        std::optional<u16> match_desc_list_file_id;
    
        inline Result ReadFrom(objnaut::fs::FileSystem &fs, fmt::InputDictionary &dict) const {
            auto &list_file = fs.GetFile(this->list_file_id);
            TWL_R_TRY(list_file.OpenRead(twl::fs::FileCompression::None));
            ScopeGuard list_file_close([&]() {
                list_file.Close();
            });
    
            auto &match_offset_list_file = fs.GetFile(this->match_offset_list_file_id);
            TWL_R_TRY(match_offset_list_file.OpenRead(twl::fs::FileCompression::None));
            ScopeGuard match_offset_list_file_close([&]() {
                match_offset_list_file.Close();
            });
    
            auto &lookup_offset_list_file = fs.GetFile(this->lookup_offset_list_file_id);
            TWL_R_TRY(lookup_offset_list_file.OpenRead(twl::fs::FileCompression::None));
            ScopeGuard lookup_offset_list_file_close([&]() {
                lookup_offset_list_file.Close();
            });
            
            std::optional<std::reference_wrapper<twl::fs::File>> match_desc_list_file = {};
            if(this->match_desc_list_file_id.has_value()) {
                match_desc_list_file = std::reference_wrapper<twl::fs::File>(fs.GetFile(this->match_desc_list_file_id.value()));
                TWL_R_TRY(match_desc_list_file.value().get().OpenRead(twl::fs::FileCompression::None));
            }
            ScopeGuard match_desc_list_file_close([&]() {
                if(this->match_desc_list_file_id.has_value()) {
                    match_desc_list_file.value().get().Close();
                }
            });
    
            TWL_R_TRY(dict.ReadFrom(list_file, match_offset_list_file, lookup_offset_list_file, match_desc_list_file));
            TWL_R_SUCCEED();
        }

        inline Result WriteTo(objnaut::fs::FileSystem &fs, fmt::InputDictionary &dict) const {
            auto &list_file = fs.GetFile(this->list_file_id);
            TWL_R_TRY(list_file.OpenWrite());
            ScopeGuard list_file_close([&]() {
                list_file.Close();
            });
    
            auto &match_offset_list_file = fs.GetFile(this->match_offset_list_file_id);
            TWL_R_TRY(match_offset_list_file.OpenWrite());
            ScopeGuard match_offset_list_file_close([&]() {
                match_offset_list_file.Close();
            });
    
            auto &lookup_offset_list_file = fs.GetFile(this->lookup_offset_list_file_id);
            TWL_R_TRY(lookup_offset_list_file.OpenWrite());
            ScopeGuard lookup_offset_list_file_close([&]() {
                lookup_offset_list_file.Close();
            });
            
            std::optional<std::reference_wrapper<twl::fs::File>> match_desc_list_file = {};
            if(this->match_desc_list_file_id.has_value()) {
                match_desc_list_file = std::reference_wrapper<twl::fs::File>(fs.GetFile(this->match_desc_list_file_id.value()));
                TWL_R_TRY(match_desc_list_file.value().get().OpenWrite());
            }
            ScopeGuard match_desc_list_file_close([&]() {
                if(this->match_desc_list_file_id.has_value()) {
                    match_desc_list_file.value().get().Close();
                }
            });
    
            TWL_R_TRY(dict.WriteTo(list_file, match_offset_list_file, lookup_offset_list_file, match_desc_list_file));
            TWL_R_SUCCEED();
        }
    };

    constexpr InputDictionaryEntry ObjectDictionaries[] = {
        {
            .list_file_id = 13220,
            .match_offset_list_file_id = 13251,
            .lookup_offset_list_file_id = 32173,
            .match_desc_list_file_id = 13236
        },
        {
            .list_file_id = 13228,
            .match_offset_list_file_id = 13250,
            .lookup_offset_list_file_id = 32171,
            .match_desc_list_file_id = 13235
        },
        {
            .list_file_id = 13225,
            .match_offset_list_file_id = 13253,
            .lookup_offset_list_file_id = 32175,
            .match_desc_list_file_id = 13238
        },
        {
            .list_file_id = 13219,
            .match_offset_list_file_id = 13255,
            .lookup_offset_list_file_id = 32176,
            .match_desc_list_file_id = 13240
        },
        {
            .list_file_id = 13227,
            .match_offset_list_file_id = 13256,
            .lookup_offset_list_file_id = 32177,
            .match_desc_list_file_id = 13241
        },
        {
            .list_file_id = 13221,
            .match_offset_list_file_id = 13262,
            .lookup_offset_list_file_id = 32180,
            .match_desc_list_file_id = 13246
        },
        {
            .list_file_id = 24063,
            .match_offset_list_file_id = 24064,
            .lookup_offset_list_file_id = 32172,
            .match_desc_list_file_id = 24073
        }
    };

    constexpr InputDictionaryEntry AdjectiveDictionaries[] = {
        {
            .list_file_id = 13267,
            .match_offset_list_file_id = 13282,
            .lookup_offset_list_file_id = 32161,
            .match_desc_list_file_id = {}
        },
        {
            .list_file_id = 13275,
            .match_offset_list_file_id = 13281,
            .lookup_offset_list_file_id = 32159,
            .match_desc_list_file_id = {}
        },
        {
            .list_file_id = 13272,
            .match_offset_list_file_id = 13284,
            .lookup_offset_list_file_id = 32163,
            .match_desc_list_file_id = {}
        },
        {
            .list_file_id = 13266,
            .match_offset_list_file_id = 13290,
            .lookup_offset_list_file_id = 32164,
            .match_desc_list_file_id = {}
        },
        {
            .list_file_id = 13274,
            .match_offset_list_file_id = 13291,
            .lookup_offset_list_file_id = 32165,
            .match_desc_list_file_id = {}
        },
        {
            .list_file_id = 13268,
            .match_offset_list_file_id = 13295,
            .lookup_offset_list_file_id = 32168,
            .match_desc_list_file_id = {}
        },
        {
            .list_file_id = 24074,
            .match_offset_list_file_id = 24075,
            .lookup_offset_list_file_id = 32160,
            .match_desc_list_file_id = {}
        }
    };

}
