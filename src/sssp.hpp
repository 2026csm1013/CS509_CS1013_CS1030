#ifndef SSSP_HPP
#define SSSP_HPP

#include "graph.hpp"
#include <vector>
#include <limits>

// Sentinel for "unreachable" — printed as INF by the driver.
constexpr double SSSP_UNREACHABLE = std::numeric_limits<double>::infinity();

struct SSSPResult
{
  std::vector<double> distance; // SSSP_UNREACHABLE if unreachable
  std::vector<int> predecessor; // -1 if unreachable or source
};

// Dijkstra's algorithm over a weighted CSR graph (all weights must be
// positive, as required by the assignment spec). Runs in O((V+E) log V)
// using a binary-heap priority queue.
SSSPResult sssp(const CSRGraph &g, int source);

#endif // SSSP_HPP
