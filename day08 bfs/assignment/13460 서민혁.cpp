#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N, M;
    cin >> N >> M;
    queue<vector<int>> next;
    vector<vector<char>> map(N, vector<char>(M));
    vector<int> initial_state(5); 
    // state = {red_y, red_x, blue_y, blue_x, count}

    initial_state[4] = 0;
    vector<pair<int, int>> directions {
        pair<int, int> {-1, 0},
        pair<int, int> {+1, 0},
        pair<int, int> {0, -1},
        pair<int, int> {0, +1},
    };
    for (int i = 0; i < N; i++)
    {
        string row;
        cin >> row;
        for (int j = 0; j < M; j++)
        {
            if (row[j] == 'R')
            {
                initial_state[0] = i;
                initial_state[1] = j;
                map[i][j] = '.';
            }
            else if (row[j] == 'B')
            {
                initial_state[2] = i;
                initial_state[3] = j;
                map[i][j] = '.';
            }
            else
            {
                map[i][j] = row[j];
            }
        }
    }
    next.push(initial_state);


    int minimum = 11;
    while (!next.empty())
    {
        vector<int> state = next.front();
        state[4] += 1;
        next.pop();

        for (int direction = 0; direction < 4; direction++)
        {
            vector<int> next_state = state;
            // 이미 얻은 최소 횟수보다 작으면 더 깊이 진행하지 않는다
            bool next_continue = next_state[4] < minimum;

            // 각각의 공이 떨어졌는지 여부를 확인
            bool red_ball_fell = false;
            bool blue_ball_fell = false;

            if (next_continue)
            {
                for (int i = 0; i < 20; i++)
                {
                    // 다음 칸이 벽이 아니고 다른 공이 자리 차지하고 있지 않을때 한칸 이동
                    // 파란공이 떨어진 상태면 이미 끝나버려서 파란공 떨어졌는지 여부는 체크 안해도 됨
                    if (map[next_state[2] + directions[direction].first][next_state[3] + directions[direction].second] != '#' &&
                        !(next_state[2] + directions[direction].first == next_state[0] && next_state[3] + directions[direction].second == next_state[1])
                    )
                    {
                        next_state[2] += directions[direction].first;
                        next_state[3] += directions[direction].second;
                        if (map[next_state[2]][next_state[3]] == 'O')
                        {
                            blue_ball_fell = true;
                            next_continue = false;
                            break;
                        }
                    }

                    // 다음 칸이 벽이 아니고 다른 공이 자리 차지하고 있지 않을때 한칸 이동
                    // 빨간공이 이미 떨어진 상태면 더 안봐도 됨
                    if (!red_ball_fell &&
                        map[next_state[0] + directions[direction].first][next_state[1] + directions[direction].second] != '#' &&
                        !(next_state[0] + directions[direction].first == next_state[2] && next_state[1] + directions[direction].second == next_state[3])
                    )
                    {
                        next_state[0] += directions[direction].first;
                        next_state[1] += directions[direction].second;
                        if (map[next_state[0]][next_state[1]] == 'O')
                        {
                            next_state[0] = 500;
                            next_state[1] = 500;
                            
                            red_ball_fell = true;
                            next_continue = false;
                        }
                    }
                }
            }
            if (next_continue)
            {
                next.push(next_state);
            }
            else
            {
                // 빨간공만 떨어졌을때 성공
                if (!blue_ball_fell && red_ball_fell) minimum = next_state[4];
            }
        }
    }
    cout << (minimum > 10 ? -1 : minimum);

}
