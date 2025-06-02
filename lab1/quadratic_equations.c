#include "quadratic_equation.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int find_roots(double a, double b, double c, double e, double *x) {
  if (fabs(a) <= e) {
    return NOT_QUADRATIC_EQUATION;
  }
  b = b / a;
  c = c / a;
  int sign;
  if (b < -e) {
    sign = -1;
  } else {
    sign = 1;
  }
  double d = b * b - 4 * c;
  if (d < -e) {
    return NO_REAL_ROOTS;
  } else if (fabs(d) <= e) {
    x = realloc(x, sizeof(double));
    x[0] = -b / 2;
    return ONE_ROOT;
  } else {
    x = realloc(x, sizeof(double) * 2);
    x[0] = (-b - sign * sqrt(d)) / 2;
    x[1] = c / x[0];
    if (x[0] > x[1]) {
      double p = x[1];
      x[1] = x[0];
      x[0] = p;
    }
    return TWO_ROOTS;
  }
}
