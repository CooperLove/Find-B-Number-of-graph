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
		char* Cand;
		char* currCand;
		char* Bvts;
		short numcand;
		short sizeB;
		short posBvt;
		short posCand;

		bool genL;
		bool genR;

		Graph* g;

	public:
		TreeNode();

		TreeNode(TreeNode* t, bool dir);

		TreeNode(Graph* G, char* order);

		virtual ~TreeNode();

		TreeNode* genLeft();

		TreeNode* genRight();

		bool hasLeft();

		bool hasRight();

		bool hasChild();

		char* getCand();

		char* getBvertices();

		short getBNum();

		short getCanNum();

		void print ();
	protected:
};

#endif /* SRC_SOLVER_TREENODE_H_ */
