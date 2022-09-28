all:
	gcc -o ./bin/jgraphGenerator ./src/jgraphGenerator.cpp -lstdc++

clean :	
	rm ./bin/* *.jpg *.txt


