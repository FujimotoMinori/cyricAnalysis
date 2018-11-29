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
    TString ifn = "/Users/fujimoto/cyric11/cyricData/sumplace_run00046.txt" ;
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
    TH2F* h2 = new TH2F("h2","flipped row/col in each readout_cycle",400,0,400,192,0,192);

    //read file
    char a[10000] = {};
    int b,c,d;
    int count = 1;
    while(getline(fin,str))
    {
	if(str[0] == '#') continue;
	if(str[0] == 't') {
	    b = 0;
	    sscanf(str.data(),"%s %d",a,&b);
            //std::cout << "total = " << b << std::endl;
	    ++count;
	    //std::cout << "count = " << count << std::endl;
	}else{
	    c = 0;
	    sscanf(str.data(),"%d %d",&c,&d);
	}
	if(b!=76800) {
        //std::cout << "total = " << b << std::endl;
	    //std::cout << "count = " << count << std::endl;
	    h2->Fill(c,d);
	}
    }

    //set root file for output
    //string foutname = "outputPR.root";
    //TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

    //draw 2Dhistogram
    //TCanvas *c1 = new TCanvas("c", "c",1000,1000);
    h2->SetTitle("SEU test;col;row");
    h2->SetStats(0);
    h2->Draw("colz");
    //TH1D *pj = h2->ProjectionX("object name",100,400);
    //pj->Draw();


    //fout->Write();
    //fout->Close();

    fin.close();

    return 0;
    std::cout << "#-----finished totalrowcol.cxx-----" << std::endl;

}


