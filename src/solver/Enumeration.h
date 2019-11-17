/*
 * Enumeration.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_ENUMERATION_H_
#define SRC_SOLVER_ENUMERATION_H_

#include "../tools/Graph.h"
#include "TreeNode.h"
#include "Colorable.h"

class Enumeration {

	int bestsol;                       // Melhor solução
	Colorable* color;                  // Solver

	Graph* g;                          // Grafo
	int* order;                        // Ordem dos vértices

	TreeNode* stack[];                 // Pilha utilizada na recursão
public:
	Enumeration(Graph* g, int* order, Colorable* c);

	virtual ~Enumeration();

	void buildRoot();                  // Constroi a raiz

	int solveMax();                    // Efetua a enumeração utilizando cortes
 
	void fullEnum();                   // Enumera todos os ramos possíveis

	void fullEnum(TreeNode* root);     

	TreeNode* GetRoot();               // Retorna a raiz

	int GetBestSolution ();            // Retorna a melhor solução

	void SetBestSolution (int);        // Seta a melhor solução

	bool verify (int*, int*, int);     // Verifica se dois arrays são equivalentes
};

#endif /* SRC_SOLVER_ENUMERATION_H_ */
