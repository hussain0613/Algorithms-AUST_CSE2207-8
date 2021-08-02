#include<stdio.h>
#include<bits/stdc++.h>

using std::vector;
using std::priority_queue;
using std::pair;
using std::make_pair;
using std::stack;

#define INPUT_FILE_NAME "input.txt"
#define INF INT_MAX // pseudo infinity

int SIZE;

vector<vector<pair<int, int>>> graph; // adjacency list with weight
vector<int> predecessors, distances;

class Comparator{
public:
    bool operator()(const int &a, const int &b){
        return distances.at(a) > distances.at(b);
    }
};
priority_queue<int, vector<int>, Comparator> q;



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


void dijkastra(int root)
{
    distances.at(root) = 0;

    for(int i = 0; i<SIZE; ++i){
        q.push(i);
    }


    while(! q.empty()){
        int src = q.top();
        q.pop();

        for(int i = 0; i<graph.at(src).size(); ++i){
            int child = graph.at(src).at(i).first;
            int weight = graph.at(src).at(i).second;

            int dist = distances.at(src);
            if(dist != INF) dist += weight;
            else dist = INF; // it will execute only if there's some node which is unreachable from the given root

            if(distances.at(child) > dist){
                distances.at(child) = dist;
                predecessors.at(child) = src;
            }
        }
    }

}



int main()
{
    graph_input();
    //printf("\n");

    printf("the adjacency list with weight: \n");
    print_graph();
    printf("\n");

    initialize();

    dijkastra(0);

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

    return 0;
}
