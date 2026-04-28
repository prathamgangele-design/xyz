// Dijkstra'
#include<iostream> 
using namespace std; 
 
#define MAX 100 
#define INF 99999 
 
int main() { 
 
    int n; 
    cout << "Enter number of loca ons: "; 
    cin >> n; 
 
    int graph[MAX][MAX]; 
 
    cout << "Enter adjacency matrix (0 if no path):\n"; 
    for(int i=0;i<n;i++) { 
        for(int j=0;j<n;j++) { 
            cin >> graph[i][j]; 
            if(graph[i][j] == 0 && i != j) 
                graph[i][j] = INF; 
        } 
    } 
 
    int src; 
    cout << "Enter source loca on: "; 
    cin >> src; 
 
    int dist[MAX]; 
    bool visited[MAX]; 
 
    for(int i=0;i<n;i++) { 
        dist[i] = INF; 
        visited[i] = false; 
    } 
 
    dist[src] = 0; 
 
    for(int count=0; count<n-1; count++) { 
 
        int min = INF, u = -1; 
 
        for(int i=0;i<n;i++) { 
            if(!visited[i] && dist[i] < min) { 
                min = dist[i]; 
                u = i; 
            } 
        } 
 
        visited[u] = true; 
 
        for(int v=0; v<n; v++) { 
            if(!visited[v] && graph[u][v] != INF && 
               dist[u] + graph[u][v] < dist[v]) { 
                dist[v] = dist[u] + graph[u][v]; 
            } 
        } 
    } 
 
    cout << "\nShortest distances from source:\n"; 
    for(int i=0;i<n;i++) { 
        cout << "To " << i << " = " << dist[i] << endl; 
    } 
 
    return 0; 
}
