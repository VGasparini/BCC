#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct futebol{
	/*
  This struct are used to describe a match
  */
	char teamA[15];
	char teamB[15];
	int scoreA, scoreB, day, month, year, audience;
	char local[20];
}Futebol;

char names[5][15] = {"Real Madrid","Barcelona","PSG","Liverpool","JEC"};
char locals[5][25] = {"Santiago Bernabeu","Camp Nou","Parc des Princes","Anfield","Arena Joinville"};

void createBySize(FILE *fp);
void createByInstance(FILE *fp);
void createAndStores(FILE *fp);
void shows(FILE *fp);

int main(void){
	srand(time(NULL));
	int op;
	FILE *fp;
	printf("Selecione modo de funcionamento\n----------\n\n1 - Limitar por tamanho\n2 - Limitar por partida(s)\n3 - shows na tela\n\n-> ");
	scanf("%d", &op);
	switch (op) {
		case 1:
			fp = fopen("data.txt", "w");
			createBySize(fp);
			fclose(fp);
			break;
		case 2:
			fp = fopen("data.txt", "w");
			createByInstance(fp);
			fclose(fp);
			break;
		case 3:
			fp = fopen("data.txt", "rt");
			shows(fp);
			fclose(fp);
			break;
	}
	return 0;
}


void createAndStores(FILE *fp){
	/*
	This function simulates a random match and stores in @arq
	*/
	Futebol aux;
	strcpy(aux.teamA,names[(rand()%5)]);
	strcpy(aux.teamB,names[(rand()%5)]);
	do{
		if(strcmp(aux.teamA,aux.teamB) == 0)
				strcpy(aux.teamB,names[(rand()%5)]);
	}while(strcmp(aux.teamA,aux.teamB) == 0);
			strcpy(aux.local,locals[rand()%5]);
			aux.scoreA = rand()%9;
			aux.scoreB = rand()%9;
			aux.day = rand()%30;
			aux.month = rand()%12;
			aux.year = 2017;
			aux.audience = rand()%100000;
	fprintf(fp,"%s;%d;%s;%d;%s;%d;%d/%d/%d\n", aux.teamA,aux.scoreA,aux.teamB,aux.scoreB,aux.local,aux.audience,aux.day,aux.month,aux.year);
}


void createBySize(FILE *fp){
	/*
  This function generates a file until size @limit is reached
  */
	int bytes = 0, size = 0, i = 0;
	char unit;
	printf("Informe o tamanho desejado (Bytes, KB, MB ou GB)\n ->");
	scanf("%d %c", &size, &unit);
	switch (unit){
		case 'B':
			bytes = (int)(size)/51;
			break;
		case 'K':
			bytes = (int)(size * 1024)/51;
			break;
		case 'M':
			bytes = (int)(size * 1048576)/51;
			break;
		case 'G':
			bytes = (int)(size * 1073741824)/51;
			break;
		default:
			printf("Opcao invalida... Saindo\n");
			return;
	}
	clock_t begin = clock();
	for(i = 0; i < bytes; i++) createAndStores(fp);
	printf("Tempo de execucao: %.4lf\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
}


void createByInstance(FILE *fp){
	/*
  This function generates a file until instances @limit is reached
  */
	int i = 0, limit = 0;
	printf("Informe a quantidade de instancias\n ->");
	scanf("%d", &limit);
	clock_t begin = clock();
	for(i ; i < limit; i++) createAndStores(fp);
	printf("Tempo de execucao: %.4lf\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
}


void shows(FILE *fp){
	char line[100];
	char *result;
	while (!feof(fp)){
		result = fgets(line, 100, fp);
		if (result)	printf("%s\n",line);
  }
}
