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
 * Name:      cpde_pwizMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Carsten Arnholm ()
 * Created:   2012-07-02
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#include "cpde_pwizMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(cpde_pwizDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "cpde_wizard.h"
#include <wx/dirdlg.h>
#include <wx/dir.h>
#include <wx/filedlg.h>
#include <wx/icon.h>
#include "file_utils.h"

#include "images/pwiz_16x16.xpm"
#include "images/pwiz_32x32.xpm"
#include "images/pwiz_64x64.xpm"

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

//(*IdInit(cpde_pwizDialog)
const long cpde_pwizDialog::ID_STATICTEXT7 = wxNewId();
const long cpde_pwizDialog::ID_STATICTEXT1 = wxNewId();
const long cpde_pwizDialog::ID_LISTBOX1 = wxNewId();
const long cpde_pwizDialog::ID_STATICTEXT3 = wxNewId();
const long cpde_pwizDialog::ID_TEXTCTRL2 = wxNewId();
const long cpde_pwizDialog::ID_BUTTON3 = wxNewId();
const long cpde_pwizDialog::ID_STATICTEXT2 = wxNewId();
const long cpde_pwizDialog::ID_TEXTCTRL1 = wxNewId();
const long cpde_pwizDialog::ID_STATICTEXT5 = wxNewId();
const long cpde_pwizDialog::ID_STATICTEXT6 = wxNewId();
const long cpde_pwizDialog::ID_BUTTON4 = wxNewId();
const long cpde_pwizDialog::ID_STATICTEXT4 = wxNewId();
const long cpde_pwizDialog::ID_BUTTON5 = wxNewId();
const long cpde_pwizDialog::ID_STATICLINE1 = wxNewId();
const long cpde_pwizDialog::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(cpde_pwizDialog,wxDialog)
    //(*EventTable(cpde_pwizDialog)
    //*)
END_EVENT_TABLE()

cpde_pwizDialog::cpde_pwizDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(cpde_pwizDialog)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, _("cpde Code::Blocks project wizard"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_template_root = new wxStaticText(this, ID_STATICTEXT7, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    BoxSizer6->Add(m_template_root, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    BoxSizer3->Add(BoxSizer6, 0, wxBOTTOM|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Select project template"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer3->Add(StaticText1, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    m_list = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxSize(521,150), 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    BoxSizer3->Add(m_list, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Root folder to create project folder in"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    BoxSizer3->Add(StaticText3, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_project_root = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer4->Add(m_project_root, 1, wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BrowseButton = new wxButton(this, ID_BUTTON3, _("..."), wxDefaultPosition, wxSize(25,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer4->Add(BrowseButton, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer4, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Project Title"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer3->Add(StaticText2, 0, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    m_project_title = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    BoxSizer3->Add(m_project_title, 0, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT5, _("Final path to project"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    BoxSizer3->Add(StaticText4, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    m_final = new wxStaticText(this, ID_STATICTEXT6, wxEmptyString, wxDefaultPosition, wxSize(-1,25), 0, _T("ID_STATICTEXT6"));
    wxFont m_finalFont(8,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Arial"),wxFONTENCODING_DEFAULT);
    m_final->SetFont(m_finalFont);
    BoxSizer3->Add(m_final, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    CreateProjectButton = new wxButton(this, ID_BUTTON4, _("Create project file"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer3->Add(CreateProjectButton, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_info_text = new wxStaticText(this, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    BoxSizer3->Add(m_info_text, 0, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    ZipButton = new wxButton(this, ID_BUTTON5, _("zip templates..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer2->Add(ZipButton, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 5);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer2->Add(StaticLine1, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    Button2 = new wxButton(this, ID_BUTTON2, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer2->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    BoxSizer1->Add(BoxSizer2, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&cpde_pwizDialog::OnTextEnterRootOrProject);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cpde_pwizDialog::OnTextEnterRootOrProject);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cpde_pwizDialog::OnBrowseButtonClick);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&cpde_pwizDialog::OnTextEnterRootOrProject);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cpde_pwizDialog::OnCreateProjectButtonClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cpde_pwizDialog::OnZipButtonClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&cpde_pwizDialog::OnQuit);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&cpde_pwizDialog::OnInit);
    //*)

   m_config = new wxConfig(wxT("cpde_pwiz"),wxT("CPDE"));

   wxIconBundle icons;
   icons.AddIcon(wxIcon(&pwiz_16x16_xpm[0]));
   icons.AddIcon(wxIcon(&pwiz_32x32_xpm[0]));
   icons.AddIcon(wxIcon(&pwiz_64x64_xpm[0]));
   SetIcons(icons);
}

cpde_pwizDialog::~cpde_pwizDialog()
{
    //(*Destroy(cpde_pwizDialog)
    //*)

    delete m_config;
}

void cpde_pwizDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void cpde_pwizDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void cpde_pwizDialog::OnInit(wxInitDialogEvent& event)
{
   wxString template_root = cpde_wizard::getDefaultTemplateRoot();
   vector<wxString> full_paths;
   cpde_wizard::getTemplates(template_root,full_paths);
   m_template_root->SetLabel(template_root);

   m_list->Clear();
   for(auto it=full_paths.begin(); it!=full_paths.end(); it++) {
      m_list->Append(*it);
   }

   wxString path = m_config->Read(wxT("/ProjectRoot"),wxT(""));
   m_project_root->SetValue(path);
}

void cpde_pwizDialog::OnBrowseButtonClick(wxCommandEvent& event)
{
   wxDirDialog dlg(this);
   dlg.SetPath(m_project_root->GetValue());
   if(dlg.ShowModal()) {
      m_project_root->SetValue(dlg.GetPath());
   }
}

void cpde_pwizDialog::OnCreateProjectButtonClick(wxCommandEvent& event)
{
   wxArrayInt selections;
   if(m_list->GetSelections(selections) == 0) {
      wxMessageBox(wxT("Please select in list"),wxT("No template selected"));
      return;
   }

   wxString template_root = cpde_wizard::getDefaultTemplateRoot();
   wxString template_name = m_list->GetStringSelection();

   wxString project_root =  m_project_root->GetValue();
   if(project_root.length() == 0) {
      wxMessageBox(wxT("Non-zero path to project root folder must be specified"));
      return;
   }
   if(!wxDir::Exists(project_root)) {
      int answer = wxMessageBox(wxT("Do you want to create it?"),wxT("Folder ") + project_root + wxT(" does not exist"), wxICON_QUESTION|wxYES_NO);
      if (answer != wxYES)return;
   }
   m_config->Write(wxT("/ProjectRoot"),project_root);

   wxString project_name =  m_project_title->GetValue();
   if(project_name.length() == 0) {
      wxMessageBox(wxT("A Non-zero project title must be specified"));
      return;
   }

   m_info_text->SetLabel(wxT("Wizard Error?"));
   cpde_wizard wizard(template_root,template_name,project_root,project_name);
   if(wizard.run_wizard()) {
      m_info_text->SetLabel(wxT("Wizard completed. Use File | Open in C::B"));
   }
}


void cpde_pwizDialog::OnZipButtonClick(wxCommandEvent& event)
{
   wxString path = m_config->Read(wxT("/ProjectRoot"),wxT(""));

   wxFileDialog dlg(this,wxT("Save As Zip file"),path,wxT("UserTemplates.zip"),wxT("ZIP file (*.zip)|*.zip"),wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
   if(dlg.ShowModal() == wxID_OK) {

      wxString zip_path = dlg.GetPath();
      ::wxRemoveFile(zip_path);
      cpde_wizard::zipTemplates(zip_path);
   }
}

void cpde_pwizDialog::OnTextEnterRootOrProject(wxCommandEvent& event)
{
   wxString project_root  = m_project_root->GetValue();
   wxString project_title = m_project_title->GetValue();


   int fweight = wxNORMAL;
   wxString template_name = m_list->GetStringSelection();
   if(template_name.Length() > 0) {
      if(project_title.Length() > 0) {
         fweight = wxBOLD;
      }
      else {
         project_title = wxT("<PROJECT TITLE>");
      }
   }

   wxFont m_finalFont(8,wxSWISS,wxFONTSTYLE_NORMAL,fweight,false,_T("Arial"),wxFONTENCODING_DEFAULT);
   m_final->SetFont(m_finalFont);
   wxFileName project_final(project_root,project_title,wxT("cbp"));
   m_final->SetLabel(project_final.GetFullPath());
   m_final->Update();
}
