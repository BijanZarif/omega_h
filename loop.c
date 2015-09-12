#include "loop.h"
#include <stdlib.h>
#include <assert.h>

void* loop_malloc(unsigned long n)
{
  return loop_host_malloc(n);
}

void loop_free(void* p)
{
  loop_host_free(p);
}

void* loop_host_malloc(unsigned long n)
{
  if (!n)
    return NULL;
  void* p = malloc(n);
  assert(p);
  return p;
}

void* loop_host_realloc(void* p, unsigned long n)
{
  return realloc(p, n);
}

void loop_host_free(void* p)
{
  free(p);
}
