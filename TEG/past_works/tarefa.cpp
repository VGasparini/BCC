#include <bits/stdc++.h>

using namespace std;

int main(){
  string s;
  vector<vector<int>> v;
  while(getline(cin,s)){
    stringstream ss(s);
    int t;
    vector<int> tmp;
    while(ss >> t){
        tmp.push_back(t);
    }
    v.push_back(tmp);
  }
  
  int matriz_adj[v.size()][v.size()] = {0};


  for(int i=0; i<v.size(); i++){
    for(auto j:v[i]) matriz_adj[i][j] = 1,matriz_adj[j][i] = 1;
  }

  for(int i=0; i<v.size(); i++){
    for(int j=0; j<v.size(); j++) cout << matriz_adj[i][j] << " ";
    cout << endl;
  }
}
