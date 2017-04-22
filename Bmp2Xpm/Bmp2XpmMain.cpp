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
 * Name:      Bmp2XpmMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Carsten Arnholm ()
 * Created:   2009-09-25
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#include "Bmp2XpmMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(Bmp2XpmDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/filedlg.h>
#include <wx/dcbuffer.h>
#include <wx/dirdlg.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/txtstrm.h>
#include <wx/wfstream.h>


#include "xpm/red_circle.xpm"
#include "xpm/yellow_circle.xpm"
#include "xpm/green_circle.xpm"
#include "xpm/black16x16.xpm"
#include "xpm/xpm_16x16.xpm"
#include "xpm/xpm_32x32.xpm"
#include "xpm/xpm_64x64.xpm"

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

//(*IdInit(Bmp2XpmDialog)
const long Bmp2XpmDialog::ID_BUTTON4 = wxNewId();
const long Bmp2XpmDialog::ID_STATICTEXT4 = wxNewId();
const long Bmp2XpmDialog::ID_BUTTON3 = wxNewId();
const long Bmp2XpmDialog::ID_STATICBITMAP1 = wxNewId();
const long Bmp2XpmDialog::ID_BUTTON1 = wxNewId();
const long Bmp2XpmDialog::ID_CHECKBOX3 = wxNewId();
const long Bmp2XpmDialog::ID_CHECKBOX1 = wxNewId();
const long Bmp2XpmDialog::ID_PANEL2 = wxNewId();
const long Bmp2XpmDialog::ID_CHECKBOX2 = wxNewId();
const long Bmp2XpmDialog::ID_STATICBITMAP2 = wxNewId();
const long Bmp2XpmDialog::ID_STATICTEXT1 = wxNewId();
const long Bmp2XpmDialog::ID_SLIDER1 = wxNewId();
const long Bmp2XpmDialog::ID_PANEL1 = wxNewId();
const long Bmp2XpmDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Bmp2XpmDialog,wxDialog)
    //(*EventTable(Bmp2XpmDialog)
    //*)
END_EVENT_TABLE()

Bmp2XpmDialog::Bmp2XpmDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Bmp2XpmDialog)
    wxButton* ChangeDir;
    wxBoxSizer* BoxSizer5;
    wxBoxSizer* BoxSizer2;
    wxButton* SaveXPM;

    Create(parent, wxID_ANY, _("BMP2XPM - C. Arnholm 2009"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxSYSTEM_MENU|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRAISED_BORDER, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    ChangeDir = new wxButton(this, ID_BUTTON4, _("OutDir ..."), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer5->Add(ChangeDir, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_outfile = new wxStaticText(this, ID_STATICTEXT4, wxEmptyString, wxDefaultPosition, wxSize(500,-1), wxSUNKEN_BORDER, _T("ID_STATICTEXT4"));
    BoxSizer5->Add(m_outfile, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer5, 1, wxTOP|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    OpenBmp = new wxButton(Panel1, ID_BUTTON3, _("Open BMP..."), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer2->Add(OpenBmp, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_circle_bitmap = new wxStaticBitmap(Panel1, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
    BoxSizer2->Add(m_circle_bitmap, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SaveXPM = new wxButton(Panel1, ID_BUTTON1, _("Save XPM"), wxDefaultPosition, wxSize(80,-1), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer2->Add(SaveXPM, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_save_ico = new wxCheckBox(Panel1, ID_CHECKBOX3, _("Save also .ICO"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    m_save_ico->SetValue(true);
    BoxSizer2->Add(m_save_ico, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_sticky = new wxCheckBox(Panel1, ID_CHECKBOX1, _("Sticky OutDir"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    m_sticky->SetValue(false);
    BoxSizer2->Add(m_sticky, 0, wxTOP|wxLEFT|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->Fit(Panel1);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer3->Add(Panel1, 0, wxTOP|wxBOTTOM|wxEXPAND|wxALIGN_LEFT|wxALIGN_TOP, 5);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_transparent = new wxCheckBox(this, ID_CHECKBOX2, _("Bckg. col:"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    m_transparent->SetValue(true);
    BoxSizer4->Add(m_transparent, 0, wxTOP|wxBOTTOM|wxLEFT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BkgBitmap = new wxStaticBitmap(this, ID_STATICBITMAP2, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP2"));
    BoxSizer4->Add(BkgBitmap, 0, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("(RMB)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    BoxSizer4->Add(StaticText1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ZoomSlider = new wxSlider(this, ID_SLIDER1, 0, 0, 10, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SLIDER1"));
    BoxSizer4->Add(ZoomSlider, 1, wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer4, 0, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_graph = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(-1,240), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer3->Add(m_graph, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Bmp2XpmDialog::OnChangeDirClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Bmp2XpmDialog::OnOpenBmpClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Bmp2XpmDialog::OnSaveXPMClick);
    m_graph->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&Bmp2XpmDialog::OnGraphRightDown,0,this);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&Bmp2XpmDialog::OnTimer1Trigger);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&Bmp2XpmDialog::OnResize);
    //*)


   Init();
}

void Bmp2XpmDialog::Init()
{
   Timer1.Start(100);

   m_xpm_dir = wxStandardPaths::Get().GetDataDir();
   ShowOutFile(wxT(""));

   m_circle_bitmap->SetIcon(wxIcon(red_circle_xpm));
   BkgBitmap->SetIcon(wxIcon(black16x16_xpm));
   m_hex_bkg = wxT("Black");

   wxIconBundle icons;
   icons.AddIcon(wxIcon(&xpm_16x16_xpm[0]));
   icons.AddIcon(wxIcon(&xpm_32x32_xpm[0]));
   icons.AddIcon(wxIcon(&xpm_64x64_xpm[0]));
   SetIcons(icons);
}

Bmp2XpmDialog::~Bmp2XpmDialog()
{
    //(*Destroy(Bmp2XpmDialog)
    //*)
}

void Bmp2XpmDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Bmp2XpmDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void Bmp2XpmDialog::OnOpenBmpClick(wxCommandEvent& event)
{
   wxFileDialog dlg(this,wxT("Select BMP file"),wxEmptyString,wxT(""),wxT("BMP file (*.bmp)|*.bmp"),wxFD_OPEN|wxFD_FILE_MUST_EXIST);
   if(dlg.ShowModal() == wxID_OK) {

      wxString bmp_path = dlg.GetPath();
      m_name            = wxFileName(dlg.GetFilename()).GetName();
      wxString bmp_dir  = dlg.GetDirectory();

      m_bitmap = wxBitmap(bmp_path,wxBITMAP_TYPE_ANY );
      wxCoord w = m_bitmap.GetWidth();
      wxCoord h = m_bitmap.GetHeight();

      m_graph->SetSize(w,h);
      wxString msg = wxString::Format(wxT("     (%d,%d)"),w,h);
      m_circle_bitmap->SetIcon(wxIcon(yellow_circle_xpm));

      if(!m_sticky->IsChecked()) {
          m_xpm_dir = bmp_dir;
      }

      ShowOutFile(msg);
   }
}


void Bmp2XpmDialog::ShowOutFile(const wxString& msg)
{
   wxString name = (m_name.Length() > 0)?  m_name+wxT(".xpm") : "";
   wxFileName fname(m_xpm_dir,name);
   wxString xpm_path = fname.GetFullPath();
   m_outfile->SetLabel(xpm_path + msg );
}

void Bmp2XpmDialog::OnChangeDirClick(wxCommandEvent& event)
{
    wxDirDialog dlg(this,wxT("Select folder for XPM files"),m_xpm_dir,wxDD_NEW_DIR_BUTTON);
    if(dlg.ShowModal()== wxID_OK) {
        m_xpm_dir = dlg.GetPath();
        ShowOutFile("");
    }
}

void Bmp2XpmDialog::OnSaveXPMClick(wxCommandEvent& event)
{
    if(m_bitmap.IsOk()) {
       wxFileName fname(m_xpm_dir,m_name+wxT(".xpm"));
       wxString path = fname.GetFullPath();
       m_bitmap.SaveFile(path,wxBITMAP_TYPE_XPM);
       if(m_transparent->IsChecked()) {
          ReplaceBackground(path);
       }

       if(m_save_ico->IsChecked()) {
          wxBitmap ico(path,wxBITMAP_TYPE_XPM );
          wxFileName ico_name(m_xpm_dir,m_name+wxT(".ico"));
          ico.SaveFile(ico_name.GetFullPath(),wxBITMAP_TYPE_ICO);
       }

       m_circle_bitmap->SetIcon(wxIcon(green_circle_xpm));
    }
}


void Bmp2XpmDialog::ReplaceBackground(const wxString& xpm_path)
{
    wxString tmp_name = xpm_path + wxT("_tmp");
    {
        wxFFileOutputStream output(tmp_name);
        wxTextOutputStream out( output );

        wxFileInputStream input(xpm_path);
        wxTextInputStream in(input);
        while (input.CanRead() && !input.Eof()) {
            wxString line = in.ReadLine();
            line.Replace(m_hex_bkg,"None");
            out << line << endl;
        }
    }

    ::wxRemoveFile(xpm_path);
    ::wxRenameFile(tmp_name,xpm_path);

}

void Bmp2XpmDialog::OnTimer1Trigger(wxTimerEvent& event)
{
   if(m_bitmap.IsOk()) {

      int factor = 1 + ZoomSlider->GetValue();
      m_image = m_bitmap.ConvertToImage().Scale(factor*m_bitmap.GetWidth(),factor*m_bitmap.GetHeight());

      wxCoord w = m_image.GetWidth();
      wxCoord h = m_image.GetHeight();
      m_graph->SetSize(w,h);
      wxClientDC ndc(m_graph);
      PrepareDC(ndc);
      wxBufferedDC dc(&ndc,wxSize(w,h)) ;
      dc.DrawBitmap(m_image,0,0,false);
   }
}

void Bmp2XpmDialog::OnResize(wxSizeEvent& event)
{
    Layout();
}




void Bmp2XpmDialog::OnGraphRightDown(wxMouseEvent& event)
{
    wxPoint pos = event.GetPosition();
    unsigned char r = m_image.GetRed(pos.x,pos.y);
    unsigned char g = m_image.GetGreen(pos.x,pos.y);
    unsigned char b = m_image.GetBlue(pos.x,pos.y);

    const int isize=16;
    wxImage img(isize,isize);
    for(int i=0;i<isize; i++) {
        for(int j=0;j<isize; j++) {
            img.SetRGB(i,j,r,g,b);
        }
    }
    BkgBitmap->SetBitmap(wxBitmap(img));

    m_hex_bkg = wxString::Format(wxT("#%.2X%.2X%.2X"),r,g,b);
    if(m_hex_bkg == wxT("#00000"))  m_hex_bkg = wxT("Black");
}


