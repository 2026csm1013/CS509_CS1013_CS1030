
#include  <iostream>
#include   <vector>
#include   <queue>
#include  <fstream>
#include <sstream>
#include <chrono>
#include "../common/csr_graph.hpp"

using  namespace   std;

// Helper funct
int getSNode(string fileName) {

    ifstream file(fileName);

    if (!file.is_open()) return 0; 

    string line;
    while (getline(file, line)) {

        stringstream ss(line);
        string tag;
        ss >> tag;
        
        if (tag == "SOURCE") {

            int src;
            ss >> src;
            return src;
        }
    }

    return 0; 
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "give input path." << endl;
        return 1;
    }

    string filePath = argv[1];

    // Load graph struct in csr format

   csrGraph graph = graphToCSR(filePath);

    int srcNode = getSNode(filePath);

    int numVt = graph.numNodes;
    
    vector<int> dist(numVt, -1);
    vector<int> ordrvisted;

    // strt exec time
    auto tStart = chrono:: high_resolution_clock::now( );

    queue<int> bfsQueue;

    // Sourc node
    dist[srcNode] = 0;

    bfsQueue.push(srcNode);

    while (!bfsQueue.empty( ) ) {

        int currNode = bfsQueue.front( );
        bfsQueue.pop( );
        ordrvisted.push_back( currNode );

        // Travers neighbr nod
        int startIdx = graph.rowPtr[currNode];

        int endIdx = graph.rowPtr[currNode + 1];

        for (int i = startIdx; i < endIdx; i++) {

            int neigbr = graph.colIndic[i];
            
            // neighbr not visit yet if
            if (dist[neigbr] == -1) {

                dist[neigbr] = dist[currNode] + 1;
                bfsQueue.push(neigbr);
            }

         }

    }


    auto tEnd = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> execTime = tEnd - tStart;

    
    cout << "Algorithm: BFS" << endl;

    cout << "Source: " << srcNode << endl;

    cout << "Traversal: ";

    for (size_t i = 0; i < ordrvisted.size(); i++) {
        cout << ordrvisted[i] << " ";
    }
    cout << endl;

    cout << "Distances:" << endl;

    for (int i = 0; i < numVt; i++) {
        cout << i << " " << dist[i] << endl;
    }

    cout <<  "Execution time: "  << execTime.count( )   << " ms"  << endl;

    return 0;
}
