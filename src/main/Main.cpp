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

	// Set* s = new Set(10);
	// s->print();
	// s->removeAll();
	// s->print();
	g->print();
	int* v = order->degreeMax();
	int* v2 = v;
	Colorable* c = new Colorable();
	c->SetG(g);
	Enumeration* en = new Enumeration(g, v2, c);
	printf ("Begin enumeration!\n");
	en->buildRoot();
	en->fullEnum();
	printf ("End enumeration!\n");

	printf ("Begin coloring!\n\t");
	char* arq2 = "log.txt";
	char *arq3 = "arq3.txt";
	char *arq4 = "arq4.lp";
	c->carregarVariaveis();
	//inicializando cplex...
	int bv[6] = {0,1,0,1,0,1};
	c->startCplex(arq2, bv);
	//adicionando restricoes da formulacao...
	printf("Var \n");
    c->addRestricoes();  
	printf("Solving problem!\n");
	c->solveProblem(arq3, arq4);
	printf ("End coloring!\n");

	printf ("Max degree\n\t");
	for (int i = 0; i < g->GetN(); i++)
		printf ("%d ",v[i]);
	printf("\n");

	printf ("Min degree\n\t");
	v = order->degreeMin();
	for (int i = 0; i < g->GetN(); i++)
		printf ("%d ",v[i]);
	printf("\n");
	
	TreeNode* t = new TreeNode(g, v2);        t->print();
	TreeNode* t1 = new TreeNode(t, false);   t1->print();
	TreeNode* t2 = new TreeNode(t1, false);  t2 ->print();
	TreeNode* t3 = new TreeNode(t2, true);  t3 ->print();
	TreeNode* t4 = new TreeNode(t3, true);   t4 ->print();
	TreeNode* t5 = new TreeNode(t4, false);  t5 ->print();
	TreeNode* t6 = new TreeNode(t5, false);  t6 ->print();

	printf("OKAY!\n");

	fclose(fin);
	fclose(fout);

	return 0;
}


