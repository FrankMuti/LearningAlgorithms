/**
 *   author:  stein
 *   created: 2020.09.21 17:39:24
**/
#include <bits/stdc++.h>
using namespace std;

/**
 * Alice and Bob, alice (0, 0),Bob (R, S)
 * Alice + (M, N)
 * Bob  - (P, Q)
 * 
 * When will they meet? t or -1
 * 
 * # Inputs
 * R S
 * M N P Q
**/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int a ,b, r, s;
  cin >> r >> s;
  int m, n, p, q, t = 0;
  cin >> m >> n >> p >> q;  
  while (a < r && b < s) {
    a += m, b += n;
    r -= p, s -= q;
    t++;
  }
  cout << (a == r && b == s ? t : -1)  << endl; 
  return 0;
}
