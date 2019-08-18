/*
 * Graph.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#include "Graph.h"
#include <cstdlib>

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
void Graph::addEdge(long v, long u){
	//TODO
	this->neighbors[u].vertices[v] = 1;
}

/*
 * Remove a aresta entre v e u
 */
void Graph::removeEdge(long v, long u){
	//TODO
	this->neighbors[u].vertices[v] = 0;
}

/*
 * Verifica se existe a aresta entre v e u
 *  */
bool Graph::hasEdge(long v, long u){
	//TODO
	return this->neighbors[u].vertices[v] == 1 ? true : false;
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
	Set* s = new Set(this->n);
	for (int i = 0; i < this->n; i++)
		if (this->neighbors[v].vertices[i] == 0)
			s->vertices[i] = 1;
	return s;
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
	return this->n;
}
int Graph::GetM (){
	return this->m;
}

