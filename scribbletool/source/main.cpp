#include <common.hpp>

#include <cli/cli_PrintMisc.hpp>
#include <cli/cli_PrintObject.hpp>
#include <cli/cli_ExportTexture.hpp>
#include <cli/cli_ObjectsHtml.hpp>

int main(int argc, char **argv) {
    args::ArgumentParser parser("Various Scribblenauts-related utilities: Super Scribblenauts-EU (BH2P) / Scribblenauts Remix");
    args::HelpFlag help(parser, "help", "Displays this help menu", {'h', "help"});

    const auto game_ident = "Game: Super Scribblenauts = bh2p, Scribblenauts Remix = remix (where the files come from)";
    const auto lang_ident = "Language (BH2P: es,nl,fr,ge,it,es,unk / Remix: en,en-uk,ge)";

    const auto index_ident = "Input index file (1i / patch OBB)";
    const auto package_ident = "Input package file (1p / main OBB)";

    args::Group commands(parser, "Commands:", args::Group::Validators::Xor);

    args::Command listobj(commands, "list-obj", "List object dictionary (lists all objects for a given language)");
    args::Group listobj_required(listobj, "", args::Group::Validators::All);
    args::ValueFlag<std::string> listobj_inidx(listobj_required, "in-idx", index_ident, {'i', "idx"});
    args::ValueFlag<std::string> listobj_inpkg(listobj_required, "in-pkg", package_ident, {'p', "pkg"});
    args::ValueFlag<std::string> listobj_game(listobj_required, "game", game_ident, {'g', "game"});
    args::ValueFlag<std::string> listobj_lang(listobj_required, "lang", lang_ident, {'l', "lang"});

    args::Command listadj(commands, "list-adj", "List adjectives");
    args::Group listadj_required(listadj, "", args::Group::Validators::All);
    args::ValueFlag<std::string> listadj_inidx(listadj_required, "in-idx", index_ident, {'i', "idx"});
    args::ValueFlag<std::string> listadj_inpkg(listadj_required, "in-pkg", package_ident, {'p', "pkg"});
    args::ValueFlag<std::string> listadj_game(listadj_required, "game", game_ident, {'g', "game"});
    args::ValueFlag<std::string> listadj_lang(listadj_required, "lang", lang_ident, {'l', "lang"});

    args::Command printtexts(commands, "print-txts", "Print texts from text file");
    args::Group printtexts_required(printtexts, "", args::Group::Validators::All);
    args::ValueFlag<std::string> printtexts_inidx(printtexts_required, "in-idx", index_ident, {'i', "idx"});
    args::ValueFlag<std::string> printtexts_inpkg(printtexts_required, "in-pkg", package_ident, {'p', "pkg"});
    args::ValueFlag<std::string> printtexts_game(printtexts_required, "game", game_ident, {'g', "game"});
    args::ValueFlag<std::string> printtexts_file(printtexts_required, "file", "Text file ID", {'f', "file"});
    args::ValueFlag<std::string> printtexts_lang(printtexts_required, "lang", lang_ident, {'l', "lang"});

    args::Command printobj(commands, "print-obj", "Print object");
    args::Group printobj_required(printobj, "", args::Group::Validators::All);
    args::ValueFlag<std::string> printobj_inidx(printobj_required, "in-idx", index_ident, {'i', "idx"});
    args::ValueFlag<std::string> printobj_inpkg(printobj_required, "in-pkg", package_ident, {'p', "pkg"});
    args::ValueFlag<std::string> printobj_file(printobj_required, "file", "Object file ID", {'f', "file"});

    args::Command exporttex(commands, "export-tex", "Export texture to PNG");
    args::Group exporttex_required(exporttex, "", args::Group::Validators::All);
    args::ValueFlag<std::string> exporttex_inidx(exporttex_required, "in-idx", index_ident, {'i', "idx"});
    args::ValueFlag<std::string> exporttex_inpkg(exporttex_required, "in-pkg", package_ident, {'p', "pkg"});
    args::ValueFlag<std::string> exporttex_game(exporttex_required, "game", game_ident, {'g', "game"});
    args::ValueFlag<std::string> exporttex_file(exporttex_required, "file", "Texture file ID", {'f', "file"});
    args::ValueFlag<std::string> exporttex_outpng(exporttex_required, "out-png", "Output PNG file", {'o', "outpng"});

    args::Command genobjhtml(commands, "gen-obj-html", "Generate HTML pages for object dictionary (for all objects for a given language)");
    args::Group genobjhtml_required(genobjhtml, "", args::Group::Validators::All);
    args::ValueFlag<std::string> genobjhtml_inidx(genobjhtml_required, "in-idx", index_ident, {'i', "idx"});
    args::ValueFlag<std::string> genobjhtml_inpkg(genobjhtml_required, "in-pkg", package_ident, {'p', "pkg"});
    args::ValueFlag<std::string> genobjhtml_game(genobjhtml_required, "game", game_ident, {'g', "game"});
    args::ValueFlag<std::string> genobjhtml_lang(genobjhtml_required, "lang", lang_ident, {'l', "lang"});
    args::ValueFlag<std::string> genobjhtml_outdir(genobjhtml_required, "outdir", "Output directory", {'o', "outdir"});

    try {
        parser.ParseCLI(argc, argv);
    }
    catch(std::exception &e) {
        std::cerr << parser;
        std::cout << e.what() << std::endl;
        return 1;
    }

    if(listobj) {
        const auto in_idx_path = listobj_inidx.Get();
        const auto in_pkg_path = listobj_inpkg.Get();
        const auto game_str = listobj_game.Get();
        const auto lang_str = listobj_lang.Get();

        cli::ListObjects(in_idx_path, in_pkg_path, game_str, lang_str);
    }
    else if(listadj) {
        const auto in_idx_path = listadj_inidx.Get();
        const auto in_pkg_path = listadj_inpkg.Get();
        const auto game_str = listadj_game.Get();
        const auto lang_str = listadj_lang.Get();

        cli::ListAdjectives(in_idx_path, in_pkg_path, game_str, lang_str);
    }
    else if(printtexts) {
        const auto in_idx_path = printtexts_inidx.Get();
        const auto in_pkg_path = printtexts_inpkg.Get();
        const auto game_str = printtexts_game.Get();
        const auto file_str = printtexts_file.Get();
        const auto lang_str = printtexts_lang.Get();

        cli::PrintTexts(in_idx_path, in_pkg_path, game_str, file_str, lang_str);
    }
    else if(printobj) {
        const auto in_idx_path = printobj_inidx.Get();
        const auto in_pkg_path = printobj_inpkg.Get();
        const auto file_str = printobj_file.Get();

        cli::PrintObject(in_idx_path, in_pkg_path, file_str);
    }
    else if(exporttex) {
        const auto in_idx_path = exporttex_inidx.Get();
        const auto in_pkg_path = exporttex_inpkg.Get();
        const auto game_str = exporttex_game.Get();
        const auto file_str = exporttex_file.Get();
        const auto out_png_path = exporttex_outpng.Get();

        cli::ExportTexture(in_idx_path, in_pkg_path, game_str, file_str, out_png_path);
    }
    else if(genobjhtml) {
        const auto in_idx_path = genobjhtml_inidx.Get();
        const auto in_pkg_path = genobjhtml_inpkg.Get();
        const auto game_str = genobjhtml_game.Get();
        const auto lang_str = genobjhtml_lang.Get();
        const auto out_dir = genobjhtml_outdir.Get();

        cli::GenerateObjectsHtml(in_idx_path, in_pkg_path, game_str, lang_str, out_dir);
    }

    return 0;
}
