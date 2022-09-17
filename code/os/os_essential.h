/* date = August 17th 2022 6:31 am */
#ifndef OS_ESSENTIAL_H
#define OS_ESSENTIAL_H

///////////////////////////////////
// NOTE(nates): Thread context

#if !defined(TCTX_SCRATCH_POOL_CAP)
#define TCTX_SCRATCH_POOL_CAP 4
#endif

typedef struct OS_ThreadContext
{
  Arena *scratch_pool[TCTX_SCRATCH_POOL_CAP];
} OS_ThreadContext;


////////////////////////////
//~ NOTE(nates): File iterator

typedef struct OS_FileIter
{
	U8 V[640];
} OS_FileIter;

///////////////////////////////
// NOTE(nates): File paths

typedef U32 OS_SystemPath;
enum OS_SystemPath
{
	OS_SystemPath_CurrentDir,
	OS_SystemPath_ExeDir,
	OS_SystemPath_UserDir,
	OS_SystemPath_TempDir,
	OS_SystemPath_COUNT,
};

////////////////////////////
// NOTE(nates): DLLS

typedef U64 OS_Handle;

typedef struct OS_Library
{
	OS_Handle handle;
	DenseTime last_write_time;
} OS_Library;

///////////////////////////
//~ NOTE(nates): Setup

func_ void OS_MainInit(OS_ThreadContext *tctx, int argc, char **args);
func_ Str8List OS_GetCommandLineArgs(void);

///////////////////////////////////////////////
//~ NOTE(nates): Shutdown

func_ void OS_Abort(void);

///////////////////////////////
//~ NOTE(nates): Thread Context

func_ void OS_TctxSet(void *ptr);
func_ void *OS_TctxGet(void);

//////////////////////////
// NOTE(nates): Memory Functions

func_ void *OS_ReserveMemory(U64 size);
func_ void  OS_CommitMemory(void *ptr, U64 size);
func_ void  OS_DecommitMemory(void *ptr, U64 size);
func_ void  OS_ReleaseMemory(void *base);

////////////////////////////////
//~ NOTE(nates): OS_FileFunctions

func_ Str8 OS_ReadFile(Arena *arena, Str8 filename);
func_ B32  OS_WriteListFile(Str8 filename, Str8List data);

func_ FileProperties OS_file_properties(Str8 filename);

func_ B32 OS_PathExists(Str8 path);
func_ B32 OS_DeleteFile(Str8 filename);
func_ B32 OS_RenameFile(Str8 filename, Str8 newname);
func_ B32 OS_MakeDirectory(Str8 path);
func_ B32 OS_DeleteDirectory(Str8 path);

func_ OS_FileIter OS_FileIterInit(Str8 path);
func_ B32  OS_FileIterNext(Arena *arena, OS_FileIter *iter,
													 Str8 *name_out, FileProperties *prop_out);
func_ void OS_FileIterEnd(OS_FileIter *iter);

// NOTE(nates): System paths

func_ Str8 OS_GetSystemPath(Arena *arena, OS_SystemPath path);

/////////////////////////////////
//~ NOTE(nates): Time functions

func_ DateTime os_GetUniversalTime(void);
func_ DateTime os_LocalTimeFromUniversalTime(DateTime *time);
func_ DateTime os_UniversalTimeFromLocalTime(DateTime *time);

// Percision

func_ U64 os_GetMicroSeconds(void);
func_ U64 os_GetMilliSeconds(void);
func_ void os_SleepMS(U64 ms);


//////////////////////////////////////
//~ NOTE(nates): DLL's

func_ OS_Library os_LoadLib(Str8 filename);
func_ B32        os_CloseLib(OS_Library library);
#define OS_GetLibProc(library, func_name, func_type) \
(func_type *)os_GetLibProc_(library, func_name)
func_ void *     os_GetLibProc_(OS_Library library, Str8 function_name);

/////////////////////////////////////////
//~ NOTE(nates): Entropy

func_ void os_GetEntropy(U64 *seed);


#endif // OS_ESSENTIAL_H
