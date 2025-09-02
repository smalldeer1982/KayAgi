#include<bits/stdc++.h>
using namespace std;
double x[5],y[5];
double dist(double a,double b,double c,double d){
	return sqrt((a-b)*(a-b)+(c-d)*(c-d));
}
int main(){
	double dis=0;
	for(int i=1;i<=3;i++){
		cin>>x[i]>>y[i];
	}
	   dis +=dist(x[1],x[2],y[1],y[2]);
	   dis +=dist(x[1],x[3],y[1],y[3]);
	   dis +=dist(x[3],x[2],y[3],y[2]);
	 printf("%.2lf",dis);
	return 0;
}
 