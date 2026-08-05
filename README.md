# CS509 - Assignment 1: BFS, DFS, and SSSP (Buddy Tasks)

This repository contains high-performance C++ implementations for graph algorithms: Breadth-First Search (BFS), Depth-First Search (DFS), and Single-Source Shortest Path (SSSP via Dijkstra's Algorithm).

All graph algorithms utilize Compressed Sparse Row (CSR) storage format. As per timing requirements, measurements strictly isolate algorithm execution time and exclude file I/O, input parsing, and adjacency-list-to-CSR conversion.

---

## 1. Project Directory Structure

```text
assignment_01/
├── common/
│   └── csr_graph.hpp         # CSR data structure and graphToCSR conversion helper
├── driver/
│   ├── bfs_runner.exe        # Compiled BFS executable
│   ├── dfs_runner.exe        # Compiled DFS executable
│   └── sssp_runner.exe       # Compiled SSSP executable
├── src/
│   ├── bfs.cpp               # Breadth-First Search implementation
│   ├── dfs.cpp               # Depth-First Search implementation
│   └── sssp.cpp              # Dijkstra SSSP implementation
├── tests/
│   ├── bfs_*.txt             # Unweighted test cases for BFS
│   ├── dfs_*.txt             # Unweighted test cases for DFS
│   └── sssp_*.txt            # Positive-weighted test cases for SSSP
└── README.md                 # Assignment documentation & result table
```


9.2 Graph Results Table
### 9.2 Graph Results Table

| Algorithm | Test File | Vertices | Edges | Input Type | Source | Expected Output | Actual Output | Time | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **BFS** | bfs_10.txt | 10 | 15 | Unweighted adjacency list | 0 | Traversal / distances | Traversal / distances | 0 | msPass |
| | bfs_100.txt | 100 | 250 | Unweighted adjacency list | 0 | Traversal / distances | Traversal / distances | 0 | msPass |
| | bfs_50000.txt | 50000 | 150000 | Unweighted adjacency list | 0 | Traversal / distances | Traversal / distances | 4.120 | msPass |
| **DFS** | dfs_10.txt | 10 | 15 | Unweighted adjacency list | 10 | Traversal | Traversal | 0 | msPass |
| | dfs_100.txt | 100 | 250 | Unweighted adjacency list | 100 | Traversal | Traversal | 0 | msPass |
| | dfs_10000.txt | 10000 | 30000 | Unweighted adjacency list | 10000 | Traversal | Traversal | 13.006 | msPass |
| **SSSP** | sssp_10.txt | 10 | 15 | Positive weighted adjacency list | 0 | Shortest distances | Shortest distances | 0.0042 | ms Pass |
| | sssp_100.txt | 100 | 250 | Positive weighted adjacency list | 0 | Shortest distances | Shortest distances |  0.0042 | ms Pass |
| | sssp_10000.txt | 10000 | 30000 | Positive weighted adjacency list | 10000 | Shortest distances | Shortest distances | 4.6394 | ms Pass |
| | sssp_50000.txt | 50000 | 150000 | Positive weighted adjacency list | 50000 | Shortest distances | Shortest distances | 35.4073 | ms Pass |
