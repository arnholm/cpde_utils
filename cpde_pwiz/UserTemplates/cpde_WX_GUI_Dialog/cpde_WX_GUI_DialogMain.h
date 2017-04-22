/***************************************************************
 * Name:      %%%project_name_lowercase%%%Main.h
 * Purpose:   Defines Application Frame
 * Author:    Carsten Arnholm ()
 * Created:   2013-08-31
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#ifndef %%%project_name_lowercase%%%MAIN_H
#define %%%project_name_lowercase%%%MAIN_H

//(*Headers(%%%project_name_lowercase%%%Dialog)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

class %%%project_name_lowercase%%%Dialog: public wxDialog
{
    public:

        %%%project_name_lowercase%%%Dialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~%%%project_name_lowercase%%%Dialog();

    private:

        //(*Handlers(%%%project_name_lowercase%%%Dialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(%%%project_name_lowercase%%%Dialog)
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON1;
        static const long ID_STATICLINE1;
        static const long ID_BUTTON2;
        //*)

        //(*Declarations(%%%project_name_lowercase%%%Dialog)
        wxButton* Button1;
        wxStaticText* StaticText1;
        wxBoxSizer* BoxSizer2;
        wxButton* Button2;
        wxStaticLine* StaticLine1;
        wxBoxSizer* BoxSizer1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // %%%project_name_lowercase%%%MAIN_H
