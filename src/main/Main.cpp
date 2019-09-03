/*
 * main.cpp
 *
 *  Created on: 17 de ago de 2019
 *      Author: marcio
 */

#include "../tools/Graph.h"
#include "../tools/Set.h"
#include "../tools/Timer.h"
#include "../solver/Enumeration.h"
#include "../solver/TreeNode.h"
#include "../solver/VertexOrder.h"
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
	VertexOrder* order = new VertexOrder (g);

	g->print();
	char* v = order->degreeMax();
	char* v2 = v;
	Colorable* c = new Colorable();
	c->SetG(g);
	Enumeration* en = new Enumeration(g, v2, c);
	printf ("Begin enumeration!\n");
	en->buildRoot();
	en->fullEnum();
	printf ("End enumeration!\n");

	printf ("Max degree\n\t");
	for (int i = 0; i < g->GetN(); i++)
		printf ("%d ",v[i]);
	printf("\n");

	printf ("Min degree\n\t");
	v = order->degreeMin();
	for (int i = 0; i < g->GetN(); i++)
		printf ("%d ",v[i]);
	printf("\n");

	printf("OKAY!\n");

	fclose(fin);
	fclose(fout);

	return 0;
}


/*
char* arq2 = "log.txt";
	char *arq3 = "arq3.txt";
	char *arq4 = "arq4.lp";
	c->carregarVariaveis();
	//inicializando cplex...
	c->startCplex(arq2, bv);
	//adicionando restricoes da formulacao...
	printf("Var \n");
    c->addRestricoes();  
	printf("Solving problem!\n");
	c->solveProblem(arq3, arq4);
*/