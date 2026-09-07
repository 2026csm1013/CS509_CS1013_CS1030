#ifndef FASTMAP_HPP
#define FASTMAP_HPP

#include <vector>
#include <string>

using namespace std;

struct FastMapInput
{
  int N = 0;                              // Number of objects
  int target_k = 0;                       // Target embedding dimension
  vector<vector<double>> distance_matrix; // N x N symmetric pairwise distance matrix
};

struct FastMapResult
{
  vector<vector<double>> coordinates; // N x target_k projected coordinates
  vector<pair<int, int>> pivots;      // Pivot pair (pivot1, pivot2) for each dimension
  double avg_distance_error = 0.0;    // Average distance mapping error
  double execution_time_ms = 0.0;
};

// Reads NxN distance matrix file for FastMap
FastMapInput read_fastmap_input(const string &path);

// Core FastMap algorithm implementation (timed region)
FastMapResult compute_fastmap(const FastMapInput &input);

#endif