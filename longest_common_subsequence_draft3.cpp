/*
A program to find the longest common subsequence for 4 strings

test_input:
7 6
ABCBDAB
BDCABA
test_ouput:
BCBA, BDAB [among many others]
*/


#include<stdio.h>
#include<bits/stdc++.h>


using namespace std;

// global variable definitions

vector<char> seq1, seq2, seq3, seq4;


void read_input()
{
    seq1.push_back(0);
    seq2.push_back(0);
    seq3.push_back(0);
    seq4.push_back(0);

    int c = 0;
    char inp;

    while(scanf("%c", &inp) != -1){
        if(inp == '\n') {
            ++c;
        }
        else{
            if(c == 0) seq1.push_back(inp);
            else if(c == 1) seq2.push_back(inp);
            else if(c == 2) seq3.push_back(inp);
            else seq4.push_back(inp);
        }


    }
}

void get_lcs(vector<vector<int>> c, vector<char> seq1, vector<char> &solution, int i, int j)
{
    if(i == 0 || j == 0) return;
    int l = c.at(i).at(j);
    if(l > c.at(i-1).at(j-1) && l > c.at(i-1).at(j) && l > c.at(i).at(j-1)){
        get_lcs(c, seq1, solution, i-1, j-1);
        //printf("%c ", seq1[i]);
        solution.push_back(seq1.at(i));
    }
    else if (c.at(i-1).at(j) >= c.at(i).at(j-1)){
        get_lcs(c, seq1, solution, i-1, j);
    }
    else{
        get_lcs(c, seq1, solution, i, j-1);
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

    printf("Sequence 1 (%d): ", seq1.size() - 1);
    for(int i = 1; i < seq1.size(); ++i){
        printf("%c ", seq1.at(i));
    }
    printf("\n");

    printf("Sequence 2 (%d): ", seq2.size() - 1);
    for(int j = 1; j < seq2.size(); ++j){
        printf("%c ", seq2.at(j));
    }
    printf("\n");

    printf("Sequence 3 (%d): ", seq3.size() - 1);
    for(int j = 1; j < seq3.size(); ++j){
        printf("%c ", seq3.at(j));
    }
    printf("\n");

    printf("Sequence 4 (%d): ", seq4.size() - 1);
    for(int j = 1; j < seq4.size(); ++j){
        printf("%c ", seq4.at(j));
    }
    printf("\n");

    vector<vector<int>> c = lcs(seq1, seq2);


    vector<char> solution1;
    solution1.push_back(0);

    get_lcs(c, seq1, solution1, seq1.size()-1, seq2.size()-1);


    vector<char> solution2;
    solution2.push_back(0);
    get_lcs(lcs(solution1, seq3), solution1, solution2, solution1.size()-1, seq3.size()-1);


    vector<char> solution3;
    solution3.push_back(0);
    get_lcs(lcs(solution2, seq4), solution2, solution3, solution2.size()-1, seq4.size()-1);



    printf("solution (%d): ", solution3.size()-1);
    for(int j = 1; j < solution3.size(); ++j){
        printf("%c ", solution3.at(j));
    }
    printf("\n");

    return 0;
}




