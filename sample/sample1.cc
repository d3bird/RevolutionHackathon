#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

void read_file(string filename, int data[]);

int main(){

  string filename;
  int x;
  int data[x];

  cout << "Enter file name to read values: ";
  cin >> filename;
  cout << "Enter array size: ";
  cin >> x;
  read_file(filename, data);
  for (int i = 0; i < x; i++){
    cout << data[i] << " ";
  }

  return 0;
}
void read_file(string filename, int data[]){
  int x = 0;
  ifstream ins;
  ins.open (filename.c_str() );
  while (ins){
    ins >> data[x];
    x++;
  }
  ins.close();
  return;
}
