#include <cli/cli_ExportTexture.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

bool TryExportBh2pTexture(io::FileSystem &fs, const u16 file_id, const std::string &out_png_path) {
    struct stat st;
    if((stat(out_png_path.c_str(), &st) == 0) && S_ISREG(st.st_mode)) {
        return true;
    }
    if(!fs.HasFile(file_id)) {
        return false;
    }

    auto &tex_file = fs.GetFile(file_id);
    R_TRY_ERRLOG_BOOL(tex_file.OpenRead(fs::FileCompression::None), "Unable to open texture file");
    ScopeGuard close([&]() {
        tex_file.Close();
    });

    u8 color_count;
    R_TRY_ERRLOG_BOOL(tex_file.Read(color_count), "Unable to read color count");
    auto color_buf = std::make_unique<u16[]>(color_count);
    R_TRY_ERRLOG_BOOL(tex_file.ReadBuffer(color_buf.get(), color_count * sizeof(u16)), "Unable to read colors");

    u8 tex_w;
    R_TRY_ERRLOG_BOOL(tex_file.Read(tex_w), "Unable to read texture width");
    u8 tex_h;
    R_TRY_ERRLOG_BOOL(tex_file.Read(tex_h), "Unable to read texture height");

    const auto char_buf_size = (tex_w * tex_h) / sizeof(u16);
    auto char_buf = std::make_unique<u8[]>(char_buf_size);
    R_TRY_ERRLOG_BOOL(tex_file.ReadBuffer(char_buf.get(), char_buf_size), "Unable to read character data");

    auto out_rgba = std::make_unique<u32[]>(tex_w * tex_h);
    for(size_t i = 0; i < char_buf_size; i++) {
        const auto pix1 = char_buf[i] & 0xF;
        const auto pix2 = (char_buf[i] & 0xF0) >> 4;
    
        #define CONV_COLOR(v, idx) { \
            twl::gfx::xbgr1555::Color in_clr = { \
                .raw_val = color_buf[v] \
            }; \
            twl::gfx::abgr8888::Color out_clr = { \
                .clr = { \
                    .r = (u8)((int)((double)in_clr.clr.r * (255.0f/31.0f))), \
                    .g = (u8)((int)((double)in_clr.clr.g * (255.0f/31.0f))), \
                    .b = (u8)((int)((double)in_clr.clr.b * (255.0f/31.0f))), \
                    .a = (u8)((v != 0) ? 0xFF : 0), \
                } \
            }; \
            out_rgba[idx] = out_clr.raw_val; \
        }

        CONV_COLOR(pix1, i * 2);
        CONV_COLOR(pix2, i * 2 + 1);
    }

    return stbi_write_png(out_png_path.c_str(), tex_w, tex_h, sizeof(u32), out_rgba.get(), tex_w * sizeof(u32)) != 0;
}

bool TryExportRemixTexture(io::FileSystem &fs, const u16 file_id, const std::string &out_png_path) {
    struct stat st;
    if((stat(out_png_path.c_str(), &st) == 0) && S_ISREG(st.st_mode)) {
        return true;
    }
    if(!fs.HasFile(file_id)) {
        return false;
    }

    auto &png_tex_file = fs.GetFile(file_id);
    R_TRY_ERRLOG_BOOL(png_tex_file.OpenRead(fs::FileCompression::None), "Unable to open PNG texture file");
    ScopeGuard close_file([&]() {
        png_tex_file.Close();
    });

    fs::StdioFile out_file(out_png_path);
    R_TRY_ERRLOG_BOOL(out_file.OpenWrite(), "Unable to open output PNG file");
    ScopeGuard close_out([&]() {
        out_file.Close();
    });

    R_TRY_ERRLOG_BOOL(out_file.WriteBuffer(png_tex_file.GetBuffer(), png_tex_file.GetBufferSize()), "Unable to save PNG texture file");
    return true;
}

namespace {

    void ExportBh2pTexture(const std::string &in_index, const std::string &in_package, const std::string &file_id_str, const std::string &out_png_path) {
        try {
            const auto file_id = std::stoi(file_id_str);

            io::FileSystem fs;
        
            fs::StdioFile rf_index(in_index);
            R_TRY_ERRLOG(rf_index.OpenRead(fs::FileCompression::None), "Unable to open index file");
            ScopeGuard close_index([&]() {
                rf_index.Close();
            });

            fs::StdioFile rf_package(in_package);
            R_TRY_ERRLOG(rf_package.OpenRead(fs::FileCompression::None), "Unable to open package file");
            ScopeGuard close_package([&]() {
                rf_package.Close();
            });

            R_TRY_ERRLOG(fs.ReadFrom(rf_index, rf_package), "Unable to read filesystem");

            remove(out_png_path.c_str());
            if(TryExportBh2pTexture(fs, file_id, out_png_path)) {
                std::cout << "Texture successfully exported to '" << out_png_path << "'" << std::endl;
            }
            else {
                std::cout << "Failed to export texture" << std::endl;
            }
        }
        catch(std::exception &ex) {
            std::cerr << "Invalid file ID: " << ex.what() << std::endl;
        }
    }

    void ExportRemixTexture(const std::string &in_index, const std::string &in_package, const std::string &file_id_str, const std::string &out_png_path) {
        try {
            const auto file_id = std::stoi(file_id_str);

            io::FileSystem fs;
        
            fs::StdioFile rf_index(in_index);
            R_TRY_ERRLOG(rf_index.OpenRead(fs::FileCompression::None), "Unable to open index file");
            ScopeGuard close_index([&]() {
                rf_index.Close();
            });

            fs::StdioFile rf_package(in_package);
            R_TRY_ERRLOG(rf_package.OpenRead(fs::FileCompression::None), "Unable to open package file");
            ScopeGuard close_package([&]() {
                rf_package.Close();
            });

            R_TRY_ERRLOG(fs.ReadFrom(rf_index, rf_package), "Unable to read filesystem");

            remove(out_png_path.c_str());
            if(TryExportRemixTexture(fs, file_id, out_png_path)) {
                std::cout << "Texture successfully exported to '" << out_png_path << "'" << std::endl;
            }
            else {
                std::cout << "Failed to export texture" << std::endl;
            }
        }
        catch(std::exception &ex) {
            std::cerr << "Invalid file ID: " << ex.what() << std::endl;
        }
    }

}

namespace cli {

    void ExportTexture(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &file_id_str, const std::string &out_png_path) {
        Game game;
        if(!ParseGame(game_str, game)) {
            std::cerr << "Invalid game provided..." << std::endl;
            return;
        }

        switch(game) {
            case Game::BH2P: {
                ExportBh2pTexture(in_index, in_package, file_id_str, out_png_path);
                break;
            }
            case Game::Remix: {
                ExportRemixTexture(in_index, in_package, file_id_str, out_png_path);
                break;
            }
        }
    }

}
