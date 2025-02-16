#include <asmhack-base.h>

/* Trick to get '@' or '$' characters in the notebook, allowing to use hidden/internal objects/adjs ;) */

void Inject_MainLoop(StructL *strl) {
    // Original functionality
    StructL_SomeLoopFn(strl);

    if(g_GlobalBB) {
        StructP *strp = g_GlobalBB->strbb1->strbbb->strp;

        if(g_GlobalE) {
            // TODO: also change cursor!!!
            if(StructE_TestKeysDown(g_GlobalE, Key_X)) {
                Util_SNPrintF(strp->input_str_buf, 0x80, "$---");
                strp->input_str_len = 4;
            }
            else if(StructE_TestKeysDown(g_GlobalE, Key_Y)) {
                Util_SNPrintF(strp->input_str_buf, 0x80, "@---");
                strp->input_str_len = 4;
            }
        }
        
    }
}
ncp_set_call(0x020DF904, Inject_MainLoop);
