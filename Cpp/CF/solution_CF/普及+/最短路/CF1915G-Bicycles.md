# Bicycles

## 题目描述

给定 $n$ 个城市和 $m$ 条连接两个城市 $u_i$ 和 $v_i$ 的双向道路，长度为 $w_i$。

现在城市 $n$ 举办了一场派对，住在城市 $1$ 的 Slavic 想要去参加。在城市之间往返需要骑自行车，而 Slavic 没有自行车，所以他需要在这些城市里购买自行车以赶到城市 $n$。

从 $1$ 到 $n$ 的每个城市 $j$ 里都有且仅有一辆自行车可供购买，每辆自行车的速度系数为 $s_j$。

当 Slavic 骑上编号为 $j$ 的自行车后，他可以在任何时刻和任何地点通过一条道路 $i$，花费 $w_i\times s_j$ 的时间。

求 Slavic 骑车从城市 $1$ 赶到城市 $n$ 参加派对所需的最短时间。

## 说明/提示

$ 2 \leq n \leq 1000 $，$ n - 1 \leq m \leq 1000$，$ 1 \leq s_i \leq 1000 $；

$ 1 \le u_i, v_i \le n $ , $ u_i \neq v_i $，$ 1 \leq w_i \leq 10^5$；

所有测试数据的 $\sum n$、$\sum m$ 不超过 $1000$。

保证存在方案能从城市 $1$ 到达城市 $n$。

By Misaka16172

## 样例 #1

### 输入

```
3
5 5
1 2 2
3 2 1
2 4 5
2 5 7
4 5 1
5 2 1 3 3
5 10
1 2 5
1 3 5
1 4 4
1 5 8
2 3 6
2 4 3
2 5 2
3 4 1
3 5 8
4 5 2
7 2 8 4 1
7 10
3 2 8
2 1 4
2 5 7
2 6 4
7 1 2
4 3 5
6 4 2
6 7 1
6 7 4
4 5 9
7 6 5 4 3 2 1```

### 输出

```
19
36
14```

# 题解

## 作者：wsx248 (赞：7)

不难看出是在图上求最短距离，考虑如何做。

发现对到达的每一个点，都有两种可能性：

1. 不修改速度，以原速度继续前进
2. 修改速度为当前点上的速度，继续前进

很显然，速度直接影响到未来的消耗时间，因此想到分层图，按速度分层，每到达一个点后根据是否换速度做两次松弛即可。

注意开 `long long`，以及最后取值时是取 $dis_{n, a_i}$。

```cpp
#include<iostream>
#include<cmath>
#include<queue>
#include<cstring>
using namespace std;
const int N = 1e3+5;
struct Edge{
	int to, nxt, w;
}edge[N<<1];
int h[N], cnt = 1;
void add(int u, int v, int w)
{
	edge[cnt] = {v, h[u], w};
	h[u] = cnt++;
}

int n, m;
int a[N];
long long dis[N][N];
bool vis[N][N];
struct node{
	long long dis;
	int u, speed;
	bool operator < (const node &b) const&
	{
		return dis > b.dis;
	}
};
void dijkstra()
{
	memset(dis, 0x3f, sizeof dis);
	memset(vis, 0, sizeof vis);
	priority_queue<node> q;
	dis[1][a[1]] = 0;
	q.push({0, 1, a[1]});
	
	while(q.size())
	{
		int t = q.top().u;
		int s = q.top().speed;
		q.pop();
		
		if(vis[t][s])
			continue;
		vis[t][s] = 1;
		
		for(int i=h[t];i;i=edge[i].nxt)
		{
			int j = edge[i].to;
			int w = edge[i].w;
			long long sp = w * 1ll * s;
			if(dis[j][s]>dis[t][s]+sp)	//不换速度 
			{
				dis[j][s] = dis[t][s] + sp;
				q.push({dis[j][s], j, s});
			}
			if(dis[j][a[j]]>dis[t][s]+sp)
			{
				dis[j][a[j]] = dis[t][s] + sp;
				q.push({dis[j][a[j]], j, a[j]});
			}
		}
	}
}

int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		cin>>n>>m;
		memset(h, 0, sizeof h);
		cnt = 1;		
		for(int i=1;i<=m;i++)
		{
			int u, v, w;
			cin>>u>>v>>w;
			add(u, v, w);
			add(v, u, w);
		}
		for(int i=1;i<=n;i++)
			cin>>a[i];
		dijkstra();
		long long ans = 1e18;
		for(int i=1;i<=n;i++)
			ans = min(ans, dis[n][a[i]]);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：DrAlfred (赞：5)

摘要：最短路，分层图，拆点

[传送门：https://www.luogu.com.cn/problem/CF1915G](https://www.luogu.com.cn/problem/CF1915G)

## 题意

给定一个 $ n $ 个点（城市）， $ m $ 条边的无向联通图。每到一个城市可以买一辆自行车。第 $ i $ 个城市购买的自行车有一个慢度系数 $ s_i $。如果骑着这辆自行车通过边权为 $ w $ 的边，则需要 $ w \times s_i $ 的时间。每到一个城市可以任意选择是否更换自行车。问从 $ 1 $ 号城市到第 $ n $ 号城市所要的最短时间。

## 分析思路

分层图板题。

注意到数据范围比较小，考虑拆点。将第 $ i $ 个点根据当前自行车的慢度系数拆成 $ 1000n $ 个点，然后对于每条边，考虑是否换自行车，跑 `Dijkstra` 即可。

时间复杂度 $O\left(tm \log kn \right)$，其中 $k$ 为拆点带来的常数 $1000$，可以通过本题。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
typedef long long ll;
struct Edge {
    ll to, w;
};
struct Node {
    ll pos, w, s;
    inline bool operator<(const Node &x) const {
        return w > x.w;
    }
} last;
vector<Edge> G[N];
priority_queue<Node> heap;
ll t, n, m, u, v, w, s[N], dis[N][N], vis[N][N];
inline ll Dijkstra(void) {
    heap.push({1, 0, s[1]}), dis[1][s[1]] = 0;
    while (!heap.empty()) {
        last = heap.top(), heap.pop();
        if (vis[last.pos][last.s]) {
            continue;
        }
        vis[last.pos][last.s] = 1;
        for (auto edge : G[last.pos]) {
            const ll ns = last.s, u = edge.to;
            if (dis[u][ns] > last.w + edge.w * ns) {
                dis[u][ns] = last.w + edge.w * ns;
                heap.push({u, dis[u][ns], ns});
                heap.push({u, dis[u][ns], s[u]});
            }
        }
    }
    ll minn = LLONG_MAX;
    for (int i = 1; i <= 1000; i++) {
        minn = min(minn, dis[n][i]);
    }
    return minn;
}
inline void solve(void) {
    cin >> n >> m;
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0x00, sizeof(vis));
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i <= m; i++) {
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }
    cout << Dijkstra() << '\n';
}
int main(int argc, char const *argv[]) {
    cin >> t;
    while (t--) solve();
    return 0;
}

```

---

## 作者：20111019Yu (赞：2)

### 思路

读完题可以发现这就是一个经典的最短路，只需要将 $dis$ 和 $vis$ 数组的维度多加一维记录速度系数就可以了。

在做松弛操作的时候只需要将 $i.w$ 换成 $i.w\times t.u$。

根据贪心可知，到达一个城市时，单车一定是取当前单车和本城市单车中更优的那一个。

最后的答案便是 $\min\limits_{i=1}^{n} dis_{n,s_{i}}$

于是在一顿瞎搞后代码就出来了。

### code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int t, x, y, z, a[1005], dis[1005][1005], n, m;
struct node{
	int u, v, w;
	bool operator < (const node &i) const{
		return v > i.v;
	}
};\\重载运算符
vector<node> vec[1005];
bool vis[1005][1005];

void dijkstra(){
	priority_queue<node> q;
	memset(dis, 0x7f, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[1][a[1]] = 0;
	q.push({1, 0, a[1]});
	while(!q.empty()){
		node t = q.top();
		q.pop();
//		cout << t.u << " " << t.v << " " << t.w << endl;
		if(vis[t.u][t.w]) continue;
		vis[t.u][t.w] = 1;
		for( auto &i : vec[t.u] ){
			if(dis[i.u][min(t.w, a[i.u])] > dis[t.u][t.w] + i.v * t.w){
				dis[i.u][min(t.w, a[i.u])] = dis[t.u][t.w] + i.v * t.w;
				q.push({i.u, dis[i.u][min(t.w, a[i.u])], min(a[i.u], t.w)});
			}\\松弛操作
		}
	}
}

signed main(){
	cin >> t;
	while(t--){
		int ans = 1e18;
		for( int i = 1; i <= n; i++ ) vec[i].clear();\\多测要清空
		cin >> n >> m;
		while(m--){
			cin >> x >> y >> z;
			vec[x].push_back({y, z});
			vec[y].push_back({x, z});
		}
		for( int i = 1; i <= n; i++ ) cin >> a[i];
		dijkstra();
		for( int i = 1; i <= n; i++ ) ans = min(ans, dis[n][a[i]]);
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：紊莫 (赞：2)

分层图最短路，容易想到按照速度分层。

速度系数肯定是越小越好，在一般的最短路算法中加入速度系数这一栏，然后就是裸的最短路板子，可参考 P4779 【模板】单源最短路径（标准版）。


代码如下，您需要注意的是多测要清空。

```cpp
// Problem: G. Bicycles
// Contest: Codeforces - Codeforces Round 918 (Div. 4)
// URL: https://codeforces.com/problemset/problem/1915/G
// Memory Limit: 256 MB
// Time Limit: 4000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//@紊莫
#include <bits/stdc++.h>
#define int long long
#define F(i,a,b) for(int i=(a);i<=(b);i++)
#define dF(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0)x = ~x + 1, putchar('-');if (x > 9) write(x / 10);putchar(x % 10 + '0');}
inline void writeln(int x){write(x);putchar('\n');}
inline void writesp(int x){write(x);putchar(' ');}
inline int lowbit(int x) {return x&(-x);}
typedef long long ll;
typedef pair<int,int> Pair;
const int N=1005,M=(N<<1),inf=1e18;
int n,m,w[N],d[N][N],v[N][N],h[N];

struct node{
	int now,dis,car;
	bool operator <(node x)const{
		return dis>x.dis;
	}
};
signed main(){
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int T;cin>>T;
	while(T--){
		cin>>n>>m;
		vector<Pair> G[N];
		F(i,1,m){
			int u,v;
			cin>>u>>v>>w[i];
			G[u].push_back({v,i});
			G[v].push_back({u,i});
		}
		int Mx=0;
		F(i,1,n) cin>>h[i],
			Mx=max(Mx,h[i]);
		
		memset(d,0x3f,sizeof d);
		memset(v,0,sizeof v);
		d[1][h[1]]=0;
		priority_queue<node> q;
		q.push({1,0,h[1]});
		while(q.size()){
			node f=q.top(); q.pop();
			if(v[f.now][f.car]) continue;
			v[f.now][f.car] = 1;
			for(auto x:G[f.now]){
				int ncar = min(f.car,h[x.first]);
				if(f.dis+f.car*w[x.second]<d[x.first][ncar]){
					d[x.first][ncar]=f.dis+f.car*w[x.second];
					q.push({x.first,d[x.first][ncar],ncar});
				}
			}
		}
		int ans=inf;
		F(i,0,Mx) ans=min(ans,d[n][i]);
		cout<<ans<<'\n';
	}
    return 0;
}

```


---

## 作者：AlicX (赞：2)

## Solution 

~~个人认为此题是在强套算法。~~

拿到此题不难想到要最短路，以及一个显而易见的贪心：每次尽可能用最快的自行车。发现 $n,s_i \leq 1000$，于是考虑在优先队列里放入三个值：当前的时间，当前所在的点，当前最快的自行车，然后就是正常的最短路了，时间复杂度 $O(nS\log nS)$。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second 
#define debug() puts("-----") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=1010; 
int n,m; 
int s[N]; 
bool st[N][N]; 
int dis[N][N]; 
int h[N],idx=0;  
struct Node{ 
	int w; 
	int to,ne; 
}tr[N<<1]; 
void add(int u,int v,int w){
	tr[idx].w=w,tr[idx].to=v,tr[idx].ne=h[u],h[u]=idx++; 
} 
void dij(){
	priority_queue<pair<int,pii>> q; 
	dis[1][s[1]]=0; q.push({0,{1,s[1]}}); 
	while(!q.empty()){
		int u=q.top().y.x,j=q.top().y.y; q.pop(); 
		if(st[u][j]) continue; st[u][j]=true; 
		for(int i=h[u];i!=-1;i=tr[i].ne){
			int to=tr[i].to; 
//			for(int j=1;j<=1000;j++){
				int w=min(j,s[to]); 
				if(dis[to][w]>dis[u][j]+j*tr[i].w){
					dis[to][w]=dis[u][j]+j*tr[i].w; 
					q.push({-dis[to][w],{to,w}}); 
				} 
//			} 
		}
	} int ans=1e18; 
	for(int i=1;i<=1000;i++) ans=min(ans,dis[n][i]); 
	cout<<ans<<endl;  
} 
void work(){ 
	cin>>n>>m; idx=0; 
	for(int i=1;i<=n;i++){
		h[i]=-1; 
		for(int j=1;j<=1000;j++) st[i][j]=false,dis[i][j]=1e18; 
	} while(m--){ 
		int u,v,w; 
		cin>>u>>v>>w; 
		add(u,v,w),add(v,u,w); 
	} for(int i=1;i<=n;i++) cin>>s[i]; 
	dij(); 
} 
signed main(){ 
	int T; scanf("%lld",&T); 
	while(T--) work(); return 0; 
} 
```

---

## 作者：OIer_Hhy (赞：1)

今天在学最短路，于是我就切了道最短路板子……

这个数据范围，只能用 dijkstra。

我们用 $dis_{i,j}$ 表示在 $i$ 号城市骑 $j$ 系数的自行车最短路，用 $vis_{i,j}$ 表示在 $i$ 号城市骑 $j$ 系数的自行车路线是否出现过。

我们用一些堆优化，把每次的序号、距离、系数放进堆里，就可以过这道题。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long ll;
const int N=1e3+20;
int t,n,m,u,v;
ll dis[N][N],vis[N][N],w,s[N];
struct node{
	ll pos,w,s;
	inline bool operator<(const node &other)const{
        return w>other.w;
    }
};
priority_queue<node> q;
struct edge{
	ll to,w;
};
vector<edge> G[N];
inline void init(){
	for(int i=1;i<=n;i++) G[i].clear();
	memset(vis,0,sizeof vis);
	memset(dis,0x7f,sizeof dis);
	dis[1][s[1]]=0;

}
inline int dijkstra(){
	q.push({1,0,s[1]});
	dis[1][s[1]]= 0;
    while (!q.empty()) {
        node last=q.top();
		q.pop();
        if (vis[last.pos][last.s])
            continue;
        vis[last.pos][last.s] = 1;
        for (auto E:G[last.pos]) {
            ll k=last.s,u=E.to;
            if (dis[u][k]>(last.w)+ E.w * k) {
                dis[u][k]=(last.w)+ E.w * k;
                q.push({u,dis[u][k],k});
                q.push({u,dis[u][k],s[u]});
            }
        }
    }
    ll mn=LLONG_MAX;
    for(int i=1;i<=1000;i++)
        mn=min(mn,dis[n][i]);
    return mn;
}
inline void solve(){
	cin>>n>>m;
	init();
	for(int i=1;i<=m;i++){
		cin>>u>>v>>w;
		G[u].push_back({v,w});
		G[v].push_back({u,w});
	}
	for(int i=1;i<=n;i++) cin>>s[i];
	cout<<dijkstra()<<endl;
}

signed main(){
	cin>>t;
	while(t--) solve();
	return 0;
}



```

---

## 作者：liruixiong0101 (赞：1)

## P0 题意：
给定一个图，图中的每一个点都有一辆慢度系数为 $s$ 的自行车，如果您开着慢度系数为 $s$ 的自行车行驶过边权为 $w$ 的边时，所需消耗的时间为 $w\cdot s$ 请问从 $1$ 点出发，最快消耗多少的时间可以到达 $n$ 点。

## P1 思路：
我们发现其实在 $1$ 到 $n$ 的路径中，很多的时刻自己所骑的自行车的慢度系数都是相同的，就想到了乘法分配律将 $i$ 到 $j$ 所需要花费的时间写成 $s\cdot D(i,j)$。看到 $n,m\le 1000$，可以将每个点之间两两建边，考虑将每一个点都向其他点连一条长度为 $s\cdot D(i,j)$ 的边（$D(i,j)$ 表示 $i$ 到 $j$ 的最短路径长度），建立一个新图，这样就可以直接在新图上跑单源最短路了。

时间复杂度：$O(nm\log n+n^2\log n)$，空间复杂度：$O(n+m)$。

## P2 代码：
```cpp
#include <bits/stdc++.h>

using namespace std;
using LL = long long;
using Pli = pair<LL, int>;

const int kMaxN = 1005;

int T, n, m, s[kMaxN];
vector<Pli> g[2][kMaxN];
priority_queue<Pli> q;
LL dis[kMaxN];
bool vis[kMaxN];

void Dijkstra(vector<Pli> g[kMaxN], int s, int n) {
  q = priority_queue<Pli>();
  fill(dis + 1, dis + 1 + n, 1e18);
  fill(vis + 1, vis + 1 + n, 0);
  for (q.push({dis[s] = 0, s}); q.size();) {
    int u = q.top().second;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (Pli i : g[u]) {
      int v = i.second;
      LL w = i.first;
      if (dis[v] > dis[u] + w) {
        q.push({-(dis[v] = dis[u] + w), v});
      }
    }
  }
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> T; T; T--) {
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
      cin >> u >> v >> w;
      g[0][u].push_back({w, v});
      g[0][v].push_back({w, u});
    }
    for (int i = 1; i <= n; i++) {
      cin >> s[i], Dijkstra(g[0], i, n);
      for (int j = 1; j <= n; j++) {
        g[1][i].push_back({dis[j] * s[i], j});
      }
    }
    Dijkstra(g[1], 1, n);
    cout << dis[n] << '\n';
    for (int i = 1; i <= n; i++) {
      g[0][i].clear(), g[1][i].clear();
    }
  }
  return 0;
}
```

---

## 作者：InversionShadow (赞：0)

第一眼看到这道题，咦？这不是最短路板子吗？

再看一眼，哦有一个 $s_i$，~~那没事了~~。

这种题目你考虑在普通的最短路板子上修改，它多了一个 $s_i$，你的 `dis` 数组就多一维来存储当前的时间系数，同理 `vis` 也是，那么松弛操作的权值就变成了 `e[i].w * u.w`，就是当前的边权乘上时间系数。

然后就是，要开 `long long`。

```cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 2100;

int t, head[N], tot, s[N], dis[N][N];
bool vis[N][N];

struct Node {
	int to, nxt, w;
} e[N];

struct Edge {
	int u, v, w;
	const bool operator < (const Edge &e) const {
		return v > e.v;
	}
};

priority_queue<Edge> q;

void add(int u, int v, int w) {
	e[++tot] = {v, head[u], w};
	head[u] = tot;
}

void dijkstra() {
	memset(dis, 63, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	while (!q.empty()) q.pop();
	q.push({1, 0, s[1]}), dis[1][s[1]] = 0;
	while (!q.empty()) {
		auto u = q.top(); q.pop();
		if (vis[u.u][u.w]) continue;
		vis[u.u][u.w] = 1;
		for (int i = head[u.u]; i; i = e[i].nxt) {
			int v = e[i].to;
			if (dis[v][min(u.w, s[v])] > dis[u.u][u.w] + e[i].w * u.w) {
				dis[v][min(u.w, s[v])] = dis[u.u][u.w] + e[i].w * u.w, q.push({v, dis[v][min(u.w, s[v])], min(s[v], u.w)});
			}
		}
	}
}

void solve() {
	memset(head, 0, sizeof(head));
	int n, m;
	cin >> n >> m, tot = 0;
	while (m--) {
		int u, v, w; cin >> u >> v >> w;
		add(u, v, w), add(v, u, w);
	}
	for (int i = 1; i <= n; i++) cin >> s[i];
//	cout << "----------\n";
	dijkstra();
	int ans = 1e18;
	for (int i = 1; i <= n; i++) ans = min(ans, dis[n][s[i]]);
	cout << ans << '\n';
}

signed main() {
	cin >> t;
	while (t--) solve();
	return 0;
}
```

---

## 作者：szh_AK_all (赞：0)

## 题意
一共有 $n$ 个点，$m$ 条双向边，对于第 $i$ 个点可以让速度改变为 $s_i$，从而让经过道路的时间改变。求从点 $1$ 到 $n$ 的最短路。

## 分析
既然是求最短路，并且速度可以改变，很容易想到分层图。可以使用分层图的思想，在松弛操作里稍作改变。

首先，由于需要确定在经过边时的速度，所以让最短路 $dis$ 数组增加一维，即第二维表示速度。再用类似于动态规划的方法在松弛操作里考虑速度变化时的情况，那么这题就成了分层图思想的板子了。

## Code
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<int>g[1005];
vector<int>w[1005];
int n, m;
int s[1005];

struct node {
	int x, dis, su;
	node(int aa, int bb, int cc) {
		x = aa;
		dis = bb;
		su = cc;
	}
	friend bool operator<(node l, node r) {
		return l.dis > r.dis;
	}
};
int dis[1005][1005];
int vis[1005][1005];

void dij() {//求最短路
	memset(dis, 0x3f, sizeof(dis));//注意初始化
	memset(vis, 0, sizeof(vis));
	priority_queue<node>q;
	dis[1][s[1]] = 0;
	q.push(node(1, 0, s[1]));
	while (!q.empty()) {
		int x = q.top().x, su = q.top().su;
		q.pop();
		if (vis[x][su])
			continue;
		vis[x][su] = 1;
		for (int i = 0; i < g[x].size(); i++) {
			int y = g[x][i];
			int ww = w[x][i];
			if (dis[y][su] > dis[x][su] + ww * su) {
				dis[y][su] = dis[x][su] + ww * su;
				q.push(node(y, dis[y][su], su));
			}
			if (dis[y][s[y]] > dis[x][su] + ww * su) {//第二维松弛操作
				dis[y][s[y]] = dis[x][su] + ww * su;
				q.push(node(y, dis[y][s[y]], s[y]));
			}
		}
	}
}

signed main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> n >> m;
		for (int i = 1; i <= m; i++) {
			int u, v, ww;
			cin >> u >> v >> ww;
			g[u].push_back(v);
			g[v].push_back(u);
			w[u].push_back(ww);
			w[v].push_back(ww);
		}
		for (int i = 1; i <= n; i++)
			cin >> s[i];
		dij();
		int ans = 1000000000000000;//注意ans应该开的足够大
		for (int i = 1; i <= n; i++)
			ans = min(ans, dis[n][s[i]]), g[i].clear(), w[i].clear();//注意清空
		cout << ans << endl;
	}
}
                           
```

---

## 作者：TruchyR (赞：0)

看完题面，感觉不是很好做。  

结果一看到数据范围就乐了。  

考虑使用 Dijkstra 解决这一最短路问题：  

设 $dis_{i,j}$ 为到达 $i$ 号点，骑着速度系数为 $j$ 的自行车的最小时间。  

每次更新的时候，先骑上速度系数最小的自行车，再更新其他状态即可，其他与最短路模板无异。  

代码中使用了三元组，最大点 80 毫秒左右，可以通过本题。

```cpp
#include<bits/stdc++.h>
#define CKE if(CHECK)
#define FRE if(FIL)
#define int long long
#define MX 1005
#define MP make_pair
#define GP pair<int,int>
#define MT make_tuple
#define GT tuple<int,int,int>
using namespace std;
const int CHECK=0,FIL=0;int read();
int T,n,m,res,s[MX],dis[MX][MX];
priority_queue<GT,vector<GT>,greater<GT> >q;
vector<GP> v[MX];
signed main(){
	FRE freopen(".in","r",stdin);
	FRE freopen(".out","w",stdout);
	T=read();while(T--){
		//读入 &  初始化 
		n=read();m=read();
		for(int i=1;i<=n;i++) v[i].clear();
		while(m--){
			int a,b,w;
			a=read();b=read();w=read();
			v[a].push_back(MP(b,w));
			v[b].push_back(MP(a,w)); 
		}
		while(q.size()) q.pop();
		for(int i=1;i<=n;i++) s[i]=read();
		memset(dis,0x3f,sizeof(dis));dis[1][s[1]]=0;
		q.push(MT(0,1,s[1]));
		//Dijk 
		while(q.size()){
			GT tp=q.top();q.pop();
			int l=get<0>(tp),u=get<1>(tp),sp=get<2>(tp);
			if(dis[u][sp]<l) continue; sp=min(sp,s[u]); 
			for(auto i:v[u]){
				int t=i.first,lu=l+sp*i.second;
				if(lu<dis[t][sp]){
					dis[t][sp]=lu;
					q.push(MT(lu,t,sp));
				}
			}
		}res=1000000000000000000ll;
		for(int i=1;i<=1000;i++) res=min(res,dis[n][i]);
		printf("%lld\n",res);
	}
	return 0;
}
int read(){
	int Ca=0;char Cr=' ';int Cf=1;
	while(Cr<'0' || Cr>'9'){Cr=getchar();if(Cr=='-'){Cf=-1;}}
	while(Cr>='0' && Cr<='9'){Ca=Ca*10+Cr-48;Cr=getchar();}
	return Ca*Cf;
}

```

---

## 作者：Special_Tony (赞：0)

# 思路
这道题中，原本是最短路的板子题，但因为有 $s_i$ 的变化，所以我们不能直接普通使用最短路。然后你会发现 $n$ 和 $s_i$ 都很小，只有 $1000$，因此我们可以把 $d_i\to d_{i,j}$，其中 $d_{i,j}$ 表示在第 $i$ 个点且当前速度为 $j$ 时最小的距离。然后 $s_i$ 的话肯定是贪心取，取一路过来速度最快的自行车就行。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
int t, n, m, a[1005], x, y, z;
ll d[1005][1005];
vector <pii> v[1005];
struct node {
	ll dis;
	int u, minx;
	bool operator < (const node& cmp) const {
		return dis > cmp.dis;
	}
} ;
priority_queue <node> q;
ll dijkstra () {
	for (int i = 1; i <= n; ++ i)
		memset (d[i], 0x3f, sizeof d[i]);
	d[1][a[1]] = 0;
	q.push ({0, 1, a[1]});
	while (! q.empty ()) {
		const node t = q.top ();
		q.pop ();
		const int u = t.u, s = t.minx;
		if (t.dis > d[u][s])
			continue ;
		for (pii i : v[u]) {
			const int v = i.first, x = min (s, a[v]);
			if (t.dis + i.second * s < d[v][x])
				q.push ({d[v][x] = t.dis + i.second * s, v, x});
		}
	}
	ll minx = 1e18;
	for (int i = 0; i < 1003; ++ i)
		minx = min (minx, d[n][i]);
	return minx;
}
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> t;
	while (t --) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++ i)
			v[i].clear ();
		while (m --) {
			cin >> x >> y >> z;
			v[x].push_back ({y, z});
			v[y].push_back ({x, z});
		}
		for (int i = 1; i <= n; ++ i)
			cin >> a[i];
		cout << dijkstra () << '\n';
	}
	return 0;
}
```

---

## 作者：2c_s (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1915G)

## 思路

最短路径问题，我们采用 dijkstra 算法进行计算。

由于无法保证骑哪种自行车一定是最优解，且 $n$ 的范围为 $1\le n\le 1000$，足够开下二维数组，所以我们就可以用二维数组计算最短路。

定义 ``dis[i][j]`` 为骑第 $j\space(1\le j\le n)$ 辆自行车到 $i\space (1\le i\le n)$ 点时候的最短路径。

到第 $i$ 个点时有两种走法：

- 如果不换车，那么第二维不变。如果上一个点编号为 $k\space(1\le k\le n)$，则当前最短路 ``dis[i][j]`` 更新为 ``min(dis[i][j],dis[k][j]+k.w*s[j])``。

- 如果换车，那么要用这个点的编号替换上面一种情况的 ``dis[i][j]`` 数组第二维。

最后循环找到终点时骑每辆自行车的最短路最小值输出。

- 有多组测试数据，记得清空变量、数组等。

- 记得开 long long。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pli pair<ll,int>
#define fi first
#define se second
using namespace std;
inline ll read(){//快读。
	ll k=0,flag=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')flag=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		k=(k<<1)+(k<<3)+(c^48);
		c=getchar();
	}
	return k*flag;
}
void print(ll x){//快写。
    if(x<0){
        putchar('-');
        x=-x;
    }
    ll y=10,len=1;
    while(y<=x){
		y=(y<<1)+(y<<3);
        len++;
    }
    while(len--){
        y/=10;
        putchar(x/y+48);
        x%=y;
    }
    return ;
}
const int N=1010;
int n,m;
ll s[N],dis[N][N];
vector<pli>g[N];
struct node{
    ll step;
    int ty,x;
    bool operator<(const node a)const{return step>a.step;}
    //优先队列是大根堆，重载时要反着写才能变成小根堆。
};priority_queue<node>q;
inline void dij(){
    memset(dis,0x7f,sizeof dis);
    dis[1][1]=0;
    q.push({0,1,1});
    while(q.size()){
        auto k=q.top();
        q.pop();
        for(auto i:g[k.x]){
            if(dis[i.se][k.ty]>dis[k.x][k.ty]+s[k.ty]*i.fi){//不换车。
                dis[i.se][k.ty]=dis[k.x][k.ty]+s[k.ty]*i.fi;
                q.push({dis[i.se][k.ty],k.ty,i.se});
            }
            if(dis[i.se][i.se]>dis[k.x][k.ty]+s[k.ty]*i.fi){//换车。
                dis[i.se][i.se]=dis[k.x][k.ty]+s[k.ty]*i.fi;
                q.push({dis[i.se][i.se],i.se,i.se});
            }
        }
    }
    return ;
}
inline void solve(){
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        int u=read(),v=read();
        ll w=read();
        g[u].pb({w,v});
        g[v].pb({w,u});
    }
    for(int i=1;i<=n;++i)s[i]=read();
    dij();
    ll ans=1e18;
    for(int i=1;i<=n;++i)ans=min(ans,dis[n][i]);
    print(ans);
    puts("");
    for(int i=1;i<=n;++i)g[i].clear();
    return ;
}
int main(){
    int T=read();
    while(T--)solve();
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/147988618)

---

## 作者：Lily_White (赞：0)

## 题意简述
给定图 $G$，在每个结点处有一辆自行车。骑着“减慢系数”为 $s$ 自行车通过边权为 $w$ 的边的花费是 $sw$，你可以利用手上有的任意一辆自行车，求从 $1$ 到 $n$ 的最小花费。

## 算法
本题可以运用**分层图最短路的拆点**求解。

这个算法一般的使用情景是，经过某条边的花费是可以随我们的决策改变的。例如，在经典例题 [JLOI2011 飞行路线](https://www.luogu.com.cn/problem/P4568) 中，我们可以免费通过若干边。而在本题中，自行车的选择使得每次经过每条边时实际花费都不等于边权。

拆点的要义在于，我们避免对究竟如何进行决策的讨论（如果这么讨论的话，就需要记录经过了哪些点，获取的最优自行车是什么，等等），而通过对图进行“拆点”的操作，我们就能使得最优决策自然地以在图上曾经经过的路径表示。

具体地，我们将一个点 $u$ 拆做 $1000$ 个点 $u_i$，$u_i$ 的意义就是**当前在 $u$ 处，并且持有的最优自行车为减慢系数是 $i$** 的。这样，我们运行最短路算法时，就可以自动地做出最优决策了。

相应地，在松弛操作时，我们需要做两次松弛，分别对应换/不换自行车。

## 代码
核心部分代码如下：
```cpp
priority_queue<Node> pq;
pq.push({1, 0, s[1]});
memset(dis, INF, sizeof(dis));
memset(vis, 0, sizeof(vis));
dis[1][s[1]] = 0;
while (!pq.empty()) {
    auto [u, udis, us] = pq.top();
    pq.pop();
    if (vis[u][us]) continue;
    vis[u][us] = true;
    for (auto [v, w] : g[u]) {
        if (dis[v][us] > udis + w * us) {
            dis[v][us] = udis + w * us;
            pq.push({v, dis[v][us], us});
            pq.push({v, dis[v][us], s[v]});
        }
    }
}
```
   

---

## 作者：foryou_ (赞：0)

一眼最短路。

容易发现每到一个点 $u$ 就会有两种决策：换速度系数与不换速度系数。

于是定义状态 $dis_{u,p}$ 表示在点 $u$ 速度系数为 $p$ 时所需的最短时间。 

跑一遍 dijkstra，

对于每条边 $u \to v$，分别对 $dis_{v,p}$ 与 $dis_{v,s_v}$ 进行两次松弛操作即可。

答案显然为 $\min_{i=1}^{n}\{dis_{n,s_i}\}$。

[实现](https://www.luogu.com.cn/paste/y7o1liyi)。

---

## 作者：harmis_yz (赞：0)

## 分析

参照去年普及组 T4，很显然能发现就是一个暴力最短路。设 $dis_{i,j}$ 表示从 $1$ 走到 $i$ 且能得到的 $s$ 最小为 $j$ 时的最短路。那么答案就是 $\min\{dis_{n,i}|1 \le i \le V\}$。

考虑最短路转移。对于当前的 $dis_{u,j}$，走到 $v$ 的代价将会是 $w_{u \to v} \times j$。而在 $v$ 这个点可以买下一辆自行车，所以是之后的 $s$ 最小值为 $\min(s_v,j)$。即有：$dis_{v,\min(s_v,j)}=\min(dis_{v,\min(s_v,j)},dis_{u,j})$。

复杂度 $O(nV\log n)$

## 代码

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,pair<int,int>>
#define x first
#define y second
 
il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}
il void write(int x) {    
    if(x<0) putchar('-'),x=-x;    
    if(x>9) write(x/10);    
    putchar(x%10+'0');    
    return;    
}
 
const int N=2005;
int n,m,s[N];
int ne[N],e[N],h[N],w[N],idx;
int dis[N][N],vis[N][N];
 
il void add(int a,int b,int c){ne[++idx]=h[a],e[idx]=b,w[idx]=c,h[a]=idx;}
il void dij(){
	for(re int i=1;i<=n;++i)for(re int j=1;j<=1001;++j) dis[i][j]=1e16,vis[i][j]=0;
	priority_queue<PII,vector<PII>,greater<PII>> qu;
	qu.push({0,{s[1],1}}),dis[1][s[1]]=0;
	while(!qu.empty()){
		PII now=qu.top();qu.pop();
		if(vis[now.y.y][now.y.x]) continue;
		vis[now.y.y][now.y.x]=1;
		for(re int i=h[now.y.y];i;i=ne[i]){
			int j=e[i];if(dis[j][min(s[j],now.y.x)]>dis[now.y.y][now.y.x]+w[i]*now.y.x){
				dis[j][min(s[j],now.y.x)]=dis[now.y.y][now.y.x]+w[i]*now.y.x;
				qu.push({dis[j][min(s[j],now.y.x)],{min(s[j],now.y.x),j}});
			}
		}
	}
	return ;
}
 
il void solve(){
	n=read(),m=read();idx=0;
	for(re int i=1;i<=n;++i) h[i]=0;
	for(re int i=1,a,b,c;i<=m;++i)
		a=read(),b=read(),c=read(),add(a,b,c),add(b,a,c);
	for(re int i=1;i<=n;++i) s[i]=read();
	dij();int Min=1e18;
	for(re int i=1;i<=1001;++i) Min=min(Min,dis[n][i]);
	write(Min),puts("");
	return ;
}
 
signed main(){
	int t=read();while(t--)
	solve();
	return 0;
}
```


---

## 作者：technopolis_2085 (赞：0)

~~大概率是 2023 年的最后一篇题解~~

分析：

看到时间限制和数据范围，直接暴力 floyd 计算出最短路。

然后考虑 dp。

设 $dp_i$ 代表到第 $i$ 个点的最短时间。

所以 $dp_i$ 可以从 $dp_j+dist_{j,i}×s_j$ 转移过来，其中 $1≤j≤n$。

但是，我们发现转移方向不太好操作，于是考虑转化成图论模型：对于 $i$ 和 $j$ 两点，从 $j$ 到 $i$ 连一条有向边，边权为转移代价，然后跑最短路就行了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn=1010;
int a[maxn];
int dist[maxn][maxn];
int dp[maxn];
int n,m;

vector<pair<int,int> > G[maxn];

struct node{
	int u;
	int d;
	bool operator <(const node &cmp) const{
		return d>cmp.d;
	}
};

void dij(){
	priority_queue<node> q;
	q.push((node){1,0});
	for (int i=1;i<=n;i++) dp[i]=1e18;
	dp[1]=0;
	
	while (!q.empty()){
		node f=q.top(); q.pop();
		int u=f.u,d=f.d;
		if (d>dp[u]) continue;
		
		for (int i=0;i<(int)G[u].size();i++){
			int v=G[u][i].first;
			if (dp[v]>dp[u]+G[u][i].second){
				dp[v]=dp[u]+G[u][i].second;
				q.push((node){v,dp[v]});
			}
		}
	}
}

signed main(){
	int T;
	scanf("%lld",&T);
	while (T--){
		scanf("%lld%lld",&n,&m);
		for (int i=1;i<=n;i++) G[i].clear();
		for (int i=1;i<=n;i++){
			for (int j=1;j<=n;j++){
				if (i==j) dist[i][j]=0;
				else dist[i][j]=1e18;
			}
		}
		for (int i=1;i<=m;i++){
			int u,v,w;
			scanf("%lld%lld%lld",&u,&v,&w);
			dist[u][v]=min(dist[u][v],w);
			dist[v][u]=min(dist[v][u],w);
		}
		
		for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
		
		for (int k=1;k<=n;k++){
			for (int i=1;i<=n;i++){
				for (int j=1;j<=n;j++){
					dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
				}
			}
		}
		
		for (int i=1;i<=n;i++){
			for (int j=i+1;j<=n;j++){
				G[i].push_back(make_pair(j,dist[i][j]*a[i]));
				G[j].push_back(make_pair(i,dist[i][j]*a[j]));
			}
		}
		
		dij();
		printf("%lld\n",dp[n]);
	}
	return 0;
}

/*
1
4 3
1 2 1
2 3 1
1 4 100
100 2 1 100*/
```


---

## 作者：GenesisCrystal (赞：0)

~~QAQ赛后1min切掉的。~~

## Solution

考虑分层图和 $\text{Dijkstra}$。

对于每一个点，$dis_{i,j}$ 代表到了第 $i$ 个点，途径城市中的最小 $s_i$ 为 $j$。

然后对于一个 $dis_{i, j}$，有一条边 $i \overset{w} \rightarrow v$，有 $dis_{v, \min(j, s_v)} \gets \min(dis_{v, \min(j, s_v)}, dis_{i, j} + j \times w)$。

起点是 $(1, s_1)$，答案是 $\min \limits _{i=1} ^{1000} dis_{n, i}$。

## Code

```cpp
#include <iostream>
#include <queue>

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int kMaxN = 1001;

int t, n, m;
vector<pii> g[kMaxN];
struct Node {
  ll dis, s, to;
  Node(ll to, ll s, ll dis) : dis(dis), s(s), to(to) {}
  friend bool operator<(Node a, Node b) {
    return a.dis > b.dis;
  }
};

void Solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    g[i].clear();
  }
  for (int i = 1, u, v, w; i <= m; i++) {
    cin >> u >> v >> w;
    g[u].push_back({v, w}), g[v].push_back({u, w});
  }
	ll s[kMaxN];
	for (int i = 1; i <= n; i++) {
		cin >> s[i];
	}
	priority_queue<Node> q;
	ll dis[kMaxN][kMaxN] = {};
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 1000; j++) {
			dis[i][j] = 1e18;
		}
	}
	bool f[kMaxN][kMaxN] = {};
	dis[1][s[1]] = 0;
	q.push(Node(1, s[1], 0));
	while (!q.empty()) {
		ll tx = q.top().to, ts = q.top().s;
		q.pop();
		if (f[tx][ts]) {
			continue;
		}
		f[tx][ts] = 1;
		for (pii i : g[tx]) {
			if (dis[i.first][min(s[i.first], ts)] > dis[tx][ts] + i.second * ts) {
				dis[i.first][min(s[i.first], ts)] = dis[tx][ts] + i.second * ts;
				q.push(Node(i.first, min(s[i.first], ts), dis[i.first][min(s[i.first], ts)]));
			}
		}
	}
	ll ans = 1e18;
	for (int i = 1; i <= 1000; i++) {
		ans = min(ans, dis[n][i]);
	}
	cout << ans << '\n';
}

int main() {
  for (cin >> t; t; t--) {
		Solve();
  }
  return 0;
}

```

---

