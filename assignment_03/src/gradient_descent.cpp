#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;

// evaluate f(x) = c0 + c1*x + c2*x^2 + ... using direct horner method
double evalPoly(const vector<double>& coeff, int degVal, double curX) {

    double res = coeff[degVal];

    for (int i = degVal - 1; i >= 0; i--) {

        res = res * curX + coeff[i];
    }

    return res;
}
