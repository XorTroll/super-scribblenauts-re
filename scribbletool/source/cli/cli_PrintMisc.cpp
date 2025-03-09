#include <cli/cli_PrintMisc.hpp>

namespace {

    void ListDictionary(const bool is_objects, const std::string &in_index, const std::string &in_package, const def::DictionaryDefinition &dict_def) {
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

        fmt::Dictionary dict;
        R_TRY_ERRLOG(dict_def.ReadFrom(fs, dict), "Unable to read dictionary");

        if(is_objects) {
            std::cout << "================================================================ ADJECTIVE DICTIONARY PRINTOUT ================================================================" << std::endl;
        }
        else {
            std::cout << "================================================================  OBJECT DICTIONARY PRINTOUT   ================================================================" << std::endl;
        }

        std::cout << "> Word count: " << dict.words.size() << std::endl;

        std::cout << "----------------------------------------------------------------       Jump table listing      ----------------------------------------------------------------" << std::endl;
        u16 max_obj_id_i = 0;
        for(const auto &word: dict.words) {
            for(const auto &meaning: word->meanings) {
                max_obj_id_i = std::max(max_obj_id_i, meaning.adj_obj_id);
            }
        }
        for(u16 i = 0; i <= max_obj_id_i; i++) {
            bool found = false;
            for(const auto &word: dict.words) {
                if(found) {
                    break;
                }

                for(const auto &meaning: word->meanings) {
                    if(meaning.adj_obj_id == i) {
                        std::cout << "JumpTable[object ID " << i << "]: Word \"" << word->name << "\" ";

                        if(!meaning.obj_detail_text.empty()) {
                            std::cout << "(detail \"" << meaning.obj_detail_text << "\") ";
                        }

                        std::cout << "fileid=" << meaning.file_id << ", unk1_zero=" << word->unk1_zero << ", unk2=" << meaning.unk2;

                        if(!meaning.obj_detail_text.empty()) {
                            std::cout << ", unk3_object_id=" << meaning.unk3_object_id;
                        }

                        if(meaning.redir_word != nullptr) {
                            std::cout << " ==> redir to word ID " << meaning.redir_word->word_id << ", \"" << meaning.redir_word->name << "\"";
                        }

                        std::cout << std::endl;

                        found = true;
                        break;
                    }
                }
            }

            if(!found) {
                std::cout << "JumpTable[object ID " << i << "]: <empty>" << std::endl;
            }
        }

        std::cout << "----------------------------------------------------------------       Word table listing      ----------------------------------------------------------------" << std::endl;
        u16 max_word_i = 0;
        for(const auto &word: dict.words) {
            max_word_i = std::max(max_word_i, word->word_id);
        }
        for(u16 i = 0; i <= max_word_i; i++) {
            bool found = false;
            for(const auto &word: dict.words) {
                if(found) {
                    break;
                }

                if(word->word_id == i) {
                    std::cout << "> WordTable[word ID " << i << "]: \"" << word->name << "\", unk1_zero=" << word->unk1_zero << ": ";
                    for(const auto &meaning: word->meanings) {
                        std::cout << "{ ";

                        if(!meaning.obj_detail_text.empty()) {
                            std::cout << "detail=\"" << meaning.obj_detail_text << "\", ";
                        }

                        std::cout << "fileid=" << meaning.file_id << ", unk2=" << meaning.unk2;

                        if(!meaning.obj_detail_text.empty()) {
                            std::cout << ", unk3_object_id=" << meaning.unk3_object_id;
                        }

                        if(meaning.redir_word != nullptr) {
                            std::cout << " ==> redir to word ID " << meaning.redir_word->word_id << ", \"" << meaning.redir_word->name << "\"";
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

    void ListBh2pObjects(const std::string &in_index, const std::string &in_package, const std::string &lang_str) {
        bh2p::Language lang;
        if(!ParseBh2pLanguage(lang_str, lang, true)) {
            std::cerr << "Invalid BH2P language provided..." << std::endl;
            return;
        }

        ListDictionary(true, in_index, in_package, bh2p::def::ObjectDictionaries[static_cast<u32>(lang)]);
    }

    void ListBh2pAdjectives(const std::string &in_index, const std::string &in_package, const std::string &lang_str) {
        bh2p::Language lang;
        if(!ParseBh2pLanguage(lang_str, lang, true)) {
            std::cerr << "Invalid BH2P language provided..." << std::endl;
            return;
        }

        ListDictionary(false, in_index, in_package, bh2p::def::AdjectiveDictionaries[static_cast<u32>(lang)]);
    }

    void ListRemixObjects(const std::string &in_index, const std::string &in_package, const std::string &lang_str) {
        remix::Language lang;
        if(!ParseRemixLanguage(lang_str, lang)) {
            std::cerr << "Invalid Remix language provided..." << std::endl;
            return;
        }

        ListDictionary(true, in_index, in_package, remix::def::ObjectDictionaries[static_cast<u32>(lang)]);
    }

    void ListRemixAdjectives(const std::string &in_index, const std::string &in_package, const std::string &lang_str) {
        remix::Language lang;
        if(!ParseRemixLanguage(lang_str, lang)) {
            std::cerr << "Invalid Remix language provided..." << std::endl;
            return;
        }

        ListDictionary(false, in_index, in_package, remix::def::AdjectiveDictionaries[static_cast<u32>(lang)]);
    }

    template<class L>
    void PrintTexts(const std::string &in_index, const std::string &in_package, const std::string &file_id_str, const L lang) {
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

            auto &file = fs.GetFile(file_id);
            R_TRY_ERRLOG(file.OpenRead(fs::FileCompression::None), "Unable to open filesystem file");
            ScopeGuard close_file([&]() {
                file.Close();
            });

            fmt::TextList<L> list;
            R_TRY_ERRLOG(list.ReadFrom(file), "Unable to read text list file");

            for(u32 i = 0; i < list.GetCount(); i++) {
                std::cout << "Text[" << i << "]: \"" << list.Get(lang, i) << "\"" << std::endl;
            }
        }
        catch(std::exception &ex) {
            std::cerr << "Invalid file ID: " << ex.what() << std::endl;
        }
    }

    void PrintBh2pTexts(const std::string &in_index, const std::string &in_package, const std::string &file_id_str, const std::string &lang_str) {
        bh2p::Language lang;
        if(!ParseBh2pLanguage(lang_str, lang, false)) {
            std::cerr << "Invalid BH2P language provided..." << std::endl;
            return;
        }

        PrintTexts<bh2p::Language>(in_index, in_package, file_id_str, lang);
    }

    void PrintRemixTexts(const std::string &in_index, const std::string &in_package, const std::string &file_id_str, const std::string &lang_str) {
        remix::Language lang;
        if(!ParseRemixLanguage(lang_str, lang)) {
            std::cerr << "Invalid Remix language provided..." << std::endl;
            return;
        }

        PrintTexts<remix::Language>(in_index, in_package, file_id_str, lang);
    }

}

namespace cli {

    void ListObjects(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &lang_str) {
        Game game;
        if(!ParseGame(game_str, game)) {
            std::cerr << "Invalid game provided..." << std::endl;
            return;
        }

        switch(game) {
            case Game::BH2P: {
                ListBh2pObjects(in_index, in_package, lang_str);
                break;
            }
            case Game::Remix: {
                ListRemixObjects(in_index, in_package, lang_str);
                break;
            }
        }
    }

    void ListAdjectives(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &lang_str) {
        Game game;
        if(!ParseGame(game_str, game)) {
            std::cerr << "Invalid game provided..." << std::endl;
            return;
        }

        switch(game) {
            case Game::BH2P: {
                ListBh2pAdjectives(in_index, in_package, lang_str);
                break;
            }
            case Game::Remix: {
                ListRemixAdjectives(in_index, in_package, lang_str);
                break;
            }
        }
    }

    void PrintTexts(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &file_id_str, const std::string &lang_str) {
        Game game;
        if(!ParseGame(game_str, game)) {
            std::cerr << "Invalid game provided..." << std::endl;
            return;
        }

        switch(game) {
            case Game::BH2P: {
                PrintBh2pTexts(in_index, in_package, file_id_str, lang_str);
                break;
            }
            case Game::Remix: {
                PrintRemixTexts(in_index, in_package, file_id_str, lang_str);
                break;
            }
        }
    }

}

