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
ll start;
// 1 -> 132
// 2 -> 211
// 3 -> 232

// return number of 1, 2, 3 in a vector for 1 ~ position and the number at position
vector<ll> solve(ll position, ll depth)
{
    if (position == 0)
    {
        vector<ll> answer{
            0, 0, 0, 0
        };
        return answer;
    }
    if (depth == 0)
    {
        vector<ll> answer{
            start == 1 ? 1 : 0,
            start == 2 ? 1 : 0,
            start == 3 ? 1 : 0,
            start
        };
        return answer;
    }
    if (position % 3 == 1)
    {
        vector<ll> parent = solve((position + 2) / 3, depth - 1);
        ll s1 = 0;
        ll s2 = 0;
        ll s3 = 0;
        ll now;
        if (parent[3] == 1)
        {
            now = 1;
            s1 = 0;
            s2 = 1;
            s3 = 1;
        }
        if (parent[3] == 2)
        {
            now = 2;
            s1 = 2;
            s2 = 0;
            s3 = 0;
        }
        if (parent[3] == 3)
        {
            now = 2;
            s1 = 0;
            s2 = 1;
            s3 = 1;
        }

        vector<ll> answer {
            parent[0] * 1 + parent[1] * 2 + parent[2] * 0 - s1,
            parent[0] * 1 + parent[1] * 1 + parent[2] * 2 - s2,
            parent[0] * 1 + parent[1] * 0 + parent[2] * 1 - s3,
            now
        };
        return answer;
    }
    if (position % 3 == 2)
    {
        vector<ll> parent = solve((position + 1) / 3, depth - 1);
        ll s1 = 0;
        ll s2 = 0;
        ll s3 = 0;
        ll now;
        if (parent[3] == 1)
        {
            now = 3;
            s1 = 0;
            s2 = 1;
            s3 = 0;
        }
        if (parent[3] == 2)
        {
            now = 1;
            s1 = 1;
            s2 = 0;
            s3 = 0;
        }
        if (parent[3] == 3)
        {
            now = 3;
            s1 = 0;
            s2 = 1;
            s3 = 0;
        }

        vector<ll> answer {
            parent[0] * 1 + parent[1] * 2 + parent[2] * 0 - s1,
            parent[0] * 1 + parent[1] * 1 + parent[2] * 2 - s2,
            parent[0] * 1 + parent[1] * 0 + parent[2] * 1 - s3,
            now
        };
        return answer;
    }
    if (position % 3 == 0)
    {
        vector<ll> parent = solve((position + 0) / 3, depth - 1);
        ll s1 = 0;
        ll s2 = 0;
        ll s3 = 0;
        ll now;
        if (parent[3] == 1)
        {
            now = 2;
            s1 = 0;
            s2 = 0;
            s3 = 0;
        }
        if (parent[3] == 2)
        {
            now = 1;
            s1 = 0;
            s2 = 0;
            s3 = 0;
        }
        if (parent[3] == 3)
        {
            now = 2;
            s1 = 0;
            s2 = 0;
            s3 = 0;
        }

        vector<ll> answer {
            parent[0] * 1 + parent[1] * 2 + parent[2] * 0 - s1,
            parent[0] * 1 + parent[1] * 1 + parent[2] * 2 - s2,
            parent[0] * 1 + parent[1] * 0 + parent[2] * 1 - s3,
            now
        };
        return answer;
    }

    return vector<ll> {0, 0, 0, 1};
}
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll left, right, N;
    cin >> start >> left >> right >> N;

    vector<ll> a = solve(left, N);
    vector<ll> b = solve(right + 1, N);
    cout << b[0] - a[0] << " " << b[1] - a[1] << " " << b[2] - a[2];
}
