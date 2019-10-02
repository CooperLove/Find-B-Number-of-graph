/*
 * TreeNode.cpp
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#include "TreeNode.h"
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

TreeNode::TreeNode(){}

TreeNode::TreeNode(TreeNode* t, bool dir){
	this->g                        = t->g;
	this->Cand                     = t->Cand;            //printf ("01 OKAY!\n");
	this->numcand                  = t->getCanNum() > 0 ? t->getCanNum() - 1 : 0;     //printf ("02 OKAY!\n");
	this->Bvts                     = t->Bvts;            //printf ("03 OKAY!\n");
	this->posBvt                   = t->posBvt + 1;
	this->Bvts[t->currCand[0] - 1] = dir ? 0 : 1;        //printf ("04 OKAY!%d\n",t->numcand);
	char* newCand                   = new char[t->numcand - 1]; //printf ("05 OKAY!\n");
	this->posCand                  = this->posCand + 1 > this->g->GetN() ? this->posCand + 1 : this->posCand;
	//printf ("06 OKAY!\n");

	//printf ("%d - %d!\n",this->posBvt, t->g->GetN());
	for (int i = 0; i < t->numcand - 1; i++) // 123456 -> 23456
		newCand[i] = t->Cand[i + this->posBvt];
	this->currCand = newCand;
	this->getBNum();
	
	//printf ("TreeNode OKAY! %d %d\n",t->getCanNum(), this->numcand);
	//this->print();
}

TreeNode::TreeNode (Graph* G, char* order) {
	// TODO Auto-generated constructor stub
	this->g        = G;
	this->numcand  = G->GetN();
	this->Cand     = order;
	this->currCand = order;
	this->posBvt   = 0;
	this->Bvts     = new char[this->numcand];
	this->posCand  = 0;

	for (int i = 0; i < this->numcand; i++)
		this->Bvts[i] = 0;
	
}

TreeNode::~TreeNode() {
	// TODO Auto-generated destructor stub
}

TreeNode* TreeNode::genLeft(){
	TreeNode* t = new TreeNode(this, false);
	this->genL = true;
	return t;
}

TreeNode* TreeNode::genLeft(int bestsol){
	TreeNode* t = new TreeNode(this, false);
	this->genL = true;
	int bnum = t->getBNum2();
	
	char* b = t->getBvertices();
	char* c = t->getCand();
	int n = this->g->GetN();
	int cnum = t->getCanNum();

	for (int i = 0; i < n; i++)
	{
		if (b[i] == 1 && t->g->degree(i) < bestsol)
		{ t->getBvertices()[i] = 0; t->setBNum(t->getBNum() - 1);}
		if (c[i] == 1 && t->g->degree(i) < bestsol)
		{ t->getCurCand()[i] = 0; t->setCandNum(t->getCanNum() - 1); }
	}

	for (int u = 0; u < n; u++)
		for (int v = u+1; v < n; v++)
			if (!t->g->hasEdge(u,v) && this->g->GetMatrix()[u][v] == 1)
			{t->getCurCand()[u] = 0; t->setCandNum (t->getCanNum() - 1); }

	for (int i = 0; i < n; i++)
	{	
		if (t->getBvertices()[i] == 1 && t->g->degree(i) < bnum - 1)
		{ t->setBNum(t->getBNum2() - 1); }
	}
	if (cnum + bnum < bestsol || t->getBNum2() == 0 || t->getBNum2() < bestsol){
		t->genL = true; t->genR = true;
	}
	
	if (t->getCanNum() > 0){
		int s = 0;
		char* new_cand = (char*) malloc(t->getCanNum() * sizeof(char));
		for (int i = 0; i < cnum; i++)
		{
			if (t->currCand[i] != 0){
				new_cand[s++] = t->currCand[i];
			}
		}
		printf("Set\n");
		t->setCand(new_cand);
	}
	t->numcand = t->getCanNum() > 0 ? t->getCanNum() : 0; 
	return t;
}

TreeNode* TreeNode::genRight(){
	TreeNode* t = new TreeNode(this, true);
	this->genR = true;
	return t;
}

TreeNode* TreeNode::genRight(int bestsol){
	TreeNode* t = new TreeNode(this, true);
	this->genR = true;
	
	char* b = t->getBvertices();
	char* c = t->getCand();
	int n = this->g->GetN();
	int bnum = t->getBNum();
	int cnum = t->getCanNum();

	for (int i = 0; i < n; i++)
	{
		if (b[i] == 1 && t->g->degree(i) < bestsol)
			t->getBvertices()[i] = 0; t->setBNum(t->getBNum() - 1);
		if (c[i] == 1 && t->g->degree(i) < bestsol){
			t->currCand[i] = 0; t->setCandNum(t->getCanNum() - 1);
		}
	}
	int s = 0;
	char* new_cand = (char*) malloc(t->getCanNum() * sizeof(char));
	for (int i = 0; i < cnum; i++)
	{
		if (t->currCand[i] != 0){
			new_cand[s++] = t->currCand[i];
		}
	}
	t->setCand(new_cand);

	t->numcand = t->getCanNum();

	if (t->getCanNum() + t->getBNum() < bestsol){
		t->sizeB = 0;
		t->numcand = 0;
		printf("Corte 2 dir\n");
	}

	for (int i = 0; i < n; i++)
	{
		if (t->getBvertices()[i] == 1 && t->g->degree(i) < bnum - 1){
		printf ("Corte 4 dir %lu %d ",t->g->degree(i), bnum-1);
			t->setBNum(t->getBNum2() - 1);
		}
	}
	return t;
}

bool TreeNode::hasLeft(){
	return this->genL ? false : true;
}

bool TreeNode::hasRight(){
	return this->genR ? false : true;
}

bool TreeNode::hasChild(){
	return this->numcand == 0 ? false : true;
}

char* TreeNode::getCand(){
	return this->Cand;
}

char* TreeNode::getCurCand(){
	return this->currCand;
}

char* TreeNode::getBvertices(){
  	return this->Bvts;
}

void TreeNode::setBNum (short value){
	this->sizeB = value;
}

short TreeNode::getBNum(){
	short a = 0;
	for (int i = 0; i < this->g->GetN(); i++)
		if (this->Bvts[i] == 1)
			a++;
	this->sizeB = a;
	return this->sizeB;
}
short TreeNode::getBNum2 (){
	return this->sizeB;
}

void TreeNode::setCandNum (short value){
	this->numcand = value;
}

void TreeNode::setCand (char* value){
	this->currCand = value;
}

short TreeNode::getCanNum(){
	return this->numcand;
}

void TreeNode::setVisited(bool value){
	this->visited =value;
}

bool TreeNode::getVisited(){
	return this->visited;
}

void TreeNode::print (){
	printf ("\tB vertices atuais => ");
	for (int i = 0; i < this->g->GetN(); i++)
		printf ("%d ", this->Bvts[i]);
	printf ("     ");
	printf ("%d Candidatos atuais => ",this->numcand);
	for (int i = 0; i < this->numcand; i++)
		printf ("%d ", this->currCand[i]);
	printf ("\n");
	
}
