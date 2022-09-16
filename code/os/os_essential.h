/* date = August 17th 2022 6:31 am */
#ifndef OS_ESSENTIAL_H
#define OS_ESSENTIAL_H

///////////////////////////////////
// NOTE(nates): Thread context

#if !defined(TCTX_SCRATCH_POOL_CAP)
#define TCTX_SCRATCH_POOL_CAP 4
#endif

typedef struct os_thread_context
{
  arena *ScratchPool[TCTX_SCRATCH_POOL_CAP];
} os_thread_context;


////////////////////////////
//~ NOTE(nates): File iterator

typedef struct os_fileiter
{
	u8 V[640];
} os_fileiter;

///////////////////////////////
// NOTE(nates): File paths

typedef u32 os_system_path;
enum os_system_path
{
	OS_SystemPath_CurrentDir,
	OS_SystemPath_ExeDir,
	OS_SystemPath_UserDir,
	OS_SystemPath_TempDir,
	OS_SystemPath_COUNT,
};

////////////////////////////
// NOTE(nates): DLLS

typedef u64 os_handle;

typedef struct os_library
{
	os_handle Handle;
	dense_time LastWriteTime;
} os_library;

///////////////////////////
//~ NOTE(nates): Setup

func_ void OS_MainInit(os_thread_context *Tctx, int Argc, char **Args);
func_ string8_list OS_GetCommandLineArgs(void);

///////////////////////////////////////////////
//~ NOTE(nates): Shutdown

func_ void OS_Abort(void);

///////////////////////////////
//~ NOTE(nates): Thread Context

func_ void OS_TctxSet(void *ptr);
func_ void *OS_TctxGet(void);

//////////////////////////
// NOTE(nates): Memory Functions

func_ void *OS_ReserveMemory(u64 size);
func_ void  OS_CommitMemory(void *ptr, u64 size);
func_ void  OS_DecommitMemory(void *ptr, u64 size);
func_ void  OS_ReleaseMemory(void *base);

////////////////////////////////
//~ NOTE(nates): OS_FileFunctions

func_ string8 OS_ReadFile(arena *Arena, string8 filename);
func_ b32     OS_WriteListFile(string8 filename, string8_list data);

func_ file_properties OS_file_properties(string8 filename);

func_ b32 OS_PathExists(string8 path);
func_ b32 OS_DeleteFile(string8 filename);
func_ b32 OS_RenameFile(string8 filename, string8 newname);
func_ b32 OS_MakeDirectory(string8 path);
func_ b32 OS_DeleteDirectory(string8 path);

func_ os_fileiter OS_FileIterInit(string8 path);
func_ b32  OS_FileIterNext(arena *Arena, os_fileiter *iter,
													 string8 *name_out, file_properties *prop_out);
func_ void OS_FileIterEnd(os_fileiter *iter);

// NOTE(nates): System paths

func_ string8 OS_SystemPath(arena *Arena, os_system_path path);

/////////////////////////////////
//~ NOTE(nates): Time functions

func_ date_time OS_GetUniversalTime(void);
func_ date_time OS_LocalTimeFromUniversalTime(date_time *time);
func_ date_time OS_UniversalTimeFromLocalTime(date_time *time);

// Percision

func_ u64 OS_GetMicroSeconds(void);
func_ u64 OS_GetMilliSeconds(void);
func_ void OS_SleepMS(u64 ms);


//////////////////////////////////////
//~ NOTE(nates): DLL's

func_ os_library OS_LoadLib(string8 filename);
func_ b32        OS_CloseLib(os_library library);
#define OS_GetLibProc(library, func_name, func_type) \
(func_type *)OS_GetLibProc_(library, func_name)
func_ void *     OS_GetLibProc_(os_library library, string8 function_name);

/////////////////////////////////////////
//~ NOTE(nates): Entropy

func_ void OS_GetEntropy(u64 *seed);


#endif // OS_ESSENTIAL_H
