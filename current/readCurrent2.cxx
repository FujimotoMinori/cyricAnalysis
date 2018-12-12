/*
   readCurrent2.C
   get the top of beam current
 */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TString.h>
void readCurrent2(){
    std::cout << "#-----start readCurrent2.cxx-----" << std::endl;

    TH1F *h1 = new TH1F("h1","h1",100,-2.0e-9,2.0e-9);
    TH1F *h2 = new TH1F("h2","Dump current",50,0.,2.0e-9);

    //read data
    ifstream ifs("/Users/fujimoto/Desktop/DumpCurrent_CYRIC_20181127-29/cyric1129_1.dat");
    std::cout << "set data" << std::endl;
    int i = 0;
    double val[1000000] = {};
    while(!ifs.eof()){
        Double_t xx;
        ifs >> xx ;
        i++;
        val[i] = xx;
        if(i>22578&&i<23171){
            h1->Fill(xx);
        }
    }
    std::cout << "i= " << i << std::endl;
    ifs.close();
    std::cout << "#finished reading files" << std::endl;

    //get the max value max[k] in 0.5 scan
    double max[10000] = {};
    int k = 0;
    for(int j=22578;j<=23171;j++){
        if(j%56 == 22578%56) {
            k++;
            max[k] = 0.;
        }
        if(val[j]>max[k]) max[k] = val[j];
    }

    std::cout << "number of peak= " << k << std::endl;

    //get the mean of the max value
    double tmax;
    double mean;
    for(int m = 1;m<=k;m++){
        tmax += max[m];
    }
    mean = tmax/k;
    std::cout << "mean= " << mean << std::endl;

    //modify the value to 1nA?
    for(int l=1;l<=k;l++) {
        std::cout << "newval= " << (max[l]/mean)*1.0e-9 << std::endl;
        h2->Fill(max[l]);
        //h2->Fill((max[l]/mean)*1.0e-9);
    }

    //fit histogram
    TF1 *f1 = new TF1("func","gaus",0.9e-9,1.8e-9);
    f1->SetParameter(0,6);
    f1->SetParameter(1,1.2e-9);
    f1->SetParameter(2,0.1e-9);
    h1->Fit("func","l","",0.9e-9,1.8e-9);

    TCanvas* c1 = new TCanvas("c1");
    h1->Draw();
    TCanvas* c2 = new TCanvas("c2");
    h2->Draw();

    return;
    std::cout << "#-----finished readCurrent2.cxx-----" << std::endl;

    }


