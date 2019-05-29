#ifndef AS_TEMPLATE_H
#define AS_TEMPLATE_H

#include "ce_angelscript_ex/as_reftype.h"

// angelscript scripting class 
class as_template : public as_reftype {
public:
   // constructor
   as_template();
   virtual ~as_template();

   // InstallType registers this class in the scripting engine
   static void InstallType(asIScriptEngine* engine);

   // required by as_reftype
   as_reftype* clone_scoped();

protected:
   static as_template* ctor_default() { return new as_template(); }

public:
   // ==== SCRIPTING INTERFACE

   // Register scripting constructors
   static void DeclareConstructors(asIScriptEngine* engine)
   {
      int r = 0;
      r = DeclareConstructor(engine,"as_template","as_template@ as_template()",asFUNCTION(as_template::ctor_default)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods
      as_reftype::DeclareMethods<as_reftype>(engine);
      as_reftype::DeclareMethods<T>(engine);

      // local methods
      int r = 0;
      // r = DeclareMethod(engine,type_name,"double x() const", asMETHOD(as_template,x)); as_assert( r >= 0 );

   }

private:
};

#endif
