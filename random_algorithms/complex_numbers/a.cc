/**
 *   author:  stein
 *   created: 2020.09.11 22:18:06
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(20);
  int n = 2;
  vector<long double> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  complex<long double> u, v, s;
  u = {x[0], y[0]};
  v = {x[1], y[1]};
  s = u + v;
  cout << s.real() << " " << s.imag() << endl;
  cout << abs(u-v) << endl;
  cout << arg(u) << endl;
  complex<long double> p = polar(abs(u), arg(u)) *= polar(1.0, 0.5);
  cout << p.real() << " " << p.imag() << endl;
  return 0;
}
