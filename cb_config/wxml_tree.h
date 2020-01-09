#ifndef WXML_TREE_H
#define WXML_TREE_H

#include <wx/filename.h>
#include <wx/xml/xml.h>
#include "wxml_node.h"

// minimal emulation of cf_utils xml classes, but using wxWidgets XML implementation
// because boost property tree does not support CDATA

class wxml_tree {
public:
   wxml_tree();
   virtual ~wxml_tree();

   bool read_xml(const wxFileName& file);
   bool write_xml(const wxFileName& file);

   wxml_node get_root();

private:
   wxXmlDocument m_doc;
};

#endif // WXML_TREE_H
