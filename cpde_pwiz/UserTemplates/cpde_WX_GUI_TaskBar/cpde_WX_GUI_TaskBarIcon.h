#ifndef %%%PROJECT_NAME_UPPERCASE%%%ICON_H
#define %%%PROJECT_NAME_UPPERCASE%%%ICON_H

#include <wx/string.h>   // wxString
#include <wx/taskbar.h>


class %%%project_name_lowercase%%%Icon : public wxTaskBarIcon {
public:
   %%%project_name_lowercase%%%Icon();
   virtual ~%%%project_name_lowercase%%%Icon();

private:
   static const long ID_OPEN_DIALOG;
   static const long ID_EXIT;

private:
   virtual wxMenu* CreatePopupMenu();

   void OnLeftButtonDClick(wxTaskBarIconEvent&);
   void OnLeftButtonDown(wxTaskBarIconEvent&);
   void OnMenuOpenDialog(wxCommandEvent&);
   void OnMenuExit(wxCommandEvent&);

   void OnMenuCheckmark(wxCommandEvent&);
   void OnMenuUICheckmark(wxUpdateUIEvent&);

   DECLARE_EVENT_TABLE()
};

#endif 
