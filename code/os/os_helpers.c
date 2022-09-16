
///////////////////////////////
// NOTE(nates): Thread context functions

func_ void 
OS_TctxInit(os_thread_context *tctx)
{
	arena **scratch = tctx->ScratchPool;
	for(u32 i = 0; i < ArrayCount(tctx->ScratchPool); ++i, scratch += 1)
	{
		*scratch = ArenaAlloc(GB(1));
	}
}

func_ arena *
OS_TctxGetScratch(os_thread_context *tctx, arena **conflict_array, u32 count)
{
	arena *result = 0;
	arena **scratch = tctx->ScratchPool;
	for(u32 i = 0; i < ArrayCount(tctx->ScratchPool); ++i, scratch += 1)
	{
		b32 is_non_conflict = true;
		
		arena **conflict_ptr = conflict_array;
		for(u32 j = 0; j < count; ++j, conflict_ptr += 1)
		{
			if(*scratch == *conflict_ptr)
			{
				is_non_conflict = false;
				break;
			}
		}
		
		if(is_non_conflict)
		{
			result = *scratch;
			break;
		}
	}
	return(result);
}

////////////////////////////
// NOTE(nates): Scratch helper functions

func_ arena_temp
GetScratch(arena *conflict0, arena *conflict1)
{
	os_thread_context *tctx = (os_thread_context *)OS_TctxGet();
	arena *conflict_array[2] = {conflict0, conflict1};
	arena *scratch = OS_TctxGetScratch(tctx, conflict_array, 2);
	return(BeginArenaTemp(scratch));
}


//////////////////////////////
// NOTE(nates): OS_File helpers

func_ b32
OS_WriteFile(string8 filename, string8 data)
{
	string8_node node = {0};
	string8_list list = {0};
	push_explicit_str8list(&list, data, &node);
	b32 result = OS_WriteListFile(filename, list);
	return(result);
}