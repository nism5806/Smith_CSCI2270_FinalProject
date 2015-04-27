# Smith_CSCI2270_FinalProject
final project

Project Summary:
My project is similar to the Zombie Cities assignment with another search algorithm
and a game where the user traverses through the graph themselves. When the program is 
run, the user is prompted for an integer difficulty. A random graph is generated with that number
of vertices. The user is given a random location and a random destination that is farther than
one edge away is chosen. The current location along with all adjacent locations and the distances to them
are displayed. The user inputs a name of an adjacent location and they are moved there if it is valid.
This process repeats until the destination is reached. Then the same start and destination
are inputted into various search algorithms and their paths are displayed.

How to Run:
Right click the folder the files are located in and click "Open Terminal Here"
type ./Pathgame.exe and the game will run

Dependencies:
None

System Requirements:
Runs on Ubuntu operating system

Group Members:
Nick Smith

Contributors:
None

Open issues/bugs:
Functions properly but could be improved...
-graph generating algorithm could probably be improved although I was amazed 
I could get it to function as well as it does.
-couldn't figure out how to apply any other search algorithms to the same problem
-difference between Dijkstra's and Astar not really evident without looking at code



