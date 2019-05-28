#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include <wx/defs.h>
#include <wx/platinfo.h>  // platform info
#include <wx/app.h>

#include <wx/string.h>   // wxString
#include <wx/filefn.h>   // File Functions
#include <wx/filename.h> // wxFile
#include <wx/cmdline.h>  // command line parser

#include <list>
#include <map>
#include <algorithm>
using namespace std;
typedef map<wxString,wxString> CmdLineMap;    // CmdLineMap


/*
   switch 	  This is a boolean option which can be given or not, but which doesn't have any value.
              We use the word switch to distinguish such boolean options from more generic options
              like those described below. For example, -v might be a switch meaning "enable verbose mode".

   option 	  Option for us here is something which comes with a value unlike a switch.
              For example, -o:filename might be an option which allows to specify the name of the output file.

   parameter  This is a required program argument.

   More info at: http://docs.wxwidgets.org/2.8/wx_wxcmdlineparser.html#wxcmdlineparser

*/

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
   //   kind               shortName      longName         description                          parameterType          flag(s)
  { wxCMD_LINE_PARAM,     "class_name",   "class_name",          "<class_name>",  wxCMD_LINE_VAL_STRING,  wxCMD_LINE_OPTION_MANDATORY },
  { wxCMD_LINE_OPTION,    "template",       "template", "<template_class_name>",  wxCMD_LINE_VAL_STRING,    wxCMD_LINE_PARAM_OPTIONAL },
  { wxCMD_LINE_NONE,             "",                "",                      "",    wxCMD_LINE_VAL_NONE,    wxCMD_LINE_PARAM_OPTIONAL }
};

// sample command line params: --project=cpde_export  --target=W32_Debug --tdir=w32\bin\Debug\

void ParserToMap(wxCmdLineParser& parser, CmdLineMap& cmdMap)
{
   size_t pcount = sizeof(cmdLineDesc)/sizeof(wxCmdLineEntryDesc) - 1;
   size_t iparam=0;
   for(size_t i=0; i<pcount; i++) {
      wxString pname = cmdLineDesc[i].longName;
      if(cmdLineDesc[i].kind == wxCMD_LINE_PARAM) {
         if(iparam < parser.GetParamCount()) {
            cmdMap.insert(make_pair(pname,parser.GetParam(iparam++)));
         }
      }
      else {
         // switch or option, must check if present
         if(parser.Found(pname)) {
            wxString pvalue;
            if(cmdLineDesc[i].type == wxCMD_LINE_VAL_STRING) {
               parser.Found(pname,&pvalue);
            }
            else if(cmdLineDesc[i].type == wxCMD_LINE_VAL_NUMBER) {
               long lvalue=0;
               parser.Found(pname,&lvalue);
               pvalue.Printf(wxT("%i"),lvalue);
            }
            cmdMap.insert(make_pair(pname,pvalue));
         }
      }
   }
}


void replace_substring(std::string& line, const std::string& oldString, const std::string& newString)
{
   const size_t oldSize = oldString.length();

   // do nothing if line is shorter than the string to find
   if( oldSize > line.length() ) return;

   const size_t newSize = newString.length();
   for( size_t pos = 0; ; pos += newSize ) {

      // Locate the substring to replace
      pos = line.find( oldString, pos );
      if( pos == std::string::npos ) return;

      if( oldSize == newSize ) {
         // if they're same size, use std::string::replace
         line.replace( pos, oldSize, newString );
      }
      else {
         // if not same size, replace by erasing and inserting
         line.erase( pos, oldSize );
         line.insert( pos, newString );
      }
   }
}

std::string replace_substring_copy(const std::string& line, const std::string& oldString, const std::string& newString)
{
   std::string line_copy(line);
   replace_substring(line_copy,oldString,newString);
   return std::move(line_copy);
}


void replace_substring_in_file(const std::string& file_path, const std::string& oldString, const std::string& newString)
{
   // perform in-place replacement

   // first read the file and store in list
   std::list<std::string> lines;
   {
      std::ifstream in(file_path);
      if(in.is_open()) {
         std::string line;
         while(std::getline(in,line)) {
            lines.push_back(replace_substring_copy(line,oldString,newString));
         }
      }
      else {
         throw std::runtime_error("File could not be opened for read: " + file_path);
      }
   }

   // write to same file
   {
      std::ofstream out(file_path);
      if(out.is_open()) {
         for(auto& line : lines) {
            out << line << std::endl;
         }
      }
      else {
         throw std::runtime_error("File could not be opened for write: " + file_path);
      }
   }
}


int main(int argc, char **argv)
{
   // initialise wxWidgets library
   wxInitializer initializer(argc,argv);

   // parse command line
   wxCmdLineParser parser(cmdLineDesc);
   parser.DisableLongOptions();
   parser.SetSwitchChars(wxT("-"));
   parser.SetCmdLine(argc,argv);
   if(parser.Parse() != 0) {
      // command line parameter error
      return 1;
   }

   try {
      // parser success
      // convert parameters to map
      CmdLineMap cmdMap;
      ParserToMap(parser,cmdMap);

      string class_name = cmdMap["class_name"].ToStdString();

      string template_name = "template";
      bool has_template = cmdMap.find("template")  != cmdMap.end();
      if(has_template) {
         template_name = cmdMap["template"].ToStdString();
      }
      list<wxFileName> t_files = {wxFileName(template_name+".h"),wxFileName(template_name+".cpp")};
      for(auto& t_file : t_files) {
         if(!t_file.Exists()) throw std::logic_error( t_file.GetFullPath().ToStdString() + " does not exist");
      }


      for(auto& t_file : t_files) {
         wxString ext           = t_file.GetExt();
         string template_class  = t_file.GetName().ToStdString();
         wxFileName class_file("",class_name,ext);
         wxCopyFile(t_file.GetFullPath(),class_file.GetFullPath());

         // replace the class name
         string file_path = class_file.GetFullPath().ToStdString();
         replace_substring_in_file(file_path,template_class,class_name);

         // replace the include guard
         string old_guard = template_class+"_h";
         string new_guard = class_name+"_h";
         std::transform(old_guard.begin(),old_guard.end(),old_guard.begin(),::toupper);
         std::transform(new_guard.begin(),new_guard.end(),new_guard.begin(),::toupper);
         replace_substring_in_file(file_path,old_guard,new_guard);

         cout << "   " << std::setw(10) << std::left << t_file.GetFullPath().ToStdString()  << "  ==>  "  << file_path << endl;
      }
   }
   catch(std::exception& ex) {
      cout << " Error: " << ex.what() << endl;
   }

   return 0;
}


