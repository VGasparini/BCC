#include<stdio.h>

//Atenção: a matriz ocupa cerca de 4,6GiB de memória
#define M 35000

int mat[M][M];

int main(){
	for(int i =0; i < M; i++){
		for (int j=0;j<M;j++){
			mat[i][j]=1;
		}
	}

	/*
	//imprimindo a matriz
	for(int i =0; i < M; i++){
		for (int j=0;j<M;j++){
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
	*/

	printf("Fim!");

	return 0;
}
