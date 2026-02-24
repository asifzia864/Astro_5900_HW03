# include <iostream>
# include <vector>
# include <cmath>
# include <complex>
# include <fstream>
# include <iomanip>
using namespace std;
int main(){
    int x_min = 0;
    int x_max = 1;
    int Nx = 256;
    double dx = (x_max - x_min)/double(Nx);

    std::vector<double> x(Nx);
    for (int i = 0; i <Nx; i++){
        x[i] = x_min + i*dx;
    }
    std::vector<double> y(Nx);
    for (int i = 0; i < Nx; i++){
        
    }

    return 0;
}