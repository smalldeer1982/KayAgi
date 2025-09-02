#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long n,a,b,c,jy[200005],sum=0;
long long dfs(long long res){
	if(res<=c){
		return 1;
	}
	if(jy[res]!=0){
		return jy[res];
	}
	else{
		jy[res]=(dfs(res-a)%mod+dfs(res-b)%mod)%mod;
		return jy[res];
	}
}
int main(){
	cin>>n>>a>>b>>c;
	cout<<dfs(n);
	return 0;
}
