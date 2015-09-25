#ifndef QUALITY_H
#define QUALITY_H

typedef double (*quality_function)(double (*coords)[3]);

double triangle_quality(double coords[3][3]);
double tet_quality(double coords[4][3]);

extern quality_function const the_quality_functions[4];
extern quality_function const the_equal_order_quality_functions[4];

double* element_qualities(
    unsigned elem_dim,
    unsigned nelems,
    unsigned const* verts_of_elems,
    double const* coords);

double min_element_quality(
    unsigned elem_dim,
    unsigned nelems,
    unsigned const* verts_of_elems,
    double const* coords);

struct mesh;

double* mesh_qualities(struct mesh* m);
double mesh_min_quality(struct mesh* m);

#endif
