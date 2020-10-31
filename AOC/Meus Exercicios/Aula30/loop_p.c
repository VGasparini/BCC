#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define TAM 64*127*5
#define ITERACOES_TESTE 100000

int main(){
	int i;
	long soma;
	int *vetor = calloc(TAM,sizeof(int));

	if(vetor == NULL){
		printf("Falha ao alocar memória");
		return -1;
	}

	/*for(int contador=0; contador < ITERACOES_TESTE; contador++){
		for(int i=0; i<TAM; i++){
			vetor[i] ++;
		}
	}*/

	for(int contador=0; contador < ITERACOES_TESTE; contador++){
		#pragma omp parallel num_threads(2)
		{//thread1 faz os pares
			if(omp_get_thread_num()==0){
				for(int i=0; i<TAM; i+=2){
					vetor[i] ++;
				}
			}else if(omp_get_thread_num()==1){//thread2 faz os ímpares
				for(int i=1; i<TAM; i+=2){
					vetor[i] ++;
				}
			}
		}
	}
	
	soma = 0;
	for(int i=0; i<TAM; i++){
		soma += vetor[i];
	}
	printf("%ld\n", soma);

	free(vetor);
	return 0;
}
