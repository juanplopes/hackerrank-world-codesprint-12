#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<stack>
#define MAX 8100000
#define MOD 1000000007ll
using namespace std;

long long T[MAX], W[MAX], MX[4010][4010], L[MAX], R[MAX];
stack<long long> Q;


int main() {
    int N;
    while(cin >> N) {
        for(int i=0; i<N; i++) {
            cin >> T[i];
        }
        
        int M = 0;
        for(int k=0; k<N; k++) {
            for(int i=0; i<N-k; i++) {
                long long maxx = k == 0 ? T[i] : max(MX[k-1][i], T[i+k]);
                MX[k][i] = maxx;
                W[M++] = maxx;
            }
        }
        
        while(Q.size()) Q.pop();
        Q.push(-1);
        for(int i=0; i<M; i++) {
            while(Q.top() >= 0 and W[Q.top()] < W[i])
                Q.pop();
            L[i] = i-Q.top();
            Q.push(i);            
        }
        
        while(Q.size()) Q.pop();
        Q.push(M);
        for(int i=M-1; i>=0; i--) {
            while(Q.top() < M and W[Q.top()] <= W[i])
                Q.pop();
            R[i] = Q.top()-i;
            Q.push(i);            
        }

        int test = 0;
        int expected = M*(M+1)/2;

        long long sum = 0;
        for(int i=0; i<M; i++) {
            sum += L[i] * R[i] % MOD * W[i] % MOD;
            sum %= MOD;
            
            test += L[i] * R[i];
        }
//        cout << " " << test << " " << expected << endl;
        
        cout << sum << endl;
    }
}
