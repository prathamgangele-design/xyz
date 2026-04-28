// Dfs 
#include <iostream> 
using namespace std; 
 
#define MAX 100 
 
int N, M; 
int maze[MAX][MAX]; 
int visited[MAX][MAX]; 
 
 
int pathX[MAX*MAX], pathY[MAX*MAX]; 
int pathLen = 0; 
 
 
int dx[] = {1, -1, 0, 0}; 
int dy[] = {0, 0, 1, -1}; 
 
 
bool isSafe(int x, int y) { 
    return (x >= 0 && x < N && 
            y >= 0 && y < M && 
            maze[x][y] == 0 && 
            !visited[x][y]); 
} 
 
 
bool dfs(int x, int y, int gx, int gy) { 
 
    visited[x][y] = 1; 
 
    
    pathX[pathLen] = x; 
    pathY[pathLen] = y; 
    pathLen++; 
 
    
    if (x == gx && y == gy) 
        return true; 
 
    
    for (int i = 0; i < 4; i++) { 
        int nx = x + dx[i]; 
        int ny = y + dy[i]; 
 
        if (isSafe(nx, ny)) { 
            if (dfs(nx, ny, gx, gy)) 
                return true; 
        } 
    } 
 
   
    pathLen--; 
    return false; 
} 
 
int main() { 
 
    int sx, sy, gx, gy; 
 
    cout << "Enter rows and columns: "; 
    cin >> N >> M; 
 
    cout << "Enter maze (0=open, 1=blocked):\n"; 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++) { 
            cin >> maze[i][j]; 
            visited[i][j] = 0; 
        } 
    } 
 
    cout << "Enter start (row col): "; 
    cin >> sx >> sy; 
 
    cout << "Enter goal (row col): "; 
    cin >> gx >> gy; 
 
    if (maze[sx][sy] == 1 || maze[gx][gy] == 1) { 
        cout << "Invalid start or goal\n"; 
    } 
    else if (dfs(sx, sy, gx, gy)) { 
 
        cout << "\nPath (start to goal):\n"; 
        for (int i = 0; i < pathLen; i++) { 
            cout << "(" << pathX[i] << "," << pathY[i] << ") "; 
        } 
        cout << "\nPath Found\n"; 
    } 
    else { 
        cout << "\nNo Path Found\n"; 
    } 
 
    return 0; 
} 
