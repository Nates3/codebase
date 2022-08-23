@echo off

call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64 1>NUL 2>NUL


set Options= -DENABLE_ASSERT=1
set CompilerSwitches=-Od -c -FC -nologo -Z7 -Fomain.obj %Options%

set LinkerLibs=kernel32.lib winmm.lib userenv.lib advapi32.lib
set LinkerFlags=-nologo -incremental:no -opt:ref -DEBUG:FULL main.obj %LinkerLibs%

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

cl %CompilerSwitches% ..\code\main.c
link.exe %LinkerFlags% %LinkerLibs%

popd