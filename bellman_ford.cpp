#include<stdio.h>
#include<bits/stdc++.h>

using std::vector;
using std::pair;
using std::make_pair;
using std::stack;

#define INPUT_FILE_NAME "input__ignore__.txt"
#define INF INT_MAX // pseudo infinity

int SIZE;

vector<vector<pair<int, int>>> graph; // adjacency list with weight
vector<int> edges[3];
vector<int> predecessors, distances;


void graph_input() // weighted and directed
{
    FILE *file = fopen(INPUT_FILE_NAME, "r");
    //FILE *file = stdin;

    int edge_count;

    int src, dest, wght;

    fscanf(file, "%d%d", &SIZE, &edge_count);
    //printf("size: %d edge_count: %d\n", SIZE, edge_count);

    for(int i =0; i<SIZE; ++i){
        graph.push_back(vector<pair<int, int>>());
    }
    //printf("initiated \n");

    for(int i = 0; i<edge_count; ++i){
        fscanf(file, "%d%d%d", &src, &dest, &wght);
        //printf("src: %d, dest: %d, wght: %d\n", src, dest, wght);
        graph.at(src).push_back(make_pair(dest, wght));

        edges[0].push_back(src);
        edges[1].push_back(dest);
        edges[2].push_back(wght);
    }
}

void print_graph()
{
    for(int i = 0; i<graph.size(); ++i){
        printf("%d -> ", i);
        for(int j = 0; j<graph.at(i).size(); ++j){
            printf("(%d, %d) ", graph.at(i).at(j).first, graph.at(i).at(j).second);
        }
        printf("\n");
    }
}

void initialize()
{
    for(int i =0; i< SIZE; ++i){
        predecessors.push_back(-1);
        distances.push_back(INF);
    }
}


bool bellman_ford(int root)
{
    distances.at(root) = 0;

    for(int i = 0; i<SIZE; ++i){
        for(int j = 0; j<edges[0].size(); ++j){
            int src = edges[0].at(j);
            int dest = edges[1].at(j);
            int weight = edges[2].at(j);

            int dist = distances.at(src);
            if(dist != INF) dist += weight;

            if(distances.at(dest) > dist){
                distances.at(dest) = dist;
                predecessors.at(dest) = src;
            }
        }
    }

    for(int j = 0; j<edges[0].size(); ++j){
        int src = edges[0].at(j);
        int dest = edges[1].at(j);
        int weight = edges[2].at(j);

        int dist = distances.at(src);
        if(dist != INF) dist += weight;

        if(distances.at(dest) > dist){
            return false;
        }
    }
    return true;

}



int main()
{
    graph_input();
    //printf("\n");

    printf("the adjacency list with weight: \n");
    print_graph();
    printf("\n");

    printf("the edges with weight:\n");
    for(int i =0; i< edges[0].size(); ++i){
        printf("%d %d %d\n", edges[0].at(i), edges[1].at(i), edges[2].at(i));
    }
    printf("\n");

    initialize();

    bool bf = bellman_ford(0);

    printf("node \t dist \t path\n"); // node_id/number, distance from source, predecessor
    for(int i=0; i<SIZE; ++i){
        printf("%d \t %d \t", i, distances.at(i));
        stack<int> path;
        for(int j = i; j != -1; j = predecessors[j]){
            path.push(j);
        }
        if(!path.empty()) printf("%d", path.top());
        path.pop();
        while(!path.empty()){
            printf(" -> %d", path.top());
            path.pop();
        }
        printf("\n");
    }
    printf("\n");

    printf("no negative weight cycle: %d\n", bf);

    return 0;
}

