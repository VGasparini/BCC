#include <bits/stdc++.h>

using namespace std;

// for i in `seq 1 10`; do time ./a.exe file.txt; done
// { time ./a.exe file.txt; } 2> time.txt
// { for i in `seq 1 10`; do time ./bubble.exe file.txt; done } 2> bubble.txt;{ for i in `seq 1 10`; do time ./insert.exe file.txt; done } 2> insert.txt;{ for i in `seq 1 10`; do time ./select.exe file.txt; done } 2> select.txt;{ for i in `seq 1 10`; do time ./bubble.exe fileOrd.txt; done } 2> bubbleOrd.txt;{ for i in `seq 1 10`; do time ./insert.exe fileOrd.txt; done } 2> insertOrd.txt;{ for i in `seq 1 10`; do time ./select.exe fileOrd.txt; done } 2> selectOrd.txt

void bubble(vector<long int> v, int n){

    int i, j, aux;
    for (i = n - 1; i > 0; i--){
        for (j = 0; j < i; j++){
            if (v[j] > v[j+1]){
                aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
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

    bubble( vetor, cont );

    return 0;
}
