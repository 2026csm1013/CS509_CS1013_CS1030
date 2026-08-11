#ifndef CONNECTED_COMPONENTS_HPP
#define CONNECTED_COMPONENTS_HPP

#include <vector>
#include "../../assignment_01/src/csr.hpp"

using namespace std;

struct ConnectedComponentsResult
{
  int num_components = 0;
  vector<int> component_ids; // component id per vertex
  double execution_time_ms = 0.0;
};

// computes connected components using BFS traversal on CSR graph
ConnectedComponentsResult run_connected_components(const CSRGraph &csr);

#endif