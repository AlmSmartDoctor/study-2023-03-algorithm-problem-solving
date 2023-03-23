#include "bits/stdc++.h"
using namespace std;

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    string board[5];
    for(int i = 0; i < 5; i++){
        cin >> board[i];
    }
    vector<int> block, ys, xs;
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == '.') continue;
            ys.push_back(i);
            xs.push_back(j);
            block.push_back(1 << (i * 5 + j));
        }
    }
    int n = block.size();
    auto chk = [](int msk){
        int board[5][5] = {0};
        for(int i = 0; i < 25; i++){
            if(msk & (1 << i)) board[i / 5][i % 5] = 1;
        }
        int cnt = 0;
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(!board[i][j]) continue;
                cnt++;
                queue<pair<int, int> > q;
                q.push({i, j});
                board[i][j] = 0;
                while(q.size()){
                    int y, x;
                    tie(y, x) = q.front();
                    q.pop();
                    for(int k = 0; k < 4; k++){
                        int ny = y + dy[k], nx = x + dx[k];
                        if(ny < 0 || ny >= 5 || nx < 0 || nx >= 5 || !board[ny][nx]) continue;
                        q.push({ny, nx});
                        board[ny][nx] = 0;
                    }
                }
            }
        }
        return cnt == 1;
    };
    int ans = 999;
    function<void(int, int, int)> solve = [&](int pos, int sum, int msk){
        if(ans <= sum) return;
        if(pos == n){
            if(chk(msk)) ans = min(ans, sum);
            return;
        }
        for(int dy = -ys[pos]; dy < 5 - ys[pos]; dy++){
            for(int dx = -xs[pos]; dx < 5 - xs[pos]; dx++){
                int moved = block[pos];
                if(dy < 0) moved >>= 5 * -dy;
                else moved <<= 5 * dy;
                if(dx < 0) moved >>= -dx;
                else moved <<= dx;
                if(msk & moved) continue;
                solve(pos + 1, sum + abs(dy) + abs(dx), msk | moved);
            }
        }
    };
    solve(0, 0, 0);
    cout << ans;
}
