
#pragma once
#include <common.hpp>

bool TryExportBh2pTexture(io::FileSystem &fs, const u16 file_id, const std::string &out_png_path);
bool TryExportRemixTexture(io::FileSystem &fs, const u16 file_id, const std::string &out_png_path);

namespace cli {

    void ExportTexture(const std::string &in_index, const std::string &in_package, const std::string &game, const std::string &file_id_str, const std::string &out_png_path);

}
