/*
##############################
#     Vinicius Gasparini     #
# Complexidade de Algoritmos #
#  Atividade 1 - Ocorrência  #
##############################
*/

#include <bits/stdc++.h>
#define MAXN 1000006

using namespace std;

map<long long, int> count_map; // std::map implementa uma árvore rubro-negra balanceada.

int main(){
    int n; scanf("%d",&n);
    for(int i = 0; i<n; i++){
        long long x; scanf("%lld",&x);
        if(count_map.count(x) == 0) count_map[x] = 1;
        else count_map[x]++;
    }
    long long seek; scanf("%lld",&seek);
    printf("Foram registrados %lld repeticoes do numero %lld\n",count_map[seek],seek);
}
