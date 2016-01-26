#ifndef OMEGA_H_H
#define OMEGA_H_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct osh_mesh* osh_t;

void osh_free(osh_t m);

osh_t osh_read_vtk(char const* filename);
void osh_write_vtk(osh_t m, char const* filename);

osh_t osh_new(unsigned elem_dim);
unsigned* osh_build_ents(osh_t m, unsigned ent_dim, unsigned nents);

unsigned osh_dim(osh_t m);
unsigned osh_nelems(osh_t m);
unsigned osh_nverts(osh_t m);
unsigned osh_count(osh_t m, unsigned dim);

unsigned const* osh_down(osh_t m, unsigned high_dim, unsigned low_dim);
unsigned const* osh_up(osh_t m, unsigned low_dim, unsigned high_dim);
unsigned const* osh_up_offs(osh_t m, unsigned low_dim, unsigned high_dim);
unsigned const* osh_up_dirs(osh_t m, unsigned low_dim, unsigned high_dim);
unsigned const* osh_star(osh_t m, unsigned low_dim, unsigned high_dim);
unsigned const* osh_star_offs(osh_t m, unsigned low_dim, unsigned high_dim);

double const* osh_coords(osh_t m);

unsigned const* osh_own_rank(osh_t m, unsigned dim);
unsigned const* osh_own_id(osh_t m, unsigned dim);

double* osh_new_field(osh_t m, unsigned dim, char const* name, unsigned ncomps);
double* osh_get_field(osh_t m, unsigned dim, char const* name);
void osh_free_field(osh_t m, char const* name);

unsigned osh_nfields(osh_t om, unsigned dim);
char const* osh_field(osh_t m, unsigned dim, unsigned i);
unsigned osh_components(osh_t m, unsigned dim, char const* name);

unsigned* osh_new_label(osh_t m, unsigned dim, char const* name, unsigned ncomps);
unsigned* osh_get_label(osh_t m, unsigned dim, char const* name);
void osh_free_label(osh_t m, char const* name);

unsigned long* osh_new_global(osh_t m, unsigned dim);

void osh_accumulate_to_owner(osh_t m, char const* name);
void osh_conform(osh_t m, char const* name);

void osh_mark_classified(osh_t m, unsigned ent_dim,
    unsigned class_dim, unsigned class_id, unsigned* marked);

void osh_ghost(osh_t* m, unsigned nlayers);

void osh_adapt(osh_t* m,
    double size_ratio_floor,
    double good_element_quality,
    unsigned nsliver_layers,
    unsigned max_passes);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
