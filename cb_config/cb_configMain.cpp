/***************************************************************
 * Name:      cb_configMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    cpde template ()
 * Created:   2012-07-19
 * Copyright: cpde template ()
 * License:
 **************************************************************/

#include "cb_configMain.h"
#include <wx/msgdlg.h>
#include <wx/stdpaths.h>

#include "wxProcessList.h"

//(*InternalHeaders(cb_configFrame)
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

//(*IdInit(cb_configFrame)
const long cb_configFrame::ID_PANEL1 = wxNewId();
const long cb_configFrame::ID_NOTEBOOK1 = wxNewId();
const long cb_configFrame::ID_MENUITEM1 = wxNewId();
const long cb_configFrame::idMenuQuit = wxNewId();
const long cb_configFrame::idMenuAbout = wxNewId();
const long cb_configFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(cb_configFrame,wxFrame)
    //(*EventTable(cb_configFrame)
    //*)
END_EVENT_TABLE()

cb_configFrame::cb_configFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(cb_configFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("cb_config"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(800,400));
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxPoint(273,383), wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    m_select = new SelectPanel(Notebook1, ID_PANEL1, wxPoint(235,327), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Notebook1->AddPage(m_select, _("Select Configuration"), false);
    AuiManager1->AddPane(Notebook1, wxAuiPaneInfo().Name(_T("PaneName0")).CenterPane().Caption(_("Pane caption")));
    AuiManager1->Update();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, ID_MENUITEM1, _("Save config"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cb_configFrame::OnFileSaveConfig);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cb_configFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cb_configFrame::OnAbout);
    //*)


    // check if Code::Blocks is running
    std::vector<wxProcessEntry> proc = wxProcessList::Get("codeblocks");
    if(proc.size() == 0) {

       // ok, Code::Blocks is not running
       wxFileName configpath = GetConfigPath();
       SetTitle("cb_config - " + configpath.GetFullPath());

       ReadConfig(configpath);
    }
    else {
       wxMessageBox("Please shut down all instances of Code::Blocks before using cb_config", "Code::Blocks is running");

       SetTitle("cb_config - Please close Code::Blocks and restart cb_config");
    }
}

cb_configFrame::~cb_configFrame()
{
     // shut down AUI
    AuiManager1->UnInit();

    //(*Destroy(cb_configFrame)
    //*)
}

void cb_configFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void cb_configFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


wxFileName cb_configFrame::GetConfigPath()
{
   wxString sep = wxFileName::GetPathSeparator();
   wxStandardPaths& std_path = wxStandardPaths::Get();
   return wxFileName(std_path.GetUserConfigDir()+sep+"CodeBlocks"+sep+"default.conf");
}

void cb_configFrame::ReadConfig(const wxFileName& fname)
{
   if(!fname.Exists()) {
      wxMessageBox(fname.GetFullPath(), _("Code::Blocks config file does dot exist"));
      return;
   }

   m_cb_config.read_xml(fname.GetFullPath().ToStdString());
   m_select->set_config(&m_cb_config);
}

void cb_configFrame::WriteConfig(const wxFileName& fname)
{
   wxString timestamp = wxDateTime::Now().FormatISOCombined();
   timestamp.Replace(":","");
   timestamp.Replace("-","");
   timestamp.Replace("T","_");


   // before writing the config, always create a backup of the old one
   wxFileName backup_fname(fname);
   backup_fname.SetName(fname.GetName()+'_'+timestamp);
   backup_fname.AppendDir("cb_config");

   if(!wxDirExists(backup_fname.GetPath())) wxMkDir(backup_fname.GetPath());
   wxCopyFile(fname.GetFullPath(),backup_fname.GetFullPath());
   wxMessageBox(backup_fname.GetFullPath(), _("Code::Blocks config backup file created"));

   m_cb_config.write_xml(fname.GetFullPath().ToStdString());
   wxMessageBox(fname.GetFullPath(), _("Code::Blocks config file saved"));
}

void cb_configFrame::OnFileSaveConfig(wxCommandEvent& event)
{
   if(m_select->get_config()) {
      wxFileName configpath = GetConfigPath();
      WriteConfig(configpath);
   }
}
