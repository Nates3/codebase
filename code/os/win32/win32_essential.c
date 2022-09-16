
///////////////////////////////////////////
//~ NOTE(nates): Win32 helpers

func_ file_properties
Win32FilePropertiesFromFileData(DWORD file_attributes, 
																FILETIME creation_time, FILETIME last_write_time, 
																DWORD file_size_high, DWORD file_size_low)
{
	file_properties result = {0};
	result.Size = ((u64)file_size_high << 32) | (u64)file_size_low;
	result.Flags |= (HasFlags(file_attributes, FILE_ATTRIBUTE_DIRECTORY)) ? FilePropertyFlag_IsFolder : 0;
	result.CreateTime = (dense_time)(((u64)creation_time.dwHighDateTime << 32) | (u64)creation_time.dwLowDateTime);
	result.ModifyTime = (dense_time)(((u64)last_write_time.dwHighDateTime << 32) | (u64)last_write_time.dwLowDateTime);
	
	result.Access |= DataAccessFlag_Read|DataAccessFlag_Write|DataAccessFlag_Execute;
	if(HasFlags(file_attributes, FILE_ATTRIBUTE_READONLY)) {
		RemoveFlags(result.Access, DataAccessFlag_Write);
	}
	
	return(result);
}

/////////////////////////////
// NOTE(nate): Win32 time

func_ date_time
Win32DateTimeFromSystemTime(SYSTEMTIME *time)
{
	date_time date = {
		.Ms = time->wMilliseconds,
		.Sec = time->wSecond,
		.Min = time->wMinute,
		.Hour = time->wHour,
		.Day = (u8)(time->wDay - 1),
		.Mon = (u8)time->wMonth,
		.Year = time->wYear,
	};
	return(date);
}

func_ SYSTEMTIME
Win32SystemTimeFromDateTime(date_time *time)
{
	SYSTEMTIME result = {
		.wMilliseconds = (WORD)time->Ms,
		.wSecond = (WORD)time->Sec,
		.wMinute = (WORD)time->Min,
		.wHour = (WORD)time->Hour,
		.wDay = (WORD)(time->Day + 1),
		.wMonth = (WORD)time->Mon,
		.wYear = (WORD)time->Year,
	};
	return(result);
}


func_ date_time
Win32DateTimeFromFileTime(FILETIME *filetime)
{
	SYSTEMTIME system_time = {0};
	FileTimeToSystemTime(filetime, &system_time);
	date_time date = Win32DateTimeFromSystemTime(&system_time);
	return(date);
}

func_ dense_time 
Win32DenseTimeFromFileTime(FILETIME *filetime)
{
	date_time date = Win32DateTimeFromFileTime(filetime);
	dense_time result = DenseTimeFromDateTime(&date);
	return(result);
}

////////////////////////////////////////
//~ NOTE(nates): OS_IMPLEMENTATION

///////////////////////////////
// NOTE(nates): Variables

global_ DWORD win32_thread_context_index = 0;
global_ u64 win32_ticks_per_second = 1;
global_ arena *win32_perm_arena = 0;
global_ string8_list win32_cmd_args = {0};


/////////////////////////////////////
// NOTE(nates): Setup

func_ void 
OS_MainInit(os_thread_context *tctx_memory, int argc, char **args)
{
	win32_thread_context_index = TlsAlloc();
	OS_TctxInit(tctx_memory);
	OS_TctxSet(tctx_memory);
	
	LARGE_INTEGER perf_freq = {0};
	if(QueryPerformanceFrequency(&perf_freq)) {
		win32_ticks_per_second = ((u64)perf_freq.HighPart << 32) | ((u64)perf_freq.LowPart);
	}
	timeBeginPeriod(1);
	
	win32_perm_arena = ArenaAlloc(GB(4));
	
	char **opl = args + argc;
	for(char **arg = args; arg < opl; arg += 1) {
		string8 str = Str8Cstr(*arg);
		string8 copy = CopyStr8(win32_perm_arena, str);
		PushStr8List(win32_perm_arena, &win32_cmd_args, copy);
	}
}

func_ void
Win32MainInit(os_thread_context *tctx_memory,
							HINSTANCE hInstance, HINSTANCE hPrevInstance,
							LPSTR lpCmdLine, int nCmdShow)
{
	int argc = __argc;
	char **args = __argv;
	OS_MainInit(tctx_memory, argc, args);
}

func_ string8_list
OS_GetCommandLineArgs(void)
{
	string8_list result = win32_cmd_args;
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
OS_ReserveMemory(u64 size)
{
	void *result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_READWRITE);
	return(result);
}

func_ void
OS_CommitMemory(void *ptr, u64 size_to_commit)
{
	VirtualAlloc(ptr, size_to_commit, MEM_COMMIT, PAGE_READWRITE);
}

func_ void
OS_DecommitMemory(void *ptr, u64 size)
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


func_ string8 OS_ReadFile(arena *Arena, string8 filename)
{
	arena_temp scratch = GetScratch(Arena, 0);
	string16 filename16 = Str16FromStr8(scratch.Arena, filename);
	HANDLE file = CreateFileW((WCHAR *)filename16.M, GENERIC_READ, FILE_SHARE_READ, 
														0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReleaseScratch(scratch);
	
	LARGE_INTEGER file_size = {0};
	void *memory = 0;
	if(file != INVALID_HANDLE_VALUE) {
		GetFileSizeEx(file, &file_size);
		arena_temp restore_point = BeginArenaTemp(Arena);
		memory = PushArray(Arena, u8, file_size.QuadPart);
		DWORD IGNORED = 0;
		
		if(ReadFile(file, memory, file_size.QuadPart, &IGNORED, 0) == false) {
			EndArenaTemp(restore_point);
		}
		
		CloseHandle(file);
	}
	else {
		InvalidPath;
	}
	
	string8 result = {memory, file_size.QuadPart};
	return(result);
}

func_ b32
OS_WriteListFile(string8 filename, string8_list data)
{
	arena_temp scratch = GetScratch(0, 0);
	string16 filename16 = Str16FromStr8(scratch.Arena, filename);
	HANDLE file = CreateFileW((WCHAR *)filename16.M, GENERIC_WRITE, 0, 
														0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	ReleaseScratch(scratch);
	
	b32 result = true;
	if(file != INVALID_HANDLE_VALUE) {
		for(string8_node *node = data.First;
				node != 0; node = node->Next) {
			DWORD IGNORED = 0;
			result = WriteFile(file, node->String.M, node->String.Size, &IGNORED, 0);
		}
		CloseHandle(file);
	}
	else {
		InvalidPath;
	}
	
	return(result);
}

func_ file_properties
OS_FileProperties(string8 filename)
{
	arena_temp scratch = GetScratch(0, 0);
	
	WIN32_FILE_ATTRIBUTE_DATA data = {0};
	string16 filename16 = Str16FromStr8(scratch.Arena, filename);
	GetFileAttributesExW((WCHAR *)filename16.M, 
											 GetFileExInfoStandard, 
											 &data);
	ReleaseScratch(scratch);
	
	file_properties result = Win32FilePropertiesFromFileData(data.dwFileAttributes,
																													 data.ftCreationTime, data.ftLastWriteTime,
																													 data.nFileSizeHigh, data.nFileSizeLow);
	
	return(result);
}

func_ b32
OS_PathExists(string8 path)
{
	b32 result = true;
	arena_temp scratch = GetScratch(0, 0);
	string16 path16 = Str16FromStr8(scratch.Arena, path);
	DWORD attributes = GetFileAttributesW((WCHAR *)path16.M);
	if(attributes == INVALID_FILE_ATTRIBUTES) {
		result = false;
	}
	ReleaseScratch(scratch);
	return(result);
}

func_ b32 
OS_DeleteFile(string8 filename)
{
	arena_temp scratch = GetScratch(0, 0);
	string16 filename16 = Str16FromStr8(scratch.Arena, filename);
	b32 result = DeleteFileW((WCHAR *)filename16.M);
	ReleaseScratch(scratch);
	return(result);
}

func_ b32
OS_RenameFile(string8 filename, string8 newname)
{
	arena_temp scratch = GetScratch(0, 0);
	string16 filename16 = Str16FromStr8(scratch.Arena, filename);
	string16 newname16 = Str16FromStr8(scratch.Arena, newname);
	b32 result = MoveFileW((WCHAR *)filename16.M, (WCHAR *)newname16.M);
	ReleaseScratch(scratch);
	return(result);
}

func_ b32 
OS_MakeDirectory(string8 path)
{
	arena_temp scratch = GetScratch(0, 0);
	string16 path16 = Str16FromStr8(scratch.Arena, path);
	b32 result = CreateDirectoryW((WCHAR *)path16.M, 0);
	ReleaseScratch(scratch);
	return(result);
}

func_ b32 
OS_DeleteDirectory(string8 path)
{
	arena_temp scratch = GetScratch(0, 0);
	string16 path16 = Str16FromStr8(scratch.Arena, path);
	b32 result = RemoveDirectoryW((WCHAR *)path16.M);
	ReleaseScratch(scratch);
	return(result);
}


//////////////////////////////////////////////
// NOTE(nates): File iteration functions

func_ os_fileiter
OS_FileIterInit(string8 path)
{
	os_fileiter result = {0};
	
	string8_node nodes[2] = {0};
	string8_list list = {0};
	PushExplicitStr8List(&list, path, nodes);
	PushExplicitStr8List(&list, Str8Lit("\\*"), nodes + 1);
	arena_temp scratch = GetScratch(0, 0);
	string8 full_path = JoinStr8List(scratch.Arena, &list);
	// TODO(nates): Consider taking a string list for str16s
	string16 path16 = Str16FromStr8(scratch.Arena, full_path);
	win32_fileiter *win32_iter = (win32_fileiter *)&result;
	MemoryZeroStruct(&result);
	win32_iter->Handle = FindFirstFileW((WCHAR *)path16.M, &win32_iter->FindData);
	ReleaseScratch(scratch);
	return(result);
}

func_ b32
OS_FileIterNext(arena *Arena, os_fileiter *iter,
								string8 *name_out, file_properties *prop_out)
{
	b32 result = false;
	win32_fileiter *win32_iter = (win32_fileiter *)iter;
	if(win32_iter->Handle != 0 &&
		 win32_iter->Handle != INVALID_HANDLE_VALUE) {
		for(;win32_iter->Done == false;) {
			WCHAR *filename = win32_iter->FindData.cFileName;
			b32 is_dot = (filename[0] == '.' && filename[1] == 0);
			b32 is_dotdot = (filename[0] == '.' && filename[1] == '.' && filename[2] == 0);
			
			b32 emit = (!is_dot && !is_dotdot);
			WIN32_FIND_DATAW data = {0};
			if(emit) {
				MemoryCopyStruct(&data, &win32_iter->FindData);
			}
			
			if(!FindNextFileW(win32_iter->Handle, &win32_iter->FindData)) {
				win32_iter->Done = true;
			}
			
			if(emit) {
				*name_out = Str8FromStr16(Arena, Str16Cstr((u16 *)data.cFileName));
				*prop_out = Win32FilePropertiesFromFileData(data.dwFileAttributes,
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
OS_FileIterEnd(os_fileiter *iter)
{
	win32_fileiter *win32_iter = (win32_fileiter *)iter;
	if(win32_iter->Handle != 0 &&
		 win32_iter->Handle != INVALID_HANDLE_VALUE) {
		FindClose(win32_iter->Handle);
	}
}

// NOTE(nates): System paths

func_ string8 OS_SystemPath(arena *Arena, os_system_path path)
{
	string8 result = {0};
	switch(path) {
		case OS_SystemPath_CurrentDir: {
			DWORD buffer_size = GetCurrentDirectory(0, 0);
			arena_temp scratch = GetScratch(Arena, 0);
			u16 *buffer = PushArray(scratch.Arena, u16, buffer_size);
			GetCurrentDirectoryW(buffer_size, buffer);
			result = Str8FromStr16(Arena, Str16(buffer, buffer_size - 1));
			ReleaseScratch(scratch);
		} break;
		case OS_SystemPath_ExeDir: {
			arena_temp scratch = GetScratch(Arena, 0);
			arena_temp restore_point = BeginArenaTemp(scratch.Arena);
			DWORD string_length = 0;
			u16 *temp_buffer = 0;
			u32 size = 512;
			for(;;) {
				temp_buffer = PushArray(restore_point.Arena, u16, size);
				string_length = GetModuleFileNameW(0, temp_buffer, size);
				DWORD last_error = GetLastError();
				if(last_error != ERROR_INSUFFICIENT_BUFFER) {
					break;
				}
				size += 512;
				end_Arena_temp(restore_point);
			}
			
			string8 temp_exefile = Str8FromStr16(restore_point.Arena, Str16(temp_buffer, string_length));
			string8 actual_path = ChopAtLastSlashStr8(temp_exefile);
			string_length = actual_path.Size;
			EndArena_temp(restore_point);
			
			u16 *buffer = PushArray(scratch.Arena, u16, string_length + 1);
			GetModuleFileNameW(0, buffer, string_length + 1);
			result = Str8FromStr16(Arena, Str16(buffer, string_length - 1));
			ReleaseScratch(scratch);
		} break;
		
		case OS_SystemPath_UserDir: {
			arena_temp scratch = GetScratch(Arena, 0);
			
			// NOTE(nates): Get the profiles directory
			u32 profile_dir_buffer_size = 0;
			GetProfilesDirectoryW(0, &profile_dir_buffer_size);
			u16 *profile_dir_buffer = PushArray(scratch.Arena, u16, profile_dir_buffer_size);
			GetProfilesDirectoryW(profile_dir_buffer, &profile_dir_buffer_size);
			string8 profile_dir = Str8FromStr16(scratch.Arena, Str16(profile_dir_buffer, profile_dir_buffer_size - 1));
			
			// NOTE(nates): Get the current user's name
			u32 user_name_buffer_size = 0;
			GetUserNameW(0, &user_name_buffer_size);
			u16 *user_name_buffer = PushArray(scratch.Arena, u16, user_name_buffer_size);
			GetUserNameW(user_name_buffer, &user_name_buffer_size);
			string8 user_name = Str8FromStr16(scratch.Arena, Str16(user_name_buffer, user_name_buffer_size - 1));
			
			string8_node nodes[3] = {0};
			string8_list list = {0};
			PushExplicitStr8List(&list, profile_dir, nodes + 0);
			PushExplicitStr8List(&list, Str8Lit("\\"), nodes + 1);
			PushExplicitStr8List(&list, user_name, nodes + 2);
			result = JoinStr8List(Arena, &list);
			
			ReleaseScratch(scratch);
		} break;
		
		case OS_SystemPath_TempDir: {
			arena_temp scratch = GetScratch(Arena, 0);
			u32 buffer_size = 0;
			buffer_size = GetTempPathW(0, 0);
			u16 *buffer = PushArray(scratch.Arena, u16, buffer_size);
			GetTempPathW(buffer_size, buffer);
			result = Str8FromStr16(Arena, Str16(buffer, buffer_size - 2));
			
			ReleaseScratch(scratch);
		} break;
		
		InvalidCase;
	}
	
	return(result);
}


/////////////////////////////////////
// NOTE(nates): OS Time functions

func_ date_time
OS_GetUniversalTime(void)
{
	SYSTEMTIME system_time = {0};
	GetSystemTime(&system_time);
	date_time result = Win32DateTimeFromSystemTime(&system_time);
	return(result);
}

func_ date_time
OS_GetLocalTimeFromUniversalTime(date_time *universal)
{
	SYSTEMTIME universal_system_time = Win32SystemTimeFromDateTime(universal);
	FILETIME universal_file_time = {0};
	SystemTimeToFileTime(&universal_system_time, &universal_file_time);
	FILETIME local_file_time = {0};
	FileTimeToLocalFileTime(&universal_file_time, &local_file_time);
	date_time result = Win32DateTimeFromFileTime(&local_file_time);
	return(result);
}

func_ date_time
OS_UniversalTimeFromLocalTime(date_time *local_time)
{
	SYSTEMTIME local_system_time = Win32SystemTimeFromDateTime(local_time);
	FILETIME local_file_time = {0};
	SystemTimeToFileTime(&local_system_time, &local_file_time);
	FILETIME universal_file_time = {0};
	LocalFileTimeToFileTime(&local_file_time, &universal_file_time);
	date_time result = Win32DateTimeFromFileTime(&universal_file_time);
	return(result);
}

func_ u64
OS_GetMicroSeconds(void)
{
	u64 result = 0;
	LARGE_INTEGER time = {0};
	if(QueryPerformanceCounter(&time)) {
		u64 ticks = ((u64)time.HighPart << 32) | ((u64)time.LowPart);
		result = (ticks/win32_ticks_per_second)*Million(1);
	}
	return(result);
}

func_ u64 
OS_GetMilliSeconds(void)
{
	u64 result = 0;
	LARGE_INTEGER time = {0};
	if(QueryPerformanceCounter(&time)) {
		u64 ticks = ((u64)time.HighPart << 32) | ((u64)time.LowPart);
		result = (ticks/win32_ticks_per_second)*Thousand(1);
	}
	return(result);
}

func_ void 
OS_SleepMS(u64 ms)
{
	Sleep(ms);
}

//////////////////////////////////////
// NOTE(nates): Dlls


func_ os_library 
OS_LoadLib(string8 filename)
{
	arena_temp scratch = GetScratch(0, 0);
	
	string16 filename16 = Str16FromStr8(scratch.Arena, filename);
	HMODULE library = LoadLibraryW((WCHAR *)filename16.M);
	file_properties properties = OS_FileProperties(filename);
	os_library result = {0};
	result.Handle = (os_handle)library;
	result.LastWriteTime = properties.ModifyTime;
	ReleaseScratch(scratch);
	return(result);
}

func_ b32
OS_CloseLib(os_library library)
{
	b32 result = FreeLibrary((HMODULE)library.Handle);
	return(result);
}

func_ void *     
OS_GetLibProc_(os_library library, string8 function_name)
{
	void *function = GetProcAddress((HMODULE)library.Handle, function_name.M);
	return(function);
}

////////////////////////////////////
// NOTE(nates): Entropy

func_ void OS_GetEntropy(u64 *seed)
{
	HCRYPTPROV crpyt_prov = 0;
	CryptAcquireContextW(&crpyt_prov, 0, 0,  PROV_DSS, CRYPT_VERIFYCONTEXT);
	CryptGenRandom(crpyt_prov, 8, (BYTE *)seed);
	CryptReleaseContext(crpyt_prov,0);
}
