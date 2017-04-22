/***************************************************************
 * Name:      %%%project_name_lowercase%%%Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Carsten Arnholm ()
 * Created:   2013-08-31
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#include "%%%project_name_lowercase%%%Main.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(%%%project_name_lowercase%%%Dialog)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(%%%project_name_lowercase%%%Dialog)
const long %%%project_name_lowercase%%%Dialog::ID_STATICTEXT1 = wxNewId();
const long %%%project_name_lowercase%%%Dialog::ID_BUTTON1 = wxNewId();
const long %%%project_name_lowercase%%%Dialog::ID_STATICLINE1 = wxNewId();
const long %%%project_name_lowercase%%%Dialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(%%%project_name_lowercase%%%Dialog,wxDialog)
    //(*EventTable(%%%project_name_lowercase%%%Dialog)
    //*)
END_EVENT_TABLE()

%%%project_name_lowercase%%%Dialog::%%%project_name_lowercase%%%Dialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(%%%project_name_lowercase%%%Dialog)
    Create(parent, id, _("wxWidgets/CPDE app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Welcome to\nwxWidgets\nand CPDE"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !StaticText1Font.Ok() ) StaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    StaticText1Font.SetPointSize(20);
    StaticText1->SetFont(StaticText1Font);
    BoxSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 10);
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    Button1 = new wxButton(this, ID_BUTTON1, _("About"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer2->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    Button2 = new wxButton(this, ID_BUTTON2, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    BoxSizer1->Add(BoxSizer2, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&%%%project_name_lowercase%%%Dialog::OnAbout);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&%%%project_name_lowercase%%%Dialog::OnQuit);
    //*)
}

%%%project_name_lowercase%%%Dialog::~%%%project_name_lowercase%%%Dialog()
{
    //(*Destroy(%%%project_name_lowercase%%%Dialog)
    //*)
}

void %%%project_name_lowercase%%%Dialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void %%%project_name_lowercase%%%Dialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
