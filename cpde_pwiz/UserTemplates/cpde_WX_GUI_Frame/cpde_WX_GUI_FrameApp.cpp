/***************************************************************
 * Name:      %%%project_name_lowercase%%%App.cpp
 * Purpose:   Code for Application Class
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
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
    // wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	%%%project_name_lowercase%%%Frame* Frame = new %%%project_name_lowercase%%%Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
