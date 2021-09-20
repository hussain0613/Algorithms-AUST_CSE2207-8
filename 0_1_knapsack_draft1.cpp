/*
A program implementing 0-1 Knapsack --- via bottom up(tabulation) dynamic programming approach

test1_input:
4 5
2 3
3 4
4 5
5 6
test1_output: 7 or
0 0 0 0 0 0
0 0 3 3 3 3
0 0 3 4 4 7
0 0 3 4 5 7
0 0 3 4 5 7
*/

#include<bits/stdc++.h>

using namespace std;


vector<vector<int>> knapsack(int n, int capacity, vector<pair<int, int>> items)
{
    vector<vector<int>> table(n+1, vector<int>(capacity+1)); // initializing with (n+1) # of vectors, each of which are of size (capacity+1), i.e. a 2d vector of shape (n+1)*(cap+1)

    for(int i = 0; i < n; ++i){ // 0-ing the first column
        table.at(i).at(0) = 0;
    }
    for(int c = 0; c < capacity; ++c){ // 0-ing the first row
        table.at(0).at(c) = 0;
    }

    for(int i = 1; i <= n; ++i){
        for(int c = 1; c <= capacity; ++c){
            int w = items.at(i).first, p = items.at(i).second;

            int p_prev = table.at(i-1).at(c);

            if(w <= c && (p_prev < p + table.at(i-1).at(c-w) ) ){
                table.at(i).at(c) = p + table.at(i-1).at(c-w); // picking item
            }
            else{
                table.at(i).at(c) = p_prev; // discarding item without changing capacity
            }
        }
    }


    return table;
}


vector<int> get_items_status(vector<vector<int>> table)
{
    int n = table.size() - 1; // # of items
    vector<int> status;
    if(n <= 0){
        cout << "Empty table!";
        return status;
    }

    int capacity = table.at(0).size() - 1;

    if(capacity <= 0){
        cout << "No sack!";
        return status;
    }

    for(int i = 1; i <= n; ++i){
        int flag = 0;
        if(table.at(i-1).at(capacity) < table.at(i).at(capacity)) flag = 1;
        status.push_back(flag);
    }

    return status;
}

int main()
{
    freopen("input__ignore__.txt", "r", stdin);

    // reading input
    int n, capacity, p, w;
    vector<pair<int, int>> items;
    cin >> n >> capacity;

    items.push_back({-1, -1}); // so that letter we don't have to minus 1 every time
    for(int i = 0; i < n; ++i){
        cin >> w >> p;
        items.push_back({w, p});
    }

    // displaying input
    cout << "\n# of items: " << n << "\nCapacity: " << capacity << "\n\nItems (weight, profit): \n";

    for(int i = 1; i <= n; ++i){
        cout << items.at(i).first << " " << items.at(i).second << endl;
    }

    // knapsack
    vector<vector<int>> table = knapsack(n, capacity, items);
    vector<int> status = get_items_status(table);
    // displaying the table

    cout << "\nTable: \n";
    for(int i = 0; i <= n; ++i){
        for(int c = 0; c <= capacity; ++c){
            cout << table.at(i).at(c) << " ";
        }
        cout << endl;
    }

    // displaying each items status i.e. picked or not picked
    cout << "\nStatus (picked or not): \n";
    for(int i = 0; i<status.size(); ++i)
        cout << status.at(i) << " ";
    cout << endl;

    return 0;
}
