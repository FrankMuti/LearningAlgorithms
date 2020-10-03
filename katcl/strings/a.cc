/** 
 *    author:     stein
 *    created:    2020.09.30 19:41:24
**/
#include <bits/stdc++.h>
using namespace std;

// KMP
// pi[x] computes the length of the longest prefix of s that ends at x,
// other thank s[0...x] itself (abacaba - 0010123)/
// Can be used to find all occurrences of a string.
//
// Time: O(n)
vector<int> pi(const string& s) {
  vector<int> p (s.size());
  for (int i = 1; i < (int) s.size(); i++) {
    int g = p[i-1];
    while (g && s[i] != s[g]) g = p[g-1];
    p[i] = g + (s[i] == s[g]); 
  }
  return p;
}
vector<int> match(const string& s, const string& pat) {
  vector<int> p = pi(pat + '\0' + s), res;
  for (int i = (int) p.size() - (int) s.size(); i < (int) p.size(); i++) {
    if (p[i] == pat.size()) res.push_back(i-2*pat.size());
  } 
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s = "abacaba", pat = "aca";
  auto res = match(s, pat);
  for (auto it : res) cout << it << " "; 
  return 0;
}

