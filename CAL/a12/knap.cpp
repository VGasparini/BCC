#include <bits/stdc++.h>

using namespace std;

set<string> ans;
string disciplines[] = {" ", "ALP ", "CAL ", "REC ", "TEC ", "PAP ", "BAN ", "PPR ", "SOP "};

int knapSack(int T, vector<int> is, vector<int> ch, int n){
    
    int i, t;
    int K[n + 1][T + 1];
    for (i = 0; i <= n; i++){
        set<string> tmp;
        for (t = 0; t <= T; t++){
            if (i == 0 || t == 0)
                K[i][t] = 0;
            else if (is[i - 1] <= t)
                K[i][t] = max(ch[i - 1] + K[i - 1][t - is[i - 1]] , K[i - 1][t] );
            else
                K[i][t] = K[i - 1][t];
        }
    }

    cout << "Matriz solucao" << endl;
    for (int i = 0; i < n + 1; i++){
        for (int j = 0; j < T + 1; j++)
            printf("%3d ", K[i][j]);
        cout << endl;
    }

    int w = T;
    int best = K[n][T];
    for (i = n; i > 0 && best > 0; i--) {
        if (best == K[i - 1][w])
                continue;
        else{
            ans.insert(disciplines[i - 1]);
            best = best - ch[i - 1];
            w = w - is[i - 1];
        }
    }

    return K[n][T];
}


int main() {
    vector<int> ch = {0, 5, 6, 5, 6, 3, 4, 2, 4};
    vector<int> is = {99, 3, 6, 9, 8, 5, 4, 3, 4};
    int t = 16;
    int n = ch.size();
    int best = knapSack(t, is, ch, n);
    cout << "Is maximo = " << best << endl;
    cout << "Disciplinas = ";
    for (auto i : ans)
        cout << i << " ";
    return 0;
}