#include <assert.h>

#include "bcast.h"
#include "comm.h"
#include "mesh.h"
#include "parallel_inertial_bisect.h"
#include "parallel_mesh.h"
#include "refine_by_size.h"
#include "vtk.h"

int main()
{
  comm_init();
  struct mesh* m = 0;
  if (comm_rank() == 0) {
    m = new_box_mesh(1);
    for (unsigned i = 0; i < 2; ++i)
      uniformly_refine(&m);
  }
  m = bcast_mesh_metadata(m);
  mesh_number_simply(m, 0);
  balance_mesh_inertial(&m);
  mesh_global_renumber(m, 0);
  write_parallel_vtu(m, "out.pvtu");
  free_mesh(m);
  comm_fini();
}