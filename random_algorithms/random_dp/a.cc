/**
 *    author:     stein
 *    created:    2020.10.21 17:01:54
**/
#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;
const int mod = 1e9+7;

vector<bool> ready;
vector<int> value;

// recursive solution
int recursive_solve(int x, vector<int> coins) {
  if (x < 0) return inf;
  if (x == 0) return 0;
  int best = inf;
  for (auto& c : coins) {
    best = min(best, recursive_solve(x-c, coins)+1);
  }
  return best;
}

// using memoization
int memo_solve(int x, vector<int> coins) {
  if (x < 0) return inf;
  if (x == 0) return 0;
  if (ready[x]) return value[x];
  int best = inf;
  for (auto c : coins) {
    best = min(best, memo_solve(x-c, coins)+1);
  }
  value[x] = best;
  ready[x] = true;
  return best;
}

int iter_solve(int n, vector<int> coins) {
  for (int x = 1; x <= n; x++) {
    value[x] = inf;
    for (auto c : coins) {
      if (x-c >= 0) {
        value[x] = min(value[x], value[x-c]+1);
      }
    }
  }
  return value[n];
}

// Constructin a soln
vector<int> first;
int iter_c_solve(int n, vector<int> coins) {
  for (int x = 1; x <= n; x++) {
    value[x] = inf;
    for (auto c : coins) {
      if (x-c >= 0 && value[x-c]+1 < value[x]) {
        value[x] = value[x-c]+1;
        first[x] = c;
      }
    }
  }
  while (n > 0) {
    cout << first[n]  << " ";
    n -= first[n];
  }
  cout << "\n";
  return first.back();
}

// Counting the number of solutions
vector<int> count_;
int cnt_solve(int n, vector<int> coins) {
  count_[0] = 1;
  for (int x = 1; x <= n; x++) {
    for (auto c : coins) {
      if (x-c >= 0) {
        count_[x] += count_[x-c] % mod;
      }
    }
  }
  for (auto it : count_) cout << it << " ";
  return count_[n];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<int> f {1, 3, 4};
  int x = 10;
  ready.resize(x+1, false);
  value.resize(x+1, 0);
  first.resize(x+1, 0);
  count_.resize(x+1, 0);
  int res = cnt_solve(x, f);
  cout << res << endl;
  return 0;
}

