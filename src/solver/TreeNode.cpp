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
	this->numcand                  = t->numcand - 1;     //printf ("02 OKAY!\n");
	this->Bvts                     = t->Bvts;            //printf ("03 OKAY!\n");
	this->posBvt                   = t->posBvt + 1;
	this->Bvts[t->currCand[0] - 1] = dir ? 0 : 1;        //printf ("04 OKAY!\n");
	int* newCand                   = new int[t->numcand - 1];
	this->posCand                  = this->posCand + 1 > this->g->GetN() ? this->posCand + 1 : this->posCand;
	//printf ("05 OKAY!\n");

	//printf ("%d - %d!\n",this->posBvt, t->g->GetN());
	for (int i = 0; i < t->numcand - 1; i++) // 123456 -> 23456
		newCand[i] = t->Cand[i + this->posBvt];
	this->currCand = newCand;
	//printf ("TreeNode OKAY!\n");
	
}

TreeNode::TreeNode (Graph* G, int* order) {
	// TODO Auto-generated constructor stub
	this->g        = G;
	this->numcand  = G->GetN();
	this->Cand     = order;
	this->currCand = order;
	this->posBvt   = 0;
	this->Bvts     = new int[this->numcand];
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

TreeNode* TreeNode::genRight(){
	TreeNode* t = new TreeNode(this, true);
	this->genR = true;
	return t;
}

bool TreeNode::hasLeft(){
	return this->genL ? false : true;
}

bool TreeNode::hasRight(){
	return this->genR ? false : true;;
}

bool TreeNode::hasChild(){
	return this->numcand == 0 ? false : true;
}

int* TreeNode::getCand(){
	return this->Cand;
}

int* TreeNode::getBvertices(){
  	return this->Bvts;
}

int TreeNode::getBNum(){
	return this->sizeB;
}

int TreeNode::getCanNum(){
	return this->numcand;
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
