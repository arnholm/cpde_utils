/***************************************************************
 * Name:      %%%project_name_lowercase%%%App.cpp
 * Purpose:   Code for Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2013-08-31
 * Copyright: Carsten Arnholm ()
 * License:   wxWidgets
 **************************************************************/

#include "%%%project_name_lowercase%%%App.h"
#include "%%%project_name_lowercase%%%Icon.h"
#include "%%%project_name_lowercase%%%Dialog.h"

//(*AppHeaders
#include <wx/image.h>
//*)

IMPLEMENT_APP(%%%project_name_lowercase%%%App);

bool %%%project_name_lowercase%%%App::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK ) {

      // Similar to a dialog based application, a dialog is the top window.
      // However, the dialog is initially not shown in a CPDE taskbar application.
      // Instead a derivation from wxTaskBarIcon is created that installs a task bar icon
      // and which provides a popup-menu to show the main dialog
      m_dlg = new %%%project_name_lowercase%%%Dialog(0);
      m_taskBarIcon = new %%%project_name_lowercase%%%Icon();
    	SetTopWindow(m_dlg);
    }
    return true;
}

void %%%project_name_lowercase%%%App::ShowDialog(bool show)
{
   m_dlg->Show(show);
}

void %%%project_name_lowercase%%%App::ToggleDialog()
{
   if(m_dlg->IsShown())m_dlg->Show(false);
   else                m_dlg->Show(true);
}

void %%%project_name_lowercase%%%App::Exit()
{
   delete m_dlg;
   wxApp::CleanUp();
   exit(0);
}
