
#pragma once
#include <objnaut/objnaut_Base.hpp>

namespace objnaut {

    enum class ObjectCategoryId : u16 {
        Audio = 0,
        Big = 1,
        Bird = 2,
        BuildingObjects = 3,
        Clothes = 4,
        Container = 5,
        Creature = 6,
        Electronics = 7,
        Entertainment = 8,
        Environment = 9,
        Fish = 10,
        Food = 11,
        Furniture = 12,
        Gameplay = 13,
        Human = 14,
        Insect = 15,
        Mammal = 16,
        Materials = 17,
        Misc = 18,
        Organic = 19,
        Plants = 20,
        Reptile = 21,
        Tool = 22,
        Vehicle = 23,
        Weapon = 24,
        Audio_Accessories = 25,
        Audio_Amplifying = 26,
        Audio_Audioplayer = 27,
        Audio_Instrument = 28,
        Audio_Muting = 29,
        Audio_Accessories_Metal = 30,
        Audio_Accessories_Other = 31,
        Audio_Accessories_Wood = 32,
        Audio_Amplifying_Sub2None = 46,
        Audio_Audioplayer_Electric = 52,
        Audio_Audioplayer_Other = 53,
        Audio_Instrument_Buzzy = 66,
        Audio_Instrument_Electric = 67,
        Audio_Instrument_Metal = 68,
        Audio_Instrument_Wood = 69,
        Audio_Muting_Sub2None = 107,
        Big_Animals = 110,
        Big_Children = 111,
        Big_Entertainment = 112,
        Big_Environment = 113,
        Big_Fooddrink = 115,
        Big_Living = 117,
        Big_Medical = 118,
        Big_Places = 119,
        Big_Precious = 120,
        Big_Rooms = 122,
        Big_Transit = 124,
        Big_Water = 125,
        Big_Animals_Sub2None = 126,
        Big_Children_Sub2None = 129,
        Big_Entertainment_Sub2None = 133,
        Big_Environment_Sub2None = 146,
        Big_Fooddrink_Sub2None = 167,
        Big_Living_Sub2None = 182,
        Big_Medical_Sub2None = 193,
        Big_Places_Sub2None = 197,
        Big_Precious_Sub2None = 220,
        Big_Rooms_Sub2None = 236,
        Big_Transit_Sub2None = 243,
        Big_Water_Sub2None = 248,
        Bird_Large = 257,
        Bird_Medium = 258,
        Bird_Small = 259,
        Bird_Large_Other = 261,
        Bird_Medium_Carnivore = 268,
        Bird_Medium_Fisheater = 269,
        Bird_Medium_Vegetarian = 270,
        Bird_Small_Other = 284,
        Bird_Small_Vegetarian = 285,
        BuildingObjects_BuildingBlocks = 306,
        BuildingObjects_Buildings = 307,
        BuildingObjects_BuildingBlocks_Electric = 308,
        BuildingObjects_BuildingBlocks_Glass = 309,
        BuildingObjects_BuildingBlocks_Metal = 310,
        BuildingObjects_BuildingBlocks_Stone = 311,
        BuildingObjects_BuildingBlocks_Wood = 312,
        BuildingObjects_Buildings_Animals = 355,
        BuildingObjects_Buildings_Other = 356,
        Clothes_Face = 382,
        Clothes_Feet = 383,
        Clothes_Head = 385,
        Clothes_Jewelry = 386,
        Clothes_Legs = 387,
        Clothes_Torso = 388,
        Clothes_Face_Other = 389,
        Clothes_Face_Sight = 390,
        Clothes_Feet_Sub2None = 402,
        Clothes_Hands_Sub2None = 410,
        Clothes_Head_Appearance = 418,
        Clothes_Head_Protection = 419,
        Clothes_Head_Warmth = 420,
        Clothes_Jewelry_Sub2None = 449,
        Clothes_Legs_Appearance = 458,
        Clothes_Legs_Other = 459,
        Clothes_Legs_Warmth = 460,
        Clothes_Torso_Appearance = 474,
        Clothes_Torso_Armor = 475,
        Clothes_Torso_Other = 476,
        Clothes_Torso_Warmth = 477,
        Container_Bag = 519,
        Container_Flat = 520,
        Container_Lid = 521,
        Container_Lockable = 522,
        Container_Nolid = 523,
        Container_Other = 524,
        Container_Bag_Cloth = 525,
        Container_Bag_Paper = 526,
        Container_Bag_Synthetic = 527,
        Container_Flat_Food = 536,
        Container_Flat_Other = 537,
        Container_Lid_Glass = 545,
        Container_Lid_Metal = 546,
        Container_Lid_Plastic = 547,
        Container_Lid_Wood = 548,
        Container_Lockable_Metal = 572,
        Container_Lockable_Wood = 573,
        Container_Nolid_Glass = 579,
        Container_Nolid_Metal = 580,
        Container_Nolid_Plastic = 581,
        Container_Nolid_Wood = 582,
        Container_Other_Money = 613,
        Electronics_Medium = 661,
        Electronics_Small = 662,
        Electronics_Tiny = 663,
        Electronics_Medium_Sub2None = 664,
        Electronics_Small_Sub2None = 682,
        Electronics_Tiny_Sub2None = 707,
        Entertainment_Ball = 741,
        Entertainment_Electric = 742,
        Entertainment_Metal = 743,
        Entertainment_Other = 744,
        Entertainment_Plastic = 745,
        Entertainment_Rubber = 746,
        Entertainment_Sports = 747,
        Entertainment_Wood = 748,
        Entertainment_Ball_Bouncy = 749,
        Entertainment_Ball_Heavy = 750,
        Entertainment_Electric_Gaming = 767,
        Entertainment_Electric_Other = 768,
        Entertainment_Electric_Personal = 769,
        Entertainment_Electric_Viewing = 770,
        Entertainment_Metal_Bigtoy = 780,
        Entertainment_Metal_Toy = 781,
        Entertainment_Other_Game = 786,
        Entertainment_Other_Toy = 787,
        Entertainment_Plastic_Game = 802,
        Entertainment_Plastic_Sports = 803,
        Entertainment_Plastic_Toy = 804,
        Entertainment_Rubber_Sports = 816,
        Entertainment_Rubber_Toy = 817,
        Entertainment_Sports_Parts = 821,
        Entertainment_Wood_Huge = 835,
        Entertainment_Wood_Large = 836,
        Entertainment_Wood_Medium = 837,
        Entertainment_Wood_Small = 838,
        Environment_Damaging = 853,
        Environment_Ice = 854,
        Environment_Rock = 855,
        Environment_Sky = 856,
        Environment_Vapor = 857,
        Environment_Water = 858,
        Environment_Damaging_Sub2None = 859,
        Environment_Ice_Sub2None = 863,
        Environment_Rock_Sub2None = 872,
        Environment_Sky_Sub2None = 875,
        Environment_Vapor_Sub2None = 885,
        Environment_Water_Sub2None = 890,
        Fish_Carnivore = 895,
        Fish_Nonmoving = 896,
        Fish_Predator = 897,
        Fish_Prey = 898,
        Fish_Slow = 899,
        Fish_Sub1None = 900,
        Fish_Carnivore_Sub2None = 901,
        Fish_Nonmoving_Sub2None = 908,
        Fish_Predator_Sub2None = 913,
        Fish_Prey_Sub2None = 918,
        Fish_Slow_Sub2None = 926,
        Fish_Sub1None_Sub2None = 935,
        Food_Beverages = 937,
        Food_Condiment = 938,
        Food_Dairy = 939,
        Food_Fruitveg = 940,
        Food_Junk = 941,
        Food_Meat = 942,
        Food_NutsGrains = 943,
        Food_OtherMeal = 944,
        Food_Beverages_Caffeinated = 946,
        Food_Beverages_Soothing = 947,
        Food_Beverages_Sweet = 948,
        Food_Condiment_Fatal = 971,
        Food_Condiment_Flavor = 972,
        Food_Condiment_Garnish = 973,
        Food_Condiment_Ingredient = 974,
        Food_Condiment_MildlySpicy = 975,
        Food_Condiment_Recovery = 976,
        Food_Condiment_Sideitem = 977,
        Food_Condiment_Spicy = 978,
        Food_Condiment_Sweet = 979,
        Food_Condiment_Viscous = 980,
        Food_Dairy_Ingredient = 1024,
        Food_Dairy_Liquid = 1025,
        Food_Dairy_Made = 1026,
        Food_Dairy_Raw = 1027,
        Food_FruitVeg_Flavor = 1039,
        Food_FruitVeg_Leaf = 1040,
        Food_FruitVeg_Raw = 1041,
        Food_FruitVeg_Sweet = 1042,
        Food_Junk_Breakfast = 1094,
        Food_Junk_Frozen = 1095,
        Food_Junk_Salty = 1096,
        Food_Junk_Sweet = 1097,
        Food_Meat_Cooked = 1138,
        Food_Meat_Rawred = 1139,
        Food_Meat_Rawsea = 1140,
        Food_Meat_Rawwhite = 1141,
        Food_NutsGrains_Made = 1173,
        Food_NutsGrains_Many = 1174,
        Food_NutsGrains_Raw = 1175,
        Food_OtherMeal_Other = 1194,
        Food_OtherMeal_Spicy = 1195,
        Furniture_Appliances = 1214,
        Furniture_Container = 1215,
        Furniture_Fabric = 1216,
        Furniture_Metal = 1217,
        Furniture_Other = 1218,
        Furniture_Wood = 1219,
        Furniture_Appliances_Cooking = 1220,
        Furniture_Appliances_Cooling = 1221,
        Furniture_Appliances_Heating = 1222,
        Furniture_Appliances_Light = 1223,
        Furniture_Appliances_Other = 1224,
        Furniture_Appliances_Washing = 1225,
        Furniture_Container_Metal = 1260,
        Furniture_Container_Wood = 1261,
        Furniture_Fabric_Sub2None = 1274,
        Furniture_Metal_Sub2None = 1277,
        Furniture_Other_Sub2None = 1288,
        Furniture_Wood_Sub2None = 1293,
        Gameplay_Ice = 1314,
        Gameplay_Metal = 1315,
        Gameplay_Stone = 1316,
        Gameplay_Trigger = 1317,
        Gameplay_Wood = 1318,
        Gameplay_Ice_Encasing = 1319,
        Gameplay_Ice_NonEncasing = 1320,
        Gameplay_Metal_Normal = 1323,
        Gameplay_Stone_LowIntegrity = 1340,
        Gameplay_Stone_Normal = 1341,
        Gameplay_Trigger_Button = 1347,
        Gameplay_Trigger_Other = 1348,
        Gameplay_Trigger_Switch = 1349,
        Gameplay_Wood_LowIntegrity = 1358,
        Gameplay_Wood_Normal = 1359,
        Insect_Air = 1504,
        Insect_Ground = 1505,
        Insect_Water = 1506,
        Insect_Air_AttractedTolight = 1507,
        Insect_Air_LeafEater = 1508,
        Insect_Air_Stingers = 1509,
        Insect_Ground_Aggressive = 1518,
        Insect_Ground_Gooey = 1519,
        Insect_Ground_Harmless = 1520,
        Insect_Ground_LeafEater = 1521,
        Insect_Ground_Nonmoving = 1522,
        Insect_Ground_Parasite = 1523,
        Insect_Water_Harmless = 1548,
        Insect_Water_Nonmoving = 1549,
        Insect_Water_Pincers = 1550,
        Mammal_Huge = 1561,
        Mammal_Large = 1562,
        Mammal_Medium = 1563,
        Mammal_Small = 1564,
        Mammal_Tiny = 1565,
        Mammal_Huge_Bear = 1566,
        Mammal_Huge_Herbivore = 1567,
        Mammal_Huge_Hooved = 1568,
        Mammal_Huge_Other = 1569,
        Mammal_Huge_Water = 1570,
        Mammal_Large_Feline = 1587,
        Mammal_Large_Hooved = 1588,
        Mammal_Large_Other = 1589,
        Mammal_Large_Water = 1590,
        Mammal_Medium_Dog = 1610,
        Mammal_Medium_Hooved = 1611,
        Mammal_Medium_Other = 1612,
        Mammal_Small_Critter = 1633,
        Mammal_Small_Dog = 1634,
        Mammal_Small_Hooved = 1635,
        Mammal_Small_Other = 1636,
        Mammal_Small_Water = 1637,
        Mammal_Tiny_Critter = 1668,
        Mammal_Tiny_Dog = 1669,
        Mammal_Tiny_Other = 1670,
        Materials_Bone = 1683,
        Materials_Bouncy = 1684,
        Materials_Burning = 1685,
        Materials_Dirt = 1686,
        Materials_Fabric = 1687,
        Materials_Flammable = 1688,
        Materials_Fragile = 1689,
        Materials_HighIntegrity = 1690,
        Materials_Magnet = 1691,
        Materials_Metal = 1692,
        Materials_Other = 1693,
        Materials_Plastic = 1694,
        Materials_Precious = 1695,
        Materials_Rock = 1696,
        Materials_Sticky = 1697,
        Materials_Bone_Sub2None = 1698,
        Materials_Bouncy_Sub2None = 1701,
        Materials_Burning_Sub2None = 1703,
        Materials_Dirt_Sub2None = 1705,
        Materials_Fabric_Sub2None = 1714,
        Materials_Flammable_Highly = 1725,
        Materials_Flammable_Slippery = 1726,
        Materials_Flammable_Sub2None = 1727,
        Materials_Fragile_Sub2None = 1746,
        Materials_HighIntegrity_Sub2None = 1749,
        Materials_Magnet_Destroys = 1751,
        Materials_Magnet_General = 1752,
        Materials_Metal_Sub2None = 1756,
        Materials_Other_Sub2None = 1763,
        Materials_Plastic_Sub2None = 1767,
        Materials_Precious_Sub2None = 1769,
        Materials_Rock_HighIntegrity = 1784,
        Materials_Rock_LowIntegrity = 1785,
        Materials_Rock_MediumIntegrity = 1786,
        Materials_Sticky_Sub2None = 1803,
        Misc_Fabric = 1807,
        Misc_Glass = 1808,
        Misc_Metal = 1809,
        Misc_Other = 1810,
        Misc_Paper = 1811,
        Misc_Plastic = 1812,
        Misc_Stone = 1813,
        Misc_Wood = 1814,
        Misc_Fabric_Highintegrity = 1815,
        Misc_Fabric_Lowintegrity = 1816,
        Misc_Fabric_Mediumintegrity = 1817,
        Misc_Glass_Sub2None = 1850,
        Misc_Metal_Large = 1860,
        Misc_Metal_Medium = 1861,
        Misc_Metal_Small = 1862,
        Misc_Metal_Tiny = 1863,
        Misc_Other_Sub2None = 1921,
        Misc_Paper_Other = 1935,
        Misc_Paper_Thick = 1936,
        Misc_Plastic_Medium = 1967,
        Misc_Plastic_Small = 1968,
        Misc_Stone_Large = 1988,
        Misc_Stone_Medium = 1989,
        Misc_Stone_Small = 1990,
        Misc_Stone_Tiny = 1991,
        Misc_Wood_Large = 2013,
        Misc_Wood_Medium = 2014,
        Misc_Wood_Small = 2015,
        Misc_Wood_Tiny = 2016,
        Organic_Bone = 2054,
        Organic_Parts = 2055,
        Organic_Bone_Other = 2056,
        Organic_Bone_Sharp = 2057,
        Organic_Parts_Flesh = 2080,
        Organic_Parts_Gooey = 2081,
        Organic_Parts_Other = 2082,
        Plants_ConiferousTree = 2129,
        Plants_DeciduousTree = 2130,
        Plants_Flower = 2131,
        Plants_OtherGreenery = 2132,
        Plants_Seed = 2133,
        Plants_Shrub = 2134,
        Plants_Wood = 2135,
        Plants_ConiferousTree_Full = 2136,
        Plants_DeciduousTree_Full = 2138,
        Plants_DeciduousTree_Small = 2139,
        Plants_DeciduousTree_Thin = 2140,
        Plants_Flower_Large = 2149,
        Plants_Flower_Presentable = 2150,
        Plants_Flower_Raw = 2151,
        Plants_Flower_Romantic = 2152,
        Plants_OtherGreenery_Parts = 2166,
        Plants_OtherGreenery_Ropelike = 2167,
        Plants_Seed_PreBloom = 2173,
        Plants_Seed_Young = 2174,
        Plants_Shrub_GroundCover = 2180,
        Plants_Shrub_Harmful = 2181,
        Plants_Shrub_Presentable = 2182,
        Plants_Shrub_Raw = 2183,
        Plants_Shrub_Water = 2184,
        Plants_Shrub_Wild = 2185,
        Plants_Wood_Parts = 2203,
        Plants_Wood_Useful = 2204,
        Reptile_Dinosaur = 2212,
        Reptile_Ground = 2213,
        Reptile_Water = 2214,
        Reptile_Dinosaur_Other = 2215,
        Reptile_Dinosaur_Predator = 2216,
        Reptile_Ground_Lizard = 2229,
        Reptile_Ground_Snake = 2230,
        Reptile_Water_Other = 2237,
        Reptile_Water_Predator = 2238,
        Tool_Bashing = 2248,
        Tool_Bouncing = 2249,
        Tool_Chemical = 2250,
        Tool_Createsfire = 2251,
        Tool_Cutting = 2252,
        Tool_Digging = 2253,
        Tool_Drawing = 2254,
        Tool_Fans = 2255,
        Tool_Grabbing = 2256,
        Tool_Hygeine = 2257,
        Tool_Kitchen = 2258,
        Tool_Lighting = 2259,
        Tool_Medical = 2260,
        Tool_OfficeSupplies = 2261,
        Tool_Poking = 2262,
        Tool_Restraint = 2263,
        Tool_Rope = 2264,
        Tool_Special = 2265,
        Tool_SprayWater = 2266,
        Tool_UnderWater = 2267,
        Tool_Bashing_Cleaning = 2268,
        Tool_Bashing_Other = 2269,
        Tool_Bashing_Sports = 2270,
        Tool_Bouncing_NoEquip = 2290,
        Tool_Bouncing_Other = 2291,
        Tool_Chemical_Nouse = 2301,
        Tool_Chemical_Other = 2302,
        Tool_CreatesFire_NoEquip = 2320,
        Tool_CreatesFire_Nouse = 2321,
        Tool_CreatesFire_Other = 2322,
        Tool_Cutting_CutsWood = 2338,
        Tool_Cutting_Other = 2339,
        Tool_Digging_Sub2None = 2355,
        Tool_Drawing_Liquid = 2365,
        Tool_Drawing_Other = 2366,
        Tool_Fans_NoEquip = 2389,
        Tool_Fans_Other = 2390,
        Tool_Grabbing_Sub2None = 2395,
        Tool_Hygeine_Fabric = 2402,
        Tool_Hygeine_Paper = 2403,
        Tool_Hygeine_Plastic = 2404,
        Tool_Kitchen_Metal = 2418,
        Tool_Kitchen_Other = 2419,
        Tool_Kitchen_Wood = 2420,
        Tool_Lighting_Beam = 2431,
        Tool_Lighting_Circular = 2432,
        Tool_Medical_Sub2None = 2438,
        Tool_Officesupplies_Glass = 2444,
        Tool_Officesupplies_Metal = 2445,
        Tool_Officesupplies_Paper = 2446,
        Tool_Officesupplies_Plastic = 2447,
        Tool_Officesupplies_Stone = 2448,
        Tool_Officesupplies_Wood = 2449,
        Tool_Poking_Sub2None = 2489,
        Tool_Restraint_Other = 2497,
        Tool_Restraint_Piercing = 2498,
        Tool_Restraint_Sticky = 2499,
        Tool_Rope_Charged = 2519,
        Tool_Rope_Grapple = 2520,
        Tool_Rope_Other = 2521,
        Tool_Special_Buoyant = 2538,
        Tool_Special_Cutting = 2539,
        Tool_Special_Equip = 2540,
        Tool_Special_NoEquip = 2541,
        Tool_Special_Precious = 2542,
        Tool_Spraywater_Sub2None = 2593,
        Tool_Underwater_Sub2None = 2602,
        Vehicle_Air = 2609,
        Vehicle_Ground = 2610,
        Vehicle_Snow = 2611,
        Vehicle_Space = 2612,
        Vehicle_Water = 2613,
        Vehicle_Air_Burst = 2614,
        Vehicle_Air_Float = 2615,
        Vehicle_Air_Large = 2616,
        Vehicle_Air_Propeller = 2617,
        Vehicle_Ground_Large = 2628,
        Vehicle_Ground_Medium = 2629,
        Vehicle_Ground_Small = 2630,
        Vehicle_Ground_Tiny = 2631,
        Vehicle_Snow_Medium = 2678,
        Vehicle_Snow_Small = 2679,
        Vehicle_Snow_Tiny = 2680,
        Vehicle_Space_Large = 2687,
        Vehicle_Space_Medium = 2688,
        Vehicle_Water_Medium = 2691,
        Vehicle_Water_Small = 2692,
        Weapon_Artillery = 2711,
        Weapon_Bomb = 2712,
        Weapon_Gun = 2713,
        Weapon_Melee = 2714,
        Weapon_Parts = 2715,
        Weapon_Projectile = 2716,
        Weapon_Trap = 2717,
        Weapon_Artillery_Sub2None = 2718,
        Weapon_Bomb_Sub2None = 2726,
        Weapon_Gun_LargeSpread = 2735,
        Weapon_Gun_LowDamage = 2736,
        Weapon_Gun_Normal = 2737,
        Weapon_Gun_Other = 2738,
        Weapon_Melee_Bashing = 2753,
        Weapon_Melee_Cutting = 2754,
        Weapon_Melee_Other = 2755,
        Weapon_Melee_Poking = 2756,
        Weapon_Melee_Spray = 2757,
        Weapon_Parts_Explosive = 2788,
        Weapon_Parts_Other = 2789,
        Weapon_Projectile_Sub2None = 2808,
        Weapon_Trap_Sub2None = 2819,
        Weapon_Projectile_Magic = 2842,
        Gameplay_Gameonly = 2860,
        Gameplay_Gameonly_Starite = 2861,
        Human_Player = 2863,
        Human_Player_Maxwell = 2864,
        Environment_Sky_Stormmacro = 3057,
        Plants_DeciduousTree_FruitTreeMacro = 3193,
        Plants_OtherGreenery_RopeMacro = 3236,
        Plants_Shrub_FruitMacro = 3241,
        Vehicle_Parts = 3338,
        Vehicle_Parts_Sub2None = 3339,
        Human_Developer = 3456,
        Human_Developer_Secretz = 3458,
        Gameplay_Trigger_LowIntegrity = 3564,
        Electronics_Large = 3624,
        Electronics_Large_Sub2None = 3625,
        BuildingObjects_Ancient = 3647,
        BuildingObjects_Ancient_Stone = 3648,
        Vehicle_Snow_Large = 4015,
        Mammal_Medium_Feline = 4068,
        Tool_Hygeine_Other = 4172,
        Insect_Air_Harmless = 4278,
        Audio_Amplifying_Metal = 4652,
        Audio_Amplifying_Other = 4653,
        Audio_Instrument_Other = 4656,
        Plants_OtherGreenery_FruitMacro = 4953,
        Plants_Shrub_VeggieMacro = 4955,
        Easteregg = 5408,
        Easteregg_Secretz = 5587,
        Easteregg_Secretz_Other = 5588,
        Environment_Sky_Zodiac = 5601,
        Clothes_Head_Hair = 5835,
        Mammal_Small_Cat = 5857,
        Big_Entertainment_Sports = 5858,
        Tool_Special_Wings = 5971,
        Clothes_Face_Hair = 5985,
        Weapon_Magic = 6013,
        Weapon_Magic_Hand = 6014,
        Human_Developer_Devfriend = 6062,
        Creature_Friendly = 6129,
        Creature_Robot = 6130,
        Creature_Scary = 6131,
        Creature_Friendly_Animal = 6132,
        Creature_Friendly_Gods = 6133,
        Creature_Friendly_Human = 6134,
        Creature_Friendly_Hybrid = 6135,
        Creature_Friendly_Other = 6136,
        Big_Places_Government = 6138,
        Big_Places_Mechanic = 6139,
        Big_Places_Military = 6140,
        Big_Places_Morbid = 6141,
        Creature_Robot_Normal = 6142,
        Big_Places_Museum = 6143,
        Creature_Scary_Beast = 6144,
        Creature_Scary_Demon = 6145,
        Creature_Scary_Evil = 6146,
        Creature_Scary_Gods = 6147,
        Creature_Scary_Neutral = 6148,
        Creature_Scary_Undead = 6149,
        Big_Places_Religion = 6158,
        Big_Places_Science = 6159,
        Big_Places_Shopping = 6160,
        Big_Water_Structures = 6171,
        Human_Athletes = 6179,
        Human_Criminals = 6180,
        Human_Entertainment = 6181,
        Human_Fighters = 6182,
        Human_Legal = 6183,
        Human_Other = 6184,
        Human_Ruler = 6185,
        Human_Science = 6186,
        Human_Athletes_Competitive = 6187,
        Human_Athletes_Fighter = 6188,
        Human_Athletes_Other = 6189,
        Human_Athletes_Support = 6190,
        Human_Criminals_Crazy = 6195,
        Human_Criminals_Crime = 6196,
        Human_Criminals_Other = 6197,
        Human_Criminals_Super = 6198,
        Human_Entertainment_Actor = 6203,
        Human_Entertainment_Artist = 6204,
        Human_Entertainment_Dancer = 6205,
        Human_Entertainment_Musician = 6206,
        Human_Entertainment_Other = 6207,
        Human_Entertainment_Performer = 6208,
        Human_Entertainment_Singer = 6209,
        Human_Fighters_Ancient = 6217,
        Human_Fighters_Medieval = 6219,
        Human_Fighters_Military = 6220,
        Human_Fighters_Super = 6221,
        Human_Legal_JusticeSystem = 6227,
        Human_Legal_Police = 6228,
        Human_Other_Animals = 6232,
        Human_Other_Basic = 6233,
        Human_Other_Business = 6234,
        Human_Other_Children = 6235,
        Human_Other_Cleaning = 6236,
        Human_Other_Craftsman = 6237,
        Human_Other_Education = 6238,
        Human_Other_Farming = 6239,
        Human_Other_Food = 6240,
        Human_Other_Government = 6241,
        Human_Other_Morbid = 6242,
        Human_Other_Other = 6243,
        Human_Other_PickyEaters = 6244,
        Human_Other_Religion = 6245,
        Human_Other_VehicleRelated = 6246,
        Human_Other_Wedding = 6247,
        Human_Ruler_Elected = 6264,
        Human_Ruler_Military = 6265,
        Human_Ruler_Royal = 6266,
        Human_Science_Biologist = 6270,
        Human_Science_Medical = 6271,
        Human_Science_Other = 6272,
        Human_Science_Space = 6273,
        Misc_Metal_Signs = 6278,
        Weapon_Scifi = 6348,
        Weapon_Scifi_Gun = 6349,
        Clothes_Hands = 6771,
        BuildingObjects_Shapes = 6817,
        BuildingObjects_Shapes_Sub2None = 6818,
        BuildingObjects_Letters = 6921,
        BuildingObjects_Letters_Letters = 6922,
        BuildingObjects_Letters_Numbers = 6923,
        BuildingObjects_Letters_Punctuation = 6924,
        Human_Player_Brothers = 7185
    };

    inline std::string FormatObjectCategoryId(const ObjectCategoryId category) {
        switch(category) {
            case ObjectCategoryId::Audio:
                return "Audio";
            case ObjectCategoryId::Big:
                return "Big";
            case ObjectCategoryId::Bird:
                return "Bird";
            case ObjectCategoryId::BuildingObjects:
                return "BuildingObjects";
            case ObjectCategoryId::Clothes:
                return "Clothes";
            case ObjectCategoryId::Container:
                return "Container";
            case ObjectCategoryId::Creature:
                return "Creature";
            case ObjectCategoryId::Electronics:
                return "Electronics";
            case ObjectCategoryId::Entertainment:
                return "Entertainment";
            case ObjectCategoryId::Environment:
                return "Environment";
            case ObjectCategoryId::Fish:
                return "Fish";
            case ObjectCategoryId::Food:
                return "Food";
            case ObjectCategoryId::Furniture:
                return "Furniture";
            case ObjectCategoryId::Gameplay:
                return "Gameplay";
            case ObjectCategoryId::Human:
                return "Human";
            case ObjectCategoryId::Insect:
                return "Insect";
            case ObjectCategoryId::Mammal:
                return "Mammal";
            case ObjectCategoryId::Materials:
                return "Materials";
            case ObjectCategoryId::Misc:
                return "Misc";
            case ObjectCategoryId::Organic:
                return "Organic";
            case ObjectCategoryId::Plants:
                return "Plants";
            case ObjectCategoryId::Reptile:
                return "Reptile";
            case ObjectCategoryId::Tool:
                return "Tool";
            case ObjectCategoryId::Vehicle:
                return "Vehicle";
            case ObjectCategoryId::Weapon:
                return "Weapon";
            case ObjectCategoryId::Audio_Accessories:
                return "Audio_Accessories";
            case ObjectCategoryId::Audio_Amplifying:
                return "Audio_Amplifying";
            case ObjectCategoryId::Audio_Audioplayer:
                return "Audio_Audioplayer";
            case ObjectCategoryId::Audio_Instrument:
                return "Audio_Instrument";
            case ObjectCategoryId::Audio_Muting:
                return "Audio_Muting";
            case ObjectCategoryId::Audio_Accessories_Metal:
                return "Audio_Accessories_Metal";
            case ObjectCategoryId::Audio_Accessories_Other:
                return "Audio_Accessories_Other";
            case ObjectCategoryId::Audio_Accessories_Wood:
                return "Audio_Accessories_Wood";
            case ObjectCategoryId::Audio_Amplifying_Sub2None:
                return "Audio_Amplifying_Sub2None";
            case ObjectCategoryId::Audio_Audioplayer_Electric:
                return "Audio_Audioplayer_Electric";
            case ObjectCategoryId::Audio_Audioplayer_Other:
                return "Audio_Audioplayer_Other";
            case ObjectCategoryId::Audio_Instrument_Buzzy:
                return "Audio_Instrument_Buzzy";
            case ObjectCategoryId::Audio_Instrument_Electric:
                return "Audio_Instrument_Electric";
            case ObjectCategoryId::Audio_Instrument_Metal:
                return "Audio_Instrument_Metal";
            case ObjectCategoryId::Audio_Instrument_Wood:
                return "Audio_Instrument_Wood";
            case ObjectCategoryId::Audio_Muting_Sub2None:
                return "Audio_Muting_Sub2None";
            case ObjectCategoryId::Big_Animals:
                return "Big_Animals";
            case ObjectCategoryId::Big_Children:
                return "Big_Children";
            case ObjectCategoryId::Big_Entertainment:
                return "Big_Entertainment";
            case ObjectCategoryId::Big_Environment:
                return "Big_Environment";
            case ObjectCategoryId::Big_Fooddrink:
                return "Big_Fooddrink";
            case ObjectCategoryId::Big_Living:
                return "Big_Living";
            case ObjectCategoryId::Big_Medical:
                return "Big_Medical";
            case ObjectCategoryId::Big_Places:
                return "Big_Places";
            case ObjectCategoryId::Big_Precious:
                return "Big_Precious";
            case ObjectCategoryId::Big_Rooms:
                return "Big_Rooms";
            case ObjectCategoryId::Big_Transit:
                return "Big_Transit";
            case ObjectCategoryId::Big_Water:
                return "Big_Water";
            case ObjectCategoryId::Big_Animals_Sub2None:
                return "Big_Animals_Sub2None";
            case ObjectCategoryId::Big_Children_Sub2None:
                return "Big_Children_Sub2None";
            case ObjectCategoryId::Big_Entertainment_Sub2None:
                return "Big_Entertainment_Sub2None";
            case ObjectCategoryId::Big_Environment_Sub2None:
                return "Big_Environment_Sub2None";
            case ObjectCategoryId::Big_Fooddrink_Sub2None:
                return "Big_Fooddrink_Sub2None";
            case ObjectCategoryId::Big_Living_Sub2None:
                return "Big_Living_Sub2None";
            case ObjectCategoryId::Big_Medical_Sub2None:
                return "Big_Medical_Sub2None";
            case ObjectCategoryId::Big_Places_Sub2None:
                return "Big_Places_Sub2None";
            case ObjectCategoryId::Big_Precious_Sub2None:
                return "Big_Precious_Sub2None";
            case ObjectCategoryId::Big_Rooms_Sub2None:
                return "Big_Rooms_Sub2None";
            case ObjectCategoryId::Big_Transit_Sub2None:
                return "Big_Transit_Sub2None";
            case ObjectCategoryId::Big_Water_Sub2None:
                return "Big_Water_Sub2None";
            case ObjectCategoryId::Bird_Large:
                return "Bird_Large";
            case ObjectCategoryId::Bird_Medium:
                return "Bird_Medium";
            case ObjectCategoryId::Bird_Small:
                return "Bird_Small";
            case ObjectCategoryId::Bird_Large_Other:
                return "Bird_Large_Other";
            case ObjectCategoryId::Bird_Medium_Carnivore:
                return "Bird_Medium_Carnivore";
            case ObjectCategoryId::Bird_Medium_Fisheater:
                return "Bird_Medium_Fisheater";
            case ObjectCategoryId::Bird_Medium_Vegetarian:
                return "Bird_Medium_Vegetarian";
            case ObjectCategoryId::Bird_Small_Other:
                return "Bird_Small_Other";
            case ObjectCategoryId::Bird_Small_Vegetarian:
                return "Bird_Small_Vegetarian";
            case ObjectCategoryId::BuildingObjects_BuildingBlocks:
                return "BuildingObjects_BuildingBlocks";
            case ObjectCategoryId::BuildingObjects_Buildings:
                return "BuildingObjects_Buildings";
            case ObjectCategoryId::BuildingObjects_BuildingBlocks_Electric:
                return "BuildingObjects_BuildingBlocks_Electric";
            case ObjectCategoryId::BuildingObjects_BuildingBlocks_Glass:
                return "BuildingObjects_BuildingBlocks_Glass";
            case ObjectCategoryId::BuildingObjects_BuildingBlocks_Metal:
                return "BuildingObjects_BuildingBlocks_Metal";
            case ObjectCategoryId::BuildingObjects_BuildingBlocks_Stone:
                return "BuildingObjects_BuildingBlocks_Stone";
            case ObjectCategoryId::BuildingObjects_BuildingBlocks_Wood:
                return "BuildingObjects_BuildingBlocks_Wood";
            case ObjectCategoryId::BuildingObjects_Buildings_Animals:
                return "BuildingObjects_Buildings_Animals";
            case ObjectCategoryId::BuildingObjects_Buildings_Other:
                return "BuildingObjects_Buildings_Other";
            case ObjectCategoryId::Clothes_Face:
                return "Clothes_Face";
            case ObjectCategoryId::Clothes_Feet:
                return "Clothes_Feet";
            case ObjectCategoryId::Clothes_Head:
                return "Clothes_Head";
            case ObjectCategoryId::Clothes_Jewelry:
                return "Clothes_Jewelry";
            case ObjectCategoryId::Clothes_Legs:
                return "Clothes_Legs";
            case ObjectCategoryId::Clothes_Torso:
                return "Clothes_Torso";
            case ObjectCategoryId::Clothes_Face_Other:
                return "Clothes_Face_Other";
            case ObjectCategoryId::Clothes_Face_Sight:
                return "Clothes_Face_Sight";
            case ObjectCategoryId::Clothes_Feet_Sub2None:
                return "Clothes_Feet_Sub2None";
            case ObjectCategoryId::Clothes_Hands_Sub2None:
                return "Clothes_Hands_Sub2None";
            case ObjectCategoryId::Clothes_Head_Appearance:
                return "Clothes_Head_Appearance";
            case ObjectCategoryId::Clothes_Head_Protection:
                return "Clothes_Head_Protection";
            case ObjectCategoryId::Clothes_Head_Warmth:
                return "Clothes_Head_Warmth";
            case ObjectCategoryId::Clothes_Jewelry_Sub2None:
                return "Clothes_Jewelry_Sub2None";
            case ObjectCategoryId::Clothes_Legs_Appearance:
                return "Clothes_Legs_Appearance";
            case ObjectCategoryId::Clothes_Legs_Other:
                return "Clothes_Legs_Other";
            case ObjectCategoryId::Clothes_Legs_Warmth:
                return "Clothes_Legs_Warmth";
            case ObjectCategoryId::Clothes_Torso_Appearance:
                return "Clothes_Torso_Appearance";
            case ObjectCategoryId::Clothes_Torso_Armor:
                return "Clothes_Torso_Armor";
            case ObjectCategoryId::Clothes_Torso_Other:
                return "Clothes_Torso_Other";
            case ObjectCategoryId::Clothes_Torso_Warmth:
                return "Clothes_Torso_Warmth";
            case ObjectCategoryId::Container_Bag:
                return "Container_Bag";
            case ObjectCategoryId::Container_Flat:
                return "Container_Flat";
            case ObjectCategoryId::Container_Lid:
                return "Container_Lid";
            case ObjectCategoryId::Container_Lockable:
                return "Container_Lockable";
            case ObjectCategoryId::Container_Nolid:
                return "Container_Nolid";
            case ObjectCategoryId::Container_Other:
                return "Container_Other";
            case ObjectCategoryId::Container_Bag_Cloth:
                return "Container_Bag_Cloth";
            case ObjectCategoryId::Container_Bag_Paper:
                return "Container_Bag_Paper";
            case ObjectCategoryId::Container_Bag_Synthetic:
                return "Container_Bag_Synthetic";
            case ObjectCategoryId::Container_Flat_Food:
                return "Container_Flat_Food";
            case ObjectCategoryId::Container_Flat_Other:
                return "Container_Flat_Other";
            case ObjectCategoryId::Container_Lid_Glass:
                return "Container_Lid_Glass";
            case ObjectCategoryId::Container_Lid_Metal:
                return "Container_Lid_Metal";
            case ObjectCategoryId::Container_Lid_Plastic:
                return "Container_Lid_Plastic";
            case ObjectCategoryId::Container_Lid_Wood:
                return "Container_Lid_Wood";
            case ObjectCategoryId::Container_Lockable_Metal:
                return "Container_Lockable_Metal";
            case ObjectCategoryId::Container_Lockable_Wood:
                return "Container_Lockable_Wood";
            case ObjectCategoryId::Container_Nolid_Glass:
                return "Container_Nolid_Glass";
            case ObjectCategoryId::Container_Nolid_Metal:
                return "Container_Nolid_Metal";
            case ObjectCategoryId::Container_Nolid_Plastic:
                return "Container_Nolid_Plastic";
            case ObjectCategoryId::Container_Nolid_Wood:
                return "Container_Nolid_Wood";
            case ObjectCategoryId::Container_Other_Money:
                return "Container_Other_Money";
            case ObjectCategoryId::Electronics_Medium:
                return "Electronics_Medium";
            case ObjectCategoryId::Electronics_Small:
                return "Electronics_Small";
            case ObjectCategoryId::Electronics_Tiny:
                return "Electronics_Tiny";
            case ObjectCategoryId::Electronics_Medium_Sub2None:
                return "Electronics_Medium_Sub2None";
            case ObjectCategoryId::Electronics_Small_Sub2None:
                return "Electronics_Small_Sub2None";
            case ObjectCategoryId::Electronics_Tiny_Sub2None:
                return "Electronics_Tiny_Sub2None";
            case ObjectCategoryId::Entertainment_Ball:
                return "Entertainment_Ball";
            case ObjectCategoryId::Entertainment_Electric:
                return "Entertainment_Electric";
            case ObjectCategoryId::Entertainment_Metal:
                return "Entertainment_Metal";
            case ObjectCategoryId::Entertainment_Other:
                return "Entertainment_Other";
            case ObjectCategoryId::Entertainment_Plastic:
                return "Entertainment_Plastic";
            case ObjectCategoryId::Entertainment_Rubber:
                return "Entertainment_Rubber";
            case ObjectCategoryId::Entertainment_Sports:
                return "Entertainment_Sports";
            case ObjectCategoryId::Entertainment_Wood:
                return "Entertainment_Wood";
            case ObjectCategoryId::Entertainment_Ball_Bouncy:
                return "Entertainment_Ball_Bouncy";
            case ObjectCategoryId::Entertainment_Ball_Heavy:
                return "Entertainment_Ball_Heavy";
            case ObjectCategoryId::Entertainment_Electric_Gaming:
                return "Entertainment_Electric_Gaming";
            case ObjectCategoryId::Entertainment_Electric_Other:
                return "Entertainment_Electric_Other";
            case ObjectCategoryId::Entertainment_Electric_Personal:
                return "Entertainment_Electric_Personal";
            case ObjectCategoryId::Entertainment_Electric_Viewing:
                return "Entertainment_Electric_Viewing";
            case ObjectCategoryId::Entertainment_Metal_Bigtoy:
                return "Entertainment_Metal_Bigtoy";
            case ObjectCategoryId::Entertainment_Metal_Toy:
                return "Entertainment_Metal_Toy";
            case ObjectCategoryId::Entertainment_Other_Game:
                return "Entertainment_Other_Game";
            case ObjectCategoryId::Entertainment_Other_Toy:
                return "Entertainment_Other_Toy";
            case ObjectCategoryId::Entertainment_Plastic_Game:
                return "Entertainment_Plastic_Game";
            case ObjectCategoryId::Entertainment_Plastic_Sports:
                return "Entertainment_Plastic_Sports";
            case ObjectCategoryId::Entertainment_Plastic_Toy:
                return "Entertainment_Plastic_Toy";
            case ObjectCategoryId::Entertainment_Rubber_Sports:
                return "Entertainment_Rubber_Sports";
            case ObjectCategoryId::Entertainment_Rubber_Toy:
                return "Entertainment_Rubber_Toy";
            case ObjectCategoryId::Entertainment_Sports_Parts:
                return "Entertainment_Sports_Parts";
            case ObjectCategoryId::Entertainment_Wood_Huge:
                return "Entertainment_Wood_Huge";
            case ObjectCategoryId::Entertainment_Wood_Large:
                return "Entertainment_Wood_Large";
            case ObjectCategoryId::Entertainment_Wood_Medium:
                return "Entertainment_Wood_Medium";
            case ObjectCategoryId::Entertainment_Wood_Small:
                return "Entertainment_Wood_Small";
            case ObjectCategoryId::Environment_Damaging:
                return "Environment_Damaging";
            case ObjectCategoryId::Environment_Ice:
                return "Environment_Ice";
            case ObjectCategoryId::Environment_Rock:
                return "Environment_Rock";
            case ObjectCategoryId::Environment_Sky:
                return "Environment_Sky";
            case ObjectCategoryId::Environment_Vapor:
                return "Environment_Vapor";
            case ObjectCategoryId::Environment_Water:
                return "Environment_Water";
            case ObjectCategoryId::Environment_Damaging_Sub2None:
                return "Environment_Damaging_Sub2None";
            case ObjectCategoryId::Environment_Ice_Sub2None:
                return "Environment_Ice_Sub2None";
            case ObjectCategoryId::Environment_Rock_Sub2None:
                return "Environment_Rock_Sub2None";
            case ObjectCategoryId::Environment_Sky_Sub2None:
                return "Environment_Sky_Sub2None";
            case ObjectCategoryId::Environment_Vapor_Sub2None:
                return "Environment_Vapor_Sub2None";
            case ObjectCategoryId::Environment_Water_Sub2None:
                return "Environment_Water_Sub2None";
            case ObjectCategoryId::Fish_Carnivore:
                return "Fish_Carnivore";
            case ObjectCategoryId::Fish_Nonmoving:
                return "Fish_Nonmoving";
            case ObjectCategoryId::Fish_Predator:
                return "Fish_Predator";
            case ObjectCategoryId::Fish_Prey:
                return "Fish_Prey";
            case ObjectCategoryId::Fish_Slow:
                return "Fish_Slow";
            case ObjectCategoryId::Fish_Sub1None:
                return "Fish_Sub1None";
            case ObjectCategoryId::Fish_Carnivore_Sub2None:
                return "Fish_Carnivore_Sub2None";
            case ObjectCategoryId::Fish_Nonmoving_Sub2None:
                return "Fish_Nonmoving_Sub2None";
            case ObjectCategoryId::Fish_Predator_Sub2None:
                return "Fish_Predator_Sub2None";
            case ObjectCategoryId::Fish_Prey_Sub2None:
                return "Fish_Prey_Sub2None";
            case ObjectCategoryId::Fish_Slow_Sub2None:
                return "Fish_Slow_Sub2None";
            case ObjectCategoryId::Fish_Sub1None_Sub2None:
                return "Fish_Sub1None_Sub2None";
            case ObjectCategoryId::Food_Beverages:
                return "Food_Beverages";
            case ObjectCategoryId::Food_Condiment:
                return "Food_Condiment";
            case ObjectCategoryId::Food_Dairy:
                return "Food_Dairy";
            case ObjectCategoryId::Food_Fruitveg:
                return "Food_Fruitveg";
            case ObjectCategoryId::Food_Junk:
                return "Food_Junk";
            case ObjectCategoryId::Food_Meat:
                return "Food_Meat";
            case ObjectCategoryId::Food_NutsGrains:
                return "Food_NutsGrains";
            case ObjectCategoryId::Food_OtherMeal:
                return "Food_OtherMeal";
            case ObjectCategoryId::Food_Beverages_Caffeinated:
                return "Food_Beverages_Caffeinated";
            case ObjectCategoryId::Food_Beverages_Soothing:
                return "Food_Beverages_Soothing";
            case ObjectCategoryId::Food_Beverages_Sweet:
                return "Food_Beverages_Sweet";
            case ObjectCategoryId::Food_Condiment_Fatal:
                return "Food_Condiment_Fatal";
            case ObjectCategoryId::Food_Condiment_Flavor:
                return "Food_Condiment_Flavor";
            case ObjectCategoryId::Food_Condiment_Garnish:
                return "Food_Condiment_Garnish";
            case ObjectCategoryId::Food_Condiment_Ingredient:
                return "Food_Condiment_Ingredient";
            case ObjectCategoryId::Food_Condiment_MildlySpicy:
                return "Food_Condiment_MildlySpicy";
            case ObjectCategoryId::Food_Condiment_Recovery:
                return "Food_Condiment_Recovery";
            case ObjectCategoryId::Food_Condiment_Sideitem:
                return "Food_Condiment_Sideitem";
            case ObjectCategoryId::Food_Condiment_Spicy:
                return "Food_Condiment_Spicy";
            case ObjectCategoryId::Food_Condiment_Sweet:
                return "Food_Condiment_Sweet";
            case ObjectCategoryId::Food_Condiment_Viscous:
                return "Food_Condiment_Viscous";
            case ObjectCategoryId::Food_Dairy_Ingredient:
                return "Food_Dairy_Ingredient";
            case ObjectCategoryId::Food_Dairy_Liquid:
                return "Food_Dairy_Liquid";
            case ObjectCategoryId::Food_Dairy_Made:
                return "Food_Dairy_Made";
            case ObjectCategoryId::Food_Dairy_Raw:
                return "Food_Dairy_Raw";
            case ObjectCategoryId::Food_FruitVeg_Flavor:
                return "Food_FruitVeg_Flavor";
            case ObjectCategoryId::Food_FruitVeg_Leaf:
                return "Food_FruitVeg_Leaf";
            case ObjectCategoryId::Food_FruitVeg_Raw:
                return "Food_FruitVeg_Raw";
            case ObjectCategoryId::Food_FruitVeg_Sweet:
                return "Food_FruitVeg_Sweet";
            case ObjectCategoryId::Food_Junk_Breakfast:
                return "Food_Junk_Breakfast";
            case ObjectCategoryId::Food_Junk_Frozen:
                return "Food_Junk_Frozen";
            case ObjectCategoryId::Food_Junk_Salty:
                return "Food_Junk_Salty";
            case ObjectCategoryId::Food_Junk_Sweet:
                return "Food_Junk_Sweet";
            case ObjectCategoryId::Food_Meat_Cooked:
                return "Food_Meat_Cooked";
            case ObjectCategoryId::Food_Meat_Rawred:
                return "Food_Meat_Rawred";
            case ObjectCategoryId::Food_Meat_Rawsea:
                return "Food_Meat_Rawsea";
            case ObjectCategoryId::Food_Meat_Rawwhite:
                return "Food_Meat_Rawwhite";
            case ObjectCategoryId::Food_NutsGrains_Made:
                return "Food_NutsGrains_Made";
            case ObjectCategoryId::Food_NutsGrains_Many:
                return "Food_NutsGrains_Many";
            case ObjectCategoryId::Food_NutsGrains_Raw:
                return "Food_NutsGrains_Raw";
            case ObjectCategoryId::Food_OtherMeal_Other:
                return "Food_OtherMeal_Other";
            case ObjectCategoryId::Food_OtherMeal_Spicy:
                return "Food_OtherMeal_Spicy";
            case ObjectCategoryId::Furniture_Appliances:
                return "Furniture_Appliances";
            case ObjectCategoryId::Furniture_Container:
                return "Furniture_Container";
            case ObjectCategoryId::Furniture_Fabric:
                return "Furniture_Fabric";
            case ObjectCategoryId::Furniture_Metal:
                return "Furniture_Metal";
            case ObjectCategoryId::Furniture_Other:
                return "Furniture_Other";
            case ObjectCategoryId::Furniture_Wood:
                return "Furniture_Wood";
            case ObjectCategoryId::Furniture_Appliances_Cooking:
                return "Furniture_Appliances_Cooking";
            case ObjectCategoryId::Furniture_Appliances_Cooling:
                return "Furniture_Appliances_Cooling";
            case ObjectCategoryId::Furniture_Appliances_Heating:
                return "Furniture_Appliances_Heating";
            case ObjectCategoryId::Furniture_Appliances_Light:
                return "Furniture_Appliances_Light";
            case ObjectCategoryId::Furniture_Appliances_Other:
                return "Furniture_Appliances_Other";
            case ObjectCategoryId::Furniture_Appliances_Washing:
                return "Furniture_Appliances_Washing";
            case ObjectCategoryId::Furniture_Container_Metal:
                return "Furniture_Container_Metal";
            case ObjectCategoryId::Furniture_Container_Wood:
                return "Furniture_Container_Wood";
            case ObjectCategoryId::Furniture_Fabric_Sub2None:
                return "Furniture_Fabric_Sub2None";
            case ObjectCategoryId::Furniture_Metal_Sub2None:
                return "Furniture_Metal_Sub2None";
            case ObjectCategoryId::Furniture_Other_Sub2None:
                return "Furniture_Other_Sub2None";
            case ObjectCategoryId::Furniture_Wood_Sub2None:
                return "Furniture_Wood_Sub2None";
            case ObjectCategoryId::Gameplay_Ice:
                return "Gameplay_Ice";
            case ObjectCategoryId::Gameplay_Metal:
                return "Gameplay_Metal";
            case ObjectCategoryId::Gameplay_Stone:
                return "Gameplay_Stone";
            case ObjectCategoryId::Gameplay_Trigger:
                return "Gameplay_Trigger";
            case ObjectCategoryId::Gameplay_Wood:
                return "Gameplay_Wood";
            case ObjectCategoryId::Gameplay_Ice_Encasing:
                return "Gameplay_Ice_Encasing";
            case ObjectCategoryId::Gameplay_Ice_NonEncasing:
                return "Gameplay_Ice_NonEncasing";
            case ObjectCategoryId::Gameplay_Metal_Normal:
                return "Gameplay_Metal_Normal";
            case ObjectCategoryId::Gameplay_Stone_LowIntegrity:
                return "Gameplay_Stone_LowIntegrity";
            case ObjectCategoryId::Gameplay_Stone_Normal:
                return "Gameplay_Stone_Normal";
            case ObjectCategoryId::Gameplay_Trigger_Button:
                return "Gameplay_Trigger_Button";
            case ObjectCategoryId::Gameplay_Trigger_Other:
                return "Gameplay_Trigger_Other";
            case ObjectCategoryId::Gameplay_Trigger_Switch:
                return "Gameplay_Trigger_Switch";
            case ObjectCategoryId::Gameplay_Wood_LowIntegrity:
                return "Gameplay_Wood_LowIntegrity";
            case ObjectCategoryId::Gameplay_Wood_Normal:
                return "Gameplay_Wood_Normal";
            case ObjectCategoryId::Insect_Air:
                return "Insect_Air";
            case ObjectCategoryId::Insect_Ground:
                return "Insect_Ground";
            case ObjectCategoryId::Insect_Water:
                return "Insect_Water";
            case ObjectCategoryId::Insect_Air_AttractedTolight:
                return "Insect_Air_AttractedTolight";
            case ObjectCategoryId::Insect_Air_LeafEater:
                return "Insect_Air_LeafEater";
            case ObjectCategoryId::Insect_Air_Stingers:
                return "Insect_Air_Stingers";
            case ObjectCategoryId::Insect_Ground_Aggressive:
                return "Insect_Ground_Aggressive";
            case ObjectCategoryId::Insect_Ground_Gooey:
                return "Insect_Ground_Gooey";
            case ObjectCategoryId::Insect_Ground_Harmless:
                return "Insect_Ground_Harmless";
            case ObjectCategoryId::Insect_Ground_LeafEater:
                return "Insect_Ground_LeafEater";
            case ObjectCategoryId::Insect_Ground_Nonmoving:
                return "Insect_Ground_Nonmoving";
            case ObjectCategoryId::Insect_Ground_Parasite:
                return "Insect_Ground_Parasite";
            case ObjectCategoryId::Insect_Water_Harmless:
                return "Insect_Water_Harmless";
            case ObjectCategoryId::Insect_Water_Nonmoving:
                return "Insect_Water_Nonmoving";
            case ObjectCategoryId::Insect_Water_Pincers:
                return "Insect_Water_Pincers";
            case ObjectCategoryId::Mammal_Huge:
                return "Mammal_Huge";
            case ObjectCategoryId::Mammal_Large:
                return "Mammal_Large";
            case ObjectCategoryId::Mammal_Medium:
                return "Mammal_Medium";
            case ObjectCategoryId::Mammal_Small:
                return "Mammal_Small";
            case ObjectCategoryId::Mammal_Tiny:
                return "Mammal_Tiny";
            case ObjectCategoryId::Mammal_Huge_Bear:
                return "Mammal_Huge_Bear";
            case ObjectCategoryId::Mammal_Huge_Herbivore:
                return "Mammal_Huge_Herbivore";
            case ObjectCategoryId::Mammal_Huge_Hooved:
                return "Mammal_Huge_Hooved";
            case ObjectCategoryId::Mammal_Huge_Other:
                return "Mammal_Huge_Other";
            case ObjectCategoryId::Mammal_Huge_Water:
                return "Mammal_Huge_Water";
            case ObjectCategoryId::Mammal_Large_Feline:
                return "Mammal_Large_Feline";
            case ObjectCategoryId::Mammal_Large_Hooved:
                return "Mammal_Large_Hooved";
            case ObjectCategoryId::Mammal_Large_Other:
                return "Mammal_Large_Other";
            case ObjectCategoryId::Mammal_Large_Water:
                return "Mammal_Large_Water";
            case ObjectCategoryId::Mammal_Medium_Dog:
                return "Mammal_Medium_Dog";
            case ObjectCategoryId::Mammal_Medium_Hooved:
                return "Mammal_Medium_Hooved";
            case ObjectCategoryId::Mammal_Medium_Other:
                return "Mammal_Medium_Other";
            case ObjectCategoryId::Mammal_Small_Critter:
                return "Mammal_Small_Critter";
            case ObjectCategoryId::Mammal_Small_Dog:
                return "Mammal_Small_Dog";
            case ObjectCategoryId::Mammal_Small_Hooved:
                return "Mammal_Small_Hooved";
            case ObjectCategoryId::Mammal_Small_Other:
                return "Mammal_Small_Other";
            case ObjectCategoryId::Mammal_Small_Water:
                return "Mammal_Small_Water";
            case ObjectCategoryId::Mammal_Tiny_Critter:
                return "Mammal_Tiny_Critter";
            case ObjectCategoryId::Mammal_Tiny_Dog:
                return "Mammal_Tiny_Dog";
            case ObjectCategoryId::Mammal_Tiny_Other:
                return "Mammal_Tiny_Other";
            case ObjectCategoryId::Materials_Bone:
                return "Materials_Bone";
            case ObjectCategoryId::Materials_Bouncy:
                return "Materials_Bouncy";
            case ObjectCategoryId::Materials_Burning:
                return "Materials_Burning";
            case ObjectCategoryId::Materials_Dirt:
                return "Materials_Dirt";
            case ObjectCategoryId::Materials_Fabric:
                return "Materials_Fabric";
            case ObjectCategoryId::Materials_Flammable:
                return "Materials_Flammable";
            case ObjectCategoryId::Materials_Fragile:
                return "Materials_Fragile";
            case ObjectCategoryId::Materials_HighIntegrity:
                return "Materials_HighIntegrity";
            case ObjectCategoryId::Materials_Magnet:
                return "Materials_Magnet";
            case ObjectCategoryId::Materials_Metal:
                return "Materials_Metal";
            case ObjectCategoryId::Materials_Other:
                return "Materials_Other";
            case ObjectCategoryId::Materials_Plastic:
                return "Materials_Plastic";
            case ObjectCategoryId::Materials_Precious:
                return "Materials_Precious";
            case ObjectCategoryId::Materials_Rock:
                return "Materials_Rock";
            case ObjectCategoryId::Materials_Sticky:
                return "Materials_Sticky";
            case ObjectCategoryId::Materials_Bone_Sub2None:
                return "Materials_Bone_Sub2None";
            case ObjectCategoryId::Materials_Bouncy_Sub2None:
                return "Materials_Bouncy_Sub2None";
            case ObjectCategoryId::Materials_Burning_Sub2None:
                return "Materials_Burning_Sub2None";
            case ObjectCategoryId::Materials_Dirt_Sub2None:
                return "Materials_Dirt_Sub2None";
            case ObjectCategoryId::Materials_Fabric_Sub2None:
                return "Materials_Fabric_Sub2None";
            case ObjectCategoryId::Materials_Flammable_Highly:
                return "Materials_Flammable_Highly";
            case ObjectCategoryId::Materials_Flammable_Slippery:
                return "Materials_Flammable_Slippery";
            case ObjectCategoryId::Materials_Flammable_Sub2None:
                return "Materials_Flammable_Sub2None";
            case ObjectCategoryId::Materials_Fragile_Sub2None:
                return "Materials_Fragile_Sub2None";
            case ObjectCategoryId::Materials_HighIntegrity_Sub2None:
                return "Materials_HighIntegrity_Sub2None";
            case ObjectCategoryId::Materials_Magnet_Destroys:
                return "Materials_Magnet_Destroys";
            case ObjectCategoryId::Materials_Magnet_General:
                return "Materials_Magnet_General";
            case ObjectCategoryId::Materials_Metal_Sub2None:
                return "Materials_Metal_Sub2None";
            case ObjectCategoryId::Materials_Other_Sub2None:
                return "Materials_Other_Sub2None";
            case ObjectCategoryId::Materials_Plastic_Sub2None:
                return "Materials_Plastic_Sub2None";
            case ObjectCategoryId::Materials_Precious_Sub2None:
                return "Materials_Precious_Sub2None";
            case ObjectCategoryId::Materials_Rock_HighIntegrity:
                return "Materials_Rock_HighIntegrity";
            case ObjectCategoryId::Materials_Rock_LowIntegrity:
                return "Materials_Rock_LowIntegrity";
            case ObjectCategoryId::Materials_Rock_MediumIntegrity:
                return "Materials_Rock_MediumIntegrity";
            case ObjectCategoryId::Materials_Sticky_Sub2None:
                return "Materials_Sticky_Sub2None";
            case ObjectCategoryId::Misc_Fabric:
                return "Misc_Fabric";
            case ObjectCategoryId::Misc_Glass:
                return "Misc_Glass";
            case ObjectCategoryId::Misc_Metal:
                return "Misc_Metal";
            case ObjectCategoryId::Misc_Other:
                return "Misc_Other";
            case ObjectCategoryId::Misc_Paper:
                return "Misc_Paper";
            case ObjectCategoryId::Misc_Plastic:
                return "Misc_Plastic";
            case ObjectCategoryId::Misc_Stone:
                return "Misc_Stone";
            case ObjectCategoryId::Misc_Wood:
                return "Misc_Wood";
            case ObjectCategoryId::Misc_Fabric_Highintegrity:
                return "Misc_Fabric_Highintegrity";
            case ObjectCategoryId::Misc_Fabric_Lowintegrity:
                return "Misc_Fabric_Lowintegrity";
            case ObjectCategoryId::Misc_Fabric_Mediumintegrity:
                return "Misc_Fabric_Mediumintegrity";
            case ObjectCategoryId::Misc_Glass_Sub2None:
                return "Misc_Glass_Sub2None";
            case ObjectCategoryId::Misc_Metal_Large:
                return "Misc_Metal_Large";
            case ObjectCategoryId::Misc_Metal_Medium:
                return "Misc_Metal_Medium";
            case ObjectCategoryId::Misc_Metal_Small:
                return "Misc_Metal_Small";
            case ObjectCategoryId::Misc_Metal_Tiny:
                return "Misc_Metal_Tiny";
            case ObjectCategoryId::Misc_Other_Sub2None:
                return "Misc_Other_Sub2None";
            case ObjectCategoryId::Misc_Paper_Other:
                return "Misc_Paper_Other";
            case ObjectCategoryId::Misc_Paper_Thick:
                return "Misc_Paper_Thick";
            case ObjectCategoryId::Misc_Plastic_Medium:
                return "Misc_Plastic_Medium";
            case ObjectCategoryId::Misc_Plastic_Small:
                return "Misc_Plastic_Small";
            case ObjectCategoryId::Misc_Stone_Large:
                return "Misc_Stone_Large";
            case ObjectCategoryId::Misc_Stone_Medium:
                return "Misc_Stone_Medium";
            case ObjectCategoryId::Misc_Stone_Small:
                return "Misc_Stone_Small";
            case ObjectCategoryId::Misc_Stone_Tiny:
                return "Misc_Stone_Tiny";
            case ObjectCategoryId::Misc_Wood_Large:
                return "Misc_Wood_Large";
            case ObjectCategoryId::Misc_Wood_Medium:
                return "Misc_Wood_Medium";
            case ObjectCategoryId::Misc_Wood_Small:
                return "Misc_Wood_Small";
            case ObjectCategoryId::Misc_Wood_Tiny:
                return "Misc_Wood_Tiny";
            case ObjectCategoryId::Organic_Bone:
                return "Organic_Bone";
            case ObjectCategoryId::Organic_Parts:
                return "Organic_Parts";
            case ObjectCategoryId::Organic_Bone_Other:
                return "Organic_Bone_Other";
            case ObjectCategoryId::Organic_Bone_Sharp:
                return "Organic_Bone_Sharp";
            case ObjectCategoryId::Organic_Parts_Flesh:
                return "Organic_Parts_Flesh";
            case ObjectCategoryId::Organic_Parts_Gooey:
                return "Organic_Parts_Gooey";
            case ObjectCategoryId::Organic_Parts_Other:
                return "Organic_Parts_Other";
            case ObjectCategoryId::Plants_ConiferousTree:
                return "Plants_ConiferousTree";
            case ObjectCategoryId::Plants_DeciduousTree:
                return "Plants_DeciduousTree";
            case ObjectCategoryId::Plants_Flower:
                return "Plants_Flower";
            case ObjectCategoryId::Plants_OtherGreenery:
                return "Plants_OtherGreenery";
            case ObjectCategoryId::Plants_Seed:
                return "Plants_Seed";
            case ObjectCategoryId::Plants_Shrub:
                return "Plants_Shrub";
            case ObjectCategoryId::Plants_Wood:
                return "Plants_Wood";
            case ObjectCategoryId::Plants_ConiferousTree_Full:
                return "Plants_ConiferousTree_Full";
            case ObjectCategoryId::Plants_DeciduousTree_Full:
                return "Plants_DeciduousTree_Full";
            case ObjectCategoryId::Plants_DeciduousTree_Small:
                return "Plants_DeciduousTree_Small";
            case ObjectCategoryId::Plants_DeciduousTree_Thin:
                return "Plants_DeciduousTree_Thin";
            case ObjectCategoryId::Plants_Flower_Large:
                return "Plants_Flower_Large";
            case ObjectCategoryId::Plants_Flower_Presentable:
                return "Plants_Flower_Presentable";
            case ObjectCategoryId::Plants_Flower_Raw:
                return "Plants_Flower_Raw";
            case ObjectCategoryId::Plants_Flower_Romantic:
                return "Plants_Flower_Romantic";
            case ObjectCategoryId::Plants_OtherGreenery_Parts:
                return "Plants_OtherGreenery_Parts";
            case ObjectCategoryId::Plants_OtherGreenery_Ropelike:
                return "Plants_OtherGreenery_Ropelike";
            case ObjectCategoryId::Plants_Seed_PreBloom:
                return "Plants_Seed_PreBloom";
            case ObjectCategoryId::Plants_Seed_Young:
                return "Plants_Seed_Young";
            case ObjectCategoryId::Plants_Shrub_GroundCover:
                return "Plants_Shrub_GroundCover";
            case ObjectCategoryId::Plants_Shrub_Harmful:
                return "Plants_Shrub_Harmful";
            case ObjectCategoryId::Plants_Shrub_Presentable:
                return "Plants_Shrub_Presentable";
            case ObjectCategoryId::Plants_Shrub_Raw:
                return "Plants_Shrub_Raw";
            case ObjectCategoryId::Plants_Shrub_Water:
                return "Plants_Shrub_Water";
            case ObjectCategoryId::Plants_Shrub_Wild:
                return "Plants_Shrub_Wild";
            case ObjectCategoryId::Plants_Wood_Parts:
                return "Plants_Wood_Parts";
            case ObjectCategoryId::Plants_Wood_Useful:
                return "Plants_Wood_Useful";
            case ObjectCategoryId::Reptile_Dinosaur:
                return "Reptile_Dinosaur";
            case ObjectCategoryId::Reptile_Ground:
                return "Reptile_Ground";
            case ObjectCategoryId::Reptile_Water:
                return "Reptile_Water";
            case ObjectCategoryId::Reptile_Dinosaur_Other:
                return "Reptile_Dinosaur_Other";
            case ObjectCategoryId::Reptile_Dinosaur_Predator:
                return "Reptile_Dinosaur_Predator";
            case ObjectCategoryId::Reptile_Ground_Lizard:
                return "Reptile_Ground_Lizard";
            case ObjectCategoryId::Reptile_Ground_Snake:
                return "Reptile_Ground_Snake";
            case ObjectCategoryId::Reptile_Water_Other:
                return "Reptile_Water_Other";
            case ObjectCategoryId::Reptile_Water_Predator:
                return "Reptile_Water_Predator";
            case ObjectCategoryId::Tool_Bashing:
                return "Tool_Bashing";
            case ObjectCategoryId::Tool_Bouncing:
                return "Tool_Bouncing";
            case ObjectCategoryId::Tool_Chemical:
                return "Tool_Chemical";
            case ObjectCategoryId::Tool_Createsfire:
                return "Tool_Createsfire";
            case ObjectCategoryId::Tool_Cutting:
                return "Tool_Cutting";
            case ObjectCategoryId::Tool_Digging:
                return "Tool_Digging";
            case ObjectCategoryId::Tool_Drawing:
                return "Tool_Drawing";
            case ObjectCategoryId::Tool_Fans:
                return "Tool_Fans";
            case ObjectCategoryId::Tool_Grabbing:
                return "Tool_Grabbing";
            case ObjectCategoryId::Tool_Hygeine:
                return "Tool_Hygeine";
            case ObjectCategoryId::Tool_Kitchen:
                return "Tool_Kitchen";
            case ObjectCategoryId::Tool_Lighting:
                return "Tool_Lighting";
            case ObjectCategoryId::Tool_Medical:
                return "Tool_Medical";
            case ObjectCategoryId::Tool_OfficeSupplies:
                return "Tool_OfficeSupplies";
            case ObjectCategoryId::Tool_Poking:
                return "Tool_Poking";
            case ObjectCategoryId::Tool_Restraint:
                return "Tool_Restraint";
            case ObjectCategoryId::Tool_Rope:
                return "Tool_Rope";
            case ObjectCategoryId::Tool_Special:
                return "Tool_Special";
            case ObjectCategoryId::Tool_SprayWater:
                return "Tool_SprayWater";
            case ObjectCategoryId::Tool_UnderWater:
                return "Tool_UnderWater";
            case ObjectCategoryId::Tool_Bashing_Cleaning:
                return "Tool_Bashing_Cleaning";
            case ObjectCategoryId::Tool_Bashing_Other:
                return "Tool_Bashing_Other";
            case ObjectCategoryId::Tool_Bashing_Sports:
                return "Tool_Bashing_Sports";
            case ObjectCategoryId::Tool_Bouncing_NoEquip:
                return "Tool_Bouncing_NoEquip";
            case ObjectCategoryId::Tool_Bouncing_Other:
                return "Tool_Bouncing_Other";
            case ObjectCategoryId::Tool_Chemical_Nouse:
                return "Tool_Chemical_Nouse";
            case ObjectCategoryId::Tool_Chemical_Other:
                return "Tool_Chemical_Other";
            case ObjectCategoryId::Tool_CreatesFire_NoEquip:
                return "Tool_CreatesFire_NoEquip";
            case ObjectCategoryId::Tool_CreatesFire_Nouse:
                return "Tool_CreatesFire_Nouse";
            case ObjectCategoryId::Tool_CreatesFire_Other:
                return "Tool_CreatesFire_Other";
            case ObjectCategoryId::Tool_Cutting_CutsWood:
                return "Tool_Cutting_CutsWood";
            case ObjectCategoryId::Tool_Cutting_Other:
                return "Tool_Cutting_Other";
            case ObjectCategoryId::Tool_Digging_Sub2None:
                return "Tool_Digging_Sub2None";
            case ObjectCategoryId::Tool_Drawing_Liquid:
                return "Tool_Drawing_Liquid";
            case ObjectCategoryId::Tool_Drawing_Other:
                return "Tool_Drawing_Other";
            case ObjectCategoryId::Tool_Fans_NoEquip:
                return "Tool_Fans_NoEquip";
            case ObjectCategoryId::Tool_Fans_Other:
                return "Tool_Fans_Other";
            case ObjectCategoryId::Tool_Grabbing_Sub2None:
                return "Tool_Grabbing_Sub2None";
            case ObjectCategoryId::Tool_Hygeine_Fabric:
                return "Tool_Hygeine_Fabric";
            case ObjectCategoryId::Tool_Hygeine_Paper:
                return "Tool_Hygeine_Paper";
            case ObjectCategoryId::Tool_Hygeine_Plastic:
                return "Tool_Hygeine_Plastic";
            case ObjectCategoryId::Tool_Kitchen_Metal:
                return "Tool_Kitchen_Metal";
            case ObjectCategoryId::Tool_Kitchen_Other:
                return "Tool_Kitchen_Other";
            case ObjectCategoryId::Tool_Kitchen_Wood:
                return "Tool_Kitchen_Wood";
            case ObjectCategoryId::Tool_Lighting_Beam:
                return "Tool_Lighting_Beam";
            case ObjectCategoryId::Tool_Lighting_Circular:
                return "Tool_Lighting_Circular";
            case ObjectCategoryId::Tool_Medical_Sub2None:
                return "Tool_Medical_Sub2None";
            case ObjectCategoryId::Tool_Officesupplies_Glass:
                return "Tool_Officesupplies_Glass";
            case ObjectCategoryId::Tool_Officesupplies_Metal:
                return "Tool_Officesupplies_Metal";
            case ObjectCategoryId::Tool_Officesupplies_Paper:
                return "Tool_Officesupplies_Paper";
            case ObjectCategoryId::Tool_Officesupplies_Plastic:
                return "Tool_Officesupplies_Plastic";
            case ObjectCategoryId::Tool_Officesupplies_Stone:
                return "Tool_Officesupplies_Stone";
            case ObjectCategoryId::Tool_Officesupplies_Wood:
                return "Tool_Officesupplies_Wood";
            case ObjectCategoryId::Tool_Poking_Sub2None:
                return "Tool_Poking_Sub2None";
            case ObjectCategoryId::Tool_Restraint_Other:
                return "Tool_Restraint_Other";
            case ObjectCategoryId::Tool_Restraint_Piercing:
                return "Tool_Restraint_Piercing";
            case ObjectCategoryId::Tool_Restraint_Sticky:
                return "Tool_Restraint_Sticky";
            case ObjectCategoryId::Tool_Rope_Charged:
                return "Tool_Rope_Charged";
            case ObjectCategoryId::Tool_Rope_Grapple:
                return "Tool_Rope_Grapple";
            case ObjectCategoryId::Tool_Rope_Other:
                return "Tool_Rope_Other";
            case ObjectCategoryId::Tool_Special_Buoyant:
                return "Tool_Special_Buoyant";
            case ObjectCategoryId::Tool_Special_Cutting:
                return "Tool_Special_Cutting";
            case ObjectCategoryId::Tool_Special_Equip:
                return "Tool_Special_Equip";
            case ObjectCategoryId::Tool_Special_NoEquip:
                return "Tool_Special_NoEquip";
            case ObjectCategoryId::Tool_Special_Precious:
                return "Tool_Special_Precious";
            case ObjectCategoryId::Tool_Spraywater_Sub2None:
                return "Tool_Spraywater_Sub2None";
            case ObjectCategoryId::Tool_Underwater_Sub2None:
                return "Tool_Underwater_Sub2None";
            case ObjectCategoryId::Vehicle_Air:
                return "Vehicle_Air";
            case ObjectCategoryId::Vehicle_Ground:
                return "Vehicle_Ground";
            case ObjectCategoryId::Vehicle_Snow:
                return "Vehicle_Snow";
            case ObjectCategoryId::Vehicle_Space:
                return "Vehicle_Space";
            case ObjectCategoryId::Vehicle_Water:
                return "Vehicle_Water";
            case ObjectCategoryId::Vehicle_Air_Burst:
                return "Vehicle_Air_Burst";
            case ObjectCategoryId::Vehicle_Air_Float:
                return "Vehicle_Air_Float";
            case ObjectCategoryId::Vehicle_Air_Large:
                return "Vehicle_Air_Large";
            case ObjectCategoryId::Vehicle_Air_Propeller:
                return "Vehicle_Air_Propeller";
            case ObjectCategoryId::Vehicle_Ground_Large:
                return "Vehicle_Ground_Large";
            case ObjectCategoryId::Vehicle_Ground_Medium:
                return "Vehicle_Ground_Medium";
            case ObjectCategoryId::Vehicle_Ground_Small:
                return "Vehicle_Ground_Small";
            case ObjectCategoryId::Vehicle_Ground_Tiny:
                return "Vehicle_Ground_Tiny";
            case ObjectCategoryId::Vehicle_Snow_Medium:
                return "Vehicle_Snow_Medium";
            case ObjectCategoryId::Vehicle_Snow_Small:
                return "Vehicle_Snow_Small";
            case ObjectCategoryId::Vehicle_Snow_Tiny:
                return "Vehicle_Snow_Tiny";
            case ObjectCategoryId::Vehicle_Space_Large:
                return "Vehicle_Space_Large";
            case ObjectCategoryId::Vehicle_Space_Medium:
                return "Vehicle_Space_Medium";
            case ObjectCategoryId::Vehicle_Water_Medium:
                return "Vehicle_Water_Medium";
            case ObjectCategoryId::Vehicle_Water_Small:
                return "Vehicle_Water_Small";
            case ObjectCategoryId::Weapon_Artillery:
                return "Weapon_Artillery";
            case ObjectCategoryId::Weapon_Bomb:
                return "Weapon_Bomb";
            case ObjectCategoryId::Weapon_Gun:
                return "Weapon_Gun";
            case ObjectCategoryId::Weapon_Melee:
                return "Weapon_Melee";
            case ObjectCategoryId::Weapon_Parts:
                return "Weapon_Parts";
            case ObjectCategoryId::Weapon_Projectile:
                return "Weapon_Projectile";
            case ObjectCategoryId::Weapon_Trap:
                return "Weapon_Trap";
            case ObjectCategoryId::Weapon_Artillery_Sub2None:
                return "Weapon_Artillery_Sub2None";
            case ObjectCategoryId::Weapon_Bomb_Sub2None:
                return "Weapon_Bomb_Sub2None";
            case ObjectCategoryId::Weapon_Gun_LargeSpread:
                return "Weapon_Gun_LargeSpread";
            case ObjectCategoryId::Weapon_Gun_LowDamage:
                return "Weapon_Gun_LowDamage";
            case ObjectCategoryId::Weapon_Gun_Normal:
                return "Weapon_Gun_Normal";
            case ObjectCategoryId::Weapon_Gun_Other:
                return "Weapon_Gun_Other";
            case ObjectCategoryId::Weapon_Melee_Bashing:
                return "Weapon_Melee_Bashing";
            case ObjectCategoryId::Weapon_Melee_Cutting:
                return "Weapon_Melee_Cutting";
            case ObjectCategoryId::Weapon_Melee_Other:
                return "Weapon_Melee_Other";
            case ObjectCategoryId::Weapon_Melee_Poking:
                return "Weapon_Melee_Poking";
            case ObjectCategoryId::Weapon_Melee_Spray:
                return "Weapon_Melee_Spray";
            case ObjectCategoryId::Weapon_Parts_Explosive:
                return "Weapon_Parts_Explosive";
            case ObjectCategoryId::Weapon_Parts_Other:
                return "Weapon_Parts_Other";
            case ObjectCategoryId::Weapon_Projectile_Sub2None:
                return "Weapon_Projectile_Sub2None";
            case ObjectCategoryId::Weapon_Trap_Sub2None:
                return "Weapon_Trap_Sub2None";
            case ObjectCategoryId::Weapon_Projectile_Magic:
                return "Weapon_Projectile_Magic";
            case ObjectCategoryId::Gameplay_Gameonly:
                return "Gameplay_Gameonly";
            case ObjectCategoryId::Gameplay_Gameonly_Starite:
                return "Gameplay_Gameonly_Starite";
            case ObjectCategoryId::Human_Player:
                return "Human_Player";
            case ObjectCategoryId::Human_Player_Maxwell:
                return "Human_Player_Maxwell";
            case ObjectCategoryId::Environment_Sky_Stormmacro:
                return "Environment_Sky_Stormmacro";
            case ObjectCategoryId::Plants_DeciduousTree_FruitTreeMacro:
                return "Plants_DeciduousTree_FruitTreeMacro";
            case ObjectCategoryId::Plants_OtherGreenery_RopeMacro:
                return "Plants_OtherGreenery_RopeMacro";
            case ObjectCategoryId::Plants_Shrub_FruitMacro:
                return "Plants_Shrub_FruitMacro";
            case ObjectCategoryId::Vehicle_Parts:
                return "Vehicle_Parts";
            case ObjectCategoryId::Vehicle_Parts_Sub2None:
                return "Vehicle_Parts_Sub2None";
            case ObjectCategoryId::Human_Developer:
                return "Human_Developer";
            case ObjectCategoryId::Human_Developer_Secretz:
                return "Human_Developer_Secretz";
            case ObjectCategoryId::Gameplay_Trigger_LowIntegrity:
                return "Gameplay_Trigger_LowIntegrity";
            case ObjectCategoryId::Electronics_Large:
                return "Electronics_Large";
            case ObjectCategoryId::Electronics_Large_Sub2None:
                return "Electronics_Large_Sub2None";
            case ObjectCategoryId::BuildingObjects_Ancient:
                return "BuildingObjects_Ancient";
            case ObjectCategoryId::BuildingObjects_Ancient_Stone:
                return "BuildingObjects_Ancient_Stone";
            case ObjectCategoryId::Vehicle_Snow_Large:
                return "Vehicle_Snow_Large";
            case ObjectCategoryId::Mammal_Medium_Feline:
                return "Mammal_Medium_Feline";
            case ObjectCategoryId::Tool_Hygeine_Other:
                return "Tool_Hygeine_Other";
            case ObjectCategoryId::Insect_Air_Harmless:
                return "Insect_Air_Harmless";
            case ObjectCategoryId::Audio_Amplifying_Metal:
                return "Audio_Amplifying_Metal";
            case ObjectCategoryId::Audio_Amplifying_Other:
                return "Audio_Amplifying_Other";
            case ObjectCategoryId::Audio_Instrument_Other:
                return "Audio_Instrument_Other";
            case ObjectCategoryId::Plants_OtherGreenery_FruitMacro:
                return "Plants_OtherGreenery_FruitMacro";
            case ObjectCategoryId::Plants_Shrub_VeggieMacro:
                return "Plants_Shrub_VeggieMacro";
            case ObjectCategoryId::Easteregg:
                return "Easteregg";
            case ObjectCategoryId::Easteregg_Secretz:
                return "Easteregg_Secretz";
            case ObjectCategoryId::Easteregg_Secretz_Other:
                return "Easteregg_Secretz_Other";
            case ObjectCategoryId::Environment_Sky_Zodiac:
                return "Environment_Sky_Zodiac";
            case ObjectCategoryId::Clothes_Head_Hair:
                return "Clothes_Head_Hair";
            case ObjectCategoryId::Mammal_Small_Cat:
                return "Mammal_Small_Cat";
            case ObjectCategoryId::Big_Entertainment_Sports:
                return "Big_Entertainment_Sports";
            case ObjectCategoryId::Tool_Special_Wings:
                return "Tool_Special_Wings";
            case ObjectCategoryId::Clothes_Face_Hair:
                return "Clothes_Face_Hair";
            case ObjectCategoryId::Weapon_Magic:
                return "Weapon_Magic";
            case ObjectCategoryId::Weapon_Magic_Hand:
                return "Weapon_Magic_Hand";
            case ObjectCategoryId::Human_Developer_Devfriend:
                return "Human_Developer_Devfriend";
            case ObjectCategoryId::Creature_Friendly:
                return "Creature_Friendly";
            case ObjectCategoryId::Creature_Robot:
                return "Creature_Robot";
            case ObjectCategoryId::Creature_Scary:
                return "Creature_Scary";
            case ObjectCategoryId::Creature_Friendly_Animal:
                return "Creature_Friendly_Animal";
            case ObjectCategoryId::Creature_Friendly_Gods:
                return "Creature_Friendly_Gods";
            case ObjectCategoryId::Creature_Friendly_Human:
                return "Creature_Friendly_Human";
            case ObjectCategoryId::Creature_Friendly_Hybrid:
                return "Creature_Friendly_Hybrid";
            case ObjectCategoryId::Creature_Friendly_Other:
                return "Creature_Friendly_Other";
            case ObjectCategoryId::Big_Places_Government:
                return "Big_Places_Government";
            case ObjectCategoryId::Big_Places_Mechanic:
                return "Big_Places_Mechanic";
            case ObjectCategoryId::Big_Places_Military:
                return "Big_Places_Military";
            case ObjectCategoryId::Big_Places_Morbid:
                return "Big_Places_Morbid";
            case ObjectCategoryId::Creature_Robot_Normal:
                return "Creature_Robot_Normal";
            case ObjectCategoryId::Big_Places_Museum:
                return "Big_Places_Museum";
            case ObjectCategoryId::Creature_Scary_Beast:
                return "Creature_Scary_Beast";
            case ObjectCategoryId::Creature_Scary_Demon:
                return "Creature_Scary_Demon";
            case ObjectCategoryId::Creature_Scary_Evil:
                return "Creature_Scary_Evil";
            case ObjectCategoryId::Creature_Scary_Gods:
                return "Creature_Scary_Gods";
            case ObjectCategoryId::Creature_Scary_Neutral:
                return "Creature_Scary_Neutral";
            case ObjectCategoryId::Creature_Scary_Undead:
                return "Creature_Scary_Undead";
            case ObjectCategoryId::Big_Places_Religion:
                return "Big_Places_Religion";
            case ObjectCategoryId::Big_Places_Science:
                return "Big_Places_Science";
            case ObjectCategoryId::Big_Places_Shopping:
                return "Big_Places_Shopping";
            case ObjectCategoryId::Big_Water_Structures:
                return "Big_Water_Structures";
            case ObjectCategoryId::Human_Athletes:
                return "Human_Athletes";
            case ObjectCategoryId::Human_Criminals:
                return "Human_Criminals";
            case ObjectCategoryId::Human_Entertainment:
                return "Human_Entertainment";
            case ObjectCategoryId::Human_Fighters:
                return "Human_Fighters";
            case ObjectCategoryId::Human_Legal:
                return "Human_Legal";
            case ObjectCategoryId::Human_Other:
                return "Human_Other";
            case ObjectCategoryId::Human_Ruler:
                return "Human_Ruler";
            case ObjectCategoryId::Human_Science:
                return "Human_Science";
            case ObjectCategoryId::Human_Athletes_Competitive:
                return "Human_Athletes_Competitive";
            case ObjectCategoryId::Human_Athletes_Fighter:
                return "Human_Athletes_Fighter";
            case ObjectCategoryId::Human_Athletes_Other:
                return "Human_Athletes_Other";
            case ObjectCategoryId::Human_Athletes_Support:
                return "Human_Athletes_Support";
            case ObjectCategoryId::Human_Criminals_Crazy:
                return "Human_Criminals_Crazy";
            case ObjectCategoryId::Human_Criminals_Crime:
                return "Human_Criminals_Crime";
            case ObjectCategoryId::Human_Criminals_Other:
                return "Human_Criminals_Other";
            case ObjectCategoryId::Human_Criminals_Super:
                return "Human_Criminals_Super";
            case ObjectCategoryId::Human_Entertainment_Actor:
                return "Human_Entertainment_Actor";
            case ObjectCategoryId::Human_Entertainment_Artist:
                return "Human_Entertainment_Artist";
            case ObjectCategoryId::Human_Entertainment_Dancer:
                return "Human_Entertainment_Dancer";
            case ObjectCategoryId::Human_Entertainment_Musician:
                return "Human_Entertainment_Musician";
            case ObjectCategoryId::Human_Entertainment_Other:
                return "Human_Entertainment_Other";
            case ObjectCategoryId::Human_Entertainment_Performer:
                return "Human_Entertainment_Performer";
            case ObjectCategoryId::Human_Entertainment_Singer:
                return "Human_Entertainment_Singer";
            case ObjectCategoryId::Human_Fighters_Ancient:
                return "Human_Fighters_Ancient";
            case ObjectCategoryId::Human_Fighters_Medieval:
                return "Human_Fighters_Medieval";
            case ObjectCategoryId::Human_Fighters_Military:
                return "Human_Fighters_Military";
            case ObjectCategoryId::Human_Fighters_Super:
                return "Human_Fighters_Super";
            case ObjectCategoryId::Human_Legal_JusticeSystem:
                return "Human_Legal_JusticeSystem";
            case ObjectCategoryId::Human_Legal_Police:
                return "Human_Legal_Police";
            case ObjectCategoryId::Human_Other_Animals:
                return "Human_Other_Animals";
            case ObjectCategoryId::Human_Other_Basic:
                return "Human_Other_Basic";
            case ObjectCategoryId::Human_Other_Business:
                return "Human_Other_Business";
            case ObjectCategoryId::Human_Other_Children:
                return "Human_Other_Children";
            case ObjectCategoryId::Human_Other_Cleaning:
                return "Human_Other_Cleaning";
            case ObjectCategoryId::Human_Other_Craftsman:
                return "Human_Other_Craftsman";
            case ObjectCategoryId::Human_Other_Education:
                return "Human_Other_Education";
            case ObjectCategoryId::Human_Other_Farming:
                return "Human_Other_Farming";
            case ObjectCategoryId::Human_Other_Food:
                return "Human_Other_Food";
            case ObjectCategoryId::Human_Other_Government:
                return "Human_Other_Government";
            case ObjectCategoryId::Human_Other_Morbid:
                return "Human_Other_Morbid";
            case ObjectCategoryId::Human_Other_Other:
                return "Human_Other_Other";
            case ObjectCategoryId::Human_Other_PickyEaters:
                return "Human_Other_PickyEaters";
            case ObjectCategoryId::Human_Other_Religion:
                return "Human_Other_Religion";
            case ObjectCategoryId::Human_Other_VehicleRelated:
                return "Human_Other_VehicleRelated";
            case ObjectCategoryId::Human_Other_Wedding:
                return "Human_Other_Wedding";
            case ObjectCategoryId::Human_Ruler_Elected:
                return "Human_Ruler_Elected";
            case ObjectCategoryId::Human_Ruler_Military:
                return "Human_Ruler_Military";
            case ObjectCategoryId::Human_Ruler_Royal:
                return "Human_Ruler_Royal";
            case ObjectCategoryId::Human_Science_Biologist:
                return "Human_Science_Biologist";
            case ObjectCategoryId::Human_Science_Medical:
                return "Human_Science_Medical";
            case ObjectCategoryId::Human_Science_Other:
                return "Human_Science_Other";
            case ObjectCategoryId::Human_Science_Space:
                return "Human_Science_Space";
            case ObjectCategoryId::Misc_Metal_Signs:
                return "Misc_Metal_Signs";
            case ObjectCategoryId::Weapon_Scifi:
                return "Weapon_Scifi";
            case ObjectCategoryId::Weapon_Scifi_Gun:
                return "Weapon_Scifi_Gun";
            case ObjectCategoryId::Clothes_Hands:
                return "Clothes_Hands";
            case ObjectCategoryId::BuildingObjects_Shapes:
                return "BuildingObjects_Shapes";
            case ObjectCategoryId::BuildingObjects_Shapes_Sub2None:
                return "BuildingObjects_Shapes_Sub2None";
            case ObjectCategoryId::BuildingObjects_Letters:
                return "BuildingObjects_Letters";
            case ObjectCategoryId::BuildingObjects_Letters_Letters:
                return "BuildingObjects_Letters_Letters";
            case ObjectCategoryId::BuildingObjects_Letters_Numbers:
                return "BuildingObjects_Letters_Numbers";
            case ObjectCategoryId::BuildingObjects_Letters_Punctuation:
                return "BuildingObjects_Letters_Punctuation";
            case ObjectCategoryId::Human_Player_Brothers:
                return "Human_Player_Brothers";
            default:
                return "";
        }
    }

    enum class ObjectSubCategoryId : u16 {
    };

    enum class AdjectiveCategoryId : u16 {
    };

    enum class AdjectiveSubCategoryId : u16 {
    };

    enum class Animation : u8 {
        Attack = 0,
        Celebrate = 1,
        Cheer = 2,
        Climb = 3,
        ClimbLadder = 4,
        Dance = 5,
        Death = 6,
        Dig = 7,
        Drive = 8,
        Eat = 9,
        Fiddle = 10,
        Follow = 11,
        GetUp = 12,
        Hurt = 13,
        Idle = 14,
        Idle2 = 15,
        Jump = 16,
        JumpIdle = 17,
        Kick = 18,
        Land = 19,
        LayDown = 20,
        Melee = 21,
        PickUp = 22,
        Ride = 23,
        Run = 24,
        Scared = 25,
        ScaredRun = 26,
        Shoot = 27,
        Sleep = 28,
        StickyWalk = 29,
        Swim = 30,
        SwimIdle = 31,
        Throw = 32,
        Walk = 33,
        Fly = 34,
        FlyIdle = 35,
        Poke = 36,
        Special1 = 37,
        Special2 = 38,
        SwimExtendedIdle = 39,
        FlyExtendedIdle = 40,
        Sit = 41,
        ScaredFly = 42,
        ScaredSwim = 43,
        Count
    };

    inline std::string FormatAnimation(const Animation anim) {
        switch(anim) {
            case Animation::Attack:
                return "Attack";
            case Animation::Celebrate:
                return "Celebrate";
            case Animation::Cheer:
                return "Cheer";
            case Animation::Climb:
                return "Climb";
            case Animation::ClimbLadder:
                return "ClimbLadder";
            case Animation::Dance:
                return "Dance";
            case Animation::Death:
                return "Death";
            case Animation::Dig:
                return "Dig";
            case Animation::Drive:
                return "Drive";
            case Animation::Eat:
                return "Eat";
            case Animation::Fiddle:
                return "Fiddle";
            case Animation::Follow:
                return "Follow";
            case Animation::GetUp:
                return "GetUp";
            case Animation::Hurt:
                return "Hurt";
            case Animation::Idle:
                return "Idle";
            case Animation::Idle2:
                return "Idle2";
            case Animation::Jump:
                return "Jump";
            case Animation::JumpIdle:
                return "JumpIdle";
            case Animation::Kick:
                return "Kick";
            case Animation::Land:
                return "Land";
            case Animation::LayDown:
                return "LayDown";
            case Animation::Melee:
                return "Melee";
            case Animation::PickUp:
                return "PickUp";
            case Animation::Ride:
                return "Ride";
            case Animation::Run:
                return "Run";
            case Animation::Scared: 
                return "Scared";
            case Animation::ScaredRun:
                return "ScaredRun";
            case Animation::Shoot:
                return "Shoot";
            case Animation::Sleep:
                return "Sleep";
            case Animation::StickyWalk:
                return "StickyWalk";
            case Animation::Swim:
                return "Swim";
            case Animation::SwimIdle:
                return "SwimIdle";
            case Animation::Throw:
                return "Throw";
            case Animation::Walk:
                return "Walk";
            case Animation::Fly:
                return "Fly";
            case Animation::FlyIdle:
                return "FlyIdle";
            case Animation::Poke:
                return "Poke";
            case Animation::Special1:
                return "Special1";
            case Animation::Special2:
                return "Special2";
            case Animation::SwimExtendedIdle:
                return "SwimExtendedIdle";
            case Animation::FlyExtendedIdle:
                return "FlyExtendedIdle";
            case Animation::Sit:
                return "Sit";
            case Animation::ScaredFly:
                return "ScaredFly";
            case Animation::ScaredSwim:
                return "ScaredSwim";
            default:
                return "";
        }
    }

    enum class SoundAttribute : u8 {
        None = 0,
        Alarming = 1,
        Entertaining = 2,
        Scary = 3,
        Soothing = 4
    };

    inline std::string FormatSoundAttribute(const SoundAttribute attr) {
        switch(attr) {
            case SoundAttribute::None:
                return "None";
            case SoundAttribute::Alarming:
                return "Alarming";
            case SoundAttribute::Entertaining:
                return "Entertaining";
            case SoundAttribute::Scary:
                return "Scary";
            case SoundAttribute::Soothing:
                return "Soothing";
            default:
                return "";
        }
    }

    enum class BodyPart : u8 {
        None = 0,
        Body = 1,
        Neck = 2,
        Head = 3,
        Arm = 4,
        Leg = 5,
        Tail = 6,
        Wing = 7,

        Everything = 0xFF
    };
    
    inline std::string FormatBodyPart(const BodyPart part) {
        switch(part) {
            case BodyPart::None:
                return "None";
            case BodyPart::Body:
                return "Body";
            case BodyPart::Neck:
                return "Neck";
            case BodyPart::Head:
                return "Head";
            case BodyPart::Arm:
                return "Arm";
            case BodyPart::Leg:
                return "Leg";
            case BodyPart::Tail:
                return "Tail";
            case BodyPart::Wing:
                return "Wing";
            case BodyPart::Everything:
                return "Everything";
            default:
                return "";
        }
    }

    enum class EmitterLabel : u8 {
        None = 0,
        Mouth = 1,
        Body = 2
    };

    inline std::string FormatEmitterLabel(const EmitterLabel label) {
        switch(label) {
            case EmitterLabel::None:
                return "None";
            case EmitterLabel::Mouth:
                return "Mouth";
            case EmitterLabel::Body:
                return "Body";
            default:
                return "";
        }
    }

    enum class EquipLocation : u8 {
        EquipperPickup = 1,
        EquipperHead = 2,
        EquipperTorso = 3,
        EquipperArmLeft = 4,
        EquipperArmRight = 5,
        EquipperHandLeft = 6,
        EquipperHandRight = 7,
        EquipperLegLeft = 8,
        EquipperLegRight = 9,
        EquipperFootLeft = 10,
        EquipperFootRight = 11,
        EquipperBelt = 12,
        EquipperBack = 13,
        EquipperFace = 14,

        EquipmentMask = 0x80,

        EquipmentPickup = 0x81,
        EquipmentHead = 0x82,
        EquipmentTorso = 0x83,
        EquipmentArmLeft = 0x84,
        EquipmentArmRight = 0x85,
        EquipmentHandLeft = 0x86,
        EquipmentHandRight = 0x87,
        EquipmentLegLeft = 0x88,
        EquipmentLegRight = 0x89,
        EquipmentFootLeft = 0x8A,
        EquipmentFootRight = 0x8B,
        EquipmentBelt = 0x8C,
        EquipmentBack = 0x8D,
        EquipmentFace = 0x8E
    };

    inline std::string FormatEquipLocation(const EquipLocation location) {
        switch(location) {
            case EquipLocation::EquipperPickup:
                return "EquipperPickup";
            case EquipLocation::EquipperHead:
                return "EquipperHead";
            case EquipLocation::EquipperTorso:
                return "EquipperTorso";
            case EquipLocation::EquipperArmLeft:
                return "EquipperArmLeft";
            case EquipLocation::EquipperArmRight:
                return "EquipperArmRight";
            case EquipLocation::EquipperHandLeft:
                return "EquipperHandLeft";
            case EquipLocation::EquipperHandRight:
                return "EquipperHandRight";
            case EquipLocation::EquipperLegLeft:
                return "EquipperLegLeft";
            case EquipLocation::EquipperLegRight:
                return "EquipperLegRight";
            case EquipLocation::EquipperFootLeft:
                return "EquipperFootLeft";
            case EquipLocation::EquipperFootRight:
                return "EquipperFootRight";
            case EquipLocation::EquipperBelt:
                return "EquipperBelt";
            case EquipLocation::EquipperBack:
                return "EquipperBack";
            case EquipLocation::EquipperFace:
                return "EquipperFace";
            case EquipLocation::EquipmentPickup:
                return "EquipmentPickup";
            case EquipLocation::EquipmentHead:
                return "EquipmentHead";
            case EquipLocation::EquipmentTorso:
                return "EquipmentTorso";
            case EquipLocation::EquipmentArmLeft:
                return "EquipmentArmLeft";
            case EquipLocation::EquipmentArmRight:
                return "EquipmentArmRight";
            case EquipLocation::EquipmentHandLeft:
                return "EquipmentHandLeft";
            case EquipLocation::EquipmentHandRight:
                return "EquipmentHandRight";
            case EquipLocation::EquipmentLegLeft:
                return "EquipmentLegLeft";
            case EquipLocation::EquipmentLegRight:
                return "EquipmentLegRight";
            case EquipLocation::EquipmentFootLeft:
                return "EquipmentFootLeft";
            case EquipLocation::EquipmentFootRight:
                return "EquipmentFootRight";
            case EquipLocation::EquipmentBelt:
                return "EquipmentBelt";
            case EquipLocation::EquipmentBack:
                return "EquipmentBack";
            case EquipLocation::EquipmentFace:
                return "EquipmentFace";
            default:
                return "";
        }
    }

    enum class HotSpotType : u8 {
        HotSpotAttach = 0,
        HotSpotCenterOfGravity = 1,
        HotSpotSaddle = 2,
        HotSpotSaddleSnap = 3,
        HotSpotContainerOpening = 4,
        HotSpotEquip = 5,
        HotSpotWaypoint = 6,
        HotSpotSplit = 7,
        HotSpotLight = 8,
        HotSpotEmitter = 9,
        HotSpotFire = 10,
        JointFixed = 11,
        JointRevolute = 12,
        JointRotationalSpring = 13,
        HotSpotCombiner = 14,
        HotSpotPierce = 15,
        HotSpotSkyPin = 16,
        HotSpotDigger = 17
    };

    inline std::string FormatHotSpotType(const HotSpotType type) {
        switch(type) {
            case HotSpotType::HotSpotAttach:
                return "HotSpotAttach";
            case HotSpotType::HotSpotCenterOfGravity:
                return "HotSpotCenterOfGravity";
            case HotSpotType::HotSpotSaddle:
                return "HotSpotSaddle";
            case HotSpotType::HotSpotSaddleSnap:
                return "HotSpotSaddleSnap";
            case HotSpotType::HotSpotContainerOpening:
                return "HotSpotContainerOpening";
            case HotSpotType::HotSpotEquip:
                return "HotSpotEquip";
            case HotSpotType::HotSpotWaypoint:
                return "HotSpotWaypoint";
            case HotSpotType::HotSpotSplit:
                return "HotSpotSplit";
            case HotSpotType::HotSpotLight:
                return "HotSpotLight";
            case HotSpotType::HotSpotEmitter:
                return "HotSpotEmitter";
            case HotSpotType::HotSpotFire:
                return "HotSpotFire";
            case HotSpotType::JointFixed:
                return "JointFixed";
            case HotSpotType::JointRevolute:
                return "JointRevolute";
            case HotSpotType::JointRotationalSpring:
                return "JointRotationalSpring";
            case HotSpotType::HotSpotCombiner:
                return "HotSpotCombiner";
            case HotSpotType::HotSpotPierce:
                return "HotSpotPierce";
            case HotSpotType::HotSpotSkyPin:
                return "HotSpotSkyPin";
            case HotSpotType::HotSpotDigger:
                return "HotSpotDigger";
            default:
                return "";
        }
    }
    
}
