/*
 * Graph.h
 *
 *  Created on: 15 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_TOOLS_GRAPH_H_
#define SRC_TOOLS_GRAPH_H_

#include "Set.h"
#include <cstdlib>

class Graph {
private:

	long n; // numero de vertices
	long m; // numero de arestas

	Set* neighbors; //a matrix de adjacencias, cada vértice tem sei próprio Set

	Graph();// cria um grafo vazio, necessário para alguns métodos.

public:
	/*
	 * Cria um grafo com n vértices vazio, sem arestas.
	 */
	Graph(long n);

	/*
	 *
	 */
	virtual ~Graph();

	/*
	 *Numero de arestas
	 *
	 */
	long sizeE();

	/*
	 * Numero de vértices
	 */
	long sizeV();

	/*
	 * Adiciona uma arestas entre os vértices u e v
	 */
	void addEdge(long v, long u);

	/*
	 * Remove a aresta entre v e u
	 */
	void removeEdge(long v, long u);

	/*
	 * Verifica se existe a aresta entre v e u
	 *  */
	bool hasEdge(long v, long u);

	/*
	 * Recupera a vizinhanca de v.
	 */
	Set* getNeig(long v);


	/*
	 * Recupera a anti-vizinhança do vértice.
	 */
	Set* getAntiNeig(long v);


	/*
	 * Grau do vertice.
	 */
	long degree(long v);

	/**
	 * Cria uma cópia do grafo
	 *
	 * */
	Graph* copy();

	/*
	 * print
	 * */
	void print();

	/*
	 * Aloca o array de vizinhos para todos os vértices
	 * */
	void AllocNeigh ();

	void SetN (int);
	void SetM (int);
	int GetN ();
	int GetM ();
};

#endif /* SRC_TOOLS_GRAPH_H_ */
