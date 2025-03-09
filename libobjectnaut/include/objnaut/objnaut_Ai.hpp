
#pragma once
#include <objnaut/objnaut_Filter.hpp>

namespace objnaut {

    enum class AiMood : u8 {
        Friendly = 0,
        Neutral = 1,
        Hostile = 2,
        Sleepy = 3,
        Sick = 4,
        Frenzy = 5,
        Defend = 6,
        Sad = 7
    };

    inline std::string FormatAiMood(const AiMood mood) {
        switch(mood) {
            case AiMood::Friendly:
                return "Friendly";
            case AiMood::Neutral:
                return "Neutral";
            case AiMood::Hostile:
                return "Hostile";
            case AiMood::Sleepy:
                return "Sleepy";
            case AiMood::Sick:
                return "Sick";
            case AiMood::Frenzy:
                return "Frenzy";
            case AiMood::Defend:
                return "Defend";
            case AiMood::Sad:
                return "Sad";
            default:
                return "";
        }
    }

    enum class AtrRepMode : u8 {
        AttractDestroy = 0,
        AttractConsume = 1,
        AttractInvestigate = 2,
        AttractFollow = 3,
        AttractProtect = 4,
        AttractUse = 5,
        AttractMount = 6,
        AttractSteal = 7,
        RepulseFlee = 8,
        AttractSplit = 9,
        AttractGuard = 10,
        UseToolSplit = 11,
        UseToolDealDamage = 12,
        UseToolFireProjectile = 13,
        UseToolUse = 14,
        StageObject = 15,
        UseVehicle = 16
    };

    inline std::string FormatAtrRepMode(const AtrRepMode mode) {
        switch(mode) {
            case AtrRepMode::AttractDestroy:
                return "AttractDestroy";
            case AtrRepMode::AttractConsume:
                return "AttractConsume";
            case AtrRepMode::AttractInvestigate:
                return "AttractInvestigate";
            case AtrRepMode::AttractFollow:
                return "AttractFollow";
            case AtrRepMode::AttractProtect:
                return "AttractProtect";
            case AtrRepMode::AttractUse:
                return "AttractUse";
            case AtrRepMode::AttractMount:
                return "AttractMount";
            case AtrRepMode::AttractSteal:
                return "AttractSteal";
            case AtrRepMode::RepulseFlee:
                return "RepulseFlee";
            case AtrRepMode::AttractSplit:
                return "AttractSplit";
            case AtrRepMode::AttractGuard:
                return "AttractGuard";
            case AtrRepMode::UseToolSplit:
                return "UseToolSplit";
            case AtrRepMode::UseToolDealDamage:
                return "UseToolDealDamage";
            case AtrRepMode::UseToolFireProjectile:
                return "UseToolFireProjectile";
            case AtrRepMode::UseToolUse:
                return "UseToolUse";
            case AtrRepMode::StageObject:
                return "StageObject";
            case AtrRepMode::UseVehicle:
                return "UseVehicle";
            default:
                return "";
        }
    }

    enum class AiEmoteType : u8 {
        Ankh = 0,
        Art = 1,
        Bird = 2,
        Brain = 3,
        Building = 4,
        Chemistry = 5,
        Consume = 6,
        Crown = 7,
        Death = 8,
        Destroy = 9,
        Drink = 10,
        Electric = 11,
        Entertainment = 12,
        Evil = 13,
        Exclamation = 14,
        Explode = 15,
        Family = 16,
        Female = 17,
        Fire = 18,
        Fish = 19,
        Flowers = 20,
        Follow = 21,
        Food = 22,
        Friendly = 23,
        Good = 24,
        Guard = 25,
        Hostile = 26,
        Hypnotized = 27,
        Investigate = 28,
        Justice = 29,
        Love = 30,
        Magic = 31,
        Male = 32,
        Mammal = 33,
        Math = 34,
        Mechanical = 35,
        Medical = 36,
        Medieval = 37,
        Military = 38,
        Money = 39,
        Mount = 40,
        Muscles = 41,
        Music = 42,
        Neutral = 43,
        Peace = 44,
        Plant = 45,
        Politics = 46,
        Protect = 47,
        Radioactive = 48,
        Religion = 49,
        Sad = 50,
        Scared = 51,
        Scary = 52,
        Science = 53,
        Sick = 54,
        Sight = 55,
        Sleepy = 56,
        Split = 57,
        Sports = 58,
        Steal = 59,
        Talk = 60,
        Toxic = 61,
        Use = 62,
        YinYang = 63
    };

    inline std::string FormatAiEmoteType(const AiEmoteType emote) {
        switch(emote) {
            case AiEmoteType::Ankh:
                return "Ankh";
            case AiEmoteType::Art:
                return "Art";
            case AiEmoteType::Bird:
                return "Bird";
            case AiEmoteType::Brain:
                return "Brain";
            case AiEmoteType::Building:
                return "Building";
            case AiEmoteType::Chemistry:
                return "Chemistry";
            case AiEmoteType::Consume:
                return "Consume";
            case AiEmoteType::Crown:
                return "Crown";
            case AiEmoteType::Death:
                return "Death";
            case AiEmoteType::Destroy:
                return "Destroy";
            case AiEmoteType::Drink:
                return "Drink";
            case AiEmoteType::Electric:
                return "Electric";
            case AiEmoteType::Entertainment:
                return "Entertainment";
            case AiEmoteType::Evil:
                return "Evil";
            case AiEmoteType::Exclamation:
                return "Exclamation";
            case AiEmoteType::Explode:
                return "Explode";
            case AiEmoteType::Family:
                return "Family";
            case AiEmoteType::Female:
                return "Female";
            case AiEmoteType::Fire:
                return "Fire";
            case AiEmoteType::Fish:
                return "Fish";
            case AiEmoteType::Flowers:
                return "Flowers";
            case AiEmoteType::Follow:
                return "Follow";
            case AiEmoteType::Food:
                return "Food";
            case AiEmoteType::Friendly:
                return "Friendly";
            case AiEmoteType::Good:
                return "Good";
            case AiEmoteType::Guard:
                return "Guard";
            case AiEmoteType::Hostile:
                return "Hostile";
            case AiEmoteType::Hypnotized:
                return "Hypnotized";
            case AiEmoteType::Investigate:
                return "Investigate";
            case AiEmoteType::Justice:
                return "Justice";
            case AiEmoteType::Love:
                return "Love";
            case AiEmoteType::Magic:
                return "Magic";
            case AiEmoteType::Male:
                return "Male";
            case AiEmoteType::Mammal:
                return "Mammal";
            case AiEmoteType::Math:
                return "Math";
            case AiEmoteType::Mechanical:
                return "Mechanical";
            case AiEmoteType::Medical:
                return "Medical";
            case AiEmoteType::Medieval:
                return "Medieval";
            case AiEmoteType::Military:
                return "Military";
            case AiEmoteType::Money:
                return "Money";
            case AiEmoteType::Mount:
                return "Mount";
            case AiEmoteType::Muscles:
                return "Muscles";
            case AiEmoteType::Music:
                return "Music";
            case AiEmoteType::Neutral:
                return "Neutral";
            case AiEmoteType::Peace:
                return "Peace";
            case AiEmoteType::Plant:
                return "Plant";
            case AiEmoteType::Politics:
                return "Politics";
            case AiEmoteType::Protect:
                return "Protect";
            case AiEmoteType::Radioactive:
                return "Radioactive";
            case AiEmoteType::Religion:
                return "Religion";
            case AiEmoteType::Sad:
                return "Sad";
            case AiEmoteType::Scared:
                return "Scared";
            case AiEmoteType::Scary:
                return "Scary";
            case AiEmoteType::Science:
                return "Science";
            case AiEmoteType::Sick:
                return "Sick";
            case AiEmoteType::Sight:
                return "Sight";
            case AiEmoteType::Sleepy:
                return "Sleepy";
            case AiEmoteType::Split:
                return "Split";
            case AiEmoteType::Sports:
                return "Sports";
            case AiEmoteType::Steal:
                return "Steal";
            case AiEmoteType::Talk:
                return "Talk";
            case AiEmoteType::Toxic:
                return "Toxic";
            case AiEmoteType::Use:
                return "Use";
            case AiEmoteType::YinYang:
                return "YinYang";
            default:
                return "";
        }
    }

    struct AiAtrRepOptions {
        AtrRepMode mode : 6;
        bool has_custom_emote : 1;
        bool only_when_equipped : 1;
    };
    static_assert(sizeof(AiAtrRepOptions) == sizeof(u8));
    
    struct AiAtrRep {
        u8 insert_point;
        AiAtrRepOptions options;
        AiEmoteType custom_emote;
        ObjectCategoryId obj_category_id;
        u16 obj_subcategory_id_1;
        u16 obj_subcategory_id_2;
        u16 obj_id;
        u16 adj_category_id;
        u16 adj_subcategory_id;
        u16 adj_id;
        Filter filter;
    };

    struct ModAiAtrRep {
        u8 insert_point;
        AiAtrRep atr_rep;
    };

    constexpr u8 AtrRepListModuleTag = 13;
    
}
