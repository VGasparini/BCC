/*
##############################
#      Lucas Meneghelli      #
#     Vinicius Gasparini     #
# Complexidade de Algoritmos #
#   Atividade 3 - Fibonacci  #
##############################
*/


#include <bits/stdc++.h>

using namespace std;

long long fib(int n){
    if(n==0) return 0;
    if(n==1) return 1;
    else{
        return fib(n-1)+fib(n-2);
    }
}

int main(){
    int n;
    cout << "Digite n: ";
    cin >> n;
    cout << "fib(n) = " << fib(n) << endl;
}
