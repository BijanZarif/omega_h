#include <assert.h>
#include <stdlib.h>

#include "ints.h"
#include "loop.h"
#include "mesh.h"
#include "subset.h"
#include "vtk.h"

int main(int argc, char** argv)
{
  assert(argc == 4);
  struct mesh* m = read_vtu(argv[1]);
  unsigned dim = (unsigned) atoi(argv[2]);
  assert(dim <= 3);
  unsigned* offsets = uints_linear(mesh_count(m, dim) + 1, 1);
  struct mesh* sm = subset_mesh(m, dim, offsets);
  loop_free(offsets);
  free_mesh(m);
  write_vtu(sm, argv[3]);
  free_mesh(sm);
}