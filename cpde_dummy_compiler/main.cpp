// BeginLicense:
// Part of: cpde_utils
// Copyright (C) 2017 Carsten Arnholm  http://arnholm.org/
//
// This file may be used under the terms of either the GNU General
// Public License version 2 or 3 (at your option) as published by the
// Free Software Foundation and appearing in the files LICENSE.GPL2
// and LICENSE.GPL3 included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// EndLicense:
   
#include <iostream>
#include <fstream>
#include <list>
#include <stdlib.h>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filename.h>    // wxFileName
#include <wx/tokenzr.h>  // wxStringTokenizer


// The CPDE dummy compiler can be used as a stand in for Windows .asm assmbler
// Instead of compiling the assembler file, it creates a dummy c++ file and compiles it to the target object file name.
// This way, the linker is happy even though the .asm file isn't compiled-
// This procedure makes it possible to manage conditional compilation via C::B global variables

bool wxMkpath(const wxString& path)
{
   // wxMkpath is similar to wxMkdir, except it can create
   // a complete path without requiring all but the last to already exist.
   // The return value is true when the path already exists or is created

   // if the path already exists, there is nothing to do
   if(!wxDirExists(path)) {

      list<wxString> tokens;
      wxStringTokenizer tkz(path, wxT("/\\"));
      while ( tkz.HasMoreTokens() )       {
          wxString token = tkz.GetNextToken();
          tokens.push_back(token);
      }

      wxString sub_path;
      for(list<wxString>::iterator it = tokens.begin(); it != tokens.end(); it++) {
         sub_path += *it + wxFileName::GetPathSeparator();
         if(!wxDirExists(sub_path)) {
            if(!wxMkdir(sub_path))return false;
         }
      }
   }
   return true;
}

void write_source(string source_file, string function_name)
{
   ofstream cpp(source_file);
   cpp << "void dummy_compiler_" << function_name << "() {} " << endl;
}

string cpp_compile_command(string source_path, string object_path)
{
   string command = "cl /nologo /c " + source_path + " /Fo" + object_path;
   return command;
}


int main(int argc, char **argv)
{
   // initialise wxWidgets library
   wxInitializer initializer(argc,argv);

   for(int i=1; i<argc; i++) {
      wxString arg(argv[i]);

      if("/Fo" == arg.Left(3)) {

         // get the full target file name
         wxString target(arg.Right(arg.size()-3));
         wxFileName fntarget(target);
         wxString name = fntarget.GetName();
         wxString path = fntarget.GetPath();

         // make sure the output path exists
         wxMkpath(path);

         // construct a C++ file with a function of that name
         wxFileName fn_source_file(path,name,"cpp");
         string source_path = fn_source_file.GetFullPath().ToStdString();
         write_source(source_path,name.ToStdString());
         string command = cpp_compile_command(source_path,target.ToStdString());

         // compile the generated file and remove the generated source file afterwards
         cout << "cpde_dummy_compiler: " << arg << endl;
         system(command.c_str());
         wxRemove(fn_source_file.GetFullPath());

         return 0;
      }
   }
   return 0;
}


