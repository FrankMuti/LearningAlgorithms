/**
 *   author:  stein
 *   created: 2020.09.21 18:23:59
 * 
 *   source: http://www.usaco.org/index.php?page=viewproblem2&cpid=891
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("shell.in", "r", stdin);
  freopen("shell.out", "w", stdout);
  int n;
  cin >> n;
  vector<int> a (n), b (n), c (n);
  for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
  function<int(int)> corr = [&] (int start) {
    int current = start, correct = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == current) current = b[i];
      else if (b[i] == current) current= a[i];
      correct += (current == c[i]);
    }
    return correct;
  };
  cout << max({corr(1), corr(2), corr(3)}) << endl;
  return 0;
}
