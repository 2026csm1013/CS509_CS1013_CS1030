#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;

const long long INF_VAL = 1e15;

// flow edge struct
struct FlowEdg {

    int toNod;
    long long cap;
    long long flw;
    int revIdx;
};

// cut edge struct
struct CutEdg {

    int u;
    int v;
    long long wt;
};

// add fwd and rev edges
void addFlowEdge(int u, int v, long long cap, vector<FlowEdg>& edgPool, vector<vector<int>>& net) {

    int fwdId = edgPool.size();
    int revId = fwdId + 1;

    edgPool.push_back({v, cap, 0, revId});
    net[u].push_back(fwdId);

    edgPool.push_back({u, 0, 0, fwdId});
    net[v].push_back(revId);
}

// bfs for level graph
bool buildLevel(int src, int snk, int numNod, const vector<FlowEdg>& edgPool, 
                const vector<vector<int>>& net, vector<int>& lvlArr) {

    fill(lvlArr.begin(), lvlArr.end(), -1);
    lvlArr[src] = 0;

    queue<int> q;
    q.push(src);

    while (!q.empty()) {

        int u = q.front();
        q.pop();

        for (int i = 0; i < net[u].size(); i++) {

            int eIdx = net[u][i];
            int v = edgPool[eIdx].toNod;

            if (edgPool[eIdx].cap - edgPool[eIdx].flw > 0 && lvlArr[v] == -1) {

                lvlArr[v] = lvlArr[u] + 1;
                q.push(v);
            }
        }
    }

    return lvlArr[snk] != -1;
}

// dfs to push flow
long long sendFlow(int u, int snk, long long pushAmt, vector<FlowEdg>& edgPool, 
                   const vector<vector<int>>& net, const vector<int>& lvlArr, vector<int>& ptrArr) {

    if (pushAmt == 0 || u == snk) {

        return pushAmt;
    }

    for (int& cid = ptrArr[u]; cid < net[u].size(); cid++) {

        int eIdx = net[u][cid];
        int v = edgPool[eIdx].toNod;

        if (lvlArr[u] + 1 != lvlArr[v] || edgPool[eIdx].cap - edgPool[eIdx].flw <= 0) {

            continue;
        }

        long long avail = edgPool[eIdx].cap - edgPool[eIdx].flw;
        long long tr = sendFlow(v, snk, min(pushAmt, avail), edgPool, net, lvlArr, ptrArr);

        if (tr == 0) {

            continue;
        }

        edgPool[eIdx].flw += tr;
        edgPool[edgPool[eIdx].revIdx].flw -= tr;

        return tr;
    }

    return 0;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "file path missing\n";
        return 1;
    }

    string fileLoc = argv[1];
    ifstream fin(fileLoc);

    if (!fin.is_open()) {

        cerr << "cant open file: " << fileLoc << "\n";
        return 1;
    }

    int numNod, numEdg;

    if (!(fin >> numNod >> numEdg)) {

        cerr << "invalid input format\n";
        return 1;
    }

    // read adj list
    vector<vector<pair<int, long long>>> adjList(numNod);

    for (int i = 0; i < numNod; i++) {

        int u, deg;
        fin >> u >> deg;

        for (int j = 0; j < deg; j++) {

            int v;
            long long cap;
            fin >> v >> cap;
            adjList[u].push_back({v, cap});
        }
    }

    int srcNod = 0;
    int snkNod = numNod - 1;
    string tag;

    while (fin >> tag) {

        if (tag == "SOURCE") {

            fin >> srcNod;
        } else if (tag == "SINK") {

            fin >> snkNod;
        }
    }

    fin.close();

    // check src and sink
    if (srcNod < 0 || srcNod >= numNod || snkNod < 0 || snkNod >= numNod || srcNod == snkNod) {

        cerr << "invalid source or sink\n";
        return 1;
    }

    // convert to csr
    vector<int> rowPtr(numNod + 1, 0);
    vector<int> colIndic;
    vector<long long> valList;

    for (int i = 0; i < numNod; i++) {

        rowPtr[i] = colIndic.size();

        for (int j = 0; j < adjList[i].size(); j++) {

            colIndic.push_back(adjList[i][j].first);
            valList.push_back(adjList[i][j].second);
        }
    }

    rowPtr[numNod] = colIndic.size();

    // start timer
    auto tStart = chrono::high_resolution_clock::now();

    // make dinic graph from csr
    vector<FlowEdg> edgPool;
    vector<vector<int>> net(numNod);
    vector<int> lvlArr(numNod);
    vector<int> ptrArr(numNod);

    for (int u = 0; u < numNod; u++) {

        for (int idx = rowPtr[u]; idx < rowPtr[u + 1]; idx++) {

            int v = colIndic[idx];
            long long cap = valList[idx];
            addFlowEdge(u, v, cap, edgPool, net);
        }
    }

    // dinic loop
    long long maxFlw = 0;

    while (buildLevel(srcNod, snkNod, numNod, edgPool, net, lvlArr)) {

        fill(ptrArr.begin(), ptrArr.end(), 0);

        while (long long pushed = sendFlow(srcNod, snkNod, INF_VAL, edgPool, net, lvlArr, ptrArr)) {

            maxFlw += pushed;
        }
    }

    // find reachable nodes for mincut
    vector<bool> vis(numNod, false);
    queue<int> q;

    q.push(srcNod);
    vis[srcNod] = true;

    while (!q.empty()) {

        int u = q.front();
        q.pop();

        for (int i = 0; i < net[u].size(); i++) {

            int eIdx = net[u][i];
            int v = edgPool[eIdx].toNod;

            if (edgPool[eIdx].cap - edgPool[eIdx].flw > 0 && !vis[v]) {

                vis[v] = true;
                q.push(v);
            }
        }
    }

    // get cut edges
    long long cutCap = 0;
    vector<CutEdg> cutEdges;

    for (int u = 0; u < numNod; u++) {

        if (vis[u]) {

            for (int idx = rowPtr[u]; idx < rowPtr[u + 1]; idx++) {

                int v = colIndic[idx];
                long long c = valList[idx];

                if (!vis[v]) {

                    cutCap += c;
                    cutEdges.push_back({u, v, c});
                }
            }
        }
    }

    auto tEnd = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = tEnd - tStart;
    double totalTime = elapsed.count();

    // print output
    cout << "Algorithm: Maxflow-Mincut\n";
    cout << "Source: " << srcNod << "\n";
    cout << "Sink: " << snkNod << "\n";
    cout << "Maximum flow: " << maxFlw << "\n";
    cout << "Minimum cut capacity: " << cutCap << "\n";

    // print partition for small graphs
    if (numNod <= 100) {

        cout << "Source side: ";
        for (int i = 0; i < numNod; i++) {

            if (vis[i]) {

                cout << i << " ";
            }
        }
        cout << "\n";

        cout << "Sink side: ";
        for (int i = 0; i < numNod; i++) {

            if (!vis[i]) {

                cout << i << " ";
            }
        }
        cout << "\n";

        cout << "Cut edges:\n";
        for (int i = 0; i < cutEdges.size(); i++) {

            cout << cutEdges[i].u << " " << cutEdges[i].v << " " << cutEdges[i].wt << "\n";
        }
    }

    cout << fixed << setprecision(4);
    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}