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
   
/***************************************************************
 * Name:      cpde_pwizApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2012-07-02
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#include "cpde_pwizApp.h"

//(*AppHeaders
#include "cpde_pwizMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(cpde_pwizApp);

bool cpde_pwizApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	cpde_pwizDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
