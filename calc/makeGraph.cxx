void makeGraph(){
    
	float x[100],y[100];
	float ex[100],ey[100];
	int n=0;

	FILE* fp=0;
	if( (fp=fopen("sigmax.txt","r"))==0){
		std::printf("Cannot open file\n");
		return;
	}

	float a,b,c;
	while (! feof(fp)){
		fscanf(fp,"%f %f %f",&a,&b,&c);
		x[n]=a;
		y[n]=b;
        ex[n]=0;
		ey[n]=c;
		n++;
	}

	float x2[100],y2[100];
	float ex2[100],ey2[100];
	int n2=0;

	FILE* fp2=0;
	if( (fp2=fopen("sigmafitx.txt","r"))==0){
		std::printf("Cannot open file\n");
		return;
	}

	float a2,b2,c2;
	while (! feof(fp2)){
		fscanf(fp2,"%f %f %f",&a2,&b2,&c2);
		x2[n2]=a2;
		y2[n2]=b2;
        ex2[n2]=0;
		ey2[n2]=c2;
		n2++;
	}

    TCanvas* c1 = new TCanvas("c1");
	TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
	g ->SetMarkerStyle(20);
    g->SetMarkerSize(1);
	g ->SetMarkerColor(kBlue);
	g ->SetLineColor(kBlue);
	g ->Draw("ap");
	g ->SetTitle("beamsigmax;# of slot;#sigma_{x} (mm)");
	g ->GetXaxis()->SetLimits(0,16);
    g ->GetXaxis()->SetTitleSize(0.04);
    g ->GetYaxis()->SetTitleSize(0.04);
    g ->GetXaxis()->SetTitleOffset(0.8);
    g ->GetYaxis()->SetTitleOffset(0.8);

	TGraphErrors* g2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
	g2 ->SetMarkerStyle(20);
    g2 ->SetMarkerColor(kRed);
    g2 ->SetLineColor(kRed);
    g2 ->Draw("same p");

    g->Fit("pol1","","",1.0,-1.0);

    TLegend* leg=new TLegend(0.3,0.2,0.85,0.32);
    leg->AddEntry(g,"fit from finger","p");
    leg->AddEntry(g2,"fit from place of flipped bit","p");
    leg->SetTextSize(0.05);
    leg->Draw();
    
}

