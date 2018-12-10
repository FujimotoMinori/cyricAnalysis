//code by Nakamura-san

#include "TF1.h"
void OverscanSim2D(){
  double beamsigmax=4;
  double beamsigmay=4;
  double overscansigmax=3;
  double overscansigmay=3;
  //  double pos=0;
  //  double endpos=10;
  double samplesizex=20;
  double samplesizey=10;

  double posstep=1;
  double precision=1./posstep;
  double mergin=15; // for plot

  double posx=-1*overscansigmax*2;
  double posy=-1*overscansigmay*2;
  double endposx=samplesizex+overscansigmax*2;
  double endposy=samplesizey+overscansigmay*2;
  
  //  TF1 *fb = new TF1("fb","[0]*exp(-0.5*((x-[1])/[2])**2)",-10,samplesize+10);
  TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",0,20,0,10); 
  f2->SetParameters(1,samplesizex/2.,beamsigmax,samplesizey/2.,beamsigmay); 


  int nbinx=(int)precision*((int)samplesizex+2*mergin);
  double xmin=-1*mergin;
  double xmax=samplesizex+mergin;
  int nbiny=(int)precision*((int)samplesizey+2*mergin);
  double ymin=-1*mergin;
  double ymax=samplesizey+mergin;
  
  TH2D *h1=new TH2D("h1","h1",nbinx,xmin,xmax,nbiny,ymin,ymax);
  TH2D *h2=new TH2D("h2","h2",nbinx,xmin,xmax,nbiny,ymin,ymax);
  TH2D *h3=new TH2D("h3","h3",nbinx,xmin,xmax,nbiny,ymin,ymax);
  h2->SetLineColor(2);
  h3->SetLineColor(4);
  while(posx<=endposx){
    posy=-1*overscansigmay*2;
    while(posy<=endposy){
      //      std::cout << posx << " " << posy << std::endl;
      f2->SetParameter(1,posx);
      f2->SetParameter(3,posy);
      for(int ix=1;ix<=nbinx;ix++){
	for(int iy=1;iy<=nbiny;iy++){
	  double val1=h1->GetBinContent(ix,iy);
	  double val2=h2->GetBinContent(ix,iy);
	  double val3=h3->GetBinContent(ix,iy);
	  h1->SetBinContent(ix,iy,val1+f2->Eval(h1->GetXaxis()->GetBinCenter(ix),h1->GetYaxis()->GetBinCenter(iy)));
	  if(posx>-1*overscansigmax&&posx<=samplesizex+overscansigmax && posy>-1*overscansigmay&&posy<=samplesizey+overscansigmay)
	    h2->SetBinContent(ix,iy,val2+f2->Eval(h2->GetXaxis()->GetBinCenter(ix),h2->GetYaxis()->GetBinCenter(iy)));
	  if(posx>0&&posx<=samplesizex && posy>0&&posy<=samplesizey)
	    h3->SetBinContent(ix,iy,val3+f2->Eval(h3->GetXaxis()->GetBinCenter(ix),h3->GetYaxis()->GetBinCenter(iy)));
	}
      }
      posy+=posstep;
    }
    posx+=posstep;
  }
  int binx0=mergin/posstep+1;
  int binx1=nbinx-mergin/posstep;
  int biny0=mergin/posstep+1;
  int biny1=nbiny-mergin/posstep;
  TCanvas *c1 = new TCanvas("c1","c1",1200,400);
  c1->Divide(3,1);
  c1->cd(1);
  h1->Draw("COLZ");
  std::cout << "2sigma overscan fiducial / total current: " << h1->Integral(binx0,binx1,biny0,biny1)/h1->Integral() << std::endl;
  c1->cd(2);
  h2->Draw("COLZ");
  std::cout << "1sigma os / 2sigma os : " << h2->Integral(binx0,binx1,biny0,biny1)/h1->Integral(binx0,binx1,biny0,biny1) << std::endl;
  c1->cd(3);
  h3->Draw("COLZ");
  std::cout << "0sigma os / 2sigma os : " << h3->Integral(binx0,binx1,biny0,biny1)/h1->Integral(binx0,binx1,biny0,biny1) << std::endl;
}
