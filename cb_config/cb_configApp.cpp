/***************************************************************
 * Name:      cb_configApp.cpp
 * Purpose:   Code for Application Class
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#include "cb_configApp.h"

//(*AppHeaders
#include "cb_configMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(cb_configApp);

bool cb_configApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    // wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	cb_configFrame* Frame = new cb_configFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
