/*
    calcurate the mean and error with errors in each run
*/

#include <iostream>
#include <cmath>

void weigtedaverage(){
    double meanscan[] = {1.93,1.87,1.86,2.06};
    double sigmascan[] = {0.13,0.12,0.12,0.13};
    double meanpoint[] = {1.69,1.81,1.72,1.32};
    double sigmapoint[] = {0.13,0.17,0.17,0.11};
    //double meanall[] = {1.93,1.87,1.86,2.06,1.69,1.81,1.72,1.32};
    //double sigmaall[] = {0.13,0.12,0.12,0.13,0.13,0.17,0.17,0.11};
    double wden = 0.;
    double wnum = 0.;

    double wmean = 0.;
    double werror = 0.;

    double mean = 0.;
    double error = 0.;

    int n = 4;
    //int n = 8;

    for (int i = 0; i < n; i++){
        wnum += (1/(sigma[i]*sigma[i]))*mean[i];        
        wden += 1/(sigma[i]*sigma[i]);        
    }

    std::cout << "分子= " << wnum << std::endl;
    std::cout << "分母= " << wden << std::endl;

    wmean = wnum/wden;
    std::cout << "weightedmean= " << wmean << std::endl;

    werror = sqrt(1/wden);
    std::cout << "weightederror= " << werror << std::endl;

     


    return;
}

