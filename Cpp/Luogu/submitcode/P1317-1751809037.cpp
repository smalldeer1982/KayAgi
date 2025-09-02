#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,a[10005],ans=0;
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;){
		while(a[i]<=a[i-1]&&i<=n){
			i+=1;
		}
		while(a[i]>=a[i-1]&&i<=n){
			i+=1;
		}
		ans+=1;
	}
	cout<<ans-2;
	return 0;
}
