/*
    calcurate the flux and the cross section
    irradiating while scanning version 
*/
#include <iostream>
#include <cmath>

using namespace std;

int calcError(){
	double current,ecurrent;
	double time;
	double area;
	double ratio,eratio;
	double e;
	double bit;

	double N,eN;
	double flux,eflux;
	double fluxt,efluxt;
	double sigma,esigma;
	double finalsigma,efinalsigma;
	
  current = 1.0e-9; 
	//ecurrent = 0.01e-9;
	ecurrent = 0.;
	time = 2289;
	area = 1.9;
	ratio = 0.59;
	eratio = 0.0001;
	e = 1.6e-19;
	bit = 491520;

  //N = 18126;
  N = 15924;
	eN = sqrt(N);
	//eN = 1241+sqrt(N);
	flux = current*ratio/e/area;
	fluxt = flux*time;

	sigma = N/fluxt; 
	finalsigma = sigma/bit;

	//error
	eflux = sqrt(pow(ratio*ecurrent,2)+pow(current*eratio,2))/e/area;
	efluxt = eflux*time;
  esigma = sqrt(pow(fluxt*eN,2)+pow(N*efluxt,2))/pow(fluxt,2);
	efinalsigma = esigma/bit;

	std::cout << "flux=" << flux << std::endl;
	std::cout << "eflux=" << eflux << std::endl;
	std::cout << "fluxt=" << fluxt << std::endl;
	std::cout << "efluxt=" << efluxt << std::endl;
	std::cout << "sigma=" << sigma << std::endl;
	std::cout << "esigma=" << esigma << std::endl;
	std::cout << "finalsigma=" << finalsigma << std::endl;
	std::cout << "efinalsigma=" << efinalsigma << std::endl;

	return 0;	
}



