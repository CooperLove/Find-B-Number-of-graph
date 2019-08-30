#include <ilcplex/cplex.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
//#include "Timer.h"
//#include "linear.h"

//The initial time
	struct timeval  clockinit;

	//the final time
	struct timeval  clockend;

	//the time zone
	struct timezone tz;

	//
	float seconds;

/////VARIAVEIS GLOBAIS DE ENTRADA//////

int **G; /*matriz de adjacencia representando o Grafo*/
int n;/* numero de vertices do Grafo*/
int e; // numero de arestas
int m = 47; //cores

/////VARIAVEIS GLOBAIS PARA AS VARIAVEIS DO CPLEX//////

int **variavelX; /* matriz para criar as variaveis para as arestas*/
int **variavelZ;
int *variavelD;
int cont = 0; /*quantidade de variaves de vertice*/

CPXENVptr env;/*o ambiente do problema*/
CPXLPptr lp;/*o problema*/
CPXFILEptr logfile = NULL;

FILE *out;/*o arquivo de saida (RESULTADO DO CPLEX)*/


/////////////CARREGANDO ENTRADAS//////////////////

void carregarGrafo(char arq[]){

	FILE *inst = fopen(arq,"r");

		if(!inst){
		    printf("erro na leitura do arquivo!");
		}

		int i,j;
		int v;
		fscanf(inst,"%d",&n);
		fscanf(inst,"%d",&e);
		printf("Numero vertices: %d\n Numero arestas: %d\n",n,e);

		G = (int**)(malloc(n*sizeof(int*)));
        for(int i = 0 ; i < n ; i++) G[i] = (int*)malloc(n*sizeof(int));
            char aux[1];
        for(int i = 0; i < e ; i++){
            fscanf(inst,"%s",&aux);
            fscanf(inst,"%d",&v);
            fscanf(inst,"%d",&j);
            v -= 1; j -=1;
            G[v][j] = 1;
            G[j][v] = 1;
            //printf("Aresta %d %d = %d\n",v,j,G[v][j]);
        }
        for(int i = 0; i < n ; i++){
            G[i][i] = 0;
        }
        
        /*
        for(int i = 0; i < n ; i++){
            for(int j = 0; j < n ; j++){
                printf("%d ",G[j][i]);
            }
            printf("\n");
        }
        
        
        
		for (i=0;i<n;i++)
		{

 			G[i] = (int*)malloc(n*sizeof(int));

			for (j=0;j<n;j++)
			{
				fscanf(inst,"%d",&v);
				G[i][j] = v;
			}

		}
        */
		fclose(inst);
		//TESTE
		/*printf("\nVertices = %d \n", n);
		for (i=0;i<n;i++)
		{

			for (j=0;j<n;j++)
			{
				printf("%d ", G[i][j]);
			}
			printf("\n");
		}*/

}


//////////////CRIANDO AS VARIAVEIS//////////////

void carregarVariaveis(){

	int u,v, t;
	cont =0;
	      
	      
	      
		//variaveis para arestas (Z)
		
		variavelX = (int**)malloc(n*sizeof(int*));
       
		for (u = 0; u < n; u++)
		{
			variavelX[u] = (int*)malloc(m*sizeof(int));
			for(v = 0; v < m; v++)
			{
				variavelX[u][v] = cont;
				cont ++;
				//printf("%d ", variavelX[u][v]+1);
				
			} //printf("\n");
		}
        printf("\nVariavel X: %d\n",cont);  
        int numZ = cont;     
		variavelZ = (int**)malloc(n*sizeof(int*));
		for (u = 0; u < n; u++)
		{
			variavelZ[u] = (int*)malloc(m*sizeof(int));
			for(v = 0; v < m; v++)
			{
				variavelZ[u][v] = cont;
				cont ++;
				//printf("%d ", variavelZ[u][v]+1);
				
			} //printf("\n");
		}
		printf("\nVariavel Z: %d\n",cont-numZ);
		int numD = cont;
		variavelD = (int*)malloc(m*sizeof(int));
		for (t = 0; t < m; t++)
		{
			//if(G[u][v] != 0){
			variavelD[t] = cont;
			cont ++;
			//printf("%d ", variavelD[t]+1);
		}
		printf("\nVariavel D: %d\n",cont-numD);
		printf("\nVariaveis = %d \n", cont);

		
}


/////////////////////////////////////////// INICIALIZANDO CPLEX ///////////////////////////////////

void startCplex(char arq[]){

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

	int u,v, contador=0, i;

	for(u = 0; u < n; u++)
	{
		for(v = 0; v < m; v++)
		{
	        obj[contador] = 0; //troquei
			lb[contador] = 0.0;
			ub[contador] = 1.0;
			type[contador] = 'B';
			contador++;
		}
	}
	for(u = 0; u < n; u++)
	{
		for(v = 0; v < m; v++)
		{
	        obj[contador] = 0; //troquei
			lb[contador] = 0.0;
			ub[contador] = 1.0;
			type[contador] = 'B';
			contador++;
		}
	}
	
		for(i = 0; i < m; i++)
		{
			//if(G[u][i] != 0){
			    //printf("Var X%d",contador);
	        	obj[contador] = 1; //troquei
				lb[contador] = 0.0;
				ub[contador] = 1.0;
				type[contador] = 'B';
				contador++;
				//printf("%d ",obj[contador]);
			//}
		}//printf("\n");

    
	//chamadas do CPLEX para adicionar os vetores no modelo - lp
	status = CPXnewcols (env, lp, contador, obj, lb, ub, type, NULL);

	//só é necessario se for de minimização - max é padrão do cplex
	CPXchgobjsen(env, lp, CPX_MAX); // CPX_MIN, para o de miminização
}


///////////////////////////////////// RESTRICOES DA FORMULACAO ////////////////////////////////

// cada vertice deve ter grau no máximo 1

void addRestricao(int v){
      
    //printf("Rest u =%d v= %d\n", u, v);
	int  contador =0;
	int tam = n*m;
	double coef[tam];
	int col[tam];// col -id 
    int c = 0;
    
	for(c = 0; c < m; c++)
	{
	    //if(v > u && G[u][v] != 0){
		col[contador] = variavelX[v][c];
	        
	        coef[contador] = 1.0;
	        contador++;


	}
    
	int rows[2] = {0,contador}; // troquei 
	double b[1] = {1.0}; //troquei
	char sense[1] = {'E'}; //troquei

        CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
      
} 

void addRestricao2(int v, int w, int c){
    //printf("(%d %d %d) ",v,w,c);
            
    int  contador = 0;
	//int tam = n;
	int k = 0;
	/*
	printf("Conjunto...:");
	for(k = 0; k < tam ; k++){
	    printf("%d",v[k]);
	}
	*/  
	double coef[n];
	int col[n];// col -id 
    int i = 0;
    
	        
	       	col[contador] = variavelX[v][c];
	       	//printf("i = %d j = %d v = %d\n", i, j, col[contador]);
	        coef[contador] = 1.0;
	        contador++;
            
            col[contador] = variavelX[w][c];
	       	//printf("i = %d j = %d v = %d\n", i, j, col[contador]);
	        coef[contador] = 1.0;
	        contador++;	        
            
	

	int rows[2] = {0, contador}; // troquei 
	double b[1] = {1.0}; //troquei
	char sense[1] = {'L'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
      
    
}

int* Calculate_Neighborhood(int v){
    int *vertices = (int*)malloc(n*sizeof(int));
    int u, cont = 0;
    for (u = 0 ; u < n ; u++){
	    if(G[u][v] != 0) 
	        vertices[cont++] = u;
	}
	for (u = cont ; u < n ; u++) vertices[cont++] = -1;
	return vertices;
}

int SizeArray(int array[]){
    int u,size = 0;
    for (u = 0 ; u < n ; u++) {
        printf("%d ",array[u]);
        if(array[u] != -1) size++;
    }
    return size;
}

int* OtherColors(int c){
    int *colors = (int*)malloc((m-1)*sizeof(int));
    int u;
    for (u = 0 ; u < m ; u++){
        if(u != c) //printf("%d ~",u);
	    if(u != c) colors[cont++] = u;
	}
	//printf("\n");
	return colors;
}

void addRestricao3(int v, int c, int d){
    int  contador =0;
	int tam = n * m;
	double coef[tam];
	int col[tam];// col -id 
     
    int i = 0;
    int w = 0;
	
	    //for(c = 0; c < n; c++){
	       	col[contador] = variavelZ[v][c];
	       	coef[contador++] = 1.0;
	    //}
        
        int* vet = Calculate_Neighborhood(v);
        int index=0;
        
        for(w = 0; w < n; v++){
	       	if(vet[index] != -1){
	       	    col[contador] = variavelX[ vet[index++] ][d];
	       	    coef[contador++] = -1.0;
	       	}else break;
        }
        
	    col[contador] = variavelD[d];
	    coef[contador++] = 1.0;
    
	int rows[2] = {0, contador}; // troquei 
	double b[1] = {1.0}; //troquei
	char sense[1] = {'L'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
      
    
}


void addRestricao4(int c){
    int  contador = 0;
	//int tam = n;
	int k = 0;
	//printf("c = %d\n",c);
	/*
	printf("Conjunto...:");
	for(k = 0; k < tam ; k++){
	    printf("%d",v[k]);
	}
	*/  
	double coef[n];
	int col[n];// col -id 
    int v = 0;
        
	    col[contador] = variavelD[c];
	    coef[contador] = 1.0;
	    contador++;
	    int ck = c;
	    for(v = 0; v < n; v++){
	       	col[contador] = variavelZ[v][ck];
	       	//printf("v = %d c = %d col = %d\n", v, c, variavelX[v][c]);
	       	coef[contador] = -1.0;
	        contador++;
        }
	    
    
	int rows[2] = {0, contador}; // troquei 
	double b[1] = {0.0}; //troquei
	char sense[1] = {'L'}; //troquei

    CPXaddrows(env, lp, 0, 1, contador, b, sense, rows, col, coef, NULL, NULL);
      
}
void subConjunto(int n){
	int i,j,c = 0;
	for(i = 0 ; i < (1 << n) ; i++){
        printf("subconjunto %d: ",i);
        int coiso[n];
        for(j = 0 ; j < n ; j++){
            if((i & (1 << j))!= 0){
                coiso[c] = j;
                //printf("%d ",j);
                c++;
            }
        }
        //if(c > 2)addRestricao2(coiso, c);
        c = 0;
        printf("\n");
    }
}
//////////////////////////////////////////// RESOLUCAO /////////////////////////////////

void solveProblem(char arq1[], char arq2[]){


	int status = 0;

	out = fopen(arq1, "w");

	//gerando o .lp
	CPXwriteprob (env, lp, arq2, NULL);

	//RESOLVENDO :D :D :D \o \o \o
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

	for (u=0; u < n ; u++)
	{
		for (v=0; v < m ; v++)
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
	fprintf(out,"\n");
	for (u=0; u < n ; u++)
	{
		for (v=0; v < m ; v++)
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
	fprintf(out,"\n");
	for (v=0; v < m ; v++)
		{
			//if(G[u][v] != 0){
				fprintf(out, "%c", 'X');
				fprintf(out, "%d",  contador+1);
				//fprintf(out, "%d", (v+1));
				fprintf(out, "%c", '=');
				fprintf(out, "%f\n", vetor[contador]);
				contador++;
			//}
		}

	 fclose(out);
}

void addRestricoes(){
    
	int u, v, c, d;
	
    for (u=0; u < n; u++)
	{
		//for (v = u+1 ; v < n ; v++){
		    printf("Rest 1\n");
			addRestricao(u);
	    //}
	}
	for (u=0; u < n; u++)
	{
		for (v = u+1 ; v < n ; v++){
		    for (c = 0 ; c < m ; c++){
		        printf("Rest 2\n");
				if(G[u][v] != 0) addRestricao2(u,v,c);
	        }
	    }
	}
	
	for (v = 0 ; v < n ; v++){
        for (c = 0 ; c < m ; c++){
            for (d = 0 ; d < m ; d++){
                printf("Rest 3\n");
				if(c != d) addRestricao3(v, c, d);
	        }
	    }   
	}
	
	for (c = 0 ; c < m ; c++){
        printf("Rest 4\n");
		addRestricao4(c);
	}
	printf("Fim var\n");
}

void start(){
	seconds = 0.0;
	gettimeofday(&clockinit, &tz);
}
/*
//Pauses the clock
float pause(){
	gettimeofday(&clockend, &tz);
	seconds += ((float)(clockend.tv_sec - clockinit.tv_sec)) + ((float)(clockend.tv_usec - clockinit.tv_usec))/1000000;
	gettimeofday(&clockinit, &tz);
	return seconds;
}
*/
//Stop the clock
float stop(){
	gettimeofday(&clockend, &tz);
	seconds += ((float)(clockend.tv_sec - clockinit.tv_sec)) + ((float)(clockend.tv_usec - clockinit.tv_usec))/1000000;
	return seconds;
}


int main(){
    
	int valor = 0;
	int u, v, c, d;


	char *arq1 = "instancia.txt";

	char *arq2 = "log.txt";


	carregarGrafo(arq1);

	//carregando variaveis...
	carregarVariaveis();

	//inicializando cplex...
	startCplex(arq2);

	//adicionando restricoes da formulacao...
	printf("Var \n");
    addRestricoes();  
	
	/*
	for (c = 0 ; c < n ; c++){
        int *vet = Calculate_Neighborhood(c);
        printf("Vizinhança de %d: ",c);
        for (u = 0 ; u < n ; u++){
            if(vet[u] != -1)printf("%d ", vet[u]);
	    }
	    printf("\n");
	}
	*/
	int q[] = {0,1,2};
   
      // modelo está completo :D
      //subConjunto(n);
	char *arq3 = "arq3.txt";
	char *arq4 = "arq4.lp";
    printf("Tempo\n");
	start();
    printf("Resolvendo problema\n");
    solveProblem(arq3, arq4);
    printf("Problema resolvido\n");
    //Calculates the time elapsed...
    float elapsedtm;
    elapsedtm = stop();
    printf("....\n");
    printf("Elapsed Time: %f\n",elapsedtm);
	

///Escreva um programa para imprimir em ordem lexicográfica todos os subconjuntos do conjunto {1,..., n} . Para n=4
}
