#ifndef SUBSET_H
#define SUBSET_H

unsigned* ints_subset(
    unsigned n,
    unsigned width,
    unsigned const* a,
    unsigned const* offsets);

double* doubles_subset(
    unsigned n,
    unsigned width,
    double const* a,
    unsigned const* offsets);

struct mesh;

struct mesh* subset_mesh(
    struct mesh* m,
    unsigned elem_dim,
    unsigned const* offsets);

#endif