/**
 *   author:  stein
 *   created: 
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;  
  vector<int> f (n);
  for (auto& it : f) cin >> it;
  int sum = 0;
  for (auto& it : f) sum += (it % 2 ? 0 : it), cout << it << " ";
  cout << "\n" << sum << endl;
  return 0; 
}
