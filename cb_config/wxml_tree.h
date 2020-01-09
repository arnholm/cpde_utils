#ifndef WXML_TREE_H
#define WXML_TREE_H

#include <wx/filename.h>
#include <wx/xml/xml.h>
#include "wxml_node.h"

class wxml_tree {
public:
   wxml_tree();
   virtual ~wxml_tree();

   bool read_xml(const wxFileName& file);
   bool write_xml(const wxFileName& file);

   wxml_node get_root();

protected:

private:
   wxXmlDocument m_doc;
};

#endif // WXML_TREE_H
