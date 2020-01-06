#include "SelectPanel.h"
#include <map>
using namespace std;

//(*InternalHeaders(SelectPanel)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(SelectPanel)
const long SelectPanel::ID_STATICTEXT1 = wxNewId();
const long SelectPanel::ID_LISTBOX1 = wxNewId();
const long SelectPanel::ID_BUTTON1 = wxNewId();
const long SelectPanel::ID_STATICTEXT2 = wxNewId();
const long SelectPanel::ID_STATICTEXT3 = wxNewId();
const long SelectPanel::ID_LISTBOX2 = wxNewId();
const long SelectPanel::ID_COMBOBOX1 = wxNewId();
const long SelectPanel::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SelectPanel,wxPanel)
	//(*EventTable(SelectPanel)
	//*)
END_EVENT_TABLE()

SelectPanel::SelectPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size, int opt, const wxString& name)
: m_cb_config(0)
{
	//(*Initialize(SelectPanel)
	wxBoxSizer* BoxSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* BoxSizer3;
	wxStaticBoxSizer* StaticBoxSizer1;
	wxStaticBoxSizer* StaticBoxSizer2;
	wxStaticBoxSizer* StaticBoxSizer3;

	Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("wxID_ANY"));
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxVERTICAL, this, _("Global Variable Set"));
	m_global_text = new wxStaticText(this, ID_STATICTEXT1, _("SelectedSet"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticBoxSizer1->Add(m_global_text, 0, wxALL|wxEXPAND, 5);
	m_globals = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	StaticBoxSizer1->Add(m_globals, 1, wxALL|wxEXPAND, 5);
	m_globals_apply = new wxButton(this, ID_BUTTON1, _("Apply"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	StaticBoxSizer1->Add(m_globals_apply, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(StaticBoxSizer1, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer2 = new wxStaticBoxSizer(wxVERTICAL, this, _("User Defined Compiler"));
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	m_compiler_text = new wxStaticText(this, ID_STATICTEXT2, _("SelectedCompiler"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	BoxSizer3->Add(m_compiler_text, 2, wxLEFT|wxRIGHT|wxEXPAND, 5);
	m_compiler_parent = new wxStaticText(this, ID_STATICTEXT3, _("(Parent)"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	BoxSizer3->Add(m_compiler_parent, 1, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(BoxSizer3, 0, wxEXPAND, 5);
	m_compilers = new wxListBox(this, ID_LISTBOX2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
	StaticBoxSizer2->Add(m_compilers, 1, wxALL|wxEXPAND, 5);
	StaticBoxSizer3 = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Target Compiler Name"));
	m_compiler_target = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
	m_compiler_target->SetSelection( m_compiler_target->Append(_("MSVC")) );
	StaticBoxSizer3->Add(m_compiler_target, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(StaticBoxSizer3, 0, wxEXPAND, 5);
	m_compiler_apply = new wxButton(this, ID_BUTTON2, _("Apply"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	StaticBoxSizer2->Add(m_compiler_apply, 0, wxALL|wxEXPAND, 5);
	BoxSizer2->Add(StaticBoxSizer2, 1, wxALL|wxEXPAND, 5);
	BoxSizer1->Add(BoxSizer2, 1, wxALL|wxEXPAND, 5);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
	BoxSizer1->SetSizeHints(this);

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SelectPanel::OnGlobalApplyClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SelectPanel::OnCompilerApplyClick);
	//*)
}

SelectPanel::~SelectPanel()
{
	//(*Destroy(SelectPanel)
	//*)
}

void SelectPanel::set_config(xml_tree* cb_config)
{
   m_cb_config = cb_config;

   // display configuration
   xml_node root;
   if(m_cb_config->get_root(root)) {
      if(root.tag() == "CodeBlocksConfig") {
         FillGlobals(root);
         FillCompilers(root);
      }
   }

}


void  SelectPanel::FillGlobals(xml_node& root)
{
   // display global variable sets
   m_globals->Clear();
   m_global_text->SetLabel("");

   xml_node gcv;
   if(root.get_child("gcv",gcv)) {

      // set names
      xml_node sets;
      if(gcv.get_child("sets",sets)) {
         for(auto i=sets.begin(); i!=sets.end(); i++) {
            xml_node gcv_set(i);
            m_globals->Append(gcv_set.tag());
         }
      }

      // active set
      xml_node active;
      if(gcv.get_child("ACTIVE",active)) {
         xml_node str;
         if(active.get_child("str",str)) {
            std::string active_set = str.get_value("");
            m_global_text->SetLabel(active_set);
            m_globals->SetStringSelection(active_set);
         }
      }
   }
}

// apply new global variables set
void SelectPanel::OnGlobalApplyClick(wxCommandEvent& event)
{
   xml_node root;
   if(m_cb_config->get_root(root)) {
      if(root.tag() == "CodeBlocksConfig") {

         xml_node gcv;
         if(root.get_child("gcv",gcv)) {

            // get selection in list
            std::string active_set = m_globals->GetStringSelection().MakeLower().ToStdString();

            // apply selection in "ACTIVE" tag
            xml_node active;
            if(gcv.get_child("ACTIVE",active)) {
               xml_node str;
               if(active.get_child("str",str)) {
                  str.put_value(active_set);
               }
            }
         }
      }

      FillGlobals(root);
   }
}

void  SelectPanel::FillCompilers(xml_node& root)
{
   // display active compiler

   m_compilers->Clear();
   m_compiler_text->SetLabel("");
   m_compiler_parent->SetLabel("");

   xml_node compiler;
   if(root.get_child("compiler",compiler)) {

      // mapping between compiler and "parent" compiler
      map<string,string> parent_compilers;

      // show user defined compilers
      xml_node user_sets;
      if(compiler.get_child("user_sets",user_sets)) {
         for(auto i=user_sets.begin(); i!=user_sets.end(); i++) {
            xml_node user_compiler(i);

            // get compiler name (uppercase)
            xml_node name;
            string compiler_name;
            if(user_compiler.get_child("NAME",name)) {
               xml_node str;
               if(name.get_child("str",str)) {
                  compiler_name = str.get_value("");
                  m_compilers->Append(compiler_name);
               }
            }

            xml_node parent;
            if(user_compiler.get_child("PARENT",parent)) {
               xml_node str;
               if(parent.get_child("str",str)) {
                  std::string parent_comp = str.get_value("");
                  std::transform(compiler_name.begin(),compiler_name.end(),compiler_name.begin(),::tolower);

                  // <compiler,parent_compiler> both in lowercase
                  parent_compilers[compiler_name] = parent_comp;
               }
            }
         }
      }

      // get the default (=active) compiler and display it with its parent compiler
      // also highlight in list
      xml_node default_compiler;
      if(compiler.get_child("DEFAULT_COMPILER",default_compiler)) {
         xml_node str;
         if(default_compiler.get_child("str",str)) {
            std::string active_comp = str.get_value("");
            m_compiler_parent->SetLabel('('+parent_compilers[active_comp]+')');
            std::transform(active_comp.begin(),active_comp.end(),active_comp.begin(),::toupper);
            m_compiler_text->SetLabel(active_comp);
            m_compilers->SetStringSelection(active_comp);
         }
      }
   }

}


void SelectPanel::OnCompilerApplyClick(wxCommandEvent& event)
{
   xml_node root;
   if(m_cb_config->get_root(root)) {
      if(root.tag() == "CodeBlocksConfig") {
         xml_node compiler;
         if(root.get_child("compiler",compiler)) {
            std::string source_name = m_compilers->GetStringSelection().MakeLower().ToStdString();
            std::string target_name = m_compiler_target->GetStringSelection().MakeLower().ToStdString();
            if(target_name != source_name) {
               xml_node user_sets;
               if(compiler.get_child("user_sets",user_sets)) {
                  xml_node source;
                  xml_node target;
                  user_sets.get_child(source_name,source);

                  // copy the compiler node to the target node
                  if(!user_sets.get_child(target_name,target)) {
                     target = user_sets.add_child(target_name);
                  }
                  CopyCompiler(compiler,target,target_name,source);
               }
            }
         }
      }

      FillCompilers(root);
   }
}


void SelectPanel::CopyCompiler(xml_node& compiler, xml_node& target, const string& target_name, xml_node& source)
{
   xml_node default_compiler;
   if(compiler.get_child("DEFAULT_COMPILER",default_compiler)) {
      target = xml_node(target_name,source);

      xml_node name;
      if(target.get_child("NAME",name)) {
         string target_name_upper = target_name;
         std::transform(target_name.begin(),target_name.end(),target_name_upper.begin(),::toupper);
         xml_node str;
         if(name.get_child("str",str)) {
            str.put_value(target_name_upper);
         }
      }

      xml_node parent;
      if(target.get_child("PARENT",parent)) {
         xml_node str;
         if(parent.get_child("str",str)) {
            str.put_value(source.tag());
         }
      }
   }

}
