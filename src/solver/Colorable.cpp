/*
 * Colorable.cpp
 *
 *  Created on: 22 de ago de 2019
 *      Author: marcio
 */

#include "Colorable.h"

Colorable::Colorable() {
	// TODO Auto-generated constructor stub

}

Colorable::~Colorable() {
	// TODO Auto-generated destructor stub
}


void Colorable::carregarVariaveis(){

	int u,v, t;
	cont = 0;
		//variaveis para arestas (Z)
		int n = this->g->GetN();

		variavelX = (int**)malloc(n * sizeof(int*));
       
		for (u = 0; u < n; u++)
		{
			variavelX[u] = (int*)malloc(n * sizeof(int));
			for(v = 0; v < n; v++)
			{
				variavelX[u][v] = cont;
				cont ++;
				//printf("%d ", variavelX[u][v]+1);
				
			} //printf("\n");
		}
        printf("\nVariavel X: %d\n",cont);  
}

void Colorable::startCplex(char arq[], int* bvert){

	int status = 0;
	env = CPXopenCPLEX(&status);

	/* Abrindo um logfile */

   		logfile = CPXfopen (arq, "a");
   		if ( logfile == NULL )
		{
			printf("\nErro na abertura do arquivo de log\n");
		}else{
   		   status = CPXsetlogfile (env, logfile);
		   if (status)
		   {
				printf("\nErro na abertura do arquivo de log\n");
		   }
		}
	/* não é obrigatório */



        //criando o problema - inicialmente estará vazio!
	lp = CPXcreateprob(env, &status,"Formulacao EEEE :D");


	// vetores que vão auxiliar na criação da FO e das variáveis - estão vazios

	
	double* obj = (double*)malloc(cont*sizeof(double));/*a funcao objetivo: a constante multiplicadora*/
	double* lb =  (double*)malloc(cont*sizeof(double));/*o limite inferior das variaveis*/
	double* ub =  (double*)malloc(cont*sizeof(double));/*o limite superior das variaveis*/
	char* type =  (char*)malloc(cont*sizeof(char));/*o tipo das variaveis*/

	// popular os vetores acima

	int u,v, contador = 0, i;
	int n = this->g->GetN();
	
	for(u = 0; u < n; u++)
	{
		for(v = 0; v < n; v++)
		{
			obj[contador] = 0; //troquei
			if (bvert[u] == 1 && u == v)
				obj[contador] = 1;
			lb[contador] = 0.0;
			ub[contador] = 1.0;
			type[contador] = 'B';
			
			contador++;
		}
	}
	

	//chamadas do CPLEX para adicionar os vetores no modelo - lp
	status = CPXnewcols (env, lp, contador, obj, lb, ub, type, NULL);

	//só é necessario se for de minimização - max é padrão do cplex
	CPXchgobjsen(env, lp, CPX_MAX); // CPX_MIN, para o de miminização
}

void Colorable::addRestricoes(){
	int n = this->g->GetN();
	for (int v = 0; v < n; v++)
		addRestricao01 (v);
	
	printf(" fon\n");
	for (int v = 0; v < n; v++)
		for (int u = 0; u < n; u++)
			for (int w = 0; w < n; w++)
				if (this->g->hasEdge(u,w)) 
					addRestricao02 (u,w,v);
	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++)
			addRestricao03(u, v);
	for (int v = 0; v < n; v++)
		for (int u = 0; u < n; u++){
			Set* s = this->g->getNeig(v);
			if (s->isIn(u))
				addRestricao04(v, u);
		}
	
}

void Colorable::addRestricao01 (int v){
      
    //printf("Rest u =%d v= %d\n", u, v);
	Set* s = this->g->getAntiNeig(v);
	int n = this->g->GetN();
	int  contador =0;
	int tam = n;
	double coef[tam];
	int col[tam];// col -id 
    int c = 0;
    
	
	col[contador] = variavelX[v][v];
	coef[contador] = 1.0;
	contador++;
	s->print();
	for (int i = 0; i < n; i++)
	{
		if (s->isIn(i) && i != v){
			printf("O vertice %d esta em S\n",i);
			col[contador] = variavelX[i][v];
			coef[contador] = 1.0;
			contador++;
		}
	}
	
	int rows[2] = {0,contador}; // troquei 
	double b[1] = {1.0}; //troquei
	char sense[1] = {'E'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
      
} 

void Colorable::addRestricao02 (int u, int w, int v){
    int  contador =0;
	int n = this->g->GetN();
	int tam = n;
	double coef[tam];
	int col[tam];// col -id 
    int c = 0;
    
	
	col[contador] = variavelX[v][u];
	coef[contador] = 1.0;
	contador++;

	col[contador] = variavelX[v][w];
	coef[contador] = 1.0;
	contador++;

	col[contador] = variavelX[v][v];
	coef[contador] = -1.0;
	contador++;

	//printf ("\t (%d,%d) %d %d -%d <= 0\n",u,w, variavelX[v][u], variavelX[v][w], variavelX[v][v]);
    
	int rows[2] = {0,contador}; // troquei 
	double b[1] = {0.0}; //troquei
	char sense[1] = {'L'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
      
}
void Colorable::addRestricao03 (int u, int v){
	int  contador =0;
	int n = this->g->GetN();
	int tam = n;
	double coef[tam];
	int col[tam];// col -id 
    int c = 0;

	Set* anU = this->g->getAntiNeig (u);
	Set* viV = this->g->getNeig (v);
	Set* s = anU->inter(viV);
	for (int w = 0; w < n; w++)
	{
		if (s->isIn(w)){
			col[contador] = variavelX[u][w];
			coef[contador] = 1.0;
			contador++;
		}
	}
	
	col[contador] = variavelX[u][v];
	coef[contador] = -1.0;
	contador++;

	col[contador] = variavelX[v][v];
	coef[contador] = -1.0;
	contador++;

	//printf ("\t (%d,%d) %d %d -%d <= 0\n",u,w, variavelX[v][u], variavelX[v][w], variavelX[v][v]);
    
	int rows[2] = {0,contador}; // troquei 
	double b[1] = {-1.0}; //troquei
	char sense[1] = {'G'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
    
}

void Colorable::addRestricao04 (int v, int u){
      int  contador =0;
	int n = this->g->GetN();
	int tam = n;
	double coef[tam];
	int col[tam];// col -id 
    int c = 0;
	
	col[contador] = variavelX[v][u];
	coef[contador] = 1.0;
	contador++;

	col[contador] = variavelX[v][v];
	coef[contador] = -1.0;
	contador++;

	//printf ("\t (%d,%d) %d %d -%d <= 0\n",u,w, variavelX[v][u], variavelX[v][w], variavelX[v][v]);
    
	int rows[2] = {0,contador}; // troquei 
	double b[1] = {0.0}; //troquei
	char sense[1] = {'L'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
}

void Colorable::solveProblem(char arq1[], char arq2[]){


	int status = 0;
	int n = this->g->GetN();

	out = fopen(arq1, "w");

	//gerando o .lp
	CPXwriteprob (env, lp, arq2, NULL);

	//RESOLVENDO :D :D :D \o \o \o
	printf("Resolvendo\n");
	status = CPXmipopt(env,lp);


	double value;
	//recuperando o valor da FO
	status = CPXgetobjval(env, lp, &value);
	printf ("status retorno de funcao objetivo: %d\n", status);

	double vetor[cont];
	//recuperando o valor das variáveis
	status= CPXgetx(env, lp, vetor, 0,cont-1);
	printf ("status retorno de valor das variaveis: %d\n", status);
    printf("FO = %f\n",value);

	//ESCREVENDO ARQUIVO DE SAIDA

	int u,v=0;
	int contador=0;
	fprintf(out, "%s\n", "Solucao");
	fprintf(out, "%s", "Valor objetivo = ");
	fprintf(out, "%f\n\n", value);

	printf("\tAntes\n");
	for (u=0; u < n ; u++)
	{
		for (v=0; v < n ; v++)
		{
			if(vetor[contador] == 1.0){
				fprintf(out, "%c", 'X');
				fprintf(out, "%d",  contador+1);
				//fprintf(out, "%d", (v+1));
				fprintf(out, "%c", '=');
				fprintf(out, "%f\n", vetor[contador]);
				
			}
			contador++;
		}
	}
	printf("\tDepois\n");
	fclose(out);
}


void Colorable::SetG (Graph* g){
	this->g = g;
}


