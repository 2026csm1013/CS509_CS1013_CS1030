#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <iomanip>
#include <chrono>
#include "../../common/csr_graph.hpp"

using namespace std;

// brandes algorithm for betweenness centrality
vector<double> calcBetweenness(const csrGraph& g) {

    int totalNodes = g.numNodes;
    vector<double> bcScores(totalNodes, 0.0);

    // bfs from each source node
    for (int src = 0; src < totalNodes; src++) {

        stack<int> vStack;
        vector<vector<int>> pList(totalNodes);
        vector<long long> pCnt(totalNodes, 0);
        vector<int> dist(totalNodes, -1);

        pCnt[src] = 1;
        dist[src] = 0;

        queue<int> q;
        q.push(src);

        while (!q.empty()) {

            int curNod = q.front();
            q.pop();
            vStack.push(curNod);

            int stIdx = g.rowPtr[curNod];
            int endIdx = g.rowPtr[curNod + 1];

            for (int i = stIdx; i < endIdx; i++) {

                int nbr = g.colIndic[i];

                if (dist[nbr] < 0) {

                    q.push(nbr);
                    dist[nbr] = dist[curNod] + 1;
                }

                if (dist[nbr] == dist[curNod] + 1) {

                    pCnt[nbr] = pCnt[nbr] + pCnt[curNod];
                    pList[nbr].push_back(curNod);
                }
            }
        }

        vector<double> dep(totalNodes, 0.0);

        // accumulation phase
        while (!vStack.empty()) {

            int w = vStack.top();
            vStack.pop();

            for (int v : pList[w]) {

                double coeff = (double)pCnt[v] / pCnt[w];
                dep[v] = dep[v] + coeff * (1.0 + dep[w]);
            }

            if (w != src) {

                bcScores[w] = bcScores[w] + dep[w];
            }
        }
    }

    // divide by 2 for undirected graph
    for (int i = 0; i < totalNodes; i++) {

        bcScores[i] = bcScores[i] / 2.0;
    }

    return bcScores;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "input file path not provided.\n";
        return 1;
    }

    string fileLoc = argv[1];

    // load graph
    csrGraph g = graphToCSR(fileLoc);

    // execution timer
    auto tStart = chrono::high_resolution_clock::now();

    vector<double> scores = calcBetweenness(g);

    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    // output results
    cout << "Algorithm: Betweenness Centrality\n";
    cout << "Vertex Centrality\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < g.numNodes; i++) {

        cout << i << " " << scores[i] << "\n";
    }

    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}