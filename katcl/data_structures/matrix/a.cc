/** 
 *    author:     stein
 *    created:    2020.09.28 02:25:08
 
      Matrix
      Basic operations on square matrices
      
      Usage:
      Matrix<int, 3> A; 
      A.d = {{{{1, 2, 3}}, {{4, 5, 6}}, {{7, 8, 9}}}}
      vector<int> vec = {1, 2, 3};
      vec = (A^N) * vec;
**/
#include <bits/stdc++.h>
using namespace std;

template<class T, int N> 
struct Matrix {
  typedef Matrix M;
  array<array<T, N>, N> d {};
  M operator* const (M& m) const {
    M a;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
          a.d[i][j] += d[i][k] * m.d[k][j];
        }
      }
    }
    return a;
  }
  vector<T> operator* (const vector<T>& vec) const {
    vector<T> ret (N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        ret[i] += d[i][j] * vec[j];
      }
    }
    return ret;
  }
  M operator^ (long long p) const {
    assert(p >= 0);
    M a, b (*this);
    for (int i = 0; i < N; i++) {
      a.d[i][i] = 1;
    }
    while (p) {
      if (p & 1) a = a*b;
      b = b*b;
      p >>= 1;
    }
    return a;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  
  return 0;
}

