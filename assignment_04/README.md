# Assignment 4: Execution and Performance Report (Buddy Tasks)

**Name:** Fardeen Khan Nabi Khan, Prashik Meshram  
**Entry Number:** 2026CSM1013, 2026CSM1030  
**GitHub Repository Link:** https://github.com/2026csm1013/CS509_CS1013_CS1030.git  

---

## 1. Introduction & Overview

This report documents the implementation, correctness validation, and benchmark profiling for **Assignment 4 (Buddy Tasks: K-Means Clustering and FastMap)**.

The algorithms evaluated in this assignment are:

1. **K-Means Clustering**
2. **FastMap**

### 1.1 K-Means Clustering

K-Means is implemented using **Lloyd's iterative clustering algorithm** to partition multidimensional data points into `K` clusters.

The implementation performs the following operations iteratively:

- Computes Euclidean distances between data points and cluster centroids.
- Assigns each point to its nearest centroid.
- Recalculates centroid positions using the mean of assigned points.
- Computes the Within-Cluster Sum of Squares (WCSS).
- Repeats the process until convergence or the maximum iteration limit is reached.

### 1.2 FastMap

FastMap is a metric multidimensional scaling algorithm used to embed high-dimensional data into a lower-dimensional Euclidean space.

The implementation:

- Selects furthest-pair pivot objects for each target dimension.
- Uses the law of cosines to calculate projected coordinates.
- Updates distances recursively after each projection.
- Produces a lower-dimensional representation while attempting to preserve the original pairwise distances.

---

### 1.3 Timing Rule Compliance

Execution time is measured using a high-resolution timer.

The timer:

- Starts immediately before the algorithm execution.
- Stops immediately after the algorithm completes.
- Includes only the computational portion of the algorithm.

The following operations are excluded from the reported execution time:

- File I/O
- String parsing
- Memory allocation
- Input preparation
- Result formatting
- Output printing

All reported execution times are given in **milliseconds (ms)**.

---

## 2. Directory Structure & Execution Setup

### 2.1 Project Layout

The project is organized as follows:

```text
CS509_CS1013_CS1030/
├── assignment_04/
│   ├── driver/
│   │   ├── kmeans_runner.exe
│   │   └── fastmap_runner.exe
│   │
│   ├── src/
│   │   ├── kmeans.cpp
│   │   ├── fastmap.cpp
│   │   └── fastmap.hpp
│   │
│   └── tests/
│       ├── km_01.txt
│       ├── km_02.txt
│       ├── km_03.txt
│       ├── km_04.txt
│       ├── fm_01.txt
│       ├── fm_02.txt
│       ├── fm_03.txt
│       └── fm_04.txt
│
└── README.md
```

### 2.2 Input Format Specifications

#### K-Means Input Format

The K-Means datasets use the following format:

```text
N D K MAX_ITER TOLERANCE

x0_0 x0_1 ... x0_(D-1)
x1_0 x1_1 ... x1_(D-1)
...
x(N-1)_0 ... x(N-1)_(D-1)
```

where:

- `N` = number of data points
- `D` = dimensionality of each data point
- `K` = number of clusters
- `MAX_ITER` = maximum number of iterations
- `TOLERANCE` = convergence tolerance

#### FastMap Input Format

The FastMap datasets use the following general format:

```text
N Target_k

[Pairwise Distance Matrix or Feature Coordinate Vectors]
```

where:

- `N` = number of objects
- `Target_k` = target embedding dimension

---

## 3. Compilation & Execution

Both programs are compiled using **GCC/G++ with C++17 and `-O3` optimization**.

### 3.1 Build Commands

Create the driver directory if required:

```bash
mkdir -p assignment_04/driver
```

#### Compile K-Means

```bash
g++ -O3 -std=c++17 assignment_04/src/kmeans.cpp -o assignment_04/driver/kmeans_runner.exe
```

#### Compile FastMap

```bash
g++ -O3 -std=c++17 assignment_04/src/fastmap.cpp -o assignment_04/driver/fastmap_runner.exe
```

### 3.2 Execution Commands

#### Run K-Means

```bash
./assignment_04/driver/kmeans_runner.exe assignment_04/tests/km_01.txt
```

#### Run FastMap

```bash
./assignment_04/driver/fastmap_runner.exe assignment_04/tests/fm_01.txt
```

The same execution commands can be used for the remaining benchmark datasets by replacing the input filename.

---

## 4. Benchmark Execution Results

### 4.1 K-Means Results Table (Section 10.3)

| **File** | **N** | **D** | **K** | **Max Iter.** | **Actual Iter.** | **WCSS** | **Time** | **Status** |
|:---|---:|---:|---:|---:|---:|---:|---:|:---:|
| `km_01.txt` | 100 | 2 | 3 | 300 | 2 | 1099.581138 | 0.0000 ms | **Pass** |
| `km_02.txt` | 1,000 | 2 | 5 | 300 | 2 | 10557.064101 | 0.0000 ms | **Pass** |
| `km_03.txt` | 10,000 | 5 | 8 | 300 | 2 | 265357.534554 | 1.0020 ms | **Pass** |
| `km_04.txt` | 100,000 | 5 | 10 | 300 | 2 | 2660665.618849 | 8.9920 ms | **Pass** |

### 4.2 FastMap Results Table (Section 10.4)

| **File** | **N** | **Target k** | **Pivots (per dim)** | **Avg. Distance Error** | **Time** | **Status** |
|:---|---:|---:|:---|---:|---:|:---:|
| `fm_01.txt` | 10 | 2 | Dim 1: (8, 2), Dim 2: (9, 1) | 0.0000 | 0.0017 ms | **Pass** |
| `fm_02.txt` | 100 | 2 | Dim 1: (11, 64), Dim 2: (13, 55) | 0.0000 | 0.0357 ms | **Pass** |
| `fm_03.txt` | 1,000 | 3 | Dim 1: (64, 717), Dim 2: (650, 183), Dim 3: (540, 14) | 0.0000 | 2.5998 ms | **Pass** |
| `fm_04.txt` | 10,000 | 3 | Dim 1: (9380, 5041), Dim 2: (3042, 8591), Dim 3: (3852, 4596) | 0.0000 | 168.4370 ms | **Pass** |

---

## 5. Performance Observations & Analysis

### 5.1 Correctness Verification

#### K-Means Convergence

Across all four K-Means datasets, the point assignments stabilized within **2 iterations**.

The algorithm therefore converged well before reaching the maximum iteration limit of `300`.

| Dataset | N | K | Actual Iterations | Status |
|:---|---:|---:|---:|:---:|
| `km_01.txt` | 100 | 3 | 2 | **Pass** |
| `km_02.txt` | 1,000 | 5 | 2 | **Pass** |
| `km_03.txt` | 10,000 | 8 | 2 | **Pass** |
| `km_04.txt` | 100,000 | 10 | 2 | **Pass** |

This indicates that the tested datasets reached stable cluster assignments quickly.

#### FastMap Metric Preservation

FastMap maintained an average distance error of **0.0000** across all four test cases.

This indicates that, for the tested datasets, the recursive projection preserved the measured inter-point distances accurately.

| Dataset | N | Target k | Avg. Distance Error | Status |
|:---|---:|---:|---:|:---:|
| `fm_01.txt` | 10 | 2 | 0.0000 | **Pass** |
| `fm_02.txt` | 100 | 2 | 0.0000 | **Pass** |
| `fm_03.txt` | 1,000 | 3 | 0.0000 | **Pass** |
| `fm_04.txt` | 10,000 | 3 | 0.0000 | **Pass** |

---

### 5.2 Scalability

#### K-Means Efficiency

K-Means execution time increases with the number of data points and dimensionality.

The largest dataset contains:

- `N = 100,000`
- `D = 5`
- `K = 10`
- Maximum iterations = `300`
- Actual iterations = `2`

Despite the large dataset size, the algorithm completed in **8.9920 ms**.

The measured execution times were:

| Dataset | N | D | K | Time |
|:---|---:|---:|---:|---:|
| `km_01.txt` | 100 | 2 | 3 | 0.0000 ms |
| `km_02.txt` | 1,000 | 2 | 5 | 0.0000 ms |
| `km_03.txt` | 10,000 | 5 | 8 | 1.0020 ms |
| `km_04.txt` | 100,000 | 5 | 10 | 8.9920 ms |

The increase in runtime is consistent with the increasing number of points, dimensions, and clusters processed during each iteration.

#### FastMap Efficiency

FastMap execution time increases significantly with the number of objects.

The measured execution times were:

| Dataset | N | Target k | Time |
|:---|---:|---:|---:|
| `fm_01.txt` | 10 | 2 | 0.0017 ms |
| `fm_02.txt` | 100 | 2 | 0.0357 ms |
| `fm_03.txt` | 1,000 | 3 | 2.5998 ms |
| `fm_04.txt` | 10,000 | 3 | 168.4370 ms |

The largest FastMap dataset contains **10,000 points** and is projected into **3 dimensions**, requiring **168.4370 ms**.

The substantial increase in execution time demonstrates the higher computational cost of FastMap as the number of objects increases.

---

## 6. Algorithmic Complexity

| Algorithm | Method | Time Complexity | Space Complexity |
|:---|:---|:---|:---|
| **K-Means** | Lloyd's Algorithm | `O(I × N × K × D)` | `O(N × D + K × D + N)` |
| **FastMap** | Pivot-Based Projection | `O(k × N²)` | `O(N² + N × k)` |

where:

- `N` = number of data points/objects
- `D` = dimensionality of the input data
- `K` = number of clusters
- `I` = number of K-Means iterations
- `k` = target FastMap embedding dimension

### 6.1 K-Means Complexity

For each iteration, K-Means calculates the distance between each data point and each centroid.

For `N` points, `K` clusters, and `D` dimensions, the distance computation requires:

```text
O(N × K × D)
```

If the algorithm performs `I` iterations, the total time complexity is:

```text
O(I × N × K × D)
```

The required storage is primarily used for the input points, centroids, cluster assignments, and auxiliary data:

```text
O(N × D + K × D + N)
```

### 6.2 FastMap Complexity

FastMap repeatedly performs pivot selection and distance calculations for each target dimension.

For `N` objects and target dimension `k`, the implementation operates over pairwise distances, giving an approximate time complexity of:

```text
O(k × N²)
```

The space complexity depends on storing the pairwise distance information and the resulting embedded coordinates:

```text
O(N² + N × k)
```

---

## 7. Conclusion

Both **K-Means Clustering** and **FastMap** successfully passed all benchmark datasets.

The main conclusions from the experiments are:

- K-Means converged within **2 iterations** for every tested dataset.
- The maximum K-Means dataset contained **100,000 points**, 5 dimensions, and 10 clusters.
- The largest K-Means execution time was **8.9920 ms**.
- FastMap produced an average distance error of **0.0000** for all tested datasets.
- The largest FastMap dataset contained **10,000 points** and was projected into **3 dimensions**.
- The largest FastMap execution time was **168.4370 ms**.
- All benchmark cases completed successfully without runtime errors or convergence failures.
- High-resolution profiling was used to measure algorithm execution independently of file I/O, parsing, allocation, and output formatting.

Overall, the benchmark results demonstrate that both algorithms were implemented successfully and performed correctly on the supplied evaluation datasets, while the timing results illustrate the different computational costs associated with iterative clustering and metric-space dimensionality reduction.