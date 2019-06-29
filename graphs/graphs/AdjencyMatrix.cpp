//
//  AdjencyMatrix.cpp
//  graphs
//
//  Created by Mykola Medynsky on 6/24/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include "AdjencyMatrix.hpp"
//AdjencyMatrix graph = AdjencyMatrix(10);

void AdjencyMatrix::addEdge(int from, int to, int cost) {
    if (from >= vertexCount|| to >= vertexCount) {
        throw std::invalid_argument("Vertex not in graph");
    }
    matrix[from][to] = cost;
    if (!flag) {
        matrix[to][from] = cost;
        edges.push_back({cost,{from, to}});
    }

}
void AdjencyMatrix::printMatrix(){
    for (int i = 0; i < vertexCount; i++){
        for (int j = 0; j < vertexCount; j++){
            cout<< setw(5) << matrix[i][j] ;
        }
        cout<< endl;
    }
}
void AdjencyMatrix::connectedComponents(bool newFlag){
    falseInitialization();
    for (int v=0; v<vertexCount; v++)
    {
        if (visited[v] == false)
        {
            DFS(v, newFlag);
            cout << "\n";
        }
    }
}
void AdjencyMatrix::falseInitialization(){
    for (int i = 0; i < vertexCount; i++)
    {
        visited[i] = false;
    }
}
void AdjencyMatrix::DFS(int i, bool newFlag) {
    int j;
    if (flag) {
        cout << i <<" ";
    }
    visited[i] = true;
    for(j = 0; j < vertexCount; j++)
        if(!visited[j] && matrix[i][j] != 0)
            DFS(j, newFlag);
}

int AdjencyMatrix::minDistance(int dist[], bool sptSet[])
{

    int min = INT_MAX, min_index = 0;
    
    for (int v = 0; v < vertexCount; v++)
        if (sptSet[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    return min_index;
}
void AdjencyMatrix::dijkstra(int src){
    int dist[vertexCount];
    
    bool sptSet[vertexCount];
    for (int i = 0; i < vertexCount; i++){
        dist[i] = 9999;
        sptSet[i] = false;
    }

    dist[src] = 0;
    

    for (int count = 0; count < vertexCount-1; count++)
    {

        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < vertexCount; v++){
            if (!sptSet[v] && matrix[u][v] && dist[u] != MAX  && dist[u]+matrix[u][v] < dist[v])
                dist[v] = dist[u] + matrix[u][v];
        }
    }
    
    
    
    for (int i = 0; i < vertexCount; i++)
        cout<< src<< " to " << i << " Cost: " << dist[i] <<endl;
    
}

void AdjencyMatrix::topologicalSortUtil(int v, stack<int> &stack, bool visited[])
{

    visited[v] = true;
    for (int i = 0; i < vertexCount; i++){
        if (matrix[v][i]!=0 && !visited[i]){
            topologicalSortUtil(i,  stack, visited);
        }
    }
    stack.push(v);
}


void AdjencyMatrix::topologicalSort()
{
    stack<int> stack;
    falseInitialization();
    for (int i = 0; i < vertexCount; i++)
        if (visited[i] == false){
            
            topologicalSortUtil(i, stack, visited);

        }
    
    while (stack.empty() == false)
    {
        cout << stack.top() << " ";
        stack.pop();
    }
}

void AdjencyMatrix::dfsSpanningTreeUtil(int v){
    visited[v] = true;
    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i] &&  matrix[v][i]) {

            cout << "("<< v << " " << i << ")" <<endl;
            dfsSpanningTreeUtil(i);
        }
    }
}
void AdjencyMatrix::dfsSpanningTree(int v){
    falseInitialization();
    dfsSpanningTreeUtil(v);
}
bool AdjencyMatrix::isConnected(bool newFlag){
    
    falseInitialization();
    
    DFS(0, newFlag);
    
    for (int i = 1; i< vertexCount; i++)
        if (visited[i] == false)
            return false;
    
    return true;
}
void AdjencyMatrix::minimumSpanningTree(bool newFlag){
    sort(edges.begin(), edges.end());
    
    int mst_wt = 0;  // Initialize weight of MST
    int matrixCopy[MAX][MAX];
    for (int i = 0; i < vertexCount; i++){
        for (int j = 0; j < vertexCount; j++){
            matrixCopy[i][j] = matrix[i][j];
        }
    }
    cout << "Edges in MST" << endl;
    
    // Iterate through all sorted edges in
    // decreasing order of weights
    for (int i=edges.size()-1; i>=0; i--)
    {
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        
        // Remove edge from undirected graph
        matrix[u][v] = 0;
        matrix[v][u] = 0;
        
        // Adding the edge back if removing it
        // causes disconnection. In this case this
        // edge becomes part of MST.
        if (isConnected(newFlag) == false)
        {
            
            matrix[u][v] = 1;
            matrix[v][u] = 1;
            
            // This edge is part of MST
            cout << "(" << u << ", " << v << ")" << endl;
            mst_wt += edges[i].first;
        }
    }
}
