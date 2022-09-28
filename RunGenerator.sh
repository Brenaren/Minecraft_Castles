#!/bin/bash

# I used the script made by Samantha Zimmermann as a blueprint to create this script since I am 
# not familiar with scripting languages yet.

# This script will run the makefile and then run the program with the given arguements.
# After it does that it will convert the output to a jpg or pdf.

make

if [ "$#" -lt 2 ]; then
	echo "usage: RunGenerator.sh <edge_length (min 5 max 10)> <colors (min 1 max 7)>"
	exit
fi

for i in 1 2 3 4 5
	./bin/jgraphGenerator /files/castle$i.txt $@ > tmpi.txt
	./jgraph -P tmp$i.txt | ps2pdf - castle$i.pdf
	./jgraph -P tmp$i.txt | ps2pdf - | convert -density 300 - -quality 100 castle$i.jpg
done

