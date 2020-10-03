/**
 *   author:  stein
 *   created: 2020.09.11 22:37:47
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // Direction after cross multiplication: left if > 0, right if < 0, none if 0 
  complex<long double> a {4, 2}, b {1, 2};
  long double p = (conj(a)*b).imag();
  cout << p << endl;
  // point location
  
  return 0;
}
