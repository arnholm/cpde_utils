#include "wxProcessList.h"

#include <wx/arrstr.h>
#include <wx/utils.h>

#ifdef __WXMSW__
#include <windows.h>
#include <tlhelp32.h>
#endif

// based on
// https://forums.wxwidgets.org/viewtopic.php?t=20145&highlight=getprocesslist

static void ExecuteCommand(const wxString& command, wxArrayString& output, long flags = wxEXEC_NODISABLE| wxEXEC_SYNC)
{
#ifdef __WXMSW__
	wxExecute(command, output, flags);
#else
	FILE *fp;
	char line[512];
	memset(line, 0, sizeof(line));
	fp = popen(command.mb_str(wxConvUTF8), "r");
	while ( fgets( line, sizeof line, fp)) {
      output.Add(wxString(line, wxConvUTF8));
		memset(line, 0, sizeof(line));
	}

	pclose(fp);
#endif
}


wxProcessList::wxProcessList()
{}

wxProcessList::~wxProcessList()
{}

std::vector<wxProcessEntry> wxProcessList::Get()
{
  std::vector<wxProcessEntry> proclist;

#ifdef __WXMSW__

	//get child processes of this node
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hProcessSnap) {
		return proclist;
	}

	//Fill in the size of the structure before using it.
	PROCESSENTRY32 pe;
	memset(&pe, 0, sizeof(pe));
	pe.dwSize = sizeof(PROCESSENTRY32);

	// Walk the snapshot of the processes, and for each process,
	// kill it if its parent is pid.
	if (!Process32First(hProcessSnap, &pe)) {
		// Can't get first process.
		CloseHandle (hProcessSnap);
		return proclist;
	}

	do {
		wxProcessEntry entry;
		entry.name = pe.szExeFile;
		entry.pid = (long)pe.th32ProcessID;
		proclist.push_back(entry);
	} while (Process32Next (hProcessSnap, &pe));
	CloseHandle (hProcessSnap);
#else
	//GTK and other
	wxArrayString output;
#if defined (__WXGTK__)
	ExecuteCommand(wxT("ps -A -o pid,command  --no-heading"), output);
#elif defined (__WXMAC__)
	// Mac does not like the --no-heading...
	ExecuteCommand(wxT("ps -A -o pid,command "), output);
#endif
	for (size_t i=0; i< output.GetCount(); i++) {
		wxString line = output.Item(i);
		//remove whitespaces
		line = line.Trim().Trim(false);

		//get the process ID
		wxProcessEntry entry;
		wxString spid = line.BeforeFirst(wxT(' '));
		spid.ToLong( &entry.pid );
		entry.name = line.AfterFirst(wxT(' '));

		if (entry.pid == 0 && i > 0) {
			//probably this line belongs to the provious one
			wxProcessEntry e = proclist.back();
			proclist.pop_back();
			e.name << entry.name;
			proclist.push_back( e );
		} else {
			proclist.push_back( entry );
		}
	}
#endif

   return proclist;
}

std::vector<wxProcessEntry> wxProcessList::Get(const wxString& substring)
{
   std::vector<wxProcessEntry> procall = Get();
   std::vector<wxProcessEntry> proclist;
   for(auto& pe : procall) {
      if(pe.name.Find(substring) != wxNOT_FOUND) proclist.push_back(pe);
   }
   return proclist;
}

