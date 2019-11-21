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
	this->g                        = t->g;                                          // Seta o grafo
	this->Cand                     = t->Cand;                                       // Seta os candidatos
	this->numcand                  = t->getCanNum() > 0 ? t->getCanNum() - 1 : 0;   // decrementa o num de candidatos caso ainda existam candidatos 
	//printf("Antes bvert\n");
	this->Bvts                     = (int*) malloc(sizeof(int) * this->g->GetN());                      // Seta os bvertices
	for (int i = 0; i < this->g->GetN(); i++)
	{
		this->Bvts[i] = t->Bvts[i];
	}
	//printf("Alocou bvert\n");
	this->posBvt                   = t->posBvt + 1;
	this->posCand                  = this->posCand + 1 > this->g->GetN() ? this->posCand + 1 : this->posCand;
	this->Bvts[t->currCand[0] - 1] = dir ? 0 : 1;                                   // Marca o bvertice como 1 caso seja um ramo a esq, C.C. marca como 0 
	int* newCand                   = new int[t->numcand - 1];                       // Instancia o array dos novos candidatos
	//this->currCand                 = new int[t->numcand - 1];
	for (int i = 0; i < t->numcand - 1; i++) // Pega todos os candidatos exceto o primeiro: 123456 -> 23456
		newCand[i] = t->Cand[i + this->posBvt];
	this->currCand = newCand; // Atualiza os candidatos atuais
	this->currCand = new int[t->numcand - 1]; 
	for (int i = 0; i < t->numcand - 1; i++)
	{
		this->currCand[i] = newCand[i];
	}
	
	this->getBNum();          // Calcula o numero de bvertices
	/*
	

	*/
}

TreeNode::TreeNode (Graph* G, int* order) { // Construtor da raiz
	// TODO Auto-generated constructor stub
	this->g        = G;                       // Seta o grafo
	this->numcand  = G->GetN();               // Total de candidatos 
	this->Cand     = order;                   // ordem inicial são os candidatos
	this->currCand = order;                   // currCand é um array auxiliar para efetuar a enumeração
	this->posBvt   = 0;                       
	this->Bvts     = new int[this->numcand];  // Numero de bvertices é igual ao tamanho do grafo
	this->posCand  = 0;

	for (int i = 0; i < this->numcand; i++) // Inicializa os bvert
		this->Bvts[i] = 0;
	
}

TreeNode::~TreeNode() {
	// TODO Auto-generated destructor stub

	delete this->Bvts;
	delete this->currCand;
}

TreeNode* TreeNode::genLeft(){
	TreeNode* t = new TreeNode(this, false);
	this->genL = true;
	return t;
}

TreeNode* TreeNode::genLeft(int bestsol){
	TreeNode* t = new TreeNode(this, false);
	//printf("Esq\n");
	this->genL = true; // Marca o filho esquerdo como gerado
	int bnum = t->getBNum2(); // Numero de bvert -> Bnum() calcula o num e retorna, Bnum2() só retorna
	
	
	int* b = t->getBvertices();
	int* c = t->getCand();
	int n = this->g->GetN(); // Tamanho do grafo
	int cnum = t->getCanNum(); // Numero de candidatos
	
	for (int i = 0; i < n; i++)
	{
		if (b[i] == 1 && t->g->degree(i) < bestsol)
		{ t->getBvertices()[i] = 0; t->setBNum(t->getBNum() - 1);}
		if (c[i] == 1 && t->g->degree(i) < bestsol)
		{ t->getCurCand()[i] = 0; t->setCandNum(t->getCanNum() - 1); }
	}
	/*
	//printf("Null ? %d\n",this->g->hasEdge(0,1));
	int wt = this->getCanNum();
	for (int u = 0; u < wt; u++){
		for (int v = u+1; v < wt; v++){
			if (t->getCurCand()[v] - 1 < 0 || t->getCurCand()[u] -1 < 0) continue;
			int a = t->getCurCand()[u] - 1;
			int b = t->getCurCand()[v] - 1;
			//printf("bool = %d %d - %d\n",a, b, this->g->GetMatrix()[a][b]);
			//if (!t->g->hasEdge(a,b) && this->g->GetMatrix()[a][b] == 1){
			//	t->getCurCand()[u] = 0; 
			//	t->setCandNum (t->getCanNum() - 1);
			//}
		}
	}
	//printf("Corte\n");
	if (t->getCanNum() > 0){
		int s = 0;
		int* new_cand = (int*) malloc(t->getCanNum()* sizeof(int));
		int a = t->getCanNum();
		for (int i = 0; i < wt; i++)
		{
			if (t->currCand[i] != 0){
				new_cand[s++] = t->currCand[i];
			}
		}
		t->setCand(new_cand);
	}
	printf("Mudou os cand\n");
	t->print();
	*/
	t->numcand = t->getCanNum() > 0 ? t->getCanNum() : 0;
	for (int i = 0; i < n; i++)
	{	
		if (t->getBvertices()[i] == 1 && t->g->degree(i) < bnum - 1)
		{ t->setBNum(t->getBNum2() - 1); }
	}
	if (cnum + bnum < bestsol || t->getBNum2() == 0 || t->getBNum2() < bestsol){
		t->genL = true; t->genR = true;
	}
	
	return t;
}

TreeNode* TreeNode::genRight(){
	TreeNode* t = new TreeNode(this, true);
	this->genR = true;
	return t;
}

TreeNode* TreeNode::genRight(int bestsol){
	TreeNode* t = new TreeNode(this, true);
	this->genR = true; // Marcar o filho direito como gerado
	
	int* b = t->getBvertices();
	int* c = t->getCand();
	int n = this->g->GetN(); // Tamanho do grafo
	int bnum = t->getBNum(); // Numero de b-vertices
	int cnum = t->getCanNum(); // Numero de candidatos

	for (int i = 0; i < n; i++) // Primeiro corte
	{
		if (b[i] == 1 && t->g->degree(i) < bestsol)
			t->getBvertices()[i] = 0; t->setBNum(t->getBNum() - 1);
		if (c[i] == 1 && t->g->degree(i) < bestsol){
			t->currCand[i] = 0; t->setCandNum(t->getCanNum() - 1);
		}
	}
	int s = 0;
	int* new_cand = (int*) malloc(t->getCanNum() * sizeof(int));
	for (int i = 0; i < cnum; i++) // Segundo corte
	{
		if (t->currCand[i] != 0){
			new_cand[s++] = t->currCand[i];
		}
	}
	t->setCand(new_cand); // Atualiza o array de cand 

	t->numcand = t->getCanNum();

	if (t->getCanNum() + t->getBNum() < bestsol){
		t->sizeB = 0;
		t->numcand = 0;
	}

	for (int i = 0; i < n; i++)
	{
		if (t->getBvertices()[i] == 1 && t->g->degree(i) < bnum - 1){
			t->setBNum(t->getBNum2() - 1);
		}
	}
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

int* TreeNode::getCurCand(){
	return this->currCand;
}

int* TreeNode::getBvertices(){
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

void TreeNode::setCand (int* value){
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
