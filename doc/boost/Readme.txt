
How to install & compile boost

WINDOWS: build boost 1.59.0 (or later)
--------------------------------------
Download       		http://www.boost.org/users/download/
Download to:   		D:\CPDE2\zdep\3rdparty\boost
Extract 7z file to:	D:\CPDE2\zdep\3rdparty\boost\boost_1_59_0

Procedure must be run from "Visual Studio Command Prompt"
    Start -> Programs -> Microsoft Visual Studio 2010 Express -> Visual Studio Command Prompt (2010)
    Start -> Programs -> Visual Studio 2013 -> Visual Studio Tools -> VS2013 x86 Native Tools Command Prompt

1. change dir below as required, for example
   E:\cpde2\zzdep\3rdparty\boost\x64\boost_1_59_0

2. Edit bootstrap.bat and change the toolset version
   set toolset=msvc   ==>   set toolset=msvc : 120
   Where 120 corresponds to MSVC 2013 
   and   100 corresponds to MSVC 2010 

3. run bootstrap
   .\bootstrap.bat
	
4. Run build using  address-model=64 or address-model=32
   for x86: .\b2 toolset=msvc-12.0 windows-api=desktop address-model=32
   for x64: .\b2 toolset=msvc-12.0 windows-api=desktop address-model=64


Code::Blocks global variable:

global variable "boost" 
Base 			:  D:\CPDE2\zdep\3rdparty\boost\boost_1_59_0
include path	:  D:\CPDE2\zdep\3rdparty\boost\boost_1_59_0
lib path		:  D:\CPDE2\zdep\3rdparty\boost\boost_1_59_0\stage\lib

	
LINUX: install boost 1.59.0 (or later)
-------------------------------------------

Similar to Windows

/work/.../boost/boost_1_59_0$ ./bootstrap.sh
/work/.../boost/boost_1_59_0$ ./b2 

Code::Blocks global variable:

global variable "boost" 
Base            :  /work/.../boost/boost_1_59_0
include path    :  /work/.../boost/boost_1_59_0
lib path        :  /work/.../boost/boost/boost_1_59_0/stage/lib

With the above method, /work/.../boost/boost/boost_1_51_0/stage/lib must be added to LD_LIBRARY_PATH

LINUX: Alternative method, installing to /usr/local

$ sudo ./bootstrap.sh --prefix=/usr/local
$ sudo ./b2 install 

Then you don't need to change the LD_LIBRARY_PATH every time, but instead 
you can use something like
export LD_LIBRARY_PATH=$PATH:/usr/local/lib
