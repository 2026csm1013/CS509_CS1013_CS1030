#include  <iostream>
#include   <vector>
#include   <stack>
#include  <fstream>
#include <sstream>
#include <chrono>
#include "../common/csr_graph.hpp"

using namespace  std;

// Helper funct
int getSNode(string fileName) {

    ifstream file(fileName);

    if (!file.is_open( )){

    return 0; 
   }

    string line;

    while ( getline(file,  line)  ) {

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
    
    vector<bool> visted(numVt, false);
    vector<int> ordrvisted;

    // strt  exec  time
    auto tStart  = chrono:: high_resolution_clock::now(  );

    stack<int> dfsStack;

    // Sourc node
    dfsStack.push(srcNode);

    while (!dfsStack.empty( ) ) {

        int currNode = dfsStack.top( );
        dfsStack.pop( );

        if (!visted[currNode]) {

            visted[currNode] = true;
            ordrvisted.push_back( currNode  );

            // Travers neighbr nod
            int startIdx = graph.rowPtr[currNode];

            int endIdx = graph.rowPtr[currNode + 1];

            for (int i = endIdx - 1; i >= startIdx; i--) {

                int neigbr = graph.colIndic[i];

                if (!visted[neigbr]) {
                    dfsStack.push(neigbr);
                }
            }

        }

    }


    auto tEnd =  chrono::high_resolution_clock::now( );

    chrono::duration<double, milli> execTime = tEnd - tStart;

    
    cout << "Algorithm: DFS" << endl;

    cout << "Source: " << srcNode << endl;

    cout << "Traversal: ";

    int limit = min((int)ordrvisted.size(), 20);

    for (int i = 0; i < limit; i++) {
        cout << ordrvisted[i] << " ";
    }
    if (ordrvisted.size() > 20) {
        cout << "...";
    }
    cout << endl;

    cout <<  "Execution time: "  << execTime.count( )   << " ms"  << endl;

    return 0;
}
