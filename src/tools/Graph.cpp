/*
 * Graph.cpp
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#include "Graph.h"

// cria um grafo vazio, necessário para alguns métodos.
Graph::Graph(){
	//TODO
}

/*
 * Cria um grafo com n vértices vazio, sem arestas.
 */
Graph::Graph(long n){
	//TODO
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
	return 0;
}

/*
 * Numero de vértices
 */
long Graph::sizeV(){
	//TODO
	return 0;
}

/*
 * Adiciona uma arestas entre os vértices u e v
 */
void Graph::addEdge(long v, long u){
	//TODO
}

/*
 * Remove a aresta entre v e u
 */
void Graph::removeEdge(long v, long u){
	//TODO
}

/*
 * Verifica se existe a aresta entre v e u
 *  */
bool Graph::hasEdge(long v, long u){
	//TODO
}

/*
 * Recupera a vizinhanca de v.
 */
Set* Graph::getNeig(long v){
	//TODO
	return NULL;
}

/*
 * Recupera a anti-vizinhança do vértice.
 */
Set* Graph::getAntiNeig(long v){
	//TODO
	return NULL;
}

/*
 * Grau do vertice.
 */
long Graph::degree(long v){
	//TODO
}

/**
 * Cria uma cópia do grafo
 *
 * */
Graph* Graph::copy(){
	//TODO
}

/*
 * print
 * */
void Graph::print(){
	//TODO
}
