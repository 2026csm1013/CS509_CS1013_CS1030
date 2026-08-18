#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;


// evaluate fx with horner
double evalPoly( const vector<double>& coeff, int degVal, double curX )  {

    double res = coeff[degVal];

    for (int i = degVal - 1; i >= 0; i--)  {


        res = res * curX + coeff[i];
    }


    return res;

}



// compute derivative fx
double evalDeriv( const vector<double>& coeff, int degVal, double curX )   {


    double gradVal = 0.0;
    double pwr = 1.0;

    for ( int i = 1; i <= degVal; i++)  {


        gradVal = gradVal + (double)i * coeff[i] * pwr;
        pwr = pwr * curX;

    }


    return gradVal;

}



int main( int argc, char* argv[])  {


    if ( argc < 2) {


        cerr << "file path missing\n";
        return 1;
    }


    string fileLoc = argv[1];
    ifstream fin(fileLoc);

    if ( !fin.is_open())  {


        cerr << "cant open file: " << fileLoc << "\n";
        return 1;


    }


    int degVal = 0;
    vector<double> coeff;
    double initX = 0.0;
    double lRate  = 0.0;
    double tolVal = 0.0;
    int maxIter  = 0;


    string tag;


    while ( fin >> tag)   {

        if ( tag == "DEGREE")  {


            fin >> degVal;


        } 
        
        else if (tag == "COEFFICIENTS") {

            coeff.resize(degVal + 1, 0.0);

            for (int i = 0; i <= degVal; i++) {

                fin >> coeff[i];
            }

        } 
        
        else if (tag == "INITIAL_X") {

            fin >> initX;
        }
        
        else if (tag == "LEARNING_RATE") {

            fin >> lRate;
        } 
        
        else if (tag == "TOLERANCE") {

            fin >> tolVal;
        } 
        
        else if (tag == "MAX_ITERATIONS") {

            fin >> maxIter;
        }

    }


    fin.close();

    // input validation
    if ( degVal <= 0 || (int)coeff.size() != degVal + 1 || lRate <= 0 || tolVal <= 0 || maxIter <= 0 ) 
    {

        cerr << "invalid gradient descent parameters\n";
        return 1;

    }

    // start timer
    auto tStart = chrono::high_resolution_clock::now();


    double curX = initX;
    int iterCnt = 0;
    bool isConv = false;


    // gd loop
    while ( iterCnt < maxIter )  {



        double dVal = evalDeriv(coeff, degVal, curX);

        if ( fabs(dVal) <= tolVal )  {


            isConv = true;
            break;

        }


        curX = curX - lRate * dVal;
        iterCnt++;

    }

    // final grad check
    if (!isConv )  {


        double finalD = evalDeriv(coeff, degVal, curX);

        if (fabs(finalD) <= tolVal )  {


            isConv = true;
        }

    }



    double finalFx = evalPoly( coeff, degVal, curX);

    auto tEnd = chrono::high_resolution_clock::now();


    chrono::duration<double, milli> elapsed = tEnd - tStart;
    double totalTime = elapsed.count();

    // print outp
    cout << "Algorithm: Gradient Descent\n";
    cout << "Degree: " << degVal << "\n";
    cout << fixed << setprecision(6);
    cout << "Final x: " << curX << "\n";
    cout << "Final f(x): " << finalFx << "\n";
    cout << "Iterations: " << iterCnt << "\n";
    cout << "Converged: " << (isConv ? "true" : "false") << "\n";
    cout << setprecision(4);
    cout << "Execution time: " << totalTime << " ms\n";

    

    return 0;
}