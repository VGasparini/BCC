/*
##############################
#      Lucas Meneghelli      #
#     Vinicius Gasparini     #
# Complexidade de Algoritmos #
#     Atividade 4 - Regua    #
##############################
*/


#include <bits/stdc++.h>

using namespace std;

vector<vector<float>> output;

void rulerRecursive( float first, float last, int height ){

    float mid;

    if( height > 0 ){

        mid = first + ( last - first ) / 2;
        output[height-1].push_back(mid);
        rulerRecursive( first, mid, height - 1 );
        rulerRecursive( mid, last, height - 1 );
    
    }
}

int main(int argc, char const *argv[]) {

    int height;
    float first, last;

    output.assign(height,vector<float>());

    cout << "Informe a altura: ";
    cin >> height;
    cout << "Informe a primeira posição: ";
    cin >> first;

    cout << "Informe a última posição: ";
    cin >> last;

    rulerRecursive( first, last, height );
    cout << endl;
    for(int i=0;i<height;i++){
        cout << "Altura " << i+1 << ": ";
        for(auto a:output[i]) cout << a << " ";
        cout << endl;
    }
    return 0;
}
