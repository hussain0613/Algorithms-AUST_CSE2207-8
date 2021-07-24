#include<stdio.h>
#include<queue>

#define SIZE 5 // number of nodes


using std::queue;


void bfs(int root, int g[][SIZE])
{
    int dist[SIZE], pred[SIZE];

    queue<int> q;

    for(int i; i<SIZE; ++i){
        dist[i] = -1;
        pred[i] = -1;
    }

    dist[root] = 0;
    pred[root] = -1;

    q.push(root);

    while(!q.empty()){

        int curr = q.front();
        q.pop();

        for(int i=0; i<SIZE; ++i){
            int d_curr = dist[curr];
            int edge = g[curr][i];

            if(edge >= 0 && (dist[i] > d_curr + edge || dist[i] < 0)){ // use 'edge>0' if the value of the edge is just a flag and 0 means not connected, use '>=' if the value of the edge is distance/weight
                                                                        //dist[i]<0 is enough if the graph is unweighted
                dist[i] = d_curr + edge;
                pred[i] = curr;

                q.push(i);
            }
        }
    }

    for(int i=0; i<SIZE; ++i){
        printf("node: %d\npred: %d \ndistance from root: %d\n\n", i, pred[i], dist[i]);

    }
}


void add_edge(int i, int j, int g[][SIZE], int weight = 1, bool is_bi_directional = true) // default: unweighted and bidirectional
{
    g[i][j] = weight;

    if(is_bi_directional) g[j][i] = weight;
}


int main()
{
    int g[SIZE][SIZE];

    for(int i=0; i<SIZE; ++i){
        for(int j = 0; j<SIZE; ++j){
            g[i][j] = -1;
        }
    }

    add_edge(0, 1, g, 1, false);
    add_edge(1, 0, g, 100, false);

    add_edge(0, 2, g, 10);

    add_edge(1, 3, g, 5);

    add_edge(2, 4, g, 5);

    add_edge(1, 4, g, 20);

    add_edge(3, 4, g, 60);

    printf("the graph matrix: \n");
    for(int i=0; i<SIZE; ++i){
        for(int j = 0; j<SIZE; ++j){
            printf("%d ", g[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");


    bfs(0, g);

    return 0;
}
