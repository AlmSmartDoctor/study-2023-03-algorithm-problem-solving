#include <string>
#include <iomanip>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <unordered_map>
#include <numeric>
#include <algorithm>
#include <regex>
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <queue>
using namespace std;
typedef long long ll;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    int count = 0;
    cin >> N;
    
    // 스택이 비어버리는 경우 방지하기 위해서 0 하나 넣어주고 시작함
    vector<int> stack {0};

    int next_number;
    for (int i = 0; i < N; i++)
    {
        cin >> next_number;

        // 현재 스택에서 가장 큰 수가 다음 수보다 작으면 다음 수 넣어주고 카운트 + 1
        if (next_number > stack.back())
        {
            stack.push_back(next_number);
            count += 1;
        }
        else if (next_number < stack.back())
        {
            // 현재 스택에서 가장 큰 수보다 다음 수가 작으면 스택에서 가장 큰 수 쳐낸다 -> 다음 수가 더 크거나 같아질때까지 반복
            while (next_number < stack.back())
            {
                stack.pop_back();
            }

            // 다음 수가 스택에서 가장 큰 수랑 같으면 아무것도 안해준다
            // 다음 수가 스택에서 가장 큰 수보다 크면 다음 수 넣어주고 카운트 + 1
            if (next_number > stack.back())
            {
                stack.push_back(next_number);
                count += 1;
            }
        }
    }
    cout << count;
}
