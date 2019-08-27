/*
 * Colorable.h
 *
 *  Created on: 22 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_COLORABLE_H_
#define SRC_SOLVER_COLORABLE_H_

#include <ilcplex/cplex.h>
#include <stdlib.h>
#include <string.h>

class Colorable {
private:

	//the cplex enviroment
	CPXENVptr env = NULL;

	//the cplex problem
	CPXLPptr lp = NULL;

public:
	Colorable();

	virtual ~Colorable();

	void build(int* bvert, int bnum);

	bool solve();
};

#endif /* SRC_SOLVER_COLORABLE_H_ */
