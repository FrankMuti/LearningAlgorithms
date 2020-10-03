/**
 *   author:  stein
 *   created: 2020.09.24 19:20:10
**/
#include <bits/stdc++.h>
using namespace std;

struct Tree {
  typedef int T;
  static constexpr T unit = INT_MIN;
  T f (T a, T b) { return max(a, b); }
  vector<T> s; 
  int n;
  Tree (int n = 0, T def = unit) : s (2*n, def) , n (n) {}
  void update(int pos, T val) {
    for (s[pos += n] = val; pos /= 2; ) {
      s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
  }
  T query(int b, int e) {
    T ra = unit, rb = unit;
    for (b += n, e += n; b < e; b /= 2, e /= 2) {
      if (b % 2) ra = f (ra, s[b++]);
      if (e % 2) rb = f (s[--e], rb);
    }
    return f (ra,rb);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Tree tree;
  tree.s = {0,39, 22, 17, 13, 9, 9, 8, 5, 8, 6, 3, 2, 7, 2, 6};
  tree.n = tree.s.size();
  vector<int> arr {tree.s};
  int sum = 0;
  for (int i = 0; i < tree.n; i++) {
    sum += arr[i];
    cout << tree.query(0, i) << " " << sum << endl;
  }
  return 0;
}
