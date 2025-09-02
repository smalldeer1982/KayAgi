#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,r,rmb[105],rp[105],t[105];
int dp1[105][105],dp2[105][105];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>rmb[i]>>rp[i]>>t[i];
	}
	cin>>m>>r;
	for(int i=1;i<=n;i++){
		for(int j=m;j>=rmb[i];j--){
			for(int k=r;k>=rp[i];k--){
				if(dp1[j][k]<dp1[j-rmb[i]][k-rp[i]]+1){
					dp1[j][k]=dp1[j-rmb[i]][k-rp[i]]+1;
					dp2[j][k]=dp2[j-rmb[i]][k-rp[i]]+t[i];
				}
				else if(dp1[j][k]==dp1[j-rmb[i]][k-rp[i]]+1){
					dp2[j][k]=min(dp2[j][k],dp2[j-rmb[i]][k-rp[i]]+t[i]);
				}
			}
		}
	}
	cout<<dp2[m][r];
	return 0;
}
