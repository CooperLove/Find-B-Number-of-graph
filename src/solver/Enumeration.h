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

	int bestsol;
	Colorable* color;

	Graph* g;
	char* order;

	TreeNode* stack[];
public:
	Enumeration(Graph* g, char* order, Colorable* c);

	virtual ~Enumeration();

	void buildRoot();

	int solveMax();

	void fullEnum();

	void fullEnum(TreeNode* root);

	TreeNode* GetRoot();

	int GetBestSolution ();

	void SetBestSolution (int);
};

#endif /* SRC_SOLVER_ENUMERATION_H_ */
