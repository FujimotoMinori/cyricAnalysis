void makeGraphone(){
    
	float x[100],y[100];
	float ex[100],ey[100];
	int n=0;

	FILE* fp=0;
	if( (fp=fopen("allCS.txt","r"))==0){
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

    TCanvas* c1 = new TCanvas("c1");
	TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
	g ->SetMarkerStyle(20);
    g->SetMarkerSize(1);
	g ->SetMarkerColor(kBlue);
	g ->SetTitle("SEU cross section;run number;#sigma (cm^{2})");
    g->SetMaximum(3.0);
    g->SetMinimum(0.0);
	g ->Draw("ap");

}

