
#pragma once
#include <objnaut/base.hpp>
#include <twl/fs/fs_FileFormat.hpp>

namespace objnaut::fmt {
    
    struct Input;

    struct InputMatch {
        u16 file_id;
        u16 match_list_idx;
        u16 unk2;
        std::string description;
        u16 unk3;
        std::shared_ptr<Input> redir_input;
    };

    struct Input {
        std::string input_text;
        u16 lookup_list_idx;
        u16 unk1;
        std::vector<InputMatch> matches;
    };

    struct InputDictionary {
        std::vector<std::shared_ptr<Input>> inputs;

        Result ReadFrom(twl::fs::File &rf_list, twl::fs::File &rf_match_offset_list, twl::fs::File &rf_lookup_offset_list, std::optional<std::reference_wrapper<twl::fs::File>> &rf_match_desc_list);
        Result WriteTo(twl::fs::File &wf_list, twl::fs::File &wf_match_offset_list, twl::fs::File &wf_lookup_offset_list, std::optional<std::reference_wrapper<twl::fs::File>> &wf_match_desc_list);
    };

}
