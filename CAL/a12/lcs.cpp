#include <bits/stdc++.h>

using namespace std;

string lcs(string X, string Y){
    int m = X.length();
    int n = Y.length();
    int L[m + 1][n + 1];

    for (int i = 0; i <= m; i++){
        for (int j = 0; j <= n; j++){
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    int index = L[m][n];
    string lcs;
    int i = m, j = n;
    
    while (i > 0 && j > 0){
        if (X[i - 1] == Y[j - 1]){
            lcs += X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main(){
    string a = "ACCUGTATAUCGUCACTU";
    string b = "GCAUTTC";
    cout << "Maior subsequencia comum entre " << a << " e " << b << " = " << lcs(a,b) << endl;
    return 0;
}