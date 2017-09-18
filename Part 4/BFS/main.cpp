#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
//notice that dp works if values are > 0, but since I can't assume that, I will use a bfs
ifstream fin("sum.in");
ofstream fout("sum.out");
int r, c;

int main() {
    fin>>r>>c;
    int grid[r][c];
    int values[r][c];
    for(int x = 0; x<r; x++){
        for(int y = 0; y<c; y++){
            fin>>grid[x][y];
            values[x][y] = 1<<30;
        }
    }
    queue<pair<int, int> > q;
    q.push(make_pair(0, 0));
    values[0][0] = grid[0][0];
    while(!q.empty()){
        int a = q.front().first; int b = q.front().second; q.pop();
        if(a == r-1 && b == c-1){
            continue;
        }
        if(a>0 && values[a-1][b] > values[a][b]+grid[a-1][b]){
            values[a-1][b] = values[a][b]+grid[a-1][b];
            q.push(make_pair(a-1, b));
        }
        if(a<r-1 && values[a+1][b] > values[a][b]+grid[a+1][b]){
            values[a+1][b] = values[a][b]+grid[a+1][b];
            q.push(make_pair(a+1, b));

        }
        if(b>0 && values[a][b-1] > values[a][b]+grid[a][b-1]){
            values[a][b-1] = values[a][b]+grid[a][b-1];
            q.push(make_pair(a, b-1));

        }
        if(b<r-1 && values[a][b+1] > values[a][b]+grid[a][b+1]){
            values[a][b+1] = values[a][b]+grid[a][b+1];
            q.push(make_pair(a, b+1));
        }
    }
    fout<<values[r-1][c-1]<<endl;
}
