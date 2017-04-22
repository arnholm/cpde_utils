#ifndef %%%PROJECT_NAME_UPPERCASE%%%_CONFIG_H_INCLUDED
#define %%%PROJECT_NAME_UPPERCASE%%%_CONFIG_H_INCLUDED

#ifdef _MSC_VER

   /// MSVC compiler

   #ifdef %%%PROJECT_NAME_UPPERCASE%%%_IMPLEMENTATION
      #define %%%PROJECT_NAME_UPPERCASE%%%_PUBLIC  
      #define %%%PROJECT_NAME_UPPERCASE%%%_EXTERN
   #else
      #define %%%PROJECT_NAME_UPPERCASE%%%_PUBLIC 
      #define %%%PROJECT_NAME_UPPERCASE%%%_EXTERN 
   #endif
   #define %%%PROJECT_NAME_UPPERCASE%%%_PRIVATE

#elif __GNUC__

   /// gnu gcc

   #define %%%PROJECT_NAME_UPPERCASE%%%_PUBLIC   
   #define %%%PROJECT_NAME_UPPERCASE%%%_PRIVATE 
   #define %%%PROJECT_NAME_UPPERCASE%%%_EXTERN
	  
#else

  #error "Unknown compiler"

#endif // %%%PROJECT_NAME_UPPERCASE%%%_CONFIG_H_INCLUDED

