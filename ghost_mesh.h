#ifndef GHOST_MESH_H
#define GHOST_MESH_H

struct mesh;

void ghost_mesh(struct mesh** p_m, unsigned nlayers);
void unghost_mesh(struct mesh** p_m);

void mesh_ensure_ghosting(struct mesh** p_m, unsigned nlayers);

void set_own_ranks_by_indset(
    struct mesh* m,
    unsigned key_dim);

#endif
