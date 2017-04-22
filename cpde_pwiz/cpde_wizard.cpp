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
   
#include "cpde_wizard.h"
#include <wx/dir.h>
#include <wx/wfstream.h>
#include <wx/zipstrm.h>
#include <wx/txtstrm.h>
#include "file_utils.h"


 wxString CBDIR =
#if defined(__WXMSW__)
   wxT("CodeBlocks");
#else
   wxT(".codeblocks");
#endif



cpde_wizard::cpde_wizard(const wxString& template_root,
                         const wxString& template_name,
                         const wxString& project_root,
                         const wxString& project_name)
: m_template_root(template_root)
, m_template_name(template_name)
, m_template_name_UPR(template_name)
, m_project_root(project_root)
, m_project_name(project_name)
, m_project_name_UPR(project_name)
{
   m_template_name_UPR.MakeUpper();
   m_project_name_UPR.MakeUpper();
}

cpde_wizard::~cpde_wizard()
{
}

wxString cpde_wizard::getDefaultTemplateRoot()
{
   static wxStandardPathsBase& std_path = wxStandardPaths::Get();
   wxString config = std_path.GetUserConfigDir();
   wxFileName template_root(config,wxT(""));
   template_root.AppendDir(CBDIR);
   template_root.AppendDir(wxT("UserTemplates"));
   return template_root.GetFullPath();
}


void cpde_wizard::getTemplates(const wxString& template_root, vector<wxString>& full_paths)
{
   wxString mask = wxT("cpde_*");
   wxDir dir;
   if(dir.Open(template_root)) {
      wxString filename;
      bool cont = dir.GetFirst(&filename, mask);
      while (cont) {
        full_paths.push_back(filename);
        cont = dir.GetNext(&filename);
      }
   }
}

void cpde_wizard::zipTemplates(const wxString& zip_path)
{
   wxString root = getDefaultTemplateRoot();
   size_t rootlen = root.Length();
   wxString mask = wxT("*");
   vector<wxString> full_paths;
   wxGetAllFiles(root,mask,full_paths);

   if(full_paths.size() > 0) {

      // create the zip file
      wxFFileOutputStream out(zip_path);
      wxZipOutputStream  zip_out(out);
      wxTextOutputStream txt_out(zip_out);

      for(auto it=full_paths.begin(); it!=full_paths.end(); it++) {

         // Create an entry in the zip file for this template file
         wxFileName template_file(*it);
         wxString entry_fullpath = template_file.GetFullPath();
         size_t txtlen = entry_fullpath.Length();
         wxString entry_path = entry_fullpath.Right(txtlen-rootlen);
         zip_out.PutNextEntry(entry_path);


         // actually write the file data
         wxFileInputStream input(entry_fullpath);
         wxTextInputStream in(input);
         while (input.CanRead() && !input.Eof()) {
            wxString line = in.ReadLine();
            txt_out << line << endl;
         }
      }
   }
}

bool cpde_wizard::run_wizard()
{
   wxFileName project_folder(m_project_root,m_project_name);
   if(wxMkpath(project_folder.GetFullPath())) {

      wxFileName template_folder(m_template_root,m_template_name);

      vector<wxString> full_paths;
      wxString mask = wxT("*");
      wxGetAllFiles(template_folder.GetFullPath(), mask,full_paths);
      for(auto it=full_paths.begin(); it!=full_paths.end(); it++) {
         wxFileName template_file(*it);
         process_file(template_file);
      }
      return true;
   }
   return false;
}

bool cpde_wizard::process_file(wxFileName& template_file)
{
   wxString in_debug = template_file.GetFullPath();
   wxFileName template_folder(m_template_root,m_template_name);

   // Get the path to the template file (excluding the file name)
   wxString template_file_path = template_file.GetPath();
   size_t   file_path_len = template_file_path.Length();
   size_t   folder_len    = template_folder.GetFullPath().Length();

   // get the file path relative to the project by removing the leftmost characters,
   // i.e. subtract of template folder path length from template file path length
   wxString file_rel_path = template_file_path.Right(file_path_len-folder_len);

   // open the template file for reading
   wxTextFile  in_file;
   if(in_file.Open(template_file.GetFullPath())) {

      // the target file name is like the template file name (no path)
      // but we must replace the template name with the project name in the string
      wxString target_name = template_file.GetName();
      target_name.Replace(m_template_name,m_project_name);

      // create the path if needed
      wxFileName target_folder(m_project_root + wxFileName::GetPathSeparator());
      target_folder.AppendDir(m_project_name);
      if(file_rel_path.Length() > 0) {
         // remove the path separator before adding
         file_rel_path = file_rel_path.Right(file_rel_path.Length()-1);
         target_folder.AppendDir(file_rel_path);
      }
      wxString folder_dbg = target_folder.GetFullPath();
      wxMkpath(target_folder.GetFullPath());

      // construct the full target file path
      wxFileName target_file(target_folder.GetFullPath(),target_name,template_file.GetExt());
      wxString file_dbg = target_file.GetFullPath();

      // create the target file
      wxTextFile  out_file;
      if(out_file.Create(target_file.GetFullPath())) {

         // copy line by line
         wxString line = in_file.GetFirstLine();
         while(!in_file.Eof()) {
            line.Replace(wxT("%%%project_name_lowercase%%%"), m_project_name);
            line.Replace(wxT("%%%PROJECT_NAME_UPPERCASE%%%"), m_project_name_UPR);
            out_file.AddLine(line);
            line = in_file.GetNextLine();
         }
         out_file.Write();
         out_file.Close();

         in_file.Close();
         return true;
      }
   }
   return false;
}
