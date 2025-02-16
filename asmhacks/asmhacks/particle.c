#include <asmhack-base.h>

void Inject_TwlMain(void) {
    // Original functionality
    CreateGlobalA();

    ////

    DebugPrint("Hello from Scribblenauts asmhack!\n");
}
ncp_set_call(0x02000C7C, Inject_TwlMain);

/* Modify particles, changing SNOW effect to be like ASH */

// ncp_repl(0x0202EC8C, "MOVEQ R12, #22"); // orig
ncp_repl(0x0202EC8C, "MOVEQ R12, #14"); // custom
