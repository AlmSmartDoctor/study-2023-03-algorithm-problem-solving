#include "bits/stdc++.h"
using namespace std;

const string s = "NESW";
const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<string> v(n);
  for(int i = 0; i < n; i++){
    cin >> v[i];
  }
  vector<vector<bool> > mark(n, vector<bool>(m));
  function<void(int, int)> solve = [&](int y, int x){
    int d = s.find(v[y][x]);
    int ty = y, tx = x;
    while(1){
      ty += dy[d];
      tx += dx[d];
      if(ty < 0 || ty >= n || tx < 0 || tx >= m || (mark[ty][tx] && v[y][x] == v[ty][tx])){
        mark[y][x] = 1;
        cout << '(' << y << ',' << x << ')' << '\n';
        return;
      }
      if(v[ty][tx] != '.' && !mark[ty][tx]){
        solve(ty, tx);
        if(v[y][x] == v[ty][tx]){
          mark[y][x] = 1;
          cout << '(' << y << ',' << x << ')' << '\n';
          return;
        }
      }
    }
  };
  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      if(v[i][j] != '.' && !mark[i][j]){
        solve(i, j);
      }
    }
  }
}
