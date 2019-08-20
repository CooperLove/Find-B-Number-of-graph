/*
 * Enumeration.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_ENUMERATION_H_
#define SRC_SOLVER_ENUMERATION_H_

#include "Graph.h"
#include "TreeNode.h"

class Enumeration {

	TreeNode** Q;
	int bestsol;

public:
	Enumeration(Graph* g, int* order);

	virtual ~Enumeration();

	void buildRoot();

	int solveMax();

	void fullEnum();
};

#endif /* SRC_SOLVER_ENUMERATION_H_ */
