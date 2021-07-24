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

            if(edge > 0 && (dist[i] < 0)){
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


void add_edge(int i, int j, int g[][SIZE]) // default: unweighted and bidirectional
{
    g[i][j] = 1;
    g[j][i] = 1;
}


int main()
{
    int g[SIZE][SIZE];

    for(int i=0; i<SIZE; ++i){
        for(int j = 0; j<SIZE; ++j){
            g[i][j] = 0;
        }
    }

    add_edge(0, 1, g);
    add_edge(1, 0, g);

    add_edge(0, 2, g);

    add_edge(1, 3, g);

    add_edge(2, 4, g);

    //add_edge(1, 4, g);

    add_edge(3, 4, g);

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

