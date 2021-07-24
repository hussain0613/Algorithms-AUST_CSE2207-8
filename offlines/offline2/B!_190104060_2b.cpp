#include<stdio.h>

// macros
#define SIZE 9 // Number of nodes

#define for_(var) for(int var = 0; var<SIZE; ++var)



// function prototype declarations
void initialize();
void add_edge(int, int);
void find_has_parents(); // determine which nodes has parents and which don't

void topological_sort();
void dfs(int);


// global vaiables
int graph[SIZE][SIZE];
bool has_parent[SIZE]; // in case can't reach all nodes from any single node
int node_stats[SIZE][2]; // the time of discovery, and the time when it's finished for each node. -1 will indicate not discovered, not dead
int sorted_nodes[SIZE];


int sorted_node_pointer = SIZE-1; // the next sorted node will be inserted at this position in the sorted_nodes
int time = 0;

int main()
{
    initialize();


    add_edge(0, 1);
    add_edge(0, 7);
    add_edge(1, 2);
    add_edge(1, 7);
    add_edge(2, 5);
    add_edge(3, 2);
    add_edge(3, 4);
    add_edge(4, 5);
    add_edge(6, 7);

    printf("the adjacency: \n");
    for_(i){
        for_(j){
            printf(" %d ", graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    find_has_parents();

    printf("has parents: ");
    for_(i){
        printf("%d ", has_parent[i]);
    }
    printf("\n\n");


    topological_sort();

    printf("topologically sorted nodes: ");
    for_(i){
        printf("%d ", sorted_nodes[i]);
    }
    printf("\n");


    return 0;
}

// function definitions

void initialize()
{
    for_(i){
        has_parent[i] = 0;
        node_stats[i][0] = -1;
        node_stats[i][1] = -1;
        sorted_nodes[i] = -1;
        for_(j){
            graph[i][j] = 0;
        }
    }
}


void add_edge(int i, int j)
{
    if(i>-1 && j>-1 && i<SIZE && j<SIZE)
        graph[i][j] = 1;
}


void find_has_parents()
{
    for_(c){
        for_(r){
            if(graph[r][c]) {
                has_parent[c] = 1;
                break;
            }
        }
    }
}


void dfs(int root)
{
    ++time;
    node_stats[root][0] = time;

    for_(i){
        if(graph[root][i] && node_stats[i][1] == -1) { // has path, and not finished
            if(node_stats[i][0] != -1) {
                printf("[!] Cycle detected! root: %d, i: %d\n", root, i);
                return;
            }
            dfs(i);
        }
    }

    ++time;
    node_stats[root][1] = time;
    sorted_nodes[sorted_node_pointer--] = root;
}


void topological_sort()
{
    for_(i){
        if(!has_parent[i]) dfs(i);
    }
}


