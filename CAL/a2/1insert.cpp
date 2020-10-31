#include <bits/stdc++.h>

using namespace std;

//for i in `seq 1 10`; do time ./a.exe file.txt; done

void insercao(vector<long int> v, int n){
    int i, j, x;
    for (i = 1; i < n; i++){
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
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

    insercao( vetor, cont );

    return 0;
}
