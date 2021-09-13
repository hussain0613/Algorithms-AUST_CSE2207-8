/*
A program to find the longest common subsequence

test_input:
7 6
ABCBDAB
BDCABA
test_ouput:
BCBA [among many others]
*/


#include<stdio.h>
#include<bits/stdc++.h>


using namespace std;

// global variable definitions

vector<char> seq1, seq2;


void read_input()
{
    seq1.push_back(0);
    seq2.push_back(0);

    int m, n;
    char inp;
    scanf("%d%d", &m, &n);
    getchar();

    for(int i = 1; i <= m; ++i){
        scanf("%c", &inp);
        seq1.push_back(inp);
    }
    getchar();
    for(int j = 1; j <= n; ++j){
        scanf("%c", &inp);
        seq2.push_back(inp);
    }
}

void print_lcs(vector<vector<int>> c, vector<char> seq1, int i, int j)
{
    if(i == 0 || j == 0) return;
    int l = c.at(i).at(j);
    if(l > c.at(i-1).at(j-1) && l > c.at(i-1).at(j) && l > c.at(i).at(j-1)){
        print_lcs(c, seq1, i-1, j-1);
        printf("%c ", seq1[i]);
    }
    else if (c.at(i-1).at(j) >= c.at(i).at(j-1)){
        print_lcs(c, seq1, i-1, j);
    }
    else{
        print_lcs(c, seq1, i, j-1);
    }
}


vector<vector<int>> lcs(vector<char> seq1, vector<char> seq2)
{
    int m = seq1.size();
    int n = seq2.size();

    vector<vector<int>> c(m, vector<int>(n)); // initializing with m # of vectors, each of which are of size n

    for(int i = 0; i<m; ++i){ //0-ing the 1st column
        c.at(i).at(0) = 0;
    }

    for(int j = 0; j<n; ++j){ // 0-ing the 1st row
        c.at(0).at(j) = 0;
    }
    for(int i=1; i<m; ++i){
        for(int j = 1; j<n; ++j){
            if(seq1.at(i) == seq2.at(j)){
                c.at(i).at(j) = c.at(i-1).at(j-1) + 1;
               // printf("%c ", seq1.at(i));
            }
            else{
                if(c.at(i-1).at(j) >= c.at(i).at(j-1)){
                    c.at(i).at(j) = c.at(i-1).at(j);
                }
                else{
                    c.at(i).at(j) = c.at(i).at(j-1);
                }
            }
        }
    }

    return c;
}


int main()
{
    freopen("input__ignore__.txt", "r", stdin);

    read_input();
    int m = seq1.size(), n = seq2.size();

    printf("Sequence 1 (%d): ", seq1.size());
    for(int i = 1; i < seq1.size(); ++i){
        printf("%c ", seq1.at(i));
    }
    printf("\n");

    printf("Sequence 2 (%d): ", seq2.size());
    for(int j = 1; j < seq2.size(); ++j){
        printf("%c ", seq2.at(j));
    }
    printf("\n");

    vector<vector<int>> c = lcs(seq1, seq2);
    printf("LCS (%d): ", c.at(m-1).at(n-1));
    print_lcs(c, seq1, m-1, n-1);
    printf("\n");
    return 0;
}




