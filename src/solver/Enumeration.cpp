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
	return -1;
}

void Enumeration::fullEnum(){
	int nodes = 0;
	int nivel = 0;
	printf ("Inicio %d => %d\n",nivel, this->g->GetN() - 1);
	int MAX_NODES = (int) pow (2.0, (float)this->g->GetN());
	int leaves = 0;
	while (nodes < MAX_NODES)
	{
		if (!this->stack[nivel]->hasChild() ){
			printf ("Nivel %d, %d\n",nivel,leaves+1);
			this->stack[nivel]->print();
			nivel--;
			leaves++;
			continue;
		}
		if (nodes > MAX_NODES) break;
		if (this->stack[nivel]->hasLeft()){
			TreeNode* t = this->stack[nivel]->genLeft();
			//printf ("Esq %d ",nivel);
			this->stack[nivel + 1] = t; 
			nodes++;
			nivel++;
			printf (" <= ");
			continue;
		}
		if (this->stack[nivel]->hasRight()){
			TreeNode* t = this->stack[nivel]->genRight();
			//printf ("Esq %d ",nivel);
			this->stack[nivel + 1] = t; 
			nodes++;
			nivel++;
			printf (" => %d ",nivel);
			continue;
		}
		//this->stack[nivel]->print();
		nivel--;
	}
	printf ("\n\tPrintou %d folhas\n",leaves);
}

void Enumeration::fullEnum(TreeNode* root){
	if (!root->hasChild()){
		//printf ("Folha\n");
		root->print();
		return;
	}
	if (root->hasLeft()){
		//printf ("Esq\n");
		TreeNode* t = root->genLeft();
		fullEnum(t);
	}
	if (root->hasRight()){
		//printf ("Dir\n");
		TreeNode* t = root->genRight();
		fullEnum(t);
	}
}

TreeNode* Enumeration::GetRoot(){
	return this->stack[0];
}