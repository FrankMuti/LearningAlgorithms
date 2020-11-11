/**
 *    author:     stein
 *    created:    2020.11.11 15:36:08
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n = 7;
  vector<int> f (n+1);
  f[0] = 0;
  f[1] = 1;
  for (int i = 2; i <= n; i++) {
    f[i] += f[i];
  }
  return 0;
}

