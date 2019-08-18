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
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv){

	//input file
	FILE* fin = fopen (argv[1], "r");
	if (fin == NULL){
		printf ("O arquivo fin nao pode ser aberto!");
		return -1;
	}

	//output file
	FILE* fout = fopen(argv[2], "a");
	if (fout == NULL){
		printf ("O arquivo fout nao pode ser aberto!");
		return -1;
	}
	//the reader for the graph
	Reader myReader;

	//the graph
	Graph* h;
	Graph* g = myReader.read(fin);

	// Set* s = new Set(10);
	// s->print();
	// s->removeAll();
	// s->print();
	g->print();

	printf("OKAY!\n");

	return 0;
}


