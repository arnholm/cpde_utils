Building boost 64bit using MSVC2013 Express
===========================================

MSVC2013 Express does not have a native 64 bit compiler, 
so we must use the x86_amd64 cross-compiler to generate the libraries

Procedure:

1. Start "VS2013 x64 Cross Tools Command Prompt"
2. go to E:\cpde3\zdep\3rdparty\boost\x64\boost_1_59_0
3. Run vcvars32 x64
4. Edit bootstrap.bat 
      change from : set toolset=msvc 
      to          : set toolset=msvc : 120
5. .\bootstrap.bat
6. .\b2 --toolset=msvc-12.0 --address-model=64 --build-type=desktop

Result in ..\stage\lib