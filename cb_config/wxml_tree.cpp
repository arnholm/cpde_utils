#include "wxml_tree.h"

wxml_tree::wxml_tree()
{}

wxml_tree::~wxml_tree()
{}

bool wxml_tree::read_xml(const wxFileName& file)
{
   return m_doc.Load(file.GetFullPath());
}

bool wxml_tree::write_xml(const wxFileName& file)
{
   return m_doc.Save(file.GetFullPath());
}

wxml_node  wxml_tree::get_root()
{
   return wxml_node(m_doc.GetRoot());
}
