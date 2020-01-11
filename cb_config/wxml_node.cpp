#include "wxml_node.h"

wxml_node::wxml_node()
: m_node(0)
{}

wxml_node::wxml_node(wxXmlNode* node)
: m_node(node)
{}

wxml_node::~wxml_node()
{}

void wxml_node::clear()
{
   if(m_node) {
      wxXmlNode* c = m_node->GetChildren();
      while (c) {
         wxml_node child(c);
         child.clear();

         wxXmlNode* c_this = c;
         c = c->GetNext();

         m_node->RemoveChild(c_this);
         delete c_this;
      }

      std::vector<wxString> attribs;
      wxXmlAttribute* a = m_node->GetAttributes();
      while(a) {
         attribs.push_back(a->GetName());
         a = a->GetNext();
      }

      for(auto& a : attribs) {
         m_node->DeleteAttribute(a);
      }
   }
}


wxString wxml_node::tag() const
{
   return ( (m_node != 0)? m_node->GetName() : "" );
}

wxml_node wxml_node::add_child(const wxString& tag)
{
   wxXmlNode* c = new wxXmlNode(m_node,wxXML_ELEMENT_NODE,tag);
   return wxml_node(c);
}

wxml_node wxml_node::add_child_cdata(const wxString& tag,wxString& content)
{
   wxXmlNode* c = new wxXmlNode(m_node,wxXML_CDATA_SECTION_NODE,tag,content);
   return wxml_node(c);
}

bool wxml_node::get_child(const wxString& tag, wxml_node& child) const
{
   if(!m_node)return false;

   wxXmlNode* c = m_node->GetChildren();
   while (c) {
      if(c->GetName() == tag) {
         child.set_wxnode(c);
         return true;
      }
      c = c->GetNext();
   }
   return false;
}

void wxml_node::set_wxnode(wxXmlNode* node)
{
   m_node = node;
}

std::vector<wxml_node> wxml_node::get_children() const
{
   std::vector<wxml_node> children;
   if(m_node) {
      wxXmlNode* c = m_node->GetChildren();
      while (c) {
         children.push_back(wxml_node(c));
         c = c->GetNext();
      }
   }
   return children;
}

wxString wxml_node::get_value(const wxString& def) const
{
   if(!m_node)return "";
   return m_node->GetNodeContent();
}

void wxml_node::set_content(const wxString& txt)
{
   if(!m_node)return;
   wxXmlNode* c = m_node->GetChildren();
   if(c && c->GetType() == wxXML_CDATA_SECTION_NODE) {
      c->SetContent(txt);
   }
}

void wxml_node::deep_copy(wxml_node& source,const wxString& target_name)
{
   // clear any contents of this node
   clear();

   wxString tag_copy = (target_name.length() > 0)? target_name : tag();
   m_node->SetName(tag_copy);

   // copy any attributes
   wxXmlAttribute* a = m_node->GetAttributes();
   while(a) {
      m_node->AddAttribute(a->GetName(),a->GetValue());
      a = a->GetNext();
   }

   // clone the contents from the source node
   for(auto& source_child : source.get_children() ) {
      wxString child_tag = source_child.tag();

      wxString value = source_child.get_value("");
      if(value.length() > 0) {

         // store the value as CDATA grand-child
         // we assume leaf node here, so no more deep copy
         wxml_node target_child = add_child(source_child.tag());
         wxml_node target_child_cdata = target_child.add_child_cdata("cdata",value);
      }
      else {

         // ordinary element
         wxml_node target_child = add_child(source_child.tag());
         target_child.deep_copy(source_child);
      }
   }

}
