#include "doubles.h"
#include "loop.h"
#include <assert.h>
#include <math.h>

double doubles_max(double const* a, unsigned n)
{
  double max = a[0];
  for (unsigned i = 1; i < n; ++i)
    if (a[i] > max)
      max = a[i];
  return max;
}

double doubles_min(double const* a, unsigned n)
{
  double min = a[0];
  for (unsigned i = 1; i < n; ++i)
    if (a[i] < min)
      min = a[i];
  return min;
}

void doubles_axpy(double a, double const* x, double const* y,
    double* out, unsigned n)
{
  for (unsigned i = 0; i < n; ++i)
    out[i] = a * x[i] + y[i];
}

double* doubles_copy(double const* a, unsigned n)
{
  double* b = loop_malloc(sizeof(double) * n);
  for (unsigned i = 0; i < n; ++i)
    b[i] = a[i];
  return b;
}

/* ambitious note to self: this could be one source
   of partitionig/ordering dependence from inputs
   to outputs. */
double doubles_sum(double const* a, unsigned n)
{
  double s = 0;
  for (unsigned i = 0; i < n; ++i)
    s += a[i];
  return s;
}

double* doubles_exscan(double const* a, unsigned n)
{
  double* o = loop_malloc(sizeof(double) * (n + 1));
  double sum = 0;
  o[0] = 0;
  for (unsigned i = 0; i < n; ++i) {
    sum += a[i];
    o[i + 1] = sum;
  }
  return o;
}

unsigned doubles_diff(double const* a, double const* b, unsigned n,
    double tol, double floor)
{
  assert(0 < tol);
  assert(0 < floor);
  for (unsigned i = 0; i < n; ++i) {
    double fa = fabs(a[i]);
    double fb = fabs(b[i]);
    if (fa < floor && fb < floor)
      continue;
    double fm = fb > fa ? fb : fa;
    double rel = fabs(a[i] - b[i]) / fm;
    if (rel > tol)
      return 1;
  }
  return 0;
}
