#include <asmhack-base.h>

/* Main loop injection, printing the overlays currently loaded */

void Inject_TwlMain(void) {
    // Original functionality
    CreateGlobalA();

    ////

    DebugPrint("Hello from Scribblenauts asmhack!\n");
}
ncp_set_call(0x02000C7C, Inject_TwlMain);

void Inject_MainLoop(StructL *strl) {
    // Original functionality
    StructL_SomeLoopFn(strl);
    
    ////

    DebugPrintf("Hello from Scribblenauts main loop! ovls %d and %d\n", g_GlobalD->cur_loaded_ovl_id, g_GlobalD->cur_ovl_id_2);
}
ncp_set_call(0x020DF904, Inject_MainLoop);
