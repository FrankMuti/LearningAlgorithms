/** 
 *    author:     stein
 *    created:    2020.09.28 03:31:39
      
      RMQ
      Range Minimum Queries on an array. 
      Returns min(V[a], V[a+1], ..., V[b-1]) in constant time.

      Usage:
      RMQ rmq(values);
      rmq.query(inclusive, exclusive);
      Time: O(|V|log|V| + Q)
**/
#include <bits/stdc++.h>
using namespace std;

template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= V.size(); pw *= 2, ++k) {
      jmp.emplace_back(V.size() - pw * 2 + 1);
      for (int j = 0; j < jmp[k].size(); j++) {
        jmp[k][j] = min(jmp[k-1][j], jmp[k-1][j+pw]);
      }
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b-a);
    return min(jmp[dep][a], jmp[dep][b-(1 << dep)]);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int n;
  cin >> n;
  vector<int> f (n);
  for (auto& it : f) cin >> it;
  RMQ rmq(f);  
  for (int i = 0; i < n - 3; i++) {
    for (int j = i; j < i + 3; j++) cout << f[j] << " ";
    cout << " : " << rmq.query(i, i+3) << endl;
  }
  return 0;
}

