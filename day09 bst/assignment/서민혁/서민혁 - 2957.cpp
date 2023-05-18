#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    map<int, int> tree;
    tree[0] = 0;
    tree[300001] = 0;

    ll c = 0;
    int N, x;
    cin >> N >> x;
    tree[x] = 0;

    cout << c << "\n";
    
    map<int, int>::iterator left_iter = --tree.find(x);
    map<int, int>::iterator right_iter = ++tree.find(x);
    for (int i = 1; i < N; i++)
    {    
        cin >> x;
        tree[x] = 0;
        int closest_left = (--tree.find(x)) -> second + 1;
        int closest_right = (++tree.find(x)) -> second + 1;
        tree[x] = max(closest_left, closest_right);
        c += tree[x];
        cout << c << "\n";
    }
}



// bst에서 가장 가까운 값의 자식 노드로 들어간다
// x 값과 가장 가까운 값을 갖는 노드 y 가 있다, 노드 z 에서 x 는 무조건 y쪽으로 내려간다 if not, x < z < y or x > z > y => 모순

// bst에서 가장 가까운 값이 둘이면 더 깊은곳으로 들어간다
// x 값에, 가장 가까운 값을 갖는 두 노드 x + y, x - y가 있다.
// 이러면 x - y + 1 ~ x + y - 1 사이에 값을 갖는 노드는 없다
// 즉 어떤 노드에 대해서 x - y, x + y 는 항상 같은 방향에 있다
// 그리고 x + y 는 x - y 의 자손이거나 x - y 는 x + y 의 자손이다
// 그래서 더 깊은곳으로 들어간다
