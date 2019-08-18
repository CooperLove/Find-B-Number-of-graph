/*
 * Reader.cpp
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#include "Reader.h"



Reader::Reader(){}

Reader::~Reader(){}

Graph* Reader::read(FILE* dimacs){
	//TODO
	int n1 = 0, n2 = 0, N, E;
	char end = 'a';

	fscanf(dimacs, "%d %d", &N, &E);
	printf ("Grafo com %d vertices e %d arestas!\n", N, E);
	Graph* g = new Graph(N);
	g->SetN (N);
	g->SetM (E);
	g->AllocNeigh ();
	fscanf(dimacs, "%c %d %d\n", &end, &n1, &n2);
		printf ("First: %c %d %d\n",end,n1,n2);
	while(fscanf(dimacs, "%c %d %d\n", &end, &n1, &n2) != EOF){
		printf ("While: %c %d %d\n",end,n1,n2);
		g->getNeig (n1 -1)->vertices[n2 - 1] = 1;
    }
	printf ("Grafo OKAY!\n");
	return g;
}


