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
    int finishingTime;
    int leader;
    int SSC;//strongly connected compentent ID
};

int t = 0; //global variable to track finishing times (e.g. - number of nodes processed)
int s = NULL;//global veraible to track the source vertex from which DFS was initaited
vector<Vertex> vertices(10);

void DFS_Loop(vector<vector<int>>&);
void DFS(vector<vector<int>>&, size_t, bool);
vector<vector<int>> createGraph(fstream&);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    fstream f {"list.txt", ios::in | ios::binary}; //open file for input
    
    if (!f){//program failes to open data file}
        cout << "File could not be opened\n";
        return 9;
    }
    
    vector<vector<int>> g = createGraph(f);
    
    for (int i = 0; i < 10; ++i){
        vertices[i].explored = false;
    }
    
    DFS_Loop(g);
    
    for (int i = 0; i < 10; ++i){
        cout << "i: " << i << " finishing: " << vertices[i].finishingTime << endl;
    }
    return 0;
}

vector<vector<int>> createGraph(fstream& f){
    int numVertices = 10;
    int head;
    int tail;
    
    vector<vector<int>> g(numVertices);
    
    while (f >> tail >> head) {//read line from file
//        g[tail].push_back(head);//create edge
        g[head].push_back(tail);//create edge

    }
    return g;
}

void DFS_Loop(vector<vector<int>>& g) {
    for(size_t i = g.size() - 1; i >= 1; --i){
        if (!vertices[i].explored){
            s = i;
            DFS(g, i, 1);
        }
    }
}

void DFS(vector<vector<int>>& g, size_t i, bool reverse=false){
    vertices[i].explored = true;
    vertices[i].leader = s;
    for (int j = 0; j < g[i].size(); ++j){
        int v = g[i][j];
        if (v == 0 ){
            cout << "ddd ";
        }//cout << "i: " << i << endl;
        //cout << "j: " << j << endl;
        //cout << "v: " << g[i][j] << endl;
        if (!vertices[v].explored){
            DFS(g, j);
        }
    }
    ++t;
    vertices[i].finishingTime = t;
}
