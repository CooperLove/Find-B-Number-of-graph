/*
 * TreeNode.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_TREENODE_H_
#define SRC_SOLVER_TREENODE_H_

#include "../tools/Graph.h"

class TreeNode {
	private:
		int* Cand;
		int* currCand;
		int* Bvts;
		int numcand;
		int sizeB;
		int posBvt;

		bool genL;
		bool genR;

		Graph* g;

	public:
		TreeNode(TreeNode* t, bool dir);

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
		void print ();
	protected:
};

#endif /* SRC_SOLVER_TREENODE_H_ */
