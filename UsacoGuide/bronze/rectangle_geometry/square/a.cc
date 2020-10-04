/**
 *    author:     stein
 *    created:    2020.10.02 14:12:12
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("square.in", "r", stdin);
  freopen("square.out", "w", stdout);
  struct Rect{
    int x1, y1, x2, y2;
  };
  Rect a, b;
  cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
  cin >> b.x1 >> b.y1 >> b.x2 >> b.y2;
  int mx_x = max({0, a.x2, b.x2}), mn_x = min({10, a.x1, b.x1});
  int mx_y = max({0, a.y2, b.y2}), mn_y = min({10, a.y1, b.y1});
  int m_d = max(mx_x - mn_x, mx_y - mn_y);
  cout << m_d*m_d << endl;
  return 0;
}

