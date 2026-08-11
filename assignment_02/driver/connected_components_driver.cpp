#include <iostream>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <string>
#include "../../assignment_01/src/csr.hpp"
#include "../src/connected_components.hpp"

using namespace std;

namespace fs = filesystem;

void print_result(const ConnectedComponentsResult &res, int V)
{
  cout << "Algorithm: Connected Components\n";
  cout << "Number of components: " << res.num_components << "\n";
  cout << "Vertex Component\n";

  for (int i = 0; i < V; ++i)
  {
    cout << i << " " << res.component_ids[i] << "\n";
  }

  cout << fixed << setprecision(3);
  cout << "Execution time: " << res.execution_time_ms << " ms\n";
}

void process_single_file(const string &path)
{
  cout << "\nProcessing file: " << path << "\n";

  try
  {
    // 1. read unweighted adjacency list (NOT TIMED)
    AdjacencyList adj_list = read_adjacency_list(path, false);

    // 2. convert to CSR (NOT TIMED)
    CSRGraph csr = convert_to_csr(adj_list);

    // 3. execute connected components
    ConnectedComponentsResult res = run_connected_components(csr);

    // 4. output results
    print_result(res, csr.V);
  }
  catch (const exception &e)
  {
    cerr << "Error: " << e.what() << "\n";
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <test_file_path> OR " << argv[0] << " --all <test_dir>\n";
    return 1;
  }

  string arg1 = argv[1];

  if (arg1 == "--all")
  {
    if (argc < 3)
    {
      cerr << "Error: Missing directory path for --all\n";
      return 1;
    }

    string dir_path = argv[2];

    for (const auto &entry : fs::directory_iterator(dir_path))
    {
      if (entry.path().extension() == ".txt" && entry.path().filename().string().rfind("cc_", 0) == 0)
      {
        process_single_file(entry.path().string());
      }
    }
  }
  else
  {
    process_single_file(arg1);
  }

  return 0;
}