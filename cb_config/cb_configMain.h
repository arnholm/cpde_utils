/***************************************************************
 * Name:      cb_configMain.h
 * Purpose:   Defines Application Frame
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#ifndef CB_CONFIGMAIN_H
#define CB_CONFIGMAIN_H
#include <wx/filename.h>

//(*Headers(cb_configFrame)
#include <wx/aui/aui.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/statusbr.h>
//*)

#include "SelectPanel.h"
#include "xml_tree.h"

class cb_configFrame: public wxFrame
{
public:

  cb_configFrame(wxWindow* parent,wxWindowID id = -1);
  virtual ~cb_configFrame();

  wxFileName GetConfigPath();

  void ReadConfig(const wxFileName& fname);
  void WriteConfig(const wxFileName& fname);

private:

  //(*Handlers(cb_configFrame)
  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnFileSaveConfig(wxCommandEvent& event);
  //*)

  //(*Identifiers(cb_configFrame)
  static const long ID_PANEL1;
  static const long ID_NOTEBOOK1;
  static const long ID_MENUITEM1;
  static const long idMenuQuit;
  static const long idMenuAbout;
  static const long ID_STATUSBAR1;
  //*)

  //(*Declarations(cb_configFrame)
  SelectPanel* m_select;
  wxAuiManager* AuiManager1;
  wxMenuItem* MenuItem3;
  wxNotebook* Notebook1;
  wxStatusBar* StatusBar1;
  //*)

  DECLARE_EVENT_TABLE()

private:
  xml_tree m_cb_config;  // Code::Blocks 'default.conf'
};

#endif // CB_CONFIGMAIN_H
