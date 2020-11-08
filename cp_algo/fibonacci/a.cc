/**
 *    author:     stein
 *    created:    2020.11.06 01:00:53
**/
#include <bits/stdc++.h>

using namespace std;

// Fast Doubling Method
class FastDoublingMethod {
  public:
    pair<int, int> fib(int n) {
      if (n == 0)
        return {0, 1};
      pair<int, int> p = fib(n >> 1);
      int c = p.first * (2 * p.second - p.first);
      int d = p.first * p.first + p.second * p.second;
      if (n & 1) return {d, c + d};
      else return {c, d};
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  FastDoublingMethod f;
  for (int i = 0; i < 10; i++) {
    cout << f.fib(i).first << ' ';
  }
  return 0;
}

