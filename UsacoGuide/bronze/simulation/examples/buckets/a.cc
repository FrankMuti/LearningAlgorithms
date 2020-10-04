/**
 *   author:  stein
 *   created: 2020.09.21 18:11:09
**/
#include <bits/stdc++.h>
using namespace std;

/**
 * N Buckects, capacity C_i
 * Each bucket filled with A_i units
 * Pours Bucket 1 into 2, 2 into 3,...N-1 into N
 * When pouring B into B+1, he pours as much as
 * possible until B is empty or bucket B+1 is full
 * Find out how much water is in each bucket once Charlie is done.
 * 
 * # Input
 * N
 * C_1, C_2, ..., C_N
 * A_1, A_2, ..., A_N
 * 
 * # Output 
 * N-Lines 
 * A_1, ..., A_N
 * 
**/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  vector<int> f (n), g (n);
  for (auto& it : f) cin >> it;
  for (auto& it : g) cin >> it;
  for (int i = 1; i < n; i++) {
    int amt = min(f[i] - g[i], g[i-1]);
    g[i-1] -= amt;
    g[i] += amt;
  }
  for (auto it : g) cout << it << " ";
  cout << endl;
  return 0;
}
