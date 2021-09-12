#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

vector<int> dimensions{30, 35, 15, 5, 10, 20, 25};
//vector<int> dimensions{10, 5, 1, 10, 2, 10};

map<pair<int, int>, int> m;
map<pair<int, int>, int> s;
/*{
    {make_pair(1, 6), 3},
    {make_pair(1, 3), 2},
    {make_pair(1, 2), 1},
    {make_pair(1, 1), 1},

    {make_pair(2, 2), 2},
    {make_pair(3, 3), 3},

    {make_pair(4, 6), 4},
    {make_pair(4, 4), 4},
    {make_pair(5, 6), 5},
    {make_pair(5, 5), 5},
    {make_pair(6, 6), 6}
};*/

string make_str(int i, int j)
{
    string str;
    str += to_string(i);
    str += ",";
    str += to_string(j);

    return str;
}

void matrix_chain_multiplication(vector<int> p)
{
    int n = p.size() - 1; // # of matrices

    for(int i = 1; i <=n ; ++i){
        m[{i, i}] = 0;
    }

    for(int l = 2; l <= n; ++l){ // # of matrices to be parenthesized together
        for(int i = 1; i <= n-l+1; ++i){ // i+l-1 <= n; so, i <= n-l+1
            int j = i + l - 1;
            m.insert({{i, j}, INT_MAX});
            for(int k=i; k < j; ++k){
                int val = m.at({i, k}) + m.at({k+1, j}) + p.at(i-1)*p.at(k)*p.at(j); // as i<=k<j# of matrices int m[i,k] and m[k+1, j] < #matrices int m[i, j], so their existence is assured
                // cost of two subproblems + #row of 1st mat * #col of 1st mat * #col of 2nd mat
                if(val < m.at({i, j}) ){
                    m[{i, j}] = val;
                    s[{i, j}] = k;
                }
            }
        }
    }
}

void print_parenthesized(map<pair<int, int>, int> s, int i, int j)
{
    if(i==j)
        printf("A%d", i);
    else{
        printf("(");
        int k = s[make_pair(i, j)];
        print_parenthesized(s, i, k);
        print_parenthesized(s, k+1, j);
        printf(")");
    }
}


int main()
{

    matrix_chain_multiplication(dimensions);
    print_parenthesized(s, 1, dimensions.size()-1);

    cout<< "\n"<<make_str(50, 60);


    return 0;
}
