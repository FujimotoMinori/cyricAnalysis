#include <iostream>

double func(double x){
    double y;
    y=2*x;	

    return y;	
}

double integral(int n,double a,double b, double(*func)(double)){
    double s,s1,x,x1,dx;

    dx= (b-a)/n;	

    for(int i=0;i<n;i++){
        x = a+i*dx;
        x1 = x+dx;
        s1 = ((func(x)+func(x1))/2)*dx;	

        s += s1;
    }
    return s;

}

int main(){
    double a,b;
    int n;

    a=0;
    b=10;
    n=100; 

    double answer;
    answer = integral(n,a,b,func);
    std::cout << "answer=" << answer << std::endl;	

    return 0;	
}


