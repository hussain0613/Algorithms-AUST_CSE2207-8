/*
A program to find the optimal parenthization for matrix chain multiplication


test1_input: 30 35 15 5 10 20 25
test2_input: 10 5 1 10 2 10
*/


#include<stdio.h>
#include<string>
#include<vector>
#include<unordered_map>


using namespace std;

vector<int> dimensions;

unordered_map<string, int> m;
unordered_map<string, int> s;


void read_input()
{
    int inp;
    while(scanf("%d", &inp) != EOF)
        dimensions.push_back(inp);
}


string make_str(int i, int j)
{
    string str;
    str += to_string(i);
    str += ",";
    str += to_string(j);

    return str;
}

void matrix_chain_mul_order(vector<int> p)
{
    int n = p.size() - 1; // # of matrices

    for(int i = 1; i <=n ; ++i){
        m[make_str(i, i)] = 0;
    }

    for(int l = 2; l <= n; ++l){ // # of matrices to be parenthesized together
        for(int i = 1; i <= n-l+1; ++i){ // i+l-1 <= n; so, i <= n-l+1
            int j = i + l - 1;
            m.insert({make_str(i, j), INT_MAX});
            for(int k=i; k < j; ++k){
                int val = m.at(make_str(i, k)) + m.at(make_str(k+1, j)) + p.at(i-1)*p.at(k)*p.at(j); // as i<=k<j # of matrices in m[i,k] and m[k+1, j] < #matrices in m[i, j], so their existence is assured
                // cost of the two subproblems + #row of 1st mat * #col of 1st mat * #col of 2nd mat
                if(val < m.at(make_str(i, j)) ){
                    m[make_str(i, j)] = val;
                    s[make_str(i, j)] = k;
                }
            }
        }
    }
}

void print_parenthesized(unordered_map<string, int> s, int i, int j)
{
    if(i==j)
        printf("A%d", i);
    else{
        printf("(");
        int k = s[make_str(i, j)];
        print_parenthesized(s, i, k);
        print_parenthesized(s, k+1, j);
        printf(")");
    }
}


int main()
{
    freopen("input__ignore__.txt", "r", stdin);

    read_input();
    printf("\nDimension array: \n\t");
    for(int i = 0; i<dimensions.size(); ++i){
        printf("%d ", dimensions.at(i));
    }
    printf("\n\nParenthesized Chain: \n\t");

    matrix_chain_mul_order(dimensions);
    print_parenthesized(s, 1, dimensions.size()-1);
    printf("\n");

    return 0;
}

