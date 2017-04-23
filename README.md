# cpde_utils
Cross Platform Development Envoronment (CPDE) utility applications

CPDE is a C++ cross platform development environment based on the Code::Blocks IDE and build system. CPDE  depends on [wxWidgets](https://www.wxwidgets.org/) and [boost](http://www.boost.org/). CPDE supports Windows (MSVC compiler) and Linux. 

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
