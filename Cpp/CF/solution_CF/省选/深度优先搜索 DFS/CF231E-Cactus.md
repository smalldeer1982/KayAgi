# Cactus

## 题目描述

A connected undirected graph is called a vertex cactus, if each vertex of this graph belongs to at most one simple cycle.

A simple cycle in a undirected graph is a sequence of distinct vertices $ v_{1},v_{2},...,v_{t} $ $ (t&gt;2) $ , such that for any $ i $ $ (1<=i&lt;t) $ exists an edge between vertices $ v_{i} $ and $ v_{i+1} $ , and also exists an edge between vertices $ v_{1} $ and $ v_{t} $ .

A simple path in a undirected graph is a sequence of not necessarily distinct vertices $ v_{1},v_{2},...,v_{t} $ $ (t&gt;0) $ , such that for any $ i $ $ (1<=i&lt;t) $ exists an edge between vertices $ v_{i} $ and $ v_{i+1} $ and furthermore each edge occurs no more than once. We'll say that a simple path $ v_{1},v_{2},...,v_{t} $ starts at vertex $ v_{1} $ and ends at vertex $ v_{t} $ .

You've got a graph consisting of $ n $ vertices and $ m $ edges, that is a vertex cactus. Also, you've got a list of $ k $ pairs of interesting vertices $ x_{i},y_{i} $ , for which you want to know the following information — the number of distinct simple paths that start at vertex $ x_{i} $ and end at vertex $ y_{i} $ . We will consider two simple paths distinct if the sets of edges of the paths are distinct.

For each pair of interesting vertices count the number of distinct simple paths between them. As this number can be rather large, you should calculate it modulo $ 1000000007 $ ( $ 10^{9}+7 $ ).

## 样例 #1

### 输入

```
10 11
1 2
2 3
3 4
1 4
3 5
5 6
8 6
8 7
7 6
7 9
9 10
6
1 2
3 5
6 9
9 2
9 3
9 10
```

### 输出

```
2
2
2
4
4
1
```

# 题解

## 作者：chenxumin1017 (赞：6)

# 题意
给定一张 $n$ 个点 $m$ 条边的图，保证图中任意一点只属于一个简单环。

给定两点，求两点间简单路径条数。

$1 \le n,m, k \le 10^{5}$

# 思路
在任意一个简单环，都有两种走法，通过这个性质，题目不就变为了求两点间简单路径上环的数量。

这个问题，在原图上显然不好做！

不如进行缩点，此时就变为了树上两点间最短路径上经过缩点后的点的数量。这不就变成了树上差分与最近公共祖先的板题了吗？

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int, int>;
const int MAXN = 1e5 + 5, MAXL = 20, MOD = 1e9 + 7;;
int n, m, q, vis[MAXN], dcnt, y[MAXN], dis[MAXN], f[MAXL][MAXN], c[MAXN], sum[MAXN], sum2[MAXL][MAXN];
vector<int> v[MAXN], vv, s[MAXN];
set<int> v3[MAXN];
vector<pii> v2;
void dfs(int x, int fa){
  //cout << x << ' ' << fa << '\n';
  if(vis[x] == 1){
    ++dcnt;
    int flag = 0;
    for(int i = 0; i < vv.size(); i++){
      if(vv[i] == x)flag = 1;
      if(!y[vv[i]])y[vv[i]] = dcnt * flag;
    }
    return;
  }
  if(vis[x]) return;
  vis[x] = 1;
  vv.push_back(x);
  for(int i : v[x]){
    if(i != fa){
      dfs(i, x);
    }
  }
  vv.pop_back();
  vis[x] = 2;
}
void DFS(int x, int fa){
  f[0][x] = fa;
  sum2[0][x] = c[fa];
  dis[x] = dis[fa] + 1;
  for(int i = 1; i < MAXL; i++){
    f[i][x] = f[i - 1][f[i - 1][x]];
    sum2[i][x] = sum2[i - 1][f[i - 1][x]] + sum2[i - 1][x];
  }
  for(int i : s[x]){
    if(i != fa){
      DFS(i, x);
    }
  }
}

int LCA(int x, int y){
  if(dis[x] < dis[y]){
    swap(x, y);
  }
  int len = dis[x] - dis[y], ans = 0;
  for(int i = MAXL - 1; i >= 0; i--){
    if((len >> i) & 1){
      ans += sum2[i][x];
      x = f[i][x];

    }
  }
  if(x == y){
    return ans - c[x];
  }
  for(int i = MAXL - 1; i >= 0; i--){
    if(f[i][x] != f[i][y]){
      ans += sum2[i][x] + sum2[i][y];
      x = f[i][x];
      y = f[i][y];
    }
  }
  return ans + c[f[0][x]];
}
signed main(){
  ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> n >> m;
  for(int i = 1, x, y; i <= m; i++){
    cin >> x >> y;
    v[x].push_back(y);
    v[y].push_back(x);
    v2.push_back({x, y});
  }
  for(int i = 1; i <= n; i++){
    dfs(i, 0);
  }
  for(int i = 1; i <= n; i++){
    if(!y[i]) y[i] = ++dcnt;
    else c[y[i]] = 1;
  }
  for(int i = 0; i < v2.size(); i++){
    if(y[v2[i].first] != y[v2[i].second]){
      v3[y[v2[i].first]].insert(y[v2[i].second]);
      v3[y[v2[i].second]].insert(y[v2[i].first]);
    }
  }
  for(int i = 1; i <= dcnt; i++){
    for(int j : v3[i]){
      s[i].push_back(j);
    }
  }
  DFS(1, 0);
  cin >> q;
  sum[0] = 1;
  for(int i = 1; i <= 1e5; i++){
    sum[i] = sum[i - 1] * 2 % MOD;
  }
  for(int i = 1, l, r; i <= q; i++){
    cin >> l >> r;
    l = y[l], r = y[r];
    int z = LCA(l, r);
    cout << sum[z + c[l] + c[r]] << '\n';
  }
  return 0;
}
```

---

## 作者：2huk (赞：3)

- 给定一张 $n$ 个点，$m$ 条边的无向图，保证每个点至多在一个简单环中。$k$ 次询问，每次给出 $x, y$，求出从 $x$ 走到 $y$ 的简单路径数量。答案对 $10^9 + 7$ 取模。
- $n, m, k \le 10^5$。

样例图是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/6dxbukxg.png)

假如要从 $5 \to 9$，显然会经过一个环 $(6,7,8)$。那么穿过这个环的方式有两种：$6 \to 7$ 或 $6 \to 8 \to 7$。

不难发现对于穿过每一个环都有两种方案。所以答案即 $2^k$，其中 $k$ 表示两点之间环的数量。

我们可以将原图进行处理，将环缩成一个点，即将[边双连通分量](https://www.luogu.com.cn/problem/P8436)缩点。由于这是一棵点仙人掌，所以缩点后的形态一定是一颗树。那么在树上查询就是平凡的了。

---

## 作者：Egg_eating_master (赞：3)

我们发现，通过每个环的合法路径数都有两种。设从 $x$ 到 $y$ 的路径上有 $d$ 个环，那么答案就是 $2^d$。

问题转化为求两点路径间有多少个环。

我们考虑缩边双。由于题目保证图是一个点仙人掌，因此缩完图之后一定是一棵树。此时我们只需要求两点的树上距离即可。

用 LCA 维护一下就可以了。

时间复杂度 $O(n+m+q\log n)$。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
int n, m, q;
int head[100005];
int u[1000005], v[1000005], nxt[1000005];
int low[100005], dfn[100005];
bool cut[1000005];
int dcc[100005], size[100005];
int tot = 1, cnt, lza;
vector<int> a[100005];
int f[100005], dep[100005];
int nmsl[100005], son[100005];
int top[100005];
int len[100005];
void add(int x, int y) {
	tot++;
	u[tot] = x; v[tot] = y; 
	nxt[tot] = head[x]; head[x] = tot;
}
void dfs(int ed, int x) {
	low[x] = dfn[x] = ++cnt;
	for (int i = head[x]; i; i = nxt[i]) {
		int y = v[i];
    	if (!dfn[y]) {
    		dfs(i, y); low[x] = min(low[x], low[y]);
    		if (dfn[x] < low[y]) cut[i] = cut[i ^ 1] = 1;
    	} else if (i != (ed ^ 1)) low[x] = min(low[x], dfn[y]);
	}
} 
void dfs2(int x, int cnt) {
	dcc[x] = cnt; size[cnt]++;
    for (int i = head[x]; i; i = nxt[i]) {
    	int y = v[i];
    	if (dcc[y] || cut[i]) continue;
    	dfs2(y, cnt);
    }
}//缩边双
void dfs1(int fa, int x) {
	f[x] = fa; dep[x] = dep[fa] + 1; len[x] = len[fa] + (size[x] > 1); nmsl[x] = 1;
	for (int i = 0; i < a[x].size(); i++) {
		int y = a[x][i];
		if (y == fa) continue;
		dfs1(x, y);
		nmsl[x] += nmsl[y];
		if (son[x] == 0 || nmsl[son[x]] < nmsl[y]) son[x] = y;
	}
}
void dfs3(int x, int t) {
	top[x] = t;
	if (son[x] == 0) return;
	dfs3(son[x], t);
	for (int i = 0; i < a[x].size(); i++) {
		int y = a[x][i];
		if (y == f[x] || y == son[x]) continue;
		dfs3(y, y);
	}
}//预处理树剖求LCA
int ask(int x, int y) {
    while (top[x] != top[y]) {
    	if (dep[top[x]] < dep[top[y]]) swap(x, y);
    	x = f[top[x]];
	}
	return dep[x] < dep[y] ? x : y;
}
ll power(int a, int b) {
	ll res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod; b >>= 1;
	}
	return res;
}
int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v;
		add(u, v); add(v, u);
	}
	for (int i = 1; i <= n; i++)
	    if (!dfn[i]) dfs(0, i);
	for (int i = 1; i <= n; i++)
	    if (!dcc[i])
	        dfs2(i, ++lza);
	for (int i = 1; i <= n; i++)
	    for (int j = head[i]; j; j = nxt[j]) {
	    	int x = v[j];
        	if (dcc[i] != dcc[x]) a[dcc[i]].push_back(dcc[x]);
    	}
	dfs1(0, 1); dfs3(1, 1);
	cin >> q;
	for (int i = 1; i <= q; i++) {
		int x, y; cin >> x >> y; x = dcc[x], y = dcc[y];
		int lca = ask(x, y);
		cout << power(2, len[x] + len[y] - len[lca] * 2 + (size[lca] > 1)) << endl;//由于求的是点权和，因此特判lca这个点
	}
	return 0;
}
```


---

## 作者：zztqwq (赞：3)

# Codeforces 231E

## Solution

把所有环缩一下，记 $u,v$ 路径上原本是环的点的数量为 $d$，那么答案就是 $2^d$。

缩点可以用边双，缩完之后是棵树，直接倍增 LCA 即可。

~~一遍过工程题的感觉真爽~~

## Code

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
const int N=2e5+10,M=2e5+10;
int Head[N],Ver[M],Nxt[M],Tot=1;
void Add(int x,int y)
{
	Ver[++Tot]=y;
	Nxt[Tot]=Head[x];
	Head[x]=Tot; 
}
bool bridge[M];
int dfn[N],low[N],num=0;
void tarjan(int x,int in)
{
	dfn[x]=low[x]=++num;
	for(int i=Head[x];i;i=Nxt[i])
	{
		int y=Ver[i];
		if(!dfn[y])
		{
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x])
				bridge[i]=bridge[i^1]=1;
		}
		else if(i!=(in^1))
			low[x]=min(low[x],dfn[y]);
	}
}
int col[N],cont[N],dis[N];
void dfs(int x,int c)
{
	cont[c]++;
	col[x]=c;
	for(int i=Head[x];i;i=Nxt[i])
	{
		int y=Ver[i];
		if(bridge[i]||col[y])continue;
		dfs(y,c);
	}
}
int head[N],ver[M],nxt[M],tot=0;
void add(int x,int y)
{
	ver[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfs1(int x,int f)
{
	dis[x]+=(cont[x]>1);
	for(int i=head[x];i;i=nxt[i])
	{
		int y=ver[i];
		if(y==f)continue;
		dis[y]=dis[x];
		dfs1(y,x);
	}
}
bool vis[N];int dep[N],fa[N][30],t;
void bfs()
{
	queue<int> que;
	que.push(1);
	vis[1]=1;
	dep[1]=1;
	while(!que.empty())
	{
		int x=que.front();que.pop();
		for(int i=head[x];i;i=nxt[i])
		{
			int y=ver[i];
			if(vis[y])continue;
			dep[y]=dep[x]+1;
			fa[y][0]=x;
			for(int j=1;j<=t;j++)fa[y][j]=fa[fa[y][j-1]][j-1];
			vis[y]=1;
			que.push(y);
		}
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=t;i>=0;i--)
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	if(x==y) return x;
	for(int i=t;i>=0;i--)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int qpow(int a,int n)
{
	a%=1000000007; int ans=1;
	while(n)
	{
		if(n&1)ans=(long long)ans*a%1000000007;
		a=(long long)a*a%1000000007;
		n>>=1; 
	}
	return ans;
}
int main()
{
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int u,v;scanf("%d%d",&u,&v);
		Add(u,v);Add(v,u);
	}
	tarjan(1,-1);
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(!col[i])
			dfs(i,++cnt); 
	t=(int)(log(n)/log(2))+1;
	for(int i=1;i<=n;i++)
		for(int j=Head[i];j;j=Nxt[j])
			if(col[i]!=col[Ver[j]])
				add(col[i],col[Ver[j]]);
	dfs1(1,0);
	bfs();
	int q;scanf("%d",&q);
	while(q--)
	{
		int x,y;scanf("%d%d",&x,&y);
		int l=lca(col[x],col[y]);
		printf("%d\n",
		qpow(2,dis[col[x]]+dis[col[y]]-dis[l]-dis[fa[l][0]]));
	}
	return 0;
}
```



---

## 作者：WrongAnswer_90 (赞：2)

[CF231E Cactus](https://www.luogu.com.cn/problem/CF231E)

点仙人掌的性质：每个点最多只在一个环里。

![image.png](https://s2.loli.net/2023/08/28/JBc4Dr8FA5imX6R.png)

对于 $u,v$ 之间的路径，显然一定是由一些链和一些环拼接而成的。

对于链，只能按照唯一的方式行走。

对于环，有两种走的方案：顺时针和逆时针走。

各个环间互不影响，乘法原理得到答案就是 $2$ 的环个数次方。

边双所点后维护前缀和，变成树上 LCA 问题，倍增或树剖或 tarjan 即可。

```cpp
inline int power(int x,int y)
{
	int ans=1;
	for(;y;x=x*x%MOD,y>>=1)if(y&1)ans=ans*x%MOD;
	return ans;
}
int n,m,q,tot,cnt,num,col[300001],val[300001],dep[300001],fa[300001][21],x[300001],y[300001],dfn[300001],low[300001],cut[200001],head[300001],to[500001],nex[500001];
vector<int> T[300001];
stack<int> st;
inline void add(int x,int y){to[++cnt]=y,nex[cnt]=head[x],head[x]=cnt;}
void tarjan(int k,int from)
{
	dfn[k]=low[k]=++tot,st.push(k);
	for(int i=head[k];i;i=nex[i])
	{
		if(i==(from^1))continue;
		if(!dfn[to[i]])
		{
			tarjan(to[i],i),low[k]=min(low[k],low[to[i]]);
			if(low[to[i]]>dfn[k])cut[i]=cut[i^1]=1;
		}
		else low[k]=min(low[k],dfn[to[i]]);
	}
	if(dfn[k]==low[k])
	{
		col[k]=++num;int y=1;
		while(st.top()!=k)++y,col[st.top()]=num,st.pop();
		st.pop();
		if(y>1)val[num]=1;
	}
}
void dfs(int k,int father)
{
	val[k]+=val[father],dep[k]=dep[father]+1,fa[k][0]=father;
	for(int i=1;i<=20;++i)fa[k][i]=fa[fa[k][i-1]][i-1];
	for(auto to:T[k])if(to!=father)dfs(to,k);
}
inline int LCA(int x,int y)
{
	if(dep[x]>dep[y])swap(x,y);
	for(int i=20;i>=0;--i)if(dep[fa[y][i]]>=dep[x])y=fa[y][i];
	for(int i=20;i>=0;--i)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
	return x==y?x:fa[x][0];
}
inline void mian()
{
	cnt=1,read(n,m);int a,b,lca;
	for(int i=1;i<=m;++i)read(x[i],y[i]),add(x[i],y[i]),add(y[i],x[i]);
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i,0);
	for(int i=1;i<=m;++i)if(col[x[i]]!=col[y[i]])T[col[x[i]]].eb(col[y[i]]),T[col[y[i]]].eb(col[x[i]]);
	dfs(1,0),read(m);
	while(m--)read(a,b),a=col[a],b=col[b],lca=LCA(a,b),write(power(2,val[a]+val[b]-val[lca]-val[fa[lca][0]]),'\n');
}
```

---

## 作者：Inter12 (赞：1)

匆忙写的，如有错误可以指出。

### 题目概括

给定一个**简单无向连通图**，其中包含很多个简单环，问：从点 $x$ 到 $y$ 有多少条**不重边**的路径。

## 关于此题做法

首先，我们发现**样例的答案都是** $2$ **的幂**！因此我们可以下一个模糊的结论，就是答案都和 $2$ 的幂有关。

然后我们又去看问的问题，问的是**不重边**的路径有多少条，那么什么时候会不重边呢？

- 当图是一棵树的时候（也就是说没有环的时候），任意两点之间的简单路径都只有 $1$ 条。

- 当图是不是一个树的时候（也就是说有环的时候），如下图（抱歉有点乱，图也部分不符合题意，但结果相同）：

一个环时：

![](https://cdn.luogu.com.cn/upload/image_hosting/2vtc7me5.png)

两个环时：

![](https://cdn.luogu.com.cn/upload/image_hosting/ac0jop1z.png)

这让我们有所启发：噢！每一个环都能**从上和从下走**，也就是每一个环都有两种走法，根据**乘法原理**，从 $x$ 到 $y$ 经过 $n$ 个环就有 $2^n$ 种走法！

这时有人就会问了：不一定啊！如果 $x$ 和 $y$ 有不同的经过的环的走法呢？

这个不必担心，因为整个图可以换个方法理解为：在一棵树上，有很多个点，有一些点是一个环。换个角度：将环看作点，就是一棵树因此在图中，不会存在有不同的环的走法。

**简单无向图**判断环的数量，就会让人想到**边双连通分量**。

本来**边双连通分量**是会判定该区域的所有的环（超过 $1$ 个就会出现环套环或者是两个环共用一个点），但是由于这道题的图的特性，因此不存在环套环和两个环共用一个点的情况，也就是说**每个边双连通分量都是一个环或者是一个点**。

### 边双连通分量（想必做这种题的人都知道啦）

这里略过定义，只讲性质：

1. 因为原定义中一个边双连通分量没有割边，所以我们可以将它形象的理解为在将边双连通分量缩为一个点后，连接各个点双连通分量的都是割边。

2. 因为割边一旦割去就会使得整个图不连通，因此整个图在缩点后就变为了一棵树。我们可以将所有的缩点都打上点权，是环的就要有 $1$ 的点权贡献，不是环的就没有贡献。题目也就转化为：在一棵树上，从 $x$ 所在的边双连通分量走到 $y$ 的边双连通分量（包括 $x$ 和 $y$ 所在的分量），求总点权。

### LCA 倍增

在一棵树上，遍历经过的分量，统计总边权，也就是说我们可以在树上维护一个前缀和，统计从根节点出发，到当前的分量的环数，然后到时候计算求解。这不 LCA 的求解方式吗？

因此我们可以预处理倍增，同时顺便预处理 $sum_i$ 表示从根节点到编号为 $i$ 的分量所需经过的环数。

因此，每当询问 $x$ 和 $y$ 时，我们可以求他们的树上距离，用计算距离（本质上来说就是一种维护深度前缀和的计算方法）的方式，将所经过的环的数量统计出来。

注：数组 $sum$ 同上，数组 $num$ 指的是当前分量的点数，大于 $1$ 就形成了环。

最终敲定计算方法：

$$sum_x \ + \ sum_y \ - \ 2 \ \times \ sum_{lca(x,y)} \ + \ (num_{lca(x,y)} > 1)$$

为什么要加上 $num_{lca(x, y)} > 1$ 呢？

因为原来的计算方法是将 $lca(x, y)$ 的贡献消除了的，这里还要加上 $lca(x, y)$ 单点的贡献（这里借鉴于楼下大佬的说法，蒟蒻也揣摩了一下，好像确实是这么一回事）。

在最后计算结果的时候，如果怕代码跑得太慢，可以用快速幂。

**小贴士：取模非常慢，如果不是硬是不取模就会溢出，不要取模。**

### 代码君奉上——

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5, M = 1e5 + 5, mod = 1e9 + 7;

int n, m, dfn[N], low[N], tot, cnt = 0, dcc[N], k, dp[N][30], dep[N], q, num[N], sum[N];

struct node
{
	int id, y;
};

struct edge
{
	int x, y;
}e[M];

vector<node> nbr[N];

vector<int> nbrs[N];

bool bridg[M];

// 判定割边 
void tarjan(int edg, int cur)
{
	dfn[cur] = low[cur] = ++tot;
	for(auto F : nbr[cur])
	{
		int nxt = F.y, id = F.id;
		if(!dfn[nxt])
		{
			tarjan(id, nxt);	
			low[cur] = min(low[cur], low[nxt]);
			if(dfn[cur] < low[nxt] && !bridg[id])
				bridg[id] = true, e[++k].x = cur, e[k].y = nxt;
		} else if(id != edg)
			low[cur] = min(low[cur], dfn[nxt]);
	}
	return ;
}

// 预处理lca 
void get_lca(int cur, int fa)
{
	sum[cur] = sum[fa] + (num[cur] > 1);
	dp[cur][0] = fa, dep[cur] = dep[fa] + 1;
	for(int i = 1; (1 << i) <= dep[cur]; i++)
		dp[cur][i] = dp[dp[cur][i - 1]][i - 1];
	for(auto nxt : nbrs[cur])
	{
		if(nxt == fa)
			continue;
		get_lca(nxt, cur);
	}
	return ;
}

// lca
int lca(int x, int y)
{
	if(dep[x] > dep[y])
		swap(x, y);
	for(int i = 20; i >= 0; i--)
		if(dep[x] <= dep[dp[y][i]])
			y = dp[y][i];
	if(x == y)
		return x;
	for(int i = 20; i >= 0; i--)
		if(dp[x][i] != dp[y][i])
			x = dp[x][i], y = dp[y][i];
	return dp[x][0];
}

// 计算贡献 
int getdis(int x, int y)
{
	int dist = lca(x, y);
	return sum[x] + sum[y] - 2 * sum[dist] + (num[dist] > 1);
}

// 暴力计算当前点属于哪一个分量 
void dfs(int cur, int cntn)
{
	dcc[cur] = cntn;
	num[cntn]++;
	for(auto E : nbr[cur])
	{
		int nxt = E.y, id = E.id;
		if(!dcc[nxt] && !bridg[id])
			dfs(nxt, cntn);
	}
	return ;
}

// 快速幂计算 
int Quick_pow(int a, int b)
{
    int anss = 1, base = a;
    while (b)
	{
        if (b & 1)
            anss = (anss * base) % mod;
        base = (base * base) % mod;
        b >>= 1;
    }
    return anss % mod;
}

signed main()
{
	cin >> n >> m;
	// 建图 
	for(int i = 1; i <= m; i++)
	{
		int a, b;
		cin >> a >> b;
		nbr[a].push_back((node){i, b});
		nbr[b].push_back((node){i, a});
	}
	// 割边 
	for(int i = 1; i <= n; i++)
	{
		if(!dfn[i])
			tarjan(0, i);
	}
	// 判定i属于哪个分量 
	for(int i = 1; i <= n; i++)
		if(!dcc[i])
			dfs(i, ++cnt);
	// 缩点 
	for(int i = 1; i <= k; i++)
	{
		int idx = dcc[e[i].x], idy = dcc[e[i].y];
		nbrs[idx].push_back(idy);
		nbrs[idy].push_back(idx);
	}
	get_lca(1, 0);
	cin >> q;
	while(q--)
	{
		int a, b;
		cin >> a >> b; 
		// 计算有几个环 
		int gets = getdis(dcc[a], dcc[b]);
		cout << Quick_pow(2, gets) << '\n';
	}
	return 0;
}
```

---

## 作者：KidA (赞：1)

在无向图中，对于每一个简单环，

都会产生两种不同的走法，即走环的「上侧」或「下侧」。（可自行画图理解）

因为本题保证了是点仙人掌，于是设两点间的路径上有 $n$ 个环，则答案即为 $2^n$。

不难想到缩点形成一棵树，这样就可以简单地使用树上差分统计贡献了。

时间复杂度是 $O(q \log n)$ 的。[实现](https://codeforces.com/problemset/submission/231/291744541)。

感觉思路和代码都十分自然。最多上位绿。

---

## 作者：shurongwang (赞：1)

先将仙人掌用 `tarjan` 缩点为一棵树.

对于树上的节点 `u`, 若它由多个点缩成, 那么, 经过 `u` 时, 简单路径的条数会翻倍, 否则没有变化.

维护 `w[u]` 表示 从点 `u` 到根共有多少个点 `v` 由多个点缩成, 这用树上前缀和维护即可.

对于树上的点 `u`, `v`, 他们的距离为 `dep[u] + dep[v] - dep[lca(u, v)] * 2`.

同理, 他们之间简单路径的条数为 `2 ^ (w[u] + w[v] - w[lca(u, v)] * 2 + (size[lca(u, v)] > 1))`. 

(由于 `w[u]` 为点权, `- w[lca(u, v)] * 2` 时把 `lca(u, v)` 的权值捡了两次, 要加上 `lca(u, v)` 本身)

```cpp
#include <bits/stdc++.h>

#define null               ""
#define endl               '\n'
#define all(dat)           dat.begin(), dat.end()
#define over(msg)          cout << msg << endl, exit(0);
#define loop(i, to)        for (int i = 0; i < to; ++i)
#define cont(i, to)        for (int i = 1; i <= to; ++i)
#define circ(i, fr, to)    for (int i = fr; i <= to; ++i)
#define foreach(i, dat)    for (__typeof(dat.begin()) i = dat.begin(); i != dat.end(); ++i)

typedef long long          num;

using namespace std;

const int logsize = 18;
int n, m, q, rt = 1, t, sc, vis[100005], dfn[100005], low[100005], sid[100005], sz[100005], dep[100005], pr[100005][logsize], w[100005], mod = 1e9 + 7;
stack<int> s;
vector<int> g[100005], ng[100005];

int inline read() {
    int res = 0;
    char c = getchar();
    for (; !isdigit(c); c = getchar());
    for (; isdigit(c); res *= 10, res += c ^ 48, c = getchar());
    return res;
}

// tarjan 求强连通分量, 将仙人掌的环缩为一点.
void tarjan(int u, int p) {
    dfn[u] = low[u] = ++t;
    vis[u] = 1;
    s.push(u);
    for (int v : g[u]) {
        if (v == p || vis[v] == 2)  continue;
        if (!vis[v]) {
            tarjan(v, u);
        }
        low[u] = min(low[u], low[v]);
    }
    if (dfn[u] == low[u]) {
        ++sc;
        for (;;) {
            int v = s.top();
            s.pop();
            vis[v] = 2;
            sid[v] = sc;
            ++sz[sc];
            if (u == v)  break;
        }
    }
}

void dfs(int u, int p) {
    dep[u] = u == rt ? 0 : dep[p] + 1;
    w[u] = u == rt ? sz[u] > 1 : w[p] + (sz[u] > 1);
    pr[u][0] = p;
    for (int v : ng[u]) {
        if (v == p)  continue;
        dfs(v, u);
    }
}

// 以 rt 为根遍历树, 建立倍增表.
void inline init() {
    dfs(rt, -1);
    cont (i, logsize - 1) {
        cont (u, sc) {
            int p = pr[u][i - 1];
            if (p == -1) {
                pr[u][i] = -1;
            } else {
                pr[u][i] = pr[p][i - 1];
            }
        }
    }
}

// 倍增求 u, v 的 lca.
int inline lca(int u, int v) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }
    loop (i, logsize) {
        if ((dep[v] - dep[u]) >> i & 1) {
            v = pr[v][i];
        }
    }
    if (u == v)  return u;
    for (int i = logsize - 1; i >= 0; --i) {
        if (pr[u][i] != pr[v][i]) {
            u = pr[u][i];
            v = pr[v][i];
        }
    }
    return pr[u][0];
}

// 快速幂.
int inline qpow(num a, int p) {
    num res = 1;
    while (p) {
        if (p & 1) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        p >>= 1;
    }
    return res % mod;
}

int main() {
    ios_base::sync_with_stdio(0);
    n = read();
    m = read();
    cont (i, m) {
        int u = read(), v = read();
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    // tarjan 缩点并建树.
    cont (u, n) {
        if (!vis[u]) {
            tarjan(u, -1);
        }
    }
    cont (u, n) {
        for (int v : g[u]) {
            int su = sid[u], sv = sid[v];
            if (su == sv)  continue;
            ng[su].push_back(sv);
        }
    }
    
    // 用倍增法求 lca, 并求得答案.
    init();
    q = read();
    cont (i, q) {
        int u = read(), v = read(), su = sid[u], sv = sid[v], sp = lca(su, sv);
        int d = w[su] + w[sv] - w[sp] * 2 + (sz[sp] > 1);
        cout << qpow(2, d) << endl;
    }
}

```


---

## 作者：Weekoder (赞：0)

> 再也没有火焰为他升起。

### 思路

首先可以发现的是，对于一个简单环，环中的任意两点有且仅有两条不同的路径。根据题目中点仙人掌的性质，我们可以考虑用边双连通分量将每个简单环都缩为一点。

那么对于两个点 $x,y$，在边双连通分量图的视角里就可以将答案按如下方式计算：每经过一个大小不为 $1$ 的 e-dcc 就翻倍。若 $x,y$ 路径上符合条件分量的个数 $k$，则答案为 $2^k$。

又因为边双连通分量所构成的图是一棵树，所以考虑对于每次询问，都用 LCA 配合快速幂以 $\Theta(\log n)$ 的时间复杂度解决。

[代码](https://www.luogu.com.cn/paste/3p4tl3bl)。

---

## 作者：GJX_Algorithm (赞：0)

# CF231E 题解
## 题目描述
- 给定一个 $n$ 个点，$m$ 条边的无向图，且保证每个点最多属于一个简单环。

- 请你求出 $x$ 到 $y$ 之间简单路径的数量对 $10^9 + 7$ 取模后的值。


## 解题思路
- 如图，当 $x$ 到 $y$ 只有一条路径时，这条唯一路径必定是无环的，因为如果有环，那么其一定可以走环的上侧与下侧，使得路径不唯一：

![](https://cdn.luogu.com.cn/upload/image_hosting/zcjooxwn.png)

- 如图，当 $x$ 到 $y$ 之间有两个环时：

![](https://cdn.luogu.com.cn/upload/image_hosting/hxuah5hw.png)

- 根据上述结论可以总结出规律：当 $x$ 与 $y$ 之间有 $cnt$ 个环时，因为每个环都可以分两种情况，故 $x$ 与 $y$ 之间路径数量为 $2^{cnt}$。

- 于是问题就转化为：**求 $x$ 与 $y$ 之间有多少环**。此问题我们可以：

  1. 用边双连通分量缩点。
  
  2. 然后在缩完点的树上进行统计，统计每个点到根的环的数量。答案可以 lca 求。
 
  3. 若 $x$ 与 $y$ 在同一个边双连通分量中，其答案为 2。
 
- 由于题中已明确说明为简单环，故不用考虑其他复杂情况，直接无脑统计即可。

## 核心代码
- tarjan 缩点：
```cpp
void tarjan(int cur, int in_edge)
{
    dfn[cur] = low[cur] = ++tot;
    for (int i = head[cur]; i; i = Next[i])
    {
        int nxt = to[i];
        if (dfn[nxt] == 0)
        {
            tarjan(nxt, i);
            low[cur] = min(low[cur], low[nxt]);
            if (low[nxt] > dfn[cur])
            {
                bridge[i] = bridge[i ^ 1] = 1;
                sum++;
            }
        }
        else if (i != (in_edge ^ 1))
            low[cur] = min(low[cur], dfn[nxt]);
    }
    return ;
}
void dfs(int cur, int I)
{
    dcc[cur] = I;
    ndcc[I]++;
    for (int i = head[cur]; i; i = Next[i])
    {
        int nxt = to[i];
        if (dcc[nxt] != 0 || bridge[i] == 1) continue;
        dfs(nxt, I);
    }
    return ;
}
```

- 统计环数与 lca 得到答案：
```cpp
void DFS(int cur, int f)
{
    if (ndcc[cur] > 1) s[cur] = s[f] + 1;  
    else s[cur] = s[f]; //注意即使不是环也要继承父节点的环数
    fa[cur][0] = f;
    dep[cur] = dep[f] + 1;
    for (int i = 1; i <= 20; i++)
        fa[cur][i] = fa[fa[cur][i - 1]][i - 1];
    for (int i = h1[cur]; i; i = n1[i]) //这里跑的是缩完点的树
    {
        int nxt = to1[i];
        if (nxt != f) DFS(nxt, cur);
    }
    return ;
}
int lca(int x, int y)
{
    if (x == y) return x;
	if (dep[x] > dep[y]) swap(x, y);
	for (int k = 20; k >= 0; k--)
		if (dep[fa[y][k]] >= dep[x])
			y = fa[y][k];
	if (x == y) return x;
	for (int k = 20; k >= 0; k--)
		if (fa[y][k] != fa[x][k])
			x = fa[x][k], y = fa[y][k];
	return fa[x][0];
}
int get_ans(int x, int y)
{
    int l = lca(x, y);
    //注意这里与普通lca求距离有差别，是因为如果lca(x,y)也是环，那么也要算上。
    int ans = s[x] + s[y] - 2 * s[l] + (ndcc[l] > 1);
    return ans;
}
```

---

## 作者：Take_A_Single_6 (赞：0)

duel 赢的简单题！  
思路不难，但是代码难写。  
有环，考虑边双缩点。因为是一个点仙人掌，所以边双缩点之后就是一棵树。缩点的时候要注意，如果是一个点的分量，只能贡献一条路径，而如果是一个环，显然可以贡献两条路径。我们可以把第一类的分量权值设为 $1$，第二类的权值设为 $2$。倍增求 LCA 的时候顺便算一下路径数就好了，仙人掌上的路径数就是树上的路径点权之积。  
时间复杂度 $O(n\log n)$，开空间稍微注意一下。  
代码如下，略微复杂：
```cpp
#include<bits/stdc++.h>
#define int long long
#define db double
#define maxn 200005
#define mod 1000000007
#define fir first
#define sec second
#define pr pair<int,int>
#define pb push_back
#define mk make_pair
#define inf 10000000000000000
using namespace std;
inline int read()
{
    int SS=0,WW=1;
    char ch=getchar();
    while(ch<'0'||ch>'9')
	{
        if(ch=='-')WW=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9')
	{
        SS=(SS<<1)+(SS<<3)+(ch^48);
        ch=getchar();
    }
    return SS*WW;
}
inline void write(int XX)
{
    if(XX<0)putchar('-'),XX=-XX;
    if(XX>9)write(XX/10);
    putchar(XX%10+'0');
}
int n,m,q,dfn[maxn],low[maxn],c1,fl[maxn],tot,f[maxn][21],dep[maxn],w[maxn][21];
vector<int>e[maxn],g[maxn];
stack<int>st;
bool is[maxn];
void tar(int u,int fa)
{
	dfn[u]=low[u]=++c1,st.push(u);
	for(int v:e[u])
	{
		if(!dfn[v])tar(v,u),low[u]=min(low[u],low[v]);
		else if(v!=fa)low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u])
	{
		int k=-1;
		++tot;
		if(st.top()==u)
		{
			st.pop(),fl[u]=tot;
			return;
		}
		is[tot]=1;
		while(k!=u)k=st.top(),st.pop(),fl[k]=tot;
	}
}//求边双
void dfs(int u,int fa)
{
	dep[u]=dep[fa]+1,f[u][0]=fa,w[u][0]=is[fa]?2:1;
	for(int i=1;i<=20;i++)f[u][i]=f[f[u][i-1]][i-1],w[u][i]=w[u][i-1]*w[f[u][i-1]][i-1]%mod;
	for(int v:g[u])if(v!=fa)dfs(v,u);
}//倍增预处理
int lca(int x,int y)
{
	if(dep[x]<dep[y])swap(x,y);
	int fx=is[x]?2:1,fy=is[y]?2:1;
	for(int i=20;i>=0;i--)
		if(dep[f[x][i]]>=dep[y])fx=fx*w[x][i]%mod,x=f[x][i];
	if(x==y)return fx*fy%mod*(is[x]?500000004ll:1)%mod;
	for(int i=20;i>=0;i--)
		if(f[x][i]!=f[y][i])fx=fx*w[x][i]%mod,fy=fy*w[y][i]%mod,x=f[x][i],y=f[y][i];
	return fx*fy%mod*w[x][0]%mod*w[y][0]%mod*(is[f[x][0]]?500000004ll:1)%mod;
}//求LCA，注意要除一遍LCA的权值
signed main()
{
	int x,y;
	n=read(),m=read();
	for(;m;m--)x=read(),y=read(),e[x].pb(y),e[y].pb(x);
	for(int i=1;i<=n;i++)if(!dfn[i])tar(i,-10);
	q=read();
	for(int i=1;i<=n;i++)
		for(int j:e[i])
			if(fl[i]!=fl[j])g[fl[i]].pb(fl[j]);//建树
	dfs(1,0);
	for(;q;q--)
	{
		x=read(),y=read();
		if(fl[x]==fl[y])
		{
			puts("2");
			continue;
		}
		write(lca(fl[x],fl[y])),puts("");
	}
	return 0;
}
```

---

## 作者：EllinY (赞：0)

[codeforces 提交记录](https://codeforces.com/contest/231/submission/281425046)
# 题意
有一个点仙人掌图（每个点都只属于至多一个简单环），给出 $k$ 个询问，问点 $x$ 到点 $y$ 有多少条简单路径（经过的边不能重复，点可以）。
# 思路
一看这个样例输出，就感觉有猫腻，肯定和 $2$ 有关。我们画出一个仙人掌图：$\\$![](https://cdn.luogu.com.cn/upload/image_hosting/h1amrshl.png)$\\$ 图中有三个简单环：`1,2,3,4,5`；`6,7,8`；`9,10,11,12`。如果问点 $3$ 到点 $8$ 的路径，有 $4$ 条：`3,4,5,6,8`；`3,2,1,5,6,8`；`3,4,5,6,7,8`；`3,2,1,5,6,7,8`。发现这个路径可以分为三段：第一段在第一个环里从 $3$ 走到 $5$，有 $2$ 种走法；第二段从 $5$ 走到 $6$，进入第二个环；第三段在第二个环里从 $6$ 走到 $8$，有 $2$ 种走法。那如果是问 $3$ 到 $6$ 呢？是不是没有第三段了？简单路径只是边不能重复，所以从 $6$ 走到 $6$ 有两种走法，绕一圈（`6,7,8,6`）或者直接停在 $6$。走过的边的集合不同则路径不同，所以顺时针绕和逆时针绕没有区别。从 $5$ 走到 $6$ 也是 $4$ 种。可以再模拟一下从 $3$ 走到 $12$，发现是 $8$ 种。得出结论：经过了几个环，就是 $2$ 的几次方，这里的环包括起点和终点所在的环。
# 实现
由于这张图是一个仙人掌，所以当把每个环都缩成一个点的时候，图就会变成一棵树。我们先用 dfs 找到所有环，在同一个环里的用 $b_i$ 标记为相同的数值（数值从 $n+1$ 开始，方便区分原来的点和缩点得到的点）。重新建图，对树进行前缀和，用 $sum_i$ 表示从根节点（$b_1$）到 $i$ 有多少个环，用 dfs 预处理。要统计 $x$ 到 $y$ 有几个环，就计算 $sum_x+sum_y-2\times sum_{\operatorname{lca}(x,y)}+(\operatorname{lca}(x,y)>n)$。原理：$sum_x+sum_y$ 包括了 $x$ 到 $\operatorname{lca}(x,y)$ 的环，$y$ 到 $\operatorname{lca}(x,y)$ 的环和 $\operatorname{lca}(x,y)$ 到根的环乘上 2。减掉两倍的 $\operatorname{lca}(x,y)$ 到根的环的数量之后还要再加上 $\operatorname{lca}(x,y)$ 的环。$\operatorname{lca}(x,y)$ 用倍增法就可以啦。
# 代码
温馨提示：一定要用 `scanf`，否则会 TLE（本人以为是找环太慢，换了一种写法 qwq）。找环过程建议手动模拟帮助理解。
```
#include<bits/stdc++.h>
using namespace std;
#define maxlog 18 
#define mod 1000000007 
int n,m,x,y,k,b[100005],sum[200005],tot;
int anc[200005][20],dep[200005];
vector<int> go[100005],e[200005],st;
long long mi[100005];
bool vis[100005];
void dfs(int ps,int fa){
	if(vis[ps]){
		bool flag=0;
		for(int i=0;i<st.size();i++){
			if(st[i]==ps) flag=1,tot++;
			if(flag) b[st[i]]=tot;
		}
		return;
	}
	vis[ps]=1;
	st.push_back(ps);
	for(auto g:go[ps]){
		if(g==fa) continue;
		dfs(g,ps);
	}
	st.pop_back();
}
void pre(int ps,int fa){//sum 和 LCA 的前处理
	sum[ps]=sum[fa]+(ps>n);
	dep[ps]=dep[fa]+1;
	anc[ps][0]=fa;
	for(int i=1;i<maxlog;i++)
		anc[ps][i]=anc[anc[ps][i-1]][i-1];
	for(auto g:e[ps]) if(g!=fa) pre(g,ps);
}
int lca(int x,int y){
	if(x==y) return x;
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=maxlog-1;i>=0;i--)
		if(dep[anc[x][i]]>=dep[y]) x=anc[x][i];
	if(x==y) return x;
	for(int i=maxlog-1;i>=0;i--)
		if(anc[x][i]!=anc[y][i])
			x=anc[x][i],y=anc[y][i];
	return anc[x][0];
}
int main(){
	scanf("%d%d",&n,&m);
	tot=n;mi[0]=1;
	for(int i=1;i<=n;i++){
		mi[i]=mi[i-1]*2%mod;
		b[i]=i;
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&x,&y);
		go[x].push_back(y);
		go[y].push_back(x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)
		for(auto g:go[i])
			if(b[i]!=b[g])
				e[b[i]].push_back(b[g]);
	pre(b[1],0);
	scanf("%d",&k);
	for(int i=1;i<=k;i++){
		scanf("%d%d",&x,&y);
		x=b[x],y=b[y];
		int z=lca(x,y);
		int res=sum[x]+sum[y]-2*sum[z]+(z>n);
		printf("%lld\n",mi[res]);
	}
	return 0;
}
```

---

## 作者：luan341502 (赞：0)

由于点仙人掌中每个点最多属于一个环，所以可以将其缩点。

对于每两个点之间的路径条数，我们考虑到经过一个环时有两种走法，一种是顺时针走，一种是逆时针走。

我们维护一下 lca 并根据乘法原理处理即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n,m,q;
int idx=0,vis[300005],dfn[300005],low[300005];
struct edge{
	int to,next;
}e[600005],enow[600005];
int head[300005],cnt=1;
int head_now[300005],cnt_now=0;
bool br[600005];
int dcc=0,c[300005],size[300005];
int dep[300005],anc[300005][20];
long long dis[300005];
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
void add_now(int u,int v){
	enow[++cnt_now].to=v;
	enow[cnt_now].next=head_now[u];
	head_now[u]=cnt_now;
}
void tarjan(int fa,int u){
	dfn[u]=low[u]=++idx;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(v==fa) continue;
		if(!dfn[v]){
			tarjan(u,v);
			low[u]=min(low[u],low[v]);
			if(dfn[u]<low[v]) br[i]=br[i^1]=true;
		}else low[u]=min(low[u],dfn[v]);
	}
}
void dfs(int u){
	c[u]=dcc;
	size[dcc]++;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if(c[v]||br[i]) continue;
		dfs(v);
	}
}
void dfs_now(int fa,int u){
	for(int i=head_now[u];i;i=enow[i].next){
		int v=enow[i].to;
		if(v==fa) continue;
		dis[v]=dis[u]*min(size[v],2)%mod;
		dep[v]=dep[u]+1;
		anc[v][0]=u;
		dfs_now(u,v);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=18;i>=0;i--)
		if(dep[anc[u][i]]>=dep[v]) u=anc[u][i];
	if(u==v) return u;
	for(int i=18;i>=0;i--)
		if(anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}
long long inv(int k){
	long long ans=1,a=k;
	int b=mod-2;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v);
		add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(!dfn[i]) tarjan(0,i);
	}
	for(int i=1;i<=n;i++){
		if(!c[i]) ++dcc,dfs(i);
	}
	for(int i=1;i<=n;i++){
		for(int j=head[i];j;j=e[j].next){
			int k=e[j].to;
			if(c[i]!=c[k]) add_now(c[i],c[k]);
		}
	}
	dis[0]=1;
	dep[1]=1;
	dis[1]=min(size[1],2);
	dfs_now(0,1);
	for(int i=1;i<=18;i++)
		for(int j=1;j<=n;j++)
			anc[j][i]=anc[anc[j][i-1]][i-1];
	cin>>q;
	while(q--){
		int x,y;
		cin>>x>>y;
		int nowx=c[x],nowy=c[y];
		if(nowx==nowy) cout<<"2\n";
		else{
			int k=lca(nowx,nowy);
			cout<<dis[nowx]*dis[nowy]%mod*inv(dis[k])%mod*inv(dis[anc[k][0]])%mod<<"\n";
		}
	}
	return 0;
}
```


---

## 作者：x383494 (赞：0)

本文采用 CC BY-NC-SA 4.0 协议发布。

[cnblogs](https://www.cnblogs.com/x383494/p/18010714)

## 前言

提供一个圆方树做法。

孩子圆方树学傻了，忘了还有缩点这回事。

## 正文

建圆方树。

考虑一条圆方树上的路径，哪些点对答案有贡献：

- 方点，这表示路径经过一个环，方案数 $\times 2$.

- 旁边有方点的圆点。这表示走到这时可以选择在环上绕一圈，方案数 $\times 2$.

于是设“旁边有方点的圆点”权值为 $2$，方点权值为 $\dfrac{1}{2}$，其他点权值 $1$，路径上的点权值乘起来就是方案数。取对数后转化为路径权值和问题。

## 代码

```cpp
#include <iostream>
#include <cassert>
#include <vector>
#include <stack>
#define UP(i,s,e) for(auto i=s; i<e; ++i)
using std::cin; using std::cout;
namespace m{ // }{{{
constexpr int N = 1e5, M = 1e5, lgN = 17, MOD = 1e9+7;
int in, im;
std::vector<int> tos0[N], tos1[N*2];
int pntcnt, low[N], dfn[N]; //nearsq[N];
extern int treesum[];
std::stack<int> vising;
void tarjan_dfs(int x, int f){
    static int dfstim = 0;
    dfstim++;
    low[x] = dfn[x] = dfstim;
    vising.push(x);
    for(int i:tos0[x]){
        if(i == f) continue;
        if(dfn[i]){
            low[x] = std::min(low[x], dfn[i]);
            continue;
        }
        tarjan_dfs(i, x);
        low[x] = std::min(low[x], low[i]);
        if(low[i] > dfn[x]){
            assert(vising.top() == i);
            tos1[i].push_back(x);
            tos1[x].push_back(i);
            //while(vising.top() != i){
            //    vising.pop();
            //}
            vising.pop();
        } else if(low[i] == dfn[x]){
            while(1){
                int t = vising.top(); vising.pop();
                tos1[pntcnt].push_back(t);
                tos1[t].push_back(pntcnt);
                treesum[t] = 1;
                if(t == i) break;
            }
            tos1[pntcnt].push_back(x);
            tos1[x].push_back(pntcnt);
            treesum[x] = 1;
            //nearsq[x] = pntcnt;
            pntcnt++;
        }
    }
}
int dfn1[N*2], fa[N*2], treesum[N*2], st[lgN][N*2];
void dfs_mark(int x, int f){
    static int dfstim = -1; dfstim++;
    fa[x] = f; treesum[x] += (x==f ? 0 : treesum[f]) - (x>=in);
    dfn1[x] = dfstim;
    st[0][dfn1[x]] = fa[x];
    for(int i:tos1[x]){
        if(i == f) continue;
        dfs_mark(i, x);
    }
}
int dfnmin(int x, int y){ return dfn1[x] < dfn1[y] ? x : y; }
int pow2[N];
void prepare(){
    cin >> in >> im;
    pntcnt = in;
    UP(i, 0, im){
        int ia, ib; cin >> ia >> ib; ia--, ib--;
        tos0[ia].push_back(ib);
        tos0[ib].push_back(ia);
    }
    tarjan_dfs(0, 0);
    dfs_mark(0, 0);
    UP(layer, 1, lgN){
        UP(i, 0, pntcnt-(1<<layer)+1){
            st[layer][i] = dfnmin(st[layer-1][i], st[layer-1][i+(1<<layer>>1)]);
        }
    }
    pow2[0] = 1;
    UP(i, 1, pntcnt-in+1){
        pow2[i] = pow2[i-1] * 2 % MOD;
    }
}
int getlca(int x, int y){
    if(x == y) return x;
    x = dfn1[x]; y = dfn1[y];
    if(x > y) std::swap(x, y);
    int delta = std::__lg(y-x);
    return dfnmin(st[delta][x+1], st[delta][y-(1<<delta)+1]);
}
void work(){
    int ix, iy; cin >> ix >> iy; ix--, iy--;
    //if(nearsq[ix]) ix = nearsq[ix];
    //if(nearsq[iy]) iy = nearsq[iy];
    int lca = getlca(ix, iy);
    int sum = treesum[ix] + treesum[iy] - treesum[lca] - (lca ? treesum[fa[lca]] : 0);
    cout << pow2[sum] << '\n';
}
} // {}}}
int main(){ 
    m::prepare();
    int iq;
    cin >> iq;
    while(iq--) m::work();
}
```


---

