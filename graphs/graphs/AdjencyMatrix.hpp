//
//  AdjencyMatrix.hpp
//  graphs
//
//  Created by Mykola Medynsky on 6/24/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#ifndef AdjencyMatrix_hpp
#define AdjencyMatrix_hpp

#include <stdio.h>
#include <iostream>
#include <stack>
#include <vector>
#include <iterator>
#include <iomanip>
using namespace std;
#define MAX 100
class AdjencyMatrix{
public:
    int matrix[MAX][MAX];
    
    bool flag;
    void addEdge(int from, int to, int cost);
    void dijkstra(int src);
    bool isConnected(bool newFlag);
    void printMatrix();
    void connectedComponents(bool newFlag);
    void dfsSpanningTree(int v);
    void topologicalSort();
    void minimumSpanningTree(bool newFlag);
    AdjencyMatrix(int vertices) {
        if (vertices>MAX) {
            throw::invalid_argument("Vertex not in graph");
        }
        vertexCount = vertices;
        for(int i = 0; i < vertexCount; i++) {
            for(int j = 0; j < vertexCount; j++) {
                matrix[i][j] = 0;
            }
        }
    }
private:
    typedef  pair<int, int> iPair;
    vector< pair<int, iPair> > edges;
    int vertexCount;
    bool *visited = new bool[MAX];
    void falseInitialization();
    void DFS(int i, bool newFlag);
    void topologicalSortUtil(int v, stack<int> &stack, bool visited[]);
    int minDistance(int dist[], bool sptSet[]);
    void dfsSpanningTreeUtil(int v);
};
#endif /* AdjencyMatrix_hpp */
