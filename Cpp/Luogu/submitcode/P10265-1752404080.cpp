#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,a[1005][1005];
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cin>>a[i][j];
		}
	}
	int ans=0,sum=0;
	for(int i=1;i<=n;i++){
		if(a[m][i]==1){
			ans+=1;
		}
	}
	cout<<ans<<" ";
	sum+=ans;
	ans=0;
	for(int i=1;i<=n;i++){
		if(a[i][m]==1){
			ans+=1;
		}
	}
	cout<<ans<<" ";
	sum+=ans;
	cout<<sum;
	return 0;
}
