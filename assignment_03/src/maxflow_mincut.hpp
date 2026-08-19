#ifndef MAXFLOW_MINCUT_HPP
#define MAXFLOW_MINCUT_HPP

#include <vector>
#include <string>
#include <iostream>
#include "../../assignment_01/src/csr.hpp"

using namespace std;

struct CutEdge
{
  int u;
  int v;
  long long capacity;
};

struct MaxFlowResult
{
  int source = 0;
  int sink = 0;

  long long max_flow = 0;
  long long min_cut_capacity = 0;

  vector<int> source_side;
  vector<int> sink_side;

  vector<CutEdge> cut_edges;

  double execution_time_ms = 0.0;
};

struct MaxFlowInput
{
  CSRGraph csr;

  int source = 0;
  int sink = 0;
};

MaxFlowInput read_maxflow_input(const string &path);

MaxFlowResult run_maxflow_mincut(const CSRGraph &csr, int source, int sink);

void print_maxflow_result(const MaxFlowResult &res);

#endif