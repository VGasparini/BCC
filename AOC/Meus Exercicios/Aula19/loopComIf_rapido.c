#include<stdio.h>
#include<stdlib.h>

//Vetor ocupa 4GiB de RAM
//Não rode em máquinas com pouca memória!
#define TAM 1073741824

int main(){
	int i;
	int *vetor = malloc(TAM * sizeof(int));
	if(vetor == NULL) return -1;
	for(i=0; i<TAM; i+=2){
		vetor[i+1] = 1;
		vetor[i] = 2;
	}

	//for(int i=0; i < TAM; i++)
	//	printf("%d ", vetor[i]);
	free(vetor);
	return 0;
}
