/**
 *   author:  stein
 *   created: 2020.09.21 13:00:08
**/
#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  function<int(int s, int e)> getMid = [&] (int s, int e) { return s + (e-s) / 2; };
  function<int(int*, int, int, int, int, int)> getXorUtil = [&] (int *st, int ss, int se, int qs, int qe, int si)  {
    if (qs <= ss && qe >= se) return st[si];
    if (se < qs || ss > qe) return 0;
    int mid = getMid(ss, se);
    return getXorUtil(st, ss, mid, qs, qe, 2*si+1) & getXorUtil(st, mid+1, se, qs, qe, 2*si+2);
  };
  function<void(int*, int, int, int, int, int)> updateValueUtil = [&](int *st, int ss, int se, int i, int diff, int si) {
    if (i < ss || i > se) return;
    st[si] = st[si] + diff;
    if (se != ss) {
      int mid = getMid(ss, se);
      updateValueUtil(st, ss, mid, i, diff, 2*si + 1);
      updateValueUtil(st, mid+1, se, i, diff, 2*si + 2);
    }
  };
  function<void(int[], int*, int, int, int)> updateValue = [&] (int arr[], int *st, int n, int i, int new_val) {
    if (i < 0 || i > n - 1) return;
    int diff = new_val - arr[i];
    arr[i] = new_val;
    updateValueUtil(st, 0, n-1, i, diff, 0);
  };
  function<int(int*, int, int, int)> getXor = [&] (int *st, int n, int qs, int qe) {
    if (qs < 0 || qe > n - 1 || qs > qe) return -1;
    return getXorUtil(st, 0, n-1, qs, qe, 0);
  };
  function<int(int[], int, int, int*, int)> constructSTUtil = [&] (int arr[], int ss, int se, int *st, int si) {
    if (ss == se) {
      st[si] = arr[ss];
      return arr[ss];
    }
    int mid = getMid(ss, se);
    st[si] = constructSTUtil(arr, ss, mid, st, si*2+1) & constructSTUtil(arr, mid+1, se, st, si*2+2);
    return st[si];
  };
  function<int*(int[], int)> constuctST = [&] (int arr[], int n) {
    int x = (int) ceil(log2(n));
    int max_size = 2 * (int) pow(2, x) - 1;
    int *st = (int *) malloc(sizeof(int) * max_size);
    constructSTUtil(arr, 0, n-1, st, 0);
    return st;
  };
  int n;
  cin >> n;
  int arr[n];
  for (int i = 0; i < n; i++) cin >> arr[i];
  //int n = sizeof(arr) / sizeof(arr[0]);
  int *st = constuctST(arr, n);
  int sz = 2 * (int) pow(2, (int) ceil(log2(n))) - 1;
  int q, a, b;
  cin >> q;
  while (cin >> a >> b) {
    a--, b--;
    cout << getXor(st, n, a, b) << endl;
  }
}
