
#include <iostream> 
using namespace std; 
 
#define MAX 100 
 
int N, M; 
 
 
int qx[MAX*MAX], qy[MAX*MAX]; 
int front = 0, rear = 0; 
 
int dx[] = {1, -1, 0, 0}; 
int dy[] = {0, 0, 1, -1}; 
 
 
bool isSafe(int maze[MAX][MAX], int visited[MAX][MAX], int x, int y) { 
    return (x >= 0 && x < N && 
            y >= 0 && y < M && 
            maze[x][y] == 0 && 
            visited[x][y] == 0); 
} 
 
void bfs(int maze[MAX][MAX], int sx, int sy, int gx, int gy) { 
 
    int visited[MAX][MAX] = {0}; 
 
     
    int parentX[MAX][MAX], parentY[MAX][MAX]; 
 
     
    front = rear = 0; 
    qx[rear] = sx; 
    qy[rear] = sy; 
    rear++; 
 
    visited[sx][sy] = 1; 
    parentX[sx][sy] = -1; 
    parentY[sx][sy] = -1; 
 
    bool found = false; 
 
    while (front < rear) { 
 
        int x = qx[front]; 
        int y = qy[front]; 
        front++; 
 
     
        if (x == gx && y == gy) { 
            found = true; 
            break; 
        } 
 
      
        for (int i = 0; i < 4; i++) { 
            int nx = x + dx[i]; 
            int ny = y + dy[i]; 
 
            if (isSafe(maze, visited, nx, ny)) { 
                qx[rear] = nx; 
                qy[rear] = ny; 
                rear++; 
 
                visited[nx][ny] = 1; 
 
               
                parentX[nx][ny] = x; 
                parentY[nx][ny] = y; 
            } 
        } 
    } 
 
     
    if (found) { 
        cout << "\nPath (start to goal):\n"; 
 
        int pathX[MAX*MAX], pathY[MAX*MAX]; 
        int len = 0; 
 
        int x = gx, y = gy; 
 
        
        while (x != -1 && y != -1) { 
            pathX[len] = x; 
            pathY[len] = y; 
            len++; 
 
            int px = parentX[x][y]; 
            int py = parentY[x][y]; 
 
            x = px; 
            y = py; 
        } 
 
        
        for (int i = len - 1; i >= 0; i--) { 
            cout << "(" << pathX[i] << "," << pathY[i] << ") "; 
        } 
 
        cout << "\nPath Found\n"; 
    } else { 
        cout << "\nNo Path Found\n"; 
    } 
} 
 
int main() { 
 
    int maze[MAX][MAX]; 
    int sx, sy, gx, gy; 
 
    cout << "Enter rows and columns: "; 
    cin >> N >> M; 
 
    cout << "Enter maze (0=open, 1=blocked):\n"; 
    for (int i = 0; i < N; i++) { 
        for (int j = 0; j < M; j++) { 
            cin >> maze[i][j]; 
        } 
    } 
 
    cout << "Enter start (row col): "; 
    cin >> sx >> sy; 
 
    cout << "Enter goal (row col): "; 
    cin >> gx >> gy; 
 
    if (maze[sx][sy] == 1 || maze[gx][gy] == 1) { 
        cout << "Invalid start or goal\n"; 
    } else { 
        bfs(maze, sx, sy, gx, gy); 
    } 
 
    return 0; 
} 