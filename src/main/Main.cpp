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
#include <time.h>

	//The initial time
	struct timeval  clockinit;

	//the final time
	struct timeval  clockend;

	//the time zone
	struct timezone tz;

	//
	float seconds;

void start(){
	seconds = 0.0;
	gettimeofday(&clockinit, &tz);
}
/*
//Pauses the clock
float pause(){
	gettimeofday(&clockend, &tz);
	seconds += ((float)(clockend.tv_sec - clockinit.tv_sec)) + ((float)(clockend.tv_usec - clockinit.tv_usec))/1000000;
	gettimeofday(&clockinit, &tz);
	return seconds;
}
*/
//Stop the clock
float stop(){
	gettimeofday(&clockend, &tz);
	seconds += ((float)(clockend.tv_sec - clockinit.tv_sec)) + ((float)(clockend.tv_usec - clockinit.tv_usec))/1000000;
	return seconds;
}

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
	Graph* g = myReader.read(fin);                  // Inicializa o grafo com arquivo contendo os vertices
	g->print();                                     // Printa o grafo
	g->BuildMatrix();
	g->ArrayDegree();
	VertexOrder* order = new VertexOrder (g);       // Cria o array da ordem dos vertices

	
	int* v = order->degreeMax();                    // Ordem maxima
	printf ("Ordenado\n");
	int* v2 = v; 
	Colorable* c = new Colorable();                 // Cria o solver
	c->SetG(g);                                     // Seta o grafo, inicializa o cplex, carrega as variaveis e add as restrições
	Enumeration* en = new Enumeration(g, v2, c);    // Cria a enumeração
	en->SetBestSolution(1);                         // Seta o valor inicial da melhor solução como 1
	printf ("Begin enumeration!\n");
	printf("\n\n\n");
	start();
	float elapsedTime = 0;
	en->buildRoot();                                // Constroi a raiz
	en->solveMax();                                 // Enumera todas as soluções
	elapsedTime = stop();
	printf ("End enumeration!\n");
	
	// ---------------------- Prints ---------------------- //

	v = order->degreeMax();
	printf ("Max degree\n\t");
	for (int i = 0; i < g->GetN(); i++)
		printf ("%d ",v[i]);
	printf("\n");

	printf ("Min degree\n\t");
	v = order->degreeMin();
	for (int i = 0; i < g->GetN(); i++)
		printf ("%d ",v[i]);
	printf("\n");

	printf("Demorou %f segundos - OKAY!\n",elapsedTime);

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