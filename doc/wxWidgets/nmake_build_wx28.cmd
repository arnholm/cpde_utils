REM  This procedure builds wxWidgets on Windows using MS compiler and NMAKE
REM  Procedure must be run from "Visual Studio Command Prompt"
REM      Start -> Programs -> Microsoft Visual Studio 2010 Express -> Visual Studio Command Prompt (2010)
REM  
REM  change dir below as required, for example
REM      E:\cpde2\zzdep\3rdparty\wx\2.8.12\build\msw
REM
REM  then run this file: 
REM      E:\cpde2\zzdep\3rdparty\wx\2.8.12\build\msw>nmake_build.cmd
REM
nmake -f makefile.vc BUILD=release DEBUG_INFO=1 RUNTIME_LIBS=dynamic SHARED=0 UNICODE=0 
nmake -f makefile.vc BUILD=debug   DEBUG_INFO=1 RUNTIME_LIBS=dynamic SHARED=0 UNICODE=0 
REM
echo "wxWidgets build completed"