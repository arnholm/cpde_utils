#ifndef SELECTPANEL_H
#define SELECTPANEL_H

//(*Headers(SelectPanel)
#include <wx/button.h>
#include <wx/combobox.h>
#include <wx/listbox.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

#include "wxml_tree.h"
#include "wxml_node.h"

class SelectPanel: public wxPanel
{
public:

   SelectPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize, int opt=0, const wxString& name="SelectPanel");
   virtual ~SelectPanel();

   void set_config(wxml_tree* cb_config);

   wxml_tree* get_config() { return m_cb_config; }

   //(*Declarations(SelectPanel)
   wxButton* m_compiler_apply;
   wxButton* m_globals_apply;
   wxComboBox* m_compiler_target;
   wxListBox* m_compilers;
   wxListBox* m_globals;
   wxStaticText* m_compiler_parent;
   wxStaticText* m_compiler_text;
   wxStaticText* m_global_text;
   //*)

protected:
   void CopyCompiler(wxml_node& compiler, wxml_node& target, const std::string& target_name, wxml_node& source);

   void FillGlobals(wxml_node& root);
   void FillCompilers(wxml_node& root);

   //(*Identifiers(SelectPanel)
   static const long ID_STATICTEXT1;
   static const long ID_LISTBOX1;
   static const long ID_BUTTON1;
   static const long ID_STATICTEXT2;
   static const long ID_STATICTEXT3;
   static const long ID_LISTBOX2;
   static const long ID_COMBOBOX1;
   static const long ID_BUTTON2;
   //*)

private:

   //(*Handlers(SelectPanel)
   void OnGlobalApplyClick(wxCommandEvent& event);
   void OnCompilerApplyClick(wxCommandEvent& event);
   //*)

   DECLARE_EVENT_TABLE()
private:
   wxml_tree* m_cb_config;
};

#endif
