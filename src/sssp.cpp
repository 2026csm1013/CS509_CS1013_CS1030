#include "sssp.hpp"
#include <queue>
#include <utility>

// Dijkstra's algorithm with a min-heap (lazy deletion: stale, outdated
// entries are simply skipped when popped rather than removed from the
// heap directly, since std::priority_queue doesn't support decrease-key).

SSSPResult sssp(const CSRGraph &g, int source)
{
  SSSPResult result;
  result.distance.assign(g.V, SSSP_UNREACHABLE);
  result.predecessor.assign(g.V, -1);

  if (source < 0 || source >= g.V)
  {
    return result;
  }

  // Min-heap of (distance, vertex), smallest distance on top.
  using PQEntry = std::pair<double, int>;
  std::priority_queue<PQEntry, std::vector<PQEntry>, std::greater<PQEntry>> pq;

  result.distance[source] = 0.0;
  pq.push({0.0, source});

  while (!pq.empty())
  {
    auto [d, u] = pq.top();
    pq.pop();

    // Stale entry: a shorter path to u was already finalized.
    if (d > result.distance[u])
      continue;

    for (int idx = g.row_ptr[u]; idx < g.row_ptr[u + 1]; ++idx)
    {
      int v = g.col_idx[idx];
      double w = g.values[idx];
      double new_dist = result.distance[u] + w;
      if (new_dist < result.distance[v])
      {
        result.distance[v] = new_dist;
        result.predecessor[v] = u;
        pq.push({new_dist, v});
      }
    }
  }

  return result;
}
