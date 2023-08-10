
#include <windows.h>
#include <iostream>
#include <string>

// this program is a work-around for the problem described at
// https://forums.codeblocks.org/index.php/topic,25494.msg173574

// https://stackoverflow.com/questions/1951791/how-to-check-if-a-file-is-already-open-by-another-process-in-c


int main(int argc, char **argv)
{
   if(argc > 1) {

      const char* filename = argv[1];

      std::string filename_tmp = filename;
      filename_tmp += "_tmp";

      for(size_t icount=0; icount<5; icount++) {
         if(MoveFile(filename,filename_tmp.c_str())) {
            MoveFile(filename_tmp.c_str(),filename);
            Sleep(100);
            return 0;
         }
         std::cout << "cpde_wait waiting for : " << filename << std::endl;
         Sleep(100);
      }

   }

   return 1;
}
