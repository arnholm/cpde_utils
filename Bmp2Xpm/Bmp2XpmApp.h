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
 * Name:      Bmp2XpmApp.h
 * Purpose:   Defines Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2009-09-25
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#ifndef BMP2XPMAPP_H
#define BMP2XPMAPP_H

#include <wx/app.h>

class Bmp2XpmApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // BMP2XPMAPP_H
