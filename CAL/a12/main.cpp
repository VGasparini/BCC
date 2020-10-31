#include <bits/stdc++.h>
#include <cstring>

using namespace std;

string disciplines[] = { " ", "ALP ", "CAL ", "REC ", "TEC ", "PAP ", "BAN ", "PPR ", "SOP " };
int matrix[9][17];
string matrixDisc[9][17];
int values[] = {0,5,6,5,6,3,4,2,4};
int weights[] = {99,3,6,9,8,5,4,3,4};
int best = -1;

int calcMatrix(int i, int j){
    int aux1, aux2;
    if(weights[i] > j){
        return 0;
    }else{
        aux1 = calcMatrix( i-1, j );
        aux2 = calcMatrix( i-1,  j-weights[i] ) + values[i];
        if( aux1 > aux2 ){
            matrix[i][j] = aux1;
            matrixDisc[i][j] = matrixDisc[i-1][j];
        }else{
            matrix[i][j] = aux2;
            matrixDisc[i][j] = matrixDisc[i-1][j-weights[i]];
            matrixDisc[i][j].append(disciplines[i]);
        }

        if(matrix[i][j] > best)
            best = matrix[i][j];

        //matrix[i][j] = max( calcMatrix( i-1, j ), calcMatrix( i-1,  j-weights[i] ) + values[i] );
        return matrix[i][j];
    }
}

int main(){

    // inicializando matrizes
    memset(matrix, 0, sizeof(matrix));

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 17; j++){
            matrixDisc[i][j] = "";
        }
    }

    calcMatrix(8, 16);

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 17; j++){
<<<<<<< HEAD
            printf("%3d", matrix[i][j]);
=======
            printf("%d\t", matrix[i][j]);
>>>>>>> 1fb459e7a8e5b00a5e5ca80f3bd7abb3718d2c8a
        }
        printf("\n");
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 17; j++){
            if(matrix[i][j] == best)
                printf("Solucao otimizada [%d][%d] = %s\n", i, j, matrixDisc[i][j].c_str());
        }
    }

    return 0;
}
