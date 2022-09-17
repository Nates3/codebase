
///////////////////////////////////////////
//~ NOTE(nates): Win32 helpers

func_ FileProperties
W32FilePropertiesFromFileData(DWORD file_attributes, 
															FILETIME creation_time, FILETIME last_write_time, 
															DWORD file_size_high, DWORD file_size_low)
{
	FileProperties result = {0};
	result.size = ((U64)file_size_high << 32) | (U64)file_size_low;
	result.flags |= (HasFlags(file_attributes, FILE_ATTRIBUTE_DIRECTORY)) ? FilePropertyFlag_IsFolder : 0;
	result.create_time = (DenseTime)(((U64)creation_time.dwHighDateTime << 32) | (U64)creation_time.dwLowDateTime);
	result.modify_time = (DenseTime)(((U64)last_write_time.dwHighDateTime << 32) | (U64)last_write_time.dwLowDateTime);
	
	result.access |= DataAccessFlag_Read|DataAccessFlag_Write|DataAccessFlag_Execute;
	if(HasFlags(file_attributes, FILE_ATTRIBUTE_READONLY)) {
		RemoveFlags(result.access, DataAccessFlag_Write);
	}
	
	return(result);
}

/////////////////////////////
// NOTE(nate): W32 time

func_ DateTime
W32DateTimeFromSystemTime(SYSTEMTIME *time)
{
	DateTime date = {
		.ms = time->wMilliseconds,
		.sec = time->wSecond,
		.min = time->wMinute,
		.hour = time->wHour,
		.day = (U8)(time->wDay - 1),
		.mon = (U8)time->wMonth,
		.year = time->wYear,
	};
	return(date);
}

func_ SYSTEMTIME
W32SystemTimeFromDateTime(DateTime *time)
{
	SYSTEMTIME result = {
		.wMilliseconds = (WORD)time->ms,
		.wSecond = (WORD)time->sec,
		.wMinute = (WORD)time->min,
		.wHour = (WORD)time->hour,
		.wDay = (WORD)(time->day + 1),
		.wMonth = (WORD)time->mon,
		.wYear = (WORD)time->year,
	};
	return(result);
}


func_ DateTime
W32DateTimeFromFileTime(FILETIME *filetime)
{
	SYSTEMTIME system_time = {0};
	FileTimeToSystemTime(filetime, &system_time);
	DateTime date = W32DateTimeFromSystemTime(&system_time);
	return(date);
}

func_ DenseTime 
W32DenseTimeFromFileTime(FILETIME *filetime)
{
	DateTime date = W32DateTimeFromFileTime(filetime);
	DenseTime result = DenseTimeFromDateTime(&date);
	return(result);
}

////////////////////////////////////////
//~ NOTE(nates): OS_IMPLEMENTATION

///////////////////////////////
// NOTE(nates): Variables

global_ DWORD win32_thread_context_index = 0;
global_ U64 win32_ticks_per_second = 1;
global_ Arena *win32_perm_arena = 0;
global_ Str8List win32_cmd_args = {0};


/////////////////////////////////////
// NOTE(nates): Setup

func_ void 
OS_MainInit(OS_ThreadContext *tctx_memory, int argc, char **args)
{
	win32_thread_context_index = TlsAlloc();
	OS_TctxInit(tctx_memory);
	OS_TctxSet(tctx_memory);
	
	LARGE_INTEGER perf_freq = {0};
	if(QueryPerformanceFrequency(&perf_freq)) {
		win32_ticks_per_second = ((U64)perf_freq.HighPart << 32) | ((U64)perf_freq.LowPart);
	}
	timeBeginPeriod(1);
	
	win32_perm_arena = ArenaAlloc(GB(4));
	
	char **opl = args + argc;
	for(char **arg = args; arg < opl; arg += 1) {
		Str8 str = Str8FromCstr(*arg);
		Str8 copy = Str8Copy(win32_perm_arena, str);
		Str8ListPush(win32_perm_arena, &win32_cmd_args, copy);
	}
}

func_ void
W32MainInit(OS_ThreadContext *tctx_memory,
						HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow)
{
	int argc = __argc;
	char **args = __argv;
	OS_MainInit(tctx_memory, argc, args);
}

func_ Str8List
OS_GetCommandLineArgs(void)
{
	Str8List result = win32_cmd_args;
	return(result);
}

///////////////////////////////////////////////
// NOTE(nates): Shutdown

func_ void OS_Abort(void)
{
	ExitProcess(0);
}

// NOTE(nates): Thread Context
///////////////////////////////

func_ void
OS_TctxSet(void *ptr)
{
	TlsSetValue(win32_thread_context_index, ptr);
}

func_ void *
OS_TctxGet(void)
{
	void *result = TlsGetValue(win32_thread_context_index);
	return(result);
}

//////////////////////////////
// NOTE(nates): Memory functions

func_ void *
OS_ReserveMemory(U64 size)
{
	void *result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
	return(result);
}

func_ void
OS_CommitMemory(void *ptr, U64 size_to_commit)
{
	VirtualAlloc(ptr, size_to_commit, MEM_COMMIT, PAGE_READWRITE);
}

func_ void
OS_DecommitMemory(void *ptr, U64 size)
{
	VirtualFree(ptr, size, MEM_DECOMMIT);
}

func_ void 
OS_ReleaseMemory(void *base)
{
	VirtualFree(base, 0, MEM_RELEASE);
}


///////////////////////////////////
//~ NOTE(nates): File functions


func_ Str8 OS_ReadFile(Arena *arena, Str8 filename)
{
	ArenaTemp scratch = GetScratch(arena, 0);
	Str16 filename16 = Str16FromStr8(scratch.arena, filename);
	HANDLE file = CreateFileW((WCHAR *)filename16.m, GENERIC_READ, FILE_SHARE_READ, 
														0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReleaseScratch(scratch);
	
	LARGE_INTEGER file_size = {0};
	void *memory = 0;
	if(file != INVALID_HANDLE_VALUE) {
		GetFileSizeEx(file, &file_size);
		ArenaTemp restore_point = BeginArenaTemp(arena);
		memory = PushArray(arena, U8, file_size.QuadPart);
		DWORD IGNORED = 0;
		
		if(ReadFile(file, memory, file_size.QuadPart, &IGNORED, 0) == false) {
			EndArenaTemp(restore_point);
		}
		
		CloseHandle(file);
	}
	else {
		InvalidPath;
	}
	
	Str8 result = {memory, file_size.QuadPart};
	return(result);
}

func_ B32
OS_WriteListFile(Str8 filename, Str8List data)
{
	ArenaTemp scratch = GetScratch(0, 0);
	Str16 filename16 = Str16FromStr8(scratch.arena, filename);
	HANDLE file = CreateFileW((WCHAR *)filename16.m, GENERIC_WRITE, 0, 
														0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	ReleaseScratch(scratch);
	
	B32 result = true;
	if(file != INVALID_HANDLE_VALUE) {
		for(Str8Node *node = data.first;
				node != 0; node = node->next) {
			DWORD IGNORED = 0;
			result = WriteFile(file, node->str.m, node->str.size, &IGNORED, 0);
		}
		CloseHandle(file);
	}
	else {
		InvalidPath;
	}
	
	return(result);
}

func_ FileProperties
OS_FileProperties(Str8 filename)
{
	ArenaTemp scratch = GetScratch(0, 0);
	
	WIN32_FILE_ATTRIBUTE_DATA data = {0};
	Str16 filename16 = Str16FromStr8(scratch.arena, filename);
	GetFileAttributesExW((WCHAR *)filename16.m, 
											 GetFileExInfoStandard, 
											 &data);
	ReleaseScratch(scratch);
	
	FileProperties result = W32FilePropertiesFromFileData(data.dwFileAttributes,
																												data.ftCreationTime, data.ftLastWriteTime,
																												data.nFileSizeHigh, data.nFileSizeLow);
	
	return(result);
}

func_ B32
OS_PathExists(Str8 path)
{
	B32 result = true;
	ArenaTemp scratch = GetScratch(0, 0);
	Str16 path16 = Str16FromStr8(scratch.arena, path);
	DWORD attributes = GetFileAttributesW((WCHAR *)path16.m);
	if(attributes == INVALID_FILE_ATTRIBUTES) {
		result = false;
	}
	ReleaseScratch(scratch);
	return(result);
}

func_ B32 
OS_DeleteFile(Str8 filename)
{
	ArenaTemp scratch = GetScratch(0, 0);
	Str16 filename16 = Str16FromStr8(scratch.arena, filename);
	B32 result = DeleteFileW((WCHAR *)filename16.m);
	ReleaseScratch(scratch);
	return(result);
}

func_ B32
OS_RenameFile(Str8 filename, Str8 newname)
{
	ArenaTemp scratch = GetScratch(0, 0);
	Str16 filename16 = Str16FromStr8(scratch.arena, filename);
	Str16 newname16 = Str16FromStr8(scratch.arena, newname);
	B32 result = MoveFileW((WCHAR *)filename16.m, (WCHAR *)newname16.m);
	ReleaseScratch(scratch);
	return(result);
}

func_ B32 
OS_MakeDirectory(Str8 path)
{
	ArenaTemp scratch = GetScratch(0, 0);
	Str16 path16 = Str16FromStr8(scratch.arena, path);
	B32 result = CreateDirectoryW((WCHAR *)path16.m, 0);
	ReleaseScratch(scratch);
	return(result);
}

func_ B32 
OS_DeleteDirectory(Str8 path)
{
	ArenaTemp scratch = GetScratch(0, 0);
	Str16 path16 = Str16FromStr8(scratch.arena, path);
	B32 result = RemoveDirectoryW((WCHAR *)path16.m);
	ReleaseScratch(scratch);
	return(result);
}


//////////////////////////////////////////////
// NOTE(nates): File iteration functions

func_ OS_FileIter
OS_FileIterInit(Str8 path)
{
	OS_FileIter result = {0};
	
	Str8Node nodes[2] = {0};
	Str8List list = {0};
	PushExplicitStr8List(&list, path, nodes);
	PushExplicitStr8List(&list, Str8Lit("\\*"), nodes + 1);
	ArenaTemp scratch = GetScratch(0, 0);
	Str8 full_path = Str8ListJoin(scratch.arena, &list);
	// TODO(nates): Consider taking a string list for str16s
	Str16 path16 = Str16FromStr8(scratch.arena, full_path);
	W32_FileIter *win32_iter = (W32_FileIter *)&result;
	MemoryZeroStruct(&result);
	win32_iter->handle = FindFirstFileW((WCHAR *)path16.m, &win32_iter->find_data);
	ReleaseScratch(scratch);
	return(result);
}

func_ B32
OS_FileIterNext(Arena *arena, OS_FileIter *iter,
								Str8 *name_out, FileProperties *prop_out)
{
	B32 result = false;
	W32_FileIter *win32_iter = (W32_FileIter *)iter;
	if(win32_iter->handle != 0 &&
		 win32_iter->handle != INVALID_HANDLE_VALUE) {
		for(;win32_iter->done == false;) {
			WCHAR *filename = win32_iter->find_data.cFileName;
			B32 is_dot = (filename[0] == '.' && filename[1] == 0);
			B32 is_dotdot = (filename[0] == '.' && filename[1] == '.' && filename[2] == 0);
			
			B32 emit = (!is_dot && !is_dotdot);
			WIN32_FIND_DATAW data = {0};
			if(emit) {
				MemoryCopyStruct(&data, &win32_iter->find_data);
			}
			
			if(!FindNextFileW(win32_iter->handle, &win32_iter->find_data)) {
				win32_iter->done = true;
			}
			
			if(emit) {
				*name_out = Str8FromStr16(arena, Str16FromCstr((U16 *)data.cFileName));
				*prop_out = W32FilePropertiesFromFileData(data.dwFileAttributes,
																									data.ftCreationTime, data.ftLastWriteTime,
																									data.nFileSizeHigh, data.nFileSizeLow);
				result = true;
				break;
			}
		}
	}
	return(result);
}

func_ void 
OS_FileIterEnd(OS_FileIter *iter)
{
	W32_FileIter *win32_iter = (W32_FileIter *)iter;
	if(win32_iter->handle != 0 &&
		 win32_iter->handle != INVALID_HANDLE_VALUE) {
		FindClose(win32_iter->handle);
	}
}

// NOTE(nates): System paths

func_ Str8 OS_GetSystemPath(Arena *arena, OS_SystemPath path)
{
	Str8 result = {0};
	switch(path) {
		case OS_SystemPath_CurrentDir: {
			DWORD buffer_size = GetCurrentDirectory(0, 0);
			ArenaTemp scratch = GetScratch(arena, 0);
			U16 *buffer = PushArray(scratch.arena, U16, buffer_size);
			GetCurrentDirectoryW(buffer_size, buffer);
			result = Str8FromStr16(arena, MStr16(buffer, buffer_size - 1));
			ReleaseScratch(scratch);
		} break;
		case OS_SystemPath_ExeDir: {
			ArenaTemp scratch = GetScratch(arena, 0);
			ArenaTemp restore_point = BeginArenaTemp(scratch.arena);
			DWORD string_length = 0;
			U16 *temp_buffer = 0;
			U32 size = 512;
			for(;;) {
				temp_buffer = PushArray(restore_point.arena, U16, size);
				string_length = GetModuleFileNameW(0, temp_buffer, size);
				DWORD last_error = GetLastError();
				if(last_error != ERROR_INSUFFICIENT_BUFFER) {
					break;
				}
				size += 512;
				end_arena_temp(restore_point);
			}
			
			Str8 temp_exefile = Str8FromStr16(restore_point.arena, MStr16(temp_buffer, string_length));
			Str8 actual_path = ChopAtLastSlashStr8(temp_exefile);
			string_length = actual_path.size;
			Endarena_temp(restore_point);
			
			U16 *buffer = PushArray(scratch.arena, U16, string_length + 1);
			GetModuleFileNameW(0, buffer, string_length + 1);
			result = Str8FromStr16(arena, MStr16(buffer, string_length - 1));
			ReleaseScratch(scratch);
		} break;
		
		case OS_SystemPath_UserDir: {
			ArenaTemp scratch = GetScratch(arena, 0);
			
			// NOTE(nates): Get the profiles directory
			U32 profile_dir_buffer_size = 0;
			GetProfilesDirectoryW(0, &profile_dir_buffer_size);
			U16 *profile_dir_buffer = PushArray(scratch.arena, U16, profile_dir_buffer_size);
			GetProfilesDirectoryW(profile_dir_buffer, &profile_dir_buffer_size);
			Str8 profile_dir = Str8FromStr16(scratch.arena, MStr16(profile_dir_buffer, profile_dir_buffer_size - 1));
			
			// NOTE(nates): Get the current user's name
			U32 user_name_buffer_size = 0;
			GetUserNameW(0, &user_name_buffer_size);
			U16 *user_name_buffer = PushArray(scratch.arena, U16, user_name_buffer_size);
			GetUserNameW(user_name_buffer, &user_name_buffer_size);
			Str8 user_name = Str8FromStr16(scratch.arena, MStr16(user_name_buffer, user_name_buffer_size - 1));
			
			Str8Node nodes[3] = {0};
			Str8List list = {0};
			PushExplicitStr8List(&list, profile_dir, nodes + 0);
			PushExplicitStr8List(&list, Str8Lit("\\"), nodes + 1);
			PushExplicitStr8List(&list, user_name, nodes + 2);
			result = Str8ListJoin(arena, &list);
			
			ReleaseScratch(scratch);
		} break;
		
		case OS_SystemPath_TempDir: {
			ArenaTemp scratch = GetScratch(arena, 0);
			U32 buffer_size = 0;
			buffer_size = GetTempPathW(0, 0);
			U16 *buffer = PushArray(scratch.arena, U16, buffer_size);
			GetTempPathW(buffer_size, buffer);
			result = Str8FromStr16(arena, MStr16(buffer, buffer_size - 2));
			
			ReleaseScratch(scratch);
		} break;
		
		InvalidCase;
	}
	
	return(result);
}


/////////////////////////////////////
// NOTE(nates): OS Time functions

func_ DateTime
OS_GetUniversalTime(void)
{
	SYSTEMTIME system_time = {0};
	GetSystemTime(&system_time);
	DateTime result = W32DateTimeFromSystemTime(&system_time);
	return(result);
}

func_ DateTime
OS_GetLocalTimeFromUniversalTime(DateTime *universal)
{
	SYSTEMTIME universal_system_time = W32SystemTimeFromDateTime(universal);
	FILETIME universal_file_time = {0};
	SystemTimeToFileTime(&universal_system_time, &universal_file_time);
	FILETIME local_file_time = {0};
	FileTimeToLocalFileTime(&universal_file_time, &local_file_time);
	DateTime result = W32DateTimeFromFileTime(&local_file_time);
	return(result);
}

func_ DateTime
OS_UniversalTimeFromLocalTime(DateTime *local_time)
{
	SYSTEMTIME local_system_time = W32SystemTimeFromDateTime(local_time);
	FILETIME local_file_time = {0};
	SystemTimeToFileTime(&local_system_time, &local_file_time);
	FILETIME universal_file_time = {0};
	LocalFileTimeToFileTime(&local_file_time, &universal_file_time);
	DateTime result = W32DateTimeFromFileTime(&universal_file_time);
	return(result);
}

func_ U64
OS_GetMicroSeconds(void)
{
	U64 result = 0;
	LARGE_INTEGER time = {0};
	if(QueryPerformanceCounter(&time)) {
		U64 ticks = ((U64)time.HighPart << 32) | ((U64)time.LowPart);
		result = (ticks/win32_ticks_per_second)*Million(1);
	}
	return(result);
}

func_ U64 
OS_GetMilliSeconds(void)
{
	U64 result = 0;
	LARGE_INTEGER time = {0};
	if(QueryPerformanceCounter(&time)) {
		U64 ticks = ((U64)time.HighPart << 32) | ((U64)time.LowPart);
		result = (ticks/win32_ticks_per_second)*Thousand(1);
	}
	return(result);
}

func_ void 
OS_SleepMS(U64 ms)
{
	Sleep(ms);
}

//////////////////////////////////////
// NOTE(nates): Dlls


func_ OS_Library 
OS_LoadLib(Str8 filename)
{
	ArenaTemp scratch = GetScratch(0, 0);
	
	Str16 filename16 = Str16FromStr8(scratch.arena, filename);
	HMODULE library = LoadLibraryW((WCHAR *)filename16.m);
	FileProperties properties = OS_FileProperties(filename);
	OS_Library result = {0};
	result.handle = (OS_Handle)library;
	result.last_write_time = properties.modify_time;
	ReleaseScratch(scratch);
	return(result);
}

func_ B32
OS_CloseLib(OS_Library library)
{
	B32 result = FreeLibrary((HMODULE)library.handle);
	return(result);
}

func_ void *     
OS_GetLibProc_(OS_Library library, Str8 function_name)
{
	void *function = GetProcAddress((HMODULE)library.handle, function_name.m);
	return(function);
}

////////////////////////////////////
// NOTE(nates): Entropy

func_ void OS_GetEntropy(U64 *seed)
{
	HCRYPTPROV crpyt_prov = 0;
	CryptAcquireContextW(&crpyt_prov, 0, 0,  PROV_DSS, CRYPT_VERIFYCONTEXT);
	CryptGenRandom(crpyt_prov, 8, (BYTE *)seed);
	CryptReleaseContext(crpyt_prov,0);
}
