/* 
Vinicius Gasparini
Ex 3 - Programa para simular um escalonador de disco
Para emular o comportamento requisitado, foi utilizado
um conceito de "fila de prioridades" que sempre se mantém
ordenada. A cada nova inserção, é verificado e se possivel
unido consultas adjacentes de mesmo modo que não excedam 64 blocos 
*/

#include <stdio.h>
#include <stdlib.h>
#include "requests.h"

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

int main()
{
	Request *requests = NULL;

	int initial_block = 1, blocks_qtd;
	char mode;

	while (initial_block >= 0)
	{
		scanf("%d", &initial_block);
		if (initial_block >= 0)
		{
			scanf("%d %c", &blocks_qtd, &mode);
			if (blocks_qtd > 1 && blocks_qtd <= MAX_BLOCKS_ALLOWED)
			{
				if (mode == 'w' || mode == 'r')
				{
					requests = push(&requests, initial_block, blocks_qtd, mode);
				}
				else
				{
					printf("Request mode invalid\n");
				}
			}
			else
				printf("Block \n");
		}
	}

	printf("Fila:\n");
	show(&requests);

	return 0;
}