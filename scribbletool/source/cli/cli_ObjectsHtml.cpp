#include <cli/cli_ObjectsHtml.hpp>
#include <cli/cli_ExportTexture.hpp>

namespace {

    struct HtmlGenerateContext {
        Game game;
        io::FileSystem fs;
        fmt::Dictionary dict;
    };

    inline std::string EnterSection(const std::string &tag, const std::string &name) {
        /*
        <div class="container mt-3">
            <p>
                <a class="text-primary text-decoration-none" data-bs-toggle="collapse" href="#{TAG}" role="button">
                    <h4>{NAME}</h4>
                </a>
            </p>
            <div class="collapse" id="{TAG}">
                <div class="card card-body">
        */

        std::string str = "<section class=\"container mt-3\">\n";
        str += "<p>\n";
        str += "<a class=\"text-primary text-decoration-none\" data-bs-toggle=\"collapse\" href=\"#" + tag + "\" role=\"button\">\n";
        str += "<h4>" + name + "</h4>\n";
        str += "</a>\n";
        str += "</p>\n";
        str += "<div class=\"collapse\" id=\"" + tag + "\">\n";
        str += "<div class=\"card card-body\">\n";
        return str;
    }

    inline std::string ExitSection() {
        /*
                </div>
            </div>
        </div>
        */

        std::string str = "</div>\n";
        str += "</div>\n";
        str += "</section>\n";
        return str;
    }
    
    inline std::string MakeObjectEntry(const u16 file_id, const std::string &name, const fmt::Object &obj) {
        /*
        <li class="list-group-item" data-name="{OBJ-NAME}" data-id="{OBJ-ID}" data-fileid="{OBJ-FILEID}" data-triggers="{OBJ-TRIGGERS}" data-actions="{OBJ-ACTIONS}">
            <a href="{OBJ-NAME}.html">{OBJ-NAME}</a>
        </li>
        */

        std::string trigger_list;
        bool triggers_added[static_cast<size_t>(TriggerType::Count)] = {false};
        std::string action_list;
        bool actions_added[static_cast<size_t>(ActionType::Count)] = {false};
        for(const auto &trigger: obj.triggers_actions.triggers_actions) {
            if(triggers_added[static_cast<size_t>(trigger.options.type)]) {
                continue;
            }

            trigger_list += FormatTriggerType(trigger.options.type) + ",";
            triggers_added[static_cast<size_t>(trigger.options.type)] = true;

            for(const auto &action: trigger.actions) {
                if(actions_added[static_cast<size_t>(action.type)]) {
                    continue;
                }

                action_list += FormatActionType(action.type) + ",";
                actions_added[static_cast<size_t>(action.type)] = true;
            }
        }
        if(!trigger_list.empty()) {
            trigger_list.pop_back();
        }
        if(!action_list.empty()) {
            action_list.pop_back();
        }

        std::string str = "<li class=\"list-group-item\" data-name=\"" + name + "\" data-id=\"" + std::to_string(obj.header.obj_id) + "\" data-fileid=\"" + std::to_string(file_id) + "\" data-category=\"" + std::to_string((int)obj.header.category_id) + "\" data-subcategories=\"" + std::to_string((int)obj.header.subcategory_id_1) + "," + std::to_string((int)obj.header.subcategory_id_2) + "\" data-triggers=\"" + trigger_list + "\" data-actions=\"" + action_list + "\">\n";
        str += "<a class=\"text-primary text-decoration-none\" role=\"button\" href=\"" + name + ".html\">" + name + "</a>\n";
        str += "</li>\n";
        return str;
    }

    void ReplaceAll(std::string &str, const std::string &from, const std::string &to) {
        if(from.empty()) {
            return;
        }
    
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
    }

    std::string GenerateFieldImpl(const std::string &name, const std::string &value_fmt) {
        /*
        <div class="d-flex pt-2 ps-3" style="gap: 10px; align-items: center;">
            <p class="mb-0" style="white-space: nowrap;">{NAME}: </p>
            <div class="form-control">{VALUE}</div>
        </div>
        */

        std::string str = "<div class=\"d-flex pt-2 ps-3\" style=\"gap: 10px; align-items: center;\">\n";
        str += "<p class=\"mb-0\" style=\"white-space: nowrap;\">" + name + ": </p>" + "\n";
        str += "<div class=\"form-control\">" + value_fmt + "</div>\n";
        str += "</div>\n";
        return str;
    }
    
    template<typename T>
    std::string GenerateField(const std::string &name, const T &value) {
        return GenerateFieldImpl(name, std::to_string(value));
    }

    template<>
    std::string GenerateField(const std::string &name, const std::string &value) {
        return GenerateFieldImpl(name, value);
    }

    template<>
    std::string GenerateField(const std::string &name, const u8 &value) {
        return GenerateFieldImpl(name, std::to_string((int)value));
    }

    template<>
    std::string GenerateField(const std::string &name, const bool &value) {
        return GenerateFieldImpl(name, value ? "True" : "False");
    }

    std::string FormatObjectId(HtmlGenerateContext &ctx, const u16 obj_id) {
        if(obj_id == UINT16_MAX) {
            return "[any]";
        }

        for(const auto &word: ctx.dict.words) {
            for(const auto &meaning: word->meanings) {
                if(meaning.adj_obj_id == obj_id) {
                    std::string obj_name = word->name;
                    if(!meaning.obj_detail_text.empty()) {
                        obj_name += " (" + meaning.obj_detail_text + ")";
                    }
                    
                    return "<a class=\"text-primary text-decoration-none\" role=\"button\" href=\"" + obj_name + ".html\">" + obj_name + "</a>\n";
                }
            }
        }

        return "[unknown object ID " + std::to_string(obj_id) + "]";
    }

    std::string FormatObjectFileId(HtmlGenerateContext &ctx, const u16 obj_file_id) {
        if(obj_file_id == UINT16_MAX) {
            return "[any]";
        }

        for(const auto &word: ctx.dict.words) {
            for(const auto &meaning: word->meanings) {
                if(meaning.file_id == obj_file_id) {
                    std::string obj_name = word->name;
                    if(!meaning.obj_detail_text.empty()) {
                        obj_name += " (" + meaning.obj_detail_text + ")";
                    }
                    
                    return "<a class=\"text-primary text-decoration-none\" role=\"button\" href=\"" + obj_name + ".html\">" + obj_name + "</a>\n";
                }
            }
        }

        return "[unknown object file ID " + std::to_string(obj_file_id) + "]";
    }

    std::string FormatImage(HtmlGenerateContext &ctx, const std::string &out_path, const u16 file_id) {
        const auto rel_path = std::to_string(file_id) + ".png";
        const auto full_path = out_path + "/" + rel_path;

        switch(ctx.game) {
            case Game::BH2P: {
                TryExportBh2pTexture(ctx.fs, file_id, full_path);
                break;
            }
            case Game::Remix: {
                TryExportRemixTexture(ctx.fs, file_id, full_path);
                break;
            }
        }

        return "<img src=\"" + rel_path + "\" alt=\"Image file ID " + std::to_string(file_id) + "\">";
    }

    std::string GenerateFilter(HtmlGenerateContext &ctx, const std::string &tag, const std::string &name, const Filter &filter) {
        auto cnt = EnterSection(tag, name);
        for(u32 i = 0; i < filter.entries.size(); i++) {
            const auto &entry = filter.entries[i];
            cnt += EnterSection(tag + "-" + std::to_string(i), "Filter " + std::to_string(i));

            cnt += GenerateField("Exclude", entry.exclude);
            cnt += GenerateField("Object category", DefaultNullMask16(entry.obj_category_id, FormatObjectCategoryId));
            cnt += GenerateField("Object subcategory 1", Mask16((int)entry.obj_subcategory_id_1));
            cnt += GenerateField("Object subcategory 2", Mask16((int)entry.obj_subcategory_id_2));
            cnt += GenerateField("Object", FormatObjectId(ctx, entry.obj_id));
            cnt += GenerateField("Adjective category", Mask16(entry.adj_category_id));
            cnt += GenerateField("Adjective subcategory", Mask16(entry.adj_subcategory_id));
            cnt += GenerateField("Adjective ID", Mask16(entry.adj_id));

            cnt += ExitSection();
        }

        cnt += GenerateField("StageObject entity ID", Mask32(filter.stage_object_entity_id));
        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateAtrRep(HtmlGenerateContext &ctx, const std::string &tag, const AiAtrRep &atr_rep) {
        std::string cnt = GenerateField("Mode", DefaultNull(atr_rep.options.mode, FormatAtrRepMode));
        cnt += GenerateField("Only when equipped", atr_rep.options.only_when_equipped);
        if(atr_rep.options.has_custom_emote) {
            cnt += GenerateField("Custom emote", DefaultNull(atr_rep.custom_emote, FormatAiEmoteType));
        }
        cnt += GenerateField("Object category", DefaultNullMask16(atr_rep.obj_category_id, FormatObjectCategoryId));
        cnt += GenerateField("Object subcategory 1", Mask16((int)atr_rep.obj_subcategory_id_1));
        cnt += GenerateField("Object subcategory 2", Mask16((int)atr_rep.obj_subcategory_id_2));
        cnt += GenerateField("Object", FormatObjectId(ctx, atr_rep.obj_id));
        cnt += GenerateField("Adjective category", Mask16(atr_rep.adj_category_id));
        cnt += GenerateField("Adjective subcategory", Mask16(atr_rep.adj_subcategory_id));
        cnt += GenerateField("Adjective ID", Mask16(atr_rep.adj_id));
        if(atr_rep.options.mode == AtrRepMode::UseToolUse) {
            cnt += GenerateFilter(ctx, tag + "-filter", "Filters", atr_rep.filter);
        }

        return cnt;
    }

    std::string GenerateModAtrRep(HtmlGenerateContext &ctx, const std::string &tag, const ModAiAtrRep &mod_atr_rep) {
        std::string cnt = GenerateField("Insert point", mod_atr_rep.insert_point);
        cnt += GenerateAtrRep(ctx, tag, mod_atr_rep.atr_rep);
        return cnt;
    }
    
    std::string GenerateAtrRepList(HtmlGenerateContext &ctx, const std::string &tag, const std::string &name, const std::vector<AiAtrRep> &atr_reps) {
        std::string cnt = EnterSection(tag, name);
        for(u32 i = 0; i < atr_reps.size(); i++) {
            const auto &atr_rep = atr_reps[i];
            cnt += EnterSection(tag + "-" + std::to_string(i), "Atract/repulse " + std::to_string(i));

            cnt += GenerateAtrRep(ctx, tag + "-atr-rep-" + std::to_string(i), atr_rep);

            cnt += ExitSection();
        }

        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateModAtrRepList(HtmlGenerateContext &ctx, const std::string &tag, const std::string &name, const std::vector<ModAiAtrRep> &mod_atr_reps) {
        std::string cnt = EnterSection(tag, name);
        for(u32 i = 0; i < mod_atr_reps.size(); i++) {
            const auto &mod_atr_rep = mod_atr_reps[i];
            cnt += EnterSection(tag + "-" + std::to_string(i), "Atract/repulse modifier " + std::to_string(i));

            cnt += GenerateModAtrRep(ctx, tag + "-mod-atr-rep-" + std::to_string(i), mod_atr_rep);

            cnt += ExitSection();
        }

        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateFrame(HtmlGenerateContext &ctx, const std::string &out_path, const std::string &tag, const std::string &name, const ObjectFrame &frame);

    std::string GenerateFrameChildren(HtmlGenerateContext &ctx, const std::string &out_path, const std::string &tag, const std::vector<ObjectFrame> &children) {
        if(children.empty()) {
            return "";
        }
        
        std::string cnt = EnterSection(tag + "-children", "Children");

        for(u32 i = 0; i < children.size(); i++) {
            const auto &child = children[i];
            cnt += GenerateFrame(ctx, out_path, tag + "-child-" + std::to_string(i), "Frame " + std::to_string(i), child);
        }

        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateFrame(HtmlGenerateContext &ctx, const std::string &out_path, const std::string &tag, const std::string &name, const ObjectFrame &frame) {
        std::string cnt = EnterSection(tag, name + ": " + FormatFrameType(frame.type));

        cnt += GenerateField("X", FORMAT_FX32(frame.x));
        cnt += GenerateField("Y", FORMAT_FX32(frame.y));
        cnt += GenerateField("Rotation", FORMAT_FX32(frame.rot));
        cnt += GenerateField("Enabled", frame.enabled);

        switch(frame.type) {
            case FrameType::Main: {
                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.main.children);
                break;
            }
            case FrameType::Box: {
                if(frame.box.type.has_force) {
                    cnt += EnterSection(tag + "-box-force", "Force field");

                    cnt += GenerateField("Center force", frame.box.force.center_force);
                    cnt += GenerateField("Falloff type", DefaultNull(frame.box.force.options.falloff_type, FormatForceZoneFalloff));
                    cnt += GenerateField("Damping", frame.box.force.damping);
                    cnt += GenerateField("Force X", frame.box.force.force_x);
                    cnt += GenerateField("Force Y", frame.box.force.force_y);

                    cnt += GenerateFilter(ctx, tag + "-box-force-filter", "Filter", frame.box.force.filter);
                }
                if(frame.box.type.has_temperature) {
                    cnt += EnterSection(tag + "-box-temperature", "Temperature field");
                    cnt += GenerateField("Temperature", frame.box.temperature.temperature);
                }
                if(frame.box.type.has_water) {
                    cnt += EnterSection(tag + "-box-water", "Water field");
                    cnt += GenerateField("Water zone type", DefaultNull(frame.box.water.water_type, FormatWaterZoneType));
                }
                if(frame.box.type.has_damage) {
                    cnt += EnterSection(tag + "-box-damage", "Damage field");
                    cnt += GenerateField("Collide damage", frame.box.damage.collide_damage);
                    cnt += GenerateField("DPS", frame.box.damage.dps);
                    cnt += GenerateField("Knockback", frame.box.damage.knockback);
                }

                cnt += GenerateField("Width", FORMAT_FX32(frame.box.width));
                cnt += GenerateField("Height", FORMAT_FX32(frame.box.height));

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.box.children);
                break;
            }
            case FrameType::Circle: {
                if(frame.circle.type.has_force) {
                    cnt += EnterSection(tag + "-circle-force", "Force field");

                    cnt += GenerateField("Center force", frame.circle.force.center_force);
                    cnt += GenerateField("Falloff type", DefaultNull(frame.circle.force.options.falloff_type, FormatForceZoneFalloff));
                    cnt += GenerateField("Damping", frame.circle.force.damping);
                    cnt += GenerateField("Force X", frame.circle.force.force_x);
                    cnt += GenerateField("Force Y", frame.circle.force.force_y);

                    cnt += GenerateFilter(ctx, tag + "-circle-force-filter", "Filter", frame.circle.force.filter);
                }
                if(frame.circle.type.has_temperature) {
                    cnt += EnterSection(tag + "-circle-temperature", "Temperature field");
                    cnt += GenerateField("Temperature", frame.circle.temperature.temperature);
                }
                if(frame.circle.type.has_damage) {
                    cnt += EnterSection(tag + "-circle-damage", "Damage field");
                    cnt += GenerateField("Collide damage", frame.circle.damage.collide_damage);
                    cnt += GenerateField("DPS", frame.circle.damage.dps);
                    cnt += GenerateField("Knockback", frame.circle.damage.knockback);
                }

                cnt += GenerateField("Radius", FORMAT_FX32(frame.circle.radius));
                cnt += GenerateField("Surface force factor", frame.circle.surface_force_factor);

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.circle.children);
                break;
            }
            case FrameType::Polygon: {
                cnt += EnterSection(tag + "-polygon-points", "Polygon points");
                for(u32 i = 0; i < frame.polygon.poly_points.size(); i++) {
                    const auto &point = frame.polygon.poly_points[i];
                    cnt += GenerateField("Point " + std::to_string(i), std::to_string(FORMAT_FX32(point.first)) + ", " + std::to_string(FORMAT_FX32(point.second)));
                }
                cnt += ExitSection();

                cnt += EnterSection(tag + "-polygon-factors", "Surface force factors");
                for(u32 i = 0; i < frame.polygon.surface_force_factors.size(); i++) {
                    cnt += GenerateField("Factor " + std::to_string(i), frame.polygon.surface_force_factors[i]);
                }
                cnt += ExitSection();

                cnt += GenerateField("Top collision only", frame.polygon.top_collision_only);

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.polygon.children);
                break;
            }
            case FrameType::Image: {
                cnt += GenerateField("Texture", FormatImage(ctx, out_path, frame.image.tex_file_id));
                cnt += GenerateField("Mask ID", frame.image.mask_id);
                cnt += GenerateField("Display list data size", frame.image.display_list_data.size());
                // TODO: Display list data
                
                for(u32 i = 0; i < static_cast<size_t>(Limb::Count); i++) {
                    cnt += EnterSection(tag + "-limb-" + std::to_string(i), "Limb: " + DefaultNull(static_cast<Limb>(i), FormatLimb));
                    cnt += GenerateField("Index", frame.image.limb_indices[i]);
                    cnt += ExitSection();
                }

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.image.children);
                break;
            }
            case FrameType::TexQuad: {
                cnt += GenerateField("Body part", DefaultNull(frame.tex_quad.body_part, FormatBodyPart));
                cnt += GenerateField("Z order", frame.tex_quad.z_order);

                cnt += EnterSection(tag + "-tex-quad-points", "Spawn position points");
                for(u32 i = 0; i < 8; i++) {
                    const auto &point = frame.tex_quad.spawn_pos_vecs[i];
                    cnt += GenerateField("Point " + std::to_string(i), std::to_string(FORMAT_FX32(point.first)) + ", " + std::to_string(FORMAT_FX32(point.second)));
                }
                cnt += ExitSection();

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.tex_quad.children);
                break;
            }
            case FrameType::Ellipse: {
                cnt += GenerateField("Width", FORMAT_FX32(frame.ellipse.width));
                cnt += GenerateField("Height", FORMAT_FX32(frame.ellipse.height));

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.ellipse.children);
                break;
            }
            case FrameType::HotSpot: {
                cnt += GenerateField("Type", DefaultNull(frame.hotspot.options.type, FormatHotSpotType));
                cnt += GenerateField("Enabled", frame.hotspot.options.enabled);

                switch(frame.hotspot.options.type) {
                    case HotSpotType::HotSpotAttach: {
                        break;
                    }
                    case HotSpotType::HotSpotCenterOfGravity: {
                        break;
                    }
                    case HotSpotType::HotSpotSaddle: {
                        cnt += GenerateField("Saddle animation", DefaultNull(frame.hotspot.saddle.anim, FormatAnimation));
                        cnt += GenerateField("Is control spot", frame.hotspot.saddle.is_control_spot);
                        cnt += GenerateField("Saddle sorting", DefaultNull(frame.hotspot.saddle.sorting, FormatSaddleSorting));
                        cnt += GenerateField("Can knock off", frame.hotspot.saddle.can_knock_off);
                        cnt += GenerateFilter(ctx, tag + "-saddle-filter", "Filter", frame.hotspot.saddle.filter);
                        if(frame.hotspot.saddle.has_pre_mounted_object) {
                            cnt += GenerateField("Pre-mounted object", FormatObjectId(ctx, frame.hotspot.saddle.pre_mounted_obj_id));
                        }
                        break;
                    }
                    case HotSpotType::HotSpotSaddleSnap: {
                        cnt += GenerateFilter(ctx, tag + "-saddle-snap-filter", "Filter", frame.hotspot.saddle_snap.filter);
                        break;
                    }
                    case HotSpotType::HotSpotContainerOpening: {
                        break;
                    }
                    case HotSpotType::HotSpotEquip: {
                        cnt += GenerateField("Equip location", DefaultNull(frame.hotspot.equip.location, FormatEquipLocation));
                        cnt += GenerateFilter(ctx, tag + "-equip-filter", "Filter", frame.hotspot.equip.filter);
                        if(frame.hotspot.equip.has_pre_equipped_object) {
                            cnt += GenerateField("Pre-equipped object", FormatObjectFileId(ctx, frame.hotspot.equip.pre_equipped_obj_file_id));
                        }
                        break;
                    }
                    case HotSpotType::HotSpotWaypoint: {
                        break;
                    }
                    case HotSpotType::HotSpotSplit: {
                        cnt += GenerateField("Object ID A", FormatObjectFileId(ctx, frame.hotspot.split.obj_id_a));
                        cnt += GenerateField("Split A", std::to_string(FORMAT_FX32(frame.hotspot.split.split_a_x)) + ", " + std::to_string(FORMAT_FX32(frame.hotspot.split.split_a_y)));
                        cnt += GenerateField("Split A rotation", std::to_string(FORMAT_FX32(frame.hotspot.split.split_a_rot)));
                        cnt += GenerateField("Object ID B", FormatObjectFileId(ctx, frame.hotspot.split.obj_id_b));
                        cnt += GenerateField("Split B", std::to_string(FORMAT_FX32(frame.hotspot.split.split_b_x)) + ", " + std::to_string(FORMAT_FX32(frame.hotspot.split.split_b_y)));
                        cnt += GenerateField("Split B rotation", std::to_string(FORMAT_FX32(frame.hotspot.split.split_b_rot)));
                        break;
                    }
                    case HotSpotType::HotSpotLight: {
                        cnt += GenerateField("Light shape", DefaultNull(frame.hotspot.light.shape, FormatLightShape));
                        break;
                    }
                    case HotSpotType::HotSpotEmitter: {
                        cnt += GenerateField("Emit X", frame.hotspot.emitter.emit_x);
                        cnt += GenerateField("Emit Y", frame.hotspot.emitter.emit_y);
                        cnt += GenerateField("Angle", frame.hotspot.emitter.angle);
                        cnt += GenerateField("Spawn interval", frame.hotspot.emitter.spawn_interval);
                        cnt += GenerateField("Emit speed", frame.hotspot.emitter.emit_speed);
                        cnt += GenerateField("Scatter shot", frame.hotspot.emitter.scatter_shot);
                        cnt += GenerateField("Spawn count", frame.hotspot.emitter.spawn_count);
                        cnt += GenerateField("Apply gravity", frame.hotspot.emitter.apply_gravity);
                        cnt += GenerateField("Emit object", FormatObjectId(ctx, frame.hotspot.emitter.emit_object));
                        cnt += GenerateField("Emitter label", DefaultNull(frame.hotspot.emitter.label, FormatEmitterLabel));
                        break;
                    }
                    case HotSpotType::HotSpotFire: {
                        cnt += GenerateField("Fire effect size", DefaultNull(frame.hotspot.fire.fire_size, FormatFireEffectSize));
                        cnt += GenerateField("Fire enabled", frame.hotspot.fire.enabled);
                        break;
                    }
                    case HotSpotType::JointFixed: {
                        break;
                    }
                    case HotSpotType::JointRevolute: {
                        cnt += GenerateField("Is motor", frame.hotspot.joint_revolute.is_motor);
                        cnt += GenerateField("Auto torque", frame.hotspot.joint_revolute.auto_torque);
                        cnt += GenerateField("Reference object", FormatObjectId(ctx, frame.hotspot.joint_revolute.ref_obj_id));
                        cnt += GenerateField("Part X", frame.hotspot.joint_revolute.part_x);
                        cnt += GenerateField("Part Y", frame.hotspot.joint_revolute.part_y);
                        cnt += GenerateField("Part rotation", frame.hotspot.joint_revolute.part_rot);
                        break;
                    }
                    case HotSpotType::JointRotationalSpring: {
                        cnt += GenerateField("Stiffness", frame.hotspot.joint_rotational_spring.stiffness);
                        cnt += GenerateField("Reference object", FormatObjectId(ctx, frame.hotspot.joint_rotational_spring.ref_obj_id));
                        cnt += GenerateField("Part X", frame.hotspot.joint_rotational_spring.part_x);
                        cnt += GenerateField("Part Y", frame.hotspot.joint_rotational_spring.part_y);
                        cnt += GenerateField("Part rotation", frame.hotspot.joint_rotational_spring.part_rot);
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
                        cnt += GenerateField("Digger radius", frame.hotspot.digger.radius);
                        break;
                    }
                }

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.hotspot.children);
                break;
            }
            case FrameType::Reference: {
                cnt += GenerateField("Part? object", FormatObjectFileId(ctx, frame.reference.part_id_obj_file_id));

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.reference.children);
                break;
            }
            case FrameType::SFAnimation: {
                cnt += GenerateField("Sprite ID", frame.sf_anim.sprite_id);
                cnt += GenerateField("Animation ID", frame.sf_anim.animation_idx);
                cnt += GenerateField("Z order", frame.sf_anim.z_order);
                cnt += GenerateField("Speed", frame.sf_anim.speed);
                cnt += GenerateField("Disable animation", frame.sf_anim.disable_anim);
                cnt += GenerateField("Sprite file ID", frame.sf_anim.sprite_file_id);

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.sf_anim.children);
                break;
            }
            case FrameType::Particle: {
                break;
            }
            case FrameType::Stamp: {
                cnt += GenerateField("Sprite ID", frame.stamp.sprite_id);
                cnt += GenerateField("Scale", frame.stamp.scale);
                cnt += GenerateField("Z order", frame.stamp.z_order);
                cnt += GenerateField("Flipped", frame.stamp.flipped);

                if(frame.stamp.has_spawn_pos) {
                    cnt += EnterSection(tag + "-stamp-points", "Spawn position points");
                    for(u32 i = 0; i < 8; i++) {
                        const auto &point = frame.stamp.spawn_pos_vecs[i];
                        cnt += GenerateField("Point " + std::to_string(i), std::to_string(FORMAT_FX32(point.first)) + ", " + std::to_string(FORMAT_FX32(point.second)));
                    }
                    cnt += ExitSection();
                }

                cnt += GenerateFrameChildren(ctx, out_path, tag, frame.stamp.children);
                break;
            }
            default: {
                break;
            }
        }

        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateTarget(const std::string &tag, const ActionTargetData &data) {
        std::string cnt = EnterSection(tag + "-target", "Target");

        cnt += GenerateField("Target", DefaultNull(data.target, FormatActionTarget));
        cnt += GenerateField("Stage entity", Mask32(data.target_stage_entity));

        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateAction(HtmlGenerateContext &ctx, const std::string &out_path, const std::string &tag, const std::string &name, const ActionEntry &action) {
        std::string cnt = EnterSection(tag, name);

        switch(action.type) {
            case ActionType::SpawnObject: {
                cnt += GenerateField("Is particle", action.spawn_obj.is_particle);
                cnt += GenerateField("Object", FormatObjectFileId(ctx, action.spawn_obj.spawn_obj_file_id));

                if(!action.spawn_obj.is_particle) {
                    cnt += GenerateField("Inherit adjectives from parent", action.spawn_obj.inherit_adjs_from_parent);
                    if(!action.spawn_obj.adjs.empty()) {
                        cnt += EnterSection(tag + "-spawn-obj-adjs", "Adjectives");
                        for(const auto &adj_id: action.spawn_obj.adjs) {
                            cnt += GenerateField("Adjective ID", Mask16(adj_id));
                        }
                        cnt += ExitSection();
                    }
                }

                cnt += GenerateField("HotSpot index", action.spawn_obj.hotspot_idx);
                cnt += GenerateField("Max objects", action.spawn_obj.options.max_objects);
                cnt += GenerateField("Stop if no spawn", action.spawn_obj.options.stop_if_no_spawn);
                break;
            }
            case ActionType::EnableShape: {
                cnt += GenerateField("Index", action.enable_shape.index);
                cnt += GenerateField("Toggle", action.enable_shape.toggle);
                break;
            }
            case ActionType::Destroy: {
                cnt += GenerateTarget(tag, action.destroy.target);
                cnt += GenerateField("Poof cloud", action.destroy.options.poof_cloud);
                cnt += GenerateField("Destroy connected", action.destroy.options.destroy_connected);
                break;
            }
            case ActionType::PlaySfx: {
                cnt += GenerateField("Group ID", action.play_sfx.group_id);
                cnt += GenerateField("SeqArc ID", action.play_sfx.seq_arc_or_music_id);
                cnt += GenerateField("SFX ID", action.play_sfx.sfx_id);
                cnt += GenerateField("Sound attribute", DefaultNull(action.play_sfx.sound_attr, FormatSoundAttribute));

                if(!action.play_sfx.filters.empty()) {
                    cnt += EnterSection(tag + "-play-sfx-filters", "Audio filters");

                    for(u32 i = 0; i < action.play_sfx.filters.size(); i++) {
                        const auto &entry = action.play_sfx.filters[i];
                        cnt += EnterSection(tag + "-play-sfx-filter-" + std::to_string(i), "Filter " + std::to_string(i));

                        cnt += GenerateField("Object category", DefaultNullMask16(entry.obj_category_id, FormatObjectCategoryId));
                        cnt += GenerateField("Object subcategory 1", Mask16(entry.obj_subcategory_id_1));
                        cnt += GenerateField("Object subcategory 2", Mask16(entry.obj_subcategory_id_2));
                        cnt += GenerateField("Object", FormatObjectId(ctx, entry.obj_id));

                        cnt += ExitSection();
                    }

                    cnt += ExitSection();
                }
                break;
            }
            case ActionType::Activate:
            case ActionType::Deactivate:
            case ActionType::Toggle: {
                cnt += GenerateTarget(tag, action.activate_deactivate_toggle.target);
                break;
            }
            case ActionType::ApplyForce: {
                cnt += GenerateTarget(tag, action.apply_force.target);
                cnt += GenerateField("Force X", FORMAT_FX32(action.apply_force.force_x));
                cnt += GenerateField("Force Y", FORMAT_FX32(action.apply_force.force_y));
                cnt += GenerateField("Torque", FORMAT_FX32(action.apply_force.torque));
                cnt += GenerateField("Not absolute force", action.apply_force.not_absolute_force);
                break;
            }
            case ActionType::ModifyAiState: {
                cnt += GenerateTarget(tag, action.modify_ai_state.target);
                cnt += GenerateField("Mood", DefaultNull(action.modify_ai_state.mood, FormatAiMood));
                break;
            }
            case ActionType::ModifyAtrRepList: {
                cnt += GenerateTarget(tag, action.modify_atr_rep_list.target);
                cnt += GenerateModAtrRepList(ctx, tag + "-mod-atr-rep-list-normal", "Normal atract/repulse modifiers", action.modify_atr_rep_list.normal);
                cnt += GenerateModAtrRepList(ctx, tag + "-mod-atr-rep-list-exclude", "Exclude atract/repulse modifiers", action.modify_atr_rep_list.exclude);
                break;
            }
            case ActionType::SwapObject: {
                cnt += GenerateTarget(tag, action.swap_obj.target);
                cnt += GenerateField("Swap object", FormatObjectFileId(ctx, action.swap_obj.swap_obj_file_id));
                cnt += GenerateField("Use previous self", action.swap_obj.options.use_previous_self);
                cnt += GenerateField("Inherit adjectives from parent", action.swap_obj.options.inherit_adjs_from_parent);
                if(!action.swap_obj.adjs.empty()) {
                    cnt += EnterSection(tag + "-swap-obj-adjs", "Adjectives");
                    for(const auto &adj_id: action.swap_obj.adjs) {
                        cnt += GenerateField("Adjective ID", Mask16(adj_id));
                    }
                    cnt += ExitSection();
                }
                break;
            }
            case ActionType::MoveTo: {
                cnt += GenerateTarget(tag, action.move_to.target);
                cnt += GenerateField("Target X", action.move_to.target_x);
                cnt += GenerateField("Target Y", action.move_to.target_y);
                cnt += GenerateField("Frame count", action.move_to.frame_count);
                break;
            }
            case ActionType::MoveRelative: {
                cnt += GenerateTarget(tag, action.move_relative.target);
                cnt += GenerateField("Delta X", action.move_relative.delta_x);
                cnt += GenerateField("Delta Y", action.move_relative.delta_y);
                cnt += GenerateField("Frame count", action.move_relative.frame_count);
                break;
            }
            case ActionType::AttachTo: {
                cnt += GenerateField("Entity ID A", Mask16(action.attach_to.entity_id_a));
                cnt += GenerateField("Unused A", action.attach_to.unused_a);
                cnt += GenerateField("Entity ID B", Mask16(action.attach_to.entity_id_b));
                cnt += GenerateField("Unused B", action.attach_to.unused_b);
                break;
            }
            case ActionType::DetachFromAll: {
                break;
            }
            case ActionType::DealDamage: {
                cnt += GenerateTarget(tag, action.deal_damage.target);
                cnt += GenerateField("Damage amount", action.deal_damage.damage_amount);
                break;
            }
            case ActionType::Split: {
                cnt += GenerateTarget(tag, action.split.target);
                cnt += GenerateField("Unused", action.split.unused);
                break;
            }
            case ActionType::ThrowAtTarget: {
                cnt += GenerateField("Throw speed (pixels-per-frame)", action.throw_at_target.throw_speed_ppf);
                cnt += GenerateField("Animation", DefaultNull(action.throw_at_target.anim, FormatAnimation));
                break;
            }
            case ActionType::FireProjectile: {
                cnt += GenerateField("Is particle", action.fire_projectile.is_particle);
                cnt += GenerateField("Projectile object", FormatObjectFileId(ctx, action.fire_projectile.spawn_obj_file_id));
                cnt += GenerateField("HotSpot index", action.fire_projectile.hotspot_idx);
                cnt += GenerateField("Ignore gravity", action.fire_projectile.options.ignore_gravity);
                cnt += GenerateField("Index is label", action.fire_projectile.options.index_is_label);
                cnt += GenerateField("Fly speed (pixels-per-frame)", action.fire_projectile.fly_speed_ppf);
                break;
            }
            case ActionType::SetTemperature: {
                cnt += GenerateTarget(tag, action.set_temperature.target);
                cnt += GenerateField("Temperature", action.set_temperature.temperature);
                cnt += GenerateField("Unused", action.set_temperature.unused);
                break;
            }
            case ActionType::Animation: {
                cnt += GenerateTarget(tag, action.animation.target);
                cnt += GenerateField("New animation", DefaultNull(action.animation.new_anim, FormatAnimation));
                break;
            }
            case ActionType::Wait: {
                cnt += GenerateField("Frame count", action.wait.frame_count);
                break;
            }
            case ActionType::EmptyFill: {
                cnt += GenerateField("Is not empty", action.empty_fill.is_not_empty);
                break;
            }
            case ActionType::SpawnRandom: {
                cnt += EnterSection(tag + "-spawn-random-entries", "Entries");
                for(u32 i = 0; i < action.spawn_random.entries.size(); i++) {
                    const auto &entry = action.spawn_random.entries[i];
                    cnt += EnterSection(tag + "-spawn-random-entry-" + std::to_string(i), "Entry " + std::to_string(i));

                    cnt += GenerateField("Object", FormatObjectFileId(ctx, entry.spawn_id));
                    cnt += GenerateField("Adjective ID", Mask16(entry.spawn_adj_id));

                    cnt += ExitSection();
                }
                cnt += ExitSection();

                cnt += GenerateField("Inherit adjectives from parent", action.spawn_random.inherit_adjs_from_parent);
                cnt += GenerateField("HotSpot index", action.spawn_random.hotspot_idx);
                cnt += GenerateField("Max objects", action.spawn_random.options.max_objects);
                cnt += GenerateField("Stop if no spawn", action.spawn_random.options.stop_if_no_spawn);
                break;
            }
            case ActionType::SetOnFire: {
                cnt += GenerateTarget(tag, action.set_on_fire.target);
                cnt += GenerateField("Set on fire", action.set_on_fire.set_on_fire);
                break;
            }
            case ActionType::SetVariable: {
                cnt += GenerateField("Value", action.set_var.value);
                cnt += GenerateField("Register name", action.set_var.register_name);
                break;
            }
            case ActionType::Add: {
                cnt += GenerateField("Amount", action.add.amount);
                cnt += GenerateField("Register name", action.add.register_name);
                break;
            }
            case ActionType::EndLevel: {
                cnt += GenerateField("Section ID", action.end_level.section_id);
                cnt += GenerateField("Cinematic file ID", action.end_level.cinematic_file_id);
                break;
            }
            case ActionType::SpawnObjectAt: {
                cnt += GenerateTarget(tag, action.spawn_obj_at.target);
                cnt += GenerateField("Is particle", action.spawn_obj_at.is_particle);
                cnt += GenerateField("Object", FormatObjectFileId(ctx, action.spawn_obj_at.spawn_obj_file_id));
                if(!action.spawn_obj_at.adjs.empty()) {
                    cnt += GenerateField("Inherit adjectives from parent", action.spawn_obj_at.inherit_adjs_from_parent);
                    if(!action.spawn_obj_at.adjs.empty()) {
                        cnt += EnterSection(tag + "-spawn-obj-at-adjs", "Adjectives");
                        for(const auto &adj_id: action.spawn_obj_at.adjs) {
                            cnt += GenerateField("Adjective ID", Mask16(adj_id));
                        }
                        cnt += ExitSection();
                    }
                }
                cnt += GenerateField("Relative position X", action.spawn_obj_at.relative_pos_x);
                cnt += GenerateField("Relative position Y", action.spawn_obj_at.relative_pos_y);
                cnt += GenerateField("Bounce towards Maxwell", action.spawn_obj_at.options_2.bounce_towards_maxwell);
                cnt += GenerateField("Make draggable", action.spawn_obj_at.options_2.make_draggable);
                cnt += GenerateField("Supress adjectives' banner", action.spawn_obj_at.options_2.suppress_adjs_banner);
                cnt += GenerateField("Max objects", action.spawn_obj_at.options_1.max_objects);
                cnt += GenerateField("Stop if no spawn", action.spawn_obj_at.options_1.stop_if_no_spawn);
                break;
            }
            case ActionType::ShowEmote: {
                cnt += GenerateTarget(tag, action.show_emote.target);
                cnt += GenerateField("Emote", DefaultNull(action.show_emote.next_emote, FormatAiEmoteType));
                break;
            }
            case ActionType::Explode: {
                cnt += GenerateField("Explosion size", action.explode.explosion_size);
                cnt += GenerateField("Explode countdown", action.explode.explode_countdown);
                break;
            }
            case ActionType::ImageSwap: {
                cnt += GenerateTarget(tag, action.image_swap.target);
                cnt += GenerateField("Image", FormatImage(ctx, out_path, action.image_swap.file_id));
                break;
            }
            case ActionType::Cinematic: {
                cnt += GenerateField("Section ID", action.cinematic.section_id);
                cnt += GenerateField("Cinematic file ID", action.cinematic.cinematic_file_id);
                break;
            }
            case ActionType::ShowNotepad: {
                cnt += GenerateField("Show", action.show_notepad.show);
                break;
            }
            case ActionType::EncaseInIce: {
                cnt += GenerateTarget(tag, action.encase_in_ice.target);
                break;
            }
            case ActionType::SetStageObject: {
                cnt += GenerateTarget(tag, action.encase_in_ice.target);
                cnt += GenerateField("Mode (attract/repulse)", DefaultNull(action.set_stage_obj.mode, FormatAtrRepMode));
                cnt += GenerateField("Ignore StageObject line of sight", action.set_stage_obj.ignore_stage_object_line_of_sight);
                cnt += GenerateField("New target entity ID", Mask32(action.set_stage_obj.new_target_entity_id));
                break;
            }
            case ActionType::EnableEntity: {
                cnt += GenerateTarget(tag, action.enable_entity.target);
                cnt += GenerateField("Enable", action.enable_entity.enable);
                break;
            }
            case ActionType::Switch: {
                cnt += GenerateField("Switch type", DefaultNull(action.swtch.type, FormatSwitchType));
                cnt += EnterSection(tag + "-switch-action-lists", "Action lists");
                for(u32 i = 0; i < action.swtch.switch_actions.size(); i++) {
                    const auto &action_list = action.swtch.switch_actions[i];
                    cnt += EnterSection(tag + "-switch-action-list-" + std::to_string(i), "Action list " + std::to_string(i));

                    for(u32 j = 0; j < action_list.size(); j++) {
                        const auto &action_entry = action_list[j];
                        cnt += GenerateAction(ctx, out_path, tag + "-switch-action-" + std::to_string(i) + "-" + std::to_string(j), "Action", action_entry);
                    }

                    cnt += ExitSection();
                }
                cnt += ExitSection();
                break;
            }
            case ActionType::EnableSFAnim: {
                cnt += GenerateField("Index", action.enable_sf_anim.index);
                cnt += GenerateField("Toggle", action.enable_sf_anim.toggle);
                break;
            }
            case ActionType::RotateEntity: {
                cnt += GenerateTarget(tag, action.rotate_entity.target);
                cnt += GenerateField("Rotation per second", action.rotate_entity.rot_per_sec);
                break;
            }
            case ActionType::ApplyAdjective: {
                cnt += GenerateTarget(tag, action.apply_adj.target);
                cnt += GenerateField("Adjective ID", Mask16(action.apply_adj.adj_id));
                cnt += GenerateField("Suppress banner", action.apply_adj.suppress_banner);
                break;
            }
            case ActionType::ShowFeedback: {
                cnt += GenerateTarget(tag, action.show_feedback.target);
                cnt += GenerateField("Positive feedback", action.show_feedback.options.positive_feedback);
                cnt += GenerateField("Is screen space", action.show_feedback.options.is_screen_space);
                cnt += GenerateField("Relative position X", action.show_feedback.relative_pos_x);
                cnt += GenerateField("Relative position Y", action.show_feedback.relative_pos_y);
                break;
            }
            case ActionType::Lock: {
                cnt += GenerateTarget(tag, action.lock.target);
                cnt += GenerateFilter(ctx, tag + "-lock-filter", "Filters", action.lock.filter);
                break;
            }
            case ActionType::NoDrag: {
                break;
            }
            case ActionType::SetInterruptFlag: {
                cnt += GenerateField("Trigger flag slot", DefaultNull(action.set_interrupt_flag.options.trigger_slot, FormatTriggerFlagSlot));
                cnt += GenerateField("Set flag", action.set_interrupt_flag.options.set_flag);
                cnt += GenerateField("Parent trigger type", DefaultNull(action.set_interrupt_flag.parent_trigger_type, FormatTriggerType));
                break;
            }
            case ActionType::Shock: {
                cnt += GenerateTarget(tag, action.shock.target);
                break;
            }
            case ActionType::Untouchable: {
                cnt += GenerateTarget(tag, action.untouchable.target);
                cnt += GenerateField("Setting", DefaultNull(action.untouchable.setting, FormatUntouchableSetting));
                break;
            }
            case ActionType::ModifyLineOfSight: {
                cnt += GenerateTarget(tag, action.modify_line_of_sight.target);
                cnt += GenerateField("Line of sight", action.modify_line_of_sight.line_of_sight);
                break;
            }
            default: {
                break;
            }
        }

        cnt += ExitSection();

        return cnt;
    }

    std::string GenerateTrigger(HtmlGenerateContext &ctx, const std::string &out_path, const std::string &tag, const std::string &name, const TriggerAction &ta) {
        std::string cnt = EnterSection(tag, name);

        cnt += GenerateField("Non-repeatable", ta.options.non_repeatable);

        switch(ta.options.type) {
            case TriggerType::OnCollide: {
                cnt += GenerateFilter(ctx, tag + "-on-collide-filter", "Filters", ta.trigger.on_collide.filter);
                cnt += GenerateField("Minimum speed (squared)", ta.trigger.on_collide.min_speed_sq);
                cnt += GenerateField("Use other speed", ta.trigger.on_collide.use_other_speed);
                cnt += GenerateField("Only when fired", ta.trigger.on_collide.only_when_fired);
                break;
            }
            case TriggerType::OnCreate: {
                break;
            }
            case TriggerType::OnDestroy: {
                break;
            }
            case TriggerType::OnConsumed: {
                cnt += GenerateFilter(ctx, tag + "-on-consumed-filter", "Filters", ta.trigger.on_consumed.filter);
                break;
            }
            case TriggerType::OnActivated:
            case TriggerType::OnDeactivated: {
                break;
            }
            case TriggerType::OnUsed: {
                cnt += GenerateFilter(ctx, tag + "-on-used-filter", "Filters", ta.trigger.on_used.filter);
                cnt += GenerateField("Use icon", DefaultNull(ta.trigger.on_used.icon, FormatUseIcon));
                break;
            }
            case TriggerType::OnUseEquipped: {
                cnt += GenerateFilter(ctx, tag + "-on-used-filter", "Filters", ta.trigger.on_use_equipped.filter);
                cnt += GenerateField("Use icon", DefaultNull(ta.trigger.on_use_equipped.icon, FormatUseIcon));
                break;
            }
            case TriggerType::OnVehicleAction: {
                cnt += GenerateFilter(ctx, tag + "-on-used-filter", "Filters", ta.trigger.on_vehicle_action.filter);
                cnt += GenerateField("Use icon", DefaultNull(ta.trigger.on_vehicle_action.icon, FormatUseIcon));
                break;
            }
            case TriggerType::OnObjectSwap: {
                break;
            }
            case TriggerType::OnModifyCharge: {
                cnt += GenerateField("Charge modification trigger type", DefaultNull(ta.trigger.on_mod_charge.type, FormatChargeModificationTriggerType));
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
                cnt += GenerateFilter(ctx, tag + "-on-attached-detached-filter", "Filters", ta.trigger.on_attached_detached.filter);
                break;
            }
            case TriggerType::OnSight: {
                cnt += GenerateFilter(ctx, tag + "-on-sight-filter", "Filters", ta.trigger.on_sight.filter);
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
                cnt += GenerateTrigger(ctx, out_path, tag + "-cond-a-trigger", "Condition A trigger", *ta.trigger.condition.cond_a_trigger);
                cnt += GenerateTrigger(ctx, out_path, tag + "-cond-b-trigger", "Condition B trigger", *ta.trigger.condition.cond_b_trigger);
                break;
            }
            case TriggerType::OnCheckVariable: {
                cnt += GenerateField("Only check on change", ta.trigger.on_check_var.only_check_on_change);
                cnt += GenerateField("Comparison", DefaultNull(ta.trigger.on_check_var.comp, FormatScriptComparison));
                cnt += GenerateField("Register trigger value", ta.trigger.on_check_var.register_trigger_value);
                cnt += GenerateField("Register name", ta.trigger.on_check_var.register_name);
                break;
            }
            case TriggerType::OnUpdate: {
                break;
            }
            case TriggerType::OnContained:
            case TriggerType::OnUncontained: {
                cnt += GenerateFilter(ctx, tag + "-on-contained-uncontained-filter", "Filters", ta.trigger.on_contained_uncontained.filter);
                break;
            }
            case TriggerType::OnObjectAdded: {
                cnt += GenerateFilter(ctx, tag + "-on-object-added-filter", "Filters", ta.trigger.on_obj_added.filter);
                cnt += GenerateField("Unique objects", ta.trigger.on_obj_added.options.unique_objects);
                cnt += GenerateField("Unique adjectives", ta.trigger.on_obj_added.options.unique_adjectives);
                cnt += GenerateField("Detection mode", DefaultNull(ta.trigger.on_obj_added.options.mode, FormatDetectionMode));
                break;
            }
            case TriggerType::OnAiState: {
                cnt += GenerateField("Goal mood", DefaultNull(ta.trigger.on_ai_state.goal_mood, FormatAiMood));
                break;
            }
            case TriggerType::OnAiAction: {
                cnt += GenerateFilter(ctx, tag + "-on-ai-action-filter", "Filters", ta.trigger.on_ai_action.filter);
                cnt += GenerateField("Action mode (attract/repulse)", DefaultNull(ta.trigger.on_ai_action.action, FormatAtrRepMode));
                break;
            }
            case TriggerType::OnObjectCountInArea: {
                cnt += GenerateFilter(ctx, tag + "-on-obj-count-in-area-filter", "Filters", ta.trigger.on_obj_count_in_area.filter);
                break;
            }
            case TriggerType::OnDistance: {
                cnt += GenerateFilter(ctx, tag + "-on-distance-filter", "Filters", ta.trigger.on_distance.filter);
                cnt += GenerateField("Trigger distance", ta.trigger.on_distance.trigger_distance);
                break;
            }
            case TriggerType::OnVelocity: {
                cnt += GenerateField("Compare condition", DefaultNull(ta.trigger.on_velocity.compare_condition, FormatScriptComparison));
                cnt += GenerateField("trigger velocity (squared)", ta.trigger.on_velocity.trigger_velocity_sq);
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
                cnt += GenerateFilter(ctx, tag + "-on-ai-equip-unequip-filter", "Filters", ta.trigger.on_ai_equip_unequip.filter);
                break;
            }
            case TriggerType::OnAiConsume: {
                cnt += GenerateFilter(ctx, tag + "-on-ai-consume-filter", "Filters", ta.trigger.on_ai_consume.filter);
                break;
            }
            case TriggerType::OnEmpty:
            case TriggerType::OnFill: {
                cnt += GenerateFilter(ctx, tag + "-on-empty-fill-filter", "Filters", ta.trigger.on_empty_fill.filter);
                break;
            }
            case TriggerType::OnModifyIntegrity: {
                cnt += GenerateFilter(ctx, tag + "-on-modify-integrity-filter", "Filters", ta.trigger.on_modify_integrity.filter);
                break;
            }
            case TriggerType::OnHearSound: {
                cnt += GenerateField("Sound attribute", DefaultNull(ta.trigger.on_hear_sound.attr, FormatSoundAttribute));
                break;
            }
            case TriggerType::OnMounted:
            case TriggerType::OnUnmounted: {
                cnt += GenerateFilter(ctx, tag + "-on-mounted-unmounted-filter", "Filters", ta.trigger.on_mounted_unmounted.filter);
                cnt += GenerateField("Control spot only", ta.trigger.on_mounted_unmounted.control_spot_only);
                break;
            }
            case TriggerType::TriggerGroup: {
                cnt += GenerateField("Only check on change", ta.trigger.group.only_check_on_change);
                cnt += GenerateField("Comparison", DefaultNull(ta.trigger.group.comp, FormatScriptComparison));
                cnt += GenerateField("Register trigger value", ta.trigger.group.register_trigger_value);
                cnt += GenerateField("Register name", ta.trigger.group.register_name);

                for(u32 i = 0; i < ta.trigger.group.group_triggers.size(); i++) {
                    cnt += GenerateTrigger(ctx, out_path, tag + "-group-" + std::to_string(i), "Group trigger " + std::to_string(i), ta.trigger.group.group_triggers[i]);
                }
                break;
            }
            case TriggerType::OnApplyAdjective:
            case TriggerType::OnKickAdjective: {
                cnt += GenerateFilter(ctx, tag + "-on-apply-kick-adjective-filter", "Filters", ta.trigger.on_apply_kick_adj.filter);
                break;
            }
            default: {
                break;
            }
        }

        for(u32 i = 0; i < ta.actions.size(); i++) {
            const auto &action = ta.actions[i];
            cnt += GenerateAction(ctx, out_path, tag + "-action-" + std::to_string(i), "Action " + std::to_string(i) + ": " + FormatActionType(action.type), action);
        }

        cnt += ExitSection();

        return cnt;
    }

}

namespace cli {

    void GenerateObjectsHtml(const std::string &in_index, const std::string &in_package, const std::string &game_str, const std::string &lang_str, const std::string &out_dir) {
        HtmlGenerateContext ctx = {};

        if(!ParseGame(game_str, ctx.game)) {
            std::cerr << "Invalid game provided..." << std::endl;
            return;
        }
        
        fs::StdioFile rf_index(in_index);
        R_TRY_ERRLOG(rf_index.OpenRead(fs::FileCompression::None), "Unable to open index file");

        fs::StdioFile rf_package(in_package);
        R_TRY_ERRLOG(rf_package.OpenRead(fs::FileCompression::None), "Unable to open package file");

        R_TRY_ERRLOG(ctx.fs.ReadFrom(rf_index, rf_package), "Unable to read filesystem");

        switch(ctx.game) {
            case Game::BH2P: {
                bh2p::Language lang;
                if(!ParseBh2pLanguage(lang_str, lang, true)) {
                    std::cerr << "Invalid language provided..." << std::endl;
                    return;
                }

                R_TRY_ERRLOG(bh2p::def::ObjectDictionaries[static_cast<size_t>(lang)].ReadFrom(ctx.fs, ctx.dict), "Unable to read BH2P dictionary");
                break;
            }
            case Game::Remix: {
                remix::Language lang;
                if(!ParseRemixLanguage(lang_str, lang)) {
                    std::cerr << "Invalid language provided..." << std::endl;
                    return;
                }

                R_TRY_ERRLOG(remix::def::ObjectDictionaries[static_cast<size_t>(lang)].ReadFrom(ctx.fs, ctx.dict), "Unable to read Remix dictionary");
                break;
            }
        }

        struct stat st = {};
        if((stat(out_dir.c_str(), &st) != 0) || !S_ISDIR(st.st_mode)) {
            mkdir(out_dir.c_str(), 0755);
        }

        std::string index_html = IndexHtml;

        std::string objs;

        for(const auto &word: ctx.dict.words) {
            for(const auto &meaning: word->meanings) {
                auto &file = ctx.fs.GetFile(meaning.file_id);
                R_TRY_ERRLOG(file.OpenRead(fs::FileCompression::None), "Unable to open object file");
                ScopeGuard close([&]() {
                    file.Close();
                });

                fmt::Object obj;
                R_TRY_ERRLOG(obj.ReadFrom(file), "Unable to read object file");

                auto obj_name = word->name;
                if(!meaning.obj_detail_text.empty()) {
                    obj_name += " (" + meaning.obj_detail_text + ")";
                }

                const auto obj_entry = MakeObjectEntry(meaning.file_id, obj_name, obj);
                objs += obj_entry + "\n";

                std::string obj_html = ObjectHtml;

                std::string cnt;
                
                cnt += EnterSection("dict", "Dictionary");

                cnt += GenerateField("File ID", meaning.file_id);
                cnt += GenerateField("Word ID", word->word_id);
                cnt += GenerateField("Unk2", meaning.unk2);
                cnt += GenerateField("Unk3", meaning.unk3_object_id);

                cnt += ExitSection();
                
                cnt += EnterSection("header", "Header");

                cnt += GenerateField("Category", DefaultNull(obj.header.category_id, FormatObjectCategoryId));
                cnt += GenerateField("Subcategory 1", (int)obj.header.subcategory_id_1);
                cnt += GenerateField("Subcategory 2", (int)obj.header.subcategory_id_2);
                cnt += GenerateField("Object ID", obj.header.obj_id);
                cnt += GenerateField("Width", obj.header.width);
                cnt += GenerateField("Height", obj.header.height);

                cnt += ExitSection();

                cnt += EnterSection("generic", "Generic");

                cnt += GenerateField("Ignores force fields", obj.generic.options_1.ignores_force_fields);
                cnt += GenerateField("Ignores gravity", obj.generic.options_1.ignores_gravity);
                cnt += GenerateField("TA not active", obj.generic.options_1.ta_not_active);
                cnt += GenerateField("Picking uses region", obj.generic.options_1.picking_uses_region);
                cnt += GenerateField("Equip size requirement", DefaultNull(obj.generic.options_1.req, FormatEquipSizeRequirement));
                cnt += GenerateField("Vehicle animation", DefaultNull(obj.generic.options_2.vehicle_anim, FormatVehicleAnimation));
                cnt += GenerateField("Update physics from animations", obj.generic.options_2.update_physics_from_animations);
                cnt += GenerateField("Rope length", obj.generic.rope_length);
                cnt += GenerateField("Clip size", obj.generic.clip_size);
                cnt += GenerateField("Budget class", obj.generic.budget_class);
                if(obj.generic.options_1.has_climb_filter) {
                    cnt += GenerateFilter(ctx, "climb-filter", "Climb filters", obj.generic.climb_filter);
                }

                cnt += ExitSection();

                cnt += EnterSection("movement", "Movement");
                cnt += GenerateField("Movement speed", obj.movement.movement_speed);
                cnt += GenerateField("Jump height", obj.movement.jump_height);
                cnt += GenerateField("Grant jump", obj.movement.options.grant_jump);
                cnt += GenerateField("Include rider air movement", obj.movement.options.include_rider_air_movement);
                cnt += GenerateField("Requires takeoff", obj.movement.options.requires_takeoff);
                cnt += GenerateField("Grants speed", obj.movement.options.grants_speed);
                cnt += GenerateField("Ground motion", DefaultNull(obj.movement.options.ground_motion, FormatGroundMotion));
                cnt += GenerateField("Grants fly", obj.movement.options.grants_fly);
                cnt += GenerateField("Movement H flip", obj.movement.options.movement_h_flip);

                cnt += ExitSection();

                cnt += EnterSection("ai", "Ai");

                cnt += GenerateField("AI mood", DefaultNull(obj.ai.ai_mood, FormatAiMood));
                cnt += GenerateField("AI enabled", obj.ai.options.ai_enabled);
                cnt += GenerateField("Dig enabled", obj.ai.options.dig_enabled);
                cnt += GenerateField("Split enabled", obj.ai.options.split_enabled);
                cnt += GenerateField("Shoot enabled", obj.ai.options.shoot_enabled);
                cnt += GenerateField("Sight distance (tiles)", obj.ai.sight_distance_tiles);
                cnt += GenerateField("Visibility factor", obj.ai.visibility_factor);
                cnt += GenerateField("React size compare", DefaultNull(obj.ai.react_size_compare, FormatAiReactSizeCompare));
                cnt += GenerateField("Attack damage", obj.ai.attack_damage);
                cnt += GenerateAtrRepList(ctx, "ai", "Attracts/repulses", obj.ai.atr_rep_list.atr_reps);

                cnt += ExitSection();

                cnt += EnterSection("container", "Container");
                cnt += GenerateField("Open container", obj.container.options.open_container);
                cnt += GenerateField("Show contained objects", obj.container.options.show_contained_objects);
                cnt += GenerateField("Display contained objects at bottom", obj.container.options.display_contained_objects_at_bottom);
                cnt += GenerateField("Is cannon", obj.container.options.is_cannon);
                cnt += GenerateField("Container width", obj.container.container_width);
                cnt += GenerateField("Container height", obj.container.container_height);

                if(!obj.container.contained_obj_file_ids.empty()) {
                    cnt += EnterSection("container-contained-objects", "Contained objects");
                    for(u32 i = 0; i < obj.container.contained_obj_file_ids.size(); i++) {
                        const auto obj_file_id = obj.container.contained_obj_file_ids[i];
                        cnt += GenerateField("Object " + std::to_string(i), FormatObjectFileId(ctx, obj_file_id));
                    }
                    cnt += ExitSection();
                }

                cnt += ExitSection();

                cnt += EnterSection("electricity", "Electricity");

                cnt += GenerateField("Generates charge", obj.electricity.generates_charge);
                cnt += GenerateField("Water charge", DefaultNull(obj.electricity.options.water_charge, FormatWaterCharge));
                cnt += GenerateField("Can be shocked", obj.electricity.options.can_be_shocked);
                cnt += GenerateField("Ignore water particles", obj.electricity.options.ignore_water_particles);
                cnt += GenerateField("Shock on touch", obj.electricity.options.shock_on_touch);
                cnt += GenerateField("Transports charge", obj.electricity.options.transports_charge);

                cnt += ExitSection();

                cnt += EnterSection("placement", "Placement");

                cnt += GenerateField("Placement type", DefaultNull(obj.placement.type, FormatObjectPlacementType));
                cnt += GenerateField("Enable sky", obj.placement.options.enable_sky);
                cnt += GenerateField("Enable background", obj.placement.options.enable_background);
                cnt += GenerateField("Enable H flip", obj.placement.options.enable_h_flip);
                cnt += GenerateField("Enable rotate 90deg", obj.placement.options.enable_rotate_90);
                cnt += GenerateField("Collides with AI", obj.placement.options.collides_with_ai);
                cnt += GenerateField("Align to terrain", obj.placement.options.align_to_terrain);

                cnt += ExitSection();

                cnt += EnterSection("physics", "Physics");

                cnt += GenerateField("Combiner", DefaultNull(obj.physics.combiner, FormatObjectPhysicsCombiner));
                cnt += GenerateField("Material", DefaultNull(obj.physics.material, FormatObjectMaterial));
                cnt += GenerateField("Mass", obj.physics.mass);
                cnt += GenerateField("Integrity", obj.physics.integrity);
                cnt += GenerateField("Inertia", obj.physics.inertia);
                cnt += GenerateField("Fire interaction", DefaultNull(obj.physics.fire_interaction, FormatObjectFireInteraction));
                cnt += GenerateField("Buoyancy factor", obj.physics.buoyancy_factor);
                cnt += GenerateField("Is waterproof", obj.physics.options.is_waterproof);
                cnt += GenerateField("Can attach", obj.physics.options.can_attach);

                cnt += ExitSection();

                cnt += EnterSection("temperature", "Temperature");

                cnt += GenerateField("Temperature", obj.temperature.temperature);
                cnt += GenerateField("Melting point", obj.temperature.melting_point);
                cnt += GenerateField("Gas point", obj.temperature.gas_point);

                cnt += ExitSection();

                cnt += EnterSection("triggers-actions", "Triggers & Actions");

                for(u32 i = 0; i < obj.triggers_actions.triggers_actions.size(); i++) {
                    const auto &ta = obj.triggers_actions.triggers_actions[i];
                    cnt += GenerateTrigger(ctx, out_dir, "trigger-" + std::to_string(i), "Trigger " + std::to_string(i) + ": " + FormatTriggerType(ta.options.type), ta);
                }

                cnt += ExitSection();

                cnt += EnterSection("frames", "Frames");

                cnt += GenerateField("Unknown flag", obj.frames.unk);
                cnt += GenerateField("Physics shape count", obj.frames.physics_shape_count);
                cnt += GenerateFrame(ctx, out_dir, "root-frame", "Root frame", obj.frames.root);

                cnt += ExitSection();

                cnt += EnterSection("audio", "Audio");

                for(u32 i = 0; i < static_cast<size_t>(AudioTableType::Count); i++) {
                    if(obj.audio.audio_slots[i].has_value()) {
                        const auto &slot = obj.audio.audio_slots[i].value();
                        cnt += EnterSection("audio-slot-" + std::to_string(i), "Audio slot: " + FormatAudioTableType(static_cast<AudioTableType>(i)));
                        
                        cnt += GenerateField("Group ID", slot.group_id);
                        cnt += GenerateField("SeqArc ID", slot.seqarc_id);
                        cnt += GenerateField("Seq ID", slot.seq_id);
                        cnt += GenerateField("Sound attribute", DefaultNull(slot.attr, FormatSoundAttribute));

                        cnt += ExitSection();
                    }
                }

                cnt += ExitSection();

                if(obj.attack.valid) {
                    cnt += EnterSection("attack", "Attack");

                    for(u32 i = 0; i < static_cast<size_t>(Animation::Count); i++) {
                        const auto &attack = obj.attack.attacks[i];
                        cnt += EnterSection("attack-" + std::to_string(i), "Attack for animation: " + FormatAnimation(static_cast<Animation>(i)));

                        if(attack.options.file_id != 0x7FFFFFFF) {
                            cnt += GenerateField("File ID", attack.options.file_id);
                        }
                        
                        if(attack.options.has_notes) {
                            cnt += EnterSection("attack-" + std::to_string(i) + "-notes", "Notes");
                            cnt += GenerateField("Action", Mask16(attack.notes.action));
                            cnt += GenerateField("To", Mask16(attack.notes.to));
                            cnt += GenerateField("From", Mask16(attack.notes.from));
                            cnt += ExitSection();
                        }

                        cnt += ExitSection();
                    }

                    cnt += GenerateField("Attack animation length", obj.attack.attack_anim_len);

                    cnt += ExitSection();
                }

                /////////////////

                ReplaceAll(obj_html, "{OBJ-CONTENT}", cnt);
                ReplaceAll(obj_html, "{OBJ-NAME}", obj_name);

                std::ofstream out_file(out_dir + "/" + obj_name + ".html");
                out_file << obj_html;
            }
        }

        ReplaceAll(index_html, "{TITLE}", GetGameName(ctx.game) + " object list (" + lang_str + ")");
        ReplaceAll(index_html, "{OBJ-ENTRIES}", objs);

        std::ofstream out_index_file(out_dir + "/index.html");
        out_index_file << index_html;

        std::ofstream out_search_file(out_dir + "/search.js");
        out_search_file << SearchJs;

        std::cout << "Done!" << std::endl;
    }

}
