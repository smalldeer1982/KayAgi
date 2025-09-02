#include<bits/stdc++.h>
using namespace std;
int t,n,a[50005];
bool check(int x){
	for(int R=x;R<=n;R++){
		int L=R-x+1;
		if(a[R]<=0){
			if(-a[L]<=t){
				return true;
			}
		}
		else if(a[L]>=0){
			if(a[R]<=t){
				return true;
			}
		}
		else{
			int sum=a[R]-a[L]+min(-a[L],a[R]);
			if(sum<=t){
				return true;
			}
		}
	}
	return false;
}
int main(){
	cin>>t>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	sort(a+1,a+n+1);
	int l=1,r=n;
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
