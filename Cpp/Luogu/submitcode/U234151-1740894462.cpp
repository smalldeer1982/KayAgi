#include<bits/stdc++.h>
using namespace std;
int k,n,a[105],dp1[105],dp2[105];
int main(){
	cin>>k;
	for(int i=1;i<=k;i++){
		cin>>n;
		for(int j=1;j<=n;j++){
			cin>>a[j];
			dp1[j]=1;
			dp2[j]=1;
		}
		for(int j=1;j<=n;j++){
			for(int k=1;k<j;k++){
				if(a[j]>a[k]){
					dp1[j]=max(dp1[j],dp1[k]+1);
				}
			}
		}
		for(int j=n;j>=1;j--){
			for(int k=j+1;k<=n;k++){
				if(a[j]>a[k]){
					dp2[j]=max(dp2[j],dp2[k]+1);
				}
			}
		}
		int ans=0;
		for(int j=1;j<=n;j++){
			ans=max(ans,max(dp1[j],dp2[j]));
		}
		cout<<ans<<endl;
	}
	return 0;
}