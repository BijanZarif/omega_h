#include <assert.h>
#include <stdlib.h>

#include "comm.h"
#include "ghost_mesh.h"
#include "mesh.h"
#include "vtk.h"

int main(int argc, char** argv)
{
  comm_init();
  assert(argc == 4);
  struct mesh* m = 0;
  m = read_mesh_vtk(argv[1]);
  unsigned nlayers = (unsigned) atoi(argv[2]);
  assert(nlayers <= 10);
  ghost_mesh(&m, nlayers);
  write_mesh_vtk(m, argv[3]);
  free_mesh(m);
  comm_fini();
}
