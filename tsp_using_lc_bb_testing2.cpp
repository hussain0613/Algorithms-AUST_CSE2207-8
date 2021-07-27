#include<stdio.h>
#include<functional>
#include<vector>
#include<queue>

// macro definitions
#define SIZE 3
#define for_(var) for(int var = 0; var<SIZE; ++var)

// determining a pseudo-infinity for signed int
int get_mx()
{
    int nbits = sizeof(int)*8;

    return ((1 << nbits-1) - 1);
}
const int inf = get_mx(); //pseudo infinity


// data structure to hold information about a node in state space tree
struct Data{

    int node, cost, path_count;
    int rca_matrix[SIZE][SIZE], path[SIZE+1];


    bool operator<(const Data &other) const
    {
        return this->cost < other.cost;
    }

    bool operator>(const Data &other) const
    {
        return this->cost > other.cost;
    }
};
typedef struct Data Data;


void print_mat(int mat[SIZE][SIZE]);
void cpy_mat(int src[SIZE][SIZE], int dest[SIZE][SIZE]);
void pre_ruduction_processing(int mat[SIZE][SIZE], int root_node, int parent_node, int node);
int reduce(int mat[SIZE][SIZE]);



Data tsp(int mat[SIZE][SIZE], int root)
{
    Data root_data;

    root_data.path_count = 0;
    root_data.node = root;
    root_data.path[root_data.path_count] = root_data.node;

    cpy_mat(mat, root_data.rca_matrix);
    root_data.cost = reduce(root_data.rca_matrix);

    std::priority_queue<Data, std::vector<Data>, std::greater<Data>> Q;

    Q.push(root_data);

    while(Q.top().path_count < SIZE ){
        Data current = (Q.top()); //the node to be expanded
        Q.pop();


        for_(i){
            if(current.rca_matrix[current.node][i] != inf){
                Data child;
                child.node = i;
                child.path_count = current.path_count+1;

                for(int j=0; j<child.path_count; ++j){
                    child.path[j] = current.path[j];
                }
                child.path[child.path_count] = child.node;

                cpy_mat(current.rca_matrix, child.rca_matrix);
                if(child.path_count+1 != SIZE) child.rca_matrix[i][root_data.node] = inf; // not going back to root if still in the middle of the journey
                pre_ruduction_processing(child.rca_matrix, root_data.node, current.node, i);

                child.cost = current.cost + current.rca_matrix[current.node][i] + reduce(child.rca_matrix);

                Q.push(child);
            }

        }
    }
    return Q.top();
}


int main()
{
    /*int mat[SIZE][SIZE] = {
        {inf, 20, 30, 10, 11, 80},
        {1, inf, 16, 20, 20, 11},
        {2, 50, inf, 70, 40, 69},
        {3, 60, 18, inf, 30, 21},
        {4, 80, 70, 160, inf, 36},
        {5, 60, 11, 25, 14, inf}
    };*/
    int mat[SIZE][SIZE] = {
        {inf, 10, 11},
        {1, inf, 16},
        {2, 12, inf},
    };

    printf("initial cost adjacency matrix: \n");
    print_mat(mat);
    printf("\n");


    Data final_node = tsp(mat, 0);


    printf("final node: %d\n", final_node.node);
    printf("final path_count: %d\n", final_node.path_count);
    printf("final cost: %d\n", final_node.cost);
    printf("\nfinal matrix: \n");
    print_mat(final_node.rca_matrix);
    printf("\n");

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
        if(parent_node != root_node) mat[i][parent_node] = inf; // if condition, then not going back to parent_node from any other node
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

        if(min == inf) continue; // cost defaults = 0
        for_(c){
            if(mat[r][c] != inf) mat[r][c] -= min;
        }
        if(min != inf) cost += min;
    }

    // column reduction
    for_(c){
        int min = inf;
        for_(r){
            if(mat[r][c] < min) min = mat[r][c];
        }
        if(min == inf) continue; // cost does not change
        for_(r){
            if(mat[r][c] != inf) mat[r][c] -= min;
        }
        if(min != inf) cost += min;
    }


    return cost;
}






