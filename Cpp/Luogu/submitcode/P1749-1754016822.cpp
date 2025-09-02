#include<bits/stdc++.h>
using namespace std;
#define int long long
int t,n,k;
signed main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		int sum=0;
		sum=(1+k)*k/2;
		if(sum<=n){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
	}
	return 0;
}