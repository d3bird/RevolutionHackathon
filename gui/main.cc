#include <iostream>
//#include <curses.h>
#include <ncurses.h>
#include <string>
#include <stack>
#include <vector>
#include <cstring>
#include "command.h"
#include <cctype>
#include <algorithm>
using namespace std;


void example(){
 bool running = true;
 int ch;

while(running){
	ch = getch();
	if(ch==KEY_EIC){
		printw("F1 Key pressed");
		running = false;
	}else{	
		printw("The pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
printw("\n");

	}

 refresh();
// getch();
// endwin();
}


}



int createInputside(int xmax, int ymax, vector<command> &coms){
 string str= "asd";
 char* temp2;

for (int i=0;i<ymax && i<coms.size();i++){
 move(i+2,0);
 cout<<i<<endl;
 str = coms[i].getstring();
  temp2 = new char[str.size()];
  std::strncpy(temp2, str.c_str(), str.size());
  printw(str.c_str()); 

}
return 2;// returns the input
}




int printoutput(int start,int linemerge, vector<string> &lines, vector<string> &his,int ymax, int xmax){
int end = start;

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

int main(){
 vector<command> commands;
 vector<string> outputhis;
 vector<string> inputhis;
 command temp("create command");
 commands.push_back(temp);
 temp.setstring("command 2");
 commands.push_back(temp);
 temp.setstring("command 3");
 commands.push_back(temp);
 temp.setstring("command 4");
 commands.push_back(temp);
 temp.setstring("command 5");
 commands.push_back(temp);
 temp.setstring("command 6");
 commands.push_back(temp);
 temp.setstring("command 7");
 commands.push_back(temp);
 temp.setstring("command 8");
commands.push_back(temp);
 
 initscr();
 clear;
 noecho();
 cbreak();
 keypad(stdscr, TRUE);
 int h, w;
 getmaxyx(stdscr, h, w);
 int linemark = w/2;
 move(0,0);
//attron(A_BOLD);
 printw("custom command list:");
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
		lines.push_back(temps);	
		outputpos= printoutput(outputpos ,linemark,lines,outputhis,h,w);
		lines.resize(0);
		inputcommand.resize(0);
		compos =0;
		
		 }else{//run the menu command


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
//temps = to_string(((char)ch));
//temps = to_string(tempc);
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
 return 0;
 }
