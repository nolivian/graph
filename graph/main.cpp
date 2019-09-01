//
//  main.cpp
//  graph
//
//  Created by Nick on 8/30/19.
//  Copyright © 2019 Nick. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Vertex {
    bool explored;
    int leader;
};

int t = 0; //global variable to track finishing times (e.g. - number of nodes processed)
int s = NULL;//global veraible to track the source vertex from which DFS was initaited
vector<Vertex> vertices(10);
vector<int> finishing(10);

void DFS_Loop(vector<vector<int>>&, int);
void DFS(vector<vector<int>>&, size_t);
vector<vector<int>> createGraph(fstream&);

int main(int argc, const char * argv[]) {
    
    fstream f {"list.txt", ios::in | ios::binary}; //open file for input
    
    if (!f){//program failes to open data file}
        cout << "File could not be opened\n";
        return 9;
    }

    int numVertices = 10;
    int head;
    int tail;
    
    vector<vector<int>> g(numVertices);
    vector<vector<int>> g_rev(numVertices);

    while (f >> tail >> head) {//read line from file
        g[tail].push_back(head);//create edge
        g_rev[head].push_back(tail);//create edge
    }
    
    for (int i = 0; i < numVertices; ++i){
        vertices[i].explored = false;
    }
    
    DFS_Loop(g_rev, 1);
    
    for (int i = 0; i < numVertices; ++i){
        vertices[i].explored = false;
    }
    
    DFS_Loop(g, 2);

    return 0;
}

void DFS_Loop(vector<vector<int>>& g, int pass) {
    for(size_t i = g.size() - 1; i >= 1; --i){
        int node = (pass == 1 ? i : finishing[i]);

        if (vertices[node].explored){
            s = node;
            DFS(g, node);
        }
    }
}

void DFS(vector<vector<int>>& g, size_t i){
    vertices[i].explored = true;
    vertices[i].leader = s;
    for (int j = 0; j < g[i].size(); ++j){
        int v = g[i][j];

        if (!vertices[v].explored){
            DFS(g, v);
        }
    }
    ++t;
    finishing[t] = i;//capture finishing time of each node
    //vertices[i].finishingTime = t;
}
