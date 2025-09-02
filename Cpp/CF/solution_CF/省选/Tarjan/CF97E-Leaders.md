# Leaders

## 题目描述

After a revolution in Berland the new dictator faced an unexpected challenge: the country has to be somehow ruled. The dictator is a very efficient manager, yet he can't personally give orders to each and every citizen. That's why he decided to pick some set of leaders he would control. Those leaders will directly order the citizens. However, leadership efficiency turned out to vary from person to person (i.e. while person A makes an efficient leader, person B may not be that good at it). That's why the dictator asked world-famous berland scientists for help. The scientists suggested an innovatory technology — to make the leaders work in pairs.

A relationship graph is some undirected graph whose vertices correspond to people. A simple path is a path with no repeated vertices. Long and frighteningly expensive research showed that a pair of people has maximum leadership qualities if a graph of relationships has a simple path between them with an odd number of edges. The scientists decided to call such pairs of different people leader pairs. Secret services provided the scientists with the relationship graph so that the task is simple — we have to learn to tell the dictator whether the given pairs are leader pairs or not. Help the scientists cope with the task.

## 说明/提示

Notes to the samples:

1\) Between vertices 1 and 2 there are 2 different simple paths in total: 1-3-2 and 1-4-2. Both of them consist of an even number of edges.

2\) Vertices 1 and 3 are connected by an edge, that's why a simple odd path for them is 1-3.

5\) Vertices 1 and 5 are located in different connected components, there's no path between them.

## 样例 #1

### 输入

```
7 7
1 3
1 4
2 3
2 4
5 6
6 7
7 5
8
1 2
1 3
1 4
2 4
1 5
5 6
5 7
6 7
```

### 输出

```
No
Yes
Yes
Yes
No
Yes
Yes
Yes
```

# 题解

## 作者：木xx木大 (赞：12)

[CF97E](https://www.luogu.com.cn/problem/CF97E)

我真的调这题调到吐血，我一定要写一篇题解表达我复杂的心情！

* 先随便找一棵生成树出来，两点间树上距离如果是奇数则显然可行；
* 如果树上距离是偶数，则判断树上路径中是否有边在原图的奇环中。假设树上(u,v)之间存在点a和b满足a到b的路径是奇环的一部分，则奇环的“另一部分”的奇偶性一定与a到b距离的奇偶性相反。那么用“另一部分”代替a到b的路径可以改变(u,v)路径的奇偶性，因此可行。
* 除了上述情况，其他情况均不可行。
* 注意判断图不连通的情况

* 如何判断一条边是否在奇环上？结论是，一条边在奇环上的充要条件是它所在的点双存在奇环。

  证明：一个奇环向外扩展出的边一定是奇环。一个存在奇环的点双可以通过从它的奇环扩展得到。且点双之间不可能存在环。

（下面才是重点）

当我写这题写了五份代码并全挂了想看看题解的时候，我的内心是***的！

**这道题的题解除了圆方树和树剖的两篇，其他缩边双的都是能A题的假题解（包括那篇文字说是点双代码写了边双的题解）！强烈建议管理员撤下错误题解！**

Hack边双的数据：6 7 1 2 2 3 3 4 4 1 3 5 5 6 6 3 1 2 4

正确答案应该是 No

那它们为什么能AC呢？因为这道题的数据是*造的！甚至可以用随机化算法过掉！而且CF上还没有这题的题解！~~（所以其实这篇题解是用来骂这道题的）~~

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace FGF
{
	int n,m;
	const int N=5e5+5;
	struct edg{
		int to,nxt,id;
	}e[N<<1];
	int cnt=1,head[N],s;
	int rt[N],dfn[N],low[N],st[N],bel[N],col[N],num,tp,dcc,siz[N],sum[N],dep[N],fa[N][20];
	bool vis[N],is[N],fl;
	vector<int> V[N],E[N];
	void add(int u,int v,int id)
	{
		cnt++;
		e[cnt].to=v;
		e[cnt].nxt=head[u];
		head[u]=cnt;
		e[cnt].id=id;
	}
	void tarjan(int u,int f)
	{
		dfn[u]=low[u]=++num;
		dep[u]=dep[e[f^1].to]+1,fa[u][0]=e[f^1].to,rt[u]=rt[e[f^1].to];
		for(int i=1;i<=18;i++)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(vis[i]||i==(f^1))continue;
			st[++tp]=i;
			if(!dfn[v])
			{
				tarjan(v,i);
				low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u])
				{
					++dcc;
					int x=-1;
					V[dcc].push_back(u);
					do{
						x=st[tp--];
						bel[x]=bel[x^1]=dcc;
						vis[x]=vis[x^1]=1;
						V[dcc].push_back(e[x].to);
						E[dcc].push_back(x);
					}while(x!=i);
				}
			}
			else low[u]=min(low[u],dfn[v]);
		}
	}
	void dfs(int u,int f)
	{
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(vis[v]||i==(f^1))continue;
			sum[v]=sum[u]+is[i],dfs(v,i);
		}
	}
	bool dfs2(int u,int fro)
	{
		if(vis[u])
		{
			if(col[u]==col[e[fro^1].to])return 1;
			else return 0;
		}
		vis[u]=1;col[u]=col[e[fro^1].to]^1;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if((i==(fro^1))||bel[i]!=bel[fro])continue;
			if(dfs2(v,i))return 1;
		}
		return 0;
	}
	int getlca(int u,int v)
	{
		if(dep[u]<dep[v])swap(u,v);
		int d=dep[u]-dep[v];
		for(int i=18;i>=0;i--)
			if(d&(1<<i))u=fa[u][i];
		if(u==v)return u;
		for(int i=18;i>=0;i--)
			if(fa[u][i]!=fa[v][i])u=fa[u][i],v=fa[v][i];
		return fa[u][0];
	}
	void work()
	{
		scanf("%d%d",&n,&m);
		int u,v;
		for(int i=1;i<=m;i++)	
		{
			scanf("%d%d",&u,&v);
			add(u,v,i),add(v,u,i);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i])rt[0]=i,tarjan(i,0);	
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=dcc;i++)
		{
			for(int sz=V[i].size(),j=0;j<sz;j++)
				vis[V[i][j]]=0;
			if(dfs2(e[E[i][0]].to,E[i][0]))
				for(int sz=E[i].size(),j=0;j<sz;j++)
					is[E[i][j]]=is[E[i][j]^1]=1;
		}
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++)
			if(!vis[i])dfs(i,0);
		int Q;
		scanf("%d",&Q);
		while(Q--)
		{
			scanf("%d%d",&u,&v);
			if(rt[u]!=rt[v])puts("No");
			else
			{
				int lca=getlca(u,v);
				if((dep[u]+dep[v]-2*dep[lca])&1)puts("Yes");
				else if(sum[u]+sum[v]-2*sum[lca])puts("Yes");
				else puts("No");
			}
		}
	}
}
int main()
{
	FGF::work();
	return 0;
}
```




---

## 作者：xtx1092515503 (赞：8)

# [Portal](https://www.luogu.com.cn/problem/CF97E)

这里是某种奇怪的二分图+圆方树解法。

首先，对于一个询问，我们可以分成几种情况来考虑。

1. 两点不在同一个连通块中。

很简单，直接输出 ```No``` 即可。

2. 两点在同一个连通块中。

这时我们就要提取出任意一条两点间的路径出来。

（关于如何提取，我们可以从任意一个点出发跑一个单源最短路出来，然后取两点到源点的路径长度的**异或和**作为两点间路径长度——因为我们只关心路径长度的奇偶性，故这两条到源点的路径中，重叠的部分会被异或两次无效掉，剩下的就是两点间路径长度）

2.1. 路径长度是奇数。

直接输出 ```Yes``` 即可。

2.2. 路径长度是偶数。

则我们接下来就要判断是否存在一条奇路径。

很显然这条奇路径，与我们一开始选出的那条偶路径，是有不重叠的部分的。我们挑出不重叠的部分一看，发现其中必定包含一个**奇环**。因为，只有奇环上两点，才会同时存在一条奇路径和一条偶路径。

于是我们现在就要判断两点间是否存在一条路径经过一个奇环。

则我们可以求出两点间所有路径的**并集**所构成的子图中，有没有奇环。

明显这是**圆方树**的内容（不会圆方树的可以参见本人的[圆方树学习笔记](https://www.luogu.com.cn/blog/Troverld/yuan-fang-shu-xian-ren-zhang-xue-xi-bi-ji)）。故我们建出圆方树，然后判断每个方点所代表的点双中，是否存在一个奇环（可以直接通过二分图染色判定出来），如果存在就打上标记。则对于每次询问，我们只需要判断圆方树上两点间路径中是否有打上标记的节点即可。

下面分析一下复杂度。

明显圆方树的复杂度是 $O(n)$ 的；然后求单源最短路因为无边权，可以使用bfs（代码中使用了Dijkstra）；求路径上有无打标记的节点，可以树上倍增；故总复杂度 $O(n\log n)$。

[代码戳这儿](https://www.luogu.com.cn/record/37523338)

---

## 作者：yijan (赞：6)

考虑跑出 dfs 树。如果两个点在 dfs 树上路径本身长度就是奇数，可以直接走过去。

否则，相当于可以在这两点之间的路径上有两个点 $u,v$ ，可以通过在 $u$ 离开 dfs 树上的路径然后从 $v$ 回来继续走到另一个点的方式改变奇偶性。不难发现，这个条件等价于 $u,v$ 之间的路径存在于一个奇环上。同时我们还有一个结论，一个点双（因为这题要求点不相交）内部如果有一个奇环，那么点双内部任何两个点都处在一个奇环。

于是我们考虑给所有点双内有奇环的点打个标记，然后树上差分，询问的时候就询问一下两个点之间的路径上是否有点处于点双即可。

但是还是会出现一些会导致这个东西不太对的情况。

![4YW71N@8_JFEUOTY_3__4JX.png](https://i.loli.net/2020/06/09/W5apnxLPhXVNY24.png)

也就是说，进入一个点双了之后没办法通过不经过重复点跑出来。

我们可以把进入一个点双的点不标记为在这个点双之内。这样操作后 dfs 树路径上的那个点一定不会被计算贡献。因为这是 dfs 树，做 tarjan 的时候必然先会跑 dfs 树边，可以看出下面那个点双一定是在跑这个点访问到的。

于是在上面那种情况，路径上的点不会造成贡献。但是如果一个奇环能作为让长度变成奇数的，也就是在路径上既可以进有可以出，那么在这个路径上肯定存在至少两个点，在这个点双内部，所以肯定是有贡献的。

同时还得除去 LCA 的贡献：

![image.png](https://i.loli.net/2020/06/09/KDwzVdoTqBxeA32.png)

考虑这种情况，LCA 确实不是访问到所在点双的点，但是一样不能通过上面那个路径改变奇偶。这种情况很好解决，不计算 LCA 的贡献即可。如果一个与 LCA 有关的奇环可以被用，那么可以发现一定也还有一个点在路径上。

（好像还有不需要 tarjan 求点双直接整奇环的做法，但细节感觉可能比这个还多）

```cpp
#include "iostream"
#include "algorithm"
#include "cstring"
#include "cstdio"
#include "cmath"
#include "vector"
#include "map"
#include "set"
#include "queue"
using namespace std;
#define MAXN 1000006
//#define int long long
#define rep(i, a, b) for (int i = (a), i##end = (b); i <= i##end; ++i)
#define per(i, a, b) for (int i = (a), i##end = (b); i >= i##end; --i)
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define vi vector<int>
#define all(x) (x).begin() , (x).end()
#define mem( a ) memset( a , 0 , sizeof a )
typedef long long ll;
int n , m , q;
vi G[MAXN];
 
int dfn[MAXN] , low[MAXN] , g[MAXN][19] , clo , stk[MAXN] , top , ins[MAXN] , dep[MAXN] , odd[MAXN];
int od[MAXN] , bel[MAXN];
void tarjan( int u , int f ) {
	bel[u] = bel[f];
	dfn[u] = low[u] = ++ clo , ins[u] = 1;
	stk[++ top] = u;
	for( int v : G[u] ) {
		if( v == f ) continue;
		if( !dfn[v] ) {
			g[v][0] = u;
			rep( k , 1 , 18 ) if( g[g[v][k-1]][k-1] ) g[v][k] = g[g[v][k-1]][k-1]; else break;
			dep[v] = dep[u] + 1;
			tarjan( v , u ) , low[u] = min( low[u] , low[v] );
		}
		else if( ins[v] ) low[u] = min( low[u] , dfn[v] ) , odd[u] |= ( ~( dep[v] + dep[u] ) & 1 );
	}
	if( dfn[u] == low[u] ) {
		int flg = 0 , t = top;
		while( stk[t] != u && !flg ) flg = odd[stk[t]] , -- t;
		while( stk[top] != u ) {
			od[stk[top]] |= flg;
			ins[stk[top]] = 0;
			-- top;
		}
		-- top , ins[u] = 0;
	}
}
 
inline int lca( int u , int v ) {
	if( dep[u] < dep[v] ) u ^= v ^= u ^= v;
	if( dep[u] != dep[v] ) per( k , 18 , 0 ) if( dep[g[u][k]] >= dep[v] ) u = g[u][k];
	if( u == v ) return u;
	per( k , 18 , 0 ) if( g[u][k] != g[v][k] ) u = g[u][k] , v = g[v][k];
	return g[u][0];
}
 
int S[MAXN];
void dfs( int u , int f ) {
	S[u] += od[u];
	for( int v : G[u] ) if( v != f && dep[v] == dep[u] + 1 ) S[v] += S[u] , dfs( v , u );
}
 
inline bool fuck( int u , int v ) {
	if( bel[u] != bel[v] || u == v ) return false;
	if( dep[u] + dep[v] & 1 ) return true;
	return S[u] + S[v] - 2 * S[lca( u , v )] > 0;
}
 
void solve() {
	cin >> n >> m;
	int u , v;
	rep( i , 1 , m ) {
		scanf("%d%d",&u,&v);
		G[u].pb( v ) , G[v].pb( u );
	}
	rep( i , 1 , n ) if( !dfn[i] ) bel[i] = i , dep[i] = 1 , tarjan( i , i ) , dfs( i , i );
	cin >> q;
	rep( i , 1 , q ) scanf("%d%d",&u,&v) , puts( fuck( u , v ) ? "Yes" : "No" );
}
 
signed main() {
//    int T;cin >> T;while( T-- ) solve();
    solve();
}
```



---

## 作者：xhgua (赞：4)

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/CF97E)

$\Large\texttt{Description}$

给定一个 $n$ 个点 $m$ 条边的无向图，有 $q$ 次询问，每次询问 $x$ 和 $y$ 之间是否存在一条长度为奇数的简单路径。简单路径指的是不能经过任意一个点两次。

$n, m, q\leq 10^5$。

$\Large\texttt{Analysis}$

显然的，若 $x$ 和 $y$ 不在同一个连通块内，答案一定为 `No`，接下来考虑原图的一棵生成树，若在树上两点间的距离为奇数，则答案为 `Yes`。

考虑拓展到图上，相对于树而言，图会多出很多个环。如果环的长度为奇数，那么任意这一个简单环的路径都能够有一条长度为
奇数的路径，因为在简单环上，至少能提供一条长度为奇数的路径与长度为偶数的路径。如果简单环的长度为偶数，那么相对于树而言
答案不会有影响。

故若树上两点间的距离为偶数，我们考虑求出两点间是否存在一条经过奇环的路径，那也就是考虑两点间所有路径的并集是否存在奇环。

我们考虑建出原图的圆方树，对于每一个点双连通分量，通过二分图染色判断是否存在一个奇环，若存在，则给代表这个点双的方点打上标记。

最后只需判断圆方树上两点路径间是否存在打上标记的点即可，这是 trivial 的，前缀和一下即可。

$\Large\texttt{AC Code}$

```cpp
#include <bits/stdc++.h>

#define i64 long long
#define all(x) x.begin(), x.end()
#define seg(a, l, r) a + l, a + r + 1
#define rep(i, a, b) for(int i = (a); i <= (b); i++)
#define per(i, a, b) for(int i = (a); i >= (b); i--)

using namespace std;

const int N = 6e5 + 5, M = 6e5 + 5, LOG = 22;

struct DSU {
	
	int fa[N];
	
	void init(int n) {
		rep(i, 0, n + 1) fa[i] = i;
	}
	
	int father(int x) {
		if(fa[x] == x) return x;
		return fa[x] = father(fa[x]); 
	}
	
	void merge(int x, int y) {
		int fx = father(x), fy = father(y);
		if(fx == fy) return;
		
		fa[fy] = fx;
	}
	
	bool isSame(int x, int y) {
		return father(x) == father(y);
	}
} dsu;

struct Graph {
	
	struct Edge {
		int u, v, nxt;
		
		Edge() {}
		Edge(int _u, int _v, int _nxt) {
			u = _u; v = _v; nxt = _nxt;
		}
	} E[M << 1];
	
	int tot;
	int head[N];
	
	void clear() {
		tot = 0;
		memset(head, -1, sizeof(head));
	}
	
	void addEdge(int u, int v) {
		E[tot] = Edge(u, v, head[u]);
		head[u] = tot++;
	} 
} G, T;

int n, m, q, tot, timer;
int dfn[N], low[N], dis[N], dep[N], bel[N], col[N], cnt[N];
int fa[LOG][N];
bool vis[N];
stack<int> s;

bool color(int u) {
	for(int i = G.head[u]; ~i; i = G.E[i].nxt) {
		int v = G.E[i].v;
		if(bel[v] != tot) continue;
		
		if(!col[v]) {
			col[v] = 3 - col[u];
			if(color(v)) return true;
		}
		else if(col[u] == col[v]) return true;
	}
	
	return false;
}

void tarjan(int u, int f) {
	dfn[u] = low[u] = ++timer;
	dis[u] = dis[f] + 1;
	s.push(u);
	
	for(int i = G.head[u]; ~i; i = G.E[i].nxt) {
		int v = G.E[i].v;
		
		if(!dfn[v]) {
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			
			if(low[v] >= dfn[u]) {
				
				tot += 1;
				while(true) {
					
					int t = s.top();
					T.addEdge(tot, t); T.addEdge(t, tot);
					bel[t] = tot; col[t] = 0;
					s.pop();
					
					if(t == v) break;
				}
				
				T.addEdge(tot, u); T.addEdge(u, tot);
				bel[u] = tot; col[u] = 1;
				cnt[tot] = color(u);
			}
		}
		else low[u] = min(low[u], dfn[v]);
	}
}

void dfs(int u, int f) {
	dep[u] = dep[f] + 1;
	fa[0][u] = f;
	rep(i, 1, LOG - 1) fa[i][u] = fa[i - 1][fa[i - 1][u]]; 
	
	cnt[u] += cnt[f]; vis[u] = true;
	for(int i = T.head[u]; ~i; i = T.E[i].nxt) {
		int v = T.E[i].v;
		if(vis[v]) continue;
		dfs(v, u);
	}
}

int LCA(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	
	per(i, LOG - 1, 0) if(dep[fa[i][u]] >= dep[v]) u = fa[i][u];
	
	if(u == v) return u;
	 
	per(i, LOG - 1, 0) {
		if(fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	}
	
	return fa[0][u];
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

	cin >> n >> m;
	
	G.clear(); T.clear(); 
	dsu.init(n);
	
	rep(i, 1, m) {
		int u, v;
		cin >> u >> v;
		
		G.addEdge(u, v);
		G.addEdge(v, u);
		
		dsu.merge(u, v);
	}
	
	tot = n;
	
	rep(i, 1, n) {
		while(!s.empty()) s.pop();
		if(!dfn[i]) {
			tarjan(i, 0);
			dfs(i, 0);
		}
	}
	
	cin >> q;
	rep(i, 1, q) {
		int u, v;
		cin >> u >> v;
		
		if(!dsu.isSame(u, v)) {
			cout << "No" << "\n";
			continue;
		}
		
		if(dis[u] % 2 != dis[v] % 2) {
			cout << "Yes" << "\n"; 
			continue;
		}
		
		if(cnt[u] + cnt[v] - cnt[LCA(u, v)] - cnt[fa[0][LCA(u, v)]] > 0) cout << "Yes" << "\n";
		else cout << "No" << "\n";
	}

    return 0;
}
```

---

## 作者：KJGKMTZB (赞：3)

昨天考试考了这道题，考场上写了个树剖，思路是对的，但是由于本人代码能力太差导致挂成了0分（伤心）/kk（好歹是只有一个AC啊）

下面讲下主要思路：

首先这个题很明显是让我们去找一个路径上有没有边在奇环上，于是我们考虑先把这个图的DFS树建出来。

那么此时，对于一条指向一个点祖先的边，如果这条边与这条路径构成的是奇环，那么这个路径上的边都在奇环上，我么就要把这条路径上所有的边标记成在奇环上，这个可以用树剖来维护

如果对于一条指向祖先的边，它与这条路径构成的是偶环，但是这条路径上有边在奇环上，那么这个偶环一定能与那个奇环组成一个新的奇环，此时再把这个路径上所有边更新，这个仍然用树剖维护。

然后，对于每次询问，其他题解讲的已经很清楚了，我就不多说了

code:

```
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using std::vector;
#define ls rt<<1
#define rs rt<<1|1
#define mid ((l+r)>>1)
#define rep(a,b,c) for(int a=b;a<=c;a++) 
const int maxn=1e5+1;
struct Edge {
	int u,v;
}e[maxn<<1];
int head[maxn],ecnt;
inline void addedge(int u,int v) { e[++ecnt].v=v;e[ecnt].u=head[u];head[u]=ecnt; }
inline void add(int u,int v) { addedge(u,v); addedge(v,u); }
int fa[maxn],dep[maxn],top[maxn],son[maxn],siz[maxn],vis[maxn],val[maxn<<2],idx[maxn],id,n,m,a,b,q,bcj[maxn],fx,fy;
inline int find(int x) { return bcj[x]==x?x:bcj[x]=find(bcj[x]); }
inline void jh(int &x,int &y) { x^=y^=x^=y; }
inline void pushdown(int rt,int l,int r) { if(val[rt]!=(r-l+1)) return; val[ls]=(mid-l+1); val[rs]=(r-mid); }
inline void pushup(int rt) { val[rt]=val[ls]+val[rs]; }
inline void update(int rt,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return(void)(val[rt]=r-l+1);
	pushdown(rt,l,r);
	if(L<=mid) update(ls,l,mid,L,R);
	if(R>mid) update(rs,mid+1,r,L,R);
	pushup(rt);
}
inline int query(int rt,int l,int r,int L,int R) {
	if(L<=l&&r<=R) return val[rt];
	pushdown(rt,l,r);
	int ANS=0;
	if(L<=mid) ANS+=query(ls,l,mid,L,R);
	if(R>mid) ANS+=query(rs,mid+1,r,L,R);
	return ANS;
}
inline void upd(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) jh(x,y);
		update(1,1,n,idx[top[x]],idx[x]);
		x=fa[top[x]];
	}
	if(dep[y]<dep[x]) jh(x,y);
	update(1,1,n,idx[x]+1,idx[y]);
}
inline int qry(int x,int y) {
	int cnt=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) jh(x,y);
		cnt+=query(1,1,n,idx[top[x]],idx[x]);
		x=fa[top[x]];
	}
	if(dep[y]<dep[x]) jh(x,y);
	cnt+=query(1,1,n,idx[x],idx[y]);
	return cnt;
}
inline void dfs1(int x,int f) {
	siz[x]=1; dep[x]=dep[f]+1; fa[x]=f;
	for(int i=head[x],v;i;i=e[i].u) {
		v=e[i].v; if(dep[v]) continue;
		dfs1(v,x);
		siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
inline void dfs2(int x,int topf) {
	idx[x]=++id; top[x]=topf; if(!son[x]) return;
	dfs2(son[x],topf);
	for(int i=head[x],v;i;i=e[i].u) {
		v=e[i].v; if(dep[v]<dep[x]||v==son[x]) continue;
		if(fa[v]==x) dfs2(v,v);
	}
}
inline void dfs3(int x) {
	for(int i=head[x],v;i;i=e[i].u) {
		v=e[i].v; if(v==fa[x]) continue;
		if(fa[v]==x) dfs3(v);
		else if(dep[v]>dep[x]) continue;
		else if(!((dep[x]-dep[v])&1)) upd(x,v);
	}
}
inline void dfs4(int x) {
	for(int i=head[x],v;i;i=e[i].u) {
		v=e[i].v; if(v==fa[x]) continue;
		if(fa[v]==x) dfs4(v);
		else if(dep[v]>dep[x]) continue;
		else if((dep[x]-dep[v])&1) {
			int cnt=qry(x,v)-query(1,1,n,idx[v],idx[v]);
			if(cnt>0) upd(x,v);
		}
	}
}
inline int LCA(int x,int y) {
	while(top[x]!=top[y]) dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
inline int dis(int x,int y) {
	return (dep[x]+dep[y]-(dep[LCA(x,y)]<<1));
}
int main() {
	scanf("%d %d",&n,&m);
	rep(i,1,n) bcj[i]=i;
	rep(i,1,m) {
		scanf("%d %d",&a,&b); add(a,b);
		fx=find(a); fy=find(b);
		bcj[fy]=fx;
	}
	rep(i,1,n) {
		if(dep[i]) continue;
		dfs1(i,0); dfs2(i,i); dfs3(i); dfs4(i);
	}
	scanf("%d",&q);
	rep(i,1,q) {
		scanf("%d %d",&a,&b);
		int lca=LCA(a,b);
		if(find(a)!=find(b)) puts("No");
		else {
			if(dis(a,b)&1) puts("Yes");
			else if((qry(a,b)-query(1,1,n,idx[lca],idx[lca]))>0) puts("Yes");
			else puts("No");
		}
	}
}
```

---

## 作者：比利♂海灵顿 (赞：3)

# CF97E Leaders

## 简要题意

给一个简单无向图，询问两个点之间是否存在长度为奇数的简单路径。简单路径定义为没有重复点的路径，路径长度定义为边数。

## 点双

这里简单路径的定义是每个点出现最多一次的路径，所以优先考虑点双。发现点双里面，只要有至少一个奇环，任意两点间都存在奇路径。

## 点的类型

继续探索发现如果每个点双对应的方点的父亲称为 "主割点"，那么一个点双内，除了主割点，一个点到主割点有三种状态，没有奇路径，存在奇偶路径，仅有奇路径。分别称三种类型的节点为偶点，奇偶点，奇点。

## 求每个点的类型

发现有奇环的点双里，任意两点间都既有奇路径，也有偶路径，所以除主割点外的点都是奇偶点。

如果没有奇环，则 BFS 找到每个点到主点的最短路，最短路的奇偶性就是这个点的奇偶性。

对于找奇环和最短路，为了保证不会被菊花图卡到 $O(n^2)$，借助 [Calvincheng1231](https://www.luogu.com.cn/user/253946) 的题解中的方法，每个点双连通分量建一个新的点双连通图。

## 点双内的路径

对于点双内的情况，两个非主割点的点之间有简单奇路径，当且仅当有至少一个点是奇偶点，或有一个点是奇点。

因为这种情况可以取两个点到主割点的路径，使得路径总和为奇数，把重合部分删除，因为删除一条边，相当于它两次经过的贡献都删除了，所以奇偶性不变。

对于点双内，除主割点外的一点到主割点的路径，这个点只要是奇偶点或奇点，就能找到一条简单奇路径。

## 点双间的路径

接下来讨论一般情况，也就是点双间的路径，因为两点间路径上的割点已经确定了，所以我们只需要依次讨论端点和割点间路径的情况即可。这些点将路径分成了几段。

因为这几段分别在不同的点双内，所以每一段的情况就可以当作点双内部的情况来讨论，对于既有奇数又有偶数路径的段，我们称其为奇偶段，对于只有奇数路径的段，称奇段，没有奇数路径的段，称偶段。

类似地，整条路经存在奇路径，当且仅当这些段中有奇偶段，或者这些段中的奇段数量为奇数。

对于一段路径，如果它的两端有一端是路径所在点双的主割点，那么另一个端点的类型就是这一段的类型。

如果两端都不是路径所在点双的主割点，那么这一段分成两端，两段类型分别是两个点的类型。

## 树链剖分

所以我们需要做的就是查询圆方树上两点间路径上不同类型的圆点数量 (除去 LCA)。就能得到这些段的类型数量，然后 $O(1)$ 判断即可。

用树链剖分维护圆方树，支持查询路径三种类型的点的数量 (其实偶点数量和答案无关，无需维护)。由于无需修改，所以只需要用前缀和查询区间和即可。

总复杂度 $O(n + m + q\log n)$。

## 代码实现

```cpp
unsigned m, M, n, q, Bd;
unsigned A, B, C, D, t;
unsigned STop(0), ETop(0), Hd, Tl;
unsigned Cnt(0), CntCo(0), Ans[3];
unsigned Sum[200005][2], Tmp(0);
struct Node;
struct NNode;
struct Edge {
  Node* To, * Frm;
  Edge* Nxt;
}E[200005], *EStack[200005];
struct Node {
  Edge* Fst;
  NNode* Last;
  Node* Fa, * Bro, * Son, * Heavy, * Top;
  unsigned DFSr, Low, Dep, Size, BelC;
  char Type;
}N[200005], * Stack[100005], * CntN;
struct NEdge {
  NNode* To;
  NEdge* Nxt;
}NE[400005], *CntNE(NE);
struct NNode{
  NEdge* Fst;
  Node* Old;
  char Col, Dist;
}NN[200005], * Q[200005], *CntNN(NN);
inline void Tarjan(Node* x) {
  x->Low = x->DFSr = ++Cnt, x->BelC = CntCo, Stack[++STop] = x;
  Edge* Sid(x->Fst);
  while (Sid) {
    EStack[++ETop] = Sid;
    if(Sid->To->DFSr) {
      if(Sid->To->Fa) --ETop;
      x->Low = min(x->Low, Sid->To->DFSr);
    }
    else {
      unsigned LastTop(ETop);
      Tarjan(Sid->To), x->Low = min(x->Low, Sid->To->Low);
      if(Sid->To->Low == x->DFSr) {
        Node* Cur(++CntN);
        Cur->Fa = x, Cur->Bro = x->Son, x->Son = Cur;
        x->Last = Cur->Last = ++CntNN, CntNN->Old = x; 
        do {
          Stack[STop]->Bro = Cur->Son, Cur->Son = Stack[STop];
          Stack[STop]->Last = ++CntNN, (CntNN->Old = Stack[STop])->Fa = Cur;
        } while (Stack[STop--] != Sid->To);
        NNode * LiF, * LiT;
        do {
          LiF = EStack[ETop]->Frm->Last, LiT = EStack[ETop]->To->Last;
          (++CntNE)->Nxt = LiF->Fst, LiF->Fst = CntNE, CntNE->To = LiT;
          (++CntNE)->Nxt = LiT->Fst, LiT->Fst = CntNE, CntNE->To = LiF;
        } while ((ETop--) ^ LastTop);
      }
    }
    Sid = Sid->Nxt;
  }
}
inline void BFS(Node* x) {
  char Flg(0);
  Hd = Tl = 0, (Q[++Tl] = x->Last)->Col = 1, x->Last->Dist = 1;
  while (Hd ^ Tl) {
    NNode* Cur(Q[++Hd]);
    NEdge* Sid(Cur->Fst);
    while (Sid) {
      Sid->To->Col |= (Cur->Col ^ 3);
      if(Sid->To->Col == 3) {Flg = 1; break;}
      if(!(Sid->To->Dist)) (Q[++Tl] = Sid->To)->Dist = Cur->Dist + 1;
      Sid = Sid->Nxt;
    }
    if(Flg) break;
  } 
  if(Flg) x->Type = 2;
  else
    for (unsigned i(2); i <= Hd; ++i)
      Q[i]->Old->Type = ((Q[i]->Dist & 1) ? 0 : 1);
}
inline void PreDFS (Node* x) {
  x->Size = 1;
  Node* Cur(x->Son);
  unsigned Mx(0);
  while (Cur) {
    Cur->Dep = x->Dep + 1, PreDFS(Cur), x->Size += Cur->Size;
    if(Cur->Size > Mx) x->Heavy = Cur, Mx = Cur->Size;
    Cur = Cur->Bro;
  }
}
inline void DFS (Node* x) {
  x->DFSr = ++Cnt;
  if(x->Type) Sum[Cnt][x->Type - 1] = 1;
  if(!(x->Heavy)) return;
  x->Heavy->Top = x->Top, DFS(x->Heavy);
  Node* Cur(x->Son);
  while (Cur) {
    if(Cur != x->Heavy) Cur->Top = Cur, DFS(Cur);
    Cur = Cur->Bro;
  }
}
inline char Ask(Node* x, Node* y) {
  Ans[1] = Ans[2] = 0;
  while (x->Top != y->Top) {
    if(x->Top->Dep < y->Top->Dep) swap(x, y);
    C = x->Top->DFSr, D = x->DFSr, x = x->Top->Fa;
    Ans[1] += Sum[D][0] - Sum[C - 1][0];
    Ans[2] += Sum[D][1] - Sum[C - 1][1];
  }
  if(x->Dep < y->Dep) swap(x, y);
  C = y->DFSr, D = x->DFSr, x = y;
  Ans[1] += Sum[D][0] - Sum[C - 1][0];
  Ans[2] += Sum[D][1] - Sum[C - 1][1];
  --Ans[x->Type];
  if(Ans[2] || (Ans[1] & 1)) return 1;
  return 0;
}
signed main() {
  n = RD(), M = ((m = RD()) << 1), CntN = N + n;
  for (unsigned i(0); i < M; i += 2) {
    A = RD(), B = RD();
    E[i].Nxt = N[A].Fst, N[A].Fst = E + i;
    E[i ^ 1].Nxt = N[B].Fst, N[B].Fst = E + (i ^ 1);
    E[i].To = N + B, E[i].Frm = N + A;
    E[i ^ 1].To = N + A, E[i ^ 1].Frm = N + B;
  }
  for (unsigned i(1); i <= n; ++i) if(!(N[i].DFSr)) ++CntCo, Tarjan(N + i);
  Cnt = 0;
  for (Node* i(N + n + 1); i <= CntN; ++i) BFS(i);
  for (unsigned i(1); i <= n; ++i) if(N[i].Fa && N[i].Fa->Type) N[i].Type = 2;
  for (unsigned i(1); i <= n; ++i) if(!N[i].Size) N[i].Dep = 1, PreDFS(N + i);
  for (unsigned i(1); i <= n; ++i) if(!N[i].Top) N[i].Top = N + i, DFS(N + i);
  for (unsigned i(1); i <= Cnt; ++i) Sum[i][0] += Sum[i - 1][0], Sum[i][1] += Sum[i - 1][1];
  for (unsigned i(RD()); i; --i) {
    A = RD(), B = RD(), --q;
    if(A == B) {printf("No\n");continue;}
    if(N[A].BelC ^ N[B].BelC) {printf("No\n");continue;}
    printf(Ask(N + A, N + B) ? "Yes\n" : "No\n");
  } 
  return Wild_Donkey;
}
```

---

## 作者：raincity (赞：2)

[更好的阅读体验](https://blog.calvincheng1231.org.cn/sols/193.html)

## 分析
首先比较显然的想法是随便找一棵生成树，然后 $u$ 和 $v$ 之间存在奇数长度路径当且仅当满足下列两个条件之一：

* $u$ 和 $v$ 在生成树上的路径长度为奇数
* $u$ 和 $v$ 在生成树上的路径中，存在一条边在原图中的一个奇环中。

只要提前知道生成树上的每一条边是否在奇环中，然后在树上就随便用什么算法处理都行。

如何判断一条边是否在奇环中呢？

首先，两个点双之间肯定没有环。

而如果一个点双中存在一个奇环，那么这个点双中任意一条边都在一个奇环中！

选取两个奇环上的两点 $x,y$，向外扩展出一条路径：

![](https://cdn.luogu.com.cn/upload/image_hosting/cyar66g6.png)

比如上面这张图中，奇环为 1-4-5-1，选取 $x=1,y=4$，向外扩展出路径 1-2-3-4。

一定存在一条同时经过 $x$ 和 $y$ 的奇环。所以，存在两条 $x$ 到 $y$ 的路径，一条长度为偶数，一条长度为奇数。

新扩展出的路径一定可以和着两条路径中的一条组成一个奇环。在上图中，这个环是 1-2-3-4-5-1。

故一条边在奇环中，当且仅当它所在的点双中存在奇环。

可以在 Tarjan 时找到点双中的所有边，采用二分图的方式判断奇环。

时间复杂度线性。

## update: 解决
判断的时候应该要把 V-DCC 单独拿出来建新图判断，暴力遍历出边可以被卡成平方，下面是数据生成器：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

int main()
{
    freopen("CF97E.in", "w", stdout);
    puts("66667 99999");
    for (int i = 1; i <= 33333; i++)
        printf("1 %d\n1 %d\n%d %d\n", i * 2, i * 2 + 1, i * 2, i * 2 + 1);
    puts("0");
    return 0;
}
```

这份代码会生成 33333 个三元环。

被 hack 的题解：

* [木xx木大的题解](https://www.luogu.com.cn/blog/flyingfan/cf97e-leaders-dian-shuang-pan-ji-huan-shu-shang-ci-fen-post)，开 O2 后要跑 5s
* [whhsteven的题解](https://www.luogu.com.cn/blog/118109/cf97e)，开 O2 后要跑 4s

下面给出（我认为）正确的实现：

```cpp
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 100005, M = 200005, LOG = 17;
int n, m, q;
int head[N], ver[M], nxt[M], tot = 1, v[N];
int _head[N], _ver[M], _nxt[M], _tot = 1;
int dfn[N], low[N], dfsNum, stkNode[N], topNode, stkEdge[M >> 1][3], topEdge, color[N], checkNum;
int dep[N], fa[N][LOG], rt[N], root;
bool ok[M >> 1], flag[N][LOG], vis[M >> 1];

void addedge(int x, int y) { ver[++tot] = y, nxt[tot] = head[x], head[x] = tot; }
void _addedge(int x, int y) { _ver[++_tot] = y, _nxt[_tot] = _head[x], _head[x] = _tot; }

bool check(int cur)
{
    v[cur] = checkNum;
    for (int i = _head[cur]; i; i = _nxt[i])
    {
        int to = _ver[i];
        if (v[to] == checkNum)
        {
            if (color[to] == color[cur])
                return false;
            continue;
        }
        color[to] = 3 - color[cur];
        if (!check(to))
            return false;
    }
    return true;
}

void Tarjan(int cur)
{
    low[cur] = dfn[cur] = ++dfsNum, stkNode[++topNode] = cur;
    for (int i = head[cur]; i; i = nxt[i])
    {
        int curTop = topEdge, to = ver[i];
        if (!vis[i >> 1])
            vis[i >> 1] = true, topEdge++, stkEdge[topEdge][0] = (i >> 1), stkEdge[topEdge][1] = cur, stkEdge[topEdge][2] = to;
        if (!dfn[to])
        {
            Tarjan(to);
            low[cur] = min(low[cur], low[to]);
            if (low[to] >= dfn[cur])
            {
                _head[cur] = _head[to] = 0, _tot = 1;
                while (stkNode[topNode] != to)
                    _head[stkNode[topNode]] = 0, topNode--;
                topNode--;
                for (int j = curTop + 1; j <= topEdge; j++)
                    _addedge(stkEdge[j][1], stkEdge[j][2]);
                color[cur] = 1, checkNum++;
                if (!check(cur))
                    for (int j = curTop + 1; j <= topEdge; j++)
                        ok[stkEdge[j][0]] = true;
                topEdge = curTop;
            }
        }
        else
            low[cur] = min(low[cur], dfn[to]);
    }
}

void Tarjan()
{
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
}

void dfs(int cur)
{
    rt[cur] = root;
    for (int i = head[cur]; i; i = nxt[i])
    {
        int to = ver[i];
        if (rt[to])
            continue;
        dep[to] = dep[cur] + 1, fa[to][0] = cur, flag[to][0] = ok[i >> 1];
        for (int j = 1; j < LOG; j++)
            fa[to][j] = fa[fa[to][j - 1]][j - 1], flag[to][j] = flag[to][j - 1] || flag[fa[to][j - 1]][j - 1];
        dfs(to);
    }
}

bool query(int x, int y)
{
    if (rt[x] != rt[y] || x == y)
        return false;
    if ((dep[x] + dep[y]) & 1)
        return true;
    if (dep[x] < dep[y])
        swap(x, y);
    for (int i = LOG - 1; i >= 0; i--)
        if (dep[fa[x][i]] >= dep[y])
        {
            if (flag[x][i])
                return true;
            x = fa[x][i];
        }
    if (x == y)
        return false;
    for (int i = LOG - 1; i >= 0; i--)
        if (fa[x][i] != fa[y][i])
        {
            if (flag[x][i] || flag[y][i])
                return true;
            x = fa[x][i], y = fa[y][i];
        }
    return flag[x][0] || flag[y][0];
}

template <class T>
void read(T &ret)
{
    ret = 0;
    char ch = getchar(), flag = 0;
    while ((ch < '0' || ch > '9') && ch != '-')
        ch = getchar();
    if (ch == '-')
        ch = getchar(), flag = 1;
    while (ch >= '0' && ch <= '9')
        ret = ret * 10 + ch - '0', ch = getchar();
    if (flag)
        ret = -ret;
}

int main()
{
    read(n), read(m);
    for (int i = 1; i <= m; i++)
    {
        int x, y;
        read(x), read(y);
        addedge(x, y), addedge(y, x);
    }
    Tarjan();
    for (int i = 1; i <= n; i++)
    {
        if (rt[i])
            continue;
        for (int j = 0; j < LOG; j++)
            fa[i][j] = 1;
        root = i;
        dfs(i);
    }
    read(q);
    while (q--)
    {
        int x, y;
        read(x), read(y);
        if (query(x, y))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}
```

---

## 作者：whhsteven (赞：2)

### 题目链接

洛谷：[CF97E](https://www.luogu.com.cn/problem/CF97E)

Codeforces：[CF97E](https://codeforces.com/problemset/problem/97/E)

&nbsp;

### 题意简述

- 给定 $n$ 个点 $m$ 条边的无向图，没有重边和自环。

- 每次询问点 $u,v$ 间是否存在长度为奇数的简单路径。

- 这里简单路径定义为不经过重复点的路径。

&nbsp;

### 题解

**首先 % FGF 学长并祝她在余姚取得佳绩！**

本篇题解与 FGF 学长的题解思路一致，对具体实现的说明更详细一些，以期有助于理解，同时也为自己作一笔记。

&nbsp;

任意取一棵生成树，如果 $u,v$ 之间的树上路径长度为奇数则显然可行。

当 $u,v$ 之间树上路径为偶数时，我们需要找到其中的一段并用与之**两端点相同、奇偶性相反**的一段非树边路径将其替换。这样的替换能够实现，当且仅当这一段**有不少于 $1$ 条边存在于某个奇环上**。

应该如何判断任意一条边是否在某个奇环上呢？

一条边在某个奇环上，当且仅当其所在的**点双连通分量**（以下简称 NDCC）中存在奇环。

- **充分性：** 在一个奇环上任取两点，则这两点间的两条路径为一奇一偶。从这两点向外连出一个环，并称之为一次**扩展**，则新连的这一段必然能够与这两点间的这两条路径之一形成一个新的奇环。而在一个点数大于 $1$ 的 NDCC 中任意一边均在环上，从而可知这个 NDCC 可以由其某一个奇环扩展得到，并且**任意一条边均存在于某个奇环上**。

- **必要性：** 易见，两个 NDCC 之间不存在环，否则其将直接成为一个大的 NDCC。

所以我们对每一个 NDCC 求出其是否有奇环。这里，通过**二分染色**，即可判定一个 NDCC 中奇环存在与否。

&nbsp;

另外注意，需要判断图的连通性。

&nbsp;

### 代码

共实现了 $3$ 个 DFS 函数：

- `Tarjan`：求出图中的 NDCC，并顺便得到图的 DFS 树（即为一棵可行的生成树）；

- `color`：通过二分染色判断奇环存在性；

- `count`：在图的生成树上统计，每一个点到根的树上路径上，存在于某个奇环之上的边的条数。

```cpp
#include<bits/stdc++.h>

using namespace std;

namespace acah
{
	template<typename T> inline void qread(T &x)
	{
		x = 0; char ch = getchar();
		while(!isdigit(ch)) ch = getchar();
		while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	}
	
	const int maxn = 1e5 + 7;
	
	int N, M, Q;
	int ac[maxn << 1];
	
	struct edge {
		int to, nt;
	} e[maxn << 1];
	int hd[maxn], _ = 1;
	
	inline void ins(int u, int v)
	{e[++_].to = v, e[_].nt = hd[u], hd[u] = _;}
	
	int ind, dfn[maxn], low[maxn], bel[maxn << 1];
	int st[maxn << 1], tp, ndcc;
	int fa[maxn][20], rt[maxn], dep[maxn];
	bool vis[maxn << 1];
	vector<int> C[maxn], E[maxn];
	
	void Tarjan(int u, int f)
	{
		dfn[u] = low[u] = ++ind;
		fa[u][0] = e[f ^ 1].to, rt[u] = rt[fa[u][0]],
		dep[u] = dep[fa[u][0]] + 1;
		for(int i = 1; i <= 18; i++)
			fa[u][i] = fa[fa[u][i - 1]][i - 1];
		for(int i = hd[u]; i; i = e[i].nt) {
			if(vis[i] || i == (f ^ 1)) continue;
			st[++tp] = i;
			int v = e[i].to;
			if(!dfn[v]) {
				Tarjan(v, i);
				low[u] = min(low[u], low[v]);
				if(low[v] >= dfn[u]) {
					int cur;
					C[++ndcc].push_back(u);
					do {
						cur = st[tp--];
						bel[cur] = bel[cur ^ 1] = ndcc;
						vis[cur] = vis[cur ^ 1] = true;
						C[ndcc].push_back(e[cur].to);
						E[ndcc].push_back(cur); //只存单向边即可
					} while(cur != i);
				}
			} else low[u] = min(low[u], dfn[v]);
		}
	}
	
	int col[maxn];
	
	bool color(int u, int f)
	{
		int fath = e[f ^ 1].to;
		if(vis[u]) return (col[u] == col[fath]);
		vis[u] = true, col[u] = col[fath] ^ 1;
		for(int i = hd[u]; i; i = e[i].nt) {
			if(bel[i] != bel[f] || i == (f ^ 1)) continue;
			int v = e[i].to;
			if(color(v, i)) return true;
		}
		return false;
	}
	
	int cnt[maxn];
	
	void count(int u, int f)
	{
		vis[u] = true;
		for(int i = hd[u]; i; i = e[i].nt) {
			int v = e[i].to;
			if(vis[v] || i == (f ^ 1)) continue;
			cnt[v] = cnt[u] + ac[i];
			count(v, i);
		}
	}
	
	int lca(int u, int v)
	{
		if(dep[u] < dep[v]) swap(u, v);
		int dif = dep[u] - dep[v];
		for(int i = 18; i >= 0; i--)
			if(dif & (1 << i))
				u = fa[u][i];
		if(u == v) return u;
		for(int i = 18; i >= 0; i--)
			if(fa[u][i] != fa[v][i])
				u = fa[u][i], v = fa[v][i];
		return fa[u][0];
	}
	
	int work()
	{
		qread(N), qread(M);
		for(int i = 1, u, v; i <= M; i++)
			qread(u), qread(v), ins(u, v), ins(v, u);
		
		for(int i = 1; i <= N; i++)
			if(!dfn[i]) rt[0] = i, Tarjan(i, 0);
		
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= ndcc; i++) {
			for(int s = C[i].size(), j = 0; j < s; j++)
				vis[C[i][j]] = false;
			if(color(e[E[i][0]].to, E[i][0]))
				for(int s = E[i].size(), j = 0; j < s; j++)
					ac[E[i][j]] = ac[E[i][j] ^ 1] = 1;
		}
		
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= N; i++)
			if(!vis[i]) count(i, 0);
		
		qread(Q);
		for(int q = 1, u, v; q <= Q; q++) {
			qread(u), qread(v);
			if(rt[u] != rt[v]) puts("No");
			else {
				int l = lca(u, v);
				if((dep[u] + dep[v] - (dep[l] << 1)) & 1) puts("Yes");
				else if(cnt[u] + cnt[v] - (cnt[l] << 1)) puts("Yes");
				else puts("No");
			}
		}
		return 0;
	}
}

int main() {return acah::work();}
```

---

## 作者：Forever1507 (赞：1)

这题调得真的人都麻掉了。整整 $156$ 行愣是给调了 $2h$。

首先可以考虑整一棵生成树，跑树上路径。

如果树上路径本身就是奇数直接过，反之则必定有至少一个奇环覆盖了至少一条树边（改变奇偶性）。又考虑到奇环必然是点双，所以上点双。至于判断这个点双有没有奇环可以借鉴二分图判定的做法（注意到有奇环的点双向外拓展会时每条边都在一个奇环里），用染色判断，然后在 LCA 里顺路把是否在奇环也倍增一下即可。

做点双的塔尖算法中，我们除了点栈之外可以额外开一个边栈记录边。

坑点：询问一定要判联通，不然就寄（这里我调了几个世纪（bushi））

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,low[100005],dfn[100005],tot,root,cnt,sum,d[100005],dp[100005][20];
vector<pair<int,int> >nbr[100005];
vector<int>nbr2[100005];
struct node{
	int e,s,t;
}; //记录边（栈）
stack<int>stk;//点栈
stack<node>stk2;//边栈
int col[100005],a[100005];//染色和连通块
bool tag[200005][21],tagg[200005],vis[100005];//判断是否在奇环 
bool check(int cur){//二分图染色
	a[cur]=sum;
	for(int i=0;i<nbr2[cur].size();++i){
		int to=nbr2[cur][i];
		if(a[to]==sum){
			if(col[to]==col[cur])return 0;
			continue;
		}
		col[to]=3-col[cur];
		if(!check(to))return 0;
	}
	return 1;
}   
void tarjan(int cur){
	dfn[cur]=low[cur]=++tot;
	stk.push(cur);
	for(int i=0;i<nbr[cur].size();++i){
		int to=nbr[cur][i].first,e=nbr[cur][i].second;
		node crr=stk2.top();
		if(!vis[e]){
			stk2.push({e,cur,to});
			vis[e]=1;
		}
		if(!dfn[to]){
			tarjan(to);
			low[cur]=min(low[cur],low[to]);
			if(low[to]<dfn[cur])continue;
			int x=0;
			nbr2[cur].clear();
			nbr2[to].clear();
			while(!stk.empty()&&x!=to){
				x=stk.top();
				stk.pop();
				nbr2[x].clear();
			}//建新图跑二分图
			node y;
			queue<node>q;
			while(!stk2.empty()){
				y=stk2.top();
				if(y.e==crr.e&&y.s==crr.s&&y.t==crr.t)break;
				stk2.pop();
				q.push(y);
				nbr2[y.s].push_back(y.t);
				nbr2[y.t].push_back(y.s);
			}
			sum++;
			if(!check(cur)){//打标记，在奇环里
				while(!q.empty()){
					node xx=q.front();
					tagg[xx.e]=1;
					q.pop();
				}
			}
		}
		else{
			low[cur]=min(low[cur],dfn[to]);	
		}
	} 
}   
void before(int cur){
	a[cur]=sum;//常规LCA
	for(int i=0;i<nbr[cur].size();++i){
		pair<int,int>to=nbr[cur][i];
		if(a[to.first])continue;
		d[to.first]=d[cur]+1;
		dp[to.first][0]=cur;
		if(tagg[to.second])tag[to.first][0]=1;
		for(int j=1;j<=19;++j){
			dp[to.first][j]=dp[dp[to.first][j-1]][j-1];
			tag[to.first][j]=tag[to.first][j-1]|tag[dp[to.first][j-1]][j-1];//顺路维护tag
		}
		before(to.first);
	}
	return;
}   
int LCA(int u,int v){
	if(d[u]>d[v])swap(u,v);
	for(int i=19;i>=0;i--){
		if((1<<i)<=d[v]-d[u]){
			v=dp[v][i];
		}
	}
	if(u==v)return u;
	for(int i=19;i>=0;i--){
		if(dp[u][i]!=dp[v][i]){
			u=dp[u][i];
			v=dp[v][i];
		}
	}
	return dp[u][0];
}   
int calc(int u,int v){//算距离，记得判联通不合法！
	if(a[u]!=a[v]||u==v)return 0;
	int lca=LCA(u,v);
	return d[u]+d[v]-2*d[lca];
}   
bool ask(int u,int v){//判奇环
	if(a[u]!=a[v]||u==v)return 0;
	if(d[u]>d[v])swap(u,v);
	for(int i=19;i>=0;i--){
		if((1<<i)<=d[v]-d[u]){
			if(tag[v][i])return 1;
			v=dp[v][i];
		}
	}
	if(u==v)return 0;
	for(int i=19;i>=0;i--){
		if(dp[u][i]!=dp[v][i]){
			if(tag[u][i]||tag[v][i])return 1;
			u=dp[u][i];
			v=dp[v][i];
		}
	}
	return tag[u][0]|tag[v][0];
}   
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int u,v;
		cin>>u>>v;
		if(u==v)continue;
		nbr[u].push_back(make_pair(v,i));
		nbr[v].push_back(make_pair(u,i));
	}
	stk2.push({0,0,0});//先加，不然直接取top会RE
	for(int i=1;i<=n;++i){
		if(!dfn[i])tarjan(i);//不一定联通
	}
	memset(a,0,sizeof(a));
	sum=0;
	for(int i=1;i<=n;++i)if(!d[i])++sum,d[i]=1,before(i);
	int q;
	cin>>q;
	for(int i=1;i<=q;++i){
		int u,v;
		cin>>u>>v;
		if(calc(u,v)%2==1||ask(u,v)){
			cout<<"Yes\n";
		}
		else cout<<"No\n";
	}
	return 0;
}   
```


---

## 作者：极寒神冰 (赞：1)

首先分两种情况讨论

1.两点在图中距离是奇数。

2.两点在图中距离为偶数，但是在路径上有一些边在环上，那么可以走环上的另外一条边，改变奇偶性。当前距离为偶数，因为偶+偶=偶，偶+奇=奇。所以必须要走奇环才能改变奇偶性。

如果一个点双中有奇环，就给这个奇环上的点打上标记，然后树上差分，询问时就询问两个点之间是否处于点双即可。

---------------------------分割线---------------------------------------------------------------------------------------


原来的代码写挂了，下次有时间再调出来(

事实上由于是无向图所以并不需要联通分量，直接并查集维护即可

```
#include<bits/stdc++.h>
#define ld long double
#define tset puts("qwq");
#define test puts("QAQ");
#define pb(a) push_back(a)
#define pii pair<int,int> 
#define mkp make_pair
#define bg begin()
#define ed end()
#define FR(i,a,b) for(int i=(a),i##E=(b);i<i##E;i++)
#define FL(i,a,b) for(int i=(b)-1,i##E=(a-1);i>i##E;i--)
#define R(i,a,b) for(int i=(a),i##E=(b);i<=i##E;i++)
#define L(i,a,b) for(int i=(b),i##E=(a);i>=i##E;i--)
#define sz(a) int((a).size())
#define us unsigned 
#define int long long
#define Swap(x,y) (x^=y^=x^=y)
using namespace std;
const int inf=0x7f7f7f7f7f7f;
int mod;
const ld eps=1e-8;
inline int add(int x) {return x >= mod ? x - mod : x;}
inline int sub(int x) {return x < 0 ? x + mod : x;}
inline void Add(int &x, int y) {if ((x += y) >= mod) x -= mod;}
inline void Sub(int &x, int y) {if ((x -= y) < 0) x += mod;}
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
//char buf[1<<21], *p1 = buf, *p2 = buf;
int read()
{
    int x=0,f=1;
    char c=getchar();
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
    return x*f;
}
const int N=1e5+10;
int n,m,q;
int fa[N];
int bz[18][N];
int dep[N],s[N],a[N];
std::vector<int>e[N];
inline int find_r(int x){
	return x==fa[x]?x:fa[x]=find_r(fa[x]);
}
void dfs1(int u)
{
	dep[u]=dep[bz[0][u]]+1;
	for(int v:e[u])
	{
		if(!dep[v])
		{
			bz[0][v]=u;
			dfs1(v);
			if(find_r(u)==find_r(v)) a[u]|=a[v];
		}
		else if(dep[v]<dep[u]-1)
		{
			if((dep[u]+dep[v]+1)&1) a[u]=1;
			for(int x=find_r(u);dep[x]>dep[v]+1;x=find_r(x)) fa[x]=bz[0][x];
		}
	}
}
void dfs2(int u)
{
	s[u]+=a[u];
	for(int v:e[u])
	{
		if(dep[v]==dep[u]+1)
		{
			if(find_r(u)==find_r(v)) a[v]|=a[u];
			s[v]=s[u];
			dfs2(v);
		}
	}
}
int LCA(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	L(i,0,16) if(dep[bz[i][x]]>=dep[y]) x=bz[i][x];
	if(x==y) return x;
	L(i,0,16) if(bz[i][x]!=bz[i][y]) x=bz[i][x],y=bz[i][y];
	return bz[0][x];
}
signed main()
{
	n=read(),m=read();
	R(i,1,m)
	{
		int u=read(),v=read();
		e[u].pb(v),e[v].pb(u);
	}
	R(i,1,n) fa[i]=i;
	R(i,1,n) if(!dep[i]) dfs1(i),dfs2(i);
	R(j,1,16)
		R(i,1,n) bz[j][i]=bz[j-1][bz[j-1][i]];
	q=read();
	while(q--)
	{
		int u=read(),v=read();
		int l_a=LCA(u,v);
		//if(q==2) printf("%lld\n",l_a);
		if(!l_a) puts("No");
		else if(((dep[u]+dep[v])&1)||s[u]+s[v]-2*s[l_a]) puts("Yes");
		else puts("No");
	}
}
```



---

