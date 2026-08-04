
#include  <iostream>
#include   <vector>
#include   <queue>
#include  <fstream>
#include <sstream>
#include <chrono>
#include "../common/csr_graph.hpp"

using  namespace   std;

// Helper funct
int getSourceNode(string fileName) {

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

    int srcNode = getSourceNode(filePath);

    int numVertices = graph.numNodes;
    
    vector<int> dist(numVertices, -1);
    vector<int> orderVisited;

    // strt exec time
    auto tStart = chrono:: high_resolution_clock::now( );

    queue<int> bfsQueue;

    // Sourc node
    dist[srcNode] = 0;

    bfsQueue.push(srcNode);

    while (!bfsQueue.empty( ) ) {

        int currNode = bfsQueue.front( );
        bfsQueue.pop( );
        orderVisited.push_back( currNode );

        // Travers neighbr nod
        int startIdx = graph.rowPtr[currNode];

        int endIdx = graph.rowPtr[currNode + 1];

        for (int i = startIdx; i < endIdx; i++) {

            int neighbor = graph.colIndic[i];
            
            // neighbr not visit yet if
            if (dist[neighbor] == -1) {

                dist[neighbor] = dist[currNode] + 1;
                bfsQueue.push(neighbor);
            }

         }

    }


    auto tEnd = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> execTime = tEnd - tStart;

    
    cout << "Algorithm: BFS" << endl;

    cout << "Source: " << srcNode << endl;

    cout << "Traversal: ";

    for (size_t i = 0; i < orderVisited.size(); i++) {
        cout << orderVisited[i] << " ";
    }
    cout << endl;

    cout << "Distances:" << endl;

    for (int i = 0; i < numVertices; i++) {
        cout << i << " " << dist[i] << endl;
    }

    cout <<  "Execution time: "  << execTime.count( )   << " ms"  << endl;

    return 0;
}
