/* date = August 20th 2022 9:42 am */
#ifndef OS_HELPERS_H
#define OS_HELPERS_H

///////////////////////////////////////////
// NOTE(nates): ThreadContext functions

func_ void OS_TctxInit(os_thread_context *tctx);
func_ arena *OS_TctxGetScratch(os_thread_context *tctx, arena **conflict_array, u32 count);

//////////////////////////////////////////
// NOTE(nates): Scratch arena helpers

func_ arena_temp GetScratch(arena *conflict0, arena *conflict1);
#define ReleaseScratch(scratch) EndArenaTemp(scratch);

/////////////////////////////////////////
// NOTE(nates): OS_File helpers

func_ b32 OS_WriteFile(string8 file_name, string8 data);

#endif //OS_HELPERS_H
