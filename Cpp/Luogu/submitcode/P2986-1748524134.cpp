#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
int n,head[maxn],cnt,dis[maxn];
int c[maxn],all,sum[maxn];
int ans;
struct Edge{
	int nex,to,val;
	Edge(int a=-1,int b=0,int c=0):nex(a),to(b),val(c){}
}edge[maxn<<1];
void add(int u,int v,int w){
	edge[cnt]=Edge(head[u],v,w);
	head[u]=cnt++;
}
void init(){
	cnt=0;
	for(int i=1;i<=n;i++){
		head[i]=-1;
	}
}
void dfs_1(int u,int f){
	ans+=c[u]*dis[u];
	sum[u]=c[u];
	all+=c[u];
	for(int i=head[u];~i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==f){
			continue;
		}
		dis[v]=dis[u]+edge[i].val;
		dfs_1(v,u);
		sum[u]+=sum[v];
	}
}
void dfs_2(int u,int f,int now){
	ans=min(ans,now);
	for(int i=head[u];~i;i=edge[i].nex){
		int v,w;
		v=edge[i].to;
		w=edge[i].val;
		if(v==f){
			continue;	
		}
		dfs_2(v,u,now+w*(all-sum[v]*2));
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	init();
	for(int i=1;i<=n;i++){
		cin>>c[i];
	}
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w);
	}
	ans=0;
	dfs_1(1,0);
	dfs_2(1,0,ans);
	cout<<ans;
	return 0;
}
