# Assignment 2

This repository contains the C++ implementations, test drivers, and benchmark test suites. All algorithms operate on undirected, unweighted graphs represented in Compressed Sparse Row (CSR) format:
1. **Triangle Counting (TC):** Fast two-pointer set intersection on sorted CSR adjacency lists with triangle listing for $V \le 100$.
2. **Betweenness Centrality (BC):** Brandes' algorithm using BFS shortest-path exploration, path counting ($\sigma$), and stack-based dependency accumulation ($\delta$).
3. **Connected Components (CC):** Graph traversal assigning sequential component IDs in discovery order starting from 0.

## Graph Analytics Results Table

| Algorithm | Test File | Vertices ($V$) | Edges ($E$) | Expected Output | Actual Output | Algorithm Time | Status |
| --- | --- | --- | --- | --- | --- | --- | --- |
| **Triangle Counting** | `tc_10.txt` | 10 | 20 | Total Triangles + Triplet List | Total Triangles + Triplet List |  | Pass |
| **Triangle Counting** | `tc_100.txt` | 100 | 300 | Total Triangles + Triplet List | Total Triangles + Triplet List |  | Pass |
| **Triangle Counting** | `tc_10000.txt` | 10,000 | 20,000 | Total Triangles Count | Total Triangles Count |  | Pass |
| **Triangle Counting** | `tc_50000.txt` | 50,000 | 100,000 | Total Triangles Count | Total Triangles Count |  | Pass |
| **Triangle Counting** | `tc_100000.txt` | 100,000 | 200,000 | Total Triangles Count | Total Triangles Count |  | Pass |
| **Betweenness Centrality** | `bc_10.txt` | 10 | 15 | Centrality per vertex (2 d.p.) | Centrality per vertex (2 d.p.) |  | Pass |
| **Betweenness Centrality** | `bc_100.txt` | 100 | 200 | Centrality per vertex (2 d.p.) | Centrality per vertex (2 d.p.) |  | Pass |
| **Betweenness Centrality** | `bc_1000.txt` | 1,000 | 2,000 | Centrality per vertex (2 d.p.) | Centrality per vertex (2 d.p.) |  | Pass |
| **Betweenness Centrality** | `bc_5000.txt` | 5,000 | 10,000 | Centrality per vertex (2 d.p.) | Centrality per vertex (2 d.p.) |  | Pass |
| **Betweenness Centrality** | `bc_10000.txt` | 10,000 | 20,000 | Centrality per vertex (2 d.p.) | Centrality per vertex (2 d.p.) |  | Pass |
| **Connected Components** | `cc_10.txt` | 10 | 12 | Number of Comps + Node IDs | Number of Comps + Node IDs | 0.001 ms | Pass |
| **Connected Components** | `cc_100.txt` | 100 | 150 | Number of Comps + Node IDs | Number of Comps + Node IDs | 0.003 ms | Pass |
| **Connected Components** | `cc_10000.txt` | 10,000 | 20,000 | Number of Comps + Node IDs | Number of Comps + Node IDs | 0.977 ms | Pass |
| **Connected Components** | `cc_50000.txt` | 50,000 | 100,000 | Number of Comps + Node IDs | Number of Comps + Node IDs | 5.922 ms | Pass |
| **Connected Components** | `cc_100000.txt` | 100,000 | 200,000 | Number of Comps + Node IDs | Number of Comps + Node IDs | 14.545 ms | Pass |
