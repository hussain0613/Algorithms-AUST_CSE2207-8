/*
A program for the N-Queens problem
*/

#include<bits/stdc++.h>
#include<math.h>

using namespace std;

vector<vector<int>> solutions;
vector<int> solution;

bool collision(int k, int i)
{
    for(int j = 0; j < k; ++j){
        if(solution.at(j) == i || abs(k-j) == abs(i - solution.at(j))) return true;
    }
    return false;
}

void n_queens(int k, int n)
{
    // cout << "k: " << k << endl;
    for(int i = 0; i < n; ++i){
        if(!collision(k, i)){
            solution.at(k) = i;
            if(k + 1 < n){
                // cout << "k: " << k << " i: " << i <<" n: " << n << "\n";
                n_queens(k + 1, n);
            }
            else{
                solutions.push_back(solution);
                // cout << "gotcha\n";
            }
        }
    }

}

int main()
{
    //freopen("input__ignore__.txt", "r", stdin);

    int n;

    cout << "n: ";
    cin >> n;


    for(int i = 0; i< n; ++i){
        solution.push_back(-1);
    }


    n_queens(0, n);


    cout << "solutions ("<< solutions.size() << ") : \n";
    for(int i = 0; i < solutions.size(); ++i){
        for(int j = 0; j < n; ++j){
            cout << solutions.at(i).at(j) << " ";
        }
        cout << endl;
    }


    return 0;
}
