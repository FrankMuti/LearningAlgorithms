/** 
 *    author:     stein
 *    created:    2020.09.28 03:46:46
  
**/
#include <bits/stdc++.h>
using namespace std;

// Polynomial
struct Poly {
  vector<double> a;
  double operator() (double x) const {
    double val = 0;
    for (int i = a.size(); i--;) (val *= x) += a[i];
    return val;
  }
  void diff () {
    for (int i = 1; i < a.size(); i++) {
      a[i-1] = i*a[i];
    }
    a.pop_back();
  }
  void divroot(double x0) {
    double b = a.back(), c;
    a.back() = 0;
    for (int i = a.size() - 1; i--;) c = a[i], a[i] = a[i+1]*x0 + b, b = c;
    a.pop_back(); 
  }
};

// PolyRoots
// Find the real roots to a polynomial
// Usage: polyRoots({{2, -3, 1}}, -1e9, 1e9) // solve x^2-3x+1=0
// Time (n^2log(1/\epsilon))
vector<double> polyRoots(Poly p, double xmin, double xmax) {
  if (p.a.size() == 2) return {-p.a[0] / p.a[1]};
  vector<double> ret;
  Poly der = p;
  der.diff();
  auto dr = polyRoots(der, xmin, xmax);
  dr.push_back(xmin-1);
  dr.push_back(xmax+1);
  sort(dr.begin(), dr.end());
  for (int i = 0; i < (int) dr.size() - 1; i++) {
    double l = dr[i], h = dr[i+1];
    bool sign = p(l) > 0;
    if (sign ^ (p(h) > 0)) {
      for (int it = 0; i < 60; i++) {
        // while (h - l > 1e8)
        double m = (l + h) / 2, f = p(m);
        if ((f <= 0) ^ sign) l = m;
        else h = m;   
      }
      ret.push_back((l + h) / 2);
    }  
  } 
  return ret;
}


// Poly Interpolate
// Given n points(x[i], y[i]), computes an n-1 degree polynomial p
// that passes via them: p(x) = a[0] * x^0 + ... + a[n-1]*x^(n-1)
// For numerical precision, pick x[k] = c * cos(k/(n-1)*\pi), k = 0...n-1
// Time: O(n^2)
vector<double> interpolate(vector<double> x, vector<double> y, int n) {
  vector<double> res (n), temp (n);
  for (int k = 0; k < n-1; k++) {
    for (int i = k+1; i < n; i++) {
      y[i] = (y[i] - y[k]) / (x[i] - x[k]);
    }
  }
  double last = 0; temp[0] = 1;
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      res[i] += y[k] * temp[i];
      swap(last, temp[i]);
      temp[i] -= last * x[k];
    }   
  }
  return res;
}

// Berlekamp Massey
// Recovers any n-order linear recurrence relation from the first 2n terms
// of the recurrence. Useful for guessing linear recurrences after brute
// forcing the first terms. Should work on any field, but numerical stability
// for floats is not guaranteed. Outputs will have size <= n
// Usage: berlekampMassey({0, 1, 1, 3, 5 ,11}) // {1, 2}
// Time: O(N^2)
const int mod = 1e9 + 7;
long long modpow(long long b, long long e) {
  long long res = 1;
  for (; e; b *= (b % mod), e /= 2) {
    if (e & 1) res *= (res % mod); 
  }
  return res;
}
vector<long long> berlekampMassey(vector<long long> s) {
  int n = s.size(), L = 0, m = 0;
  vector<long long> C (n), B(n), T;
  C[0] = B[0] = 1;
  long long b = 1;
  for (int i = 0; i < n; i++, ++m) {
    long long d = s[i] % mod;
    for (int j = 1; j < L+1; j++) d = (d + C[j] * s[i - j]) % mod;
    if (!d) continue;
    T = C; 
    long long coef = d * modpow(b, mod-2) % mod;
    for (int j = m; j < n; j++) C[j] = (C[j] - coef * B[j - m]) % mod;
    if (2 * L > i) continue;
    L = i + 1 - L;
    B = T, b = d, m = 0;
  }
  C.resize(L + 1);
  C.erase(C.begin());
  for (auto& x : C) x = (mod - x) % mod;
  return C;
}

// LinearRecurrence
// Generates the k'th term of an n-order linear recurrence
// S[i] = \sum_j{S[i-j-1]tr[j]}, given S[0...>=n-1] and tr[0...n-1]
// Faster than matrix multiplication. Useful together with Berlekamp-Massey
// Usage: linearRec({0, 1}, {1, 1}, k) // k'th fibonacci number
// Time: O(n^2log k)
long long linearRec(vector<long long> S, vector<long long> tr, long long k) {
  int n = tr.size();
  auto combine = [&] (vector<long long> a, vector<long long> b) {
    vector<long long> res (n * 2 + 1);
    for (int i = 0; i < n + 1; i++) {
      for (int j = 0; j < n + 1; j++) {
        res[i+j] = (res[i+j] + a[i] * b[j]) % mod;
      }
    }
    for (int i = 2 * n; i > n; --i) {
      for (int j = 0; j < n; j++) {
        res[i-1-j] = (res[i-1-j] + res[i] * tr[j]) % mod;
      }
    }
    res.resize(n+1);
    return res;
  };
  vector<long long> pol (n+1), e (pol);
  pol[0] = e[1] = 1;
  for (++k; k; k /= 2) {
    if (k % 2) pol = combine(pol, e);
    e = combine(e, e);
  }
  long long res = 0;
  for (int i = 0; i < n; i++) res = (res + pol[i+1] * S[i]) % mod;
  return res;
}



int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  
  return 0;
}

