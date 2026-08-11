# Assignment 2

This repository contains the C++ implementations, test drivers, and benchmark test suites. All algorithms operate on undirected, unweighted graphs represented in Compressed Sparse Row (CSR) format:
1. **Triangle Counting (TC):** Fast two-pointer set intersection on sorted CSR adjacency lists with triangle listing for $V \le 100$.
2. **Betweenness Centrality (BC):** Brandes' algorithm using BFS shortest-path exploration, path counting ($\sigma$), and stack-based dependency accumulation ($\delta$).
3. **Connected Components (CC):** Graph traversal assigning sequential component IDs in discovery order starting from 0.
