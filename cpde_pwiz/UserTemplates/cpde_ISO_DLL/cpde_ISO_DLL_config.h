#ifndef %%%PROJECT_NAME_UPPERCASE%%%_CONFIG_H_INCLUDED
#define %%%PROJECT_NAME_UPPERCASE%%%_CONFIG_H_INCLUDED

#ifdef _MSC_VER

   /// MSVC compiler

   #ifdef %%%PROJECT_NAME_UPPERCASE%%%_IMPLEMENTATION
      #define %%%PROJECT_NAME_UPPERCASE%%%_PUBLIC __declspec(dllexport)
      #define %%%PROJECT_NAME_UPPERCASE%%%_EXTERN
   #else
      #define %%%PROJECT_NAME_UPPERCASE%%%_PUBLIC __declspec(dllimport)
      #define %%%PROJECT_NAME_UPPERCASE%%%_EXTERN extern
   #endif
   #define %%%PROJECT_NAME_UPPERCASE%%%_PRIVATE

#elif __GNUC__

   /// gnu gcc

   #define %%%PROJECT_NAME_UPPERCASE%%%_PUBLIC  __attribute__ ((visibility("default")))
   #define %%%PROJECT_NAME_UPPERCASE%%%_PRIVATE __attribute__ ((visibility("hidden")))
   #define %%%PROJECT_NAME_UPPERCASE%%%_EXTERN
	
#else

  #error "Unknown compiler"
	
#endif


#endif // %%%PROJECT_NAME_UPPERCASE%%%_CONFIG_H_INCLUDED

