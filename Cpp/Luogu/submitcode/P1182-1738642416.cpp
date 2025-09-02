#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005];
int l=0,r=0;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		if(l<a[i]){
			l=a[i];
		}
		r+=a[i];
	}
	while(l<=r){
		int mid=(l+r)/2,cnt=1,tmp=0;
		for(int i=1;i<=n;i++){
			if(a[i]+tmp<=mid){
				tmp+=a[i];
			}
			else{
				tmp=a[i];
				cnt+=1;
			}
		}
		if(cnt<=m){
			r=mid-1;
		}
		else{
			l=mid+1;
		}
	}
	cout<<l;
	return 0;
}
