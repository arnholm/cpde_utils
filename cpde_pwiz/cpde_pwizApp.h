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
 * Name:      cpde_pwizApp.h
 * Purpose:   Defines Application Class
 * Author:    Carsten Arnholm ()
 * Created:   2012-07-02
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#ifndef CPDE_PWIZAPP_H
#define CPDE_PWIZAPP_H

#include <wx/app.h>

class cpde_pwizApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // CPDE_PWIZAPP_H
