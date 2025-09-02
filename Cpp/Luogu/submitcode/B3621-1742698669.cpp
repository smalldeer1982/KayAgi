#include<bits/stdc++.h>
using namespace std;
int n,k,a[20];
void dfs(int dep){
	if(dep>k){
		for(int i=1;i<=k;i++){
			cout<<a[i]<<" ";
		}
		cout<<endl;
		return;
	}
	for(int i=1;i<=n;i++){
		a[dep]=i;
		dfs(dep+1);
	}
}
int main(){
	cin>>k>>n;
	dfs(1);
	return 0;
} 