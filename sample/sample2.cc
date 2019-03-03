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
  int decision;
  vector<consumer> data;
  data.reserve(size);
  while(true)
  {
    if(data.size() == 0)
    {
      cout << "\nWARNING: EMPTY LIST. LOAD FROM FILE FIRST.\n";
    }
    cout << "\n1. Load data from a file.\n";
    cout << "2. Display loaded data.\n";
    cout << "3. Calculate average income.\n";
    cout << "4. Search for a consumer by name.\n";
    cout << "5. Display largest income.\n";
    cout << "6. Add a new consumer.\n";
    cout << "7. Remove a consumer.\n";
    cout << "8. Save changes.\n";
    cout << "9. Quit.\n";
    cout << "\n\nEnter command: ";
    cin >> decision;
    if(decision == 1) load(data);
    else if(decision == 2) display(data);
    else if(decision == 9) return 0;
  }
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
    cout << "Something messed up. Send help.\n";
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
    cout << "\nThe list is empty. Cannot display.\n";
    return;
  }
  for(size_t i = 0; i < (data.size() - 1); i++)
  {
    cout << data[i].name << endl << data[i].income << endl;
  }
}
