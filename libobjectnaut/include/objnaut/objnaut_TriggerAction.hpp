
#pragma once
#include <objnaut/objnaut_Ai.hpp>

namespace objnaut {

    enum class TriggerType : u8 {
        OnCollide = 0,
        OnCreate = 1,
        OnDestroy = 2,
        OnConsumed = 3,
        OnActivated = 4,
        OnDeactivated = 5,
        OnUsed = 6,
        OnUseEquipped = 7,
        OnVehicleAction = 8,
        OnObjectSwap = 9,
        OnModifyCharge = 10,
        OnTemperatureSolid = 11,
        OnTemperatureFluid = 12,
        OnTemperatureGas = 13,
        OnEnterLight = 14,
        OnEnterDarkness = 15,
        OnEquipped = 16,
        OnUnequipped = 17,
        OnAttached = 18,
        OnDetached = 19,
        OnSight = 20,
        OnPhysicsRest = 21,
        OnCatchFire = 22,
        ConditionAnd = 23,
        ConditionOr = 24,
        OnCheckVariable = 25,
        OnUpdate = 26,
        OnContained = 27,
        OnUncontained = 28,
        OnObjectAdded = 29,
        OnAiState = 30,
        OnAiAction = 31,
        OnObjectCountInArea = 32,
        OnDistance = 33,
        OnVelocity = 34,
        OnSplit = 35,
        OnPressed = 36,
        OnUnpressed = 37,
        OnAiEquip = 38,
        OnAiConsume = 39,
        OnEmpty = 40,
        OnFill = 41,
        OnModifyIntegrity = 42,
        OnHearSound = 43,
        OnMounted = 44,
        OnUnmounted = 45,
        TriggerGroup = 46,
        ConditionOiAnd = 47,
        OnAiUnequip = 48,
        OnApplyAdjective = 49,
        OnExtinguishFire = 50,
        OnKickAdjective = 51,

        Count
    };

    inline std::string FormatTriggerType(const TriggerType type) {
        switch(type) {
            case TriggerType::OnCollide:
                return "OnCollide";
            case TriggerType::OnCreate:
                return "OnCreate";
            case TriggerType::OnDestroy:
                return "OnDestroy";
            case TriggerType::OnConsumed:
                return "OnConsumed";
            case TriggerType::OnActivated:
                return "OnActivated";
            case TriggerType::OnDeactivated:
                return "OnDeactivated";
            case TriggerType::OnUsed:
                return "OnUsed";
            case TriggerType::OnUseEquipped:
                return "OnUseEquipped";
            case TriggerType::OnVehicleAction:
                return "OnVehicleAction";
            case TriggerType::OnObjectSwap:
                return "OnObjectSwap";
            case TriggerType::OnModifyCharge:
                return "OnModifyCharge";
            case TriggerType::OnTemperatureSolid:
                return "OnTemperatureSolid";
            case TriggerType::OnTemperatureFluid:
                return "OnTemperatureFluid";
            case TriggerType::OnTemperatureGas:
                return "OnTemperatureGas";
            case TriggerType::OnEnterLight:
                return "OnEnterLight";
            case TriggerType::OnEnterDarkness:
                return "OnEnterDarkness";
            case TriggerType::OnEquipped:
                return "OnEquipped";
            case TriggerType::OnUnequipped:
                return "OnUnequipped";
            case TriggerType::OnAttached:
                return "OnAttached";
            case TriggerType::OnDetached:
                return "OnDetached";
            case TriggerType::OnSight:
                return "OnSight";
            case TriggerType::OnPhysicsRest:
                return "OnPhysicsRest";
            case TriggerType::OnCatchFire:
                return "OnCatchFire";
            case TriggerType::ConditionAnd:
                return "ConditionAnd";
            case TriggerType::ConditionOr:
                return "ConditionOr";
            case TriggerType::OnCheckVariable:
                return "OnCheckVariable";
            case TriggerType::OnUpdate:
                return "OnUpdate";
            case TriggerType::OnContained:
                return "OnContained";
            case TriggerType::OnUncontained:
                return "OnUncontained";
            case TriggerType::OnObjectAdded:
                return "OnObjectAdded";
            case TriggerType::OnAiState:
                return "OnAiState";
            case TriggerType::OnAiAction:
                return "OnAiAction";
            case TriggerType::OnObjectCountInArea:
                return "OnObjectCountInArea";
            case TriggerType::OnDistance:
                return "OnDistance";
            case TriggerType::OnVelocity:
                return "OnVelocity";
            case TriggerType::OnSplit:
                return "OnSplit";
            case TriggerType::OnPressed:
                return "OnPressed";
            case TriggerType::OnUnpressed:
                return "OnUnpressed";
            case TriggerType::OnAiEquip:
                return "OnAiEquip";
            case TriggerType::OnAiConsume:
                return "OnAiConsume";
            case TriggerType::OnEmpty:
                return "OnEmpty";
            case TriggerType::OnFill:
                return "OnFill";
            case TriggerType::OnModifyIntegrity:
                return "OnModifyIntegrity";
            case TriggerType::OnHearSound:
                return "OnHearSound";
            case TriggerType::OnMounted:
                return "OnMounted";
            case TriggerType::OnUnmounted:
                return "OnUnmounted";
            case TriggerType::TriggerGroup:
                return "TriggerGroup";
            case TriggerType::ConditionOiAnd:
                return "ConditionOiAnd";
            case TriggerType::OnAiUnequip:
                return "OnAiUnequip";
            case TriggerType::OnApplyAdjective:
                return "OnApplyAdjective";
            case TriggerType::OnExtinguishFire:
                return "OnExtinguishFire";
            case TriggerType::OnKickAdjective:
                return "OnKickAdjective";
            default:
                return "";
        }
    }

    struct TriggerActionOptions {
        TriggerType type : 7;
        bool non_repeatable : 1;
    };
    static_assert(sizeof(TriggerActionOptions) == sizeof(u8));

    struct OnCollideTrigger {
        Filter filter;
        u16 min_speed_sq;
        bool use_other_speed;
        bool only_when_fired;
    };

    struct OnCreateTrigger {
    };

    struct OnDestroyTrigger {
    };

    struct OnConsumedTrigger {
        Filter filter;
    };

    struct OnActivateDeactivateTrigger {
    };

    enum class UseIcon : u8 {
        Default = 0,
        AnimalAction = 1,
        Attach = 2,
        Climb = 3,
        Consume = 4,
        Dig = 5,
        EmptyEquip = 6,
        EmptyTarget = 7,
        Equip = 8,
        FillEquip = 9,
        FillTarget = 10,
        Follow = 11,
        Guard = 12,
        Ignite = 13,
        Knock = 14,
        Mount = 15,
        MoveTo = 16,
        Pet = 17,
        PlayMusic = 18,
        Protect = 19,
        Shoot = 20,
        Split = 21,
        Spray = 22,
        Steal = 23,
        Swing = 24,
        Throw = 25,
        TurnOff = 26,
        TurnOn = 27,
        Use = 28,
        UseTarget = 29,
        VehicleAction = 30,
        Apply = 31,
        Clean = 32,
        Paint = 33,
        PlaySound = 34
    };

    inline std::string FormatUseIcon(const UseIcon icon) {
        switch(icon) {
            case UseIcon::Default:
                return "Default";
            case UseIcon::AnimalAction:
                return "AnimalAction";
            case UseIcon::Attach:
                return "Attach";
            case UseIcon::Climb:
                return "Climb";
            case UseIcon::Consume:
                return "Consume";
            case UseIcon::Dig:
                return "Dig";
            case UseIcon::EmptyEquip:
                return "EmptyEquip";
            case UseIcon::EmptyTarget:
                return "EmptyTarget";
            case UseIcon::Equip:
                return "Equip";
            case UseIcon::FillEquip:
                return "FillEquip";
            case UseIcon::FillTarget:
                return "FillTarget";
            case UseIcon::Follow:
                return "Follow";
            case UseIcon::Guard:
                return "Guard";
            case UseIcon::Ignite:
                return "Ignite";
            case UseIcon::Knock:
                return "Knock";
            case UseIcon::Mount:
                return "Mount";
            case UseIcon::MoveTo:
                return "MoveTo";
            case UseIcon::Pet:
                return "Pet";
            case UseIcon::PlayMusic:
                return "PlayMusic";
            case UseIcon::Protect:
                return "Protect";
            case UseIcon::Shoot:
                return "Shoot";
            case UseIcon::Split:
                return "Split";
            case UseIcon::Spray:
                return "Spray";
            case UseIcon::Steal:
                return "Steal";
            case UseIcon::Swing:
                return "Swing";
            case UseIcon::Throw:
                return "Throw";
            case UseIcon::TurnOff:
                return "TurnOff";
            case UseIcon::TurnOn:
                return "TurnOn";
            case UseIcon::Use:
                return "Use";
            case UseIcon::UseTarget:
                return "UseTarget";
            case UseIcon::VehicleAction:
                return "VehicleAction";
            case UseIcon::Apply:
                return "Apply";
            case UseIcon::Clean:
                return "Clean";
            case UseIcon::Paint:
                return "Paint";
            case UseIcon::PlaySound:
                return "PlaySound";
            default:
                return "";
        }
    }

    struct OnUsedTrigger {
        Filter filter;
        UseIcon icon;
    };

    struct OnUseEquippedTrigger {
        Filter filter;
        UseIcon icon;
    };

    struct OnVehicleActionTrigger {
        Filter filter;
        UseIcon icon;
    };

    struct OnObjectSwapTrigger {
    };

    enum class ChargeModificationTriggerType : u8 {
        ChargeGain = 0,
        ChargeLose = 1
    };

    inline std::string FormatChargeModificationTriggerType(const ChargeModificationTriggerType type) {
        switch(type) {
            case ChargeModificationTriggerType::ChargeGain:
                return "ChargeGain";
            case ChargeModificationTriggerType::ChargeLose:
                return "ChargeLose";
            default:
                return "";
        }
    }

    struct OnModifyChargeTrigger {
        ChargeModificationTriggerType type;
    };

    struct OnAttachedDetachedTrigger {
        Filter filter;
    };

    struct OnSightTrigger {
        Filter filter;
    };

    struct TriggerAction;

    struct ConditionTrigger {
        std::unique_ptr<TriggerAction> cond_a_trigger;
        std::unique_ptr<TriggerAction> cond_b_trigger;
    };

    enum class ScriptComparison : u8 {
        Equal = 0,
        NotEqual = 1,
        Greater = 2,
        Less = 3,
        Complex = 4
    };

    inline std::string FormatScriptComparison(const ScriptComparison comp) {
        switch(comp) {
            case ScriptComparison::Equal:
                return "Equal";
            case ScriptComparison::NotEqual:
                return "NotEqual";
            case ScriptComparison::Greater:
                return "Greater";
            case ScriptComparison::Less:
                return "Less";
            case ScriptComparison::Complex:
                return "Complex";
            default:
                return "";
        }
    }

    struct OnCheckVariableTrigger {
        bool only_check_on_change;
        ScriptComparison comp;
        std::string register_trigger_value;
        std::string register_name;
    };

    struct OnContainedUncontainedTrigger {
        Filter filter;
    };

    enum class DetectionMode : u8 {
        User = 1,
        Designer = 2,
        Both = 3
    };

    inline std::string FormatDetectionMode(const DetectionMode mode) {
        switch(mode) {
            case DetectionMode::User:
                return "User";
            case DetectionMode::Designer:
                return "Designer";
            case DetectionMode::Both:
                return "Both";
            default:
                return "";
        }
    }
    
    struct OnObjectAddedTriggerActionOptions {
        bool unique_objects : 1;
        DetectionMode mode : 3;
        bool unique_adjectives : 1;
    };
    static_assert(sizeof(OnObjectAddedTriggerActionOptions) == sizeof(u8));
    
    struct OnObjectAddedTrigger {
        Filter filter;
        OnObjectAddedTriggerActionOptions options;
    };

    struct OnAiStateTrigger {
        AiMood goal_mood;
    };

    struct OnAiActionTrigger {
        Filter filter;
        AtrRepMode action;
    };

    struct OnObjectCountInAreaTrigger {
        Filter filter;
    };

    struct OnDistanceTrigger {
        Filter filter;
        ScriptComparison compare_condition;
        u16 trigger_distance;
    };

    struct OnVelocityTrigger {
        ScriptComparison compare_condition; // Only Greater or Less
        u16 trigger_velocity_sq;
    };

    struct OnAiEquipUnequipTrigger {
        Filter filter;
    };

    struct OnAiConsumeTrigger {
        Filter filter;
    };

    struct OnEmptyFillTrigger {
        Filter filter;
        bool unique_objects;
    };

    struct OnModifyIntegrityTrigger {
        Filter filter;
    };

    struct OnHearSoundTrigger {
        SoundAttribute attr;  
    };

    struct OnMountedUnmountedTrigger {
        Filter filter;
        bool control_spot_only;
    };

    struct TriggerGroupTrigger : public OnCheckVariableTrigger {
        std::vector<TriggerAction> group_triggers;
    };

    struct OnApplyKickAdjectiveTrigger {
        Filter filter;
    };

    //////////////////////////////////////

    struct Trigger {
        OnCollideTrigger on_collide;
        OnCreateTrigger on_create;
        OnDestroyTrigger on_destroy;
        OnConsumedTrigger on_consumed;
        OnActivateDeactivateTrigger on_activate_deactivate;
        OnUsedTrigger on_used;
        OnUseEquippedTrigger on_use_equipped;
        OnVehicleActionTrigger on_vehicle_action;
        OnObjectSwapTrigger on_obj_swap;
        OnModifyChargeTrigger on_mod_charge;
        OnAttachedDetachedTrigger on_attached_detached;
        OnSightTrigger on_sight;
        ConditionTrigger condition;
        OnCheckVariableTrigger on_check_var;
        OnContainedUncontainedTrigger on_contained_uncontained;
        OnObjectAddedTrigger on_obj_added;
        OnAiStateTrigger on_ai_state;
        OnAiActionTrigger on_ai_action;
        OnObjectCountInAreaTrigger on_obj_count_in_area;
        OnDistanceTrigger on_distance;
        OnVelocityTrigger on_velocity;
        OnAiEquipUnequipTrigger on_ai_equip_unequip;
        OnAiConsumeTrigger on_ai_consume;
        OnEmptyFillTrigger on_empty_fill;
        OnModifyIntegrityTrigger on_modify_integrity;
        OnHearSoundTrigger on_hear_sound;
        OnMountedUnmountedTrigger on_mounted_unmounted;
        TriggerGroupTrigger group;
        OnApplyKickAdjectiveTrigger on_apply_kick_adj;
    };

    //////////////////////

    enum class ActionType : u8 {
        SpawnObject = 0,
        EnableShape = 1,
        Destroy = 2,
        PlaySfx = 3,
        Activate = 4,
        Deactivate = 5,
        Toggle = 6,
        ApplyForce = 7,
        ModifyAiState = 8,
        ModifyAtrRepList = 9,
        SwapObject = 10,
        MoveTo = 11,
        MoveRelative = 12,
        AttachTo = 13,
        DetachFromAll = 14,
        DealDamage = 15,
        Split = 16,
        ThrowAtTarget = 17,
        FireProjectile = 18,
        SetTemperature = 19,
        Animation = 20,
        Wait = 21,
        EmptyFill = 22,
        SpawnRandom = 23,
        SetOnFire = 24,
        SetVariable = 25,
        Add = 26,
        EndLevel = 27,
        SpawnObjectAt = 28,
        ShowEmote = 29,
        Explode = 30,
        ImageSwap = 31,
        Cinematic = 32,
        ShowNotepad = 33,
        EncaseInIce = 34,
        SetStageObject = 35,
        EnableEntity = 36,
        Switch = 37,
        EnableSFAnim = 38,
        RotateEntity = 39,
        ApplyAdjective = 40,
        // Unused: ShowTextBox = 41, // Unused
        ShowFeedback = 42,
        Lock = 43,
        NoDrag = 44,
        SetInterruptFlag = 45,
        Shock = 46,
        Untouchable = 47,
        ModifyLineOfSight = 48,

        Count
    };

    static_assert(sizeof(u8) == 1);
    static_assert(sizeof(bool) == 1);

    inline std::string FormatActionType(const ActionType type) {
        switch(type) {
            case ActionType::SpawnObject:
                return "SpawnObject";
            case ActionType::EnableShape:
                return "EnableShape";
            case ActionType::Destroy:
                return "Destroy";
            case ActionType::PlaySfx:
                return "PlaySfx";
            case ActionType::Activate:
                return "Activate";
            case ActionType::Deactivate:
                return "Deactivate";
            case ActionType::Toggle:
                return "Toggle";
            case ActionType::ApplyForce:
                return "ApplyForce";
            case ActionType::ModifyAiState:
                return "ModifyAiState";
            case ActionType::ModifyAtrRepList:
                return "ModifyAtrRepList";
            case ActionType::SwapObject:
                return "SwapObject";
            case ActionType::MoveTo:
                return "MoveTo";
            case ActionType::MoveRelative:
                return "MoveRelative";
            case ActionType::AttachTo:
                return "AttachTo";
            case ActionType::DetachFromAll:
                return "DetachFromAll";
            case ActionType::DealDamage:
                return "DealDamage";
            case ActionType::Split:
                return "Split";
            case ActionType::ThrowAtTarget:
                return "ThrowAtTarget";
            case ActionType::FireProjectile:
                return "FireProjectile";
            case ActionType::SetTemperature:
                return "SetTemperature";
            case ActionType::Animation:
                return "Animation";
            case ActionType::Wait:
                return "Wait";
            case ActionType::EmptyFill:
                return "EmptyFill";
            case ActionType::SpawnRandom:
                return "SpawnRandom";
            case ActionType::SetOnFire:
                return "SetOnFire";
            case ActionType::SetVariable:
                return "SetVariable";
            case ActionType::Add:
                return "Add";
            case ActionType::EndLevel:
                return "EndLevel";
            case ActionType::SpawnObjectAt:
                return "SpawnObjectAt";
            case ActionType::ShowEmote:
                return "ShowEmote";
            case ActionType::Explode:
                return "Explode";
            case ActionType::ImageSwap:
                return "ImageSwap";
            case ActionType::Cinematic:
                return "Cinematic";
            case ActionType::ShowNotepad:
                return "ShowNotepad";
            case ActionType::EncaseInIce:
                return "EncaseInIce";
            case ActionType::SetStageObject:
                return "SetStageObject";
            case ActionType::EnableEntity:
                return "EnableEntity";
            case ActionType::Switch:
                return "Switch";
            case ActionType::EnableSFAnim:
                return "EnableSFAnim";
            case ActionType::RotateEntity:
                return "RotateEntity";
            case ActionType::ApplyAdjective:
                return "ApplyAdjective";
            case ActionType::ShowFeedback:
                return "ShowFeedback";
            case ActionType::Lock:
                return "Lock";
            case ActionType::NoDrag:
                return "NoDrag";
            case ActionType::SetInterruptFlag:
                return "SetInterruptFlag";
            case ActionType::Shock:
                return "Shock";
            case ActionType::Untouchable:
                return "Untouchable";
            case ActionType::ModifyLineOfSight:
                return "ModifyLineOfSight";
            default:
                return "";
        }
    }

    enum class ActionTarget : u8 {
        Self = 0,
        Other = 1,
        All = 2,
        Terrain = 3,
        StageEntity = 4,
        Retired = 5,
        Unknown = 6
    };

    inline std::string FormatActionTarget(const ActionTarget target) {
        switch(target) {
            case ActionTarget::Self:
                return "Self";
            case ActionTarget::Other:
                return "Other";
            case ActionTarget::All:
                return "All";
            case ActionTarget::Terrain:
                return "Terrain";
            case ActionTarget::StageEntity:
                return "StageEntity";
            case ActionTarget::Retired:
                return "Retired";
            case ActionTarget::Unknown:
                return "Unknown";
            default:
                return "";
        }
    }

    struct ActionTargetData {
        ActionTarget target;
        u32 target_stage_entity;
    };

    ////////////

    struct SpawnObjectActionOptions {
        u8 max_objects : 7;
        bool stop_if_no_spawn : 1;
    };
    static_assert(sizeof(SpawnObjectActionOptions) == sizeof(u8));

    struct SpawnObjectAction {
        bool is_particle;
        u16 spawn_obj_file_id;
        bool inherit_adjs_from_parent;
        std::vector<u16> adjs;
        u8 hotspot_idx;
        SpawnObjectActionOptions options;
    };

    struct EnableShapeAction {
        u8 index;
        bool toggle;
    };

    struct DestroyActionOptions {
        bool poof_cloud : 1;
        bool destroy_connected : 1;
    };
    static_assert(sizeof(DestroyActionOptions) == sizeof(u8));
    
    struct DestroyAction {
        ActionTargetData target;
        DestroyActionOptions options;
    };

    struct AudioFilter {
        SoundAttribute attr;
        ObjectCategoryId obj_category_id;
        u16 obj_subcategory_id_1;
        u16 obj_subcategory_id_2;
        u16 obj_id;
    };

    struct PlaySfxAction {
        u16 group_id;
        u16 seq_arc_or_music_id;
        u16 sfx_id;
        SoundAttribute sound_attr;
        std::vector<AudioFilter> filters;
    };

    struct ActivateDeactivateToggleAction {
        ActionTargetData target;
    };

    struct ApplyForceAction {
        ActionTargetData target;
        fx32 force_x;
        fx32 force_y;
        fx32 torque;
        bool not_absolute_force;
    };

    struct ModifyAiStateAction {
        ActionTargetData target;
        AiMood mood;
    };

    struct ModifyAtrRepListAction {
        ActionTargetData target;
        std::vector<ModAiAtrRep> normal;
        std::vector<ModAiAtrRep> exclude;
    };

    struct SwapObjectActionOptions {
        bool use_previous_self : 1;
        bool inherit_adjs_from_parent : 1;
    };
    static_assert(sizeof(SwapObjectActionOptions) == sizeof(u8));

    struct SwapObjectAction {
        ActionTargetData target;
        u16 swap_obj_file_id;
        SwapObjectActionOptions options;
        std::vector<u16> adjs;
    };

    struct MoveToAction {
        ActionTargetData target;
        u32 target_x;
        u32 target_y;
        u16 frame_count;
    };

    struct MoveRelativeAction {
        ActionTargetData target;
        u32 delta_x;
        u32 delta_y;
        u16 frame_count;
    };

    enum class AttachToType : u8 {
        Attach = 0,
        Mount = 1,
        Equip = 2
    };

    inline std::string FormatAttachToType(const AttachToType type) {
        switch(type) {
            case AttachToType::Attach:
                return "Attach";
            case AttachToType::Mount:
                return "Mount";
            case AttachToType::Equip:
                return "Equip";
            default:
                return "";
        }
    }

    struct AttachToAction {
        u16 entity_id_a;
        u16 unused_a;
        bool load_new_object;
        u16 entity_id_b;
        u16 unused_b;
        bool inherit_adjs_from_parent;
        std::vector<u16> adjs;
        AttachToType type;
    };

    struct DealDamageAction {
        ActionTargetData target;
        u8 damage_amount;
    };

    struct SplitAction {
        ActionTargetData target;
        u8 unused;
    };

    struct ThrowAtTargetAction {
        u16 throw_speed_ppf;
        Animation anim;
    };

    struct FireProjectileActionOptions {
        bool ignore_gravity : 1;
        bool index_is_label : 1;
    };
    static_assert(sizeof(FireProjectileActionOptions) == sizeof(u8));
    
    struct FireProjectileAction {
        bool is_particle;
        u16 spawn_obj_file_id;
        u8 hotspot_idx;
        FireProjectileActionOptions options;
        u16 fly_speed_ppf;
    };

    struct SetTemperatureAction {
        ActionTargetData target;
        u8 temperature;
        u8 unused;
    };

    struct AnimationAction {
        ActionTargetData target;
        Animation new_anim;
    };

    struct WaitAction {
        u16 frame_count;
    };

    struct EmptyFillAction {
        bool is_not_empty;
    };

    struct SpawnRandomEntry {
        u16 spawn_id;
        u16 spawn_adj_id;
    };
    
    struct SpawnRandomAction {
        std::vector<SpawnRandomEntry> entries;
        bool inherit_adjs_from_parent;
        u8 hotspot_idx;
        SpawnObjectActionOptions options;
    };

    struct SetOnFireAction {
        ActionTargetData target;
        bool set_on_fire;
    };

    struct SetVariableAction {
        std::string value;
        std::string register_name;
    };

    struct AddAction {
        u8 amount;
        std::string register_name;
    };

    struct EndLevelAction {
        u8 section_id;
        u16 cinematic_file_id;
    };

    struct SpawnObjectAtActionOptions {
        bool bounce_towards_maxwell : 1;
        bool make_draggable : 1;
        bool suppress_adjs_banner : 1;
    };
    static_assert(sizeof(SpawnObjectAtActionOptions) == sizeof(u8));
    
    struct SpawnObjectAtAction {
        ActionTargetData target;
        bool is_particle;
        u16 spawn_obj_file_id;
        bool inherit_adjs_from_parent;
        std::vector<u16> adjs;
        fx32 relative_pos_x;
        fx32 relative_pos_y;
        SpawnObjectAtActionOptions options_2;
        SpawnObjectActionOptions options_1;
    };

    struct ShowEmoteAction {
        ActionTargetData target;
        AiEmoteType next_emote;
    };

    struct ExplodeAction {
        u8 explosion_size;
        u16 explode_countdown;
    };

    struct ImageSwapAction {
        ActionTargetData target;
        u16 file_id;
    };

    struct CinematicAction {
        u8 section_id;
        u32 cinematic_file_id;
    };

    struct ShowNotepadAction {
        bool show;
    };

    struct EncaseInIceAction {
        ActionTargetData target;
    };

    struct SetStageObjectAction {
        ActionTargetData target;
        AtrRepMode mode;
        bool ignore_stage_object_line_of_sight;
        u32 new_target_entity_id;
    };

    struct EnableEntityAction {
        ActionTargetData target;
        bool enable;
    };

    enum class SwitchType : u8 {
        Shuffle = 0,
        Random = 1,
        Sequential = 2
    };

    inline std::string FormatSwitchType(const SwitchType type) {
        switch(type) {
            case SwitchType::Shuffle:
                return "Shuffle";
            case SwitchType::Random:
                return "Random";
            case SwitchType::Sequential:
                return "Sequential";
            default:
                return "";
        }
    }

    struct ActionEntry;

    struct SwitchAction {
        SwitchType type;
        std::vector<std::vector<ActionEntry>> switch_actions;
    };

    struct EnableSFAnimAction {
        u8 index;
        bool toggle;
    };

    struct RotateEntityAction {
        ActionTargetData target;
        u16 rot_per_sec;
    };

    struct ApplyAdjectiveAction {
        ActionTargetData target;
        u16 adj_id;
        bool suppress_banner;
    };

    struct ShowFeedbackActionOptions {
        bool positive_feedback : 1;
        bool is_screen_space : 1;
    };
    static_assert(sizeof(ShowFeedbackActionOptions) == sizeof(u8));
    
    struct ShowFeedbackAction {
        ActionTargetData target;
        ShowFeedbackActionOptions options;
        fx32 relative_pos_x;
        fx32 relative_pos_y;
    };

    struct LockAction {
        ActionTargetData target;
        Filter filter;
    };

    enum class TriggerFlagSlot : u8 {
        ON = 0,
        TF = 1,
        OE = 2,
        Game = 3,
        Adjective = 4
    };

    inline std::string FormatTriggerFlagSlot(const TriggerFlagSlot slot) {
        switch(slot) {
            case TriggerFlagSlot::ON:
                return "ON";
            case TriggerFlagSlot::TF:
                return "TF";
            case TriggerFlagSlot::OE:
                return "OE";
            case TriggerFlagSlot::Game:
                return "Game";
            case TriggerFlagSlot::Adjective:
                return "Adjective";
            default:
                return "";
        }
    }

    struct SetInterruptFlagActionOptions {
        TriggerFlagSlot trigger_slot : 7;
        bool set_flag : 1;
    };
    static_assert(sizeof(SetInterruptFlagActionOptions) == sizeof(u8));
    
    struct SetInterruptFlagAction {
        SetInterruptFlagActionOptions options;
        TriggerType parent_trigger_type;
    };

    struct ShockAction {
        ActionTargetData target;
    };

    enum class UntouchableSetting : u8 {
        Off = 0,
        On = 1,
        Toggle = 2
    };

    inline std::string FormatUntouchableSetting(const UntouchableSetting setting) {
        switch(setting) {
            case UntouchableSetting::Off:
                return "Off";
            case UntouchableSetting::On:
                return "On";
            case UntouchableSetting::Toggle:
                return "Toggle";
            default:
                return "";
        }
    }

    struct UntouchableAction {
        ActionTargetData target;
        UntouchableSetting setting;
    };

    struct ModifyLineOfSightAction {
        ActionTargetData target;
        u8 line_of_sight;
    };

    ///////////

    struct ActionEntry {
        ActionType type;

        SpawnObjectAction spawn_obj;
        EnableShapeAction enable_shape;
        DestroyAction destroy;
        PlaySfxAction play_sfx;
        ActivateDeactivateToggleAction activate_deactivate_toggle;
        ApplyForceAction apply_force;
        ModifyAiStateAction modify_ai_state;
        ModifyAtrRepListAction modify_atr_rep_list;
        SwapObjectAction swap_obj;
        MoveToAction move_to;
        MoveRelativeAction move_relative;
        AttachToAction attach_to;
        DealDamageAction deal_damage;
        SplitAction split;
        ThrowAtTargetAction throw_at_target;
        FireProjectileAction fire_projectile;
        SetTemperatureAction set_temperature;
        AnimationAction animation;
        WaitAction wait;
        EmptyFillAction empty_fill;
        SpawnRandomAction spawn_random;
        SetOnFireAction set_on_fire;
        SetVariableAction set_var;
        AddAction add;
        EndLevelAction end_level;
        SpawnObjectAtAction spawn_obj_at;
        ShowEmoteAction show_emote;
        ExplodeAction explode;
        ImageSwapAction image_swap;
        CinematicAction cinematic;
        ShowNotepadAction show_notepad;
        EncaseInIceAction encase_in_ice;
        SetStageObjectAction set_stage_obj;
        EnableEntityAction enable_entity;
        SwitchAction swtch;
        EnableSFAnimAction enable_sf_anim;
        RotateEntityAction rotate_entity;
        ApplyAdjectiveAction apply_adj;
        ShowFeedbackAction show_feedback;
        LockAction lock;
        SetInterruptFlagAction set_interrupt_flag;
        ShockAction shock;
        UntouchableAction untouchable;
        ModifyLineOfSightAction modify_line_of_sight;
    };

    struct TriggerAction {
        TriggerActionOptions options;
        Trigger trigger;
        std::vector<ActionEntry> actions;
    };
    
}
