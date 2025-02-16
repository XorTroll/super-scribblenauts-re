#include <asmhack-base.h>

void Inject_TwlMain(void) {
    // Original functionality
    CreateGlobalA();

    ////

    DebugPrint("Hello from Scribblenauts asmhack!\n");
}
ncp_set_call(0x02000C7C, Inject_TwlMain);

/* Modify the hardcoded value assigned to the player (48 by default) to 0xFF */

ncp_repl(0x0208B480, "MOV R1, #0xFF");
