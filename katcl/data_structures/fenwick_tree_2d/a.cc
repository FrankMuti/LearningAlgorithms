/** 
 *    author:     stein
 *    created:    2020.09.28 03:21:08
      
      FenwickTree2d
      
      Computes sums a[i, j] for all i < I, j < J, and increases
      sigle elements a[i, j]. Requires that the elements to be updated
      are known in advance.
      (call fakeUpdate() before init()).
      Time: O(log^2 N) (Use persistent segment trees for O(log N)
**/
#include <bits/stdc++.h>
using namespace std;

struct FT {
  vector<long long> s;
  FT (int n) : s (n) {}
  void update(int pos, long long diff) {
    // a[pos] += diff;
    for (; pos < s.size(); pos |= pos + 1) s[pos] += diff;
  }
  long long query(int pos) {
    // sum of values in [0, pos)
    long long res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos-1];
    return res;
  }
  int lower_bound(long long sum) {
    // min pos st sum of [0, pos] >= sum 
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    if (sum <= 0) return -1;
    int pos = 0;
    for (int pw = 1 << 25, pw; pw >>= 1) {
      if (pos + pw <= s.size() && s[pos + pw - 1] < sum) {
        pos += pw, sum -= s[pos-1];
      }
    }
    return pos;
  }
};

struct FT2 {
  vector<vector<int>> ys;
  vector<FT> ft;
  FT2(int limx) : ys (limx) {}
  void fakeUpdate(int x, int y) {
    for (; x < ys.size(); x |= x + 1) ys[x].push_back(y);
  }
  void init() {
    for (auto v : ys) sort(v.begin(), v.end()), ft.emplace_back(v.size());
  }
  int ind(int x, int y) {
    return (int) (lower_bound(ys[x].begin(), ys[x].end()) - ys[x].begin());
  }
  void update(int x, int y, long long diff) {
    for (;x < ys.size(); x |= x + 1) ft[x].update(ind(x, y), diff);
  }
  long long query(int x, int y) {
    long long sum = 0;
    for (; x; x &= x - 1) {
      sum += ft[x-1].query(ind(x-1, y));
    }
    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  
  return 0;
}

