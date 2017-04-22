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
   
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <vector>
#include <iostream>
using namespace std;

#include <wx/string.h>   // wxString

typedef void (*file_callback)(const wxString& txt);

inline void echo(const wxString& txt)
{
   cout << txt.fn_str() << endl;
}

/// wxCopyFiles copies a hierarchy of files from "root_dir_from" to "root_dir_to"
// the files to be copied are listed with file paths in file_paths
// if abs_paths=true, then the file paths include "root_dir_from" as their leftmost part
// if abs_paths=false, then the file paths are relative to "root_dir_from"
// return value is number of files copied
size_t wxCopyFiles(const wxString& root_dir_from, const vector<wxString>& file_paths, const wxString& root_dir_to, bool abs_paths, file_callback echo);


/// wxDiffStrings computes the difference between two vectors of strings
// The strings unique to a_strings are appended to a_unique
// The strings unique to b_strings are appended to b_unique
void wxDiffStrings(const vector<wxString>& a_strings, const vector<wxString>& b_strings,
                         vector<wxString>& a_unique,        vector<wxString>& b_unique);


/// wxGetAllFiles performs a recursive search under "dir", looking for file names matching "mask"
// Full paths to all files found are appended to "full_paths" (previous contents is preserved)
size_t wxGetAllFiles(const wxString& dir, const wxString& mask, vector<wxString>& full_paths);


/// wxMkpath creates a directory path in the file system
// It is similar to wxMkdir, but it can create a complete path without
// requiring all but the last to already exist.
// The return value is true when the path already exists or is created
bool wxMkpath(const wxString& path);


/// wxTruncateLeft removes the nchar leftmost characters in all input strings.
// Returns false if one or more strings are shorter than nchar
bool wxTruncateLeft(size_t nchar, vector<wxString>& strings);


/// wxRemoveFiles removes (deletes) the files specified in "file_paths"
// if abs_paths=true, then the file paths include "root_dir_from" as their leftmost part
// if abs_paths=false, then the file paths are relative to "root_dir"
// returns number of files removed
size_t wxRemoveFiles(const wxString& root_dir, const vector<wxString>& file_paths, bool abs_paths, file_callback echo);


#endif // FILE_UTILS_H
