#!/bin/bash

# I used the script made by Samantha Zimmermann as a blueprint to create this script since I am 
# not familiar with scripting languages yet.

# This script will run the makefile and then run the program with the given arguements.
# After it does that it will convert the output to a jpg or pdf.

make

if [ "$#" -lt 4 ]; then
	echo "usage: RunGenerator.sh <input_file> <output_file> <edge_length (min 5 max 10)> <colors (min 1 max 7)>"
	exit
fi

INFILE=$1
OUTFILE=$2
TYPE=${OUTFILE##*.}

shift 2

echo "./bin/jgraphGenerator $INFILE $@ > tmp.txt"
./bin/jgraphGenerator $INFILE $@ > tmp.txt

if [ $TYPE == "pdf" ]; then
	./jgraph -P tmp.txt | ps2pdf - $OUTFILE
else
	./jgraph -P tmp.txt | ps2pdf - | convert -density 300 - -quality 100 $OUTFILE
fi;

