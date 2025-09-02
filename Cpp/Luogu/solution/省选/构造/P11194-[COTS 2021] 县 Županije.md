# [COTS 2021] 县 Županije

## 题目背景


译自 [Izborne Pripreme 2021 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2021/) D1T3。$\texttt{2s,0.5G}$。

2025/07/06：加入两组 Hack 数据并进行了重测（贡献者 @[konyakest](https://www.luogu.com.cn/user/482660)），Hack 数据位于 Subtask 0。

## 题目描述



给定 $N$ 个点的树。已经将这 $N$ 个点划分成了 $K$ 个县。

现在你要为每个县确定一个**县城**。设第 $i$ 个点属于的县为 $B_i$，每个县的县城为 $A_1,A_2,\cdots,A_K$（必须两两不同），则下列关系式必须满足：

- $\forall 1\le i\le N$，$\displaystyle \operatorname{dist}(i,A_{B_i})\lt \min_{j=1,j\neq B_i}^K \operatorname{dist}(i,A_j)$。

其中，$\mathrm{dist}(a,b)$ 定义为 $a,b$ 之间简单路径的边数。

也就是说，每个县中的点到它所属的县城距离必须**严格小于**到其它县城的距离。

判断这是否是可以达成的。如果可以的话，需要给出一组符合条件的方案。

## 说明/提示



#### 样例解释

下图是样例 $3$ 的解释。

![](https://cdn.luogu.com.cn/upload/image_hosting/l3nlu402.png)

#### 数据范围

【评分方式】如果你回答对了第一问，可以获得 $40\%$ 的分数。但是需要保证输出格式正确，即，如果只打算回答第一问，也要在第二行输出 $K$ 个不同的 $\in [1,N]$ 的整数。

对于 $100\%$ 的数据，保证 $1\le B_i\le K\le N\le 2\times 10^5$，给出的是一棵树。

| 子任务编号 | $N\le $ |   特殊性质   | 得分 |  
| :--: | :--: | :--: |  :--: |  
| $ 1 $    | $ 20 $    |  无  | $ 10 $   |  
| $ 2 $    | $ 2\, 000 $    |  无 | $ 25 $   |  
| $ 3 $    | $ 2\times 10^5 $    | 有  | $ 30 $   |  
| $ 4 $    | $ 2\times 10^5 $    | 无 | $ 35 $   |  

特殊性质：每个点的度数为 $1$ 或 $3$。

## 样例 #1

### 输入

```
3 2
1 1 2
1 2
2 3```

### 输出

```
DA
2 3```

## 样例 #2

### 输入

```
4 3
1 2 2 3
1 2
2 3
3 4```

### 输出

```
NE```

## 样例 #3

### 输入

```
8 3
1 2 1 2 2 1 3 3
1 2
1 3
2 4
2 5
3 6
3 7
7 8```

### 输出

```
DA
1 2 8```

# 题解

## 作者：DaiRuiChen007 (赞：1)

[Problem Link](https://www.luogu.com.cn/problem/P11194)

**题目大意**

> 给定 $n$ 个点的树，每个点有颜色 $a_1\sim a_n$，对于每种颜色的点，选择一个中心，使得每个点到与其同色的中心的距离严格小于到其他中心的距离，构造方案。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

首先每种颜色的点肯定是要联通的，要不然不和中心再一个连通块里的点肯定不合法。

然后我们把每种颜色缩成一个块，观察两个块的交界点 $(x,y)$，设他们对应的中心为 $c_x,c_y$。

由于 $\mathrm{dis}(x,c_y)=\mathrm{dis}(y,c_y)+1<\mathrm{dis}(x,c_x)$ 且 $\mathrm{dis}(y,c_x)=\mathrm{dis}(x,c_x)+1<\mathrm{dis}(y,c_y)$。

所以 $\mathrm{dis}(x,c_x)=\mathrm{dis}(y,c_y)$，容易发现满足了这个条件后，$x$ 所属块的点到 $c_x$ 的距离一定严格大于到 $c_y$ 的距离。

因此对于每一对相邻的块，我们的中心都满足这个条件，那么这就是一组合法解。

求出合法解可以考虑 dp，即 $f_u$ 表示 $u$ 为该块中心时，其子树内的其他块是否可行。

对于子树内的其他块，设交点为 $(y,x)$，那么必须满足 $\mathrm{dis}(u,t)\in \{\mathrm{dis}(y,t)\mid f_t=1,a_t=a_y\}$。

暴力检验很显然不合法，我们可以对每个块点分治，把 $\mathrm{dis}(u,t)$ 拆成 $d_u+d_t$，然后就能维护每个 $u$ 对几个 $y$ 合法了。

构造方案时从上到下枚举每个中心是否合法。

时间复杂度 $\mathcal O(n\log n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
vector <int> G[MAXN],E[MAXN],T[MAXN],Q[MAXN];
int n,m,a[MAXN],rt[MAXN],dep[MAXN],fa[MAXN];
int dfn[MAXN],dcnt,st[MAXN][20];
int bit(int x) { return 1<<x; }
int cmp(int x,int y) { return dfn[x]<dfn[y]?x:y; }
int dist(int x,int y) {
	if(x==y) return 0;
	int l=min(dfn[x],dfn[y])+1,r=max(dfn[x],dfn[y]),k=__lg(r-l+1);
	return dep[x]+dep[y]-2*dep[cmp(st[l][k],st[r-bit(k)+1][k])];
}
void dfs1(int u,int fz) {
	dfn[u]=++dcnt,st[dcnt][0]=fz;
	fa[u]=fz,dep[u]=dep[fz]+1;
	for(int v:G[u]) if(v^fz) dfs1(v,u);
	if(!fz||a[u]!=a[fz]) {
		if(rt[a[u]]) cout<<"NE\n",exit(0);
		rt[a[u]]=u,E[a[fz]].push_back(a[u]);
	} else T[fz].push_back(u),T[u].push_back(fz);
}
vector <int> F[MAXN],C[MAXN];
bool f[MAXN];
int siz[MAXN],cur[MAXN],dis[MAXN],dp[MAXN],rs[MAXN];
bool vis[MAXN];
void calc(vector<int>&vi,int op) {
	int mx=0;
	for(int u:vi) mx=max(mx,dis[u]);
	for(int u:vi) for(int c:C[u]) {
		for(int i=0;i<(int)F[c].size();++i) if(F[c][i]) {
			if(0<=i-dis[u]&&i-dis[u]<=mx) dp[i-dis[u]]+=op;
		}
	}
	for(int u:vi) rs[u]+=dp[dis[u]];
	for(int i=0;i<=mx;++i) dp[i]=0;
}
void solve(int u) {
	vector <int> all{u}; dis[u]=0;
	for(int v:T[u]) if(!vis[v]) {
		vector <int> sub;
		function<void(int,int)> dfs6=[&](int x,int fz) {
			dis[x]=dis[fz]+1,siz[x]=1;
			all.push_back(x),sub.push_back(x);
			for(int y:T[x]) if(!vis[y]&&y!=fz) dfs6(y,x),siz[x]+=siz[y];
		};
		dfs6(v,u),calc(sub,-1);
	}
	calc(all,1);
}
void dfs4(int u) {
	vis[u]=true,solve(u);
	for(int v:T[u]) if(!vis[v]) {
		int ct=0,tot=siz[v];
		function<void(int,int)> dfs5=[&](int x,int fz) {
			cur[x]=tot-siz[x];
			for(int y:G[x]) if(!vis[y]&&y!=fz) dfs5(y,x),cur[x]=max(cur[x],siz[y]);
			if(!ct||cur[x]<cur[ct]) ct=x;
		};
		dfs5(v,u),dfs4(ct);
	}
}
void dfs2(int u) {
	for(int v:E[u]) dfs2(v),C[fa[rt[v]]].push_back(v);
	dfs4(rt[u]);
	for(int x:Q[u]) if(rs[x]==(int)E[u].size()) {
		int d=dep[x]-dep[rt[u]]; f[x]=true;
		if((int)F[u].size()<=d) F[u].resize(d+1,0);
		F[u][d]=1;
	}
	if(F[u].empty()) cout<<"NE\n",exit(0);
}
int ans[MAXN];
void dfs3(int u,int lim) {
	for(int x:Q[u]) if(f[x]&&(lim==-1||dist(x,rt[u])==lim)) {
		ans[u]=x; break;
	}
	for(int v:E[u]) dfs3(v,dist(ans[u],fa[rt[v]]));
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) cin>>a[i],Q[a[i]].push_back(i);
	for(int i=1,u,v;i<n;++i) cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
	dfs1(1,0);
	for(int k=1;k<20;++k) for(int i=1;i+bit(k)-1<=n;++i) {
		st[i][k]=cmp(st[i][k-1],st[i+bit(k-1)][k-1]);
	}
	dfs2(a[1]),dfs3(a[1],-1),cout<<"DA\n";
	for(int i=1;i<=m;++i) cout<<ans[i]<<" \n"[i==m];
	return 0;
}
```

---

## 作者：Union_of_Britain (赞：0)

下文把县称作颜色，县城称为代表。

首先每个颜色的点集在树上一定是联通的。若不然，不在代表 $u$ 所在连通块的点 $v$ 到 $P:u\to v$ 路径上经过其他颜色的代表一定更近。

同理只需考察相邻颜色的限制。仅考虑两代表为 $x,y$ 的颜色 $c_x,c_y$ 相接的点 $u,v$，得到 $d(u,y)>d(u,x),d(v,x)>d(v,y)$，即 $d(u,x)=d(v,y)$。若满足此条件，显然任意点要跨越 $(u,v)$ 去找代表是严格劣的，因此充要条件是对于所有相邻颜色都满足此限制。

把颜色缩出来的树建出来，直接设 $f_x$ 为 $x$ 为 $c_x$ 代表时其子树是否可能合法。处理颜色 $c$ 的时候考虑其颜色儿子的点的贡献，利用点分树知道该颜色哪些点满足条件即可。

这里点分树是单点加单点查，因此复杂度可以是 $O(n\log n)$，代码里是 $O(n\log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,K,col[maxn],U[maxn],V[maxn];
vector<int> e[maxn];
namespace SLPF{
	int fa[maxn],sze[maxn],son[maxn],dep[maxn],to[maxn];
	void dfs1(int u,int f){
		fa[u]=f,sze[u]=1,dep[u]=dep[f]+1;
		for(auto v:e[u]){
			if(v==f)continue;
			dfs1(v,u);sze[u]+=sze[v];
			if(sze[v]>sze[son[u]])son[u]=v;
		}
	}
	void dfs2(int u,int t){
		to[u]=t;
		if(son[u])dfs2(son[u],t);
		for(auto v:e[u])if(v!=fa[u]&&v!=son[u])dfs2(v,v);
	}
	int LCA(int u,int v){
		while(to[u]!=to[v]){
			if(dep[to[u]]<dep[to[v]])swap(u,v);
			u=fa[to[u]];
		}
		return dep[u]<dep[v]?u:v;
	}
	void predo(){dfs1(1,0);dfs2(1,1);}
	int dis(int u,int v){return dep[u]+dep[v]-dep[LCA(u,v)]*2;}
}
using SLPF::dis,SLPF::predo;
struct BIT{
	vector<int> c;int L;
	void predo(int n){L=n;c.resize(L+1);}
	void add(int p,int v){++p;if(p<=L)c[p]+=v;}
	int Ask(int p){++p;return c[p];}
}T1[maxn],T2[maxn];
int vis[maxn];
int dfs(int u,int fa){
	if(vis[u])return 0;
	int res=1;for(auto v:e[u])if(v!=fa)res+=dfs(v,u);
	return res;
}
int Find(int u,int fa,int tot,int &zx){
	if(vis[u])return 0;
	int sum=1,mx=0;
	for(auto v:e[u]){
		if(v==fa)continue;
		int t=Find(v,u,tot,zx);
		sum+=t,mx=max(mx,t);
	}
	if(max(mx,tot-sum)<=tot/2)zx=u;
	return sum;
}
int cd[maxn],Fa[maxn];
vector<int> pt[maxn],cpt;
void DFS(int u,int fa){
	cpt.push_back(u),cd[u]=cd[fa]+1;
	for(auto v:e[u]){
		if(vis[v]||v==fa)continue;
		DFS(v,u);
	}
}
int build(int u,int f){
	Find(u,0,dfs(u,0),u);vis[u]=1;cd[u]=0;
	for(auto v:e[u]){
		if(vis[v])continue;cpt.clear();
		DFS(v,u);for(auto x:cpt)pt[u].push_back(x);
	}pt[u].push_back(u);
	int mx1=0,mx2=0;
	for(auto x:pt[u]){mx1=max(mx1,dis(x,u));if(f)mx2=max(mx2,dis(x,f));}
	T1[u].predo(mx1+1);if(f)T2[u].predo(mx2+1);
	for(auto v:e[u]){
		if(vis[v])continue;
		int x=build(v,u);Fa[x]=u;
	}
	return u;
}
void ADD(int p,int d,int v){
	T1[p].add(d,v);int u=p;
	while(Fa[p]){int k=dis(Fa[p],u);
		if(d>=k)T1[Fa[p]].add(d-k,v),T2[p].add(d-k,v);
		p=Fa[p];
	}
}
int ask(int p){
	int res=T1[p].Ask(0),u=p;
	while(Fa[p]){int d=dis(Fa[p],u);
		res+=T1[Fa[p]].Ask(d)-T2[p].Ask(d);
		p=Fa[p];
	}
	return res;
}
vector<int> colp[maxn];
vector<array<int,4> > T[maxn];
void dfsc(int u){vis[u]=1;
	colp[col[u]].push_back(u);
	for(auto v:e[u]){
		if(vis[v]||col[v]!=col[u])continue;
		dfsc(v);
	}
}
int f[maxn],res[maxn],dv[maxn];
void calc(int u,int cf){
	for(auto [U,v,pu,pv]:T[u]){
		if(v==cf)continue;
		calc(v,u);
	}int cnt=0;
	for(auto [U,v,pu,pv]:T[u]){
		if(v==cf)continue;++cnt;
		for(auto x:colp[v]){if(!f[x])continue;
			int d=dis(x,pv);if(dv[d])continue;
			ADD(pu,d,1);dv[d]=1;
		}
		for(auto x:colp[v])dv[dis(x,pv)]=0;
	}
	for(auto x:colp[u])if(ask(x)==cnt)f[x]=1;
	for(auto [U,v,pu,pv]:T[u]){
		if(v==cf)continue;++cnt;
		for(auto x:colp[v]){if(!f[x])continue;
			int d=dis(x,pv);if(dv[d])continue;
			ADD(pu,d,-1);dv[d]=1;
		}
		for(auto x:colp[v])dv[dis(x,pv)]=0;
	}
}
void dfsa(int u,int d,int crt,int cf){
	int rx=-1;
	if(d==-1){for(auto x:colp[u])if(f[x])rx=x;}
	else for(auto x:colp[u]){if(f[x]&&dis(crt,x)==d)rx=x;}
	res[u]=rx;if(rx==-1)exit(1);
	for(auto [U,v,pu,pv]:T[u])if(v!=cf)dfsa(v,dis(pu,rx),pv,u);
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n>>K;for(int i=1;i<=n;i++)cin>>col[i];
	for(int i=1,u,v;i<n;i++)cin>>u>>v,e[u].push_back(v),e[v].push_back(u),U[i]=u,V[i]=v;
	for(int i=1;i<=n;i++){
		if(vis[i])continue;
		if(colp[col[i]].size())return cout<<"NE"<<endl,0;
		dfsc(i);
	}memset(vis,0,sizeof(vis));
	predo();build(1,0);
	for(int i=1;i<n;i++)if(col[U[i]]!=col[V[i]])T[col[U[i]]].push_back({col[U[i]],col[V[i]],U[i],V[i]}),T[col[V[i]]].push_back({col[V[i]],col[U[i]],V[i],U[i]});
	calc(1,0);
	bool flg=0;for(auto x:colp[1])if(f[x])flg=1;
	if(!flg)cout<<"NE"<<endl;
	else {
		cout<<"DA"<<endl;
		dfsa(1,-1,-1,0);
		for(int i=1;i<=K;i++)cout<<res[i]<<" ";cout<<endl;
	}
	return 0;
}
```

---

