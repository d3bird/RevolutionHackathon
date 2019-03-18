# RevolutionHackathon

This was our project for the Revolution Hackathon host by UC.
The main program is located in the GUI folder, just run make and the program will compile and run.

# The problem

When we logged on to a linux computer through ssh, we get a command line. Most of the time this is what we want; however, sorting through output for the one bit of information you need from a long list can be time consuming. If we had a GUI then picking out key information would be much faster. We decided write a program to to deal with this problem. 

# our solution
Our program uses the curses library to redraw the command line and recive input from the keyboard. This allows us to create a GUI in the command line. Our GUI allows the creation of scripts that can run terminal commands and color the outputs of these commands. When the scrpts are run the output is put on the right side of the screen, depending on how the scripts are setup, different sections of the output will bein different colors making it really easy to find the output that you are looking for.

# background/disclaimer 
This code was written over the course of 24 hours, there are several bugs that I did not solve in time, there are some features that mentioned in the script creation that were not fully implemented. At somepoint I do plan to come back to this and fix these bugs, as well as cleaning up the code/GUI.
