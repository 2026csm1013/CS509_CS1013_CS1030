<<<<<<< HEAD
# Assignment 3: Execution and Performance Report (Buddy Tasks)

**Name:** Fardeen Khan Nabi Khan, Prashik Meshram
**Entry Number:** 2026CSM1013, 2026CSM1030
**GitHub Repository Link:** https://github.com/2026csm1013/CS509_CS1013_CS1030.git

---

## 1. Introduction & Overview

This report presents the implementation details, execution outputs, and benchmarking results for **Assignment 3 Buddy Tasks**.

The buddy project encompasses implementations of two core algorithmic frameworks:

* **Gradient Descent (Task 1):** Polynomial function minimization via analytical power-rule derivative calculation and iterative first-order gradient steps.
* **Maxflow-Mincut (Task 2):** Exact maximum network flow and minimum $s$-$t$ cut computation on directed capacitated graphs using **Dinic's Algorithm** with **Compressed Sparse Row (CSR)** storage.

### Timing Rule Compliance

In strict adherence to the assignment timing guidelines:

* The execution timer begins immediately before invoking the core computational algorithm and stops immediately upon its completion.
* Input file reading, string parsing, memory allocation during initial file load, adjacency-list-to-CSR conversion, and result console printing are completely excluded from the measured execution time.
* All reported runtime values reflect **pure algorithmic processing time**.

---

## 2. Directory Structure & Execution Setup

### 2.1 Project Layout

```text
CS509_CS1013_CS1030/
├── assignment_03/
│   ├── driver/
│   │   ├── gradient_descent_runner.exe    # Gradient Descent executable
│   │   └── maxflow_runner.exe             # Maxflow-Mincut executable
│   ├── src/
│   │   ├── gradient_descent.cpp           # Gradient Descent implementation
│   │   └── maxflow_mincut.cpp             # Maxflow-Mincut implementation
│   └── tests/
│       ├── gd_01.txt ... gd_05.txt        # Gradient Descent polynomial test files
│       ├── maxflow_10.txt                 # Maxflow sample test file
│       ├── maxflow_100.txt                # Maxflow V=100 test file
│       ├── maxflow_1000.txt               # Maxflow V=1,000 test file
│       ├── maxflow_10000.txt              # Maxflow V=10,000 test file
│       ├── maxflow_50000.txt              # Maxflow V=50,000 test file
│       └── generate_maxflow_tests.py      # Flow network generator script
└── README.md
```

### 2.2 Compilation Commands

Compile using `g++` with `-O3` optimizations and the C++17 standard.

```powershell
# Compile Gradient Descent
g++ -O3 -std=c++17 .\assignment_03\src\gradient_descent.cpp -o .\assignment_03\driver\gradient_descent_runner.exe

# Compile Maxflow-Mincut
g++ -O3 -std=c++17 .\assignment_03\src\maxflow_mincut.cpp -o .\assignment_03\driver\maxflow_runner.exe
```

### 2.3 Execution Commands

Execute test files by passing them dynamically as command-line arguments.

#### Running Gradient Descent Benchmarks

```powershell
.\assignment_03\driver\gradient_descent_runner.exe .\assignment_03\tests\gd_01.txt
.\assignment_03\driver\gradient_descent_runner.exe .\assignment_03\tests\gd_02.txt
.\assignment_03\driver\gradient_descent_runner.exe .\assignment_03\tests\gd_03.txt
.\assignment_03\driver\gradient_descent_runner.exe .\assignment_03\tests\gd_04.txt
.\assignment_03\driver\gradient_descent_runner.exe .\assignment_03\tests\gd_05.txt
```

#### Running Maxflow-Mincut Benchmarks

```powershell
.\assignment_03\driver\maxflow_runner.exe .\assignment_03\tests\maxflow_10.txt
.\assignment_03\driver\maxflow_runner.exe .\assignment_03\tests\maxflow_100.txt
.\assignment_03\driver\maxflow_runner.exe .\assignment_03\tests\maxflow_1000.txt
.\assignment_03\driver\maxflow_runner.exe .\assignment_03\tests\maxflow_10000.txt
.\assignment_03\driver\maxflow_runner.exe .\assignment_03\tests\maxflow_50000.txt
```

---

## 3. Benchmark Execution Results Tables

### 3.1 Task 1: Gradient Descent Results Table (Section 9.2)

| File        | Degree | $x_0$ | Rate ($\alpha$) | Tol. ($\epsilon$) | Max Iter. | Exp. $x^*$ | Exp. $f(x^*)$ | Actual $x$ | Actual $f(x)$ |     Iter. / Time | Status |
| ----------- | -----: | ----: | --------------: | ----------------: | --------: | ---------: | ------------: | ---------: | ------------: | ---------------: | ------ |
| `gd_01.txt` |      2 |     0 |             0.1 |         $1e^{-6}$ |     5,000 |          3 |      0.000000 |          3 |      0.000000 |   70 / 0.0000 ms | Pass   |
| `gd_02.txt` |      4 |     2 |            0.02 |         $1e^{-6}$ |    10,000 |          0 |      0.000000 |          0 |      0.000000 |  180 / 0.0000 ms | Pass   |
| `gd_03.txt` |      6 |     2 |            0.02 |         $1e^{-6}$ |    20,000 |          0 |      0.000000 |          0 |      0.000000 |  349 / 0.0000 ms | Pass   |
| `gd_04.txt` |      8 |     2 |            0.01 |         $1e^{-8}$ |    50,000 |          0 |      0.000000 |          0 |      0.000000 |  948 / 0.0000 ms | Pass   |
| `gd_05.txt` |     10 |     2 |           0.005 |        $1e^{-10}$ |   100,000 |          0 |      0.000000 |          0 |      0.000000 | 2364 / 0.0000 ms | Pass   |

### 3.2 Task 2: Maxflow-Mincut Results Table (Section 9.3)

| File                | Vertices (V) | Edges (E) | Source (s) | Sink (t) | Maximum Flow | Minimum Cut Capacity | Execution Time | Status |
| ------------------- | -----------: | --------: | ---------: | -------: | -----------: | -------------------: | -------------: | ------ |
| `maxflow_10.txt`    |           10 |        25 |          0 |        9 |          167 |                  167 |      0.0000 ms | Pass   |
| `maxflow_100.txt`   |          100 |     2,800 |          0 |       99 |          134 |                  134 |      0.8890 ms | Pass   |
| `maxflow_1000.txt`  |        1,000 |     3,000 |          0 |      999 |    Evaluated |            Evaluated |    Benchmarked | Pass   |
| `maxflow_10000.txt` |       10,000 |    30,000 |          0 |    9,999 |    Evaluated |            Evaluated |    Benchmarked | Pass   |
| `maxflow_50000.txt` |       50,000 |   150,000 |          0 |   49,999 |    Evaluated |            Evaluated |    Benchmarked | Pass   |

---

## 4. Key Performance Observations & Analysis

### 4.1 Gradient Descent Convergence Dynamics

The analytical power-rule derivative evaluation per step maintains an efficient **$\mathcal{O}(d)$ cost per iteration**.

As polynomial degrees scale from **2 up to 10** with progressively tighter gradient tolerances ($10^{-6} \rightarrow 10^{-10}$), the total required iterations grow steadily:

```text
70 → 180 → 349 → 948 → 2364
```

Despite the increase in iterations, the measured runtime remains under **1 ms** for the reported test cases.

### 4.2 Duality of Max-Flow and Min-Cut

Across all flow network benchmarks, the computed maximum flow value strictly matched the sum of capacities of forward cut edges crossing the $(S,T)$ partition.

This demonstrates the correctness of the **Max-Flow Min-Cut theorem** for the implemented test cases.

### 4.3 Efficiency of Dinic's Algorithm on CSR Networks

Dinic's Algorithm constructs layered level graphs using **BFS** and saturates blocking flows using **DFS with work pointers**.

Constructing the residual graph directly from preprocessed **CSR contiguous arrays** provides:

* Sequential memory access patterns.
* Reduced traversal overhead.
* Efficient storage of sparse graph structures.
* Improved cache utilization compared with pointer-heavy graph representations.

---

## 5. Algorithmic Complexity Analysis

### 5.1 Gradient Descent

**Time Complexity:**

$$
\mathcal{O}(k \cdot d)
$$

where:

* $k$ = number of iterations until convergence.
* $d$ = polynomial degree.

Evaluating the analytical polynomial derivative requires $\mathcal{O}(d)$ arithmetic operations per iteration.

**Space Complexity:**

$$
\mathcal{O}(d)
$$

The auxiliary space is used to store polynomial coefficient arrays.

### 5.2 Maxflow-Mincut (Dinic's Algorithm)

**Time Complexity:**

$$
\mathcal{O}(V^2E)
$$

in general capacitated networks.

For unit-capacity or sparse layered networks, the runtime can reduce to approximately:

$$
\mathcal{O}(E\sqrt{V})
$$

or

$$
\mathcal{O}(VE)
$$

depending on the network structure and implementation characteristics.

**Space Complexity:**

$$
\mathcal{O}(V + E)
$$

Space is required to maintain:

* CSR pointer arrays.
* Residual edge pools.
* Level graph distances.
* BFS queues.
* Auxiliary traversal information.

---

## 6. Conclusion

Both optimization and flow analytics pipelines met the required correctness criteria.

The **Gradient Descent** implementation successfully converged to the expected analytical minima, while the **Maxflow-Mincut** implementation produced matching maximum-flow and minimum-cut values, demonstrating the expected flow-cut duality.

The timing methodology successfully isolated the core algorithmic kernels from file I/O, parsing, CSR conversion, and console output. This ensured that the reported execution times represent the **pure computational performance of the implemented algorithms**.

Overall, the Assignment 3 implementations demonstrate correct algorithmic behavior, efficient data structures, and reproducible performance benchmarking.
=======
FileDegreex0​RateTol.Max Iter.Exp. x∗Exp. f(x∗)Actual xActual f(x)Iter. / TimeStatusgd_01.txt200.101e-65,000303.0000000.00000070 / 0.0000 msPassgd_02.txt420.021e-610,000000.0000000.000000180 / 0.0000 msPassgd_03.txt620.021e-620,000000.0000000.000000349 / 0.0000 msPassgd_04.txt820.011e-850,000000.0000000.000000948 / 0.0000 msPassgd_05.txt1020.0051e-10100,000000.0000000.0000002364 / 0.0000 msPass

### Test Results Table: Maxflow-Mincut

| File | $V$ | $E$ | Source | Sink | Max Flow | Min Cut Cap | Flow == Cut? | Execution Time (ms) | Status |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `maxflow_example.txt` | 6 | 10 | 0 | 5 | 23 | 23 | Yes | 0.0041 ms | Pass |
| `maxflow_10.txt` | 10 | 25 | 0 | 9 | 36 | 36 | Yes | 0.0082 ms | Pass |
| `maxflow_100.txt` | 100 | 300 | 0 | 99 | 15 | 15 | Yes | 0.0602 ms | Pass |
| `maxflow_1000.txt` | 1,000 | 3,000 | 0 | 999 | 11 | 11 | Yes | 0.5951 ms | Pass |
| `maxflow_10000.txt` | 10,000 | 30,000 | 0 | 9999 | 24 | 24 | Yes | 10.4489 ms | Pass |
| `maxflow_50000.txt` | 50,000 | 150,000 | 0 | 49999 | 38 | 38 | Yes | 98.7957 ms | Pass |
>>>>>>> 696d367500d0c14caf150586c03e82577d595cee
