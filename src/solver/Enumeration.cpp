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
	TreeNode* t = new TreeNode[this->g->GetN()];
	*this->stack = t;
	for (int i = 0; i < this->g->GetN(); i++)
		this->stack[i] = new TreeNode();

	TreeNode* root = new TreeNode(this->g, this->order);
	this->stack[0] = root;
	this->stack[0]->print();
}

int Enumeration::solveMax(){
	int nodes = 0;
	int nivel = 0;
	printf ("Inicio %d => %d\n",nivel, this->g->GetN() - 1);
	int MAX_NODES = (int) pow (2.0, (float)this->g->GetN());
	int leaves = 0;
	do
	{
		if (nodes > MAX_NODES) break;
		//this->stack[nivel]->print();
		//getchar();
		if (!this->stack[nivel]->hasChild()){
			printf("\t-------------------------------------------------\n");
			//this->stack[nivel]->print();
			//this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum());
			printf("\t-------------------------------------------------\n");
			nivel--; leaves++;
			continue;
		}
		///*
		if (this->stack[nivel]->hasLeft() ){
			TreeNode* t = this->stack[nivel]->genLeft(this->bestsol);
			printf("Gerou esq!\n");
			//free(this->stack[nivel]);
			if (t->getBNum2() != 0){
				this->stack[nivel + 1] = t; 
				nodes++; nivel++; //printf (" <= ");
				continue;
			}
		}
		
		if (this->stack[nivel]->hasRight() ){
			TreeNode* t = this->stack[nivel]->genRight(this->bestsol);
			//free(this->stack[nivel]);
			if (t->getBNum2() != 0){	
				this->stack[nivel + 1] = t; 
				nodes++; nivel++; //printf (" => ");
				continue;
			}
		}
		
		//free(this->stack[nivel]);
		//this->stack[nivel] = new TreeNode();
		nivel--;
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
		if (nodes > MAX_NODES) break;
		if(nodes%15000 == 0)
			printf("Node %d\n",nodes);
		//getchar();
		if (!this->stack[nivel]->hasChild() ){
			//printf ("Nivel %d, %d\n",nivel,leaves+1);
			//printf("\n%d  ",this->stack[nivel]->getBNum());
			//this->stack[nivel]->print();
			int tam = this->g->GetN();
			int* na = (int*) malloc(tam * sizeof(int));
			//printf("\t\t\t");
			for (size_t i = 0; i < tam; i++)
			{
				na[i] = this->stack[nivel]->getBvertices()[i];
				printf("%d ", na[i]);
			}
			//printf("\n");
			printf ("Antes = %d ", this->verify(this->stack[nivel]->getBvertices(), na, this->stack[nivel]->getBNum()));
			this->color->build(na, this->stack[nivel]->getBNum());
			printf ("Depois = %d\n", this->verify(this->stack[nivel]->getBvertices(), na, this->stack[nivel]->getBNum()));
			
			//this->stack[nivel]->print();
			nivel--; leaves++;
			continue;
		}else
		{
			//this->stack[nivel]->print();
		}
		
		if (this->stack[nivel]->hasLeft()){
			TreeNode* t = this->stack[nivel]->genLeft();
			this->stack[nivel + 1] = t;
			nodes++; nivel++; //printf (" <= ");
			continue;
		}
		if (this->stack[nivel]->hasRight()){
			TreeNode* t = this->stack[nivel]->genRight();
			this->stack[nivel + 1] = t;
			nodes++; nivel++; //printf (" => ");
			continue;
		}
		nivel--;
	} while (nivel != 0);
	printf ("\n\tPrintou %d folhas e um total de %d\n",leaves,nodes+1);
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