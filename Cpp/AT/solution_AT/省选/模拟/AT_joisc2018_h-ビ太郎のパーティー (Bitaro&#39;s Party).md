# ビ太郎のパーティー (Bitaro&#39;s Party)

## 题目描述

## 题目背景

![](https://cdn.luogu.com.cn/upload/image_hosting/cqzxwjey.png)


给定含有 $n$ 个点 $m$ 条单向边的有向无环图，每条边的边权值都为 $1$。

给定 $q$ 次询问，第 $i$ 次询问给定一个点 $T_i$，其中有 $Y_i$ 个点无法前往 $T_i$；假定剩下的点都会前往 $T_i$，询问剩余的点中距离 $T_i$ 最远距离是多少。

## 说明/提示

$1\leqslant{n}\leqslant10^5,0\leqslant{m}\leqslant2\times10^5,1\leqslant{q}\leqslant10^5,(\sum_{i=1}^{q}{Y_i})\leqslant10^5$。

# 题解

## 作者：Purslane (赞：3)

# Solution

为什么题目翻译里面没有说它是有向无环图！我生气了！（因为英文和日文题面里面都提到了水会往势能更低的地方跑因此不会有环。。。）

然后发现它告诉你 $\sum y_i$ 的值，这大概能启示我们用根号分治。

不妨设一个阈值，我们设为 $B$。当 $y_i \ge B$ 的时候，直接暴力求某些点到这个点的最长路，直接拓扑排序的时候进行动态规划即可。当 $y_i < B$，我们发现最多只会禁掉 $B-1$ 个点。那我维护到 $u$ 最长路前 $B$ 大的，中间必有一个没有被禁掉而且会成为答案。这个在拓扑排序的时候归并一下即可（第一个要注意出现相同的点要取较大值，第二个注意的是不用取反图了）。

然后答案当然是 $mB+\frac{\sum y_i}{B}n$。适当选取 $B$ 的值可以做到 $O(\sqrt{mn (\sum y_i)})$。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10,MAXM=400+10;
int n,m,q,len=400,Deg[MAXN],flg[MAXN],deg[MAXN];
vector<int> G[MAXN],g[MAXN]; vector<pair<int,int>> init[MAXN];
vector<pair<int,int>> merge(vector<pair<int,int>> A,vector<pair<int,int>> B) {
	vector<pair<int,int>> ans;
	ffor(i,0,(int)B.size()-1) B[i].first++;
	if(A.empty()) return B;
	if(B.empty()) return A;
	int ida=0,idb=0;
	while(ida<A.size()&&idb<B.size()) {
		if(A[ida]>B[idb]) {
			if(flg[A[ida].second]==0&&ans.size()<len) flg[A[ida].second]=1,ans.push_back(A[ida]);
			ida++;
		}
		else {
			if(flg[B[idb].second]==0&&ans.size()<len) flg[B[idb].second]=1,ans.push_back(B[idb]);
			idb++;
		}
	}
	while(ida<A.size()) {
		if(flg[A[ida].second]==0&&ans.size()<len) flg[A[ida].second]=1,ans.push_back(A[ida]);
		ida++;
	}
	while(idb<B.size()) {
		if(flg[B[idb].second]==0&&ans.size()<len) flg[B[idb].second]=1,ans.push_back(B[idb]);
		idb++;
	}
	for(auto pr:A) flg[pr.second]=0;
	for(auto pr:B) flg[pr.second]=0;
	return ans;
}
int dp[MAXN];
void solve(int u) {
	queue<int> q; int ans=-1;
	ffor(i,1,n) dp[i]=-1,deg[i]=Deg[i];
	dp[u]=0;
	ffor(i,1,n) if(deg[i]==0) q.push(i);
	while(!q.empty()) {
		int u=q.front(); q.pop();
		for(auto v:g[u]) {
			deg[v]--; if(deg[v]==0) q.push(v);
			if(dp[u]>=0) dp[v]=max(dp[v],dp[u]+1);
		}
	}
	ffor(i,1,n) ans=max(ans,dp[i]);
	cout<<ans<<'\n';
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m>>q;
	ffor(i,1,m) {int u,v; cin>>u>>v,G[u].push_back(v),g[v].push_back(u),deg[v]++,Deg[u]++;}
	queue<int> que; ffor(i,1,n) if(deg[i]==0) que.push(i);
	while(!que.empty()) {
		int u=que.front(); que.pop();
		if(init[u].size()<len) init[u].push_back({0,u});
		for(auto v:G[u]) {
			deg[v]--,merge(init[v],init[u]);
			if(deg[v]==0) que.push(v);
		}
	}
	ffor(i,1,q) {
		int u,cnt; cin>>u>>cnt;
		vector<int> id;
		ffor(j,1,cnt) {int v; cin>>v,id.push_back(v),flg[v]=1;}
		if(cnt<=len) {
			int ans=-1;
			for(auto pr:init[u]) if(flg[pr.second]==0&&pr.second!=u) {ans=pr.first;break;}	
			cout<<ans<<'\n';
		}
		else solve(u);
		for(auto v:id) flg[v]=0;
	}
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

考虑根号分治。对于 $y\geq B$，这样的询问至多 $\frac{sum}{B}$ 组，在图上做一遍拓扑排序即可，这样做的复杂度是 $O(\frac{n\times sum}{B})$ 的。对于 $y<B$，考虑维护出每个位置到达他最远的 $B$ 个点，找到最远的不在这 $y$ 个点中的点即可。使用归并排序即可。注意我们需要去重，可以使用一个 map 记录每个位置是否出现过。这样做复杂度是 $O(nB\log B)$。

取合适的 $B$ 即可，这里本人使用的 $B=150$。

```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
using namespace std;
vector<int> vc[200005];
vector<pair<int,int>> nr[200005];
int B=150;
int ok[200005],dist[200005],tag[200005];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
	int n,m,q; cin>>n>>m>>q;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
	}
	for(int i=1;i<=n;i++){
		if(nr[i].size()<B){
			nr[i].push_back(make_pair(0,i));
		}
		for(auto v:vc[i]){
			vector<pair<int,int>> nw;
			int it1=0,it2=0;
			while(((it1!=nr[i].size())||(it2!=nr[v].size()))&&(nw.size()<B)){
				if(it1==nr[i].size()){
					if(tag[nr[v][it2].second]){
						it2++;
						continue; 
					}  tag[nr[v][it2].second]=1;
					nw.push_back(nr[v][it2]);
					it2++;
					continue;
				}
				if(it2==nr[v].size()){
					if(tag[nr[i][it1].second]){
						it1++;
						continue; 
					} tag[nr[i][it1].second]=1;
					auto t=nr[i][it1];
					t.first++;
					nw.push_back(t);
					it1++;
					continue;
				}
				if(nr[i][it1].first+1>nr[v][it2].first){
					if(tag[nr[i][it1].second]){
						it1++; 
						continue; 
					} tag[nr[i][it1].second]=1;
					auto t=nr[i][it1];
					t.first++;
					nw.push_back(t);
					it1++;
					continue;
				}
				else{
					if(tag[nr[v][it2].second]){
						it2++; 
						continue; 
					} tag[nr[v][it2].second]=1;
					nw.push_back(nr[v][it2]);
					it2++;
					continue;
				}
			}
			swap(nw,nr[v]);
			nw.clear();
			for(auto u:nr[v]) tag[u.second]=0;
		}
	}
//	for(int i=1;i<=n;i++,cout<<"\n") for(auto v:nr[i]) cout<<v.first<<" "<<v.second<<"  ";
	while(q--){
		int s,k; cin>>s>>k;
		if(k>=150){
			for(int i=1;i<=n;i++) ok[i]=1,dist[i]=-1;
			while(k--){
				int x; cin>>x; ok[x]=0;
			}
			for(int i=1;i<=n;i++){
				if(ok[i]) dist[i]=max(dist[i],0);
				if(dist[i]>=0){
					for(auto v:vc[i]){
						dist[v]=max(dist[v],dist[i]+1);
					}
				}
			}
			cout<<dist[s]<<"\n";
		}
		else{
			vector<int> nd;
			while(k--){
				int x; cin>>x; nd.push_back(x);
			}
			for(auto v:nd) tag[v]=1;
			int maxv=-1;
			for(auto v:nr[s]){
				if(!tag[v.second]){
					maxv=v.first;
					break;
				}
			}
			for(auto v:nd) tag[v]=0;
			cout<<maxv<<"\n"; 
		}
	} 
	return 0;
} 
```

---

## 作者：DaiRuiChen007 (赞：0)

# JOISC2018H 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_joisc2018_h)

**题目大意**

> 给定一张 $n$ 个点 $m$ 条边的有向图，$q$ 次询问 $x_i$ 并给定 $k_i$ 个点，求 $1\sim n$ 中除这 $x_i$ 个点之外的点到 $x_i$ 的最长距离。
>
> 数据范围：$n,q,k=\sum k_i\le 10^5,m\le 2\times 10^5$，每条边都是从编号小的点连向到编号大的点。

**思路分析**

考虑根号分治，若 $k_i\le \sqrt n$，我们只关心最短的 $\sqrt n$ 条路径，拓扑排序的过程中每次归并排序合并答案，注意同一个点不要被多次统计。

$k_i>\sqrt n$ 的情况暴力处理，这样的询问只有 $\mathcal O\left(\dfrac {k}{\sqrt n}\right)$ 个，$\mathcal O(n+m)$ 暴力求即可。

时间复杂度 $\mathcal O((n+m+k)\sqrt n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5,inf=2e9;
vector <array<int,2>> P[MAXN];
vector <int> G[MAXN];
int dis[MAXN],mark[MAXN],mp[MAXN];
signed main() {
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	int B=sqrt(n);
	for(int i=1;i<=m;++i) {
		int u,v;
		scanf("%d%d",&u,&v);
		G[v].push_back(u);
	}
	fill(mp+1,mp+n+1,-inf);
	for(int u=1;u<=n;++u) {
		P[u].push_back({0,u});
		for(int v:G[u]) for(auto I:P[v]) mp[I[1]]=max(mp[I[1]],I[0]+1);
		for(int v:G[u]) {
			int ed=P[u].size();
			for(auto I:P[v]) if(mp[I[1]]==I[0]+1) {
				P[u].push_back({mp[I[1]],I[1]}),mp[I[1]]=-inf;
			}
			inplace_merge(P[u].begin(),P[u].begin()+ed,P[u].end(),greater<array<int,2>>());
			if((int)P[u].size()>B) P[u].resize(B);
		}
	}
	for(int T=1;T<=q;++T) {
		int t,y;
		scanf("%d%d",&t,&y);
		for(int i=0,j;i<y;++i) scanf("%d",&j),mark[j]=T;
		for(auto p:P[t]) {
			if(mark[p[1]]<T) {
				printf("%d\n",p[0]);
				goto ok;
			}
		}
		if((int)P[t].size()<B) puts("-1");
		else {
			fill(dis+1,dis+t+1,-inf),dis[t]=0;
			for(int u=t;u;--u) {
				for(int v:G[u]) dis[v]=max(dis[v],dis[u]+1);
			}
			int ans=-1;
			for(int i=1;i<=t;++i) if(mark[i]<T) ans=max(ans,dis[i]);
			printf("%d\n",ans<0?-1:ans);	
		}
		ok:;
	}
	return 0;
}
```



---

