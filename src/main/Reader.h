/*
 * Reader.h
 *
 *  Created on: 19 de dez de 2016
 *      Author: marcio
 */

#ifndef SRC_MAIN_READER_H_
#define SRC_MAIN_READER_H_

#include <cstdio>
#include <cstdlib>
#include "../tools/Graph.h"

using namespace std;

class Reader {
public:
	Reader();

	virtual ~Reader();

    Graph* read(FILE* dimacs);
};

#endif /* SRC_MAIN_READER_H_ */
