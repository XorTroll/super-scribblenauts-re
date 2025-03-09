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

    DebugPrintf("AnotherObjectFileId %d\n", *ref_g_AnotherObjectFileId);

    t++;
}
ncp_set_call(0x020DF904, Inject_MainLoop);
