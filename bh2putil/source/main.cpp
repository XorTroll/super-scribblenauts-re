#include <args.hxx>
#include <cstdint>
#include <sys/stat.h>
#include <objnaut/fmt/fmt_TextList.hpp>
#include <objnaut/fs/fs_FileSystem.hpp>
#include <objnaut/def/def_InputDictionary.hpp>
#include <objnaut/def/def_TextList.hpp>

using namespace twl;
using namespace objnaut;

#define R_TRY_ERRLOG(rc, ...) { \
    const auto _tmp_rc = (rc); \
    if(_tmp_rc.IsFailure()) { \
        std::cerr << __VA_ARGS__ << ": " << _tmp_rc.GetDescription() << std::endl; \
        return; \
    } \
}

namespace {

    bool ParseLanguage(const std::string &lang_str, Language &out_lang, const bool allow_unk) {
        if(lang_str == "en") {
            out_lang = Language::English;
        }
        else if(lang_str == "nl") {
            out_lang = Language::Dutch;
        }
        else if(lang_str == "fr") {
            out_lang = Language::French;
        }
        else if(lang_str == "ge") {
            out_lang = Language::German;
        }
        else if(lang_str == "it") {
            out_lang = Language::Italian;
        }
        else if(lang_str == "es") {
            out_lang = Language::Spanish;
        }
        else if(allow_unk && (lang_str == "unk")) {
            out_lang = Language::UnkSpecial;
        }
        else {
            return false;
        }

        return true;
    }

    void ListInputs(const std::string &kind_str, const std::string &in_1i, const std::string &in_1p, const def::InputDictionaryEntry &entry) {
        objnaut::fs::FileSystem fs;
        
        twl::fs::StdioFile rf_1i(in_1i);
        R_TRY_ERRLOG(rf_1i.OpenRead(twl::fs::FileCompression::None), "Unable to open 1i");

        twl::fs::StdioFile rf_1p(in_1p);
        R_TRY_ERRLOG(rf_1p.OpenRead(twl::fs::FileCompression::None), "Unable to open 1p");

        R_TRY_ERRLOG(fs.ReadFrom(rf_1i, rf_1p), "Unable to read filesystem");

        fmt::InputDictionary dict;
        R_TRY_ERRLOG(entry.ReadFrom(fs, dict), "Unable to read input dictionary");

        std::cout << kind_str << std::endl;

        std::cout << "Input count: " << dict.inputs.size() << std::endl;

        std::cout << "Match list:" << std::endl;
        u16 max_i = 0;
        for(const auto &in: dict.inputs) {
            for(const auto &match: in->matches) {
                max_i = std::max(max_i, match.match_list_idx);
            }
        }
        for(u16 i = 0; i <= max_i; i++) {
            bool found = false;
            for(const auto &in: dict.inputs) {
                if(found) {
                    break;
                }

                for(const auto &match: in->matches) {
                    if(match.match_list_idx == i) {
                        std::cout << "> Match[" << i << "]: \"" << in->input_text << "\" ";

                        if(!match.description.empty()) {
                            std::cout << "(\"" << match.description << "\") ";
                        }

                        std::cout << "fileid=" << match.file_id << ", unk1=" << in->unk1 << ", unk2=" << match.unk2;

                        if(!match.description.empty()) {
                            std::cout << ", unk3=" << match.unk3;
                        }

                        if(match.redir_input != nullptr) {
                            std::cout << " ==> \"" << match.redir_input->input_text << "\"";
                        }

                        std::cout << std::endl;

                        found = true;
                        break;
                    }
                }
            }

            if(!found) {
                std::cout << "> Match[" << i << "]: <empty>" << std::endl;
            }
        }

        std::cout << "Input lookup list:" << std::endl;
        u16 max_l_i = 0;
        for(const auto &in: dict.inputs) {
            max_l_i = std::max(max_l_i, in->lookup_list_idx);
        }
        for(u16 i = 0; i <= max_l_i; i++) {
            bool found = false;
            for(const auto &in: dict.inputs) {
                if(found) {
                    break;
                }

                if(in->lookup_list_idx == i) {
                    std::cout << "> Lookup[" << i << "]: \"" << in->input_text << "\", unk1=" << in->unk1 << ": ";
                    for(const auto &match: in->matches) {
                        std::cout << "{ ";

                        if(!match.description.empty()) {
                            std::cout << "\"" << match.description << "\", ";
                        }

                        std::cout << "fileid=" << match.file_id << ", unk2=" << match.unk2;

                        if(!match.description.empty()) {
                            std::cout << ", unk3=" << match.unk3;
                        }

                        if(match.redir_input != nullptr) {
                            std::cout << " ==> \"" << match.redir_input->input_text << "\"";
                        }

                        std::cout << " } ";
                    }
                    std::cout << std::endl;

                    found = true;
                    break;
                }
            }

            if(!found) {
                std::cout << "> Lookup[" << i << "]: <empty>" << std::endl;
            }
        }
    }

    void ListTexts(const std::string &in_1i, const std::string &in_1p, const std::string &file_id_str, const std::string &lang_str) {
        Language lang;
        if(!ParseLanguage(lang_str, lang, false)) {
            std::cerr << "Invalid language provided..." << std::endl;
            return;
        }

        try {
            const auto file_id = std::stoi(file_id_str);

            objnaut::fs::FileSystem fs;
        
            twl::fs::StdioFile rf_1i(in_1i);
            R_TRY_ERRLOG(rf_1i.OpenRead(twl::fs::FileCompression::None), "Unable to open 1i");

            twl::fs::StdioFile rf_1p(in_1p);
            R_TRY_ERRLOG(rf_1p.OpenRead(twl::fs::FileCompression::None), "Unable to open 1p");

            R_TRY_ERRLOG(fs.ReadFrom(rf_1i, rf_1p), "Unable to read filesystem");

            auto &file = fs.GetFile(file_id);
            R_TRY_ERRLOG(file.OpenRead(twl::fs::FileCompression::None), "Unable to open filesystem file");
            ScopeGuard close([&]() {
                file.Close();
            });

            fmt::TextList list;
            R_TRY_ERRLOG(list.ReadFrom(file), "Unable to read text list file");

            for(u32 i = 0; i < list.GetCount(); i++) {
                std::cout << "Text[" << i << "]: \"" << list.Get(lang, i) << "\"" << std::endl;
            }
        }
        catch(std::exception &ex) {
            std::cerr << "Invalid file ID: " << ex.what() << std::endl;
        }
    }

    void ListObjects(const std::string &in_1i, const std::string &in_1p, const std::string &lang_str) {
        const auto kind = "OBJECT LIST PRINTOUT";
        Language lang;
        if(!ParseLanguage(lang_str, lang, true)) {
            std::cerr << "Invalid language provided..." << std::endl;
            return;
        }

        ListInputs(kind, in_1i, in_1p, def::ObjectDictionaries[static_cast<u32>(lang)]);
    }

    void ListAdjectives(const std::string &in_1i, const std::string &in_1p, const std::string &lang_str) {
        const auto kind = "ADJECTIVE LIST PRINTOUT";
        Language lang;
        if(!ParseLanguage(lang_str, lang, true)) {
            std::cerr << "Invalid language provided..." << std::endl;
            return;
        }

        ListInputs(kind, in_1i, in_1p, def::AdjectiveDictionaries[static_cast<u32>(lang)]);
    }

    void Test(const std::string &in_1i, const std::string &in_1p, const std::string &lang_str, const std::string &out_in_list, const std::string &out_match_offset_list, const std::string &out_lookup_offset_list, const std::string &out_match_desc_list) {
        Language lang;
        if(!ParseLanguage(lang_str, lang, false)) {
            std::cerr << "Invalid language provided..." << std::endl;
            return;
        }

        objnaut::fs::FileSystem fs;
        
        twl::fs::StdioFile rf_1i(in_1i);
        R_TRY_ERRLOG(rf_1i.OpenRead(twl::fs::FileCompression::None), "Unable to open 1i");

        twl::fs::StdioFile rf_1p(in_1p);
        R_TRY_ERRLOG(rf_1p.OpenRead(twl::fs::FileCompression::None), "Unable to open 1p");

        R_TRY_ERRLOG(fs.ReadFrom(rf_1i, rf_1p), "Unable to read filesystem");

        fmt::InputDictionary dict;
        R_TRY_ERRLOG(def::ObjectDictionaries[static_cast<u32>(lang)].ReadFrom(fs, dict), "Unable to read input dictionary");

        twl::fs::StdioFile wf_out_in_list(out_in_list);
        R_TRY_ERRLOG(wf_out_in_list.OpenWrite(), "Unable to open 1");
        twl::fs::StdioFile wf_out_match_offset_list(out_match_offset_list);
        R_TRY_ERRLOG(wf_out_match_offset_list.OpenWrite(), "Unable to open 2");
        twl::fs::StdioFile wf_out_lookup_offset_list(out_lookup_offset_list);
        R_TRY_ERRLOG(wf_out_lookup_offset_list.OpenWrite(), "Unable to open 3");
        twl::fs::StdioFile wf_out_match_desc_list(out_match_desc_list);
        R_TRY_ERRLOG(wf_out_match_desc_list.OpenWrite(), "Unable to open 4");

        auto x = std::optional<std::reference_wrapper<twl::fs::File>>(wf_out_match_desc_list);
        R_TRY_ERRLOG(dict.WriteTo(wf_out_in_list, wf_out_match_offset_list, wf_out_lookup_offset_list, x), "unable tow ewirht");
    }

    void Test2(const std::string &in_1i, const std::string &in_1p, const std::string &out_1i, const std::string &out_1p) {
        objnaut::fs::FileSystem fs;
        
        twl::fs::StdioFile rf_1i(in_1i);
        R_TRY_ERRLOG(rf_1i.OpenRead(twl::fs::FileCompression::None), "Unable to open 1i");

        twl::fs::StdioFile rf_1p(in_1p);
        R_TRY_ERRLOG(rf_1p.OpenRead(twl::fs::FileCompression::None), "Unable to open 1p");

        R_TRY_ERRLOG(fs.ReadFrom(rf_1i, rf_1p), "Unable to read filesystem");

        fmt::InputDictionary dict;
        R_TRY_ERRLOG(def::ObjectDictionaries[0].ReadFrom(fs, dict), "Unable to read input dictionary");

        for(auto &in: dict.inputs) {
            if(in->input_text == "DOG") {
                in->input_text = "DAWG";
                break;
            }
        }

        auto newin = std::make_shared<fmt::Input>();
        newin->input_text = "KANYE";
        newin->lookup_list_idx = 24326;
        newin->unk1 = 0;

        auto &match1 = newin->matches.emplace_back();
        match1.description = "GOOD";
        match1.file_id = 25239;
        match1.match_list_idx = 1447;
        match1.unk2 = 354;
        match1.unk3 = 286;

        auto &match2 = newin->matches.emplace_back();
        match2.description = "BAD";
        match2.file_id = 25226;
        match2.match_list_idx = 649;
        match2.unk2 = 354;
        match2.unk3 = 286;

        dict.inputs.push_back(newin);

        R_TRY_ERRLOG(def::ObjectDictionaries[0].WriteTo(fs, dict), "Unable to write output dictionary");

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
    }

}

int main(int argc, char **argv) {
    args::ArgumentParser parser("Various BH2P-related utilities (Super Scribblenauts - EU)");
    args::HelpFlag help(parser, "help", "Displays this help menu", {'h', "help"});

    const auto lang_ident = "Language (es,nl,fr,ge,it,es,unk)";

    args::Group commands(parser, "Commands:", args::Group::Validators::Xor);

    args::Command listobj(commands, "list-obj", "List objects");
    args::Group listobj_required(listobj, "", args::Group::Validators::All);
    args::ValueFlag<std::string> listobj_in1i(listobj_required, "in1i", "Input 1i", {'i', "in1i"});
    args::ValueFlag<std::string> listobj_in1p(listobj_required, "in1p", "Input 1p", {'p', "in1p"});
    args::ValueFlag<std::string> listobj_lang(listobj_required, "lang", lang_ident, {'l', "lang"});

    args::Command listadj(commands, "list-adj", "List adjectives");
    args::Group listadj_required(listadj, "", args::Group::Validators::All);
    args::ValueFlag<std::string> listadj_in1i(listadj_required, "in1i", "Input 1i", {'i', "in1i"});
    args::ValueFlag<std::string> listadj_in1p(listadj_required, "in1p", "Input 1p", {'p', "in1p"});
    args::ValueFlag<std::string> listadj_lang(listadj_required, "lang", lang_ident, {'l', "lang"});

    args::Command listtexts(commands, "list-txts", "List texts from text file");
    args::Group listtexts_required(listtexts, "", args::Group::Validators::All);
    args::ValueFlag<std::string> listtexts_in1i(listtexts_required, "in1i", "Input 1i", {'i', "in1i"});
    args::ValueFlag<std::string> listtexts_in1p(listtexts_required, "in1p", "Input 1p", {'p', "in1p"});
    args::ValueFlag<std::string> listtexts_file(listtexts_required, "file", "Text file ID", {'f', "file"});
    args::ValueFlag<std::string> listtexts_lang(listtexts_required, "lang", lang_ident, {'l', "lang"});

    args::Command test(commands, "test", "Test");
    args::Group test_required(test, "", args::Group::Validators::All);
    args::ValueFlag<std::string> test_in1i(test_required, "in1i", "Input 1i", {'i', "in1i"});
    args::ValueFlag<std::string> test_in1p(test_required, "in1p", "Input 1p", {'p', "in1p"});
    args::ValueFlag<std::string> test_lang(test_required, "lang", lang_ident, {'l', "lang"});
    args::ValueFlag<std::string> test_out_in_list(test_required, "out_in_list", "out_in_list", {'1', "1"});
    args::ValueFlag<std::string> test_out_match_offset_list(test_required, "out_match_offset_list", "out_match_offset_list", {'2', "2"});
    args::ValueFlag<std::string> test_out_lookup_offset_list(test_required, "out_lookup_offset_list", "out_lookup_offset_list", {'3', "3"});
    args::ValueFlag<std::string> test_out_match_desc_list(test_required, "out_match_desc_list", "out_match_desc_list", {'4', "4"});

    args::Command test2(commands, "test2", "Test2");
    args::Group test2_required(test2, "", args::Group::Validators::All);
    args::ValueFlag<std::string> test2_in1i(test2_required, "in1i", "Input 1i", {'i', "in1i"});
    args::ValueFlag<std::string> test2_in1p(test2_required, "in1p", "Input 1p", {'p', "in1p"});
    args::ValueFlag<std::string> test2_out1i(test2_required, "o1i", "o 1i", {'o', "oo"});
    args::ValueFlag<std::string> test2_out1p(test2_required, "o1p", "o 1p", {'w', "ww"});

    try {
        parser.ParseCLI(argc, argv);
    }
    catch(std::exception &e) {
        std::cerr << parser;
        std::cout << e.what() << std::endl;
        return 1;
    }

    if(listobj) {
        const auto in_1i = listobj_in1i.Get();
        const auto in_1p = listobj_in1p.Get();
        const auto lang_str = listobj_lang.Get();

        ListObjects(in_1i, in_1p, lang_str);
    }
    else if(listadj) {
        const auto in_1i = listadj_in1i.Get();
        const auto in_1p = listadj_in1p.Get();
        const auto lang_str = listadj_lang.Get();

        ListAdjectives(in_1i, in_1p, lang_str);
    }
    else if(listtexts) {
        const auto in_1i = listtexts_in1i.Get();
        const auto in_1p = listtexts_in1p.Get();
        const auto file_str = listtexts_file.Get();
        const auto lang_str = listtexts_lang.Get();

        ListTexts(in_1i, in_1p, file_str, lang_str);
    }

    else if(test) {
        const auto in_1i = test_in1i.Get();
        const auto in_1p = test_in1p.Get();
        const auto lang_str = test_lang.Get();
        const auto out_in_list = test_out_in_list.Get();
        const auto out_match_offset_list = test_out_match_offset_list.Get();
        const auto out_lookup_offset_list = test_out_lookup_offset_list.Get();
        const auto out_match_desc_list = test_out_match_desc_list.Get();

        Test(in_1i, in_1p, lang_str, out_in_list, out_match_offset_list, out_lookup_offset_list, out_match_desc_list);
    }
    else if(test2) {
        const auto in_1i = test2_in1i.Get();
        const auto in_1p = test2_in1p.Get();
        const auto out_1i = test2_out1i.Get();
        const auto out_1p = test2_out1p.Get();

        Test2(in_1i, in_1p, out_1i, out_1p);
    }

    return 0;
}
