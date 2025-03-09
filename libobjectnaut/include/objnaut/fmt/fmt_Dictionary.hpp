
#pragma once
#include <objnaut/objnaut_Base.hpp>
#include <twl/fs/fs_FileFormat.hpp>

namespace objnaut::fmt {
    
    struct Word;

    struct WordMeaning {
        u16 file_id;
        u16 adj_obj_id;
        u16 unk2;
        std::string obj_detail_text;
        u16 unk3_object_id;
        std::shared_ptr<Word> redir_word;
    };

    struct Word {
        std::string name;
        u16 word_id;
        u16 unk1_zero;
        std::vector<WordMeaning> meanings;
    };

    struct Dictionary {
        std::vector<std::shared_ptr<Word>> words;

        Result ReadFrom(twl::fs::File &rf_dict, twl::fs::File &rf_jump_table, twl::fs::File &rf_word_table, std::optional<std::reference_wrapper<twl::fs::File>> &rf_details);
        Result WriteTo(twl::fs::File &wf_dict, twl::fs::File &wf_jump_table, twl::fs::File &wf_word_table, std::optional<std::reference_wrapper<twl::fs::File>> &wf_details);
    };

}
