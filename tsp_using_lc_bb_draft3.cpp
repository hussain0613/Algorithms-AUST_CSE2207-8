/*
The Traveling Salesman Problem using Least Cost Branch and Bound method
*/

/*
A -> B
cost(B) = cost(A) + cost(A -> B) + RCL(RCL_MAT(A), A, B); // for root node A = null so cost(A) = cost(A -> B) = 0

*/


#include<stdio.h>
#include<stdlib.h>
#include<functional>
#include<vector>
#include<queue>

#define SIZE 5
#define for_(var) for(int var = 0; var<SIZE; ++var)

int get_mx()
{
    int nbits = sizeof(int)*8; // number of bits used to represent a signed integer

    return ((1 << nbits-1) - 1); // 1*(2^(nbits-1)) - 1
    // note: |-mx| = mx+1
}
const int inf = get_mx(); //pseudo infinity


struct Data{
    int node, cost, level;
    int rca_matrix[SIZE][SIZE], path[SIZE+1];

    /*bool operator<(const Data &other) const
    {
        return this->cost < other.cost;
    }*/
    bool operator()(const Data d1, const Data d2)
    {
        return d1.cost > d2.cost;
    }
};
typedef struct Data Data;


void print_mat(int mat[SIZE][SIZE]);
void cpy_mat(int src[SIZE][SIZE], int dest[SIZE][SIZE]);
void pre_ruduction_processing(int mat[SIZE][SIZE], int root_node, int parent_node, int node);
int reduce(int mat[SIZE][SIZE]);



Data tsp(int mat[SIZE][SIZE])
{
    Data root_data;
    //root_data = (Data*) malloc(sizeof(Data));

    root_data.level = 0;
    root_data.path[root_data.level] = 0;
    root_data.node = 0;

    cpy_mat(mat, root_data.rca_matrix);
    root_data.cost = reduce(root_data.rca_matrix);

    std::priority_queue<Data, std::vector<Data>, Data> Q;

    Q.push(root_data);

    while(Q.top().level < SIZE ){
        Data current = (Q.top()); //the node to be expanded
        Q.pop();


        for_(i){
            if(current.rca_matrix[current.node][i] != inf){
                Data child;
                //child = (Data*) malloc(sizeof(Data));
                child.node = i;
                child.level = current.level+1;

                for(int j=0; j<child.level; ++j){
                    child.path[j] = current.path[j];
                }
                child.path[child.level] = child.node;

                cpy_mat(current.rca_matrix, child.rca_matrix);
                if(child.level+1 < SIZE) child.rca_matrix[i][0]; // not going back to root if still in the middle
                pre_ruduction_processing(child.rca_matrix, 0, current.node, i);

                child.cost = current.cost + current.rca_matrix[current.node][i] + reduce(child.rca_matrix);

                Q.push(child);
            }

        }
    }
    return Q.top();
}


int main()
{
    int mat[SIZE][SIZE] = {
        {inf, 20, 30, 10, 11},
        {15, inf, 16, 4, 2},
        {3, 5, inf, 2, 4},
        {19, 6, 18, inf, 3},
        {16, 4, 7, 16, inf}
    };

    printf("initial cost adjacency matrix: \n");
    print_mat(mat);

    Data final_node = tsp(mat);

    printf("final node: %d\n", final_node.node);
    printf("final level: %d\n", final_node.level);
    printf("final cost: %d\n", final_node.cost);
    printf("final matrix: \n");
    print_mat(final_node.rca_matrix);

    printf("The path taken: ");
    for(int i = 0; i<SIZE+1; ++i){
        printf("%d ", final_node.path[i]);
        if(i<SIZE) printf("-> ");
    }
    printf("\n");

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

        if(min == inf) break; // cost defaults = 0
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
        if(min == inf) break; // cost does not change
        //printf("col %d min: %d\n", c, min);
        for_(r){
            if(mat[r][c] != inf) mat[r][c] -= min;
        }
        if(min != inf) cost += min;
    }


    return cost;
}




