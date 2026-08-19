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