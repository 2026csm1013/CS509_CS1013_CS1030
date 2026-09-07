#include "fastmap.hpp"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <random>

using namespace std;

FastMapInput read_fastmap_input(const string &path)
{
  ifstream fin(path);

  if (!fin.is_open())
  {
    throw runtime_error("Could not open file: " + path);
  }

  FastMapInput input;

  if (!(fin >> input.N >> input.target_k))
  {
    throw runtime_error("Malformed header in " + path);
  }

  // Input validation as per Section 12 requirements
  if (input.N <= 0)
  {
    throw runtime_error("N must be a positive integer.");
  }

  if (input.target_k <= 0 || input.target_k >= input.N)
  {
    throw runtime_error("Target dimension k must satisfy 0 < k < N.");
  }

  input.distance_matrix.resize(input.N, vector<double>(input.N, 0.0));

  for (int i = 0; i < input.N; ++i)
  {
    for (int j = 0; j < input.N; ++j)
    {
      if (!(fin >> input.distance_matrix[i][j]))
      {
        throw runtime_error("Error reading distance matrix entry (" + to_string(i) + "," + to_string(j) + ")");
      }

      if (input.distance_matrix[i][j] < 0.0)
      {
        throw runtime_error("Negative distance detected in matrix.");
      }

      if (i == j && abs(input.distance_matrix[i][j]) > 1e-9)
      {
        throw runtime_error("Diagonal entries must be 0.");
      }
    }
  }

  // Validate symmetry
  for (int i = 0; i < input.N; ++i)
  {
    for (int j = i + 1; j < input.N; ++j)
    {
      if (abs(input.distance_matrix[i][j] - input.distance_matrix[j][i]) > 1e-5)
      {
        throw runtime_error("Distance matrix is not symmetric.");
      }
    }
  }

  return input;
}

// Helper: Compute deflated distance between two objects i and j given current coordinates

static double get_deflated_distance_sq(int i, int j, const vector<vector<double>> &D_orig, const vector<vector<double>> &coords, int current_dim)
{
  double d_orig_sq = D_orig[i][j] * D_orig[i][j];

  double coordinate_diff_sq = 0.0;

  for (int d = 0; d < current_dim; ++d)
  {
    double diff = coords[i][d] - coords[j][d];
    coordinate_diff_sq += diff * diff;
  }

  double deflated_sq = d_orig_sq - coordinate_diff_sq;

  return (deflated_sq > 0.0) ? deflated_sq : 0.0;
}

// Helper: Heuristic pivot selection to find two distant objects
static pair<int, int> select_pivots(int N, const vector<vector<double>> &D_orig, const vector<vector<double>> &coords, int current_dim)
{
  // Pick an initial object (0)
  int o1 = 0;

  // Find object farthest from o1 using deflated distance
  int o2 = o1;

  double max_dist_sq = -1.0;

  for (int i = 0; i < N; ++i)
  {
    double dist_sq = get_deflated_distance_sq(o1, i, D_orig, coords, current_dim);

    if (dist_sq > max_dist_sq)
    {
      max_dist_sq = dist_sq;
      o2 = i;
    }
  }

  // Find object farthest from o2
  int pivot1 = o2;
  int pivot2 = o2;

  max_dist_sq = -1.0;

  for (int i = 0; i < N; ++i)
  {
    double dist_sq = get_deflated_distance_sq(pivot1, i, D_orig, coords, current_dim);

    if (dist_sq > max_dist_sq)
    {
      max_dist_sq = dist_sq;
      pivot2 = i;
    }
  }

  return {pivot1, pivot2};
}

FastMapResult compute_fastmap(const FastMapInput &input)
{
  FastMapResult result;

  int N = input.N;
  int target_k = input.target_k;

  result.coordinates.assign(N, vector<double>(target_k, 0.0));
  result.pivots.resize(target_k);

  for (int k = 0; k < target_k; ++k)
  {
    // 1. Select Pivot Pair for dimension k
    pair<int, int> pivot_pair = select_pivots(N, input.distance_matrix, result.coordinates, k);

    int a = pivot_pair.first;
    int b = pivot_pair.second;

    result.pivots[k] = pivot_pair;

    double dab_sq = get_deflated_distance_sq(a, b, input.distance_matrix, result.coordinates, k);
    double dab = sqrt(dab_sq);

    if (dab < 1e-9)
    {
      // Objects have collapsed in remaining space; set coordinate to 0
      for (int i = 0; i < N; ++i)
      {
        result.coordinates[i][k] = 0.0;
      }

      continue;
    }

    // 2. Project every object onto line joining a and b using Law of Cosines
    for (int i = 0; i < N; ++i)
    {
      if (i == a)
      {
        result.coordinates[i][k] = 0.0;
      }
      else if (i == b)
      {
        result.coordinates[i][k] = dab;
      }
      else
      {
        double dai_sq = get_deflated_distance_sq(a, i, input.distance_matrix, result.coordinates, k);
        double dbi_sq = get_deflated_distance_sq(b, i, input.distance_matrix, result.coordinates, k);

        // x_i = (d_{ai}^2 + d_{ab}^2 - d_{bi}^2) / (2 * d_{ab})
        double x_i = (dai_sq + dab_sq - dbi_sq) / (2.0 * dab);
        result.coordinates[i][k] = x_i;
      }
    }
  }

  // Compute Average Distance Error between embedded Euclidean distances and original distances
  double total_error = 0.0;
  int pair_count = 0;

  for (int i = 0; i < N; ++i)
  {
    for (int j = i + 1; j < N; ++j)
    {
      double orig_d = input.distance_matrix[i][j];

      double embed_d_sq = 0.0;
      for (int k = 0; k < target_k; ++k)
      {
        double diff = result.coordinates[i][k] - result.coordinates[j][k];
        embed_d_sq += diff * diff;
      }
      double embed_d = sqrt(embed_d_sq);

      total_error += abs(orig_d - embed_d);
      pair_count++;
    }
  }

  result.avg_distance_error = (pair_count > 0) ? (total_error / pair_count) : 0.0;

  return result;
}