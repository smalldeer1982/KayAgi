# Edge Queries

## 题目描述

You are given an undirected, connected graph of $ n $ nodes and $ m $ edges. All nodes $ u $ of the graph satisfy the following:

- Let $ S_u $ be the set of vertices in the longest simple cycle starting and ending at $ u $ .
- Let $ C_u $ be the union of the sets of vertices in any simple cycle starting and ending at $ u $ .
- $ S_u = C_u $ .

You need to answer $ q $ queries.

For each query, you will be given node $ a $ and node $ b $ . Out of all the edges that belong to any simple path from $ a $ to $ b $ , count the number of edges such that if you remove that edge, $ a $ and $ b $ are reachable from each other.

## 说明/提示

The graph in the first sample is :

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1763F/a58367504fff9fc243e7fdf716add65881fbb1b1.png)The first query is $ (1, 4) $ . There are $ 5 $ total edges that belong to any simple path from $ 1 $ to $ 4 $ . Edges $ (3, 4), (4, 5), (5, 3) $ will be counted in the answer to the query.

The fourth query is $ (2, 8) $ . There is only one simple path from $ 2 $ to $ 8 $ , thus none of the edges will be counted in the answer to the query.

The fifth query is $ (7, 10) $ . There are $ 4 $ total edges that belong to any simple path from $ 7 $ to $ 10 $ , all of them will be counted in the answer to the query.

## 样例 #1

### 输入

```
10 11
1 2
2 3
3 4
4 5
5 3
2 7
7 9
9 10
10 6
6 7
1 8
5
1 4
5 10
3 5
2 8
7 10```

### 输出

```
3
7
3
0
4```

## 样例 #2

### 输入

```
13 15
1 2
2 3
3 4
4 1
2 4
3 5
5 6
6 7
6 8
7 9
9 10
8 7
10 11
10 12
10 13
6
9 11
1 5
1 8
5 2
5 12
12 13```

### 输出

```
0
5
8
5
3
0```

# 题解

## 作者：Alex_Wei (赞：4)

这题是不是有点裸？题目给的性质乱七八糟，完全没用。

建出圆方树，则 $a, b$ 之间涉及到的所有点双即 $a, b$ 在圆方树简单路径上的所有方点。

对于 $a, b$ 路径上的一个点双，如果其不为两点一边即割边，则删去其中任意一条边 $a, b$ 仍相互可达。因此，对于所有点双，若其为两点一边，则给其对应方点赋值 $0$，否则赋点双内部边的条数作为权值，则询问 $a, b$ 的答案即 $a, b$ 在圆方树上的简单路径上的所有方点的权值之和。

视 $n, m, q$ 同级，时间复杂度 $\mathcal{O}(n\log n)$。[代码](https://codeforces.com/contest/1763/submission/186095525)。

---

## 作者：WrongAnswer_90 (赞：3)

[CF1763F Edge Queries](https://www.luogu.com.cn/problem/CF1763F)

圆方树板子题。

首先想到的是缩边双，但是以下情况边双不好处理：

![image.png](https://s2.loli.net/2023/08/27/OvbmIPQSf4HZ1Ax.png)

点 $2,3,4$ 在一个边双里，缩点之后该边双在 $1$ 到 $6$ 的路径上，但是显然 $(2,3),(3,4),(2,4)$ 这三条边并不属于 $1$ 到 $6$ 的路径。

考虑建立圆方树，定义方点的权值为它所代表的边双中边的数量（只有一条边时权值为 $0$），那么答案就是圆方树上两点间方点权值和，正确性是显然的，因为如果方点在 $a,b$ 两点间，那么 $a$ 到 $b$ 的路径一定会经过这个点双，点双里的边是随便删的。

建出圆方树，维护树上前缀和，倍增或者树剖求 LCA 即可，离线可以做到 $\mathcal O(n)$，不过数据范围 $\mathcal O(n \log n)$ 即可通过。

```cpp
int n,m,num,kl,cnt,x[600001],dfn[600001],y[600001],low[600001],sum[600001],top[600001],siz[600001],son[600001],dep[600001],fa[600001];
vector<int> T[600001],G[600001];
stack<int> st;
void tarjan(int k)
{
	st.push(k),low[k]=dfn[k]=++cnt;
	for(auto to:G[k])
	{
		if(!dfn[to])
		{
			tarjan(to),low[k]=min(low[k],low[to]);
			if(low[to]>=dfn[k])
			{
				int y;++num;
				do T[num].eb(y=st.top()),st.pop(),T[y].eb(num);while(y!=to);
				T[num].eb(k),T[k].eb(num);
			}
		}
		else low[k]=min(low[k],dfn[to]);
	}
}
void dfs1(int k,int father,int depth)
{
	dep[k]=depth,fa[k]=father,siz[k]=1;
	for(auto to:T[k])
	{
		if(to==father)continue;
		dfs1(to,k,depth+1),siz[k]+=siz[to];
		if(siz[to]>siz[son[k]])son[k]=to;
	}
}
void dfs2(int k,int topp)
{
	if(sum[k]==1)--sum[k];
	sum[k]+=sum[fa[k]],top[k]=topp;
	if(son[k])dfs2(son[k],topp);
	for(auto to:T[k])if(to!=fa[k]&&to!=son[k])dfs2(to,to);
}
inline int LCA(int x,int y)
{
	while(top[x]!=top[y]){if(dep[top[x]]>dep[top[y]])swap(x,y);y=fa[top[y]];}
	return dep[x]>dep[y]?y:x;
}
inline void mian()
{
	read(n,m),num=n;int a,b;
	for(int i=1;i<=m;++i)read(x[i],y[i]),G[x[i]].eb(y[i]),G[y[i]].eb(x[i]);
	for(int i=1;i<=n;++i)if(!dfn[i])tarjan(i);
	dfs1(1,0,1);
	for(int i=1;i<=m;++i)
	{
		if(fa[x[i]]==fa[y[i]])++sum[fa[x[i]]];
		else if(fa[fa[x[i]]]==y[i])++sum[fa[x[i]]];
		else if(fa[fa[y[i]]]==x[i])++sum[fa[y[i]]];
	}
	dfs2(1,1),read(m);
	while(m--)read(a,b),kl=LCA(a,b),write(sum[a]+sum[b]-sum[kl]-sum[fa[kl]],'\n');
}
```

---

## 作者：Conan15 (赞：2)

题目中给的神秘性质到底有什么用啊 qwq？

挺显然的建立点双圆方树，定义圆点（原图中点）的点权为 $0$，方点（点双）的点权为**点双中的边数**。\
对于一组询问 $(u,v)$ 相当于求在圆方树上 $u \to v$ 的点权和。\
直接树上前缀和并倍增求最经公共祖先即可。

为什么这是对的？

- 依次考虑路径上的每个点双。
- 显然，在这个点双中删除任意一条边，仍然存在一条 $u$ 到 $v$ 的路径。
- 然而点双外的边删除后路径就断开了。
- 所以一个点双的贡献是它内部的**边数**。

时间复杂度 $O(q \log n)$。

---

## 作者：stntn (赞：2)

## 题意

给你一个有 $n$ 个点，$m$ 条边的无向图，满足以下条件：

- 令 $S_u$ 表示 $u$ 所在的最大环的点集。

- 令 $C_u$ 表示 $u$ 所在的任意环的点集的并集。

- $S_u=C_u$

有 $q$ 次询问，每次询问在 $u$ 到 $v$ 的所有简单路径的边集的并集中，有多少条边满足仅删去该边后 $u,v$ 仍联通。

------------

条件翻译成人话：每个点最多在一个环内。

一开始并不知道这个条件有什么用，于是有一个很 naive 的想法，跑边双后形成一棵树，询问的答案即 $u \to v$ 路径上所有边双的内部边的数量和。 

为什么错了？简单路径！

如果有这么一个边双，满足 $u \to x$，$x \to v$，$x \to \{ \text{边双内的其它点} \}$。那么 $u \to v$ 的路径并集是不包含改边双中的点的。

怎么办？圆方树！

视环为方点，点权为其边双的边数，视环内点为圆点，点权为 $0$。

这样就解决了上面的问题，如果路径仅经过环的某一点则不会将权值计入，否则就将经过方点，将权值全部计入。

到头来还是没有用到题目的性质？谁能帮我解释一下？

## CODE

注：不是标准的圆方树写法，主要是边双懒得改了。

```cpp
#include<bits/stdc++.h>
#define N 400010
#define LL long long
#define ULL unsigned long long
#define DB double
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define per(i,a,b) for(int i=a;i>=b;i--)
#define tep(u,g) for(int v:g[u])
#define INF 0x3f3f3f3f
#define mod 1000000007
#define pir pair<int,int>
#define mp(i,j) make_pair(i,j)
#define fi first
#define se second
using namespace std;
template <typename T> inline void read(T &a)
{
	a=0;T w=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){a=(a<<3)+(a<<1)+(ch^48);ch=getchar();}
	a*=w;
}
template <typename T,typename ...Args> inline
void read(T &x,Args &...args){read(x);read(args...);}
int n,m,q,pcc,dfn[N],low[N],dfncc,dis[N],top[N],fa[N],son[N],dep[N],siz[N],color[N];
bool ins[N];
vector<int> t[N],g[N];
stack<int> s;
inline void paint(int u)
{
	s.pop();ins[u]=0;color[u]=pcc;
	t[pcc].push_back(u);
	t[u].push_back(pcc);
}
inline void tarjan(int u,int fa)
{
	low[u]=dfn[u]=++dfncc;
	s.push(u);ins[u]=1;
	tep(u,g) if(v^fa)
	{
		if(!dfn[v]) tarjan(v,u),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		++pcc;
		while(s.top()^u) paint(s.top());
		paint(u); 
	}
}
inline void dfs1(int u)
{
	dep[u]=dep[fa[u]]+1;siz[u]=1;dis[u]+=dis[fa[u]];
	tep(u,t) if(v^fa[u])
	{
		fa[v]=u;dfs1(v);siz[u]+=siz[v];
		if(!son[u]||siz[son[u]]<siz[v]) son[u]=v;
	}
}
inline void dfs2(int u,int tp)
{
	top[u]=tp;if(son[u]) dfs2(son[u],tp);
	tep(u,t) if(v^fa[u]&&v^son[u]) dfs2(v,v);
}
inline int lca(int u,int v)
{
	while(top[u]^top[v]) dep[top[u]]<dep[top[v]] ? v=fa[top[v]] : u=fa[top[u]];
	return dep[u]<dep[v] ? u:v;
}
signed main()
{
	read(n,m);pcc=n;
	rep(i,1,m)
	{
		int u,v;read(u,v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	rep(i,1,n) if(!dfn[i]) tarjan(i,0);
	rep(u,1,n) tep(u,g)
	{
		if(color[u]^color[v]) t[u].push_back(v);
		else dis[color[u]]++;
	}
	rep(i,1,pcc)
	{
		sort(t[i].begin(),t[i].end());dis[i]>>=1;
		t[i].erase(unique(t[i].begin(),t[i].end()),t[i].end());
	}
	dfs1(1);dfs2(1,1);
	read(q);
	while(q--)
	{
		int u,v,Lca;read(u,v);
		Lca=lca(u,v);
		printf("%d\n",dis[u]+dis[v]-dis[Lca]-dis[fa[Lca]]);	
	}
	return 0;
}
```

---

## 作者：OldDriverTree (赞：1)

# Solution

首先对图建出广义圆方树，然后对于一次询问，答案就为可行边个数减去必经边个数，可行边个数就为圆方树上 $a\to b$ 的路径上所有方点代表的点双中边数之和（因为点双有一个性质，对于点双中任意两点 $a,b$ 和任意一边 $e$，都存在一条 $a$ 到 $b$ 经过 $e$ 的路径），必经边个数就为路径上两边一点的点双个数（因为两边一点的点双中的边为割边，其他情况点双也都为边双），我们把一个点双的可行边减必经边个数放到它对应的方点上，然后就是查询路径和，求个 $\text{LCA}$ 然后随便做一下就行了。

求 $\text{LCA}$ 我写的是树剖，这样时间复杂度为 $O(n+m+q\log n)$。

当然可以用 $O(n)\sim O(1)$ 的 $\text{LCA}$ 求法做到 $O(n+m+q)$（（

# Code

```c++
//when you use vector or deque,pay attention to the size of it.
//by OldDirverTree
#include<bits/stdc++.h>
//#include<atcoder/all>
#define P pair<int,int>
#define int long long
#define mid (l+r>>1)
using namespace std;
//using namespace atcoder;
//using mint=modint998244353;
const int N=2e5+1,M=4e5;
int tot,cnt,dfn[N],low[N];
int fa[M],dep[M],siz[M],son[M],top[M];
vector<int> g[N],G[M]; stack<int> s;
int n,m,q,dis[M];

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x) {
        x+=0x9e3779b97f4a7c15;
        x=(x^(x>>30) )*0xbf58476d1ce4e5b9;
        x=(x^(x>>27) )*0x94d049bb133111eb;
        return x^(x>>31);
    }
    size_t operator() (uint64_t x) const {
        static const uint64_t FIXED_RANDOM=chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x+FIXED_RANDOM);
    }
};
int read() {
    int x=0; bool _=true; char c=0;
    while (!isdigit(c) ) _&=(c!='-'),c=getchar();
    while (isdigit(c) ) x=x*10+(c&15),c=getchar();
    return _?x:-x;
}
void tarjan(int u)
{
    dfn[u]=low[u]=++tot,s.push(u);
    for (int v:g[u]) if (!dfn[v])
    {
        tarjan(v),low[u]=min(low[u],low[v]);
        if (low[v]==dfn[u]) {
            cnt++,G[u].push_back(n+cnt);
            for (int o=0;o^v;o=s.top(),s.pop(),G[n+cnt].push_back(o) );
        }
    }
    else low[u]=min(low[u],dfn[v]);
}
void dfs1(int u)
{
    siz[u]=1,dep[u]=dep[fa[u] ]+1;
    for (int v:G[u]) {
        fa[v]=u,dfs1(v),siz[u]+=siz[v];
        if (siz[v]>siz[son[u] ]) son[u]=v;
    }
}
void dfs2(int u) {
    dis[u]+=dis[fa[u] ];
    if (son[u]) top[son[u] ]=top[u],dfs2(son[u]);
    for (int v:G[u]) if (v^son[u]) top[v]=v,dfs2(v);
}
int LCA(int x,int y) {
    while (top[x]^top[y])
    dep[top[x] ]>dep[top[y] ]?x=fa[top[x] ]:y=fa[top[y] ];
    return dep[x]<dep[y]?x:y;
}
main()
{
    n=read(),m=read();
    while (m--) {
        int x=read(),y=read();
        g[x].push_back(y),g[y].push_back(x);
    }
    tarjan(1),dfs1(1);
    for (int x=1;x<=n;x++) for (int y:g[x])
    if (x<y) dis[fa[fa[x] ]==y?fa[x]:fa[y] ]++;
    for (int i=n+1;i<=n+cnt;i++) if (dis[i]==1) dis[i]=0;
    top[1]=1,dfs2(1),q=read();
    while (q--) {
        int x=read(),y=read(),z=LCA(x,y);
        printf("%lld\n",dis[x]+dis[y]-dis[z]-dis[fa[z] ]);
    }
    return 0;
}
```

---

## 作者：L0vely_NaiL0ng (赞：1)

首先题目给的条件没有用，对于一般无向连通图，以下做法仍然成立。

以下称点双连通分量为点双，边双连通分量为边双。

解法一：建点双圆方树，对于两点之间的树上路径中的方点，如果其对应点双有大于等于 $2$ 条边，则这个点双里随便删边仍然连通，否则（即一边连两点的点双情况）删掉之后不连通。

所以圆点和只有一条边的方点点权为 $0$，其它方点点权为对应点双内边数，求树上路径点权和。

解法二：建边双圆方树（应该可以这么称呼），方点点权为对应边双内的边数，圆点点权为 $0$，求路径上点权和（没写过）。

具体实现上，对于计算一个边双或者点双内的边数，可以考虑记录每个点双（边双）内的点，然后遍历每个点双（边双），将其中的点标记，然后枚举一端在这个点双（边双）中的边，如果另一端也有标记，则这条边是这个点双（边双）中的，最后把标记取消，遍历下一个点双（边双）。

其次，因为是个静态问题，所以求树上路径点权和可以用树上差分，求最近公共祖先的话因人而异，我写的是树剖。

```
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int n, m, q;
int dfn[N], low[N], num, st[N], t, cnt, a[N], s[N];
vector<int> e[N], p[N], g[N];
int d[N], son[N], f[N], top[N], siz[N];
bool flag[N];
void dfs(int x, int fa) {
	dfn[x] = low[x] = ++num; st[++t] = x;
	for (int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (!dfn[y]) {
			dfs(y, x); low[x] = min(low[x], low[y]);
			if (low[y] >= dfn[x]) {
				cnt++;
				while (t) {
					int z = st[t--];
					g[z].push_back(cnt); g[cnt].push_back(z); p[cnt].push_back(z);
					if (z == y) break;
				}
				g[x].push_back(cnt); g[cnt].push_back(x); p[cnt].push_back(x);
			}
		} else if (y != fa) low[x] = min(low[x], dfn[y]);
	}
}
void dfs1(int x) {
	d[x] = d[f[x]] + 1; siz[x] = 1;
	if (x == 1) s[x] = a[x];
	for (int i = 0; i < g[x].size(); i++) { 
		int y = g[x][i];
		if (y != f[x]) {
			f[y] = x; s[y] = s[x] + a[y]; dfs1(y); siz[x] += siz[y];
			if (siz[y] > siz[son[x]]) son[x] = y;
		}
	}
}
void dfs2(int x, int pa) {
	top[x] = pa;
	if (son[x]) dfs2(son[x], pa);
	for (int i = 0; i < g[x].size(); i++) {
		int y = g[x][i];
		if (y != f[x] && y != son[x]) dfs2(y, y);
	}
}
int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (d[top[x]] < d[top[y]]) swap(x, y);
		x = f[top[x]];
 	}
 	if (d[x] > d[y]) swap(x, y);
 	return x;
}
int main() {
	cin >> n >> m; cnt = n;
	for (int i = 1; i <= m; i++) {
		int x, y; cin >> x >> y; e[x].push_back(y); e[y].push_back(x);
	}
	dfs(1, 0);
	for (int i = n + 1; i <= cnt; i++) {
		for (int j = 0; j < p[i].size(); j++) {
			int x = p[i][j];
			flag[x] = 1;
		}
		for (int j = 0; j < p[i].size(); j++) {
			int x = p[i][j];
			for (int k = 0; k < e[x].size(); k++) {
				int y = e[x][k];
				if (flag[y]) a[i]++;
			}
		}
		for (int j = 0; j < p[i].size(); j++) {
			int x = p[i][j];
			flag[x] = 0;
		}
		a[i] /= 2;
		if (a[i] == 1) a[i] = 0;
	}
	dfs1(1); dfs2(1, 1);
	cin >> q;
	while (q--) {
		int x, y; cin >> x >> y;
		int LCA = lca(x, y), res = s[x] + s[y] - s[LCA] * 2;
		if (LCA > n) res += a[LCA];
		cout << res << endl;
	}
	return 0;
}
```

---

## 作者：Trafford1894 (赞：0)

这题翻译是错的，正确的应该是每个点最多在一个简单环中。

考虑建出圆方树，这时 $a \rightarrow b$ 的路径上经过了一系列点双。给这些点双在方点上赋权值，权值即为点双的边数（如果边数为 $1$ 权值为 $0$，因为这条边是割边）。

答案即为 $a \rightarrow b$ 上所有方点权值之和。想怎么维护都可以，时间复杂度 $O(n)$ 或者 $O(n \lg n)$。

为什么这样做是对的？考虑路径上所有边数 $> 1$ 的点双，其任意删边后仍是连通的，所以整条路径依然连通。

~~为什么题目的性质一点用都没有啊啊啊~~

给出一份 $O(n \lg n)$ 的参考代码。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 4e5 + 9;
int dfn[N], low[N], stk[N], dfsT, top;
vector<int> adj[N], g[N];
int fa[N][21], dis[N], dep[N], val[N], n, m, q, node;
void tarjan(int u) {
  dfn[u] = low[u] = ++dfsT;
  stk[++top] = u;
  for (int to : adj[u]) {
    if (dfn[to]) low[u] = min(low[u], dfn[to]);
    else {
      tarjan(to);
      low[u] = min(low[u], low[to]);
      if (low[to] >= dfn[u]) {
        g[++node].push_back(u);
        g[u].push_back(node);
        for (int i = 0; i != to; top--) {
          i = stk[top];
          g[node].push_back(i);
          g[i].push_back(node);
        }   
      }
    }
  }
}

void dfs1(int u, int f) {
  fa[u][0] = f;
  for (int to : g[u]) if (to != f) dfs1(to, u);
}

void dfs2(int u, int f) {
  dep[u] = dep[f] + 1; dis[u] = dis[f] + val[u];
  for (int i = 1; i <= 20; i++) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (int to : g[u]) if (to != f) dfs2(to, u);
}

int lca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  for (int i = 20; i > -1; i--) if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
  if (x == y) return x;
  for (int i = 20; i > -1; i--) if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
  return fa[x][0];
}

int main() {
  ios::sync_with_stdio(false); cin.tie(nullptr);
  cin >> n >> m; node = n;
  for (int i = 1, u, v; i <= m; i++) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  tarjan(1); dfs1(1, 0);
  for (int i = 1; i <= n; i++) {
    for (int to : adj[i]) {
      if (to < i) continue;
      if (fa[i][0] == fa[to][0]) val[fa[i][0]]++;
      else if (fa[fa[i][0]][0] == to) val[fa[i][0]]++;
      else val[fa[to][0]]++;
    }
  }

  for (int i = n + 1; i <= node; i++) if (val[i] == 1) val[i] = 0;

  dfs2(1, 0);
  cin >> q;
  for (int i = 1; i <= q; i++) {
    int a, b;
    cin >> a >> b;
    int c = lca(a, b);
    cout << dis[a] + dis[b] - dis[c] - dis[fa[c][0]] << endl;
  }
  return 0;
}
```

---

## 作者：Filberte (赞：0)

较为简单的圆方树入门题。

看到简单路径，不难想到使用点双联通分量进行处理（类比看到删除某条边后仍然联通，会想到边双联通分量）。每次查询两点间一些信息，这在树上比较好回答，所以考虑构建圆方树。

对于一个大小不为 $2$ 的点双连通分量内，任意一条边断掉后不影响连通性。所以问题转为求圆方树上两个圆点间所有方点的边数之和。圆方树的形态不会改变，直接树上差分即可求解此问题。

注意大小为 $2$ 的点双只包含 $1$ 条边，所以在此情况下这条边仍是必经边，不可删去，需要特殊判断一下。

代码实现：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 100;
const int maxn = 4e5 + 100;
int n, m;
vector<int> e[N];
int dfn[N], low[N], clk;
int st[N], tp;
vector<int> g[maxn];
int nods;
void tarjan(int u){
    dfn[u] = low[u] = ++clk;
    st[++tp] = u;
    for(int v : e[u]){
        if(!dfn[v]){
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]){
                ++nods;
                g[nods].push_back(u);
                g[u].push_back(nods);
                for(int x = 0;x != v;--tp){
                    x = st[tp];
                    g[nods].push_back(x);
                    g[x].push_back(nods);
                }
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}
int fa[maxn], s[maxn];
void dfs1(int u, int f){
    fa[u] = f;
    for(int v : g[u]){
        if(v != f) dfs1(v, u);
    }
}
int up[maxn][20], dep[maxn];
void dfs2(int u, int f){
    s[u] += s[f], dep[u] = dep[f] + 1;
    up[u][0] = f;
    for(int j = 1;j <= 19;j++) up[u][j] = up[up[u][j - 1]][j - 1];
    for(int v : g[u]) if(v != f) dfs2(v, u);
}
int lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 19;i >= 0;i--){
        if(dep[up[u][i]] >= dep[v]) u = up[u][i];
    }
    if(u == v) return u;
    for(int i = 19;i >= 0;i--) if(up[u][i] != up[v][i]){
        u = up[u][i], v = up[v][i];
    }
    return up[u][0];
}
vector<pair<int, int>> eds;
void add(int u){if(g[u].size() > 2) s[u]++;}
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> n >> m;
    nods = n;
    for(int i = 1, u, v;i <= m;i++){
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        eds.push_back(make_pair(u, v));
    }
    tarjan(1);
    dfs1(1, 0);
    for(auto [u, v] : eds){
        if(fa[u] == fa[v]) add(fa[u]);
        else if(fa[fa[u]] == v) add(fa[u]);
        else if(fa[fa[v]] == u) add(fa[v]);
    }
    dfs2(1, 0);
    int q;cin >> q;
    for(int i = 1;i <= q;i++){
        int u, v;
        cin >> u >> v;
        int lc = lca(u, v);
        int plc = fa[lc];
        cout << s[u] + s[v] - s[lc] - s[plc] << endl;
    }
    return 0;   
}
```

---

## 作者：Polaris_Australis_ (赞：0)

题里乱七八糟的性质一点没有用啊。

直接边双建圆方树，圆点点权为 $0$，方点点权为边双内的边数，然后就路径点权和就完了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

namespace Wilson_Inversion{

void main();

}

int main(){
	Wilson_Inversion::main();
	return 0;
}

namespace Wilson_Inversion{

int n,m,bel[400010],cnt(1),tot,num,head[400010],to[400010],nxt[400010],sta[400010],top;
int dfn[400010],low[400010],fa[400010][20],sz[400010][20],dep[400010];
vector<int>e[400010];

void add(int x,int y){
	to[++cnt]=y;
	nxt[cnt]=head[x];
	head[x]=cnt;
}

void tarjan(int x,int y){
	sta[++top]=x,dfn[x]=low[x]=++tot;
	for(int i(head[x]);i;i=nxt[i]){
		if(!(i^y^1))continue;
		if(!dfn[to[i]]){
			tarjan(to[i],i);
			low[x]=min(low[x],low[to[i]]);
		}else low[x]=min(low[x],dfn[to[i]]);
	}
	if(low[x]==dfn[x]){
		++num;
		int a;
		do{
			a=sta[top--];
			bel[a]=num;
		}while(x!=a);
	}
}

void dfs(int x){
	for(int i(1);i<=19;++i){
		sz[x][i]=sz[x][i-1]+sz[fa[x][i-1]][i-1];
		fa[x][i]=fa[fa[x][i-1]][i-1];
	}
	for(auto i:e[x]){
		if(i==fa[x][0])continue;
		fa[i][0]=x;
		dep[i]=dep[x]+1;
		dfs(i);
	}
}

int query(int x,int y){
	int res(0);
	if(dep[x]<dep[y])swap(x,y);
	for(int i(19);~i;--i){
		if(dep[fa[x][i]]<dep[y])continue;
		res+=sz[x][i];
		x=fa[x][i];
	}
	if(x==y){
		res+=sz[x][0];
		return res;
	}
	for(int i(19);~i;--i){
		if(fa[x][i]==fa[y][i])continue;
		res+=sz[x][i]+sz[y][i];
		x=fa[x][i],y=fa[y][i];
	}
	res+=sz[x][1]+sz[y][0];
	return res;
}

void main(){
	scanf("%d%d",&n,&m);
	int u,v;
	for(int i(1);i<=m;++i){
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
	}
	num=n;
	tarjan(1,0);
	dep[1]=1;
	for(int i(2);i<=cnt;i+=2){
		if(bel[to[i^1]]==bel[to[i]])++sz[bel[to[i]]][0];
		else e[to[i]].push_back(to[i^1]),e[to[i^1]].push_back(to[i]);
	}
	for(int i(1);i<=n;++i)e[bel[i]].push_back(i),e[i].push_back(bel[i]);
	dfs(1);
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&u,&v);
		printf("%d\n",query(u,v));
	}
}

}
```


---

## 作者：_SeeleVollerei_ (赞：0)

从前几天开始一直阳到现在，然后几天没写题，代码能力急剧下降，一言难尽。

upd on 2022.12.20:经过 Alex_Wei 的锐评，了解了专业术语！

图的性质摸一下，大概就是每个边双内部没有割点。听专业人士说这就是所谓仙人掌，但是概念啥的我不太懂。粉兔说是圆方树板子题但是我不会圆方树。

那么对于一个边双，有一个很好的性质。对于这个边双里任意两点 $u$ 和 $v$ 和任意一条边 $i$，一定有一个简单路径满足从 $u$ 出发经过 $i$ 到达 $v$。

那么当询问的 $u$ 和 $v$ 在同一边双时，答案就是这个边双的边数。

我们考虑将这个想法扩展出去，先缩点并维护每个边双的边数 $cnt_i$。现在是一个树上问题。

一个大胆的想法是答案就是查询的两个点路径上的 $cnt$ 的和。然后倍增求个 LCA 即可。

一个问题在于，有一些边双可能经过但是不完全经过。

具体来讲，就是从一个边双 $A$ 进入边双 $B$，然后再从 $B$ 进入 $C$。我们考虑对应到原图上的边，那么相当于从 $u_A$ 走到 $v_B$，从 $v_B$ 走到 $u_B$，然后再从 $u_B$ 走到 $v_C$。那么我们发现，$cnt_B$ 是否产生贡献，取决于 $u_B$ 和 $v_B$ 是否不相等。

所以我们在倍增的基础上多维护点东西。大概就是维护一个 $sum_{u,i}$ 表示从 $u$ 点往上跳 $2^i$ 个祖先所有产生贡献的祖先的 $cnt$ 之和。为了方便，这个变量是假定跳到第 $2^i+1$ 个祖先的，这样好写很多。然后判断的话可以维护一个边双到它父亲的边连的是哪两个点。

然后查询的时候特判一下即可，总复杂度 $O((n+q)\log n)$。

https://codeforces.com/contest/1763/submission/185991387

---

