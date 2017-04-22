REM  This procedure builds wxWidgets on Windows using MS compiler and NMAKE
REM  Procedure must be run from "Visual Studio Command Prompt"
REM      Start -> Programs ->Visual Studio tools -> VS2013 x64 Cross Tools Command Prompt
REM  
REM  change dir below as required, for example
REM      E:\CPDE2\zdep\3rdparty\wx\x64\3.0.2\lib\build\msw
REM
REM  then run this file: 
REM       nmake_build_wx30_x64.cmd
REM
call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat" x86_amd64
REM ------- make sure foreign makeflags don't interfere (QNX does this)
set MAKEFLAGS=
REM -------
nmake -f makefile.vc TARGET_CPU=amd64 BUILD=release DEBUG_INFO=1 RUNTIME_LIBS=dynamic SHARED=0 
nmake -f makefile.vc TARGET_CPU=amd64 BUILD=debug   DEBUG_INFO=1 RUNTIME_LIBS=dynamic SHARED=0  
REM
echo "==== wxWidgets 3.0 build completed ====="