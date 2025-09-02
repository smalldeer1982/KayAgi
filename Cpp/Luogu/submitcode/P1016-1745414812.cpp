#include<bits/stdc++.h>
using namespace std;
double D1,c,D2,P,ans,sum;
int n;
struct node{
	double d,p;
}a[10];
bool cmp(node x,node y){
	return x.d<y.d;
}
int main(){
	cin>>D1>>c>>D2>>P>>n;
	a[0].p=P;
	a[n+1].d=D1;
	for(int i=1;i<=n;i++){
		cin>>a[i].d>>a[i].p;
		if(a[i].d-a[i-1].d>D2*c){
			cout<<"No Solution";
			return 0;
		}
	}
	sort(a+1,a+n+1,cmp);
	int f=0;
	while(f<=n+1){
		int j,z=0;
		for(j=z=f+1;j<=n;j++){
			if(a[j].p<a[z].p){
				z=j;
			}
			if(a[j].p<a[f].p||a[j+1].d-a[f].d>c*D2){
				break;
			}
		}
		if(a[j].p>a[f].p){
			ans+=(c-sum)*a[f].p;
			sum=c-(a[z].d-a[f].d)/D2;
			f=z;
		}
		else{
			ans+=a[f].p*((a[j].d-a[f].d)/D2-sum);
			f=j;
			sum=0;
		}
	}
	printf("%.2f",ans);
	return 0;
}