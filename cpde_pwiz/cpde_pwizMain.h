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
 * Name:      cpde_pwizMain.h
 * Purpose:   Defines Application Frame
 * Author:    Carsten Arnholm ()
 * Created:   2012-07-02
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#ifndef CPDE_PWIZMAIN_H
#define CPDE_PWIZMAIN_H

//(*Headers(cpde_pwizDialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <wx/config.h>

class cpde_pwizDialog: public wxDialog
{
    public:

        cpde_pwizDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~cpde_pwizDialog();

    private:

        //(*Handlers(cpde_pwizDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnCreateProjectButtonClick(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        void OnBrowseButtonClick(wxCommandEvent& event);
        void OnZipButtonClick(wxCommandEvent& event);
        void OnTextEnterRootOrProject(wxCommandEvent& event);
        //*)

        //(*Identifiers(cpde_pwizDialog)
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT1;
        static const long ID_LISTBOX1;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL2;
        static const long ID_BUTTON3;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT4;
        static const long ID_BUTTON5;
        static const long ID_STATICLINE1;
        static const long ID_BUTTON2;
        //*)

        //(*Declarations(cpde_pwizDialog)
        wxButton* BrowseButton;
        wxButton* CreateProjectButton;
        wxStaticText* StaticText2;
        wxTextCtrl* m_project_root;
        wxStaticText* m_info_text;
        wxStaticText* StaticText1;
        wxBoxSizer* BoxSizer2;
        wxTextCtrl* m_project_title;
        wxStaticText* StaticText3;
        wxStaticText* m_template_root;
        wxButton* Button2;
        wxStaticText* m_final;
        wxStaticLine* StaticLine1;
        wxListBox* m_list;
        wxBoxSizer* BoxSizer1;
        wxButton* ZipButton;
        wxStaticText* StaticText4;
        //*)

        DECLARE_EVENT_TABLE()
    private:
        wxConfig*      m_config;
};

#endif // CPDE_PWIZMAIN_H
