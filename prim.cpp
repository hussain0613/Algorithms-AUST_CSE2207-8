/*
implementation of Prims's algorithm for finding Minimum Spanning Tree

test1_input:
9 14
0 1 4
0 7 8
1 2 8
1 7 11
2 3 7
2 5 4
2 8 2
3 4 9
3 5 14
4 5 10
5 6 2
6 7 1
6 8 6
7 8 7

test1_output:
Edges in the MST: (one among possible multiple correct answers)
B A 4
C B 8
D C 7
E D 9
F C 4
G F 2
H G 1
I C 2


Total weight: 37
*/

#include<bits/stdc++.h>

using namespace std;

typedef vector<vector<int>> matrix;

void print_matrix(matrix mat)
{
    for(int r = 0; r < mat.size(); ++r){
        for(int c = 0; c < mat.at(r).size(); ++c){
            int val = mat.at(r).at(c);
            if(val == INT_MAX) cout << "inf ";
            else cout << val << " ";
        }
        cout << endl;
    }
}


int n, e; // # of nodes and # of edges
matrix GRAPH;

void read_input()
{
    GRAPH.clear();

    scanf("%d%d", &n, &e);

    for(int i = 0; i < n; ++i){
        vector<int> row;
        for(int j = 0; j < n; ++j){
            row.push_back(INT_MAX);
        }
        GRAPH.push_back(row);
    }

    for(int i=0; i<e; ++i){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        GRAPH.at(u).at(v) = w;
        GRAPH.at(v).at(u) = w; // for undirected graphs
    }
}

pair<vector<int>, vector<int>> prim(matrix graph)
{
    vector<int> parents, keys, Q;

    for(int i = 0; i < graph.size(); ++i){
        parents.push_back(-1);
        keys.push_back(INT_MAX);
        Q.push_back(i);
    }

    keys.at(0) = 0;

    while(Q.size()){

        // extract min
        int u = Q.at(0);
        vector<int>::iterator itr, u_itr = Q.begin();

        for(itr = Q.begin(); itr != Q.end(); ++itr){
            if(keys[*itr] < u) {
                u = *itr;
                u_itr = itr;
            }
        }
        Q.erase(u_itr);
        // end of extract min


        for(int v = 0; v < graph.at(u).size(); ++v){
            int w = graph.at(u).at(v);
            if(find(Q.begin(), Q.end(), v) != Q.end() && w < keys.at(v)){
                parents.at(v) = u;
                keys.at(v) = w;
            }
        }
    }

    pair<vector<int>, vector<int>> ans;
    ans.first = parents;
    ans.second = keys;

    return ans;
}


int main()
{
    freopen("input__ignore__.txt", "r", stdin);

    read_input();

    printf("Graph(%d): \n", GRAPH.size());
    print_matrix(GRAPH);

    pair<vector<int>, vector<int>> ans = prim(GRAPH);
    int t_w = 0;

    printf("\n\nEdges in the MST: \n");
    for(int i = 1; i < ans.first.size(); ++i){
        printf("%c %c %d\n", i+'A' , ans.first.at(i)+'A', ans.second.at(i));
        t_w += ans.second.at(i);
    }
    printf("\n\nTotal weight: %d\n", t_w);

    return 0;
}


