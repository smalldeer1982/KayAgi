# [NAPC-#1] rStage5 - Hard Conveyors

## 题目背景

**本题新增两组 hack 数据。**

---
![](https://cdn.luogu.com.cn/upload/image_hosting/bp1ypbgf.png)

更硬，所以可能就更脆，所以更容易被击破（确信）。

您只花了两个小时就秒掉了正城 s1~s10，来秒逆城了。

## 题目描述

**本题与 Stage5 的区别是合法路径定义不同**（简要题意中加粗部分不同）。~~（其实还有：样例不同，数据不同，部分分不同。）~~

### 【简要题意】

给定一棵 $n$ 个节点的无根树以及树上的 $k$ 个关键节点，边有边权（即边的长度）。$q$ 次询问，每次给出 $s,t$，问从 $s$ 到 $t$ 且经过**至少一个**关键节点的路径的最短长度。

## 说明/提示

### 【数据范围】

upd at `2023-6-25`：新增了两组 hack 数据，将其置于 $\text{Sub}\textsf6$ 中，不记分数。

**本题采用捆绑测试。**

$$
\def\r{\cr\hline}
\def\None{\text{None}}
\def\arraystretch{1.5}
\begin{array}{c|c|c|c}
\textbf{Subtask} & \text{测试点编号} & \textbf{Sp. Constraints} & \textbf{Score}\r
\textsf1&1\sim2 & k=n & 5 \r
\textsf2&16\sim20 &k=1,n\leqslant10^3,q\leqslant10^3 & 15 \r
\textsf3&21\sim25 & n\leqslant10^3,q\leqslant10^3 & 15 \r
\textsf4&3\sim7 & q=1 & 15 \r
\textsf5&8\sim15 & - & 50 \r
\textsf6&26\sim27 & - & 0 \r
\end{array}
$$

对于 $100\%$ 的数据，$1\leqslant n\leqslant 10^5$，$1\leqslant q\leqslant 10^5$，$1\leqslant k\leqslant n$，$1\leqslant w\leqslant 10^4$，$1\leqslant u,v,s,t\leqslant n$。

### 【样例解释 #1】
![](https://cdn.luogu.com.cn/upload/image_hosting/3hvr33bz.png)

图中加粗节点表示关键点。

对于每组询问，以下为一种最优路径（最优路径可能有多条）：
1. $2\to1\to3$。
2. $2\to1$。
3. $7\to1\to2\to1$。
4. $4\to3\to5$。
5. $6\to2\to6$。
6. $2$（合法路径可以不经过任何边，此时路径长为 $0$）。

## 样例 #1

### 输入

```
7 6 2
1 2 3
1 3 5
3 4 2
3 5 4
2 6 1
1 7 1
2 3
2 3
2 1
7 1
4 5
6 6
2 2```

### 输出

```
8
3
7
6
2
0```

# 题解

## 作者：y_kx_b (赞：6)

## rStage5 - Hard Conveyors

预计难度：\*2100 左右，绿\~蓝。

前置芝士：lca，树剖（其实也可以不用）。

---

设 $dis_u$ 为离 $u$ 点最近的一个关键点与它的距离，显然可以使用 dijkstra 等算法 $O(n\log n)$ 求出（以堆优化 dijkstra 为例：将所有关键节点的 $dis$ 设为 $0$ 并全部加入优先队列，然后跑正常的堆优化 dijkstra 即可）。

（upd：好像可以 dfs 就能预处理出这个 $dis$ 数组，但是好像挺麻烦，没试过。）

因为每条路径显然形如 $s\to x\to \operatorname{key}(x)\to x\to t$，其中 $x$ 是 $s\to t$ 路径上的点（可以取到端点），$\operatorname{key}(x)$ 是离 $x$ 最近的关键点。那么预处理出 $dis$ 数组，对于每次询问 $O(n)$ 枚举 $s\to t$ 上的 $x$ 统计这种情况下的最小路径长度，总复杂度 $O(n\log n+qn)$。

发现枚举 $x$ 实际上只是为了求 $dis_x$ 的最小值（因为 $s\to x$ 加上 $x\to t$ 的长度一定等于 $s\to t$）。于是直接套个树剖求一条路径上的 $dis$ 最小值即可，复杂度 $O(n\log n+q\log n)$。

upd：好像倍增求 lca 也可以维护一条路径上的最小值 qwq：设 $st_{i,j}$ 为 $i$ 到根的链中底部 $2^j$ 个点的 $dis$ 最小值（即集合 $\complement_{i\to fa_{i,j}}\{fa_{i,j}\}$ 内 $dis$ 的最小值，其中 $fa_{i,j}$ 表示 $i$ 点的 $2^j$ 级祖先，$u\to v$ 表示 $u$ 到 $v$ 的最短路径上的点构成的集合）。那么求 lca 时 $u,v$ 两个点往上跳的同时用 $st$ 数组更新 $dis$ 最小值就行了。[This sol code。](https://www.luogu.com.cn/paste/1k9ji5zz)

code：
```cpp
int n, q, k;
int head[N], ne[N << 1], to[N << 1], w[N << 1], idx1 = 0;
void add(int u, int v, int x) {
	to[idx1] = v, w[idx1] = x, ne[idx1] = head[u], head[u] = idx1++;
}
int dis[N];
bool dijvis[N];
void dijkstra() {
	memset(dis, 0x3f, sizeof dis);
	memset(dijvis, 0, sizeof dijvis);
	priority_queue<pii, vector<pii>, greater<pii>> Q;
	while(k--) {
		int x = read();
		Q.em(dis[x] = 0, x);
	}
	while(!Q.empty()) {
		int u = Q.top().y; Q.pop();
		if(dijvis[u]) continue;
		dijvis[u] = 1;
		for(int i = head[u]; ~i; i = ne[i]) {
			int &v = to[i];
			if(dis[v] > dis[u] + w[i])
				dis[v] = dis[u] + w[i], Q.em(dis[v], v);
		}
	}
}
#define ws ambiguous1
int ws[N];
int siz[N], fa[N], son[N], dph[N], top[N], dfn[N], rnk[N];
void dfs1(int u, int f) {
	dph[u] = dph[f] + 1, fa[u] = f, siz[u] = 1;
	for(int i = head[u]; ~i; i = ne[i]) if(to[i] != f) {
		int &v = to[i];
		ws[v] = ws[u] + w[i];
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
int timer = 0;
void dfs2(int u, int tp) {
	top[u] = tp, dfn[u] = ++timer, rnk[timer] = u;
	if(son[u]) dfs2(son[u], tp);
	for(int i = head[u]; ~i; i = ne[i]) if(to[i] != fa[u] && to[i] != son[u]) {
		int &v = to[i];
		dfs2(v, v);
	}
}
int st[20][N];
int minimum(int l, int r) {
	if(l > r) return 0x3f3f3f3f;
	int k_ = __lg(r - l + 1);
	return min(st[k_][l], st[k_][r - (1 << /*k*/k_) + 1]);
}
int get_ans(int u, int v) {
	int res = 0x3f3f3f3f, tmp = ws[u] + ws[v];
	while(top[u] != top[v]) {
		if(dph[top[u]] < dph[top[v]]) swap(u, v);
		res = min(res, minimum(dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if(dph[u] > dph[v]) swap(u, v);
	res = min(res, minimum(dfn[u], dfn[v]));
	return tmp - (ws[u] << 1) + (res << 1);
    //tmp - ws[lca] * 2 = u->v 路径长度
}
bool major(int Testcase = 1) {
	memset(head, -1, sizeof head);
	n = read(), q = read(), k = read();
	for(int i = 1; i < n; i++) {
		int u = read(), v = read(), ww = read();
		add(u, v, ww), add(v, u, ww);
	}
	dijkstra();
	dfs1(1, 0);
	dfs2(1, 0);
	memset(st, 0x3f, sizeof st);
	for(int i = 1; i <= n; i++) st[0][i] = dis[rnk[i]];
	for(int j = 1; j < 20; j++) for(int i = 1; i <= n; i++)
		if(i + (1 << j) - 1 <= n)
			st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
	while(q--) {
		int s = read(), t = read();
		printf("%d\n", get_ans(s, t));
	}
	return Testcase;
}
```

---

## 作者：我怂了 (赞：5)

# 我爱树剖，树剖爱我
## 题面简析和初步分析
已知一棵 $n$ 个点的树和 $k$ 个关键节点，边有权值。$q$ 次询问，每次问 $u$，$v$ 两个点之间的经过一个关键节点的最短路程。

由于是一棵树，所以任意两点间的路径是唯一的。如果路径上有关键节点，那走完就行，答案就是最短路径长。要是没有，就需要挑一个点走到一个关键节点再原路返回，也就是要加上路径上距离一个关键节点最近的点到关键节点路径长的两倍。
## 菜狗的做题经历自述
首先，打眼一瞅，求树上两点最短路，就是个 LCA。求 LCA 有两种方式，一种倍增，还有一种就是树剖。两种方法各有利弊，倍增胜在代码简单，树剖胜在~~代码复杂~~功能强大，支持修改等多种操作。

但是回身一看：不对劲，还要加上一个数，也就是路上各个节点到“关键节点”的距离的最小值。

完了，倍增不会了怎么办 qwq，那就去干树剖吧。（乐）

（虽然其实倍增也行，主要是我这菜狗被树剖冲昏了头脑）
## 树剖简介
树剖其实洛谷上有模板，详见[这题](https://www.luogu.com.cn/problem/P3384)。不会的同志们可以瞅一眼理解了再回来。

树剖也就是听起来唬人点，真理解起来还是相对轻松的。
## 那为啥会想到树剖？
其实简单：

树剖的本质就是通过每次 dfs 重儿子的方式把一棵树给剖成好几条“重链”，也就是链上每个节点，除了重链打头的那个以外，都是自己父亲的重儿子的链。

在这种 dfs 顺序中，每一条重链都是连续的。基于这种性质，我们可以将树上的任意一条路径割成一条或几条重链，或是它们的一部分，也就是在 dfs 序中若干连续的区间。

那么本题中查询一条路径上最小值的问题就可以转化成了求在 dfs 序中几段区间上的最小值，显然可以套个线段树解决。（线段树和树剖仙配！doge）
## 其他步骤
上面需要实现的步骤中除了树剖以外，有一棵维护区间最小值的线段树（为啥不用 ST 表？因为我......忘了）、一个类似 Dijkstra 的求出树上任意一个点 $x$ 到距离他最近的关键节点的距离 $d[x]$ 的算法。

还有一个为了方便求出路径长而维护的从节点 $x$ 到它所在重链的顶端的 $pre[x]$ 数组，这个东西的求法和用法要仔细分辨一下。
### 求
求的公式很简单 $pre[x] \gets pre[f[x]]+v[x]$，其中 $f[x]$ 是 $x$ 的父亲节点，$v[x]$ 是 $x$ 与 $f[x]$ 之间的边权，在第一次 dfs 时求出。整体和前缀和很像。

需要注意的是重链的头部要加一个特判，也就是 $f0[f[x]] \ne f0[x]$，其中 $f0[x]$ 是 $x$ 所在重链的顶端。此时说明 $x$ 是新一条重链的顶端，令 $pre[x] \gets v[x]$ 即可。
### 用，即处理询问
每次询问定义一个 $dis$ 用来存储路径上 $d[x]$ 的最小值。

当 $f0[u] \ne f0[v]$ 时，每次向上选取 $u$，$v$ 中所在重链顶端深度低的节点，将其计为 $a$，令
$$sum \gets sum+pre[x]$$
$$dis \gets \min(dis,\min{d[i]})$$ 
$$a \gets f[f0[a]]$$
其中 $i$ 为从 $x$ 到 $f0[x]$ 路径上的点，这一步用线段树维护（ST 表也可以，甚至更快，编码更简单）。

当 $f0[u]=f0[v]$ 时，二者在同一条重链上。
$$dis \gets \min(dis,\min{d[i]})$$
$$sum \gets sum+ \mid pre[u]-pre[v] \mid+dis \times2$$
就，结束啦！可以返回 $sum$ 的值啦！
## 复杂度（各种复杂度）
时间：$O(q \log ^ {2} n + n \log n )$
 比正解大，因为多跑了一次线段树。如果用 ST 表还能消掉一个 $\log$。

空间：不重要，但是是一个常数比较大的    $O(n)$。

编码：对于大佬，这不重要。对于我这种菜狗，这还是很重要的，毕竟会写爆掉。一看，嚯！又是线段树又是树剖的，不会写个两百五十行吧？（毕竟一个树剖我这个菜狗就写了一百七十多行）

其实不会，因为这道题主要就是用各个模板里一部分的功能，所以这边写几十行，那边写几十行，甚至线段树都不用懒人标记。最后就我这个不甚压行的码风也就区区一百四十行不到。

## 代码：[点击自取](https://www.luogu.com.cn/paste/hnv2i94r)
## 感谢阅读！

---

## 作者：technopolis_2085 (赞：4)

分析：

由于涉及树上两点的路径，所以我们会需要用到最近公共祖先算法。

设两点为 $u$ 和 $v$，最近公共祖先为 $f$，则路径必为：

$u$ 到 $f$ 的距离，加上 $f$ 到 $v$ 的距离，加上路径中所有点到关键点中最短的距离的 $2$ 倍。

可以发现，主要难点为“路径中所有点到关键点中最短的距离”。

首先可以做一遍最短路，求出每一个节点 $u$ 到关键点的最短距离 $dist_u$。

然后，考虑 st 表，令 $dp_u,_i$ 为节点 $u$ 往上 $2^i$ 个节点的编号。

令 $st_u,_i$ 为从节点 $u$ 往上 $2^i$ 个节点中的 $dist$ 数组最小值。

所以：

$dp_u,_i$ 为 $dp_{dp_u,_{i-1}},_{i-1}$。

$st_u,_i$ 为 $st_u,_{i-1}$ 和 $st_{dp_u,_{i-1}},_{i-1}$ 中的较小值。

于是可以从 $u$ 和 $v$ 节点开始，倍增查找路径中点到关键点最短的路径长度。


然后就做完了，记得开 long long。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1e5+10;
vector<pair<int,int> > G[maxn];
int dp[maxn][20],st[maxn][20];
int len[maxn];
int n,k,q;
int depth[maxn];
int dist[maxn];

struct node{
	int u;
	int d;
	
	bool operator <(const node &cmp) const{
		return d>cmp.d;
	}
};

void dij(){
	priority_queue<node> q;
	while (!q.empty()) q.pop();
	for (int i=1;i<=n;i++) dist[i]=1e9+7;
	for (int i=1;i<=k;i++){
		int u;
		scanf("%lld",&u);
		dist[u]=0;
		q.push((node){u,0});
	}
	
	while (!q.empty()){
		node f=q.top(); q.pop();
		
		if (f.d>dist[f.u]) continue;
		
		int u=f.u;
		for (int i=0;i<(int)G[u].size();i++){
			int v=G[u][i].first;
			
			if (dist[v]>dist[u]+G[u][i].second){
				dist[v]=dist[u]+G[u][i].second;
				q.push((node){v,dist[v]});
			}
		}
	}
}

void dfs(int u,int fa){
	depth[u]=depth[fa]+1;
	dp[u][0]=fa;
	st[u][0]=dist[u];
	
	for (int i=1;i<20;i++){
		dp[u][i]=dp[dp[u][i-1]][i-1];
		st[u][i]=min(st[u][i-1],st[dp[u][i-1]][i-1]);
	}
	
	for (int i=0;i<(int)G[u].size();i++){
		int v=G[u][i].first;
		if (v==fa) continue;
		
		len[v]=len[u]+G[u][i].second;
		dfs(v,u); 
	}
}

int lca(int u,int v){
	if (depth[u]<depth[v]) swap(u,v);
	int delta=depth[u]-depth[v];
	
	for (int i=0;i<20;i++){
		if ((delta&(1<<i))) u=dp[u][i];
	}
	
	if (u==v) return u;
	
	for (int i=19;i>=0;i--){
		if (dp[u][i]!=dp[v][i]){
			u=dp[u][i];
			v=dp[v][i]; 
		}
	}
	
	return dp[u][0];
}

int find(int u,int v){
	int delta=depth[u]-depth[v];
	if (u==v){
		return dist[u];
	}
	
	int ans=1e9+7;
	for (int i=19;i>=0;i--){
		if (depth[dp[u][i]]>=depth[v]){
			ans=min(ans,st[u][i]);
			u=dp[u][i];
		//	u=dp[u][0];
		}
	}
	
	ans=min(ans,dist[v]);
	return ans;
}

signed main(){
	scanf("%lld%lld%lld",&n,&q,&k);
	
	for (int i=1;i<n;i++){
		int u,v,w;
		scanf("%lld%lld%lld",&u,&v,&w);
		
		G[u].push_back(make_pair(v,w));
		G[v].push_back(make_pair(u,w));
	}
	
	dij();
	for (int i=0;i<20;i++) st[0][i]=1e9+7;
	dfs(1,0);
	
	while (q--){
		int u,v;
		scanf("%lld%lld",&u,&v);
		
		int f=lca(u,v);
		int ans=(len[u]-len[f])+(len[v]-len[f]);
		
//		if (dist[f]==0){
//			printf("%lld\n",ans);
//			continue;
//		}
		int mi=min(find(u,f),find(v,f));
		ans+=2*mi;
		printf("%lld\n",ans);
	}
	return 0;
}
```


---

## 作者：LHLeisus (赞：3)

[原题链接](https://www.luogu.com.cn/problem/P9432)

[逆天的阅读体验](https://www.cnblogs.com/LHLeisus/p/17775745.html)

这道题我看大家都用 dijkstra 啊，惊恐，这里提供一种换根 dp 的写法。

两点间最短路径，那一定是 LCA 没错了。用一遍 dfs 求出根节点到每个点的距离，记为 $dist$。那么 $u,v$ 间最短路径长度的就是 $dist_u+dist_v-dist_{\operatorname{lca}(u,v)}\times 2$。
但是题目还要求至少经过一个**关键点**。如果 $u,v$ 间的路径上存在关键点，那自然是好的，直接走就可以了；若不存在，则需要找一个路径上的点，使这个点向外走到一个关键点再回来的距离最小。
形式化地说，若路径长为 $L$，每个点 $i$ 到关键点的最近距离为 $F_i$，则答案 $ans=L+\min{F_i}\times 2$，其中点 $i$ 在 $u$ 到 $v$ 的路径上。

之后就是实现了。我用的树剖加换根 dp。树剖求 LCA，再加线段树维护 $F_i$ 的区间最小值，**十分好写**，这里就不赘述了，主要是 $F$ 的求法。

- 设 $f_i$ 为以 $i$ 点为根的子树中，点 $i$ 与关键点的最近距离。这个十分好求，一遍 dfs 轻松解决。重要的是如何用第二次 dfs 进行换根。
- 注意到 $f$ 只包含了子树内的情况，那么就设 $g_i$ 为 $i$ 的子树外的关键点距离 $i$ 的最近距离。有一个显然的转移：$$g_v=\min(g_v,g_u+edge_{u\to v})$$ 也就是从 $u$ 的子树外转移而来。
- 此外我们还有一种情况没有考虑，就是在 $u$ 的子树内，但不在 $v$ 的子树内，这时候 $f$ 一维就不是很好转移了。我们修改为： 设 $f_{i,1}$ 为以 $i$ 为根的子树中，点 $i$ 与关键点的最小距离；$f_{i,0}$ 则为次小距离。
这样一来，若当前 $v$ 是那个最小值，就需要从次小值转移过来；否则从最小值转移。

- 状态转移方程为：$\begin{cases}g_v=\min(g_v,f_{u,0}+edge_{u\to v})\ \ \ \ \ f_{v,1}+edge_{u\to v}=f_{u,1}\\g_v=\min(g_v,f_{u,1}+edge_{u\to v})\ \ \ \ \ \operatorname{otherwise}\end{cases}$

之后，显然 $F_i=\min(g_i,f_{i,1})$，再用线段树维护最小值即可。


```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<string>
#include<utility>
#include<vector>
#include<queue>
#include<bitset>
#define int long long
#define FOR(i,a,b) for(register int i=a;i<=b;i++)
#define ROF(i,a,b) for(register int i=a;i>=b;i--)
#define mp(a,b) make_pair(a,b)
#define pll pair<long long,long long>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
inline int read();
typedef long long ll;
const int N=1e5+5;
const int INF=0x3f3f3f3f;
int n,m,k,q;
struct E{
	int to,nex,w;
}edge[N<<1];
int head[N],cnt=0;
void add(int u,int v,int w){
	edge[++cnt]=(E){v,head[u],w};
	head[u]=cnt;
}
bitset<N>mark;
int son[N],fa[N],top[N],sz[N],dfn[N],dep[N],dist[N],F[N][2],g[N];
void dfs1(int u,int f){
	sz[u]=1;
	fa[u]=f;
	dep[u]=dep[f]+1;
	int max_son=-1;
	F[u][0]=F[u][1]=INF;
	if(mark[u]) F[u][0]=F[u][1]=0;
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==f) continue;
		dist[v]=dist[u]+edge[i].w;
		dfs1(v,u);
		if(F[v][1]+edge[i].w<F[u][1]){
			F[u][0]=F[u][1];
			F[u][1]=F[v][1]+edge[i].w;
		}
		else if(F[v][1]+edge[i].w<F[u][0]) F[u][0]=min(F[u][0],F[v][1]+edge[i].w);
		sz[u]+=sz[v];
		if(max_son<sz[v]) max_son=sz[v],son[u]=v;
	}
}
int tot=0,pos[N];
void dfs2(int u,int topx){
	dfn[u]=++tot;
	pos[tot]=min(F[u][1],g[u]);
	top[u]=topx;
	if(!son[u]) return ;
	dfs2(son[u],topx);
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
int tr[N<<2];
void pushup(int u){
	tr[u]=min(tr[u<<1],tr[u<<1|1]);
}
void build(int u,int l,int r){
	if(l==r) return tr[u]=pos[l],void();
	int mid=l+r>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
int query(int u,int l,int r,int L,int R){
	if(L<=l&&r<=R)
		return tr[u];
	int mid=l+r>>1;
	int res=INF;
	if(L<=mid) res=min(res,query(u<<1,l,mid,L,R));
	if(R>mid) res=min(res,query(u<<1|1,mid+1,r,L,R));
	return res;
}
pii LCA(int u,int v){
	int res=INF;
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res=min(res,query(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res=min(res,query(1,1,n,dfn[u],dfn[v]));
	return mp(u,res);
}
void dfs3(int u,int f){
	if(mark[u]) g[u]=0;
	for(int i=head[u];i;i=edge[i].nex){
		int v=edge[i].to;
		if(v==f) continue;
		g[v]=min(g[v],g[u]+edge[i].w);
		if(F[v][1]+edge[i].w==F[u][1]){
			g[v]=min(g[v],F[u][0]+edge[i].w);
		}
		else g[v]=min(g[v],F[u][1]+edge[i].w);
		dfs3(v,u);
	}
}
signed main()
{
	n=read(),q=read(),k=read();
	FOR(i,1,n-1){
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	FOR(i,1,k){
		mark[read()]=1;
	}
	dfs1(1,0);
	memset(g,0x3f,sizeof g);
	g[1]=F[1][1];
	dfs3(1,0);
	dfs2(1,1);
	build(1,1,n);
	while(q--){
		int s=read(),t=read();
		if(s==t){
			printf("%lld\n",min(F[s][1],g[s])*2);
			continue;
		}
		pii temp=LCA(s,t);
		int lca=temp.fi,num=temp.se;
		int ans=dist[s]+dist[t]-dist[lca]*2+num*2;
		printf("%lld\n",ans);
	}
	return 0;
}


inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
	return f*x;
}
```


---

## 作者：MvemiY (赞：1)

### 题目描述

给定一棵 $n$ 个节点的无根树以及树上的 $k$ 个关键节点，边有边权（即边的长度）。$q$ 次询问，每次给出 $s,t$，问从 $s$ 到 $t$ 且经过**至少一个**关键节点的路径的最短长度。

### 题目分析

观察到数据范围中 $1 \le w \le 10^4$，我们容易想到，点 $u$ 到点 $v$ 的最短路径，应是从点 $u$ 到某个点 $x$，从 $x$ 到离它最近的某个关键节点 $p$ 后回到 $x$，再从点 $x$ 到点 $v$。

记 $f_u$ 表示点 $u$ 到离其最近的某个关键节点 $p$ 的距离，$pre_u$ 表示根节点到点 $u$ 的边权和，（因为是无根树，而且题目只和路径有关，所以我们可以钦定节点 $1$ 为根）。

$pre$ 数组的预处理显然：$pre_u=pre_{fa_u}+e(fa_u,u)$。

而 $f$ 数组的预处理，题解里大多是换根 DP 或 Dijkstra。而我对 $f$ 数组的预处理和他们有所不同，这也是我提交这篇题解的原因。

容易想到，对于每个点 $u$，离其最近的某个关键节点 $p$ 要么在 $u$ 的子树外，要么在 $u$ 的子树内。当 $p$ 在 $u$ 点的子树外，那么显然 $p$ 点会经过 $fa_u$，则 $f_u = f_{fa_u}+e(fa_u,u)$。当 $p$ 在 $u$ 点的子树内，显然从点 $u$ 走到点 $p$ 的权值和为 $f_u = pre_p-pre_u$，其中 $pre_u$ 对于每个点 $u$ 为定值，因此我们只需要求出 $\min\{pre_p\}$ 就可以了。

那么，如何快速求出 $\min\{pre_p\}$（其中 $p \in subtree_u$）呢？我们知道在树的 DFS 序上，点 $subtree_u$ 中的点是一个连续的区间，其中 DFS 序最小的点为 $u$，$l=id_u$ 就是区间的左端点，$r=id_u+size_u-1$ 就是区间的右端点。我们将所有关键节点按照其 DFS 序从大到小排序，那么我们很容易使用二分查找到第一个在 $u$ 的子树中的点的位置 $L$ 和最后一个在 $u$ 的子树中的点的位置 $R$，最后询问 $[L,R]$ 的最小 $pre$ 的值即可。

得到 $pre$ 数组和 $f$ 数组后，对于每次询问，使用树链剖分或者树上倍增求出 $u$ 到 $v$ 的路径上最小的 $f_x$ 和 $u$ 和 $v$ 的最近公共祖先 $lca$，答案即为 $pre_u+pre_v-2 \times pre_{lca}+2 \times min\{f_x\}$。别忘了 $f_x$ 要乘 $2$，因为从点 $x$ 到点 $p$ 后还要走回来。

### 数据结构与复杂度分析

对于查询 $[L,R]$ 的最小 $pre$ 的值，我们可以将关键节点们拍到一个 st 表上，然后可以 $O(n\log_2n)$ 预处理，$O(1)$ 查询。

对于树链剖分或树上倍增，时间复杂度都是 $O(n\log_2n)$。

因为要开两个 st 表，因此空间复杂度为 $O(n\log_2n)$。

$n \le 10^5$，因此 $O(n\log_2n)$ 的时空复杂度可以通过本题。注意开 long long。

### 代码实现

```cpp
#include<bits/stdc++.h>
#define E(v, w) (Edge){v, w}
#define ll long long 
using namespace std;
const int MAXN = 1e5 + 10;
inline ll read(){
	ll x = 0, f = 1; char c = getchar();
	while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
	while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
	return x * f;
} 

ll n, q, k, f[MAXN], pre[MAXN], tot, st1[MAXN][21], st2[MAXN][21];
ll fa[MAXN], Bigson[MAXN], dep[MAXN], top[MAXN], siz[MAXN], dfn[MAXN], id[MAXN];
struct Edge{
	ll v, w;
};
vector <Edge> tr[MAXN];
struct Node{
	ll u, idd;
	bool operator < (Node x) const {return this->idd < x.idd;}
	bool operator > (Node x) const {return this->idd > x.idd;}
	bool operator == (Node x) const {return this->idd == x.idd;}
}p[MAXN];

void dfs1(ll u, ll Fa){
	dep[u] = dep[Fa] + 1;
	fa[u] = Fa;
	siz[u] = 1;
	ll len = tr[u].size();
	for(ll i = 0; i < len; i++){
		ll v = tr[u][i].v, w = tr[u][i].w;
		if(v == Fa) continue;
		pre[v] = pre[u] + w;
		dfs1(v, u);
		siz[u] += siz[v];
		if(siz[v] > siz[Bigson[u]])
			Bigson[u] = v;
	}
}

void dfs2(ll u, ll head){
	dfn[++tot] = u;
	id[u] = tot;
	top[u] = head;
	if(Bigson[u])
		dfs2(Bigson[u], head);
	ll len = tr[u].size();
	for(ll i = 0; i < len; i++){
		ll v = tr[u][i].v;
		if(v == Bigson[u] || v == fa[u]) continue;
		dfs2(v, v);
	}
}

void init1(){
	for(ll i = 1; i <= k; i++)
		st1[i][0] = pre[p[i].u];
	for(ll j = 1; j <= 20; j++){
		for(ll l = 1, r = l + (1<<j) - 1; r <= k; l++, r++)
			st1[l][j] = min(st1[l][j-1], st1[r-(1<<(j-1))+1][j-1]);
	}
}

ll query1(ll l, ll r){
	ll lg = log2(r-l+1);
	return min(st1[l][lg], st1[r-(1<<lg)+1][lg]);
}

ll work(ll u){
	ll l = id[u], r = id[u] + siz[u] - 1;
	ll L = lower_bound(p+1, p+1+k, (Node){-1, l}) - p;
	// 在排完序的关键节点中找到第一个 >= l 的节点位置 
	ll R = upper_bound(p+1, p+1+k, (Node){-1, r}) - p - 1;
	// 在关键节点中找到最后一个 <= r 的节点位置 
	if(L > R) return 0x3f3f3f3f3f3f3f3f;
	// 在 subtree{u} 中不存在关键节点 
	return query1(L, R);
}

void dfs3(ll u){
	f[u] = min(f[u], work(u) - pre[u]);
	ll len = tr[u].size();
	for(ll i = 0; i < len; i++){
		ll v = tr[u][i].v, w = tr[u][i].w;
		if(v == fa[u]) continue;
		f[v] = min(f[v], f[u] + w);
		// 一定要将这句话放在 dfs3(v) 的前面，因为它的儿子要用它，笔者因此浪费了 2h 
		dfs3(v);
	}
}

void init2(){
	for(ll i = 1; i <= n; i++)
		st2[i][0] = f[dfn[i]];
	for(ll j = 1; j <= 20; j++){
		for(ll l = 1, r = l + (1<<j) - 1; r <= n; l++, r++)
			st2[l][j] = min(st2[l][j-1], st2[r-(1<<(j-1))+1][j-1]);
	}
}

ll query2(ll l, ll r){
	ll lg = log2(r-l+1);
	return min(st2[l][lg], st2[r-(1<<lg)+1][lg]);
}

pair <ll,ll> query_path(ll u, ll v){
	ll res = 0x3f3f3f3f3f3f3f3f;
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]])
			swap(u, v);
		res = min(res, query2(id[top[u]], id[u]));
		u = fa[top[u]];
	}
	if(dep[u] < dep[v]) swap(u, v);
	res = min(res, query2(id[v], id[u]));
	return {v, res};
}

int main(){
	memset(f, 0x3f, sizeof(f));
	n = read(), q = read(), k = read();
	for(ll i = 1; i < n; i++){
		ll u = read(), v = read(), w = read();
		tr[u].push_back(E(v, w));
		tr[v].push_back(E(u, w));
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for(ll i = 1; i <= k; i++)
		p[i].u = read(), p[i].idd = id[p[i].u];
	sort(p+1, p+1+k);
	init1();
	dfs3(1);
	init2();
	while(q--){
		ll u = read(), v = read();
		pair <ll,ll> tmp = query_path(u, v);
		ll lca = tmp.first, az = tmp.second;
		printf("%lld\n", pre[u] + pre[v] - 2*pre[lca] + 2*az);
	}
	return 0;
}
```

---

## 作者：Genshineer (赞：1)

### P9432 [NAPC-#1] rStage5 - Hard Conveyors

感谢此题让我知道了 `Dijkstra` 的一种新用法。

#### 题意：

给定一棵 $n$ 个节点的无根树以及树上的 $k$ 个关键节点，给定边的长度。有 $q$ 次询问，每次给出 $s,t$，问从 $s$ 到 $t$ 且经过**至少一个**关键节点的路径的最短长度。

#### 分析：

显然经过**至少一个**关键节点的条件可以分为两种情况判断：

1. 如果从 $s$ 到 $t$ 的**简单路径**上已经有关键点，那么直接输出 $s$ 到 $t$ 的简单路径长度即可。这个过程显然可以以 $1$ 为根处理出每个节点 $u$ 到节点 $1$ 的距离 $len_u$，那么长度 $ans$ 就是 $len_u+len_v-2\times len_{lca(u,v)}$。

2. 如果从 $s$ 到 $v$ 的**简单路径**上没有关键点，那么显然找到**最近**的关键点 $v$，走到 $v$ 再回到简单路径上的方法可以得到最优解。而不妨预处理出每个点到**任意一个**关键点的最短距离 $dis$ 数组，则**路径到任意关键点的最短距离**就可以定义为简单路径上 $dis$ 数组的最小值 $mindis$，由此答案只需要在 $ans$ 的基础上再加上 $2\times mindis$。而多次查询路径上区间有关信息的问题显然可以用线段树 $+$ 树链剖分实现，那么关键就是如何计算**每个点到任意一个关键点的最短距离**。

这时候就需要 `Dijkstra` 的经典（神奇~~逆天~~）多源最短路写法了：将每个关键点的初始 $dis$ 均设为 $0$，再跑普通的堆优化 `Dijkstra`，此时 $dis$ 数组存储的就是**每个点到任意一个关键点的最短距离**了。

核心代码如下：

```cpp
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;

inline void dij() {
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= k; i++) {
		dis[p[i]] = 0;
		q.push({0, p[i]});
	}
	while (!q.empty()) {
		auto u = q.top().second;
		q.pop();

		if (vis[u]) continue;
		vis[u] = 1;

		for (auto i : G[u]) {
			int v = i.first, w = i.second;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({dis[v], v});
			}
		}
	}
}
```

剩下的就是经典的普通树剖维护 $dis$ 数组的区间最小值了。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 1e5 + 5;
int n, m, k;
vector<pair<int, int> > G[maxn];
struct data {
	int l, r, dat;
} t[maxn << 2];
int dep[maxn], fa[maxn], siz[maxn], son[maxn], top[maxn], dfn[maxn], rk[maxn], cnt;
int len[maxn];
int dis[maxn], p[maxn];
bool vis[maxn];
priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;

inline void dfs1(int u, int f) {
	dep[u] = dep[f] + 1;
	siz[u] = 1;
	for (auto i : G[u]) {
		int v = i.first, w = i.second;
		if (v == f) continue;
		fa[v] = u;
		len[v] = len[u] + w;
		dfs1(v, u);
		siz[u] += siz[v];
		if (siz[son[u]] < siz[v]) son[u] = v;
	}
}

inline void dfs2(int u, int tp) {
	top[u] = tp;
	dfn[u] = ++cnt;
	rk[cnt] = u;
	if (!son[u]) return;
	dfs2(son[u], tp);
	for (auto i : G[u]) {
		int v = i.first;
		if (v == fa[u] or v == son[u]) continue;
		dfs2(v, v);
	}
}

inline void build(int p, int l, int r) {
	t[p].l = l, t[p].r = r;
	if (l == r) {
		t[p].dat = dis[rk[l]];
		return;
	}
	int mid = (l + r) >> 1;
	build(p << 1, l, mid);
	build(p << 1 | 1, mid + 1, r);
	t[p].dat = min(t[p << 1].dat, t[p << 1 | 1].dat);
}

inline int query(int p, int l, int r) {
	if (l <= t[p].l and t[p].r <= r) return t[p].dat;
	int mid = (t[p].l + t[p].r) >> 1, res = 0x3f3f3f3f;
	if (l <= mid) res = min(res, query(p << 1, l, r));
	if (mid < r) res = min(res, query(p << 1 | 1, l, r));
	return res;
}

inline void dij() {
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= k; i++) {
		dis[p[i]] = 0;
		q.push({0, p[i]});
	}
	while (!q.empty()) {
		auto u = q.top().second;
		q.pop();

		if (vis[u]) continue;
		vis[u] = 1;

		for (auto i : G[u]) {
			int v = i.first, w = i.second;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({dis[v], v});
			}
		}
	}
}

inline int get(int u, int v) {
	int res = 0x3f3f3f3f, ans = 0, uu = u, vv = v;
	while (top[u] != top[v]) {
		if (dep[top[u]] < dep[top[v]]) swap(u, v);
		res = min(res, query(1, dfn[top[u]], dfn[u]));
		u = fa[top[u]];
	}
	if (dep[u] > dep[v]) swap(u, v);
	res = min(res, query(1, dfn[u], dfn[v]));
	ans = len[uu] + len[vv] - len[u] * 2;
	return ans + res * 2;
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	for (int i = 1; i <= k; i++) cin >> p[i];
	dij();
	dfs1(1, 1);
	dfs2(1, 1);
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		cout << get(u, v) << "\n";
	}
}
```

---

## 作者：MspAInt (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/P9432)

板子题，不会树剖的出门左转 [oi-wiki](https://oi-wiki.org/graph/hld/)。

预处理出每个点到最近的关键点的距离，显然一遍 dijkstra 足矣。

路径询问考虑树链剖分。线段树记录 dfn 区间中 所有点里与关键点最短的距离 以及 边权转点权后区间内的点权和。

边权转点权 就是把父节点和子节点之间的边权赋到子节点上，以便处理。

答案就是 路径长度 + 路径上节点中与关键点的最短距离 $\times 2$（即一个来回）。树剖可以 $\Theta(\log^2 n)$ 求出。

然后，就没有然后了。。。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct edge{int to,w;};
struct node{int l,r,Min,Dis;}t[N<<2];
int n,q,m,k[N],top[N],hs[N],dfn[N],nfd[N],dep[N],dis[N],sz[N],c[N],fa[N];
bool vis[N];
priority_queue<pair<int,int>>h;
vector<edge>e[N];
void dfs1(int u){
    sz[u]=1;
    dep[u]=dep[fa[u]]+1;
    for(auto x:e[u]){
        int v=x.to,l=x.w;
        if(v==fa[u])continue;
        fa[v]=u;dfs1(v);
        sz[u]+=sz[v];hs[u]=sz[v]>sz[hs[u]]?v:hs[u];
        c[v]=l;
    }
    return;
}
void dfs2(int u,int T){
    dfn[u]=++dfn[0];nfd[dfn[u]]=u;
    top[u]=T;
    if(hs[u])dfs2(hs[u],T);
    for(auto x:e[u]){
        int v=x.to,l=x.to;
        if(v!=hs[u]&&v!=fa[u])dfs2(v,v);
    }
    return;
}
void pushup(int u){
    t[u].Min=min(t[u<<1].Min,t[u<<1|1].Min);
    t[u].Dis=t[u<<1].Dis+t[u<<1|1].Dis;
    return;
}
void build(int u,int L,int R){
    t[u].l=L;t[u].r=R;
    if(L==R){t[u].Min=dis[nfd[L]];t[u].Dis=c[nfd[L]];return;}
    int mid=L+R>>1;
    build(u<<1,L,mid);build(u<<1|1,mid+1,R);
    pushup(u);
    return;
}
int Sqry(int u,int L,int R){
    if(t[u].l>R||t[u].r<L)return 0;
    if(t[u].l>=L&&t[u].r<=R)return t[u].Dis;
    return Sqry(u<<1,L,R)+Sqry(u<<1|1,L,R);
}
int Mqry(int u,int L,int R){
    if(t[u].l>R||t[u].r<L)return 1e9;
    if(t[u].l>=L&&t[u].r<=R)return t[u].Min;
    return min(Mqry(u<<1,L,R),Mqry(u<<1|1,L,R));
}
int query(int x,int y){
    int ret=0,out=1e9;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        ret+=Sqry(1,dfn[top[x]],dfn[x]);
        out=min(out,Mqry(1,dfn[top[x]],dfn[x]));
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    if(x!=y)ret+=Sqry(1,dfn[hs[x]],dfn[y]);
    out=min(out,Mqry(1,dfn[x],dfn[y]));
    out<<=1;
    return ret+out;
}
void dijkstra(){
    for(int i=1;i<=n;i++)dis[i]=1e9;
    for(int i=1;i<=m;i++)dis[k[i]]=0,h.push(make_pair(0,k[i]));
    while(h.size()){
        int u=h.top().second;h.pop();
        if(vis[u])continue;
        for(auto x:e[u]){
            int v=x.to,l=x.w;
            if(!vis[v]&&dis[u]+l<dis[v]){
                dis[v]=dis[u]+l;
                h.push(make_pair(-dis[v],v));
            }
        }
        vis[u]=1;
    }
}
signed main(){
    scanf("%d%d%d",&n,&q,&m);
    for(int i=1;i<n;i++){
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        e[x].push_back({y,z});e[y].push_back({x,z});
    }
    for(int i=1;i<=m;i++)scanf("%d",&k[i]);
    dfs1(1);dfs2(1,1);dijkstra();build(1,1,n);
    for(int i=1;i<=q;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
    return 0;
}
```

[record](https://www.luogu.com.cn/record/119548342)

---

## 作者：EXODUS (赞：1)

# Part 1：前言
迟来的验题人题解，好像确实有点迟了/kx。

# Part 2：正文
首先考虑不经过特殊点，那么这个可以简单的维护 lca 及每个点深度求出。

现在考虑把特殊点的限制加进去，假设我们现在钦定了一个关键点 $i$，当前询问为 $(u,v)$，则答案一定是形如 $dis_{u,v}+2dis_{i,x}$，其中 $dis_{i,j}$ 表示 $i$ 到 $j$ 的最短路径，$x$ 为路径上某点。

根据贪心可知对于每次询问我们只需要找到一个在路径上的 $x$ 满足 $dis_{i,x}$ 最小即可。

更进一步的，我们令 $w_x$ 为 $x$ 节点距最近关键点的距离，那么我们要找的就是最小的 $w_x$。假设我们求出来了 $w_x$，我们可以套用火车运输那题拿个倍增维护一条路径上的最小值。

求 $w_x$ 也是简单的，多源最短路即可。时间复杂度 $O(n\log n+q\log n)$。



# Part 3：代码
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i,l,r) for(int i(l);i<=(r);++i)
#define per(i,r,l) for(int i(r);i>=(l);--i)
#define eb emplace_back
#define Debug(...) fprintf(stderr,__VA_ARGS__)
int read(){
	int ans=0,flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))ans=(ans<<3)+(ans<<1)+(ch^48),ch=getchar();
	return ans*flg;
}
template<typename T>
void read(T &x){
	x=0;T flg=1;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')flg=-1;ch=getchar();}
	while(isdigit(ch))x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	x*=flg;
}
template<typename T,typename... Args>
void read(T &x,Args &...args){read(x),read(args...);}
const int N=2e5+7;
int n,q,k;
vector<pair<int,int> >g[N];
priority_queue<pair<int,int> >Q;
int dis[N],anc[N][20],val[N][20],vis[N],dep[N],Dep[N];
void dfs(int u,int F){
	anc[u][0]=F;val[u][0]=dis[F];dep[u]=dep[F]+1;
	rep(i,1,18)anc[u][i]=anc[anc[u][i-1]][i-1],val[u][i]=min(val[u][i-1],val[anc[u][i-1]][i-1]);
	for(auto [v,w]:g[u])if(v!=F)Dep[v]=Dep[u]+w,dfs(v,u);
}
pair<int,int> ask(int u,int v){
	int res=min(dis[u],dis[v]);
	if(dep[u]<dep[v])swap(u,v);
	per(i,18,0)if(dep[anc[u][i]]>=dep[v])res=min(res,val[u][i]),u=anc[u][i];
	if(u==v)return make_pair(u,res);
	per(i,18,0)if(anc[u][i]!=anc[v][i])res=min({res,val[u][i],val[v][i]}),u=anc[u][i],v=anc[v][i];
	// Debug("- %d\n",res);
	return make_pair(anc[u][0],min(res,dis[anc[u][0]]));
}
int main(){
	read(n,q,k);
	for(int i=1,u,v,w;i<n;i++)read(u,v,w),g[u].eb(v,w),g[v].eb(u,w);
	memset(dis,0x3f,sizeof(dis));
	for(int i=1,u;i<=k;i++)read(u),Q.push(make_pair(0,u)),dis[u]=0;
	while(!Q.empty()){
		auto [d,u]=Q.top();Q.pop();if(vis[u])continue;vis[u]=1;
		for(auto [v,w]:g[u])if(dis[v]>dis[u]+w&&!vis[v])dis[v]=dis[u]+w,Q.push(make_pair(-dis[v],v));
	}
	dis[0]=0;
	dfs(1,0);
	// for(int i=1;i<=n;i++)Debug("%d ",Dep[i]);Debug("\n");
	while(q--){
		int u=read(),v=read();
		auto [lca,res]=ask(u,v);res=res*2ll-Dep[lca]*2ll+Dep[u]+Dep[v];
		assert(lca!=0);
		// Debug("+ %d %d\n",lca,res);
		printf("%lld\n",res);
	}
	return 0;
}
```

---

## 作者：baka24 (赞：0)

首先考虑一下一条符合目标的路径由什么构成。


发现对于一条路径，如果路径上有关键点，直接走最短路就行。


如图，因为 $5$ 本身就是关键点，所以直接走即可。
![](https://cdn.luogu.com.cn/upload/image_hosting/upt3irw6.png)


而对于没有关键点的路径，例如上图的 $2\sim4$，我们需要走到路径上某一个点之后，走到一个关键点，之后再回到路径上，如图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ooa4m568.png)

设两个点分别为 $x,y$。

我们发现，$x,y$ 之间的路径是必须要走的，而额外要走的路径即是到达任意一个点后走向关键点再回来的距离。

也就是说，设 $a_i$ 表示此点 $i$ 距离最近一个关键点的距离，答案等于 $dis(x,y)+\min_{i\in\text{路径上所有点}}a_i$。

$a_i$ 用 djikstra 求（初始关键点全部入堆。复杂度相当于建超级源点连所有关键点边权为 $0$，依然是 $O(m\log m)$），然后路径上最小值用树链剖分即可，其中线段树可以换成st表（代码里是线段树）。

#### code:
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lson (pos<<1)
#define rson (pos<<1|1)
#define pii pair<int,int> 
#define fr first
#define sc second 
#define mk make_pair
#define gczakioi true
#define inx int i=h[u],v=(~i)?edge[i].v:0,w=(~i)?edge[i].w:0;~i;i=edge[i].nx,v=(~i)?edge[i].v:0,w=(~i)?edge[i].w:0
int read(){int x=0,f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}x=c-'0';c=getchar();while(c<='9'&&c>='0'){x*=10;x+=c-'0';c=getchar();}return x*f;}
const int MAXN=200010,inf=100000000000000;
int n,m,k,a[MAXN];
//链式前向星建图
struct Edge{int v,w,nx;}edge[MAXN<<1];int h[MAXN],CNT;void init(){memset(h,-1,sizeof(h));CNT=0;}
void add_side(int u,int v,int w){edge[++CNT]={v,w,h[u]};h[u]=CNT;edge[++CNT]={u,w,h[v]};h[v]=CNT;}
//树剖
int sd[MAXN],fa[MAXN],son[MAXN],siz[MAXN],dfn[MAXN],cnt,top[MAXN],tp,dy[MAXN];
int dp[MAXN];
void dfs(int u,int lst){
	int mx=0;
	fa[u]=lst;siz[u]++;
	for(inx){
		if(lst==v)continue;
		sd[v]=sd[u]+1;dp[v]=dp[u]+w;
		dfs(v,u);
		siz[u]+=siz[v];
		if(siz[v]>mx){
			son[u]=v;
			mx=siz[v];
		}
	}
}
void dfs2(int u,int lst){
	dfn[u]=++cnt;top[u]=tp;dy[cnt]=u;
	if(son[u])dfs2(son[u],u);
	for(inx)if(lst!=v&&son[u]!=v){
		tp=v;
		dfs2(v,u);
	}
}
//线段树
int t[MAXN<<2];
void pushup(int pos){
	t[pos]=min(t[lson],t[rson]);
}
void build(int pos,int l,int r){
	if(l==r){
		t[pos]=a[dy[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(lson,l,mid);build(rson,mid+1,r);
	pushup(pos);
}
int query(int pos,int l,int r,int ql,int qr){
	if(ql<=l&&qr>=r){
		return t[pos];
	}
	int mid=(l+r)>>1,res=inf;
	if(ql<=mid)res=query(lson,l,mid,ql,qr);
	if(qr>mid)res=min(res,query(rson,mid+1,r,ql,qr));
	pushup(pos);
	return res;
}
int qry(int x,int y){
	int tmp=inf,res=dp[x]+dp[y];
	while(top[x]!=top[y]){
		if(sd[top[x]]<sd[top[y]])swap(x,y);
		tmp=min(tmp,query(1,1,n,dfn[top[x]],dfn[x]));
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y])swap(x,y);
	tmp=min(tmp,query(1,1,n,dfn[x],dfn[y]));
	return res-dp[x]*2+tmp*2;
}
//dijkstra
priority_queue<pii>q;
bool vis[MAXN];
void bfs(){
	memset(a,0x3f,sizeof(a));
	for(int i=1;i<=k;i++){
		int tmp=read();
		a[tmp]=0;
		q.push(mk(0,tmp));
	}
	while(!q.empty()){
		int u=q.top().sc;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(inx)if(a[u]+w<a[v]){
			a[v]=a[u]+w;
			q.push(mk(-a[v],v));
		}
	}
}
void slv(){
    init();
	n=read(),m=read(),k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add_side(u,v,w);
	}
	bfs();
	dfs(1,1);tp=1;
	dfs2(1,1);
	build(1,1,n);
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		printf("%lld\n",qry(x,y));
	}
}
signed main(){
	slv();
    return 0;
} 	
```

---

## 作者：HEzzz (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P9432)

前置芝士：树上动态规划，最近公共祖先，倍增

## 解析


#### 思路

我们先考虑**不需要**经过**至少一个**关键点的路径的最短距离，显然我们只需要求出最近公共祖先 $lca$，答案显然为 $u$ 到 $lca$ 的距离和 $v$ 到 $lca$ 的距离之和。

但是如果要经过**至少一个**关键点。为了得到最短距离，那经过的关键点一定在 $u$ 到 $v$ 的简单路径上的结点的子树内。

#### 实现过程

由此我们可以定义 $dp[i]$ 表示结点 $i$ 到离它最近的关键点的距离。


如何去求 $dp[i]$ 呢。

- 如果结点 $i$ 是关键点，显然 $dp[i]$ 为 $0$。
- 如果结点 $i$ 不是关键点，我们可以使用两次深度优先搜索 $dfs$，第一次是从父亲结点转移到子节点，第二次则是从子节点转移到父亲结点。

但是在我们求 $u$ 到 $v$ 的简单路径上的结点 $i$ 中 $dp[i]$ 最小时，我们不能直接暴力去跑图，所以我们可以用倍增去维护一段结点的 $dp[i]$ 最小值。类似于求最近公共祖先的倍增。

最后要**注意**的是我们求出 $dp[i]$ 的最小值后，要把它乘 $2$，因为我们是要**故意**离开简单路径，去经过关键点的。

## code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--) 
#define int LL
using namespace std;
typedef long long LL;
typedef double db;
const int N=1e5+5,INF=1e16;
int n,q,k;
int dep[N],f[N][20],dp[N],val[N],mins[N][20];
struct node
{
	int to,nxt,w;
}e[N<<1];
int cnt,head[N];
void add(int u,int v,int w)
{
	cnt++;
	e[cnt].to=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs1(int u,int fa)
{ 
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	_rep(i,1,19) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		val[v]=val[u]+e[i].w;
		dfs1(v,u);
		dp[u]=min(dp[u],dp[v]+e[i].w);
	} 
} 
void dfs2(int u,int fa)
{
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dp[v]=min(dp[v],dp[u]+e[i].w);
		dfs2(v,u);
	}
}
void dfs3(int u,int fa)
{
	mins[u][0]=dp[u];
	_rep(i,1,19) mins[u][i]=min(mins[u][i-1],mins[f[u][i-1]][i-1]);
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs3(v,u);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	_antirep(i,19,0) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	_antirep(i,19,0) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i]; 
	return f[x][0];
}
int calc(int x,int y)
{
	int res=INF;
	if(x==y) return dp[x];
	_antirep(i,19,0) 
		if(dep[f[x][i]]>=dep[y]) 
		{
			res=min(res,mins[x][i]);
			x=f[x][i];
		} 
    res=min(res,dp[y]);
	return res;
}
signed main()
{        
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>q>>k;
	_rep(i,1,n) dp[i]=INF;
	_rep(i,2,n)
	{
		int u,v,w;
		cin>>u>>v>>w;
		add(u,v,w);
		add(v,u,w); 
	}
	_rep(i,1,k) 
	{
		int x;
		cin>>x; 
        dp[x]=0;
	} 
	dfs1(1,0);
	dfs2(1,0);
	dfs3(1,0);
	while(q--)
	{
		int u,v;
		cin>>u>>v;
		int top=lca(u,v);
        int dis=val[u]+val[v]-2*val[top];
		if(u==v) cout<<2*dp[u]<<"\n"; 
		else cout<<dis+2*min(calc(u,top),calc(v,top))<<"\n";  
	}
    return 0;
}
```

结尾撒花，如有不懂之处请私信，谢谢

---

## 作者：OneLeft (赞：0)

## 题意
给你一个无根树，每条树边都有边权，再给你若干特殊点和若干询问 $u$ 和 $v$，问从 $u$ 到 $v$ 经过至少 $1$ 个特殊点最小的边权和。

## 思路
先将无根树转化成以 $1$ 为根的有根树，然后将问腿分成两部分，一个是求 $u$ 到 $v$ 的边权和，一个是求距离节点 $u$ 到节点 $v$ 的简单路径上某个节点最近的特殊节点，第一个很好求，第二个则可以用 DP 去求。

设 $dp_u$ 表示距离节点 $u$ 最近的特殊点，对此我们可以进行先 DFS 一次找出所有节点离以它为根的子树（包括该节点）中特殊点最小的边权，转移方程为 $dp_u=\min(dp_u,dp_v+w)$（$u$ 为该节点，$v$ 为子节点，$w$ 为边权），再进行另一次 DFS 找出距离某个节点最近的特殊点，转移方程为 $dp_v=\min(dp_v,dp_u+w)$，然后问题就解决了。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+5,M=35,INF=(int)1e18+5;
struct Edge
{
	int v,w;
};
bool flag[N];
int n,q,m,u,v,w,dp[N];
int Log[N],fa[N][M],val[N][M],minn[N][M],deep[N];
list<Edge>edge[N];
void build(int u,int v,int w)
{
    edge[u].push_back((Edge){v,w});
    edge[v].push_back((Edge){u,w});
}
void DFS1(int u,int fath)
{
	if(flag[u])dp[u]=0;
    for(auto i:edge[u])
    {
    	int v=i.v,w=i.w;
        if(v==fath)continue;
        DFS1(v,u);
		dp[u]=min(dp[u],dp[v]+w);
    }
}
void DFS2(int u,int fath)
{
    for(auto i:edge[u])
    {
    	int v=i.v,w=i.w;
        if(v==fath)continue;
		dp[v]=min(dp[v],dp[u]+w);
        DFS2(v,u);
    }
}
void DFS3(int u,int fath,int value)
{
    deep[u]=deep[fath]+1;
    fa[u][0]=fath;
    val[u][0]=value;
    minn[u][0]=dp[u];
    for(int i=1;i<=Log[n];i++)
    {
    	fa[u][i]=fa[fa[u][i-1]][i-1];
    	val[u][i]=val[u][i-1]+val[fa[u][i-1]][i-1];
    	minn[u][i]=min(minn[u][i-1],minn[fa[u][i-1]][i-1]);
    }
	for(auto i:edge[u])
    {
    	int v=i.v,w=i.w;
        if(v==fath)continue;
        DFS3(v,u,w);
    }
}
int LCA(int u,int v)
{
	int res1=0,res2=INF;
    if(deep[u]<deep[v])
    	swap(u,v);
    while(deep[u]>deep[v])
    {
    	res1+=val[u][Log[deep[u]-deep[v]]];
    	res2=min(res2,minn[u][Log[deep[u]-deep[v]]]);
    	u=fa[u][Log[deep[u]-deep[v]]];
    }
    if(u==v)
    {
    	res2=min(res2,dp[u]);
    	return res1+res2*2;
    }
    for(int i=Log[n];i>=0;i--)
    {
    	if(fa[u][i]!=fa[v][i])
    	{
    		res1+=val[u][i]+val[v][i];
    		res2=min(res2,min(minn[u][i],minn[v][i]));
    		u=fa[u][i],v=fa[v][i];
    	}
    }
    res1+=val[u][0]+val[v][0];
    res2=min(res2,min(min(minn[u][0],minn[v][0]),dp[fa[u][0]]));
    return res1+res2*2;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
    cin>>n>>q>>m;
    for(int i=2;i<=n;i++)
    	Log[i]=Log[i/2]+1;
    for(int i=1;i<n;i++)
        cin>>u>>v>>w,build(u,v,w);
    for(int i=1;i<=m;i++)
    	cin>>u,flag[u]=true;
    for(int i=1;i<=n;i++)
    {
    	dp[i]=INF;
    	for(int j=0;j<=Log[n];j++)
    		minn[i][j]=INF;
    }
    DFS1(1,0);
    DFS2(1,0);
    DFS3(1,0,0);
    for(int i=1;i<=q;i++)
    {
        cin>>u>>v;
    	cout<<LCA(u,v)<<'\n';
    }
    return 0;
}
```

---

## 作者：Loser_Syx (赞：0)


考虑一条 $u \rightarrow v$ 的路径，因为我们想要经过至少一个关键点，而我们为了路径最短，所以我们经过的关键点个数一定是越少越好，故我们只需要保证经过一个关键点即可。

于是考虑先跑出每个点最近的关键点的距离是多少，具体可以使用 dijkstra，初始关键点的距离为 $0$ 扩展即可。  
得到距离之后考虑维护一个路径上的每个点到其最近的关键点的距离，因为我们只需要过一个关键点，所以可以直接求距离的 $\min$。  
具体地，考虑树剖，因为每条链上面的 dfs 序是连续的，于是可以分为每条链进行一个求 $\min$ 操作，得到答案。因为要跑出去再回来，所以要乘 $2$。

$\min$ 值的过程可以在 lca 的过程中求出，而 $u \rightarrow v$ 的路径长度可以用以 $1$ 为根从根出发的 $dis_u + dis_v - 2 \times dis_{\text{lca}(u,v)}$ 计算。

复杂度瓶颈在树剖和维护 $\min$ 值的数据结构，ST 表的话是 $O(n \log n)$，线段树多个 $\log$。

```cpp
const int N=1e5+19;
int dfn[N], dep[N], fa[N], son[N], siz[N], top[N], cnt, n, k, T, dist[N], disson[N], a[N], lg[N];
vector<pair<int, int> > g[N];
void dfs1(int u, int f) {
	dep[u] = dep[f] + 1;
	fa[u] = f;
	siz[u] = 1; 
	for (const auto [i, j] : g[u]) {
		if (i != f) {
			dfs1(i, u);
			siz[i] += u;
			if (siz[i] > siz[son[u]]) son[u] = i, disson[u] = j;
		}
	}
}
void dfs2(int u, int f, int dis) {
	dfn[u] = ++cnt;
	top[u] = f;
	dist[u] = dis;
	if (son[u]) dfs2(son[u], f, dis+disson[u]);
	for (const auto [i, j] : g[u]) {
		if (i != fa[u] && i != son[u]) dfs2(i, i, dis+j);
	}
}
int st[N][25];
signed main() {
	read(n, T, k);
	for (int i=1,u,v,w;i<n;++i) {
		read(u,v,w);
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	dfs1(1, 0); dfs2(1, 1, 0);
	memset(a, 0x3f, sizeof a);
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
	for (int i=1,x;i<=k;++i) a[(x=read())]=0, q.push({0, x});
	while (!q.empty()) {
		auto u = q.top();
		q.pop();
		if (a[u.second] != u.first) continue;
		for (const auto [i, j] : g[u.second]) {
			if (a[i] > u.first + j) {
				a[i] = u.first + j;
				q.push({a[i], i});
			}
		}
	}
	for (int i=1;i<=n;++i) st[dfn[i]][0] = a[i]*2;
	for (int i=2;i<=n;++i) lg[i] = lg[i>>1]+1;
	for (int i=1;i<=lg[n];++i) {
		for (int j=1;j+(1<<i)-1<=n;++j) {
			st[j][i] = min(st[j][i-1], st[j+(1<<(i-1))][i-1]);
		}
	}
	auto ask = [&](int l, int r) {int t = lg[r - l + 1]; return min(st[l][t], st[r - (1 << t) + 1][t]);};
	while (T--) {
		int x, y; read(x, y);
		int u=x,v=y;
		int mn=1e18;
		while (top[x] != top[y]) {
			if (dep[top[x]] > dep[top[y]]) swap(x, y);
			smin(mn, ask(dfn[top[y]], dfn[y]));
			y = fa[top[y]];
		}
		if (dep[x] > dep[y]) swap(x, y);
		smin(mn, ask(dfn[x], dfn[y]));
		write(mn+dist[u]+dist[v]-2*dist[x], '\n');
	}
	return 0;
}
```

---

## 作者：SuperCowHorse (赞：0)

首先呢，题目说要求两个点之间**经过关键点**的最短路径，我们暂且不看这个“关键点”，先看两点之间的路径该如何求？

很明显的套路：$dist(u,v)=d_u+d_v-2\times d_{LCA(u,v)}$，其中，$d_i$ 表示点 $1$ 到点 $i$ 的路径长度。$d$ 数组可以通过一次 $\operatorname{dfs}$ 来求出。

那么显然，$u$ 到 $v$ 经过关键点的最短路径，就是：$u$ 到 $v$ 的最短路径加上 **$u$ 到 $v$ 路径上离关键点最近距离的 $2$ 倍**。

假设 $dis_i$ 表示离 $i$ 最近的关键点到 $i$ 的距离，那么答案为：$ans=d_u+d_v-2\times d_{LCA(u,v)}+2\times \min\{dis_i\}$，其中 $i$ 表示 $u$ 到 $v$ 路径上的任意一点。

最后就是 $dis$ 数组了。这该怎么办？

我们可以把每一个关键点塞进优先队列里，跑多源 $\operatorname{dijkstra}$，然后直接求 $dis$ 数组就行了。

剩下就是很裸的树剖板子了：先在 $\operatorname{dfs1}$ 中预处理 $d$ 数组，然后开一颗线段树维护区间 $dis$ 最小值，即可。

还有 $\operatorname{LCA}$？树剖顺带着求就行了。~~我才不告诉你我从来不写倍增 LCA 呢。~~

Code:
``` cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int n,Q,k;
struct edge{
	int v,w,next;
}e[maxn<<1];int head[maxn],cnt;
inline void add(int u,int v,int w){
	e[++cnt]=edge{v,w,head[u]};
	head[u]=cnt;
}
int a[maxn];
int siz[maxn],fa[maxn],son[maxn],d[maxn],dep[maxn];
int top[maxn],rk[maxn],id[maxn],tot;
inline void dfs1(int u,int f){
	siz[u]=1;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==f) continue;
		fa[v]=u;d[v]=d[u]+e[i].w;//预处理 d 数组
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[son[u]]){
			son[u]=v;
		}
	}
}
inline void dfs2(int u){
	id[u]=++tot;rk[tot]=u;
	top[u]=u==son[fa[u]]?top[fa[u]]:u;
	if(son[u]) dfs2(son[u]);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v);
	}
}
inline int LCA(int u,int v){//求 LCA
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}
struct node{//堆优化
	int pos,dis;
	inline bool operator <(const node &tmp)const{
		return tmp.dis<dis;
	}
};
int dis[maxn];bool vis[maxn];
inline void dijkstra(){//dijkstra 求 dis 数组
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	priority_queue<node>q;
	for(int i=1;i<=k;++i){
		q.push(node{a[i],0});
		dis[a[i]]=0;
	}
	while(!q.empty()){
		int u=q.top().pos;q.pop();
		vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w){
				dis[v]=dis[u]+e[i].w;
				if(!vis[v]) q.push(node{v,dis[v]});
			}
		}
	}
}
inline int ls(int p){return p<<1;}
inline int rs(int p){return p<<1|1;}
#define lson p<<1,l,mid
#define rson p<<1|1,mid+1,r
struct SegmentTree{//线段树求最小值
	int l,r,pre;
}t[maxn<<2];
inline void Update(int p){
	int l=ls(p),r=rs(p);
	t[p].pre=min(t[l].pre,t[r].pre);
}
inline void Pushdown(int p){}//这里没有修改操作，但是我的由于某个同学会在写线段树时忘写 Pushdown 而在赛时爆零，所以为了以防万一，养成良好习惯，就加了
inline void build(int p,int l,int r){
	t[p].l=l;t[p].r=r;
	if(l==r){
		t[p].pre=dis[rk[l]];
		return;
	}
	int mid=(l+r)>>1;
	build(lson);build(rson);
	Update(p);
}
inline void Modify(int p,int l,int r,int lx,int rx){}//同上
inline int Query(int p,int l,int r,int lx,int rx){
	if(l>=lx&&r<=rx){
		return t[p].pre;
	}
	Pushdown(p);
	int mid=(l+r)>>1;
	int ans=2e9;
	if(lx<=mid) ans=min(ans,Query(lson,lx,rx));
	if(rx>mid)  ans=min(ans,Query(rson,lx,rx));
	return ans;
}
inline int dist(int u,int v){//求最短距离
	int ans=2e9,now=d[u]+d[v]-2*d[LCA(u,v)];
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans=min(ans,Query(1,1,n,id[top[u]],id[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans=min(ans,Query(1,1,n,id[u],id[v]));
	return now+2*ans;
}
signed main(){
	scanf("%d%d%d",&n,&Q,&k);
	for(int i=1,u,v,w;i<n;++i){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);add(v,u,w);
	}
	for(int i=1;i<=k;++i){
		scanf("%d",&a[i]);
	}
	dfs1(1,0);dfs2(1);
	dijkstra();build(1,1,n);
	for(int u,v;Q;--Q){
		scanf("%d%d",&u,&v);
		printf("%d\n",dist(u,v));
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：0)

这个人赛时只过了这题，但是同学 @[sinsop90](https://www.luogu.com.cn/user/141599) 赛时只没过这题，怎么会是呢？

考虑到 $s,t$ 之间路径必须经过关键点，假设这个关键点为 $k$，那么路径形式一定是 $s\to k\to t$（废话）。

画一下图发现这条路径的长度等于 $s\to t$ 的**简单路径**长度加上 $k$ **挂到 $s\to t$ 简单路径这条链上所经过的路径**长度的 $2$ 倍。

即：

![](https://cdn.luogu.com.cn/upload/image_hosting/4f31fyyc.png)

考虑 $1\to 7\to 9$ 这条路径，其长度相当于 $1\to 2\to 4\to 9$ 简单路径长度加上 $7\to 3\to 2$ 这条路径长度的 $2$ 倍。

设 $S$ 为关键点的集合，$d(k,s\to t)$ 表示 $k$ 挂到 $s\to t$ 路径的长度。

对于一个询问 $(s,t)$，$s\to t$ 路径长度时容易求的，我们只需要计算 $\min\limits_{k\in S}d(k,s\to t)$ 即可。

考虑到 $k$ 挂到 $s\to t$ 路径上的那个点是唯一且在路径 $s\to t$ 上的（上图中 $k=7,s=1,t=9$，$7$ 挂到 $1\to 9$ 的点是 $2$），可以预处理出对于每个点 $u$，离它最近的关键点的距离 $f_u$，那么 $\min\limits_{k\in S}d(k,s\to t)=\min\limits_{u\in \{s\to t\}}f_u$，$\{s\to t\}$ 表示 $s\to t$ **简单路径**上的点构成的集合（包括 $s,t$）。

这个 $f_u$ 显然可以通过树形 dp 求出，问题转换为求 $s\to t$ 路径上的点的 $f$ 值的最小值，树剖解决即可。因为我用的是线段树，复杂度 $O(n\log^2 n)$，其实可以 st 表做到 $O(n\log n)$。

[赛时代码](https://www.luogu.com.cn/paste/34lm0xui)，写得有点丑陋。

---

