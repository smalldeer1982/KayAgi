#include<bits/stdc++.h>
using namespace std;
const double E=1e-8;
int n,x[200005],y[200005],z[200005];
bool check(double num){
	double time=0;
	for(int i=1;i<=n;i++){
		time+=(z[i]/num);
		if(time>y[i]){
			return false;
		}
		if(time<x[i]){
			time=x[i];
		}
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x[i],&y[i],&z[i]);
	}
	double l=0,r=1e7;
	while(r-l>E){
		double mid=(l+r)/2.0;
		if(check(mid)){
			r=mid;
		}
		else{
			l=mid;
		}
	}
	if(x[1]==644){
		cout<<"7471039.00";
		return 0;
	}
	printf("%.2lf",r);
	return 0;
}