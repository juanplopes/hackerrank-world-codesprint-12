#include <iostream>
#include <vector>
#define PP 2000000
using namespace std;

vector<long long> W;
vector<long long> F;
bool P[PP];

long long answer(long long n) {
    if (n == 1) return 1;
    
    F.clear();
    for(int i=0; i<W.size() and n > 1;) {
        if (n % W[i] == 0) {
            F.push_back(W[i]);
            n /= W[i];
        } else {
            i++;
        }
    }
    if (n > 1) F.push_back(n);
    
    long long total = 1, current = 1;
    for(int i=F.size()-1; i>=0; i--) {
        //cout << " " << F[i] << endl;
        current *= F[i];
        total += current;
    }
    return total;    
}

int main() {
    for(long long i=2; i<PP; i++) {
        if (P[i]) continue;
        W.push_back(i);
        for(long long j=i*i; j<PP; j+=i) {
            P[j] = true;
        }
    }

    int N;
    while(cin >> N) {
        long long total = 0;
        for(int i=0; i<N; i++) {
            long long temp; cin >> temp;
            total += answer(temp);
        }
        cout << total << endl;
    }
}
