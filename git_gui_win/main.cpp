#include <windows.h>
#pragma comment (lib,"shell32.lib")

// this program is a work-around for the problem described at
// http://forums.codeblocks.org/index.php/topic,23266.msg158446.html#msg158446

int main(int argc, char **argv)
{
   ShellExecute(0, "open", "git", "gui", NULL, 0);
   return 0;
}
