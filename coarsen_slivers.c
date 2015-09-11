#include "coarsen_slivers.h"
#include "mark.h"
#include "quality.h"
#include "ints.h"
#include "mesh.h"
#include "collapse_codes.h"
#include "coarsen_common.h"
#include <stdlib.h>

#include <stdio.h>

unsigned coarsen_slivers(
    struct mesh** p_m,
    double quality_floor,
    unsigned nlayers)
{
  struct mesh* m = *p_m;
  unsigned elem_dim = mesh_dim(m);
  unsigned nelems = mesh_count(m, elem_dim);
  double* quals = mesh_qualities(m);
  unsigned* slivers = malloc(sizeof(unsigned) * nelems);
  for (unsigned i = 0; i < nelems; ++i)
    slivers[i] = quals[i] < quality_floor;
  free(quals);
  printf("%u elems marked before layering\n", ints_sum(slivers, nelems));
  mesh_mark_dual_layers(m, &slivers, nlayers);
  printf("%u elems marked after layering\n", ints_sum(slivers, nelems));
  unsigned* marked_verts = mesh_mark_down(m, elem_dim, 0, slivers);
  printf("%u verts marked\n", ints_sum(marked_verts, mesh_count(m, 0)));
  free(slivers);
  unsigned nedges = mesh_count(m, 1);
  unsigned const* verts_of_edges = mesh_ask_down(m, 1, 0);
  unsigned* col_codes = malloc(sizeof(unsigned) * nedges);
  for (unsigned i = 0; i < nedges; ++i) {
    unsigned const* verts_of_edge = verts_of_edges + i * 2;
    col_codes[i] = 0;
    for (unsigned j = 0; j < 2; ++j) {
      unsigned vert = verts_of_edge[j];
      if (marked_verts[vert])
        col_codes[i] |= (1<<j);
    }
  }
  free(marked_verts);
  unsigned ret = coarsen_common(&m, col_codes, 0, 1);
  free(col_codes);
  *p_m = m;
  return ret;
}
