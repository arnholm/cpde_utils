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


// > cpde_lic -r *.cpp -lic=license.txt

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
  //   kind            shortName         longName          description                                parameterType          flag(s)
  { wxCMD_LINE_SWITCH, wxT_2("h"),       wxT_2("help"),    wxT_2("command line parameter help"),      wxCMD_LINE_VAL_NONE,   wxCMD_LINE_OPTION_HELP },
  { wxCMD_LINE_SWITCH, wxT_2("r"),       wxT_2("recurse"), wxT_2("Recursive file search"),            wxCMD_LINE_VAL_NONE,   wxCMD_LINE_PARAM_OPTIONAL  },
  { wxCMD_LINE_OPTION, wxT_2("lic"),     wxT_2("lic"),     wxT_2("license file"),                     wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_PARAM,  wxT_2("filemask"),wxT_2("filemask"),wxT_2("<filemask>"),                       wxCMD_LINE_VAL_STRING, wxCMD_LINE_OPTION_MANDATORY  },
  { wxCMD_LINE_NONE,   wxT_2(""),        wxT_2(""),        wxT_2(""),                                 wxCMD_LINE_VAL_NONE  , wxCMD_LINE_PARAM_OPTIONAL    }
};

void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap);
void PrintMap(CmdLineMap& cmdMap, ostream& out);


struct cmdline_params
{
   cmdline_params(CmdLineMap& cmdMap)
   {
      recurse  = cmdMap.find(wxT("recurse")) != cmdMap.end();
      lic      = cmdMap[wxT("lic")];
      filemask = cmdMap[wxT("filemask")];
   }

   bool test()
   {
      if(lic.Length() == 0)         { cout << "lic parameter has zero length" << endl; return false; }
      if(filemask.Length() == 0)    { cout << "filemask parameter has zero length" << endl; return false; }

      wxFileName fname_lic(lic);
      if(!fname_lic.Exists())       { cout << "lic file does not exist: " << fname_lic.GetFullPath() << endl; return false; }
      return true;
   }

   wxString lic;
   wxString filemask;
   bool     recurse;
};

#endif // CMDLINE_UTILS_H
