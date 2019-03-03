#include <iostream>
//#include <curses.h>
#include <ncurses.h>
#include <string>
#include <stack>
#include <vector>
#include <cstring>
//#include "command.h"
#include <cctype>
#include <algorithm>
#include <unistd.h>
//#pragma once

using namespace std;

class command{
public:

command(std::string i){com =i;}
command(){com ="";}
std::string getstring(){return com;}
void setstring(std::string i){com =i;}

vector<int> getcommands(){return comman;}
vector<string> getparms(){return par;}

void setcomands(vector<int> i){comman =i;}
void setpars(vector<string> i){par =i;}

private:
vector<int> comman;
vector<string> par;

std::string com;

};








int createInputside(int xmax, int ymax, vector<command> &coms){
move(0,0);
 printw("custom command list:");
 string str= "asd";
 char* temp2;

for (int i=0;i<ymax && i<coms.size();i++){
 move(i+2,0);
 //cout<<i<<endl;
 str = coms[i].getstring();
  temp2 = new char[str.size()];
  std::strncpy(temp2, str.c_str(), str.size());
  printw(str.c_str()); 

}
return 2;// returns the input
}




int printoutput(int start,int linemerge, vector<string> &lines, vector<string> &his,int ymax, int xmax){
int end = start;
int maxsize = xmax -linemerge;
vector<string> temp;
string temps;
string temps2;
for(int i =0; i <lines.size();i++){
	temps = lines[i];
	if(temps.length()>=maxsize){
	while(temps.length()>=maxsize){
		temps2 = temps.substr(0,maxsize-1);
		temps = temps.substr(maxsize-1);
		lines.push_back(temps2);
	}
	lines.push_back(temps);	
	
	}else{
		temp.push_back(lines[i]);
	}
}
lines = temp;
if(lines.size()+his.size()>ymax){
int diff = lines.size()+his.size()-ymax;
int temp;
	for(int i =0; i < lines.size(); i++){//adding the new lines to the history
		his.push_back(lines[i]);
	}
	for(int i =0 ; i < diff;i++){//removing the old commands
		his.erase(his.begin());
	}

	for(int y =1; y<ymax;y++){
		for(int x=linemerge+1; x<xmax;x++){
		move(y,x);
		echochar(' ');
		}
		move(y,linemerge+1);
		printw(his[y-1].c_str());
		refresh();
	}
//	for(int y =1; y<ymax;y++){// recreating the output
		
		//move(y,temp);
		//printw(his[y-1].c_str());
//	}
}else{

for(int i =0; i <lines.size();i++){
	if(end<xmax){
	move(end,linemerge+1);
        printw(lines[i].c_str());
	refresh();
	end++;
	his.push_back(lines[i]);
	}else{
//	for(int y =0;y<ymax;y++){
	//	for(int x = linemerge+1;x<xmax;x++){
			
	//	}
	}

}
}
return end;
}



std::string exec(const char* cmd) {
    char buffer[128];
    string comstr = string(cmd) + " 2>&1";
    std::string result = "";
   // FILE* pipe = popen(comstr.c_str(), "r");
 FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
            result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

void drawcomands(){
move(0,0);
 printw("custom command list:");

}

void getcolor(vector<int> &comint, vector<string> &comstring,int linemark){
int ch;
	bool colrun = true;
								move(10,0);
								printw("pick a color");
								move(11,0);
								printw("1. red");
								move(12,0);
								printw("2. green");
								move(13,0);
								printw("3. cyan");
								int cpos2 =11;
								move(11,0);
								refresh();
								while(colrun){
									ch = getch();
									switch(ch){
										case KEY_UP:
											if(cpos2==11){
											cpos2 = 13;
											}else{
											cpos2--;
											}	
											move(cpos2,0);	
											break;
											case KEY_DOWN:
											if (cpos2 ==13){
											cpos2 = 11;
											}else{
											cpos2++;
											}
											move(cpos2,0);
											break;
											case 10:
											comint.push_back(2);
											switch(cpos2){
												case 10:
													comstring.push_back("r");
													break;
												case 11:
													comstring.push_back("g");
													break;
												case 12:
													comstring.push_back("c");
													break;
											}
											colrun = false;
											break;
										}
									refresh();
								}
								for(int y =10;y<14;y++){
									for(int x =0; x<linemark;x++){
										move(y,x);
										echochar(' ');
										refresh();
									}
								}

}




void getconsole(vector<int> &comint, vector<string> &comstring,int linemark, vector<char> &inputcommand,int termpoint){
	string temps;
	char tempc;
	int ch;
	int x =0;
		bool conin = true;
								move(10,0);
								printw("input console command with parameters");
								move(11,0);
								printw("click enter when finished");
								inputcommand.resize(0);
								while(conin){
									ch = getch();
								if(ch ==10 && inputcommand.size()>0){
									for(int a = 0 ; a < inputcommand.size();a++){
										temps.push_back(inputcommand[a]);
										move(termpoint, a);
										echochar(' ');
										refresh();
									 }
									conin = false;

								}else if( ch== KEY_BACKSPACE){
									 if(!inputcommand.empty()){
									 inputcommand.pop_back();
									 x--;
									 move(termpoint,x);
									// temps = " ";
									 echochar(' ');
									 refresh();
									 }
								}else{	
									tempc = ch;	
								inputcommand.push_back(tempc);
								move(termpoint,x);
								echochar(ch);
								x++;	
								}
								}
								inputcommand.resize(0);
								comint.push_back(1);
								comstring.push_back(temps);
								for(int y=10; y<13;y++){
									for(int x=0; x< linemark;x++){
										move(y,x);
										echochar(' ');
										refresh();
									}
								}



}


vector<string> runcommand(command run){
	string name = run.getstring();
	vector<int> com = run.getcommands();
	vector<string> parms= run.getparms();
	vector<string> lines;
	//lines.push_back("parms size =");
	//string tempis = to_string( parms.size());
	//lines.push_back(tempis);
	//tempis = to_string(com.size());
	//lines.push_back(tempis);
	bool cred = false;
	bool cgreed = false;
	bool ccyan = false;
	for(int i =0; i <com.size();i++){
		if(com[i]==1){
			//console
				string str = exec(parms[i].c_str());
				string tempss ="";
				for(int i =0 ; i < str.length(); i++){
					if(str[i]== '\n'){
					lines.push_back(tempss);
					tempss="";
					}else{
					tempss.push_back(str[i]);
					}
				}
				lines.push_back(tempss);
				if(cred||cgreed||ccyan){
				lines.push_back(":cend:");
				cred = false;
				cgreed = false;
				ccyan = false;
				}
		}else if(com[i]==2){//change color
				if(std::stoi( parms[i])==1){
						cred = true;
						lines.push_back(":red:");
				}else if(std::stoi( parms[i])==2){
 
						
						lines.push_back(":green:");
						cgreed =true;
				}else{
						
						lines.push_back(":cycan:");
						ccyan = true;
				}
		}else{

			if(cred||cgreed||ccyan){
				lines.push_back(":cend:");
				cred = false;
				cgreed = false;
				ccyan = false;
			}
 		}
	}
	return lines;
}

int main(){

 vector<command> commands;
 vector<string> outputhis;
 vector<string> inputhis;
 command temp("create command");
 commands.push_back(temp);
 
 initscr();
 start_color();
 clear;
 noecho();
 cbreak();
 keypad(stdscr, TRUE);
 int h, w;
 getmaxyx(stdscr, h, w);
 int linemark = w/2;
 //move(0,0);
 //printw("custom command list:");
 move(0,linemark+1);
 printw("output");
 for(int i =0 ;i< h;i++){
	move(i, linemark);
	printw("|");
 }
int termpoint =h-3;
move(termpoint, 0);
printw("termanal input:");
termpoint++;

move(termpoint-7,0);
int comh= termpoint -7;
int comhpos = comh+1;
printw("command history:");

move(2,0);
int endpos = createInputside(linemark, h,  commands);
refresh();

bool running = true;
int lastpos =1+commands.size();
int ch;
int xc =0;
int yc=2;
int menupos =0;
int outputpos =1;
vector<char> inputcommand;
vector<string> lines;
int compos =0;
char tempc;
string temps;
while (running){
 ch = getch();
 switch(ch){
	case KEY_UP:
		if(menupos==0){
			yc= lastpos;
			menupos = commands.size()-1;
			move(yc,xc);
		}else{
			yc--;
			menupos--;
			move(yc,xc);
		}



		break;
	 case KEY_DOWN:
		if(menupos == commands.size()-1){
			menupos = 0;
			yc =2;
			move(yc,xc);
		}else{
			menupos++;
			yc++;
			move(yc,xc);
		}
		 break;
	 case KEY_RIGHT:
		 if(compos<inputcommand.size()){
			 compos++;
			 move(termpoint,compos);
			} 		
		 break;
	 case KEY_LEFT:
	  	if(compos >0){
			compos--;
			 move(termpoint,compos);
		}
		 break;
	 case 10:// if the enter key is pressed
	//	string str(inputcommand.begin(),inputcommand.end());
	//	printw("enter was clicked");
		 temps ="";
		 if(!inputcommand.empty()){// if there is a consol cmand
		 move(termpoint,compos);
		 for(int a = 0 ; a < inputcommand.size();a++){
			temps.push_back(inputcommand[a]);
			move(termpoint, a);
			
			 echochar(' ');
		 }
		// inputhis.push_back(temps); 
	  	
		string str = exec(temps.c_str());
	//	if(str.length()==0){}
		string tempss ="";
		for(int i =0 ; i < str.length(); i++){
			if(str[i]== '\n'){
				lines.push_back(tempss);
				tempss="";
			}else{
			tempss.push_back(str[i]);
			}
		}
		
	//	lines.push_back(str);	
		outputpos= printoutput(outputpos ,linemark,lines,outputhis,h,w);
		lines.resize(0);
		inputcommand.resize(0);
		compos =0;
		
		inputhis.push_back(temps);
		int index = inputhis.size()-1;
		for(int i = termpoint-2;i>comhpos-1;i--){
			for(int x =0; x<linemark;x++){
				move(i,x);
				
				 echochar(' ');
			}
			move(i,0);
			printw(inputhis[index].c_str());
			index--;
			if(index<0){
				break;
			}
		}
		

		 }else{//run the menu command
			if(menupos ==0){// creating a custom function
				inputcommand.resize(0);
				for(int y =0; y<h/2;y++){
					for(int x =0;x<linemark;x++){
						move(y,x);
						echochar(' ');
					}
				}
				move(0,linemark/2);
				printw("welcome to create you own function");
				move(1,linemark/2);
				printw("please input the name");
				while(true){
				ch = getch();
				if(ch ==10 && inputcommand.size()>0){
					for(int a = 0 ; a < inputcommand.size();a++){
						temps.push_back(inputcommand[a]);
						move(termpoint, a);
						echochar(' ');
					 }
					break;
				}else{	
					tempc = ch;
					move(termpoint,compos);
					compos++;
					echochar(tempc);	
					inputcommand.push_back(tempc);	
				}
				}
				command newc(temps);
				vector<int> comint;
				vector<string>comstring;
				int pos =5;
				move(3,0);
				printw("nav the menu using the arrow keys and enter");
				move(4,0);
				printw("pick the commands in the order you want them to exicute");
				move(5,0);
				printw("1. add a console command");
				move(6,0);
				printw("2. change the color of the output");
				move(7,0);
				printw("3. compare data from two programs");
				move(8,0);
				printw("4. save and exit");
				move(9,0);
				printw("5. exit without saving");
				bool creating = true;
				while(creating){
					ch = getch();
					switch(ch){
					case KEY_UP:
						if(pos==5){
						pos = 9;
						}else{
						pos--;
						}
						move(pos,0);	
						break;
					case KEY_DOWN:
						if (pos ==9){
						pos = 5;
						}else{
						pos++;
						}
						move(pos,0);
						break;
					case 10:
						switch(pos){
							case 8:// save and exit
								creating = false;
								newc.setcomands(comint);
								newc.setpars(comstring );





								commands.push_back(newc);
								break;
							case 9://exit without saving
								creating = false;	
								break;
							case 5://add a consoleomand
								getconsole(comint,comstring, linemark,inputcommand, termpoint);
								break;						
							case 7: //compar data
								break;


							case 6://change the color
								getcolor( comint,  comstring, linemark);	
								break;
						}
					break;	

					}


				}
					
				

				for(int y=0; y<comhpos;y++){//flush out the function creator
					for(int x =0; x<linemark;x++){
						move(y,x);
						echochar(' ');
					}
				}
			createInputside(linemark, h,  commands);
			}else{// run the custom function
				lines.push_back("start of running command");
			lines =	runcommand(commands[menupos]);
			lines.push_back("end of running command");
			outputpos= printoutput(outputpos ,linemark,lines,outputhis,h,w);					
			}

		 }
		 break;
               	 case KEY_BACKSPACE:
		 if(!inputcommand.empty()){
		 inputcommand.pop_back();
		 compos--;
		 move(termpoint,compos);
		 temps = " ";
		 echochar(' ');
		// compos--;
		 }
		 break;

 default:
       tempc = ch;
move(termpoint,compos);
compos++;

echochar(ch);
move(yc,xc);//moving back to the menue
inputcommand.push_back(tempc);

	 break;
 }


refresh();

}


//getch();
 endwin();// ends curses mode and
//cout<< exec("ls")<<endl;
//cin.get();
 return 0;
 }
