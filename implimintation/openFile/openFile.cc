#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
  cout << "This is the parent! Here, meet my child.";
  pid_t pid = fork();
  if(pid == 0)
  {
    execl("./b.out", "/home/bain/Hackathon/RevolutionHackathon/implimintation/testFile", (char *)NULL);
  }
  else
  {
    sleep(1);
    cout << "Back to the parent!\n";
  }
}
