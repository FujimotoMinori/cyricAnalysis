void makeGraphone(){
    
	float x[100],y[100];
	float ex[100],ey[100];
	int n=0;
    float total = 0;
    float mean = 1.63;
    float emean = 0.22;

	FILE* fp=0;
	if( (fp=fopen("sigmathermal.txt","r"))==0){
		std::printf("Cannot open file\n");
		return;
	}

	float a,b,c;
	while (! feof(fp)){
		fscanf(fp,"%f %f %f",&a,&b,&c);
		x[n]=a;
		y[n]=b-mean;
        ex[n]=0;
		ey[n]=sqrt(c*c+emean*emean);
		//ey[n]=c;

        std::cout << "b = " << b << std::endl;
        std::cout << "c = " << c << std::endl;
        std::cout << "eman = " << emean << std::endl;
        std::cout << "ey = " << ey[n] << std::endl;
        total += b; 
		n++;
	}
    std::cout << "total = " << total << std::endl;
    std::cout << "n = " << n << std::endl;
    std::cout << "mean = " << total/n << std::endl;

    TCanvas* c1 = new TCanvas("c1");
	TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
	g ->SetMarkerStyle(20);
    g->SetMarkerSize(1);
	g ->SetMarkerColor(kBlue);
	//g ->GetXaxis()->SetRangeUser(-0.5,3.5);
	//g ->SetTitle("SEU cross section;run number ;#sigma (#times10^{-14}cm^{2})");
	g ->SetTitle("SEU cross section;temprature ({}^{#circ}C) ;#sigma (#times10^{-14}cm^{2})");
	//g ->SetTitle("SEU cross section;dose rate (#times10^{15}n_{eq}) ;#sigma (#times10^{-14}cm^{2})");
    g->SetMaximum(1.5);
    //g->SetMinimum(0.0);
    g->SetMinimum(-1.5);
	g ->Draw("ap");

}

