#include<bits/stdc++.h>
using namespace std;
int n,k,a[100005],ans;
bool check(int x){
	int t=0;
	for(int i=1;i<=n;i++){
		t+=a[i]/x;
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
	int l=0,r=1e8,mid;
	while(l<r){
		mid=(l+r+1)/2;
		if(check(mid)){
			r=mid-1;
		}
		else{
			l=mid;
			ans=mid;
		}
	}
	cout<<ans;
	return 0;
}