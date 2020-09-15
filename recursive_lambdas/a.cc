/**
 *   author:  stein
 *   created: 2020.09.10 19:52:39
**/
#include <bits/stdc++.h>
using namespace std;


// use a y-combinator
template <class F>
struct y_combinator
{
  F f; // the lambda will be stored here
  template <class... Args> 
  decltype (auto) operator() (Args&&... args) const {
    // we pass ourselves to f, then the arguments
    // the lamda should take the first argument as auto&& recurse or similar
    return f (*this, forward<Args>(args)...);
  }
};
template <class F>
y_combinator <decay_t<F>> make_y_combinator (F&& f) {
  return {
    forward<F> (f)
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr); 

  int test = -1;
  // using std::function
  function<int(int, int)> gcd = [&](int a, int b) {
    return b == 0 ? a : gcd(b, a%b);
  };
  test = gcd(9, 6);
  cout << test << endl;

  // Using Y Combinator
    // Using Y Combinator
  auto gcd_y = make_y_combinator(
    [] (auto&& gcd_y, int a, int b) {
      return b == 0 ? a : gcd_y(b, a%b);
    }
  );
  test = gcd_y(10, 5);
  cout << test << endl;
  return 0;
}
