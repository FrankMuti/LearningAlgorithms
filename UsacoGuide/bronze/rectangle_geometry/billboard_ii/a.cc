/**
 *    author:     stein
 *    created:    2020.10.05 22:43:01
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  struct Rect {
    int x1, y1, x2, y2;
    int area() {
      return (y2-y1) * (x2-x1);
    }
  };
  function<int(Rect, Rect)> inter = [&] (Rect p, Rect q) {
    int xo = max(0, min(p.x2, q.x2) - max(p.x1, q.x1));
    int yo = max(0, min(p.y2, q.y2) - max(p.y1, q.y1));
    return xo * yo;
  };
  Rect a, b;
  cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
  cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
  int area = a.area() - inter(a, b);
  cout << area << endl;
  return 0;
}

