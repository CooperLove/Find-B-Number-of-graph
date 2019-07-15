#include <stdlib.h>
#include <stdio.h>
#include "struct.c"

#pragma region VarGlobais
int K = 3, N = 0, E = 0, size = -1, pos = 0;
int ch, n1 = -1, n2 = -1, vAtual = 1;
char end;
Set* ADJ[];
#pragma endregion

void AllocSet(int tam, FILE* file){
    Set* s = malloc( sizeof(Set) );
    s->neighboors  = malloc( sizeof(int)*tam );
    s->size        = tam;
    for (size_t i = 0; i < size; i++)
    {
        fscanf(file, "%c %d %d\n", &end, &n1, &n2);
        s->neighboors[i] = n2;
        //printf("%c %d %d\n",end,n1,n2);
        printf("%d ",s->neighboors[i]);
    }
    ADJ[pos++] = s;
    printf("]\n");
}
void PrintArray(){
    printf("\nPrinting array...\n");
    for (int i = 0; i < N; i++)
    {
        printf("V%d -> [",i+1);
        for (size_t j = 0; j < ADJ[i]->size; j++)
        {
            printf("%d ",ADJ[i]->neighboors[j]);
        }
        printf("]\n");
    }
}

int main (){
    FILE* file = fopen("entrada.txt", "r");
    FILE* output = fopen("output.txt", "w+");
    if (file == NULL || output == NULL) {
        printf("Cannot open file!\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(file, "%d %d", &N, &E);
    printf("N,V = %d, E = %d, K = %d\n",N, E, K);

    while(fscanf(file, "%c %d %d\n", &end, &n1, &n2) != EOF){
        if (vAtual != n1 && n1 != -1) {
            fprintf(output, "%d\n", size); 
            vAtual = n1; size = 1;
        }
        else size++;
    }
    fprintf(output, "%d\n", size); 
    //ADJ = malloc( sizeof(Set)*N );
    for (int i = 0; i < N; i++) ADJ[i] = malloc( sizeof(Set) );
    
    rewind(file); fscanf(file, "%d %d\n", &N, &E);
    rewind(output);
    int i = 1;
    while(fscanf(output, "%d", &size) != EOF){
        printf("Vertice = %d -> [",i++);
        AllocSet(size, file);
    }

    PrintArray();
    

    fclose(file);
    return(EXIT_SUCCESS);
}
/*
        ADJ[posI]      = malloc( sizeof(Set) );
        Set* s         = malloc( sizeof(Set) );
        s->neighboors  = malloc( sizeof(int)*size );
        s->size        = size;
        printf("Size array = %d \n",s->size);
        for (size_t i = 0; i < size; i++){
            s->neighboors[i] = ch;
            printf("%d ",s->neighboors[i]);
            ch = fgetc(file);
        }
        ADJ[posI] = s;
        printf("\n");
 */