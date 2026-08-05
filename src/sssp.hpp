#ifndef SSSP_HPP
#define SSSP_HPP

#include "graph.hpp"
#include <vector>
#include <limits>

using namespace std;

// unreachable — marked as INF.

constexpr double SSSP_UNREACHABLE = numeric_limits<double>::infinity();

struct SSSPResult
{
  vector<double> distance;
  vector<int> pre_decessor; // -1 if unreachable or source
};

// Dijkstra's algorithm over a weighted CSR graph using priority queue.

SSSPResult sssp(const CSRGraph &csr_graph, int source);

#endif
