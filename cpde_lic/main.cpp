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
#include <string>
#include <list>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFileName
#include <wx/dir.h>      // wxDir
#include <wx/cmdline.h>  // command line parser

#include "cmdline_utils.h"
#include <map>
using namespace std;

void ProcessFile(wxFileName fname, const list<string>& lic);

int main(int argc, char **argv)
{
   // initialise wxWidgets library
   wxInitializer initializer(argc,argv);

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.DisableLongOptions();
   parser.SetSwitchChars(wxT("-"));
   parser.SetCmdLine(argc,argv);
   parser.SetLogo(wxT("CPDE_LIC - Cross Platform Development Environment, file licensing utility, V1.0-00 01-Apr-2017"));
   if(parser.Parse() != 0) {
      // command line parse error
      return 1;
   }

   // convert from parser to map representation of parameters
   CmdLineMap cmdMap;
   ParserToMap(parser,cmdMap);
   if(cmdMap.find(wxT("verbose")) != cmdMap.end())PrintMap(cmdMap,cout);

   // extract explicit parameters
   cmdline_params params(cmdMap);
   // test if they seem to have sensible values
   if(!params.test()) {
      return 1;
   }

   // get the licensing text
   list<string> lic;
   wxFileName fname_lic(params.lic);
   ifstream in_lic(fname_lic.GetFullPath().ToStdString());
   if(in_lic.is_open())
   {
      string line;
      while(std::getline(in_lic,line))
      {
         lic.push_back(line);
      }
   }

   if(lic.size() > 0) {

      // find all files to add licensing text to

      // set recursion flag
      int flags = (params.recurse)? wxDIR_DEFAULT : wxDIR_FILES;

      // search from current directory
      wxString path = wxGetCwd();
      wxArrayString source_files;
      wxDir::GetAllFiles(path,&source_files,params.filemask,flags);

      // process the files
      size_t nfiles = source_files.GetCount();
      for(size_t i=0; i<nfiles; i++) {
         wxFileName fname(source_files[i]);
         cout << fname.GetFullPath() << endl;
         ProcessFile(fname,lic);
      }

      cout << endl;
      cout << nfiles << " files found" << endl;
      PrintMap(cmdMap,cout);
   }

   return 0;
}


void ProcessFile(wxFileName fname, const list<string>& lic)
{
   list<string> source = lic;
   ifstream in_source(fname.GetFullPath().ToStdString());
   if(in_source.is_open()) {
      string line;
      while(std::getline(in_source,line))
      {
         source.push_back(line);
      }
      in_source.close();

      ofstream out_source(fname.GetFullPath().ToStdString());
      if(out_source.is_open()) {
         for(auto& line : source) {
            out_source << line << endl;
         }
      }
   }

}
