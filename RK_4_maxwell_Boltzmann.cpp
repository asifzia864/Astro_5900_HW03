#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>


const double m = 1.6726219e-27;  // mass 
const double k = 1.380649e-23; // Boltzmann constant 
const double T = 10000.0;        // Temperature 
const double PI = std::acos(-1.0);

double fv(double v, double P) {
    double term1 = std::pow(m / (2.0 * PI * k * T), 1.5);
    double term2 = 4.0 * PI * std::pow(v, 2);
    double exponent = std::exp(-(m * std::pow(v, 2)) / (2.0 * k * T));
    return term1 * term2 * exponent;
}

int main() {
    //  v_min for 1 to 2 transition 
    double delta_E = 10.2 * 1.60218e-19; 
    double v_min = std::sqrt(2.0 * delta_E / m);
    
    // integration limits
    double v_max = 60000.0; 
    int v_steps = 1000;      
    double dv = (v_max - v_min) / double(v_steps);

    double v = v_min;
    double f = 0.0; // at exactly v_min there is no transition 
    
    std::ofstream outFile("fraction_output.csv");
    outFile << "v,P\n";

    for (int i = 0; i < v_steps; i++) {
        outFile << std::fixed << std::setprecision(10) << v << "," << f << "\n";

        double k1 = fv(v, f);
        double k2 = fv(v + dv / 2.0, f + (dv / 2.0) * k1);
        double k3 = fv(v + dv / 2.0, f + (dv / 2.0) * k2);
        double k4 = fv(v + dv, f + dv * k3);

        f = f + (dv / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        v = v + dv;
    }

    outFile << v << "," << f << "\n";
    outFile.close();

    std::cout << "v_min: " << v_min << std::endl;
    std::cout << "Final Fraction: " << f << std::endl;

    return 0;
}