/**
 *   author:  stein
 *   created: 2020.09.10 18:06:35
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, mul = 1;
  cin >> n;
  vector<int> f (n), g (n);
  for (int i = 0; i < n; i++) {
    cin >> f[i] >> g[i];
    mul *= g[i];
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    cout << f[i] << " " << mul / g[i] << " " << (mul / g[i]) % g[i] << endl;
    sum += f[i] * (mul / g[i]) * ((mul / g[i]) % g[i]);
  }
  cout << sum << endl;
  return 0;
}
