/**
 *   author:  stein
 *   created: 2020.09.21 18:06:25
**/
#include <bits/stdc++.h>
using namespace std;

/**
 * Alice (0, 0), Bob (R, S)
 * Every second, 
 * Alice += (M, N), Bob -= (R, S)
 * When will they meet if they meet ? t : -1
 * 
 * # Inputs
 * R S
 * M N P Q
**/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int r, s, a = 0, b = 0;
  cin >> r >> s;
  int m, n, p, q;
  cin >> m >> n >> p >> q;
  int t = 0;
  while (a < r && b < s) {
    a += m, b += n;
    r -= p, s -= q;
    t++;
  }
  cout << (a == r && b == s ? t : -1) << endl;
  return 0;
}
