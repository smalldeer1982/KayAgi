#include<bits/stdc++.h>
using namespace std; 
const int N=50005;
int a[N],n,m,e;
bool check(int mid){
	int c=0,p=0;
	for(int i=1;i<=n;i++){
		if(a[i]-p<mid){
			c++;
		}
		else{
			p=a[i];
		}
	}
	if(e-p<mid){
		c++;
	}
	return c<=m;
}
int main(){
	cin>>e>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=e,mid;
	while(l<r){
		mid=(l+r+1)/2;
		if(check(mid)){
			l=mid;
		}
		else{
			r=mid-1;
		}
	}
	cout<<l;
	return 0;
}