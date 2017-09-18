//Part 2

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
ifstream fin("coins.in");
ofstream fout("coins.out");
double v;
vector<int> values;

int main() {
    fin>>v;
    values.push_back(1);
    values.push_back(5);
    values.push_back(10);
    values.push_back(25);
    int dp[(int)(v*100)];
    dp[0] = 0;
    for(int x = 1; x<=v*100; x++){
        dp[x] = 1<<29;
        for(int y = 0; y<values.size(); y++){
            for(int p = 1; x-p*values[y]>=0; p++){
                dp[x] = min(dp[x], dp[x-p*values[y]]+p);
            }
        }
    }
    fout<<dp[(int)(v*100)]<<endl;
}
