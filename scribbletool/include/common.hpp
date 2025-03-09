
#pragma once
#include <cstdint>
#include <sys/stat.h>
#include <fstream>

#include <args.hxx>

#include <twl/util/util_Compression.hpp>
#include <twl/gfx/gfx_Conversion.hpp>

#include <objnaut/fmt/fmt_Object.hpp>
#include <objnaut/io/io_FileSystem.hpp>

#include <objnaut/bh2p/fmt/fmt_TextList.hpp>
#include <objnaut/bh2p/def/def_Dictionary.hpp>
#include <objnaut/bh2p/def/def_TextList.hpp>

#include <objnaut/remix/fmt/fmt_TextList.hpp>
#include <objnaut/remix/def/def_Dictionary.hpp>

#include <data.h>

using namespace twl;
using namespace objnaut;

#define R_TRY_ERRLOG(rc, ...) { \
    const auto _tmp_rc = (rc); \
    if(_tmp_rc.IsFailure()) { \
        std::cerr << __VA_ARGS__ << ": " << _tmp_rc.GetDescription() << std::endl; \
        return; \
    } \
}

#define R_TRY_ERRLOG_BOOL(rc, ...) { \
    const auto _tmp_rc = (rc); \
    if(_tmp_rc.IsFailure()) { \
        std::cerr << __VA_ARGS__ << ": " << _tmp_rc.GetDescription() << std::endl; \
        return false; \
    } \
}

#define FORMAT_FX32(val) (float)((float)(val) / 4096.0f)

template<class C>
inline std::string DefaultNull(const C &val, std::string(&fmt_fn)(const C)) {
    const auto word = fmt_fn(val);
    if(!word.empty()) {
        return word;
    }
    else {
        return "[unknown value: " + std::to_string((int)val) + "]";
    }
}

template<class C>
inline std::string DefaultNullMask16(const C &val, std::string(&fmt_fn)(const C)) {
    const auto word = fmt_fn(val);
    if((u16)val == UINT16_MAX) {
        return "[any]";
    }
    else if(!word.empty()) {
        return word;
    }
    else {
        return "[unknown value: " + std::to_string((int)val) + "]";
    }
}

inline std::string Mask16(const u16 val) {
    if(val == UINT16_MAX) {
        return "[any]";
    }
    else {
        return std::to_string(val);
    }
}

inline std::string Mask32(const u32 val) {
    if(val == UINT32_MAX) {
        return "[any]";
    }
    else {
        return std::to_string(val);
    }
}

inline bool ParseBh2pLanguage(const std::string &lang_str, bh2p::Language &out_lang, const bool allow_unk) {
    if(lang_str == "en") {
        out_lang = bh2p::Language::English;
    }
    else if(lang_str == "nl") {
        out_lang = bh2p::Language::Dutch;
    }
    else if(lang_str == "fr") {
        out_lang = bh2p::Language::French;
    }
    else if(lang_str == "ge") {
        out_lang = bh2p::Language::German;
    }
    else if(lang_str == "it") {
        out_lang = bh2p::Language::Italian;
    }
    else if(lang_str == "es") {
        out_lang = bh2p::Language::Spanish;
    }
    else if(allow_unk && (lang_str == "unk")) {
        out_lang = bh2p::Language::UnkSpecial;
    }
    else {
        return false;
    }

    return true;
}

inline bool ParseRemixLanguage(const std::string &lang_str, remix::Language &out_lang) {
    if(lang_str == "en") {
        out_lang = remix::Language::English;
    }
    else if(lang_str == "en-uk") {
        out_lang = remix::Language::EnglishUk;
    }
    else if(lang_str == "ge") {
        out_lang = remix::Language::German;
    }
    else {
        return false;
    }

    return true;
}

enum class Game {
    BH2P,
    Remix
};

inline bool ParseGame(const std::string &game_str, Game &out_game) {
    if(game_str == "bh2p") {
        out_game = Game::BH2P;
    }
    else if(game_str == "remix") {
        out_game = Game::Remix;
    }
    else {
        return false;
    }

    return true;
}

inline std::string GetGameName(const Game game) {
    switch(game) {
        case Game::BH2P:
            return "Super Scribblenauts";
        case Game::Remix:
            return "Scribblenauts Remix";
        default:
            return "";
    }
}
