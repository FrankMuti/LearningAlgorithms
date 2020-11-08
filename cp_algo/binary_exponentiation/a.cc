/**
 *    author:     stein
 *    created:    2020.11.05 19:57:28
**/
#include <bits/stdc++.h>

using namespace std;

long long binpow(long long a, long long b) {
  long long res = 1;
  while (b > 0) {
    if (b & 1) res *= a;
    a *= a;
    b >>= 1;
  }
  return res;
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n = 13;
  cout << binpow(3, n) << endl;
  return 0;
}

