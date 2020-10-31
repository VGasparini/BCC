// http://www.cs.umsl.edu/~sanjiv/classes/cs5130/lectures/bb.pdf
// https://www2.seas.gwu.edu/~bell/csci212/Branch_and_Bound.pdf

#include <bits/stdc++.h>
using namespace std;
#define N 3

struct Node{
    Node *parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

Node *newNode(int mat[N][N], int x, int y, int newX,
              int newY, int level, Node *parent){
    Node *node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

int calculateCost(int initial[N][N], int final[N][N]){
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}

int isSafe(int x, int y){
    return (x >= 0 && x < N && y >= 0 && y < N);
}

int pathCount(Node *root){
    if (root == NULL)
        return 1;
    return 1+pathCount(root->parent);
}

struct comp{
    bool operator()(const Node *lhs, const Node *rhs) const{
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

int solve(int initial[N][N], int x, int y,
           int final[N][N]){
    priority_queue<Node *, std::vector<Node *>, comp> pq;

    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);

    pq.push(root);
    while (!pq.empty()){
        Node *min = pq.top();
        pq.pop();
        if (min->cost == 0){
            return pathCount(min);
        }

        for (int i = 0; i < 4; i++){
            if (isSafe(min->x + row[i], min->y + col[i])){
                Node *child = newNode(min->mat, min->x,
                                      min->y, min->x + row[i],
                                      min->y + col[i],
                                      min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }
    }
}

int main(){
    int initial[N][N];
    int x,y;

    cout << "Defina o jogo inicial" << endl;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++){
            int t;
            cin >> t;
            initial[i][j]=t;
            if(not t) x=i,y=j;
        }

    int final[N][N] ={
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 0}};
    
    cout << endl << "São necessários " << solve(initial, x, y, final) - 1 << " movimentos para completar o jogo" << endl;

    return 0;
}