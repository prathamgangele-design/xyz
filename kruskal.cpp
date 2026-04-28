//Kruskal’s algorithm 
 
#include <iostream> 
using namespace std; 
 
#define V 100 
#define E 100 
 
 
struct Edge { 
    int u, v, w; 
}; 
 
Edge edges[E]; 
int parent[V]; 
 
 
int findParent(int i) { 
    while (parent[i] != i) 
        i = parent[i]; 
    return i; 
} 
 
 
void unionSet(int a, int b) { 
    parent[b] = a; 
} 
 
int main() { 
 
    int n, e; 
    cout << "Enter number of ver ces: "; 
    cin >> n; 
 
    cout << "Enter number of edges: "; 
    cin >> e; 
 
    
    cout << "Enter edges (u v weight):\n"; 
    for (int i = 0; i < e; i++) { 
        cin >> edges[i].u >> edges[i].v >> edges[i].w; 
    } 
 
    
    for (int i = 0; i < e - 1; i++) { 
        for (int j = 0; j < e - i - 1; j++) { 
            if (edges[j].w > edges[j + 1].w) { 
                Edge temp = edges[j]; 
                edges[j] = edges[j + 1]; 
                edges[j + 1] = temp; 
            } 
        } 
    } 
 
    
    for (int i = 0; i < n; i++) 
        parent[i] = i; 
 
    int cost = 0; 
    int count = 0; 
 
    cout << "\nEdges in Minimum Spanning Tree:\n"; 
 
    for (int i = 0; i < e; i++) { 
 
        int u = findParent(edges[i].u); 
        int v = findParent(edges[i].v); 
 
        // if no cycle 
        if (u != v) { 
            cout << edges[i].u << " - " << edges[i].v 
                 << " : " << edges[i].w << endl; 
 
            unionSet(u, v); 
            cost += edges[i].w; 
            count++; 
        } 
 
        if (count == n - 1) 
            break; 
    } 
 
    cout << "\nTotal MST Cost = " << cost << endl; 
 
    return 0; 
} 
