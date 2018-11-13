/*
    analyze.C
*/
#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2D.h>
#include <TH2F.h>
#include <TCanvas.h>

int analyze(){
  std::cout << "#-----start analyze.cxx-----" << std::endl;
 
  //set open file
  /*
  std::string inputFile = "";
  int opt;
  while ((opt = getopt(argc, argv, "hivc:")) != -1) {
    switch (opt){
    case 'c':
        inputFile = std::string(optarg);
    }
   }*/

    TString ifn = "../../YARR/src/redirect.txt";
    //TString ifn = inputFile;
    ifstream fin;
    std::string str;
    fin.open(ifn);
    if(fin.fail()){
       cerr << "cannot open file : " << ifn << std::endl;
       return 1;
    }

   //read file
   int a,b,c;
   const int n_Col = 400;
   const int n_Row = 192;
   int val[n_Col][n_Row];
   while(getline(fin,str))
   {
     if(str[0] == '#') continue;
     else if(str[0] == 'v') continue;
        a = 0; 
        b = 0; 
        c = 0; 
        sscanf(str.data(), "%d %d %d", &a, &b, &c);
        val[a][b] = c;
	//std::cout << " val= " << val[a][b]  << std::endl;
   }

   
   //make histograms
   TH2F *h0 = new TH2F("h0","bits[0];column;row",400,0,399,192,0,191);
   TH2F *h1 = new TH2F("h1","bits[1];column;row",400,0,399,192,0,191);
   TH2F *h2 = new TH2F("h2","bits[2];column;row",400,0,399,192,0,191);
   TH2F *h3 = new TH2F("h3","bits[3];column;row",400,0,399,192,0,191);
   TH2F *h4 = new TH2F("h4","bits[4];column;row",400,0,399,192,0,191);
   TH2F *h5 = new TH2F("h5","bits[5];column;row",400,0,399,192,0,191);
   TH2F *h6 = new TH2F("h6","bits[6];column;row",400,0,399,192,0,191);
   TH2F *h7 = new TH2F("h7","bits[7];column;row",400,0,399,192,0,191);

   //get values of each bits
   bool bits[8][n_Col][n_Row];
   // // [0] Enable Injection
   // // [1] Small injection capacitor
   // // [2] Imon and Hitbus out
   // // [3:6] TDAC value [6]=MSB
   // // [7]: sign
   
   for (unsigned row=0; row<n_Row; row+=1) {
     for (unsigned col=0; col<n_Col; col+=1) {
       for (int i=0; i<8; i+=1) {
	 bool bv = ((val[col][row] >> i) & 0b1);
	 bits[i][col][row] = bv; 
	 //std::cout <<  bits[i][col][row]; 
       }
         if(bits[0][col][row] == 0b1) h0->Fill(col,row); 
         if(bits[1][col][row] == 0b1) h1->Fill(col,row); 
         if(bits[2][col][row] == 0b1) h2->Fill(col,row); 
         if(bits[3][col][row] == 0b1) h3->Fill(col,row); 
         if(bits[4][col][row] == 0b1) h4->Fill(col,row); 
         if(bits[5][col][row] == 0b1) h5->Fill(col,row); 
         if(bits[6][col][row] == 0b1) h6->Fill(col,row); 
         if(bits[7][col][row] == 0b1) h7->Fill(col,row); 
       //std::cout << std::endl;
       //std::cout << "col= " << col << " row= " << row << " val= " << val[col][row]  << std::endl;
     }
   }
   
   //Draw histograms
   TCanvas *c1 = new TCanvas("c", "c",1000,1000);
   gStyle->SetOptStat(11);
   c1->Divide(2,4);
   c1->cd(1); 
   h0->Draw("colz");
   c1->cd(2); 
   h1->Draw("colz");
   c1->cd(3); 
   h2->Draw("colz");
   c1->cd(4); 
   h3->Draw("colz");
   c1->cd(5); 
   h4->Draw("colz");
   c1->cd(6); 
   h5->Draw("colz");
   c1->cd(7); 
   h6->Draw("colz");
   c1->cd(8); 
   h7->Draw("colz");

   fin.close();

   return 0;
   std::cout << "#-----finished analyze.cxx-----" << std::endl;

}

