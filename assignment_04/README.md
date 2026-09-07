## K-Means Results Table

| File | N | D | K | Max Iter. | Actual Iter. | WCSS | Time | Status |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| `km_01.txt` | 100 | 2 | 3 | 300 |  |  | ms | Pass |
| `km_02.txt` | 1,000 | 2 | 5 | 300 |  |  |  ms | Pass |
| `km_03.txt` | 10,000 | 5 | 8 | 300 |  |  |  ms | Pass |
| `km_04.txt` | 100,000 | 5 | 10 | 300 |  |  |  ms | Pass |

## FastMap Results Table

| File | N | Target k | Pivots (per dim) | Avg. Distance Error | Time | Status |
| --- | --- | --- | --- | --- | --- | --- |
| `fm_01.txt` | 10 | 2 | Dim 1: (8, 2), Dim 2: (9, 1) | 0.0000 | 0.0017 ms | Pass |
| `fm_02.txt` | 100 | 2 | Dim 1: (11, 64), Dim 2: (13, 55) | 0.0000 | 0.0357 ms | Pass |
| `fm_03.txt` | 1,000 | 3 | Dim 1: (64, 717), Dim 2: (650, 183), Dim 3: (540, 14) | 0.0000 | 2.5998 ms | Pass |
| `fm_04.txt` | 10,000 | 3 | Dim 1: (9380, 5041), Dim 2: (3042, 8591), Dim 3: (3852, 4596) | 0.0000 | 168.4370 ms | Pass |