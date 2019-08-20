/*
 * TreeNode.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_TREENODE_H_
#define SRC_SOLVER_TREENODE_H_

#include "Graph.h"

class TreeNode {

	int* Cand;
	int* Bvts;
	int numcand;
	int sizeB;

	bool genL;
	bool genR;

public:
	TreeNode(Graph* G, int* order);

	virtual ~TreeNode();

	TreeNode* genLeft();

	TreeNode* genRight();

	bool hasLeft();

	bool hasRight();

	bool hasChild();

	int* getCand();

	int* getBvertices();

	int getBNum();

	int getCanNum();
};

#endif /* SRC_SOLVER_TREENODE_H_ */
