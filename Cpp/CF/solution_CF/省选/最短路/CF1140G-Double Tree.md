# Double Tree

## 题目描述

给出一个$2N$个点、$3N-2$条边的无向图，边有边权。这张图满足以下性质：

①对于图上的一条边$(u,v)(2 | u , 2 | v)$，一定存在边$(u+1,v+1)$，反之亦然；

②图上存在边$(u,u \oplus 1)$

可以知道编号为偶数的点的导出子图和编号为奇数的点的导出子图都是一棵树，且它们同构。

现在给出$Q$组询问，每组询问询问两个点$x,y$之间的最短路长度。

## 样例 #1

### 输入

```
5
3 6 15 4 8
1 2 5 4
2 3 5 7
1 4 1 5
1 5 2 1
3
1 2
5 6
1 10
```

### 输出

```
3
15
4
```

# 题解

## 作者：yuzhechuan (赞：5)

本题有很多nb的做法，但这里讲的是一个比较菜的纯树形倍增dp的做法

---

### 题解：

假如现在只有一棵树，除了前缀和的做法外，显然可以用倍增维护每个节点向上若干级的代价，答案就是两个询问点各自到lca处的代价和

现在有了两棵树，同样的思路，但由于可以在两棵树之间切换，需要提前预处理出$w[x]$表示$x$到$x'$或$x'$到$x$的最小代价

$w[x]$很简单，因为换树操作只有三种方式：直接换、父亲换、儿子换，所以直接跑两次dfs就可以解决，注意如果绕路的话会增加两条边的代价（两棵树上各一次）

接下来就是维护倍增数组了，设$f[x][i][0/1][0/1]$表示$x$向上跳$2^i$次，起点是否在二号树，终点是否在二号树时的最小代价

转移也很简单，由于中途点要么在一号树要么在二号树，所以直接两种情况取个min即可

预处理完，考虑查询

对于起点终点分别维护两个变量$dp0,dp1$，表示当前跳跃位置是否在二号树上时的最小代价，转移与倍增预处理基本上一模一样

由于起点终点跳到lca时要么都在一号树，要么都在二号树，所以答案就是$\min\{dp0+dp0',dp1+dp1'\}$

---

### 代码：

```cpp
#pragma GCC optimize(3,"Ofast","inline")
#pragma GCC target("avx")
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	char c=getchar();bool f=0;x=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t,class ...A> inline void read(t &x,A &...a){
	read(x);read(a...);
}
template<class t> inline void write(t x){
	if(x<0) putchar('-'),write(-x);
	else{if(x>9) write(x/10);putchar('0'+x%10);}
}

#define int long long

const int N=3e5+5;
int w[N],f[N][20][2][2],fx[2],fy[2],d[N],lg,n,h[N],en,fa[N][20];

struct edge{
	int n,v,w1,w2;
}e[N<<1];

void add(int x,int y,int a,int b){
	e[++en]=(edge){h[x],y,a,b};
	h[x]=en;
}

void dfs1(int x,int fa){
	::fa[x][0]=fa;d[x]=d[fa]+1;
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v,w1=e[i].w1,w2=e[i].w2;
		if(y==fa) continue;
		dfs1(y,x);
		w[x]=min(w[x],w[y]+w1+w2);
	}
}

void dfs2(int x,int fa){
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v,w1=e[i].w1,w2=e[i].w2;
		if(y==fa) continue;
		w[y]=min(w[y],w[x]+w1+w2);
		dfs2(y,x);
	}
}

void dfs(int x,int fa){
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v,w1=e[i].w1,w2=e[i].w2;
		if(y==fa) continue;
		dfs(y,x);
		f[y][0][0][0]=min(w1,w[y]+w2+w[x]);
		f[y][0][0][1]=min(w[y]+w2,w1+w[x]);
		f[y][0][1][0]=min(w[y]+w1,w2+w[x]);
		f[y][0][1][1]=min(w2,w[x]+w1+w[y]);
	}
}

int lca(int x,int y){
	if(d[x]<d[y]) swap(x,y);
	for(int i=lg;~i;i--) if(d[y]<=d[fa[x][i]]) x=fa[x][i];
	if(x==y) return x;
	for(int i=lg;~i;i--) if(fa[x][i]^fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

void doit(){
	int x,y,opx,opy,lca;
	opx=read(x)+1&1;opy=read(y)+1&1;
	x=x+1>>1,y=y+1>>1;lca=::lca(x,y);
	fx[opx]=fy[opy]=0;fx[!opx]=w[x];fy[!opy]=w[y];
	for(int i=lg;~i;i--) if(d[fa[x][i]]>=d[lca]){
		int w0=fx[0],w1=fx[1];
		fx[0]=min(w0+f[x][i][0][0],w1+f[x][i][1][0]);
		fx[1]=min(w0+f[x][i][0][1],w1+f[x][i][1][1]);
		x=fa[x][i];
	}
	for(int i=lg;~i;i--) if(d[fa[y][i]]>=d[lca]){
		int w0=fy[0],w1=fy[1];
		fy[0]=min(w0+f[y][i][0][0],w1+f[y][i][1][0]);
		fy[1]=min(w0+f[y][i][0][1],w1+f[y][i][1][1]);
		y=fa[y][i];
	}
	write(min(fx[0]+fy[0],fx[1]+fy[1]));puts("");
}

signed main(){
	memset(f,31,sizeof f);
	lg=log2(read(n));
	for(int i=1;i<=n;i++) read(w[i]);
	for(int i=1,x,y,a,b;i<n;i++) read(x,y,a,b),add(x,y,a,b),add(y,x,a,b);
	dfs1(1,0);dfs2(1,0);
	dfs(1,0);
	for(int i=1;i<=lg;i++) for(int x=1;x<=n;x++){
		fa[x][i]=fa[fa[x][i-1]][i-1];
		f[x][i][0][0]=min(f[x][i-1][0][0]+f[fa[x][i-1]][i-1][0][0],f[x][i-1][0][1]+f[fa[x][i-1]][i-1][1][0]);
		f[x][i][0][1]=min(f[x][i-1][0][0]+f[fa[x][i-1]][i-1][0][1],f[x][i-1][0][1]+f[fa[x][i-1]][i-1][1][1]);
		f[x][i][1][0]=min(f[x][i-1][1][0]+f[fa[x][i-1]][i-1][0][0],f[x][i-1][1][1]+f[fa[x][i-1]][i-1][1][0]);
		f[x][i][1][1]=min(f[x][i-1][1][0]+f[fa[x][i-1]][i-1][0][1],f[x][i-1][1][1]+f[fa[x][i-1]][i-1][1][1]);
	}
	int t;read(t);
	while(t--) doit();
}
```

---

## 作者：SSerxhs (赞：5)

这题明明和NOIP2018d2t3差不多啊...甚至更简单一些，~~不是应该蓝了吗~~

简化版翻译：有一棵树，在树上走的人有0,1两种形态，两种状态走同一条边的代价不同，每个节点切换形态代价不同，多组询问树上最短距离，每组询问都给定初末形态和节点。

先预处理出每个节点转换形态的最小代价，注意可以走到其他点转换再回来，树dp解决。第一遍dp求出在某个点转换或者到其子树转换再回来，第二遍dp求出在某个点

考虑设 $g[x][i][j]$ 表示转移到 $f[x]$ 后的状态为 $i$ 而在 $x$ 的状态为$j$的情况下 $x->f[x]$ 的代价，则可以通过 $+\max$ 形的矩阵乘法维护，即 $g[x][i][j]->\max(g[x][i][k]+g[f[x][k][j])$，相当于枚举 $f[x]$ 的状态。考虑用带权并查集维护，用tarjan lca方法把询问挂到lca上，然后枚举lca状态即可。注意特判各种边界，总复杂度$O(n+q)$，比倍增和ddp不知快到哪里去了

```cpp
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N=3e5+2,M=6e5+2,O=1.2e6+2;
ll len1[M],len2[M],v[N],g[N][4],ans[M];
ll lx,ly;
int lj[M],nxt[M],fir[N],f[N],qlj[O],qnxt[O],qfir[N],xw[O][3];
int flj[M],fnxt[M],ffir[N];
int n,q,i,x,y,c,bs,qs,fs;
bool ed[N];
inline void read(int &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
inline void read(ll &x)
{
	c=getchar();
	while ((c<48)||(c>57)) c=getchar();
	x=c^48;c=getchar();
	while ((c>=48)&&(c<=57))
	{
		x=x*10+(c^48);
		c=getchar();
	}
}
inline void add()
{
	lj[++bs]=y;
	len1[bs]=lx;
	len2[bs]=ly;
	nxt[bs]=fir[x];
	fir[x]=bs;
	lj[++bs]=x;
	len1[bs]=lx;
	len2[bs]=ly;
	nxt[bs]=fir[y];
	fir[y]=bs;
}
inline void fadd(int x,int y)
{
	flj[++fs]=y;
	fnxt[fs]=ffir[x];
	ffir[x]=fs;
}
inline void qadd(int x,int y,int i)
{
	qlj[++qs]=i;
	qnxt[qs]=qfir[x];
	qfir[x]=qs;
}
void dfs1(int x)
{
	ed[x]=1;
	for (int i=fir[x];i;i=nxt[i]) if (!ed[lj[i]])
	{
		dfs1(lj[i]);
		v[x]=min(v[x],v[lj[i]]+len1[i]+len2[i]);
	}
	ed[x]=0;
}
void dfs2(int x)
{
	ed[x]=1;
	for (int i=fir[x];i;i=nxt[i]) if (!ed[lj[i]])
	{
		v[lj[i]]=min(v[lj[i]],v[x]+len1[i]+len2[i]);
		dfs2(lj[i]);
	}
	ed[x]=0;
}
void dfs3(int x)
{
	ed[x]=1;
	for (int i=fir[x];i;i=nxt[i]) if (!ed[lj[i]])
	{
		g[lj[i]][0]=min(len2[i],v[x]+v[lj[i]]+len1[i]);
		g[lj[i]][1]=min(len2[i]+v[lj[i]],len1[i]+v[x]);
		g[lj[i]][2]=min(len1[i]+v[lj[i]],len2[i]+v[x]);
		g[lj[i]][3]=min(len1[i],v[x]+v[lj[i]]+len2[i]);
		dfs3(lj[i]);
	}
	ed[x]=0;
}
void getf(register int x)
{
	if (f[f[x]]==f[x]) return;
	getf(f[x]);
	g[0][0]=min(g[x][0]+g[f[x]][0],g[x][2]+g[f[x]][1]);
	g[0][1]=min(g[x][1]+g[f[x]][0],g[x][3]+g[f[x]][1]);
	g[0][2]=min(g[x][0]+g[f[x]][2],g[x][2]+g[f[x]][3]);
	g[0][3]=min(g[x][1]+g[f[x]][2],g[x][3]+g[f[x]][3]);
	memcpy(g[x],g[0],32);
	f[x]=f[f[x]];
}
void dfs4(int x)
{
	ed[x]=1;int i;
	for (i=qfir[x];i;i=qnxt[i]) if (ed[y=xw[qlj[i]][2]])
	{
		getf(y);
		fadd(f[y],qlj[i]);
	}
	for (i=fir[x];i;i=nxt[i]) if (!ed[lj[i]])
	{
		dfs4(lj[i]);
		f[lj[i]]=x;
	}
	for (i=ffir[x];i;i=fnxt[i])
	{
		y=flj[i];
		if (y>q) c=y-q; else c=y;
		if (xw[y][2]!=x)
		{
			qs=xw[y][0]>>1&1;bs=xw[y][0]&1;
			getf(xw[y][1]);getf(xw[y][2]);
			ans[c]=min(g[xw[y][1]][bs]+g[xw[y][2]][qs],g[xw[y][1]][bs|2]+g[xw[y][2]][qs|2]);
		}
		else {getf(xw[y][1]);ans[c]=g[xw[y][1]][xw[y][0]];}
	}
}
int main()
{
	read(n);
	for (i=1;i<=n;i++) read(v[i]);
	for (i=1;i<n;i++)
	{
		read(x);read(y);read(lx);read(ly);
		add();f[i]=i;
	}dfs1(1);dfs2(1);dfs3(1);
	read(q);
	for (i=1;i<=q;i++)
	{
		read(x);read(y);
		if (x+1>>1==y+1>>1) {if (x!=y) ans[i]=v[x+1>>1];continue;}
		xw[i][0]=(x&1)|(y&1)<<1;
		xw[i+q][0]=(y&1)|(x&1)<<1;
		qadd(xw[i][1]=xw[i+q][2]=x=x+1>>1,xw[i][2]=xw[i+q][1]=y=y+1>>1,i);
		qadd(y,x,i+q);
	}
	dfs4(1);
	for (i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
```


---

## 作者：Aria_Math (赞：3)

模拟赛三道题有两道题做法和题解不一样捏。~~然后发现就是 CF 官方做法。~~

提供一个无脑做法。

一般图上的两两最短路是难做的，特殊图上的两两最短路一般处理方法是分治。具体的，[网格图上最短路](https://www.luogu.com.cn/problem/P3350) 可以对平面分治，而这道题可以点分治。

因为两棵树的形态是相同的，所以我们可以每次选出第一颗树的重心 $rt$，假如 $(u,v)$ 的最短路经过 $rt$，则答案为 $dis(u,rt)+dis(v,rt)$，这可以从 $rt$ 出发跑 Dijkstra 得到。同理要处理经过 $rt+1$ 的情况。否则，因为既不能经过 $rt$ 也不能经过 $rt+1$，$(u,v)$ 的最短路就在更小的联通块里。点分治处理即可。时间复杂度 $\mathcal{O}(n\log^2n)$。

$\mathcal{Code}$
```cpp
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<ll, int>;
const int N = 6e5 + 10;
struct Edge {
	int v; ll w;
};
int n, m, rt, mx, siz[N], vis[N], col[N], inq[N];
ll dis1[N], dis2[N], ans[N];
vector<int> G[N];
vector<Edge> E[N];
vector<pair<int, int>> Q[N];
void Add(int u, int v, ll w) {
	E[u].push_back({v, w});
	E[v].push_back({u, w});
}
void Solve(int u, int ver) {
	rt = 0, mx = 1e9;
	auto DfsRt = [](auto DfsRt, int u, int fat, int ver) -> void {
		siz[u] = 1; int now = 0;
		for(int v : G[u]) if(v != fat && !vis[v])
			DfsRt(DfsRt, v, u, ver), siz[u] += siz[v], now = max(now, siz[v]);
		now = max(now, ver - siz[u]);
		if(mx > now) mx = now, rt = u;
	}; DfsRt(DfsRt, u, 0, ver);
	vector<int> seq;
	auto Dfs = [&](auto Dfs, int u, int fat) -> void {
		siz[u] = 1; col[u] = col[u + n] = 1; seq.push_back(u);
		for(int v : G[u]) if(v != fat && !vis[v])
			Dfs(Dfs, v, u), siz[u] += siz[v];
	}; Dfs(Dfs, rt, 0);
	auto Dijkstra = [&](int S, ll *dis) {
		for(int u : seq) dis[u] = dis[u + n] = 1e18, inq[u] = inq[u + n] = 0;
		priority_queue<PII, vector<PII>, greater<PII>> q;
		q.push({dis[S] = 0, S});
		while(!q.empty()) {
			int u = q.top().second; q.pop();
			if(inq[u]) continue; inq[u] = 1;
			for(auto [v, w] : E[u]) if(col[v])
				if(dis[v] > dis[u] + w) q.push({dis[v] = dis[u] + w, v});
		}
		for(int u : seq) inq[u] = inq[u + n] = 0;
	};
	Dijkstra(rt, dis1); Dijkstra(rt + n, dis2);
	for(int v : seq) for(auto [w, id] : Q[v]) if(col[w])
		ans[id] = min(ans[id], min(dis1[v] + dis1[w], dis2[v] + dis2[w]));
	for(int v : seq) for(auto [w, id] : Q[v + n]) if(col[w])
		ans[id] = min(ans[id], min(dis1[v + n] + dis1[w], dis2[v + n] + dis2[w]));
	int _rt = rt; vis[rt] = 1;
	for(int v : seq) col[v] = col[v + n] = 0;
	for(int v : G[_rt]) if(!vis[v]) 
		Solve(v, siz[v]);
}
int main() {
	//freopen("data.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	cin.tie(0)->sync_with_stdio(0);
	cin >> n; ll w;
	for(int i = 1; i <= n; ++i)
		cin >> w, Add(i, i + n, w);
	for(int i = 1; i < n; ++i) {
		int x, y; ll w1, w2;
		cin >> x >> y >> w1 >> w2;
		Add(x, y, w1), Add(x + n, y + n, w2);
		G[x].push_back(y), G[y].push_back(x);
	}
	cin >> m;
	for(int i = 1; i <= m; ++i) {
		int u, v; cin >> u >> v;
		if(u & 1) u = u + 1 >> 1;
		else u = (u >> 1) + n;
		if(v & 1) v = v + 1 >> 1;
		else v = (v >> 1) + n;
		Q[u].push_back({v, i});
		Q[v].push_back({u, i});
	}
	memset(ans, 0x3f, sizeof(ans));
	Solve(1, n);
	for(int i = 1; i <= m; ++i)
		printf("%lld\n", ans[i]);
	return 0;
}
```

---

## 作者：Arghariza (赞：2)

今天 NOIP 模拟赛 T2。

应某个人要求写的题解。

题目大意就是给定一棵带边权的树 $T$，存在一棵形态完全相同的树 $T'$（边权不同），然后 $T$ 和 $T'$ 对应节点连带权的边，然后 $Q$ 次询问，每次询问两个点 $u(u')$ 和 $v(v')$ 的最短路 $d_{u(u'),v(v')}$。

每个点有两个状态 $u/u'$，考虑如何让 $u$ 从一个状态魂穿到另一个状态，即 $d_{u,u'}$。

考虑链的情况，不难发现只有两种情况：$u$ 走到 $f_u$（$u$ 的父亲），然后 $f_u$ 魂穿到 $f'_u$，然后从 $f'_u$ 走到 $u'$；或者是 $u$ 走到 $v\in \text{subtree}(u)$，然后 $v$ 魂穿到 $v'$，然后从 $v'$ 走到 $u$。其中从 $u$ 到 $v$ 和从 $v'$ 到 $u'$ 都是不会改变状态的。

然后照搬上树，发现也只有这两种情况，令 $w_{u,v}$ 为 $u$ 到 $v$ **不改变状态**的距离，$g_u$ 为 $u$ 连 $u'$ 那条边的边权：

- 走 $f_u$：$d_{u,u'}\gets w_{u,f_{u}}+d_{f_{u},f'_{u}}+w_{f'_u,u'}$，这部分按深度从上到下计算 $d$ 值即可。
- 走子树：$d_{u,u'}\gets \min\limits_{v\in \text{subtree(u)}}w_{u,v}+g_v+w_{v',u'}$，拆开后维护 $u$ 子树的 $\min\limits_{v\in \text{subtree}(u)}g_v+dis_v+dis_{v'}$ 即可，$dis_u$ 为 $u$ 走到对应 $T/T'$ 的根的不改变状态的路径长度。

然后就能很简单地求出 $d_{u,u'}$ 这东西，然后考虑 $u$ 到 $v$ 的最短路一定经过树上 $u\to \text{lca}(u,v)\to v$ 路径上的点。只需计算出所有 $u/u'$ 走到 $f_u/f'_u$ 的最短路即可通过简单的动态 dp 求出 $u$ 到 $v$ 的最短路。

类似刚才的分析，可以得出 $u/u'\to f_u/f'_u$ 的最短路一定是在某个 $u\to u'\to f'_u\to f_u\to u$ 环上的。于是任意两点之间的距离就是好求的了。

具体地，以 $u\to f'_u$ 为例：

- 走 $u\to f_u\to f'_u$ 这条路径，长度为 $w_{u,f_u}+d_{f_u,f'_u}$。
- 走 $u\to u'\to f'_u$ 这条路径，长度为 $d_{u,u'}+w_{u',f'_u}$。

两者取 $\min$ 即可，其它也是类似的。

然后就做完了，复杂度 $O(k^3(n+q)\log n)$（倍增）。

```cpp
// Problem: Double Tree
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF1140G
// Memory Limit: 1000 MB
// Time Limit: 10000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#define int long long
using namespace std;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define mt make_tuple
    #define mp make_pair
    #define fi first
    #define se second
    #define pc putchar
    #define pb emplace_back
    #define ins insert
    #define era erase
    typedef tuple<int, int, int> tu3;
    typedef pair<int, int> pi;
    inline int rd() {
        char ch = gh();
        int x = 0;
        bool t = 0;
        while (ch < '0' || ch > '9') t |= ch == '-', ch = gh();
        while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch ^ 48), ch = gh();
        return t ? ~(x - 1) : x;
    }
    inline void wr(int x) {
        if (x < 0) x = ~(x - 1), putchar('-');
        if (x > 9) wr(x / 10);
        putchar(x % 10 + '0');
    }
}
using namespace vbzIO;

const int N = 3e5 + 300;
const int inf = 1e18;

int n, q, w[N], d[N], dep[N][2], wfa[N][2], fat[N][20], dp[N];// d : u -> u'
int mnw[N], lg[N];// min w v + dep v + dep v'
vector<tu3> g[N];

#define gt(x, y) get<y>(x)

struct mat {
	int s[2][2];
	mat () { s[0][0] = s[0][1] = s[1][0] = s[1][1] = inf; }
	mat operator * (const mat &rhs) const {
		mat res;
		for (int i = 0; i <= 1; i++)
			for (int j = 0; j <= 1; j++)
				for (int k = 0; k <= 1; k++)
					res.s[i][j] = min(res.s[i][j], s[i][k] + rhs.s[k][j]);
		return res;
	}
} f[N][20];// u / u' -> fa / fa'

void dfs1(int u, int fa) {
	dp[u] = dp[fa] + 1;
	dep[u][0] = dep[fa][0] + wfa[u][0];
	dep[u][1] = dep[fa][1] + wfa[u][1];
	mnw[u] = w[u] + dep[u][0] + dep[u][1];
	for (tu3 p : g[u]) {
		int v = gt(p, 0), w0 = gt(p, 1), w1 = gt(p, 2);
		if (v == fa) continue;
		wfa[v][0] = w0, wfa[v][1] = w1, dfs1(v, u);
		mnw[u] = min(mnw[u], mnw[v]);
	}
}

void dfs2(int u, int fa) {
	d[u] = mnw[u] - dep[u][0] - dep[u][1], fat[u][0] = fa;
	if (fa) {
		d[u] = min(d[u], d[fa] + wfa[u][0] + wfa[u][1]);
		f[u][0].s[0][0] = min(wfa[u][0], wfa[u][1] + d[u] + d[fa]);
		f[u][0].s[0][1] = min(d[u] + wfa[u][1], wfa[u][0] + d[fa]);
		f[u][0].s[1][0] = min(d[u] + wfa[u][0], wfa[u][1] + d[fa]);
		f[u][0].s[1][1] = min(wfa[u][1], wfa[u][0] + d[u] + d[fa]);
	}
	for (int i = 1; (1 << i) <= n; i++) 
		fat[u][i] = fat[fat[u][i - 1]][i - 1];
	for (int i = 1; (1 << i) <= n; i++)
		if (fat[u][i]) f[u][i] = f[u][i - 1] * f[fat[u][i - 1]][i - 1];
	for (tu3 p : g[u]) {
		int v = gt(p, 0);
		if (v == fa) continue;
		dfs2(v, u);
	}
}



int lca(int u, int v) {
	if (dp[u] < dp[v]) swap(u, v);
	while (dp[u] > dp[v])
		u = fat[u][lg[dp[u] - dp[v]] - 1];
	if (u == v) return u;
	for (int k = lg[dp[u]] - 1; ~k; k--)
		if (fat[u][k] != fat[v][k])
			u = fat[u][k], v = fat[v][k];
	return fat[u][0];
}

mat qry(int u, int pr, int op) {
	mat res;
	res.s[0][op] = 0;
	res.s[0][op ^ 1] = d[u];
	if (u == pr) return res;
	for (int i = 19; ~i; i--) 
		if (dp[fat[u][i]] >= dp[pr])
			res = res * f[u][i], u = fat[u][i];
	return res;
}

signed main() {
	n = rd();
	for (int i = 1; i <= n; i++)
		lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);
	for (int i = 1; i <= n; i++) w[i] = rd();
	for (int i = 1, u, v, w1, w2; i <= n - 1; i++) {
		u = rd(), v = rd(), w1 = rd(), w2 = rd();
		g[u].pb(mt(v, w1, w2)), g[v].pb(mt(u, w1, w2));
	}
	dfs1(1, 0), dfs2(1, 0);
	q = rd();
	while (q--) {
		int u = rd(), v = rd(), op0, op1;
		op0 = (u & 1) ? 0 : 1;
		op1 = (v & 1) ? 0 : 1;
		u = (u + 1) / 2, v = (v + 1) / 2;
		int lc = lca(u, v);
		mat q1 = qry(u, lc, op0), q2 = qry(v, lc, op1);
		wr(min(q1.s[0][0] + q2.s[0][0], q1.s[0][1] + q2.s[0][1])), pc('\n');
	}
    return 0;
}
```

---

## 作者：netlify (赞：0)

模拟赛出了树上倍增，所以想到来补一篇题解。

### 题意

两颗同构的树，对应的节点间连边，边有正边权，回答 $q$ 次询问，每次询问两节点 $u,v$ 之间的最短路。

### 思路

约定记号：若 $u$ 是树 $1$ 上某点，则 $u'$ 为其在树 2 上的对应点。

假如现在只有一棵树，那么倍增处理树上路径即可。

现在有两棵树，切换树可能有三种情况：跳到父亲换，跳到子树换，直接换。设 $w[u]$ 为在 $u$ 点换树的代价。

首先有 $w[u]$ 在 $u$ 点直接换树的代价。现在考虑跳到父亲或儿子换树的可能性。

![](https://cdn.luogu.com.cn/upload/image_hosting/7d6g2wqv.png)

设 $v$ 为 $u$ 儿子，$w_1,w_2$ 为 $(u,v)$ 在两棵树中的边权，有： 
$$
w[u]=\min(w[u],w[v]+w_1+w_2)
$$
和
$$
w[v]=\min(w[v],w[u]+w_1+w_2)
$$
据此进行两次 dfs 求出 $w[u]$。

然后是倍增求 lca，与树上路径相似，设 $dp[i][j][0/1][0/1]$ 为 $i$ 点往上跳 $2^j$ 步，起点是/否在 $1$ 号树，终点是否在 $1$ 号树的最小权值。

考虑先求初始状态，还是上面的那个图。

从 $v$ 到 $u$ 有两种情况，直接走 $(u,v)$ 间的连边 $w_1$，或者换树走，$v\rightarrow v'\rightarrow u'\rightarrow u$，权值 $w[v]+w[u]+w_2$。其它情况同理。

所以有转移：
$$
\operatorname{dp}[v][0][0][0]=\min(w1,w[v]+w_2+w[u])
$$

$$
\operatorname{dp}[v][0][0][1]=\min(w_1+w[u],w[v]+w_2)
$$

$$
\operatorname{dp}[v][0][1][0]=\min(w_1+w[v],w[u]+w_2)
$$

$$
\operatorname{dp}[v][0][1][1]=\min(w_2,w[v]+w_1+w[u])
$$

初始状态完考虑倍增。倍增要复杂一些，建议配合图来理解。

求出 $\operatorname{dp}[i][j][0/1][0/1]$ 需要分两步跳，首先跳到 $\operatorname{fa}[i][j-1]$ ，然后跳到 $\operatorname{fa}[\operatorname{fa}[i][j-1]][j-1]$ 即 $\operatorname{fa}[i][j]$。

下面设 $a$ 点为 $\operatorname{fa}[i][j-1]$，$b$ 点为 $\operatorname{fa}[i][j]$，以 $i$ 点转移到 $b$ 点为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/o6m61ui9.png)

显然有 $i\rightarrow a\rightarrow b$ 和 $i\rightarrow a'\rightarrow b$ 两种走法，得到转移： 
$$
\operatorname{dp}[u][i][0][0]=\min(\operatorname{dp}[u][i-1][0][0]+\operatorname{dp}[fa[u][i-1]][i-1][0][0],\operatorname{dp}[u][i-1][0][1]+\operatorname{dp}[fa[u][i-1]][i-1][1][0])
$$
其余同理，得到：
$$
\operatorname{dp}[u][i][0][1]=\min(\operatorname{dp}[u][i-1][0][0]+\operatorname{dp}[fa[u][i-1]][i-1][0][1],\operatorname{dp}[u][i-1][0][1]+\operatorname{dp}[fa[u][i-1]][i-1][1][1])
$$

$$
\operatorname{dp}[u][i][1][0]=\min(\operatorname{dp}[u][i-1][1][0]+dp[fa[u][i-1]][i-1][0][0],\operatorname{dp}[u][i-1][1][1]+\operatorname{dp}[fa[u][i-1]][i-1][1][0])
$$

$$
\operatorname{dp}[u][i][1][1]=\min(\operatorname{dp}[u][i-1][1][0]+\operatorname{dp}[fa[u][i-1]][i-1][0][1],\operatorname{dp}[u][i-1][1][1]+\operatorname{dp}[fa[u][i-1]][i-1][1][1])
$$

至此预处理完成。考虑询问。

先把询问的点编号转换成我们树上的编号，即 $u\leftarrow \left \lfloor \frac{u+1}{2}  \right \rfloor  $，$ v\leftarrow \left \lfloor \frac{v+1}{2}  \right \rfloor $，并判断两点所在树的编号。

肯定先求 lca，求完后设 $\operatorname{dpu}[0/1]$ 表示 $u$ 跳到 lca 时在树 1/2 的代价，$\operatorname{dpv}[0/1]$ 同理。

所以倍增跳即可。

答案即为 $\min(dpu[0]+dpv[0],dpu[1]+dpv[1])$。

代码~~轻微~~重度压行，仅供参考。

````cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int _=3e5+5,inf=0x3f3f3f3f3f3f3f3f;
int n,w[_];
struct node{int to,w1,w2;};
vector<node>G[_];
void dfs1(int u,int fa){
    for(auto [v,w1,w2]:G[u])if(v!=fa)dfs1(v,u),w[u]=min(w[u],w[v]+w1+w2);
}
void dfs2(int u,int fa){
    for(auto [v,w1,w2]:G[u])if(v!=fa)w[v]=min(w[v],w[u]+w1+w2),dfs2(v,u);
}
int fa[_][20],dep[_],dp[_][20][2][2];
void dfs3(int u,int Fa){
    fa[u][0]=Fa,dep[u]=dep[Fa]+1;
    for(auto [v,w1,w2]:G[u])if(v!=Fa)
            dp[v][0][0][0]=min(w1,w[v]+w2+w[u]),
            dp[v][0][0][1]=min(w1+w[u],w[v]+w2),
            dp[v][0][1][0]=min(w1+w[v],w[u]+w2),
            dp[v][0][1][1]=min(w2,w[v]+w1+w[u]),
            dfs3(v,u);
}
int lca(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    for(int i=log2(n);i>=0;i--)dep[v]<=dep[fa[u][i]]&&(u=fa[u][i]);
    if(u==v)return u;
    for(int i=log2(n);i>=0;i--)fa[u][i]^fa[v][i]&&(u=fa[u][i],v=fa[v][i]);
    return fa[u][0];
}
signed main(){
    ios::sync_with_stdio(false);
    memset(dp,31,sizeof(dp));
    cin>>n;
    for(int i=1;i<=n;i++)cin>>w[i];
    for(int u,v,w1,w2,i=1;i<n;i++)cin>>u>>v>>w1>>w2,G[u].emplace_back((node){v,w1,w2}),G[v].emplace_back((node){u,w1,w2});
    dfs1(1,0),dfs2(1,0),dfs3(1,0);
    for(int u=1;u<=n;u++){
        for(int i=1;i<=log2(n);i++){
            fa[u][i]=fa[fa[u][i-1]][i-1];
            dp[u][i][0][0]=min(dp[u][i-1][0][0]+dp[fa[u][i-1]][i-1][0][0],dp[u][i-1][0][1]+dp[fa[u][i-1]][i-1][1][0]);
            dp[u][i][0][1]=min(dp[u][i-1][0][0]+dp[fa[u][i-1]][i-1][0][1],dp[u][i-1][0][1]+dp[fa[u][i-1]][i-1][1][1]);
            dp[u][i][1][0]=min(dp[u][i-1][1][0]+dp[fa[u][i-1]][i-1][0][0],dp[u][i-1][1][1]+dp[fa[u][i-1]][i-1][1][0]);
            dp[u][i][1][1]=min(dp[u][i-1][1][0]+dp[fa[u][i-1]][i-1][0][1],dp[u][i-1][1][1]+dp[fa[u][i-1]][i-1][1][1]);
        }
    }
    int q;
    cin>>q;
    for(int u,v;q--;){
        cin>>u>>v;
        int tu=(u+1)&1,tv=(v+1)&1;
        u=u+1>>1,v=v+1>>1;
        int Lca=lca(u,v),dpu[2],dpv[2];
        dpu[tu]=0,dpu[!tu]=w[u],dpv[tv]=0,dpv[!tv]=w[v];
        for(int i=log2(n);i>=0;i--)
            if(dep[fa[u][i]]>=dep[Lca]){
                int dpu0=dpu[0],dpu1=dpu[1];
                dpu[0]=min(dpu0+dp[u][i][0][0],dpu1+dp[u][i][1][0]);
                dpu[1]=min(dpu1+dp[u][i][1][1],dpu0+dp[u][i][0][1]);
                u=fa[u][i];
            }
        for(int i=log2(n);i>=0;i--)
            if(dep[fa[v][i]]>=dep[Lca]){
                int dpv0=dpv[0],dpv1=dpv[1];
                dpv[0]=min(dpv0+dp[v][i][0][0],dpv1+dp[v][i][1][0]);
                dpv[1]=min(dpv1+dp[v][i][1][1],dpv0+dp[v][i][0][1]);
                v=fa[v][i];
            }
        cout<<min(dpu[0]+dpv[0],dpu[1]+dpv[1])<<"\n";
    }
    return 0;
}
````

upd 2024/12/4 : 修改 LaTex

---

## 作者：shinkuu (赞：0)

居然差一点场切了。

首先可以将两棵树上对应的点看作一个点的两个不同状态考虑一个类似最短路的东西：设 $dis_{i,j,0/1,0/1}$ 为树上 $0/1$ 状态的 $i$ 点到 $0/1$ 状态的最短路。考虑怎样维护这个值。

由于是树上路径问题，容易发现设 $k$ 为树上 $(i,j)$ 路径上任意一个点,都有 $\min(dis_{i,k,p,0}+dis_{k,j,0,q},dis_{i,k,p,1}+dis_{k,j,1,q})=dis_{i,j,p,q}$。利用这个性质，容易发现，可以通过树剖加线段树维护 $dis$。

具体来说，将每条边对应到点上，维护经过一段连续的 dfn 序所对应的边的最短路径。线段树每段区间拆成两段后，pushup 枚举中间状态，用一个类似 floyd 更新的方式得到这一段的答案。其他都是基本操作。并且注意有些地方要翻链。

除此之外，还有可能最优路径是从起点到路径外的一点，再回到中点。为了应对这种情况，可以预处理的时候更新一下两棵树对应点连的边的边权，通过两次 dp 找到最优值。

code：

```cpp
int n,m,q;
ll c[N],w[N][2];
int fa[N],dep[N],siz[N],son[N];
int cur,top[N],dfn[N],rk[N];
int tot,head[N];
struct node{
	int to,nxt;
	ll cw1,cw2;
}e[N<<1];
struct Node{
	ll dis[2][2];
	Node(){
		mems(dis,0);
	}
}tr[N<<2],emp;
inline void add(int u,int v,ll w1,ll w2){
	e[++tot]={v,head[u],w1,w2};
	head[u]=tot;
}
void dfs1(int u,int f){
	fa[u]=f;
	dep[u]=dep[f]+1;
	siz[u]=1;
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		w[v][0]=e[i].cw1,w[v][1]=e[i].cw2;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]])
			son[u]=v;
	}
}
void dfs2(int u,int t){
	top[u]=t;
	dfn[u]=++cur,rk[cur]=u;
	if(!son[u])
		return;
	dfs2(son[u],t);
	go(i,u){
		int v=e[i].to;
		if(v==fa[u]||v==son[u])
			continue;
		dfs2(v,v);
	}
}
void init1(int u,int f){
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		init1(v,u);
		c[u]=min(c[u],c[v]+w[v][0]+w[v][1]);
	}
}
void init2(int u,int f){
	go(i,u){
		int v=e[i].to;
		if(v==f)
			continue;
		c[v]=min(c[v],c[u]+w[v][0]+w[v][1]);
		init2(v,u);
	}
}
inline Node rev(Node x){
	swap(x.dis[0][1],x.dis[1][0]);
	return x;
}
inline Node pushup(Node ls,Node rs){
	Node o;
	rep(i,0,1){
		rep(j,0,1){
			o.dis[i][j]=min(ls.dis[i][0]+rs.dis[0][j],ls.dis[i][1]+rs.dis[1][j]);
		}
	}
	return o;
}
void build(int l,int r,int o){
	if(l==r){
		ll A=w[rk[l]][0],B=w[rk[l]][1],C=c[rk[l]],D=c[fa[rk[l]]];
		tr[o].dis[0][0]=min(A,B+C+D);
		tr[o].dis[0][1]=min(A+C,B+D);
		tr[o].dis[1][0]=min(A+D,B+C);
		tr[o].dis[1][1]=min(A+C+D,B);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,o<<1);
	build(mid+1,r,o<<1|1);
	tr[o]=pushup(tr[o<<1],tr[o<<1|1]);
}
inline Node query(int l,int r,int o,int x,int y){
	if(r<x||l>y)
		return emp;
	if(l>=x&&r<=y)
		return tr[o];
	int mid=(l+r)>>1;
	if(x<=mid&&y>mid)
		return pushup(query(l,mid,o<<1,x,y),query(mid+1,r,o<<1|1,x,y));
	if(x<=mid)
		return query(l,mid,o<<1,x,y);
	return query(mid+1,r,o<<1|1,x,y);
}
ll ask(int u,int v){
	int opu=(u&1)^1,opv=(v&1)^1;
	u=(u+1)/2,v=(v+1)/2;
	Node x,y;
	x.dis[0][1]=x.dis[1][0]=c[u];
	y.dis[0][1]=y.dis[1][0]=c[v];
	while(top[u]!=top[v]){
		if(dep[top[u]]>dep[top[v]]){
			x=pushup(query(1,n,1,dfn[top[u]],dfn[u]),x);
			u=fa[top[u]];
		}else{
			y=pushup(query(1,n,1,dfn[top[v]],dfn[v]),y);
			v=fa[top[v]];
		}
	}
	if(dfn[u]<dfn[v])
		y=pushup(query(1,n,1,dfn[u]+1,dfn[v]),y);
	if(dfn[u]>dfn[v])
		x=pushup(query(1,n,1,dfn[v]+1,dfn[u]),x);
	x=pushup(rev(x),y);
	return x.dis[opu][opv];
}
void Yorushika(){
	scanf("%d",&n);
	emp.dis[0][1]=emp.dis[1][0]=1ll*inf*inf;
	rep(i,1,n){
		scanf("%lld",&c[i]);
	}
	rep(i,1,n-1){
		int u,v;
		ll w1,w2;
		scanf("%d%d%lld%lld",&u,&v,&w1,&w2);
		add(u,v,w1,w2);
		add(v,u,w1,w2);
	}
	dfs1(1,0);
	dfs2(1,1);
	init1(1,0);
	init2(1,0);
	build(1,n,1);
	scanf("%d",&q);
	rep(i,1,q){
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%lld\n",ask(u,v));
	}
}
signed main(){
	int t=1;
	//	scanf("%d",&t);
	while(t--)
		Yorushika();
}
```

---

