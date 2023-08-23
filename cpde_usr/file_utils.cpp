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

#include "file_utils.h"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <set>
#include <functional>
#include <iterator>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>


#include <wx/filefn.h>   // File Functions
#include <wx/file.h>     // wxFile
#include <wx/dir.h>      // wxDir
#include <wx/filename.h> // wxFileName
#include <wx/tokenzr.h>  // wxStringTokenizer


size_t wxGetAllFiles(const wxString& dir, const wxString& mask, vector<wxString>& full_paths)
{
   // wxGetAllFiles performs a recursive search under "dir", looking for file names matching "mask"
   // Full paths to all files found are appended to "full_paths" (previous contents is preserved)

   wxArrayString h_files;
   wxDir::GetAllFiles(dir,&h_files,mask);
   size_t count = h_files.GetCount();

   set<wxString> no_dupes;
   if(full_paths.size() > 0)copy(full_paths.begin(),full_paths.end(),inserter(no_dupes,no_dupes.begin()));

   full_paths.reserve(full_paths.size()+count);
   for(size_t i=0; i<count; i++) {
      no_dupes.insert(h_files[i]);
   }
   full_paths.clear();
   copy(no_dupes.begin(),no_dupes.end(),back_inserter(full_paths));

   return count;
}

bool wxTruncateLeft(size_t nchar, vector<wxString>& strings)
{
   // wxTruncateLeft removes the nchar leftmost characters in all input strings.
   // Returns false if one or more strings are shorter than nchar

   for(size_t i=0; i<strings.size(); i++) {
      const wxString& txt = strings[i];
      size_t txtlen = txt.Length();
      if(txtlen < nchar)return false;
      strings[i] = txt.Right(txtlen-nchar);
   }
   return true;
}

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

size_t wxCopyFiles(const wxString& root_dir_from, const vector<wxString>& file_paths, const wxString& root_dir_to, bool abs_paths, file_callback echo)
{
   // wxCopyFiles copies a hierarchy of files from "root_dir_from" to "root_dir_to"
   // the files to be copied are listed with file paths in file_paths
   // if abs_paths=true, then the file paths include "root_dir_from" as their leftmost part
   // if abs_paths=false, then the file paths are relative to "root_dir_from"

   size_t ncopy_ok = 0;

   // First make sure source and target dirs end with a directory separator
   wxString dir_source(root_dir_from);
   if(dir_source[dir_source.Length()-1] != wxFileName::GetPathSeparator()) dir_source += wxFileName::GetPathSeparator();

   wxString dir_target(root_dir_to);
   if(dir_target[dir_target.Length()-1] != wxFileName::GetPathSeparator()) dir_target += wxFileName::GetPathSeparator();

   // Then make relative file paths
   vector<wxString> relative_file_paths(file_paths);
   if(abs_paths) wxTruncateLeft(dir_source.Length(),relative_file_paths);

   // now copy all the files
   for(size_t i=0; i<relative_file_paths.size(); i++) {
      wxString file_name = relative_file_paths[i];
      wxString path_source = dir_source + file_name;
      wxString path_target = dir_target + file_name;

      // make sure target path exists
      wxFileName  wxfilename(path_target);
      wxMkpath(wxfilename.GetPath());

      // then actually copy the file
      if(wxfilename.FileExists()) {
         ::wxRemoveFile(path_target);
      }

      // try to copy the file up to numtry times with a delay between attempts
      // Sometimes 'antivirus' software can cause problems by locking the file we are copying
      const size_t numtry=5;
      bool copy_ok = false;
      for(size_t i=0;i<numtry; i++) {
         copy_ok = wxCopyFile(path_source,path_target,true);
         if(copy_ok)break;

         wxString txt = "***Copy_RETRY ";
         ostringstream sout;
         sout << " " << setw(2) << i+1 << " of " <<  setw(2) << relative_file_paths.size() << ": " << setw(50) << left << file_name << " ==> " << path_target;
         txt += sout.str();
         echo(txt);

         if(i<1)wxBell();
         wxMilliSleep(100);
      }
      if(copy_ok) {

         // copy also the date/time info
         wxFileName fn_source(path_source);
         wxFileName fn_target(path_target);
         wxDateTime dtAccess,dtMod,dtCreate;
         if(fn_source.GetTimes(&dtAccess,&dtMod,&dtCreate)) {
            fn_target.SetTimes(&dtAccess,&dtMod,&dtCreate);
         }
      }
      if(echo) {
         wxString txt = (copy_ok)? wxT("Copy_OK   "): wxT("***Copy_ERROR ");

         ostringstream sout;
         sout << " " << setw(2) << i+1 << " of " <<  setw(2) << relative_file_paths.size() << ": " << setw(50) << left << file_name << " ==> " << path_target;
         txt += sout.str();

         echo(txt);
      }

      if(copy_ok)ncopy_ok++;
   }
   return ncopy_ok;
}

size_t wxRemoveFiles(const wxString& root_dir, const vector<wxString>& file_paths, bool abs_paths, file_callback echo)
{
   // wxRemoveFiles removes (deletes) the files specified in "file_paths"
   // if abs_paths=true, then the file paths include "root_dir_from" as their leftmost part
   // if abs_paths=false, then the file paths are relative to "root_dir"
   // returns true when all files could be deleted, otherwise false.

   // make absolute file paths
   vector<wxString> abs_file_paths;
   if(!abs_paths) {
      wxString dir_target(root_dir);
      if(dir_target[dir_target.Length()-1] != wxFileName::GetPathSeparator()) dir_target += wxFileName::GetPathSeparator();
      abs_file_paths.reserve(file_paths.size());
      for(size_t i=0; i<file_paths.size(); i++) {
         abs_file_paths.push_back(dir_target + file_paths[i]);
      }
   }
   else {
      abs_file_paths = file_paths;
   }

   size_t delete_count = 0;
   for(size_t i=0; i<abs_file_paths.size(); i++) {
      bool delete_ok = true;
      wxFileName wxfilename(abs_file_paths[i]);
      if(wxfilename.FileExists()) {
        delete_ok = wxRemoveFile(abs_file_paths[i]);
        if(delete_ok)delete_count++;
      }
      if(echo) {
         wxString txt = (delete_ok)? wxT("Delete_OK "): wxT("***Delete_ERROR ");
         txt += abs_file_paths[i];
         echo(txt);
      }
   }

   return delete_count;
}


void wxDiffStrings(const vector<wxString>& a_strings, const vector<wxString>& b_strings,
                         vector<wxString>& a_unique,        vector<wxString>& b_unique)
{
   // wxDiffStrings computes the difference between two vectors of strings
   // The strings unique to a_strings are appended to a_unique
   // The strings unique to b_strings are appended to b_unique

   set<wxString> a_set;  copy(a_strings.begin(),a_strings.end(),inserter(a_set,a_set.begin()));
   set<wxString> b_set;  copy(b_strings.begin(),b_strings.end(),inserter(b_set,b_set.begin()));

   for(size_t i=0; i<a_strings.size(); i++) b_set.erase(a_strings[i]);
   for(size_t i=0; i<b_strings.size(); i++) a_set.erase(b_strings[i]);

   copy(a_set.begin(),a_set.end(),back_inserter(a_unique));
   copy(b_set.begin(),b_set.end(),back_inserter(b_unique));
}
