# [ABC362D] Shortest Path 3

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc362/tasks/abc362_d

$ N $ 頂点 $ M $ 辺の単純連結無向グラフが与えられます。頂点 $ i\,(1\leq\ i\ \leq\ N) $ は重み $ A_i $ を持ちます。また、辺 $ j\,(1\leq\ j\ \leq\ M) $ は頂点 $ U_j,V_j $ を双方向に結び、重み $ B_j $ を持ちます。

このグラフ上のパスの重みを、パス上に現れる頂点の重みと辺の重みの総和と定義します。

各 $ i=2,3,\dots,N $ について、以下の問題を解いてください。

- 頂点 $ 1 $ から頂点 $ i $ までのパスであって、重みが最小となるものの重みを求めよ。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ N-1\ \leq\ M\ \leq\ 2\ \times\ 10^5 $
- $ 1\ \leq\ U_j\ <\ V_j\ \leq\ N $
- $ i\neq\ j $ なら $ (U_i,V_i)\ \neq\ (U_j,V_j) $
- グラフは連結である
- $ 0\ \leq\ A_i\ \leq\ 10^9 $
- $ 0\ \leq\ B_j\ \leq\ 10^9 $
- 入力はすべて整数
 
### Sample Explanation 1

頂点 $ 1 $ から頂点 $ 2 $ へのパスを考えます。 パス $ 1\ \to\ 2 $ の重みは $ A_1+B_1+A_2=1+1+2=4 $、パス $ 1\ \to\ 3\ \to\ 2 $ の重みは $ A_1+B_2+A_3+B_3+A_2=1+6+3+2+2=14 $ であり、最小の重みは $ 4 $ です。 頂点 $ 1 $ から頂点 $ 3 $ へのパスを考えます。 パス $ 1\ \to\ 3 $ の重みは $ A_1+B_2+A_3=1+6+3=10 $、パス $ 1\ \to\ 2\ \to\ 3 $ の重みは $ A_1+B_1+A_2+B_3+A_3=1+1+2+2+3=9 $ であり、最小の重みは $ 9 $ です。

### Sample Explanation 3

答えが 32-bit 整数に収まらないことがあることに注意してください。

## 样例 #1

### 输入

```
3 3
1 2 3
1 2 1
1 3 6
2 3 2```

### 输出

```
4 9```

## 样例 #2

### 输入

```
2 1
0 1
1 2 3```

### 输出

```
4```

## 样例 #3

### 输入

```
5 8
928448202 994752369 906965437 942744902 907560126
2 5 975090662
1 2 908843627
1 5 969061140
3 4 964249326
2 3 957690728
2 4 942986477
4 5 948404113
1 3 988716403```

### 输出

```
2832044198 2824130042 4696218483 2805069468```

# 题解

## 作者：_zqh_ (赞：4)

> 涉及芝士点：最短路。

如果把点权去掉，本题就是一个彻头彻尾的单源最短路问题；

那么就考虑将点权转到边权上。

更新一条边的时候，有两个端点 $u, v$，设我们从 $u$ 转到 $v$，那我们在更新 $dst_v$ 的时候可以将点权和边权一起加上：

$$
dst_v = dst_u + pval_v + eval_{u,v}
$$

这里 $pval$ 代表点权，$eval$ 代表边权。

而这里不更新 $pval_u$ 的原因是上次更新 $dst_u$ 的时候已经更新过了。

### Code

好吧，连我自己都搞不清楚这到底是 SPFA 还是 BFS。

#### 注意事项

- 不要用标记数组。
- 最开始赋初值时要将 $dst_1$ 赋值成 $pval_1$ 而不是 $0$。

```cpp
#include <bits/stdc++.h>
// #pragma GCC optimize(2)
#define int long long
#define pii pair<int, int>
#define piiii pair<pii, pii>
#define il inline
#define p_q priority_queue
#define u_m unordered_map
#define bt bitset
#define rg register
#define rd Nothing::read
#define wt Nothing::write
#define endl '\n'

using namespace std;

namespace Nothing {
il int read() {
    int f = 1, t = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        t = t * 10 + ch - '0';
        ch = getchar();
    }
    return t * f;
}

il void write(int x, bool s) {
    if (x < 0) {
        putchar('-');
        write(-x, false);
        return;
    }
    if (!s && x == 0)
        return;
    if (s && x == 0) {
        putchar('0');
        return;
    }
    write(x / 10, false);
    putchar(x % 10 + '0');
}
}  // namespace Nothing

const int N1 = 300005;
const int N2 = 1000006;
const int Mod = 998244353;

namespace COMB {
int fac[N2] = {0};
il void Cinit(int p) {
    fac[0] = 1;
    for (int i = 1; i < N2; i++) {
        fac[i] = fac[i - 1] * i % p;
    }
}
il int qpow(int a, int b, int p) {
    int ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * a % p;
        }
        a = a * a % p;
        b >>= 1;
    }
    return ans;
}
il int C(int n, int m, int p) {
    if (m > n || m < 0) {
        return 0;
    }
    return fac[n] * qpow(fac[m], p - 2, p) % p * qpow(fac[n - m], p - 2, p) % p;
}
il int Lucas(int n, int m, int p) {
    if (!m)
        return 1;
    return (C(n % p, m % p, p) * Lucas(n / p, m / p, p)) % p;
}
il int GCD(int n, int m, int p) {
    return __gcd(n, m) % p;
}
il int LCM(int n, int m, int p) {
    return n * m % p * qpow(GCD(n, m, p), p - 2, p) % p;
}
}  // namespace COMB
using namespace COMB;
using namespace Nothing;

// #define debug 1
// #define multi_test 1
#define IOS 1

int T = 1;

int n, m;

int val[200005];

bool vis[200005];//赛时太急，这个数组没啥用

vector<pii> G[200005];

int Dist[200005];

void Bfs(int Stt) {
    memset(Dist, 0x3f, sizeof(Dist));
    queue<int> q;
    q.push(Stt);
    Dist[Stt] = val[Stt];
    while (q.size()) {
        int tmp = q.front();
        q.pop();
        vis[tmp] = true;
        for (pii x : G[tmp]) {
            if (Dist[x.first] > Dist[tmp] + val[x.first] + x.second) {
                Dist[x.first] = Dist[tmp] + val[x.first] + x.second;
                q.push(x.first);
            }
        }
    }
}

void Init() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    Bfs(1);
    for (int i = 2; i <= n; i++) {
        cout << Dist[i] << " ";
    }
    return;
}

void Solve() {
    
    return;
}

signed main() {
#ifdef IOS
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif
#ifdef debug
    freopen("zqh.in", "r", stdin);
    freopen("zqh.out", "w", stdout);
#endif
#ifdef multi_test
    cin >> T;
#endif
    while (T--) {
        Init();
        Solve();
    }
    return 0;
}
/*

*/
```

---

## 作者：qhr2023 (赞：2)

## solution

最短路板子题，考虑迪杰斯特拉算法，我们只需要对边权处理一下即可。

举个例子，有 $A$、$B$、$C$ 三点，$A$ 和 $B$、$B$ 和 $C$ 之间各有一条无向边，这条 $A$ 到 $C$ 路径的路径权就等于三个点的点权加两条边的边权，如果我们把每条边的边权变成边权加上指向点的点权，那么路径权就可以看成起始点 $A$ 的点权加两条边权，这样就成了正权单源最短路板子了。

实现的话，把起始值设为起始点权，套模板就可以了，结合代码食用。

## code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 200005
using namespace std;
int n, m, u, v, w, a[N];
struct edge { ll v, w; };
vector<edge> e[N];
long long dis[N];
bool vis[N];
struct node{
	ll u, dis;
	bool operator<(const node &b) const { return dis>b.dis; }
};
void dij () {
	memset(dis, 0x3f, sizeof dis);
	priority_queue<node> q;
	q.push({1, a[1]});
	while (q.size()) {
		ll u=q.top().u, d=q.top().dis;
		q.pop();
		if (vis[u])
			continue;
		vis[u]=1;
		dis[u]=d;
		for (auto i:e[u])
			if (dis[i.v]>i.w+d)
				dis[i.v]=i.w+d,
				q.push({i.v, dis[i.v]});
	}
}
int main(){
	cin >> n >> m;
	for (int i=1; i<=n; i++)
		cin >> a[i];
	while (m--) 
		cin >> u >> v >> w,
		e[u].push_back({v, w+a[v]}),
		e[v].push_back({u, w+a[u]});
	dij();
	for (int i=2; i<=n; i++)
		cout << dis[i] << ' ';
	return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

简单最短路。迪杰斯特拉板子上松弛加一个点权就好了，挺简单的一道 D。~~感觉比 C 简单~~。

松弛部分代码可以看看：
```cpp
for(int i=head[u];i;i=edge[i].nxt){
	if(!vis[edge[i].to] and dis[edge[i].to]>dis[u]+edge[i].val+a[edge[i].to]){
    	dis[edge[i].to]=dis[u]+edge[i].val+a[edge[i].to];
    	q.push(make_pair(dis[edge[i].to],edge[i].to));
	}
}
```

提醒三点：
1. 开 `long long`！
2. 无向图，数组开够！
3. 初始化要给 $dis_1$ 赋值为 $a_1$！

[放个代码](https://atcoder.jp/contests/abc362/submissions/55537378)

---

## 作者：D0000 (赞：0)

[模板单源最短路](https://www.luogu.com.cn/problem/P3371)？

啥？点权是什么？

其实只需要进行略微操作，其实一个从 $u$ 到 $v$ 长度为 $w$ 的边的边权可以看作 $w$ 加上 $v$ 的点权，因为如果经过这条边一定会经过 $v$。

最后记得加上起点 $1$ 的点权。

---

## 作者：nightwatch.ryan (赞：0)

### 思路
最短路板子。

先建个无向图，然后将从顶点 $1$ 到其他所有点的最短路径权重设为一个很大的值。这里用 $dis$ 数组来存储顶点 $1$ 到其他所有点的最短路径权重。

接下来我们用 Dijkstra 算法来求顶点 $1$ 到其他所有点的最短路径权重。本题解使用优先队列优化的 Dijkstra。

优先队列将所有顶点的权重从小到大排序。

如果优先队列不为空，取出顶端元素，将当前顶点的权重设为 $w$，将当前顶点设为 $u$。如果 $w$ 大于目前已知的最短路径权重，也就是 $dis_u$，那么跳过。

遍历当前顶点的所有邻接顶点，设当前遍历到的邻接顶点是 $v$，计算从顶点 $1$ 到顶点 $v$ 的路径权重，设这个值为 $nxt$，如果 $nxt$ 小于 $dis_v$，则将 $dis_v$ 更新为 $nxt$，并且将 $nxt$ 和 $v$ 加入优先队列。

最后，输出 $dis$ 数组。
### 代码
```cpp
#include<iostream>
#include<climits>
#include<queue>
#define int long long
#define pii std::pair<int,int>
#define N 400005
struct Node{
	int to,far;
};
int a[N],dis[N];
signed main(){
	int n,m;
	std::cin>>n>>m;
	std::vector<std::vector<Node>>G(n+1);
	for(int i=1;i<=n;i++)std::cin>>a[i];
	for(int i=1;i<=m;i++){
		int u,v,w;
		std::cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	std::priority_queue<pii,std::vector<pii>,std::greater<pii>>q;
	for(int i=0;i<=n;i++)dis[i]=LLONG_MAX;
	q.push({a[1],1}),dis[1]=a[1];
	while(q.size()){
		pii pr=q.top();
		int w=pr.first;
		int u=pr.second;
		q.pop();
		if(w>dis[u])continue;
		for(auto i:G[u]){
			int v=i.to,nxt_u=w+i.far+a[v];
			if(nxt_u<dis[v]){
				dis[v]=nxt_u;
				q.push({nxt_u,v});
			}
		}
	}
	for(int i=2;i<=n;i++)std::cout<<dis[i]<<" ";
}
```

---

## 作者：stripe_python (赞：0)

D 最板子的一集。

点权和边权都是非负数，考虑堆优化 Dijkstra。

考虑 Dijkstra 的原松弛过程，从 $u$ 到 $v$ 的路径长为 $w+a_v$。然后打一遍板子即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define N 200005
#define int long long

int a[N];
int tot = 0, head[N];
struct Edge {
	int next, to, dis;
} edge[N << 1];
inline void add_edge(int u, int v, int w) {
	edge[++tot].next = head[u], edge[tot].to = v, edge[tot].dis = w, head[u] = tot;
}

int n, m, u, v, w;

namespace Dijkstra {
	struct node {
		int to, dis;
		node() : to(0), dis(0) {}
		node(int x, int y) : to(x), dis(y) {}
		
		bool operator< (const node& other) const {
			return dis > other.dis;
		}
	};
	priority_queue<node> q;
	int dis[N];
	
	inline void dijkstra(int s) {
		memset(dis, 0x3f, sizeof(dis));
		dis[s] = a[s];   // 加上源点的点权
		q.emplace(s, a[s]);
		while (!q.empty()) {
			int u = q.top().to, d = q.top().dis;
			q.pop();
			if (d != dis[u]) continue;
			for (int j = head[u]; j != 0; j = edge[j].next) {
				int v = edge[j].to, w = edge[j].dis;
				if (dis[v] > dis[u] + a[v] + w) {
					dis[v] = dis[u] + a[v] + w;
					q.emplace(v, dis[v]);
				}
			}
		}
	}
}

void _main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= m; i++) {
		cin >> u >> v >> w;
		add_edge(u, v, w), add_edge(v, u, w);
	}
	Dijkstra::dijkstra(1);
	for (int i = 2; i <= n; i++) cout << Dijkstra::dis[i] << ' ';
} signed main() { 
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	
	_main();
	return 0;
}
```

---

## 作者：Special_Tony (赞：0)

# 思路
[双倍经验](/problem/P4779)。

显然，经过一条 $u\to v$ 且边权为 $w$ 的边后，代价一定是 $w+a_v$。而初始就经过 $1$ 号点，所以 $dis_1=a_1$，然后跑一遍 dijkstra 模板就行了。注意此题是双向边。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
struct node {
	int x;
	ll dis;
	bool operator < (const node& t) const {
		return dis > t.dis;
	}
} t;
const ll inf = 1e18;
int n, m, a[200005], x, y, z;
ll d[200005];
vector <pii> v[200005];
priority_queue <node> q;
void dij () {
	fill (d + 2, d + 1 + n, inf);
	q.push ({1, d[1] = a[1]});
	while (! q.empty ()) {
		t = q.top ();
		q.pop ();
		if (t.dis > d[t.x])
			continue ;
		for (const pii& i : v[t.x])
			if (d[i.first] > t.dis + i.second)
				q.push ({i.first, d[i.first] = t.dis + i.second});
	}
	return ;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i];
	while (m --)
		cin >> x >> y >> z, v[x].emplace_back (y, z + a[y]), v[y].emplace_back (x, z + a[x]);
	dij ();
	for (int i = 2; i <= n; ++ i)
		cout << d[i] << ' ';
	return 0;
}
```

---

## 作者：xixisuper (赞：0)

# AT_abc362_d	[ABC362D] Shortest Path 3 题解

典，感觉中上等黄或下等绿顶天了。

本题解采用分层图最短路算法。

## 思路

看到最短路，想都不用想直接套上 Dijkstra，问题在于怎样处理点权。

我们考虑分层，把整个图分成两层。对于点 $i$ 的点权 $A_i$，我们可以等价看作上层的节点 $i$ 向下层的节点 $i$ 连一条边权为 $A_i$ 的单向边。

对于不同点之间的连边，我们这样处理：假设点 $u$ 与点 $v$ 之间有一条边权为 $w$ 的无向边，我们考虑将下层的点 $u$ 向上层的点 $v$ 连一条边权为 $w$ 的单向边，同时将下层的点 $v$ 向上层的点 $u$ 连一条边权为 $w$ 的单向边。

进行这样的分层之后，我们发现，上层的点只能向下层的相同点走，而下层的点只能通向上层，这样每经过一个点，必然会增加上对应的点权，而最后只需输出上层 $1$ 号点到下层 $i$ 号点的最短路径即可。

## 代码

8 min 码出来的，觉得码风较丑的请见谅。

```cpp
#include <iostream>
#include <queue>
#include <vector> 
#define ll long long
using namespace std;
const ll N=2e5+10;
ll n,m,head[N<<1],tot,dis[N<<1];
struct EdgE{ll v,w,nxt;}edge[N<<2];
bool vis[N<<1];
inline void add_edge(ll from,ll to,ll len){
	edge[++tot].v=to;
	edge[tot].nxt=head[from];
	edge[tot].w=len;
	head[from]=tot;
}
ll x,y,z;
struct node{
	ll id,len;
	friend bool operator >(const node &a,const node &b){
		return a.len>b.len;
	}
};
priority_queue<node,vector<node>,greater<node> > q;
void dij(){
	node now;
	now.id=1,now.len=0;
	q.push(now);
	while(!q.empty()){
		now=q.top();
		q.pop();
		if(vis[now.id]) continue;
		vis[now.id]=1;
		dis[now.id]=now.len;
		for(ll i=head[now.id];i;i=edge[i].nxt){
			ll v=edge[i].v;
			if(vis[v]) continue;
			node pu;
			pu.id=v,pu.len=now.len+edge[i].w;
			q.push(pu);
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(ll i=1;i<=n;i++){
		cin>>x;
		add_edge(i,i+n,x);
		//上层点向下层点连边
	}
	for(ll i=1;i<=m;i++){
		cin>>x>>y>>z;
		add_edge(x+n,y,z);
		add_edge(y+n,x,z);
		//下层点向上层点连边
	}
	dij();
	for(ll i=2;i<=n;i++) cout<<dis[i+n]<<' ';
	return 0;
}
```

---

## 作者：xxboyxx (赞：0)

### 翻译

给你一个简单连接的无向图，有 $N$ 个顶点和 $M$ 条边。每个顶点与边都有权重。

该图中路径的权重定义为路径上出现的顶点和边的权重之和。

针对每个 $i=2,3,\dots,N$，找出从顶点 $1$ 到顶点 $i$ 的路径的最小权重。

### 思路

一看就是单源最短路，但是这道题有了点权，所以，我们就需要将点权算在边权上，然后跑 dijkstra。其实从一个点到另一个点除了出发点就是边权加**到达点点权**，那么最后计算时需要加上出发点的点权。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node
{
	int x,y;
	bool operator <(const node & a) const
	{
		return y>a.y;
	}
};
priority_queue<node> q;
int n,m;
int a[200005];
vector<int> g[200005];
vector<int> v[200005];
int ans[200005];
int f[200005];
signed main()
{
	cin>>n>>m;
	for (int i=1;i<=n;i++)
		cin>>a[i];
	for (int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		g[x].push_back(y);
		g[y].push_back(x);
		v[x].push_back(a[y]+z);//边权加到达点点权
		v[y].push_back(a[x]+z);//同上 
	}
	for (int i=1;i<=n;i++)
		ans[i]=1e18;//这里一定要开大点！ 
	ans[1]=0;
	node k;
	k.x=1,k.y=0;
	q.push(k);
	while (!q.empty())//跑dijkstra
	{
		int x=q.top().x;
		q.pop();
		if (f[x]==0)
		{
			f[x]=1;
			int l=g[x].size();
			for (int i=0;i<l;i++)
			{
				int t=g[x][i];
				if (ans[x]+v[x][i]<ans[t])
				{
					ans[t]=ans[x]+v[x][i];
					node y;
					y.x=t,y.y=ans[t];
					q.push(y);
				}
			}
		}
	}
	for (int i=2;i<=n;i++)
		cout<<ans[i]+a[1]<<' ';//加上出发点点权 
	return 0;
}
```

---

## 作者：jiangruibo (赞：0)

### 思路：
这题是一道**最短路**的板题，题目做了些改变，加上了**点权**，且是**无向图**，那我们很容易就能想到在建边时按**边权**加上所到的**那个点的点权**去算，因为是无向图，所以需要**正向反向各建一次**，跑完一遍最短路后，输出答案得加上一个起点的点权即可。

### 代码：
```
#include <bits/stdc++.h>
#define int long long
#define endl "\n"
#define ull unsigned long long
typedef long long LL;
using namespace std;

int fr[1000010],to[1000010];
int nex[1000010],v[1000010],tl,d[1000010];
bool b[1000010];
void add(int x,int y,int w)
{
    to[++tl]=y;
    v[tl]=w;
    nex[tl]=fr[x];
    fr[x]=tl;
}
priority_queue<pair<int,int>> q;

int a[1000010];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
    int n,m,s;
    cin>>n>>m;
    s=1;
    for(int i=1;i<=n;i++)
    {
    	cin>>a[i];
	}
    for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
        add(x,y,z+a[y]);
        add(y,x,z+a[x]);
    }
    for(int i=1;i<=n;i++) 
	{
		d[i]=1e18;
	}
    d[s]=0;
    q.push(make_pair(0,s));
    while(!q.empty())
	{
        int x=q.top().second;
        q.pop(); 
        if(b[x]) continue;
        b[x]=1;
        for(int i=fr[x];i;i=nex[i])
		{
            int y=to[i],l=v[i];
            if(d[y]>d[x]+l)
			{
                d[y]=d[x]+l;
                q.push(make_pair(-d[y],y));
            }
        }
    }
    for(int i=2;i<=n;i++) 
	{
		cout<<d[i]+a[1]<<" ";
	}
    return 0;
}
```

---

## 作者：Public_leda_team (赞：0)

对于这道题，我们要改造普通的最短路算法。

我们发现，走到 $1$ 号节点的权值之和就是 $A_1$，那么在执行最短路的过程中，我们考虑将边权和点权都算进去，这样就可以满足题目的要求。建图时把 $(U_i, V_i, B_i)$ 加入图中就行了。

[Submission Link.](https://atcoder.jp/contests/abc362/submissions/55552028)

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc362_d)

## 思路

解法正如题名所说，跑一遍最短路即可。由于是单源的最短路，所以我们选择 dijkstra 算法求解。

- 记得开 long long。

- 记得把点权和边权一块算上，**初始点也算**。

- 一定要标点（用布尔数组），否则会超过时限。

之后就是最短路的板子了。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pli pair<ll,int>
#define fi first
#define se second
using namespace std;
ll read(){//快读。
	ll k=0,flag=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')flag=-1;c=getchar();}
	while(c>='0'&&c<='9'){k=(k<<1)+(k<<3)+(c^48);c=getchar();}
	return k*flag;
}
const int N=2e5+10;
int n,m;
ll a[N],dis[N];
vector<pli>g[N];
bool vis[N];
priority_queue<pli,vector<pli>,greater<pli>>q;//记得把大根堆转为小根堆。
void dij(int s){
	memset(dis,0x7f,sizeof(dis));//赋个极大值方便求最短。
	dis[s]=a[s];
	q.push({0,s});
	while(q.size()){
		pli now=q.top();
		q.pop();
		if(vis[now.se])continue;
		vis[now.se]=1;
		for(auto i:g[now.se]){
			if(dis[i.se]>dis[now.se]+i.fi+a[i.se]){
				dis[i.se]=dis[now.se]+i.fi+a[i.se];
				q.push({dis[i.se],i.se});
			}
		}
	}
	return ;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		ll w=read();
		g[u].pb({w,v});
		g[v].pb({w,u});
	}
	dij(1);
	for(int i=2;i<=n;++i)printf("%lld ",dis[i]);
	return 0;
}
```

[AC 记录](https://atcoder.jp/contests/abc362/submissions/55534316)

---

## 作者：luobotianle (赞：0)

单源最短路变体。

计算点权只需要在松弛时加上目标点的点权即可。

本题不卡 SPFA，~~但最好不要使用已死算法解题。~~

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+5;
ll n,m,a[N],dis[N],vis[N];
struct edge{
	int next,to,w;
}e[N*2];
int h[N],cnt;
void add(int u,int v,int w){
	e[++cnt]={h[u],v,w};
	h[u]=cnt;
}
struct node{
	ll val,u;
	bool operator < (const node &a)const{
		return val>a.val;
	}
};
void dij(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=a[s];
	priority_queue<node> q;
	q.push({a[s],s});
	while(!q.empty()){
		int u=q.top().u;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].next){
			int to=e[i].to;
			if(dis[to]>dis[u]+e[i].w+a[to]){
				dis[to]=dis[u]+e[i].w+a[to];
				if(!vis[to]){
					q.push({dis[to],to});
				}
			}
		}
	}
}
void spfa(int s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=a[s];
	vis[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=h[u];i;i=e[i].next){
			int to=e[i].to;
			if(dis[to]>dis[u]+e[i].w+a[to]){
				dis[to]=dis[u]+e[i].w+a[to];
				if(!vis[to]){
					q.push(to);
					vis[to]=1;
				}
			}
		}
		vis[u]=0;
	}
} 
main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1,u,v,w;i<=m;i++){
    	cin>>u>>v>>w;
    	add(u,v,w);
    	add(v,u,w);
	}
	dij(1); 
//	spfa(1);
	for(int i=2;i<=n;i++)cout<<dis[i]<<" ";
    return 0;
}
```

---

## 作者：Network_Flow (赞：0)

### 题意：
给你一张无向图，每条边，每个点有一个权值，求从点 $1$ 到其他每个点的权值最小值。
### 做法：
因为没有负边，所以可以采用 Dijkstra.

你还不会 Dijkstra？出门左转 [P4779](https://www.luogu.com.cn/problem/P4779)。

原来的 Dijkstra 每次是加上一条边的边权，取最小值，因为经过了一个点对应的边，这个点也必定要经过，所以直接将原来的 $dis_{p.to}=\min\{dis_{pos}+p.w\}$ 改成 $dis_{p.to}=\min\{dis_{pos}+p.w+W_{p.to}\}$ （其中 $p.to$ 标志接下来要去到的点，$p.w$ 表示边的边权, $W$ 数组表示点权）即可通过。

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <climits>
#define int long long
#define SIZE 200005

using namespace std;
int n, m, head[SIZE], nxt[2*SIZE], ver[2*SIZE], deg[SIZE], dis[SIZE], tot, edge[SIZE], w[SIZE];
struct EdgeInfo{
	int to, w;
};
struct Msg{
	int pos, t;
	friend bool operator <(const Msg &a, const Msg &b){
		return a.t>b.t;
	}
};
vector<EdgeInfo> e[200005];
priority_queue<Msg> q;
void dij(){
	dis[1]=w[1];
	q.push({1, w[1]});
	while(!q.empty()){
		int pos=q.top().pos, curTime=q.top().t;
		q.pop();
		if(curTime!=dis[pos]) continue;
		for (auto &p:e[pos]){
			if(dis[p.to]>dis[pos]+p.w+w[p.to]){
				dis[p.to]=dis[pos]+p.w+w[p.to];
				q.push({p.to, dis[p.to]});
			}
		}
	}
	return;
}
signed main(){
	scanf("%lld%lld", &n, &m);
	for (int i=1; i<=n; i++){
		dis[i]=LLONG_MAX;
		scanf("%lld", &w[i]);
	}
	for (int i=1; i<=m; i++){
		int u, v, w;
		scanf("%lld%lld%lld", &u, &v, &w);
		e[u].push_back({v, w});
		e[v].push_back({u, w});
	}
	dij();
	for (int i=2; i<=n; i++) printf("%lld ", dis[i]);
	
	return 0;
}
```

---

## 作者：Hughpig (赞：0)

还是用 $\text{Dijkstra}$ 算法求最短路，但是由点 $u$ 到点 $v$ 的距离要改为 $w+A_v$（$w$ 为边权）。

注意最短路径上会计算 $1$ 号点的点权，所以到 $1$ 号点的最短路径应该设为 $A_1$。

代码：

```cpp
/*
*Author: Hughpig
*made in China
*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define up(l,r,i) for(int i=(l);(i)<=(r);++i)
#define pii pair<ll,ll>
#define pb emplace_back 

constexpr int N=2e5+9;

ll n,m,a[N],dis[N];
bool vis[N];
vector<pii> G[N];

struct node{
	ll dis,p;
	friend bool operator <(node a,node b){
		return a.dis>b.dis;
	}
};

priority_queue<node> pq;

void dijkstra(){
	pq.push((node){a[1],1});
	while(pq.size()){
		auto tmp=pq.top();pq.pop();
		int u=tmp.p;if(vis[u])continue;
		vis[u]=1;
		for(auto [v,w]:G[u]){
			if(dis[v]>dis[u]+w+a[v]){
				dis[v]=dis[u]+w+a[v];
				if(!vis[v])pq.push((node){dis[v],v});
			}
		}
	}
}

int main()
{
    cin>>n>>m;
    up(1,n,i)cin>>a[i];
    up(1,m,i){
    	ll u,v,w;cin>>u>>v>>w;
    	G[u].pb(make_pair(v,w));
    	G[v].pb(make_pair(u,w));
	}
	up(1,n,i)dis[i]=1e18;
	dis[1]=a[1];
	dijkstra();
	up(2,n,i)cout<<dis[i]<<' ';
	return 0;
}
```

---

## 作者：39xiemy (赞：0)

## 题目大意

现给出一个有 $N$ 个顶点和 $M$ 条边的连通无向图，每个点都有一个权值 $A_i$，每条边都有一个权值 $B_i$。对于每个 $i = 2 , 3 ,\dots ,N$，输出从点 $1$ 到点 $i$ 的路径的最小权值和，注意起点和终点的权值也计算在内。

## 分析

是最短路模板题。

由于这道题没有负权边，可以直接用 Dijkstra 算法来做。初始化时，将 $dis_1$ 赋值为 $A_1$，在计算过程中，将点的权值也加上即可。

## 代码

使用了线段树进行优化。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pushup (tr[n*2].mn<tr[n*2+1].mn?tr[n].mn=tr[n*2].mn,tr[n].bh=tr[n*2].bh:tr[n].mn=tr[n*2+1].mn,tr[n].bh=tr[n*2+1].bh)
using namespace std;
int n,m,s,u,v,w,w2[200002],tot,head[200001],dis[200001];
struct node{
	int to,nex,w;
}bian[400002];
struct nod{
	int l,r,mn,bh;
}tr[1062149];
inline void read(int &x){
    bool f=1;x=0;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=!f;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
    x=(f?x:-x);return;
}
inline void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');return;
}
inline void add(int x,int y）
{
	bian[++tot].to=y;
	bian[tot].nex=head[x];
	bian[tot].w=w;
	head[x]=tot;
}
inline void ad(int n,int l,int r)
{
	tr[n].l=l,tr[n].r=r;
	if(l==r)
	{
		tr[n].mn=dis[l],tr[n].bh=l;
		return;
	}
	int mid=(l+r)>>1;
	ad(n*2,l,mid);
	ad(n*2+1,mid+1,r);
	pushup;
	return;
}
inline void be(int n,int l,int k)
{
	if(tr[n].l==tr[n].r)
	{
		tr[n].mn=k;
		return;
	}
	int mid=(tr[n].l+tr[n].r)>>1;
	if(l<=mid)
	{
		be(n*2,l,k);
	}
	else
	{
		be(n*2+1,l,k);
	}
	pushup;
	return;
}
inline void dijkstra(int n)
{
	int x;
	for(int i=1;i<=n;++i)
	{
		x=tr[1].bh;
		for(int j=head[x];j;j=bian[j].nex)
		{
			if(dis[bian[j].to]>dis[x]+bian[j].w+w2[bian[j].to])
			{
				dis[bian[j].to]=dis[x]+bian[j].w+w2[bian[j].to];
				be(1,bian[j].to,dis[x]+bian[j].w+w2[bian[j].to]);
			}
		}
		be(1,x,LLONG_MAX);
	}
	return;
}
signed main()
{
	read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		read(w2[i]);
	}
	for(int i=1;i<=m;++i)
	{
		read(u);read(v);read(w);
		add(u,v);add(v,u);
	}
	for(int i=2;i<=n;++i) dis[i]=LLONG_MAX;
	dis[1]=w2[1];  //要将dis[1]赋值为A[1]
	ad(1,1,n);
	dijkstra(n);
	for(int i=2;i<=n;++i)
	{
		write(dis[i]);
		putchar(' ');
	}
	return 0;
}
```

---

