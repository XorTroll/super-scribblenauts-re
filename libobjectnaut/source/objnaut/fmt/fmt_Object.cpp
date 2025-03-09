#include <objnaut/fmt/fmt_Object.hpp>

namespace objnaut::fmt {

    namespace {

        Result ReadFilter(fs::File &rf, Filter &out_filter) {
            u8 filter_count;
            TWL_R_TRY(rf.Read(filter_count));
            out_filter.entries.clear();
            out_filter.entries.reserve(filter_count);
            for(u32 i = 0; i < filter_count; i++) {
                auto &entry = out_filter.entries.emplace_back();
                TWL_R_TRY(rf.Read(entry.exclude));
                TWL_R_TRY(rf.Read(entry.obj_category_id));
                TWL_R_TRY(rf.Read(entry.obj_subcategory_id_1));
                TWL_R_TRY(rf.Read(entry.obj_subcategory_id_2));
                TWL_R_TRY(rf.Read(entry.obj_id));
                TWL_R_TRY(rf.Read(entry.adj_category_id));
                TWL_R_TRY(rf.Read(entry.adj_subcategory_id));
                TWL_R_TRY(rf.Read(entry.adj_id));
            }

            TWL_R_TRY(rf.Read(out_filter.stage_object_entity_id));

            TWL_R_SUCCEED();
        }

        Result ReadAtrReps(fs::File &rf, std::vector<AiAtrRep> &out_atr_reps) {
            u8 count;
            TWL_R_TRY(rf.Read(count));

            out_atr_reps.clear();
            out_atr_reps.reserve(count);
            for(u32 i = 0; i < count; i++) {
                auto &atr_rep = out_atr_reps.emplace_back();
                TWL_R_TRY(rf.Read(atr_rep.options));

                if(atr_rep.options.has_custom_emote) {
                    AiEmoteType emote;
                    TWL_R_TRY(rf.Read(emote));

                    atr_rep.custom_emote = emote;
                }
                else {
                    atr_rep.custom_emote = {};
                }

                TWL_R_TRY(rf.Read(atr_rep.obj_category_id));
                TWL_R_TRY(rf.Read(atr_rep.obj_subcategory_id_1));
                TWL_R_TRY(rf.Read(atr_rep.obj_subcategory_id_2));
                TWL_R_TRY(rf.Read(atr_rep.obj_id));
                TWL_R_TRY(rf.Read(atr_rep.adj_category_id));
                TWL_R_TRY(rf.Read(atr_rep.adj_subcategory_id));
                TWL_R_TRY(rf.Read(atr_rep.adj_id));

                if(atr_rep.options.mode == AtrRepMode::UseToolUse) {
                    TWL_R_TRY(ReadFilter(rf, atr_rep.filter));
                }
            }

            TWL_R_SUCCEED();
        }
        
        Result ReadModAtrReps(fs::File &rf, std::vector<ModAiAtrRep> &out_atr_reps) {
            u8 count;
            TWL_R_TRY(rf.Read(count));

            out_atr_reps.clear();
            out_atr_reps.reserve(count);
            for(u32 i = 0; i < count; i++) {
                auto &atr_rep = out_atr_reps.emplace_back();
                TWL_R_TRY(rf.Read(atr_rep.insert_point));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.options));

                if(atr_rep.atr_rep.options.has_custom_emote) {
                    AiEmoteType emote;
                    TWL_R_TRY(rf.Read(emote));

                    atr_rep.atr_rep.custom_emote = emote;
                }
                else {
                    atr_rep.atr_rep.custom_emote = {};
                }

                TWL_R_TRY(rf.Read(atr_rep.atr_rep.obj_category_id));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.obj_subcategory_id_1));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.obj_subcategory_id_2));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.obj_id));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.adj_category_id));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.adj_subcategory_id));
                TWL_R_TRY(rf.Read(atr_rep.atr_rep.adj_id));

                if(atr_rep.atr_rep.options.mode == AtrRepMode::UseToolUse) {
                    TWL_R_TRY(ReadFilter(rf, atr_rep.atr_rep.filter));
                }
            }

            TWL_R_SUCCEED();
        }

        inline Result ReadActionTargetData(fs::File &rf, ActionTargetData &out_data) {
            TWL_R_TRY(rf.Read(out_data.target));
            if(out_data.target == ActionTarget::StageEntity) {
                TWL_R_TRY(rf.Read(out_data.target_stage_entity));
            }
            else {
                out_data.target_stage_entity = UINT32_MAX;
            }

            TWL_R_SUCCEED();
        }

        Result ReadAction(fs::File &rf, ActionEntry &out_action) {
            TWL_R_TRY(rf.Read(out_action.type));

            switch(out_action.type) {
                case ActionType::SpawnObject: {
                    TWL_R_TRY(rf.Read(out_action.spawn_obj.is_particle));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj.spawn_obj_file_id));

                    if(!out_action.spawn_obj.is_particle) {
                        TWL_R_TRY(rf.Read(out_action.spawn_obj.inherit_adjs_from_parent));

                        u8 adj_count;
                        TWL_R_TRY(rf.Read(adj_count));
                        out_action.spawn_obj.adjs.clear();
                        out_action.spawn_obj.adjs.reserve(adj_count);
                        for(u32 i = 0; i < adj_count; i++) {
                            u16 adj_id;
                            TWL_R_TRY(rf.Read(adj_id));
                            out_action.spawn_obj.adjs.push_back(adj_id);
                        }
                    }

                    TWL_R_TRY(rf.Read(out_action.spawn_obj.hotspot_idx));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj.options));
                    break;
                }
                case ActionType::EnableShape: {
                    TWL_R_TRY(rf.Read(out_action.enable_shape.index));
                    TWL_R_TRY(rf.Read(out_action.enable_shape.toggle));
                    break;
                }
                case ActionType::Destroy: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.destroy.target));
                    TWL_R_TRY(rf.Read(out_action.destroy.options));
                    break;
                }
                case ActionType::PlaySfx: {
                    TWL_R_TRY(rf.Read(out_action.play_sfx.group_id));
                    TWL_R_TRY(rf.Read(out_action.play_sfx.seq_arc_or_music_id));
                    TWL_R_TRY(rf.Read(out_action.play_sfx.sfx_id));
                    TWL_R_TRY(rf.Read(out_action.play_sfx.sound_attr));

                    u8 filter_count;
                    TWL_R_TRY(rf.Read(filter_count));
                    out_action.play_sfx.filters.clear();
                    out_action.play_sfx.filters.reserve(filter_count);
                    for(u32 i = 0; i < filter_count; i++) {
                        auto &filter = out_action.play_sfx.filters.emplace_back();
                        TWL_R_TRY(rf.Read(filter.attr));
                        TWL_R_TRY(rf.Read(filter.obj_category_id));
                        TWL_R_TRY(rf.Read(filter.obj_subcategory_id_1));
                        TWL_R_TRY(rf.Read(filter.obj_subcategory_id_2));
                        TWL_R_TRY(rf.Read(filter.obj_id));
                    }
                    break;
                }
                case ActionType::Activate:
                case ActionType::Deactivate:
                case ActionType::Toggle: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.activate_deactivate_toggle.target));
                    break;
                }
                case ActionType::ApplyForce: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.apply_force.target));
                    TWL_R_TRY(rf.Read(out_action.apply_force.force_x));
                    TWL_R_TRY(rf.Read(out_action.apply_force.force_y));
                    TWL_R_TRY(rf.Read(out_action.apply_force.torque));
                    TWL_R_TRY(rf.Read(out_action.apply_force.not_absolute_force));
                    break;
                }
                case ActionType::ModifyAiState: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.modify_ai_state.target));
                    TWL_R_TRY(rf.Read(out_action.modify_ai_state.mood));
                    break;
                }
                case ActionType::ModifyAtrRepList: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.modify_atr_rep_list.target));
                
                    TWL_R_TRY(ReadModAtrReps(rf, out_action.modify_atr_rep_list.normal));

                    u8 tag;
                    TWL_R_TRY(rf.Read(tag));
                    if(tag != AtrRepListModuleTag) {
                        TWL_R_FAIL(ResultObjectModifyAtrRepListTagMismatch);
                    }

                    TWL_R_TRY(ReadModAtrReps(rf, out_action.modify_atr_rep_list.exclude));
                    break;
                }
                case ActionType::SwapObject: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.swap_obj.target));
                    TWL_R_TRY(rf.Read(out_action.swap_obj.swap_obj_file_id));
                    TWL_R_TRY(rf.Read(out_action.swap_obj.options));

                    u8 adj_count;
                    TWL_R_TRY(rf.Read(adj_count));
                    out_action.swap_obj.adjs.clear();
                    out_action.swap_obj.adjs.reserve(adj_count);
                    for(u32 i = 0; i < adj_count; i++) {
                        u16 adj_id;
                        TWL_R_TRY(rf.Read(adj_id));
                        out_action.swap_obj.adjs.push_back(adj_id);
                    }
                    break;
                }
                case ActionType::MoveTo: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.move_to.target));
                    TWL_R_TRY(rf.Read(out_action.move_to.target_x));
                    TWL_R_TRY(rf.Read(out_action.move_to.target_y));
                    TWL_R_TRY(rf.Read(out_action.move_to.frame_count));
                    break;
                }
                case ActionType::MoveRelative: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.move_relative.target));
                    TWL_R_TRY(rf.Read(out_action.move_relative.delta_x));
                    TWL_R_TRY(rf.Read(out_action.move_relative.delta_y));
                    TWL_R_TRY(rf.Read(out_action.move_relative.frame_count));
                    break;
                }
                case ActionType::AttachTo: {
                    TWL_R_TRY(rf.Read(out_action.attach_to.entity_id_a));
                    TWL_R_TRY(rf.Read(out_action.attach_to.unused_a));
                    TWL_R_TRY(rf.Read(out_action.attach_to.load_new_object));
                    TWL_R_TRY(rf.Read(out_action.attach_to.entity_id_b));
                    TWL_R_TRY(rf.Read(out_action.attach_to.unused_b));

                    if(out_action.attach_to.load_new_object) {
                        TWL_R_TRY(rf.Read(out_action.attach_to.inherit_adjs_from_parent));

                        u8 adj_count;
                        TWL_R_TRY(rf.Read(adj_count));
                        out_action.attach_to.adjs.clear();
                        out_action.attach_to.adjs.reserve(adj_count);
                        for(u32 i = 0; i < adj_count; i++) {
                            u16 adj_id;
                            TWL_R_TRY(rf.Read(adj_id));
                            out_action.attach_to.adjs.push_back(adj_id);
                        }
                    }

                    TWL_R_TRY(rf.Read(out_action.attach_to.type));
                    break;
                }
                case ActionType::DetachFromAll: {
                    break;
                }
                case ActionType::DealDamage: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.deal_damage.target));
                    TWL_R_TRY(rf.Read(out_action.deal_damage.damage_amount));
                    break;
                }
                case ActionType::Split: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.split.target));
                    TWL_R_TRY(rf.Read(out_action.split.unused));
                    break;
                }
                case ActionType::ThrowAtTarget: {
                    TWL_R_TRY(rf.Read(out_action.throw_at_target.throw_speed_ppf));
                    TWL_R_TRY(rf.Read(out_action.throw_at_target.anim));
                    break;
                }
                case ActionType::FireProjectile: {
                    TWL_R_TRY(rf.Read(out_action.fire_projectile.is_particle));
                    TWL_R_TRY(rf.Read(out_action.fire_projectile.spawn_obj_file_id));
                    TWL_R_TRY(rf.Read(out_action.fire_projectile.hotspot_idx));
                    TWL_R_TRY(rf.Read(out_action.fire_projectile.options));
                    TWL_R_TRY(rf.Read(out_action.fire_projectile.fly_speed_ppf));
                    break;
                }
                case ActionType::SetTemperature: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.set_temperature.target));
                    TWL_R_TRY(rf.Read(out_action.set_temperature.temperature));
                    TWL_R_TRY(rf.Read(out_action.set_temperature.unused));
                    break;
                }
                case ActionType::Animation: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.animation.target));
                    TWL_R_TRY(rf.Read(out_action.animation.new_anim));
                    break;
                }
                case ActionType::Wait: {
                    TWL_R_TRY(rf.Read(out_action.wait.frame_count));
                    break;
                }
                case ActionType::EmptyFill: {
                    TWL_R_TRY(rf.Read(out_action.empty_fill.is_not_empty));
                    break;
                }
                case ActionType::SpawnRandom: {
                    u8 entry_count;
                    TWL_R_TRY(rf.Read(entry_count));
                    out_action.spawn_random.entries.clear();
                    out_action.spawn_random.entries.reserve(entry_count);
                    for(u32 i = 0; i < entry_count; i++) {
                        auto &entry = out_action.spawn_random.entries.emplace_back();
                        TWL_R_TRY(rf.Read(entry.spawn_id));
                        TWL_R_TRY(rf.Read(entry.spawn_adj_id));
                    }

                    TWL_R_TRY(rf.Read(out_action.spawn_random.inherit_adjs_from_parent));
                    TWL_R_TRY(rf.Read(out_action.spawn_random.hotspot_idx));
                    TWL_R_TRY(rf.Read(out_action.spawn_random.options));
                    break;
                }
                case ActionType::SetOnFire: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.set_on_fire.target));
                    TWL_R_TRY(rf.Read(out_action.set_on_fire.set_on_fire));
                    break;
                }
                case ActionType::SetVariable: {
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_action.set_var.value));
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_action.set_var.register_name));
                    break;
                }
                case ActionType::Add: {
                    TWL_R_TRY(rf.Read(out_action.add.amount));
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_action.add.register_name));
                    break;
                }
                case ActionType::EndLevel: {
                    TWL_R_TRY(rf.Read(out_action.end_level.section_id));
                    TWL_R_TRY(rf.Read(out_action.end_level.cinematic_file_id));
                    break;
                }
                case ActionType::SpawnObjectAt: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.spawn_obj_at.target));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj_at.is_particle));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj_at.spawn_obj_file_id));

                    if(!out_action.spawn_obj_at.is_particle) {
                        TWL_R_TRY(rf.Read(out_action.spawn_obj_at.inherit_adjs_from_parent));

                        u8 adj_count;
                        TWL_R_TRY(rf.Read(adj_count));
                        out_action.spawn_obj_at.adjs.clear();
                        out_action.spawn_obj_at.adjs.reserve(adj_count);
                        for(u32 i = 0; i < adj_count; i++) {
                            u16 adj_id;
                            TWL_R_TRY(rf.Read(adj_id));
                            out_action.spawn_obj_at.adjs.push_back(adj_id);
                        }
                    }

                    TWL_R_TRY(rf.Read(out_action.spawn_obj_at.relative_pos_x));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj_at.relative_pos_y));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj_at.options_2));
                    TWL_R_TRY(rf.Read(out_action.spawn_obj_at.options_1));
                    break;
                }
                case ActionType::ShowEmote: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.show_emote.target));
                    TWL_R_TRY(rf.Read(out_action.show_emote.next_emote));
                    break;
                }
                case ActionType::Explode: {
                    TWL_R_TRY(rf.Read(out_action.explode.explosion_size));
                    TWL_R_TRY(rf.Read(out_action.explode.explode_countdown));
                    break;
                }
                case ActionType::ImageSwap: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.image_swap.target));
                    TWL_R_TRY(rf.Read(out_action.image_swap.file_id));
                    break;
                }
                case ActionType::Cinematic: {
                    TWL_R_TRY(rf.Read(out_action.cinematic.section_id));
                    TWL_R_TRY(rf.Read(out_action.cinematic.cinematic_file_id));
                    break;
                }
                case ActionType::ShowNotepad: {
                    TWL_R_TRY(rf.Read(out_action.show_notepad.show));
                    break;
                }
                case ActionType::EncaseInIce: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.encase_in_ice.target));
                    break;
                }
                case ActionType::SetStageObject: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.set_stage_obj.target));
                    TWL_R_TRY(rf.Read(out_action.set_stage_obj.mode));
                    TWL_R_TRY(rf.Read(out_action.set_stage_obj.ignore_stage_object_line_of_sight));
                    TWL_R_TRY(rf.Read(out_action.set_stage_obj.new_target_entity_id));
                    break;
                }
                case ActionType::EnableEntity: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.enable_entity.target));
                    TWL_R_TRY(rf.Read(out_action.enable_entity.enable));
                    break;
                }
                case ActionType::Switch: {
                    TWL_R_TRY(rf.Read(out_action.swtch.type));

                    u8 action_count;
                    TWL_R_TRY(rf.Read(action_count));
                    out_action.swtch.switch_actions.clear();
                    out_action.swtch.switch_actions.reserve(action_count);
                    for(u32 i = 0; i < action_count; i++) {
                        u8 attached_action_count;
                        TWL_R_TRY(rf.Read(attached_action_count));

                        auto &switch_action = out_action.swtch.switch_actions.emplace_back();
                        for(u32 j = 0; j < attached_action_count; j++) {
                            auto &attached_action = switch_action.emplace_back();
                            TWL_R_TRY(ReadAction(rf, attached_action));
                        }
                    }
                    break;
                }
                case ActionType::EnableSFAnim: {
                    TWL_R_TRY(rf.Read(out_action.enable_sf_anim.index));
                    TWL_R_TRY(rf.Read(out_action.enable_sf_anim.toggle));
                    break;
                }
                case ActionType::RotateEntity: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.rotate_entity.target));
                    TWL_R_TRY(rf.Read(out_action.rotate_entity.rot_per_sec));
                    break;
                }
                case ActionType::ApplyAdjective: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.apply_adj.target));
                    TWL_R_TRY(rf.Read(out_action.apply_adj.adj_id));
                    TWL_R_TRY(rf.Read(out_action.apply_adj.suppress_banner));
                    break;
                }
                case ActionType::ShowFeedback: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.show_feedback.target));
                    TWL_R_TRY(rf.Read(out_action.show_feedback.options));
                    TWL_R_TRY(rf.Read(out_action.show_feedback.relative_pos_x));
                    TWL_R_TRY(rf.Read(out_action.show_feedback.relative_pos_y));
                    break;
                }
                case ActionType::Lock: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.lock.target));
                    TWL_R_TRY(ReadFilter(rf, out_action.lock.filter));
                    break;
                }
                case ActionType::NoDrag: {
                    break;
                }
                case ActionType::SetInterruptFlag: {
                    TWL_R_TRY(rf.Read(out_action.set_interrupt_flag.options));
                    TWL_R_TRY(rf.Read(out_action.set_interrupt_flag.parent_trigger_type));
                    break;
                }
                case ActionType::Shock: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.shock.target));
                    break;
                }
                case ActionType::Untouchable: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.untouchable.target));
                    TWL_R_TRY(rf.Read(out_action.untouchable.setting));
                    break;
                }
                case ActionType::ModifyLineOfSight: {
                    TWL_R_TRY(ReadActionTargetData(rf, out_action.modify_line_of_sight.target));
                    TWL_R_TRY(rf.Read(out_action.modify_line_of_sight.line_of_sight));
                    break;
                }
                default: {
                    TWL_R_FAIL(ResultObjectInvalidActionType);
                    break;
                }
            }

            TWL_R_SUCCEED();
        }
        
        Result ReadTriggerAction(fs::File &rf, TriggerAction &out_trigger) {
            TWL_R_TRY(rf.Read(out_trigger.options));

            switch(out_trigger.options.type) {
                case TriggerType::OnCollide: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_collide.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_collide.min_speed_sq));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_collide.use_other_speed));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_collide.only_when_fired));
                    break;
                }
                case TriggerType::OnCreate: {
                    break;
                }
                case TriggerType::OnDestroy: {
                    break;
                }
                case TriggerType::OnConsumed: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_consumed.filter));
                    break;
                }
                case TriggerType::OnActivated:
                case TriggerType::OnDeactivated: {
                    break;
                }
                case TriggerType::OnUsed: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_used.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_used.icon));
                    break;
                }
                case TriggerType::OnUseEquipped: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_use_equipped.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_use_equipped.icon));
                    break;
                }
                case TriggerType::OnVehicleAction: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_vehicle_action.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_vehicle_action.icon));
                    break;
                }
                case TriggerType::OnObjectSwap: {
                    break;
                }
                case TriggerType::OnModifyCharge: {
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_mod_charge.type));
                    break;
                }
                case TriggerType::OnTemperatureSolid:
                case TriggerType::OnTemperatureFluid:
                case TriggerType::OnTemperatureGas: {
                    break;
                }
                case TriggerType::OnEnterLight: {
                    break;
                }
                case TriggerType::OnEnterDarkness: {
                    break;
                }
                case TriggerType::OnEquipped:
                case TriggerType::OnUnequipped: {
                    break;
                }
                case TriggerType::OnAttached:
                case TriggerType::OnDetached: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_attached_detached.filter));
                    break;
                }
                case TriggerType::OnSight: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_sight.filter));
                    break;
                }
                case TriggerType::OnPhysicsRest: {
                    break;
                }
                case TriggerType::OnCatchFire:
                case TriggerType::OnExtinguishFire: {
                    break;
                }
                case TriggerType::ConditionAnd:
                case TriggerType::ConditionOr:
                case TriggerType::ConditionOiAnd: {
                    out_trigger.trigger.condition.cond_a_trigger = std::make_unique<TriggerAction>();
                    out_trigger.trigger.condition.cond_b_trigger = std::make_unique<TriggerAction>();
                    TWL_R_TRY(ReadTriggerAction(rf, *out_trigger.trigger.condition.cond_a_trigger));
                    TWL_R_TRY(ReadTriggerAction(rf, *out_trigger.trigger.condition.cond_b_trigger));
                    break;
                }
                case TriggerType::OnCheckVariable: {
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_check_var.only_check_on_change));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_check_var.comp));
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_trigger.trigger.on_check_var.register_trigger_value));
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_trigger.trigger.on_check_var.register_name));
                    break;
                }
                case TriggerType::OnUpdate: {
                    break;
                }
                case TriggerType::OnContained:
                case TriggerType::OnUncontained: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_contained_uncontained.filter));
                    break;
                }
                case TriggerType::OnObjectAdded: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_obj_added.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_obj_added.options));
                    break;
                }
                case TriggerType::OnAiState: {
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_ai_state.goal_mood));
                    break;
                }
                case TriggerType::OnAiAction: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_ai_action.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_ai_action.action));
                    break;
                }
                case TriggerType::OnObjectCountInArea: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_obj_count_in_area.filter));
                    break;
                }
                case TriggerType::OnDistance: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_distance.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_distance.compare_condition));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_distance.trigger_distance));
                    break;
                }
                case TriggerType::OnVelocity: {
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_velocity.compare_condition));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_velocity.trigger_velocity_sq));
                    break;
                }
                case TriggerType::OnSplit: {
                    break;
                }
                case TriggerType::OnPressed: {
                    break;
                }
                case TriggerType::OnUnpressed: {
                    break;
                }
                case TriggerType::OnAiEquip:
                case TriggerType::OnAiUnequip: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_ai_equip_unequip.filter));
                    break;
                }
                case TriggerType::OnAiConsume: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_ai_consume.filter));
                    break;
                }
                case TriggerType::OnEmpty:
                case TriggerType::OnFill: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_empty_fill.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_empty_fill.unique_objects));
                    break;
                }
                case TriggerType::OnModifyIntegrity: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_modify_integrity.filter));
                    break;
                }
                case TriggerType::OnHearSound: {
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_hear_sound.attr));
                    break;
                }
                case TriggerType::OnMounted:
                case TriggerType::OnUnmounted: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_mounted_unmounted.filter));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.on_mounted_unmounted.control_spot_only));
                    break;
                }
                case TriggerType::TriggerGroup: {
                    TWL_R_TRY(rf.Read(out_trigger.trigger.group.only_check_on_change));
                    TWL_R_TRY(rf.Read(out_trigger.trigger.group.comp));
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_trigger.trigger.group.register_trigger_value));
                    TWL_R_TRY(rf.ReadNullTerminatedString(out_trigger.trigger.group.register_name));

                    u8 group_trigger_count;
                    TWL_R_TRY(rf.Read(group_trigger_count));
                    out_trigger.trigger.group.group_triggers.clear();
                    out_trigger.trigger.group.group_triggers.reserve(group_trigger_count);
                    for(u32 i = 0; i < group_trigger_count; i++) {
                        auto &trigger = out_trigger.trigger.group.group_triggers.emplace_back();
                        TWL_R_TRY(ReadTriggerAction(rf, trigger));
                    }
                    break;
                }
                case TriggerType::OnApplyAdjective:
                case TriggerType::OnKickAdjective: {
                    TWL_R_TRY(ReadFilter(rf, out_trigger.trigger.on_apply_kick_adj.filter));
                    break;
                }
                default: {
                    TWL_R_FAIL(ResultObjectInvalidTriggerType);
                }
            }

            u8 action_count;
            TWL_R_TRY(rf.Read(action_count));
            out_trigger.actions.clear();
            out_trigger.actions.reserve(action_count);
            for(u32 i = 0; i < action_count; i++) {
                auto &action = out_trigger.actions.emplace_back();
                TWL_R_TRY(ReadAction(rf, action));
            }

            TWL_R_SUCCEED();
        }
        
        Result ReadFrame(fs::File &rf, ObjectFrame &out_frame, const bool parent_is_main = false);

        inline Result ReadFrameChildren(fs::File &rf, std::vector<ObjectFrame> &out_children, const bool frame_is_main = false) {
            u8 child_count;
            TWL_R_TRY(rf.Read(child_count));
            out_children.clear();
            out_children.reserve(child_count);
            for(u32 i = 0; i < child_count; i++) {
                auto &child = out_children.emplace_back();
                TWL_R_TRY(ReadFrame(rf, child, frame_is_main));
            }

            TWL_R_SUCCEED();
        }

        Result ReadFrame(fs::File &rf, ObjectFrame &out_frame, const bool parent_is_main) {
            TWL_R_TRY(rf.Read(out_frame.type));
            TWL_R_TRY(rf.Read(out_frame.x));
            TWL_R_TRY(rf.Read(out_frame.y));
            TWL_R_TRY(rf.Read(out_frame.rot));
            TWL_R_TRY(rf.Read(out_frame.enabled));

            switch(out_frame.type) {
                case FrameType::Main: {
                    ReadFrameChildren(rf, out_frame.main.children, true);
                    break;
                }
                case FrameType::Box: {
                    TWL_R_TRY(rf.Read(out_frame.box.type));

                    if(out_frame.box.type.has_force) {
                        TWL_R_TRY(rf.Read(out_frame.box.force.center_force));
                        TWL_R_TRY(rf.Read(out_frame.box.force.options));
                        TWL_R_TRY(rf.Read(out_frame.box.force.damping));
                        TWL_R_TRY(rf.Read(out_frame.box.force.force_x));
                        TWL_R_TRY(rf.Read(out_frame.box.force.force_y));
                        TWL_R_TRY(ReadFilter(rf, out_frame.box.force.filter));
                    }
                    if(out_frame.box.type.has_temperature) {
                        TWL_R_TRY(rf.Read(out_frame.box.temperature.temperature));
                    }
                    if(out_frame.box.type.has_water) {
                        TWL_R_TRY(rf.Read(out_frame.box.water.water_type));
                    }
                    if(out_frame.box.type.has_damage) {
                        TWL_R_TRY(rf.Read(out_frame.box.damage.collide_damage));
                        TWL_R_TRY(rf.Read(out_frame.box.damage.dps));
                        TWL_R_TRY(rf.Read(out_frame.box.damage.knockback));
                    }

                    TWL_R_TRY(rf.Read(out_frame.box.width));
                    TWL_R_TRY(rf.Read(out_frame.box.height));

                    ReadFrameChildren(rf, out_frame.box.children);
                    break;
                }
                case FrameType::Circle: {
                    TWL_R_TRY(rf.Read(out_frame.circle.type));

                    if(out_frame.circle.type.has_force) {
                        TWL_R_TRY(rf.Read(out_frame.circle.force.center_force));
                        TWL_R_TRY(rf.Read(out_frame.circle.force.options));
                        TWL_R_TRY(rf.Read(out_frame.circle.force.damping));
                        TWL_R_TRY(rf.Read(out_frame.circle.force.force_x));
                        TWL_R_TRY(rf.Read(out_frame.circle.force.force_y));
                        TWL_R_TRY(ReadFilter(rf, out_frame.circle.force.filter));
                    }
                    if(out_frame.circle.type.has_temperature) {
                        TWL_R_TRY(rf.Read(out_frame.circle.temperature.temperature));
                    }
                    // Water not supported here, for some reason
                    if(out_frame.circle.type.has_damage) {
                        TWL_R_TRY(rf.Read(out_frame.circle.damage.collide_damage));
                        TWL_R_TRY(rf.Read(out_frame.circle.damage.dps));
                        TWL_R_TRY(rf.Read(out_frame.circle.damage.knockback));
                    }

                    TWL_R_TRY(rf.Read(out_frame.circle.radius));
                    TWL_R_TRY(rf.Read(out_frame.circle.surface_force_factor));

                    ReadFrameChildren(rf, out_frame.circle.children);
                    break;
                }
                case FrameType::Polygon: {
                    u8 poly_point_count;
                    TWL_R_TRY(rf.Read(poly_point_count));
                    out_frame.polygon.poly_points.clear();
                    out_frame.polygon.poly_points.reserve(poly_point_count);
                    for(u32 i = 0; i < poly_point_count; i++) {
                        auto &point = out_frame.polygon.poly_points.emplace_back();
                        TWL_R_TRY(rf.Read(point.first));
                        TWL_R_TRY(rf.Read(point.second));
                    }
                    for(u32 i = 0; i < poly_point_count; i++) {
                        auto &surface_force_factor = out_frame.polygon.surface_force_factors.emplace_back();
                        TWL_R_TRY(rf.Read(surface_force_factor));
                    }

                    TWL_R_TRY(rf.Read(out_frame.polygon.top_collision_only));

                    ReadFrameChildren(rf, out_frame.polygon.children);
                    break;
                }
                case FrameType::Image: {
                    TWL_R_TRY(rf.Read(out_frame.image.tex_file_id));
                    TWL_R_TRY(rf.Read(out_frame.image.mask_id));

                    u16 display_list_size;
                    TWL_R_TRY(rf.Read(display_list_size));
                    if(display_list_size > 0) {
                        auto display_list = new u8[display_list_size]();
                        ScopeGuard display_list_delete([&]() {
                            delete[] display_list;
                        });
                        TWL_R_TRY(rf.ReadBuffer(display_list, display_list_size));
                        out_frame.image.display_list_data.assign(display_list, display_list + display_list_size);

                        for(u32 i = 0; i < static_cast<size_t>(Limb::Count); i++) {
                            TWL_R_TRY(rf.Read(out_frame.image.limb_indices[i]));
                        }
                    }

                    ReadFrameChildren(rf, out_frame.image.children);
                    break;
                }
                case FrameType::TexQuad: {
                    TWL_R_TRY(rf.Read(out_frame.tex_quad.body_part));
                    TWL_R_TRY(rf.Read(out_frame.tex_quad.z_order));

                    for(u32 i = 0; i < 8; i++) {
                        TWL_R_TRY(rf.Read(out_frame.tex_quad.spawn_pos_vecs[i].first));
                        TWL_R_TRY(rf.Read(out_frame.tex_quad.spawn_pos_vecs[i].second));
                    }

                    ReadFrameChildren(rf, out_frame.tex_quad.children);
                    break;
                }
                case FrameType::Ellipse: {
                    TWL_R_TRY(rf.Read(out_frame.ellipse.width));
                    TWL_R_TRY(rf.Read(out_frame.ellipse.height));

                    ReadFrameChildren(rf, out_frame.ellipse.children);
                    break;
                }
                case FrameType::HotSpot: {
                    TWL_R_TRY(rf.Read(out_frame.hotspot.options));

                    switch(out_frame.hotspot.options.type) {
                        case HotSpotType::HotSpotAttach: {
                            break;
                        }
                        case HotSpotType::HotSpotCenterOfGravity: {
                            break;
                        }
                        case HotSpotType::HotSpotSaddle: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.saddle.anim));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.saddle.is_control_spot));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.saddle.sorting));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.saddle.can_knock_off));
                            TWL_R_TRY(ReadFilter(rf, out_frame.hotspot.saddle.filter));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.saddle.has_pre_mounted_object));
                            if(out_frame.hotspot.saddle.has_pre_mounted_object) {
                                TWL_R_TRY(rf.Read(out_frame.hotspot.saddle.pre_mounted_obj_id));
                            }
                            break;
                        }
                        case HotSpotType::HotSpotSaddleSnap: {
                            TWL_R_TRY(ReadFilter(rf, out_frame.hotspot.saddle_snap.filter));
                            break;
                        }
                        case HotSpotType::HotSpotContainerOpening: {
                            break;
                        }
                        case HotSpotType::HotSpotEquip: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.equip.location));
                            TWL_R_TRY(ReadFilter(rf, out_frame.hotspot.equip.filter));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.equip.has_pre_equipped_object));
                            if(out_frame.hotspot.equip.has_pre_equipped_object) {
                                TWL_R_TRY(rf.Read(out_frame.hotspot.equip.pre_equipped_obj_file_id));
                            }
                            break;
                        }
                        case HotSpotType::HotSpotWaypoint: {
                            break;
                        }
                        case HotSpotType::HotSpotSplit: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.obj_id_a));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.split_a_x));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.split_a_y));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.split_a_rot));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.obj_id_b));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.split_b_x));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.split_b_y));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.split.split_b_rot));
                            break;
                        }
                        case HotSpotType::HotSpotLight: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.light.shape));
                            break;
                        }
                        case HotSpotType::HotSpotEmitter: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.emit_x));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.emit_y));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.angle));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.spawn_interval));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.emit_speed));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.scatter_shot));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.spawn_count));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.apply_gravity));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.obj_is_particle));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.emit_object));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.emitter.label));
                            break;
                        }
                        case HotSpotType::HotSpotFire: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.fire.fire_size));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.fire.enabled));
                            break;
                        }
                        case HotSpotType::JointFixed: {
                            break;
                        }
                        case HotSpotType::JointRevolute: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_revolute.is_motor));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_revolute.auto_torque));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_revolute.ref_obj_id));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_revolute.part_x));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_revolute.part_y));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_revolute.part_rot));
                            break;
                        }
                        case HotSpotType::JointRotationalSpring: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_rotational_spring.stiffness));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_rotational_spring.ref_obj_id));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_rotational_spring.part_x));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_rotational_spring.part_y));
                            TWL_R_TRY(rf.Read(out_frame.hotspot.joint_rotational_spring.part_rot));
                            break;
                        }
                        case HotSpotType::HotSpotCombiner: {
                            break;
                        }
                        case HotSpotType::HotSpotPierce: {
                            break;
                        }
                        case HotSpotType::HotSpotSkyPin: {
                            break;
                        }
                        case HotSpotType::HotSpotDigger: {
                            TWL_R_TRY(rf.Read(out_frame.hotspot.digger.radius));
                            break;
                        }
                    }

                    ReadFrameChildren(rf, out_frame.hotspot.children);
                    break;
                }
                case FrameType::Reference: {
                    if(parent_is_main) {
                        TWL_R_TRY(rf.Read(out_frame.reference.part_id_obj_file_id));
                    }

                    ReadFrameChildren(rf, out_frame.reference.children);
                    break;
                }
                case FrameType::SFAnimation: {
                    TWL_R_TRY(rf.Read(out_frame.sf_anim.sprite_id));
                    TWL_R_TRY(rf.Read(out_frame.sf_anim.animation_idx));
                    TWL_R_TRY(rf.Read(out_frame.sf_anim.z_order));
                    TWL_R_TRY(rf.Read(out_frame.sf_anim.speed));
                    TWL_R_TRY(rf.Read(out_frame.sf_anim.disable_anim));
                    TWL_R_TRY(rf.Read(out_frame.sf_anim.sprite_file_id));

                    ReadFrameChildren(rf, out_frame.sf_anim.children);
                    break;
                }
                case FrameType::Particle: {
                    break;
                }       
                case FrameType::Stamp: {
                    TWL_R_TRY(rf.Read(out_frame.stamp.sprite_id));
                    TWL_R_TRY(rf.Read(out_frame.stamp.scale));
                    TWL_R_TRY(rf.Read(out_frame.stamp.z_order));
                    TWL_R_TRY(rf.Read(out_frame.stamp.flipped));
                    
                    TWL_R_TRY(rf.Read(out_frame.stamp.has_spawn_pos));
                    if(out_frame.stamp.has_spawn_pos) {
                        for(u32 i = 0; i < 8; i++) {
                            TWL_R_TRY(rf.Read(out_frame.stamp.spawn_pos_vecs[i].first));
                            TWL_R_TRY(rf.Read(out_frame.stamp.spawn_pos_vecs[i].second));
                        }
                    }

                    ReadFrameChildren(rf, out_frame.stamp.children);
                    break;
                }
                default: {
                    TWL_R_FAIL(ResultObjectInvalidFrameType);
                }
            }

            TWL_R_SUCCEED();
        }

    }

    Result Object::ReadAllFrom(fs::File &rf) {
        TWL_R_TRY(rf.Read(this->header.category_id));
        TWL_R_TRY(rf.Read(this->header.subcategory_id_1));
        TWL_R_TRY(rf.Read(this->header.subcategory_id_2));
        TWL_R_TRY(rf.Read(this->header.obj_id));
        TWL_R_TRY(rf.Read(this->header.width));
        TWL_R_TRY(rf.Read(this->header.height));

        ModuleTag generic_tag;
        TWL_R_TRY(rf.Read(generic_tag));
        if(generic_tag != ModuleTag::Generic) {
            TWL_R_FAIL(ResultObjectGenericTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->generic.options_1));
        TWL_R_TRY(rf.Read(this->generic.options_2));
        TWL_R_TRY(rf.Read(this->generic.rope_length));
        TWL_R_TRY(rf.Read(this->generic.clip_size));
        TWL_R_TRY(rf.Read(this->generic.budget_class));

        if(this->generic.options_1.has_climb_filter) {
            TWL_R_TRY(ReadFilter(rf, this->generic.climb_filter));
        }
        else {
            this->generic.climb_filter = {};
        }

        ModuleTag movement_tag;
        TWL_R_TRY(rf.Read(movement_tag));
        if(movement_tag != ModuleTag::Movement) {
            TWL_R_FAIL(ResultObjectMovementTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->movement.movement_speed));
        TWL_R_TRY(rf.Read(this->movement.jump_height));
        TWL_R_TRY(rf.Read(this->movement.options));
        TWL_R_TRY(rf.Read(this->movement.movement_as_equipment));
        TWL_R_TRY(rf.Read(this->movement.movement_as_ai));
        TWL_R_TRY(rf.Read(this->movement.movement_as_vehicle));

        ModuleTag ai_tag;
        TWL_R_TRY(rf.Read(ai_tag));
        if(ai_tag != ModuleTag::Ai) {
            TWL_R_FAIL(ResultObjectAiTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->ai.ai_mood));
        TWL_R_TRY(rf.Read(this->ai.options));
        TWL_R_TRY(rf.Read(this->ai.sight_distance_tiles));
        TWL_R_TRY(rf.Read(this->ai.visibility_factor));
        TWL_R_TRY(rf.Read(this->ai.react_size_compare));
        TWL_R_TRY(rf.Read(this->ai.attack_damage));

        TWL_R_TRY(ReadAtrReps(rf, this->ai.atr_rep_list.atr_reps));
        TWL_R_TRY(ReadAtrReps(rf, this->ai.atr_rep_list.excludes));

        ModuleTag container_tag;
        TWL_R_TRY(rf.Read(container_tag));
        if(container_tag != ModuleTag::Container) {
            TWL_R_FAIL(ResultObjectContainerTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->container.options));
        TWL_R_TRY(rf.Read(this->container.container_width));
        TWL_R_TRY(rf.Read(this->container.container_height));

        u8 container_obj_count;
        TWL_R_TRY(rf.Read(container_obj_count));
        this->container.contained_obj_file_ids.clear();
        this->container.contained_obj_file_ids.reserve(container_obj_count);
        for(u32 i = 0; i < container_obj_count; i++) {
            u16 obj_file_id;
            TWL_R_TRY(rf.Read(obj_file_id));
            this->container.contained_obj_file_ids.push_back(obj_file_id);
        }

        ModuleTag electricity_tag;
        TWL_R_TRY(rf.Read(electricity_tag));
        if(electricity_tag != ModuleTag::Electricity) {
            TWL_R_FAIL(ResultObjectElectricityTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->electricity.generates_charge));
        TWL_R_TRY(rf.Read(this->electricity.options));

        ModuleTag placement_tag;
        TWL_R_TRY(rf.Read(placement_tag));
        if(placement_tag != ModuleTag::Placement) {
            TWL_R_FAIL(ResultObjectPlacementTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->placement.type));
        TWL_R_TRY(rf.Read(this->placement.options));

        ModuleTag physics_tag;
        TWL_R_TRY(rf.Read(physics_tag));
        if(physics_tag != ModuleTag::Physics) {
            TWL_R_FAIL(ResultObjectPhysicsTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->physics.combiner));
        TWL_R_TRY(rf.Read(this->physics.material));
        TWL_R_TRY(rf.Read(this->physics.mass));
        TWL_R_TRY(rf.Read(this->physics.integrity));
        TWL_R_TRY(rf.Read(this->physics.inertia));
        TWL_R_TRY(rf.Read(this->physics.fire_interaction));
        TWL_R_TRY(rf.Read(this->physics.buoyancy_factor));
        TWL_R_TRY(rf.Read(this->physics.options));

        ModuleTag temperature_tag;
        TWL_R_TRY(rf.Read(temperature_tag));
        if(temperature_tag != ModuleTag::Temperature) {
            TWL_R_FAIL(ResultObjectTemperatureTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->temperature.temperature));
        TWL_R_TRY(rf.Read(this->temperature.melting_point));
        TWL_R_TRY(rf.Read(this->temperature.gas_point));

        ModuleTag triggers_actions_tag;
        TWL_R_TRY(rf.Read(triggers_actions_tag));
        if(triggers_actions_tag != ModuleTag::TriggersActions) {
            TWL_R_FAIL(ResultObjectTriggersActionsTagMismatch);
        }

        u8 trigger_count;
        TWL_R_TRY(rf.Read(trigger_count));
        this->triggers_actions.triggers_actions.clear();
        this->triggers_actions.triggers_actions.reserve(trigger_count);
        for(u32 i = 0; i < trigger_count; i++) {
            auto &trigger = this->triggers_actions.triggers_actions.emplace_back();
            TWL_R_TRY(ReadTriggerAction(rf, trigger));
        }

        ModuleTag frames_tag;
        TWL_R_TRY(rf.Read(frames_tag));
        if(frames_tag != ModuleTag::Frames) {
            TWL_R_FAIL(ResultObjectFramesTagMismatch);
        }

        TWL_R_TRY(rf.Read(this->frames.unk));
        TWL_R_TRY(rf.Read(this->frames.physics_shape_count));
        TWL_R_TRY(ReadFrame(rf, this->frames.root));

        ModuleTag audio_tag;
        TWL_R_TRY(rf.Read(audio_tag));
        if(audio_tag != ModuleTag::Audio) {
            TWL_R_FAIL(ResultObjectAudioTagMismatch);
        }

        u8 audio_slot_count;
        TWL_R_TRY(rf.Read(audio_slot_count));
        
        for(u32 i = 0; i < static_cast<size_t>(AudioTableType::Count); i++) {
            this->audio.audio_slots[i] = {};
        }

        for(u32 i = 0; i < audio_slot_count; i++) {
            u8 slot_idx;
            TWL_R_TRY(rf.Read(slot_idx));

            ObjectAudioSlot slot = {};
            TWL_R_TRY(rf.Read(slot.group_id));
            TWL_R_TRY(rf.Read(slot.seqarc_id));
            TWL_R_TRY(rf.Read(slot.seq_id));
            TWL_R_TRY(rf.Read(slot.attr));

            this->audio.audio_slots[slot_idx] = slot;   
        }

        ModuleTag attack_tag;
        if(rf.Read(attack_tag).IsSuccess()) {
            if(attack_tag != ModuleTag::Attack) {
                TWL_R_FAIL(ResultObjectAttackTagMismatch);
            }

            this->attack.valid = true;

            for(u32 i = 0; i < static_cast<size_t>(Animation::Count); i++) {
                this->attack.attacks[i] = {};

                TWL_R_TRY(rf.Read(this->attack.attacks[i].options));

                if((this->attack.attacks[i].options.file_id != 0x7FFFFFFF) && this->attack.attacks[i].options.has_notes) {
                    TWL_R_TRY(rf.Read(this->attack.attacks[i].notes.action));
                    TWL_R_TRY(rf.Read(this->attack.attacks[i].notes.from));
                    TWL_R_TRY(rf.Read(this->attack.attacks[i].notes.to));
                }
            }

            TWL_R_TRY(rf.Read(this->attack.attack_anim_len));
        }
        else {
            this->attack.valid = false;
        }

        TWL_R_SUCCEED();
    }

    namespace {

        Result WriteFilter(fs::File &wf, const Filter &filter) {
            TWL_R_TRY(wf.Write<u8>(filter.entries.size()));

            for(const auto &entry : filter.entries) {
                TWL_R_TRY(wf.Write(entry.exclude));
                TWL_R_TRY(wf.Write(entry.obj_category_id));
                TWL_R_TRY(wf.Write(entry.obj_subcategory_id_1));
                TWL_R_TRY(wf.Write(entry.obj_subcategory_id_2));
                TWL_R_TRY(wf.Write(entry.obj_id));
                TWL_R_TRY(wf.Write(entry.adj_category_id));
                TWL_R_TRY(wf.Write(entry.adj_subcategory_id));
                TWL_R_TRY(wf.Write(entry.adj_id));
            }

            TWL_R_TRY(wf.Write(filter.stage_object_entity_id));

            TWL_R_SUCCEED();
        }

        Result WriteAtrReps(fs::File &wf, const std::vector<AiAtrRep> &atr_reps) {
            TWL_R_TRY(wf.Write<u8>(atr_reps.size()));

            for(const auto &atr_rep : atr_reps) {
                TWL_R_TRY(wf.Write(atr_rep.options));

                if(atr_rep.options.has_custom_emote) {
                    TWL_R_TRY(wf.Write(atr_rep.custom_emote));
                }

                TWL_R_TRY(wf.Write(atr_rep.obj_category_id));
                TWL_R_TRY(wf.Write(atr_rep.obj_subcategory_id_1));
                TWL_R_TRY(wf.Write(atr_rep.obj_subcategory_id_2));
                TWL_R_TRY(wf.Write(atr_rep.obj_id));
                TWL_R_TRY(wf.Write(atr_rep.adj_category_id));
                TWL_R_TRY(wf.Write(atr_rep.adj_subcategory_id));
                TWL_R_TRY(wf.Write(atr_rep.adj_id));

                if(atr_rep.options.mode == AtrRepMode::UseToolUse) {
                    TWL_R_TRY(WriteFilter(wf, atr_rep.filter));
                }
            }

            TWL_R_SUCCEED();
        }

        Result WriteModAtrReps(fs::File &wf, const std::vector<ModAiAtrRep> &atr_reps) {
            TWL_R_TRY(wf.Write<u8>(atr_reps.size()));

            for(const auto &atr_rep : atr_reps) {
                TWL_R_TRY(wf.Write(atr_rep.insert_point));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.options));

                if(atr_rep.atr_rep.options.has_custom_emote) {
                    TWL_R_TRY(wf.Write(atr_rep.atr_rep.custom_emote));
                }

                TWL_R_TRY(wf.Write(atr_rep.atr_rep.obj_category_id));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.obj_subcategory_id_1));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.obj_subcategory_id_2));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.obj_id));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.adj_category_id));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.adj_subcategory_id));
                TWL_R_TRY(wf.Write(atr_rep.atr_rep.adj_id));

                if(atr_rep.atr_rep.options.mode == AtrRepMode::UseToolUse) {
                    TWL_R_TRY(WriteFilter(wf, atr_rep.atr_rep.filter));
                }
            }

            TWL_R_SUCCEED();
        }

        inline Result WriteActionTargetData(fs::File &wf, const ActionTargetData &data) {
            TWL_R_TRY(wf.Write(data.target));
            if(data.target == ActionTarget::StageEntity) {
                TWL_R_TRY(wf.Write(data.target_stage_entity));
            }

            TWL_R_SUCCEED();
        }

        Result WriteAction(fs::File &wf, const ActionEntry &action) {
            TWL_R_TRY(wf.Write(action.type));
            
            switch(action.type) {
                case ActionType::SpawnObject: {
                    TWL_R_TRY(wf.Write(action.spawn_obj.is_particle));
                    TWL_R_TRY(wf.Write(action.spawn_obj.spawn_obj_file_id));

                    if(!action.spawn_obj.is_particle) {
                        TWL_R_TRY(wf.Write(action.spawn_obj.inherit_adjs_from_parent));

                        TWL_R_TRY(wf.Write<u8>(action.spawn_obj.adjs.size()));
                        for(const auto &adj_id : action.spawn_obj.adjs) {
                            TWL_R_TRY(wf.Write(adj_id));
                        }
                    }

                    TWL_R_TRY(wf.Write(action.spawn_obj.hotspot_idx));
                    TWL_R_TRY(wf.Write(action.spawn_obj.options));
                    break;
                }
                case ActionType::EnableShape: {
                    TWL_R_TRY(wf.Write(action.enable_shape.index));
                    TWL_R_TRY(wf.Write(action.enable_shape.toggle));
                    break;
                }
                case ActionType::Destroy: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.destroy.target));
                    TWL_R_TRY(wf.Write(action.destroy.options));
                    break;
                }
                case ActionType::PlaySfx: {
                    TWL_R_TRY(wf.Write(action.play_sfx.group_id));
                    TWL_R_TRY(wf.Write(action.play_sfx.seq_arc_or_music_id));
                    TWL_R_TRY(wf.Write(action.play_sfx.sfx_id));
                    TWL_R_TRY(wf.Write(action.play_sfx.sound_attr));

                    TWL_R_TRY(wf.Write<u8>(action.play_sfx.filters.size()));
                    for(const auto &filter : action.play_sfx.filters) {
                        TWL_R_TRY(wf.Write(filter.attr));
                        TWL_R_TRY(wf.Write(filter.obj_category_id));
                        TWL_R_TRY(wf.Write(filter.obj_subcategory_id_1));
                        TWL_R_TRY(wf.Write(filter.obj_subcategory_id_2));
                        TWL_R_TRY(wf.Write(filter.obj_id));
                    }
                    break;
                }
                case ActionType::Activate:
                case ActionType::Deactivate:
                case ActionType::Toggle: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.activate_deactivate_toggle.target));
                    break;
                }
                case ActionType::ApplyForce: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.apply_force.target));
                    TWL_R_TRY(wf.Write(action.apply_force.force_x));
                    TWL_R_TRY(wf.Write(action.apply_force.force_y));
                    TWL_R_TRY(wf.Write(action.apply_force.torque));
                    TWL_R_TRY(wf.Write(action.apply_force.not_absolute_force));
                    break;
                }
                case ActionType::ModifyAiState: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.modify_ai_state.target));
                    TWL_R_TRY(wf.Write(action.modify_ai_state.mood));
                    break;
                }
                case ActionType::ModifyAtrRepList: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.modify_atr_rep_list.target));

                    TWL_R_TRY(WriteModAtrReps(wf, action.modify_atr_rep_list.normal));

                    TWL_R_TRY(wf.Write<u8>(13)); // ???

                    TWL_R_TRY(WriteModAtrReps(wf, action.modify_atr_rep_list.exclude));
                    break;
                }
                case ActionType::SwapObject: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.swap_obj.target));
                    TWL_R_TRY(wf.Write(action.swap_obj.swap_obj_file_id));
                    TWL_R_TRY(wf.Write(action.swap_obj.options));

                    TWL_R_TRY(wf.Write<u8>(action.swap_obj.adjs.size()));
                    for(const auto &adj_id : action.swap_obj.adjs) {
                        TWL_R_TRY(wf.Write(adj_id));
                    }
                    break;
                }
                case ActionType::MoveTo: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.move_to.target));
                    TWL_R_TRY(wf.Write(action.move_to.target_x));
                    TWL_R_TRY(wf.Write(action.move_to.target_y));
                    TWL_R_TRY(wf.Write(action.move_to.frame_count));
                    break;
                }
                case ActionType::MoveRelative: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.move_relative.target));
                    TWL_R_TRY(wf.Write(action.move_relative.delta_x));
                    TWL_R_TRY(wf.Write(action.move_relative.delta_y));
                    TWL_R_TRY(wf.Write(action.move_relative.frame_count));
                    break;
                }
                case ActionType::AttachTo: {
                    TWL_R_TRY(wf.Write(action.attach_to.entity_id_a));
                    TWL_R_TRY(wf.Write(action.attach_to.unused_a));
                    TWL_R_TRY(wf.Write(action.attach_to.load_new_object));
                    TWL_R_TRY(wf.Write(action.attach_to.entity_id_b));
                    TWL_R_TRY(wf.Write(action.attach_to.unused_b));

                    if(action.attach_to.load_new_object) {
                        TWL_R_TRY(wf.Write(action.attach_to.inherit_adjs_from_parent));

                        TWL_R_TRY(wf.Write<u8>(action.attach_to.adjs.size()));
                        for(const auto &adj_id : action.attach_to.adjs) {
                            TWL_R_TRY(wf.Write(adj_id));
                        }
                    }

                    TWL_R_TRY(wf.Write(action.attach_to.type));
                    break;
                }
                case ActionType::DetachFromAll: {
                    break;
                }
                case ActionType::DealDamage: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.deal_damage.target));
                    TWL_R_TRY(wf.Write(action.deal_damage.damage_amount));
                    break;
                }
                case ActionType::Split: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.split.target));
                    TWL_R_TRY(wf.Write(action.split.unused));
                    break;
                }
                case ActionType::ThrowAtTarget: {
                    TWL_R_TRY(wf.Write(action.throw_at_target.throw_speed_ppf));
                    TWL_R_TRY(wf.Write(action.throw_at_target.anim));
                    break;
                }
                case ActionType::FireProjectile: {
                    TWL_R_TRY(wf.Write(action.fire_projectile.is_particle));
                    TWL_R_TRY(wf.Write(action.fire_projectile.spawn_obj_file_id));
                    TWL_R_TRY(wf.Write(action.fire_projectile.hotspot_idx));
                    TWL_R_TRY(wf.Write(action.fire_projectile.options));
                    TWL_R_TRY(wf.Write(action.fire_projectile.fly_speed_ppf));
                    break;
                }
                case ActionType::SetTemperature: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.set_temperature.target));
                    TWL_R_TRY(wf.Write(action.set_temperature.temperature));
                    TWL_R_TRY(wf.Write(action.set_temperature.unused));
                    break;
                }
                case ActionType::Animation: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.animation.target));
                    TWL_R_TRY(wf.Write(action.animation.new_anim));
                    break;
                }
                case ActionType::Wait: {
                    TWL_R_TRY(wf.Write(action.wait.frame_count));
                    break;
                }
                case ActionType::EmptyFill: {
                    TWL_R_TRY(wf.Write(action.empty_fill.is_not_empty));
                    break;
                }
                case ActionType::SpawnRandom: {
                    TWL_R_TRY(wf.Write<u8>(action.spawn_random.entries.size()));
                    for(const auto &entry : action.spawn_random.entries) {
                        TWL_R_TRY(wf.Write(entry.spawn_id));
                        TWL_R_TRY(wf.Write(entry.spawn_adj_id));
                    }

                    TWL_R_TRY(wf.Write(action.spawn_random.inherit_adjs_from_parent));
                    TWL_R_TRY(wf.Write(action.spawn_random.hotspot_idx));
                    TWL_R_TRY(wf.Write(action.spawn_random.options));
                    break;
                }
                case ActionType::SetOnFire: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.set_on_fire.target));
                    TWL_R_TRY(wf.Write(action.set_on_fire.set_on_fire));
                    break;
                }
                case ActionType::SetVariable: {
                    TWL_R_TRY(wf.WriteNullTerminatedString(action.set_var.value));
                    TWL_R_TRY(wf.WriteNullTerminatedString(action.set_var.register_name));
                    break;
                }
                case ActionType::Add: {
                    TWL_R_TRY(wf.Write(action.add.amount));
                    TWL_R_TRY(wf.WriteNullTerminatedString(action.add.register_name));
                    break;
                }
                case ActionType::EndLevel: {
                    TWL_R_TRY(wf.Write(action.end_level.section_id));
                    TWL_R_TRY(wf.Write(action.end_level.cinematic_file_id));
                    break;
                }
                case ActionType::SpawnObjectAt: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.spawn_obj_at.target));
                    TWL_R_TRY(wf.Write(action.spawn_obj_at.is_particle));
                    TWL_R_TRY(wf.Write(action.spawn_obj_at.spawn_obj_file_id));

                    if(!action.spawn_obj_at.is_particle) {
                        TWL_R_TRY(wf.Write(action.spawn_obj_at.inherit_adjs_from_parent));

                        TWL_R_TRY(wf.Write<u8>(action.spawn_obj_at.adjs.size()));
                        for(const auto &adj_id : action.spawn_obj_at.adjs) {
                            TWL_R_TRY(wf.Write(adj_id));
                        }
                    }

                    TWL_R_TRY(wf.Write(action.spawn_obj_at.relative_pos_x));
                    TWL_R_TRY(wf.Write(action.spawn_obj_at.relative_pos_y));
                    TWL_R_TRY(wf.Write(action.spawn_obj_at.options_2));
                    TWL_R_TRY(wf.Write(action.spawn_obj_at.options_1));
                    break;
                }
                case ActionType::ShowEmote: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.show_emote.target));
                    TWL_R_TRY(wf.Write(action.show_emote.next_emote));
                    break;
                }
                case ActionType::Explode: {
                    TWL_R_TRY(wf.Write(action.explode.explosion_size));
                    TWL_R_TRY(wf.Write(action.explode.explode_countdown));
                    break;
                }
                case ActionType::ImageSwap: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.image_swap.target));
                    TWL_R_TRY(wf.Write(action.image_swap.file_id));
                    break;
                }
                case ActionType::Cinematic: {
                    TWL_R_TRY(wf.Write(action.cinematic.section_id));
                    TWL_R_TRY(wf.Write(action.cinematic.cinematic_file_id));
                    break;
                }
                case ActionType::ShowNotepad: {
                    TWL_R_TRY(wf.Write(action.show_notepad.show));
                    break;
                }
                case ActionType::EncaseInIce: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.encase_in_ice.target));
                    break;
                }
                case ActionType::SetStageObject: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.set_stage_obj.target));
                    TWL_R_TRY(wf.Write(action.set_stage_obj.mode));
                    TWL_R_TRY(wf.Write(action.set_stage_obj.ignore_stage_object_line_of_sight));
                    TWL_R_TRY(wf.Write(action.set_stage_obj.new_target_entity_id));
                    break;
                }
                case ActionType::EnableEntity: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.enable_entity.target));
                    TWL_R_TRY(wf.Write(action.enable_entity.enable));
                    break;
                }
                case ActionType::Switch: {
                    TWL_R_TRY(wf.Write(action.swtch.type));

                    TWL_R_TRY(wf.Write<u8>(action.swtch.switch_actions.size()));
                    for(const auto &switch_action : action.swtch.switch_actions) {
                        TWL_R_TRY(wf.Write<u8>(switch_action.size()));
                        
                        for(const auto &action : switch_action) {
                            TWL_R_TRY(WriteAction(wf, action));
                        }
                    }
                    break;
                }
                case ActionType::EnableSFAnim: {
                    TWL_R_TRY(wf.Write(action.enable_sf_anim.index));
                    TWL_R_TRY(wf.Write(action.enable_sf_anim.toggle));
                    break;
                }
                case ActionType::RotateEntity: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.rotate_entity.target));
                    TWL_R_TRY(wf.Write(action.rotate_entity.rot_per_sec));
                    break;
                }
                case ActionType::ApplyAdjective: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.apply_adj.target));
                    TWL_R_TRY(wf.Write(action.apply_adj.adj_id));
                    TWL_R_TRY(wf.Write(action.apply_adj.suppress_banner));
                    break;
                }
                case ActionType::ShowFeedback: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.show_feedback.target));
                    TWL_R_TRY(wf.Write(action.show_feedback.options));
                    TWL_R_TRY(wf.Write(action.show_feedback.relative_pos_x));
                    TWL_R_TRY(wf.Write(action.show_feedback.relative_pos_y));
                    break;
                }
                case ActionType::Lock: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.lock.target));
                    TWL_R_TRY(WriteFilter(wf, action.lock.filter));
                    break;
                }
                case ActionType::NoDrag: {
                    break;
                }
                case ActionType::SetInterruptFlag: {
                    TWL_R_TRY(wf.Write(action.set_interrupt_flag.options));
                    TWL_R_TRY(wf.Write(action.set_interrupt_flag.parent_trigger_type));
                    break;
                }
                case ActionType::Shock: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.shock.target));
                    break;
                }
                case ActionType::Untouchable: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.untouchable.target));
                    TWL_R_TRY(wf.Write(action.untouchable.setting));
                    break;
                }
                case ActionType::ModifyLineOfSight: {
                    TWL_R_TRY(WriteActionTargetData(wf, action.modify_line_of_sight.target));
                    TWL_R_TRY(wf.Write(action.modify_line_of_sight.line_of_sight));
                    break;
                }
                default: {
                    TWL_R_FAIL(ResultObjectInvalidActionType);
                    break;
                }
            }

            TWL_R_SUCCEED();
        }

        Result WriteTriggerAction(fs::File &wf, const TriggerAction &trigger) {
            TWL_R_TRY(wf.Write(trigger.options));

            switch(trigger.options.type) {
                case TriggerType::OnCollide: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_collide.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_collide.min_speed_sq));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_collide.use_other_speed));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_collide.only_when_fired));
                    break;
                }
                case TriggerType::OnCreate: {
                    break;
                }
                case TriggerType::OnDestroy: {
                    break;
                }
                case TriggerType::OnConsumed: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_consumed.filter));
                    break;
                }
                case TriggerType::OnActivated:
                case TriggerType::OnDeactivated: {
                    break;
                }
                case TriggerType::OnUsed: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_used.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_used.icon));
                    break;
                }
                case TriggerType::OnUseEquipped: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_use_equipped.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_use_equipped.icon));
                    break;
                }
                case TriggerType::OnVehicleAction: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_vehicle_action.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_vehicle_action.icon));
                    break;
                }
                case TriggerType::OnObjectSwap: {
                    break;
                }
                case TriggerType::OnModifyCharge: {
                    TWL_R_TRY(wf.Write(trigger.trigger.on_mod_charge.type));
                    break;
                }
                case TriggerType::OnTemperatureSolid:
                case TriggerType::OnTemperatureFluid:
                case TriggerType::OnTemperatureGas: {
                    break;
                }
                case TriggerType::OnEnterLight: {
                    break;
                }
                case TriggerType::OnEnterDarkness: {
                    break;
                }
                case TriggerType::OnEquipped:
                case TriggerType::OnUnequipped: {
                    break;
                }
                case TriggerType::OnAttached:
                case TriggerType::OnDetached: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_attached_detached.filter));
                    break;
                }
                case TriggerType::OnSight: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_sight.filter));
                    break;
                }
                case TriggerType::OnPhysicsRest: {
                    break;
                }
                case TriggerType::OnCatchFire:
                case TriggerType::OnExtinguishFire: {
                    break;
                }
                case TriggerType::ConditionAnd:
                case TriggerType::ConditionOr:
                case TriggerType::ConditionOiAnd: {
                    TWL_R_TRY(WriteTriggerAction(wf, *trigger.trigger.condition.cond_a_trigger));
                    TWL_R_TRY(WriteTriggerAction(wf, *trigger.trigger.condition.cond_b_trigger));
                    break;
                }
                case TriggerType::OnCheckVariable: {
                    TWL_R_TRY(wf.Write(trigger.trigger.on_check_var.only_check_on_change));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_check_var.comp));
                    TWL_R_TRY(wf.WriteNullTerminatedString(trigger.trigger.on_check_var.register_trigger_value));
                    TWL_R_TRY(wf.WriteNullTerminatedString(trigger.trigger.on_check_var.register_name));
                    break;
                }
                case TriggerType::OnUpdate: {
                    break;
                }
                case TriggerType::OnContained:
                case TriggerType::OnUncontained: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_contained_uncontained.filter));
                    break;
                }
                case TriggerType::OnObjectAdded: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_obj_added.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_obj_added.options));
                    break;
                }
                case TriggerType::OnAiState: {
                    TWL_R_TRY(wf.Write(trigger.trigger.on_ai_state.goal_mood));
                    break;
                }
                case TriggerType::OnAiAction: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_ai_action.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_ai_action.action));
                    break;
                }
                case TriggerType::OnObjectCountInArea: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_obj_count_in_area.filter));
                    break;
                }
                case TriggerType::OnDistance: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_distance.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_distance.compare_condition));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_distance.trigger_distance));
                    break;
                }
                case TriggerType::OnVelocity: {
                    TWL_R_TRY(wf.Write(trigger.trigger.on_velocity.compare_condition));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_velocity.trigger_velocity_sq));
                    break;
                }
                case TriggerType::OnSplit: {
                    break;
                }
                case TriggerType::OnPressed: {
                    break;
                }
                case TriggerType::OnUnpressed: {
                    break;
                }
                case TriggerType::OnAiEquip:
                case TriggerType::OnAiUnequip: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_ai_equip_unequip.filter));
                    break;
                }
                case TriggerType::OnAiConsume: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_ai_consume.filter));
                    break;
                }
                case TriggerType::OnEmpty:
                case TriggerType::OnFill: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_empty_fill.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_empty_fill.unique_objects));
                    break;
                }
                case TriggerType::OnModifyIntegrity: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_modify_integrity.filter));
                    break;
                }
                case TriggerType::OnHearSound: {
                    TWL_R_TRY(wf.Write(trigger.trigger.on_hear_sound.attr));
                    break;
                }
                case TriggerType::OnMounted:
                case TriggerType::OnUnmounted: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_mounted_unmounted.filter));
                    TWL_R_TRY(wf.Write(trigger.trigger.on_mounted_unmounted.control_spot_only));
                    break;
                }
                case TriggerType::TriggerGroup: {
                    TWL_R_TRY(wf.Write(trigger.trigger.group.only_check_on_change));
                    TWL_R_TRY(wf.Write(trigger.trigger.group.comp));
                    TWL_R_TRY(wf.WriteNullTerminatedString(trigger.trigger.group.register_trigger_value));
                    TWL_R_TRY(wf.WriteNullTerminatedString(trigger.trigger.group.register_name));

                    TWL_R_TRY(wf.Write<u8>(trigger.trigger.group.group_triggers.size()));
                    for(const auto &sub_trigger : trigger.trigger.group.group_triggers) {
                        TWL_R_TRY(WriteTriggerAction(wf, sub_trigger));
                    }
                    break;
                }
                case TriggerType::OnApplyAdjective:
                case TriggerType::OnKickAdjective: {
                    TWL_R_TRY(WriteFilter(wf, trigger.trigger.on_apply_kick_adj.filter));
                    break;
                }
                default: {
                    TWL_R_FAIL(ResultObjectInvalidTriggerType);
                }
            }

            TWL_R_TRY(wf.Write<u8>(trigger.actions.size()));
            for(const auto &action : trigger.actions) {
                TWL_R_TRY(WriteAction(wf, action));
            }

            TWL_R_SUCCEED();
        }

        Result WriteFrame(fs::File &wf, const ObjectFrame &frame, const bool parent_is_main = false);

        inline Result WriteFrameChildren(fs::File &wf, const std::vector<ObjectFrame> &children, const bool frame_is_main = false) {
            TWL_R_TRY(wf.Write<u8>(children.size()));
            for(const auto &child : children) {
                TWL_R_TRY(WriteFrame(wf, child, frame_is_main));
            }

            TWL_R_SUCCEED();
        }

        Result WriteFrame(fs::File &wf, const ObjectFrame &frame, const bool parent_is_main) {
            TWL_R_TRY(wf.Write(frame.type));
            TWL_R_TRY(wf.Write(frame.x));
            TWL_R_TRY(wf.Write(frame.y));
            TWL_R_TRY(wf.Write(frame.rot));
            TWL_R_TRY(wf.Write(frame.enabled));
            

            switch(frame.type) {
                case FrameType::Main: {
                    TWL_R_TRY(WriteFrameChildren(wf, frame.main.children, true));
                    break;
                }
                case FrameType::Box: {
                    TWL_R_TRY(wf.Write(frame.box.type));

                    if(frame.box.type.has_force) {
                        TWL_R_TRY(wf.Write(frame.box.force.center_force));
                        TWL_R_TRY(wf.Write(frame.box.force.options));
                        TWL_R_TRY(wf.Write(frame.box.force.damping));
                        TWL_R_TRY(wf.Write(frame.box.force.force_x));
                        TWL_R_TRY(wf.Write(frame.box.force.force_y));
                        TWL_R_TRY(WriteFilter(wf, frame.box.force.filter));
                    }
                    if(frame.box.type.has_temperature) {
                        TWL_R_TRY(wf.Write(frame.box.temperature.temperature));
                    }
                    if(frame.box.type.has_water) {
                        TWL_R_TRY(wf.Write(frame.box.water.water_type));
                    }
                    if(frame.box.type.has_damage) {
                        TWL_R_TRY(wf.Write(frame.box.damage.collide_damage));
                        TWL_R_TRY(wf.Write(frame.box.damage.dps));
                        TWL_R_TRY(wf.Write(frame.box.damage.knockback));
                    }

                    TWL_R_TRY(wf.Write(frame.box.width));
                    TWL_R_TRY(wf.Write(frame.box.height));
                    
                    TWL_R_TRY(WriteFrameChildren(wf, frame.box.children));
                    break;
                }
                case FrameType::Circle: {
                    TWL_R_TRY(wf.Write(frame.circle.type));
                    
                    if(frame.circle.type.has_force) {
                        TWL_R_TRY(wf.Write(frame.circle.force.center_force));
                        TWL_R_TRY(wf.Write(frame.circle.force.options));
                        TWL_R_TRY(wf.Write(frame.circle.force.damping));
                        TWL_R_TRY(wf.Write(frame.circle.force.force_x));
                        TWL_R_TRY(wf.Write(frame.circle.force.force_y));
                        TWL_R_TRY(WriteFilter(wf, frame.circle.force.filter));
                    }
                    if(frame.circle.type.has_temperature) {
                        TWL_R_TRY(wf.Write(frame.circle.temperature.temperature));
                    }
                    // Water not supported here, for some reason
                    if(frame.circle.type.has_damage) {
                        TWL_R_TRY(wf.Write(frame.circle.damage.collide_damage));
                        TWL_R_TRY(wf.Write(frame.circle.damage.dps));
                        TWL_R_TRY(wf.Write(frame.circle.damage.knockback));
                    }

                    TWL_R_TRY(wf.Write(frame.circle.radius));
                    TWL_R_TRY(wf.Write(frame.circle.surface_force_factor));

                    TWL_R_TRY(WriteFrameChildren(wf, frame.circle.children));
                    break;
                }
                case FrameType::Polygon: {
                    TWL_R_TRY(wf.Write<u8>(frame.polygon.poly_points.size()));
                    for(const auto &point : frame.polygon.poly_points) {
                        TWL_R_TRY(wf.Write(point.first));
                        TWL_R_TRY(wf.Write(point.second));
                    }
                    for(const auto &surface_force_factor : frame.polygon.surface_force_factors) {
                        TWL_R_TRY(wf.Write(surface_force_factor));
                    }

                    TWL_R_TRY(wf.Write(frame.polygon.top_collision_only));

                    TWL_R_TRY(WriteFrameChildren(wf, frame.polygon.children));
                    break;
                }
                case FrameType::Image: {
                    TWL_R_TRY(wf.Write(frame.image.tex_file_id));
                    TWL_R_TRY(wf.Write(frame.image.mask_id));

                    TWL_R_TRY(wf.Write<u16>(frame.image.display_list_data.size()));
                    if(!frame.image.display_list_data.empty()) {
                        TWL_R_TRY(wf.WriteBuffer(frame.image.display_list_data.data(), frame.image.display_list_data.size()));

                        for(u32 i = 0; i < static_cast<size_t>(Limb::Count); i++) {
                            TWL_R_TRY(wf.Write(frame.image.limb_indices[i]));
                        }
                    }

                    TWL_R_TRY(WriteFrameChildren(wf, frame.image.children));
                    break;
                }
                case FrameType::TexQuad: {
                    TWL_R_TRY(wf.Write(frame.tex_quad.body_part));
                    TWL_R_TRY(wf.Write(frame.tex_quad.z_order));

                    for(u32 i = 0; i < 8; i++) {
                        TWL_R_TRY(wf.Write(frame.tex_quad.spawn_pos_vecs[i].first));
                        TWL_R_TRY(wf.Write(frame.tex_quad.spawn_pos_vecs[i].second));
                    }

                    TWL_R_TRY(WriteFrameChildren(wf, frame.tex_quad.children));
                    break;
                }
                case FrameType::Ellipse: {
                    TWL_R_TRY(wf.Write(frame.ellipse.width));
                    TWL_R_TRY(wf.Write(frame.ellipse.height));

                    TWL_R_TRY(WriteFrameChildren(wf, frame.ellipse.children));
                    break;
                }
                case FrameType::HotSpot: {
                    TWL_R_TRY(wf.Write(frame.hotspot.options));

                    switch(frame.hotspot.options.type) {
                        case HotSpotType::HotSpotAttach: {
                            break;
                        }
                        case HotSpotType::HotSpotCenterOfGravity: {
                            break;
                        }
                        case HotSpotType::HotSpotSaddle: {
                            TWL_R_TRY(wf.Write(frame.hotspot.saddle.anim));
                            TWL_R_TRY(wf.Write(frame.hotspot.saddle.is_control_spot));
                            TWL_R_TRY(wf.Write(frame.hotspot.saddle.sorting));
                            TWL_R_TRY(wf.Write(frame.hotspot.saddle.can_knock_off));
                            TWL_R_TRY(WriteFilter(wf, frame.hotspot.saddle.filter));
                            TWL_R_TRY(wf.Write(frame.hotspot.saddle.has_pre_mounted_object));
                            if(frame.hotspot.saddle.has_pre_mounted_object) {
                                TWL_R_TRY(wf.Write(frame.hotspot.saddle.pre_mounted_obj_id));
                            }
                            break;
                        }
                        case HotSpotType::HotSpotSaddleSnap: {
                            TWL_R_TRY(WriteFilter(wf, frame.hotspot.saddle_snap.filter));
                            break;
                        }
                        case HotSpotType::HotSpotContainerOpening: {
                            break;
                        }
                        case HotSpotType::HotSpotEquip: {
                            TWL_R_TRY(wf.Write(frame.hotspot.equip.location));
                            TWL_R_TRY(WriteFilter(wf, frame.hotspot.equip.filter));
                            TWL_R_TRY(wf.Write(frame.hotspot.equip.has_pre_equipped_object));
                            if(frame.hotspot.equip.has_pre_equipped_object) {
                                TWL_R_TRY(wf.Write(frame.hotspot.equip.pre_equipped_obj_file_id));
                            }
                            break;
                        }
                        case HotSpotType::HotSpotWaypoint: {
                            break;
                        }
                        case HotSpotType::HotSpotSplit: {
                            TWL_R_TRY(wf.Write(frame.hotspot.split.obj_id_a));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.split_a_x));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.split_a_y));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.split_a_rot));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.obj_id_b));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.split_b_x));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.split_b_y));
                            TWL_R_TRY(wf.Write(frame.hotspot.split.split_b_rot));
                            break;
                        }
                        case HotSpotType::HotSpotLight: {
                            TWL_R_TRY(wf.Write(frame.hotspot.light.shape));
                            break;
                        }
                        case HotSpotType::HotSpotEmitter: {
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.emit_x));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.emit_y));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.angle));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.spawn_interval));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.emit_speed));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.scatter_shot));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.spawn_count));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.apply_gravity));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.obj_is_particle));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.emit_object));
                            TWL_R_TRY(wf.Write(frame.hotspot.emitter.label));
                            break;
                        }
                        case HotSpotType::HotSpotFire: {
                            TWL_R_TRY(wf.Write(frame.hotspot.fire.fire_size));
                            TWL_R_TRY(wf.Write(frame.hotspot.fire.enabled));
                            break;
                        }
                        case HotSpotType::JointFixed: {
                            break;
                        }
                        case HotSpotType::JointRevolute: {
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_revolute.is_motor));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_revolute.auto_torque));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_revolute.ref_obj_id));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_revolute.part_x));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_revolute.part_y));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_revolute.part_rot));
                            break;
                        }
                        case HotSpotType::JointRotationalSpring: {
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_rotational_spring.stiffness));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_rotational_spring.ref_obj_id));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_rotational_spring.part_x));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_rotational_spring.part_y));
                            TWL_R_TRY(wf.Write(frame.hotspot.joint_rotational_spring.part_rot));
                            break;
                        }
                        case HotSpotType::HotSpotCombiner: {
                            break;
                        }
                        case HotSpotType::HotSpotPierce: {
                            break;
                        }
                        case HotSpotType::HotSpotSkyPin: {
                            break;
                        }
                        case HotSpotType::HotSpotDigger: {
                            TWL_R_TRY(wf.Write(frame.hotspot.digger.radius));
                            break;
                        }
                    }

                    TWL_R_TRY(WriteFrameChildren(wf, frame.hotspot.children));
                    break;
                }
                case FrameType::Reference: {
                    if(parent_is_main) {
                        TWL_R_TRY(wf.Write(frame.reference.part_id_obj_file_id));
                    }

                    TWL_R_TRY(WriteFrameChildren(wf, frame.reference.children));
                    break;
                }
                case FrameType::SFAnimation: {
                    TWL_R_TRY(wf.Write(frame.sf_anim.sprite_id));
                    TWL_R_TRY(wf.Write(frame.sf_anim.animation_idx));
                    TWL_R_TRY(wf.Write(frame.sf_anim.z_order));
                    TWL_R_TRY(wf.Write(frame.sf_anim.speed));
                    TWL_R_TRY(wf.Write(frame.sf_anim.disable_anim));
                    TWL_R_TRY(wf.Write(frame.sf_anim.sprite_file_id));

                    TWL_R_TRY(WriteFrameChildren(wf, frame.sf_anim.children));
                    break;
                }
                case FrameType::Particle: {
                    break;
                }
                case FrameType::Stamp: {
                    TWL_R_TRY(wf.Write(frame.stamp.sprite_id));
                    TWL_R_TRY(wf.Write(frame.stamp.scale));
                    TWL_R_TRY(wf.Write(frame.stamp.z_order));
                    TWL_R_TRY(wf.Write(frame.stamp.flipped));

                    TWL_R_TRY(wf.Write(frame.stamp.has_spawn_pos));
                    if(frame.stamp.has_spawn_pos) {
                        for(u32 i = 0; i < 8; i++) {
                            TWL_R_TRY(wf.Write(frame.stamp.spawn_pos_vecs[i].first));
                            TWL_R_TRY(wf.Write(frame.stamp.spawn_pos_vecs[i].second));
                        }
                    }

                    TWL_R_TRY(WriteFrameChildren(wf, frame.stamp.children));
                    break;
                }
                default: {
                    TWL_R_FAIL(ResultObjectInvalidFrameType);
                }
            }

            TWL_R_SUCCEED();
        }

    }

    Result Object::WriteTo(fs::File &wf) {
        TWL_R_TRY(wf.Write(this->header.category_id));
        TWL_R_TRY(wf.Write(this->header.subcategory_id_1));
        TWL_R_TRY(wf.Write(this->header.subcategory_id_2));
        TWL_R_TRY(wf.Write(this->header.obj_id));
        TWL_R_TRY(wf.Write(this->header.width));
        TWL_R_TRY(wf.Write(this->header.height));

        TWL_R_TRY(wf.Write(ModuleTag::Generic));

        TWL_R_TRY(wf.Write(this->generic.options_1));
        TWL_R_TRY(wf.Write(this->generic.options_2));
        TWL_R_TRY(wf.Write(this->generic.rope_length));
        TWL_R_TRY(wf.Write(this->generic.clip_size));
        TWL_R_TRY(wf.Write(this->generic.budget_class));

        if(this->generic.options_1.has_climb_filter) {
            TWL_R_TRY(WriteFilter(wf, this->generic.climb_filter));
        }

        TWL_R_TRY(wf.Write(ModuleTag::Movement));

        TWL_R_TRY(wf.Write(this->movement.movement_speed));
        TWL_R_TRY(wf.Write(this->movement.jump_height));
        TWL_R_TRY(wf.Write(this->movement.options));
        TWL_R_TRY(wf.Write(this->movement.movement_as_equipment));
        TWL_R_TRY(wf.Write(this->movement.movement_as_ai));
        TWL_R_TRY(wf.Write(this->movement.movement_as_vehicle));

        TWL_R_TRY(wf.Write(ModuleTag::Ai));

        TWL_R_TRY(wf.Write(this->ai.ai_mood));
        TWL_R_TRY(wf.Write(this->ai.options));
        TWL_R_TRY(wf.Write(this->ai.sight_distance_tiles));
        TWL_R_TRY(wf.Write(this->ai.visibility_factor));
        TWL_R_TRY(wf.Write(this->ai.react_size_compare));
        TWL_R_TRY(wf.Write(this->ai.attack_damage));

        TWL_R_TRY(WriteAtrReps(wf, this->ai.atr_rep_list.atr_reps));
        TWL_R_TRY(WriteAtrReps(wf, this->ai.atr_rep_list.excludes));

        TWL_R_TRY(wf.Write(ModuleTag::Container));

        TWL_R_TRY(wf.Write(this->container.options));
        TWL_R_TRY(wf.Write(this->container.container_width));
        TWL_R_TRY(wf.Write(this->container.container_height));

        TWL_R_TRY(wf.Write<u8>(this->container.contained_obj_file_ids.size()));
        for(const auto obj_file_id : this->container.contained_obj_file_ids) {
            TWL_R_TRY(wf.Write(obj_file_id));
        }

        TWL_R_TRY(wf.Write(ModuleTag::Electricity));

        TWL_R_TRY(wf.Write(this->electricity.generates_charge));
        TWL_R_TRY(wf.Write(this->electricity.options));

        TWL_R_TRY(wf.Write(ModuleTag::Placement));
        
        TWL_R_TRY(wf.Write(this->placement.type));
        TWL_R_TRY(wf.Write(this->placement.options));

        TWL_R_TRY(wf.Write(ModuleTag::Physics));

        TWL_R_TRY(wf.Write(this->physics.combiner));
        TWL_R_TRY(wf.Write(this->physics.material));
        TWL_R_TRY(wf.Write(this->physics.mass));
        TWL_R_TRY(wf.Write(this->physics.integrity));
        TWL_R_TRY(wf.Write(this->physics.inertia));
        TWL_R_TRY(wf.Write(this->physics.fire_interaction));
        TWL_R_TRY(wf.Write(this->physics.buoyancy_factor));
        TWL_R_TRY(wf.Write(this->physics.options));

        TWL_R_TRY(wf.Write(ModuleTag::Temperature));

        TWL_R_TRY(wf.Write(this->temperature.temperature));
        TWL_R_TRY(wf.Write(this->temperature.melting_point));
        TWL_R_TRY(wf.Write(this->temperature.gas_point));

        TWL_R_TRY(wf.Write(ModuleTag::TriggersActions));

        TWL_R_TRY(wf.Write<u8>(this->triggers_actions.triggers_actions.size()));
        for(const auto &trigger : this->triggers_actions.triggers_actions) {
            TWL_R_TRY(WriteTriggerAction(wf, trigger));
        }

        TWL_R_TRY(wf.Write(ModuleTag::Frames));

        TWL_R_TRY(wf.Write(this->frames.unk));
        TWL_R_TRY(wf.Write(this->frames.physics_shape_count));
        TWL_R_TRY(WriteFrame(wf, this->frames.root));

        TWL_R_TRY(wf.Write(ModuleTag::Audio));

        u8 audio_slot_count = 0;
        for(const auto &slot : this->audio.audio_slots) {
            if(slot.has_value()) {
                audio_slot_count++;
            }
        }
        TWL_R_TRY(wf.Write(audio_slot_count));

        for(u32 i = 0; i < static_cast<size_t>(AudioTableType::Count); i++) {
            if(this->audio.audio_slots[i].has_value()) {
                const auto &slot = this->audio.audio_slots[i].value();
                TWL_R_TRY(wf.Write<u8>(i));
                TWL_R_TRY(wf.Write(slot.group_id));
                TWL_R_TRY(wf.Write(slot.seqarc_id));
                TWL_R_TRY(wf.Write(slot.seq_id));
                TWL_R_TRY(wf.Write(slot.attr));
            }
        }

        if(this->attack.valid) {
            TWL_R_TRY(wf.Write(ModuleTag::Attack));

            for(const auto &attack : this->attack.attacks) {
                TWL_R_TRY(wf.Write(attack.options));

                if((attack.options.file_id != 0x7FFFFFFF) && attack.options.has_notes) {
                    TWL_R_TRY(wf.Write(attack.notes.action));
                    TWL_R_TRY(wf.Write(attack.notes.from));
                    TWL_R_TRY(wf.Write(attack.notes.to));
                }
            }

            TWL_R_TRY(wf.Write(this->attack.attack_anim_len));
        }

        TWL_R_SUCCEED();
    }

}
