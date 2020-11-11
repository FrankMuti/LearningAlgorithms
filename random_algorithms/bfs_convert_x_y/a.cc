/**
 *    author:     stein
 *    created:    2020.11.08 22:51:31
**/
#include <bits/stdc++.h>

using namespace std;

chrono::steady_clock::time_point begin_ = chrono::steady_clock::now();

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
#define int long long
  struct Node {
    int val, level;
  };
  int y, x = 0;
  cin >> y;  
  set<int> visit;
  queue<Node> q;
  Node n = {x, 0};
  q.push(n);
  while (!q.empty()) {
    Node t = q.front();
    q.pop();
    if (t.val == y) {
      cout << t.level << endl;
      break;
    }
    visit.insert(t.val);
    if (t.val*2 == y || t.val+1 == y) {
      cout << t.level+ (t.val+1 == y) << endl;
      break;
    }
    if (visit.find(t.val*2) == visit.end()) {
      n.val = t.val*2;
      n.level = t.level;
      q.push(n);
    }
    if (visit.find(t.val+1) == visit.end()) {
      n.val = t.val+1;
      n.level = t.level+1;
      q.push(n);
    }
  }
  chrono::steady_clock::time_point end_ = chrono::steady_clock::now();
  cout << chrono::duration_cast<chrono::microseconds>(end_ - begin_).count() << endl;
  return 0;
}

