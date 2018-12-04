/*
   readCurrent.C
   read dump current and make histogram 
   use this code if you want to see DumpCurrent
 */

{
#include <vector>
#include <fstream>

    vector<Double_t> num,x;

    std::cout << "start" << std::endl;
    TH1F *h1 = new TH1F("h1","h1",100,-2.0e-9,2.0e-9);
    TH1F *h2 = new TH1F("h2","h2",100,-2.0e-9,2.0e-9);

    //read data
    ifstream ifs("/Users/fujimoto/Desktop/DumpCurrent_CYRIC_20181127-29/cyric1129_1.dat");
    std::cout << "set data" << std::endl;
    int i;
    while(!ifs.eof()){
        Double_t xx;
        ifs >> xx ;
        i++;
        x.push_back(xx);
        num.push_back(i);
        if(i>10080&&i<10176){
            h1->Fill(xx);
        }
    }
    ifs.close();
    std::cout << "finished reading file" << std::endl;

    Double_t* xpointer=&(x.at(0));
    Double_t* npointer=&(num.at(0));

    //make graph
    TGraph* tg = new TGraph(x.size(),npointer,xpointer);

    tg->SetMarkerStyle(21);
    tg->SetMarkerColor(kRed);
    tg->SetMarkerSize(0.5);
    //tg->GetXaxis()->SetTitle("Input Voltage V");
    //tg->SetMaximum(1.5e-9);
    //tg->SetMinimum(-1.5e-9);
    tg->GetYaxis()->SetTitle("current");
    tg->GetYaxis()->SetTitleOffset(1.3);
    tg->SetTitle("");

    //fit histogram
    TF1 *f1 = new TF1("func","gaus",-2.0e-9,1.0e-9);
    f1->SetParameter(0,180);
    f1->SetParameter(1,-0.6e-9);
    f1->SetParameter(2,0.5e-10);
    h1->Fit("func","l","",-1.0e-9,-1.0e-9);
    //h1->Fit("gaus");

    TCanvas* c1 = new TCanvas("c1");
    tg->Draw("AP");
    TCanvas* c2 = new TCanvas("c2");
    h1->Draw();

    //TLegend* tl=new TLegend(0.5,0.2,0.89,0.3);
    //tl->AddEntry(tg->GetFunction("pol1"),"(1899.3+/-0.6)x+(2045.4+/-0.4)","l");
    //tl->SetTextSize(0.03);
    //tl->Draw();
    }


