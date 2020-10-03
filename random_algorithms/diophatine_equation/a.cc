/**
 *   author:  stein
 *   created: 2020.09.10 17:45:49
 * 
 *   incomplete
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int a, b, c;
  cin >> a >> b >> c;
  vector<vector<int>> f (0,vector<int> (3, 0));
  int g = a % b;
  f.push_back(vector<int> {a, b*(a/b), g});
  while (g > 0) {
    a = b; b = g;
    if (a % b == 0) break; 
    g = a % b;
    f.push_back(vector<int> {a, b * (a/b), g});
  }
  auto it = f.back();
  int fa = it[0], fb = it[1], fc = it[2], n = f.size();
  for (int i = n - 2; i >= 0; i--) {

  }

  cout << fa << " " << fb << " " << fc << endl;
  for (auto it : f) {
    cout << it[0] << " " << it[1] << " " << it[2] << endl;
  }
  return 0;
}
