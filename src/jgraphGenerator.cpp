#include <stdio.h>
#include <cstdio>
#include <vector>
#include <fstream>

using namespace std;

/* This takes the lower left corner coordinates and generates a tower of the given color. */
void generate_tower (int x, int y, int edge, string color) {
  
  /* This generates the upper and lower borders of the tower. */	
  for (int i = 0; i < edge; i++) {
	if (i == 0 || i == edge - 1) {
      for (int j = 0; j < edge; j++) {
	    printf("newline poly pfill color %s pts %d %d  %d %d  %d %d  %d %d\n", 
		  color.c_str(), x + j, y + i, x + j + 1, y + i, x + j + 1, y + i + 1, x + j, y + i + 1);
	  }
	}
  }

  /* This does the same thing for the vertical borders. */
  for (int i = 0; i < edge; i++) {
    for (int j = 0; j < edge; j++) {
	  if (j == 0 || j == edge - 1) {
		printf("newline poly pfill color %s pts %d %d  %d %d  %d %d  %d %d\n", 
		  color.c_str(), x + j, y + i, x + j + 1, y + i, x + j + 1, y + i + 1, x + j, y + i + 1);
	  }
	}
  }
}

/* 
 * This takes the lower left corner of a wall block and generates a vertical 
 * wall of the given color. 
 */
void generate_vert_wall (int x, int y, int edge, string color) {
 
  int left, right;

  /* 
   * Here we figure out where to place the walls to have a walkway of width 3 for odd
   * edge lengths and 2 for even lengths.
   */
  if (edge % 2 == 1) {
    left  = (edge / 2) - 2;
    right = (edge / 2) + 2;
  } else {
    left  = (edge / 2) - 2;
	right = (edge / 2) + 1;
  }

  /* This generates two vertical lines to replicate a wall. */
  for (int i = 0; i < edge; i++) {
    for (int j = 0; j < edge; j++) {
      if (j == left || j == right) {
		printf("newline poly pfill color %s pts %d %d  %d %d  %d %d  %d %d\n", 
		  color.c_str(), x + j, y + i, x + j + 1, y + i, x + j + 1, y + i + 1, x + j, y + i + 1);
	  }
	}
  }
}

/* 
 * This takes the lower left corner of a wall block and generates a horizontal 
 * wall of the given color. 
 */
void generate_horz_wall (int x, int y, int edge, string color) {
  
  int lower, upper;

  /* 
   * Here we figure out where to place the walls to have a walkway of width 3 for odd
   * edge lengths and 2 for even lengths.
   */
  if (edge % 2 == 1) {
    lower = (edge / 2) - 2;
    upper = (edge / 2) + 2;
  } else {
    lower = (edge / 2) - 2;
    upper = (edge / 2) + 1;
  }

  /* This generates two horizontal lines to replicate a wall. */
  for (int i = 0; i < edge; i++) {
    if (i == lower || i == upper) {
      for (int j = 0; j < edge; j++) {
	    printf("newline poly pfill color %s pts %d %d  %d %d  %d %d  %d %d\n", 
		  color.c_str(), x + j, y + i, x + j + 1, y + i, x + j + 1, y + i + 1, x + j, y + i + 1);
	  }
	}
  }
}

/* 
 * This takes the lower left corner of a wall block and generates a horizontal 
 * wall of the given color with a solid black wall to represent a gate.. 
 */
void generate_gate (int x, int y, int edge, int orientation) {
  int wall1, wall2;

  /* 
   * Here we figure out where to place the walls to have a walkway of width 3 for odd
   * edge lengths and 2 for even lengths.
   */
  if (edge % 2 == 1) {
    wall1 = (edge / 2) - 2;
    wall2 = (edge / 2) + 2;
  } else {
    wall1 = (edge / 2) - 2;
    wall2 = (edge / 2) + 1;
  }

  /* An orientation of 1 signifies a vertical wall and a 0 is a horizontal wall. */
  if (orientation) {
  
	/* Here is the vertical gate generation. */
	for (int i = 0; i < edge; i++) {
      for (int j = 0; j < edge; j++) {
        if (j >= wall1 && j <= wall2) {
		  printf("newline poly pfill color %s pts %d %d  %d %d  %d %d  %d %d\n", 
		    "0 0 0", x + j, y + i, x + j + 1, y + i, x + j + 1, y + i + 1, x + j, y + i + 1);
	    }
	  }
    }
    
  } else {

	/* Here is the horizontal gate generation. */
    for (int i = 0; i < edge; i++) {
      if (i >= wall1 && i <= wall2) {
        for (int j = 0; j < edge; j++) {
	      printf("newline poly pfill color %s pts %d %d  %d %d  %d %d  %d %d\n", 
		    "0 0 0", x + j, y + i, x + j + 1, y + i, x + j + 1, y + i + 1, x + j, y + i + 1);
	    }
	  }
    }
  }
}

/* 
 * This function creates gridlines for the grid. This is necessary because at 
 * larger scale the unit gridmarks go away by default. 
 */
void generate_grid_lines (int size) {
  
  /* Generate the horizontal grid lines. */
  for (int i = 0; i <= size; i++) {
    printf("newline color 0 linethickness 1 pts %d %d  %d %d\n", 0, i, size, i);  
  }

  /* Generate the horizontal grid lines. */
  for (int i = 0; i <= size; i++) {
    printf("newline color 0 linethickness 1 pts %d %d  %d %d\n", i, 0, i, size);  
  }
}

/* This will create the jgraph input for the castle. */
void generate_castle(vector <vector <int> > BP, int edge, int num_colors) {
  
  int k; 
  int size;

  if (BP[0].size() > BP.size()) {
	  size = BP[0].size();
  } else {
	  size = BP.size();
  }

  /* I set a vector of the color strings to allow for coloring the graph. */
  vector <string> colors;
  colors.resize(7);
  colors = {"0 0 0", "1 0 0", "0 1 0", "0 0 1", "1 1 0", "1 0 1", "0 1 1"};

  /* First I print the newgraph command. */
  printf("newgraph\n  xaxis min %d max %d\n    grid_lines mgrid_lines\n"
		             "yaxis min %d max %d\n    grid_lines mgrid_lines\n",
					  0, edge * size, 0, edge * size);

  /* We want to generate this from the bottom left to the top right. */
  for (int i = BP.size() - 1; i > -1; i--) {
	  k = i; //This will allow for more than black to be in the first column.
    for (int j = 0; j < BP[i].size(); j++) {
      switch (BP[i][j]) {
        case 1: //Tower
	      generate_tower(j * edge, (BP.size() - 1 - i) * edge, edge, colors[k % num_colors]);
	      k++;
	      break;
	    case 2: //Vertical wall
	      generate_vert_wall(j * edge, (BP.size() - 1 - i) * edge, edge, colors[k % num_colors]);
	      k++;
	      break;
	    case 3: //Horizontal wall
	      generate_horz_wall(j * edge, (BP.size() - 1 - i) * edge, edge, colors[k % num_colors]);
	      k++;
	      break;
		case 4: //Vertical gate
		  generate_gate(j * edge, (BP.size() - 1 - i) * edge, edge, 1);
		  break;
		case 5: //Horizontal gate
		  generate_gate(j * edge, (BP.size() - 1 - i) * edge, edge, 0);
		  break;
		case 0:
		  //We do nothing here.
		  break;
	    default:
	      printf("Error in input file, %d must be only 0 1 2 3 4 or 5.\n", BP[i][j]);
	      exit(1);
	  }
	}
  }
  
  /* Generate the grid lines. */
  generate_grid_lines(edge * size);
}

int main (int argc, char **argv) {
  int num_towers, edge, num_colors, size, max_size, iter, colors;
  string fin, in_string;
  vector<vector <int> > blueprint;
  ifstream input; 

  if (argc != 4) {
	printf("Usage: jgraphGenerator inputFile edgeLength #ofColors\n");
	exit(1);
  }

  /* Set program arguements. */
  fin  = argv[1];
  edge = stoi(argv[2]);
  colors = stoi(argv[3]); 
  
  /* If colors is greater than 7 it will cycle through all colors. */
  if (colors > 7) colors = 7;
  /* We have to set the min of colors to 1 so we dfon't divide by 0 when deciding colors. */
  if (colors < 1) colors = 1;

  /* 
   * To avoid absurdly large outputs we limit edge length and our walls need at
   * least an edge of size 5.
   */
  if (edge > 10) edge = 10;
  if (edge < 5 ) edge = 5;
  
  input.open(fin);
  if (!(input.is_open())) {
    fprintf(stderr, "File failed to open\n");
	exit(1);
  }

  iter = 0;
  max_size = 0;

  /* Here we set our blueprint to the input files blueprint. */
  while (input.peek() != EOF) {
	getline(input, in_string);
	/* Add a row to the blueprint and set the row size to the size of the string. */
	blueprint.resize(blueprint.size() + 1);
	blueprint[iter].resize(in_string.size(), 0);

	/* This max_size will be used to resize rows at the end in the case of 
	 * some rows being shorter than others. */
	if (in_string.size() > max_size) max_size = in_string.size();

	/* Parse the string into ints and store into the blueprint. */
    for (int i = 0; i < in_string.size(); i++) {
      blueprint[iter][i] = (int)(in_string[i] - '0');
	}

	iter++;
  }

  /* 
   * Here I set the size of all our blueprint entries to the same length and set 
   * any added ints to 0. 
   */
  for (int i = 0; i < blueprint.size(); i++) {
    blueprint[i].resize(max_size, 0);
  }

  /* Now we call the generation function which prints out the jgraph commands to stdout. */
  generate_castle(blueprint, edge, colors);
  
  input.close();

  return 0;
}
