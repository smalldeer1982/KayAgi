#include<bits/stdc++.h>
using namespace std;
int n,c[1005];
struct node{
	int t,s;
}a[1005];
bool cmp(node x,node y){
	if(x.s==y.s){
		return x.t<y.t;
	}
	return x.s<y.s;
}
bool check(int x){
	for(int i=1;i<=n;i++){
		if(c[i]+x>a[i].s){
			return false;
		}
	}
	return true;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i].t>>a[i].s;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		c[i]=c[i-1]+a[i].t;
	}
	int l=-1,r=1e6+5;
	while(l<r){
		int mid=(l+r+1)/2;
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
