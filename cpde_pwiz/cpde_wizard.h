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
   
#ifndef CPDE_WIZARD_H
#define CPDE_WIZARD_H

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFileName
#include <wx/file.h>     // wxFile
#include <wx/textfile.h> // wxTextFile
#include <wx/stdpaths.h> // wxStandardPaths
#include <vector>
using namespace std;

class cpde_wizard {
public:
   cpde_wizard(const wxString& template_root,
               const wxString& template_name,
               const wxString& project_root,
               const wxString& project_name);
   virtual ~cpde_wizard();

   static wxString getDefaultTemplateRoot();
   static void getTemplates(const wxString& template_root, vector<wxString>& full_paths);
   static void zipTemplates(const wxString& zip_path);

   bool run_wizard();
private:
   bool process_file(wxFileName& template_file);

private:
   wxString m_template_root;
   wxString m_template_name;
   wxString m_template_name_UPR;

   wxString m_project_root;
   wxString m_project_name;
   wxString m_project_name_UPR;
};

#endif // CPDE_WIZARD_H
