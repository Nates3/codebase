/* date = August 20th 2022 9:42 am */
#ifndef OS_HELPERS_H
#define OS_HELPERS_H

///////////////////////////////////////////
// NOTE(nates): ThreadContext functions

func_ void os_TctxInit(OS_ThreadContext *tctx);
func_ Arena *os_TctxGetScratch(OS_ThreadContext *tctx, Arena **conflict_array, U32 count);

//////////////////////////////////////////
// NOTE(nates): Scratch arena helpers

func_ ArenaTemp GetScratch(Arena *conflict0, Arena *conflict1);
#define ReleaseScratch(scratch) EndArenaTemp(scratch);

/////////////////////////////////////////
// NOTE(nates): OS_File helpers

func_ B32 OS_WriteFile(Str8 file_name, Str8 data);

#endif //OS_HELPERS_H
