#include "quadratic_equation.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test_find_roots_1() {
  double e = 1E-7;
  double a = 1;
  double b = 0;
  double c = -1;
  double *x = (double *)malloc(0);
  int res = find_roots(a, b, c, e, x);
  assert(res == TWO_ROOTS);
  assert(fabs(x[0] + 1) < e);
  assert(fabs(x[1] - 1) < e);
  free(x);
}
void test_find_roots_2() {
  double e = 1E-7;
  double a = 1;
  double b = 0;
  double c = 0;
  double *x = (double *)malloc(0);
  int res = find_roots(a, b, c, e, x);
  assert(res == ONE_ROOT);
  assert(fabs(x[0]) < e);
  free(x);
}
void test_find_roots_3() {
  double e = 1E-7;
  double a = 1;
  double b = 0;
  double c = 1;
  double *x = (double *)malloc(0);
  int res = find_roots(a, b, c, e, x);
  assert(res == NO_REAL_ROOTS);
  free(x);
}
void test_find_roots_4() {
  double e = 1E-7;
  double acc = 1E-4;
  double a = 1;
  double b = 0;
  double c = -1E-7;
  double *x = (double *)malloc(0);
  int res = find_roots(a, b, c, e, x);
  assert(res == TWO_ROOTS);
  assert(fabs(x[0] + 3E-4) < acc);
  assert(fabs(x[1] - 3E-4) < acc);
  free(x);
}
void test_find_roots_5() {
  double e = 1E-7;
  double acc = 1E-11;
  double a = 1;
  double b = -1E+10;
  double c = -1;
  double *x = (double *)malloc(0);
  int res = find_roots(a, b, c, e, x);
  assert(res == TWO_ROOTS);
  assert(fabs(x[0] + 1E-10) < acc);
  assert(fabs(x[1] - 1E+10) < acc);
  free(x);
}
void test_find_roots_6() {
  double e = 1E-6;
  double acc = 1E-7;
  double a = 1;
  double b = 0;
  double c = -1E-8;
  double *x = (double *)malloc(0);
  int res = find_roots(a, b, c, e, x);
  assert(res == ONE_ROOT);
  assert(fabs(x[0]) < acc);
  free(x);
}

int main() {
  test_find_roots_1();
  test_find_roots_2();
  test_find_roots_3();
  test_find_roots_4();
  test_find_roots_5();
  test_find_roots_6();
  return 0;
}
