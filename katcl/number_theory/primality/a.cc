/** 
 *    author:     stein
 *    created:    2020.09.29 00:42:41
**/
#include <bits/stdc++.h>
using namespace std;

#define u unsigned

// Eratosthenes
// Prime sieve for generating all primes up to a certain limit.
// isprime[i] is true iff i is a prime
// Time: lim=100,000,000 = 0.8s += (var)
// Runs 30% faster if only indices are stored
const int MAX_PR = 5000000;
bitset<MAX_PR> isprime;
vector<int> eratosthenesSieve(int lim) {
  isprime.set();
  isprime[0] = isprime[1] = 0;
  for (int i = 4; i < lim; i += 2) isprime[i] = 0;
  for (int i = 3; i*i < lim; i += 2) {
    if (isprime[i]) {
      for (int j = i*i; j < lim; j += i*2) isprime[j] = 0;
    }
  }
  vector<int> pr; 
  for (int i = 2; i < lim; i++) {
    if (isprime[i]) pr.push_back(i);
  }
  return pr;
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

// MillerRabin
// Deterministic Miller-Rabin primality test.
// Guaranteed to work for numbers up to 7e18;
// Time: 7 time complexity of a^b mod c
bool isPrime(unsigned long long n) {
  if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
  unsigned long long A[] = {
    2, 325, 9375, 28178, 450775, 9780504, 1795265022
  };
  unsigned long long s = __builtin_ctzll(n-1), d = n >> s;
  for (auto a : A) { // ^ Count trailing zeros 
    unsigned long long p = modpow(a%n, d, n), i = s;
    while (p != 1 && p != n - 1 && a % n && i--) {
      p = modmul(p, p, n);
    }
    if (p != n - 1 && i != s) return false;
  }
  return true;
}

// Factor
// Pollard-rho randomized factorization algorithm
// Returns prime factors of a number, in arbitrary order
// (e.g 2299 -> { 11, 19, 11 })
// Time: o(n^(1/4)), less for numbers with small factors
unsigned long long pollard(unsigned long long n) {
  auto f = [n](unsigned long long x) { return modmul(x, x, n) + 1; };
  unsigned long long x = 0, y = 0, t = 0, prd = 2, i = 1, q;
  while (t++ % 40 || __gcd(prd, n) == 1) {
    if (x == y) x = ++i, y = f(x);
    if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
    x = f(x), y = f(f(y));
  }
  return __gcd(prd, n);
}
vector<unsigned long long> factor(unsigned long long n) {
  if (n == 1) return {};
  if (isPrime(n)) return {1, n};
  unsigned long long x = pollard(n);
  auto l = factor(x), r = factor(n/x);
  l.insert(l.end(), r.begin(), r.end());
  return l;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}

