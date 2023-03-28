#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const string s = "NESW";

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct Myset{
    vector<int> p, out;

    Myset(int n){
        p.resize(n, -1);
        out.resize(n);
    }

    int find(int x){
        if(p[x] < 0) return x;
        return p[x] = find(p[x]);
    }

    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return;
        p[u] = v;
    }
};

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<string> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    vector<Myset> nxt(4, Myset(n * m));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(v[i][j] != '.') continue;
            for(int k = 0; k < 4; k++){
                int ny = i + dy[k], nx = j + dx[k];
                if(ny < 0 || ny >= n || nx < 0 || nx >= m){
                    nxt[k].out[i * m + j] = 1;
                }
                else{
                    nxt[k].merge(i * m + j, ny * m + nx);
                }
            }
        }
    }
    queue<pair<int, int> > q;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(v[i][j] == '.') continue;
            int d = s.find(v[i][j]);
            int ny = i + dy[d], nx = j + dx[d];
            if(ny < 0 || ny >= n || nx < 0 || nx >= m || nxt[d].out[nxt[d].find(ny * m + nx)]){
                q.push({i, j});
            }
        }
    }
    while(q.size()){
        int y, x;
        tie(y, x) = q.front();
        q.pop();
        cout << '(' << y << ',' << x << ')' << '\n';
        for(int k = 0; k < 4; k++){
            int ny = y + dy[k], nx = x + dx[k];
            if(ny < 0 || ny >= n || nx < 0 || nx >= m){
                nxt[k].out[y * m + x] = 1;
            }
            else{
                nxt[k].merge(y * m + x, ny * m + nx);
            }
        }
        for(int k = 0; k < 4; k++){
            int p = nxt[k].find(y * m + x);
            if(nxt[k].out[p]) continue;
            int od = (k + 2) % 4;
            if(s.find(v[p / m][p % m]) != od) continue;
            int py = p / m, px = p % m;
            if(!nxt[od].out[nxt[od].find((py + dy[od]) * m + (px + dx[od]))]) continue;
            q.push({py, px});
        }
    }
}
