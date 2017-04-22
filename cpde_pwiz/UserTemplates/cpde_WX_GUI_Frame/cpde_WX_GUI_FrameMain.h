/***************************************************************
 * Name:      %%%project_name_lowercase%%%Main.h
 * Purpose:   Defines Application Frame
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#ifndef %%%PROJECT_NAME_UPPERCASE%%%MAIN_H
#define %%%PROJECT_NAME_UPPERCASE%%%MAIN_H

//(*Headers(%%%project_name_lowercase%%%Frame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class %%%project_name_lowercase%%%Frame: public wxFrame
{
    public:

        %%%project_name_lowercase%%%Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~%%%project_name_lowercase%%%Frame();

    private:

        //(*Handlers(%%%project_name_lowercase%%%Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(%%%project_name_lowercase%%%Frame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(%%%project_name_lowercase%%%Frame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // %%%PROJECT_NAME_UPPERCASE%%%MAIN_H
