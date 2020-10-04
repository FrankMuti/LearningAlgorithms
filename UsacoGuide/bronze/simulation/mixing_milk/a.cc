/** 
 *    author:     stein
 *    created:    2020.10.01 12:59:41
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen("mixmilk.in", "r", stdin);
  freopen("mixmilk.out", "w", stdout);
  vector<int> m (3), c (3);
  for (int i = 0; i < 3; i++) {
    cin >> c[i] >> m[i];
  }
  auto pour = [] (int& m1, int& m2, int& c2) {
    int amt = min(m1, c2 - m2);
    m1 -= amt;  
    m2 += amt;
  };
  for (int i = 0; i < 3; i++) {
    pour(m[0], m[1], c[1]);
    pour(m[1], m[2], c[2]);
    pour(m[2], m[0], c[0]);
  }
  pour(m[0], m[1], c[1]); 
  for (auto it : m) cout << it << endl;
  return 0;
}

