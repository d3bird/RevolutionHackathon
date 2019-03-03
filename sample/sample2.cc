//Includes
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Basic struct
struct consumer
{
  string name;
  int income;
};

//Function prototypes
void load(vector<consumer> &data);
//Loads data from a file into a vector of consumers
void display(const vector<consumer> &data);
//Prints a vector of consumers out to the terminal

//Main
int main()
{
  size_t size = 10;
  vector<consumer> data;
  data.reserve(size);
  load(data);
  cout << "Outputting data:" << endl;
  display(data);
  cout << endl;
  load(data);
  cout << "Outputting data:" << endl;
  display(data);
}

void load(vector<consumer> &data)
{
  data.clear();
  int x = 0;
  string filename;
  std::ifstream ins;
  consumer tmp;
  cout << "Enter filename: ";
  cin >> filename;
  ins.open(filename.c_str());
  if(ins.fail())
  {
    cout << "Something messed up. Send help." << endl;
    return;
  }
  while(ins)
  {
    while(ins.peek() == '\r' || ins.peek() == '\n') ins.ignore();
    getline(ins, tmp.name);
    ins >> tmp.income;
    data.push_back(tmp);
    x++;
  }
  ins.close();
}

void display(const vector<consumer> &data)
{
  if(data.size() == 0)
  {
    cout << endl << "The list is empty. Cannot display." << endl;
    return;
  }
  for(size_t i = 0; i < (data.size() - 1); i++)
  {
    cout << data[i].name << endl << data[i].income << endl;
  }
}
