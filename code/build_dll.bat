@echo off

if not exist ..\build mkdir ..\build
pushd ..\build

set compiler_flags=-Od -c -TC -FC -nologo -Z7 -Fo:dll_main.obj
set link_flags=-nologo -DLL -DEBUG:FULL -EXPORT:U32Sum
set link_libs=winmm.lib

cl %compiler_flags% ../code/dll_main.c
link.exe %link_flags% dll_main.obj %link_libs%

popd