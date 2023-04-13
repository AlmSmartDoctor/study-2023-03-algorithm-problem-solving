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

int position = 60;
vector<vector<int>> original(36, vector<int>(position, 0));
vector<vector<int>> difference(36, vector<int>(position, 0));

vector<int> flatten(vector<int> target)
{
    for (int i = position - 1; i >= 0; i--)
    {
        if (target[i] > 35)
        {
            target[i - 1] += target[i] / 36;
            target[i] = target[i] % 36;
        }
    }
    return target;
}
bool compare(vector<int> a, vector<int> b)
{
    for (int i = 0; i < position; i++)
    {
        if (a[i] > b[i]) return true;
        else if (a[i] < b[i]) return false;
    }
    return true;
}
vector<int> get_maximum(vector<vector<int>> target, int k)
{
    vector<int> list{};
    for (int i = 0; i < k; i++)
    {
        int biggest = 35;
        for (int j = 0; j < 35; j++)
        {
            if (!compare(target[biggest], target[j]))
            {
                biggest = j;
            }
        }
        list.push_back(biggest);
        target[biggest] = vector<int> (position, 0);
    }
    return list;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string number;
        cin >> number;
        for (int j = 0; j < number.size(); j++)
        {
            char c = number[number.size() - 1 - j];
            if (c < 58) // c is digit
            {
                original[c - 48][position - 1 - j] += 1;
            }
            else // c is alphabet
            {
                original[c - 55][position - 1 - j] += 1;
            }
        }
    }

    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < position; j++)
        {
            difference[i][j] = original[i][j] * (35 - i);
        }
        difference[i] = flatten(difference[i]);
        original[i] = flatten(original[i]);
    }
    
    int k;
    cin >> k;
    vector<int> list = get_maximum(difference, k);
    vector<int> sum = vector<int>(position, 0);

    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < position; j++)
        {
            sum[j] += original[i][j] * i;
        }
    }

    for (int i = 0; i < list.size(); i++)
    {
        for (int j = 0; j < position; j++)
        {
            sum[j] += difference[list[i]][j];
        }
    }
    
    sum = flatten(sum);

    bool print = false;
    for (int i = 0; i < position; i++)
    {
        if (sum[i] != 0)
            print = true;
        if (print)
        {
            if (sum[i] > 9)
            {
                char a = sum[i] + 55;
                cout << a;
            }
            else
            {
                cout << sum[i];
            }
        }
    }
    if (!print) cout << 0;
}
