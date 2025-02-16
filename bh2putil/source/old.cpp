#include <args.hxx>
#include <cstdint>
#include <sys/stat.h>
#include <twl/util/util_Compression.hpp>
#include <twl/gfx/gfx_Conversion.hpp>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <fmt/fmt_TextList.hpp>
#include <fs/fs_FileSystem.hpp>
#include <table.hpp>

using namespace twl;

#define R_TRY_ERRLOG(rc, ...) { \
    const auto _tmp_rc = (rc); \
    if(_tmp_rc.IsFailure()) { \
        std::cerr << __VA_ARGS__ << ": " << _tmp_rc.GetDescription() << std::endl; \
        return; \
    } \
}

namespace {

    bool ReadFromFile(const std::string &path, u8 *&out_buf, size_t &out_buf_size) {
        auto f = fopen(path.c_str(), "rb");
        if(f) {
            fseek(f, 0, SEEK_END);
            const auto f_size = ftell(f);
            rewind(f);

            auto file_ptr = new u8[f_size]();

            if(fread(file_ptr, f_size, 1, f) != 1) {
                delete[] file_ptr;
                fclose(f);
                return false;
            }

            out_buf = file_ptr;
            out_buf_size = f_size;

            fclose(f);
            return true;
        }
        else {
            return false;
        }
    }

    bool WriteToFile(const std::string &path, const void *buf, const size_t buf_size) {
        auto f = fopen(path.c_str(), "wb");
        if(f) {
            if(fwrite(buf, buf_size, 1, f) != 1) {
                fflush(f);
                fclose(f);
                return false;
            }

            fclose(f);
            return true;
        }
        else {
            return false;
        }
    }

    ////

    void Test(const std::string &in_1i, const std::string &in_1p, const std::string &out) {
        u8 *in1i_buf;
        size_t in1i_size;
        ReadFromFile(in_1i, in1i_buf, in1i_size);

        u32 *in1i_buf32 = reinterpret_cast<u32*>(in1i_buf);

        const u32 entry_count = *in1i_buf32;

        u8 *in1p_buf;
        size_t in1p_size;
        ReadFromFile(in_1p, in1p_buf, in1p_size);

        const std::string cmd1 = "rm -rf \"" + out + "\"";
        system(cmd1.c_str());
        
        const std::string cmd2 = "mkdir \"" + out + "\"";
        system(cmd2.c_str());

        u32 comp = 0;

        gfx::GraphicsToRgbaContext ctx = {
            .def_width = 128,
            .def_height = 58,
            .pix_fmt = gfx::PixelFormat::Palette256,
            .char_fmt = gfx::CharacterFormat::Char,
            .first_color_transparent = true
        };

        for(u32 i = 0; i < entry_count; i++) {
            const size_t offset = in1i_buf32[i + 1];
            const size_t size = in1i_buf32[i + 2] - in1i_buf32[i + 1];
            if(size > 0) {
                u8 *entry_buf = in1p_buf + offset;

                std::cout << "> File [" << i << "], offset 0x" << std::hex << offset << std::dec << ", size 0x" << std::hex << size << std::dec << "!" << std::endl;

                u8 *entry_buf_last = entry_buf + size - 1;
                // Skip all ending 0xFF's
                while(*entry_buf_last == 0xFF) {
                    entry_buf_last -= 1;
                }

                const auto path = out + "/" + "file_" + std::to_string(i) + ".bin";

                u8 *file_buf = entry_buf;
                size_t file_size = size;
                bool del_buf = false;

                const auto last8 = *entry_buf_last;
                if(last8 == 1) {
                    // First file 24 bits
                    const auto actual_size = *reinterpret_cast<u32*>(entry_buf) >> 8;
                    std::cout << "Compressed! base size 0x" << std::hex << size << std::dec << " vs final size 0x" << std::hex << actual_size << std::dec << "..." << std::endl;
                    
                    const auto cmp_path = out + "/" + "file_" + std::to_string(i) + "_comp.bin";
                    WriteToFile(cmp_path, entry_buf, size);

                    u8 *dec_buf;
                    size_t dec_buf_size;
                    twl::util::LzVersion dum;
                    size_t dum2;
                    std::cout << "LZ decomp: " << twl::util::LzDecompress(entry_buf, dec_buf, dec_buf_size, dum, dum2).GetDescription() << std::endl;

                    file_buf = dec_buf;
                    file_size = dec_buf_size;

                    /*
                    u8 *reenc_buf;
                    size_t reenc_size;
                    twl::util::LzCompress(file_buf, file_size, dum, twl::util::DefaultRepeatSize, reenc_buf, reenc_size);

                    const auto re_path = out + "/" + "file_" + std::to_string(i) + "_recmp.bin";
                    WriteToFile(re_path, reenc_buf, reenc_size);

                    delete[] reenc_buf;
                    */

                    comp++;
                }
                else if(last8 == 0) {
                    std::cout << "Not compressed!" << std::endl;
                    file_size -= 1;
                }
                else {
                    std::cout << "Unknown last byte? " << (int)last8 << std::endl;
                    return;
                }

                WriteToFile(path, file_buf, file_size);

                if(i == 993) {
                    ctx.plt_data = file_buf;
                    ctx.plt_data_size = file_size;
                    del_buf = false;
                }
                else if(i == 985) {
                    ctx.gfx_data = file_buf;
                    ctx.gfx_data_size = file_size;
                    del_buf = false;
                }

                if(del_buf) {
                    delete[] file_buf;
                }
            }
        }

        std::cout << "Plt data size 0x" << std::hex << ctx.plt_data_size << std::dec << std::endl;
        std::cout << "Gfx data size 0x" << std::hex << ctx.gfx_data_size << std::dec << std::endl;

        const auto rc = gfx::ConvertGraphicsToRgba(ctx);
        std::cout << "gfxconv " << rc.GetDescription() << std::endl;

        if(rc.IsSuccess()) {
            if(stbi_write_png((out + "_test.png").c_str(), ctx.out_width, ctx.out_height, 4, ctx.out_rgba, ctx.out_width * 4)) {
                std::cout << "png ok" << std::endl;
            }
            else {
                std::cout << "png err" << std::endl;
            }
        }

        std::cout << entry_count << " files, " << comp << " compressed" << std::endl;

        delete[] in1i_buf;
        delete[] in1p_buf;
    }

    //////////////////////////////

    void PrintText(::fs::FileSystem &fs, const u32 file_id, const u32 text_id) {
        auto &file = fs.GetFile(file_id);
        R_TRY_ERRLOG(file.OpenRead(), "open text file for read");
        fmt::TextList texts;
        R_TRY_ERRLOG(texts.ReadFrom(file), "read text list file");
        R_TRY_ERRLOG(file.Close(), "close r text file");

        std::cout << "file [" << file_id << "], text [" << text_id << "] -> \"" << texts.Get(Language::English, text_id) << "\"" << std::endl;
    }

    void PrintTexts(::fs::FileSystem &fs, const u32 file_id) {
        auto &file = fs.GetFile(file_id);
        R_TRY_ERRLOG(file.OpenRead(), "open text file for read");
        fmt::TextList texts;
        R_TRY_ERRLOG(texts.ReadFrom(file), "read text list file");
        R_TRY_ERRLOG(file.Close(), "close r text file");

        for(u32 i = 0; i < texts.GetCount(); i++) {
            std::cout << "file [" << file_id << "], text [" << i << "] -> \"" << texts.Get(Language::English, i) << "\"" << std::endl;
        }
    }
    
    void DemoText(::fs::FileSystem &fs, const u32 file_id, const u32 text_id) {
        auto &file = fs.GetFile(file_id);
        R_TRY_ERRLOG(file.OpenRead(), "open text file for read");
        fmt::TextList texts;
        R_TRY_ERRLOG(texts.ReadFrom(file), "read text list file");
        R_TRY_ERRLOG(file.Close(), "close r text file");

        std::cout << "file [" << file_id << "], (original) text [" << text_id << "] -> \"" << texts.Get(Language::English, text_id) << "\"" << std::endl;

        texts.Set(Language::English, text_id, "mYING YANG");

        R_TRY_ERRLOG(file.OpenWrite(), "open text file for wr");
        R_TRY_ERRLOG(texts.WriteTo(file), "wr text list file");
        R_TRY_ERRLOG(file.Close(), "close w text file");
    }

    void PrintObjects(::fs::FileSystem &fs, const u32 offset_file_id, const u32 obj_file_id) {
        auto &offset_file = fs.GetFile(offset_file_id);
        R_TRY_ERRLOG(offset_file.OpenRead(), "open text file for read");

        size_t offset_file_size;
        R_TRY_ERRLOG(offset_file.GetSize(offset_file_size), "getsize");

        const auto count = offset_file_size / sizeof(u32);

        std::cout << "Item count: " << count << std::endl;

        auto &obj_list_file = fs.GetFile(obj_file_id);
        R_TRY_ERRLOG(obj_list_file.OpenRead(), "open text file for read");

        for(u32 i = 0; i < count; i++) {
            u32 offset;
            R_TRY_ERRLOG(offset_file.Read(offset), "fff");

            if(offset == 0) {
                std::cout << "Object[" << i << "]: <empty>" << std::endl;
            }
            else {
                R_TRY_ERRLOG(obj_list_file.SetAbsoluteOffset(offset), "ggg");

                u8 init[2] = {};
                R_TRY_ERRLOG(obj_list_file.ReadBuffer(init, 2), "www");

                const auto size = init[1];

                auto name = new char[size + 1]();
                R_TRY_ERRLOG(obj_list_file.ReadBuffer(name, size), "hhh");

                u16 id;
                R_TRY_ERRLOG(obj_list_file.Read(id), "vvb");

                u16 unk;
                R_TRY_ERRLOG(obj_list_file.Read(unk), "vvb2");

                u8 count2;
                R_TRY_ERRLOG(obj_list_file.Read(count2), "cnt2");

                std::vector<u16> list1;
                std::vector<u16> list2;
                std::vector<u16> list3;

                for(u32 i = 0; i < count2; i++) {
                    u16 ci;
                    R_TRY_ERRLOG(obj_list_file.Read(ci), "cnttt5");

                    list1.push_back(ci);
                }
                for(u32 i = 0; i < count2; i++) {
                    u16 ci;
                    R_TRY_ERRLOG(obj_list_file.Read(ci), "cnttt51");

                    list2.push_back(ci);
                }
                for(u32 i = 0; i < count2; i++) {
                    u16 ci;
                    R_TRY_ERRLOG(obj_list_file.Read(ci), "cnttt52");

                    list3.push_back(ci);
                }

                std::cout << "Word[" << i << ", size " << (u32)init[0] << "]: \"" << name << "\", id = " << id << ", unk = " << unk << ", itemcount = " << (u32)count2;

                for(u32 i = 0; i < count2; i++) {
                    std::cout << ", item" << i << " = {" << list1[i] << ", " << list2[i] << ", " << list3[i] << "}";
                }

                std::cout << std::endl;

                delete[] name;
            }
        }

        offset_file.Close();
        obj_list_file.Close();
    }

    void ExtractFont(::fs::FileSystem &fs, const u32 file_id, const u32 glyph_w, const u32 glyph_h) {
        const std::string fontdir = "font" + std::to_string(file_id);
        const std::string cmd1 = "rm -rf \"" + fontdir + "\"";
        system(cmd1.c_str());
        const std::string cmd2 = "mkdir \"" + fontdir + "\"";
        system(cmd2.c_str());

        for(u32 g = 0; g < 96; g++) {
            u8 glyphdata[glyph_w * glyph_h];
            auto &font = fs.GetFile(file_id);
            R_TRY_ERRLOG(font.OpenRead(), "fontread");
            font.SetAbsoluteOffset(g*glyph_w*glyph_h);
            R_TRY_ERRLOG(font.ReadBuffer(glyphdata, sizeof(glyphdata)), "readglyph");
            font.Close();

            u32 colors[] = {
                0x00000000, // transparent
                0x000000FF, // black
                0x313131FF, // dark gray
                0xffffffFF, // white
                0x426b7bFF, // gray/blue 1
                0x5a8ca5FF, // gray/blue 2
                0xff00ffFF  // ???
            };

            u32 rgbaptr[glyph_w * glyph_h] = {};
            for(u32 i = 0; i < glyph_w * glyph_h; i++) {
                rgbaptr[i] = __builtin_bswap32(colors[glyphdata[i]]);
            }

            if(stbi_write_png((fontdir + "/" + std::to_string(g) + ".png").c_str(), glyph_w, glyph_h, 4, rgbaptr, glyph_w * 4)) {
                std::cout << "png ok font " << file_id << std::endl;
            }
            else {
                std::cout << "png err" << std::endl;
            }
        }
    }

    void ExtractBitmap(::fs::FileSystem &fs, const u32 file_id, const u32 w, const u32 h, const std::string &out_png_name) {
        u16 data[w * h];
        auto &bmp_file = fs.GetFile(file_id);
        R_TRY_ERRLOG(bmp_file.OpenRead(), "bmpread");
        R_TRY_ERRLOG(bmp_file.ReadBuffer(data, sizeof(data)), "readdata");
        bmp_file.Close();

        u32 rgbaptr[w * h] = {};
        for(u32 i = 0; i < (w * h); i++) {
            twl::gfx::abgr1555::Color clr = {
                .raw_val = data[i]
            };
            twl::gfx::abgr8888::Color rclr = {
                .clr = {
                    .r = (u8)((int)((double)clr.clr.r * (255.0f/31.0f))),
                    .g = (u8)((int)((double)clr.clr.g * (255.0f/31.0f))),
                    .b = (u8)((int)((double)clr.clr.b * (255.0f/31.0f))),
                    .a = 0xFF,
                }
            };
            rgbaptr[i] = rclr.raw_val;
        }

        if(stbi_write_png((out_png_name + ".png").c_str(), w, h, 4, rgbaptr, w * 4)) {
            std::cout << "png ok bmp " << file_id << std::endl;
        }
        else {
            std::cout << "png bmp err" << std::endl;
        }
    }

    void Test2(const std::string &in_1i, const std::string &in_1p, const std::string &out_1i, const std::string &out_1p) {
        ::fs::FileSystem fs;
        
        twl::fs::StdioFile rf_1i(in_1i);
        R_TRY_ERRLOG(rf_1i.OpenRead(twl::fs::FileCompression::None), "rf 1i open");
        twl::fs::StdioFile rf_1p(in_1p);
        R_TRY_ERRLOG(rf_1p.OpenRead(twl::fs::FileCompression::None), "rf 1p open");

        R_TRY_ERRLOG(fs.ReadFrom(rf_1i, rf_1p), "fs read");

        auto &bmp_file = fs.GetFile(264);
        R_TRY_ERRLOG(bmp_file.OpenWrite(), "wwwwww");
        bmp_file.SetAbsoluteOffset(0x2d4);
        u8 tmpbuf[0xc8];
        memset(tmpbuf, 0x33, 0xc8);
        bmp_file.WriteBuffer(tmpbuf, 0xc8);
        bmp_file.Close();

        /*
        PrintText(fs, 285, 0);
        PrintText(fs, 287, 1);
        PrintText(fs, 287, 0);
        PrintText(fs, 287, 2);

        PrintText(fs, 273, 0);
        PrintText(fs, 273, 1);
        */

        // DemoText(fs, 287, 0);

        // PrintObjects(fs, 13251, 13220); // short
        // PrintObjects(fs, 32173, 13220); // long
        // PrintObjects(fs, 13282, 13267); // short
        // PrintObjects(fs, 32161, 13267); // long

        /*
        ExtractFont(fs, 896, 9, 12);
        ExtractFont(fs, 891, 15, 22);
        ExtractFont(fs, 893, 11, 14);
        ExtractFont(fs, 895, 6, 8);
        ExtractFont(fs, 892, 15, 22);
        ExtractFont(fs, 894, 11, 14);
        ExtractFont(fs, 897, 9, 12);
        */

        // PrintTexts(fs, 279);

        fmt::InputDictionary dict;
        R_TRY_ERRLOG(ObjectsEN.ReadFrom(fs, dict), "dictread");

        std::cout << "read!" << std::endl;

        /*
        R_TRY_ERRLOG(rf_1i.Close(), "rf 1i close");
        R_TRY_ERRLOG(rf_1p.Close(), "rf 1p close");

        twl::fs::StdioFile wf_1i(out_1i);
        R_TRY_ERRLOG(wf_1i.OpenWrite(), "wf 1i open");
        twl::fs::StdioFile wf_1p(out_1p);
        R_TRY_ERRLOG(wf_1p.OpenWrite(), "wf 1p open");

        R_TRY_ERRLOG(fs.WriteTo(wf_1i, wf_1p), "fs write");

        R_TRY_ERRLOG(wf_1i.Close(), "wf 1i close");
        R_TRY_ERRLOG(wf_1p.Close(), "wf 1p close");

        std::cout << "done test2" << std::endl;
        */
    }

}

int main(int argc, char **argv) {
    args::ArgumentParser parser("Various BH2P-related utilities");
    args::HelpFlag help(parser, "help", "Displays this help menu", {'h', "help"});

    args::Group commands(parser, "Commands:", args::Group::Validators::Xor);

    args::Command test(commands, "test", "Test");
    args::Group test_required(test, "", args::Group::Validators::All);
    args::ValueFlag<std::string> test_in1i(test_required, "in1i", "in1i", {'i', "in1i"});
    args::ValueFlag<std::string> test_in1p(test_required, "in1p", "in1p", {'p', "in1p"});
    args::ValueFlag<std::string> test_out(test_required, "out", "out", {'o', "out"});

    args::Command test2(commands, "test2", "Test2");
    args::Group test2_required(test2, "", args::Group::Validators::All);
    args::ValueFlag<std::string> test2_in1i(test2_required, "in1i", "in1i", {'i', "in1i"});
    args::ValueFlag<std::string> test2_in1p(test2_required, "in1p", "in1p", {'p', "in1p"});
    args::ValueFlag<std::string> test2_out1i(test2_required, "out1i", "out1i", {'o', "out1i"});
    args::ValueFlag<std::string> test2_out1p(test2_required, "out1p", "out1p", {'s', "out1p"});

    try {
        parser.ParseCLI(argc, argv);
    }
    catch(std::exception &e) {
        std::cerr << parser;
        std::cout << e.what() << std::endl;
        return 1;
    }

    if(test) {
        const auto in1i = test_in1i.Get();
        const auto in1p = test_in1p.Get();
        const auto out = test_out.Get();

        Test(in1i, in1p, out);
    }
    else if(test2) {
        const auto in1i = test2_in1i.Get();
        const auto in1p = test2_in1p.Get();
        const auto out1i = test2_out1i.Get();
        const auto out1p = test2_out1p.Get();

        Test2(in1i, in1p, out1i, out1p);
    }

    return 0;
}
