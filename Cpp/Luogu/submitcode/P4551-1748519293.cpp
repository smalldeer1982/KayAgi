#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
struct edge{
	int to,w;
};
int s[maxn],ch[maxn*31][2];
vector<edge>p[maxn];
int n,tot;
void dfs(int x,int f){
	for(int i=0;i<p[x].size();i++){
		int v=p[x][i].to;
		if(v!=f){
			s[v]=s[x]^p[x][i].w;
			dfs(v,x);
		}
	}
}
void insert(int val){
	int x=0;
	for(int i=(1<<30);i;i>>=1){
		int a=bool(val&i);
		if(!ch[x][a]){
			ch[x][a]=++tot;
		}
		x=ch[x][a];
	}
}
int find(int val){
	int ans=0,x=0;
	for(int i=(1<<30);i;i>>=1){
		int a=bool(val&i);
		if(ch[x][!a]){
			ans+=i;
			x=ch[x][!a];
		}
		else{
			x=ch[x][a];
		}
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		p[u].push_back((edge){v,w});
		p[v].push_back((edge){u,w});
	}
	dfs(1,-1);
	for(int i=1;i<=n;i++){
		insert(s[i]);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		ans=max(ans,find(s[i]));
	}
	cout<<ans;
	return 0;
}
