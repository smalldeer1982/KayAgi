#include<bits/stdc++.h>
using namespace std;
int L,n,k,a[100005];
int judge(int x){
	int sum=0;
	for(int i=2;i<=n;i++){
		sum+=(a[i]-a[i-1]-1)/x;
	}
	if(sum<=k){
		return 1;
	}
	else{
		return 0;
	}
}
int main(){
	cin>>L>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	int l=1,r=L;
	while(l<r){
		int mid=(l+r)/2;
		if(judge(mid)){
			r=mid;
		}
		else{
			l=mid+1;
		}
	}
	cout<<l<<endl;
	return 0;
}