/**
 *   author:  stein
 *   created: 2020.09.11 23:01:50
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<pair<int, int>> f (n);
  for (auto& it : f) cin >> it.first >> it.second;
  double area = 0;
  for (int i = 0; i < n - 1; i++) {
    area += (f[i].first * f[i+1].second) - (f[i+1].first * f[i].second);
  }
  cout << area / 2 << endl;
  return 0;
}
