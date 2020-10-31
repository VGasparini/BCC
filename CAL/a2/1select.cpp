#include <bits/stdc++.h>

using namespace std;

//for i in `seq 1 10`; do time ./a.exe file.txt; done

void selectionSort(vector<long int> v, int n){
    int i, j, x, aux;
    for (i = 0; i < n; i++){
        x = i;
        for (j = i+1; j < n; j++){
            if( v[j] < v[x] )
            x = j;
        }
        aux = v[i];
        v[i] = v[x];
        v[x] = aux;
    }
}

int main(int argc, char const *argv[]) {

    setbuf( stdout, NULL );

    if( argc != 2 ){
        cout << "\n Informe apenas o arquivo de leitura como parâmetro.\n";
        return 0;
    }

    string   line;
    ifstream file( argv[1] );
    long int cont = 0;
    istream& s = file;
    vector<long int> vetor;

	while( getline( s, line ) ){
        vetor.push_back( stoi( line ) );
        cont++;
    }

    selectionSort( vetor, cont );

    return 0;
}
