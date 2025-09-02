#include<bits/stdc++.h>
using namespace std;
int n,k,a[20],vis[20];
void dfs(int dep){
	if(dep>k){
		for(int i=1;i<=k;i++){
			cout<<a[i]<<" ";
		}
		cout<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;
			a[dep]=i;
			dfs(dep+1);
			vis[i]=0;
		}
	}
}
int main(){
	cin>>n>>k;
	dfs(1);
	return 0;
} 