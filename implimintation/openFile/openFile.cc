#include <unistd.h>
using namespace std;

int main()
{
  execl("./b.out", "/.", (char *)NULL);
}
