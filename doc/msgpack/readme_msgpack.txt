Building msgpack on Windows with CMake
=======================================

Detailed instructions http://msgpack.org/
follow link under "Languages", click "C/C++ /msgpack"
Scroll down to find "GUI on Windows"

Quick info:
- Can be built using MSVC2013 and MSVC2013 Express
- Requires CMake


Download and buld 64bit (repeat for 32 bit by replacing x64 -> x86)
==================================================================

Create folder and go to
E:\cpde2\zzdep\3rdparty\msgpack\x64

$ git clone https://github.com/msgpack/msgpack-c.git

1 Launch cmake GUI client.
2 Set 'Where is the source code:' text box     :   E:\cpde2\zzdep\3rdparty\msgpack\x64\msgpack-c
  and 'Where to build the binaries:' text box. :   E:\cpde2\zzdep\3rdparty\msgpack\x64\msgpack-c\x64
3 Click 'Configure' button.
4 Choose your Visual Studio version.
5 Make sure static build is checked, may have to change and run 'Configure' again.
  Click 'Generate' button.
6 Open the created msgpack.sln on Visual Studio. 
7 Select Release target and build all Build all.

msgpack.lib found in E:\cpde2\zzdep\3rdparty\msgpack\x64\msgpack-c\Release


Linux
======
ref  http://msgpack.org/

$ git clone https://github.com/msgpack/msgpack-c.git
$ cd msgpack-c
$ cmake .
$ make
$ sudo make install

