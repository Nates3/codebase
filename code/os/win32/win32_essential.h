/* date = August 21st 2022 10:22 am */
#ifndef WIN32_ESSENTIAL_H
#define WIN32_ESSENTIAL_H

///////////////////////////
// NOTE(nates): Windows includes 

#include <windows.h>

//////////////////////////////////
// NOTE(nates): Win32 file iter

typedef struct win32_fileiter
{
  HANDLE Handle;
	WIN32_FIND_DATAW FindData;
	b32 Done;
} win32_fileiter;

StaticAssert(sizeof(win32_fileiter) <= sizeof(os_fileiter), win32_fileiter);

/////////////////////////////////////////////////////////////
// NOTE(nates): Special winmain init function

func_ void Win32MainInit(os_thread_context *tctx_memory,
												 HINSTANCE hInstance, HINSTANCE hPrevInstance,
												 LPSTR lpCmdLine, int nCmdShow);

////////////////////////////////////////////////////////////////////
// NOTE(nates): Win32 time helpers
func_ file_properties 
Win32FilePropertiesFromFileData(DWORD file_attributes, FILETIME creation_time, 
																FILETIME last_write_time, DWORD file_size_high, 
																DWORD file_size_low);
func_ date_time   Win32DateTimeFromSystemTime(SYSTEMTIME *time);
func_ SYSTEMTIME Win32SystemTimeFromDateTime(date_time *time);
func_ date_time   Win32DateTimeFromFileTime(FILETIME *filetime);
func_ dense_time  Win32DenseTimeFromFileTime(FILETIME *filetime);

#endif //WIN32_ESSENTIAL_H
