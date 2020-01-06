// BeginLicense:
// Part of: spacelibs - reusable libraries for 3d space calculations
// Copyright (C) 2017 Carsten Arnholm
// All rights reserved
//
// This file may be used under the terms of either the GNU General
// Public License version 2 or 3 (at your option) as published by the
// Free Software Foundation and appearing in the files LICENSE.GPL2
// and LICENSE.GPL3 included in the packaging of this file.
//
// This file is provided "AS IS" with NO WARRANTY OF ANY KIND,
// INCLUDING THE WARRANTIES OF DESIGN, MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE.
// EndLicense:

#include "xml_tree.h"
#include <fstream>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

xml_tree::xml_tree()
{}

xml_tree::~xml_tree()
{}

void xml_tree::clear()
{
   m_tree.clear();
   m_root_name = "";
}

bool xml_tree::create_root(const string& root_name)
{
   xml_node root;
   boost::optional<ptree&> node = m_tree.get_child_optional(root_name);
   if(node) return false;

   m_root_name = root_name;
   m_tree.add_child(m_root_name,ptree());
   return true;
}

bool xml_tree::get_root(xml_node& root)
{
   boost::optional<ptree&> node = m_tree.get_child_optional(m_root_name);
   if(node) {
      root =  xml_node(m_root_name, node.get());
      return true;
   }
   return false;
}

bool xml_tree::write_xml(ostream& os) const
{
   os.imbue(std::locale());
   boost::property_tree::write_xml(os,m_tree,boost::property_tree::xml_writer_make_settings<std::string>('\t', 1));
   return true;
}

bool xml_tree::write_xml(const string& path) const
{
   ofstream out(path.c_str());
   return write_xml(out);
}

bool xml_tree::read_xml(istream& is)
{
   m_tree = ptree();
   boost::property_tree::read_xml(is,m_tree,boost::property_tree::xml_parser::trim_whitespace);
   if(m_tree.size() == 1) {
      ptree::iterator i=m_tree.begin();
      m_root_name = i->first;
      return true;
   }
   return false;
}

bool xml_tree::read_xml(const string& path)
{
   ifstream in(path.c_str());
   if(in.is_open()) {
      return read_xml(in);
   }
   return false;
}

bool xml_tree::write_json(ostream& os, bool pretty)
{
   os.imbue(std::locale());
   boost::property_tree::write_json(os,m_tree,pretty);
   return true;
}

bool xml_tree::write_json(const string& path, bool pretty)
{
   ofstream out(path.c_str());
   return write_json(out,pretty);
}


bool xml_tree::read_json(istream& is)
{
   m_tree = ptree();
   boost::property_tree::read_json(is,m_tree);
   if(m_tree.size() == 1) {
      ptree::iterator i=m_tree.begin();
      m_root_name = i->first;
      return true;
   }
   return false;
}

bool xml_tree::read_json(const string& path)
{
   ifstream in(path.c_str());
   if(in.is_open()) {
      return read_json(in);
   }
   return false;
}

