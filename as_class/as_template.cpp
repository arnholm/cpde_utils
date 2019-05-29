#include "as_template.h"

// #include <fstream>
// #include <iostream>

using namespace std;

void as_template::InstallType(asIScriptEngine* engine)
{
   // below declaration is called before installing this type
   DeclareTypeEx("as_template",engine,"Fix this description in as_template.cpp");

   // declate constructors
   as_template::DeclareConstructors(engine);

   // Declare the as_template methods
   as_template::DeclareMethods<as_template>(engine);
}

as_template::as_template()
: as_reftype(as_typeid<as_template>())
{}

as_template::~as_template()
{}

as_reftype* as_template::clone_scoped()
{
   return new as_template(*this);
}

