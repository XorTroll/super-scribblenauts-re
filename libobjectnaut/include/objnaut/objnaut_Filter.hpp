
#pragma once
#include <objnaut/objnaut_Common.hpp>

namespace objnaut {

    struct FilterEntry {
        bool exclude;
        ObjectCategoryId obj_category_id;
        u16 obj_subcategory_id_1;
        u16 obj_subcategory_id_2;
        u16 obj_id;
        u16 adj_category_id;
        u16 adj_subcategory_id;
        u16 adj_id;
    };
    
    struct Filter {
        std::vector<FilterEntry> entries;
        u32 stage_object_entity_id;
    };
    
}
