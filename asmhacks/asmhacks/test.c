#include <asmhack-base.h>

void PrintObjectMask8(Object *obj) {
    char maskbuf[64] = {};
    IntToBinaryString(obj->strof.mask_a, 8, maskbuf, sizeof(maskbuf));
    DebugPrintf("obj '%s' maska %s\n", obj->obj_name_str, maskbuf);
}

u32 t = 0;

void Inject_MainLoop(StructL *strl) {
    // Original functionality
    StructL_SomeLoopFn(strl);

    

    if(g_GlobalBB) {
        for(u32 i = 0; i < g_GlobalBB->obj_list.size; i++) {
            Object *obj = g_GlobalBB->obj_list.ptr[i];
            DebugPrintf("obj '%s' %d %d\n", obj->obj_name_str, obj->strof.os32225, obj->stroa.mask_x);
            obj->stroa.mask_x |= 0x2;

            // obj->strof.mask_a = 8;
            // obj->strof.mask_b = 16;
        }
    }

    t++;
}
ncp_set_call(0x020DF904, Inject_MainLoop);
