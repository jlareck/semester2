//
//  main.cpp
//  testTreeAndGraph
//
//  Created by Mykola Medynsky on 5/17/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <list>
#include <utility>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 100
typedef  pair<int, int> iPair;
  vector< pair<int, iPair> > edges;
struct Node{

    int dest;
    int cost;
};
void addEdge(list<Node> graph[], int source, int dest, int cost, bool flag) {
    Node newNode;
    if (flag){
        newNode.dest = dest;
        newNode.cost = cost;
        graph[source].push_back(newNode);
        newNode.dest = source;
        newNode.cost = cost;
        graph[dest].push_back(newNode);
        edges.push_back({cost, {source, dest}});
    }
    else{
        newNode.dest = dest;
        newNode.cost = cost;
        graph[source].push_back(newNode);
    }
}
void printGraph(list<Node> graph[], int V)
{
    for (int v = 0; v < V; ++v)
    {
        cout << "\n Adjacency list of vertex "
        << v << "\n head ";
        for (auto x : graph[v])
            cout << "->" << x.dest;
        printf("\n");
    }
}
void DFSUtil(int v, bool visited[], list<Node> graph[] )
{

    visited[v] = true;
  //  cout << v << " ";    // I am using this function in finding min spanning tree that's why I commented this line
    
    for (auto x : graph[v])
        if (!visited[x.dest])
            DFSUtil(x.dest, visited, graph);
}
bool findElement(const int& v,const int& i, list<Node> graph[]){
 
    for (auto x: graph[v]){
        if (x.dest == i){
            return true;
        }
    }
    return false;
}
void dfsSpanningTree(int v, int n, bool visited[], list<Node> graph[]) {
    visited[v] = true;
    for (int i = 0; i < n; i++) {
        if (!visited[i] && findElement(v, i, graph)) {
            printf("(%d %d)\n", v, i);
            dfsSpanningTree(i, n, visited, graph);
        }
    }
}
void DFS(int v, list<Node>graph[])
{
    // Mark all the vertices as not visited
    bool *visited = new bool[MAX];
    for (int i = 0; i < MAX; i++)
        visited[i] = false;
    
    // Call the recursive helper function
    // to print DFS traversal
    DFSUtil(v, visited, graph);
}
void dijkstra(list<Node> adj[], double dist[], int start, int size) {
    
    
    for(int i = 0; i < size; i++) {
        dist[i] = 9999;
    }
    
    dist[start] = 0;
    list<int> queueOfVertices;
    
    for(int i = 0; i < size; i++) {
        queueOfVertices.push_back(i);
    }
    
    while(!queueOfVertices.empty()) {
        list<int> :: iterator i;
        i = min_element(queueOfVertices.begin(), queueOfVertices.end());
        int u = *i;
        queueOfVertices.remove(u);
        
        
        for(auto it: adj[u]) {
            //  cout <<u<< " " <<it->cost << " "<< it->dest<<endl;
            if((dist[u]+(it.cost)) < dist[it.dest]) {
                dist[it.dest] = (dist[u]+(it.cost));
            }
        }
    }
}
bool isConnected(int size, list<Node> graph[])
{


    bool *visited = new bool[size];
    for(int v = 0; v < size; v++)
        visited[v] = false;
    // Find all reachable vertices from first vertex
    DFSUtil(0, visited, graph);
    
    // If set of reachable vertices includes all,
    // return true.
    for (int i=1; i<size; i++)
        if (visited[i] == false)
            return false;
    
    return true;
}
void deleteFromVector(list<Node> vec[], int u, int v) {
    list<Node>::iterator i = vec[u].begin();
    while((*i).dest!=v) {
        i++;
    
    }
    vec[u].erase(i);
}
// This function assumes that edge (u, v)
// exists in graph or not,
void reverseDeleteMST(list<Node> adj[], int size)
{
    // Sort edges in increasing order on basis of cost
    sort(edges.begin(), edges.end());
    
    int mst_wt = 0;  // Initialize weight of MST
    
    cout << "Edges in MST\n";
    
    // Iterate through all sorted edges in
    // decreasing order of weights
    for (int i = edges.size()-1; i>=0; i--)
    {
        Node u, v;
        u.dest = edges[i].second.first;
        v.dest = edges[i].second.second;
        
        // Remove edge from undirected graph
        deleteFromVector(adj, u.dest, v.dest);
        deleteFromVector(adj, v.dest, u.dest);
        
        // Adding the edge back if removing it
        // causes disconnection. In this case this
        // edge becomes part of MST.
        if (isConnected(size, adj) == false)
        {
            adj[u.dest].push_back(v);
            adj[v.dest].push_back(u);
            
            // This edge is part of MST
            cout << "(" << u.dest << ", " << v.dest << ") \n";
            mst_wt += edges[i].first;
        }
    }
    
    cout << "Total weight of MST is " << mst_wt;
}

void connectedComponents(list<Node> graph[], int n)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[n];
    for(int v = 0; v < n; v++)
        visited[v] = false;
    
    for (int v=0; v<n; v++)
    {
        if (visited[v] == false)
        {
            // print all reachable vertices
            // from v
            DFSUtil(v, visited, graph);
            
            cout << "\n";
        }
    }
}
void task1(){
    list<Node> graph[MAX];
    bool flag = true;
   
    addEdge(graph, 0, 1, 4, flag);
    addEdge(graph, 0, 7, 8, flag);
    addEdge(graph, 1, 2, 8, flag);
    addEdge(graph, 1, 7, 11, flag);
    addEdge(graph, 2, 3, 7, flag);
    addEdge(graph, 2, 8, 2, flag);
    addEdge(graph, 2, 5, 4, flag);
    addEdge(graph, 3, 4, 9, flag);
    addEdge(graph, 3, 5, 14, flag);
    addEdge(graph, 4, 5, 10, flag);
    addEdge(graph, 5, 6, 2, flag);
    addEdge(graph, 6, 7, 1, flag);
    addEdge(graph, 6, 8, 6, flag);
    addEdge(graph, 7, 8, 7, flag);
    int size = 9;
//    addEdge(graph, 0, 4, 3, flag);
//    addEdge(graph, 0, 3, 4, flag);
//    addEdge(graph, 1, 2, 2, flag);
//    addEdge(graph, 1, 4, 6, flag);
//    addEdge(graph, 1, 5, 5, flag);
//    addEdge(graph, 2, 3, 5, flag);
//    addEdge(graph, 2, 5, 5, flag);
//    addEdge(graph, 5, 3, 5, flag);
  //  addEdge(graph, 5, 6, 7, flag);
    printGraph(graph, size);
    connectedComponents(graph, size);
    double dist[size];
    int start = 0;
    
    dijkstra(graph, dist, start, size);
    for(int i = 0; i<size; i++)
        if(i != start)
            cout << start << " to " << i << ", Cost: " << dist[i] << endl;
    bool *visited = new bool[size];
    for(int v = 0; v < size; v++)
        visited[v] = false;
    cout << "Spanning tree"<<endl;
    dfsSpanningTree(0, size,  visited, graph);
    
    reverseDeleteMST(graph, size);
}
void task2(){
    list<Node> graph[MAX];
    bool flag = false;
    addEdge(graph, 0, 1, 5, flag);
    addEdge(graph, 0, 2, 5, flag);
    addEdge(graph, 1, 2, 5, flag);
    addEdge(graph, 2, 0, 5, flag);
    addEdge(graph, 2, 3, 5, flag);
    addEdge(graph, 3, 3, 5, flag);
    DFS(2, graph);
    
}
int main(int argc, const char * argv[]) {
    
    srand(time(nullptr));
    task1();
    return 0;
}

