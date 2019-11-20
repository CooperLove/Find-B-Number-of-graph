#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


enum density {d1 = 10, d2 = 25, d3 = 50, d4 = 75, d5 = 90}densities;
static const enum density density_map[] = {d1,d2,d3,d4,d5};
enum nVertices {v1 = 7, v2 = 12, v3 = 16, v4 = 18, v5 = 21} numVert;
static const enum nVertices vertices_map[] = {v1,v2,v3,v4,v5}; 


void Generate_Graph(FILE* arq,int density, int numVertices){
    //printf("eoq\n");
    fprintf(arq,"\n\n");
    int random = 9999, numEdges = 0;
    if (density > 100){
        printf("Density must be between 0 and 100!"); exit(-1);
    }
    srand(time(NULL));
    for(int i = 0; i < numVertices; i++){
        for(int j = i + 1; j < numVertices; j++)
        {
            
            random = rand()%100;
            //printf("%d\n",random);
            if (random <= density && random > 0) {
                //printf("%d\n",random);
                fprintf(arq, "e %d %d\n",i+1,j+1);
                fprintf(arq, "e %d %d\n",j+1,i+1);
                numEdges+=2;
            }
        }   
    }
    rewind(arq);
    printf("%d %d\n", numVertices, numEdges);
    fprintf(arq,"%d %d\n", numVertices, numEdges);
    fflush(arq);
    return;
}

void MakeArqName(char *string, int i, int j){
    char arqName[20] = "";
    char a[10] = ""; sprintf(a, "%d", vertices_map[i]);
    char* under = "_";
    strcat(arqName, "graph"); strcat(arqName,a);
    strcat(arqName,under);
    sprintf(a, "%d", density_map[j]);strcat(arqName,a);
    strcat(arqName,".txt");
    
    strcpy(string, arqName);
    //printf("%s\n",string);
}

int main (int argc, char* argv){

    FILE *arq = fopen("\\graph00_0.txt", "a+");
    if (arq == NULL) {
        printf("Failure opening file!\n"); exit(EXIT_FAILURE);
    }
    
    for(size_t i = 0; i < 5; i++)
    {
        for(size_t j = 0; j < 5; j++)
        {
            char* fileName = (char*)malloc(sizeof(char));
            MakeArqName(fileName,i,j);
            
            //printf("%d %d = %s\n",vertices_map[i],density_map[j], fileName);
            arq = fopen(fileName, "w+");
            if (arq == NULL){
                printf("Failure opening file!\n"); //exit(EXIT_FAILURE);
            } 
            Generate_Graph(arq, density_map[j],vertices_map[i]);
            //fclose(arq);
        }
        printf("\n");
    }    
    fclose(arq);

    return 0;
}















