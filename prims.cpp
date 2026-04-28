// Prims algorthim 
#include <iostream> 
using namespace std; 
 
#define V 100 
#define INF 9999 
 
int n, e; 
int graph[V][V]; 
 
void input() { 
 
    cout << "Enter number of ver ces: "; 
    cin >> n; 
 
    cout << "Enter number of edges: "; 
    cin >> e; 
 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < n; j++) { 
            graph[i][j] = 0; 
        } 
    } 
 
    cout << "Enter edges (u v weight):\n"; 
    for (int i = 0; i < e; i++) { 
        int u, v, w; 
        cin >> u >> v >> w; 
        graph[u][v] = w; 
        graph[v][u] = w;    
    } 
} 
 
 
void primMST() { 
 
    int visited[V] = {0}; 
    visited[0] = 1;    
 
    int edgeCount = 0; 
    int totalCost = 0; 
 
    cout << "\nEdges in Minimum Spanning Tree:\n"; 
 
    while (edgeCount < n - 1) { 
 
        int min = INF; 
        int a = -1, b = -1; 
 
       
        for (int i = 0; i < n; i++) { 
            if (visited[i]) { 
                for (int j = 0; j < n; j++) { 
                    if (!visited[j] && graph[i][j] != 0) { 
                        if (graph[i][j] < min) { 
                            min = graph[i][j]; 
                            a = i; 
                            b = j; 
                        } 
                    } 
                } 
            } 
        } 
 
        cout << a << " - " << b << " : " << min << endl; 
 
        visited[b] = 1; 
        totalCost += min; 
        edgeCount++; 
    } 
 
    cout << "\nTotal MST Cost = " << totalCost << endl; 
} 
 
 
int main() { 
 
    input();       
    primMST();     
 
    return 0; 
} 
 
 
 
 
