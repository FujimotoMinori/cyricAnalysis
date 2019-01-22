void makeGraphAll(){
    
    float mean = 1.78;
    float emean = 0.22;
	float x[100],y[100];
	float ex[100],ey[100];
	int n=0;

	FILE* fp=0;
	if( (fp=fopen("sigmascan.txt","r"))==0){
		std::printf("Cannot open file\n");
		return;
	}

	float a,b,c;
	while (! feof(fp)){
		fscanf(fp,"%f %f %f",&a,&b,&c);
		x[n]=a;
		//y[n]=b;
		y[n]=b-mean;
        ex[n]=0;
		//ey[n]=c;
		ey[n]=sqrt(c*c+emean*emean);
		n++;
	}

	float x2[100],y2[100];
	float ex2[100],ey2[100];
	int n2=0;

	FILE* fp2=0;
	if( (fp2=fopen("sigmapoint.txt","r"))==0){
		std::printf("Cannot open file\n");
		return;
	}

	float a2,b2,c2;
	while (! feof(fp2)){
		fscanf(fp2,"%f %f %f",&a2,&b2,&c2);
		x2[n2]=a2;
		//y2[n2]=b2;
		y2[n2]=b2-mean;
        ex2[n2]=0;
		//ey2[n2]=c2;
		ey2[n2]=sqrt(c2*c2+emean*emean);
		n2++;
	}

    //TCanvas* c1 = new TCanvas("c1");
    TCanvas* c1 = new TCanvas("c1","c1",600,400);
	TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
	g ->SetMarkerStyle(20);
    g->SetMarkerSize(1);
	g ->SetMarkerColor(kBlue);
	//g ->SetLineColor(kBlue);
    //g->SetMinimum(0.0);
    //g->SetMaximum(3.0);
    g->SetMinimum(-1.0);
    g->SetMaximum(1.0);
	g ->Draw("ap");
	g ->SetTitle(";run number ;#sigma (#times10^{-14}cm^{2})");
	g ->GetXaxis()->SetLimits(40,54);
    g ->GetXaxis()->SetTitleSize(0.04);
    g ->GetYaxis()->SetTitleSize(0.04);
    g ->GetXaxis()->SetTitleOffset(0.8);
    g ->GetYaxis()->SetTitleOffset(0.8);

	TGraphErrors* g2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
	g2 ->SetMarkerStyle(20);
    g2 ->SetMarkerColor(kRed);
    //g2 ->SetLineColor(kRed);
    g2 ->Draw("same p");

    TF1* f1 = new TF1("func1","0",39,55); 
    f1->SetLineColor(kBlack);
    f1->SetLineWidth(1);
    f1->Draw("same");

    TLegend* leg=new TLegend(0.55,0.2,0.75,0.32);
    leg->AddEntry(g,"scan","p");
    leg->AddEntry(g2,"point","p");
    leg->SetTextSize(0.05);
    leg->Draw();
    
}


