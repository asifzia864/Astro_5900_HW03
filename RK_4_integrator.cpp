#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>

double f(double x, double y) {
    return y * y + 1.0; 
}
// RK4 solver
double solve_rk4(int Nx, double x_start, double x_target, double y_start) {
    double dx = (x_target - x_start) / double(Nx);
    double x_curr = x_start;
    double y_curr = y_start;

    for (int i = 0; i < Nx; i++) {
        double k1 = f(x_curr, y_curr);
        double k2 = f(x_curr + dx / 2.0, y_curr + (dx / 2.0) * k1);
        double k3 = f(x_curr + dx / 2.0, y_curr + (dx / 2.0) * k2);
        double k4 = f(x_curr + dx, y_curr + dx * k3);
        y_curr += (dx / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);
        x_curr += dx;
    }
    return y_curr;
}

int main() {
    const double x_target = 1.0, x_start = 0.0, y_start = 0.0;
    std::vector<int> grid_points = {8, 16, 32, 64, 128, 256, 512, 1024};
    
    // Best value from 1024 grid points
    double y_best = 1.5574077247; 

    std::ofstream outFile("rk4_convergence.csv");
    outFile << "Nx,dx,y_val,frac_diff\n";

    for (int Nx : grid_points) {
        double dx = (x_target - x_start) / (double)Nx;
        double y_val = solve_rk4(Nx, x_start, x_target, y_start);
        double frac_diff = std::abs(y_val - y_best) / y_best;

        outFile << Nx << "," << dx << "," << std::fixed << std::setprecision(10) 
                << y_val << "," << std::scientific << frac_diff << "\n";
    }

    outFile.close();
    return 0;
}