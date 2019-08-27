/*
 * Representative.cpp
 *
 *  Created on: Apr 13, 2018
 *      Author: marcio
 */

#include "Representative2.h"

int myheuristicfunc11(CPXCENVptr env, void *cbdata, int wherefrom, void *cbhandle, double *objval_p, double *x, int *checkfeas_p, int *useraction_p){
	int result_p;
	CPXgetcallbackinfo(env, cbdata, wherefrom, CPX_CALLBACK_INFO_NODE_COUNT, (void*)&result_p);

	if(result_p == 0){
		*((double*)cbhandle) = *objval_p;
	}
	*useraction_p = 0;
	return 0;
}

void Representative2::innerbuild(){
	int status;
	env = CPXopenCPLEX(&status);
	lp = CPXcreateprob(env, &status, "B-col with lower bounds");

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			x[i][j] = -1;
		}
	}

	char name[100];
	for(int i = 0; i < n; i++){
		if(g->degree(i) >= lb-1){
			x[i][i] = var++;
			sprintf(name, "x[%d][%d]", i+1, i+1);
			addBinVar(BIGM + 1.0, name);
			for(int j = 0; j< n; j++){
				if(j != i && !g->hasEdge(i, j)){
					x[i][j] = var++;
					sprintf(name, "x[%d][%d]", i+1, j+1);
					addBinVar(BIGM, name);
				}
			}
		}
	}

	Set* visited = new Set(n);
	long u, w;
	Set* mark = new Set(n);
	for(int v = 0; v < n; v++){
		addRepresentativeConst(v);
		visited->removeAll();
		visited->unio(g->getAntiNeig(v));
		u = 0;
		mark->removeAll();
		while(!visited->isEmpty()){
			u = visited->firstElemAfter(u);
			w = visited->firstElemAfter(u+1);
			while(w < n){
				if(g->hasEdge(w, u)){
					addEdgeConst(v, u, w);
					mark->add(u);
					mark->add(w);
				}
				w = visited->firstElemAfter(w+1);
			}

			if(!mark->isIn(u)) addSingleVConst(v, u);

			visited->remove(u);
		}
	}

	delete visited;
	delete mark;

	for(int v = 0; v < n; v++){
		for(int u = 0; u < n; u++){
			if(v!=u && x[v][v] >= 0 && x[u][u] >= 0 && !g->hasEdge(v, u)) addBcolConstraint(v, u);
		}
	}

}

void Representative2::innerSolver(){
	CPXchgprobtype(env, lp, 1);

	CPXchgobjsen(env, lp, CPX_MAX);

	int status = CPXsetdblparam(env, CPX_PARAM_TILIM/*1039*/, 600.0);
	//status = CPXwriteprob (env, lp, "Representative.lp", NULL);

	//to retrieve the LP solution
	double mydata;
	status = CPXsetheuristiccallbackfunc(env, myheuristicfunc11, (void*)&mydata);

	status = CPXmipopt (env, lp);


	if(status != 0){
		printf("\n PROBLEMS TO SOLVE THE MODEL!!!! ERRO CODE = %d\n", status);
	}

	double aux;
	CPXgetobjval(env, lp, &aux);
	solution = aux - BIGM*BIGM;

	solutionLP = mydata - BIGM*BIGM;

	CPXgetmiprelgap(env, lp, &aux);
	gap = aux;

	nnodes = CPXgetnodecnt(env, lp);


	/**********/
	//double z[1000];
	//status = CPXgetx (env, lp, z, 0, CPXgetnumcols(env, lp)-1);

	//for(int i = 0; i < n; i++){
	//	if(y[i] >= 0 && (z[x[i][i]] >= 0.5 ||z[y[i]] >= 0.5))printf("x[%d][%d] = %f  ---- y[%d] = %f \n", i+1, i+1, z[x[i][i]], i+1, z[y[i]]);
	//	for(int j = 0; j < n; j++){
	//		if(x[i][j] >= 0 && i != j && z[x[i][j]] >= 0.5)printf("x[%d][%d] = %f\n", i+1, j+1, z[x[i][j]]);
	//	}
	//}
}


void Representative2::addBinVar(double coef, char* name){
	double obj = coef;
	double lb = 0.0;
	double up = 1.0;
	char type = 'B';
	CPXnewcols(env, lp, 1, &obj, &lb, &up, &type, &name);
}

void Representative2::addEdgeConst(long v, long u, long w){
	double rhs = 0.0;// lado direito

	char sense = 'L';

	int rmatind[3] = {x[v][v], x[v][u], x[v][w]};
	double rmatval[3] = {-1.0, 1.0, 1.0};

	int rmatbeg[2] = {0, 2};

	if(x[v][v] >= 0)CPXaddrows(env, lp, 0, 1, 3, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}

void Representative2::addSingleVConst(long v, long u){
	double rhs = 0.0;// lado direito

	char sense = 'L';

	int rmatind[2] = {x[v][v], x[v][u]};
	double rmatval[2] = {-1.0, 1.0};

	int rmatbeg[2] = {0, 1};

	if(x[v][v] >= 0)CPXaddrows(env, lp, 0, 1, 2, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}

void Representative2::addRepresentativeConst(long v){
	int nzcnt = 0; //numero de coeficientes nao zero
	double rhs = 1.0;// lado direito

	char sense = 'L';

	int rmatind[n];
	double rmatval[n];

	if(x[v][v] >= 0){
		rmatind[nzcnt] = x[v][v];
		rmatval[nzcnt++] = 1.0;
	}
	for(int i = 0; i < n; i++){
		if(i != v && !g->hasEdge(v, i) && x[i][i] >= 0){
			rmatind[nzcnt] = x[i][v];
			rmatval[nzcnt++] = 1.0;
		}
	}

	int rmatbeg[2] = {0, nzcnt - 1};

	if(nzcnt > 0)CPXaddrows(env, lp, 0, 1, nzcnt, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}

void Representative2::addBcolConstraint(long v, long u){
	int nzcnt = 0; //numero de coeficientes nao zero
	double rhs = 1.0;// lado direito

	char sense = 'L';

	int rmatind[n];
	double rmatval[n];

	rmatind[nzcnt] = x[v][v];
	rmatval[nzcnt++] = 1.0;
	rmatind[nzcnt] = x[u][u];
	rmatval[nzcnt++] = 1.0;

	for(int i = 0; i < n; i++){
		if(i != v && i != u && !g->hasEdge(u, i) && g->hasEdge(v, i)){
			rmatind[nzcnt] = x[u][i];
			rmatval[nzcnt++] = -1.0;
		}
	}

	int rmatbeg[2] = {0, nzcnt - 1};

	if(x[v][v] >= 0 && x[u][u] >= 0)CPXaddrows(env, lp, 0, 1, nzcnt, &rhs, &sense, rmatbeg,rmatind, rmatval, NULL, NULL);
}


Representative2::Representative2(Graph* h, long lnb): Solver(h){
	lb = lnb;
	g = h;
	n = g->sizeV();
	var = 0;
	x = new long*[n];
	for(int i = 0; i < n; i++){
		x[i] = new long[n];
	}
	BIGM = n;
}

Representative2::~Representative2(){
	for(int i = 0; i < n; i++) delete x[i];

	delete x;
}

void Representative2::addInitialSolution(Heuristic* heu){
	int mcnt = 1;
	int nzcnt = var;
	int beg[2];
	int varindices[2*n*n];
	double values[2*n*n];

	for(int i = 0; i < var; i++){
		varindices[i] = i;
		values[i] = 0.0;
	}

	int limit = heu->getSolution();
	Set* colors;
	int rep, bv;

	for(int i = 0; i < limit; i++){
		colors = heu->getSolutionColor(i);
		rep = heu->getBVertexColor(i);
		values[x[rep][rep]] = 1.0;

		for(int j = colors->firstElem(); j < n; j = colors->firstElemAfter(j+1)){
			values[x[rep][j]] = 1.0;
		}
	}

	int effortlevel = CPX_MIPSTART_AUTO;

	CPXaddmipstarts(env, lp, mcnt, nzcnt, beg, varindices, values, &effortlevel, NULL);
}

