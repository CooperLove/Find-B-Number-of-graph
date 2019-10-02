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

char* VertexOrder::degreeMax (){
	int size = this->g->GetN();
	char* v = new char[size];
	for (int i = 0; i < size; i++)
		v[i] = i+1;
	
	for (int i = 0; i < size; i++)
		for (int j = i+1; j < size; j++)
			if (g->degree(v[i]-1) < g->degree(v[j]-1)){
				Swap (&v[i], &v[j]);
				//printf("(%d %d) < (%d %d)\n",i,g->degree(i),j, g->degree(j));
			}
	for (int i = 0; i < size; i++)
		printf("%d->%lu ",v[i]-1, g->degree(v[i]-1));
	printf ("\n");
	return v;
}

char* VertexOrder::degreeMin (){
	int size = g->GetN();
	char* v = new char[size];
	for (int i = 0; i < size; i++)
		v[i] = i + 1;

	for (int i = 0; i < size; i++)
		for (int j = i+1; j < size; j++)
			if (g->degree(v[i]-1) > g->degree(v[j]-1))
				Swap (&v[i], &v[j]);
	return v;
}

char* VertexOrder::rand (){
	char* v = new char[1];
	return v;
}

void VertexOrder::Swap (char* a, char* b){
	//printf ("%d %d -- ",*a,*b);
	int aux = *a;
	*a = *b;
	*b = aux;
	//printf ("%d %d\n",*a,*b);
}


