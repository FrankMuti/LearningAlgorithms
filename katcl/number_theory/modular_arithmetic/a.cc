/** 
 *    author:     stein
 *    created:    2020.09.28 23:55:32
**/
#include <bits/stdc++.h>
using namespace std;

// Modular Arithmetic
const long long mod = (long long) 1e9+7; // faster if const
struct Mod {
  long long x;
  Mod(long long xx) : x (xx) {}
  Mod operator+ (Mod b) { return Mod((x + b.x) % mod); }
  Mod operator- (Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator* (Mod b) { return Mod((x * b.x) % mod); }
  Mod operator/ (Mod b) { return *this * invert(b); }
  Mod invert(Mod a) {
    long long x, y, g = 1;//euclid(a.x, mod, x, y);
    assert(g == 1);
    return Mod((x + mod) % mod);
  }
  Mod operator^ (long long e) {
    if (!e) return Mod(1);
    Mod r = *this ^ (e / 2); 
    r = r * r;
    return e&1 ? *this * r : r;
  }
};

// ModInverse
const long long LIM = 200000;
void inverse() {
  long long* inv = new long long[LIM] - 1; inv[1] = 1;
  for (int i = 2; i < LIM; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
}

// ModPow
long long modpow(long long b, long long e) {
  long long res = 1;
  for (; e; b = b * b % mod, e /= 2) {
    if (e & 1) res = res * b % mod; 
  }
  return res;
}

// ModLog
// Returns the smallest x > 0 s.t a^x = b (mod m), or -1 if no
// such x exists
long long modlog(long long a, long long b, long long m) {
  long long n = (long long) sqrt(m) + 1, e = 1, f = 1, j = 1;
  unordered_map<long long, long long> A;
  while (j <= n && (e = f = e * a % m) != b % m) {
    A[e * b % m] = j++;
  }
  if (e == b % m) return j;
  if (__gcd(m, e) == __gcd(m, b)) {
    for (int i = 2; i < n + 2; i++) {
      if (A.count(e = e * f % m)) {
        return n * i - A[e];
      }
    }
  }
  return -1;
}

// ModSum
// Sums of mod'ed arithmetic progression
// modsum(to, c, k, m) = \sum{i = 0}{to-1} (k_i + c) $ m
// divsum is similar but for floored division
long long sumsq(long long to) { return to / 2 * ((to-1) | 1); }
long long divsum(long long to, long long c, long long k, long long m) {
  long long res = k / m * sumsq(to) + c / m * to;
  k %= m; c %= m;
  if (!k) return res;
  long long to2 = (to * k + c) / m;
  return res + (to-1) * to2 - divsum(to2, m-1-c, m, k);
} 
long long modsum(long long to, long long c, long long k, long long m) {
  c = ((c % m) + m) % m;
  k = ((k % m) + m) % m;
  return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}

// ModMull
// Calculate a*b mod c (or a^b mod c) for 0 <= a, b <= c <= 7.2e18
long long modmul(long long a, long long b, long long m) {
  long long res = a * b - m * (unsigned long long) (1.L / m * a * b);
  return res + m * (res < 0) - m * (res >= (long long) m);
}
long long modpow(long long b, long long e, long long mod) {
  long long res = 1;
  for (; e; b = modmul(b, b, mod), e /= 2) {
    if (e & 1) res = modmul(res, b, mod);
  }
  return res;
}
// ModSqrt
// Tonelli-Shanks algorithm for modular square roots
// Finds x s.t x^2 = a (mod p) (-x gives other solution).
// Time: O(log^2 p) worst case, O(log p) for most
long long sqrt(long long a, long long p) {
  a %= p;
  if (a < 0) a += p;
  if (a == 0) return 0;
  assert(modpow(a, (p-1)/2, p) == 1); // else no solution
  if (p % 4 == 3) return modpow(a, (p+1)/4, p);
  // a^(n+3)/8 or 2^(n+3)/8 * 2^(n-1)/4 works if p % 8 == 5
  long long s = p - 1, n = 2;
  int r = 0, m;
  while (s % 2 == 0) ++r, s /= 2;
  while (modpow(n, (p-1) / 2, p) != p - 1) ++n; 
  long long x = modpow(a, (s + 1) / 2, p);
  long long b = modpow(a, s, p), g = modpow(n, s, p);
  for (;; r = m) {
    long long t = b;
    for (m = 0; m < r && t != 1; ++m) {
      t = t * t % p;
    }
    if (m == 0) return x;
    long long gs = modpow(g, 1LL << (r - m - 1), p);
    g = gs * gs % p;
    x = x * gs % p;
    b = b * g % p; 
  }   
  return 1;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout << sqrt(10, mod) << endl;
  return 0;
}

