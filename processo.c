#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include<stdlib.h>

#define LIM 100

void lerMatriz(FILE* file, int matriz[LIM][LIM], int matrizm, int matrizn);
int mutiplicacaoDosElementos(int * auxElements);
void mutiplicacaoDasMatrizes(int* auxElements, int am, int bm, int an, int bn, int matrizA[LIM][LIM], int matrizB[LIM][LIM], pid_t *processos, FILE* file, int maxSize);
void printarMatriz(int m, int n, int matriz[LIM][LIM]);

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
    pid_t processos[maxSize];
    file = fopen("Matriz_C_processo.txt","w");
    
    int count = 0;
    int* auxElements = NULL;
    if(an == bm){
  	  printf("Matriz C\n");
  	  for (int i = 0; i < maxSize; i++){
    	  processos[i] = fork();

			  if(processos[count] == 0){
        mutiplicacaoDasMatrizes(auxElements,  am,  bm,  an,  bn, matrizA,  matrizB, processos, file, maxSize);
        exit(0);
      	}else{
      		pid_t status = wait(NULL);
      		exit(0);
      	}
      }

    }else{
        printf("Incompatilidade de Matriz");
    }
    fclose(file);
    free(auxElements);

    
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

//função de execução da thread
int mutiplicacaoDosElementos(int * auxElements){ 
    int elementOfMatrixC = 0;
    
    //data[0] que é a coluna de A pois é a quantidade de linhas 
    int collumnOfA = auxElements[0];
    for (int i = 1; i <= collumnOfA; i++){
        elementOfMatrixC += auxElements[i]*auxElements[i+collumnOfA];
    }

   return elementOfMatrixC;
   
}

void mutiplicacaoDasMatrizes(int* auxElements, int am, int bm, int an, int bn, int matrizA[LIM][LIM], int matrizB[LIM][LIM], pid_t *processos,FILE* file, int maxSize){
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

			    int resultElement = mutiplicacaoDosElementos(auxElements);
			    printf(" %d",resultElement);
			    fprintf(file," %d", resultElement);
             
			}
			fprintf(file,"\n");
   		printf("\n");

    }

   printf("Matriz C salva!");


}


void printarMatriz(int m, int n, int matriz[LIM][LIM]){
  for (int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
             
            printf(" %d",matriz[i][j]);
        }
        printf("\n");
    }
}