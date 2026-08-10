#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../../common/csr_graph.hpp"

using namespace std;

// struct for storing triangle vertices
struct Triangle {

    int u, v, w;
};

// function to count triangles in csr graph
long long countTriangles(const csrGraph& g, vector<Triangle>& smallTris) {

    int totalNodes = g.numNodes;
    long long triCnt = 0;

    // iterate through all vertices
    for (int u = 0; u < totalNodes; u++) {

        int stIdx = g.rowPtr[u];
        int endIdx = g.rowPtr[u + 1];

        // pick neighbor v > u
        for (int i = stIdx; i < endIdx; i++) {

            int v = g.colIndic[i];

            if (v <= u) continue;

            // pick neighbor w > v
            for (int j = i + 1; j < endIdx; j++) {

                int w = g.colIndic[j];

                if (w <= v) continue;

                // check if edge (v, w) exists
                int vSt = g.rowPtr[v];
                int vEnd = g.rowPtr[v + 1];

                bool foundEdge = false;

                for (int k = vSt; k < vEnd; k++) {

                    if (g.colIndic[k] == w) {

                        foundEdge = true;
                        break;
                    }
                }

                if (foundEdge) {

                    triCnt++;

                    // record triplet for small graphs
                    if (totalNodes <= 100) {

                        smallTris.push_back({u, v, w});
                    }
                }
            }
        }
    }

    return triCnt;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "input file path not provided.\n";
        return 1;
    }

    string fileLoc = argv[1];

    // load csr graph
    csrGraph g = graphToCSR(fileLoc);

    // check negative weights
    for (int w : g.valList) {

        if (w < 0) {

            cerr << "negative edge weight found\n";
            return 1;
        }
    }

    vector<Triangle> smallTris;

    // execution timer
    auto tStart = chrono::high_resolution_clock::now();

    long long ans = countTriangles(g, smallTris);

    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    // print output results
    cout << "Algorithm: Triangle Counting\n";
    cout << "Total triangles: " << ans << "\n";

    if (g.numNodes <= 100 && !smallTris.empty()) {

        cout << "Triangles found:\n";

        for (int i = 0; i < smallTris.size(); i++) {

            cout << "(" << smallTris[i].u << ", " << smallTris[i].v << ", " << smallTris[i].w << ")\n";
        }
    }

    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}