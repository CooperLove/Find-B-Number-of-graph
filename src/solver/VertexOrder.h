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

	char* degreeMax ();

	char* degreeMin ();

	char* rand ();

private:
	void Swap (char*, char*);
};

#endif /* SRC_SOLVER_VERTEXORDER_H_ */
