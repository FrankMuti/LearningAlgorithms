/**
 *    author:     stein
 *    created:    2020.10.01 22:46:40
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("lostcow.in", "r", stdin);
  freopen("lostcow.out", "w", stdout);
  int x, y;
  cin >> x >> y;
  int diff = abs(y-x);
  int res = 0, st = 1;
  for (int i = 1; ; i++) {
    res += st/2 + st;
    if ((y>x && i&1 && st >= diff) || (x>y && !(i&1) && (x-st) <= y)) {
      res -= st - diff;
      break;
    }
    st *= 2;
  }
  cout << res << endl;
  return 0;
}

