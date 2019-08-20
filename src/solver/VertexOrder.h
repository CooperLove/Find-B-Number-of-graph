/*
 * VertexOrder.h
 *
 *  Created on: 20 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_VERTEXORDER_H_
#define SRC_SOLVER_VERTEXORDER_H_

#include "Graph.h"

class VertexOrder {
public:
	VertexOrder(Graph* g);

	virtual ~VertexOrder();

	int* degreeMax();

	int* degreeMin();

	int* rand();

};

#endif /* SRC_SOLVER_VERTEXORDER_H_ */
