#include<bits/stdc++.h>
using namespace std;
int n,v,w,a[500005],maxn=-1;
bool check(int x){
	int sum=x;
	for(int i=1;i<=n;i++){
		if(a[i]-x*v<=0){
			continue;
		}
	    else{
			sum-=((a[i]-x*v+w-1)/w);
		}    
	}
	if(sum<0){
		return true;
	}
	return false;
}
int main(){
	cin>>n>>v>>w;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maxn=max(maxn,a[i]);
	}
	sort(a+1,a+n+1);
	int l=1,r=maxn;
	while(l<=r){
		int mid=(l+r)/2;
		if(check(mid)){
			l=mid+1;
		}
		else{
			r=mid-1;
		}
	}
	cout<<l;
	return 0;
}
