void makeGraph(){
    
	float x[100],y[100];
	float ex[100],ey[100];
	int n=0;

	FILE* fp=0;
	if( (fp=fopen("sigmaz.txt","r"))==0){
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
	if( (fp2=fopen("sigmafitz.txt","r"))==0){
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

	TGraphErrors* g = new TGraphErrors(n,x,y,ex,ey);
	g ->SetMarkerStyle(20);
	g ->SetMarkerColor(kBlue);
	g ->Draw("ap");
	g ->SetTitle("Sigma;slot;sigma");
	//g ->GetXaxis()->SetLimits(120,150);

	TGraphErrors* g2 = new TGraphErrors(n2,x2,y2,ex2,ey2);
	g2 ->SetMarkerStyle(20);
	//g2 ->SetMarkerColor(kRed);
	g2 ->Draw("same ap");

	/*TF1 *f1 = new TF1("f1","[0]/(x-[1])",130,150);
		f1 ->SetParameters(1.0e5,100.);
		//f1 ->SetParNames("A","T_C");
		g ->Fit("f1","","",130,150);
		gStyle ->SetOptFit();
		gStyle ->SetOptStat();
		gStyle ->SetStatH(0.08);
		gStyle ->SetStatW(0.08);*/

}

