//
//  main.cpp
//  graph
//
//  Created by Nick on 8/30/19.
//  Copyright © 2019 Nick. All rights reserved.
//

#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <iterator>
#include <stdexcept>

using namespace std;

struct Vertex {
    int label;//identifier for Vertex
    bool explored;
    int finishingTime;
    int leader;
    int SSC;//strongly connected compentent ID
};

struct Edge {
    int label;//identifier for Edge
    int tail;
    int head;
};

struct Graph {
    vector<Edge> edges;
    vector<Vertex> vertices;
};

int t = 0; //global variable to track finishing times (e.g. - number of nodes processed)
int s = NULL;//global veraible to track the source vertex from which DFS was initaited

void printEdge(const Edge&);
void DFS_Loop(Graph&);
void DFS(Graph&, int i, bool);
Graph createGraph(fstream&);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    fstream f {"list.txt", ios::in | ios::binary}; //open file for input
    
    if (!f){//program failes to open data file}
        cout << "File could not be opened\n";
        return 9;
    }
    
    Graph g = createGraph(f);
    
    DFS_Loop(g);
    
    return 0;
}

Graph createGraph(fstream& f){
    int i = 0;
    int numEdges = 0;
    int head;
    int tail;
    Edge edge;
    Graph g; //structure representing graph
    
    while (f >> tail >> head) {//read line from file
        
        edge = {i, tail, head};//create edge
        
        int m = max (head, tail);
        if (m > numEdges){
            numEdges = m;
        }
        
        g.edges.push_back(edge);//add edge to vector
        ++i;
    }
    
    for (int i = 0; i < numEdges; ++i){
        g.vertices.push_back({i, false, NULL, NULL, NULL});
    }

    return g;
}

void printEdge(const Edge& e) {
    cout << "edge: " << e.label << "\nhead: " << e.head << "\ntail: " << e.tail << endl;
}

void DFS_Loop(Graph& g) {
    for(int i = g.vertices.size(); i >= 1; --i){
        if (!g.vertices[i].explored){
            s = i;
            DFS(g, i, 1);
        }
    }
}

void DFS(Graph& g, int i, bool reverse=false){
    g.vertices[i].explored = true;
    g.vertices[i].leader = i;
    
    
}
