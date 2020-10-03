/** 
 *    author:     stein
 *    created:    2020.09.28 02:39:35

      LineContainer
      Container where you can add lines of the form kx+m and
      query maximum values at points x. Useful for dp("convex hull trick").
    
**/
#include <bits/stdc++.h>
using namespace std;

struct Line {
  mutable long long k, m, p;
  bool operator< (const Line& o) const { return k < o.k; }
  bool operator< (long long x) const { return p < x; } 
};

struct LineContainer : multiset<Line, Less<>> {
  // (for doubles, use inf = 1/.0, div(a, b) = a/)
  const long long inf = LLONG_MAX;
  long long div(long long a, long long b) {
    // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false;}
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(long long k, long long m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  long long query(long long x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  
  return 0;
}

