/* date = August 21st 2022 10:22 am */
#ifndef WIN32_ESSENTIAL_H
#define WIN32_ESSENTIAL_H

///////////////////////////
// NOTE(nates): Windows includes 

#include <windows.h>

//////////////////////////////////
// NOTE(nates): Win32 file iter

typedef struct W32_FileIter
{
  HANDLE handle;
	WIN32_FIND_DATAW find_data;
	B32 done;
} W32_FileIter;

StaticAssert(sizeof(W32_FileIter) <= sizeof(OS_FileIter), W32_FileIter);

/////////////////////////////////////////////////////////////
// NOTE(nates): Special winmain init function

func_ void W32MainInit(OS_ThreadContext *tctx_memory,
											 HINSTANCE hInstance, HINSTANCE hPrevInstance,
											 LPSTR lpCmdLine, int nCmdShow);

////////////////////////////////////////////////////////////////////
// NOTE(nates): W32 time helpers
func_ FileProperties 
W32FilePropertiesFromFileData(DWORD file_attributes, FILETIME creation_time, 
															FILETIME last_write_time, DWORD file_size_high, 
															DWORD file_size_low);
func_ DateTime   W32DateTimeFromSystemTime(SYSTEMTIME *time);
func_ SYSTEMTIME W32SystemTimeFromDateTime(DateTime *time);
func_ DateTime   W32DateTimeFromFileTime(FILETIME *filetime);
func_ DenseTime  W32DenseTimeFromFileTime(FILETIME *filetime);

#endif //WIN32_ESSENTIAL_H
