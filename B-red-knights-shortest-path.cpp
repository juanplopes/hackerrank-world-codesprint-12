#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Pos {
    int x, y, p, type, steps;
    Pos(int x, int y, int p, int type, int steps) : 
        x(x), y(y), p(p), type(type), steps(steps) {}
};

vector<Pos> Q;
bool V[300][300];
vector<string> A;

void push(int N, int x, int y, int p, int type, int steps) {
    if (x < 0 || x >= N || y < 0 || y >= N || V[x][y]) return;
    V[x][y] = true;
    Q.push_back(Pos(x, y, p, type, steps));
}

string name(int type) {
    if (type == 1) return "L";
    if (type == 2) return "R";
    if (type == 3) return "UL";
    if (type == 4) return "UR";
    if (type == 5) return "LL";
    if (type == 6) return "LR";
    return "ERROR";
}

int main() {
    int N;
    while(cin >> N) {
        memset(V, 0, sizeof V);
        Q.clear();
        
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        push(N, x1, y1, -1, -1, 0);
        
        bool found = false;
        for(int i=0; i<Q.size(); i++) {
            Pos z = Q[i];
            
            if (z.x == x2 and z.y == y2) {
                A.clear();
                while(z.p != -1) {
                    A.push_back(name(z.type));
                    z = Q[z.p];
                }
                cout << A.size() << endl;
                for(int i=A.size()-1; i>=0; i--) {
                    cout << (i < A.size()-1 ? " " : "") << A[i];
                }
                cout << endl;
                found = true;
                break;
            }
            
            push(N, z.x - 2, z.y - 1, i, 3, z.steps+1); //UL
            push(N, z.x - 2, z.y + 1, i, 4, z.steps+1); //UR

            push(N, z.x, z.y + 2, i, 2, z.steps+1); //R
            push(N, z.x + 2, z.y + 1, i, 6, z.steps+1); //LR

            push(N, z.x, z.y - 2, i, 1, z.steps+1); //L
            push(N, z.x + 2, z.y - 1, i, 5, z.steps+1); //LL
        }

        if (!found) {
            cout << "Impossible" << endl;
        }
    }
}
