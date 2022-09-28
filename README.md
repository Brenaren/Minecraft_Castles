# Minecraft_Castles
- Jonathan Graham
- Last revision: Sept. 28th, 2020
- Created for a lab in Jim Plank's COSC 494 course at UTK, [Lab1:Jgraph](http://web.eecs.utk.edu/~jplank/plank/classes/cs494/494/labs/Lab-1-Jgraph/)

## Description

This is a program to generate square grids of Minecraft castle blueprints. It reads in from a .txt file populated with numbers 0 - 5.
The numbers are as follows :

    0 - Empty square of dimentions edge X edge
    1 - Tower: This will place a square tower of the given edge length.
    2 - Vertical Wall: This will place a wall that blocks horizontal movement.
    3 - Horizontal Wall: This will place a wall that blocks vertical movement.
    4 - Vertical Gate: This places a solid vertical wall signifying a gate in the wall.
    5 - Horizontal Gate: This places a solid horizontal wall signifying a gate in the wall.

The program does not generate the input files, but they are very simple to create. The input files are stored in the files directory as castle#.txt.
For instance, files/castle1.txt is :

    131
    402
    131
   
Which (when using an edge length of 6 and 1 color) produces :
![](castle1.jpg)
