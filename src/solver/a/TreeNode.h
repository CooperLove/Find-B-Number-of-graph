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
		short numcand;
		short sizeB;
		short posBvt;
		short posCand;

		bool genL;
		bool genR;
		bool visited;

		Graph* g;

	public:
		TreeNode();

		TreeNode(TreeNode* t, bool dir);

		TreeNode(Graph* G, int* order);

		virtual ~TreeNode();

		TreeNode* genLeft();

		TreeNode* genRight();

		TreeNode* genLeft(int);

		TreeNode* genRight(int);

		bool hasLeft();

		bool hasRight();

		bool hasChild();

		int* getCand();
		
		int* getCurCand();

		int* getBvertices();

		void setBNum (short);

		short getBNum();

		short getBNum2 ();

		void setCand(int*);

		void setCandNum (short);

		void setVisited(bool);

		short getCanNum();

		bool getVisited();

		void print ();
	protected:
};

#endif /* SRC_SOLVER_TREENODE_H_ */
