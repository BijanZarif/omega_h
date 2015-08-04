#ifndef INDEPENDENT_SET_H
#define INDEPENDENT_SET_H

/* given an undirected graph (usually obtained from get_star),
 * an initial filtered subset of the vertices,
 * and a scalar value (goodness) at the vertices,
 * returns a maximal independent set of the subgraph
 * induced by the filter, whose members are
 * preferrably those with locally high goodness values.
 * In order for this function to run efficiently,
 * there should not exist long paths with monotonically
 * decreasing goodness.
 */

unsigned* find_independent_set(
    unsigned nverts,
    unsigned const* offsets,
    unsigned const* adj,
    unsigned const* filter,
    double const* goodness);

#endif
