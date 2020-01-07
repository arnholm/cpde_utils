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

#include "xml_node.h"

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost::algorithm;

xml_node::xml_node()
{}

xml_node::xml_node(const string& tag, const xml_node& other_node )
: m_tag(tag)
, m_ptree_node(other_node.m_ptree_node)
{}

xml_node::xml_node(const string& tag, ptree& ptree_node)
: m_tag(tag)
, m_ptree_node(ptree_node)
{}

xml_node::xml_node(iterator it)
: m_tag(it->first)
, m_ptree_node(it->second)
{}

xml_node& xml_node::operator=(const xml_node& other_node )
{
   m_tag        = other_node.m_tag;
   m_ptree_node = other_node.m_ptree_node;
   return *this;
}

void xml_node::deep_copy(xml_node& source, const string& tag)
{
   string tag_copy = (tag.length() > 0)? tag : m_tag;
   m_tag = tag;

   // clear any contents of this node
   m_ptree_node.get().clear();

   // clone the contents from the source node
   if(source.has_value()) {
      put_value(source.get_value(""));
   }
   for(auto i=source.begin(); i!=source.end(); i++) {
      xml_node source_child(i);
      xml_node target_child = add_child(source_child.tag());
      target_child.deep_copy(source_child);
   }
}

xml_node::~xml_node()
{}

bool xml_node::is_valid() const
{
   return (bool)m_ptree_node;
}

string xml_node::tag() const
{
   return m_tag;
}

void set_tag(const string& tag);

bool xml_node::is_attribute_node() const
{
   return ("<xmlattr>" == m_tag);
}

bool xml_node::add_property(const string& name, const string& value)
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      m_ptree_node.get().put(attrib,value);
      return true;
   }
   return false;
}

bool xml_node::add_property(const string& name, size_t value)
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      m_ptree_node.get().put(attrib,value);
      return true;
   }
   return false;
}

bool xml_node::add_property(const string& name, int value)
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      m_ptree_node.get().put(attrib,value);
      return true;
   }
   return false;
}

bool xml_node::add_property(const string& name, double value)
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      m_ptree_node.get().put(attrib,value);
      return true;
   }
   return false;
}

bool xml_node::has_property(const string& name) const
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      boost::optional<string> v = m_ptree_node.get().get_optional<string>(attrib); // anything can be represented as a string
      return (bool)v;
   }
   return false;
}

string xml_node::get_property(const string& name, const string& default_value) const
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      boost::optional<string> v = m_ptree_node.get().get_optional<string>(attrib);
      if(v) {
         trim(v.get());
         return v.get();
      }
   }
   return  default_value;
}

size_t xml_node::get_property(const string& name, size_t default_value) const
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      boost::optional<size_t> v = m_ptree_node.get().get_optional<size_t>(attrib);
      if(v) return v.get();
   }
   return  default_value;
}


int    xml_node::get_property(const string& name, int default_value) const
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      boost::optional<int> v = m_ptree_node.get().get_optional<int>(attrib);
      if(v) return v.get();
   }
   return  default_value;
}

double xml_node::get_property(const string& name, double default_value) const
{
   if(m_ptree_node) {
      string attrib = "<xmlattr>." + name;
      boost::optional<double> v = m_ptree_node.get().get_optional<double>(attrib);
      if(v) return v.get();
      return  default_value;
   }
   return  default_value;
}

bool xml_node::put_value(const string& value)
{
   if(m_ptree_node) {
      m_ptree_node.get().put_value(value);
      return true;
   }
   return false;
}

bool xml_node::put_value(size_t value)
{
   if(m_ptree_node) {
      m_ptree_node.get().put_value(value);
      return true;
   }
   return false;
}

bool xml_node::put_value(int value)
{
   if(m_ptree_node) {
      m_ptree_node.get().put_value(value);
      return true;
   }
   return false;
}

bool xml_node::put_value(double value)
{
   if(m_ptree_node) {
      m_ptree_node.get().put_value(value);
      return true;
   }
   return false;
}

string xml_node::get_value(const string& default_value) const
{
   if(m_ptree_node) {
      boost::optional<string> v = m_ptree_node.get().get_value_optional<string>();
      if(v) return v.get();
      return  default_value;
   }
   return  default_value;
}

size_t xml_node::get_value(size_t default_value) const
{
   if(m_ptree_node) {
      boost::optional<size_t> v = m_ptree_node.get().get_value_optional<size_t>();
      if(v) return v.get();
      return  default_value;
   }
   return  default_value;
}

int  xml_node::get_value(int default_value) const
{
   if(m_ptree_node) {
      boost::optional<int> v = m_ptree_node.get().get_value_optional<int>();
      if(v) return v.get();
      return  default_value;
   }
   return  default_value;
}

double xml_node::get_value(double default_value) const
{
   if(m_ptree_node) {
      boost::optional<double> v = m_ptree_node.get().get_value_optional<double>();
      if(v) return v.get();
      return  default_value;
   }
   return  default_value;
}

bool xml_node::has_value() const
{
   if(m_ptree_node) {
      boost::optional<string> v = m_ptree_node.get().get_value_optional<string>(); // anything can be represented as a string
      return (bool)v;
   }
   return false;
}

xml_node xml_node::add_child(const string& tag)
{
   if(m_ptree_node) {
      return xml_node(tag, m_ptree_node.get().add_child(tag,ptree()));
   }
   return xml_node();
}

bool xml_node::get_child(const string& tag, xml_node& child) const
{
   if(m_ptree_node) {
      boost::optional<ptree &> child_node = m_ptree_node.get().get_child_optional(tag);
      if(child_node) {
         child = xml_node(tag, child_node.get());
         return true;
      }
   }
   return  false;
}

bool xml_node::get_property_node(xml_node& pnode)
{
   return get_child("<xmlattr>",pnode);
}

xml_node::iterator xml_node::begin() const
{
   return m_ptree_node.get().begin();
}

xml_node::iterator xml_node::end() const
{
   return m_ptree_node.get().end();
}

// erase the child pointed at by the iterator. "it_child" becomes invalid.
// returns a valid iterator pointing to the element after the erased.
xml_node::iterator xml_node::erase(iterator it_child)
{
   return m_ptree_node.get().erase(it_child);
}

