// SSSP driver.

// Usage:
//   sssp_driver <test_file.txt>
//   sssp_driver --all <tests_directory>
//

#include "../src/graph.hpp"
#include "../src/sssp.hpp"
#include <chrono>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <algorithm>

using namespace std;

namespace fs = filesystem;
using Clock = chrono::steady_clock;

static bool run_one_file(const string &path)
{
  cout << "==============================================\n";
  cout << "Test file: " << path << "\n";

  // --- Setup: NOT timed ---

  AdjacencyList list;

  try
  {
    list = read_adjacency_list(path, /*weighted=*/true);
  }
  catch (const exception &e)
  {
    cerr << "Error reading " << path << ": " << e.what() << "\n";
    return false;
  }

  // preprocessing — not timed
  CSRGraph csr = convert_to_csr(list);

  cout << "Vertices: " << list.V << ", Edges: " << list.E << "\n\n";

  // --- timed ---
  auto t0 = Clock::now();

  SSSPResult res = sssp(csr, list.source);

  auto t1 = Clock::now();

  double ms = chrono::duration<double, milli>(t1 - t0).count();

  cout << "Algorithm: SSSP\n";
  cout << "Source: " << list.source << "\n";
  cout << "Vertex Distance\n";

  for (int v = 0; v < csr.V; ++v)
  {
    cout << v << " ";
    if (res.distance[v] == SSSP_UNREACHABLE)
    {
      cout << "INF\n";
    }
    else if (res.distance[v] == static_cast<long long>(res.distance[v]))
    {
      cout << static_cast<long long>(res.distance[v]) << "\n";
    }
    else
    {
      cout << res.distance[v] << "\n";
    }
  }

  cout << "Execution time: " << fixed << setprecision(4) << ms << " ms\n\n";

  return true;
}

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Usage:\n"
         << "  " << argv[0] << " <test_file.txt>\n"
         << "  " << argv[0] << " --all <tests_directory>\n";
    return 1;
  }

  string first_arg = argv[1];

  if (first_arg == "--all")
  {
    if (argc < 3)
    {
      cerr << "Error: --all requires a directory path.\n";
      return 1;
    }

    string dir = argv[2];

    if (!fs::exists(dir) || !fs::is_directory(dir))
    {
      cerr << "Error: directory not found: " << dir << "\n";
      return 1;
    }

    vector<fs::path> files;

    for (const auto &entry : fs::directory_iterator(dir))
    {
      if (entry.path().extension() == ".txt")
        files.push_back(entry.path());
    }

    sort(files.begin(), files.end());

    if (files.empty())
    {
      cerr << "No .txt test files found in " << dir << "\n";
      return 1;
    }

    bool is_ok = true;

    for (const auto &f : files)
    {
      if (!run_one_file(f.string()))
        is_ok = false;
    }
    return is_ok ? 0 : 1;
  }
  else
  {
    string path = first_arg;
    if (!fs::exists(path))
    {
      cerr << "Error: input file not found: " << path << "\n";
      return 1;
    }
    return run_one_file(path) ? 0 : 1;
  }
}
