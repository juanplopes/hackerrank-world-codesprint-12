#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include<sstream>
#define MAX 100100
#define MOD 1000000000
using namespace std;

long long F[50];
long long fat(long long v) {
    if (v >= 40) return 0;
    return F[v];
}

struct Slot {
    int a, b, pending;
    vector<int> V;
    
    Slot() {  }
    Slot(int a, int b) : V(41, 0), a(a), b(b), pending(0) {
        V[0] = b-a+1;
    }
    
    void add(int value) {
        if (value == 0) return;
        value = min(value, 40);
        pending += value;
        for(int i=40+value-1; i>=value; i--) {
            V[min(i, 40)] += V[i-value];
            V[i-value] = 0;
        }
    }   
    
    void set(int index) {
        V = vector<int>(41, 0);
        V[min(index, 40)] = 1;
    }
    
    long long value() {
        long long sum = 0;
        for(int i=1; i<=40; i++) {
            sum += V[i] * fat(i);
            sum %= MOD;
        }
        return sum;
    }
    
    inline Slot operator+(const Slot& other) const {
        Slot c (min(a, other.a), max(b, other.b));
        for(int i=0; i<=40; i++)
            c.V[i] = V[i] + other.V[i];
        return c;
    }
};

struct SegTree {
    Slot V[300100];
    
    void init(int i, int a, int b) {
        V[i] = Slot(a, b);
        if (a == b) return;
        int mid = (a+b)/2;
        init(i*2+1, a, mid);
        init(i*2+2, mid+1, b);
    }
    
    void add(int i, int a, int b, int value, int pending) {
        V[i].add(pending);
        if (a > V[i].b or b < V[i].a) return;
        if (a <= V[i].a and b >= V[i].b) {
            V[i].add(1);
            return;
        }
        
        add(i*2+1, a, b, value, V[i].pending);
        add(i*2+2, a, b, value, V[i].pending);
        V[i] = V[i*2+1] + V[i*2+2];
    }

    void set(int i, int a, int value, int pending) {
        V[i].add(pending);
        if (a > V[i].b or a < V[i].a) return;
        if (a == V[i].a and a == V[i].b) {
            V[i].set(value);
            return;
        }

        set(i*2+1, a, value, V[i].pending);
        set(i*2+2, a, value, V[i].pending);
        V[i] = V[i*2+1] + V[i*2+2];
    }
    
    long long query(int i, int a, int b, int pending) {
        V[i].add(pending);
        if (a > V[i].b or b < V[i].a) return 0;
        if (a <= V[i].a and b >= V[i].b) return V[i].value();
        
        long long value = 0;
        value += query(i*2+1, a, b, V[i].pending);
        value += query(i*2+2, a, b, V[i].pending);

        V[i] = V[i*2+1] + V[i*2+2];
        return value % MOD;
    } 
    
    void init(int a, int b) { init(0, a, b); }
    void add(int a, int b, int value) { add(0, a, b, value, 0); } 
    void set(int a, int value) { set(0, a, value, 0); }
    long long query(int a, int b) { return query(0, a, b, 0); }
};

SegTree T;

int main() {
    F[0] = 1;
    for(int i=1; i<=40; i++)
        F[i] = (F[i-1] * i) % MOD;
        
    int N, M;
    while(cin >> N >> M) {
        T.init(1, N);

        for(int i=1; i<=N; i++) {
            long long temp; cin >> temp;
            T.set(i, temp);
        }    
        
        for(int i=0; i<M; i++) {
            long long t, a, b;
            cin >> t >> a >> b;
            if (t==1) {
                T.add(a, b, 1);
            } else if (t==2) {
                cout << T.query(a, b) << endl;
            } else if (t == 3) {
                T.set(a, b);
            }
        }
    }
}
