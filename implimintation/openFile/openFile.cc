#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <mutex>
using namespace std;

int main()
{
  std::mutex test;
  test.lock();
  cout << "This is the parent! Here, meet my child.";
  pid_t pid = vfork();
  if(pid == 0)
  {
    execl("./b.out", "/.", (char *)NULL);
    test.unlock();
  }
  else
  {
    wait(0);
    cout << "Back to the parent!\n";
  }
}
