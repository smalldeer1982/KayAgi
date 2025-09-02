#include<bits/stdc++.h>
using namespace std;
double n,k,a[100005],ans;
bool check(double x){
	double t=0;
	for(int i=1;i<=n;i++){
		t+=int(a[i]/x);
	}
	if(t<k){
		return true;
	}
	return false;
}
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	double l=0,r=1e5+5,mid;
	while(r-l>0.001){
		mid=(l+r)/2;
		if(check(mid)){
			r=mid;
		}
		else{
			l=mid;
			ans=mid;
		}
	}
	printf("%.2f",ans);
	return 0;
}