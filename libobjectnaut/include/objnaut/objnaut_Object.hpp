
#pragma once
#include <objnaut/objnaut_TriggerAction.hpp>

namespace objnaut {

    enum class ModuleTag : u8 {
        Generic = 10,
        Movement = 13,
        Ai = 1,
        Container = 2,
        Electricity = 3,
        Placement = 4,
        Physics = 5,
        Temperature = 6,
        TriggersActions = 7,
        Frames = 8,
        Audio = 11,
        Attack = 9
    };

    struct ObjectHeader {
        ObjectCategoryId category_id;
        ObjectSubCategoryId subcategory_id_1;
        ObjectSubCategoryId subcategory_id_2;
        u16 obj_id;
        u16 width;
        u16 height;
    };

    enum class EquipSizeRequirement : u8 {
        MustMatch = 0,
        CanBeSmaller = 1,
        CanBeBigger = 2,
        DoesNotMatter = 3
    };

    inline std::string FormatEquipSizeRequirement(const EquipSizeRequirement req) {
        switch(req) {
            case EquipSizeRequirement::MustMatch:
                return "MustMatch";
            case EquipSizeRequirement::CanBeSmaller:
                return "CanBeSmaller";
            case EquipSizeRequirement::CanBeBigger:
                return "CanBeBigger";
            case EquipSizeRequirement::DoesNotMatter:
                return "DoesNotMatter";
            default:
                return "";
        }
    }

    enum class VehicleAnimation : u8 {
        None = 0,
        Motor = 1,
        Airplane = 2,
        StabilizeOnly = 3
    };

    inline std::string FormatVehicleAnimation(const VehicleAnimation anim) {
        switch(anim) {
            case VehicleAnimation::None:
                return "None";
            case VehicleAnimation::Motor:
                return "Motor";
            case VehicleAnimation::Airplane:
                return "Airplane";
            case VehicleAnimation::StabilizeOnly:
                return "StabilizeOnly";
            default:
                return "";
        }
    }

    struct ObjectGenericOptions1 {
        bool ignores_force_fields : 1;
        bool ignores_gravity : 1;
        bool ta_not_active : 1;
        bool picking_uses_region : 1;
        bool has_climb_filter : 1;
        EquipSizeRequirement req : 3;
    };
    static_assert(sizeof(ObjectGenericOptions1) == sizeof(u8));

    struct ObjectGenericOptions2 {
        VehicleAnimation vehicle_anim : 4;
        bool update_physics_from_animations : 1;
    };
    static_assert(sizeof(ObjectGenericOptions1) == sizeof(u8));

    struct ObjectGenericModule {
        ObjectGenericOptions1 options_1;
        ObjectGenericOptions2 options_2;
        u8 rope_length;
        u8 clip_size;
        u8 budget_class;
        Filter climb_filter;
    };

    enum class GroundMotion : u8 {
        Default = 0,
        Bounce = 1,
        Roll = 2,
        Slide = 3,
        Walk = 4,
        Drive = 5
    };

    inline std::string FormatGroundMotion(const GroundMotion motion) {
        switch(motion) {
            case GroundMotion::Default:
                return "Default";
            case GroundMotion::Bounce:
                return "Bounce";
            case GroundMotion::Roll:
                return "Roll";
            case GroundMotion::Slide:
                return "Slide";
            case GroundMotion::Walk:
                return "Walk";
            case GroundMotion::Drive:
                return "Drive";
            default:
                return "";
        }
    }

    struct ObjectMovementOptions {
        bool grant_jump : 1;
        bool include_rider_air_movement : 1;
        bool requires_takeoff : 1;
        bool grants_speed : 1;
        GroundMotion ground_motion : 2;
        bool grants_fly : 1;
        bool movement_h_flip : 1;
    };
    static_assert(sizeof(ObjectMovementOptions) == sizeof(u8));

    struct ObjectMovementFlags {
        bool walk : 1;
        bool swim : 1;
        bool dive : 1;
        bool fly : 1;
        bool glide : 1;
        bool hover : 1;
        bool climb : 1;
        bool unused : 1;
    };
    static_assert(sizeof(ObjectMovementFlags) == sizeof(u8));

    struct ObjectMovementModule {
        u16 movement_speed;
        u8 jump_height;
        ObjectMovementOptions options;
        ObjectMovementFlags movement_as_equipment;
        ObjectMovementFlags movement_as_ai;
        ObjectMovementFlags movement_as_vehicle;
    };

    struct ObjectAiOptions {
        bool ai_enabled : 1;
        bool dig_enabled : 1;
        bool split_enabled : 1;
        bool shoot_enabled : 1;
    };
    static_assert(sizeof(ObjectAiOptions) == sizeof(u8));

    struct AiAtrRepList {
        std::vector<AiAtrRep> atr_reps;
        std::vector<AiAtrRep> excludes;
    };

    enum class AiReactSizeCompare : u8 {
        SizeCompare = 0,
        Attack = 1,
        Flee = 2
    };

    inline std::string FormatAiReactSizeCompare(const AiReactSizeCompare compare) {
        switch(compare) {
            case AiReactSizeCompare::SizeCompare:
                return "SizeCompare";
            case AiReactSizeCompare::Attack:
                return "Attack";
            case AiReactSizeCompare::Flee:
                return "Flee";
            default:
                return "";
        }
    }

    struct ObjectAiModule {
        AiMood ai_mood;
        ObjectAiOptions options;
        u8 sight_distance_tiles;
        u8 visibility_factor;
        AiReactSizeCompare react_size_compare;
        u8 attack_damage;
        AiAtrRepList atr_rep_list;
    };

    struct ObjectContainerOptions {
        bool open_container : 1;
        bool show_contained_objects : 1;
        bool display_contained_objects_at_bottom : 1;
        bool is_cannon : 1;
    };
    static_assert(sizeof(ObjectContainerOptions) == sizeof(u8));

    struct ObjectContainerModule {
        ObjectContainerOptions options;
        u8 container_width;
        u8 container_height;
        std::vector<u16> contained_obj_file_ids;
    };

    enum class WaterCharge : u8 {
        None = 0,
        Short = 1,
        Electrify = 2
    };

    inline std::string FormatWaterCharge(const WaterCharge charge) {
        switch(charge) {
            case WaterCharge::None:
                return "None";
            case WaterCharge::Short:
                return "Short";
            case WaterCharge::Electrify:
                return "Electrify";
            default:
                return "";
        }
    }

    struct ObjectElectricityOptions {
        WaterCharge water_charge : 2;
        bool can_be_shocked : 1;
        bool ignore_water_particles : 1;
        bool shock_on_touch : 1;
        bool transports_charge : 1;
    };
    static_assert(sizeof(ObjectElectricityOptions) == sizeof(u8));

    struct ObjectElectricityModule {
        bool generates_charge;
        ObjectElectricityOptions options;
    };

    enum class ObjectPlacementType : u8 {
        Free = 0,
        Static = 1,
        Puddle = 2,
        Terrain = 3
    };

    inline std::string FormatObjectPlacementType(const ObjectPlacementType type) {
        switch(type) {
            case ObjectPlacementType::Free:
                return "Free";
            case ObjectPlacementType::Static:
                return "Static";
            case ObjectPlacementType::Puddle:
                return "Puddle";
            case ObjectPlacementType::Terrain:
                return "Terrain";
            default:
                return "";
        }
    }

    struct ObjectPlacementOptions {
        bool enable_sky : 1;
        bool enable_background : 1;
        bool enable_h_flip : 1;
        bool enable_rotate_90 : 1;
        bool collides_with_ai : 1;
        bool align_to_terrain : 1;
    };
    static_assert(sizeof(ObjectPlacementOptions) == sizeof(u8));

    struct ObjectPlacementModule {
        ObjectPlacementType type;
        ObjectPlacementOptions options;
    };
    
    enum class ObjectPhysicsCombiner : u8 {
        None = 0,
        Pierce = 1,
        Combine = 2,
        Rope = 3
    };

    inline std::string FormatObjectPhysicsCombiner(const ObjectPhysicsCombiner combiner) {
        switch(combiner) {
            case ObjectPhysicsCombiner::None:
                return "None";
            case ObjectPhysicsCombiner::Pierce:
                return "Pierce";
            case ObjectPhysicsCombiner::Combine:
                return "Combine";
            case ObjectPhysicsCombiner::Rope:
                return "Rope";
            default:
                return "";
        }
    }

    enum class ObjectMaterial : u8 {
        OrganicPlant = 0,
        OrganicAnimal = 1,
        Food = 2,
        Wood = 3,
        Earth = 4,
        Stone = 5,
        Fire = 6,
        Water = 7,
        Metal = 8,
        Gas = 9,
        Plastic = 10,
        Fabric = 11,
        Glass = 12,
        Starite = 13
    };

    inline std::string FormatObjectMaterial(const ObjectMaterial material) {
        switch(material) {
            case ObjectMaterial::OrganicPlant:
                return "OrganicPlant";
            case ObjectMaterial::OrganicAnimal:
                return "OrganicAnimal";
            case ObjectMaterial::Food:
                return "Food";
            case ObjectMaterial::Wood:
                return "Wood";
            case ObjectMaterial::Earth:
                return "Earth";
            case ObjectMaterial::Stone:
                return "Stone";
            case ObjectMaterial::Fire:
                return "Fire";
            case ObjectMaterial::Water:
                return "Water";
            case ObjectMaterial::Metal:
                return "Metal";
            case ObjectMaterial::Gas:
                return "Gas";
            case ObjectMaterial::Plastic:
                return "Plastic";
            case ObjectMaterial::Fabric:
                return "Fabric";
            case ObjectMaterial::Glass:
                return "Glass";
            case ObjectMaterial::Starite:
                return "Starite";
            default:
                return "";
        }
    }

    struct ObjectPhysicsOptions {
        bool is_waterproof : 1;
        bool can_attach : 1;
    };
    static_assert(sizeof(ObjectPhysicsOptions) == sizeof(u8));

    enum class ObjectFireInteraction : u8 {
        Material = 0,
        NoDamage = 1,
        ExplodeSmall = 2,
        ExplodeNormal = 3,
        ExplodeBig = 4,
        ExplodeAuto = 5,
        Damage = 6,
        SuperExplode = 7
    };

    inline std::string FormatObjectFireInteraction(const ObjectFireInteraction interaction) {
        switch(interaction) {
            case ObjectFireInteraction::Material:
                return "Material";
            case ObjectFireInteraction::NoDamage:
                return "NoDamage";
            case ObjectFireInteraction::ExplodeSmall:
                return "ExplodeSmall";
            case ObjectFireInteraction::ExplodeNormal:
                return "ExplodeNormal";
            case ObjectFireInteraction::ExplodeBig:
                return "ExplodeBig";
            case ObjectFireInteraction::ExplodeAuto:
                return "ExplodeAuto";
            case ObjectFireInteraction::Damage:
                return "Damage";
            case ObjectFireInteraction::SuperExplode:
                return "SuperExplode";
            default:
                return "";
        }
    }

    struct ObjectPhysicsModule {
        ObjectPhysicsCombiner combiner;
        ObjectMaterial material;
        u8 mass;
        s16 integrity; // HP?
        u8 inertia;
        ObjectFireInteraction fire_interaction;
        u8 buoyancy_factor;
        ObjectPhysicsOptions options;
    };

    struct ObjectTemperatureModule {
        u8 temperature;
        u8 melting_point;
        u8 gas_point;
    };

    struct ObjectTriggersActionsModule {
        std::vector<TriggerAction> triggers_actions;
    };

    //////////////////////////////////////

    enum class FrameType : u8 {
        Main = 0,
        Box = 1,
        Circle = 2,
        Polygon = 3,
        Image = 4,
        TexQuad = 5,
        Ellipse = 6,
        HotSpot = 7,
        Reference = 8,
        SFAnimation = 9,
        Particle = 10,
        Stamp = 11
    };

    inline std::string FormatFrameType(const FrameType type) {
        switch(type) {
            case FrameType::Main:
                return "Main";
            case FrameType::Box:
                return "Box";
            case FrameType::Circle:
                return "Circle";
            case FrameType::Polygon:
                return "Polygon";
            case FrameType::Image:
                return "Image";
            case FrameType::TexQuad:
                return "TexQuad";
            case FrameType::Ellipse:
                return "Ellipse";
            case FrameType::HotSpot:
                return "HotSpot";
            case FrameType::Reference:
                return "Reference";
            case FrameType::SFAnimation:
                return "SFAnimation";
            case FrameType::Particle:
                return "Particle";
            case FrameType::Stamp:
                return "Stamp";
            default:
                return "";
        }
    }

    struct ObjectFrame;

    struct MainFrameEntry {
        std::vector<ObjectFrame> children;
    };

    struct FieldType {
        bool has_force : 1;
        bool has_temperature : 1;
        bool has_water : 1;
        bool has_damage : 1;
    };
    static_assert(sizeof(FieldType) == sizeof(u8));

    enum class ForceZoneFalloff : u8 {
        Constant = 0,
        Linear = 1,
        LinearInverse = 2,
        Quadratic = 3,
        QuadraticInverse = 4,
        Quicksand = 5
    };

    inline std::string FormatForceZoneFalloff(const ForceZoneFalloff falloff) {
        switch(falloff) {
            case ForceZoneFalloff::Constant:
                return "Constant";
            case ForceZoneFalloff::Linear:
                return "Linear";
            case ForceZoneFalloff::LinearInverse:
                return "LinearInverse";
            case ForceZoneFalloff::Quadratic:
                return "Quadratic";
            case ForceZoneFalloff::QuadraticInverse:
                return "QuadraticInverse";
            case ForceZoneFalloff::Quicksand:
                return "Quicksand";
            default:
                return "";
        }
    }

    struct ForceFieldOptions {
        ForceZoneFalloff falloff_type : 7;
        bool magnet : 1;
    };
    static_assert(sizeof(ForceFieldOptions) == sizeof(u8));

    struct ForceFieldData {
        u8 center_force;
        ForceFieldOptions options;
        u8 damping;
        u8 force_x;
        u8 force_y;
        Filter filter;
    };

    struct TemperatureFieldData {
        s32 temperature;
    };

    enum class WaterZoneType : u8 {
        Water = 0,
        Lava = 1,
        Quicksand = 2
    };

    inline std::string FormatWaterZoneType(const WaterZoneType type) {
        switch(type) {
            case WaterZoneType::Water:
                return "Water";
            case WaterZoneType::Lava:
                return "Lava";
            case WaterZoneType::Quicksand:
                return "Quicksand";
            default:
                return "";
        }
    }

    struct WaterFieldData {
        WaterZoneType water_type;
    };

    struct DamageFieldData {
        u8 collide_damage;
        u8 dps;
        u8 knockback;
    };

    struct BoxFrameEntry {
        FieldType type;

        ForceFieldData force;
        TemperatureFieldData temperature;
        WaterFieldData water;
        DamageFieldData damage;

        fx32 width;
        fx32 height;

        std::vector<ObjectFrame> children;
    };

    struct CircleFrameEntry {
        FieldType type;

        ForceFieldData force;
        TemperatureFieldData temperature;
        DamageFieldData damage;

        fx32 radius;
        u8 surface_force_factor;

        std::vector<ObjectFrame> children;
    };

    struct PolygonFrameEntry {
        std::vector<std::pair<fx32, fx32>> poly_points;
        std::vector<u8> surface_force_factors;
        bool top_collision_only;

        std::vector<ObjectFrame> children;
    };

    enum class Limb : u8 {
        Body = 0,
        Head = 1,
        LeftArm = 2,
        RightArm = 3,
        LeftLeg = 4,
        RightLeg = 5,
        Count
    };

    inline std::string FormatLimb(const Limb limb) {
        switch(limb) {
            case Limb::Body:
                return "Body";
            case Limb::Head:
                return "Head";
            case Limb::LeftArm:
                return "LeftArm";
            case Limb::RightArm:
                return "RightArm";
            case Limb::LeftLeg:
                return "LeftLeg";
            case Limb::RightLeg:
                return "RightLeg";
            default:
                return "";
        }
    }

    struct ImageFrameEntry {
        u16 tex_file_id;
        u16 mask_id;
        std::vector<u8> display_list_data;
        u8 limb_indices[static_cast<size_t>(Limb::Count)]; 

        std::vector<ObjectFrame> children;
    };

    struct TexQuadFrameEntry {
        BodyPart body_part;
        u16 z_order;
        std::pair<fx32, fx32> spawn_pos_vecs[8];

        std::vector<ObjectFrame> children;
    };

    struct EllipseFrameEntry {
        fx32 width;
        fx32 height;
    
        std::vector<ObjectFrame> children;    
    };

    struct HotSpotFrameEntryOptions {
        HotSpotType type : 7;
        bool enabled : 1;
    };
    static_assert(sizeof(HotSpotFrameEntryOptions) == sizeof(u8));

    enum class SaddleSorting : u8 {
        ZBack = 0,
        ZSort = 1,
        ZFront = 2
    };

    inline std::string FormatSaddleSorting(const SaddleSorting sorting) {
        switch(sorting) {
            case SaddleSorting::ZBack:
                return "ZBack";
            case SaddleSorting::ZSort:
                return "ZSort";
            case SaddleSorting::ZFront:
                return "ZFront";
            default:
                return "";
        }
    }

    struct HotSpotSaddleData {
        Animation anim;
        bool is_control_spot;
        SaddleSorting sorting;
        bool can_knock_off;
        Filter filter;
        bool has_pre_mounted_object;
        u16 pre_mounted_obj_id;
    };

    struct HotSpotSaddleSnapData {
        Filter filter;
    };

    struct HotSpotEquipData {
        EquipLocation location;
        Filter filter;
        bool has_pre_equipped_object;
        u16 pre_equipped_obj_file_id;
    };

    struct HotSpotSplitData {
        u16 obj_id_a;
        fx32 split_a_x;
        fx32 split_a_y;
        fx32 split_a_rot;
        u16 obj_id_b;
        fx32 split_b_x;
        fx32 split_b_y;
        fx32 split_b_rot;
    };

    enum class LightShape : u8 {
        ShapeCircle64 = 0,
        ShapeCircle128 = 1,
        ShapeOval = 2,
        PolygonCone64 = 3,
        PolygonCone128 = 4
    };

    inline std::string FormatLightShape(const LightShape shape) {
        switch(shape) {
            case LightShape::ShapeCircle64:
                return "ShapeCircle64";
            case LightShape::ShapeCircle128:
                return "ShapeCircle128";
            case LightShape::ShapeOval:
                return "ShapeOval";
            case LightShape::PolygonCone64:
                return "PolygonCone64";
            case LightShape::PolygonCone128:
                return "PolygonCone128";
            default:
                return "";
        }
    }

    struct HotSpotLightData {
        LightShape shape;
    };

    struct HotSpotEmitterData {
        fx32 emit_x;
        fx32 emit_y;
        fx32 angle;
        s32 spawn_interval;
        fx32 emit_speed;
        bool scatter_shot;
        u8 spawn_count;
        bool apply_gravity;
        bool obj_is_particle;
        u16 emit_object;
        EmitterLabel label;
    };

    enum class FireEffectSize : u8 {
        Tiny = 0,
        Small = 1,
        Normal = 2,
        Medium = 3,
        Large = 4,
        Auto = 5
    };

    inline std::string FormatFireEffectSize(const FireEffectSize size) {
        switch(size) {
            case FireEffectSize::Tiny:
                return "Tiny";
            case FireEffectSize::Small:
                return "Small";
            case FireEffectSize::Normal:
                return "Normal";
            case FireEffectSize::Medium:
                return "Medium";
            case FireEffectSize::Large:
                return "Large";
            case FireEffectSize::Auto:
                return "Auto";
            default:
                return "";
        }
    }

    struct HotSpotFireData {
        FireEffectSize fire_size;
        bool enabled;
    };

    struct JointRevoluteData {
        bool is_motor;
        u8 auto_torque;
        u16 ref_obj_id;
        fx32 part_x;
        fx32 part_y;
        fx32 part_rot;
    };

    struct JointRotationalSpringData {
        u8 stiffness;
        u16 ref_obj_id;
        fx32 part_x;
        fx32 part_y;
        fx32 part_rot;
    };

    struct HotSpotDiggerData {
        u16 radius;
    };
    
    struct HotSpotFrameEntry {
        HotSpotFrameEntryOptions options;

        HotSpotSaddleData saddle;
        HotSpotSaddleSnapData saddle_snap;
        HotSpotEquipData equip;
        HotSpotSplitData split;
        HotSpotLightData light;
        HotSpotEmitterData emitter;
        HotSpotFireData fire;
        JointRevoluteData joint_revolute;
        JointRotationalSpringData joint_rotational_spring;
        HotSpotDiggerData digger;

        std::vector<ObjectFrame> children;
    };

    struct ReferenceFrameEntry {
        u16 part_id_obj_file_id;

        std::vector<ObjectFrame> children;
    };

    struct SFAnimationFrameEntry {
        u16 sprite_id;
        u8 animation_idx;
        u8 z_order;
        fx32 speed;
        bool disable_anim;
        u16 sprite_file_id;

        std::vector<ObjectFrame> children;
    };

    struct StampFrameEntry {
        u16 sprite_id;
        fx32 scale;
        fx32 z_order;
        bool flipped;
        bool has_spawn_pos;
        std::pair<fx32, fx32> spawn_pos_vecs[8];

        std::vector<ObjectFrame> children;
    };

    struct ObjectFrame {
        FrameType type;
        fx32 x;
        fx32 y;
        fx32 rot;
        bool enabled;
        
        MainFrameEntry main;
        BoxFrameEntry box;
        CircleFrameEntry circle;
        PolygonFrameEntry polygon;
        ImageFrameEntry image;
        TexQuadFrameEntry tex_quad;
        EllipseFrameEntry ellipse;
        HotSpotFrameEntry hotspot;
        ReferenceFrameEntry reference;
        SFAnimationFrameEntry sf_anim;
        StampFrameEntry stamp;
    };

    struct ObjectFramesModule {
        bool unk;
        u8 physics_shape_count;
        ObjectFrame root;
    };

    enum class AudioTableType : u8 {
        InitAttack = 0,
        Destroyed = 1,
        Consume = 2,
        ObjectOfInterest = 3,
        Use = 4,
        Flee = 5,
        ExtendedIdle = 6,
        Steal = 7,
        Happy = 8,
        Sick = 9,
        Sleepy = 10,
        ActiveIdle = 11,
        FireProjectile = 12,
        UsedOrUsedEquipped = 13,
        Activated = 14,
        Deactivated = 15,
        Mount = 16,
        Unmount = 17,
        Count
    };

    inline std::string FormatAudioTableType(const AudioTableType type) {
        switch(type) {
            case AudioTableType::InitAttack:
                return "InitAttack";
            case AudioTableType::Destroyed:
                return "Destroyed";
            case AudioTableType::Consume:
                return "Consume";
            case AudioTableType::ObjectOfInterest:
                return "ObjectOfInterest";
            case AudioTableType::Use:
                return "Use";
            case AudioTableType::Flee:
                return "Flee";
            case AudioTableType::ExtendedIdle:
                return "ExtendedIdle";
            case AudioTableType::Steal:
                return "Steal";
            case AudioTableType::Happy:
                return "Happy";
            case AudioTableType::Sick:
                return "Sick";
            case AudioTableType::Sleepy:
                return "Sleepy";
            case AudioTableType::ActiveIdle:
                return "ActiveIdle";
            case AudioTableType::FireProjectile:
                return "FireProjectile";
            case AudioTableType::UsedOrUsedEquipped:
                return "UsedOrUsedEquipped";
            case AudioTableType::Activated:
                return "Activated";
            case AudioTableType::Deactivated:
                return "Deactivated";
            case AudioTableType::Mount:
                return "Mount";
            case AudioTableType::Unmount:
                return "Unmount";
            default:
                return "";
        }
    }

    struct ObjectAudioSlot {
        u16 group_id;
        u16 seqarc_id;
        u16 seq_id;
        SoundAttribute attr;
    };
    
    struct ObjectAudioModule {
        std::optional<ObjectAudioSlot> audio_slots[static_cast<size_t>(AudioTableType::Count)];
    };

    struct ObjectAttackOptions {
        u32 file_id : 31;
        bool has_notes : 1;
    };
    static_assert(sizeof(ObjectAttackOptions) == sizeof(u32));

    struct ObjectAttackNotes {
        u16 action;
        u16 to;
        u16 from;
    };

    struct ObjectAttack {
        ObjectAttackOptions options;
        ObjectAttackNotes notes;
    };

    struct ObjectAttackModule {
        bool valid;
        ObjectAttack attacks[static_cast<size_t>(Animation::Count)];
        u16 attack_anim_len;
    };

    struct Object {
        ObjectHeader header;
        ObjectGenericModule generic;
        ObjectMovementModule movement;
        ObjectAiModule ai;
        ObjectContainerModule container;
        ObjectElectricityModule electricity;
        ObjectPlacementModule placement;
        ObjectPhysicsModule physics;
        ObjectTemperatureModule temperature;
        ObjectTriggersActionsModule triggers_actions;
        ObjectFramesModule frames;
        ObjectAudioModule audio;
        ObjectAttackModule attack;
    };

}
