
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#define LIM 100


void lerMatriz(FILE* file, int matriz[LIM][LIM], int matrizm, int matrizn);
void salvandoMatrizC(FILE* file,  pthread_t *threads, int maxSize, int bn);
void mutiplicacaoDasMatrizes(int* auxElements, int am, int bm, int an, int bn, int matrizA[LIM][LIM], int matrizB[LIM][LIM], pthread_t *threads, int count);
void printarMatriz(int m, int n, int matriz[LIM][LIM]);


//função de execução da thread
void *mutiplicacaoDosElementos(void* argument){ 
    int *auxElements = (int *)argument;
    int elementOfMatrixC = 0;
    
    //data[0] que é a coluna de A pois é a quantidade de linhas 
    int collumnOfA = auxElements[0];
    for (int i = 1; i <= collumnOfA; i++){
        elementOfMatrixC += auxElements[i]*auxElements[i+collumnOfA];
    }
    
    int *resultElement = (int*)malloc(sizeof(int));
        *resultElement = elementOfMatrixC;
   
    pthread_exit(resultElement);
}

int main(int argc, char *argv[]){
    

    FILE * file;

    int matrizA[LIM][LIM];
    int matrizB[LIM][LIM];

    int am, an, bm, bn, cm, cn;

    /*Lendo matriz A:*/
    file = fopen(argv[1], "r");
    fscanf(file,"%d %d",&am,&an);
    lerMatriz(file, matrizA, am, an);
    /*Lendo matriz B:*/
    file = fopen(argv[2], "r");
    fscanf(file,"%d %d",&bm,&bn);
    lerMatriz(file, matrizB, bm, bn);

    
    printf("Matriz A\n");
    /*mostrnado matriz A:*/    
    printarMatriz( am, an, matrizA);

    printf("Matriz B\n");
    /*mostrnado matriz A:*/  
    printarMatriz( bm, bn, matrizB);          
    
    
    int maxSize = am*bn;
    pthread_t *threads;
    threads = (pthread_t*)malloc(maxSize*sizeof(pthread_t));
    
    int count = 0;
    int* auxElements = NULL;
    if(an == bm){
        mutiplicacaoDasMatrizes(auxElements,  am,  bm,  an,  bn, matrizA,  matrizB, threads, count);
    }else{
        printf("Incompatilidade de Matriz");
    }


    
    /*salvando: C = A*B */
    file = fopen("Matriz_C_thread.txt","w");
    salvandoMatrizC(file, threads, maxSize, bn);
    free(auxElements);

    free(threads);
return 0;
}



void lerMatriz(FILE* file, int matriz[LIM][LIM], int matrizm, int matrizn){

  if(file != NULL) {
    for(int i = 0; i < matrizm; i++)
      for(int j = 0; j < matrizn; j++)
        fscanf(file,"%d",&matriz[i][j]);

    fclose(file);
  }else{
    printf("Erro em arquivo!");
  }
}


void salvandoMatrizC(FILE* file,  pthread_t *threads, int maxSize, int bn){

    printf("Matriz C\n");
    for (int i = 0; i < maxSize; i++){
        void *resultElementFromThread;
        
        pthread_join(threads[i], &resultElementFromThread);
                   
        int *resultElement = (int *)resultElementFromThread;
        printf(" %d",*resultElement);
        fprintf(file," %d", *resultElement);
        if ((i + 1) % bn == 0){
            printf("\n");
            fprintf(file,"\n");
        }
    }

    fclose(file);

    printf("Matriz C salva!");

}

void mutiplicacaoDasMatrizes(int* auxElements, int am, int bm, int an, int bn, int matrizA[LIM][LIM], int matrizB[LIM][LIM], pthread_t *threads,  int count){
    for (int i = 0; i < am; i++){
        for (int j = 0; j < bn; j++){
                
            //guardando as linhas e colunas das matrizes
            auxElements = (int *)malloc((20)*sizeof(int));

            //pegando a coluna na matriz A pois sera a quantidade de linhas da matriz C
            auxElements[0] = an;
    
            for (int k = 0; k < an; k++){
                auxElements[k+1] = matrizA[i][k];
               
               
            }
            for (int k = 0; k < bm; k++){
                auxElements[k+an+1] = matrizB[k][j];
                
               
            }
           
            pthread_create(&threads[count++], NULL, mutiplicacaoDosElementos, (void*)(auxElements));
                
        }
    }
}

void printarMatriz(int m, int n, int matriz[LIM][LIM]){
  for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
             
            printf(" %d",matriz[i][j]);
        }
        printf("\n");
    }
}
