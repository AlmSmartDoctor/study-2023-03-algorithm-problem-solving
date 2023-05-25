#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class bigger
{
    public:
    bool operator() (pair<int, int> a, pair<int, int> b)
    {
        return a.second > b.second;
    }
};

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    priority_queue<pair<int, int>, vector<pair<int, int>>, bigger> pq;
    int N, L, a;
    cin >> N >> L;
    for (int i = 0; i < N; i++)
    {
        cin >> a;
        pq.push(pair<int, int> {i, a});
        while (pq.top().first < i - L + 1)
        {
            pq.pop();
        }
        cout << pq.top().second << " ";
    }
}
