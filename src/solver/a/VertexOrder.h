/*
 * VertexOrder.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_VERTEXORDER_H_
#define SRC_SOLVER_VERTEXORDER_H_

#include "../tools/Graph.h"

class VertexOrder {
	Graph* g;
public:
	VertexOrder(Graph* g);

	virtual ~VertexOrder();

	int* degreeMax ();

	int* degreeMin ();

	int* rand ();

private:
	void Swap (int*, int*);
};

#endif /* SRC_SOLVER_VERTEXORDER_H_ */
