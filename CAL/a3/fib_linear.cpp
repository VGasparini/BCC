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
    long long dp[n+2];
    dp[0] = 0;
    dp[1] = 1;
    for(int i=2; i<=n; i++)
        dp[i] = dp[i-1]+dp[i-2];
    return dp[n];
}

int main(){
    int n;
    cout << "Digite n: ";
    cin >> n;
    cout << "fib(n): " << fib(n) << endl;
}
