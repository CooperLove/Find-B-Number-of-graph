/*
 * Colorable.h
 *
 *  Created on: 22 de ago de 2019
 *      Author: marcio
 */

#ifndef SRC_SOLVER_COLORABLE_H_
#define SRC_SOLVER_COLORABLE_H_

class Colorable {
public:
	Colorable();

	virtual ~Colorable();

	void build(int* bvert, int bnum);

	bool solve();
};

#endif /* SRC_SOLVER_COLORABLE_H_ */
