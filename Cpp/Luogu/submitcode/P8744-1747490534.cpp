#include<bits/stdc++.h>
using namespace std;
int n;
vector<int>p[100005];
int dfs(int c){
	int maxx=0;
	for(int i=0;i<p[c].size();i++){
		int v=p[c][i];
		maxx=max(maxx,dfs(v));
	}
	return maxx+p[c].size();
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		int x;
		cin>>x;
		p[x].push_back(i);
	}
	cout<<dfs(1);
	return 0;
}
