#include "bits/stdc++.h"
using namespace std;

typedef long long ll;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

struct Myset{
    vector<int> p;

    Myset(int n){
        p.resize(n, -1);
    }

    int find(int x){
        if(p[x] < 0) return x;
        return p[x] = find(p[x]);
    }

    void merge(int u, int v){
        u = find(u);
        v = find(v);
        if(u == v) return;
        if(p[u] < p[v]){
            p[u] += p[v];
            p[v] = u;
        }
        else{
            p[v] += p[u];
            p[u] = v;
        }
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
    Myset ms(n * m);
    while(1){
        bool done = true;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(v[i][j] == '.') continue;
                for(int k = 0; k < 4; k++){
                    int ny = i + dy[k], nx = j + dx[k];
                    if(ny < 0 || ny >= n || nx < 0 || nx >= m || v[ny][nx] == '.') continue;
                    ms.merge(i * m + j, ny * m + nx);
                }
            }
        }
        for(int i = 0; i < n; i++){
            vector<int> mark(m + 1);
            for(int j = 0; j < m; j++){
                if(v[i][j] == '.') continue;
                for(int k = m - 1; k >= j; k--){
                    if(ms.find(i * m + j) == ms.find(i * m + k)){
                        mark[j]++;
                        mark[k + 1]--;
                    }
                }
            }
            for(int j = 1; j <= m; j++){
                mark[j] += mark[j - 1];
            }
            for(int j = 0; j < m; j++){
                if(mark[j] && v[i][j] == '.'){
                    done = false;
                    v[i][j] = '#';
                }
            }
        }
        for(int j = 0; j < m; j++){
            vector<int> mark(n + 1);
            for(int i = 0; i < n; i++){
                if(v[i][j] == '.') continue;
                for(int k = n - 1; k >= i; k--){
                    if(ms.find(i * m + j) == ms.find(k * m + j)){
                        mark[i]++;
                        mark[k + 1]--;
                    }
                }
            }
            for(int i = 1; i <= n; i++){
                mark[i] += mark[i - 1];
            }
            for(int i = 0; i < n; i++){
                if(mark[i] && v[i][j] == '.'){
                    done = false;
                    v[i][j] = '#';
                }
            }
        }
        if(done) break;
    }
    for(int i = 0; i < n; i++){
        cout << v[i] << '\n';
    }
}
