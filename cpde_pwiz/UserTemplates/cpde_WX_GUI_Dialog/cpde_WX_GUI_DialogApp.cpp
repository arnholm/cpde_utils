/***************************************************************
 * Name:      %%%project_name_lowercase%%%App.cpp
 * Purpose:   Code for Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2013-08-31
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#include "%%%project_name_lowercase%%%App.h"

//(*AppHeaders
#include "%%%project_name_lowercase%%%Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(%%%project_name_lowercase%%%App);

bool %%%project_name_lowercase%%%App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	%%%project_name_lowercase%%%Dialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
