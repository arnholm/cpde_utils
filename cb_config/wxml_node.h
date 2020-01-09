#ifndef WXML_NODE_H
#define WXML_NODE_H

#include <wx/xml/xml.h>
#include <vector>

class wxml_node {
public:
   wxml_node();
   wxml_node(wxXmlNode* node);
   virtual ~wxml_node();

   // make the node completely empty
   void clear();

   wxString tag() const;

   wxml_node add_child(const wxString& tag);
   wxml_node add_child_cdata(const wxString& tag, wxString& content);

   bool get_child(const wxString& tag, wxml_node& child) const;
   std::vector<wxml_node> get_children() const;

   wxString get_value(const wxString& def) const;
   void set_content(const wxString& txt);

   void deep_copy(wxml_node& source,const wxString& target_name = "");

protected:
   void set_wxnode(wxXmlNode* node);

private:
   wxXmlNode* m_node;
};

#endif // WXML_NODE_H
