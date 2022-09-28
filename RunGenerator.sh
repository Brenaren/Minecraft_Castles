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
do
	./bin/jgraphGenerator ./files/castle$i.txt $@ > tmp$i.txt
	./jgraph -P tmp$i.txt | ps2pdf - ./pdf/castle$i.pdf
	./jgraph -P tmp$i.txt | ps2pdf - | convert -density 300 - -quality 100 ./jpg/castle$i.jpg
	rm tmp$i.txt
done;

