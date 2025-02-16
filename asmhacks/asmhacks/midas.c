#include <asmhack-base.h>

/* Anything grabbed by the player gets adjectives GOLDEN and YELLOW, with custom display names */

void Inject_MainLoop(StructL *strl) {
    // Original functionality
    StructL_SomeLoopFn(strl);

    if(g_GlobalBB) {
        for(u32 i = 0; i < g_GlobalBB->obj_list.size; i++) {
            Object *obj = g_GlobalBB->obj_list.ptr[i];

            if((obj->strooo->ooo33_mask_a & (1 << 7)) == 0) {
                AdjectiveHolder_PushAdjective(&obj->adj_holder, 17379, "MIDAS'D", 1, 1024, 0xFFFF);
                AdjectiveHolder_PushAdjective(&obj->adj_holder, 17321, "BRIGHT", 1, 1024, 0xFFFF);
                AdjectiveHolder_MaybeRefresh(&obj->adj_holder, 1);
            }
        }
    }
}
ncp_set_call(0x020DF904, Inject_MainLoop);
