#include<bits/stdc++.h>
using namespace std;
double a,b,c,d;
double f(double x){
	return a*x*x*x+b*x*x+c*x+d;
}
int main(){
	cin>>a>>b>>c>>d;
	for(int i=-100;i<=100;i++){
		double l=i,r=i+1,mid;
		if(f(l)==0){
			printf("%.2f ",l);
			continue;
		}
		if(f(r)==0){
			continue;
		}
		if(f(l)*f(r)<0){
			while(r-l>0.001){
				mid=(l+r)/2;
				if(f(mid)*f(r)>0){
					r=mid;
				}
				else{
					l=mid;
				}
			}
			printf("%.2f ",l);
		}
	}
	return 0;
}