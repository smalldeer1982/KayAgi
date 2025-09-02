# Cities Excursions

## 题目描述

There are $ n $ cities in Berland. Some pairs of them are connected with $ m $ directed roads. One can use only these roads to move from one city to another. There are no roads that connect a city to itself. For each pair of cities $ (x,y) $ there is at most one road from $ x $ to $ y $ .

A path from city $ s $ to city $ t $ is a sequence of cities $ p_{1} $ , $ p_{2} $ , ... , $ p_{k} $ , where $ p_{1}=s $ , $ p_{k}=t $ , and there is a road from city $ p_{i} $ to city $ p_{i+1} $ for each $ i $ from $ 1 $ to $ k-1 $ . The path can pass multiple times through each city except $ t $ . It can't pass through $ t $ more than once.

A path $ p $ from $ s $ to $ t $ is ideal if it is the lexicographically minimal such path. In other words, $ p $ is ideal path from $ s $ to $ t $ if for any other path $ q $ from $ s $ to $ t $ $ p_{i}<q_{i} $ , where $ i $ is the minimum integer such that $ p_{i}≠q_{i} $ .

There is a tourist agency in the country that offers $ q $ unusual excursions: the $ j $ -th excursion starts at city $ s_{j} $ and ends in city $ t_{j} $ .

For each pair $ s_{j} $ , $ t_{j} $ help the agency to study the ideal path from $ s_{j} $ to $ t_{j} $ . Note that it is possible that there is no ideal path from $ s_{j} $ to $ t_{j} $ . This is possible due to two reasons:

- there is no path from $ s_{j} $ to $ t_{j} $ ;
- there are paths from $ s_{j} $ to $ t_{j} $ , but for every such path $ p $ there is another path $ q $ from $ s_{j} $ to $ t_{j} $ , such that $ p_{i}>q_{i} $ , where $ i $ is the minimum integer for which $ p_{i}≠q_{i} $ .

The agency would like to know for the ideal path from $ s_{j} $ to $ t_{j} $ the $ k_{j} $ -th city in that path (on the way from $ s_{j} $ to $ t_{j} $ ).

For each triple $ s_{j} $ , $ t_{j} $ , $ k_{j} $ ( $ 1<=j<=q $ ) find if there is an ideal path from $ s_{j} $ to $ t_{j} $ and print the $ k_{j} $ -th city in that path, if there is any.

## 样例 #1

### 输入

```
7 7 5
1 2
2 3
1 3
3 4
4 5
5 3
4 6
1 4 2
2 6 1
1 7 3
1 3 2
1 3 5
```

### 输出

```
2
-1
-1
2
-1
```

# 题解

## 作者：KaisuoShutong (赞：6)

感觉 @Saliеri 的题解从什么意义上来说都很麻烦，我的实现应该简单一些？

## 题意
求一张有向图上两点间字典序最小路径的第 k 个，或判定其不存在字典序最小路径/无法到达。  
$n,m\le 3000, q\le400000$。

## 题解
注意到 $n$ 只有 $3000$，允许我们枚举路径终点 $T$。  
此时建出反图，那么从 $T$ 做一遍 dfs 即可找到所有能到达 $T$ 的点，不管字典序问题。  
那么，对于每个可以到达 $T$ 的点，其在到 $T$ 的字典序最小路径上的后继节点都是唯一的，即为可以到达 $T$ 的点中字典序最小的。  
我们将每个点连边其后继节点，那么会形成一颗新的树，注意到其为内向。  
再将新树中的边反向，此时形成一颗外向树吗，此时再从 $T$ 点 dfs，能够访问到的点即为合法的起点 $S$。

最后，将询问离线，在第二个 dfs 时开个栈统计一下就搞定了。

点个赞吧。

```cpp
#include<bits/stdc++.h>
using namespace std;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 3010;
vector<int>g[maxn],z[maxn],G[maxn];char v[maxn];int Q[maxn],pr[400010],n,m,q;
void add(int x,int y) {g[y].push_back(x),z[x].push_back(y);}
void ADD(int x,int y) {G[x].push_back(y);}
void dfs(int x) {v[x]=1;for(auto y:g[x]) if(!v[y]) dfs(y);}
struct E {int s,t,k,n;};vector<E>ve[maxn],w[maxn];
void _dfs(int x) {
	Q[++Q[0]]=x;
	for(auto y:w[x]) if(Q[0]>=y.k) pr[y.n]=Q[Q[0]-y.k+1];
	for(auto y:G[x]) _dfs(y);--Q[0];
}
signed main() {
	n=read(),m=read(),q=read();
	for(int i=1,x;i<=m;i++) x=read(),add(x,read());
	for(int i=1;i<=n;i++) sort(z[i].begin(),z[i].end());
	for(int i=1,x,y;i<=q;i++) x=read(),y=read(),ve[y].push_back((E){x,y,read(),i}),pr[i]=-1;
	for(int t=1;t<=n;t++) {
		for(int i=1;i<=n;i++) G[i].clear(),w[i].clear(),v[i]=0;
		v[t]=1,dfs(t);
		for(int i=1;i<=n;i++) if(v[i]&&i^t)
			for(auto y:z[i]) if(v[y]) {ADD(y,i);break;}
		for(auto y:ve[t]) w[y.s].push_back(y);
		_dfs(t);
	}
	for(int i=1;i<=q;i++) cout<<pr[i]<<'\n';
	return 0;
}
```

---

## 作者：Spikeweed (赞：5)

#### Solution：
观察数据范围发现点数和边数比较小，$n, m\leq 3000$，但是询问数比较多。
所以考虑把询问离线下来，然后暴力枚举每一个点，$O(nm)$ 去更新答案。
##### 数组含义：
假设我们当前正在更新从 $root$ 这个点开始的答案：

$q[root][y][i][\{k, id\}]$：表示 $x$ 到 $y$ 的路径上的第 $i$ 个问题问 $x$ 到 $y$ 的第 $k$ 个点是啥，$id$ 为离线后原询问的下标

$ans[i]$：表示第 $i$ 个询问的答案

$vis2[i]$：表示这个点的是否有被更新过答案，如果被更新过，则不能再次更新（字典序最小）

$vis1[i]$：表示这个点是否在搜索树上（是否被走过），如果是，那么说明形成了环，反之不成环。

$cnt[i]$：表示 $i$ 是多少个环的起始点

特别的， $tmp$ 表示当前环的个数。

##### 算法过程：
枚举路径初始点 $root$ ，做一遍 $dfs$
假设当前我们搜索到节点 $y$ , 有如下三种情况：
*  $vis2[y] = 1$ , 说明当前节点有字典序更小的路径可以到达这个点，所以直接跳过即可
*  $vis2[y] = 0$ && $vis1[y] = 0$， 说明当前点 $y$ 没有被访问过，继续$dfs$
* $vis2[y] = 0$ && $vis1[y] = 1$，  **重点来了**， 因为$vis1[y]=1$, 说明形成了环，因此需要将环上的点以及环所能到达的点都赋成 $-1$ ,如果暴力去枚举环上的点并标记 $-1$， 其实比较难写。这里我记录环的个数$(tmp)$以及环的起始点， 在 $dfs$ 的过程中，如果 $tmp>0$ ，那么说明当前点是在环上，在枚举出边的时候直接讲答案赋成 $-1$，反之就直接更新答案 

##### 代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3001, M = 4e5 + 7;
int n, m, k;
int ans[M] = {};
vector < pair <int , int> > q[N][N];
vector < int > a[N];
int qq[N], top = 0;
int tmp = 0;
bool vis1[N], vis2[N] = {};
int root = 0;
int cnt[N] = {};

void dfs(int x) {
	qq[++ top] = x;
	if (!tmp) {
		for (int i = 0; i < q[root][x].size(); i ++) {
			int kk = q[root][x][i].first;
			int id = q[root][x][i].second;
			if (kk <= top) ans[id] = qq[kk];
		}
	}
	for (int i = 0; i < a[x].size(); i ++) {
		int y = a[x][i];
		if (vis2[y]) continue;
		if (!vis1[y]) vis1[y] = 1, dfs(y);
			else ++ tmp, cnt[y] ++;
	}
	-- top;
	tmp -= cnt[x]; //接下来回溯，因此不在以x为起始的环上了，所以要减去cnt[x]
	cnt[x] = 0;
	vis2[x] = 1;
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= m; i ++) {
		int x, y;
		scanf("%d %d", &x, &y);
		a[x].push_back(y);
	}
	for (int i = 1; i <= n; i ++) sort(a[i].begin(), a[i].end());
	for (int i = 1; i <= k; i ++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		q[x][y].push_back(pair <int, int>{z, i});
		ans[i] = -1;
	}
	for (int i = 1; i <= n; i ++) {
		tmp = 0, root = i, top = 0;
		for (int j = 1; j <= n; j ++) vis1[j] = vis2[j] = 0;
		dfs(i);
	}
	for (int i = 1; i <= k; i ++) printf("%d\n", ans[i]);
	return 0;
}
```

 

---

## 作者：_maojun_ (赞：3)

一种需要卡空间的在线做法。

---

首先应该可以想到一个 $O(n^2(n+m))$ 的做法：枚举起点，按照优先级走出边，每次拷贝当前点到起点的路径，这样询问可以做到 $O(1)$。

询问 $O(1)$ 没有什么用，但是你发现每次拷贝太蠢了，于是在枚举起点的基础上倍增。$fa[s][i][k]$ 表示从 $s$ 到 $i$ 的路径上的第 $2^k$ 个点，询问的时候进行 $O(\log n)$ 次跳跃，这样复杂度是 $O((n(n+m)+q)\log n)$。

不幸的是，因为 $\left\lceil\log n\right\rceil=12$，你的 `int fa[N][N][K]` 的空间开销是 $3005\times3005\times12\times 4\text B\approx413\text{MB}$，寄。

但是你发现这个数组里面存的值不超过 $3000$，于是直接把 `int` 换成 `short`，空间除二，就过了。

```cpp
#define eb emplace_back

const int MAXN=3e3+5;
int n,m;vector<int>G[MAXN];

bool vis[MAXN],ins[MAXN];int top=0,stk[MAXN];
short s,dis[MAXN][MAXN],fa[MAXN][MAXN][13];// short
int low;inline void ckmn(int&x,int y){(dis[s][x]>dis[s][y])&&(x=y);}
void chk(int u){
	vis[u]=true;for(int v:G[u])
		if(!vis[v])chk(v);
		else if(ins[v])ckmn(low,v);					// low 记录环中离 s 最近的点
}
void dfs(int u){
	stk[++top]=u;ins[u]=true;dis[s][u]=top;
	for(int k=0;(1<<k)<top;k++)fa[s][u][k]=stk[1+(1<<k)];
	vis[u]=true;
	for(int v:G[u]){
		if(low&&!vis[v]){chk(v);continue;}		// 有比 v 更优先的环就全部打标记
		if(!vis[v]){dfs(v);(low==v)&&(low=0);}	// 离开 v 之后要在 low 中清除 v
		else if(ins[v])ckmn(low,v);
	}top--;ins[u]=false;
}
int main(){
	int q;scanf("%d%d%d",&n,&m,&q);
	for(int i=1,u,v;i<=m;i++){scanf("%d%d",&u,&v);G[u].eb(v);}
	for(int i=1;i<=n;i++)sort(G[i].begin(),G[i].end());
	for(int i=1;i<=n;i++){memset(vis,false,n+1);dis[s=i][low=0]=n+1;dfs(i);}
	for(int s,t,k;q--;){
		scanf("%d%d%d",&s,&t,&k);
		if(dis[s][t]<k){printf("-1\n");continue;}
		k--;for(int i=0;k>>i;i++)if(k>>i&1)
			s=fa[s][t][i];
		printf("%d\n",s);
	}
	return 0;
}
```

---

## 作者：Arghariza (赞：1)

首先这个问题肯定不弱于传递闭包，所以先 $O(\frac{n^3}{\omega})/O(n(n+m))$ 做一遍传递闭包，求出 $i$ 能到的点的集合。

然后对询问离线，同时处理所有 $t$ 相同的询问。其实可以在线但是会被卡空间。

显然如果 $s$ 到不了 $t$ 就寄了，否则处理出每个点 $s$ 走最小路径到 $t$ 的第一步走向的点，即若 $to_{s,t}=w$，那么最小路径为 $s\to w\to \cdots \to t$。如果 $s$ 走不到 $t$ 那么硬点 $to_{s,t}=0$，同时硬点 $to_{t,t}=0$。我们发现对于每个 $to_{i,t}=0(i\neq t)$，$i$ 都是走不到 $t$ 的，所以也不存在 $to_{j,t}=i$。

我们将 $s$ 向 $to_{s,t}$ 连边，由于没有出边的点一定没有入边，$to_{t,t}=0$，这个图就变成了 一堆孤立点 加 一堆不包括 $t$ 的内向基环树 加 一棵以 $t$ 为根的内向树。

对于一次询问，如果 $s$ 是孤立点或者基环树中的点就无解，分别对应走不到/走到环的情况，否则在内向树上求 $k-1$ 级祖先即可。单次询问复杂度 $O(\log n)$。

```cpp
// Problem: Cities Excursions
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF864F
// Memory Limit: 250 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <bits/stdc++.h>
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#define eb emplace_back
#define pb pop_back
#define mt make_tuple
#define mp make_pair
#define fi first
#define se second

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef tuple<int, int, int> tu;
bool Mbe;

namespace vbzIO {
    char ibuf[(1 << 20) + 1], *iS, *iT;
    #if ONLINE_JUDGE
    #define gh() (iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, (1 << 20) + 1, stdin), (iS == iT ? EOF : *iS++) : *iS++)
    #else
    #define gh() getchar()
    #endif
    #define pc putchar
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

const int N = 3e3 + 300;
const int M = 4e5 + 400;

int n, m, q, op, to[N][N], ans[M];
bitset<N> e[N];
vector<int> g[N];

struct Q {
	int u, k, id; 
	Q () { }
	Q (int _u, int _k, int _id) :
		u(_u), k(_k), id(_id) { }
};

vector<Q> qr[N];

struct Tree {
	vector<int> g[N];
	int dfc, rt, fa[N], sz[N], son[N], id[N], rid[N], top[N];
	void clear() {
		for (int i = 1; i <= n; i++)
			fa[i] = sz[i] = son[i] = id[i] = rid[i] = top[i] = 0, g[i].clear();
		dfc = rt = 0;
	}
	void dfs1(int u, int fat) {
		fa[u] = fat, sz[u] = 1;
		for (int v : g[u]) {
			if (v == fat) continue;
			dfs1(v, u), sz[u] += sz[v];
			if (sz[v] > sz[son[u]]) son[u] = v;
		}
	}
	void dfs2(int u, int pr) {
		top[u] = pr, rid[id[u] = ++dfc] = u;
		if (son[u]) dfs2(son[u], pr);
		for (int v : g[u]) {
			if (v == fa[u] || v == son[u]) continue;
			dfs2(v, v);
		}
	}
	int kth(int u, int k) {
		while (id[u] && k >= id[u] - id[top[u]] + 1) 
			k -= id[u] - id[top[u]] + 1, u = fa[top[u]];
		if (k >= id[u]) return -1;
		return rid[id[u] - k];
	}
} T;

void solve() {
	n = rd(), m = rd(), q = rd();
	for (int i = 1, u, v; i <= m; i++) 
		u = rd(), v = rd(), e[u].set(v), g[u].eb(v);
	for (int i = 1; i <= n; i++) e[i].set(i);
	for (int i = 1; i <= n; i++) sort(g[i].begin(), g[i].end());
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (e[j].test(i)) e[j] |= e[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			for (int k : g[i]) {
				if (e[k].test(j)) {
					to[i][j] = k;
					break;
				}
			}
		}
	}
	for (int i = 1, s, t, k; i <= q; i++) 
		s = rd(), t = rd(), k = rd(), qr[t].eb(Q(s, k, i));
	for (int i = 1; i <= n; i++) {
		T.clear();
		for (int j = 1; j <= n; j++)
			if (to[j][i]) T.g[to[j][i]].eb(j);
		T.rt = i, T.dfs1(i, 0), T.dfs2(i, i);
		for (auto [s, k, id] : qr[i]) {
			if (!T.id[s]) ans[id] = -1;
			else {
				int u = T.kth(s, k - 1);
				if (u == -1) ans[id] = -1;
				else ans[id] = u;
			}
		}
	}
	for (int i = 1; i <= q; i++) cout << ans[i] << '\n';
}

bool Med;
int main() {
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << (&Mbe - &Med) / 1048576.0 << " MB\n";
	#ifdef FILE
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	int T = 1;
	// cin >> T;
	while (T--) solve();
	cerr << (int)(1e3 * clock() / CLOCKS_PER_SEC) << " ms\n";
	return 0;
}
```

---

## 作者：Saliеri (赞：1)

我们首先假设终点确定为 $t$。

那么我们可以知道，如果 $s$ 可以到达 $t$，那么 $s$ 过后下一个点是固定的。

即，在字典序最小的 $s\rightarrow t$ 路径上 $s$ 的后继一定是 $s$ 可以到达的点中能到达 $t$ 的点中编号最小的点。

于是，我们如果将 $s$ 与 $s'$ 的后继连边，那么构成的图上 $t$ 没有出边，其他点均有一条出边。换言之，这张图是 **若干个环+一棵树**。

对于环中的点和与 $t $ 不连通的点，答案显然是 -1。否则，求答案等价于在**树上求 $k$ 级祖先**。

因为可以离线，在 DFS 的过程中维护一个栈即可 $O(1)$ 回答。

我们留下的问题是，没有求出两两点间的连通性，以及没有判断哪些点在环中。

- 其一，Tarjan 缩点 + DAG 上 DP，可以做到 $O(nm)$。或者你还可以在 DP 时采用 bitset 优化。

- 其二，用一个并查集维护即可。

于是，我们枚举 $t$，建图后离线回答询问即可做到 $O(nm+(n^2+q)\log n)$。$\log$ 是给并查集的，并查集常数很小，所以可过。

___

值得一提的是，这份代码一打完就过了，可喜可贺。

```cpp
#include <queue>
#include <cstdio>
#include <bitset>
#include <vector>
const int maxn = 3e3+5,maxq = 4e5+5;
inline int min(int a,int b){return a<b?a:b;}
int n,m,q,ans[maxq];
struct Query{int s,k,id;};
struct Query2{~Query2(){};int k,id;};
std :: vector <Query> qry[maxn];
std :: vector <Query2> qry2[maxn];
std :: bitset <maxn> vis[maxn],ond[maxn];
std :: vector <int> G[maxn],DAG[maxn],SCC[maxn],T[maxn];
int dfn[maxn],low[maxn],b[maxn],inst[maxn],st[maxn],rd[maxn],top,tim,cnt;
void Tarjan(int u){
	dfn[u] = low[u] = ++tim,inst[u] = 1,st[++top] = u;
	for(int v:G[u]){
		if(!dfn[v])Tarjan(v),low[u] = min(low[u],low[v]);
		else if(inst[v])low[u] = min(low[u],dfn[v]);
	}
	if(low[u] == dfn[u]){
		int now;++cnt;ond[cnt][cnt] = 1;
		do{now = st[top--],b[now] = cnt,inst[now] = 0,SCC[cnt].push_back(now);}while(now^u);
	}
}
void getvis(){
	for(int i=1;i<=n;++i)if(!dfn[i])Tarjan(i);
	for(int u=1;u<=n;++u)
		for(int v:G[u])
			if(b[u] != b[v])DAG[b[v]].push_back(b[u]),++rd[b[u]];
	std :: queue <int> q;
	for(int i=1;i<=cnt;++i)if(!rd[i])q.push(i);
	while(!q.empty()){
		int u = q.front();q.pop();
		for(int v:DAG[u])--rd[v],ond[v] |= ond[u],(!rd[v]?q.push(v):void());
	}
	for(int i=1;i<=n;++i)
		for(int j=1;j<=cnt;++j)
			if(ond[b[i]][j])
				for(int v:SCC[j])vis[i][v] = 1;
}
struct DSU{
	int fa[maxn];
	void clr(){for(int i=1;i<=n;++i)fa[i] = i;}
	int getfa(int x){return fa[x] == x ? x : fa[x] = getfa(fa[x]);}
	void merge(int x,int y){
		int fx = getfa(x),fy = getfa(y);
		if(fx != fy)fa[fx] = fy;
	}
}dsu;
void getans(int u){
	st[++top] = u;
	for(auto Q:qry2[u])ans[Q.id] = Q.k<=top?st[top-Q.k+1]:-1;
	for(int v:T[u])getans(v);--top;
}
int main(){
	scanf("%d %d %d",&n,&m,&q);
	for(int i=1,x,y;i<=m;++i)
		scanf("%d %d",&x,&y),G[x].push_back(y);
	getvis();
	for(int i=1,s,t,k;i<=q;++i)
		scanf("%d %d %d",&s,&t,&k),qry[t].push_back((Query){s,k,i});
	for(int t=1;t<=n;++t){
		dsu.clr();
		for(int i=1;i<=n;++i)T[i].clear(),qry2[i].clear();
		for(int u=1;u<=n;++u)
			if(u != t){
				if(!vis[u][t])continue;
				int minid = 0x3f3f3f3f;
				for(int v:G[u])if(vis[v][t])minid = min(minid,v);
				T[minid].push_back(u),dsu.merge(minid,u);
			}
		for(auto Q:qry[t]){
			if(!vis[Q.s][t] || dsu.getfa(Q.s) != dsu.getfa(t))ans[Q.id] = -1;
			else qry2[Q.s].push_back((Query2){Q.k,Q.id});
		}
		getans(t);
	}
	for(int i=1;i<=q;++i)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：donaldqian (赞：1)

我们发现 $q$ 很大而 $n,m$ 很小，考虑离线。枚举终点 $u$，建反图找出能到达 $u$ 的所有点（不考虑字典序），令这个集合为 $S$。显然，$\forall v\isin S$，$v\to u$ 的字典序最小路径中 $v$ 的后继节点是唯一确定的（其实就是原图里，$v$ 的临点中，能到达 $u$ 且编号最小的点）。

我们不妨设这个后继节点是 $x$。建一个新图，从 $x$ 向 $v$ 连边，则该图中 $u$ 所在的连通块是一棵外向树。再跑一遍 dfs，用一个栈存路径，求答案即可。[代码](https://codeforces.com/contest/864/submission/296143293)。

---

