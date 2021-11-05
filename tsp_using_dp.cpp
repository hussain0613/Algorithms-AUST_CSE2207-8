/**
Traveling Salesman Problem(TSP) using top-down Dynamic Programming(DP) method

g(i, S) =   graph[i][0] ; when S = {}
        =   min( for all j in S, graph[i][j] + g(j, S-{j}) ) ; when S != {}

test_case#1:
    input:
        {
            {0, 10, 15, 20},
            {5, 0, 9, 10},
            {6, 13, 0, 12},
            {8, 8, 9, 0}
        }
    expected output:
        Cost: 35
        Path: 0 1 3 2 0

test_case#2:
    input:
        {
            {0, 20, 30, 10, 11},
            {15, 0, 16, 4, 2},
            {3, 5, 0, 2, 4},
            {19, 6, 18, 0, 3},
            {16, 4, 7, 16, 0}
        }
    expected output:
        Cost: 28
        Path: 0 3 1 4 2 0

*/

#include<bits/stdc++.h>

using std::vector;
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::stringstream;


void print_matrix(vector<vector<int>> matrix)
{
    for(int r = 0; r < matrix.size(); ++r){
        for(int c = 0; c < matrix.at(r).size(); ++c){
            cout << matrix.at(r).at(c) << " \t ";
        }
        cout << endl;
    }
    cout << endl;
}


void concat_vect(vector<int> &dest, vector<int> src)
{

    for(vector<int>::iterator itr = src.begin(); itr != src.end(); ++itr)
    {
        dest.push_back(*itr);
    }
}

string vect_to_str(vector<int> vect)
{
    stringstream ss;
    for(vector<int>::iterator itr = vect.begin(); itr != vect.end(); ++itr){
        ss << *itr << ", ";
    }
    return ss.str();
}


struct tsp_result{
    int cost;
    vector<int> path;
};
typedef struct tsp_result tsp_result;


void print_mem(unordered_map<int, unordered_map<string, tsp_result>> mem)
{
    unordered_map<int, unordered_map<string, tsp_result>>::iterator itr;
    for(itr = mem.begin(); itr != mem.end(); ++itr){
        cout << itr->first << ": {\n";

        unordered_map<string, tsp_result>::iterator itr2;
        for(itr2 = itr->second.begin(); itr2 != itr->second.end(); ++itr2){
            cout << "\t {" << itr2->first << "} : cost: " << itr2->second.cost << " path: {" << vect_to_str(itr2->second.path) << "}\n";
        }
        cout << "\n}\n";
    }
}


tsp_result g(vector<vector<int>> &graph, int i, vector<int> S, int dest, unordered_map<int, unordered_map<string, tsp_result>> &mem)
{
    string str_S = vect_to_str(S);

    if(mem.find(i) != mem.end()){
        //cout << "found mem["<<i<<"]\n";
        if(mem[i].find(str_S) != mem[i].end()){
            tsp_result res = mem.at(i).at(str_S);
            cout << "from mem: " << "g("<< i <<", {" << str_S << "}) = " << res.cost << endl;
            return res;
        }
    }

    tsp_result res;
    res.cost = INT_MAX;
    if(S.size() == 0) {
        res.cost = graph.at(i).at(dest);
        res.path.push_back(dest);
        mem[i][str_S] = res;
        cout << "g(" << i << ", {" << str_S << "}) = " << res.cost << endl;
        return res;
    }

    for(vector<int>::iterator itr = S.begin(); itr != S.end(); ++itr){

        vector<int> new_S = S;
        new_S.erase(new_S.begin() + (itr - S.begin()) );

        tsp_result temp_res = g(graph, *itr,  new_S, dest, mem);
        int temp_cost = graph.at(i).at(*itr) + temp_res.cost;

        if(temp_cost < res.cost){
            res.cost = temp_cost;
            res.path = {*itr};
            concat_vect(res.path, temp_res.path);
        }
    }

    mem[i][str_S] = res;

    cout << "g("<<i<<", {"<<str_S<<"}) = " << res.cost << endl;
    return res;
}

tsp_result tsp(int root, vector<vector<int>> graph)
{
    unordered_map<int, unordered_map<string, tsp_result>> mem;

    tsp_result res;
    res.path.push_back(root);

    vector<int> S;
    for(int i = 0; i < graph.size(); ++i){
        if(i != root) S.push_back(i);
    }

    tsp_result temp = g(graph, root, S, root, mem);

    res.cost = temp.cost;
    concat_vect(res.path, temp.path);

    cout << "\nmem(" << mem.size() << "): \n";
    print_mem(mem);

    return res;
}


int main()
{
    vector<vector<int>> graph{
        {0, 10, 15, 20},
            {5, 0, 9, 10},
            {6, 13, 0, 12},
            {8, 8, 9, 0}
    };

    cout << "The Given Graph:\n";
    print_matrix(graph);


    int root = 0;
    tsp_result res = tsp(root, graph);

    cout << endl;
    cout << "Cost: " << res.cost << endl;
    cout << "Path: ";
    for(int i = 0; i<res.path.size(); ++i){
        cout << res.path.at(i) << " ";
    }
    cout << endl;

    return 0;
}
