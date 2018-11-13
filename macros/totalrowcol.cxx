/*
   totalrowcol.C

   read summary file (summary*.txt) and just make graph of primary function
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

int totalrowcol(/*const string& inputFile*/){
    std::cout << "#-----start totalrowcol.cxx-----" << std::endl;

    //set open file
    //TString ifn = inputFile;
    TString ifn = "/home/pixeldaq/YARR_rd53a/cyric/macros/sumcol.txt" ;
    ifstream fin;
    std::string str;

    //open files
    fin.open(ifn);
    if(fin.fail()){
	cerr << "#cannot open file1 : " << ifn << std::endl;
	return 1;
    }

    std::cout << "#finished opening files" << std::endl;

    //define histogram
    TH2F* h2 = new TH2F("h2","flipped row/col in each readout_cycle",142,0,142,400,0,400);

    //read file
    char a[10000] = {};
    int b;
    int c;
    int count = 1;
    while(getline(fin,str))
    {
	if(str[0] == '#') continue;
	if(str[0] == 't') {
	    b = 0;
	    sscanf(str.data(),"%s %d",a,&b);
	    ++count;
	}else{
	    c = 0;
	    sscanf(str.data(),"%d",&c);
            //cout << "c= " << c << endl;
	    //++bcount;
	}
            //cout << "c= " << c << endl;
            //cout << "count=" << count << endl;
            h2->Fill(count,c);
    }

    //std::cout << "#count=" << count << std::endl;

    //set root file for output
    //string foutname = "outputPR.root";
    //TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");


    //draw 2Dhistogram
    //TCanvas *c1 = new TCanvas("c", "c",1000,1000);
    h2->SetTitle("SEU test;Readout Cycle;number of flip bit");
    h2->Draw("colz");

    //fout->Write();
    //fout->Close();

    fin.close();

    return 0;
    std::cout << "#-----finished totalrowcol.cxx-----" << std::endl;

}


