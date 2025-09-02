#include<bits/stdc++.h>
using namespace std;
int n,len=0,a[100005],b[100005],maps[100005],dp[100005];
int main(){
	cin>>n;
	memset(dp,0x3f3f3f,sizeof(dp));
	for(int i=1;i<=n;i++){
		cin>>a[i];
		maps[a[i]]=i;
	}
	for(int i=1;i<=n;i++){
		cin>>b[i];
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		int l=0,r=len,mid;
		if(maps[b[i]]>dp[len]){
			dp[++len]=maps[b[i]];
		}
		else {	
			while(l<r){	
			    mid=(l+r)/2;
			    if(dp[mid]>maps[b[i]]){
					r=mid;
				}
				else{
					l=mid+1; 
				} 
			}
			dp[l]=min(maps[b[i]],dp[l]);
     	}
    }
	cout<<len;
	return 0;
}