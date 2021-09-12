/*
A program to find the optimal parenthization for matrix chain multiplication


test1_input: 30 35 15 5 10 20 25
test1_output: ((A1(A2A3))((A4A5)A6))

test2_input: 10 5 1 10 2 10
*/


#include<stdio.h>
#include<string>
#include<vector>


using namespace std;

vector<int> dimensions;

vector<vector<int>> m;
vector<vector<int>> s;

void read_input()
{
    int inp;
    while(scanf("%d", &inp) != EOF)
        dimensions.push_back(inp);
}


void initialize(int n)
{
    for(int i = 0; i<n; ++i){
        vector<int> vec;
        for(int j = 0; j<n; ++j){
            vec.push_back(-1);
        }
        m.push_back(vec);
        s.push_back(vec);
    }
}

void matrix_chain_mul_order(vector<int> p)
{
    int n = p.size() - 1; // # of matrices

    for(int i = 1; i <n ; ++i){
        m.at(i).at(i) = 0;
    }

    for(int l = 2; l <= n; ++l){ // # of matrices to be parenthesized together
        for(int i = 0; i < n-l+1; ++i){ // i+l-1 < n; so, i < n-l+1
            int j = i + l - 1;
            m.at(i).at(j) = INT_MAX;
            for(int k=i; k < j; ++k){
                int val = m.at(i).at(k) + m.at(k+1).at(j) + p.at(i)*p.at(k+1)*p.at(j+1); // as i<=k<j # of matrices in m[i,k] and m[k+1, j] < #matrices in m[i, j], so their existence is assured
                // cost of the two subproblems + #row of 1st mat * #col of 1st mat * #col of 2nd mat
                if(val < m.at(i).at(j) ){
                    m.at(i).at(j) = val;
                    s.at(i).at(j) = k;
                }
            }
        }
    }
}

void print_parenthesized(vector<vector<int>> s, int i, int j)
{
    if(i==j)
        printf("A%d", i+1);
    else{
        printf("(");
        int k = s.at(i).at(j);
        print_parenthesized(s, i, k);
        print_parenthesized(s, k+1, j);
        printf(")");
    }
}


int main()
{
    freopen("input__ignore__.txt", "r", stdin);

    read_input();
    initialize(dimensions.size()-1);

    printf("\nDimension array: \n\t");
    for(int i = 0; i<dimensions.size(); ++i){
        printf("%d ", dimensions.at(i));
    }
    printf("\n\nParenthesized Chain: \n\t");

    matrix_chain_mul_order(dimensions);
    print_parenthesized(s, 0, dimensions.size()-2);
    printf("\n");

    return 0;
}


