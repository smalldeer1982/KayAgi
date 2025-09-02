#include<bits/stdc++.h>
using namespace std;
int n,m,g[55];
int w[1<<25],ans,cnt;
void dfs1(int u,int s){
	if(u==n/2){
		w[cnt++]=s;
		return;
	}
	dfs1(u+1,s);
	if(g[u]<=m-s){
		dfs1(u+1,s+g[u]);
	}
}
void dfs2(int u,int s){
	if(u==n){
		ans=max(ans,*(upper_bound(w,w+cnt,m-s)-1)+s);
		return;
	}
	dfs2(u+1,s);
	if(g[u]<=m-s){
		dfs2(u+1,s+g[u]);
	}
}
bool cmp(int x,int y){
	return x>y;
}
int main(){
	cin>>m>>n;
	for(int i=0;i<n;i++){
		cin>>g[i];
	}
	sort(g,g+n,cmp);
	dfs1(0,0);
	sort(w,w+cnt);
	cnt=unique(w,w+cnt)-w;
	dfs2(n/2,0);
	cout<<ans;
	return 0;
}
