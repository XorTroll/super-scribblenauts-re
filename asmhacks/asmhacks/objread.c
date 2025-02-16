#include <asmhack-base.h>

/* Injection to log when an object file is accessed */

void Inject_TwlMain(void) {
    // Original functionality
    CreateGlobalA();

    ////

    DebugPrint("Hello from Scribblenauts asmhack!\n");
}
ncp_set_call(0x02000C7C, Inject_TwlMain);

void Inject_StructO_V4_ReadSomeFile(StructC *strc, void **out_entry_data_buf, int entry_id, int flush_mem, StructB *strb) {
    // Original functionality
    StructC_ReadFileData(strc, out_entry_data_buf, entry_id, flush_mem, strb);
    
    ////

    DebugPrintf("UnkO read! fileid=%d\n", entry_id);
}
ncp_set_call(0x0208ABF8, Inject_StructO_V4_ReadSomeFile);
