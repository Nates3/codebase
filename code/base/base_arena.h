/* date = August 17th 2022 2:29 am */
#ifndef BASE_ARENA_H
#define BASE_ARENA_H

///////////////////////////////////
// NOTE(nates): Arenas

typedef struct arena
{
	u64 Pos;
	u64 CommitPos;
	u64 Size;
	u64 Align;
}arena;

typedef struct arena_temp
{
	arena *Arena;
	u64 Pos;
}arena_temp;


// IMPORTANT NOTE(nates): Arena's are implimented differently depending
// on whether or not you include os_inc.h. Without the os layer, 
// arena's use malloc and commit memory upfront. With the os layer, 
// ArenaAlloc doesn't commit up front and instead reserves address space.
// Subsequent alloctaions on arena's in the os implimentation will commit memory
// If you want you can ignore this and just include this .h and your own
// .c implimentation

/////////////////////////////////
// NOTE(nates): Arena functions

func_ arena *ArenaAlloc(u64 size);
func_ void  *ArenaPush(arena *Arena, u64 Size);
func_ void  *ArenaPushZero(arena *Arena, u64 Size);
func_ void   ArenaPop(arena *Arena, u64 Size);
func_ void   ArenaSetPos(arena *Arena, u64 Pos);
func_ void  *ArenaPos(arena *Arena);
func_ void  *ArenaStart(arena *Arena);
func_ void  *ArenaEnd(arena *Arena);
func_ void   ArenaClear(arena *Arena);
func_ void   ArenaRelease(arena *Arena);
func_ u64    ArenaSize(arena *Arena);
#define PushArray(Arena, Type, Count) (Type *)ArenaPush(Arena, sizeof(Type)*Count)
#define PushArrayZero(Arena, Type, Count) (Type *)ArenaPushZero(Arena, sizeof(Type)*Count);
#define PushSize(Arena, Size) ArenaPush(Arena, Size)
#define PushSizeZero(Arena, Size) ArenaPushZero(Arena, Size)

func_ arena_temp BeginArenaTemp(arena *Arena);
func_ void      EndArenaTemp(arena_temp Temp);

#endif //BASE_ARENA_H
