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
 * Name:      Bmp2XpmMain.h
 * Purpose:   Defines Application Frame
 * Author:    Carsten Arnholm ()
 * Created:   2009-09-25
 * Copyright: Carsten Arnholm ()
 * License:
 **************************************************************/

#ifndef BMP2XPMMAIN_H
#define BMP2XPMMAIN_H

//(*Headers(Bmp2XpmDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/timer.h>
//*)
#include <wx/image.h>
#include <wx/bitmap.h>

class Bmp2XpmDialog: public wxDialog
{
    public:

        Bmp2XpmDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~Bmp2XpmDialog();

        void Init();

    private:

        //(*Handlers(Bmp2XpmDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnOpenBmpClick(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnSaveXPMClick(wxCommandEvent& event);
        void OnChangeDirClick(wxCommandEvent& event);
        void OnGraphRightDown(wxMouseEvent& event);
        //*)

        void ReplaceBackground(const wxString& xpm_path);

        void ShowOutFile(const wxString& msg);

        //(*Identifiers(Bmp2XpmDialog)
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT4;
        static const long ID_BUTTON3;
        static const long ID_STATICBITMAP1;
        static const long ID_BUTTON1;
        static const long ID_CHECKBOX3;
        static const long ID_CHECKBOX1;
        static const long ID_PANEL2;
        static const long ID_CHECKBOX2;
        static const long ID_STATICBITMAP2;
        static const long ID_STATICTEXT1;
        static const long ID_SLIDER1;
        static const long ID_PANEL1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(Bmp2XpmDialog)
        wxBoxSizer* BoxSizer1;
        wxBoxSizer* BoxSizer3;
        wxBoxSizer* BoxSizer4;
        wxButton* OpenBmp;
        wxCheckBox* m_save_ico;
        wxCheckBox* m_sticky;
        wxCheckBox* m_transparent;
        wxPanel* Panel1;
        wxPanel* m_graph;
        wxSlider* ZoomSlider;
        wxStaticBitmap* BkgBitmap;
        wxStaticBitmap* m_circle_bitmap;
        wxStaticText* StaticText1;
        wxStaticText* m_outfile;
        wxTimer Timer1;
        //*)

        DECLARE_EVENT_TABLE()

    private:
        wxBitmap m_bitmap;
        wxImage  m_image;     // same as bitmap, but possibly scaled
        wxString m_xpm_dir;   // path to ouput dir for xpm file
        wxString m_name;      // name of xpm file, no path
        wxString m_hex_bkg;
};

#endif // BMP2XPMMAIN_H
