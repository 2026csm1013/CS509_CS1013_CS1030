#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>

using namespace std;

// compute squared euclidean distance
double calcSqDist(const vector<double>& p1, const vector<double>& p2, int d) {

    double distSum = 0.0;

    for (int i = 0; i < d; i++) {

        double diff = p1[i] - p2[i];
        distSum += diff * diff;
    }

    return distSum;
}


bool loadDataset(const string& filePath, int& n, int& d, int& k, vector<vector<double>>& pts, int& maxIt, double& tol) {

    ifstream fin(filePath);



    if (!fin.is_open()) {

        cerr << "file not opening " << filePath << "\n";
        return false;


    }



    if (!(fin >> n >> d >> k)) {

        cerr << "invalid dimensions\n";
        return false;
    }

    if (n <= 0 ||  d <= 0 || k <= 0 || k > n) {

        cerr << "invalid parameters N, D, or K\n";
        return false;


    }

    pts.resize(n, vector<double>(d, 0.0));

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < d; j++) {

            fin >> pts[i][j];
        }

    }

    string tag;

    while (fin >> tag) {

        if (tag == "MAX_ITERATIONS") {


            fin >> maxIt;
        } else if (tag == "TOLERANCE") {

            fin >> tol;
        }


    }

    fin.close();

    if (maxIt <= 0 || tol <= 0.0) {

        cerr << "invalid loop conditions\n";
        return false;
    }



    return true;
}


int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "file path missing\n";
        return 1;
    }


    string fileLoc = argv[1];

    int totalPts = 0;
    int numDims = 0;
    int numClust = 0;
    int maxIt = 300;
    double tol = 0.0001;

    vector<vector<double>> pts;


    if (!loadDataset(fileLoc, totalPts, numDims, numClust, pts, maxIt, tol)) {

        return 1;

    }


    vector<vector<double>> cent(numClust, vector<double>(numDims, 0.0));

    for (int i = 0; i < numClust; i++) {

        for (int j = 0; j < numDims; j++) {

            cent[i][j] = pts[i][j];


        }
    }

    vector<int> assign(totalPts, -1);
    vector<vector<double>> coordSums(numClust, vector<double>(numDims, 0.0));
    vector<int> countPts(numClust, 0);

    int iter = 0;
    bool isConv = false;

    
    auto tStart = chrono::high_resolution_clock::now();

    

    while (iter < maxIt) {

        iter++;

        // assignment step: map point to nearest centroid
        for (int i = 0; i < totalPts; i++) {

            int bestC = 0;
            double bestD = calcSqDist(pts[i], cent[0], numDims);

            for (int c = 1; c < numClust; c++) {

                double d = calcSqDist(pts[i], cent[c], numDims);

                if (d < bestD) {

                    bestD = d;
                    bestC = c;
                }


            }

            assign[i] = bestC;
        }

        
        for (int c = 0; c < numClust; c++) {

            countPts[c] = 0;

            for (int j = 0; j < numDims; j++) {

                coordSums[c][j] = 0.0;


            }
        }

       
        for (int i = 0; i < totalPts; i++) {

            int c = assign[i];
            countPts[c]++;

            for (int j = 0; j < numDims; j++) {

                coordSums[c][j] += pts[i][j];
            }
        }



        
        double maxShift = 0.0;

        for (int c = 0; c < numClust; c++) {

            if (countPts[c] > 0) {

                double shiftDistSq = 0.0;

                for (int j = 0; j < numDims; j++) {

                    double newCoord = coordSums[c][j] / countPts[c];
                    double diff = newCoord - cent[c][j];

                    shiftDistSq += diff * diff;
                    cent[c][j] = newCoord;
                }

                double shift = sqrt(shiftDistSq);

                if (shift > maxShift) {

                    maxShift = shift;
                }
            }



        }

        if (maxShift <= tol) {

            isConv = true;
            break;
        }
    }

    auto tEnd = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = tEnd - tStart;
    double totalTime = elapsed.count();


    double wcss = 0.0;

    for (int i = 0; i < totalPts; i++) {

        wcss += calcSqDist(pts[i], cent[assign[i]], numDims);
    }




    cout << "Algorithm: K-Means Clustering\n";
    cout << "K: " << numClust << "\n";
    cout << "Point assignments:\n";

    for (int i = 0; i < totalPts; i++) {

        cout << i << " " << assign[i] << "\n";
    }

    cout << "Final centroids:\n";
    cout << fixed << setprecision(6);

    for (int c = 0; c < numClust; c++) {

        cout << c << ":";

        for (int j = 0; j < numDims; j++) {

            cout << " " << cent[c][j];
        }

        cout << "\n";
    }


    cout << "WCSS: " << wcss << "\n";
    cout << "Iterations: " << iter << "\n";
    cout << "Converged: " << (isConv ? "true" : "false") << "\n";
    cout << fixed << setprecision(4);
    cout << "Execution time: " << totalTime << " ms\n";

    return 0;

    
}