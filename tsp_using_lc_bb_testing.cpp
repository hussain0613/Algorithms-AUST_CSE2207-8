/*
The Traveling Salesman Problem using Least Cost Branch and Bound method
*/

/*
A -> B
cost(B) = cost(A) + cost(A -> B) + RCL(RCL_MAT(A), A, B); // for root node A = null so cost(A) = cost(A -> B) = 0

*/


#include<stdio.h>

#define SIZE 3
#define for_(var) for(int var = 0; var<SIZE; ++var)

int get_mx()
{
    int nbits = sizeof(int)*8; // number of bits used to represent a signed integer

    return ((1 << nbits-1) - 1); // 1*(2^(nbits-1)) - 1
    // note: |-mx| = mx+1
}
const int inf = get_mx(); //pseudo infinity


struct Data{
    int cost;
    int rca_matrix[SIZE][SIZE];
};
typedef struct Data Data;

void print_mat(int mat[SIZE][SIZE]);
void cpy_mat(int src[SIZE][SIZE], int dest[SIZE][SIZE]);
void pre_ruduction_processing(int mat[SIZE][SIZE], int root_node, int parent_node, int node);
int reduce(int mat[SIZE][SIZE]);


int main()
{
    int mat[SIZE][SIZE] = {
        {inf, 10, 11},
        {1, inf, 16},
        {2, 12, inf},
    };

    printf("initial cost adjacency matrix: \n");
    print_mat(mat);

    // *******************************
    Data d0;
    cpy_mat(mat, d0.rca_matrix);
    d0.cost = reduce(d0.rca_matrix);
    printf("node0 rcl matrix: \n");
    print_mat(d0.rca_matrix);
    printf("cost: %d\n", d0.cost);
    printf("\n");

    // ********************************
    int root = 0, parent = 0, node = 2;
    Data d1;
    Data *parent_data = &d0, *current_data = &d1;

    cpy_mat(parent_data->rca_matrix, current_data->rca_matrix);
    pre_ruduction_processing(current_data->rca_matrix, root, parent, node);
    current_data->rca_matrix[node][root] = inf;
    current_data->cost = parent_data->cost + parent_data->rca_matrix[parent][node] + reduce(current_data->rca_matrix);
    printf("node0-1 rcl matrix: \n");
    print_mat(current_data->rca_matrix);
    printf("cost: %d\n", current_data->cost);
    printf("\n");

    /*/ ********************************
    root = 0, parent = 3, node = 1;
    Data d2;
    parent_data = &d1, current_data = &d2;

    cpy_mat(parent_data->rca_matrix, current_data->rca_matrix);
    pre_ruduction_processing(current_data->rca_matrix, root, parent, node);
    current_data->rca_matrix[node][root] = inf;
    current_data->cost = parent_data->cost + parent_data->rca_matrix[parent][node] + reduce(current_data->rca_matrix);
    printf("node0-3-1 rcl matrix: \n");
    print_mat(current_data->rca_matrix);
    printf("cost: %d\n", current_data->cost);
    printf("\n");

    // ********************************
    root = 0, parent = 1, node = 4;
    Data d3;
    parent_data = &d2, current_data = &d3;

    cpy_mat(parent_data->rca_matrix, current_data->rca_matrix);
    pre_ruduction_processing(current_data->rca_matrix, root, parent, node);
    current_data->rca_matrix[node][root] = inf;
    current_data->cost = parent_data->cost + parent_data->rca_matrix[parent][node] + reduce(current_data->rca_matrix);
    printf("node0-3-1-4 rcl matrix: \n");
    print_mat(current_data->rca_matrix);
    printf("cost: %d\n", current_data->cost);
    printf("\n");

    // ********************************
    root = 0, parent = 4, node = 2;
    Data d4;
    parent_data = &d3, current_data = &d4;

    cpy_mat(parent_data->rca_matrix, current_data->rca_matrix);
    pre_ruduction_processing(current_data->rca_matrix, root, parent, node);
    //current_data->rca_matrix[node][root] = inf; // going back to root from this one, as this is the last one
    current_data->cost = parent_data->cost + parent_data->rca_matrix[parent][node] + reduce(current_data->rca_matrix);
    printf("node0-3-1-4-2 rcl matrix: \n");
    print_mat(current_data->rca_matrix);
    printf("cost: %d\n", current_data->cost);
    printf("\n");

    // ********************************
    root = 0, parent = 2, node = 0;
    Data d5;
    parent_data = &d4, current_data = &d5;

    cpy_mat(parent_data->rca_matrix, current_data->rca_matrix);
    pre_ruduction_processing(current_data->rca_matrix, root, parent, node);
    //current_data->rca_matrix[node][root] = inf; // already set as inf
    current_data->cost = parent_data->cost + parent_data->rca_matrix[parent][node] + reduce(current_data->rca_matrix);
    printf("node0-3-1-4-2-0 rcl matrix: \n");
    print_mat(current_data->rca_matrix);
    printf("cost: %d\n", current_data->cost);
    printf("\n");
    */

    return 0;
}

void print_mat(int mat[SIZE][SIZE])
{
    for_(r){
        for_(c){
            if(mat[r][c] == inf) printf(" inf \t");
            else printf(" %d \t", mat[r][c]);
        }
        printf("\n");
    }
    printf("\n");
}

void cpy_mat(int src[SIZE][SIZE], int dest[SIZE][SIZE])
{
    for_(r){
        for_(c){
            dest[r][c] = src[r][c];
        }
    }
}

void pre_ruduction_processing(int mat[SIZE][SIZE], int root_node, int parent_node, int node)
{
    for_(i){
        mat[i][node] = inf; // not coming back to this node from any other node
        if(parent_node != root_node) mat[i][parent_node] = inf; // not going back to parent_node from any other node
        mat[parent_node][i] = inf; // not going to any node from parent node
    }
    // mat[node][root_node] = inf; // not going to root node from this node

}

int reduce(int mat[SIZE][SIZE])
{
    int cost = 0;

    // row reduction
    for_(r){
        int min = inf;
        for_(c){
            if(mat[r][c] < min) min = mat[r][c];
        }
        //printf("row %d min: %d\n", r, min);

        if(min == inf) continue; // cost defaults = 0
        for_(c){
            if(mat[r][c] != inf) mat[r][c] -= min;
        }
        if(min != inf) cost += min;
    }

    //printf("\n");

    // column reduction
    for_(c){
        int min = inf;
        for_(r){
            if(mat[r][c] < min) min = mat[r][c];
        }
        printf("min_: %d\n", min);
        if(min == inf) continue; // cost does not change
        //printf("col %d min: %d\n", c, min);
        for_(r){
            if(mat[r][c] != inf) mat[r][c] -= min;
        }
        if(min != inf) cost += min;
    }

    printf("cost_: %d\n", cost);
    return cost;
}


