/**
 *    author:     stein
 *    created:    2020.10.02 13:20:41
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //freopen("shuffle.in", "r", stdin);
  //freopen("shuffle.out", "w", stdout);
  int n;
  cin >> n;
  vector<int> a (n), f (n);
  for (auto& it : a) cin >> it;
  for (auto& it : f) cin >> it;
  for (int i = 0; i < 3; i++) {
    vector<int> tmp = (f);
    for (int j = 0; j < n; j++) {
      f[j] = tmp[a[j]-1]; 
    }
  }
  for (auto it : f) cout << it << endl;
  return 0;
}

