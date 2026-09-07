#include "../src/fastmap.hpp"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;

namespace fs = filesystem;

void run_test_case(const string &path)
{
  cout << "\nProcessing file: " << path << "\n";

  FastMapInput input;

  try
  {
    input = read_fastmap_input(path);
  }
  catch (const exception &e)
  {
    cerr << "Error reading FastMap input: " << e.what() << "\n";
    return;
  }

  // Measure algorithm execution time ONLY (Pivot selection, projection, deflation)
  auto start_time = chrono::high_resolution_clock::now();
  FastMapResult result = compute_fastmap(input);
  auto end_time = chrono::high_resolution_clock::now();

  chrono::duration<double, milli> elapsed = end_time - start_time;

  result.execution_time_ms = elapsed.count();

  // Output formatting adhering strictly to Section 8.3 Expected FastMap Output
  cout << "Algorithm: FastMap\n";
  cout << "Target dimensions: " << input.target_k << "\n";
  cout << "Pivots per dimension:\n";

  // for (int k = 0; k < input.target_k; ++k)
  // {
  //   cout << "Dim " << (k + 1) << ": " << result.pivots[k].first << " " << result.pivots[k].second << "\n";
  // }

  cout << "Object coordinates:\n";
  cout << fixed << setprecision(6);

  for (int i = 0; i < input.N; ++i)
  {
    cout << i << ":";

    for (int k = 0; k < input.target_k; ++k)
    {
      cout << " " << result.coordinates[i][k];
    }

    cout << "\n";
  }

  cout << fixed << setprecision(4);

  for (int k = 0; k < input.target_k; ++k)
  {
    cout << "Dim " << (k + 1) << ": " << result.pivots[k].first << " " << result.pivots[k].second << "\n";
  }

  cout << "Avg Distance Error: " << result.avg_distance_error << "\n";
  cout << "Execution time: " << result.execution_time_ms << " ms\n";
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <input_file_path_or_--all> [dir_path]\n";
    return 1;
  }

  string arg1 = argv[1];

  if (arg1 == "--all")
  {
    string dir_path = (argc >= 3) ? argv[2] : "assignment_04/tests";

    if (!fs::exists(dir_path))
    {
      cerr << "Error: Directory " << dir_path << " does not exist.\n";
      return 1;
    }

    vector<string> files;

    for (const auto &entry : fs::directory_iterator(dir_path))
    {
      if (entry.path().extension() == ".txt" && entry.path().filename().string().rfind("fm_", 0) == 0)
      {
        files.push_back(entry.path().string());
      }
    }

    sort(files.begin(), files.end());

    for (const auto &file : files)
    {
      run_test_case(file);
    }
  }
  else
  {
    run_test_case(arg1);
  }

  return 0;
}