#include<bits/stdc++.h>
using namespace std;
int n;
double maxx;
struct node{
	int m,d;
}a[4005];
int month[20]={0,31,29,31,30,31,30,31,31,30,31,30,31};
bool cmp(node x,node y){
	if(x.m==y.m){
		return x.d<y.d;
	}
	return x.m<y.m;
}
void solve(int z){
	double sum=0;
	if(a[z].d==0){
		for(int i=a[z-1].m;i<=a[z].m-1;i++){
			sum+=month[i];
		}
	}
	else{
		for(int i=a[z-1].m+1;i<=a[z].m-1;i++){
			sum+=month[i];
		}	
	}
	if(a[z-1].m!=a[z].m){
		sum+=month[a[z-1].m]-a[z-1].d;
	}
	if(a[z-1].m==a[z].m){
		sum+=a[z].d-a[z-1].d-1;
	}
	else{
		sum+=a[z].d-1;
	}
	maxx=max(maxx,sum);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].m>>a[i].d;
	}
	if(n==366){
		cout<<0;
		return 0;
	} 
	sort(a+1,a+n+1,cmp);
	a[0].m=1;
	a[0].d=0;
	a[n+1].m=12;
	a[n+1].d=32; 
	for(int i=1;i<=n+1;i++){
		solve(i);
	}
	cout<<round(maxx/366*24*60*60);
	return 0;
} 