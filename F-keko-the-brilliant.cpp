#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#define MAX 100100
#define MOD 1000000000
using namespace std;

int W[200200];
vector<int> G[200200];

int dfs(int p, int v, int minn) {
    int total1 = W[v] < minn ? 1 : 0;
    int total2 = W[v] < minn ? 1 : 0;
    bool inj = false;
    for(int i=0; i<G[v].size(); i++) {
        int u = G[v][i];
        if (u == p) continue;
        //cout << " " << v << "(" << W[v] << ") " << u << "(" << W[u] << ")" << endl;
        
        if (W[u] < W[v]) inj = true;
        total1 += dfs(v, u, minn);
    }
    
    for(int i=0; i<G[v].size(); i++) {
        int u = G[v][i];
        if (u == p) continue;
        //cout << " " << v << "(" << W[v] << ") " << u << "(" << W[u] << ")" << endl;
        total2 += dfs(v, u, max(minn, W[v]));
    }
    return min(total1 + (inj ? 1 : 0), total2);
}



int main() {
    int N;
    while(cin >> N) {
        for(int i=1; i<=N; i++) {
            cin >> W[i];
            G[i].clear();
        }
        
        for(int i=0; i<N-1; i++) {
            int a, b; cin >> a >> b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        cout << dfs(-1, 1, 0) << endl;
    }
}
