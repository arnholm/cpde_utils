# cpde_utils
Cross Platform Development Envoronment (CPDE) utility applications

CPDE is a C++ cross platform development environment based on the Code::Blocks IDE and build system. CPDE  depends on [wxWidgets](https://www.wxwidgets.org/) and [boost](http://www.boost.org/). CPDE supports Windows (MSVC compiler) and Linux. 

See [Code::Blocks configuration of MSVC compiler tools and Windows SDK](doc/toolchain/CodeBlocks_MSVC_setup.pdf) for a description of how to configure Code::Blocks for CPDE using a MSVC compiler on Windows.

## cpde_utils applications
* **cpde_pwiz** - Wizard application to generate a new CPDE-style Code::Blocks project 
  * can be run independently or used via the Code::Blocks Tools menu
  * creates Code::Blocks CPDE-style project files from template projects 
  * generated projects references cpde_usr and wx-config, see below.
* **cpde_usr** - Application to export files from project build to a common "usr" folder. 
  * Run as post-build step in CPDE projects
  * Exports all header files in project
  * Exports library and binary files as requested
* **wx-config** - This is only used on Windows with MSVC build targets using wxWidges. 
* **cpde_lic** - Utility to add licensing text to source files
* **Bmp2Xpm** - Utility to convert Windows .bmp files to .xpm and .ico formats

## cpde_usr command line syntax
The cpde_usr application is typically run as a post-build step in a Code::Blocs project. The syntax is:

	    Usage:  cpde_usr [-h] [-v] [-bin] [-dll] [-xi] [-xt] -project <str> -build <str> -root <str> [-iroot <str>] -target <str> -usr <str>
	      -h                    command line parameter help
	      -v                    Verbose mode, echo parameters
	      -bin                  Target file is executable binary
	      -dll                  Target file is dll/shared object
	      -xi                   Exclude copying include files
	      -xt                   Exclude copying target file
	      -project=<str>        Project name
	      -build=<str>          Project build target name
	      -root=<str>           Project root directory (absolute)
	      -iroot=<str>          Project include root directory (relative) if different from project root
	      -target=<str>         Project target directory (relative) & file name
	      -usr=<str>            Usr root directory (absolute) = $(CPDE_USR)    

Typical invocation in a Code::Blocks post-build step:

    $(CPDE_USR)/bin/cpde_usr -dll -project=$(PROJECT_NAME)  -root=$(PROJECT_DIR)  -build=$(TARGET_NAME)  -target=$(TARGET_OUTPUT_FILE)  -usr=$(CPDE_USR)
    
In this example $(CPDE_USR) evaluates an environment variable and $(PROJECT_NAME), $(PROJECT_DIR), $(TARGET_NAME) and $(TARGET_OUTPUT_FILE) are standard variables in Code::Blocks.

## wx-config command line syntax (Windows only)
This version of wx-config is for Windows only (on Linux the syntax is different). The use of wx-config is only relevant when wxWidgets is ised in the project. Instead of setting up all include paths and libraries manually, wx-config will automatically generate this information, based on the location of the wxWidgets installation

    Usage: wx-config [options]
    Options:
      --prefix[=DIR]              Path of the wxWidgets installation (e.g. C:\wxWidgets\x64\3.1.0)
      --wxcfg[=DIR]               Relative path of the build (ie. vc_x64_lib\mswud )
      --iso                       Output only "iso C++" options, ignore WX settings
      --cflags                    Outputs all pre-processor and compiler flags.
      --cxxflags                  Same as --cflags but for C++.
      --libs                      Outputs all linker flags.

Typical invocation in a Code::Blocks compile step, notice the use of backtics (') 

    `$(CPDE_USR)\bin\wx-config.exe --prefix=$(#wx) --wxcfg=$(#wx.release) --cxxflags`
    
Typical invocation in a Code::Blocks link step, notice the use of backtics (')   

    `$(CPDE_USR)\bin\wx-config.exe  --prefix=$(#wx) --wxcfg=$(#wx.release) --libs`
    
In the compile and link steps above, the Code::Blocks [global variable](http://wiki.codeblocks.org/index.php/Global_compiler_variables) 'wx' defines a wxWidgets 64-bit build using MSVC compiler, for debug and release:

    wx.base    = E:\<somepath>\wx\x64\3.1.0
    wx.debug   = vc_x64_lib\mswud
    wx.release = vc_x64_lib\mswu
    
    
## cpde_lic
cpde_lic inserts the text from the provided license file into the files matching the filemask

    Usage: cpde_lic [-h] [-r] -lic <str> <filemask>
      -h            command line parameter help
      -r            Recursive file search
      -lic=<str>    license file    

    
## Bmp2Xpm 
This is a stand-alone GUI application for image conversion. Useful for compiling image data such as icons into the application in a portable manner.


# building cpde_utils for linux
This description applies to 64 bit Ubuntu/Kubuntu etc. 

cpde is based on the Code::Blocks IDE and build system, so you need to install it
    
    $ sudo apt-get install codeblocks codeblocks-contrib
    
Every cpde project exports include files, libraries and binaries to a common area where other projects can find them. You should to set up this first. The name and location of the root folder (`~/cpde/usr` below) is user defined, but the subfolder names must be `include`,  `lib` and `bin` :

    $ mkdir ~/cpde
    $ cd ~/cpde
    $ mkdir usr
    $ mkdir usr/include
    $ mkdir usr/lib
    $ mkdir usr/bin

Add a corresponding setting to your ~/.bashrc file so you can run the programs built easily

    export PATH=$PATH:~/cpde/usr/bin/
    export LD_LIBRARY_PATH=$PATH
    
Now enable Code::Blocks to be be aware of the common file area. Start Code::Blocks and make sure the 'Environment variables' plugin is installed and enabled, then add an environment variable via `Settings -> Environment ...` , scroll on the left and select 'Environment variables'. Enter a new variable called `CPDE_USR` and assign the value  `~/cpde/usr` (make it consistent with your definition above). 

The basic setup is complete, but we need wxWidgets to compile some of the utilities, including the cpde_user application. CPDE requires wxWidgets built as static libraries. Begin with installing the wxWidgets dependencies:

    $ sudo apt-get install g++
    $ sudo apt-get install zlibc
    $ sudo apt-get install pkg-config
    $ sudo apt-get install gtk2.0
    $ sudo apt-get install freeglut3 freeglut3-dev
    
Clone cpde_utils from GitHub
    
    $ mkdir ~/cpde_git
    $ cd ~/cpde_git
    $ git clone https://github.com/arnholm/cpde_utils
     
Download wxWidgets 3.0.3 from http://wxwidgets.org/downloads/ 
Extract to ~/cpde_git/3rdparty/wx/3.0.3  - it should now contain folders "art", "build" etc. 
Then compile using the cpde_utils build script for wxWidgets, note the "buildgtk" subfolder:

    $ mkdir  ~/cpde_git/3rdparty/wx/3.0.3/buildgtk
    $ cd ~/cpde_git/3rdparty/wx/3.0.3/buildgtk
    $ cp ~/cpde_git/cpde_utils/doc/wxWidgets/buildWxWidgets.sh .
    $ chmod 700 ./buildWxWidgets.sh 
    $ sudo ./buildWxWidgets.sh 

Following a successful build, wxWidgets becomes installed to /usr/local . In Code::Blocks, define the 'wx' global variable via `Settings -> Global variables ...` . 

Built-in field 
* `base` : /usr/local

In addition 2 user defined fields are required
* `config` : `/usr/local/bin/wx-config --version=3.0 --toolkit=gtk2`  
* `debug` : `dummy`
    
Close and restart Code::Blocks to save the settings. Then open the cpde_utils.workspace file and build the cpde_usr application (*Note:* make sure the GCC_Release build target is selected first). On successful build it will be copied to the `bin` folder you defined for cpde. You can test it in a terminal window by typing

    $ cpde_usr

It is recommended to supplement with a similar Code::Blocks global variable setting for boost

    $ sudo apt-get install boost-all-dev
    
In Code::Blocks, define the 'boost' global variable via `Settings -> Global variables ...` . 

Built-in fields 
* `base` : /usr/include/boost 
* `lib` : /usr/lib/x86_64-linux-gnu

Basic setup is complete.
