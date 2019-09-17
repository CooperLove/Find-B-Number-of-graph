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

Enumeration::Enumeration(Graph* g, char* order, Colorable* c) {
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
		if (!this->stack[nivel]->hasChild()/* && this->stack[nivel]->getBNum2() >= this->bestsol*/){
			//printf ("Nivel %d, %d\n",nivel,leaves+1);
			//printf("\nPrint\n");
			this->stack[nivel]->print();
			this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum());
			nivel--; leaves++;
			continue;
		}
		if (this->stack[nivel]->hasLeft() ){
			TreeNode* t = this->stack[nivel]->genLeft(this->bestsol);
			//printf("T Esq %d ",t->getBNum2());
			//t->print();
			if (t->getBNum2() != 0){
				this->stack[nivel + 1] = t; 
				nodes++; nivel++; printf (" <= ");
				continue;
			}
		}
		//printf("Dir %d\n",this->stack[nivel]->hasRight());
		if (this->stack[nivel]->hasRight() ){
			//printf("Gerando dir\n");
			TreeNode* t = this->stack[nivel]->genRight(this->bestsol);
			//printf("T Dir\n");
			if (t->getBNum2() != 0){	
				this->stack[nivel + 1] = t; 
				nodes++; nivel++; printf (" => ");
				continue;
			}
		}
		//this->stack[nivel]->setVisited(true);
		//printf("Subiu\n");
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
		if (!this->stack[nivel]->hasChild() ){
			//printf ("Nivel %d, %d\n",nivel,leaves+1);
			printf("\n");
			this->stack[nivel]->print();
			this->color->build(this->stack[nivel]->getBvertices(), this->stack[nivel]->getBNum());
			nivel--; leaves++;
			continue;
		}
		if (this->stack[nivel]->hasLeft()){
			TreeNode* t = this->stack[nivel]->genLeft();
			this->stack[nivel + 1] = t; 
			nodes++; nivel++; printf (" <= ");
			continue;
		}
		if (this->stack[nivel]->hasRight()){
			TreeNode* t = this->stack[nivel]->genRight();
			this->stack[nivel + 1] = t; 
			nodes++; nivel++; printf (" => ");
			continue;
		}
		nivel--;
	} while (nivel != 0);
	printf ("\n\tPrintou %d folhas\n",leaves);
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