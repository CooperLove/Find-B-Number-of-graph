/*
 * Enumeration.cpp
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#include "Enumeration.h"
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Enumeration::Enumeration(Graph* g, int* order, Colorable* c) {
	// TODO Auto-generated constructor stub
	this->g = g;
	this->order = order;
	this->color = c;
}

Enumeration::~Enumeration() {
	 
	// TODO Auto-generated destructor stub
}

void Enumeration::buildRoot(){

	this->stack = new TreeNode*[this->g->GetN()];                                     // Faz a pilha apontar para o novo array
	for (int i = 0; i < this->g->GetN(); i++)             // Inicializa a pilha com TreeNodes vazios
		this->stack[i] = new TreeNode();

	TreeNode* root = new TreeNode(this->g, this->order);  // Cria a raiz 
	this->stack[0] = root;                                // primeiro elemento da pilha é a raiz
	this->stack[0]->print();                              // Print da raiz

}

int Enumeration::solveMax(){
	int nodes = 0;
	int nivel = 0;
	printf ("Inicio %d => %d\n",nivel, this->g->GetN() - 1);
	int MAX_NODES = (int) pow (2.0, (float)this->g->GetN());
	int leaves = 0;
	
	/*
	int** solucoes = (int**) malloc(sizeof(int*) * (MAX_NODES/2));
	int* tamSolucoes = (int*) malloc(sizeof(int) * (MAX_NODES/2));
	for (size_t i = 0; i < MAX_NODES/2; i++)
	{
		solucoes[i] = (int*) malloc(sizeof(int) * this->g->GetN());
	}
	int j = 0;
	printf("alocou!!\n");
	*/
	do
	{
		//this->stack[nivel]->print();
		//getchar();
		if (!this->stack[nivel]->hasChild()){ // O nó é uma folha
			printf("\t-------------------------------------------------\n");
			//this->stack[nivel]->print();      // Printa o nó 
			//solucoes[j] = this->stack[nivel]->getBvertices();
			//tamSolucoes[j++] = this->stack[nivel]->getBNum2();
			bool result = this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum()); // Chamada ao CPLEX
			/*
			bool result;
				result = this->color->build(solucoes[j-1], tamSolucoes[j-1]);
			int sol = this->GetBestSolution();
			if (tamSolucoes[j-1] > sol)
			if (result == true){
				this->bestsol = this->color->GetBestSolution();
					printf("Melhor solução = %d\n",this->bestsol);
			}
			*/
			printf("\t-------------------------------------------------\n");
			nivel--; leaves++;                // Decrementa o nivel e incrementa o num de folhas
			continue;
		}
		
		if (this->stack[nivel]->hasLeft() ){    // Caso o filho esquerdo não tenha sido gerado
			TreeNode* t = this->stack[nivel]->genLeft(this->bestsol); // Gera o filho esquerdo 
			if (t->getBNum2() != 0){	        // Se depois dos cortes ainda possuir algum bvertice
				this->stack[nivel + 1] = t;     // Coloca o nó criado na pilha
				nodes++; nivel++;               // Incrimenta o nivel e os nós
				continue;
			}
		}
			
		
		if (this->stack[nivel]->hasRight() ){  // Caso o filho direito não tenha sido gerado
			TreeNode* t = this->stack[nivel]->genRight(this->bestsol); // Gera o filho direito
			if (t->getBNum2() != 0){	       // Se depois dos cortes ainda possuir algum bvertice
				this->stack[nivel + 1] = t;    // Coloca o nó criado na pilha
				nodes++; nivel++;              // Incrimenta o nivel e os nós
				continue;
			}
		}
			
		if (nivel > 0) nivel--; // Caso não tenha filhos e não seja uma folha
	} while (nivel != 0);
	/*
	for (int i = 0; i < MAX_NODES/2; i++)
	{
		if (tamSolucoes[i] == 0) break;
		for (int j = 0; j < this->g->GetN(); j++)
		{
			printf("%d ",solucoes[i][j]);
		}
		printf(" => %d\n",tamSolucoes[i]);
	}
	int solucoesEncontradas = 0;
	for (int i = 0; i < MAX_NODES/2; i++)
	{
		if (tamSolucoes[i] == 0)
			break;
		bool result = this->color->build(solucoes[i], tamSolucoes[i]);
		if (result == true) {
			solucoesEncontradas++;
			printf("\t\t");
			for (int j = 0; j < this->g->GetN(); j++)
			{
				printf("%d ",solucoes[i][j]);
			}
			printf(" => %d\n",tamSolucoes[i]);
		}
	}
	*/
	
	printf ("\n\tPrintou %d folhas\n",leaves);
	//printf("Foram encontradas %d soluções e a melhor foi: %d\n",solucoesEncontradas ,this->color->GetBestSolution());
	
	return -1;
}

void Enumeration::fullEnum(){
	int nodes = 0;
	int nivel = 0;
	printf ("Inicio %d => %d\n",nivel, this->g->GetN() - 1);
	int MAX_NODES = (int) pow (2.0, (float)this->g->GetN());
	int leaves = 0;
	int** solucoes = (int**) malloc(sizeof(int*) * (MAX_NODES/2));
	int* tamSolucoes = (int*) malloc(sizeof(int) * (MAX_NODES/2));
	for (size_t i = 0; i < MAX_NODES/2; i++)
	{
		solucoes[i] = (int*) malloc(sizeof(int) * this->g->GetN());
	}
	
	int j = 0;
	do
	{
		//if (nodes > MAX_NODES) break;
		if (!this->stack[nivel]->hasChild() ){
			
			this->stack[nivel]->print();
			solucoes[j] = this->stack[nivel]->getBvertices();
			tamSolucoes[j++] = this->stack[nivel]->getBNum2();
			//this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum());			
			//printf("Node: %d < %d\n",nodes, leaves);
			nivel--; leaves++;
			continue;
		}
		
		if (this->stack[nivel]->hasLeft()){
			TreeNode* t = this->stack[nivel]->genLeft();
			this->stack[nivel + 1] = t;
			nodes++; nivel++; 
			continue;
		}
		if (this->stack[nivel]->hasRight()){
			TreeNode* t = this->stack[nivel]->genRight();
			this->stack[nivel + 1] = t;
			nodes++; nivel++; 
			continue;
		}
		nivel--;
	} while (nivel != 0);
	for (int i = 0; i < MAX_NODES/2; i++)
	{
		for (int j = 0; j < this->g->GetN(); j++)
		{
			//printf("%d ",solucoes[i][j]);
		}
		//printf(" => %d\n",tamSolucoes[i]);
	}
	int solucoesEncontradas = 0;
	int bestIndex = 0;
	int bs = 1;
	for (int i = 0; i < MAX_NODES/2; i++)
	{
		bool result = this->color->build(solucoes[i], tamSolucoes[i]);
		if (result == true) {
			if (this->color->GetBestSolution() > bs){
				bs = this->color->GetBestSolution();
				bestIndex = i;
			}
			solucoesEncontradas++;
			for (int j = 0; j < this->g->GetN(); j++)
			{
				printf("%d ",solucoes[i][j]);
			}
			printf(" => %d\n",tamSolucoes[i]);
		}
	}
	this->color->build(solucoes[bestIndex], tamSolucoes[bestIndex]);
	printf ("\n\tPrintou %d folhas e um total de %d de Possiveis = %d \n",leaves,nodes+1, MAX_NODES);
	printf("Foram encontradas %d soluções e a melhor foi: %d\n",solucoesEncontradas ,this->color->GetBestSolution());
	
}


bool Enumeration::verify(int* bvert, int* copia, int size){
	for (size_t i = 0; i < size; i++)
	{
		if (bvert[i] != copia[i]){
			return false;
		}
	}
	return true;
}

void Enumeration::fullEnum(TreeNode* root){
	if (!root->hasChild()){
		root->print();
		return;
	}
	if (root->hasLeft()){
		TreeNode* t = root->genLeft();
		fullEnum(t);
	}
	if (root->hasRight()){
		TreeNode* t = root->genRight();
		fullEnum(t);
	}
}

TreeNode* Enumeration::GetRoot(){
	return this->stack[0];
}

int Enumeration::GetBestSolution (){
	return this->bestsol;
}

void Enumeration::SetBestSolution (int value){
	this->bestsol = value;
}
