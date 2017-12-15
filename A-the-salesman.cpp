#include <iostream>
using namespace std;

int main() {
    int tests; cin >> tests;
    int N;
    while(cin >> N) {
        int minn = 0x1f1f1f1f, maxx = 0;
    
        for(int i=0; i<N; i++) {
            int temp; cin >> temp;
            minn = min(minn, temp);
            maxx = max(maxx, temp);
        }
        
        cout << maxx - minn << endl;
    }
}
