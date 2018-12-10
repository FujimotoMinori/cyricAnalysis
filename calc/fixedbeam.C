//code by Nakamura-san

void fixedbeam(){
  double xsize=20 ; // mm
  double ysize=10 ; // mm
  double beamsigmax=3; //mm
  double beamsigmay=3; //mm
  double beamcurrent=1; // nA
  double duration=10; // min
  double fluence=5e15; // neq/cm2 for other places

  gStyle->SetPadRightMargin(0.15);
  TH2D *h2 = new TH2D("h","h",xsize*10,0,xsize,ysize*10,0,ysize);
  h2->GetXaxis()->SetTitle("X [mm]");
  h2->GetYaxis()->SetTitle("Y [mm]");
  TH2D *h3 = new TH2D("flat","flat",xsize*10,0,xsize,ysize*10,0,ysize);
  TF2 *f2 = new TF2("f2","[0]*TMath::Gaus(x,[1],[2])*TMath::Gaus(y,[3],[4])",0,20,0,10); 
  f2->SetParameters(1,xsize/2.,beamsigmax,ysize/2.,beamsigmay); 
  
  for(int ix=1;ix<=(int)xsize*10;ix++){
    for(int iy=1;iy<=(int)ysize*10;iy++){
      h2->SetBinContent(ix,iy,f2->Eval(h2->GetXaxis()->GetBinCenter(ix),h2->GetYaxis()->GetBinCenter(iy)));
      h3->SetBinContent(ix,iy,fluence);
    }
  }
  h2->Scale((beamcurrent*1e-9/1.9e-19*duration*60)*10000/h2->Integral());
  h2->Add(h3);
  h2->Divide(h3);
  TCanvas *c2 = new TCanvas("c1","c1",1000,500);
  h2->Draw("COLZ");
  c2->Update();
  c2->Print("fixedbeam.png");
} 
