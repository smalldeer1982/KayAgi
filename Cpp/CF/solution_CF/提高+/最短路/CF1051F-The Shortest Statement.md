# The Shortest Statement

## 题目描述

给你一个有 $n$ 个点，$m$ 条边的无向连通图。有 $q$ 次询问，第 $i$ 次询问回答从 $u_i$ 到 $v_i$ 的最短路的长度。

## 样例 #1

### 输入

```
3 3
1 2 3
2 3 1
3 1 5
3
1 2
1 3
2 3
```

### 输出

```
3
4
1
```

## 样例 #2

### 输入

```
8 13
1 2 4
2 3 6
3 4 1
4 5 12
5 6 3
6 7 8
7 8 7
1 4 1
1 8 3
2 6 9
2 7 1
4 6 3
6 8 2
8
1 5
1 7
2 3
2 8
3 7
3 4
6 8
7 8
```

### 输出

```
7
5
6
7
7
1
2
7
```

# 题解

## 作者：GaryH (赞：17)

# CF1051F 题解

分享一个来自 ```sjx``` 巨佬的线性做法，如果有什么错误之处敬请指出。

题意就不说了，我直接讲做法。

首先建出原图的最小生成树，那么余下的非树边只有至多 $21$ 条，

我们将所有非树边的左右端点记为关键点，并将这些关键点两两间的 ```LCA``` 也标记成关键点。

我们发现，由 ```LCA``` 产生的新关键点小于关键点数，因为：

我们将原关键点按 ```dfs``` 序升序排序，再将所有排序后相邻的关键点对的 `LCA` 标记成关键点，

容易证明，这样标记后，任意两个关键点的 `LCA` 都已经是关键点了。

这些关键点只有不超过 $83$ 个，我们可以预处理原图中所有关键点间任意两个的最短路，

具体来说，我们建一个只与关键点有关的新图 $G'$，

对任意两个关键点 $u,v$ ，我们往 $G'$ 中加一条 $u\rightarrow v$ 的边，权为两点在生成在树上的距离。

然后，对于所有连接两个关键点的非树边，我们将这些边也加进 $G'$ 中。

我们在这张图中计算出任意两点间的最短路，

就等价于计算出了原图中任意两个关键点间的最短路。

为方便接下来的叙述，我们称关键点为黑点，非关键点为白点。

此时，树上的黑点将所有白点划分成了若干个连通块，

那么对于一组询问 $(u,v)$，

我们只需要找到所有与 $u$ 所在的连通块接壤的黑点 $p_1,p_2,\cdots,p_i$，

再找到所有与 $v$ 所在的连通块接壤的黑点 $q_1,q_2,\cdots,q_j$，那么这组询问的答案就是：

$ans=\min\limits_{x\in[1,i],y\in[1,j]}dist(p_x,q_y)$，其中 $dist(u,v)$ 代表关键点对 $u,v$ 间的最短路。

当然，如果点 $u$ 或点 $v$ 本身就是黑点的话，与 $u$ 或 $v$ 接壤的黑点就只有自己。

看上去现在的复杂度仍然不低，但实际上我们可以证明 $i,j\in[0,2]$ 以保证复杂度。

我们需要证明的，实际上是：

对于任意一个白点构成的连通块 $T$，与其接壤的黑点不超过两个。

那么，我们在这个连通块中随意挑一个点 $s$，沿着 $s$ 的祖先链往上走，可以走到至多一个黑点；

同时，点 $s$ 的子树中不可能存在大于等于两个黑点，否则这个连通块中必然存在至少一个黑点，

因为两个黑点的 ```LCA``` 也是黑点，这与连通块中全是白点的条件矛盾，

故与一个连通块接壤的黑点不超过两个。

那么，对于每组询问，我们暴力的计算 $ans$，最后将 $ans$ 和 $(u,v)$ 在树上的距离取 $\min$ 即可。

我们用树剖查询 `LCA`，用你知道的任意一种快速求最短路方式求关键点间的最短路，

而求图中的最小生成树，

我们可以~~用基数排序或者 `tarjan` 发明的随机数据期望线性最小生成树算法~~发现，

实际上我们可以用图中的任意一棵生成树代替，都不会影响答案的正确性。

而求图中的任意一棵生成树，我们直接 `dfs` 即可。

这样复杂度就是 $O((m-n)^2\log(m-n)+n+m)$ 或 $O((m-n)^3+n+m)$，

取决于你的全源最短路使用的是立方级别的算法还是平方带 $\log$ 级别的算法。

当然，在 $m-n$ 很小时，这个算法的表现是线性的。

~~所以理论上是不是可以出一道边数减点数为 `300`，询问数为 `1e7` 的的加强版？~~

代码可以在 `CF` 上看 `sjx` 的，`ta` 的用户名叫 `songjiaxing`，以下是代码链接。

[代码链接](https://codeforces.com/contest/1051/submission/140159293)

---

## 作者：81179332_ (赞：16)

观察到 $m-n\le 20$，所以我们先搞出来一棵生成树，然后将非树边的两个端点标记为特殊点，而这些特殊点的个数不超过 $42$。

则 $u$ 到 $v$ 的最短路分两种情况，不经过非树边和经过非树边。

对于不经过非树边的情况，直接用 `lca` 求两点之间的距离即可。

对于经过非树边的情况，我们枚举 $u$ 到 $v$ 的最短路要经过哪个特殊点，则对于特殊点 $k$，则$dis_{u,v}=\min\limits_{k=1}^{2\times(m-n+1)}dis_{u,k}+dis_{k,v}$

那么我们只需要预处理出每个特殊点到其他点的最短距离即可，用 `Dijkstra` 实现。

最后，对两种情况取个 `min` 即可。

~~也就我会写得如此过度封装。。~~

```cpp
#include<cstdio>
#include<algorithm>
#include<cctype>
#include<cstring>
#include<queue>
#include<vector>

using namespace std;

#define INF 1000000000000000000ll
#define pprint(x) print(x),putchar(' ')
#define fprint(x) print(x),putchar('\n')

//#define getchar() (SS == TT && (TT = (SS = BB) + fread(BB,1,1 << 15,stdin),TT == SS) ? EOF : *SS++)
char BB[1 << 15],*SS = BB,*TT = BB;
inline long long read()
{
	long long x = 0;int f = 1;
	char ch = getchar();
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-')
			f = -1;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	return x * f;
}
void print(long long x)
{
	if(x < 0)
		putchar('-'),x = -x;
	if(x > 9)
		print(x / 10);
	putchar(x % 10 + '0');
}

const int N = 100100;

struct edge
{
	int to,nxt,w;
};

#define EE; edge e[N << 1];\
	int head[N],cnt;\
	void add(int u,int v,int w)\
	{\
		e[++cnt].w = w,e[cnt].to = v,e[cnt].nxt = head[u];\
		head[u] = cnt;\
	}\
	void add_edge(int u,int v,int w)\
	{\
		add(u,v,w),add(v,u,w);\
	}

int n;

struct Tree
{
	EE;
	int f[N][20],dep[N];
	long long dis[N];
	void dfs(int u,int fa)
	{
		f[u][0] = fa,dep[u] = dep[fa] + 1;
		for(int i = head[u];i;i = e[i].nxt)
		{
			int v = e[i].to;
			if(v == fa)
				continue;
			dis[v] = dis[u] + e[i].w;
			dfs(v,u);
		}
	}
	void init()
	{
		dfs(1,0);
		for(int j = 1;j < 20;j++)
			for(int i = 1;i <= n;i++)
				f[i][j] = f[f[i][j - 1]][j - 1];
	}
	int LCA(int u,int v)
	{
		if(dep[u] < dep[v])
			swap(u,v);
		int h = dep[u] - dep[v];
		for(int i = 19;~i;i--) if(h & (1 << i)) u = f[u][i];
		if(u == v) return u;
		for(int i = 19;~i;i--) if(f[u][i] ^ f[v][i]) u = f[u][i],v = f[v][i];
		return f[u][0];
	}
	long long Dis(int u,int v){ return dis[u] + dis[v] - 2 * dis[LCA(u,v)]; }
}T;

bool book[N];
vector<int> s;

struct Graph
{
	EE;
	vector<long long> dis[N];
	bool vis[N];
	priority_queue<pair<long long,int> > q;
	void Dij(int S)
	{
		vector<long long> &d = dis[S];
		memset(vis,0,sizeof(vis));
		d.resize(n + 1);
		for(int i = 1;i <= n;i++)
			d[i] = INF;
		d[S] = 0,q.push(make_pair(0,S));
		while(!q.empty())
		{
			pair<long long,int> x = q.top();q.pop();
			int u = x.second;
			if(vis[u])
				continue;
			vis[u] = 1;
			for(int i = head[u];i;i = e[i].nxt)
			{
				int v = e[i].to;
				if(d[u] + e[i].w < d[v])
					d[v] = d[u] + e[i].w,q.push(make_pair(-d[v],v));
			}
		}
	}
	void init()
	{
		for(auto i:s)
			Dij(i);
	}
}G;

int fa[N];
int getf(int u){ return fa[u] == u ? u : fa[u] = getf(fa[u]); }
void merge(int u,int v){ fa[getf(u)] = fa[getf(v)]; }

void init()
{
	n = read();
	int m = read();
	for(int i = 1;i <= n;i++)
		fa[i] = i;
	for(int i = 1;i <= m;i++)
	{
		int u = read(),v = read(),w = read();
		G.add_edge(u,v,w);
		if(getf(u) != getf(v))
			merge(u,v),T.add_edge(u,v,w);
		else
		{
			if(!book[u]) s.push_back(u);
			if(!book[v]) s.push_back(v);
			book[u] = book[v] = 1;
		}
	}
	T.init(),G.init();
}

int main()
{
	init();
	int q = read();
	while(q--)
	{
		int u = read(),v = read();
		long long ans = T.Dis(u,v);
		for(int i:s)
			ans = min(ans,G.dis[i][u] + G.dis[i][v]);
		fprint(ans);
	}
	return 0;
}
```

---

## 作者：tommymio (赞：5)

注意到 $m-n\leq 20$。所以事实上题目给出的图 $G$ 是一棵生成树 $T$ 加上 $m-n+1$ 条边。

在这种图上求最短路，包括两个部分，全在 $T$ 上的最短路和经过一些非树边的最短路。经过非树边的最短路，可以暴力求出，因为只会有不超过 $2(m-n+1)$ 个点，这部分的时间复杂度为 $O(2(m-n+1) \log n)$。全在 $T$ 上的最短路，就是树上两点间距离，因为树上两点间有且今夜一条简单路径，这部分的时间复杂度为 $O(n+n \log n)$，其中 $O(n \log n)$ 为倍增求 $\text{lca}$ 的时间复杂度。

那么最终任意两点 $x,y$ 的最短路为树上距离和非树边最短路的值取 $\max$。非树边最短路 $dis(x,y)=\min_{i\in S}\{dis(x,i)+dis(i,y)\}$，其中 $S$ 为 所有非树边的两个顶点构成的点集。无向图上 $dis(i,y)=dis(y,i)$，所以 $dis(x,y)=\min_{i\in S}\{dis(i,x)+dis(i,y)\}$。那么预处理 $S$ 中的每个点到其他点的最短路，使用 $\text{dijistra}$ 实现即可。

总时间复杂度为 $O(2(m-n+1) \log n+n \log n)$。

```cpp
#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
typedef long long ll;
const ll inf=1e14;
int cnt=0;
struct edge {int x,y,w;} e[100105]; 
std::vector<int> vec; 
std::vector<int> v[100005],val[100005];
ll dis[45][100005],sum[100005];
int fa[100005],dep[100005],vis[100005],h[100005],to[200005],ver[200005],w[200005],f[100005][25]; 
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline void add(int x,int y,int z) {to[++cnt]=y;ver[cnt]=h[x];w[cnt]=z;h[x]=cnt;}
inline ll min(const ll &x,const ll &y) {return x<y? x:y;}
inline int find(int x) {return x==fa[x]? x:fa[x]=find(fa[x]);}
inline void swap(int &x,int &y) {int tmp=y;y=x;x=tmp;}
inline bool cmp(const edge &x,const edge &y) {return x.w<y.w;}
inline void prework(int x) {
	for(register int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1];
	for(register int i=h[x];i;i=ver[i]) {int y=to[i]; if(y==f[x][0]) continue; f[y][0]=x; sum[y]=sum[x]+w[i]; dep[y]=dep[x]+1; prework(y);}
}
inline int LCA(int x,int y) {
	if(dep[x]<dep[y]) swap(x,y);
	for(register int i=20;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i]; if(x==y) return x;
	for(register int i=20;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i]; return f[x][0];
}
inline void dijistra(int n,int id) {
	for(register int i=1;i<=n;++i) vis[i]=0,dis[id][i]=inf;
	std::priority_queue<std::pair<ll,int> > Q;
	dis[id][vec[id]]=0ll; Q.push(std::make_pair(0,vec[id]));
	while(Q.size()) {
		int x=Q.top().second; Q.pop();
		if(vis[x]) continue; vis[x]=1;
		for(register int i=0;i<v[x].size();++i) {int y=v[x][i]; if(dis[id][y]>dis[id][x]+val[x][i]) {dis[id][y]=dis[id][x]+val[x][i]; Q.push(std::make_pair(-dis[id][y],y));}}
	}
}
int main() {
	int n=read(),m=read();
	for(register int i=1;i<=n;++i) fa[i]=i;
	for(register int i=1;i<=m;++i) {
		e[i].x=read();e[i].y=read();e[i].w=read();
		v[e[i].x].push_back(e[i].y); val[e[i].x].push_back(e[i].w);
		v[e[i].y].push_back(e[i].x); val[e[i].y].push_back(e[i].w);
	}
	std::sort(e+1,e+1+m,cmp);
	for(register int i=1;i<=m;++i) {
		int fx=find(e[i].x),fy=find(e[i].y);
		if(fx!=fy) {add(e[i].x,e[i].y,e[i].w);add(e[i].y,e[i].x,e[i].w);fa[fx]=fy;}
		else {vec.push_back(e[i].x);vec.push_back(e[i].y);}
	}
	for(register int i=0;i<vec.size();++i) dijistra(n,i);
	int Q=read(); prework(1);
	while(Q--) {
		int s=read(),t=read(); ll res=sum[s]+sum[t]-2*sum[LCA(s,t)];
		for(register int i=0;i<vec.size();++i) res=min(res,dis[i][s]+dis[i][t]);
		printf("%lld\n",res);
	}
	return 0;
}
```



---

## 作者：feicx (赞：5)

## 不要被黑题的标签给吓倒了！这是唬你的。

注意条件$n-m \le 20$，这个很重要。这说明这是一个环套树，且在环上的点是不超过50的。

### 那么说，要求最短路是不是只要用最短路算法来处理处于环上的特殊点，其他的点按树上距离处理LCA即可。

这是本题思路最巧的地方。

这道题的大概思路就出来啦～～

------------

首先随便搞一棵生成树,那么会有一些边不在生成树上。这个可以在输入边的时候用并查集处理出来！

把这些边的端点标记为特殊点。

对于一个询问,如果最短路只经过生成树上的边,就可以通过LCA直接计算，否则就使用最短路算法处理出来，这样最坏的复杂度也就是$O(40 \times n \log n + q \log n)$。对于这个题目足够了！

------------
~~要始终记住NOI2018出题人说的话： **
关于SPFA，它死了。**~~

所以最短路我写的是堆优化的dijkstra算法哦。

------------

```cpp
#include<bits/stdc++.h>
using namespace std;

#define Pair pair<int, int>
#define MP(x, y) make_pair(x, y)
#define fi first
#define se second
#define LL long long

const int MAXN = 2 * 1e5 + 10;

inline int read() {
    char c = getchar(); int x = 0, f = 1;
    while(c < '0' || c > '9') {if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

int N, M, Q, head[MAXN], num = 0, vis[MAXN], fa[MAXN][21], dep[MAXN], happen[MAXN];
LL dis[50][MAXN], Tdis[MAXN];
vector<int> p;

struct Edge {
    LL u, v, w, f, nxt;
}E[MAXN];

inline void AddEdge(int x, int y, int z) {
    E[num] = (Edge) {x, y, z, 0, head[x]};
    head[x] = num++;
}

void dfs(int x, int _fa) {
    vis[x] = 1; dep[x] = dep[_fa] + 1;
    for(int i = head[x]; ~i; i = E[i].nxt) {
        int to = E[i].v;
        if(vis[to]) continue;
        E[i].f = E[i ^ 1].f = 1;
        Tdis[to] = Tdis[x] + (LL)E[i].w;
        fa[to][0] = x;
        dfs(to, x);
    }
}

void Dij(int x, int id) {
    memset(dis[id], 0x7f, sizeof(dis[id])); dis[id][x] = 0;
    memset(vis, 0, sizeof(vis));
    priority_queue<Pair> q; q.push(MP(0, x));
    while(!q.empty()) {
        int p = q.top().se; q.pop();
        if(vis[p]) continue;
        for(int i = head[p]; ~i; i = E[i].nxt) {
            int to = E[i].v;
            if(dis[id][to] > dis[id][p] + E[i].w && (!vis[to]))
                dis[id][to] = dis[id][p] + E[i].w, q.push(MP(-dis[id][to], to));
        }
    }
}

void Pre() {
    for(int j = 1; j <= 20; j++)
        for(int i = 1; i <= N; i++)
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 20; i >= 0; i--)
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    if(x == y) return x;
    for(int i = 20; i >= 0; i--)
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main(){
    memset(head, -1, sizeof(head));
    N = read(); M = read();
    for(int i = 1; i <= M; i++) {
        int x = read(), y = read(), z = read();
        AddEdge(x, y, z);
        AddEdge(y, x, z);
    }
    dfs(1, 0);
    for(int i = 0; i < num; i++)
        if(!E[i].f) {
            if(!happen[E[i].u]) p.push_back(E[i].u), happen[E[i].u] = 1;
            if(!happen[E[i].v]) p.push_back(E[i].v), happen[E[i].v] = 1;
        }

    for(int i = 0; i < p.size(); i++)
        Dij(p[i], i);
    Pre();
    int Q = read();
    while(Q--) {
        int x = read(), y = read();
        LL ans = Tdis[x] + Tdis[y] - 2 * Tdis[lca(x, y)];
        for(int i = 0; i < p.size(); i++)
            ans = min(ans, dis[i][x] + dis[i][y]);
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：Nero_Claudius (赞：4)

这道题思路比较有意思，第一次做完全没想到点子上。。。

------------

看到题目第一反应是一道最短路裸题，但是数据范围1e5说明完全不可能。

这个时候可以观察到题目给出了一个很有意思的条件，就是说边最多比点多20。

这有什么用呢？

那么我们大胆猜想，可否将整个图划分为21条边（连接最多42个点）和一颗树？（极限情况）

如果这样的话，对于任意的两个节点uv，它们之间的最短路只有两种情况：

1. 这两个点都在树上。所以说最短路必然是u->lca(u,v)->v。

2. 不是上面那种情况。这个时候肯定会有连到外面那21个边。我们暴力枚举一下就可以了。

到这里思路就完全出来了，我们先把不属于树的点挑出来，对每一个都跑一下最短路。

然后对于每一组询问判断一下属于哪一种情况就可以了。

------------

AC代码如下：

`37657ms 67712kb`

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
using namespace std;
namespace StandardIO{
	template<typename T>inline void read(T &x){
		x=0;T f=1;char c=getchar();
		for(;c<'0'||c>'9';c=getchar())if(c=='-')f=-1;
		for(;c>='0'&&c<='9';c=getchar())x=x*10+c-'0';
		x*=f;
	}
	template<typename T>inline void write(T x){
		if(x<0)putchar('-'),x*=-1;
		if(x>=10)write(x/10);
		putchar(x%10+'0');
	}
}
using namespace StandardIO;
namespace Solve{
	#define int long long
	const int N=100100;
	const int INF=2147483647;
	int n,m,p;
	int cnt;
	int head[N];
	struct node{
		int to,val,next;
	}edge[N<<1];
	template<typename T>inline void add(T a,T b,T c){
		edge[++cnt].to=b,edge[cnt].val=c,edge[cnt].next=head[a],head[a]=cnt;
	}
	struct qnode{
		int key,val;
		bool operator < (qnode x)const{
			return val>x.val;
		}
	};
	int top;
	int vis[N],fa[N][23],dist[N],dep[N],q[N];
	int dis[50][N];
	inline void dfs(int now,int father){
		vis[now]=1,fa[now][0]=father;
		for(register int i=head[now];i;i=edge[i].next){
			int to=edge[i].to;
			if(to==father)continue;
			if(vis[to])q[++top]=now,q[++top]=to;
			else{
				dep[to]=dep[now]+1,dist[to]=dist[now]+edge[i].val;
				dfs(to,now);
			}
		}
	}
	template<typename T>inline T lca(T x,T y){
		if(dep[x]<dep[y])swap(x,y);
		for(register int i=19;i>=0;--i){
			if(dep[fa[x][i]]>=dep[y])x=fa[x][i];
		}
		if(x==y)return x;
		for(register int i=19;i>=0;--i){
			if(fa[x][i]!=fa[y][i]){
				x=fa[x][i],y=fa[y][i];
			}
		}
		return fa[x][0];
	}
	inline void dijkstra(int now){
		memset(dis[now],63,sizeof(dis[now]));
		memset(vis,0,sizeof(vis));
		priority_queue<qnode>Q;
		dis[now][q[now]]=0;
		Q.push((qnode){q[now],0});
		while(!Q.empty()){
			int tmp=Q.top().key;Q.pop();
			if(vis[tmp])continue;
			vis[tmp]=1;
			for(register int i=head[tmp];i;i=edge[i].next){
				int to=edge[i].to;
				if(!vis[to]&&dis[now][tmp]+edge[i].val<dis[now][to]){
					dis[now][to]=dis[now][tmp]+edge[i].val;
					Q.push((qnode){to,dis[now][to]});
				}
			}
		}
	}
	inline void solve(){
		read(n),read(m);
		for(register int i=1;i<=m;++i){
			int a,b,c;
			read(a),read(b),read(c);
			add(a,b,c),add(b,a,c);
		}
		dep[1]=1,dfs(1,0);
		for(register int j=1;j<=19;++j){
			for(register int i=1;i<=n;++i){
				fa[i][j]=fa[fa[i][j-1]][j-1];
			}
		}
		sort(q+1,q+top+1);top=unique(q+1,q+top+1)-q-1;
		for(register int i=1;i<=top;++i)dijkstra(i);
		read(p);
		while(p--){
			int x,y;
			read(x),read(y);
			int ans=dist[x]+dist[y]-2*dist[lca(x,y)];
			for(register int i=1;i<=top;++i)ans=min(ans,dis[i][x]+dis[i][y]);
			write(ans),putchar('\n');
		}
	}
}
using namespace Solve;
#undef int
int main(){
	solve();
}

```

---

## 作者：浅夜_MISAKI (赞：3)

蒟蒻的第一道黑题居然是图论23333（其实这道题根本没有黑题难度）
这道题时限4000ms但是每次询问跑一次最短路显然是不行的

注意m-n<=20,这便是这道题的切入点，也就是说这是在一棵树上加了一些非树边，那么就好弄了，对于多出来的这21条边跑最短路，对于每组询问，lca路径的值与经过这21条边的路径取min即可
#### first
我们把树拎出来，kruskal即可；
#### second 
lca处理；
#### third 
最短路处理；
#### last 
询问；

（注意边权很大要开longlong！！！，被卡好久）
然后就A掉了一道黑题233333
最后放AC代码
```cpp
#include<bits/stdc++.h>
#define _ 0//卖萌专用
#define clear(a,val) memset(a,val,sizeof(a))
using namespace std;
typedef long long ll;
//////////////////////////////////////////////
const ll M=2*111111;//数组开大点
ll n,m,cnt=1,u,v,w,q,op;
ll ff[M],head[M],f[M][30],deep[M];
ll distan[M],dis[100][M];
struct apple{ll u,v,w;}ee[M];
struct orange{
	ll pos,dis;
	orange(ll pos,ll dis):pos(pos),dis(dis){}	
};
bool operator<(orange a,orange b){return a.dis>b.dis;}
struct lemon{
	ll from,nxt,to,val;
	lemon(ll from=0,ll nxt=0,ll to=0,ll val=0):from(from),nxt(nxt),to(to),val(val){}
}edge[M];
bool fl[M],vis[M],used[M];
////////////////////////////////////////
bool cmp(apple a,apple b){return a.w!=b.w?a.w<b.w:a.u>b.u;}
ll find(ll a){return ff[a]==a?a:ff[a]=find(ff[a]);}
inline void add(ll u,ll v,ll w)
	{edge[cnt]=lemon(u,head[u],v,w),head[u]=cnt++;}
void kruskal()
{
	ll fa,fb;
	for(ll i=1;i<=n;i++)ff[i]=i;
	sort(ee+1,ee+m+1,cmp);
	for(ll i=1;i<=m;i++)
	{
		fa=find(ee[i].u),fb=find(ee[i].v);
		if(fa!=fb)
			ff[fa]=fb,add(ee[i].u,ee[i].v,ee[i].w),add(ee[i].v,ee[i].u,ee[i].w);
		else fl[i]=1;
	}		
}
void init()
{
	clear(head,-1),clear(dis,0x7f);
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++)
		scanf("%lld%lld%lld",&ee[i].u,&ee[i].v,&ee[i].w);
}
priority_queue<orange>Q;
void dij(ll oop,ll st)
{
	clear(vis,0);
	dis[oop][st]=0;
	Q.push(orange(st,dis[oop][st]));
	while(!Q.empty())
	{
		orange now=Q.top();Q.pop();
		ll u=now.pos;
		if(vis[u])continue;vis[u]=1;
		for(ll i=head[u];i!=-1;i=edge[i].nxt)
		{
			ll to=edge[i].to;
			if(dis[oop][to]>dis[oop][u]+edge[i].val)
			{
				dis[oop][to]=dis[oop][u]+edge[i].val;
				Q.push(orange(to,dis[oop][to]));
			}
		}
	}
}
void Misaki()
{
	for(ll i=1;i<=m;i++)
		if(fl[i])
			add(ee[i].u,ee[i].v,ee[i].w),add(ee[i].v,ee[i].u,ee[i].w);
	for(ll i=1;i<=m;i++)
		if(fl[i])
		{
			dij(++op,ee[i].u);
			dij(++op,ee[i].v);
		}
}
ll lca(ll x,ll y)
{
	if(deep[x]<deep[y])swap(x,y);
	for(ll i=20;i>=0;i--)
		if(deep[f[x][i]]>=deep[y])
			x=f[x][i];
	if(x==y)return x;
	for(ll i=20;i>=0;i--)
		if(f[x][i]!=f[y][i])
			x=f[x][i],y=f[y][i];
	return f[x][0];
}
void ask()
{
	ll u,v,ans;
	scanf("%lld",&q);
	for(ll i=1;i<=q;i++)
	{
		scanf("%lld%lld",&u,&v);
		ll ances=lca(u,v);
		ans=distan[u]+distan[v]-2*distan[ances];//不要把ans赋成2147483647什么的，会被卡	
		for(ll i=1;i<=op;i++)
			ans=min(dis[i][u]+dis[i][v],ans);
		printf("%lld\n",ans);
	}
}
void dfs(ll now)
{
	used[now]=1;
	for(ll i=head[now];i!=-1;i=edge[i].nxt)
	{
		ll to=edge[i].to;
		if((!used[to]) && (to!=now))
			distan[to]=distan[now]+edge[i].val,
			deep[to]=deep[now]+1,
			f[to][0]=now,
			dfs(to);
	}
}
void ddfs()
{
	for(ll i=1;i<=n;i++)
		if(!used[i])
			deep[i]=1,dfs(i);
	for(ll j=1;j<=20;j++)
		for(ll i=1;i<=n;i++)
			f[i][j]=f[f[i][j-1]][j-1];
}
int main()
{
	init();	
	kruskal();//最小生成树
	ddfs();//lca部分
	Misaki();//最短路
	ask();//询问
	return ~~(0^_^0);//卖萌QAQ
}
```
此题不难，但是还是非常适合练码力，复习各种算法的，祝大家NOIPrp++


---

## 作者：Tweetuzki (赞：3)

原题的 undirected **connected** graph 中的 **connected** 是有加粗的，而且这道题的数据范围有特意给了 $m - n \le 20$，很自然地联想到与树有关系。

首先对于 $m = n - 1$ 的树，比较容易解决。可以考虑维护一个前缀和 $h$，$h_v$ 表示从根节点到 $v$ 号点的距离。前缀和可以在一次 DFS 中求出。之后，对于树上任意的两点 $u, v$，它们之间的最短路（下文简写为 $dis(u,v)$）就是 $u \rightarrow Lca(u, v) \rightarrow v$ 这条路（其中 $Lca(u, v)$ 表示 $u, v$ 两点的最近公共祖先，可以使用倍增 $\log n$ 求得）长度就是 $h_u - h_{Lca(u,v)} + h(v) - h_{Lca(u,v)}$。

试着将 $m$ 变大。当 $m = n$ 时，比起树来说多一条边，我们设这条边从连接 $x$ 和 $y$，长度为 $z$。那么 $u, v$ 之间的路就多了好多条路。通过~~直觉~~思考，不难发现，对 $dis(u,v)$ 有贡献的路只有 $u \rightarrow x \rightarrow y \rightarrow v$ 和 $u \rightarrow y \rightarrow x \rightarrow v$ 这两条路，长度分别为 $dis(u,x)+z+dis(v,y)$ 和 $dis(v,x)+z+dis(u,y)$。与原来的长度作比较，每次询问时取三者最大值即可。

再将 $m$ 扩大。这时候树上就出现了 $(m-n+1)$ 条非树边，这时候，$u$ 到 $v$ 的路就更多了。

考虑枚举这个路径经过的某一点 $i$，把这条路径拆分成 $u \rightarrow i$ 和 $i \rightarrow v$ 两部分。那这个 $i$ 会是什么值，才对更新 $dis(u,v)$ 有贡献呢？

贪心地想到，只需枚举这 $(m-n+1)$ 条非树边的最多 $2(m-n+1)$ 个端点。为什么是正确的呢？因为 $dis(u,v)$ 这条路，只有两种情况：

1. 没有经过任何非树边，只经过树边。 ----- 这种情况就是 $dis(u,v)$ 的初始值。
2. 经过某一条非树边。 ----- 那这条路径一定经过这条非树边的两个端点。

所以 $dis(u,v)$ 还可以通过 $dis(u,i)+dis(i,v)$ 来更新。注意到这是无向图，所以 $dis(u, i) = dis(i, u)$。于是这个更新的式子就变成了 $dis(i,u) + dis(i,v)$，是从 $i$ 点开始的单源最短路。

接着惊奇地发现有 $m - n \le 20$ 的限制，所以 $i$ 至多只有 $42$ 个。所以可以暴力对每个 $i$ 都跑一下最短路，就可以更新答案了。

时间复杂度 $O( (m - n) \cdot ( m + q ) \log n )$。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define mp(x, y) make_pair(x, y)
#define pb(x) push_back(x)
typedef long long llt;
typedef pair <llt, int> pli;

const int MaxN = 100000 + 5, MaxM = 100020 + 5;
const int MaxQ = 100000 + 5;
const int MaxLog = 20;
const int MaxD = 42 + 2;

struct edge {
    int to; llt val;
    edge( int _to, llt _val ) {
        to = _to;
        val = _val;
    }
};

int N, M, Q;
int U[MaxM], V[MaxM]; llt W[MaxM];
int par[MaxN];
int fa[MaxLog + 1][MaxN], depth[MaxN]; llt h[MaxN];
int Short_points[MaxD], cnt;
llt dis[MaxD][MaxN]; bool vis[MaxN];
vector <edge> G[MaxN];
vector <edge> Tr[MaxN];
priority_queue < pli, vector<pli>, greater<pli> > pq;

void init() {
    scanf( "%d %d", &N, &M );
    for ( int i = 1; i <= M; ++i ) {
        scanf( "%d %d %lld", &U[i], &V[i], &W[i] );
        G[ U[i] ].pb( edge( V[i], W[i] ) );
        G[ V[i] ].pb( edge( U[i], W[i] ) );
    }
}

int Find( int x ) {
    if ( x == par[x] ) return x;
    else return par[x] = Find( par[x] );
}

void Kruskal() { // Kruskal 算法生成树
    for ( int i = 1; i <= N; ++i ) par[i] = i;

    for ( int i = 1; i <= M; ++i ) {
        int u = U[i], v = V[i]; llt w = W[i];
        int p = Find( u ), q = Find( v );

        if ( p != q ) {
            Tr[u].pb( edge( v, w ) );
            Tr[v].pb( edge( u, w ) );
            par[p] = q;
        } else {
            Short_points[ ++cnt ] = u;
            Short_points[ ++cnt ] = v;
        }
    }
}

void dfs( int u ) { // DFS 处理树的信息
    for ( auto e : Tr[u] ) {
        int v = e.to; llt w = e.val;
        if ( v == fa[0][u] ) continue;

        depth[v] = depth[u] + 1;
        h[v] = h[u] + w;
        fa[0][v] = u;
        for ( int i = 1; ( 1 << i ) <= depth[v]; ++i )
            fa[i][v] = fa[ i - 1 ][ fa[ i - 1 ][v] ];
        dfs( v );
    }
}

void Dijkstra( llt d[], int s ) { // 对每个端点暴力求解最短路
    memset( d, 0x7F, sizeof d ); memset( vis, 0, sizeof vis );
    d[s] = 0; pq.push( mp( d[s], s ) );

    while ( !pq.empty() ) {
        int u = pq.top().second; pq.pop();
        if ( vis[u] ) continue; vis[u] = true;
        for ( auto e : G[u] ) {
            int v = e.to; llt w = e.val;
            if ( d[u] + w < d[v] ) {
                d[v] = d[u] + w;
                pq.push( mp( d[v], v ) );
            }
        }
    }
}

int getLca( int u, int v ) { // 倍增求 u, v 两点 LCA
    if ( depth[u] < depth[v] ) swap( u, v );
    int d = depth[u] - depth[v];
    for ( int i = MaxLog; i >= 0; --i )
        if ( d & ( 1 << i ) ) u = fa[i][u];
    if ( u == v ) return u;

    for ( int i = MaxLog; i >= 0; --i )
        if ( fa[i][u] != fa[i][v] )
            u = fa[i][u],
            v = fa[i][v];
    return fa[0][u];
}

void solve() {
    Kruskal();
    depth[1] = 1; dfs( 1 );
    memset( dis, 0x7F, sizeof dis );
    for ( int i = 1; i <= cnt; ++i ) Dijkstra( dis[i], Short_points[i] );

    scanf( "%d", &Q );
    for ( int q = 1; q <= Q; ++q ) {
        int u, v; scanf( "%d %d", &u, &v );
        llt ans = h[u] + h[v] - 2 * h[ getLca( u, v ) ];
        // 枚举端点，更新答案
        for ( int i = 1; i <= cnt; ++i )
            ans = min( ans, dis[i][u] + dis[i][v] );
        printf( "%lld\n", ans );
    }
}

int main() {
    init();
    solve();
    return 0;
}
```

---

## 作者：James_Brady (赞：2)

这道题~~毒瘤至极~~特别好

题意：

已知一个n点m边的无向图，q次询问，求任意两点的最短路

首先我们得明白，每次跑最短路铁定超时

但是，这里有一个特殊条件：**m-n<=20**，我们得好好利用

先跑kruskal建最小生成树，然后树上求最短路就很省时了

但是有个问题，建完树后那剩下20多条边怎么办呢？

这就没有捷径了，找出每条没用过的边，记录两边节点u，v，分别在原图跑最短路

这样，就得出他们到每个点的最短路p[u][i]，40多次总比n次好

对于每个查询，先树上跑最短路（用lca），再在每个先前记录的点上进行比较（因为最短路可能不在树上）

这样，dis(u,v)=min(tree_dis(u,v),p[i][u]+p[i][v]);

上代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define ll long long
using namespace std;
typedef pair<ll,int>pii;
priority_queue<pii,vector<pii>,greater<pii> >q;
int n,m,t,h[100010],p[100010][30],f[100010],k,k1,vis[100010],h1[100010];
int mp[100010],pos;
ll d[100010],dis[100010],dis1[110][100010];
struct node{
	int u;
	int v;
	ll w;
	bool used;//是否用过
}ee[400010];//存原来的边
struct ndde{
	int v;
	ll w;
	int nex;
}e[400010];//存最小生成树
struct ndoe{
	int v;
	ll w;
	int nex;
}eee[400010];//存原图
void add(int u,int v,ll w)
{
	e[++k].v=v;
	e[k].w=w;
	e[k].nex=h[u];
	h[u]=k;
}
void add1(int u,int v,ll w)
{
	eee[++k1].v=v;
	eee[k1].w=w;
	eee[k1].nex=h1[u];
	h1[u]=k1;
}
int find(int x)
{
	if(f[x]==x)
	return x;
	return f[x]=find(f[x]);
}
void kruskal()//最小生成树
{
	int cnt=0;
	for(int i=1;i<=n;i++)
	f[i]=i;
	for(int i=1;i<=m&&cnt<n-1;i++)
	{
		int fx=find(ee[i].u),fy=find(ee[i].v);
		if(f[fx]!=fy)
		{
			cnt++;
			ee[i].used=1;
			f[fx]=fy;
			add(ee[i].u,ee[i].v,ee[i].w);
			add(ee[i].v,ee[i].u,ee[i].w);
		}
	}
}
void dij(int st)//最短路
{
	while(!q.empty())
	q.pop();
	for(int i=1;i<=n;i++)
	{
		dis1[mp[st]][i]=1e17;
		vis[i]=0;
	}
	dis1[mp[st]][st]=0;
	q.push(make_pair(dis1[mp[st]][st],st));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
		continue;
		vis[u]=1;
		for(int i=h1[u];i;i=eee[i].nex)
		{
			int v=eee[i].v,w=eee[i].w;
			if(dis1[mp[st]][v]>dis1[mp[st]][u]+w)
			{
				dis1[mp[st]][v]=dis1[mp[st]][u]+w;
				q.push(make_pair(dis1[mp[st]][v],v));
			}
		}
	}
}
void dfs(int u,int fa)
{
	d[u]=d[fa]+1;
	p[u][0]=fa;
	for(int i=1;i<=20;i++)
	p[u][i]=p[p[u][i-1]][i-1];
	for(int i=h[u];i;i=e[i].nex)
	{
		int v=e[i].v;
		if(v==fa) continue;
		dis[v]=dis[u]+e[i].w;
		dfs(v,u);
	}
}
int lca(int u,int v)//lca模板
{
	if(d[u]>d[v])
	swap(u,v);
	for(int i=20;i>=0;i--)
	if(d[u]<=d[v]-(1<<i))
	v=p[v][i];
	if(u==v)
	return u;
	for(int i=20;i>=0;i--)
	{
		if(p[u][i]==p[v][i]) continue;
		u=p[u][i];
		v=p[v][i];
	}
	return p[u][0];
}
ll dist(int u,int v)
{
	return dis[u]+dis[v]-2*dis[lca(u,v)];//树上距离
}
ll dista(int u,int v)
{
	ll ans=dist(u,v);
	for(int i=1;i<=pos;i++)
	{
		ans=min(ans,dis1[i][u]+dis1[i][v]);
		ans=min(ans,dis1[i][u]+dis1[i][v]);
	}
	return ans;
}
bool cmp(node xx,node yy)
{
	return xx.w<yy.w;
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int a,b;
		ll c;
		scanf("%d%d%lld",&a,&b,&c);
		ee[i].u=a;
		ee[i].v=b;
		ee[i].w=c;
		add1(a,b,c);
		add1(b,a,c);
	}
	sort(ee+1,ee+m+1,cmp);
	kruskal();
	for(int i=1;i<=m;i++)
	if(!ee[i].used)
	{
		if(!mp[ee[i].u])
		mp[ee[i].u]=++pos;//因为u，v可能很大，1e5*1e5存不下，所以用一个数组mp映射
		if(!mp[ee[i].v])
		mp[ee[i].v]=++pos;
		dij(ee[i].u);
		dij(ee[i].v);
	}
	dfs(1,0);
	scanf("%d",&t);
	while(t--)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		printf("%lld\n",dista(a,b));
	}
	return 0;
}
```


---

## 作者：LlLlCc (赞：1)

看完题目，裸的全源最短路

一看数据规模：$1。。。10^5$，打扰了...

题目有一个有趣的性质：$M-N\leq 20$

也就是说就是在一棵树上加上不超过$20$条边，$Q(1\leq Q\leq 10^5)$次询问让你求两点间的最短路长度

这个东西如果在树中，那是一个非常经典的$LCA$问题

不妨设：

$dis_x:$点$x$到跟节点的距离

求距离$(x\rightarrow y)$，也就是求出$x,y$的$LCA$，答案就是$dis_x-dis_{LCA}+dis_y-dis_{LCA}$

所以我们可以在原图中找出一棵最小生成树（其实只要是棵树都行）

然后再将不在树上的边全部加进来，跑一遍最短路，看看在原树中的距离和加边后的距离哪个小即可。因为最多加$20$条边，所以最多跑$20$边最短路算法，保证了算法的复杂度

其实很容易发现，最坏的情况也只是在一棵树上加$20$条边，所以说是非常稀疏的图，跑$SPFA$要比跑堆优化的$dijkstra$快的多，$SPFA$接近线性

```
#include<bits/stdc++.h>
#define maxn 1000005
#define ll long long
using namespace std;
int n,m,q,fa[maxn][20],Fa[maxn],Dep[maxn],nxt[maxn],Id[5000005],Now,lnk[maxn],son[maxn],tot,x,y;
ll dis[maxn],heap[5000005],w[maxn];
bool vis[maxn];
struct lc{
	int x,y;
	ll z;
	bool flg;
    bool operator <(const lc b)const{return z<b.z;}
}e[maxn],Q[maxn];
inline int read(){
	int ret=0;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch<='9'&&ch>='0') ret=ret*10+ch-'0',ch=getchar();
	return ret;
}
inline void add(int x,int y,ll z){nxt[++tot]=lnk[x];lnk[x]=tot;son[tot]=y;w[tot]=z;}
inline int Getfa(int x){return Fa[x]==x? x:Fa[x]=Getfa(Fa[x]);}
inline void Dfs(int x){
	Dep[x]=Dep[fa[x][0]]+1;
	for (int i=1;i<20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=lnk[x];i;i=nxt[i])
	  if (son[i]!=fa[x][0]){
	  	fa[son[i]][0]=x;dis[son[i]]=dis[x]+w[i];
	    Dfs(son[i]);
	  }
}
inline int LCA(int x,int y){
	ll Now=0;
	if (Dep[x]<Dep[y]) swap(x,y);
	for (int i=19;i>=0;i--) if (Dep[fa[x][i]]>=Dep[y]) x=fa[x][i];
	if (x==y) return x;
	for (int i=19;i>=0;i--) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
inline void Swap(int x,int y){swap(heap[x],heap[y]);swap(Id[x],Id[y]);}
inline void Put(int id,ll x){heap[Now=++tot]=x;Id[tot]=id;while (Now>1&&heap[Now]<heap[Now>>1]) Swap(Now,Now>>1),Now>>=1;}
inline int Get(){
	int Mi=Id[1];Id[1]=Id[tot];heap[1]=heap[tot],tot--,Now=1;int Son=2;
	while (Son<=tot){
		if (Son<tot&&heap[Son+1]<heap[Son]) Son++;
		if (heap[Son]<heap[Now]) Swap(Now,Son),Now=Son,Son=Now<<1;
		else break;
	}
	return Mi;
}
inline void Dij(int S){
	for (int i=1;i<=n;i++) vis[i]=0,dis[i]=1e16;
	dis[S]=0;tot=0;Put(S,0);
	while (tot){
		int N=Get();if (vis[N]) continue;
	    vis[N]=1;
	    for (int i=lnk[N];i;i=nxt[i])
	      if (!vis[son[i]]&&dis[son[i]]>dis[N]+w[i]) dis[son[i]]=dis[N]+w[i],Put(son[i],dis[son[i]]);
	}
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++) Fa[i]=i;
	for (int i=1;i<=m;i++) e[i].x=read(),e[i].y=read(),e[i].z=read();
	sort(e+1,e+m+1);
	for (int i=1;i<=m;i++){
		int fx=Getfa(e[i].x),fy=Getfa(e[i].y);
		if (fx==fy){e[i].flg=1;continue;}
		add(e[i].x,e[i].y,e[i].z),add(e[i].y,e[i].x,e[i].z);
	    Fa[fx]=fy;
	}
	q=read();Dfs(1);
	for (int i=1;i<=q;i++){
		Q[i].x=read(),Q[i].y=read();
		int lca=LCA(Q[i].x,Q[i].y); 
		Q[i].z=dis[Q[i].x]+dis[Q[i].y]-(ll)2*dis[lca];
	}
	for (int i=1;i<=m;i++) if (e[i].flg) add(e[i].x,e[i].y,e[i].z),add(e[i].y,e[i].x,e[i].z);
	for (int i=1;i<=m;i++){
    	if (!e[i].flg) continue;
    	Dij(e[i].x);
        for (int j=1;j<=q;j++) Q[j].z=min(dis[Q[j].x]+dis[Q[j].y],Q[j].z);
    }
    for (int i=1;i<=q;i++) printf("%lld\n",Q[i].z);
    return 0;
}
```

---

## 作者：MikukuOvO (赞：1)

由于边和点的相差很小，并且还是一个连通图，所以我们可以认为是在一棵树上加了若干条边，那么我们考虑一组点对$(u,v)$之间的最短距离可以变成树上最短距离和分别考虑必须经过某条边的最短距离，这样我们把形成环的边的两个点记录下来，然后分别对于这些点跑最短路，可以证明这样的点最多只有$40$个，因此总复杂度为$qlogn+40\times nlogn+40\times q$

```cpp
const int N=1e5+5;
const int M=45;

int n,m,q,cnt,num;
int s[M],head[N],anc[N],ex[N],ey[N],ez[N],dep[N];
int f[N][21];
ll g[N],dis[M][N];
struct edge
{
	int to,nxt,w;
};
edge e[N<<1];
struct node
{
	int to,w;
};
vc<node>t[N];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>c;
bool vis[N];

void add(int x,int y,int z)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	e[cnt].w=z;
	head[x]=cnt;
}
void link(int x,int y,int z)
{
	add(x,y,z),add(y,x,z);
}
int find(int x)
{
	if(anc[x]==x) return x;
	return anc[x]=find(anc[x]);
}
void Kruskal()
{
	for(int i=1;i<=n;++i) anc[i]=i;
	for(int i=1;i<=m;++i)
	{
		int x=ex[i],y=ey[i],z=ez[i];
		int fx=find(x),fy=find(y);
		if(fx==fy) s[++num]=x,s[++num]=y;
		else
		{
			t[x].pub({y,z}),t[y].pub({x,z});
			anc[fx]=fy;
		}
	}
}
void dfs(int x,int fa,int d)
{
	f[x][0]=fa,dep[x]=d;
	for(int i=1;i<=20;++i) f[x][i]=f[f[x][i-1]][i-1];
	for(auto i:t[x])
	{
		int v=i.to,w=i.w;
		if(v==fa) continue;
		g[v]=g[x]+w;
		dfs(v,x,d+1);
	}
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	for(int i=20;i>=0;--i) if(dep[f[x][i]]>=dep[y]) x=f[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;--i) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
void Dijkstra(int id,int src)
{
	memset(dis[id],INF,sizeof(dis[id])),ms(vis);
	dis[id][src]=0,c.push(make_pair(dis[id][src],src));
	while(!c.empty())
	{
		int x=c.top().se;
		c.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(int i=head[x];i;i=e[i].nxt)
		{
			int v=e[i].to;
			if(dis[id][x]+e[i].w<dis[id][v]) dis[id][v]=dis[id][x]+e[i].w,c.push(make_pair(dis[id][v],v));
		}
	}
}
int main()
{
	fio();
	gi(n,m);
	for(int i=1;i<=m;++i) gi(ex[i],ey[i],ez[i]),link(ex[i],ey[i],ez[i]);
	Kruskal();
	dfs(1,0,1);
	for(int i=1;i<=num;++i) Dijkstra(i,s[i]);
	gi(q);
	while(q--)
	{
		int x,y;
		gi(x),gi(y);
		ll d=g[x]+g[y]-2*g[lca(x,y)];
		for(int i=1;i<=num;++i) d=min(d,dis[i][x]+dis[i][y]);
		print(d),pc(10);
	}
	end();
}
```

---

## 作者：大菜鸡fks (赞：1)

m-n<=20这个性质很重要。 由此联想到，如果建一棵生成树，那么最短路上的很多都是树边。

据此分类讨论：

1.路径在生成树上，最短路径即树上两点间距离。

2.路径包含有非树边，那么最多只包含20条非树边。

我们如何处理？ 把这20条非树边的两端单独拿出来做最短路。假设u点有一条非树边， 那么就用 dis[u][S]+dis[u][T]来更新答案

```cpp
#include<bits/stdc++.h>
#define int long long 
#define pa pair<int,int>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=1e5+30,INF=1e18; 
struct edge{
	int link,next,val;
}e[N<<1],ed[N<<1];
struct Edge{
	int u,v,w; 
}E[N];
bool vis[N],mark[N];
int ans,cnt,he[N],n,m,tot,head[N];
inline void add_edge(int u,int v,int w){
	e[++tot]=(edge){v,head[u],w}; head[u]=tot;
}
inline void Add_edge(int u,int v,int w){
	ed[++tot]=(edge){v,he[u],w}; he[u]=tot; 
}
inline void ins(int u,int v,int w){
	Add_edge(u,v,w); Add_edge(v,u,w);
}
inline void insert(int u,int v,int w){
	add_edge(u,v,w); add_edge(v,u,w);
}
inline void init(){
	n=read(); m=read();
	for (int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		insert(u,v,w);
		E[i]=(Edge){u,v,w};
	}
}
int D[N],dis[45][N],dep[N],anc[N][20],fa[N];
int getfa(int x){
	return (fa[x]==x)?x:fa[x]=getfa(fa[x]);
}
void dfs(int u,int Fa){
	anc[u][0]=Fa; dep[u]=dep[Fa]+1;
	for (int i=1;i<20;i++) anc[u][i]=anc[anc[u][i-1]][i-1];
	for (int i=he[u];i;i=ed[i].next){
		int v=ed[i].link;
		if (v!=Fa){
			D[v]=D[u]+ed[i].val;
			dfs(v,u);
		}
	}
}
inline int LCA(int u,int v){
	if (dep[u]<dep[v]) swap(u,v);
	int delta=dep[u]-dep[v];
	for (int i=0;i<20;i++) if (delta&(1<<i)) u=anc[u][i];
	if (u==v) return u;
	for (int i=19;i>=0;i--) if (anc[u][i]!=anc[v][i]) u=anc[u][i],v=anc[v][i];
	return anc[u][0];
}
inline int dist(int u,int v){
	return D[u]+D[v]-2*D[LCA(u,v)];
}
priority_queue<pa,vector<pa>,greater<pa> > heap;
inline void dijkstra(int S,int id){
	for (int i=1;i<=n;i++) dis[id][i]=INF; 
	memset(vis,0,sizeof vis);
	dis[id][S]=0; heap.push(make_pair(0,S));
	while (!heap.empty()){
		int u=heap.top().second; heap.pop();
		if (vis[u]) continue;
		vis[u]=1;
		for (int i=head[u];i;i=e[i].next){
			int v=e[i].link;
			if (dis[id][v]>dis[id][u]+e[i].val){
				dis[id][v]=dis[id][u]+e[i].val;
				heap.push(make_pair(dis[id][v],v));
			}
		}
	}
}
inline void build(){
	for (int i=1;i<=n;i++) fa[i]=i; tot=0;
	for (int i=1;i<=m;i++){
		int p=getfa(E[i].u),q=getfa(E[i].v);
		if (p!=q){
			fa[p]=q;
			ins(E[i].u,E[i].v,E[i].w);
		}else{
			mark[E[i].u]=mark[E[i].v]=1;
		}
	}
	dfs(1,0);
	for (int i=1;i<=n;i++){
		if (mark[i]){
			dijkstra(i,++cnt);
		}
	}
}
inline void solve(){
	build(); int q=read();
	for (int i=1;i<=q;i++){
		int u=read(),v=read();
		ans=dist(u,v);
		for (int j=1;j<=cnt;j++){
			ans=min(dis[j][u]+dis[j][v],ans); 
		}
		writeln(ans);
	}
}
signed main(){
	init(); solve();
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：0)


## 分析

一句话题意：给出一个无向连通图，图中有n个点，m条边，m-n<=20，给出q个询问，每一个询问包含两个整数u和v，对于每一次询问，输出u和v之间的最短路

善良的出题人特别强调了m-n<=20这一个条件

其实如果没有这个条件的话，我们就只能暴力去枚举了

但是既然给出了这个条件，我们就要好好地利用

边数最多只比点数多20，说明这一个图是非常接近一棵树的

如果是树的话，那我们就可以直接用一个LCA维护就可以了

但是这道题中的图要比正常的树多几条边

所以我们可以考虑先来一个最小生成树（随便生成一个树也可以）

这样我们就可以把n-1条边搞定

剩下的m-n+1条边，我们就可以分别以这两条边的两个端点为起点跑最短路

同时把这些点建立一个map映射

这样最短路最多会跑42次

在每一次处理两个点时，我们就可以拿这两个点的LCA

和这两个点到map映射那些点的距离之和中取最小值

需要注意的是，最小生成树和最短路不能用一个图，因为你最小生成树sort之后边就不对应了

所以要提前保存好

## 代码

``` cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
using namespace std;
typedef long long ll;
const int maxn=2e5+50;
map<ll,ll> ma;
struct asd{
    ll from,to,next;
    ll val;
}b[maxn*2],b2[maxn*2],b3[maxn*2];
ll tot=2,head[maxn];
ll diss[50][maxn];
ll bh;
inline void ad(ll aa,ll bb,ll cc){
    b[tot].from=aa;
    b[tot].to=bb;
    b[tot].next=head[aa];
    b[tot].val=cc;
    head[aa]=tot++;
}
ll h2[maxn],t2=2;
inline void ad2(ll aa,ll bb,ll cc){
    b2[t2].from=aa;
    b2[t2].to=bb;
    b2[t2].next=h2[aa];
    b2[t2].val=cc;
    h2[aa]=t2++;
}
ll h3[maxn],t3=2;
inline void ad3(ll aa,ll bb,ll cc){
    b3[t3].from=aa;
    b3[t3].to=bb;
    b3[t3].next=h3[aa];
    b3[t3].val=cc;
    h3[aa]=t3++;
}
//以上是建边，分别对应原图（跑最短路）、LCA、最小生成树
struct jie{
	ll num;
	ll dis;
	jie(ll aa=0,ll bb=0){
		num=aa,dis=bb;
	}
	bool operator < (const jie& A) const{
		return dis>A.dis;
	}
};
ll vis[maxn];
void dij(ll xx){
    priority_queue<jie> q;
	q.push(jie(xx,0));
	diss[ma[xx]][xx]=0;
    memset(vis,0,sizeof(vis));
	while(!q.empty()){
		ll now=q.top().num;
		q.pop();
		if(vis[now]) continue;
		vis[now]=1;
		for(ll i=head[now];i!=-1;i=b[i].next){
			ll u=b[i].to;
			if(diss[ma[xx]][u]>b[i].val+diss[ma[xx]][now]){
				diss[ma[xx]][u]=b[i].val+diss[ma[xx]][now];
				q.push(jie(u,diss[ma[xx]][u]));
			}
		}
	}
}
//dij模板
ll f[maxn][25],dep[maxn];
ll cost[maxn][25];
void dfs(ll now,ll fa,ll da){
    dep[now]=dep[fa]+1;
    f[now][0]=fa;
    cost[now][0]=da;
    for(ll i=1;(1<<i)<=dep[now];i++){
        f[now][i]=f[f[now][i-1]][i-1];
        cost[now][i]=cost[now][i-1]+cost[f[now][i-1]][i-1];
    }
    for(ll i=h2[now];i!=-1;i=b2[i].next){
        ll u=b2[i].to;
        if(fa!=u) dfs(u,now,b2[i].val);
    }
}
ll Lca(ll aa,ll bb){
    if(dep[aa]>dep[bb]) swap(aa,bb);
    ll len=dep[bb]-dep[aa],k=0;
    ll ans=0;
    while(len){
        if(len&1){
            ans+=cost[bb][k];
            bb=f[bb][k];
        }
        k++,len>>=1;
    }
    if(aa==bb) return ans;
    for(ll i=20;i>=0;i--){
        if(f[aa][i]==f[bb][i]) continue;
        ans+=cost[aa][i];
        ans+=cost[bb][i];
        aa=f[aa][i],bb=f[bb][i];
    }
    return ans+cost[aa][0]+cost[bb][0];
}
//倍增求LCA模板
ll zx[maxn*2],visb[maxn*2];
ll zhao(ll xx){
    if(xx==zx[xx]) return xx;
    return zx[xx]=zhao(zx[xx]);
}
void bing(ll xx,ll yy){
    zx[zhao(xx)]=zhao(yy);
}
bool cmp(asd aa,asd bb){
    return aa.val<bb.val;
}
void shu(ll xx){
    sort(b3+2,b3+t3,cmp);
    for(ll i=0;i<maxn;i++) zx[i]=i;
    ll cnt=0;
    for(ll i=2;i<t3;i++){
        ll x=b3[i].from,y=b3[i].to;
        if(zhao(x)!=zhao(y)){
            bing(x,y);
            ad2(x,y,b3[i].val);
            ad2(y,x,b3[i].val);
            visb[i]=1;
            if(++cnt==xx) return;
        }
    }
}
//最小生成树模板
int main(){
    memset(diss,0x3f,sizeof(diss));
    memset(head,-1,sizeof(head));
    memset(h2,-1,sizeof(h2));
    memset(h3,-1,sizeof(h3));
    ll n,m;
    scanf("%lld%lld",&n,&m);
    for(ll i=1;i<=m;i++){
        ll aa,bb;
        ll cc;
        scanf("%lld%lld%lld",&aa,&bb,&cc);
        ad(aa,bb,cc),ad(bb,aa,cc);
        ad3(aa,bb,cc);
    }
    shu(n-1);
    for(ll i=2;i<t3;i++){
        if(!visb[i]){
            visb[i]=1;
            ll x=b3[i].from,y=b3[i].to;
            if(!ma[x]) ma[x]=++bh,dij(x);
            if(!ma[y]) ma[y]=++bh,dij(y);
        }
    }
    //把没有加到最小生成树中的边的两个端点拿出来跑最短路
    dfs(1,0,0);
    ll q;
    scanf("%lld",&q);
    for(ll i=1;i<=q;i++){
        ll aa,bb;
        scanf("%d%d",&aa,&bb);
        ll ans=Lca(aa,bb);
        for(ll i=1;i<=bh;i++){
            ans=min(ans,diss[i][aa]+diss[i][bb]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
```



---

