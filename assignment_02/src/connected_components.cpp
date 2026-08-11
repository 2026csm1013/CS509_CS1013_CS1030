#include "connected_components.hpp"
#include <chrono>
#include <queue>

using namespace std;

ConnectedComponentsResult run_connected_components(const CSRGraph &csr)
{
  ConnectedComponentsResult result;
  result.component_ids.assign(csr.V, -1);

  auto start_time = chrono::high_resolution_clock::now();

  int curr_comp_id = 0;

  queue<int> q;

  for (int i = 0; i < csr.V; ++i)
  {
    if (result.component_ids[i] != -1) {
      continue;
    }

    // found new unvisited component
    result.component_ids[i] = curr_comp_id;

    q.push(i);

    while (!q.empty())
    {
      int u = q.front();
      q.pop();

      int start_idx = csr.row_ptr[u];

      int end_idx = csr.row_ptr[u + 1];

      for (int idx = start_idx; idx < end_idx; ++idx)
      {
        int v = csr.col_idx[idx];

        if (result.component_ids[v] == -1)
        {
          result.component_ids[v] = curr_comp_id;
          q.push(v);
        }
      }
    }

    ++curr_comp_id;
  }

  auto stop_time = chrono::high_resolution_clock::now();

  chrono::duration<double, milli> duration = stop_time - start_time;

  result.num_components = curr_comp_id;
  result.execution_time_ms = duration.count();

  return result;
}