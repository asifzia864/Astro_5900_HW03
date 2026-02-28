#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

double f(double x, double y) {
    return y * y + 1.0;
}
// Euler solver
double solve_euler(int Nx, double x_start, double x_target, double y_start) {
    double dx = (x_target - x_start) / double(Nx);
    double x_curr = x_start;
    double y_curr = y_start;

    for (int i = 0; i < Nx; i++) {
        y_curr += dx * f(x_curr, y_curr);
        x_curr += dx;
    }
    return y_curr;
}

int main() {
    const double x_target = 1.0, x_start = 0.0, y_start = 0.0;
    const double y_best = 1.5574077247; 
    
    std::vector<int> grid_points = {8, 16, 32, 64, 128, 256, 512, 1024}; //Testing diff grid points
    
    std::ofstream outFile("euler_convergence.csv");
    outFile << "Nx,dx,y_val,frac_diff\n";

    for (int Nx : grid_points) {
        double dx = (x_target - x_start) / (double)Nx;
        double y_val = solve_euler(Nx, x_start, x_target, y_start);
        double frac_diff = std::abs(y_val - y_best) / y_best;

        outFile << Nx << "," << dx << "," << std::fixed << std::setprecision(10) 
                << y_val << "," << std::scientific << frac_diff << "\n";
    }

    outFile.close();

    return 0;
}