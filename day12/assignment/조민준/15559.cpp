#include <iostream>
#include <vector>

using namespace std;

int N, M;
int gift;

vector<vector<char>> map(1000, vector<char>(1000));
vector<vector<int>> visited(1000, vector<int>(1000));

// North West East South
int dr[4] = {-1, 0, 0, 1};
int dc[4] = {0, -1, 1, 0};

int getDir(char c) {
    if (c == 'N') { return 0; }
    else if (c == 'W') { return 1; }
    else if ( c == 'E') { return 2; }
    else { return 3; } // c == 'S'
}

void move(int r, int c, int pathId) {
    // dfs
    visited[r][c] = pathId;

    int dir = getDir(map[r][c]);
    int nr = r + dr[dir];
    int nc = c + dc[dir];

    if (visited[nr][nc] == 0) {
        // 아직 방문하지 않은 칸일 경우
        move(nr, nc, pathId);
    }
    else if (visited[nr][nc] == pathId) {
        // 이번에 탐색한 이동 경로에서 이미 방문한 칸일 경우 (사이클 형성)
        gift++;
    }
}

void solve() {      
    int pathId = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            if (visited[i][j] == 0) {
                pathId++;
                move(i, j, pathId);
            }
        }
    }
}

int main() {
    cin >> N >> M;
    char buffer[1001];

    for (int i=0; i<N; i++) {
        cin >> buffer;
        for (int j=0; j<M; j++) {
            map[i][j] = buffer[j];
        }
    }

    solve();

    cout << gift << endl;

    return 0;
}