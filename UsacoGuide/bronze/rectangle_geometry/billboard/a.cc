/**
 *    author:     stein
 *    created:    2020.10.02 13:43:42
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("billboard.in", "r", stdin);
  freopen("billboard.out", "w", stdout);
  struct Rect {
    int x1, y1, x2, y2;
    int area() {
      return (y2-y1) * (x2-x1);
    }
  };
  function<int(Rect, Rect)> inter = [&] (Rect p, Rect q) {
    int xOver = max(0, min(p.x2, q.x2) - max(p.x1, q.x1));
    int yOver = max(0, min(p.y2, q.y2) - max(p.y1, q.y1));
    return xOver * yOver;
  };
  Rect a, b, t;
  cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
  cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
  cin >> t.x1 >> t.y1 >> t.x2 >> t.y2;
  cout << a.area() + b.area() - inter(a, t) - inter(b, t) << endl;
  return 0;
}

