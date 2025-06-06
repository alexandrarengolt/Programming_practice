#include "../integral.h"
#include <assert.h>
#include <math.h>

double square_function(double x) { return x * x; }

double cos_function(double x) { return cos(x); }

void test_integral_1() {
  float a = -10;
  float b = -2;
  int num_of_parts = 300000;
  double result = integral(square_function, a, b, num_of_parts);

  assert(fabs(result - 330.66) < 10E-2);
}

void test_integral_2() {
  float a = -1;
  float b = 5;
  int num_of_parts = 300000;
  double result = integral(square_function, a, b, num_of_parts);

  assert(fabs(result - 42.00) < 10E-2);
}

void test_integral_3() {
  float a = 15;
  float b = 200;
  int num_of_parts = 300000;
  double result = integral(square_function, a, b, num_of_parts);

  assert(fabs(result - 2665541.66) < 10E-2);
}

void test_integral_4() {
  float a = -1;
  float b = 10;
  int num_of_parts = 400000;
  double result = integral(cos_function, a, b, num_of_parts);

  assert(fabs(result - 0.29) < 10E-2);
}

void test_integral_5() {
  float a = 15;
  float b = 20;
  int num_of_parts = 400000;
  double result = integral(cos_function, a, b, num_of_parts);

  assert(fabs(result - 0.26) < 10E-2);
}

void test_integral_6() {
  float a = -9;
  float b = -7;
  int num_of_parts = 400000;
  double result = fabs(integral(cos_function, a, b, num_of_parts));

  assert(fabs(result - 0.24) < 10E-2);
}

int main() {
  test_integral_1();
  test_integral_2();
  test_integral_3();
  test_integral_4();
  test_integral_5();
  test_integral_6();

  return 0;
}
