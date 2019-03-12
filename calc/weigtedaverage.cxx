/*
    calcurate the weigted average
*/

#include <iostream>
#include <cmath>

void weigtedaverage(){
    double mean[] = {1.93,1.87,1.86,2.06};
    double sigma[] = {0.13,0.12,0.12,0.13};
    //double mean[] = {1.69,1.81,1.72,1.32};
    //double sigma[] = {0.13,0.17,0.17,0.11};
    //double mean[] = {1.93,1.87,1.86,2.06,1.69,1.81,1.72,1.32};
    //double sigma[] = {0.13,0.12,0.12,0.13,0.13,0.17,0.17,0.11};
    double wden = 0.;
    double wnum = 0.;
    double wmean = 0.;
    double werror = 0.;

    int n = 4;
    //int n = 8;

    for (int i = 0; i < n; i++){
        wnum += (1/(sigma[i]*sigma[i]))*mean[i];        
        wden += 1/(sigma[i]*sigma[i]);        
    }

    std::cout << "分子= " << wnum << std::endl;
    std::cout << "分母= " << wden << std::endl;

    wmean = wnum/wden;
    std::cout << "mean= " << wmean << std::endl;

    werror = sqrt(1/wden);
    std::cout << "werror= " << werror << std::endl;

    return;
}
