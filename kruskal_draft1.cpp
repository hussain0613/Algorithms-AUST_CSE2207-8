#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

class Edge{
    public:
    int w, u, v;

    bool operator<(const Edge& other){
        return this->w < other.w;
    }
};

int n, e; // # of nodes and # of edges
vector<Edge> edges;

void read_input()
{
    scanf("%d%d", &n, &e);
    for(int i=0; i<e; ++i){
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        Edge edge;
        edge.u = u;
        edge.v = v;
        edge.w = w;

        edges.push_back(edge);
    }
}

vector<Edge> kruskal()
{
    vector<Edge> A;
    vector<int> S;
    for(int i=0; i<n; ++i){
        S.push_back(i); // make_set
    }
    sort(edges.begin(), edges.end());
    for(int i = 0; i<edges.size(); ++i){
        Edge edge = edges.at(i);
        int us = S.at(edge.u); // find set
        int vs = S.at(edge.v);
        if( us != vs){
            A.push_back(edge);
            // union
            for(int i =0; i<n; ++i){
                if(S.at(i) == vs) S.at(i) = us;
            }
        }
    }
    return A;
}


int main()
{
    freopen("input__ignore__.txt", "r", stdin);

    read_input();

    printf("Edges: \n");
    for(int i = 0; i<e; ++i){
        printf("%c %c %d\n", edges.at(i).u+'A', edges.at(i).v+'A', edges.at(i).w);
    }

    vector<Edge> ans = kruskal();
    int t_w = 0;

    printf("\n\nAns: \n");
    for(int i = 0; i<ans.size(); ++i){
        printf("%c %c %d\n", ans.at(i).u+'A' , ans.at(i).v+'A', ans.at(i).w);
        t_w += ans.at(i).w;
    }
    printf("\n\nTotal weight: %d", t_w);

    return 0;
}

