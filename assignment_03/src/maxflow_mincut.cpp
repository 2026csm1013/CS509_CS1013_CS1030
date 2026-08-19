#include "maxflow_mincut.hpp"
#include <fstream>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <stdexcept>
#include <limits>

using namespace std;

MaxFlowInput read_maxflow_input(const string &path)
{
  ifstream fin(path);

  if (!fin.is_open())
  {
    throw runtime_error("Could not open input file");
  }

  AdjacencyList list;

  list.weighted = true;

  if (!(fin >> list.V >> list.E))
  {
    throw runtime_error("Malformed header");
  }

  if (list.V <= 0)
  {
    throw runtime_error("Invalid vertex count");
  }

  list.adj.resize(list.V);

  for (int i = 0; i < list.V; ++i)
  {
    int u, degree;

    if (!(fin >> u >> degree))
    {
      throw runtime_error("Malformed adjacency row");
    }

    if (u < 0 || u >= list.V)
    {
      throw runtime_error("Vertex ID out of range");
    }

    list.adj[u].reserve(degree);

    for (int d = 0; d < degree; ++d)
    {
      int neighbor;
      double cap;

      if (!(fin >> neighbor >> cap))
      {
        throw runtime_error("Malformed edge");
      }

      if (cap < 0.0)
      {
        throw runtime_error("Negative capacity detected");
      }

      list.adj[u].push_back({neighbor, cap});
    }
  }

  int source = -1, sink = -1;
  string tag;

  while (fin >> tag)
  {
    if (tag == "SOURCE")
    {
      fin >> source;
    }
    else if (tag == "SINK")
    {
      fin >> sink;
    }
  }

  if (source < 0 || source >= list.V || sink < 0 || sink >= list.V)
  {
    throw runtime_error("Invalid source or sink vertex");
  }

  if (source == sink)
  {
    throw runtime_error("Source and sink cannot be identical");
  }

  MaxFlowInput input;
  input.csr = convert_to_csr(list);
  input.source = source;
  input.sink = sink;

  return input;
}

// internal structure for Dinic's Algorithm

struct ResidualEdge
{
  int to;
  int rev_idx;
  long long cap;
  long long flow;
  long long orig_cap;
};

MaxFlowResult run_maxflow_mincut(const CSRGraph &csr, int s, int t)
{
  MaxFlowResult result;
  result.source = s;
  result.sink = t;

  auto start_time = chrono::high_resolution_clock::now();

  int V = csr.V;

  vector<vector<ResidualEdge>> adj(V);

  struct OrigEdge
  {
    int u;
    int v;
    long long cap;
  };

  vector<OrigEdge> original_edges;
  original_edges.reserve(csr.E);

  for (int u = 0; u < V; ++u)
  {
    int start_idx = csr.row_ptr[u];
    int end_idx = csr.row_ptr[u + 1];

    for (int i = start_idx; i < end_idx; ++i)
    {
      int v = csr.col_idx[i];

      long long cap = static_cast<long long>(csr.values[i]);

      original_edges.push_back({u, v, cap});

      int u_idx = static_cast<int>(adj[u].size());
      int v_idx = static_cast<int>(adj[v].size());

      adj[u].push_back({v, v_idx, cap, 0, cap});
      adj[v].push_back({u, u_idx, 0, 0, 0});
    }
  }

  vector<int> level(V, -1);
  vector<int> ptr(V, 0);

  auto bfs = [&]() -> bool
  {
    fill(level.begin(), level.end(), -1);

    level[s] = 0;

    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
      int u = q.front();
      q.pop();

      for (const auto &e : adj[u])
      {
        if (e.cap - e.flow > 0 && level[e.to] == -1)
        {
          level[e.to] = level[u] + 1;
          q.push(e.to);
        }
      }
    }

    return level[t] != -1;
  };

  auto dfs = [&](auto self, int u, long long pushed) -> long long
  {
    if (pushed == 0 || u == t)
    {
      return pushed;
    }

    for (int &cid = ptr[u]; cid < static_cast<int>(adj[u].size()); ++cid)
    {
      auto &e = adj[u][cid];
      int tr = e.to;

      if (level[u] + 1 != level[tr] || e.cap - e.flow == 0)
      {
        continue;
      }

      long long tr_pushed = self(self, tr, min(pushed, e.cap - e.flow));

      if (tr_pushed == 0)
      {
        continue;
      }

      e.flow += tr_pushed;
      adj[tr][e.rev_idx].flow -= tr_pushed;

      return tr_pushed;
    }

    return 0;
  };

  // Compute Maximum Flow

  long long max_flow = 0;

  while (bfs())
  {
    fill(ptr.begin(), ptr.end(), 0);

    while (long long pushed = dfs(dfs, s, numeric_limits<long long>::max()))
    {
      max_flow += pushed;
    }
  }

  result.max_flow = max_flow;

  // Minimum Cut Extraction

  vector<bool> visited(V, false);
  queue<int> q;

  q.push(s);

  visited[s] = true;

  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    for (const auto &e : adj[u])
    {
      if (e.cap - e.flow > 0 && !visited[e.to])
      {
        visited[e.to] = true;

        q.push(e.to);
      }
    }
  }

  // Partition Source Side (S) and Sink Side (T)
  for (int u = 0; u < V; ++u)
  {
    if (visited[u])
    {
      result.source_side.push_back(u);
    }
    else
    {
      result.sink_side.push_back(u);
    }
  }

  long long min_cut_cap = 0;

  for (const auto &oe : original_edges)
  {
    if (visited[oe.u] && !visited[oe.v])
    {
      result.cut_edges.push_back({oe.u, oe.v, oe.cap});
      min_cut_cap += oe.cap;
    }
  }

  result.min_cut_capacity = min_cut_cap;

  auto end_time = chrono::high_resolution_clock::now();

  chrono::duration<double, milli> duration = end_time - start_time;

  result.execution_time_ms = duration.count();

  return result;
}

void print_maxflow_result(const MaxFlowResult &res)
{
  cout << "Algorithm: Maxflow-Mincut\n";

  cout << "Source: " << res.source << "\n";
  cout << "Sink: " << res.sink << "\n";

  cout << "Maximum flow: " << res.max_flow << "\n";
  cout << "Minimum cut capacity: " << res.min_cut_capacity << "\n";

  cout << "Source side:";
  for (int u : res.source_side)
    cout << " " << u;
  cout << "\n";

  cout << "Sink side:";

  for (int v : res.sink_side)
  {
    cout << " " << v;
  }

  cout << "\n";

  cout << "Cut edges:\n";
  for (const auto &e : res.cut_edges)
  {
    cout << e.u << " " << e.v << " " << e.capacity << "\n";
  }

  cout << fixed << setprecision(4);
  cout << "Execution time: " << res.execution_time_ms << " ms\n";
}