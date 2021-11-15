#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*Arquivo Auxiliar para criar 2 Matrizer randomicas*/

void criar_matriz(FILE *file, int n, int m){  //Função responsavel por criação de matrizes

  fprintf(file, "%d %d \n", n, m);
  
  for(int ii=0;ii<n; ii++){
    for(int hh=0; hh<m; hh++){
      fprintf(file, "%d ", rand() % 10);    //Loop que preenche matriz com numeros de 0 até 10
    }
    fprintf(file, "\n");
  }
}

int main(int argc, char *argv[]){

  void criar_matriz(FILE *file, int n, int m);

  int n1, m1, n2, m2;    //atribuição da quantidade de linhas e colunas
  n1=atoi(argv[1]);
  m1=atoi(argv[2]);
  n2=atoi(argv[3]);
  m2=atoi(argv[4]);

  srand(time(NULL));    //semente para geração de numeros (tempo)

  FILE *file1, *file2;  //Criando ponteiros dos arquivos
  file1 = fopen("Matriz_1.txt","w");
  file2 = fopen("Matriz_2.txt","w");

  criar_matriz(file1, n1, m1);  //chamando função criar matriz
  criar_matriz(file2, n2, m2);

  fclose(file1);  //fechando os arquivos
  fclose(file2);

  return 0;
}