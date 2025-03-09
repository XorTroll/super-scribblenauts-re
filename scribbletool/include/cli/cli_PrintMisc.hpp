
#pragma once
#include <common.hpp>

namespace cli {

    void ListObjects(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &lang_str);
    void ListAdjectives(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &lang_str);
    void PrintTexts(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &file_id_str, const std::string &lang_str);

}
