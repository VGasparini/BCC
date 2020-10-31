#include <bits/stdc++.h>

using namespace std;

double foo(int *v, int n, int p){
	if (n<=0) return 0;
	int soma = 0;
	for(int i=0; i<n; i+=p) soma += v[i];
	return sqrt(soma) + foo(v, soma%n, p);
}

int main(){
	int v[] = {1,5,2,4,6,1,3,5,7,10};
	int n, p; cin >> n >> p;
	// n = tamanho vetor
	// p = passo
	cout << foo(v,n,p) << endl;
}

//Melhor caso: O(log n)
//Pior caso: O(n^2)
