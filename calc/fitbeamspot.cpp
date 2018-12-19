//fitting of the beam point by using RooFit 
using namespace RooFit;

void fitbeamspot(){

    //make data
    /////////////////////////////////////////////////////////////
    string finname = "/Users/fujimoto/cyric11/cyricAnalysis/macros/results/outputplace_run00044.root";
    //file open
    TFile* fin = TFile::Open(finname.c_str(), "READ");
    cout << " input data file:" << finname.c_str() << " open..." << endl;
    TH2F *h2 = (TH2F*)fin->Get("h2"); 
    /////////////////////////////////////////////////////////////
    h2->RebinX(8);
    h2->RebinY(8);

    //make workspace
    RooWorkspace w("w", kTRUE);

    RooPlot* xframe = x->frame();
    data_h.plotOn(xframe);

    pdf->fitTo(data_h);
    pdf->plotOn(xframe);

    xframe->Draw();
    //continue...
}


