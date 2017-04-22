rem
rem http://studiofreya.com/2015/05/20/building-boost-1-58-for-32-bit-and-64-bit-architectures-with-visual-studio-2013/
rem 

REM By using 'call' we can call other batch files within this batch file, 
REM without aborting the execution of the calling batch file, 
REM and using the same environment for both batch files.

REM 32bit builds
REM For MSVC2013 Express/Professional: x86  

REM 64bit builds
REM For MSVC2013 Express     :  x86_amd64  (cross-compiler, Express does not contain the native 'amd64' toolkit)
REM For MSVC2013 Professional:  amd64      (native compiler)
REM
call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat" amd64
 
REM
REM We assume this batch procedure is placed one level above the boost package,
REM So we change the directory to bootstrap and build the boost libraries
REM Bootstrap will generate the b2 build system, and b2 will do the actual build
REM
cd boost_1_59_0
REM
REM Before running bootstrap, remember to edit the line 
REM from "set toolset=msvc"  
REM to   "set toolset=msvc : 120 ;"
call bootstrap.bat
REM
REM Set address-model=32 for x86 32-bit builds
REM Set address-model=64 for x86_amd64 cross compiler or native amd64 build
REM Set architecture=x86 in all cases
REM
.\b2 -j8 toolset=msvc-12.0 address-model=64 architecture=x86 link=static threading=multi runtime-link=shared --build-type=minimal 
echo " --- boost build ended ---"
pause

