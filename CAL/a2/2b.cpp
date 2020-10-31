/*
##############################
#      Lucas Meneghelli      #
#     Vinicius Gasparini     #
# Complexidade de Algoritmos #
#  Atividade 2b - Matrizes   #
##############################
*/

#include <bits/stdc++.h>

using namespace std;

void multiplica_matriz(vector<vector<int>> matriz_a, vector<vector<int>> matriz_b, int n)
{

    vector<vector<int>> matriz_ans;
    matriz_ans.assign( n, vector<int>( n, 0 ) );

    for( int i = 0; i < n; i++ ) {

      int k = 0;
      for( int j = 0; j < n; j++ ) {

        matriz_ans[i][k] += matriz_a[k][j] * matriz_b[j][i];
        k++;

      }

    }

    for( int i = 0; i < n; i++ ) {

      for( int j = 0; j < n; j++ ) {
          cout << matriz_ans[i][j] << " ";
      }

      cout << endl;

    }

}

int main(int argc, char const *argv[])
{
    int n;

    cout << "Algoritmo b:" << endl;

    cout << "Informe a ordem das matrizes quadradas: ";
    cin >> n;

    vector<vector<int>> matriz_a, matriz_b;
    matriz_a.assign( n, vector<int>( n, 0 ) );
    matriz_b.assign( n, vector<int>( n, 0 ) );

    cout << "Informe os " << n*n << " valores da matriz a:" << endl;

    for( int i = 0; i < n; i++ ) {

      for( int j = 0; j < n; j++ ) {
        int x;
        cout << "Valor " << i + 1 << "." << j + 1 << ": ";
        cin >> x;
        matriz_a[i][j] = x;
      }

    }

    cout << "Informe os " << n*n << " valores da matriz b:" << endl;

    for( int i = 0; i < n; i++ ) {

      for( int j = 0; j < n; j++ ) {
        int x;
        cout << "Valor " << i + 1 << "." << j + 1 << ": ";
        cin >> x;
        matriz_b[i][j] = x;
      }

    }

    multiplica_matriz( matriz_a, matriz_b, n );

    return 0;
}
