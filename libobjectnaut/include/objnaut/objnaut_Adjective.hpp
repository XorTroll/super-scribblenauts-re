
#pragma once
#include <objnaut/objnaut_Ai.hpp>
#include <objnaut/objnaut_TriggerAction.hpp>

namespace objnaut {

    struct AdjectiveHeaderOptions {
        bool inheritable : 1;
        bool not_for_runtime : 1;
    };
    static_assert(sizeof(AdjectiveHeaderOptions) == sizeof(u8));

    struct AdjectiveHeader {
        u16 category_id;
        u16 subcategory_id;
        u16 adj_id;
        AdjectiveHeaderOptions options;
        u16 budget_cost;
        u8 coolness;
        u8 material_priority;
        Filter conflict_filter;
        Filter conflict_override_filter;
    };

    enum class AdjectiveFilterType : u8 {
        Filter = 0,
        BasicFilter = 1
    };

    //////////////////////////

    enum class ModifierType : u8 {
        Property = 0,
        Color = 1,
        AtrRep = 2,
        Material = 3,
        RemoveTriggers = 4,
        AddTrigger = 5,
        Size = 6,
        Emitter = 7,
        Damage = 8,
        TemperatureZone = 9,
        AddSFAnimation = 10,
        AddRemoveObject = 11,
        Mass = 12,
        Movement = 13,
        ExcludeAiState = 14,
        EnableDisableSpot = 15,
        RemoveActions = 16
    };

    enum class PropertyModifierProperty : u8 {
        Generic_IgnoreForceFields = 1,
        Generic_IgnoreGravity = 2,
        Generic_StartDeactivated = 3,
        Generic_VehicleAnimation = 4,
        Generic_RopeLength = 5,
        Generic_Ammunition = 6,
        Ai_DefaultAiState = 7,
        Ai_EnableAi = 8,
        Ai_SightTileDistance = 9,
        Ai_Visibility = 10,

        Ai_ReactSizeCompare = 13,
        Ai_CanClimb = 14,
        Ai_CanDive = 15,
        Ai_CanFly = 16,
        Ai_CanSwim = 17,
        Ai_CanWalk = 18,
        Movement_IncludeRiderAirMovement = 19,
        Ai_GrantWaterBreathing = 20,
        Movement_RequiresTakeOff = 21,
        Ai_AttackDamage = 22,
        Container_IsOpenContainer = 23,
        Container_ShowContainedObjects = 24,
        Container_DisplayContainedObjectsAtBottom = 25,
        Container_Width = 26,
        Container_Height = 27,
        Electricity_GeneratesCharge = 28,
        Electricity_TransportsCharge = 29,
        Electricity_WaterChargeType = 30,
        Electricity_IgnoreWaterParticles = 31,
        Electricity_ShockOnTouch = 32,
        Placement_PlacementType = 33,
        Placement_SkyOnly = 34,
        Placement_IsBackground = 35,
        Placement_AllowMirror = 36,
        Placement_AllowRotate90 = 37,
        Placement_CollidesWithAi = 38,

        Physics_Material = 40,
        Physics_Mass = 41,
        Physics_Integrity = 42,
        Physics_Physics_Inertia = 43,
        Physics_FireInteraction = 44,
        Physics_BuoyancyFactor = 45,
        Physics_Waterproof = 46,

        Temperature_InitialTemperature = 48,
        Temperature_MeltingPoint = 49,
        Temperature_GasPoint = 50,
        Physics_IsOnFire = 51,
        Physics_Flammable = 52,
        Physics_Magnetic = 53,
        Physics_Sticky = 54,
        Movement_JumpHeight = 55,
        Movement_ActorVelocity = 56,
        Ai_Emote = 57,
        Movement_GrantJump = 58,
        Movement_GrantSpeed = 59,
        ShapesSpots_NoWater = 60,
        Temperature_CurrentTemperature = 61,
        Movement_MovementHFlip = 62,
        Electricity_CanBeShocked = 63,
    
        Movement_EnableMovement = 65,
        Physics_InExtinguishable = 66,
        Physics_Bouncy = 67
    };

    enum class PropertyModifierValueType : u8 {
        Boolean = 0,
        Byte = 1,
        SByte = 2,
        Int16 = 3,
        UInt16 = 4,
        Int32 = 5,
        UInt32 = 6,
        Int64 = 7,
        Uint64 = 8,
        Single = 9,
        Double = 10,
        String = 11,
        Enum = 12,
        Fx32 = 13
    };

    enum class ModifierOperation : u8 {
        Set = 1,
        Add = 2,
        Subtract = 3,
        Multiply = 4,
        Divide = 5
    };

    struct PropertyModifierData {
        PropertyModifierProperty property;
        PropertyModifierValueType value_type;
        ModifierOperation operation;

        bool boolean;
        u8 val_byte;
        s8 val_sbyte;
        s16 val_int16;
        u16 val_uint16;
        s32 val_int32;
        u32 val_uint32;
        s64 val_int64;
        u64 val_uint64;
        float val_single;
        double val_double;
        std::string val_string;
        u8 val_enum;
        fx32 val_fx32;
    };

    struct ColorModifierData {
        u32 shade;
        bool is_shade;
    };

    struct AtrRepModifierData {
        std::vector<AiAtrRep> normal;
        std::vector<AiAtrRep> exclude;
    };

    struct MaterialModifierData {
        u16 material_id;
    };

    struct RemoveTriggersModifierData {
        std::vector<TriggerType> trigger_types;
    };

    struct AddTriggerModifierData {
        std::unique_ptr<TriggerAction> triggers;
    };

    struct SizeModifierData {
        BodyPart body_part_selection;
        s32 scale_percent_x;
        s32 scale_percent_y;
    };

    struct EmitterModifierData {
        fx32 emit_angle;
        bool scatter_shot;
        bool apply_gravity;
        fx32 emit_speed;
        u32 spawn_interval;
        u8 spawn_count;
        fx32 emit_x;
        fx32 emit_y;
        bool spawn_obj_is_particle;
        u16 spawn_obj_id;
        EmitterLabel label;
    };

    struct DamageModifierData {
        u8 modifier_value;
        ModifierOperation operation;
    };

    struct TemperatureZoneModifierData {
        bool enable;
        fx32 temperature;
    };

    struct AddSFAnimationModifierData {
        u8 pos_x;
        u8 pos_y;
        u16 sprite_id;
        u8 anim_idx;
        s8 z_order;
        fx32 speed;
        bool disable_anim;
        u16 sprite_file_id;
    };

    struct AddRemoveObjectModifierData {
        bool add;
        u16 add_obj_file_id;
        EquipLocation equip_spot;
    };

    enum class MassModificationType : u8 {
        SetCategory = 0,
        ModifyCategory = 1
    };

    struct MassModifierData {
        MassModificationType type;

        u8 mod_category;
        u8 category;
    };

    struct MovementModifierData {
        bool equip_enable;
        bool equip_disable;
        bool ai_enable;
        bool ai_disable;
        bool drive_enable;
        bool drive_disable;
    };

    struct ExcludeAiStateModifierData {
        // Unsupported!
    };

    struct EnableDisableSpotModifierOptions {
        HotSpotType type : 7;
        bool enable : 1;
    };
    static_assert(sizeof(EnableDisableSpotModifierOptions) == sizeof(u8));
    
    struct EnableDisableSpotModifierData {
        bool enable;
        EquipLocation equip_spot;
    };

    struct RemoveActionsModifierData {
        ActionType action;
    };

    ////

    struct Modifier {
        ModifierType type;

        PropertyModifierData property;
        ColorModifierData color;
        AtrRepModifierData atr_rep;
        MaterialModifierData material;
        RemoveTriggersModifierData remove_triggers;
        AddTriggerModifierData add_trigger;
        SizeModifierData size;
        EmitterModifierData emitter;
        DamageModifierData damage;
        TemperatureZoneModifierData temperature_zone;
        AddSFAnimationModifierData add_sf_anim;
        AddRemoveObjectModifierData add_remove_obj;
        MassModifierData mass;
        MovementModifierData movement;
        ExcludeAiStateModifierData exclude_ai_state;
        EnableDisableSpotModifierData enable_disable_spot;
        RemoveActionsModifierData remove_actions;
    };

    struct AdjectiveFilter {
        AdjectiveFilterType type;
        FilterEntry basic_filter_entry;
        std::vector<Modifier> modifiers;
    };

    struct AdjectiveModificationModule {
        std::vector<AdjectiveFilter> filters;
    };

    struct Adjective {
        AdjectiveHeader header;
        AdjectiveModificationModule modification;
    };

}
