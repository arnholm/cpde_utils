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
   
#ifndef CMDLINE_UTILS_H
#define CMDLINE_UTILS_H

#include <iostream>
#include <map>
using namespace std;

#include <wx/filename.h>                      // wxFileName
#include <wx/cmdline.h>                       // wxCmdLineParser
typedef map<wxString,wxString> CmdLineMap;    // CmdLineMap

// For info on command line parsing, see:
//      http://docs.wxwidgets.org/2.8/wx_wxcmdlineparser.html#wxcmdlineparser

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind            shortName         longName          description                                                                   parameterType          flag(s)
  { wxCMD_LINE_SWITCH, wxT_2("h"),       wxT_2("help"),    wxT_2("command line parameter help"),                                               wxCMD_LINE_VAL_NONE,   wxCMD_LINE_OPTION_HELP },
  { wxCMD_LINE_SWITCH, wxT_2("v"),       wxT_2("verbose"), wxT_2("Verbose mode, echo parameters"),                                             wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("bin"),     wxT_2("bin"),     wxT_2("Target file is executable binary"),                                          wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("dll"),     wxT_2("dll"),     wxT_2("Target file is dll/shared object"),                                          wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("xi"),      wxT_2("xi"),      wxT_2("Exclude copying include files"),                                             wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_SWITCH, wxT_2("xt"),      wxT_2("xt"),      wxT_2("Exclude copying target file"),                                               wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },

  { wxCMD_LINE_OPTION, wxT_2("project"), wxT_2("project"), wxT_2("Project name"),                                                              wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_OPTION, wxT_2("build"),   wxT_2("build"),   wxT_2("Project build target name"),                                                 wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_OPTION, wxT_2("root"),    wxT_2("root"),    wxT_2("Project root directory (absolute)"),                                         wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_OPTION, wxT_2("iroot"),   wxT_2("iroot"),   wxT_2("Project include root directory (relative) if different from project root"),  wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL    },
  { wxCMD_LINE_OPTION, wxT_2("target"),  wxT_2("target"),  wxT_2("Project target directory (relative) & file name"),                           wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_OPTION, wxT_2("usr"),     wxT_2("usr"),     wxT_2("Usr root directory (absolute) = $(CPDE_USR)"),                               wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },

  { wxCMD_LINE_NONE,   wxT_2(""),        wxT_2(""),        wxT_2(""),                                                                          wxCMD_LINE_VAL_NONE  , wxCMD_LINE_PARAM_OPTIONAL    }
};

void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap);
void PrintMap(CmdLineMap& cmdMap, ostream& out);


struct cmdline_params
{
   cmdline_params(CmdLineMap& cmdMap)
   {
      ttype       = Tlib;  // default is static library
      if(cmdMap.find(wxT("bin")) != cmdMap.end()) {
         ttype    = Tbin;
      }
      else if(cmdMap.find(wxT("dll")) != cmdMap.end()) {
         ttype    = Tdll;
      }

      xi          = cmdMap.find(wxT("xi")) != cmdMap.end();
      xt          = cmdMap.find(wxT("xt")) != cmdMap.end();
      project     = cmdMap[wxT("project")];
      root        = cmdMap[wxT("root")];
      build       = cmdMap[wxT("build")];
      target      = cmdMap[wxT("target")];
      iroot       = cmdMap[wxT("iroot")];
      usr         = cmdMap[wxT("usr")];
      target_dir  = wxFileName(target).GetPath();
      target_file = wxFileName(target).GetFullName();
      target_wxfn = wxFileName(target);

      if(root.Length()>0 && root[root.Length()-1] != wxFileName::GetPathSeparator()) root += wxFileName::GetPathSeparator();
      if(usr.Length()>0 && usr[usr.Length()-1] != wxFileName::GetPathSeparator()) usr += wxFileName::GetPathSeparator();
      if(iroot.Length()>0 && iroot[iroot.Length()-1] != wxFileName::GetPathSeparator()) iroot += wxFileName::GetPathSeparator();
   }

   bool test()
   {
      if(project.Length() == 0) { cout << "project parameter has zero length" << endl; return false; }
      if(root.Length() == 0)    { cout << "root parameter has zero length" << endl; return false; }
      if(build.Length() == 0)   { cout << "build parameter has zero length" << endl; return false; }
      if(target.Length() == 0)  { cout << "target parameter has zero length" << endl; return false; }
      if(usr.Length() == 0)     { cout << "usr parameter has zero length" << endl; return false; }
      return true;
   }

   wxString project;
   wxString root;
   wxString build;
   wxString target;
   wxString iroot;
   wxString usr;
   wxString target_dir;
   wxString target_file;
   wxFileName target_wxfn;

   enum TTarget { Tbin=0,   // executable file
                  Tlib,     // static library
                  Tdll };   // DLL or shared object

   TTarget  ttype;
   bool     xi;
   bool     xt;
};

#endif // CMDLINE_UTILS_H
