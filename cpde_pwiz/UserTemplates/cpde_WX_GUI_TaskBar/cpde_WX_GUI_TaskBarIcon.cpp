#include "%%%project_name_lowercase%%%Icon.h"
#include "%%%project_name_lowercase%%%App.h"

#include <wx/msgdlg.h>
#include <wx/menu.h>
#include <wx/app.h>

#include "images/sample.xpm"
#include "images/smile.xpm"


const long %%%project_name_lowercase%%%Icon::ID_OPEN_DIALOG = wxNewId();
const long %%%project_name_lowercase%%%Icon::ID_EXIT = wxNewId();


BEGIN_EVENT_TABLE(%%%project_name_lowercase%%%Icon, wxTaskBarIcon)
    EVT_MENU(ID_OPEN_DIALOG, %%%project_name_lowercase%%%Icon::OnMenuOpenDialog)
    EVT_MENU(ID_EXIT,        %%%project_name_lowercase%%%Icon::OnMenuExit)
    EVT_TASKBAR_LEFT_DCLICK(%%%project_name_lowercase%%%Icon::OnLeftButtonDClick)
    EVT_TASKBAR_LEFT_DOWN(%%%project_name_lowercase%%%Icon::OnLeftButtonDown)
END_EVENT_TABLE()

%%%project_name_lowercase%%%Icon::%%%project_name_lowercase%%%Icon()
{
    wxIcon icon(smile_xpm);

    if (!SetIcon(icon, wxT("wxTaskBarIcon"))) wxMessageBox(wxT("Could not set new icon."));
}

%%%project_name_lowercase%%%Icon::~%%%project_name_lowercase%%%Icon()
{
   int i = 0;
}

wxMenu* %%%project_name_lowercase%%%Icon::CreatePopupMenu()
{
    wxMenu *menu = new wxMenu;
    menu->Append(ID_OPEN_DIALOG, _T("&Open Dialog"));
    menu->AppendSeparator();
    menu->Append(ID_EXIT,        _T("E&xit"));
    return menu;
}

void %%%project_name_lowercase%%%Icon::OnMenuOpenDialog(wxCommandEvent& )
{
  ::wxGetApp().ShowDialog(true);
}

void %%%project_name_lowercase%%%Icon::OnLeftButtonDClick(wxTaskBarIconEvent&)
{
  ::wxGetApp().ShowDialog(true);
}

void %%%project_name_lowercase%%%Icon::OnLeftButtonDown(wxTaskBarIconEvent&)
{
  ::wxGetApp().ToggleDialog();
}

void %%%project_name_lowercase%%%Icon::OnMenuExit(wxCommandEvent& event)
{
   event.Skip();

   RemoveIcon();
   ::wxGetApp().Exit();
}

