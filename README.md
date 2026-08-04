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



9.2 Graph Results Table

AlgorithmFile NameVertices (V)Edges (E)Input TypeSourceExpected OutputActual OutputTimeStatusBFSbfs_10.txt1015Unweighted adjacency list0Traversal / distancesTraversal / distances0 msPassBFSbfs_100.txt100250Unweighted adjacency list0Traversal / distancesTraversal / distances0 msPassBFSbfs_10000.txt10,00030,000Unweighted adjacency list0Traversal / distancesTraversal / distances0 msPassBFSbfs_50000.txt50,000150,000Unweighted adjacency list0Traversal / distancesTraversal / distances2.004 msPassBFSbfs_100000.txt100,000300,000Unweighted adjacency list0Traversal / distancesTraversal / distances4.120 msPassDFSdfs_10.txt1015Unweighted adjacency list0TraversalTraversal0 msPassDFSdfs_100.txt100250Unweighted adjacency list0TraversalTraversal0 msPassDFSdfs_10000.txt10,00030,000Unweighted adjacency list0TraversalTraversal0 msPassDFSdfs_50000.txt50,000150,000Unweighted adjacency list0TraversalTraversal1.001 msPassDFSdfs_100000.txt100,000300,000Unweighted adjacency list0TraversalTraversal3.006 msPassSSSPsssp_10.txt1015Positive weighted adjacency list0Shortest distancesShortest distances0 msPassSSSPsssp_100.txt100250Positive weighted adjacency list0Shortest distancesShortest distances0 msPassSSSPsssp_10000.txt10,00030,000Positive weighted adjacency list0Shortest distancesShortest distances0 msPassSSSPsssp_50000.txt50,000150,000Positive weighted adjacency list0Shortest distancesShortest distances0 msPassSSSPsssp_100000.txt100,000300,000Positive weighted adjacency list0Shortest distancesShortest distances0 msPass