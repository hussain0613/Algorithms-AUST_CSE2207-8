#include<stdio.h>

#define SIZE 12 // number of nodes


char names[SIZE] = {'0', 'A', 'B', 'C', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
int dists[SIZE], preds[SIZE], dones[SIZE];
int time = 0;

void dfs(int pred, int root, int g[][SIZE])
{
    time = 1;
    dists[root] = dists[pred] + 1;
    preds[root] = pred;

    for(int i=0; i<SIZE; ++i){
        if(g[root][i] && dists[i] == -1){
            dfs(root, i, g);
        };
    }
    time += 1;
    printf("%d %d\n", root, time);
    dones[root] = time;
}


void add_edge(int i, int j, int g[][SIZE])
{
    g[i][j] = 1;

    g[j][i] = 1;
}


int main()
{

    for(int i; i<SIZE; ++i){
        dists[i] = -1;
        preds[i] = -1;
        dones[i] = -1;
    }

    int g[SIZE][SIZE];

    for(int i=0; i<SIZE; ++i){
        for(int j = 0; j<SIZE; ++j){
            g[i][j] = 0;
        }
    }

    add_edge(1, 2, g);

    add_edge(1, 3, g);

    add_edge(2, 4, g);

    add_edge(2, 5, g);

    add_edge(2, 6, g);

    add_edge(3, 7, g);

    add_edge(4, 8, g);

    add_edge(5, 9, g);
    add_edge(6, 9, g);
    add_edge(7, 9, g);

    add_edge(7, 10, g);


    dfs(0, 1, g);

    int x = 9;
    while (x >0){
        printf("%c-%d/%d\n", names[x], dists[x]+1, dones[x]);
        x = preds[x];
    }

    return 0;
}


