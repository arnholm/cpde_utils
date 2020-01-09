#ifndef WXML_NODE_H
#define WXML_NODE_H

#include <wx/xml/xml.h>
#include <vector>

// wxml_node is a wrapper around wxXmlNode, it does NOT own the object
// this class is not supposed to be 100% general, only general enough to support Code::Blocks config XML
class wxml_node {
public:
   wxml_node();
   wxml_node(wxXmlNode* node);
   virtual ~wxml_node();

   // make the node completely empty
   void clear();

   // return the element tag
   wxString tag() const;

   // add child element to this element
   wxml_node add_child(const wxString& tag);

   // get named child
   bool get_child(const wxString& tag, wxml_node& child) const;

   // get children as a vector
   std::vector<wxml_node> get_children() const;

   // get contained value, whether CDATA or not
   wxString get_value(const wxString& def) const;

   // set CDATA text on a CDATA child of this node
   // For this to work, such a CDATA node must already exist.
   // fails silently if not
   void set_content(const wxString& txt);

   // perform deep copy to this node from source
   void deep_copy(wxml_node& source,const wxString& target_name = "");

protected:
   wxml_node add_child_cdata(const wxString& tag, wxString& content);
   void set_wxnode(wxXmlNode* node);

private:
   wxXmlNode* m_node;
};

#endif // WXML_NODE_H
