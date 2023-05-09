#include<bits/stdc++.h>


using namespace std;
#define endl '\n'
#define fast_io ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define rep(i, j) for(ll i=0;i<j;i++)
#define mrep(i, j, k) for(ll i = j; i<=k;i++)
#define drep(i, j, k) for(ll i = j; i>=k; i--)
#define pb push_back
#define pf push_front
#define pll pair<long long, long long>
#define pii pair<int,int>
#define vpll vector<pair<long long,long long>>
#define vll vector<long long>
#define ff first
#define ss second
#define YES "YES"
#define NO "NO"
#define yes "YES"
#define no "NO"
typedef long long ll;

const int MAXN = 510;
const int MAXINT = 2147483098;
const int inf = 1e9 + 7;
const int MOD = 1e9;
//const ll MAXLL = 9223372036854775258LL;
//bool comp(pair<int,pii>& a, pair<int,pii> & b) {
//	if (a.ff == b.ff) {
//		return a.ss < b.ss;
//	}
//	return a.ff > b.ff;
//}
//struct comp{
//    bool operator()(pair<int,pii> a, pair<int,pii> b){
//        if(a.ff == b.ff){
//            return a.ss > b.ss;
//        }
//        return a.ff > b.ff;
//    }
//};

////sort compare > == decending < == incresing

int n, k;
vector<int> tree[50], childNum, arr;

int dfs(int node) {

    if (childNum[node] == 0)return 1;
    int deletedLeafNodeNum = 0;

    for (int i = 0; i < tree[node].size(); i++) {
        deletedLeafNodeNum += dfs(tree[node][i]);
    }

    return deletedLeafNodeNum;
}

void solve(int testcase) {
    // indegree가 0이면 leaf node임
    cin >> n;

    childNum.resize(n, 0);
    arr.resize(n, 0);

    int leafNodeNum = 0;

    for (int i = 0; i < n; i++) {
        int parent;
        cin >> parent;
        arr[i] = parent;
        if (parent == -1)continue;
        tree[parent].push_back(i);
        childNum[parent]++;
    }
    cin >> k;
    if (arr[k] == -1) {
        cout << 0;
        return;
    }

    for (int i = 0; i < n; i++) {
        if (childNum[i] == 0)leafNodeNum++;
    }

    int deletedLeafNodeNum = dfs(k);
    if (childNum[arr[k]] == 1){
        leafNodeNum++;
    }

        cout << leafNodeNum - deletedLeafNodeNum;
}

int main() {
    //#ifndef ONLINE_JUDGE
    //    freopen("input.txt", "r", stdin);
    //#endif
    fast_io;
//    cout << fixed;
//    cout.precision(6);
//    int t;
//    cin >> t;
//    rep(i, t)solve(i);
//
    solve(1);
    //    cerr << "Time : " << (double) clock() / (double) CLOCKS_PER_SEC << "S\N";
    return 0;
}
