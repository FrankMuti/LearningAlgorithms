/**
 *    author:     stein
 *    created:    2020.11.09 00:42:25
**/
#include <bits/stdc++.h>

using namespace std;

int main() {
  int *a;
  a = (int*) malloc(4*sizeof(int));
  free(a);
  printf("%d\n", a);
  return 0;
}

