#include <stdio.h>
#define LIM 100

/*Arquivo Sequencial em linguagem c*/


void lerMatriz(FILE* file, int matriz[LIM][LIM], int matrizm, int matrizn);
void mutiplicacaoDasMatrizes(int an, int bm, int am, int bn, int cm, int cn, int matrizA[LIM][LIM], int matrizB[LIM][LIM], int matrizC[LIM][LIM]);
void salvandoMatrizC(FILE* file, int cm, int cn, int matrizC[LIM][LIM]);
void printarMatriz(int m, int n, int matriz[LIM][LIM]);


int main(int argc, char *argv[]){

  FILE * file;

  int matrizA[LIM][LIM];
  int matrizB[LIM][LIM];
  int matrizC[LIM][LIM];

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

     
  /*salvando: C = A*B */
  file = fopen("Matriz_C_sequencial.txt","w");
  if(an == bm){
    cm = am; 
    cn = bn;
    /*Multiplicação: C = A*B */
    mutiplicacaoDasMatrizes(an, bm, am, bn, cm, cn, matrizA, matrizB, matrizC);

    salvandoMatrizC(file, cm, cn, matrizC);
  }else{
    printf("Matrizes incompatíveis.\n");
  }

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

void mutiplicacaoDasMatrizes(int an, int bm, int am, int bn, int cm, int cn, int matrizA[LIM][LIM], int matrizB[LIM][LIM], int matrizC[LIM][LIM]){

  for(int i = 0; i < cm; i++){
    for(int j = 0; j < cn; j++){
      matrizC[i][j] = 0;
      for(int k = 0; k < an; k++){
        matrizC[i][j] += matrizA[i][k]*matrizB[k][j];
        
      }        
    }
  }
}


void salvandoMatrizC(FILE* file, int cm, int cn, int matrizC[LIM][LIM]){
  printf("Matriz C\n");
  if(file != NULL){
    fprintf(file,"%d %d\n",cm,cn);
    for(int i = 0; i < cm; i++){
      for(int j = 0; j < cn; j++){
        fprintf(file," %d",matrizC[i][j]);
        printf(" %d", matrizC[i][j]);
      }
    fprintf(file,"\n");
    printf("\n");
    }
    fclose(file);
    printf("Matriz C salva!");
  }else{
    printf("Erro em arquivo!");
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