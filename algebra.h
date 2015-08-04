#ifndef ALGEBRA_H
#define ALGEBRA_H

#include <math.h>

static inline void copy_vector(
    double const a[],
    double b[],
    unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    b[i] = a[i];
}

static inline void subtract_vectors(
    double const a[],
    double const b[],
    double c[],
    unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    c[i] = a[i] - b[i];
}

static inline void cross_product(
    double const a[],
    double const b[],
    double c[])
{
  c[0] = a[1] * b[2]  - a[2] * b[1];
  c[1] = a[2] * b[0]  - a[0] * b[2];
  c[2] = a[0] * b[1]  - a[1] * b[0];
}

static inline double dot_product(double const a[], double const b[], unsigned n)
{
  double d = 0;
  for (unsigned i = 0; i < n; ++i)
    d += a[i] * b[i];
  return d;
}

static inline double vector_norm(double const a[], unsigned n)
{
  return sqrt(dot_product(a, a, n));
}

static inline double vector_squared_distance(
    double const a[],
    double const b[],
    unsigned n)
{
  double s = 0;
  for (unsigned i = 0; i < n; ++i) {
    double dc = a[i] - b[i];
    s += dc * dc;
  }
  return s;
}

static inline double vector_distance(
    double const a[],
    double const b[],
    unsigned n)
{
  return sqrt(vector_squared_distance(a, b, n));
}

#endif