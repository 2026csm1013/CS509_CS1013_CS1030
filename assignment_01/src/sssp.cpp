#include "sssp.hpp"
#include <queue>
#include <utility>
<<<<<<< HEAD:src/sssp.cpp

using namespace std;
=======
using namespace std;
// Dijkstra's algorithm with a min-heap (lazy deletion: stale, outdated
// entries are simply skipped when popped rather than removed from the
// heap directly, since std::priority_queue doesn't support decrease-key).
>>>>>>> 1e86aa4 (created one common folder):assignment_01/src/sssp.cpp

// Dijkstra's algorithm with a min-heap

SSSPResult sssp(const CSRGraph &csr_graph, int source)
{
  SSSPResult result;

  result.distance.assign(csr_graph.V, SSSP_UNREACHABLE);

  result.pre_decessor.assign(csr_graph.V, -1);

  if (source < 0 || source >= csr_graph.V)
  {
    return result;
  }

<<<<<<< HEAD:src/sssp.cpp
  // min-heap of (distance, vertex).

  using PQEntry = pair<double, int>;

=======
  // Min-heap of (distance, vertex), smallest distance on top.
  using PQEntry = std::pair<double, int>;
>>>>>>> 1e86aa4 (created one common folder):assignment_01/src/sssp.cpp
  priority_queue<PQEntry, vector<PQEntry>, greater<PQEntry>> pq;

  result.distance[source] = 0.0;
  pq.push({0.0, source});

  while (!pq.empty())
  {
    auto [d, u] = pq.top();
    pq.pop();

    // a shorter path to u was already done.
    if (d > result.distance[u])
      continue;

    for (int idx = csr_graph.row_ptr[u]; idx < csr_graph.row_ptr[u + 1]; ++idx)
    {
      int v = csr_graph.col_idx[idx];
      double w = csr_graph.values[idx];
      double new_dist = result.distance[u] + w;

      if (new_dist < result.distance[v])
      {
        result.distance[v] = new_dist;
        result.pre_decessor[v] = u;
        pq.push({new_dist, v});
      }
    }
  }

  return result;
}
