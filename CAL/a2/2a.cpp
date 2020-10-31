/*
##############################
#      Lucas Meneghelli      #
#     Vinicius Gasparini     #
# Complexidade de Algoritmos #
#   Atividade 2a - Potencia  #
##############################
*/


#include <bits/stdc++.h>

using namespace std;

long long exp(long a, long b)
{
    long long ans = 1;
    int count = 0;

    for(; count < b; ans*=a, count++);

    return ans;
}

int main(int argc, char const *argv[])
{
    long a, b;

    cout << "Algoritmo a:" << endl;

    cout << "Informe a:";
    cin >> a;

    cout << "Informe b:";
    cin >> b;

    cout << exp(a,b) << endl;

    return 0;
}
