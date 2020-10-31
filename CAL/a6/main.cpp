#include<bits/stdc++.h>
#define MAX_N 100005

using namespace std;

int main(int argc, const char** argv) {
    
    int n; cin >> n;
    int vec[MAX_N];
    memset(vec,0,sizeof(vec));
    vector<int> sortedVec;

    for( int i = 0; i < MAX_N; i++ ){
        int x; cin >> x;
        vec[x]++;
    }

    for( int i = 0; i < MAX_N; i++ ){
        while( vec[i] ){
            sortedVec.push_back( i );
            vec[i]--;
        }
    }

    for( auto n:sortedVec ){
        cout << n << endl;
    }

    return 0;
}