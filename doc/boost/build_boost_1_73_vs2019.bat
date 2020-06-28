rem
rem http://studiofreya.com/2015/05/20/building-boost-1-58-for-32-bit-and-64-bit-architectures-with-visual-studio-2013/
rem 

REM run this from "x64 Native Tools Command Prompt for VS 2019"

REM By using 'call' we can call other batch files within this batch file, 
REM without aborting the execution of the calling batch file, 
REM and using the same environment for both batch files.

REM 64bit builds
REM
rem call "%VS160COMNTOOLS%..\..\VC\Auxiliary\Build\vcvarsall.bat" x64
 
REM
REM We assume this batch procedure is placed one level above the boost package,
REM So we change the directory to bootstrap and build the boost libraries
REM Bootstrap will generate the b2 build system, and b2 will do the actual build
REM
cd boost_1_73_0
REM
call bootstrap.bat vc142
REM
REM Set address-model=32 for x86 32-bit builds
REM Set address-model=64 for x86_amd64 cross compiler or native amd64 build
REM Set architecture=x86 in all cases
REM
REM Make sure the correct version of python is found
echo using python : 3.7 : D:\\cpde_dep\\3rdparty\\python\\python37 : ; > user-config.jam
REM 
.\b2 -j8 toolset=msvc  --user-config=user-config.jam address-model=64 architecture=x86 link=static threading=multi runtime-link=shared --build-type=minimal 
echo " --- boost build ended ---"
pause

