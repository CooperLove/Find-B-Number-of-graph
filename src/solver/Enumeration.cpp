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
	TreeNode* t = new TreeNode[this->g->GetN()];          // Cria um array de TreeNodes
	*this->stack = t;                                     // Faz a pilha apontar para o novo array
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
	do
	{
		
		if (!this->stack[nivel]->hasChild()){ // O nó é uma folha
			printf("\t-------------------------------------------------\n");
			this->stack[nivel]->print();      // Printa o nó 
			this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum()); // Chamada ao CPLEX
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
		nivel--; // Caso não tenha filhos e não seja uma folha
	} while (nivel != 0);
	printf ("\n\tPrintou %d folhas\n",leaves);
	return -1;
}

void Enumeration::fullEnum(){
	int nodes = 0;
	int nivel = 0;
	printf ("Inicio %d => %d\n",nivel, this->g->GetN() - 1);
	int MAX_NODES = (int) pow (2.0, (float)this->g->GetN());
	int leaves = 0;
	do
	{
		
		if (!this->stack[nivel]->hasChild() ){
			
			this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum());
			
			this->stack[nivel]->print();
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
	printf ("\n\tPrintou %d folhas e um total de %d de Possiveis = %d \n",leaves,nodes+1, MAX_NODES);
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
