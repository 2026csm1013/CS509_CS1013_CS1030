#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <stdexcept>
#include "../src/maxflow_mincut.hpp"

using namespace std;

namespace fs = filesystem;

void run_file(const string &path)
{
  cout << "\n=======================================================\n";
  cout << "Processing Test File: " << path << "\n";
  cout << "=======================================================\n";

  try
  {
    // step 1: read input & convert to CSR
    MaxFlowInput input = read_maxflow_input(path);

    // step 2: run Maxflow-Mincut
    MaxFlowResult result = run_maxflow_mincut(input.csr, input.source, input.sink);

    // step 3: print result
    print_maxflow_result(result);
  }
  catch (const exception &e)
  {
    cerr << "Error running test " << path << ": " << e.what() << "\n";
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cerr << "Usage: " << argv[0] << " <path_to_test_file>\n";
    cerr << "   or: " << argv[0] << " --all <test_directory_path>\n";

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

    if (!fs::exists(dir_path) || !fs::is_directory(dir_path))
    {
      cerr << "Error: Directory does not exist: " << dir_path << "\n";
      return 1;
    }

    vector<string> test_files;

    for (const auto &entry : fs::directory_iterator(dir_path))
    {
      if (entry.path().extension() == ".txt")
      {
        test_files.push_back(entry.path().string());
      }
    }

    sort(test_files.begin(), test_files.end());

    if (test_files.empty())
    {
      cout << "No .txt test files found in " << dir_path << "\n";
      return 0;
    }

    for (const auto &file : test_files)
    {
      run_file(file);
    }
  }
  else
  {
    run_file(arg1);
  }

  return 0;
}