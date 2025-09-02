#include<bits/stdc++.h>
using namespace std;
int n,m;
double ans1,ans2;
struct node{
	int v,c;
	double sum;
}a[205];
bool cmp(node x,node y){
	return x.sum<y.sum;
}
bool check(double x){
	for(int i=1;i<=n;i++){
		a[i].sum=x*a[i].c-a[i].v;
	}
    sort(a+1,a+n+1,cmp);
	double tot=0;
	for(int i=1;i<=m;i++){
		tot+=a[i].sum;
	}
	if(tot<=0){
		return true;
	}
	return false;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i].v;
	}
	for(int i=1;i<=n;i++){
		cin>>a[i].c;
	}
	double l=0,r;
	for(int i=1;i<=n;i++){
		if(a[i].v*1.0/a[i].c>r){
			r=a[i].v*1.0/a[i].c;
		}	
	}  		
	while(r-l>0.00001){
		double mid=(l+r)/2;
		if(check(mid)){
			l=mid;
		}
		else{
			r=mid;
		}
	}
	printf("%.3f",l);
	return 0;
}
