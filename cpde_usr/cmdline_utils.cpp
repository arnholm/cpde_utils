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
   
#include "cmdline_utils.h"

#include <wx/cmdline.h>  // command line parser

void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap)
{
   size_t pcount = sizeof(cmdLineDesc)/sizeof(wxCmdLineEntryDesc) - 1;
   for(size_t i=0; i<pcount; i++) {
      wxString pname = cmdLineDesc[i].longName;
      if(parser.Found(pname)) {
         wxString pvalue;
         if(cmdLineDesc[i].type == wxCMD_LINE_VAL_STRING) {
            parser.Found(pname,&pvalue);
         }
         cmdMap.insert(make_pair(pname,pvalue));
      }
   }
}

void PrintMap(CmdLineMap& cmdMap, ostream& out)
{
   for(CmdLineMap::iterator i=cmdMap.begin(); i!= cmdMap.end(); i++) {
      out << i->first.fn_str();
      if(i->second.length() > 0) {
         out << wxT("=") << i->second.fn_str();
      }
      out << endl;
   }
}
