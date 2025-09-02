# [ARC074F] Lotus Leaves

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc074/tasks/arc074_d

長方形の池があります。 池は縦 $ H $ 行、横 $ W $ 列のマス目状に分割されています。 上から $ i $ 行目、左から $ j $ 列目のマスを $ (i,\ j) $ と表します。

池のいくつかのマスには蓮 (はす) の葉が浮かんでいます。 ある葉 $ S $ にはカエルが乗っており、別の葉 $ T $ まで移動しようとしています。 マス $ (i,\ j) $ の情報は、文字 $ a_{ij} $ によって次のように表されます。

- `.` : 葉が浮かんでいないマスである。
- `o` : 葉が浮かんでいるマスである。
- `S` : 葉 $ S $ が浮かんでいるマスである。
- `T` : 葉 $ T $ が浮かんでいるマスである。

カエルは「今乗っている葉と同じ行または同じ列に浮かんでいる葉へジャンプする」ことを繰り返し行い、葉 $ T $ まで移動しようとしています。

すぬけ君の目標は、あらかじめ葉 $ S $, $ T $ 以外の葉を何枚か取り除いておくことで、カエルが葉 $ T $ まで移動できないようにすることです。 この目標が達成可能か判定し、可能ならば取り除く葉の枚数の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ H,\ W\ <\ =\ 100 $
- $ a_{ij} $ は `.`, `o`, `S`, `T` のどれかである。
- $ a_{ij} $ のうち `S` はちょうど $ 1 $ 個存在する。
- $ a_{ij} $ のうち `T` はちょうど $ 1 $ 個存在する。

### Sample Explanation 1

右上と左下の葉を取り除けばよいです。

## 样例 #1

### 输入

```
3 3
S.o
.o.
o.T```

### 输出

```
2```

## 样例 #2

### 输入

```
3 4
S...
.oo.
...T```

### 输出

```
0```

## 样例 #3

### 输入

```
4 3
.S.
.o.
.o.
.T.```

### 输出

```
-1```

## 样例 #4

### 输入

```
10 10
.o...o..o.
....o.....
....oo.oo.
..oooo..o.
....oo....
..o..o....
o..o....So
o....T....
....o.....
........oo```

### 输出

```
5```

# 题解

## 作者：Daniel_yuan (赞：5)

题目要求最少需要将多少个 ```o``` 改成 ```.``` ，可以使这个人无法从 ```S``` 到达 ```T``` 。很容易想到最小割。

由最小割等于最大流可以想到一个特别 naive 的想法：```S``` 只连出边，```T``` 只连入边，其它点向其能到达的点连边，然后跑网络流。

因为点与点之间连的边只是为了连通两个点，所以边权是 $+\infty$ 。比较困难的是如何通过边权的限制实现每个点只割一次。

对于这种限制点权的网络流，一种简单的方法是把一个点拆成一个入点和一个出点，并且在入点和出点之间连一条流量为点权的边。所有以该点为终点的边全部连到它的入点，反之则连到它的出点。

这样连好后就可以跑网络流了，但是对于每个点，其在每一行内最多有 $n$ 个可到达点，列也是如此，一共有 $n^2$ 个点，最多有 $n^3$ 条边，感觉 $10^6$ 不太可过，考虑优化。

不难发现，对于同一行或者同一列的点，都是互相可达，那么其实不需要两两连边，只需要对于每行和列建一个辅助节点作为中转，即可把边数降到 $n^2$ 级别。

最后的最大流就是所求答案，至于判断可行性，可以一开始就看 ```S``` 和 ```T``` 在不在同一行或同一列内，也可以看跑完网络流后是不是割了 $+\infty$ 边。

代码如下：

```cpp
#include <bits/stdc++.h>
#define RI register int
typedef long long LL;

#define FILEIO(name) freopen(name".in", "r", stdin), freopen(name".out", "w", stdout);

using namespace std;

char buf[1000000], *p1 = buf, *p2 = buf;
inline char gc() {
  if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin);
  return p1 == p2 ? EOF : *(p1++);
}
template <class T> inline void read(T &n) {
  n = 0; RI ch = gc(), f;
  while ((ch < '0' || ch > '9') && ch != '-') ch = gc();
  f = (ch == '-' ? ch = gc(), -1 : 1);
  while (ch >= '0' && ch <= '9') n = n * 10 + (ch ^ 48), ch = gc();
  n *= f;
}

int const MAXN = 105, INF = 0x7f7f7f7f;
struct Edges { int to, next, dis; } e[MAXN * MAXN * MAXN];
int head[MAXN * MAXN * MAXN], tot = 1;
int In[MAXN][MAXN], Out[MAXN][MAXN], cnt, S, T, Row[MAXN], Line[MAXN];
int dep[MAXN * MAXN * MAXN], cur[MAXN * MAXN * MAXN];
char s[MAXN][MAXN];
queue <int> q;

inline void addedge(int from, int to, int dis) {
  e[++tot] = (Edges){to, head[from], dis};
  head[from] = tot;
  e[++tot] = (Edges){from, head[to], 0};
  head[to] = tot;
}

bool Bfs() {
  memset(dep, 0, sizeof(dep));
  dep[S] = 1;
  q.push(S);
  while (!q.empty()) {
    int t = q.front(); q.pop();
    for (RI i = head[t]; i; i = e[i].next)
      if (!dep[e[i].to] && e[i].dis)
        dep[e[i].to] = dep[t] + 1, q.push(e[i].to);
  }
  if (!dep[T]) return 0;
  for (RI i = 1; i <= cnt; ++i) cur[i] = head[i];
  return 1;
}

int Dfs(int now, int res) {
  if (now == T || !res) return res;
  int sum = 0;
  for (RI i = cur[now]; i; i = e[i].next) {
    cur[now] = i;
    if (dep[e[i].to] == dep[now] + 1) {
      int d = Dfs(e[i].to, min(res, e[i].dis));
      if (d) {
        sum += d;
        res -= d;
        e[i].dis -= d;
        e[i ^ 1].dis += d;
      }
    }
  }
  return sum;
}

int Dinic() {
  int Maxflow = 0;
  while (Bfs())
    Maxflow += Dfs(S, INF);
  return Maxflow;
}

int main() {
  
#ifdef LOCAL
  FILEIO("a");
#endif

  int n, m; scanf("%d %d", &n, &m);
  for (RI i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  for (RI i = 1; i <= n; ++i) Row[i] = ++cnt;
  for (RI i = 1; i <= m; ++i) Line[i] = ++cnt;
  for (RI i = 1; i <= n; ++i)
    for (RI j = 1; j <= m; ++j) {
      if (s[i][j] == 'o') {
        In[i][j] = ++cnt, Out[i][j] = ++cnt;
        addedge(Out[i][j], Row[i], INF);
        addedge(Out[i][j], Line[j], INF);
        addedge(Row[i], In[i][j], INF);
        addedge(Line[j], In[i][j], INF);
        addedge(In[i][j], Out[i][j], 1);
      }
      if (s[i][j] == 'S') {
        S = ++cnt;
        addedge(S, Row[i], INF);
        addedge(S, Line[j], INF);  
      }
      if (s[i][j] == 'T') {
        T = ++cnt;
        addedge(Row[i], T, INF);
        addedge(Line[j], T, INF);
      }
    }
  int Maxflow = Dinic();
  if (Maxflow > n * m) puts("-1");
  else printf("%d\n", Maxflow);

  return 0;
}

// created by Daniel yuan

```

---

## 作者：NATO (赞：4)

#### 思路浅析：

观察到删除最少的点数使某两个指定点不联通，很容易想到最小割。

朴素建图是很平凡的，套路地考虑先拆点，目的是把割点变成割边。将一个点拆成入点和出点两个点，连上一条流量为 $1$ 的边来表示是否删掉这个点，再按照题意向该点所在行、列的每个可以通过的点连边，跑网络流即可，但边数 $O(n^3)$，无法通过本题。

优化也是很容易想到的，考虑我们一行（列）的所有点之间都是两两两边的，这很浪费，考虑建立一个“集散地”（虚点），一行（列）的所有点和对应虚点连双向边即可，这样边数就是 $O(n^2)$ 的了，再跑网络流，可以通过此题。

#### 参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define INF 214738464719260817ll
using namespace std;
ll h,w;
ll s,t;
char a;
ll head[20205],cnt=1;
struct ed
{
	ll v,next,w;
}edge[120005];
void add(ll u,ll v,ll w)
{
	edge[++cnt].v=v;edge[cnt].w=w;edge[cnt].next=head[u];head[u]=cnt;
	edge[++cnt].v=u;edge[cnt].w=0;edge[cnt].next=head[v];head[v]=cnt;
}
queue<ll>k;
ll dep[20205],cur[20205];
bool bfs()
{
	for(ll i=1;i<=h*w*2+h+w;++i)dep[i]=0,cur[i]=head[i];
	dep[s]=1;
	k.push(s);
	while(!k.empty())
	{
		ll h=k.front();k.pop();
		for(ll i=head[h];i;i=edge[i].next)
		{
			ll v=edge[i].v,w=edge[i].w;
			if(!w||dep[v])continue;
			dep[v]=dep[h]+1;
			k.push(v);
		}
	}
	return dep[t];
}
ll dfs(ll id,ll get)
{
	if(id==t)return get;
	ll cost=0;
	for(ll i=cur[id];i;i=edge[i].next)
	{
		ll v=edge[i].v,w=edge[i].w;cur[id]=i;
		if(dep[v]!=dep[id]+1||!w)continue;
		ll nc=dfs(v,min(get,w));
		get-=nc;cost+=nc;
		edge[i].w-=nc;edge[i^1].w+=nc;
	}
	if(!cost)dep[id]=0;
	return cost;
}
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>h>>w;
	for(ll i=1;i<=h;++i)
		for(ll j=1;j<=w;++j)
		{
			cin>>a;
			if(a!='.')
			{
				ll where=(i-1)*w+j;
				if(a!='S'&&a!='T')
				add(where,where+h*w,1);
				if(a=='S')s=where+h*w;
				if(a=='T')t=where;
				add(where+h*w,2*h*w+i,INF);
				add(2*h*w+i,where,INF);
				add(where+h*w,2*h*w+h+j,INF);
				add(2*h*w+h+j,where,INF);
			}
		}
	ll ls,res=0;
	while(bfs())
	while(ls=dfs(s,INF))
	res+=ls;
	if(res<=h*w)cout<<res;
	else cout<<-1;
}
```

---

## 作者：__FL__ (赞：3)

## 思路
看到要割掉一些点，使得从起点无法到达终点，很容易想到最小割。我们可以将每个点拆为入点和出点，入点向出点连一条流量为 $1$ 的边，一个点的出点向它所有能到达的点的入点连一条流量为正无穷的边，显然当入点连出点的边流满时，就相当于我们把这条边割去了。最后根据最大流最小割定理，直接跑最大流就行了。

这个思路似乎还需要优化，因为每一个点都需要向它能到达的点连边，这个数量是 $n$ 的量级，而一共有 $n^2$ 量级的点，总共最多会连 $n^3$ 量级的边，按理说应该建虚点进行优化。但是经过我的测试，$\mathrm{Dinic}$ 算法不建虚点的情况下连 $200ms$ 都没跑到。我认为这是因为对于这道题来说，边排布得十分密集，同时搜索的层数也较浅，导致 $\mathrm{Dinic}$ 增广较少次数就能找到答案。

对于无解的情况，显然只有从起点能直接到达终点时会发生，特判出来就好。

## 代码


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 20005,M = 10000005,inf = 1e10;
int n,m,s,t,head[N],nxt[M],to[M],w[M],cnt=-1,d[N],ans,fa[N];
char mp[105][105];
queue<int>q;
inline void add(int u,int v,int c) {nxt[++cnt] = head[u]; head[u] = cnt; to[cnt] = v; w[cnt] = c;}
inline void Add(int u,int v,int c) {add(u,v,c); add(v,u,0);}
bool bfs()
{
	while (!q.empty()) q.pop();
	memset(d,0,sizeof d);
	q.push(s);
	d[s] = 1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int i = head[u]; ~i; i = nxt[i])
		{
			int v = to[i];
			if (w[i] && !d[v])
			{
				d[v] = d[u]+1;
				if (v == t)
					return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
int dfs(int u,int limit)
{
	if (u == t) return limit;
	int flow = 0;
	for (int i = head[u]; ~i; i = nxt[i])
	{
		int v = to[i];
		if (d[v] == d[u]+1 && w[i])
		{
			int p = dfs(v,min(w[i],limit-flow));
			if (!p) d[v] = -1;
			flow += p;
			w[i] -= p;
			w[i^1] += p;
			if (flow == limit) return flow;
		}
	}
	return flow;
}
int Dinic()
{
	int ans = 0;
	while (bfs())
		ans += dfs(s,inf);
	return ans;
}
inline int f(int x,int y) {return m>n? (x-1)*m+y: (x-1)*n+y;}
signed main()
{
	ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	memset(head,-1,sizeof head);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> mp[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			Add(f(i,j)+n*m,f(i,j),1);
			if (mp[i][j] == 'S')
			{
				s = f(i,j);
				for (int k = 1; k <= n; k++)
					if (mp[k][j] == 'o')
						Add(f(i,j),f(k,j)+n*m,1);
					else if (mp[k][j] == 'T')
					{
						cout << -1;
						return 0;
					}
				for (int k = 1; k <= m; k++)
					if (mp[i][k] == 'o')
						Add(f(i,j),f(i,k)+n*m,1);
					else if (mp[i][k] == 'T')
					{
						cout << -1;
						return 0;
					}
			}
			else if (mp[i][j] == 'T')
				t = f(i,j)+n*m;
			else if (mp[i][j] == 'o')
			{
				for (int k = 1; k <= n; k++)
					if (mp[k][j] == 'o' && k != i || mp[k][j] == 'T')
						Add(f(i,j),f(k,j)+n*m,inf);
				for (int k = 1; k <= m; k++)
					if (mp[i][k] == 'o' && k != j || mp[i][k] == 'T')
						Add(f(i,j),f(i,k)+n*m,inf);
			}
		}
	cout << Dinic();
	return 0;
}
```

---

## 作者：Reunite (赞：3)

先考虑暴力建可达性的图，转化为删去最少的点使得 $S,T$ 不连通，也许可以通过拆出入点以及虚点优化跑最小割做，但我没细想。

删点不好做，考虑怎么点边转换，注意到若当前在 $(x,y)$，则同行同列点都等价，可以看成往其他行列的连边，也就是经典网格图转二分图模型。若点 $(x,y)$ 存在，则连 $L_x$ 与 $R_y$ 的**双向边**，容量为 $1$。若是 $S,T$，就行列分别与源汇点连双向边，容量无限。则其最小割即为答案。

稍微说明一下为什么是对的，首先任一条非 $S,T$ 连出的边都意味着一个点，每删一条边就删去了一个点；如果到达了 $L_i$，则说明整个 $i$ 行都可达，$R_i$ 同理，则当源汇点不连通时，一定不可达。都连双向边是因为每次可以选择走行或者列。

点数 $O(n+m)$，边数 $O(nm)$，直接跑 Dinic 最小割就行了。

```cpp
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",c[i]+1);
    int S=n+m+1,T=S+1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]=='S') add(S,i,1e9),add(S,j+n,1e9);
            if(c[i][j]=='T') add(i,T,1e9),add(j+n,T,1e9);
            if(c[i][j]!='.') add(i,j+n,1),add(j+n,i,1);
        }
    }
    int x=Dinic(S,T);
    if(x<=n*m) printf("%d\n",x);
    else puts("-1");
```

---

## 作者：19ty02 (赞：2)

## 题目大意

给出一个 $n \times m$ 的池塘，上面有一些荷叶，有一个青蛙从 $'S'$ 荷叶出发，每次只能跳到同行同列的荷叶，现在你可以移除一些荷叶，求最少要移除多少荷叶可以是青蛙无法到达 $'T'$ 荷叶。

$1\leq n,m \leq 100$

## 解法
结合数据范围，不难想到可以使用最小割。

问题在于如何建图，朴素的想法是把一个荷叶拆成两个点，连一条权值为1的边，若两个荷叶在同一行或同一列，就连一条权值为 $inf$ 的边，但这样边数最多会卡到 $O(n^3)$ 级别，无法通过本题。

考虑网格图中网络流建模的一个经典的trick，就是把网格图当成二分图，左边有 $n$ 个节点，代表每一行，右边有 $m$ 个节点，代表每一列。

1. 如果 $(i,j)$ 是荷叶，就把 $L_i$ 到 $R_j$ 连一条边权为1的边( $L_i$ 为二分图左边的第 $i$ 个节点，$R_j$ 为二分图右边的第 $j$ 个节点)，代表着第 $i$ 行可以通过此荷叶到达第 $j$ 列。

2. 如果 $(i,j)$ 是 $'S'$，$S$ 向 $L_i$ 和 $R_j$ 分别连一条 $inf$ 的边。

3. 如果 $(i,j)$ 是 $'T'$，$L_i$ 和 $R_j$ 分别向 $T$ 连一条 $inf$ 的边。

然后跑最小割就行了。

## 代码
```cpp
#include<cstdio>
#include<cstring>
#include<iostream> 
using namespace std;
const int N=205,inf=N*N;
int n,m,h[N],tot=1,S,T;
char ch[N][N];
struct edge{
	int v,w,nxt;
}e[N*N];
void add(int u,int v,int w){
	e[++tot]=(edge){v,w,h[u]};
	h[u]=tot;
}
int lev[N],q[N],l,r;
bool bfs(){
	memset(lev,-1,sizeof(lev));l=1;r=0;
	lev[S]=0;q[++r]=S;
	while(l<=r){
		int u=q[l++];
		for(int i=h[u];i;i=e[i].nxt){
			int v=e[i].v;
			if(lev[v]==-1&&e[i].w){
				lev[v]=lev[u]+1;
				q[++r]=v;
			}
		}
	}
	return lev[T]!=-1;
} 
int dfs(int u,int upf){
	if(u==T)return upf;
	int rst=upf;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].v,w=e[i].w;
		if(lev[v]==lev[u]+1&&w){
			int now=dfs(v,min(rst,w));
			rst-=now;
			e[i].w-=now;
			e[i^1].w+=now;
			if(!rst)break;
		}
	}
	return upf-rst;
}
int main(){
	scanf("%d%d",&n,&m);T=n+m+1;
	for(int i=1;i<=n;i++){
		scanf("%s",ch[i]+1);
		for(int j=1;j<=m;j++){
			if(ch[i][j]=='o'){
				add(i,j+n,1);
				add(j+n,i,1); 
			}
			if(ch[i][j]=='S'){
				add(S,i,inf);add(i,S,0);
				add(S,j+n,inf);add(j+n,S,0);
			}
			if(ch[i][j]=='T'){
				add(i,T,inf);add(T,i,0);
				add(j+n,T,inf);add(T,j+n,0);
			}
		}
	}
	int ans=0; 
	while(bfs()){
		ans+=dfs(S,inf);
	}
	if(ans>=inf)printf("-1");
	else printf("%d",ans);
}

```

---

## 作者：Xy_top (赞：0)

一道很简单的题，但是逼着我学会了 dinic（原先只会 EK）。

看这个数据范围，不可能是有什么神秘的结论了，然后又是要割掉边使得 $S$ 无法到达 $T$，很自然地想到网络流吧。

一个显然的建图方法是，将每个点拆成出入两个点（这是为了控制流量），如果这个点是 ``.``，那么出点入点之间的流量为 $0$（这个点已经被割了），否则为 $1$。

那么将一个点染成 ``.`` 就相当于把它废了，也就相当于，注意如果把一个点的出点入点之间的边割了，消耗 $1$ 的操作次数。

然后再把任意两个能到的点连边，流量为 $inf$（不能割这条边）。

但是超时了，因为边数高达 $n^3$，显然能够想到对每一行每一列建虚点，入点和出点分别连虚点，然后流量为 $inf$。

最后看跑完的流量是否 $< inf$ 即可。

代码：

```cpp
#include <bits/stdc++.h>
#define For(i, a, b) for (int i = (a); i <= (b); i ++)
#define foR(i, a, b) for (int i = (a); i >= (b); i --)
using namespace std;
int n, m, s, t;
int k, ans;
int d[100005], pre[30005], head[30005];
char c;
queue <int> q;
struct Edge {int v, w, nxt;}a[100005];
void add (int u, int v, int w) {
	a[k] = {v, w, head[u]};
	head[u] = k ++;
}
bool BFS () {
	For (i, 1, 3 * n * m) d[i] = 0;
	For (i, 1, 3 * n * m) pre[i] = head[i];
	d[s] = 1;
	q.push (s);
	while (!q.empty () ) {
		int u = q.front ();
		q.pop ();
		for (int i = pre[u]; ~i; i = a[i].nxt) {
			int v = a[i].v;
			if (a[i].w && (d[v] == 0 || d[v] > d[u] + 1) ) {
				d[v] = d[u] + 1;
				q.push (v);
			}
		}
	}
	return d[t];
}
int dfs (int u, int flow) {
	if (u == t) return flow;
	int ret = 0;
	for (int i = pre[u]; ~i; i = a[i].nxt) {
		pre[u] = i;
		int v = a[i].v, f;
		if (d[v] == d[u] + 1 && a[i].w && (f = dfs (v, min (a[i].w, flow - ret) ) ) ) {
			ret += f;
			a[i].w -= f;
			a[i ^ 1].w += f;
			if (ret == flow) return ret;
		}
	}
	return ret;
}
signed main () {
	cin >> n >> m;
	For (i, 1, 3 * n * m) head[i] = -1;
	For (i, 1, n) {
		For (j, 1, m) {
			int x = (i - 1) * m + j, y = (i - 1) * m + j + n * m;
			c = getchar ();
			while (c == '\n' || c == ' ') c = getchar ();
			if (c == 'o') {
				add (x, y, 1);
				add (y, x, 0);
			}//x 入，y 出
			if (c != 'T') {
				add (y, i + 2 * n * m, 1000000000);
				add (i + 2 * n * m, y, 0);
				add (y, n + j + 2 * n * m, 1000000000);
				add (n + j + 2 * n * m, y, 0);
			} else t = x;
			if (c != 'S') {
				add (i + 2 * n * m, x, 1000000000);
				add (x, i + 2 * n * m, 0);
				add (n + j + 2 * n * m, x, 1000000000);
				add (x, n + j + 2 * n * m, 0);
			} else s = y;
		}
	}
	while (BFS () ) ans += dfs (s, 1000000000);
	if (ans >= 1000000000) cout << -1;
	else cout << ans;
	return 0;
}
```


---

## 作者：Arghariza (赞：0)

如果网格只是 $4$ 联通的话，似乎就是最小割板子了（当然也有不用最小割的做法）。

然后考虑一行一列相互连通怎么做，有一个套路叫网格图转二分图。

因为我们可以将一行或一列看成联通的整体，所以建一个二分图，左边表示 $1$ 到 $n$ 行，右边表示 $1$ 到 $m$ 列。

- 如果 $(i,j)$ 为空地，说明这个点可以连接第 $i$ 行和第 $j$ 列，给 $(l_i,r_j)$ 连上边。
- 如果 $(i,j)$ 为障碍，说明通过这个点不能连接 $l_i,r_j$，那就不连边即可。
- 如果 $(i,j)$ 为起点，则将源点连接 $l_i,r_j$ 即可。
- 如果 $(i,j)$ 为终点，则将 $l_i,r_j$ 连接到汇点即可。

两个点之间有连边时可以看作联通，那么不难看出我们要求的就是原图的最小割。

跑最大流即可。

```cpp
#include <bits/stdc++.h>
#define int long long
namespace mystd {
	inline int read() {
	    char c = getchar();
	    int x = 0, f = 1;
	    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
	    while (c >= '0' && c <= '9') x = (x << 1) + (x << 3) + c - '0', c = getchar();
	    return x * f;
	}
	inline void write(int x) {
	    if (x < 0) x = ~(x - 1), putchar('-');
	    if (x > 9) write(x / 10);
	    putchar(x % 10 + '0');
	}
}
using namespace std;
using namespace mystd;

const int maxn = 110;
const int inf = 1e18;
struct edge { int to, nxt, w; } e[maxn * maxn << 3];
int n, m, s, t, tot = 1, ans, head[maxn << 1], dep[maxn << 1];
char c[maxn][maxn];

void add_edge(int u, int v, int w) { e[++tot] = (edge) { v, head[u], w }, head[u] = tot; }
void add_flow(int u, int v, int w) { add_edge(u, v, w), add_edge(v, u, w); }

bool bfs() {
	memset(dep, 0, sizeof(dep));
	dep[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (e[i].w && !dep[v]) dep[v] = dep[u] + 1, q.push(v);
		}
	}
	return dep[t];
}

int dfs(int u, int in) {
	if (u == t) return in;
	int out = 0;
	for (int i = head[u]; i && in; i = e[i].nxt) {
		int v = e[i].to;
		if (dep[v] == dep[u] + 1 && e[i].w) {
			int res = dfs(v, min(in, e[i].w));
			e[i].w -= res;
			e[i ^ 1].w += res;
			in -= res;
			out += res;
		}
	}
	if (!out) dep[u] = 0;
	return out;
}

signed main() {
	n = read(), m = read();
	for (int i = 1; i <= n; i++) scanf("%s", c[i] + 1);
	s = 0, t = n + m + 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (c[i][j] == 'S') add_flow(s, i, inf), add_flow(s, n + j, inf);
			else if (c[i][j] == 'T') add_flow(i, t, inf), add_flow(n + j, t, inf);
			else if (c[i][j] == 'o') add_flow(i, n + j, 1), add_flow(n + j, i, 1);
		}
	}
	while (bfs()) ans += dfs(s, 1e18);
	write(ans >= 1e18 ? -1 : ans / 2);
	return 0;
}

```

---

