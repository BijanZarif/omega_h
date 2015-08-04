#include "refine_topology.h"
#include "tables.h"
#include <stdlib.h>
#include <assert.h>

/* two more dimensions are introduced in the implementation:
 *   the "base" dimension is one minus the product dimension,
 *       product entities are generated by connecting a base entity
 *       to a generated vertex
 *   the "opp" dimension, the opp of the base dimension.
 *       the bases of an element which generate products are those
 *       which are opp to entities adjacent to the source entity.
 *
 * for example, when splitting an edge of a tet, the two vertices
 * of the edge cause the two new tets to be generated from
 * two base triangles, each base triangle being opp from
 * an edge vertex.
 */

void refine_topology(
    unsigned elem_dim,
    unsigned src_dim,
    unsigned prod_dim,
    unsigned nelems,
    unsigned const* verts_of_elems,
    unsigned const* gen_offset_of_elems,
    unsigned const* gen_vert_of_elems,
    unsigned const* gen_direction_of_elems,
    unsigned* nprods_out,
    unsigned** verts_of_prods_out)
{
  assert(elem_dim <= 3);
  assert(elem_dim >= src_dim);
  assert(elem_dim >= prod_dim);
  assert(prod_dim > 0);
  *nprods_out = 0;
  *verts_of_prods_out = 0;
  unsigned base_dim = prod_dim - 1;
  unsigned opp_dim = get_opposite_dim(elem_dim, base_dim);
  if (src_dim < opp_dim)
    return;
  unsigned opps_per_src = the_down_degrees[src_dim][opp_dim];
  assert(opps_per_src);
  unsigned nsplit_elems = gen_offset_of_elems[nelems];
  if (!nsplit_elems)
    return;
  unsigned nprods = nsplit_elems * opps_per_src;
  unsigned verts_per_prod = the_down_degrees[prod_dim][0];
  unsigned verts_per_base = verts_per_prod - 1;
  unsigned verts_per_elem = the_down_degrees[elem_dim][0];
  unsigned* verts_of_prods = malloc(
      sizeof(unsigned) * nsplit_elems * opps_per_src * verts_per_prod);
  unsigned const* const* elem_opps_of_srcs =
    the_canonical_orders[elem_dim][src_dim][opp_dim];
  unsigned const* const* elem_verts_of_bases =
    the_canonical_orders[elem_dim][base_dim][0];
  unsigned const* elem_base_of_opps = the_opposite_orders[elem_dim][opp_dim];
  for (unsigned i = 0; i < nelems; ++i) {
    if (gen_offset_of_elems[i] == gen_offset_of_elems[i + 1])
      continue;
    unsigned direction = gen_direction_of_elems[i];
    unsigned const* elem_opps_of_src = elem_opps_of_srcs[direction];
    unsigned const* verts_of_elem = verts_of_elems + i * verts_per_elem;
    unsigned gen_vert = gen_vert_of_elems[i];
    unsigned* verts_of_prod = verts_of_prods + 
      gen_offset_of_elems[i] * opps_per_src * verts_per_prod;
    for (unsigned j = 0; j < opps_per_src; ++j) {
      unsigned opp = elem_opps_of_src[j];
      unsigned base = elem_base_of_opps[opp];
      unsigned const* elem_verts_of_base = elem_verts_of_bases[base];
      for (unsigned k = 0; k < verts_per_base; ++k)
        verts_of_prod[k] = verts_of_elem[elem_verts_of_base[k]];
      verts_of_prod[verts_per_base] = gen_vert;
      verts_of_prod += verts_per_prod;
    }
  }
  *nprods_out = nprods;
  *verts_of_prods_out = verts_of_prods;
}
