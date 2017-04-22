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
 * Name:      Bmp2XpmApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2009-09-25
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#include "Bmp2XpmApp.h"

//(*AppHeaders
#include "Bmp2XpmMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Bmp2XpmApp);

bool Bmp2XpmApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Bmp2XpmDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
