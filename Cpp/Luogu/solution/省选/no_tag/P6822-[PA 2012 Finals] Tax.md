# [PA 2012 Finals] Tax

## 题目描述

给出一个 $n$ 个点 $m$ 条边的无向图，经过一个点的代价是进入和离开这个点的两条边的边权的较大值，求从起点 $1$ 到点 $n$ 的最小代价。起点的代价是离开起点的边的边权，终点的代价是进入终点的边的边权。

## 说明/提示

$1\leq n\leq 10^5$，$1\leq m\leq 2\times 10^5$，$1\leq c\leq 10^6$。

## 样例 #1

### 输入

```
4 5
1 2 5
1 3 2
2 3 1
2 4 4
3 4 8```

### 输出

```
12```

# 题解

## 作者：STDquantum (赞：19)

原题链接：[P6822 [PA2012] Tax](https://www.luogu.com.cn/problem/P6822)。

虽然说是套路题，但是如果是第一次做的话也还是有些困难的，于是我就来用图形形象化地说明一下。只是便于理解，并没有正解的推导过程。

直接说做法（连边均为有向边）：

0. 建立超级源点 $s$ 和超级汇点 $t$，并且无向边拆成有向边、化边为点。

1. 对于所有从 $1$ 出发的边，从 $s$ 向这些边对应的点连权值为原图权值的边；对于所有结束于 $n$ 的边，从这些边对应的点向 $t$ 连权值为原图权值的边。
2. 所有边向自己的反向边连权值为原图权值的边。
3. 将一个点出发的所有边按照边权排序，对于排序后相邻的两条边 $i$ 与 $i+1$，从 $i$ 向 $i+1$ 连权值为 $w_{i+1}-w_i$ 的边，从 $i+1$ 向 $i$ 连权值为 $0$ 的边。

到此连边过程就结束了，从 $s$ 跑单源最短路（不能用 SPFA！！！），$dis_t$ 即为题中所求的值。

现在举一个简单的例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/rkuu5h7d.png)

边上方的数字代表从左到右的有向边的编号，边下方的数字代表从右到左的有向边的编号。

按照所给方式连边后的图（节点编号对应上图边的编号）：

![](https://cdn.luogu.com.cn/upload/image_hosting/klzif8ok.png)

现在我们来看一条合法的从 $s$ 到 $t$ 的路径：$s\rightarrow 1\rightarrow 5\rightarrow3\rightarrow t$。

为防止语义冲突，在原图中的边定义为 $(i,j)$，$i$ 与 $j$ 均为原图中节点编号。

- $s\rightarrow 1$ 的边权为 $(1,2)$ 边权，代表从 $1$ 出来时的代价。
- $1\rightarrow5\rightarrow3$ 中，前者边权为 $(1,2)$ 边权，后者边权为 $(1,2), (2,4)$ 的边权差距。此处说为差距是因为不清楚两者之间的大小关系，若 $(1,2)$ 大于 $(2,4)$，那么 $5\rightarrow3$ 的权值为 $0$，合到一块 $1\rightarrow5\rightarrow3$ 的权值就为 $(1,2)$ 的边权；若 $(1,2)$ 小于 $(2,4)$，那么 $5\rightarrow3$ 的权值为 $w_{(2,4)}-w_{(1,2)}$，合到一块 $1\rightarrow5\rightarrow3$ 的权值就为 $(2,4)$ 的边权。
- $3\rightarrow t$ 的边权为 $(2,4)$ 边权，代表到 $n$ 结束的代价。

引入不同边的差值可以让我们直接计算出最大边权，从而避免了讨论的情况。

新图中的点分为了三个集合，源汇点、正向边和反向边。

在新图中可以发现如下性质：

- 当走源汇点和正向边之间的边时，所计算的是离开 $1$ 或来到 $n$ 的代价；
- 当走正向边和反向边内部的边时（其实就是一个点出来的边），代表着反悔操作，也就是换了一条边走。
- 当在正向和反向边之间横跳时（如 $1\rightarrow5\rightarrow3$），代表又走过了一个节点，并计算了最大边的权值。

就这样。

C++98（去掉了C++11的特性和一些可能会让人迷惑的地方）：码风有一（~~亿~~）点毒瘤，可以拿来对拍。

[云剪贴板](https://www.luogu.com.cn/paste/pz3ky7pe)。

C++11版本：

```cpp
#include <bits/stdc++.h>
using namespace std;

namespace Sweet {

template <typename T> inline void read(T &x) {
    char ch;
    int f = 1;
    while (ch = getchar(), ch > '9' || ch < '0')
        if (ch == '-') f = -1;
    x = (ch ^ 48);
    while (ch = getchar(), ch >= '0' && ch <= '9')
        x = x * 10 + (ch ^ 48);
    x *= f;
}
template <typename T> inline void write(T x) {
    static int stk[100], top = 0;
    if (x == 0) return (void)putchar('0');
    if (x < 0) x = -x, putchar('-');
    while (x) stk[++top] = x % 10, x /= 10;
    while (top) putchar(stk[top--] + '0');
}

typedef long long ll;
const int N = 1e5 + 10, V = 4e5 + 10;

basic_string<pair<int, int> > e[V];
inline void add(int x, int y, int z) { e[x] += {y, z}; } // +=相当于push_back

struct T {
    int x;
    ll dis;
    T(int X, ll Dis) : x(X), dis(Dis) {}
    bool operator<(const T &rhs) const { return dis > rhs.dis; }
};
extern int s, t;
ll dis[V];
ll Dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<T> q;
    q.emplace(s, dis[s] = 0);
    static T u(0, 0);
    while (!q.empty()) {
        u = q.top(), q.pop();
        if (u.dis != dis[u.x]) continue;
        for (auto v : e[u.x]) {
            if (dis[v.first] > u.dis + v.second) {
                q.emplace(v.first, dis[v.first] = u.dis + v.second);
            }
        }
    }
    return dis[t];
}

struct Edge {
    int v, w, id;
    bool operator<(const Edge &rhs) const { return w < rhs.w; }
};
basic_string<Edge> g[N]; // 似乎比vector要快一点？
basic_string<Edge>::iterator it;

int n, m, s = 0, t = 1;
inline void main() {
    read(n), read(m);
    for (int i = 1, a, b, c; i <= m; ++i) {
        read(a), read(b), read(c);
        g[a] += {b, c, i << 1}, g[b] += {a, c, i << 1 | 1}; // 编号方式：异或1得到反向边
    }
    for (int i = 1; i <= n; ++i) {
        if (g[i].empty()) continue; // 后面迭代器的写法要求不能为空，直接用下标遍历不用判
        sort(g[i].begin(), g[i].end());
        for (auto j : g[i]) {
            add(j.id ^ 1, j.id, j.w);
            (i == 1) && (add(s, j.id, j.w), 0); // 短路表达式 = if
            (j.v == n) && (add(j.id, t, j.w), 0);
        }
        for (it = g[i].begin(), ++it; it != g[i].end(); ++it) {
            add(it->id, (it - 1)->id, 0);
            add((it - 1)->id, it->id, it->w - (it - 1)->w);
        }
    }
    write(Dijkstra());
}

}    // namespace Sweet

int main() {
    Sweet::main();
    return 0;
}
```



---

## 作者：一之濑帆波 (赞：11)

很好的建图思想。

这题一条路径的权值取决于点，但是点的权值取决于入边和出边。我们尝试统一使点的贡献取决于其入边，让点 $u$ 的入边和出边（另一点 $v$ 的入边）产生联系。

点 $u$ 作为若干条边的“中转站”，若从权值较小的入边到权值较大的出边，应该让入边的贡献增加一部分；若从权值较大的入边到权值较小的出边，则无影响。

于是我们把边作为点，建出一个新图。

- 先将一条边拆成两个点 $i,i'$，以原边边权连接，并分属于边的两个端点；
- 原图同一点的相邻的边，其中两条为 $i,j$，假设 $val_i<val_j$，则
    - 连边 $i\to j$，权值为 $val_j-val_i$；
    - 连边 $j\to i$，权值为 $0$；
- 新建源点 $s$，向所有原图 $1$ 点的出边 $i$，连接 $s\to i$，权值为 $val_i$。

其中第二条通过排序后差分建边，可以将边数降至 $\mathcal O(m)$。

跑最短路，然后枚举原图 $n$ 点的入边寻找最优答案。

复杂度 $\mathcal O(m\log m)$。

```cpp
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using i64 = long long;

const i64 Inf = 0x3f3f3f3f3f3f3f3f;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> e(n);
    std::vector<int> val(m * 2);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        val[i] = val[i + m] = w;
        e[u].push_back(i);
        e[v].push_back(i + m);
    }
    int s = m * 2;
    std::vector<std::vector<std::pair<int, int>>> g(m * 2 + 1);
    for (int i = 0; i < m; ++i) {
        g[i].emplace_back(i + m, val[i]);
        g[i + m].emplace_back(i, val[i]);
    }
    for (auto i : e[0])
        g[s].emplace_back(i, val[i]);
    for (int u = 1; u < n - 1; ++u) {
        std::sort(e[u].begin(), e[u].end(), [&](int x, int y) { return val[x] < val[y]; });
        for (int i = 0; i < int(e[u].size()) - 1; ++i) {
            int x = e[u][i], y = e[u][i + 1];
            g[x].emplace_back(y, val[y] - val[x]);
            g[y].emplace_back(x, 0);
        }
    }

    std::vector<i64> dis(m * 2 + 1, Inf);
    std::vector<bool> vis(m * 2 + 1);
    dis[s] = 0;
    std::priority_queue<std::pair<i64, int>> hp;
    hp.push({0, s});
    while (!hp.empty()) {
        int u = hp.top().second;
        hp.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (auto i : g[u]) {
            int v = i.first;
            int w = i.second;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                hp.push({-dis[v], v});
            }
        }
    }

    i64 ans = Inf;
    for (auto i : e[n - 1])
        ans = std::min(ans, dis[i]);
    std::cout << ans << '\n';

    return 0;
}
```

---

## 作者：1saunoya (赞：11)

套路题（


考虑最朴素的方法。

$a \to b \to c$ 的边设为 $\max(z1,z2)$ 这样直接跑最短路就可以了，但是 边数是 $m^2$  的。

考虑优化。

枚举 $b$  点。

把 $b$ 的所有出边 $id\{\}$ 全部找出来。(编号)

然后我们将这些出边的边权排个序，把 **边的编号** 直接相邻做差连上，这样的话边数就会变成 $m$，并且效果等同。


然后就是喜闻乐见的最短路环节了。我们要新建两个点，一个起点一个终点。这些边暴力建边就行了。

这题卡 spfa。

```cpp
#include<bits/stdc++.h>
#define rep(i,x,y) for(int i=x;i<=y;i++)
using namespace std;
void cmax(int&x,const int&y) {
	x=x>y?x:y;
}
void cmin(int&x,const int&y) {
	x=x<y?x:y;
}
int n,m;
const int N=4e5+5;
struct node {
	int x,y,z;
} edge[N],q[N];
int cnt=0;
struct Edge {
	int v,nxt,w;
} e[N];
int head[N],ec=0;
void add(int u,int v,int w) {
	e[++ec]= {v,head[u],w};
	head[u]=ec;
}
vector<int>g[N],val[N];
long long d[N];
bool vis[N];
using pii=pair<int,int>;
priority_queue<pii,vector<pii>,greater<pii>>qq;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin>>n>>m;
	rep(i,1,m) {
		int x,y,z;
		cin>>x>>y>>z;
		edge[++cnt]= {x,y,z};
		edge[++cnt]= {y,x,z};
		add(x,cnt,cnt-1);
		add(y,cnt-1,cnt);
	}
	rep(i,1,n) {
		int t=0;
		for(int j=head[i]; j; j=e[j].nxt)
			q[++t]= {e[j].v,e[j].w,edge[e[j].v].z};
		if(!t)continue;
		sort(q+1,q+t+1,[](node x,node y) {
			return x.z<y.z;
		});
		rep(j,1,t) {
			int x=q[j].x;
			int y=q[j].y;
			int z=q[j].z;
			g[x].push_back(y);
			val[x].push_back(z);
			g[y].push_back(x);
			val[y].push_back(z);
		}
		rep(j,1,t-1) {
			int y=q[j].y;
			int z=q[j].z;
			++j;
			int yy=q[j].y;
			int zz=q[j].z;
			--j;
			g[y].push_back(yy);
			val[y].push_back(zz-z);
			g[yy].push_back(y);
			val[yy].push_back(0);
		}
	}
	int s,t;
	s=cnt+1;
	t=s+1;
	rep(i,1,cnt) {
		if(edge[i].x==1) {
			g[s].push_back(i);
			val[s].push_back(edge[i].z);
		}
		if(edge[i].y==n) {
			g[i].push_back(t);
			val[i].push_back(edge[i].z);
		}
	}
	memset(d,0x3f,sizeof(d));
	qq.emplace(d[s]=0,s);
	while(!qq.empty()) {
		auto t=qq.top();
		qq.pop();
		int u=t.second;
		int dis=t.first;
		if(d[u]<dis)continue;
		int sz=g[u].size();
		rep(i,0,sz-1) {
			int v=g[u][i];
			int w=val[u][i];
			if(d[v]>d[u]+w) {
				qq.emplace(d[v]=d[u]+w,v);
			}
		}
	}
	cout<<d[t]<<'\n';
	return 0;
}
```

---

## 作者：Booksnow (赞：6)

# Tax

## 题面

给定一个 $n$ 个点 $m$ 条边的无向图，经过一个点的代价是进入和离开这个点的两条边的两条边的边权较大值，求从起点 $1$ 到点 $n$ 的最小代价。

起点的代价是离开起点的边的边权，终点的代价是进入终点的边的边权。

$n\leq 10^5,m\leq 2\times 10^5$
 
## 分析

最先想到的实际上是暴力，在 $DJ$ 的状态上进一步记录了转移到当前状态的边权，从而进一步转移。

但很快我们会发现这不对，我们的边权具有后效性，不满足 $DJ$ 从当前最小值转移必将得到下一个最小值的性质。

一时间好像没有了其它思路。

重新回到代价的定义，一个点的代价和路径上经过它的两条边有关，即与它相邻的一些边有关。

考虑把边转化成点。

一条无向边实际上对应的是两条有向边，也即对应两个点，在这两个点之间建立一条长度为边原长的边。

![](https://www.helloimg.com/images/2021/11/04/CYDXRY.png)

观察这幅图，对于每一个点 $x$ ，我们将与它相连的边按照边权大小排序，边权小的边向第一个边权比它大的边连一条边权为它们权值差的有向边，再连接一条边权为 $0$ 的反相边。

之后我们建立一个新的起始点 $s$ ，一个新的终点 $t$ ，$s$ 与所有与 $1$ 相连的边建立一条长度为此边原长的有向边，所有与 $n$ 相连的边与 $t$ 建立一条长度为 $0$ 的有向边。

考虑这样建图为什么是对的，首先对于起点，我们前往任意一条边都将会花费一个初始代价，与题意相符，而我们的边在进入下一条边时，由于我们的代价是差值，对于小的边前往大的边，代价会很自然的变成较大值，而大的边前往小的边，代价为 $0$ ，仍然为我们的大边。

![](https://www.helloimg.com/images/2021/11/04/CYDeL9.png)

通过这样的连边，我们能够表示出每个点的代价，事实上，由于我们把初始的一条边拆成了两个点，当我们在进行如上图中 $u$ 到 $v$ 这类的转移时，相当于我们有一次切换，从由绿点散发出去的边转化成了从黄点散发出去的边，贡献的初始值还是我们的 $u$ 。即等价于我们已经算出了绿点的代价，接下来我们正在计算的是通过黄点的代价。

这样，我们就巧妙的通过不停的这样转化，表示出了题目中的代价，跑一遍最短路即可。

## CODE

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10,M=2e5+10,P=2e6+10;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') w*=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
struct Edge{ int v,w; };
struct BIT{ int id1,id2,val; }arr[M];
struct node{
	int p,val;
	bool operator <(const node &x)const{
		return val>x.val;
	}
};
int n,m,cnt,s,t;
int tot=-1,v[2*M],w[2*M],nex[2*M],first[N];
vector<Edge> vec[P];
inline void Add(int x,int y,int z)
{
	nex[++tot]=first[x];
	first[x]=tot;
	v[tot]=y,w[tot]=z;
}
inline bool cmp(BIT x,BIT y) { return x.val<y.val; }
int dis[P];
bool vis[P];
priority_queue<node> q;
inline void DJ()
{
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	q.push((node){s,0});
	while(!q.empty()){
		node now=q.top(); q.pop();
		if(vis[now.p]) continue;
		vis[now.p]=true;
		for(register int i=0;i<vec[now.p].size();i++){
			int to=vec[now.p][i].v,d=vec[now.p][i].w;
			//cout<<to<<endl; 
			if(dis[to]>dis[now.p]+d){
				dis[to]=dis[now.p]+d;
				q.push((node){to,dis[to]});
			}
		}
	}
}
signed main()
{
	memset(first,-1,sizeof(first));
	n=read(),m=read();
	for(register int i=1;i<=m;i++){
		int x=read(),y=read(),z=read();
		Add(x,y,z),Add(y,x,z); 
	}
	for(register int i=1;i<=n;i++){ //枚举起点 
		cnt=0;
		for(register int j=first[i];j!=-1;j=nex[j]){
			arr[++cnt].id1=j^1,arr[cnt].id2=j;
			arr[cnt].val=w[j];
		}
		sort(arr+1,arr+cnt+1,cmp);
		for(register int j=1;j<=cnt;j++){
			//cout<<
			vec[arr[j].id1].push_back((Edge){arr[j].id2,arr[j].val});
			if(j!=1) vec[arr[j].id2].push_back((Edge){arr[j-1].id2,0});
			if(j!=cnt) vec[arr[j].id2].push_back((Edge){arr[j+1].id2,arr[j+1].val-arr[j].val});
		}
	}
	s=tot+1,t=tot+2;
	for(register int i=first[1];i!=-1;i=nex[i]) vec[s].push_back((Edge){i,w[i]});
	for(register int i=first[n];i!=-1;i=nex[i]) vec[i].push_back((Edge){t,0});
	DJ();
	printf("%lld\n",dis[t]);
	return 0;
}
```


---

## 作者：Butterfly_qwq (赞：4)

可以想到建新图.

我们可以把无向图的边拆开变成有向图，之后将边变成点

1. 建立超级源点，原点连向所有起点为 $1$ 的边化成的点，边权为原图边权。
2. 建立超级汇点，所有终点为 $n$ 的边化成的点连向汇点，边权为原图边权。
3. 将所有边与它在原图中的反边相连，边权为原图边权。
4. 将原图中一个点连的边按边权排序，设排序完之后所有边化成的点为 $w_1,w_2,\dots,w_k$，在原图的边权为 $t_1,t_2,\dots,t_k$，则将 $w_i$ 和 $w_{i-1}$ 连单向边，边权为 $0$，将 $w_{i-1}$ 和 $w_i$ 连单向边，边权为 $t_i-t_{i-1}$。

在超级原点和超级汇点之间跑最短路，输出结果即可。

提示：

1. 如果你 #1#2 WA，不开 long long 见祖宗
2. 如果你有 TLE 也有 AC，且建图正确，关于 SPFA，它死了

Code:

```
/*
Start Coding:2023.8.13 10:13
Finish Debugging:2023.8.13 11:31
Author:FeS2_qwq
*/
#include<bits/stdc++.h>
#define int long long//不 开 long long 见 祖 宗 ( 悲
#define pii pair<int,int>
#define pip pair<int,pii>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
const int N=114514;
using namespace std;
int cnt1=1;
vector<pip> g[N];
int cnt2,head[N*4];
int dis[N*4];
struct edge
{
	int to,nxt,w;
}e[N*25];//理论上最大应该是M*2*2*3=N*24，但开N*9就能过（玄学）
void add(int u,int v,int w)
{
	e[++cnt2]={v,head[u],w};
	head[u]=cnt2;
}
bool cmp(pip a,pip b)
{
	return a.se.fi<b.se.fi;
}
void dij()
{
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	priority_queue<pii,vector<pii>,greater<pii>> q;
	q.push(mp(0,0));
	while(!q.empty())
	{
		int f=q.top().fi,u=q.top().se;
		q.pop();
		if(f!=dis[u])continue;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].to,w=e[i].w;
			if(dis[v]>dis[u]+w)
			{
				dis[v]=dis[u]+w;
				q.push(mp(dis[v],v));
			}
		}
	}
}
signed main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0,a,b,c;i<m;i++)
	{
		cin>>a>>b>>c;
		g[a].pb(mp(b,mp(c,++cnt1)));
		g[b].pb(mp(a,mp(c,++cnt1)));
	}
	for(auto ed:g[1])//建新图部分 注：超级源点为0，超级汇点为1
	{//对应步骤1 
      int id=ed.se.se,w=ed.se.fi;
		add(0,id,w); 
   }
   for(auto ed:g[n])//对应步骤2 注：由于原图是无向图，所以由n出发的边就是连向n的边的反边
	{
		int id=ed.se.se,w=ed.se.fi;
		add(id^1,1,w);//异或1即为求反边 
	}
	for(int i=1;i<=n;i++)//对应步骤3 
	{
		for(auto ed:g[i])
		{
			int id=ed.se.se,w=ed.se.fi;
			add(id,id^1,w);
		}
   }
   for(int i=1;i<=n;i++)//对应步骤4 
	{
		if(g[i].empty())continue;
		sort(g[i].begin(),g[i].end(),cmp);
		for(auto it=g[i].begin()+1;it!=g[i].end();it++)
		{
			int nid=it->se.se,lid=(it-1)->se.se;
			int nw=it->se.fi,lw=(it-1)->se.fi;
			add(nid,lid,0);
			add(lid,nid,nw-lw);
		}
   }//建图完成，跑最短路即可
	dij();
	cout<<dis[1];
	return 0; 
}
```

---

## 作者：wgyhm (赞：3)

## Description

https://www.luogu.com.cn/problem/P6822

## Solution

为什么题解都是建新图啊。虽然很高妙但是想不到啊。

考虑求最短路 dj 的过程，堆里记录每个点的最短路然后取出这个点来扩展。但是这道题只记录点的信息是不够的。我们考虑堆中记录边的信息。记 $d_i$ 表示到第 $i$ 条边 $(x,y,z)$，$x$ 的点权已经算了而 $y$ 的点权还没算的最短路。

考虑更新，枚举 $y$ 的出边 $(y,t,w)$，设其编号为 $j$ 。如果 $z\ge w$ 则 $d_j\gets \min d_i+z$，否则 $d_j\gets d_i+w$。容易想到把边权拍完序以后，重新给边标号，然后用线段树维护。

但是这样太蠢了不是吗？考虑堆的过程，每次拿最小的一条边进行更新。例如 $z\ge w$，如果有更小的 $d_k$ 已经在 $i$ 之前更新过了，则 $i$ 因为在 $k$ 之后出堆而做无效更新。换句话说，每条边只会被 $z\le w$ 的边更新一次，$z\ge w$ 的边更新一次。

这样就可以双指针了。一个小根堆维护 $d_i$，另外一个小根堆维护 $d_i+z$ 。然后双指针更新。事实上我们可以放在一个堆里。

复杂度 $O(m\log m)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define maxn 400005
#define put() putchar('\n')
#define Tp template<typename T>
#define Ts template<typename T,typename... Ar>
using namespace std;
Tp void read(T &x){
    int f=1;x=0;char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1;c=getchar();}
    while (c>='0'&&c<='9') {x=x*10+c-'0';c=getchar();}
    x*=f;
}
namespace Debug{
	Tp void _debug(char* f,T t){cerr<<f<<'='<<t<<endl;}
	Ts void _debug(char* f,T x,Ar... y){while(*f!=',') cerr<<*f++;cerr<<'='<<x<<",";_debug(f+1,y...);}
	#define gdb(...) _debug((char*)#__VA_ARGS__,__VA_ARGS__)
}using namespace Debug;
#define fi first
#define se second
#define mk make_pair
const int mod=1e9+7;
int power(int x,int y=mod-2) {
	int sum=1;
	while (y) {
		if (y&1) sum=sum*x%mod;
		x=x*x%mod;y>>=1;
	}
	return sum;
}
int n,m;
struct yyy {
	int to,w,id;
	bool operator <(const yyy &tmp) const {
		return w<tmp.w;
	}
};
struct node {
	int x,y,z;
}e[maxn];
vector<yyy>to[maxn];
int dis[maxn];
int L[maxn],R[maxn],vis[maxn][2];
priority_queue<pair<int,pair<int,int> > >q;
signed main(void){
	int i,x,y,z,l,r,fl;
	read(n);read(m);
	for (i=1;i<=m;i++) {
		read(x);read(y);read(z);
		to[x].push_back((yyy){y,z,i});
		to[y].push_back((yyy){x,z,i+m});
		e[i].x=x,e[i].y=y,e[i].z=z;
		e[i+m].x=y,e[i+m].y=x,e[i+m].z=z;
	}
	for (i=1;i<=n;i++) sort(to[i].begin(),to[i].end()),R[i]=to[i].size()-1;
	memset(dis,0x3f,sizeof(dis));
	for (auto tmp:to[1]) {
		dis[tmp.id]=tmp.w;
		q.push(mk(-dis[tmp.id],mk(tmp.id,1)));
		q.push(mk(-dis[tmp.id]-tmp.w,mk(tmp.id,0)));
	}
	while (!q.empty()) {
		i=q.top().se.fi;fl=q.top().se.se;q.pop();
		if (vis[i][fl]) continue;vis[i][fl]=1;
		x=e[i].y;
		// gdb(i,dis[i],e[i].x,e[i].y,e[i].z);
		if (fl==0) {
			l=L[x];
			while (l<to[x].size()&&to[x][l].w<=e[i].z) {
				if (dis[to[x][l].id]>dis[i]+e[i].z) {
					dis[to[x][l].id]=dis[i]+e[i].z;
					q.push(mk(-dis[to[x][l].id],mk(to[x][l].id,1)));
					q.push(mk(-dis[to[x][l].id]-e[to[x][l].id].z,mk(to[x][l].id,0)));
				}
				l++;
			} 
			L[x]=l;
		}
		if (fl==1) {
			r=R[x];
			while (r>=0&&to[x][r].w>=e[i].z) {
				if (dis[to[x][r].id]>dis[i]+e[to[x][r].id].z) {
					dis[to[x][r].id]=dis[i]+e[to[x][r].id].z;
					q.push(mk(-dis[to[x][r].id],mk(to[x][r].id,1)));
					q.push(mk(-dis[to[x][r].id]-e[to[x][r].id].z,mk(to[x][r].id,0)));
				} 
				r--;
			}
			R[x]=r;
		}
	}
	int ans=1e18;
	for (i=1;i<=m*2;i++) if (e[i].y==n) ans=min(ans,dis[i]+e[i].z);
	printf("%lld\n",ans);
	return 0;
}
//i=begin && g++ $i.cpp -o $i -std=c++14 && ./$i
```



---

## 作者：aaaaaaaawsl (赞：2)

果然还是写的全面一点吧。

为了方便阅读，下文原图的边点权不变，**新图**的**边点权**用黑体表示。最短路只**在新图**上跑，和原图没有关系。

----

对于一个点，经过这个点的代价是进入和离开这个点的两条边的边权的较大值，所以可以想到一个比较暴力的方法：建新图，对于一个点，把它连着的每条边看做一个**点**，把每一条边对应的**点**向其他的边对应的**点**连**边**，**边权**为这两条边边权的最大值。等于模拟了经过这两条原边的情况。

如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/3490vm24.png)

黑图为原图，红图为**新图**。

这样建一个虚拟源点，与 $1$ 号点连边，边权为 $0$，建一个虚拟汇点，与 $n$ 号点连边，边权为 $0$。把这些加上题目所给的图作为原图，然后建出**新图**，在**新图**上以虚拟源点与 $1$ 号点连的边对应的**点**为原点在**新图**上跑最短路，取出 $n$ 号点与虚拟汇点连的边对应的**点**的 $dis$ 即可。

考虑对于一个点所连的每条边都向所连的其他边连**新边**，所以**新图**的**边数**为 $O(m^2)$ 级别，比如菊花图的**新图**（例子没有很好的表示主要是因为画不开了）。所以考虑优化建图。

首先把一条边用两个**点**表示，注意这里不是原图中这条边所连的两点。

然后两个**点**之间连**双向边**，**边权**为原图中该边边权。

这两个**点**的理解有点抽象，它的作用是给**边**定向。对于一条边 $(u,v)$ 其中表示它的两个**点**中其中一个表示从 $u$ 走到 $v$，另一个表示从 $v$ 走到 $u$。然后对于原图中某个点 $u$ 连接的所有边，如果按照边权排序，从小到大为 $e_1, e_2 , \dots ,e_x$ 其对应的**点对**为 $(a_1, b_1),(a_2, b_2), \dots,(a_x, b_x)$，其中 $a$ 表示拆分边后表示走向 $u$ 这种状态对应的**点**，那么连**有向边** $(a_i, a_{i+1})$ **边权**为原边边权之差，再连边 $(a_{i + 1}, a_{i})$ **边权**为 $0$。

向前文所提在原图上连上虚拟源汇点，然后整张图按这种构造方式建新图。跑最短路即可。

如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/mcc03kqw.png)

在一条边两侧，颜色不同，有着**权值**相同的**边**的**点**为该边拆出来的两个**点**，相同颜色的**点**为指向相同的**边**对应的**点**。

为什么这样建图是正确的？

考虑当前在 $u$ 点，此时也代表着处于新图上的代表着走入这个点的边拆出的**点**，当要跨越一个点的时候，首先要转变到走出这个点的边拆出来的**点**，这个过程中累加了这条边的权值 $v$，即图中不同颜色**点**之间的转化。然后跨越这个点走下一条边，此时由于按照权值大小排序后从小到大按照差分值为**权值**连的**正向边**，$0$ 权值连的**反向边**，所以如果走到一个边权更大的边上，就会继续累加 $\det v$，如果走到更小的边上，就会累加零，等于在走过这一个点的时候得到了 $\max(v_1, v_2)$。

如果还不懂就照着图走一走，从**绿点**开始走，走到**黄点**结束。

------

可以看出只要定向与连边是一致的，和具体那个**点**代表向内向外走是没关系的。所以下面代码为了好写把向外走的**点**和向内走的**点**颠倒了一下。

```

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<queue>
#define int long long

using namespace std;

inline int read(){
	register int x = 0, f = 1; register char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return x * f;
}

int n, m, S, T;
const int N = 4e5 + 10;
const int M = 8e5 + 10;

struct Graph{
	int head[N], Next[M << 1], e[M << 1], idx = 1, val[M << 1];
	inline void add(int a, int b, int c){
		e[++ idx] = b; Next[idx] = head[a]; head[a] = idx; val[idx] = c;
	}
}G1, G2;

int tmp[N];
int vis[N];

inline bool cmp(int a, int b){
	return G1.val[a] < G1.val[b];
}

void dfs(int now){
	int cnt = 0; vis[now] = 1;
	for(int i = G1.head[now]; i; i = G1.Next[i]){
		int j = G1.e[i];
		if(vis[j]) continue;
		dfs(j);
	}
	for(int i = G1.head[now]; i; i = G1.Next[i]) tmp[++ cnt] = i;
	sort(tmp + 1, tmp + cnt + 1, cmp);
	for(int i = 1; i < cnt; ++ i){
		G2.add(tmp[i], tmp[i + 1], G1.val[tmp[i + 1]] - G1.val[tmp[i]]);
		G2.add(tmp[i + 1], tmp[i], 0);
	}
}

struct node{
	int pos, val;
	inline bool operator < (const node &a) const{
		return a.val < val;
	}
};

priority_queue<node> q;

int dist[N], vs[N];
void dij(){
	memset(dist, 63, sizeof dist); 
	q.push(node{S, 0}); dist[S] = 0;
	while(!q.empty()){
		node tp = q.top();
		q.pop();
		int now = tp.pos;
		if(vs[now]) continue;
		vs[now] = 1;
		for(int i = G2.head[now]; i; i = G2.Next[i]){
			int j = G2.e[i];
			if(dist[j] > dist[now] + G2.val[i]){
				dist[j] = dist[now] + G2.val[i];
				if(!vs[j]) q.push(node{j, dist[j]});
			}
		}
	}
}

signed main(){
	n = read(); m = read();
	for(int i = 1; i <= m; ++ i){
		int a = read(), b = read(), c = read();
		G1.add(a, b, c);
		G1.add(b, a, c);
		G2.add(G1.idx, G1.idx ^ 1, c);
		G2.add(G1.idx ^ 1, G1.idx, c);
	}
	G1.add(n + 1, 1, 0); S = G1.idx;
	G1.add(1, n + 1, 0);
	G2.add(G1.idx, G1.idx ^ 1, 0);
	G2.add(G1.idx ^ 1, G1.idx, 0);
	G1.add(n + 2, n, 0);
	G1.add(n, n + 2, 0); T = G1.idx;
	G2.add(G1.idx, G1.idx ^ 1, 0);
	G2.add(G1.idx ^ 1, G1.idx, 0);
	dfs(n + 1);
	dij();
	printf("%lld", dist[T]);
	return 0;
}

``` 

---

## 作者：shengnan (赞：2)



题意简述：

一个无向图，经过一个点的代价是进入和离开这个点的两条边的边权的较大值，求从起点 1到点 n的最小代价。

------------

首先考虑暴力建图：
把无向边拆为两条，把边当作点，对于两条边a->b,b->c，在这两条边之间连有向边，边权为这两条边权值较大值 边数为($m^2$)

 _思考：这种暴力建图的方式冗余在何处，从哪里入手优化_ 

发现：实际上，一个点的很多边彼此有着联系：对于一条边a->b(设权值为w)，**b点连出的所有比w小的边都是w本身，而对于比w大的边，增长的值为两边的差值**

**所以，我们考虑用差分的思想，即利用差值，优化连边**

做法：将原图每个点的出边排序，权值小的点向权值大的点连边，权值为差值，大的向小的连边，权值为0

新建源点s,汇点t，s向所有1的出边连边，所有连入n的边向t连边，求s->t的最短路即可

这样保证小边到大边，差分累加答案，大边到小边最大值仍是大边，权值为0

AC代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,tot=1,cnt=1,h[200005],head[400005],tmp[200005],s,t;
ll dis[400005];
bool vis[400005];
struct node{int to,nxt,w;}ed[400005],e[2000005];
priority_queue<pair<ll,int>,vector<pair<ll,int> >,greater<pair<ll,int> > > q;
void add(int u,int v,int w){
    ed[++tot].nxt=h[u];ed[tot].to=v;ed[tot].w=w;h[u]=tot;
}
void insert(int u,int v,int w){
	e[++cnt].nxt=head[u];e[cnt].to=v;e[cnt].w=w;head[u]=cnt;
}
bool cmp(int a,int b){return ed[a].w<ed[b].w;}
void dij(){
	for(int i=2;i<=t;i++)dis[i]=1e16;
	q.push(make_pair(0,1));
	while(!q.empty()){
		int u=q.top().second;q.pop();
		if(vis[u])continue; vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(dis[v]>dis[u]+e[i].w)
			  dis[v]=dis[u]+e[i].w,q.push(make_pair(dis[v],v));
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	s=1,t=2*(m+1);
	for(int i=1;i<=n;i++){
	   int top=0;
	   for(int j=h[i];j;j=ed[j].nxt)tmp[++top]=j;
		sort(tmp+1,tmp+top+1,cmp);
		for(int j=1;j<=top;j++){
			int now=tmp[j],nxt=tmp[j+1];
			if(ed[now].to==n)insert(now,t,ed[now].w);
			if(i==1)insert(s,now,ed[now].w);
			insert(now^1,now,ed[now].w);
			if(j<top)insert(now,nxt,ed[nxt].w-ed[now].w),insert(nxt,now,0);
		}
	}
	dij(); printf("%lld\n",dis[t]);
	return 0;
}
```



------------



---

## 作者：MusicBox (赞：1)

构造题。

考虑每个点度数较小的情况，不难发现我们可以把边看作点，然后暴力将连接一个点之间的边暴力两两连边，然后跑最短路。

原图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2f1i0hze.png)

建图（暴力，我们将边看作点）：

![](https://cdn.luogu.com.cn/upload/image_hosting/1tbyq9e9.png)

但是我们发现这种方法边数可以被卡到 $m^2$ 级别（菊花图）。

考虑如何优化这个过程。

我们发现，一个边往比自己大的边走是需要补代价的，往比自己小的点走不用补代价。

短暂思索后，发现可以将原图上的边按照边权排序，设 A < B < C（边权）。

A 到 C 的代价即为 A 到 B 的代价再加上 B 到 C 的代价。

然后可以构建出下面这张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hfjuwbhs.png)

我们对于每个边点的一端都建出一个辅助点，辅助点向第一个比自己大的点连有向边，边权为需补的代价，向比自己第一个小的点连有向边，边权为 0，因为不用补代价。

至此，本题解决，我们需要建 $3 \times m$ 左右个点，以及 $6 \times m$ 条边，然后在上面跑最短路即可。复杂度 $\mathcal O(m\log m)$。

code:

```cpp
int n, m, cnt, dis[L];

struct node {
    int u, v, w;
} f[L];

vector<pii> nds[L];
vector<pii> e[L];

void dij(int u) {
    dis[u] = inf; priority_queue<pii, vector<pii>, greater<pii> > p; p.push({0, u});
    while(!p.empty()) { auto tp = p.top(); p.pop(); int u = tp.second;
        if(dis[u] != inf) continue;
        dis[u] = tp.first;
        for(auto v : e[u]) {
            if(dis[v.first] == inf) p.push({v.second + dis[u], v.first});
        }
    }
}

signed main() {
    rd(n, m);
    f[1].u = 0, f[1].v = 1, f[1].w = 0;
    rep(i, 2, m + 1) rd(f[i].u, f[i].v, f[i].w);
    f[m + 2].u = n + 1, f[m + 2].v = n, f[m + 2].w = 0;
    cnt = m + 2;
    rep(i, 1, m + 2) {
        e[i].pb({++ cnt, f[i].w});
        e[cnt].pb({i, 0});
        nds[f[i].v].pb({i, cnt});
        e[i].pb({++ cnt, f[i].w});
        e[cnt].pb({i, 0});
        nds[f[i].u].pb({i, cnt});
    } 
    rep(i, 1, n) sort(nds[i].begin(), nds[i].end(), [&](pii a, pii b) { return f[a.first].w < f[b.first].w; }); // 
    rep(i, 1, n) {
        rep(j, 0, signed(nds[i].size()) - 2) {
            e[nds[i][j].second].pb({nds[i][j + 1].second, f[nds[i][j + 1].first].w - f[nds[i][j].first].w});
            e[nds[i][j + 1].second].pb({nds[i][j].second, 0});
        }
    }
    rep(i, 1, cnt) dis[i] = inf; dij(1);
    cout << dis[m + 2] << endl;
    return 0;
}
```

---

## 作者：rq_kyz (赞：1)

# 【题解】 P6822 [PA2012] Tax

### 传送门

[P6822 [PA2012] Tax](https://www.luogu.com.cn/problem/P6822)

---

### 题意

给出一个 $n$ 个点、$m$ 条边的无向图，经过一个点的代价是进入和离开这个点的两条边的边权的较大值，求从起点 $1$ 到终点 $n$ 的最小代价。起点的代价是离开起点的边的边权，终点的代价是进入终点的边的边权。

---

### 分析

直接进行 Dijkstra 实现起来很困难，我们可以考虑将边变为点、点变为边。

直接上构造：

1. 我们需要把无向边变为两条有向边。

2. 对于每个点进行考虑，如下图：

![](https://s11.ax1x.com/2024/01/21/pFVDWVS.png)

点 $u$ 有 $4$ 条边，分别连向 $v1$、$v2$、$v3$、$v4$，边权分别为 $w1$、$w2$、$w3$、$w4$。设 $w1\le w2\le w3\le w4$，我们将这 $4$ 条边拆分为 $8$ 个点，其中一条边被拆分为一个入度点和一个出度点。

接着，我们需要连边将他们连接起来。为了实现题目中取较大值的效果，连边方法如下图：

![](https://s11.ax1x.com/2024/01/21/pFVDI8s.png)

（后来才发现向上连的那些边没必要……）

我们发现，上面一排为入度点，下面一排为出度点。从任意一个入度点进入，到达任意一个出度点，其最短路的长度就为经过这个点的权值。而这一整块是由点 $u$ 变换得到的，我们将这些边称为点 $u$ 的**内部边**。

我们发现这样本质上是把一条边拆分为了 $4$ 个点。设边 $u-v$，我们在考虑点 $u$ 的内部边时会将边 $u-v$ 拆分为两个点，而在考虑点 $v$ 时又会拆分两次，所以一共拆分出了 $4$ 个点。只需要将 $u$ 中此边的出度连一条边指向 $v$ 的入度、$v$ 的出度连一条边指向 $u$ 的入度，全局上整个图就联通了。最后再建立一个超级源点与超级汇点，以方便计算答案（真正实现的时候也可以不建超级源点和超级汇点）。

这样我们就可以巧妙的将本题转化为一个普通的最短路问题（因为 $w1\le w2\le w3\le w4$，所以没有负边），可以直接使用 Dijkstra 算法即可求得答案。

---

### 代码

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct s1{
	ll i,l;
};
vector<s1> a[100001];
bool cmp(s1 num1,s1 num2){
	return num1.l<num2.l;
}
struct s2{
	ll x,y,l;
}b[200001];
ll last[800001];
struct s3{
	ll t,to,l;
}nxet[2000001];
ll cd=0;
void lj(ll x,ll y,ll l){
	nxet[++cd].t=last[x];
	nxet[cd].to=y;
	nxet[cd].l=l;
	last[x]=cd;
}
ll dis[800001];
bool vis[800001];
struct s4{
	ll x,l;
}h[1800001];
ll len=1;
bool f(s4 num1,s4 num2){
	return num1.l>num2.l;
}
void dijkstra(ll s){
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	h[0]={s,0};
	while(len){
		ll x=h[0].x;
		pop_heap(h,h+len,f);
		len--;
		if(vis[x])
			continue;
		vis[x]=1;
		for(ll j=last[x];j;j=nxet[j].t){
			ll y=nxet[j].to;
			if(dis[y]>dis[x]+nxet[j].l){
				dis[y]=dis[x]+nxet[j].l;
				h[len].x=y;
				h[len++].l=dis[y];
				push_heap(h,h+len,f);
			}
		}
	}
}
int main(){
	ll n,m;
	scanf("%lld%lld",&n,&m);
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld%lld",&b[i].x,&b[i].y,&b[i].l);
		if(b[i].x>b[i].y)
			b[i].x^=b[i].y^=b[i].x^=b[i].y;
		a[b[i].x].push_back({i,b[i].l});//vector存图
		a[b[i].y].push_back({i,b[i].l});
	}
	for(ll i=1;i<=n;i++){//对于每个点，连接其内部边
		sort(a[i].begin(),a[i].end(),cmp);//对于与当前点直接连接的边，以边权从小到大排序，也就是为了满足上述过程中的w1<=w2这个条件
		ll y0;
		for(ll j=0;j<a[i].size();j++){
			ll x,y;
			if(b[a[i][j].i].x==i){
				x=4*a[i][j].i-3;
				y=4*a[i][j].i-2;
			} else {
				x=4*a[i][j].i-1;
				y=4*a[i][j].i;
			}
			if(j){
				lj(y0,y,a[i][j].l-a[i][j-1].l);
				lj(y,y0,0);
			}
			lj(x,y,a[i][j].l);
			y0=y;
		}
	}
	for(ll i=1;i<=m;i++){//全局上将每个点连接起来
		lj(4*i-2,4*i-1,0);
		lj(4*i,4*i-3,0);
	}
	dijkstra(4*a[1][0].i-3);//直接出发，不需要超级源点
	ll ans=0x3f3f3f3f3f3f3f3f;
	for(ll i=0;i<a[n].size();i++)//统计答案，省去超级汇点
		ans=min(ans,dis[4*a[n][i].i]);
	printf("%lld",ans);
    return 0;
}
```

---

## 作者：tribool4_in (赞：1)

贡献是由点产生的，于是很显然的考虑把边作为点建图，两个边点之间的边权为两者较大值。但是直接这样边数容易被卡成 $O(m^2)$。

考虑一个原图中的结点 $u$，会由一条“入边”进入（权值为 $w_{in}$），然后由一条“出边”离开（权值为 $w_{out}$）。如果 $w_{in}>w_{out}$，那么经过该点的代价为 $w_{in}$，否则 $w_{in}\le w_{out}$，代价为 $w_{out}=w_{in}+(w_{out}-w_{in})$。

不妨初始让入边等于出边，考虑出边“切换”到一条最终的出边。设原出边权值为 $w_0$，考虑切换到 $w_1$，若 $w_0>w_1$ 则代价差为 $0$，否则为 $w_1-w_0$。

于是考虑如何建图。枚举贡献结点 $u$，对于每条边，先将其入边点连向出边点，表示若以此边为“入边”的初始代价。然后对于两条权值相邻的“出边” $w_{i-1}<w_i$，可以连出“切换”的边：$(i-1)\to i$ 权值为 $w_i-w_{i-1}$；$i\to (i-1)$ 权值为 $0$。然后源点汇点连边是显然的。

于是跑最短路就做完了。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, M = 2e5 + 10;
int n, m;
struct edge {
    int u, v, w;
} E[M << 1];
int etot;
vector<int> H[N];
vector<pair<int, int>> G[M << 1];
void add_edge(int u, int v, int w) {
    E[etot] = (edge){u, v, w}, H[u].push_back(etot++);
    E[etot] = (edge){v, u, w}, H[v].push_back(etot++);
}
ll dij(int s, int t) {
    static bool vis[M << 1];
    static ll dis[M << 1];
    priority_queue<pair<ll, int>> q;
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, q.emplace(-dis[s], s);
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : G[u])
            if (dis[v] > dis[u] + w) dis[v] = dis[u] + w, q.emplace(-dis[v], v);
    }
    return dis[t];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v, w; i <= m; i++) {
        cin >> u >> v >> w;
        add_edge(u, v, w);
    }
    for (int i = 1; i <= n; i++) {
        sort(H[i].begin(), H[i].end(), [&](int x, int y) { return E[x].w < E[y].w; });
        for (int j = 0; j < H[i].size(); j++) {
            G[H[i][j] ^ 1].emplace_back(H[i][j], E[H[i][j]].w);
            if (j > 0) G[H[i][j]].emplace_back(H[i][j - 1], 0);
            if (j < H[i].size() - 1) G[H[i][j]].emplace_back(H[i][j + 1], E[H[i][j + 1]].w - E[H[i][j]].w);
        }
    }
    int s = etot, t = etot + 1;
    for (auto p : H[1]) G[s].emplace_back(p, E[p].w);
    for (auto p : H[n]) G[p ^ 1].emplace_back(t, E[p].w);
    cout << dij(s, t) << '\n';
    return 0;
}
```

---

## 作者：dAniel_lele (赞：1)

拆点，将每条边的两边均弄出两个独立的点。

我们希望经过这个点可以得到 $\max(w_{in},w_{out})$ 的权值。考虑如何实现。

首先如果我们要从一个权值大的边进入，一个权值小的边出去，那么不会产生额外权值。

如果我们要从一个权值小的边进入大的边出去，额外权值是 $w_{out}-w_{in}$。

于是我们可以在每个点的相邻边暴力连边。

我们发现这样是不优的，考虑如何优化。我们发现，对于任意三条边 $w_i<w_j<w_k$，从 $i$ 进入 $j$ 出去的额外权值是 $w_j-w_i$，从 $i$ 进入 $k$ 出去的额外权值是 $w_k-w_i$。从 $j$ 进入 $k$ 出去的额外权值是 $w_k-w_j$。我们发现仅仅在 $i,j$ 之间连 $w_j-w_i$ 权值的边，$j,k$ 之间连 $w_k-w_j$ 权值的边是充足的，因为 $w_k-w_i=(w_j-w_i)+(w_k-w_j)$。

建图跑最短路即可。复杂度 $O((n+m)\log(n+m))$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
vector<pair<int,int>> vc[500005];
vector<pair<int,int>> tmp[500005];
int dist[500005],vis[500005];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,c; cin>>u>>v>>c;
		vc[i*2-1].push_back(make_pair(i*2,c));
		vc[i*2].push_back(make_pair(i*2-1,c));
		tmp[u].push_back(make_pair(c,i*2-1));
		tmp[v].push_back(make_pair(c,i*2));
		if(u==1) vc[0].push_back(make_pair(i*2-1,c));
		if(v==1) vc[0].push_back(make_pair(i*2,c));
		if(u==n) vc[i*2-1].push_back(make_pair(2*m+1,0));
		if(v==n) vc[i*2].push_back(make_pair(2*m+1,0));
	}
	for(int i=1;i<=n;i++){
		sort(tmp[i].begin(),tmp[i].end());
		for(int j=1;j<tmp[i].size();j++){
			vc[tmp[i][j-1].second].push_back(make_pair(tmp[i][j].second,tmp[i][j].first-tmp[i][j-1].first));
			vc[tmp[i][j].second].push_back(make_pair(tmp[i][j-1].second,0));
		}
	}
	memset(dist,1,sizeof(dist));
	dist[0]=0;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
	pq.push(make_pair(0,0));
	while(!pq.empty()){
		int f=pq.top().second; pq.pop();
		if(vis[f]) continue; vis[f]=1;
		for(auto v:vc[f]){
			if(dist[f]+v.second<dist[v.first]){
				dist[v.first]=dist[f]+v.second;
				pq.push(make_pair(dist[v.first],v.first));
			}
		}
	} 
//	for(int i=0;i<=2*m+1;i++) cout<<dist[i]<<" ";
	cout<<dist[2*m+1];
	return 0;
}
```

---

## 作者：aaalys (赞：0)

## 题目大意

~~可恶，我们老师竟然把紫题放到了模拟赛里。~~

[题目传送门](https://www.luogu.com.cn/problem/P6822)

原题中题意说的很清楚了。

## 思路

### 转化问题

首先先新建两条边，使原题点到点的问题转化成边到边的问题。

可以连接一条从 $0$ 到 $1$，长度为 $0$ 的边，设这条边为 $0$ 号边。

还可以连接一条从 $n$ 到 $0$，长度为 $0$ 的边，设这条边为 $m+1$ 号边。

这样原题就变为了从 $0$ 号边到 $m+1$ 号边的最小代价。

### 化边为点

边到边的问题有一种常见做法：化边为点。

即把每条边看做一个点，将边与边之间连边，从起点边向终点边求最短路得到答案。

这道题也可以这么做，可以将首尾相连的两条边相连（即两条边有共同的节点），边权为两条边长度的最大值（原题中的代价）。

### 优化建图

但这样有个很明显的缺点，如果原图是菊花图，那么新图的边数最多可达到 $m^2$ 级别，需要优化建图。

不难想到一种思路，先枚举每个共同节点，再用 $sz$ 级别的边数建新边（$sz$ 为这个点相邻的边数）。

这样可以做到让新图的总边数控制在 $m$ 级别。

不难想到，可以对 $i$ 这条点（原图上的边）新建一个辅助点 $pre_i$。

可以连一条 $i$ 到 $pre_i$ 的边，边权为原边边长，并可以连一条 $pre_i$ 到 $i$ 的边，边权为 $0$。

将 $nodes$ 中的点按照长度从小到大排序（$nodes$ 表示这个点相邻的边），连一条 $pre_{node_{i+1}}$ 到 $pre_{node_{i}}$ 的，边权为 $0$ 的边（$1\le i < sz$）。

这样原图中两条边通过 $pre$ 辅助点连了一条边，边权为两条边长度的最大值。

由于需要建双向边，可以再新建一个辅助点 $suf_i$，和 $pre_i$ 同理连边，请读者自行思考。

## 后记

求管理员通过。

有几个需要注意的细节如下。

- 一条 $u$ 到 $v$ 的原图边，在枚举共同节点 $u$ 和枚举共同节点 $v$ 时都要各建两个节点 $pre_i$ 和 $suf_i$，也就是每条边一共要新建 $4$ 个节点。
- 十年 OI 一场空，不开 long long 见祖宗。
- 最终点数为 $5m$，边数为 $12m$，记得开够数组。
- 要使用 dijkstra，不要使用~~死去的~~ SPFA。

---

## 作者：Nuisdete (赞：0)

题目中的代价是指点的代价，因此考虑点化边跑最短路。

朴素的建边方式边数可达 $\mathcal{O}(n^2)$，考虑差分优化一下。

假设现在要建边表示出一号点的代价：

![](https://cdn.luogu.com.cn/upload/image_hosting/wmn9kl66.png)

那么差分一下就大概长这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/dk81k4yg.png)

大概就是围绕着中心点建一圈点，然后按照边权从小到大排序依次连边，反向都为 $0$。

起点和终点的代价特殊处理一下就行了，有一点点细节需要注意。

```cpp
# include <cstdio>
# include <queue>
# include <vector>
# include <utility>
# include <cstring>
# include <iterator>
# include <algorithm>

# define int long long

typedef std::pair<int, int> Pii;

constexpr int MAXN = 1e6 + 5;

int n, m;

int head[MAXN << 1], numE;

std::vector<Pii> G[MAXN << 1];

struct Edge {
	int nxt, to, val;
	
	Edge() {}
	Edge(int N, int T, int V) {
		nxt = N, to = T, val = V;
	}
} edge[MAXN << 1];

void addE(int x, int y, int val) {
	edge[++numE] = Edge(head[x], y, val), head[x] = numE;
}

int dis[MAXN << 1];

bool vis[MAXN << 1];

void dij(int s) {
	std::priority_queue<Pii, std::vector<Pii>, std::greater<Pii> > hp;
	memset(dis, 0x3f, sizeof dis);
	memset(vis, false, sizeof vis);
	hp.emplace(dis[s] = 0, s);
	while (!hp.empty()) {
		int u = hp.top().second; hp.pop();
		if (!vis[u]) {
			vis[u] = true;
			for (int i = head[u]; i; i = edge[i].nxt) {
				int k = edge[i].to;
				if (dis[k] > dis[u] + edge[i].val) 
					hp.emplace(dis[k] = dis[u] + edge[i].val, k);
			}
		}
	}
}

signed main() {
	
	scanf("%lld %lld", &n, &m);
	int numN = 0, s = MAXN, t = MAXN + 1;
	for (int i = 1; i <= m; ++i) {
		int x, y, val;
		scanf("%lld %lld %lld", &x, &y, &val);
		G[x].emplace_back(++numN, val), G[y].emplace_back(++numN, val);
		addE(numN, numN - 1, val), addE(numN - 1, numN, val);
		if (x == 1) addE(s, numN - 1, val); if (y == 1) addE(s, numN, val);
		if (x == n) addE(numN, t, val); if (y == n) addE(numN - 1, t, val);
	}
	for (int u = 1; u <= n; ++u) {
		std::sort(G[u].begin(), G[u].end(), [&](const Pii& A, const Pii& B) {
			return A.second < B.second;
		});
		if (!G[u].empty()) for (auto it = G[u].begin(); it != std::prev(G[u].end()); ++it) {
			addE((*std::next(it)).first, (*it).first, 0);
			addE((*it).first, (*std::next(it)).first, (*std::next(it)).second - (*it).second);
		}
	}
	dij(s);
	printf("%lld\n", dis[t]);
	
	return 0;
} 
```

---

