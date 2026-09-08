//g++ -O3 assignment_04\src\kmeans.cpp -o assignment_04\driver\kmeans_runner.exe
//
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;


void makeKMeansFile(const string& filePath, int n, int d, int k, int maxIt, double tol) {

    ofstream fout(filePath);

    if (!fout.is_open()) {

        cerr << "cannot create file: " << filePath << "\n";
        return;
    }

    // header: N D K
    fout << n << " " << d << " " << k << "\n";

    fout << fixed << setprecision(4);

    // generate points grouped around distinct cluster centers
    for (int i = 0; i < n; i++) {

        int clusterId = i % k;

        for (int j = 0; j < d; j++) {

            
            double baseVal = clusterId * 25.0;
            double offset = (rand() % 800) / 100.0;
            double coord = baseVal + offset;

            fout << coord;

            if (j + 1 < d) {

                fout << " ";
            }
        }

        fout << "\n";
    }

    // parameters
    fout << "MAX_ITERATIONS " << maxIt << "\n";
    fout << "TOLERANCE " << tol << "\n";

    fout.close();
    cout << "created " << filePath << " (N=" << n << ", D=" << d << ", K=" << k << ")\n";
}

int main() {

    srand(42);

   
    makeKMeansFile("assignment_04/tests/km_01.txt", 100, 2, 3, 300, 0.0001);
    makeKMeansFile("assignment_04/tests/km_02.txt", 1000, 2, 5, 300, 0.0001);
    makeKMeansFile("assignment_04/tests/km_03.txt", 10000, 5, 8, 300, 0.0001);
    makeKMeansFile("assignment_04/tests/km_04.txt", 100000, 5, 10, 300, 0.0001);

    return 0;
}