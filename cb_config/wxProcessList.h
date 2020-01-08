#ifndef WXPROCESSLIST_H
#define WXPROCESSLIST_H

#include <vector>
#include <wx/string.h>

struct wxProcessEntry {
	wxString name;
	long pid;
};

class wxProcessList {
public:
   wxProcessList();
   virtual ~wxProcessList();

   // Get list of all processes
   static std::vector<wxProcessEntry> Get();

   // Get list of processes with name containing the substring
   static std::vector<wxProcessEntry> Get(const wxString& substring);

};

#endif // WXPROCESSLIST_H
