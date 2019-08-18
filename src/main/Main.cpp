/*
 * main.cpp
 *
 *  Created on: 17 de ago de 2019
 *      Author: marcio
 */

#include "../tools/Graph.h"
#include "../tools/Set.h"
#include "../tools/Timer.h"
#include "Reader.h"
#include <cstdio>


int main(int argc, char **argv){

	//input file
	FILE* fin = fopen (argv[1], "r");
	//output file
	FILE* fout = fopen(argv[2], "a");

	//the reader for the graph
	Reader myReader;

	//the graph
	Graph* h;
	Graph* g = myReader.read(fin);

	g->print();

	printf("OK!\n");

	return 0;
}

