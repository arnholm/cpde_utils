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
     // r = DeclareConstructor(engine,as_typeid<as_template>(),"as_template@ as_template()",asFUNCTION(as_template::ctor_default)); as_assert( r >= 0 );
   }

   // Register scripting member functions, the template parameter signifies the scripting type
   template <class T>
   static void DeclareMethods(asIScriptEngine* engine)
   {
      // inherit methods: replace "base_class" with actual C++ base class
      base_class::DeclareMethods<T>(engine);

      // local methods
      int r = 0;
      // r = DeclareMethod(engine,as_typeid<as_template>(),"double x() const", asMETHOD(as_template,x)); as_assert( r >= 0 );

   }

private:
};

#endif
