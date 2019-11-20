/*
 * Graph.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#include "Graph.h"
#include <cstdlib>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

// cria um grafo vazio, necessário para alguns métodos.
Graph::Graph(){
	//TODO
}

/*
 * Cria um grafo com n vértices vazio, sem arestas.
 */
Graph::Graph(long n){
	//TODO
	this->neighbors = new Set[n];
	for (int i = 0; i < n; i++)
	{
		Set* s = new Set();
		this->neighbors[i] = *s;
	}
	this->n = n;
}

/*
 *
 */
Graph::~Graph(){
	//TODO
}

/*
 *Numero de arestas
 *
 */
long Graph::sizeE(){
	//TODO
	return this->m;
}

/*
 * Numero de vértices
 */
long Graph::sizeV(){
	//TODO
	return this->m;
}

/*
 * Adiciona uma arestas entre os vértices u e v
 */
void Graph::addEdge(long u, long v){
	//TODO
	this->neighbors[u].add(v);
}

/*
 * Remove a aresta entre v e u
 */
void Graph::removeEdge(long u, long v){
	//TODO
	this->neighbors[u].remove(v);
}

/*
 * Verifica se existe a aresta entre v e u
 *  */
bool Graph::hasEdge(long u, long v){
	//TODO
	//return this->neighbors[u].vertices[v] == 1 ? true : false;
	return this->neighbors[u].isIn(v);
}

/*
 * Recupera a vizinhanca de v.
 */
Set* Graph::getNeig(long v){
	//TODO
	return &this->neighbors[v];
}

/*
 * Recupera a anti-vizinhança do vértice.
 */
Set* Graph::getAntiNeig(long v){
	//TODO
	// Set* s = new Set(this->n);
	// for (int i = 0; i < this->n; i++)
	// 	if (this->neighbors[v].vertices[i] == 0)
	// 		s->vertices[i] = 1;
	return this->neighbors[v].complement();
}

/*
 * Grau do vertice.
 */
long Graph::degree(long v){
	//TODO
	return this->neighbors[v].count();
}

/**
 * Cria uma cópia do grafo
 *
 * */
Graph* Graph::copy(){
	//TODO
	Graph* g = new Graph();
	g->neighbors = new Set[this->n];
	for (int i = 0; i < n; i++)
		g->neighbors[i].numVer = 0;
	
	for (int i = 0; i < n; i++)
		g->neighbors[i] = this->neighbors[i];
	g->m = this->m;
	g->n = this->n;
	
	return g;
}

/*
 * print
 * */
void Graph::print(){
	//TODO
	for (int i = 0; i < n; i++)
	{
		if (this->neighbors[i].numVer != 0) 
				this->neighbors[i].print();
	}
	
}

void Graph::BuildMatrix (){
	int n = this->GetN();
	this->matIsIn = (int**)malloc(n * sizeof(int*));
	printf("Matrix\n");
	for (int i = 0; i < n; i++)
		this->matIsIn[i] = (int*)malloc(n * sizeof(int));
	printf("Allocation\n");
	for (int u = 0; u < n; u++){
		Set* neighU = this->getNeig(u);	
		Set* neighV = this->getNeig(u+1);
		this->matIsIn[u][u] = 1;
		if (u+1 < n){
			this->matIsIn[u][u+1] = 1;
			printf("%ulu\n",u);
			for (int v = 0; v < n; v++)
			{
				if (neighU->vertices[v] == 1 && neighV->vertices[v] != 1)
					this->matIsIn[u][u+1] = 0;
			}
		}
	}
	printf("\nMatrix P2\n");
	for (int u = 0; u < n; u++){
		for (int v = 0; v < n; v++)
			printf("%d ",this->matIsIn[u][v]);
		printf("\n");
	}
	printf("\n");
}

void Graph::ArrayDegree(){
	int n = this->GetN();
	this->vertDegrees = (int*)malloc(n * sizeof(int));
	printf("Array degress\n");
	for (int i = 0; i < n; i++){
		this->vertDegrees[i] = this->neighbors[i].count();
		printf("%d ",this->vertDegrees[i]);
	}
	printf("\n");
}

void Graph::AllocNeigh (){
	for (int i = 0; i < n; i++){
		Set* s = new Set(n);
		this->neighbors[i] = *s;
	}
}

void Graph::SetN (int num){
	this->n = num;
}
void Graph::SetM (int num){
	this->m = num;
}
int Graph::GetN (){
	return (int) this->n;
}
int Graph::GetM (){
	return (int) this->m;
}
Set* Graph::GetNeighbors (){
	return this->neighbors;
}

int** Graph::GetMatrix(){
	return this->matIsIn;
}
