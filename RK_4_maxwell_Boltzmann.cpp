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
    
    // Convergence check for different number of steps
    std::ofstream stepFile("MB_convergence_by_steps.csv");
    stepFile << "v_steps,Final_Fraction\n";

    double fixed_v_max = 100000.0;
    std::vector<int> step_counts = {10,15,17,20,23,25,28,30,32,35,40,45,50,70,100,140,180,250,300,350,400};

    for (int steps : step_counts) {
        double v = v_min;
        double f = 0.0;
        double dv = (fixed_v_max - v_min) / double(steps);

        for (int i = 0; i < steps; i++) {
            double k1 = fv(v, f);
            double k2 = fv(v + dv / 2.0, f + (dv / 2.0) * k1);
            double k3 = fv(v + dv / 2.0, f + (dv / 2.0) * k2);
            double k4 = fv(v + dv, f + dv * k3);
            f += (dv / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
            v += dv;
        }
        stepFile << steps << "," << std::scientific << f << "\n";
    }
    stepFile.close();

    // Fixed step size, changing v_max.
    std::ofstream rangeFile("MB_convergence_by_vmax.csv");
    rangeFile << "v_max,Final_Fraction\n";

    int fixed_steps = 1000;
    for (double current_v_max = 50000.0; current_v_max <= 100000.0; current_v_max += 1000.0) {
        double v = v_min;
        double f = 0.0;
        double dv = (current_v_max - v_min) / double(fixed_steps);

        for (int i = 0; i < fixed_steps; i++) {
            double k1 = fv(v, f);
            double k2 = fv(v + dv / 2.0, f + (dv / 2.0) * k1);
            double k3 = fv(v + dv / 2.0, f + (dv / 2.0) * k2);
            double k4 = fv(v + dv, f + dv * k3);
            f += (dv / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
            v += dv;
        }
        rangeFile << std::fixed << current_v_max << "," << std::scientific << f << "\n";
    }
    rangeFile.close();

    std::cout << "Simulation Complete" << std::endl;

    return 0;
}