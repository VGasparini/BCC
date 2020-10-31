#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define TAM 64*127*5
#define ITERACOES_TESTE 100000

int main(){
  int i,contador;
  long soma;
  int *vetor = calloc(TAM,sizeof(int));

  if(vetor == NULL){
    printf("Falha ao alocar memória");
    return -1;
  }

  for(contador=0; contador < ITERACOES_TESTE; contador++){
    #pragma omp parallel num_threads(2)
    {//thread1 faz a primeira metade
      if(omp_get_thread_num()==0){
        for(int i=0; i<TAM/2; i++){
          vetor[i] ++;
        }
      }else if(omp_get_thread_num()==1){//thread2 faz a segunda metade
        for(int i=TAM/2; i<TAM; i++){
          vetor[i] ++;
        }
      }
    }
  }
  
  soma = 0;
  for(i=0; i<TAM; i++){
    soma += vetor[i];
  }
  printf("%ld\n", soma);

  free(vetor);
  return 0;
}
