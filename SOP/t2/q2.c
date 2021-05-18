/* 
Vinicius Gasparini
Ex 1 - Programa para mostrar sincronizacao e concorrencia de threads. 
*/

#include <stdio.h>

typedef struct Mapping { 
    int f;
    int v;
} mapping;

void traduz(mapping* tabpag, int el, int sz){
    int p = el / sz;
    int d = el % sz;
    printf("p= %d\n",p);
    printf("d= %d\n",d);
    if(tabpag[p].v){
        printf("f= %d\n",tabpag[p].f);
        printf("EF= %d\n",tabpag[p].f * sz + d);
    } else {
        printf("Page fault!");
    }
}

int main(void){
    int sz = 8192;
    int el;

    mapping tabpag[8];
    tabpag[0].f = 6; tabpag[0].v = 1;
    tabpag[1].f = 7; tabpag[1].v = 1;
    tabpag[2].f = 3; tabpag[2].v = 0;
    tabpag[3].f = 3; tabpag[3].v = 1;
    tabpag[4].f = 0; tabpag[0].v = 1;
    tabpag[5].f = 1; tabpag[5].v = 0;
    tabpag[6].f = 9; tabpag[6].v = 1;
    tabpag[7].f = 4; tabpag[7].v = 0;

    while(scanf("%d",&el) != EOF){
        traduz(tabpag, el, sz);
    }
}