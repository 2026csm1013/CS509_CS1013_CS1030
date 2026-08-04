#pragma once

#include <iostream>
#include  <vector>
#include  <fstream>
#include  <sstream>
#include  <string>

using  namespace  std;

// Struct 
struct csrGraph {
    int numNodes = 0;
    int numEdges  = 0;


    vector<int>  rowPtr;   
    vector<int> colIndic; 
    vector<int>  valList;  
};

// Preprocessing Wrapper 
inline csrGraph graphToCSR(const string & inputFile) {

    ifstream file(inputFile);

    if ( !file.is_open( ) ) {
        cerr << " not open  file " << inputFile << endl;

        exit(1);
    }

    int n, m;

    if (!(file >> n >> m)) {

        cerr << " dimensions of graph is not valid" << inputFile << endl;

        exit(1);
    }


    csrGraph graph;
    graph.numNodes = n;
    graph.numEdges = m;
    graph.rowPtr.resize(n + 1, 0);


    // Temp storg for adjacency list
    vector <vector<pair<int, int>>> adj(n);
    string  line;
    getline(file, line); 


    int count = 0;
    while (count < n && getline(file, line)) {

        if (line.empty()){

         continue;
    }

        stringstream ss(line);
        int srcNode, deg;
        if (!(ss >> srcNode >> deg)) {

        continue;
    }

        for (int i = 0; i < deg; i++) {

            int destNode;
            int wt = 1;

            if (!(ss >> destNode)) {

            break;
            }

            // Dynamically handle unweighted 
            if (ss >> wt) {

                adj[srcNode].push_back({destNode, wt});
            } else {

                ss.clear();
                // Default weight = 1
                adj[srcNode].push_back({destNode, 1}); 
            }
        }
        count++;
    }

    file.close();

    //  Adj to 3 CSR arrays
    int totalEdges = 0;
    for (int i = 0; i < n; i++) {
        graph.rowPtr[i] = totalEdges;
        
        for (auto& edge : adj[i]) {

            graph.colIndic.push_back(edge.first);
            graph.valList.push_back(edge.second);
            totalEdges++;
        }
    }

    
    graph.rowPtr[n] = totalEdges;

    return graph;
}