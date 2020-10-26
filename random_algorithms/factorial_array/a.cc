/**
 *    author:     stein
 *    created:    2020.10.26 14:41:31
**/
#include <bits/stdc++.h>

using namespace std;

const int M = 1000000007;
const int N = 200000;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<long long> fact(N+1, 0);
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = (fact[i-1] * i) % M;
  }
  vector<int> f {3, 10, 200, 20, 12};
  for (auto it : f) cout << fact[it] << '\n';
  return 0;
}

