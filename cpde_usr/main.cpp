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
   

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/file.h>     // wxFile
#include <wx/filename.h> // wxFileName

#include "cmdline_utils.h"
#include "file_utils.h"
#include <sstream>
using namespace std;

// Example Code::Blocks post-build step line
//   $(TARGET_OUTPUT_DIR)$(PROJECT_NAME) -bin -project=$(PROJECT_NAME)  -root=$(PROJECT_DIR)  -build=$(TARGET_NAME)  -target=$(TARGET_OUTPUT_FILE)  -export=$(CPDE)

// expands to
//   w32\bin\Debug\cpde_export -bin -project=cpde_export  -root=D:\wxDev\proj\apps\cpde_export\  -build=W32_Release  -target=w32\bin\Release\cpde_export.exe  -export=C:\cpde\1.0

bool export_include(cmdline_params& params, size_t& ncopied, size_t& nremoved);
bool export_target(cmdline_params& params, const wxString& target_file, size_t& ncopied);

int main(int argc, char **argv)
{
   // initialise wxWidgets library
   wxInitializer initializer(argc,argv);

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.DisableLongOptions();
   parser.SetSwitchChars(wxT("-"));
   parser.SetCmdLine(argc,argv);
   parser.SetLogo(wxT("CPDE_usr - Cross Platform Development Environment, file export utility, V1.0-00 01-Aug-2010"));
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

   /// Actually do the file copying
   echo(wxT(" "));
   size_t ncopied_include=0,ncopied_libs=0,nremoved=0;

   // include files first, then libraries/executables
   // Check if include file export is excluded
   if(!params.xi) {
      export_include(params,ncopied_include,nremoved);
   }

   if(!params.xt) {
     export_target(params,params.target_file,ncopied_libs);

     // special handling of DLL/shared object
     // we have to export the import library as well.
     // Windows: We copy the .lib import library to the lib filder
     // Linux: We copy the .so library to the lib filder (i.e. a second copy)
     if(params.ttype == cmdline_params::Tdll) {
        params.ttype = cmdline_params::Tlib;

        #if defined(__WXMSW__)
           // On windows we have to overrule the target file name to be the name of the export library
           // On Linux the name is unchanged
           params.target_file = params.target_wxfn.GetName() + wxT(".lib");
        #endif
        export_target(params,params.target_file,ncopied_libs);
     }
   }

   // not portable, due to size_t formatting issues
   // echo(wxString::Format(wxT("--- copied %llu files, deleted %llu files ---"),ncopied_include+ncopied_libs, nremoved));

   ostringstream sout;
   sout << "--- copied " <<ncopied_include+ncopied_libs << " files, deleted " << nremoved << " files ---";
   echo(sout.str());

   echo(wxT(" "));

   return 0;
}


bool export_include(cmdline_params& params, size_t& ncopied, size_t& nremoved)
{
   // find all header files. Note that wxGetAllFiles returns full paths,
   // so make relative paths immediately

   wxString message = wxT("--- ") + params.project + wxT(": include") ;
   echo(message);

   wxString source_include = params.root + params.iroot;

   vector<wxString> header_files;
   wxGetAllFiles(source_include,wxT("*.h"),header_files);
   wxGetAllFiles(source_include,wxT("*.hpp"),header_files);
   wxTruncateLeft(source_include.Length(),header_files);

   // create the target root path for include files
   wxString target_include = params.usr + wxT("include") + wxFileName::GetPathSeparator()+ params.project + wxFileName::GetPathSeparator();

   // actually export the header files
   ncopied = wxCopyFiles(source_include,header_files,target_include,false,echo);


   // check the new contents of the target include area
   vector<wxString> target_files;
   wxGetAllFiles(target_include,wxT("*.*"),target_files);
   wxTruncateLeft(target_include.Length(),target_files);

   // are there any residual files?
   vector<wxString>  source_not_copied,target_to_be_deleted;
   wxDiffStrings(header_files,target_files,source_not_copied,target_to_be_deleted);

   // remove any old header (or other) files from the export include dir
   nremoved = wxRemoveFiles(target_include,target_to_be_deleted,false,echo);

   bool all_copied  = (header_files.size() == 0);
   bool all_removed = (target_to_be_deleted.size() == nremoved);

   return (all_removed && all_copied);
}


bool export_target(cmdline_params& params, const wxString& target_file, size_t& ncopied)
{
   // if binary option, we export to bin rather than lib
   wxString subdir = wxT("lib");
   if(params.ttype == cmdline_params::Tbin ||
      params.ttype == cmdline_params::Tdll) {
      subdir = wxT("bin");
   }

   wxString message = wxT("--- ") + params.project + wxT(": ") + subdir;
   echo(message);

   // the project target directory we are copying from
   wxString project_target_dir = params.root + params.target_dir + wxFileName::GetPathSeparator();

   // identify the target file(s)
   vector<wxString> lib_files;
   wxGetAllFiles(project_target_dir,target_file,lib_files);
   wxTruncateLeft(project_target_dir.Length(),lib_files);

   // copy the target file(s)
   bool abs_paths = false;
   wxString export_lib = params.usr + subdir + wxFileName::GetPathSeparator();
   ncopied = wxCopyFiles(project_target_dir,lib_files,export_lib,abs_paths,echo);
   return (ncopied == lib_files.size());
}

