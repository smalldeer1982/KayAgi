# [USACO19JAN] Shortcut G

## 题目背景

USACO 19 年一月月赛金组第三题

## 题目描述

每天晚上，Farmer John 都会敲响一个巨大的铃铛，召唤他的奶牛们前来牛棚享用晚餐。奶牛们都急切地想要前往牛棚，所以她们都会沿着最短的路径行走。
农场可以描述为 $N$ 块草地（$1 \leq N \leq 10,000$），方便起见编号为 $1 \ldots N$，牛棚位于草地 $1$。草地之间由 $M$ 条双向的小路连接（$N-1 \leq M \leq 50,000$）。每条小路有其通过时间，从每块草地出发都存在一条由一些小路组成的路径可以到达牛棚。

草地 $i$ 中有 $c_i$ 头奶牛。当她们听到晚餐铃时，这些奶牛都沿着一条消耗最少时间的路径前往牛棚。如果有多条路径并列消耗时间最少，奶牛们会选择其中“字典序”最小的路径（也就是说，她们通过在两条路径第一次出现分支的位置优先选择经过编号较小的草地的方式来打破并列关系，所以经过草地 $7$、$3$、$6$、$1$ 的路径会优先于经过 $7$、$5$、$1$ 的路径，如果它们所消耗的时间相同）。

Farmer John 担心牛棚距离某些草地太远。他计算了每头奶牛路上的时间，将所有奶牛消耗的时间相加，称这个和为总移动时间。他想要通过额外添加一条从牛棚（草地 $1$）连接到某块他选择的其他草地的、通过时间为 $T$（$1 \leq T \leq 10,000$）的“近道”来尽可能地减少总移动时间。当一头奶牛在她平时前往牛棚的路上偶然看见这条近道时，如果这条近道能够使她更快地到达牛棚，她就会走这条路。否则，一头奶牛会仍然沿着原来的路径行走，即使使用这条近道可能会减少她的移动时间。

请帮助 Farmer John 求出通过添加一条近道能够达到的总移动时间减少量的最大值。


## 样例 #1

### 输入

```
5 6 2
1 2 3 4 5
1 2 5
1 3 3
2 4 3
3 4 5
4 5 2
3 5 7```

### 输出

```
40```

# 题解

## 作者：hsfzLZH1 (赞：23)

发现自己难题做多了，反不会简单题。

## 题目大意

给定一个有 $n$ 个结点和 $m$ 条边的带权无向图，每个结点 $i$ 上有 $c_i$ 头奶牛， $1$ 号结点为家，每次回家奶牛会走一条最短的路径，如果有多条长度相同的最短路径，则奶牛会走字典序最小的一条。现在，你可以增加一条从 $1$ 到任意结点的长度为给定值 $T$ 的一条边。如果一头奶牛在平时回家的路上经过了这条边相连的结点，且这条边能使其回家路径更短，则其会走这条边。求能使所有奶牛走的路径长度和的变化的最大值。

## 解题思路

从结点 $1$ 开始做最短路，建出最短路树， DFS 遍历最短路树，对最短路树上的一点，其子树中的点在回家的过程中都会经过该点。此时若连接一条从该节点到 $1$ 号结点的边，则其最短路长度总和会减少 $siz\times(dist_x -T))$ 。

建最短路树时，由于奶牛会在路径长度相等的情况下走字典序更小的路径，所以我的方法是 **从小到大** 枚举起点 $x$ ，遍历出边设为指向 $y$ ，如果满足最短路条件（即 $dist_y=dist_x+edgeweight$ ）且这个点之前没有被其他节点连过（连过则一定更小更优），则连一条边，

**注意 $c_i$ 有可能是 $0$ 。在 DFS 的过程中，不能按照 $siz$ 的值判断是否访问过结点，而应增加一个附加数组，我被这个坑了好久。**

请使用 ```long long``` 。

## 代码展示

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int maxn=100010;
typedef long long ll;
ll n,m,c[maxn],T,cur,h[maxn],nxt[maxn],p[maxn],w[maxn],u,v,t;
ll dist[maxn],siz[maxn],ans;
bool tf[maxn];
struct node
{
    ll id,v;
    bool operator<(node x)const{return v>x.v;}
};
priority_queue<node>q;
vector<int>g[10010];
void add_edge(ll u,ll v,ll t)
{
    cur++;
    nxt[cur]=h[u];
    h[u]=cur;
    p[cur]=v;
    w[cur]=t;
}
bool f[maxn];
void dfs(int x)
{
    siz[x]=c[x];f[x]=true;
    for(vector<int>::iterator it=g[x].begin();it!=g[x].end();it++)
    if(!f[*it])dfs(*it),siz[x]+=siz[*it];
    ans=max(ans,siz[x]*(dist[x]-T));
}
int main()
{
    scanf("%lld%lld%lld",&n,&m,&T);
    for(int i=1;i<=n;i++)scanf("%lld",c+i);
    while(m--)scanf("%lld%lld%lld",&u,&v,&t),add_edge(u,v,t),add_edge(v,u,t);
    q.push({1,0});
    while(!q.empty())
    {
        node x=q.top();q.pop();
        if(tf[x.id])continue;
        tf[x.id]=true;dist[x.id]=x.v;
        for(int j=h[x.id];j;j=nxt[j])q.push({p[j],x.v+w[j]});
    }
    memset(tf,0,sizeof tf);
    for(int i=1;i<=n;i++)for(int j=h[i];j;j=nxt[j])
    if(dist[p[j]]==dist[i]+w[j]&&!tf[p[j]])tf[p[j]]=true,
    g[i].push_back(p[j]),g[p[j]].push_back(i);
    dfs(1);
    printf("%lld\n",ans);
    return 0;
}

```

---

## 作者：linluke (赞：15)

**[安利一下我的博客](https://www.cnblogs.com/linzhengmin/p/11039674.html)**  
**本题算法：最短路树**  
这是个啥玩意呢，就是对于一个图，构造一棵树，使从源点开始的单源最短路径与原图一模一样。怎么做呢，跑一边Dijkstra，然后对于一个点u，枚举它的边，设当前的边为cur_edge，如果dis[u]+cue_edge的长度=dis[cur_edge的终点]，那么显然这条边应该珂以是最短路树上的一条边，然后打一个标记表示cur_edge的终点不能再被加边了，题目要求字典序最小，显然u从1到n枚举珂以解决问题。  
建好树以后跑一边DFS，我们知道当前节点u上连边的贡献是$(dis[u] - t) \times$以$u$为根的子树的牛的个数，找到贡献最大的点更新答案即可。

代码：
```cpp
#include <cstdio>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#define ll long long

using namespace std;

ll read(){
    ll x = 0; int zf = 1; char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') zf = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); return x * zf;
}

struct Edge{
    int from, to, next; ll dis;
} edges[1000001];

int head[300001], edge_num = 0;

ll dis[300001];

inline void addEdge(int u, int v, ll w){
    edges[++edge_num] = (Edge){u, v, head[u], w};
    head[u] = edge_num;
}

set< pair<ll, int> > que;
int n, t, s = 1;

void dijkstra(){
    for (int i = 1; i <= n; ++i)
        dis[i] = (1ll << 62);
    dis[s] = 0; que.insert(make_pair(0, s));
    pair<ll, int> uu; int u, v;
    while (!que.empty()){
        uu = *que.begin(); que.erase(uu);
        u = uu.second;
        for (int c_e = head[u]; c_e; c_e = edges[c_e].next){
            v = edges[c_e].to;
            if (dis[u] + edges[c_e].dis < dis[v]){
                que.erase(make_pair(dis[v], v));
                dis[v] = dis[u] + edges[c_e].dis;
                que.insert(make_pair(dis[v], v));
            }
        }
    }
}

vector<int> vec[100001];
ll ans = 0;
int a[100001];
int vis[100001];

int DFS(int u){
    int v, cnt = 0; vis[u] = 1;
    for (int i = 0; i < vec[u].size(); ++i){
        v = vec[u][i];
        if (!vis[v])
            cnt += DFS(v);
    }
    cnt += a[u];
    ans = max(ans, (dis[u] - t) * cnt);
    return cnt;
}

int v2[100001];

signed main(){
    int m; n = read(), m = read(), t = read();
    for (int i = 1; i <= n; ++i) a[i] = read();
    int u, v; ll w;
    for (int i = 1; i <= m; ++i){
        u = read(), v = read(), w = read();
        addEdge(u, v, w), addEdge(v, u, w);
    }
    dijkstra();
    for(int i = 1; i <= n; ++i)
        for(int c_e = head[i]; c_e; c_e = edges[c_e].next)
            if(dis[edges[c_e].to] == dis[i] + edges[c_e].dis && !v2[edges[c_e].to]){
                v2[edges[c_e].to] = 1;
                vec[i].push_back(edges[c_e].to), vec[edges[c_e].to].push_back(i);
            }
    DFS(1);
    printf("%lld", ans);
    return 0;
}
```

---

## 作者：CYJian (赞：8)

这道题目的话。。按照题意做就好了。。

差不多就是先跑一个Dijkstra，然后按照题意建出一颗最短路树，要求连父边优先连编号小的。

然后弄出了这个，每一头牛走的方案就出来了。(在树上就是向根节点方向走。)

这样的话就可以处理出每一个点经过了多少牛，然后就可以用  这个点经过的牛的头数$\ast($当前点到根节点的距离$-$一条新边的长度$)$ 更新答案就好了。

写起来的话。。还是算比较简单的吧。。

```
#include <bits/stdc++.h>

using namespace std;

#define reg register
#define ge getchar()
#define Re read()
#define FI "shortcut.in"
#define FO "shortcut.out"
#define MAXN 10000
#define MAXM 100000

inline int read() {
	reg int x = 0, ch;
	while(!isdigit(ch = ge)) ;
	while(isdigit(ch)) x = (x << 1) + (x << 3) + (ch & 15), ch = ge;
	return x;
}

struct Node {
	int val, x;
	friend bool operator < (reg Node a, reg Node b) { return a.val < b.val; }
	friend bool operator > (reg Node a, reg Node b) { return a.val > b.val; }
};

int n;
int m;
int T;

int dis[MAXN + 1];
int p[MAXN + 1];

int tot;
int fi[MAXN + 1];
int ne[MAXM + 1];
int to[MAXM + 1];
int le[MAXM + 1];
int To[MAXN + 1];
int Val[MAXN + 1];
int in[MAXN + 1];

inline void Link(reg int u, reg int v, reg int w) {
	tot++;
	to[tot] = v;
	le[tot] = w;
	ne[tot] = fi[u];
	fi[u] = tot;
}

inline void dijsktra(reg int S) {
	memset(dis, 63, sizeof(dis));
	bitset<MAXN + 1>Arrive; Arrive.reset();
	dis[S] = 0;
	priority_queue<Node, vector<Node>, greater<Node> >q;
	q.push((Node){0, S});
	while(!q.empty()) {
		reg int x = q.top().x; q.pop();
		if(Arrive[x]) continue; Arrive[x] = 1;
		for(reg int i = fi[x]; i; i = ne[i]) {
			reg int u = to[i];
			if(dis[u] > dis[x] + le[i]) {
				dis[u] = dis[x] + le[i];
				q.push((Node){dis[u], u});
			}
		}
	}
}

int main() {
	n = Re, m = Re, T = Re;
	for(reg int i = 1; i <= n; i++) p[i] = Re;
	for(reg int i = 1; i <= m; i++) {
		reg int u = Re, v = Re, w = Re;
		Link(u, v, w); Link(v, u, w);
	}
	dijsktra(1);
	memset(To, 63, sizeof(To));
	To[1] = 1;
	for(reg int i = 2; i <= n; i++) {
		for(reg int j = fi[i]; j; j = ne[j]) {
			if(dis[i] == dis[to[j]] + le[j] && To[i] > to[j]) {
				To[i] = to[j];
				Val[i] = dis[i] - T;
			}
		}
		in[To[i]]++;
	}
	queue<int>q;
	for(reg int i = 1; i <= n; i++) if(!in[i]) q.push(i);
	reg long long res = 0;
	while(!q.empty()) {
		reg int x = q.front(); q.pop();
		res = max(res, 1LL * Val[x] * p[x]);
		in[To[x]]--; p[To[x]] += p[x];
		if(!in[To[x]]) q.push(To[x]);
	}
	cout << res << endl;
	return 0;
}
```

---

## 作者：lgswdn_SA (赞：7)

可以理解为最短路树板子题？

既然题目要求最短路那么肯定先求出每一个点到 $1$ 的最短路（dijkstra），然后把所有奶牛的路径画出来——我告诉你，这是一棵树（建议手画一下）。

为什么呢？因为既然每条奶牛的路径是定了的，所以每条奶牛到 $1$ 的路径是唯一的，当然是树，是以 $1$ 为根的树。

这不就简单了嘛，对于每一个节点 $u$，设 $u$ 到 $1$ 的最短路是 $d_u$，那么如果我们连接 $(u,1)$ 获得的利益是 $\max \{0,(d(u)-t)\times s(u)\}$，其中 $s$ 为 $u$ 在最短路树中的子树的奶牛总数量。为什么呢？因为只有这个节点子树内的奶牛的路径会缩短。

最后我们看代码。代码中变量有一点点小混乱 $a_i$ 代表每个节点的奶牛数量，$c_i$ 代表走到 $i$ 的奶牛下一步去哪里。

```cpp
#include<bits/stdc++.h>
#define int long long
#define rep(i,a,b) for(register int i=a;i<=b;i++)
using namespace std;
const int N=10009,M=50009;

struct edge {int to,nxt,w;}e[M*2][2]; int hd[N][2],tot;
void add(int u,int v,int w,bool type) {
	e[++tot][type]=(edge){v,hd[u][type],w}; hd[u][type]=tot;
}

struct node {
	int u,val;
	bool operator < (const node &b) const {
		return val>b.val;
	}
};
int d[N];
void dijkstra(int n) {
	priority_queue<node>q; memset(d,0x3f,sizeof(d));
	q.push((node){n,d[n]=0});
	while(!q.empty()) {
		int u=q.top().u; q.pop();
		for(int i=hd[u][0],v;i;i=e[i][0].nxt) {
			v=e[i][0].to;
			if(d[v]>d[u]+e[i][0].w)
				d[v]=d[u]+e[i][0].w, q.push((node){v,d[v]});
		}
	}
}

int n,m,t,a[N],c[N],s[N],ans;

void dfs(int u,int fa) {
	s[u]=a[u];
	for(int i=hd[u][1],v;i;i=e[i][1].nxt) {
		if((v=e[i][1].to)==fa) continue;
		dfs(v,u);
		s[u]+=s[v];
	}
	ans=max(ans,s[u]*(d[u]-t));
}

signed main() {
	freopen("shortcut.in","r",stdin);
	freopen("shortcut.out","w",stdout);
	scanf("%lld%lld%lld",&n,&m,&t);
	rep(i,1,n) scanf("%lld",&a[i]);
	rep(i,1,m) {
		int u,v,w; scanf("%lld%lld%lld",&u,&v,&w);
		add(u,v,w,0), add(v,u,w,0);
	}
	dijkstra(1);
	rep(u,1,n) for(int i=hd[u][0];i;i=e[i][0].nxt) {
		int v=e[i][0].to;
		if(d[u]>d[v]) continue;
		if(d[u]+e[i][0].w==d[v]) {
			if(!c[v]) c[v]=u;
			else if(c[v]>u) c[v]=u;
		}
	}
	tot=0;
	rep(i,2,n) add(i,c[i],0,1),add(c[i],i,0,1);
	dfs(1,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Lonely_NewYear (赞：6)

# 洛谷 P5201 题解

## 前置知识 最短路树

最短路树指的是由每个点到原点的最短路的路径形成的一棵树。

所以怎么知道哪些边在最短路树中呢？可以发现，当 $dis_u+w_{u,v}=dis_v$ 时，$v$ 的最短路径必然经过了 $u$，此时可以给这个边和点打上标记，表示这个点和边已经在树中了（因为满足上面的式子的 $u$  未必只有一个）。

这道题还要求字典序，所以可以**从 $1$ 到 $n$ 枚举** $u$，找到可以加入树中的 $v$。

## 题目分析

既然求出了最短路树，再考虑近道的作用。可以发现在点 $1$ 和点 $u$ 之间连一条近道会使树上点 $u$ 所有的儿子和它本身的最短路减少 $dis_u-t$，所以可以从 $1$ 进行深度优先搜索，过程中求出每个点的儿子数量，然后在回溯前更新 $ans$。

## 代码

写了半天一直 wa 两个点，还去翻了讨论版，全改了还是 wa 两个，结果是没开双向边……

```cpp
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
struct edge
{
	int to,cost,next;
}g[100001];
int n,m,t,cnt,head[10001];
long long dis[10001],size[10001],ans;
bool vis[10001],flag[10001],can[100001];
void add(int u,int v,int w)
{
	g[++cnt]=(edge){v,w,head[u]};
	head[u]=cnt;
}
void spfa()
{
	for(int i=2;i<=n;i++)
	{
		dis[i]=1e18;
	}
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=g[i].next)
		{
			int v=g[i].to,w=g[i].cost;
			if(dis[u]+w<dis[v])
			{
				dis[v]=dis[u]+w;
				if(!vis[v])
				{
					q.push(v);
					vis[v]=1;
				}
			}
		}
	}
}
void dfs(int u)
{
	for(int i=head[u];i;i=g[i].next)
	{
		if(!can[i])
		{
			continue;
		}
		int v=g[i].to;
		dfs(v);
		size[u]+=size[v];
	}
	ans=max(ans,(dis[u]-t)*size[u]);
}
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&size[i]);
	}
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
		add(v,u,w);
	}
	spfa();
	for(int u=1;u<=n;u++)
	{
		for(int i=head[u];i;i=g[i].next)
		{
			int v=g[i].to,w=g[i].cost;
			if(!flag[v]&&dis[u]+w==dis[v])
			{
				can[i]=1;
				flag[v]=1;
			}
		}
	}
	dfs(1);
	printf("%lld",ans);
	return 0;
}
```

谢谢观看！

---

## 作者：SzTC (赞：6)

### 题目传送门

[P5201 [USACO19JAN]Shortcut G](https://www.luogu.com.cn/problem/P5201)
### 思路分析

看题解里的大佬都是用最短路树求解的，没学过最短路树的我看的一脸蒙。这里给出另一种解法（常数略大，但能跑过）。  
首先，题目要求字典序最小的最短路路径。先不管字典序，先在常规的最短路算法中求出最短路径。这个比较好求，只要在更新最短路的同时中加入这样一句话：  
```cpp
q[y]=x;
```
其中 $x$ 表示当前节点，$y$ 表示更新的节点。这样一句短短的代码，可以记录每一个当前节点的前驱节点，而前驱节点的前驱节点肯定是被记录过的，所以可以用一个递归函数输出路径：
```cpp
void print(int x)
{
	cout<<x<<" ";
	if(q[x]==0)return ;
	print(q[x]);
}
```
到了这一步以后，将记录节点的顺序改为最小字典序的方法就很简单了，只需要把原本代码中的松弛操作：
```cpp
if(dis[y]>dis[x]+e[i].w)
```
改为：
```cpp
if(dis[y]>dis[x]+e[i].w || (dis[y]==dis[x]+e[i].w && x<q[y]))
```
即可。  
显而易见的是，每一个点在到原点的路径中，一定会经过某一个节点（包括自身）。如果此时将近路连到这个节点上，那么所有经过这个点的牛就都不会走原本的路，而是走这条近路。拿题目举个栗子：  
$2$ 号节点的路径为：$2\to1$  
$4$ 号节点的路径为：$4\to2\to1$  
而 $2$ 号节点有 $2$ 头牛，$4$ 号节点有 $4$ 头牛。所以如果近路接到 $2$ 号节点，那么最后一共会有 $6$ 头牛走近路。  
而 $2$ 号节点到原点的最短路长度为 $5$，近路的长度为 $2$，所以一共减少消耗的时间为 $(5-2)\times6=18$  
同样：   
$3$ 号节点的路径为：$3\to1$  
$5$ 号节点的路径为：$5\to3\to1$   
而 $3$ 号节点有 $3$ 头牛，$5$ 号节点有 $5$ 头牛。所以如果近路接到 $3$ 号节点，那么最后一共会有 $8$ 头牛走近路。  
而 $3$ 号节点到原点的最短路长度为 $3$，近路的长度为 $2$，所以一共减少消耗的时间为 $(3-2)\times8=8$  

所以，只需要在每一个点的路径上加上这个点本身的点权，再枚举每个点，计算连边到这个点能够减少的时间，取最大值就好了。
### 代码
```cpp
#include<bits/stdc++.h>
#define inf 0x7f7f7f7f
using namespace std;
struct E{
	int to,next,w;
}e[111111];
int e_num,p[111111];
void e_add(int x,int y,int w)//邻接表存图 
{
	e[++e_num].to=y;
	e[e_num].w=w;
	e[e_num].next=p[x];
	p[x]=e_num; 
}
int n,m,t;
long long c[111111],a[111111];//注意开long long 
long long dis[111111];
int mark[111111];
int q[111111];
void SPFA()
{
	for(int i=1;i<=n;i++)dis[i]=inf;
	dis[1]=0;
	mark[1]=1;
	queue<int>que;
	que.push(1);
	while(!que.empty())
	{
		int x=que.front();
		mark[x]=0;
		que.pop();
		for(int i=p[x];i;i=e[i].next)
		{
			int y=e[i].to;
			if(dis[y]>dis[x]+e[i].w || (dis[y]==dis[x]+e[i].w && x<q[y]))//后面这部分是保持字典序的关键 
			{
				q[y]=x;//保存前驱节点 
				dis[y]=dis[x]+e[i].w;
				if(!mark[y])
				{
					mark[y]=1;
					que.push(y);
				}
			}
		}
	}
}
void print(int x,int c)
{
	a[x]+=c;
	if(q[x]==0)return ;
	print(q[x],c);
}
int main()
{
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",c+i);
	}
	for(int i=1;i<=m;i++)
	{
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		e_add(x,y,w);//双向建边 
		e_add(y,x,w);
	}
	SPFA();//考试的时候如果没有负权边不建议用SPFA（它死了）...
	for(int i=1;i<=n;i++)
		print(i,c[i]);//累加牛的数量 
	long long ans=0;//不开____见祖宗 
	for(int i=1;i<=n;i++)
		ans=max(ans,(dis[i]-t)*a[i]);//枚举 
	cout<<ans;
	return 0;
}
```

---

## 作者：pocafup (赞：4)

刚开始拿到这题的时候我直接懵逼了:字典序是啥玩意,这东西貌似很高大尚的亚子

然而,认真读了一下题后,我发现其实这道题跟我做过的某些题很像

比如: [timeline](https://www.luogu.com.cn/problem/P6145)

可能大佬们会说,貌似这题跟timeline没有一毛钱关系啊...

其实,这道题可以理解为,算出每个点到1的最短距离,然后计算每个点对点1连线最大能减少的距离

那么问题来了,你怎么知道这个点跟1连线后有几头牛改变了路径?

这里就得到了这题的核心思想:我们发现,奶牛只有在走原先路径时遇到捷径才会去.他们不会刻意走去捷径.

于是,这题就可以转化为,求出(这个点到点1的距离-连边的距离)*经过这点的奶牛的数量的和

~~说人话~~

**求出每个点的子树的数量*从这个节点用捷径能节省的距离**

这样会好理解点吗?

好下面正式开始解题:

1.求最短距离

模板题,从点1用 $dijkstra$ 求最短距离,这个不详细讲

2.求子树

**敲重点:**
这里就到了跟timeline相似的地方了.我们发现,如果一个点的子树还没有处理完,那么我们无法用这个点去更新他的父节点(如果无法理解可以看我的timeline的解法([timeline题解](https://www.cnblogs.com/DannyXu/p/12388965.html)).

所以,对于每个节点,我们将其父节点设为不可更新.然后,我们将所有可以更新的节点放进 $queue$ 里. 每当一个子节点要更新父节点的时候,我们将父节点的子叶数量-1.当一个父节点没有子叶了,那么他将会转化为一个子节点,然后我们就可以拿它继续更新他的父节点了

```cpp
for (pp v : adj[qf]){
      if (dist[v.f]==dist[qf]-v.s){
        constrain[v.f]--;//父节点子叶--
        pos[v.f]+=pos[qf];
        if (constrain[v.f]==0) q.push(v.f);//如果父节点没有子叶了
        break;
      }
    }
```

3.答案

答案之前其实已经提到过,就是每个点的子叶数量*用捷径所能减少的距离

```cpp
for (long long i=n;i>=1;i--){
  ans = max(ans,pos[i]*(dist[i]-k));
}

```

4.字典序的求法

这里是很多链式前向星的大佬卡住的地方.正常的方法是用fa存.然而,我们发现,如果用vector存图,我们可以将去的点排序,然后将遇到的第一个父节点(也就是距离最短的点)扔进队列.

这里我写的spfa没写dij,但是想法是一样的

又到了具体代码的时间了:

```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
const long long MAXN = 1e5+5;
#define pp pair<long long,long long>
#define f first
#define s second
long long dist[MAXN], n,m,k, pos[MAXN],constrain[MAXN], ans= 0 ;
vector<pp> adj[MAXN];
bool inq[MAXN],vis[MAXN];
inline void spfa(long long source){
  memset(dist,0x3f3f3f3f,sizeof(dist));
  dist[source] = 0;
  queue<long long> q;
  q.push(source);
  while(!q.empty()){
    long long qf = q.front();q.pop();
    inq[qf] = false;
    for (pp v : adj[qf]){
      if (dist[v.f]>dist[qf]+v.s){
        dist[v.f] = dist[qf]+v.s;
        if (!inq[v.f]) inq[v.f] = true,q.push(v.f);
      }
    }
  }
}//板子,不解释
inline void dfs(long long source){
  for (pp v : adj[source]){
    if (dist[v.f]==dist[source]-v.s){//如果某个点到点1的距离-他去父节点的距离==父节点到点1的距离
      constrain[v.f]++;
      break;//已经改过,break能保证字典序最小
    }
  }
}
inline void bfs(){
  queue<int> q;
  for (int i=1;i<=n;i++) if (!constrain[i]) q.push(i);//如果是子叶
  while(!q.empty()){
    int qf = q.front();q.pop();
    for (pp v : adj[qf]){
      if (dist[v.f]==dist[qf]-v.s){//同上
        constrain[v.f]--;//子叶-1
        pos[v.f]+=pos[qf];//子叶数量相加
        if (constrain[v.f]==0) q.push(v.f);//如果父节点变成了子叶
        break;//字典序
      }
    }
  }
}
long long a,b,c;
int main(){
  cin >> n >> m >> k;
  for (long long i=1;i<=n;i++) cin >> pos[i];
  for (long long i=0;i<m;i++){
    cin >> a >> b >> c;
    adj[a].push_back(make_pair(b,c));
    adj[b].push_back(make_pair(a,c));
    //vector的建边方式
  }
  for (long long i=1;i<=n;i++) sort(adj[i].begin(),adj[i].end());//排序保证字典序
  spfa(1);//板子
  for (long long i=1;i<=n;i++) dfs(i);//这名字...其实不是dfs
  bfs();
  for (long long i=n;i>=1;i--) ans = max(ans,pos[i]*(dist[i]-k));//求答案
  cout << ans;
}
```

---

## 作者：Na2PtCl6 (赞：2)

## 分析题目
### 思路
$\because$ 牛棚位于且仅位于 1 号点 

$\therefore$ 所有牛走到牛棚的路线会形成一个以 1 号点为根节点的树

这就是最短路径树。

我们可以把这棵树建出来，然后统计它每个节点 $i$ 所在的子树上 **牛的个数** $s_i$。

$\because$ 在牛的最短路径上的点才会被牛看见

$\therefore$ 链接牛棚和点 $i$ 的能节约 $s_i$ 头牛的 $d_i-t$ 个单位时间。（$d_i$ 表示点 $i$ 到牛棚的最短路径长度，$t$ 表示链接牛棚和点 $i$ 的路径的长度）

我们遍历每个点，更新答案即可。

别忘了开`long long`。

### 记录路径
考虑这个图是无向图，即最短路 **不受走的方向的影响**，我们可以从牛棚出发，跑一遍 dijkstra ,并用一个链式的数组记录从牛棚出发的所有最短路径。

注意两点

1.记录路径时要写成到达的点指向现在的点，建出来的路径是从终点通向牛棚的

2.路径长度相同的最短路别忘记处理

这个图如果是无向图的话就应该要反向建边，其他的不用改。

### 建树
因为我们已经把最短路径记录好了，所以我们只遍历第 2\~n 个点，并把它能到达的点和它连边。

注意要双向加边

### 统计子树上牛的个数
在输入的过程中，$s_i$要被赋值成点 $i$ 上牛的数量

我们从牛棚开始 dfs，把每个 $s_i$ 加上它的子节点的 $s_i$ 即可。

## 代码实现
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=50004;
bool vis[maxn];
int n,m,t,u,v,w,res;
int dis[maxn],cow[maxn],nxt[maxn],size[maxn];
vector < int > tree[maxn];
struct edge{ int to,w;};
vector < edge > g[maxn];
struct node{ 
	int id,len;
	bool operator < (const node &comp) const{
		return comp.len<len;
	}
};
priority_queue < node > q;

inline const int _max(const int &a,const int &b){
	return a>b?a:b;
}

inline void read(int &x){
	char c=getchar();x=0;
	for(;c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';c=getchar())
		x=x*10+(c^48);
}

void dij(int start){
	memset(dis,0x3f,sizeof(dis));
	dis[start]=0;
	q.push((node){start,0});
	while(!q.empty()){
		node t=q.top();
		q.pop();
		int ind=t.id;
		if(vis[ind])
			continue;
		vis[ind]=1;
		for(int i=0;i<g[ind].size();i++){
			edge now=g[ind][i];
			int to=now.to,l=dis[ind]+now.w;
			if(dis[to]>l){
				nxt[to]=ind;
				dis[to]=l;
				if(!vis[to])
					q.push((node){to,l});
			}
			if(dis[to]==l&&nxt[to]>ind)
				nxt[to]=ind;
		}
	}
}

void dfs(int node,int fa){
	for(int i=0;i<tree[node].size();i++){
		int now=tree[node][i];
		if(now==fa)
			continue;
		dfs(now,node);
		size[node]+=size[now];
	}
	res=_max(res,(dis[node]-t)*size[node]);
}

signed main(){
	read(n),read(m),read(t);
	for(int i=1;i<=n;i++)
		read(size[i]);
	while(m--){
		read(u),read(v),read(w);
		g[u].push_back((edge){v,w});
		g[v].push_back((edge){u,w});
	}
	dij(1);
	for(int i=2;i<=n;i++){
		tree[i].push_back(nxt[i]);
		tree[nxt[i]].push_back(i);
	}
	dfs(1,0);
	printf("%lld",res); 
	return 0;
}
```

---

