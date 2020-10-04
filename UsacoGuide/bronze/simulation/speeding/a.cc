/**
 *    author:     stein
 *    created:    2020.10.01 20:29:58
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  //freopen("speeding.in", "r", stdin);
  //freopen("speeding.out", "w", stdout);
  int n, m;
  cin >> n >> m;
  vector<int> r (101), b (101);
  for (int i = 0, j = 0; i < n; i++) {
    int r_l, r_s;
    cin >> r_l >> r_s;
    while (r_l--) r[++j] = r_s;
  }
  for (int i = 0, j = 0; i < m; i++) {
    int b_l, b_s;
    cin >> b_l >> b_s;
    while (b_l--) b[++j] = b_s; 
  }
  int res = 0;
  for (int i = 1; i <= 100; i++) {
    if (b[i] > r[i]) res = max(res, b[i] - r[i]); 
  }
  cout << res << endl;
  return 0;
}

