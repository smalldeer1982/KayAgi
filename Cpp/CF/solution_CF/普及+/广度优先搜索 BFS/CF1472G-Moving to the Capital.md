# Moving to the Capital

## 题目描述

### 题意
有一个由 $n$ 个点 $m$ 条边组成的有向图。边长均为 $1$。定义 $d_i$ 为点 $1$ 到点 $i$ 的最短距离。

你要通过以下方法走边，求出从每个点开始，在能到达的点 $i$ 中，$d_i$ 的最小值是多少。

- 若当前在 $i$，有一条 $i \to j$ 的有向边，且 $d_i<d_j$，可以走到 $j$ 无数次。
- 若当前在 $i$，有一条 $i \to j$ 的有向边，且 $d_i \ge d_j$，可以走到 $j$ 至多一次。

注意，至多一次指的是从每个点开始行走时，行走的路径上至多经过一次 $d _ i \ge d _ j$ 的边。

## 说明/提示

$1\leq t\leq 10^4$  
$2\leq n\leq 2\times 10^5$  
$1\leq m\leq 2\times 10^5$  
$1\leq u,v\leq n$  

Translated by @[Cym10x](/user/354015).

## 样例 #1

### 输入

```
3

6 7
1 2
1 3
2 5
2 4
5 1
3 6
6 2

2 2
1 2
2 1

6 8
1 2
1 5
2 6
6 1
2 3
3 4
4 2
5 4```

### 输出

```
0 0 1 2 0 1 
0 0 
0 0 2 1 1 0```

# 题解

## 作者：Cylete (赞：3)

先求出$1$到每个点的距离

然后dfs搜一遍即可

具体见代码

```cpp
int n, m;
vector<int> edge[N];
int dis[N], book[N], vis[N], f[N];
inline void bfs() {
	queue<int> q;
	q.push(1); book[1] = 1; dis[1] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(auto y : edge[x]) {
			if(!book[y]) {
				book[y] = 1;
				dis[y] = dis[x] + 1;
				q.push(y); 
			}
		}
	} 
}

inline void dfs(int x) {
	vis[x] = 1;
	f[x] = dis[x];
	for(auto y : edge[x]) {
		if(!vis[y] && dis[x] < dis[y])
			dfs(y);
		if(dis[x] < dis[y]) f[x] = min(f[x], f[y]);//若dis[x] < dis[y],那么x的答案可以被y更新
		else f[x] = min(f[x], dis[y]);//否则只能
用一次魔法（？）	} 
}

inline void solve() {
	read(n); read(m);
	for(int i = 1; i <= n; i++) {
		edge[i].clear();
		book[i] = dis[i] = vis[i] = f[i] = 0;
	}//多测清零
	for(int i = 1, x, y; i <= m; i++) {
		read(x); read(y);
		edge[x].push_back(y); 
	}
	bfs();//先求1至每个点的距离
	dfs(1);
	for(int i = 1; i <= n; i++) writesn(f[i]);
	puts("");
}
```

---

## 作者：KSToki (赞：2)

~~我太菜了这翻译看不懂。~~

第一步很简单，我们需要求一个 $d$ 数组，$d_i$ 表示 $1$ 号点到 $i$ 号点的最短路，应该是保证了都可以到。于是我就 copy 了我的最短路板子，当然边权都为一可以跑 bfs。

两种移动方法没有问题，问每一个点能够到达的 $d_i$ 最小的 $i$。

首先 $1$ 号节点是 $0$，任何点想要到 $1$ 必须用一次第二种走法。最终每个点经过的 $d$ 的序列除了最后一个一定是单调递增，于是我们可以用 dfs，每次比较用哪种方式往哪边走即可。

嗯，多测要清空。

代码：
```cpp
#include<bits/stdc++.h>
#define R register
#define I inline
#define ll long long
#define ull unsigned long long
#define LL __int128
#define db double
using namespace std;
#define pii pair<int,int>
#define mp(x,y) make_pair(x,y)
#define piii pair<pair<int,int>,int>
#define mp3(x,y,z) make_pair(make_pair(x,y),z)
#define fi first.first
#define se first.second
#define th second
#define putint(x) printf("%d\n",x)
#define putll(x) printf("%lld\n",x)
#define putull(x) printf("%llu\n",x)
#define lowbit(x) ((x)&(-(x)))
#define inf (0x7fffffff)
#define INF (1e18)
I int read()
{
	char ch=getchar();
	int res=0,flag=1;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
			flag=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		res=res*10+ch-'0';
		ch=getchar();
	}
	return res*flag;
}
int T,n,m,head[200001],to[200001],nxt[200001],tot,x,y,dis[200001],res[200001];
bool vis[200001];
I void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
priority_queue< pii >q;
I void dijkstra()
{
	for(R int i=1;i<=n;++i)
	{
		dis[i]=0x7fffffff/3;
		vis[i]=0;
	}
	dis[1]=0;
	q.push(mp(0,1));
	while(!q.empty())
	{
		x=q.top().second;
		q.pop();
		if(vis[x])
			continue;
		vis[x]=1;
		for(R int i=head[x];i;i=nxt[i])
		{
			y=to[i];
			if(dis[y]>dis[x]+1)
			{
				dis[y]=dis[x]+1;
				q.push(mp(-dis[y],y));
			}
		}
	}
}
void dfs(int x)
{
	vis[x]=1;
	res[x]=dis[x];
	for(R int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if((!vis[y])&&dis[x]<dis[y])
			dfs(y);
		if(dis[x]<dis[y])
			res[x]=min(res[x],res[y]);
		else
			res[x]=min(res[x],dis[y]);
	}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		tot=0;
		for(R int i=1;i<=n;++i)
			head[i]=0;
		while(m--)
		{
			x=read();
			y=read();
			add(x,y);
		}
		dijkstra();
		for(R int i=1;i<=n;++i)
		{
			vis[i]=0;
			res[i]=0;
		}
		dfs(1);
		for(R int i=1;i<=n;++i)
			printf("%d ",res[i]);
		puts("");
	}
	return 0;
}
```


---

## 作者：胖头鱼学员 (赞：2)

# CF1472G

[CF传送门](http://codeforces.com/problemset/problem/1472/G)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1472G)

## $QuestionMeaning$

有一个由$n$个结点组成的有向图。一些结点由边长为$1$的有向边相连。
已知一个数组$d_{1 \sim n}$，其中 d_i 为从编号为$1$的结点到编号为$i$的结点的最短距离。 你站在第$s$个节点上。你有以下几种选择：

沿着某条边，从第$i$个结点到第$j$个结点，$d_i<d_j$；
沿着某条边，从第$i$个结点到第$j$个结点，$d_i\geq d_j$；（每局最多只能走一次）

你的目标是：靠近编号为$1$的点。（准确地说，是找到从任意一个结点出发到第$1$个结点的最短距离）

## $Solution$

考虑最短路：

设$d_i$是编号为$i$的点到$1$的点的距离。

则$d_i<d_j$就是向前走一个点，$d_i \geq d_j$就是向回走一个点。那么发现，这个往回走的这一步肯定是最后再向回走。

求一遍最短路然后加上特殊处理即可，具体过程见代码。

## $Code$
```
# include <iostream>
# include <vector>

using namespace std;

const int kMaxN = 2e5 + 1;

struct V {
  int ans, d;
  vector<int> e;
} v[kMaxN];

int t, n, m;
int q[kMaxN] = {1};

void solve() {
  cin >> n >> m;
  fill(v + 1, v + 1 + n, v[0]);
  for (int i = 1, x, y; i <= m; i++) {
    cin >> x >> y;
    v[x].e.push_back(y);
  }
  v[1].d = v[1].ans = 1;
  for (int h = 0, t = 0; h <= t; h++) {
    int top = q[h];
    for (int to : v[top].e) {
      if (!v[to].d) {
        v[to].d = v[top].d + 1;
        q[++t] = to;
      }
    }
  }
  for (int i = n; i >= 1; i--) {
    int id = q[i];
    v[id].ans = v[id].d;
    for (int to : v[id].e) {
      v[id].ans = min(v[id].ans, (v[to].d <= v[id].d ? v[to].d : v[to].ans));
    }
  }
  for (int i = 1; i <= n; i++) {
    cout << v[i].ans - 1 << " ";
  }
  cout << endl;
}

int main() {
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}
```

---

## 作者：Fairicle (赞：1)

~~感觉大家都会做，大家好强啊~~

题意就不描述了。

肯定想到要从至多向距离更近或相等的点走一次这个条件入手。

如果你学过tarjan就会想到 low 数组（~~没学过也没关系~~）

在这题定义一个 low 数组，感性地说，它表示的是 $i$ 点能到达的与 $1$ 点距离最小的这个距离。

那么就可以初始化：

$low[i]=dis[i],low[i]=\min_{edge(i,u)\in E}(low[i],dis[u])$，其中 $E$ 代表边集，也就是这个图的所有边。

那么不止是能走去相邻的点，还可以一直向更深的地方走，最后通过某个点走向较浅的点，于是有递推式：

$low[i]=min_{edge(i,u)\in E\  \text{and}\ dis[u]>dis[i]}(low[i],low[u])$

那么如何保证转移的顺序？

只需要先转移深度深的节点即可。我们使用 BFS 求最短路（因为边权为 1），最后在队列中的节点，它们的 dis 是单调不减的，倒序转移即可。

code：

```cpp
#define ri register int
#define ll long long
#define N 200010
struct node{
    int nxt,to;
}star[N<<1];
int n,m,head[N],wl,dis[N],q[N],vis[N],l=0,r=-1,x,y,low[N],t,g[N],f[N][2];
int main(){
    t=rd();
    while(t--){
        n=rd(),m=rd();
        for(ri i=1;i<=m;++i){
            x=rd(),y=rd();
            add(x,y);//加边
        }
        q[++r]=1;for(ri i=1;i<=n;++i) dis[i]=-1;dis[1]=0;
        while(l<=r){
           int u=q[l++];
           for(ri i=head[u];i;i=star[i].nxt){
               int v=star[i].to;
               if(dis[v]==-1) dis[v]=dis[u]+1,q[++r]=v;
           }
        }
        for(ri i=n;i>=1;--i){
            low[q[i]]=dis[q[i]];
            for(ri j=head[q[i]];j;j=star[j].nxt){
                int u=star[j].to;
                if(dis[u]<=dis[q[i]]) low[q[i]]=min(low[q[i]],dis[u]);
            }
        }
        for(ri i=n;i>=1;--i){
            for(ri j=head[q[i]];j;j=star[j].nxt){
                int u=star[j].to;
                if(dis[u]>dis[q[i]]) low[q[i]]=min(low[q[i]],low[u]);
            }    
        }
        for(ri i=1;i<=n;++i) cout<<low[i]<<" ";cout<<endl;
        l=0,r=-1;wl=0;
        for(ri i=1;i<=n;++i) dis[i]=vis[i]=low[i]=head[i]=0;
    }
    return 0;
}
```


---

## 作者：1234567890sjx (赞：0)

简单树上 dp。先跑一遍 bfs 求出所有的 $d_i$，然后考虑设 $f_i$ 表示从 $i$ 开始按照上述规则可以走到的点中，$d_i$ 的最小值。

显然初始有 $f_1=0$。对于每一个 $i$ 枚举其出边 $j$。若 $d_i\ge d_j$ 那么 $f_i$ 可以使用一次机会走到 $j$，之后只能走到 $d$ 值变大的点所以选用 $d_j$ 来更新 $f_i$，否则使用 $f_j$ 更新 $f_i$。可以采用记忆化搜索做到 $O(n)$ 求解。

```cpp
vector<int> z[N];
int f[N], dis[N], vis[N];
void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    f[u] = dis[u];
    for (auto &v : z[u])
        if (dis[v] <= dis[u]) f[u] = min(f[u], dis[v]);
        else dfs(v), f[u] = min(f[u], f[v]);
}
void run() {
    int T = read();
    while (T--) {
        int n = read(), m = read();
        for (int i = 1; i <= n; ++i) z[i].clear(), dis[i] = f[i] = 1e18, vis[i] = 0;
        for (int i = 1; i <= m; ++i) {
            int x = read(), y = read();
            z[x].eb(y);
        }
        queue<int> q;
        q.push(1);
        dis[1] = 0;
        while (q.size()) {
            int t = q.front();
            q.pop();
            for (auto &g : z[t])
                if (dis[g] > dis[t] + 1) {
                    dis[g] = dis[t] + 1;
                    q.push(g);
                }
        }
        f[1] = 0;
        dfs(1);
        for (int i = 1; i <= n; ++i) cout << f[i] << ' ';
        cout << '\n';
    }
}
```

---

## 作者：yyrwlj (赞：0)

首先 bfs 求出 $d_i$ 就不再赘述。

对于 $i < j$ 并且 $d_i \ge d_j$ 的边有只能经过一次的限制，遂考虑分层图。

对于每个点考虑能走到它的点，所以建成反图。

也就是对于原图 $a$ 连向 $b$ 且 $d_a \ge d_b$ 的边，我们在分层图上让第一层的 $b$ 连向 $a$。

如果 $d_a < d_b$， 就在这两层内部分别连从 $b$ 到 $a$ 的边。

容易发现能否扩展与经过的边无关，所以相当于分层图上的边权都为 $0$。

跑个 dij 最短路即可。

Code：

```cpp
typedef pair<int, int> PII;
const int N = 200005;
struct Edge{
	int to, nxt;
}g[N << 2];
int h[N], h2[N * 2], idx;
int d[N], dis[N * 2], n, m;
bool st[N * 2];
PII G[N];
void add(int h[],int a,int b)
{
	g[++ idx].to = b, g[idx].nxt = h[a], h[a] = idx;
}
inline int id(int u,int dep)
{
	return dep * n + u;
}
void work()
{
	cin >> n >> m;
	for (int i=1;i<=n;i++)
		h[i] = h2[i] = h2[i + n] = 0, d[i] = inf;
	idx = 0;
	for (int i=1;i<=m;i++)
	{
		int a, b;
		cin>>a>>b;
		add(h, a, b);
		G[i] = {a, b};
	}
	d[1] = 0;
	queue<int> q1;
	q1.push(1);
	while (!q1.empty())
	{
		int t = q1.front();
		q1.pop();
		for (int i = h[t]; i; i = g[i].nxt)
		{
			int j = g[i].to;
			if (d[j] > d[t] + 1)
			{
				d[j] = d[t] + 1;
				q1.push(j);
			}
		}
	}
	for (int i=1;i<=m;i++)
	{
		int a = G[i].x, b = G[i].y;
		if (d[a] >= d[b])
			add(h2, id(b, 0), id(a, 1));
		else
		{
			add(h2, id(b, 0), id(a, 0));
			add(h2, id(b, 1), id(a, 1));
		}
	}
	priority_queue<PII, vector<PII>, greater<PII> > q;
	for (int i=1;i<=n;i++)
	{
		dis[id(i, 0)] = dis[id(i, 1)] = d[i];
		q.push({d[i], i});
		st[id(i, 0)] = st[id(i, 1)] = false;
	}
	while (!q.empty())
	{
		PII t = q.top();
		q.pop();
		int u = t.y, d = t.x;
		if (st[u])
			continue;
		st[u] = true;
		for (int i = h2[u]; i; i = g[i].nxt)
		{
			int j = g[i].to;
			if (dis[j] > d)
			{
				dis[j] = d;
				q.push({d, j});
			}
		}
	}
	for (int i=1;i<=n;i++)
		cout << min(dis[id(i, 0)], dis[id(i, 1)]) << ' ';
	cout << '\n';
}
```

---

## 作者：_zuoqingyuan (赞：0)

# 思路分析

我们从节点 $1$ 出发，BFS 整张图，就可以得到每个节点的 $d_i$ 的值。如果点 $i$ 的 $d_i$ 是通过 $d_j$ 转移过来的，我们就连一条边 $(j,i)$，最终形成一颗树，满足节点 $u$ 的子树内任意一节点 $v$，都有 $d_v > d_u$。

我们记 $u$ 能到达的点中，最小的 $d_i$ 值为 $g_u$。我们假定存在一条边 $(u,v)$，分不同的情况讨论 $g_u$ 取值：

- $d_v>d_u$：这种边是可以走无数次的，所以说 $v$ 可以到达的点，$u$ 也一定可以到达，我们递归求出 $g_v$ 的值，令 $g_u$ 和 $\min\{g_v\}$ 取较小值即可。

- $d_v\le d_u$：这种情况更为特殊，题目中明确规定：“行走的路径上至多经过一次 $d_i\le d_j$ 的边。”，如果点 $u$ 通过这条边到达点 $v$，无法再通过跳这类边取到更小的点。则他只能取到 $v$ 及 $v$ 子树内的点。因为这些点最小的 $d$ 值即为 $d_v$，所以令 $g_u$ 和 $\min\{d_v\}$ 取较小值即可。

然后做完了，时间复杂度 $O(n)$，~~怎么感觉和 Tarjan 好像~~。

# Code：

```cpp
#include <iostream>
#include <cstdio> 
#include <queue>
using namespace std;
const int N=2e5+10,M=2e5+10;
int T,n,m,mk[N],pre[N],ver[N],to[M],nxt[M],idx=1,d[N],low[N],vis[N];
queue<int>q;
void add(int x,int y){
	to[++idx]=y,nxt[idx]=ver[x],ver[x]=idx;
}
void bfs(int s){
	q.push(s),d[s]=0,mk[s]=1;
	while(q.size()){
		int x=q.front();q.pop();
		for(int i=ver[x];i;i=nxt[i]){
			int y=to[i];
			if(!mk[y]){
				mk[y]=1,d[y]=d[x]+1;
				q.push(y);
			}
		}
	}
	return;
}
void dfs(int x){
	low[x]=d[x],vis[x]=1;
	for(int i=ver[x];i;i=nxt[i]){
		int y=to[i];
		if(!vis[y]&&d[y]>d[x])dfs(y);
		if(d[y]>d[x])low[x]=min(low[x],low[y]);
		else low[x]=min(low[x],d[y]);
	}
	return;
}
void clear(){
	for(int i=1;i<=n;i++)low[i]=d[i]=mk[i]=pre[i]=ver[i]=vis[i]=0;
	for(int i=1;i<=idx;i++)to[i]=nxt[i]=0;
	idx=1;
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d",&n,&m);
		for(int i=1,u,v;i<=m;i++){
			scanf("%d %d",&u,&v);
			add(u,v);
		}
		bfs(1);
		dfs(1);
		for(int i=1;i<=n;i++)printf("%d ",low[i]);
		clear();
	}
	return 0;
}
```

如有错误，请指出。

---

## 作者：lin_rany (赞：0)

## CF1472G Moving to the Capital
题目链接:[CF1472G Moving to the Capital](https://www.luogu.com.cn/problem/CF1472G)

题目大意:emmm，好长好长，自己看翻译。

题解:很显然要先求出$d$数组，然后我们处理最大使用一次的反边，其实就是不管$d[i]$和$d[to]$的大小，我们直接进行转移。最后我们来处理每一个点可以到达的最优点。

AC代码：
```cpp
#include<bits/stdc++.h>

#define ld long double
#define ll long long
using namespace std;
template<class T>
void read(T& x)
{
	T res = 0, f = 1; char c = getchar();
	while (!isdigit(c)) {
		if (c == '-')f = -1; c = getchar();
	}
	while (isdigit(c)) {
		res = (res << 3) + (res << 1) + c - '0'; c = getchar();
	}
	x = res * f;
}
const ll N = 200000 + 10;
const int mod = 1e9 + 7;
int t, n, m,d[N],ans[N];
vector<int>p[N];
bool vis[N];
void bfs(int u)
{
	queue<int>pls;
	pls.push(u);
	
	d[u] = 0; vis[u] = 1;
	while (pls.size())
	{
		int f = pls.front(); pls.pop(); vis[f] = 0;
		for (auto to : p[f])
		{
			if (d[to] > d[f] + 1)
			{
				d[to] = d[f] + 1;
				if (!vis[to])
				{
					pls.push(to);
					vis[to] = 1;
				}
			}
		}

	}
}
void dfs(int u)
{
	vis[u] = 1;
	for (auto to : p[u])
	{
		if (d[to] <=d[u])continue;
		if(!vis[to])dfs(to);
		ans[u] = min(ans[u], ans[to]);
	}
}
int main()
{
	//ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("test.in", "r", stdin);
#endif // ONLINE_JUDGE
	read(t);
	while (t--)
	{
		read(n); read(m);
		for (int i = 1; i <= n; i++)p[i].clear();
		for (int i = 1; i <= n; i++)d[i] = 0x3f3f3f3f,ans[i]=d[i],vis[i]=0;
		for (int i = 1; i <= m; i++)
		{
			int x, y; read(x), read(y); p[x].push_back(y);
		}
		bfs(1);
		for (int i = 1; i <= n; i++)
		{
			ans[i] = d[i];
			for (auto to : p[i])
			{
				ans[i] = min(ans[i], d[to]);
			}
		}
		dfs(1);
		for (int i = 1; i <= n; i++)printf("%d ", ans[i]);
		printf("\n");
	}
	return 0;
}

```

---

## 作者：_ChongYun_ (赞：0)

# 题意

给定一个边权为 $1$ 的有向图。

设 $dis_x$ 表示点 $x$ 到点 $1$ 的最短距离。

对于一个点，可以尽可能地向点 $1$ 靠近。

对于两个相邻的点 $u$ 和 $v$：

- 若 $dis_u < dis_v$，可以向点 $v$ 移动。

- 若 $dis_u \geq dis_v$，可以向点 $v$ 移动，但只能走一次。

问最终每一个点尽可能的靠近点 $1$ 后，当前位置离点 $1$ 的最短距离。

# 解析

$dis$ 数组可以通过跑最短路预处理出来。

考虑 dfs，枚举点 $u$ 直接相邻的每一个点 $v$，每次选择一种方式靠近点 $1$。

这显然是一个可以 dp 的问题。

我们建立一个 $dp$ 数组，$dp_i$ 代表最终点 $i$ 的答案。

显然第一种方式会使得 $dp_i$ 越来越大，而我们不想让答案更大。

具体地，在 dfs 时：

- 若 $dis_u <dis_v$，更新答案为两者答案的较小值。

- 若 $dis_u \geq dis_v$，更新答案为 $dp_u$ 与 $dis_v$ 的较小值。

更具体地，状态转移如下：

$dp_u = \begin{cases}
  \min dp_v&dis_u <dis_v \\
  \min dis_v&dis_u \geq dis_v \\
\end{cases}
$

# 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t,n,m;
struct node{
	int to,nxt,val;
}w1[114514<<1];
int h1[114514<<1];
int ans[114514<<1];
bool vis[114514<<1];
int cnt1=0;
void Link(int x,int y,int val){
	++cnt1;
	w1[cnt1].to=y;
	w1[cnt1].nxt=h1[x];
	w1[cnt1].val=val;
	h1[x]=cnt1;
	return ;
}
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q; 
int dis[114514<<1];
void dijkstra(int st){
	for(int i=1;i<=n;i++) dis[i]=INT_MAX;
	dis[st]=0;
	q.push(make_pair(0,st));
	while(!q.empty()){
		int x=q.top().second,xx=q.top().first;
		q.pop();
		if(xx!=dis[x]) continue;
		for(int i=h1[x];i!=0;i=w1[i].nxt){
			int y=w1[i].to;
			if(dis[y]>dis[x]+w1[i].val){
				dis[y]=dis[x]+w1[i].val;
				q.push(make_pair(dis[y],y));
			}
		}
	}
	return ; 
}
void dfs(int x){
	vis[x]=true;
	ans[x]=dis[x];
	for(int i=h1[x];i!=0;i=w1[i].nxt){
		int y=w1[i].to;
		if(dis[x]<dis[y]){
			if(!vis[y]) dfs(y);
			ans[x]=min(ans[x],ans[y]);
		}
		else ans[x]=min(ans[x],dis[y]);
	}
	return ;
}
signed main(){
	cin>>t;
	while(t--){
		cnt1=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++) h1[i]=0;
		for(int i=1;i<=n;i++) ans[i]=0,vis[i]=false;
		for(int i=1;i<=m;i++){
			int u,v;
			cin>>u>>v;
			Link(u,v,1);
		}
		dijkstra(1);
		dfs(1);
		for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
		cout<<endl;
		for(int i=1;i<=cnt1;i++){
			w1[i].to=w1[i].nxt=w1[i].val=0;
		}
	}
	return 0;
}
```

~~其实可以跑 bfs，但我脑抽敲了个 dij。~~

---

## 作者：qzhwlzy (赞：0)

### 题目大意

有一张 $n$ 个节点 $m$ 条边的有向图，节点 $1$ 到节点 $i$ 的最短路为 $d_i$。现在对于每一个 $i$，假设有一个人从 $i$ 出发，按照以下规则走，求所有能走到的点 $j$ 中 $d_j$ 的最小值。

走的规则是：若要从 $u$ 走到 $v$，则要有 $d_u<d_v$；但是最多只能有一次机会能是 $d_u\ge d_v$。

### 思路

显然首先要把 $d$ 数组处理出来，从 $1$ 开始跑一遍 BFS 即可。

然后，对于每个点 $i$，走的路线肯定是先从 $i$ 不断往下跑，然后在某个点向上到达终点。于是，我们得先处理出 $i$ 向下走的子节点的答案，而这是原问题的子问题。于是可以使用 DP 解决。令 $f_i$ 表示从 $i$ 节点开始的答案，则有：

- 若 $i$ 能直接到 $v$ 且 $d_v>d_i$，有 $f_i = \min f_v$；
- 若 $i$ 能直接到 $v$ 且 $d_v\le d_i$，有 $f_i = \min d_v$。注意不是 $\min f_v$，因为 $f_v$ 可能记录 $v$ 向下再向上的答案，于是可能会向上走两次。

### 代码

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#define maxn 200005
using namespace std;
int T,n,m,u,v; struct edge{int to,nex;}a[maxn]; int head[maxn],cnt=0;
void add(int from,int to){a[++cnt].to=to; a[cnt].nex=head[from]; head[from]=cnt;}
queue<int> q; int dep[maxn],up[maxn]; bool vis[maxn];
void bfs(){
	while(!q.empty()) q.pop(); dep[1]=1; q.push(1); while(!q.empty()){
		int top=q.front(); q.pop();
		for(int i=head[top];i;i=a[i].nex) if(!dep[a[i].to]) dep[a[i].to]=dep[top]+1,q.push(a[i].to);
	}
}
void dfs(int p){
	vis[p]=1; for(int i=head[p];i;i=a[i].nex)
		if(dep[a[i].to]>dep[p]){if(!vis[a[i].to]) vis[a[i].to]=1,dfs(a[i].to); up[p]=min(up[p],up[a[i].to]);}
		else up[p]=min(up[p],dep[a[i].to]);
}
int main(){
	scanf("%d",&T); while(T--){
		scanf("%d%d",&n,&m); for(int i=1;i<=n;i++) dep[i]=up[i]=head[i]=vis[i]=0; cnt=0;
		for(int i=1;i<=m;i++) scanf("%d%d",&u,&v),add(u,v);
		bfs(); for(int i=1;i<=n;i++) up[i]=--dep[i];
		dfs(1); for(int i=1;i<=n;i++) printf("%d%c",up[i]," \n"[i==n]);
	} return 0;
}
```

---

