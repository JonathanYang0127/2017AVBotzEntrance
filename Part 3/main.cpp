//Part 3

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
ifstream fin("coins2.in");
ofstream fout("coins2.out");
int v, k;
vector<int> values;

int main() {
    fin>>v;
    int dp[v];
    while(!fin.eof()){
        fin>>k;
        values.push_back(k);
    }
    dp[0] = 0;
    for(int x = 1; x<=v; x++){
        dp[x] = 1<<29;
        for(int y = 0; y<values.size(); y++){
            for(int p = 1; x-p*values[y]>=0; p++){
                dp[x] = min(dp[x], dp[x-p*values[y]]+p);
            }
        }
        fout<<x<<" "<<dp[x]<<endl;
    }
    fout<<dp[v]<<endl;
}
