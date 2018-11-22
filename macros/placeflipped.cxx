/*
   placeflipped.cxx

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

int placeflipped(/*const string& inputFile*/){
    std::cout << "#-----start placeflipped.cxx-----" << std::endl;

    //set open file
    //TString ifn = inputFile;
    TString ifncol = "/home/pixeldaq/YARR_rd53a/cyric/macros/sumcol.txt" ;
    //TString ifnrow = "/home/pixeldaq/YARR_rd53a/cyric/macros/sumrow.txt" ;
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
    TH2F* h2 = new TH2F("h2","flipped pixel",192,0,192,400,0,400);

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
	}
            h2->Fill(count,c);
    }
    //std::cout << "#count=" << count << std::endl;

    //set root file for output
    //string foutname = "outputPR.root";
    //TFile* fout = TFile::Open(foutname.c_str(), "RECREATE");

    //draw 2Dhistogram
    h2->SetTitle("SEU test;col;row");
    h2->Draw("colz");

    fin.close();

    std::cout << "#-----finished placeflipped.cxx-----" << std::endl;
    return 0;
}



