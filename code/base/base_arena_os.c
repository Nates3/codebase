
#define ARENA_COMMIT_GRANULARITY KB(4)

#define ArenaImpl_Reserve(size) OS_ReserveMemory(size)
#define ArenaImpl_Commit(ptr, size) OS_CommitMemory(ptr, size)
#define ArenaImpl_Decommit(ptr, size) OS_DecommitMemory(ptr, size);
#define ArenaImpl_Release(ptr) OS_ReleaseMemory(ptr)

func_ arena *
ArenaAlloc(u64 size_to_reserve)
{
	size_to_reserve += sizeof(arena);
	
	void *memory = ArenaImpl_Reserve(size_to_reserve);
	u64 initial_commit_size = ARENA_COMMIT_GRANULARITY;
	ArenaImpl_Commit(memory, initial_commit_size);
	
	arena *result = (arena *)memory;
	result->CommitPos = initial_commit_size;
	result->Pos = sizeof(arena);
	result->Size = size_to_reserve;
	result->Align = 8;
	return(result);
}

func_ void *
ArenaPush(arena *Arena, u64 size)
{
	void *result = 0;
	u64 new_pos = Arena->Pos + size;
	if(new_pos <= Arena->Size) {
		u8 *base = (u8*)Arena;
		u64 align = AlignUpNum(Arena->Pos, Arena->Align);
		result = base + Arena->Pos + align;
		Arena->Pos += size + align;
		
		if(Arena->CommitPos < Arena->Pos) {
			u64 size_to_commit = Arena->Pos - Arena->CommitPos;
			size_to_commit = AlignUp(size_to_commit, ARENA_COMMIT_GRANULARITY);
			size_to_commit = ClampTop(size_to_commit, Arena->Size);
			ArenaImpl_Commit(base + Arena->CommitPos, size_to_commit);
			Arena->CommitPos += size_to_commit;
		}
	}
	else {
		InvalidPath;
	}
	
	return(result);
}

func_ void *
ArenaPushZero(arena *Arena, u64 Size)
{
	void *memory = PushSize(Arena, Size);
	MemoryZero(memory, Size);
	return(memory);
}

func_ void
ArenaPop(arena *Arena, u64 size)
{
	if(Arena->Pos > size) {
		u64 pos = Arena->Pos - size;
		Arena->Pos = pos;
		
		u64 round_up_pos = AlignUp(Arena->Pos, ARENA_COMMIT_GRANULARITY);
		u64 decommit_size = Arena->CommitPos - round_up_pos;
		if(decommit_size) {
			Assert(decommit_size%ARENA_COMMIT_GRANULARITY == 0);
			Arena->CommitPos = round_up_pos;
			
			void *ptr = (u8 *)Arena + round_up_pos;
			ArenaImpl_Decommit(ptr, decommit_size);
		}
	}
	else {
		InvalidPath;
	}
}

func_ void
ArenaSetPos(arena *Arena, u64 pos)
{
	if(pos < Arena->Pos) {
		u64 size = Arena->Pos - pos;
		ArenaPop(Arena, size);
	}
}

func_ void *
ArenaPos(arena *Arena)
{
	void *pos = (u8 *)Arena + Arena->Pos;
	return(pos);
}

func_ void *
ArenaStart(arena *Arena)
{
	void *pos = (u8 *)Arena + sizeof(arena);
	return(pos);
}

func_ void *
ArenaEnd(arena *Arena)
{
	void *result = (u8 *)Arena + Arena->Pos;
	return(result);
}

func_ void
ArenaClear(arena *Arena)
{
	u64 size = Arena->Pos - sizeof(arena);
	ArenaPop(Arena, size);
}

func_ void
ArenaRelease(arena *Arena)
{
	ArenaImpl_Release(Arena);
}

func_ u64    
ArenaSize(arena *Arena)
{
	u64 result = Arena->Pos - sizeof(arena);
	return(result);
}

func_ arena_temp
BeginArenaTemp(arena *Arena)
{
	arena_temp result = {
		Arena, Arena->Pos,
	};
	return(result);
}

func_ void
EndArenaTemp(arena_temp temp)
{
	ArenaSetPos(temp.Arena, temp.Pos);
}