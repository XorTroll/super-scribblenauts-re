#include <asmhack-base.h>

/* For each object, log all its adjectives */

void Inject_MainLoop(StructL *strl) {
    // Original functionality
    StructL_SomeLoopFn(strl);

    if(g_GlobalBB) {
        for(u32 i = 0; i < g_GlobalBB->obj_list.size; i++) {
            Object *obj = g_GlobalBB->obj_list.ptr[i];
            for(u32 j = 0; j < obj->adj_holder.adj_count; j++) {
                DebugPrintf("[%d:%d] '%s'\n", i, j, obj->adj_holder.adj_name_strs[j]);
            }
        }
    }
}
ncp_set_call(0x020DF904, Inject_MainLoop);
