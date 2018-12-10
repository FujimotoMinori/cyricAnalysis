/*
   analyzerowcol.C
   compare two files and make summary file "sumplace.txt"
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

int analyzerowcol(const string& inputFile){
    std::cout << "#-----start analyzerowcol.cxx-----" << std::endl;

    //set open file
    TString ifn = "/home/pixeldaq/cyric/afterIrrad/src/registerdata/run00053_PR00001.txt";
    TString ifn2 = inputFile;
    std::cout << "#inputFile=" <<ifn2 << std::endl;
    ifstream fin;
    ifstream fin2;
    std::string str;
    std::string str2;

    //open files
    fin.open(ifn);
    if(fin.fail()){
	cerr << "#cannot open file1 : " << ifn << std::endl;
	return 1;
    }
    fin2.open(ifn2);
    if(fin2.fail()){
	cerr << "#cannot open file2 : " << ifn2 << std::endl;
	return 1;
    }
    std::cout << "#finished opening files" << std::endl;

    //read files
    const int n_Col = 400;
    const int n_Row = 192;
    int a,b,c;
    int val[n_Col][n_Row] = {};
    while(getline(fin,str))
    {
	if(str[0] == '#') continue;
	else if(str[0] == 'v') continue;
	a = 0; 
	b = 0; 
	c = 0; 
	sscanf(str.data(), "%d %d %d", &a, &b, &c);
	val[a][b] = c;
    }

    int a2,b2,c2;
    int val2[n_Col][n_Row] = {};
    while(getline(fin2,str2))
    {
	if(str2[0] == '#') continue;
	else if(str2[0] == 'v') continue;
	a2 = 0; 
	b2 = 0; 
	c2 = 0; 
	sscanf(str2.data(), "%d %d %d", &a2, &b2, &c2);
	val2[a2][b2] = c2;
    }

    //set file for summary output
    std::ofstream summaryplace("sumplace.txt" ,std::ios::app);

    //get values of each bits
    bool bits[8][n_Col][n_Row];
    bool bits2[8][n_Col][n_Row];
    // // [0] Pixel Enable / Pixel Power and Enable
    // // [1] Injection Enable
    // // [2] Hit-OR-bus Enable
    // // [3:6] TDAC value [6]=MSB
    // // [7]: TDAC sign / Gain Selection
    for (unsigned row=0; row<n_Row; row+=1) {
	for (unsigned col=0; col<n_Col; col+=1) {
	    for (int i=0; i<8; i+=1) {
		bool bv = ((val[col][row] >> i) & 0b1);
		bool bv2 = ((val2[col][row] >> i) & 0b1);
		bits[i][col][row] = bv; 
		bits2[i][col][row] = bv2; 
	    }
	}
    }

    //compare bits in 2 files
    int f[8] = {};
    int total= 0;
    for (unsigned row=0; row<n_Row; row+=1) {
	for (unsigned col=0; col<n_Col; col+=1) {
	    if(val[col][row] != val2[col][row]){
		summaryplace << col << " " << row << std::endl;
		++total;
	    }

	    /*
	       for (int i=0; i<8; i+=1) {
	       if(bits[i][col][row] != bits2[i][col][row]) {
	       ++f[i];
	       ++total;
	//std::cout << "flipped col= " << col << " row= " << row << std::endl;
	} 
	}
	*/
	}
    }

    /*
       for (int i=0; i<8; i+=1) {
       std::cout << "numbers of false bits in bit[" << i << "] = " << f[i] << std::endl;
       summary << f[i] << " " << std::endl;
       }
       */

    std::cout << "numbers of total false bits = " << total << std::endl;
    summaryplace << "total " << total << std::endl;
    //summarycol << "total " << total << std::endl;

    summaryplace.close();

    fin.close();
    fin2.close();

    return 0;
    std::cout << "#-----finished analyzerowcol.cxx-----" << std::endl;
}

