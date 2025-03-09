#include <cli/cli_PrintObject.hpp>

namespace {

    std::string PrefixForIndent(const u32 indent) {
        std::string prefix;
        for(u32 i = 0; i < indent; i++) {
            prefix += "---";
        }
        if(indent > 0) {
            prefix += "> ";
        }
        return prefix;
    }

    void PrintFilter(const std::string &caption, const Filter &filter, const u32 indent = 0) {
        std::cout << PrefixForIndent(indent) << caption << ": " << std::endl;

        for(u32 i = 0; i < filter.entries.size(); i++) {
            const auto &entry = filter.entries[i];
            std::cout << PrefixForIndent(indent + 1) << "Filter[" << i << "]: " << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Exclude: " << std::boolalpha << entry.exclude << std::noboolalpha << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object category ID: " << DefaultNull(entry.obj_category_id, FormatObjectCategoryId) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object subcategory ID 1: " << Mask16(entry.obj_subcategory_id_1) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object subcategory ID 2: " << Mask16(entry.obj_subcategory_id_2) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object ID: " << Mask16(entry.obj_id) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Adjective category ID: " << Mask16(entry.adj_category_id) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Adjective subcategory ID: " << Mask16(entry.adj_subcategory_id) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Adjective ID: " << Mask16(entry.adj_id) << std::endl;
        }
        std::cout << PrefixForIndent(indent + 1) << "StageObject entity ID: " << Mask32(filter.stage_object_entity_id) << std::endl;
    }

    void PrintAtrRepList(const std::string &caption, const std::vector<AiAtrRep> &atr_reps, const u32 indent = 0) {
        std::cout << PrefixForIndent(indent) << caption << ": " << std::endl;

        for(u32 i = 0; i < atr_reps.size(); i++) {
            const auto &atr_rep = atr_reps[i];
            std::cout << PrefixForIndent(indent + 1) << "AtrRep[" << i << "]: " << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Mode: " << FormatAtrRepMode(atr_rep.options.mode) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Only when equipped: " << std::boolalpha << atr_rep.options.only_when_equipped << std::noboolalpha << std::endl;
            if(atr_rep.options.has_custom_emote) {
                std::cout << PrefixForIndent(indent + 2) << "Custom emote: " << FormatAiEmoteType(atr_rep.custom_emote) << std::endl;
            }
            std::cout << PrefixForIndent(indent + 2) << "Object category ID: " << DefaultNull(atr_rep.obj_category_id, FormatObjectCategoryId) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object subcategory ID 1: " << Mask16(atr_rep.obj_subcategory_id_1) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object subcategory ID 2: " << Mask16(atr_rep.obj_subcategory_id_2) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Object ID: " << Mask16(atr_rep.obj_id) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Adjective category ID: " << Mask16(atr_rep.adj_category_id) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Adjective subcategory ID: " << Mask16(atr_rep.adj_subcategory_id) << std::endl;
            std::cout << PrefixForIndent(indent + 2) << "Adjective ID: " << Mask16(atr_rep.adj_id) << std::endl;
            if(atr_rep.options.mode == AtrRepMode::UseToolUse) {
                PrintFilter("Filters", atr_rep.filter, indent + 2);
            }
        }
    }

    inline void PrintTarget(const ActionTargetData &data, const u32 indent = 0) {
        std::cout << PrefixForIndent(indent) << "Target: " << DefaultNull(data.target, FormatActionTarget) << " (stage entity = " << Mask32(data.target_stage_entity) << ")" << std::endl;
    }

    void PrintAction(const ActionEntry &action, const u32 indent = 0) {
        std::cout << PrefixForIndent(indent) << "Action type: " << DefaultNull(action.type, FormatActionType) << std::endl;

        switch(action.type) {
            case ActionType::SpawnObject: {
                std::cout << PrefixForIndent(indent) << "Is particle: " << std::boolalpha << action.spawn_obj.is_particle << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Object ID: " << Mask16(action.spawn_obj.spawn_obj_file_id) << std::endl;
                if(!action.spawn_obj.is_particle) {
                    std::cout << PrefixForIndent(indent) << "Inherit adjs from parent: " << std::boolalpha << action.spawn_obj.inherit_adjs_from_parent << std::noboolalpha << std::endl;

                    std::cout << PrefixForIndent(indent) << "Adjective IDs: ";
                    if(action.spawn_obj.adjs.empty()) {
                        std::cout << "<none>";
                    }
                    for(const auto &id: action.spawn_obj.adjs) {
                        std::cout << id << " ";
                    }
                    std::cout << std::endl;
                }
                
                std::cout << PrefixForIndent(indent) << "Hotspot index: " << (int)action.spawn_obj.hotspot_idx << std::endl;
                std::cout << PrefixForIndent(indent) << "Max objects: " << (int)action.spawn_obj.options.max_objects << std::endl;
                std::cout << PrefixForIndent(indent) << "Stop if no spawn: " << std::boolalpha << action.spawn_obj.options.stop_if_no_spawn << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::EnableShape: {
                std::cout << PrefixForIndent(indent) << "Index: " << (int)action.enable_shape.index << std::endl;
                std::cout << PrefixForIndent(indent) << "Toggle: " << std::boolalpha << action.enable_shape.toggle << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::Destroy: {
                PrintTarget(action.destroy.target, indent);
                std::cout << PrefixForIndent(indent) << "Poof cloud: " << std::boolalpha << action.destroy.options.poof_cloud << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Destroy connected: " << std::boolalpha << action.destroy.options.destroy_connected << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::PlaySfx: {
                std::cout << PrefixForIndent(indent) << "Group ID: " << action.play_sfx.group_id << std::endl;
                std::cout << PrefixForIndent(indent) << "SeqArc / music ID: " << action.play_sfx.seq_arc_or_music_id << std::endl;
                std::cout << PrefixForIndent(indent) << "SFX ID: " << action.play_sfx.sfx_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Sound attribute: " << DefaultNull(action.play_sfx.sound_attr, FormatSoundAttribute) << std::endl;

                std::cout << PrefixForIndent(indent) << "Audio filters: " << std::endl;
                for(u32 i = 0; i < action.play_sfx.filters.size(); i++) {
                    const auto &filter = action.play_sfx.filters[i];
                    std::cout << PrefixForIndent(indent + 1) << "Audio filter[" << i << "]: " << std::endl;
                    std::cout << PrefixForIndent(indent + 2) << "Object category ID: " << DefaultNull(filter.obj_category_id, FormatObjectCategoryId) << std::endl;
                    std::cout << PrefixForIndent(indent + 2) << "Object subcategory ID 1: " << Mask16(filter.obj_subcategory_id_1) << std::endl;
                    std::cout << PrefixForIndent(indent + 2) << "Object subcategory ID 2: " << Mask16(filter.obj_subcategory_id_2) << std::endl;
                    std::cout << PrefixForIndent(indent + 2) << "Object ID: " << Mask16(filter.obj_id) << std::endl;
                }
                break;
            }
            case ActionType::Activate:
            case ActionType::Deactivate:
            case ActionType::Toggle: {
                PrintTarget(action.activate_deactivate_toggle.target, indent);
                break;
            }
            case ActionType::ApplyForce: {
                PrintTarget(action.apply_force.target, indent);
                std::cout << PrefixForIndent(indent) << "Force X: " << action.apply_force.force_x << std::endl;
                std::cout << PrefixForIndent(indent) << "Force Y: " << action.apply_force.force_y << std::endl;
                std::cout << PrefixForIndent(indent) << "Torque: " << action.apply_force.torque << std::endl;
                std::cout << PrefixForIndent(indent) << "Not absolute force: " << std::boolalpha << action.apply_force.not_absolute_force << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::ModifyAiState: {
                PrintTarget(action.modify_ai_state.target, indent);
                std::cout << PrefixForIndent(indent) << "Mood: " << DefaultNull(action.modify_ai_state.mood, FormatAiMood) << std::endl;
                break;
            }
            case ActionType::ModifyAtrRepList: {
                PrintTarget(action.modify_atr_rep_list.target, indent);
                // PrintAtrRepList("Normal atracts/repulse modifiers", action.modify_atr_rep_list.normal, indent);
                // PrintAtrRepList("Exclude atracts/repulse modifiers", action.modify_atr_rep_list.exclude, indent);
                break;
            }
            case ActionType::SwapObject: {
                PrintTarget(action.swap_obj.target, indent);
                std::cout << PrefixForIndent(indent) << "Swap object ID: " << Mask16(action.swap_obj.swap_obj_file_id) << std::endl;
                std::cout << PrefixForIndent(indent) << "Use previous self: " << std::boolalpha << action.swap_obj.options.use_previous_self << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Inherit adjectives from parent: " << std::boolalpha << action.swap_obj.options.inherit_adjs_from_parent << std::noboolalpha << std::endl;

                std::cout << PrefixForIndent(indent) << "Adjective IDs: ";
                if(action.spawn_obj.adjs.empty()) {
                    std::cout << "<none>";
                }
                for(const auto &id: action.swap_obj.adjs) {
                    std::cout << id << " ";
                }
                std::cout << std::endl;
                break;
            }
            case ActionType::MoveTo: {
                PrintTarget(action.move_to.target, indent);
                std::cout << PrefixForIndent(indent) << "Target X: " << action.move_to.target_x << std::endl;
                std::cout << PrefixForIndent(indent) << "Target Y: " << action.move_to.target_y << std::endl;
                std::cout << PrefixForIndent(indent) << "Frame count: " << std::boolalpha << action.move_to.frame_count << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::MoveRelative: {
                PrintTarget(action.move_relative.target, indent);
                std::cout << PrefixForIndent(indent) << "Delta X: " << action.move_relative.delta_x << std::endl;
                std::cout << PrefixForIndent(indent) << "Delta Y: " << action.move_relative.delta_y << std::endl;
                std::cout << PrefixForIndent(indent) << "Frame count: " << std::boolalpha << action.move_relative.frame_count << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::AttachTo: {
                std::cout << PrefixForIndent(indent) << "Entity ID A: " << Mask16(action.attach_to.entity_id_a) << std::endl;
                std::cout << PrefixForIndent(indent) << "Unused A: " <<action.attach_to.unused_a << std::endl;
                std::cout << PrefixForIndent(indent) << "Entity ID B: " << Mask16(action.attach_to.entity_id_b) << std::endl;
                std::cout << PrefixForIndent(indent) << "Unused B: " <<action.attach_to.unused_b << std::endl;
                break;
            }
            case ActionType::DetachFromAll: {
                break;
            }
            case ActionType::DealDamage: {
                PrintTarget(action.deal_damage.target, indent);
                std::cout << PrefixForIndent(indent) << "Damage amount: " << (int)action.deal_damage.damage_amount << std::endl;
                break;
            }
            case ActionType::Split: {
                PrintTarget(action.split.target, indent);
                std::cout << PrefixForIndent(indent) << "Unused: " << (int)action.split.unused << std::endl;
                break;
            }
            case ActionType::ThrowAtTarget: {
                std::cout << PrefixForIndent(indent) << "Throw speed (pixels-per-frame): " << action.throw_at_target.throw_speed_ppf << std::endl;
                std::cout << PrefixForIndent(indent) << "Animation: " << DefaultNull(action.throw_at_target.anim, FormatAnimation) << std::endl;
                break;
            }
            case ActionType::FireProjectile: {
                std::cout << PrefixForIndent(indent) << "Is particle: " << std::boolalpha << action.fire_projectile.is_particle << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Spawn object file ID: " << Mask16(action.fire_projectile.spawn_obj_file_id) << std::endl;
                std::cout << PrefixForIndent(indent) << "Hotspot index: " << (int)action.fire_projectile.hotspot_idx << std::endl;
                std::cout << PrefixForIndent(indent) << "Ignore gravity: " << std::boolalpha << action.fire_projectile.options.ignore_gravity << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Index is label: " << std::boolalpha << action.fire_projectile.options.index_is_label << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Fly speed (pixels-per-frame): " << action.fire_projectile.fly_speed_ppf << std::endl;
                break;
            }
            case ActionType::SetTemperature: {
                PrintTarget(action.set_temperature.target, indent);
                std::cout << PrefixForIndent(indent) << "Temperature: " << (int)action.set_temperature.temperature << std::endl;
                std::cout << PrefixForIndent(indent) << "Unused: " << (int)action.set_temperature.unused << std::endl;
                break;
            }
            case ActionType::Animation: {
                PrintTarget(action.animation.target, indent);
                std::cout << PrefixForIndent(indent) << "New animation: " << DefaultNull(action.animation.new_anim, FormatAnimation) << std::endl;
                break;
            }
            case ActionType::Wait: {
                std::cout << PrefixForIndent(indent) << "Frame count: " << action.wait.frame_count << std::endl;
                break;
            }
            case ActionType::EmptyFill: {
                std::cout << PrefixForIndent(indent) << "Is not empty: " << std::boolalpha << action.empty_fill.is_not_empty << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::SpawnRandom: {
                std::cout << PrefixForIndent(indent) << "Entries:" << std::endl;
                for(u32 i = 0; i < action.spawn_random.entries.size(); i++) {
                    const auto &entry = action.spawn_random.entries[i];
                    std::cout << PrefixForIndent(indent + 1) << "Entry[" << i << "]: " << std::endl;
                    std::cout << PrefixForIndent(indent + 2) << "Spawn object ID: " << Mask16(entry.spawn_id) << std::endl;
                    std::cout << PrefixForIndent(indent + 2) << "Spawn adjetive ID: " << Mask16(entry.spawn_adj_id) << std::endl;
                }

                std::cout << PrefixForIndent(indent) << "Inherit adjectives from parent: " << std::boolalpha << action.spawn_random.inherit_adjs_from_parent << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Hotspot index: " << (int)action.spawn_random.hotspot_idx << std::endl;
                std::cout << PrefixForIndent(indent) << "Max objects: " << (int)action.spawn_random.options.max_objects << std::endl;
                std::cout << PrefixForIndent(indent) << "Stop if no spawn: " << std::boolalpha << action.spawn_random.options.stop_if_no_spawn << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::SetOnFire: {
                PrintTarget(action.set_on_fire.target, indent);
                std::cout << PrefixForIndent(indent) << "Set on fire: " << std::boolalpha << action.set_on_fire.set_on_fire << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::SetVariable: {
                std::cout << PrefixForIndent(indent) << "Value: " << action.set_var.value << std::endl;
                std::cout << PrefixForIndent(indent) << "Register name: " << action.set_var.register_name << std::endl;
                break;
            }
            case ActionType::Add: {
                std::cout << PrefixForIndent(indent) << "Amount: " << (int)action.add.amount << std::endl;
                std::cout << PrefixForIndent(indent) << "Register name: " << action.add.register_name << std::endl;
                break;
            }
            case ActionType::EndLevel: {
                std::cout << PrefixForIndent(indent) << "Section ID: " << action.end_level.section_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Cinematic file ID: " << action.end_level.cinematic_file_id << std::endl;
                break;
            }
            case ActionType::SpawnObjectAt: {
                PrintTarget(action.spawn_obj_at.target, indent);
                std::cout << PrefixForIndent(indent) << "Is particle: " << std::boolalpha << action.spawn_obj_at.is_particle << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Spawn object ID: " << std::boolalpha << action.spawn_obj_at.spawn_obj_file_id << std::noboolalpha << std::endl;
                
                if(!action.spawn_obj_at.is_particle) {
                    std::cout << PrefixForIndent(indent) << "Inherit adjs from parent: " << std::boolalpha << action.spawn_obj_at.inherit_adjs_from_parent << std::noboolalpha << std::endl;

                    std::cout << PrefixForIndent(indent) << "Adjective IDs: ";
                    if(action.spawn_obj_at.adjs.empty()) {
                        std::cout << "<none>";
                    }
                    for(const auto &id: action.spawn_obj_at.adjs) {
                        std::cout << id << " ";
                    }
                    std::cout << std::endl;
                }

                std::cout << PrefixForIndent(indent) << "Relative position X: " << action.spawn_obj_at.relative_pos_x << std::endl;
                std::cout << PrefixForIndent(indent) << "Relative position Y: " << action.spawn_obj_at.relative_pos_y << std::endl;
                std::cout << PrefixForIndent(indent) << "Bounce towards Maxwell: " << std::boolalpha << action.spawn_obj_at.options_2.bounce_towards_maxwell << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Make draggable: " << std::boolalpha << action.spawn_obj_at.options_2.make_draggable << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Supress adjectives' banner: " << (int)action.spawn_obj_at.options_2.suppress_adjs_banner << std::endl;
                std::cout << PrefixForIndent(indent) << "Max objects: " << (int)action.spawn_obj_at.options_1.max_objects << std::endl;
                std::cout << PrefixForIndent(indent) << "Stop if no spawn: " << std::boolalpha << action.spawn_obj_at.options_1.stop_if_no_spawn << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::ShowEmote: {
                PrintTarget(action.show_emote.target, indent);
                std::cout << PrefixForIndent(indent) << "Emote: " << DefaultNull(action.show_emote.next_emote, FormatAiEmoteType) << std::endl;
                break;
            }
            case ActionType::Explode: {
                std::cout << PrefixForIndent(indent) << "Explosion size: " << (int)action.explode.explosion_size << std::endl;
                std::cout << PrefixForIndent(indent) << "Explode countdown: " << action.explode.explode_countdown << std::endl;
                break;
            }
            case ActionType::ImageSwap: {
                PrintTarget(action.image_swap.target, indent);
                std::cout << PrefixForIndent(indent) << "File ID: " << action.image_swap.file_id << std::endl;
                break;
            }
            case ActionType::Cinematic: {
                std::cout << PrefixForIndent(indent) << "Section ID: " << (int)action.cinematic.section_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Cinematic file ID: " << action.cinematic.cinematic_file_id << std::endl;
                break;
            }
            case ActionType::ShowNotepad: {
                std::cout << PrefixForIndent(indent) << "Show: " << std::boolalpha << action.show_notepad.show << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::EncaseInIce: {
                PrintTarget(action.encase_in_ice.target, indent);
                break;
            }
            case ActionType::SetStageObject: {
                PrintTarget(action.set_stage_obj.target, indent);
                std::cout << PrefixForIndent(indent) << "Mode (attract/repulse): " << DefaultNull(action.set_stage_obj.mode, FormatAtrRepMode) << std::endl;
                std::cout << PrefixForIndent(indent) << "Ignore StageObject line of sight: " << std::boolalpha << action.set_stage_obj.ignore_stage_object_line_of_sight << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "New target entity ID: " << Mask32(action.set_stage_obj.new_target_entity_id) << std::endl;
                break;
            }
            case ActionType::EnableEntity: {
                PrintTarget(action.enable_entity.target, indent);
                std::cout << PrefixForIndent(indent) << "Enable: " << std::boolalpha << action.enable_entity.enable << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::Switch: {
                std::cout << PrefixForIndent(indent) << "Type: " << DefaultNull(action.swtch.type, FormatSwitchType) << std::endl;
                std::cout << PrefixForIndent(indent) << "Switch action lists:" << std::endl;
                for(u32 i = 0; i < action.swtch.switch_actions.size(); i++) {
                    const auto &act_list = action.swtch.switch_actions[i];
                    std::cout << PrefixForIndent(indent + 1) << "Action list[" << i << "]: " << std::endl;
                    for(u32 j = 0; j < act_list.size(); j++) {
                        const auto &act = act_list[j];
                        std::cout << PrefixForIndent(indent + 2) << "Action[" << j << "]: " << std::endl;
                        PrintAction(act, indent + 3);
                    }
                }
                break;
            }
            case ActionType::EnableSFAnim: {
                std::cout << PrefixForIndent(indent) << "Index: " << (int)action.enable_sf_anim.index << std::endl;
                std::cout << PrefixForIndent(indent) << "Toggle: " << std::boolalpha << action.enable_sf_anim.toggle << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::RotateEntity: {
                PrintTarget(action.rotate_entity.target, indent);
                std::cout << PrefixForIndent(indent) << "Rotation per second: " << action.rotate_entity.rot_per_sec << std::endl;
                break;
            }
            case ActionType::ApplyAdjective: {
                PrintTarget(action.apply_adj.target, indent);
                std::cout << PrefixForIndent(indent) << "Adjective ID: " << Mask16(action.apply_adj.adj_id) << std::endl;
                std::cout << PrefixForIndent(indent) << "Suppress banner: " << std::boolalpha << action.apply_adj.suppress_banner << std::noboolalpha << std::endl;
                break;
            }
            case ActionType::ShowFeedback: {
                PrintTarget(action.show_feedback.target, indent);
                std::cout << PrefixForIndent(indent) << "Positive feedback: " << std::boolalpha << action.show_feedback.options.positive_feedback << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Is screen space: " << std::boolalpha << action.show_feedback.options.is_screen_space << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Relative position X: " << action.show_feedback.relative_pos_x << std::endl;
                std::cout << PrefixForIndent(indent) << "Relative position Y: " << action.show_feedback.relative_pos_y << std::endl;
                break;
            }
            case ActionType::Lock: {
                PrintTarget(action.lock.target, indent);
                PrintFilter("Filters", action.lock.filter, indent);
                break;
            }
            case ActionType::NoDrag: {
                break;
            }
            case ActionType::SetInterruptFlag: {
                std::cout << PrefixForIndent(indent) << "Trigger flag slot: " << DefaultNull(action.set_interrupt_flag.options.trigger_slot, FormatTriggerFlagSlot) << std::endl;
                std::cout << PrefixForIndent(indent) << "Set flag: " << std::boolalpha << action.set_interrupt_flag.options.set_flag << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Parent trigger type: " << DefaultNull(action.set_interrupt_flag.parent_trigger_type, FormatTriggerType) << std::endl;
                break;
            }
            case ActionType::Shock: {
                PrintTarget(action.shock.target, indent);
                break;
            }
            case ActionType::Untouchable: {
                PrintTarget(action.untouchable.target, indent);
                std::cout << PrefixForIndent(indent) << "Setting: " << DefaultNull(action.untouchable.setting, FormatUntouchableSetting) << std::endl;
                break;
            }
            case ActionType::ModifyLineOfSight: {
                PrintTarget(action.modify_line_of_sight.target, indent);
                std::cout << PrefixForIndent(indent) << "Line of sight: " << (int)action.modify_line_of_sight.line_of_sight << std::endl;
                break;
            }
            default: {
                break;
            }
        }
    }

    void PrintTrigger(const TriggerAction &ta, const u32 indent = 0) {
        std::cout << PrefixForIndent(indent) << "Trigger type: " << DefaultNull(ta.options.type, FormatTriggerType) << std::endl;
        std::cout << PrefixForIndent(indent) << "Non-repeatable: " << std::boolalpha << ta.options.non_repeatable << std::noboolalpha << std::endl;
        
        switch(ta.options.type) {
            case TriggerType::OnCollide: {
                PrintFilter("Filters", ta.trigger.on_collide.filter, indent);
                std::cout << PrefixForIndent(indent) << "Minimum speed (squared): " << ta.trigger.on_collide.min_speed_sq << std::endl;
                std::cout << PrefixForIndent(indent) << "Use other speed: " << std::boolalpha << ta.trigger.on_collide.use_other_speed << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Only when fired: " << std::boolalpha << ta.trigger.on_collide.only_when_fired << std::noboolalpha << std::endl;
                break;
            }
            case TriggerType::OnCreate: {
                break;
            }
            case TriggerType::OnDestroy: {
                break;
            }
            case TriggerType::OnConsumed: {
                PrintFilter("Filters", ta.trigger.on_consumed.filter, indent);
                break;
            }
            case TriggerType::OnActivated:
            case TriggerType::OnDeactivated: {
                break;
            }
            case TriggerType::OnUsed: {
                PrintFilter("Filters", ta.trigger.on_used.filter, indent);
                std::cout << PrefixForIndent(indent) << "Use icon: " << DefaultNull(ta.trigger.on_used.icon, FormatUseIcon) << std::endl;
                break;
            }
            case TriggerType::OnUseEquipped: {
                PrintFilter("Filters", ta.trigger.on_use_equipped.filter, indent);
                std::cout << PrefixForIndent(indent) << "Use icon: " << DefaultNull(ta.trigger.on_use_equipped.icon, FormatUseIcon) << std::endl;
                break;
            }
            case TriggerType::OnVehicleAction: {
                PrintFilter("Filters", ta.trigger.on_vehicle_action.filter, indent);
                std::cout << PrefixForIndent(indent) << "Use icon: " << DefaultNull(ta.trigger.on_vehicle_action.icon, FormatUseIcon) << std::endl;
                break;
            }
            case TriggerType::OnObjectSwap: {
                break;
            }
            case TriggerType::OnModifyCharge:{
                std::cout << PrefixForIndent(indent) << "Charge modification trigger type: " << DefaultNull(ta.trigger.on_mod_charge.type, FormatChargeModificationTriggerType) << std::endl;
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
                PrintFilter("Filters", ta.trigger.on_attached_detached.filter, indent);
                break;
            }
            case TriggerType::OnSight: {
                PrintFilter("Filters", ta.trigger.on_sight.filter, indent);
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
                std::cout << PrefixForIndent(indent) << "Condition A trigger" << std::endl;
                PrintTrigger(*ta.trigger.condition.cond_a_trigger, indent + 1);
                std::cout << PrefixForIndent(indent) << "Condition B trigger" << std::endl;
                PrintTrigger(*ta.trigger.condition.cond_b_trigger, indent + 1);
                break;
            }
            case TriggerType::OnCheckVariable: {
                std::cout << PrefixForIndent(indent) << "Only check on change: " << std::boolalpha << ta.trigger.on_check_var.only_check_on_change << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Comparison: " << DefaultNull(ta.trigger.on_check_var.comp, FormatScriptComparison) << std::endl;
                std::cout << PrefixForIndent(indent) << "Register trigger value: " << ta.trigger.on_check_var.register_trigger_value << std::endl;
                std::cout << PrefixForIndent(indent) << "Register name: " << ta.trigger.on_check_var.register_name << std::endl;
                break;
            }
            case TriggerType::OnUpdate: {
                break;
            }
            case TriggerType::OnContained:
            case TriggerType::OnUncontained: {
                PrintFilter("Filters", ta.trigger.on_contained_uncontained.filter, indent);
                break;
            }
            case TriggerType::OnObjectAdded: {
                PrintFilter("Filters", ta.trigger.on_obj_added.filter, indent);
                std::cout << PrefixForIndent(indent) << "Unique objects: " << std::boolalpha << ta.trigger.on_obj_added.options.unique_objects << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Detection mode: " << DefaultNull(ta.trigger.on_obj_added.options.mode, FormatDetectionMode) << std::endl;
                std::cout << PrefixForIndent(indent) << "Unique adjectives: " << std::boolalpha << ta.trigger.on_obj_added.options.unique_adjectives << std::noboolalpha << std::endl;
                break;
            }
            case TriggerType::OnAiState: {
                std::cout << PrefixForIndent(indent) << "Goal mood: " << DefaultNull(ta.trigger.on_ai_state.goal_mood, FormatAiMood) << std::endl;
                break;
            }
            case TriggerType::OnAiAction: {
                PrintFilter("Filters", ta.trigger.on_ai_action.filter, indent);
                std::cout << PrefixForIndent(indent) << "Action (attract/repulse): " << DefaultNull(ta.trigger.on_ai_action.action, FormatAtrRepMode) << std::endl;
                break;
            }
            case TriggerType::OnObjectCountInArea: {
                PrintFilter("Filters", ta.trigger.on_obj_count_in_area.filter, indent);
                break;
            }
            case TriggerType::OnDistance: {
                PrintFilter("Filters", ta.trigger.on_distance.filter, indent);
                std::cout << PrefixForIndent(indent) << "Trigger distance: " << ta.trigger.on_distance.trigger_distance << std::endl;
                break;
            }
            case TriggerType::OnVelocity: {
                std::cout << PrefixForIndent(indent) << "Compare condition: " << DefaultNull(ta.trigger.on_velocity.compare_condition, FormatScriptComparison) << std::endl;
                std::cout << PrefixForIndent(indent) << "Trigger velocity (squared): " << ta.trigger.on_velocity.trigger_velocity_sq << std::endl;
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
                PrintFilter("Filters", ta.trigger.on_ai_equip_unequip.filter, indent);
                break;
            }
            case TriggerType::OnAiConsume: {
                PrintFilter("Filters", ta.trigger.on_ai_consume.filter, indent);
                break;
            }
            case TriggerType::OnEmpty:
            case TriggerType::OnFill: {
                PrintFilter("Filters", ta.trigger.on_empty_fill.filter, indent);
                break;
            }
            case TriggerType::OnModifyIntegrity: {
                PrintFilter("Filters", ta.trigger.on_modify_integrity.filter, indent);
                break;
            }
            case TriggerType::OnHearSound: {
                std::cout << PrefixForIndent(indent) << "Sound attribute: " << DefaultNull(ta.trigger.on_hear_sound.attr, FormatSoundAttribute) << std::endl;
                break;
            }
            case TriggerType::OnMounted:
            case TriggerType::OnUnmounted: {
                PrintFilter("Filters", ta.trigger.on_mounted_unmounted.filter, indent);
                std::cout << PrefixForIndent(indent) << "Control spot only: " << std::boolalpha << ta.trigger.on_mounted_unmounted.control_spot_only << std::noboolalpha << std::endl;
                break;
            }
            case TriggerType::TriggerGroup: {
                std::cout << PrefixForIndent(indent) << "Only check on change: " << std::boolalpha << ta.trigger.group.only_check_on_change << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Comparison: " << DefaultNull(ta.trigger.group.comp, FormatScriptComparison) << std::endl;
                std::cout << PrefixForIndent(indent) << "Register trigger value: " << ta.trigger.group.register_trigger_value << std::endl;
                std::cout << PrefixForIndent(indent) << "Register name: " << ta.trigger.group.register_name << std::endl;

                std::cout << PrefixForIndent(indent) << "Group triggers:" << std::endl;
                for(u32 i = 0; i < ta.trigger.group.group_triggers.size(); i++) {
                    const auto &sub_ta = ta.trigger.group.group_triggers[i];
                    std::cout << PrefixForIndent(indent + 1) << "Group trigger[" << i << "]: " << std::endl;
                    PrintTrigger(sub_ta, indent + 2);
                }
                break;
            }
            case TriggerType::OnApplyAdjective:
            case TriggerType::OnKickAdjective: {
                PrintFilter("Filters", ta.trigger.on_apply_kick_adj.filter, indent);
                break;
            }
            default: {
                break;
            }
        }

        std::cout << PrefixForIndent(indent) << "Actions:" << std::endl;
        for(u32 j = 0; j < ta.actions.size(); j++) {
            std::cout << PrefixForIndent(indent + 1) << "Action[" << j << "]: " << std::endl;

            const auto &action = ta.actions[j];
            PrintAction(action, indent + 2);
        }
    }

    void PrintFrame(const ObjectFrame &frame, const u32 indent);

    void PrintFrameChildren(const std::vector<ObjectFrame> &children, const u32 indent = 0) {
        if(!children.empty()) {
            std::cout << PrefixForIndent(indent) << "Children:" << std::endl;
            for(u32 i = 0; i < children.size(); i++) {
                const auto &child = children[i];
                std::cout << PrefixForIndent(indent + 1) << "Child frame[" << i << "]: " << std::endl;
                PrintFrame(child, indent + 2);
            }
        }
    }

    void PrintFrame(const ObjectFrame &frame, const u32 indent = 0) {
        std::cout << PrefixForIndent(indent) << "Frame type: " << DefaultNull(frame.type, FormatFrameType) << std::endl;
        std::cout << PrefixForIndent(indent) << "X: " << FORMAT_FX32(frame.x) << std::endl;
        std::cout << PrefixForIndent(indent) << "Y: " << FORMAT_FX32(frame.y) << std::endl;
        std::cout << PrefixForIndent(indent) << "Rotation: " << FORMAT_FX32(frame.rot) << std::endl;
        std::cout << PrefixForIndent(indent) << "Enabled: " << std::boolalpha << frame.enabled << std::noboolalpha << std::endl;

        switch(frame.type) {
            case FrameType::Main: {
                PrintFrameChildren(frame.main.children, indent);
                break;
            }
            case FrameType::Box: {
                if(frame.box.type.has_force) {
                    std::cout << PrefixForIndent(indent) << "Force field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Center force: " << (int)frame.box.force.center_force << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Falloff type: " << DefaultNull(frame.box.force.options.falloff_type, FormatForceZoneFalloff) << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Damping: " << (int)frame.box.force.damping << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Force X: " << (int)frame.box.force.force_x << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Force Y: " << (int)frame.box.force.force_y << std::endl;
                    PrintFilter("Force filter", frame.box.force.filter, indent + 1);
                }
                if(frame.box.type.has_temperature) {
                    std::cout << PrefixForIndent(indent) << "Temperature field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Temperature: " << frame.box.temperature.temperature << std::endl;
                }
                if(frame.box.type.has_water) {
                    std::cout << PrefixForIndent(indent) << "Water field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Water zone type: " << DefaultNull(frame.box.water.water_type, FormatWaterZoneType) << std::endl;
                }
                if(frame.box.type.has_damage) {
                    std::cout << PrefixForIndent(indent) << "Damage field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Collide damage: " << (int)frame.box.damage.collide_damage << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "DPS: " << (int)frame.box.damage.dps << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Knockback: " << (int)frame.box.damage.knockback << std::endl;
                }

                std::cout << PrefixForIndent(indent) << "Width: " << FORMAT_FX32(frame.box.width) << std::endl;
                std::cout << PrefixForIndent(indent) << "Height: " << FORMAT_FX32(frame.box.height) << std::endl;

                PrintFrameChildren(frame.box.children, indent);
                break;
            }
            case FrameType::Circle: {
                if(frame.circle.type.has_force) {
                    std::cout << PrefixForIndent(indent) << "Force field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Center force: " << (int)frame.circle.force.center_force << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Falloff type: " << DefaultNull(frame.circle.force.options.falloff_type, FormatForceZoneFalloff) << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Damping: " << (int)frame.circle.force.damping << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Force X: " << (int)frame.circle.force.force_x << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Force Y: " << (int)frame.circle.force.force_y << std::endl;
                    PrintFilter("Force filter", frame.circle.force.filter, indent + 1);
                }
                if(frame.circle.type.has_temperature) {
                    std::cout << PrefixForIndent(indent) << "Temperature field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Temperature: " << frame.circle.temperature.temperature << std::endl;
                }
                if(frame.circle.type.has_damage) {
                    std::cout << PrefixForIndent(indent) << "Damage field:" << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Collide damage: " << (int)frame.circle.damage.collide_damage << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "DPS: " << (int)frame.circle.damage.dps << std::endl;
                    std::cout << PrefixForIndent(indent + 1) << "Knockback: " << (int)frame.circle.damage.knockback << std::endl;
                }

                std::cout << PrefixForIndent(indent) << "Radius: " << frame.circle.radius << std::endl;
                std::cout << PrefixForIndent(indent) << "Surface force factor: " << (int)frame.circle.surface_force_factor << std::endl;

                PrintFrameChildren(frame.circle.children, indent);
                break;
            }
            case FrameType::Polygon: {
                std::cout << PrefixForIndent(indent) << "Polygon points:" << std::endl;
                for(u32 i = 0; i < frame.polygon.poly_points.size(); i++) {
                    const auto &point = frame.polygon.poly_points[i];
                    std::cout << PrefixForIndent(indent + 1) << "Point[" << i << "]: " << FORMAT_FX32(point.first) << ", " << FORMAT_FX32(point.second) << std::endl;
                }

                std::cout << PrefixForIndent(indent) << "Surface force factors:" << std::endl;
                for(u32 i = 0; i < frame.polygon.surface_force_factors.size(); i++) {
                    std::cout << PrefixForIndent(indent + 1) << "Factor[" << i << "]: " << (int)frame.polygon.surface_force_factors[i] << std::endl;
                }

                std::cout << PrefixForIndent(indent) << "Top collision only: " << std::boolalpha << frame.polygon.top_collision_only << std::noboolalpha << std::endl;

                PrintFrameChildren(frame.polygon.children, indent);
                break;
            }
            case FrameType::Image: {
                std::cout << PrefixForIndent(indent) << "Texture file ID: " << frame.image.tex_file_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Mask ID: " << frame.image.mask_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Display list data size: " << frame.image.display_list_data.size() << " bytes" << std::endl;
                
                std::cout << PrefixForIndent(indent) << "Limb indices:" << std::endl;
                for(u32 i = 0; i < static_cast<size_t>(Limb::Count); i++) {
                    std::cout << PrefixForIndent(indent + 1) << DefaultNull(static_cast<Limb>(i), FormatLimb) << ": " << (int)frame.image.limb_indices[i] << std::endl;
                }

                PrintFrameChildren(frame.image.children, indent);
                break;
            }
            case FrameType::TexQuad: {
                std::cout << PrefixForIndent(indent) << "Body part: " << DefaultNull(frame.tex_quad.body_part, FormatBodyPart) << std::endl;
                std::cout << PrefixForIndent(indent) << "Z order: " << frame.tex_quad.z_order << std::endl;
                std::cout << PrefixForIndent(indent) << "Spawn position points:" << std::endl;
                for(u32 i = 0; i < 8; i++) {
                    const auto &point = frame.tex_quad.spawn_pos_vecs[i];
                    std::cout << PrefixForIndent(indent + 1) << "Point[" << i << "]: " << FORMAT_FX32(point.first) << ", " << FORMAT_FX32(point.second) << std::endl;
                }

                PrintFrameChildren(frame.tex_quad.children, indent);
                break;
            }
            case FrameType::Ellipse: {
                std::cout << PrefixForIndent(indent) << "Width: " << FORMAT_FX32(frame.ellipse.width) << std::endl;
                std::cout << PrefixForIndent(indent) << "Height: " << FORMAT_FX32(frame.ellipse.height) << std::endl;

                PrintFrameChildren(frame.ellipse.children, indent);
                break;
            }
            case FrameType::HotSpot: {
                std::cout << PrefixForIndent(indent) << "HotSpot type: " << DefaultNull(frame.hotspot.options.type, FormatHotSpotType) << std::endl;
                std::cout << PrefixForIndent(indent) << "HotSpot enabled: " << std::boolalpha << frame.hotspot.options.enabled << std::noboolalpha << std::endl;
                
                switch(frame.hotspot.options.type) {
                    case HotSpotType::HotSpotAttach: {
                        break;
                    }
                    case HotSpotType::HotSpotCenterOfGravity: {
                        break;
                    }
                    case HotSpotType::HotSpotSaddle: {
                        std::cout << PrefixForIndent(indent) << "Saddle animation: " << DefaultNull(frame.hotspot.saddle.anim, FormatAnimation) << std::endl;
                        std::cout << PrefixForIndent(indent) << "Is control spot: " << std::boolalpha << frame.hotspot.saddle.is_control_spot << std::noboolalpha << std::endl;
                        std::cout << PrefixForIndent(indent) << "Saddle sorting: " << DefaultNull(frame.hotspot.saddle.sorting, FormatSaddleSorting) << std::endl;
                        std::cout << PrefixForIndent(indent) << "Can knock off: " << std::boolalpha << frame.hotspot.saddle.can_knock_off << std::noboolalpha << std::endl;
                        PrintFilter("Saddle filter", frame.hotspot.saddle.filter, indent);
                        if(frame.hotspot.saddle.has_pre_mounted_object) {
                            std::cout << PrefixForIndent(indent) << "Pre-mounted object ID: " << frame.hotspot.saddle.pre_mounted_obj_id << std::endl;
                        }
                        break;
                    }
                    case HotSpotType::HotSpotSaddleSnap: {
                        PrintFilter("Saddle snap filter", frame.hotspot.saddle_snap.filter, indent);
                        break;
                    }
                    case HotSpotType::HotSpotContainerOpening: {
                        break;
                    }
                    case HotSpotType::HotSpotEquip: {
                        std::cout << PrefixForIndent(indent) << "Equip location: " << DefaultNull(frame.hotspot.equip.location, FormatEquipLocation) << std::endl;
                        PrintFilter("Equip filter", frame.hotspot.equip.filter, indent);
                        if(frame.hotspot.equip.has_pre_equipped_object) {
                            std::cout << PrefixForIndent(indent) << "Pre-equipped object file ID: " << frame.hotspot.equip.pre_equipped_obj_file_id << std::endl;
                        }
                        break;
                    }
                    case HotSpotType::HotSpotWaypoint: {
                        break;
                    }
                    case HotSpotType::HotSpotSplit: {
                        std::cout << PrefixForIndent(indent) << "Object ID A: " << frame.hotspot.split.obj_id_a << std::endl;
                        std::cout << PrefixForIndent(indent) << "Split A: " << frame.hotspot.split.split_a_x << ", " << frame.hotspot.split.split_a_y << std::endl;
                        std::cout << PrefixForIndent(indent) << "Split A rotation: " << frame.hotspot.split.split_a_rot << std::endl;
                        std::cout << PrefixForIndent(indent) << "Object ID B: " << frame.hotspot.split.obj_id_b << std::endl;
                        std::cout << PrefixForIndent(indent) << "Split B: " << frame.hotspot.split.split_b_x << ", " << frame.hotspot.split.split_b_y << std::endl;
                        std::cout << PrefixForIndent(indent) << "Split B rotation: " << frame.hotspot.split.split_b_rot << std::endl;
                        break;
                    }
                    case HotSpotType::HotSpotLight: {
                        std::cout << PrefixForIndent(indent) << "Light shape: " << DefaultNull(frame.hotspot.light.shape, FormatLightShape) << std::endl;
                        break;
                    }
                    case HotSpotType::HotSpotEmitter: {
                        std::cout << PrefixForIndent(indent) << "Emit X: " << frame.hotspot.emitter.emit_x << std::endl;
                        std::cout << PrefixForIndent(indent) << "Emit Y: " << frame.hotspot.emitter.emit_y << std::endl;
                        std::cout << PrefixForIndent(indent) << "Angle: " << frame.hotspot.emitter.angle << std::endl;
                        std::cout << PrefixForIndent(indent) << "Spawn interval: " << frame.hotspot.emitter.spawn_interval << std::endl;
                        std::cout << PrefixForIndent(indent) << "Emit speed: " << frame.hotspot.emitter.emit_speed << std::endl;
                        std::cout << PrefixForIndent(indent) << "Scatter shot: " << std::boolalpha << frame.hotspot.emitter.scatter_shot << std::noboolalpha << std::endl;
                        std::cout << PrefixForIndent(indent) << "Spawn count: " << (int)frame.hotspot.emitter.spawn_count << std::endl;
                        std::cout << PrefixForIndent(indent) << "Apply gravity: " << std::boolalpha << frame.hotspot.emitter.apply_gravity << std::noboolalpha << std::endl;
                        std::cout << PrefixForIndent(indent) << "Object is particle: " << frame.hotspot.emitter.obj_is_particle << std::endl;
                        std::cout << PrefixForIndent(indent) << "Emit object ID: " << frame.hotspot.emitter.emit_object << std::endl;
                        std::cout << PrefixForIndent(indent) << "Emitter label: " << DefaultNull(frame.hotspot.emitter.label, FormatEmitterLabel) << std::endl;
                        break;
                    }
                    case HotSpotType::HotSpotFire: {
                        std::cout << PrefixForIndent(indent) << "Fire effect size: " << DefaultNull(frame.hotspot.fire.fire_size, FormatFireEffectSize) << std::endl;
                        std::cout << PrefixForIndent(indent) << "Fire enabled: " << std::boolalpha << frame.hotspot.fire.enabled << std::noboolalpha << std::endl;
                        break;
                    }
                    case HotSpotType::JointFixed: {
                        break;
                    }
                    case HotSpotType::JointRevolute: {
                        std::cout << PrefixForIndent(indent) << "Is motor: " << std::boolalpha << frame.hotspot.joint_revolute.is_motor << std::noboolalpha << std::endl;
                        std::cout << PrefixForIndent(indent) << "Auto torque: " << (int)frame.hotspot.joint_revolute.auto_torque << std::endl;
                        std::cout << PrefixForIndent(indent) << "Reference object ID: " << frame.hotspot.joint_revolute.ref_obj_id << std::endl;
                        std::cout << PrefixForIndent(indent) << "Part X: " << frame.hotspot.joint_revolute.part_x << std::endl;
                        std::cout << PrefixForIndent(indent) << "Part Y: " << frame.hotspot.joint_revolute.part_y << std::endl;
                        std::cout << PrefixForIndent(indent) << "Part rotation: " << frame.hotspot.joint_revolute.part_rot << std::endl;
                        break;
                    }
                    case HotSpotType::JointRotationalSpring: {
                        std::cout << PrefixForIndent(indent) << "Stiffness: " << std::boolalpha << (int)frame.hotspot.joint_rotational_spring.stiffness << std::noboolalpha << std::endl;
                        std::cout << PrefixForIndent(indent) << "Reference object ID: " << frame.hotspot.joint_rotational_spring.ref_obj_id << std::endl;
                        std::cout << PrefixForIndent(indent) << "Part X: " << frame.hotspot.joint_rotational_spring.part_x << std::endl;
                        std::cout << PrefixForIndent(indent) << "Part Y: " << frame.hotspot.joint_rotational_spring.part_y << std::endl;
                        std::cout << PrefixForIndent(indent) << "Part rotation: " << frame.hotspot.joint_rotational_spring.part_rot << std::endl;
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
                        std::cout << PrefixForIndent(indent) << "Digger radius: " << frame.hotspot.digger.radius << std::endl;
                        break;
                    }
                }

                PrintFrameChildren(frame.hotspot.children, indent);
                break;
            }
            case FrameType::Reference: {
                std::cout << PrefixForIndent(indent) << "part_id_obj_file_id: " << frame.reference.part_id_obj_file_id << std::endl;

                PrintFrameChildren(frame.reference.children, indent);
                break;
            }
            case FrameType::SFAnimation: {
                std::cout << PrefixForIndent(indent) << "Sprite ID: " << frame.sf_anim.sprite_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Animation ID: " << (int)frame.sf_anim.animation_idx << std::endl;
                std::cout << PrefixForIndent(indent) << "Z order: " << (int)frame.sf_anim.z_order << std::endl;
                std::cout << PrefixForIndent(indent) << "Speed: " << frame.sf_anim.speed << std::endl;
                std::cout << PrefixForIndent(indent) << "Disable animation: " << std::boolalpha << frame.sf_anim.disable_anim << std::noboolalpha << std::endl;
                std::cout << PrefixForIndent(indent) << "Sprite file ID: " << frame.sf_anim.sprite_file_id << std::endl;

                PrintFrameChildren(frame.sf_anim.children, indent);
                break;
            }
            case FrameType::Particle: {
                break;
            } 
            case FrameType::Stamp: {
                std::cout << PrefixForIndent(indent) << "Sprite ID: " << frame.stamp.sprite_id << std::endl;
                std::cout << PrefixForIndent(indent) << "Scale: " << frame.stamp.scale<< std::endl;
                std::cout << PrefixForIndent(indent) << "Z order: " << frame.stamp.z_order << std::endl;
                std::cout << PrefixForIndent(indent) << "Flipped: " << std::boolalpha << frame.stamp.flipped << std::noboolalpha << std::endl;
                
                if(frame.stamp.has_spawn_pos) {
                    std::cout << PrefixForIndent(indent) << "Spawn position points:" << std::endl;
                    for(u32 i = 0; i < 8; i++) {
                        const auto &point = frame.stamp.spawn_pos_vecs[i];
                        std::cout << PrefixForIndent(indent + 1) << "Point[" << i << "]: " << FORMAT_FX32(point.first) << ", " << FORMAT_FX32(point.second) << std::endl;
                    }
                }

                PrintFrameChildren(frame.stamp.children, indent);
                break;
            }
        }
    }

}

namespace cli {

    void PrintObject(const std::string &in_index, const std::string &in_package, const std::string &file_id_str) {
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

            fmt::Object obj;
            R_TRY_ERRLOG(obj.ReadFrom(file), "Unable to read object file");
            
            std::cout << "======================    OBJECT INFO    ======================" << std::endl;

            std::cout << "----------------------       Header      ----------------------" << std::endl;
            std::cout << "Object category ID: " << DefaultNull(obj.header.category_id, FormatObjectCategoryId) << std::endl;
            std::cout << "Object subcategory ID 1: " << (int)obj.header.subcategory_id_1 << std::endl;
            std::cout << "Object subcategory ID 2: " << (int)obj.header.subcategory_id_2 << std::endl;
            std::cout << "Object ID: " << obj.header.obj_id << std::endl;
            std::cout << "Width: " << obj.header.width << std::endl;
            std::cout << "Height: " << obj.header.height << std::endl;

            std::cout << "----------------------       Generic     ----------------------" << std::endl;
            std::cout << "Ignores force fields: " << std::boolalpha << obj.generic.options_1.ignores_force_fields << std::noboolalpha << std::endl;
            std::cout << "Ignores gravity: " << std::boolalpha << obj.generic.options_1.ignores_gravity << std::noboolalpha << std::endl;
            std::cout << "TA not active: " << std::boolalpha << obj.generic.options_1.ta_not_active << std::noboolalpha << std::endl;
            std::cout << "Picking uses region: " << std::boolalpha << obj.generic.options_1.picking_uses_region << std::noboolalpha << std::endl;
            std::cout << "Equip size requirement: " << DefaultNull(obj.generic.options_1.req, FormatEquipSizeRequirement) << std::endl;
            std::cout << "Vehicle animation: " << DefaultNull(obj.generic.options_2.vehicle_anim, FormatVehicleAnimation) << std::endl;
            std::cout << "Update physics from animations: " << std::boolalpha << obj.generic.options_2.update_physics_from_animations << std::noboolalpha << std::endl;
            std::cout << "Rope length: " << (int)obj.generic.rope_length << std::endl;
            std::cout << "Clip size: " << (int)obj.generic.clip_size << std::endl;
            std::cout << "Budget class: " << (int)obj.generic.budget_class << std::endl;
            if(obj.generic.options_1.has_climb_filter) {
                PrintFilter("Climb filters", obj.generic.climb_filter);
            }

            std::cout << "----------------------       Movement    ----------------------" << std::endl;
            std::cout << "Movement speed: " << (int)obj.movement.movement_speed << std::endl;
            std::cout << "Jump height: " << (int)obj.movement.jump_height << std::endl;
            std::cout << "Grant jump: " << std::boolalpha << obj.movement.options.grant_jump << std::noboolalpha << std::endl;
            std::cout << "Include rider air movement: " << std::boolalpha << obj.movement.options.include_rider_air_movement << std::noboolalpha << std::endl;
            std::cout << "Requires takeoff: " << std::boolalpha << obj.movement.options.requires_takeoff << std::noboolalpha << std::endl;
            std::cout << "Grants speed: " << std::boolalpha << obj.movement.options.grants_speed << std::noboolalpha << std::endl;
            std::cout << "Ground motion: " << DefaultNull(obj.movement.options.ground_motion, FormatGroundMotion) << std::endl;
            std::cout << "Grants fly: " << std::boolalpha << obj.movement.options.grants_fly << std::noboolalpha << std::endl;
            std::cout << "Movement H flip: " << std::boolalpha << obj.movement.options.movement_h_flip << std::noboolalpha << std::endl;

            std::cout << "----------------------       Ai          ----------------------" << std::endl;
            std::cout << "AI mood: " << DefaultNull(obj.ai.ai_mood, FormatAiMood) << std::endl;
            std::cout << "AI enabled: " << std::boolalpha << obj.ai.options.ai_enabled << std::noboolalpha << std::endl;
            std::cout << "Dig enabled: " << std::boolalpha << obj.ai.options.dig_enabled << std::noboolalpha << std::endl;
            std::cout << "Split enabled: " << std::boolalpha << obj.ai.options.split_enabled << std::noboolalpha << std::endl;
            std::cout << "Shoot enabled: " << std::boolalpha << obj.ai.options.shoot_enabled << std::noboolalpha << std::endl;
            std::cout << "Sight distance (tiles): " << (int)obj.ai.sight_distance_tiles << std::endl;
            std::cout << "Visibility factor: " << (int)obj.ai.visibility_factor << std::endl;
            std::cout << "React size compare: " << DefaultNull(obj.ai.react_size_compare, FormatAiReactSizeCompare) << std::endl;
            std::cout << "Attack damage: " << (int)obj.ai.attack_damage << std::endl;
            PrintAtrRepList("Atracts/repulses", obj.ai.atr_rep_list.atr_reps);

            std::cout << "----------------------       Container   ----------------------" << std::endl;
            std::cout << "Open container: " << std::boolalpha << obj.container.options.open_container << std::noboolalpha << std::endl;
            std::cout << "Show contained objects: " << std::boolalpha << obj.container.options.show_contained_objects << std::noboolalpha << std::endl;
            std::cout << "Display contained objects at bottom: " << std::boolalpha << obj.container.options.display_contained_objects_at_bottom << std::noboolalpha << std::endl;
            std::cout << "Is cannon: " << std::boolalpha << obj.container.options.is_cannon << std::noboolalpha << std::endl;
            std::cout << "Container width: " << (int)obj.container.container_width << std::endl;
            std::cout << "Container height: " << (int)obj.container.container_height << std::endl;
            std::cout << "Contained object file IDs: ";
            if(obj.container.contained_obj_file_ids.empty()) {
                std::cout << "<none>";
            }
            for(const auto &id: obj.container.contained_obj_file_ids) {
                std::cout << id << " ";
            }
            std::cout << std::endl;

            std::cout << "----------------------       Electricity ----------------------" << std::endl;
            std::cout << "Generates charge: " << std::boolalpha << obj.electricity.generates_charge << std::noboolalpha << std::endl;
            std::cout << "Water charge: " << DefaultNull(obj.electricity.options.water_charge, FormatWaterCharge) << std::endl;
            std::cout << "Can be shocked: " << std::boolalpha << obj.electricity.options.can_be_shocked << std::noboolalpha << std::endl;
            std::cout << "Ignore water particles: " << std::boolalpha << obj.electricity.options.ignore_water_particles << std::noboolalpha << std::endl;
            std::cout << "Shock on touch: " << std::boolalpha << obj.electricity.options.shock_on_touch << std::noboolalpha << std::endl;
            std::cout << "Transports charge: " << std::boolalpha << obj.electricity.options.transports_charge << std::noboolalpha << std::endl;

            std::cout << "----------------------     Placement     ----------------------" << std::endl;
            std::cout << "Placement type: " << DefaultNull(obj.placement.type, FormatObjectPlacementType) << std::endl;
            std::cout << "Enable sky: " << std::boolalpha << obj.placement.options.enable_sky << std::noboolalpha << std::endl;
            std::cout << "Enable background: " << std::boolalpha << obj.placement.options.enable_background << std::noboolalpha << std::endl;
            std::cout << "Enable H flip: " << std::boolalpha << obj.placement.options.enable_h_flip << std::noboolalpha << std::endl;
            std::cout << "Enable rotate 90deg: " << std::boolalpha << obj.placement.options.enable_rotate_90 << std::noboolalpha << std::endl;
            std::cout << "Collides with AI: " << std::boolalpha << obj.placement.options.collides_with_ai << std::noboolalpha << std::endl;
            std::cout << "Align to terrain: " << std::boolalpha << obj.placement.options.align_to_terrain << std::noboolalpha << std::endl;

            std::cout << "----------------------      Physics      ----------------------" << std::endl;
            std::cout << "Combiner: " << DefaultNull(obj.physics.combiner, FormatObjectPhysicsCombiner) << std::endl;
            std::cout << "Material: " << DefaultNull(obj.physics.material, FormatObjectMaterial) << std::endl;
            std::cout << "Mass: " << (int)obj.physics.mass << std::endl;
            std::cout << "Integrity: " << obj.physics.integrity << std::endl;
            std::cout << "Inertia: " << (int)obj.physics.inertia << std::endl;
            std::cout << "Fire interaction: " << DefaultNull(obj.physics.fire_interaction, FormatObjectFireInteraction) << std::endl;
            std::cout << "Buoyancy factor: " << (int)obj.physics.buoyancy_factor << std::endl;
            std::cout << "Is waterproof: " << std::boolalpha << obj.physics.options.is_waterproof << std::noboolalpha << std::endl;
            std::cout << "Can attach: " << std::boolalpha << obj.physics.options.can_attach << std::noboolalpha << std::endl;

            std::cout << "----------------------    Temperature    ----------------------" << std::endl;
            std::cout << "Temperature: " << (int)obj.temperature.temperature << std::endl;
            std::cout << "Melting point: " << (int)obj.temperature.melting_point << std::endl;
            std::cout << "Gas point: " << (int)obj.temperature.gas_point << std::endl;

            std::cout << "----------------------  Triggers/Actions ----------------------" << std::endl;
            for(u32 i = 0; i < obj.triggers_actions.triggers_actions.size(); i++) {
                std::cout << "Trigger[" << i << "]: " << std::endl;
                const auto &ta = obj.triggers_actions.triggers_actions[i];
                PrintTrigger(ta, 1);
            }

            std::cout << "----------------------       Frames      ----------------------" << std::endl;
            std::cout << "Unknown flag: " << std::boolalpha << obj.frames.unk << std::noboolalpha << std::endl;
            std::cout << "Physics shape count: " << (int)obj.frames.physics_shape_count << std::endl;
            std::cout << "Root frame:" << std::endl;
            PrintFrame(obj.frames.root, 1);

            std::cout << "----------------------        Audio      ----------------------" << std::endl;
            for(u32 i = 0; i < static_cast<size_t>(AudioTableType::Count); i++) {
                if(obj.audio.audio_slots[i].has_value()) {
                    const auto &slot = obj.audio.audio_slots[i].value();
                    std::cout << "AudioTableSlot[" << FormatAudioTableType(static_cast<AudioTableType>(i)) << "]: " << std::endl;
                    std::cout << PrefixForIndent(1) << "Group ID: " << slot.group_id << std::endl;
                    std::cout << PrefixForIndent(1) << "SeqArc ID: " << slot.seqarc_id << std::endl;
                    std::cout << PrefixForIndent(1) << "Seq ID: " << slot.seq_id << std::endl;
                    std::cout << PrefixForIndent(1) << "Sound attribute: " << DefaultNull(slot.attr, FormatSoundAttribute) << std::endl;
                }
            }

            if(obj.attack.valid) {
                std::cout << "----------------------       Attack      ----------------------" << std::endl;
                for(u32 i = 0; i < static_cast<size_t>(Animation::Count); i++) {
                    const auto &attack = obj.attack.attacks[i];
                    std::cout << "Attack[" << FormatAnimation(static_cast<Animation>(i)) << "]: " << std::endl;
                    if(attack.options.file_id != 0x7FFFFFFF) {
                        std::cout << PrefixForIndent(1) << "File ID: " << attack.options.file_id << std::endl;
                    }
                    if(attack.options.has_notes) {
                        std::cout << PrefixForIndent(1) << "Notes:" << std::endl;
                        std::cout << PrefixForIndent(2) << "Action: " << Mask16(attack.notes.action) << std::endl;
                        std::cout << PrefixForIndent(2) << "To: " << Mask16(attack.notes.to) << std::endl;
                        std::cout << PrefixForIndent(2) << "From: " << Mask16(attack.notes.from) << std::endl;
                    }
                }
            }
        }
        catch(std::exception &ex) {
            std::cerr << "Invalid file ID: " << ex.what() << std::endl;
        }
    }

}
