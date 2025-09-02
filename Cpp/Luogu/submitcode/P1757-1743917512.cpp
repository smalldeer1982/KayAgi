#include<bits/stdc++.h>
using namespace std;
int n,m,v[1005][1005],w[1005][1005],t[105],dp[1005];
int main(){
	cin>>m>>n;
	for(int i=1;i<=n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		t[z]+=1;
		w[z][t[z]]=x;
		v[z][t[z]]=y;
	}
	for(int i=1;i<=n;i++){
		for(int j=m;j>=0;j--){
			for(int k=1;k<=t[i];k++){
				if(j>=w[i][k]){
					dp[j]=max(dp[j],dp[j-w[i][k]]+v[i][k]);
				}
			}
		}
	}
	cout<<dp[m];
	return 0;
}
