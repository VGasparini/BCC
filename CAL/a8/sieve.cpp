#include <bits/stdc++.h>
#define MAX_N 500

using namespace std;

bool prime[MAX_N+1];

void sieve(){
    for(int i = 2; i <= (int)sqrt(MAX_N); i++)      
        if(prime[i] == false)                       
            for(int j = i*i; j <= MAX_N; j+=i)
                prime[j] = true;
}

int main(){
    prime[0] = true;
    prime[1] = true;
    sieve();
    cout << "Primos de 0 a " << MAX_N << endl; 
    for(int i = 0; i <= MAX_N; i++) !prime[i] ? cout << i << " " : cout << "";
    cout << endl;
}