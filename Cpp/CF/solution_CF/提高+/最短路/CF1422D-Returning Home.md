# Returning Home

## 题目描述

Yura has been walking for some time already and is planning to return home. He needs to get home as fast as possible. To do this, Yura can use the instant-movement locations around the city.

Let's represent the city as an area of $ n \times n $ square blocks. Yura needs to move from the block with coordinates $ (s_x,s_y) $ to the block with coordinates $ (f_x,f_y) $ . In one minute Yura can move to any neighboring by side block; in other words, he can move in four directions. Also, there are $ m $ instant-movement locations in the city. Their coordinates are known to you and Yura. Yura can move to an instant-movement location in no time if he is located in a block with the same coordinate $ x $ or with the same coordinate $ y $ as the location.

Help Yura to find the smallest time needed to get home.

## 说明/提示

In the first example Yura needs to reach $ (5, 5) $ from $ (1, 1) $ . He can do that in $ 5 $ minutes by first using the second instant-movement location (because its $ y $ coordinate is equal to Yura's $ y $ coordinate), and then walking $ (4, 1) \to (4, 2) \to (4, 3) \to (5, 3) \to (5, 4) \to (5, 5) $ .

## 样例 #1

### 输入

```
5 3
1 1 5 5
1 2
4 1
3 3```

### 输出

```
5```

## 样例 #2

### 输入

```
84 5
67 59 41 2
39 56
7 2
15 3
74 18
22 7```

### 输出

```
42```

# 题解

## 作者：7KByte (赞：5)

全局的点很多，显然不能直接做。但是关键点只有$10^5$个，这是我们解题的切入点。

我们在关键点之间建图，对于两个点之间连一条长度为两者之间最短路径的边。

但这样边的级别是$\rm O(M^2)$，显然会爆。

我们观察一下图的性质，两个点之间的边会走到，只有不存在横坐标在两点之间的点或不存在纵坐标在两点之间的点。

证明显然，如果存在这样的中间点，那么先走到中间点，再走到终点，和直接走到终点是等价的。

这样我们先按$x$排序，将相邻两个元素之间连边。同理按$y$排序，将相邻两个元素之间连边。边的级别为$\rm O(M)$。

最后跑dij即可，时间复杂度$\rm O(M\log M)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define pre(i,a,b) for(int i=a;i>=b;i--)
#define N 200005
using namespace std;
int n,m,d[N],v[N];
int sx,sy,ex,ey;
struct node{int x,y,op;}a[N];
bool cmp1(node x,node y){return x.x<y.x;}
bool cmp2(node x,node y){return x.y<y.y;}
int h[N],tot;
struct edge{
	int to,nxt,val;
}e[N<<2];
void add(int x,int y,int z){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;e[tot].val=z;
}
priority_queue<pair<int,int> >q;
void dij(){
	memset(d,0x7f,sizeof(d));
	d[0]=0;q.push(make_pair(0,0));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		v[x]=1;
		for(int i=h[x];i;i=e[i].nxt){
			if(d[e[i].to]>d[x]+e[i].val){
				d[e[i].to]=d[x]+e[i].val;
				q.push(make_pair(-d[e[i].to],e[i].to));
			}
		}
		while(!q.empty()&&v[q.top().second])q.pop();
	}
	printf("%d\n",d[m+1]);
}
int main(){
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
	rep(i,1,m)scanf("%d%d",&a[i].x,&a[i].y),a[i].op=i;
	rep(i,1,m)add(0,i,min(abs(sx-a[i].x),abs(sy-a[i].y))),add(i,m+1,abs(ex-a[i].x)+abs(ey-a[i].y));
	add(0,m+1,abs(sx-ex)+abs(sy-ey));
	sort(a+1,a+m+1,cmp1);
	rep(i,1,m-1)add(a[i].op,a[i+1].op,a[i+1].x-a[i].x),add(a[i+1].op,a[i].op,a[i+1].x-a[i].x);
	sort(a+1,a+m+1,cmp2);
	rep(i,1,m-1)add(a[i].op,a[i+1].op,a[i+1].y-a[i].y),add(a[i+1].op,a[i].op,a[i+1].y-a[i].y);
	return dij(),0;
} 
```

---

## 作者：jianhe (赞：3)

### 前言：
duel 到的。被细节坑惨了/kk

### 思路：
观察数据范围，发现 $1 \le m \le 10^5$。

那么可以考虑在传送点之间两两连边，代价为纵向距离与横向距离的较小值。然后跑最短路即可。

但这样连边是 $O(m^2)$ 的，显然不行。

手模一下发现连上的许多边都是无用的。

为什么呢？

可以发现，将传送点按横坐标大小排序时，相邻两项直接连边一定不劣于通过一个中介点。

按纵坐标排序同理。

那么本题的做法就出来了：将传送点按横坐标和纵坐标分别排两次序，然后相邻相两两连边，跑最短路即可。

但有细节要注意：终点不是传送点，不能传送，因此不能把终点也塞到传送点序列中，而应该在最后枚举每个传送点，加上传送点到终点的曼哈顿距离来统计答案。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define pii pair<ll,ll> 
#define fi first
#define se second
const ll N=1e5+10,inf=1e16;
ll n,m,ans=inf,sx,sy,fx,fy,dis[N];
struct P{ll x,y,i;}E[N];
bool cmp(P A,P B){return A.x<B.x;}
bool cmp2(P A,P B){return A.y<B.y;}
vector<pii> e[N];
void add(ll x,ll y,ll w){e[x].pb({y,w}),e[y].pb({x,w});}
void dijkstra(){
	set<pii> q;q.insert({0,0});
	for(int i=1;i<=m;i++) q.insert({dis[i]=inf,i});
	while(!q.empty()){
		ll x=q.begin()->se;q.erase(q.begin());
		for(auto p:e[x])
			if(dis[p.fi]>dis[x]+p.se) q.erase({dis[p.fi],p.fi}),q.insert({dis[p.fi]=dis[x]+p.se,p.fi});
	}
}
int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	cin>>n>>m>>sx>>sy>>fx>>fy;E[0].x=sx,E[0].y=sy;
	for(int i=1;i<=m;i++) cin>>E[i].x>>E[i].y,E[i].i=i;
	sort(E,E+m+1,cmp);
	for(int i=0;i<m;i++) add(E[i].i,E[i+1].i,abs(E[i].x-E[i+1].x));
	sort(E,E+m+1,cmp2);
	for(int i=0;i<m;i++) add(E[i].i,E[i+1].i,abs(E[i].y-E[i+1].y));
	dijkstra();
	for(int i=0;i<=m;i++) ans=min(ans,dis[E[i].i]+abs(E[i].x-fx)+abs(E[i].y-fy));
	cout<<ans;
	return 0;
}
```

---

## 作者：Dream__Sky (赞：2)

有一个很暴力的思想，每个传送门与每个传送门（及起点终点）连边，跑最短路。但这样边数是 $O(n^2)$ 的，无法接受。

我们考虑如何优化边数。

有三个关键点 $i,j,k$，且 $x_i<x_j<x_k$（假设他们 $y$ 轴不相等，且这里暂时不考虑 $y$ 轴）。我们直接从 $i$ 到 $j$ 需要的步数为 $x_k-x_i$。但如果我们以 $j$ 作为中转点，那么需要的步数为 $x_k-x_j+x_j-x_i=x_k-x_i$，发现这并不会更劣。

也就是说，每次我们只要连接最接近第 $i$ 的点的点即可。将这个结论推广到 $y$ 轴也依然适用。

但别忘了要把每个点再与起点终点连边，起点与终点之间也要建边。

接着跑最短路即可。

---

## 作者：Graph_Theory (赞：1)

### 思路

本题的难度在于连边的优化，如果找到了优化的方法，剩下的就是最短路的板子。

对于整张图的最坏情况一定是直接走到终点，所以我们只需要对这张图的所有传送点、起点、终点连边求最短路。

但是，如果给每一个传送点进行连边，也就是在 $m^2$ 条边上跑最短路，明显超时，所以我们应该想一想优化。

接下来我们想，对于任意的三个点 $x_1<x_2<x_3$ 且 $y_1<y_2<y_3$ 时，此时你想从 $1$ 到 $3$ 时，如果从 $2$ 号点经过的话，此时的步数一定是优于或等于直接从 $1$ 走到 $3$ ，因为到 $2$ 号点是瞬移过去的。

所以对任意一个传送点只和他 $x$ 轴和 $y$ 轴 左右最近的点和起点终点进行连边，也就是除了起点终点之外每一个传送点就只和 $6$ 个点连边，这样就简化了空间和时间。最后，对起点和终点连边，跑一遍最基础的最短路即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e5 + 10;
const int inf = (1 << 30);

struct node
{
	int x, y, id;
} t[N];

struct Node
{
	int w, to, nxt;
} edge[N << 3];

int cnt, head[N],
	n, m,
	sx, sy, tx, ty,
	dis[N];

bool vis[N];

priority_queue <pair <int, int> ,vector<pair <int, int>  > ,greater< pair<int, int> > > q;

bool cmpx(node p, node q)
{return p.x < q.x;}
bool cmpy(node p, node q)
{return p.y < q.y;}

void add(int u, int v, int w)
{
	cnt ++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

void dij()
{
	memset(dis, 0x7f, sizeof(dis));
	dis[0] = 0;
	q.push(make_pair(0, 0));
	while(!q.empty())
	{
		int u = q.top().second;
		int d = q.top().first;
		q.pop(); 
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = edge[i].nxt)
		{
			int v = edge[i].to, w = edge[i].w;
			if(dis[v] > d + w)
			{
				dis[v] = d + w;
				q.push(make_pair(dis[v], v));
			}
		}
	}
	cout<<dis[m + 1];
}

signed main()
{
	cin>>n>>m;
	cin>>sx>>sy>>tx>>ty;
	for(int i = 1; i <= m; ++i)
	{
		cin>>t[i].x>>t[i].y;
		t[i].id = i;
	}
	sort(t + 1, t + m + 1, cmpx); 
	for(int i = 1; i <= m - 1; ++i)
		add(t[i].id, t[i + 1].id, t[i + 1].x - t[i].x),
		add(t[i + 1].id, t[i].id, t[i + 1].x - t[i].x);
	sort(t + 1, t + m + 1, cmpy);
	for(int i = 1; i <= m - 1; ++i)
		add(t[i].id, t[i + 1].id, t[i + 1].y - t[i].y),
		add(t[i + 1].id, t[i].id, t[i + 1].y - t[i].y);
	for(int i = 1; i <= m; ++i)
		add(0, t[i].id, min(abs(sx - t[i].x), abs(sy - t[i].y))),
		add(t[i].id, m + 1, abs(tx - t[i].x) + abs(ty - t[i].y));
	add(0,m+1, abs(sx - tx) + abs(sy - ty));
	dij();
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

和 [liuzhemin666](/user/361356) duel CF 2.3k 时候的题，先 Orz [liuzhemin666](/user/361356) 一眼秒了这题。

先考虑有 $3$ 个点 A、B、C 的情况，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/knanv4lb.png)

（长度为 $3$ 的红线应该是与 A 点重合的）

发现 A 到 B 的最短距离 $5$ 可以分解成 A 到 C 的最短距离加 C 到 B 的最短距离 $3+2=5$，所以如果存在 $A_x \leq C_x \leq B_x$ 且 $A_y \leq C_y \leq B_y$ 的 C 的话，那么 A 到 B 的最短路一定可以是经过 C 的。

事实证明，当经过 C 时，可能会更短，比如上图 C 是 $(3,4)$，则最短路是 $3+1=4$。

所以我们可以仅对 $x$ 接近的两个数连边，$y$ 接近的两个数连边，其中某两个点直接的中转点便是上图中的 C。

然后考虑初始和结束连一条边（最坏情况），然后再初始向 $m$ 个点连 $m$ 条边即可，$m$ 个点向结束的连 $m$ 条边。

总边数为 $6m-3$，$m=10^5$，Dijkstra 可以跑过。

```cpp
const int N=1e5+19;
struct node {
	int x, y, id;
} a[N];
typedef pair<int, int> pii;
#define mp make_pair
#define fi first
#define se second
vector<pii> g[N];
int dis[N], vis[N];
signed main() {
	for (int i=0;i<N;++i) dis[i]=1e18;
	int n,m,sx,sy,ex,ey;read(n,m,sx,sy,ex,ey);
	for (int i=1;i<=m;++i) read(a[i].x,a[i].y), a[i].id=i;
	sort(a+1,a+1+m,[](node x, node y){return x.x<y.x;});
	for (int i=1;i<m;++i) {
		g[a[i].id].emplace_back(mp(a[i+1].id,a[i+1].x-a[i].x));
		g[a[i+1].id].emplace_back(mp(a[i].id,a[i+1].x-a[i].x));
	}
	sort(a+1,a+1+m,[](node x, node y){return x.y<y.y;});
	for (int i=1;i<m;++i) {
		g[a[i].id].emplace_back(mp(a[i+1].id,a[i+1].y-a[i].y));
		g[a[i+1].id].emplace_back(mp(a[i].id,a[i+1].y-a[i].y));
	}
	for (int i=1;i<=m;++i) {
		g[m+1].emplace_back(mp(a[i].id,min(abs(sx-a[i].x),abs(sy-a[i].y))));
		g[a[i].id].emplace_back(mp(m+2,abs(ex-a[i].x)+abs(ey-a[i].y)));
	}
	g[m+1].emplace_back(mp(m+2,abs(sx-ex)+abs(sy-ey)));
	priority_queue<pii,vector<pii>,greater<pii> > q;
	q.push({0,m+1});
	dis[m+1]=0;
	while (!q.empty()) {
		pii u=q.top();
		q.pop();
		if (vis[u.se]) continue;
		vis[u.se]=1;
		for (const auto [i,j]:g[u.se]) {
			if (j+u.fi<dis[i]) {
				dis[i]=j+u.fi;
				q.push({dis[i],i});
			}
		}
	}
	write(dis[m+2],'\n');
	return 0;
}
```

---

## 作者：LionBlaze (赞：0)

注意到 $n \le 10^9$ 但是 $m \le 10^5$，考虑离散化相似思路——优化建图，减少点数和边数。

为了方便，我们把 Yura 的家看作是一个传送点，容易发现这样对答案不会有任何影响。在最优情况下，这个传送点不会被用到。

于是我们就可以定义两个传送点之间的距离为要从一个移动到另一个所需要的最少的步数。

显然，只有可能是往左/右然后 $x$ 坐标重合，或者往上/下然后 $y$ 坐标重合。

所以，两个传送点 $a=(x_1,y_1)$ 和 $b=(x_2,y_2)$ 之间的距离 $d(a,b)=\min\left(\lvert x_1-x_2 \rvert, \lvert y_1-y_2 \rvert\right)$。

注意到 $m \le 10^5$，这样建图的边数是 $\Theta(m^2)$ 的，无法通过。

然后我们注意到如果两个传送点之间是一直横着（假设是往右）走道的，那么显然可以走到横坐标位于它们之间的传送点，然后再走过去的。原理是若 $x\le y\le z$ 或 $x \ge y \ge z$，则 $\lvert z-x \rvert = \lvert z-y \rvert + \lvert y-x \rvert$。

故我们可以跑两次，第一次按照 $x$ 坐标排序然后相邻连边，第二次按照 $y$ 坐标排序然后相邻连边。

注意到假设 $(f_x,f_y)$ 是传送点对于答案是有影响的，所以可以枚举每一个传送点（包括家）然后统计直接走的答案（曼哈顿距离）。

最终有 $m$ 个点，$\Theta(m)$ 条边，于是二叉堆优化 Dijkstra 时间复杂度 $\mathcal O(m \log m)$，可以通过。

---

## 作者：Robin_kool (赞：0)

发现每分钟走一步是幌子，其实在没有传送点的情况下可以 $O(1)$ 计算时间。因此我们考虑对 $m$ 的传送点进行连边，但是 $m^2$ 条边交上去就会爆炸。

那么就优化建边，因为是瞬移到传送点，所以假如 $A$ 和 $C$ 之间有点 $B$，从 $A$ 到 $C$ 和从 $A$ 到 $B$ 再到 $C$ 是等价的。

有了这个思路，就不难想到进行两次排序，分别以横纵坐标为关键字，对于排序后相邻的两个点连一条**双向边**。定义起点编号为 $0$，终点编号为 $m+1$，最后再把所有的特殊点与这两个点连边，注意距离不要算错，一个是到传送点，一个是从传送点出发。

边建完后，跑一遍最短路就行了，**注意存边数组多开几倍**。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 10;
ll n, m, sx, sy, tx, ty, dis[N];
bool vis[N];
priority_queue<pair<int,int> > q;
vector<int> vec[N], g[N];
inline ll read(){
	ll x = 0, m = 1;
	char ch = getchar();
	while(!isdigit(ch)){
		if(ch == '-') m = -1;
		ch = getchar();
	}
	while(isdigit(ch)){
		x = (x << 1) + (x << 3) + (ch ^ 48);
		ch = getchar();
	}
	return x * m;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		write(-x);
		return;
	}
	if(x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
inline void add(int u, int v, int w){
	vec[u].push_back(v);
	g[u].push_back(w);
}
struct Code{
	int x, y, id;
}t[N];
inline bool cmp1(Code x, Code y){
	return x.x < y.x;
}
inline bool cmp2(Code x, Code y){
	return x.y < y.y;
}
inline void dij(){
	memset(dis, 0x7f, sizeof dis);
	dis[0] = 0;
	q.push(make_pair(0, 0));
	while(!q.empty()){
		int u = q.top().second, val = q.top().first * -1;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(int i = 0; i < vec[u].size(); ++ i){
			int v = vec[u][i];
			if(dis[v] > g[u][i] + val){
				dis[v] = g[u][i] + val;
				q.push(make_pair(-dis[v], v));
			}
		}
	}
	write(dis[m + 1]);
}
signed main(){
	//freopen("CF1422D.in", "r", stdin);
	//freopen("CF1422D.out", "w", stdout);
    n = read(), m = read();
	sx = read(), sy = read(), tx = read(), ty = read();
	for(int i = 1; i <= m; ++ i){
		t[i].x = read(), t[i].y = read();
		t[i].id = i;
	} 
	sort(t + 1, t + 1 + m, cmp1);
	for(int i = 1; i < m; ++ i){
		add(t[i].id, t[i + 1].id, t[i + 1].x - t[i].x);
		add(t[i + 1].id, t[i].id, t[i + 1].x - t[i].x);
	}
	sort(t + 1, t + 1 + m, cmp2);
	for(int i = 1; i < m; ++ i){
		add(t[i].id, t[i + 1].id, t[i + 1].y - t[i].y);
		add(t[i + 1].id, t[i].id, t[i + 1].y - t[i].y);
	}
	for(int i = 1; i <= m; ++ i){
		add(0, t[i].id, min(abs(t[i].x - sx), abs(t[i].y - sy)));
		add(t[i].id, m + 1, abs(tx - t[i].x) + abs(ty - t[i].y));
	}
	add(0, m + 1, abs(tx - sx) + abs(ty - sy));
	dij();
	return 0;
}

```


---

## 作者：wzy2021 (赞：0)

首先联想到最短路，

以每个转折点为顶点，两两连一条边，再加上起点与终点，就可以了。

但这样边数至少有 $O(m^2)$，会爆炸，

考虑优化：我们直连一个点与它上下左右相邻最近的点就行了，

举个例子：

有三个转折点：$A(1, 2)$，$B (3, 3)$，$C (4, 7)$，要从 $A$ 走到 $C$,

1. 直接走：花费 $3$ 的代价

2. 先走 $B$，在走 $C$，花费 $2 + 1 = 3$ 的代价

两种走法一样，就可以不连 $AC$ 这条边。

而 $B$ 更接近于 $A$。

四个方向，有 $O (4m)$ 条边，加上起点与终点，共 $O(6m + 1)$ 条边，

最短路大家都很熟，这里不讲了。

~~~cpp
#include <queue> 
#include <cstdio>
#include <iostream>
#include <algorithm> 
using namespace std;
#define int long long

const int N = 1e5 + 10;
const int inf = (1 << 30);

struct node {
	int x, y, id;
} t[N];

struct Node {
	int w, to, nxt;
} edge[N << 3];
int cnt, head[N];

int n, m;
int sx, sy, tx, ty;

int dis[N];
bool vis[N];

priority_queue <pair <int, int> > q;

bool cmpx (node p, node q) {
	return p.x < q.x;
}

bool cmpy (node p, node q) {
	return p.y < q.y;
}

void add (int u, int v, int w) {
	cnt ++;
	edge[cnt].w = w;
	edge[cnt].to = v;
	edge[cnt].nxt = head[u];
	head[u] = cnt;
}

void dij () { // 最短路
	memset (dis, 0x7f, sizeof (dis));
	dis[0] = 0;
	q.push (make_pair (0, 0));
	while (!q.empty()) {
		int u = q.top().second; int d = -q.top().first; q.pop(); // 由于是大根堆，所以取负的存，使得小的先
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = head[u]; i; i = edge[i].nxt) {
			int v = edge[i].to, w = edge[i].w;
			if (dis[v] > d + w) {
				dis[v] = d + w;
				q.push (make_pair (-dis[v], v));
			}
		}
	}
	printf ("%d", dis[m + 1]);
}

int main() {
	scanf ("%d%d", &n, &m);
	scanf ("%d%d%d%d", &sx, &sy, &tx, &ty);
	for (int i = 1; i <= m; ++i) {
		scanf ("%d%d", &t[i].x, &t[i].y); t[i].id = i;
	}
	sort (t + 1, t + m + 1, cmpx); // 按照 x 轴排序，保证在 x 轴情况下，最接近
   	for (int i = 1; i <= m - 1; ++i) {
		add (t[i].id, t[i + 1].id, t[i + 1].x - t[i].x);
		add (t[i + 1].id, t[i].id, t[i + 1].x - t[i].x);
	}
	sort (t + 1, t + m + 1, cmpy); // 同上，按 y 轴排序
	for (int i = 1; i <= m - 1; ++i) {
		add (t[i].id, t[i + 1].id, t[i + 1].y - t[i].y);
		add (t[i + 1].id, t[i].id, t[i + 1].y - t[i].y);
	}
	for (int i = 1; i <= m; ++i) {
		add (0, t[i].id, min (abs (sx - t[i].x), abs (sy - t[i].y)));
		add (t[i].id, m + 1, abs (tx - t[i].x) + abs (ty - t[i].y));
	}
	add (0, m + 1, abs (sx - tx) + abs (sy - ty));
	dij ();
	return 0;
}
~~~

---

## 作者：FutaRimeWoawaSete (赞：0)

首先拿到这道题，切比雪夫距离？然后最短路，然后这给的 $1e5$ 个点还让我求最短路，再一算，貌似这个 $m ^ 2$ 建图要爆，然后自然而然就想到了优化建图。            

首先我们可以先想个问题：这道题是否有无用边？很明显对于一道蓝题而言优化建图的东西不可能来一个线段树优化建图之类的难码东西(更何况这是个 $D$ )，所以我们完全可以从无用边的角度来优化建图。       

观察到如果我们从 $x1$ 走到 $x2$ ，如果中间有传送点 $x3$ 的话我完全可以先走到 $x3$ 然后再走到 $x2$ 去，至少这是不劣的。      

于是我们根据 $x$ 坐标排序然后两两连边，接着根据 $y$ 坐标排序然后两两连边，最后跑一个 $Dij$ 即可。           

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int Len = 5e5 + 5;
const long long Inf = 1e18; 
bool f[Len];
int n,m,s,t,cnt,head[Len];
long long dis[Len];
bool flag[Len];
struct node
{
	int next,to;
	long long w;	
}edge[Len << 1];
struct Node
{
	int x;
	long long Dis;
	bool operator < (const Node &Ano) const
	{
		return Dis > Ano.Dis;
	}
}P,C;
void add(int from,int to,long long w)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	edge[cnt].w = w;
	head[from] = cnt;
}
void Dij()
{
	priority_queue<Node> q;
	for(int i = 1 ; i <= m ; i ++) dis[i] = Inf , f[i] = false;
	dis[t] = Inf , f[t] = false;
	dis[s] = 0 , f[s] = false;
	P.x = s , P.Dis = 0;
	q.push(P);
	while(!q.empty())
	{
		P = q.top() ; q.pop();
		if(P.x == t) 
		{
			printf("%lld\n",P.Dis);
			return;
		}
		if(!f[P.x])
		{
			f[P.x] |= 1;
			for(int e = head[P.x] ; e ; e = edge[e].next)
			{
				int to = edge[e].to;
				if(dis[to] > dis[P.x] + edge[e].w)
				{
					dis[to] = dis[P.x] + edge[e].w;
					if(!f[to])
					{
						C.x = to , C.Dis = dis[to];
						q.push(C);
					}
				}
			}
		}
	}
	printf("%lld\n",dis[t]);
} 
struct Point
{
	int x,y,id;
}PPt[Len],S,T;
bool cmt(Point x,Point y){return x.x < y.x;}
bool cmq(Point x,Point y){return x.y < y.y;}
long long ddis(Point x,Point y){return min(abs(x.x - y.x) , abs(x.y - y.y));}
long long DDis(Point x,Point y){return abs(x.x - y.x) + abs(x.y - y.y);}
signed main()
{
	scanf("%lld %lld",&n,&m);
	s = m + 1 , t = m + 2;
	scanf("%lld %lld %lld %lld",&S.x,&S.y,&T.x,&T.y);
	S.id = m + 1 , T.id = m + 2;
	for(int i = 1 ; i <= m ; i ++) 
	{
		scanf("%lld %lld",&PPt[i].x,&PPt[i].y);
		PPt[i].id = i;
		add(PPt[i].id , S.id , ddis(PPt[i] , S));
		add(S.id , PPt[i].id , ddis(PPt[i] , S));
		add(PPt[i].id , T.id , DDis(PPt[i] , T));
		add(T.id , PPt[i].id , DDis(PPt[i] , T));
	}
	add(S.id , T.id , DDis(S , T));
	sort(PPt + 1 , PPt + 1 + m , cmt);
	for(int i = 1 ; i <= m ; i ++)
	{
		if(i != 1)
		{
			add(PPt[i].id , PPt[i - 1].id , ddis(PPt[i] , PPt[i - 1]));
			add(PPt[i - 1].id , PPt[i].id , ddis(PPt[i] , PPt[i - 1]));
		}
	}
	sort(PPt + 1 , PPt + 1 + m , cmq);
	for(int i = 1 ; i <= m ; i ++)
	{
		if(i != 1)
		{
			add(PPt[i].id , PPt[i - 1].id , ddis(PPt[i] , PPt[i - 1]));
			add(PPt[i - 1].id , PPt[i].id , ddis(PPt[i] , PPt[i - 1]));
		}
	}
	Dij();
	return 0;
}
```

---

