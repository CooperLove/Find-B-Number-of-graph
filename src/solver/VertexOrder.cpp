/*
 * VertexOrder.cpp
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#include "VertexOrder.h"
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

VertexOrder::VertexOrder (Graph* g) {
	// TODO Auto-generated constructor stub
	this->g = g;
}

VertexOrder::~VertexOrder() {
	// TODO Auto-generated destructor stub
}

int* VertexOrder::degreeMax (){
	int size = this->g->GetN();
	int* v = new int[size];
	for (int i = 0; i < size; i++)
		v[i] = i+1;
	
	for (int i = 0; i < size; i++)
		for (int j = i+1; j < size; j++)
			if (g->degree(i) < g->degree(j))
				Swap (&v[i], &v[j]);
	return v;
}

int* VertexOrder::degreeMin (){
	int size = g->GetN();
	int* v = new int[size];
	for (int i = 0; i < size; i++)
		v[i] = i + 1;

	for (int i = 0; i < size; i++)
		for (int j = i+1; j < size; j++)
			if (g->degree(i) > g->degree(j))
				Swap (&v[i], &v[j]);
	return v;
}

int* VertexOrder::rand (){
	int* v = new int[1];
	return v;
}

void VertexOrder::Swap (int* a, int* b){
	//printf ("%d %d -- ",*a,*b);
	int aux = *a;
	*a = *b;
	*b = aux;
	//printf ("%d %d\n",*a,*b);
}


