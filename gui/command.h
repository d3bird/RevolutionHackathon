#pragma once
#include <string>



class command{
public:

command(std::string i){com =i;}
command(){com ="";}
std::string getstring(){return com;}
void setstring(std::string i){com =i;}
private:

std::string com;

};
