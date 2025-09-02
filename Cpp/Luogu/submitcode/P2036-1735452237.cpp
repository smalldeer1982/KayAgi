#include<bits/stdc++.h>
using namespace std;
int n,s[15],k[15],b[15],ans=INT_MAX,sd,kd;
void dfs(int x){
	if(x==n+1){
		sd=1,kd=0;
		for(int i=1;i<=n;i++){
			if(b[i]==1){
				sd*=s[i];
				kd+=k[i];
				ans=min(ans,abs(sd-kd));	
			}
		}
		
		return;
	}
	for(int i=0;i<=1;i++){
		b[x]=i;
		dfs(x+1);
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s[i]>>k[i];
	}
	dfs(1);
	cout<<ans;
	return 0;
}