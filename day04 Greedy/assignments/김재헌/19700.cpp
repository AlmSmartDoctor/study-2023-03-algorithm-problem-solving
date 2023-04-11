#include "bits/stdc++.h"
using namespace std;

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n;
  cin >> n;
  vector<pair<int, int> > v(n);
  for(int i = 0; i < n; i++){
    int h, k;
    cin >> h >> k;
    v[i] = {h, k};
  }
  sort(v.begin(), v.end());
  int lo = 1, hi = n;
  while(lo < hi){
    int mid = (lo + hi) / 2;
    bool ok = true;
    vector<int> cnt(mid);
    for(int i = n - 1; i >= 0; i--){
      int pos = prev(lower_bound(cnt.begin(), cnt.end(), v[i].second)) - cnt.begin();
      if(pos < 0){
        ok = false;
        break;
      }
      cnt[pos]++;
    }
    if(ok) hi = mid;
    else lo = mid + 1;
  }
  cout << lo;
}