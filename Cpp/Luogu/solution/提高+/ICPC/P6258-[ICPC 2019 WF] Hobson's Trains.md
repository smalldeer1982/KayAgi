# [ICPC 2019 WF] Hobson's Trains

## 题目描述

Hobson 先生从管理马厩的工作中退休后，投资于一种更加现代的交通方式：火车。

他已经修建了一个包含 $n$ 个火车站的铁路网。然而，他兑现了让乘客摆脱选择困难症的承诺：对于每个站点，乘客只能乘坐火车前往一个站点，别无其它选择。

这样的一段旅程被称作一趟。要注意这是单向的旅程，可能无法再回到出发点。

Hobson 同样也只提供一种车票，允许乘客一次旅行的距离不超过 $k$ 趟。在每个站点的出口会有一个自动读票机（只有一个，所以乘客就不用纠结于要用哪个）。机器会检查从始发站到到达站的距离是否不超过 $k$ 趟。

每个读票机必须编入一个合法始发站列表，但是列表消耗的存储空间越多，机器就越贵。

请帮助 Hobson 先生确定：对于每个站点 $A$，能够在最多 $k$ 趟的旅程中到达 $A$ 的站点个数（包含 $A$ 本身）。

![](https://cdn.luogu.com.cn/upload/image_hosting/1hewt4ho.png)

上图为样例输入 1 对应的示意图。每个圆圈代表了一个站点，圆圈旁边的数字为当 $k=2$ 时需要编入读票机的站点编号。

## 说明/提示

对于全部数据，满足 $2\le n\le 5 \times 10^5,1\le k\le n - 1$，对于任意 $1 \le i \le n$ 都满足 $1 \le d_i \le n$ 且 $d_i\ne i$。

## 样例 #1

### 输入

```
6 2
2
3
4
5
4
3
```

### 输出

```
1
2
4
5
3
1```

## 样例 #2

### 输入

```
5 3
2
3
1
5
4
```

### 输出

```
3
3
3
2
2```

# 题解

## 作者：Meatherm (赞：8)

容易发现，原图是一个基环内向树森林。

对于每一棵基环树，首先把环去掉，考虑树。每一个树节点可以对自己不超过 $k$ 级的祖先造成贡献，可以使用树上差分解决。

然后处理每个点对环的贡献。求出从每个点出发最先到达的环上的点 $id_i$，以及它离环的距离 $len_i$。那么该点对环造成的贡献是一个从点 $id_i$ 开始，长 $k-len_i+1$ 的连续段。仍然可以使用差分解决。

由于要处理的是一个环，会出现 $3 \to 4 \to 5 \to 1 \to 2$ 这类终点编号小于起点编号的情况，所以要加上取模处理。

代码写得比较烂，各位凑合着看看吧。

```cpp
# include <bits/stdc++.h>
# define rr
const int N=500010,INF=0x3f3f3f3f;
struct Edge{
	int to,next;
}edge[N];
int head[N],sum;
int d[N],loop[N],len[N],v[N],id[N];
// d[i] 含义见题面
//loop[i] 点所在环编号
//v[i] 点在环上的编号
int n,k;// 如题意
bool vis[N],ins[N]; // 是否访问过 是否在栈中
int sta[N],size;// 栈
std::vector <int> L[N]; // 环
std::vector <int> diff[N];// 环上差分
int cnt;// 环数量
int ans[N];// 每个店的最终答案
inline int read(void){
	int res,f=1;
	char c;
	while((c=getchar())<'0'||c>'9')
		if(c=='-')f=-1;
	res=c-48;
	while((c=getchar())>='0'&&c<='9')
		res=res*10+c-48;
	return res*f;
}
inline void add(int x,int y){
	edge[++sum].to=y;
	edge[sum].next=head[x];
	head[x]=sum;
	return;
}
void dfs(int i){
	vis[i]=true,ins[i]=true;
	sta[++size]=i;
	if(!vis[d[i]]){
		dfs(d[i]);
	}else if(ins[d[i]]){
		int now=size;
		++cnt;
		while(sta[now]!=d[i]){
			L[cnt].push_back(sta[now]);
			--now; 
		}
		L[cnt].push_back(d[i]);
		std::reverse(L[cnt].begin(),L[cnt].end());
		for(rr int j=0;j<(int)L[cnt].size();++j){
			loop[L[cnt][j]]=cnt;
			v[L[cnt][j]]=j+1;
		}
		diff[cnt].resize((int)L[cnt].size()+2);// 处理环
	}
	ins[i]=false;
	--size;
	return;
}
void Tree_Diff(int i,int x){ // 树上差分
	sta[++size]=i;
	len[i]=len[sta[size-1]]+1;
	id[i]=x;
	++ans[i];
	if((size-1)>k){
		--ans[sta[size-k-1]];
	}
	for(rr int j=head[i];j;j=edge[j].next){
		Tree_Diff(edge[j].to,x);
		ans[i]+=ans[edge[j].to];
	}
	--size;
	return;
}
int main(void){
	n=read(),k=read();
	for(rr int i=1;i<=n;++i){
		add(d[i]=read(),i);
	}
	for(rr int i=1;i<=n;++i){
		if(!vis[i]){
			dfs(i);
		}
	}
	for(rr int i=1;i<=n;++i){
		if(!loop[i]&&loop[d[i]]){
			size=0;
			len[0]=sta[0]=0;
			Tree_Diff(i,d[i]);
		}else if(loop[i]){
			id[i]=i;
		}
	}
	for(rr int i=1;i<=n;++i){
		if(len[i]<=k){
			int l=k-len[i];
			if(l>=(int)L[loop[id[i]]].size()-1){
				++diff[loop[id[i]]][1];
			}else{
				int End=(v[id[i]]+l-1)%(int)L[loop[id[i]]].size()+1;
				if(v[id[i]]<=End){
					++diff[loop[id[i]]][v[id[i]]],--diff[loop[id[i]]][End+1];
				}else{
					++diff[loop[id[i]]][v[id[i]]],++diff[loop[id[i]]][1],--diff[loop[id[i]]][End+1];
				}
			}
		}
	}
	for(rr int i=1;i<=cnt;++i){
		int now=0;
		for(rr int j=0;j<(int)L[i].size();++j){
			now+=diff[i][j+1];
			ans[L[i][j]]+=now;
		}
	}
	for(rr int i=1;i<=n;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
```

---

## 作者：Provicy (赞：2)

$\text{Problem}:$[题目链接](https://codeforces.com/gym/102511/problem/H)

$\text{Solution}:$

每个点出度为 $1$，说明图是一个内向基环树森林。

对于每一个点，将答案分为两部分：到树上的节点 $+$ 到环上的节点。

到树上的节点可以看作是求树上 $k$ 级祖先，并给这段路径上点的权值都加 $1$。比较方便的实现方式是倍增求 $k$ 级祖先 $+$ 树上差分。

对于环上的节点，可以破环为链，利用序列差分实现。

时间复杂度瓶颈在倍增求 $k$ 级祖先上，为 $O(n\log n)$。

$\text{Code}:$

```cpp
#include <bits/stdc++.h>
//#pragma GCC optimize(3)
//#define int long long
#define ri register
#define mk make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define is insert
#define es erase
#define vi vector<int>
#define vpi vector<pair<int,int>>
#define double long double
using namespace std; const int N=500010, M=20;
inline int read()
{
	int s=0, w=1; ri char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48), ch=getchar();
	return s*w;
}
int n,K,deg[N],d[N],dep[N],h[N],book[N],f[N][M],A[N],Ans[N],siz[N];
int head[N],maxE; struct Edge { int nxt,to; }e[N];
inline void Add(int u,int v) { e[++maxE].nxt=head[u]; head[u]=maxE; e[maxE].to=v; }
vector<int> cir[N],B[N]; int bl[N],cnt;
inline void Topo()
{
	queue<int> Q;
	for(ri int i=1;i<=n;i++) if(!deg[i]) Q.push(i);
	while(!Q.empty())
	{
		int x=Q.front(); Q.pop();
		deg[d[x]]--;
		if(!deg[d[x]]) Q.push(d[x]);
	}
	for(ri int i=1;i<=n;i++) if(deg[i]&&!book[i])
	{
		cnt++;
		int x=i;
		while(!siz[cnt] || x!=i)
		{
			bl[x]=cnt;
			h[x]=++siz[cnt], x=d[x];
		}
		cir[cnt].resize(siz[cnt]+1), B[cnt].resize(siz[cnt]*2+1);
		x=i; int now=0;
		while(!book[x])
		{
			book[x]=1, now++;
			cir[cnt][now]=x;
			x=d[x];
		}
	}
}
void DFS1(int x,int fa)
{
	f[x][0]=fa;
	dep[x]=dep[fa]+1;
	for(ri int i=1;i<M;i++) f[x][i]=f[f[x][i-1]][i-1];
	for(ri int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa||book[v]) continue;
		DFS1(v,x);
	}
}
inline int Kth(int x,int k)
{
	for(ri int i=M-1;~i;i--) if((k>>i)&1) x=f[x][i];
	return x;
}
void DFS2(int x,int fa)
{
	for(ri int i=head[x];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa||book[v]) continue;
		DFS2(v,x);
		A[x]+=A[v];
	}
}
inline void Get(int x)
{
	int up=min(K,dep[x]-1);
	int fa=Kth(x,up);
	A[x]++, A[f[fa][0]]--;
	//printf("Tree : %d %d\n",x,f[fa][0]);
	int gg=K-up;
	if(gg<=0) return;
	int z=bl[fa];
	int pos=h[fa]+1;
	//printf("Circle : %d %d\n",pos,min(pos+gg,pos+siz[z]-1));
	B[z][pos]++, B[z][min(pos+gg,pos+siz[z]-1)]--;
}
signed main()
{
	n=read(), K=read();
	for(ri int i=1;i<=n;i++)
	{
		int x=read();
		d[i]=x, deg[x]++;
		Add(x,i);
	}
	Topo();
	for(ri int i=1;i<=n;i++)
	{
		if(deg[i]) DFS1(i,0);
	}
	for(ri int i=1;i<=n;i++) Get(i);
	for(ri int i=1;i<=cnt;i++)
	{
		for(ri int j=1;j<=siz[i]*2;j++) B[i][j]+=B[i][j-1];
		for(ri int j=1;j<=siz[i];j++) Ans[cir[i][j]]+=B[i][j]+B[i][j+siz[i]];
	}
	for(ri int i=1;i<=n;i++)
	{
		if(deg[i]) DFS2(i,0);
	}
	for(ri int i=1;i<=n;i++) printf("%d\n",Ans[i]+A[i]);
	return 0;
}
```



---

## 作者：CarroT5656 (赞：1)

**题目大意**

给你一个 $n$ 个点的内向基环森林。问你对于每个点 $u$，有多少个点 $v$ 可以在 $k$ 步以内到达 $u$。

**解法分析**

考虑一个点 $u$ 能贡献到哪些点。

对于在树上的部分，显然它到它的 $k$ 级祖先都会有贡献，这一部分可以用树上倍增加树上差分做。

然后考虑在环上的部分。显然它的贡献在环上是连续的。这启发你把这个环拿出来，变成一个序列，然后可以在序列上做差分。

时间复杂度 $O(n\log n)$。

要注意图不一定连通。

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define N 500005
#define M 1000005
ll n,k,vis[N],d[N],d1[M],dep[N],anc[N][25],f[N],vis1[N],tp[N],id[N],stp[M],cnt,ft[M],lt[M],to[N],siz[M];
vector<ll> e[N],lst;
queue<ll> Q;
void dfs(ll x,ll fa,ll fr){
	vis1[x]=1;
	f[x]=fa,dep[x]=dep[fa]+1,anc[x][0]=fa,tp[x]=fr;
	for(ll i=1;i<=20;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	ll p=x;
	for(ll i=20;i>=0;i--) if((k>>i)&1) p=anc[p][i];
	if(p==0) p=fr;
	d[x]++,d[f[p]]--;
	for(ll i:e[x]) if(i!=fa&&vis[i]) dfs(i,x,fr);
}
void dfs1(ll x,ll fa){for(ll i:e[x]) if(i!=fa&&vis[i]) dfs1(i,x),d[x]+=d[i];}
void dfs2(ll x,ll fa){
	to[x]=cnt,siz[cnt]++;
	lst.pb(x),vis1[x]=1;
	id[x]=lst.size()-1;
	for(ll i:e[x]) if(i!=fa&&!vis[i]&&!vis1[i]) dfs2(i,x);
}
int main(){
	scanf("%lld%lld",&n,&k);
	for(ll i=1,x;i<=n;i++) scanf("%lld",&x),d[i]++,d[x]++,e[i].pb(x),e[x].pb(i);
	for(ll i=1;i<=n;i++) if(d[i]==1) Q.push(i);
	while(!Q.empty()){
		ll t=Q.front();Q.pop();
		vis[t]=1;
		for(ll i:e[t]) if(--d[i]==1) Q.push(i);
	}
	memset(d,0,sizeof d);
	for(ll i=1;i<=n;i++) if(!vis[i]&&!vis1[i]) dfs(i,0,i),dfs1(i,0);
	memset(vis1,0,sizeof vis1);
	for(ll i=1;i<=n;i++) if(!vis[i]&&!vis1[i]){
		stp[lst.size()]=1,lst.pb(0);
		++cnt;
		ft[cnt]=lst.size();
		dfs2(i,0);
		lt[cnt]=lst.size();
	}
	ll sz=lst.size()-1;
	for(ll i=1;i<=n;i++){
		if(dep[i]<=k){
			ll r=k+1-dep[i];
			d1[id[tp[i]]]--,d1[id[tp[i]]+1]++;
			if(r>=siz[to[tp[i]]]) d1[ft[to[tp[i]]]]++,d1[lt[to[tp[i]]]]--;
			else if(id[tp[i]]+r>=lt[to[tp[i]]]) d1[id[tp[i]]]++,d1[lt[to[tp[i]]]]--,d1[ft[to[tp[i]]]]++,d1[r-(lt[to[tp[i]]]-id[tp[i]])+ft[to[tp[i]]]+1]--;
			else d1[id[tp[i]]]++,d1[id[tp[i]]+r+1]--;
		}
	}
	for(ll i=1;i<=sz;i++){
		d1[i]+=d1[i-1];
		if(stp[i]==1) d1[i]=0;
		d[lst[i]]+=d1[i];
	}
	for(ll i=1;i<=n;i++) printf("%lld\n",d[i]);
	return 0;
}
```

---

## 作者：M1saka16I72 (赞：0)

## 前言

来个绝世唐诗做法，喜提题解区复杂度倒一。

[更可爱的阅读体验](https://misaka16172.github.io/solution-p6258.html)

## 思路

题意即对每个点求内向基环树森林里有多少个点走 $k$ 步以内能到达自己。

树上的点答案是好求的，对于环上的点，首先用 vector 记录其子树内每个深度的点各有多少个，然后考虑对其子树内最大深度进行根号分治（称最大深度 $\geq \sqrt n$ 的点为大点，$\leq \sqrt n$ 的点为小点），来计算环上不同点之间的贡献：

- 大点个数不超过 $\sqrt n$ 个，故大点与其他点之间的贡献可以直接暴力枚举计算，复杂度 $\mathcal{O}(n\sqrt n)$；

- 之后只需要计算小点与小点之间的贡献，考虑断环成链，顺序枚举所有点，每枚举到一个点会使之前的点与当前点距离加上 $i-lst$（$lst$ 为上次枚举到的点的下标），于是相当于维护一个支持全局下标加 $x$、查询下标在 $k$ 之前的前缀和的数据结构，可以使用优先队列进行懒删除，复杂度 $\mathcal{O}(n\sqrt n\log n)$。然而这样做只能计算环上 $i\rightarrow j(i<j)$ 的贡献，于是把这个过程再反向做一遍就可以了。

总复杂度 $\mathcal{O}(n\sqrt n\log n)$，时限比较宽松，可以通过。

## 代码

```cpp
vector<int> tr[N],p[N];
int n,k,fa[N],col[N],deg[N],T,cnt = 0;
bool ring[N];

void topo(){
	for(int i=1;i<=n;i++)	deg[fa[i]]++;
	queue<int> q;
	for(int i=1;i<=n;i++){
		ring[i] = 1;
		if(!deg[i])	q.push(i);
	}
	while(!q.empty()){
		int u = q.front();q.pop();
		ring[u] = 0,deg[fa[u]]--;
		if(!deg[fa[u]])	q.push(fa[u]);
	}
}

void dfs0(int u,int c){
	col[u] = c,p[c].pb_(u);
	for(int v:tr[u]){
		if(col[v])	continue;
		dfs0(v,c);
	}
}

int dep[N],mxd[N],ans[N],rt[N];

deque<int> dq;

void dfs1(int u){
	int F = 0;
	dep[u] = (ring[u]?-1:dep[fa[u]])+1,rt[u] = ring[u]?u:rt[fa[u]],mxd[u] = dep[u];
	ans[u]++;
	if(dq.size()>k)	F = dq.front(),ans[F]--,dq.pop_front();
	dq.pb_(u);
	for(int v:tr[u]){
		if(v==fa[u] || ring[v])	continue;
		dfs1(v),mxd[u] = max(mxd[u],mxd[v]);
	}
	if(F)	dq.push_front(F);
	dq.pob_();
}

void dfs2(int u){
	for(int v:tr[u]){
		if(v==fa[u] || ring[v])	continue;
		dfs2(v),ans[u]+=ans[v];
	}
}

vector<int> c[N],pre[N],nr;
bool vis[N];

void get_ring(int u){
	if(vis[u])	return;
	vis[u] = 1,nr.pb_(u),get_ring(fa[u]);
}

inline int dis(int i,int j){return i<j?j-i:(int)nr.size()-i+j;}

void calc(int i,int j){
	int d = dis(i,j);
	if(d>k)	return;
	ans[nr[j]]+=pre[nr[i]][min(k-d,mxd[nr[i]])];
}

void prt(){
	for(int i=1;i<=n;i++)	cout<<ans[i]<<"\n";
}

struct P{
	int id,d,w;
	inline bool operator <(const P &rhs)const{return w<rhs.w;}
	inline bool operator >(const P &rhs)const{return w>rhs.w;}
};

void solve(int id){
	for(int u:p[id]){
		if(!ring[u])	continue;
		dfs1(u);
	}
	nr = vector<int>();
	for(int u:p[id]){
		if(!ring[u])	continue;
		get_ring(u);
		break;
	}
	for(int u:nr)	dfs2(u);
	if(nr.size()==1)	return;
	for(int u:nr)	c[u].resize(mxd[u]+1);
	for(int u:p[id])	c[rt[u]][dep[u]]++;
	for(int u:nr){
		pre[u].resize(mxd[u]+1);
		for(int i=0;i<=mxd[u];i++)	pre[u][i] = (i?pre[u][i-1]:0)+c[u][i];
	}
	for(int i=0;i<nr.size();i++){
		if(mxd[nr[i]]<T)	continue;
		for(int j=0;j<nr.size();j++){
			if(i==j || mxd[nr[j]]<T)	continue;
			calc(i,j);
		}
		for(int j=0;j<nr.size();j++){
			if(i==j || mxd[nr[j]]>=T)	continue;
			calc(i,j),calc(j,i);
		}
	}
	int now = 0,d = 0,lst = -1;
	priority_queue<P> pq;
	for(int i=0;i<nr.size();i++){
		int u = nr[i];
		if(mxd[u]>=T)	continue;
		if(lst==-1){
			lst = i;
			for(int j=0;j<=mxd[u];j++)	pq.push({u,j,j});
			now+=pre[u][mxd[u]];
			continue;
		}
		d+=dis(lst,i);
		while(!pq.empty() && pq.top().w+d>k)	now-=c[pq.top().id][pq.top().d],pq.pop();
		ans[u]+=now;
		for(int j=0;j<=mxd[u];j++)	pq.push({u,j,j-d});
		now+=pre[u][mxd[u]],lst = i;
	}
	pq = priority_queue<P>();
	priority_queue<P,vector<P>,greater<P>> pq2;
	now = 0,d = nr.size(),lst = -1;
	for(int i=(int)nr.size()-1;i>=0;i--){
		int u = nr[i];
		if(mxd[u]>=T)	continue;
		if(lst==-1){
			lst = i;
			for(int j=0;j<=mxd[u];j++)	pq2.push({u,j,j});
			continue;
		}
		d-=dis(i,lst);
		while(!pq2.empty() && pq2.top().w+d<=k)	now+=c[pq2.top().id][pq2.top().d],pq2.pop();
		ans[u]+=now;
		for(int j=0;j<=mxd[u];j++)	pq2.push({u,j,j+(int)nr.size()-d});
		lst = i;
	}
}

void solve(){
    read(n,k),T = __builtin_sqrt(n);
    for(int i=1;i<=n;i++)	read(fa[i]),tr[fa[i]].pb_(i);
    topo();
	for(int i=1;i<=n;i++){
		if(!ring[i] || col[i])	continue;
		dfs0(i,++cnt);
	}
	for(int i=1;i<=cnt;i++)	solve(i);
	for(int i=1;i<=n;i++)	cout<<ans[i]<<"\n";
}
```

---

## 作者：MYLHF (赞：0)

首先原图是一个基环树**森林**。

首先，树上的问题是简单的：一个点能到达的点是他往上 $k$ 级祖先。

我们把基环树看做树上加了一条边，那么只需要考虑当前这条边带来的贡献。

设这条边为 $u \rightarrow v$ , $dis(x,y)$ 表示树上 $x$ 与 $y$ 的距离。

那么这条边对 $i$ 有贡献分两部分考虑：

1. 可行性判定：$i$ 在 $k-1$ 步内能走到 $u$（$i$ 的 $k$ 级祖先恰好是 $u$ 时，$i$ 不能通过这条边，也就没有贡献）

2. 通过这条边能到达的点：$v$ 往上的 $k-1-dis(i,u)$ 级祖先。然后注意不能把 $lca(v,i)$ 算进答案，因为 $lca(v,i)$ 如果能到达，就已经在 $i$ 的 $k$ 级祖先里计算过一次了。

```cpp
#include<stack>
#include<string>
#include<vector>
#include<bits/stdc++.h>
    typedef long long ll; struct Ostream_fwrite{char*buf,*p1,*pend;Ostream_fwrite(){buf=new char[1000000];p1=buf;pend=buf+1000000;}void out(char ch){if(p1==pend){fwrite(buf,1,1000000,stdout);p1=buf;}*p1++=ch;}void print(int x){static char s[15],*s1;s1=s;if(!x)*s1++='0';if(x<0)out('-'),x=-x;while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);}void println(int x){static char s[15],*s1;s1=s;if(!x)*s1++='0';if(x<0)out('-'),x=-x;while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);out('\n');}void print(ll x){static char s[25],*s1;s1=s;if(!x)*s1++='0';if(x<0)out('-'),x=-x;while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);}void println(ll x){static char s[25],*s1;s1=s;if(!x)*s1++='0';if(x<0)out('-'),x=-x;while(x)*s1++=x%10+'0',x/=10;while(s1--!=s)out(*s1);out('\n');}void print(char*s){while(*s)out(*s++);}void println(char*s){while(*s)out(*s++);out('\n');}void flush(){if(p1!=buf){fwrite(buf,1,p1-buf,stdout);p1=buf;}}~Ostream_fwrite(){flush();}}Ostream;inline void print(int x){Ostream.print(x);}inline void println(int x){Ostream.println(x);}inline void print(char x){Ostream.out(x);}inline void println(char x){Ostream.out(x);Ostream.out('\n');}inline void print(ll x){Ostream.print(x);}inline void println(ll x){Ostream.println(x);}inline void print(char*s){Ostream.print(s);}inline void println(char*s){Ostream.println(s);}inline void println(){Ostream.out('\n');}inline void flush(){Ostream.flush();}
    bool IOerror=0; inline char nc(){static char buf[100000],*p1=buf+100000,*pend=buf+100000;if(p1==pend){p1=buf;pend=buf+fread(buf,1,100000,stdin);if(pend==p1){IOerror=1;return-1;}}return*p1++;}inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}inline void read(int&x){bool sign=0;char ch=nc();x=0;for(;blank(ch);ch=nc());if(IOerror)return;if(ch=='-')sign=1,ch=nc();for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';if(sign)x=-x;}inline void read(ll&x){bool sign=0;char ch=nc();x=0;for(;blank(ch);ch=nc());if(IOerror)return;if(ch=='-')sign=1,ch=nc();for(;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';if(sign)x=-x;}inline void read(char*s){char ch=nc();for(;blank(ch);ch=nc());if(IOerror)return;for(;!blank(ch)&&!IOerror;ch=nc())*s++=ch;*s=0;}inline void read(char&c){for(c=nc();blank(c);c=nc());if(IOerror){c=-1;return;}}
#define PII pair<int,int>
#define de(x) cout<<#x<<": "<<x<<endl
#define rep(i,a,b) for(int i(a);i<=(b);++i)
#define REP(i,a,b) for(int i(a);i>=(b);--i)
using namespace std;

const int N=4e6 +7;
int n,k,a[N],vis[N],f[N][21],dep[N],w[N],cnt[N],fa[N],d[N];
int e[N],ne[N],h[N],block[N],idx,col;
vector<int> g[N],fas[N],cle;
PII bk;

inline int find(int u) { return u==fa[u] ? u : fa[u]=find(fa[u]); }

void add(int x,int y)
{
	e[++idx]=y;
	ne[idx]=h[x];
	h[x]=idx;
}

void get_bk(int u,int pa)
{
	vis[u]=col;
	for(int j(h[u]);j;j=ne[j])
	{
		int i(e[j]);
		if(vis[i]==col) bk={u,i};
		else if(!vis[i]) get_bk(i,u);
	}
}

int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int j=20;~j;--j) if(dep[f[x][j]]>=dep[y]) x=f[x][j];
	if(x==y) return x;
	for(int j=20;~j;--j) if(f[x][j]!=f[y][j]) x=f[x][j],y=f[y][j];
	return f[x][0];
}

void dfs(int u,int pa)
{
	f[u][0]=pa,dep[u]=dep[pa]+1;
	rep(j,1,20) f[u][j]=f[f[u][j-1]][j-1];
	for(int i:g[u])
	{
		if((PII){i,u}==bk) continue;
//		cout<<u<<" "<<i<<endl;
		dfs(i,u);
	}
	
	w[u]++;
	int v(u);
	for(int j=20;~j;--j) if(k>>j&1) v=f[v][j];
	w[(u==pa ? 0 : f[v][0])]--;
	
//	cout<<u<<" "<<f[v][0]<<endl;
}

void ts(int u,int pa)
{
	for(int i:g[u])
	{
		if(i==pa) continue;
		if((PII){i,u}==bk) continue;
		ts(i,u),w[u]+=w[i];
	}
}

signed main()
{
	cin>>n>>k;
	rep(i,1,n) fa[i]=i;
	rep(i,1,n) cin>>a[i],add(i,a[i]),g[a[i]].emplace_back(i),fa[find(i)]=find(a[i]),d[a[i]]=1;
	rep(i,1,n) fas[find(i)].emplace_back(i);
	
	rep(op,1,n) if(!fas[op].empty())
	{
		cle.clear();
		for(int i:fas[op]) cle.emplace_back(i);
		
		for(int i:cle) if(!vis[i]) ++col,get_bk(i,0);
		
		
//		cout<<bk.first<<" -> "<<bk.second<<endl;
		
		int rt=bk.first;
		dfs(rt,0);
		
		int to=bk.second;
		for(int i:cle)
		{
			int fx=k-dep[i];
			int most=dep[to]-dep[lca(to,i)]-1;
			int deps=max(0,min(fx,most)),u=to;
			
			if(fx<0 || most<0) continue;
			
			for(int j=20;~j;--j) if(deps>>j&1) u=f[u][j];
//			cout<<i<<" "<<dep[i]<<" "<<to<<","<<u<<" | "<<deps<<endl;
			w[to]++,w[f[u][0]]--;
		}
		
		ts(rt,0);
	}
	
	rep(i,1,n) cout<<w[i]<<endl;
	
	
	
	return 0;
}
```

---

## 作者：Arson1st (赞：0)

## [[ICPC2019 WF] Hobson's Trains](https://www.luogu.com.cn/problem/P6258) 题解

## 基环树+树上差分

首先，每个点出度都为一，说明图是一个基环内向森林。对于基环树，一种经典的处理办法是把环单独拎出来，让树挂在环上。考虑一棵树的点的贡献：对于从它到其树上的 $k$ 级祖先的链上的点，它都会产生 $1$ 的贡献。而如果它到达根之后还有多余步数可以走的话，它就会进入环中绕行，对经过的点产生 $1$ 的贡献直到步数耗尽或者绕满一圈。

对于这两种贡献我们分开考虑。首先第一种很容易想到树上差分：在本节点标记 $+1$，在 $k+1$ 节点标记 $-1$，最后从叶节点往上求前缀和数组 $ans$ 即可。对于第二种，我们再单独维护一个环上的差分数组 $cnt$。首先断环成链，考虑树上点 $u$ 的贡献区间：$[pos_{rt}+1,pos+k-dep_u]$（$rt$ 已经在树中贡献过了）。当然，长度需要对 $sz_{ring}$ 取 $\min$，最后统一从下标 $0$ 到 $sz_{ring}-1$ 跑一遍求前缀和，累加到 $ans$ 数组中即为答案。

**实现细节**：注意到环上的贡献区间可能存在形如 $[4,5,0,1]$ 的情况，取结尾位置后一位 $-1$ 时可以直接取模。但记得在这种情况时要给 $cnt[0]+1$。对于求 $k$ 级祖先，建议顺便在 DFS 时记录路径的栈，直接找到当前点位置的往前数的第 $k$ 个即可。找环的话这里用的并查集，所以复杂度为 $O(n\alpha(n))$。注意图是森林，可能要记录多个环。

```cpp
#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 5e5+10;

int read() {
	int res; char c;
	while((c=getchar()) < '0'|| c > '9'); res = c-48;
	while((c=getchar()) >= '0' && c <= '9') res = res*10 + c-48;
	return res;
}

int n, m, k, fa[N], rt[N], st[N], ed[N], cnt[N], all;
int stk[N], top, ans[N], dep[N], pos;
vector<int> son[N], ring;
bool vis[N];

int find(int x) {return x == rt[x] ? x : rt[x] = find(rt[x]);}

void dfs(int u) {
	stk[++ top] = u;
	ans[stk[max(0, top - k - 1)]] --; ans[u] ++;
	if (k > dep[u]) {
		int tmp = min((int)ring.size()-1, k-dep[u]);
		cnt[(pos+1) % ring.size()] ++;
		cnt[(pos + tmp + 1) % ring.size()] --;
		if (pos + 1 < ring.size() && pos+tmp+1 >= ring.size()) cnt[0] ++;
	}
	for (int v : son[u]) {
		if (vis[v]) continue;
		dep[v] = dep[u] + 1;
		dfs(v); ans[u] += ans[v];
	}
	top --;
}

int main() {
	n = read(); k = read();
	for (int i = 1; i <= n; i ++) rt[i] = i;
	for (int i = 1; i <= n; i ++) {
		fa[i] = read();
		if (find(i) == find(fa[i])) {
			++ all; st[all] = i; ed[all] = fa[i]; continue;
		}
		rt[find(i)] = find(fa[i]); son[fa[i]].pb(i);
	}
	for (int now = 1; now <= all; now ++) {
		ring.clear(); pos = 0;
		ring.pb(ed[now]); vis[ed[now]] = 1;
		for (int i = fa[ed[now]]; i != ed[now]; i = fa[i])
			ring.pb(i), vis[i] = 1;
		for (int i : ring) dfs(i), pos ++;
		ans[ed[now]] += cnt[0];
		for (int i = 1; i < ring.size(); i ++)
			cnt[i] += cnt[i-1], ans[ring[i]] += cnt[i], cnt[i-1] = 0;
		cnt[ring.size()-1] = 0;
	}
	for (int i = 1; i <= n; i ++) printf("%d\n", ans[i]);
}
```



---

