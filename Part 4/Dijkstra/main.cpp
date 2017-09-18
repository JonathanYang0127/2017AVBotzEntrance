#include <iostream>
#include <fstream>
using namespace std;
ifstream fin("sum.in");
ofstream fout("sum.out");
int V=9;
int r, c;
int INF = 999999;
int dist[1000000];
int graph[10000][10000];
int grid[100][100];


int minDistance(int dist[], bool visited[]){
    int min = 1<<30, min_index = -1;
    for (int v = 0; v < V; v++){
        if (visited[v] == false && dist[v] <= min){
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}
void dijkstra(int src){
    bool visited[V];
    for (int i = 0; i < V; i++){
        dist[i] = 1<<30;
        visited[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < V-1; count++){
        int u = minDistance(dist, visited);
        visited[u] = true;
        for (int v = 0; v < V; v++){
            if (!visited[v] && graph[u][v]!=INF && dist[u] != 1<<30 && dist[u]+graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

bool valid(int a, int b){
    return a>=0 && b>=0 && a<r && b<c;
}

int main (){
    fin>>r>>c;
    V = r*c;
    for(int x = 0; x<r; x++){
        for(int y = 0; y<c; y++){
            fin>>grid[x][y];
        }
    }
    memset(graph, INF, sizeof(graph));
    for(int x = 0; x<r; x++){
        for(int y = 0; y<c; y++){
            if(valid(x-1, y)){
                graph[y+c*x][y+c*(x-1)] = grid[x-1][y];
            }
            if(valid(x+1, y)){
                graph[y+c*x][y+c*(x+1)] = grid[x+1][y];
            }
            if(valid(x, y+1)){
                graph[y+c*x][y+1+c*x] = grid[x][y+1];
            }
            if(valid(x, y-1)){
                graph[y+c*x][y-1+c*x] = grid[x][y-1];
            }
        }
    }
    dijkstra(0);
    fout<<dist[(c-1)+(r-1)*c]+grid[0][0]<<endl;
}
