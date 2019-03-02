#include <iostream>
//#include <curses.h>
#include <ncurses.h>
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



int main(){

 initscr();
 clear;
 noecho();
 cbreak();
 keypad(stdscr, TRUE);
 int h, w;
 getmaxyx(stdscr, h, w);
 int linemark = w/2;
 move(0,0);
 printw("input");
 move(0,linemark+1);
 printw("output");
 for(int i =0 ;i< h;i++){
	move(i, linemark);
	printw("|");
 }



refresh();

bool running = true;
//while(running){



//}


getch();
 endwin();// ends curses mode and 
cout<<"the max length is "<<w<<endl;
cout<<"the max height is "<<h<<endl;
return 0;
}
