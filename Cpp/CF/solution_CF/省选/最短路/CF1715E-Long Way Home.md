# Long Way Home

## 题目描述

Stanley lives in a country that consists of $ n $ cities (he lives in city $ 1 $ ). There are bidirectional roads between some of the cities, and you know how long it takes to ride through each of them. Additionally, there is a flight between each pair of cities, the flight between cities $ u $ and $ v $ takes $ (u - v)^2 $ time.

Stanley is quite afraid of flying because of watching "Sully: Miracle on the Hudson" recently, so he can take at most $ k $ flights. Stanley wants to know the minimum time of a journey to each of the $ n $ cities from the city $ 1 $ .

## 说明/提示

In the first sample, it takes no time to get to city 1; to get to city 2 it is possible to use a flight between 1 and 2, which will take 1 unit of time; to city 3 you can get via a road from city 1, which will take 1 unit of time.

In the second sample, it also takes no time to get to city 1. To get to city 2 Stanley should use a flight between 1 and 2, which will take 1 unit of time. To get to city 3 Stanley can ride between cities 1 and 2, which will take 3 units of time, and then use a flight between 2 and 3. To get to city 4 Stanley should use a flight between 1 and 2, then take a ride from 2 to 4, which will take 5 units of time.

## 样例 #1

### 输入

```
3 1 2
1 3 1```

### 输出

```
0 1 1```

## 样例 #2

### 输入

```
4 3 1
1 2 3
2 4 5
3 4 7```

### 输出

```
0 1 4 6```

## 样例 #3

### 输入

```
2 1 1
2 1 893746473```

### 输出

```
0 1```

## 样例 #4

### 输入

```
5 5 2
2 1 33
1 5 93
5 3 48
2 3 21
4 2 1```

### 输出

```
0 1 2 2 3```

# 题解

## 作者：lenlen (赞：15)

和朋友一起打 VP，结果打到这道题，正好学了斜率优化，就做了一下。

### Problem

题目大意：给定一张图，其中你可以坐 $k$ 次飞机，可以从任意一点 $u$ 飞到任意一点 $v$，代价为 $(u-v)^2$，求起始点 $1$ 到所有点的最短路径。

数据范围： $n \leq 10^5,m \leq 10^5,k \leq 20$。

### Solution

看到这个题，一开始我想的是分层图，但是因为任意一点到任意一点都可以连一条路径，所以空间会炸掉（当然说不定一些大佬可以用分层图做，反正我这个蒟蒻不会）。

注意 $(u-v)^2$，平白无故他为什么要加个平方呢？这时我们就可以想到运用斜率优化，毕竟出现了平方，而且最短路的 dp 式子也很简单，这个题想到斜率优化之后就是板子了。

简单推一下：

$$dp_i=\min\limits_{j=1}^n dp_j+(i-j)^2$$

套路：

$$dp_i=dp_j+i^2-2ij+j^2$$

$$dp_j+j^2=2i \times j +dp_i-i^2$$

继续套路：

$$y=kx+b,y=dp_j+j^2,k=2i,x=j,b=dp_i-i^2$$

好了斜率优化推出来了，紧接着就是一些小问题：

1. 首先显然我们要做 $k$ 遍斜率优化，可以发现 $k \leq 20$ 所以我们这个想法行的通。

2. 做第 $i$ 遍斜率优化的时候，很明显，我们用的是第 $i-1$ 遍斜率优化后处理出来的最短路来进行更新，而做第 $i$ 遍的时候会影响原来的值，所以我们要把第 $i-1$ 遍之后的最短路存下来更新第 $i$ 遍的。

3. 显然，做完斜率优化之后，某些点的最短路会发生变化，紧跟着，从这个点走原图（不是坐飞机）的一些点也会发生变化，所以我们要把更新之后的点扔到 Dijkstra 里面更新一次。

### Code

具体细节看如下代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+7232;
int n,m,k;
int x,y;
long long dis[N],sum[N],z;
short vis[N];
int h[N],cnt;
struct hl{
    int v,nxt;
    long long w;
}e[N<<1];
void add(int u,int v,long long w)
{
    e[++cnt].v=v;e[cnt].nxt=h[u];h[u]=cnt;e[cnt].w=w;
}
struct llt{
    int id;
    long long d;
    bool operator < (const llt&x ) const{
        return d>x.d;
    }
}tmp;
priority_queue<llt> p;
void dij()
{
    memset(vis,0,sizeof(vis));
    while(!p.empty())
    {
        tmp=p.top();p.pop();
        if(vis[tmp.id]) continue;
        vis[tmp.id]=1;
        for(int i=h[tmp.id];i;i=e[i].nxt)
        {
            if(dis[e[i].v]>dis[tmp.id]+e[i].w)
            {
                dis[e[i].v]=dis[tmp.id]+e[i].w;
                p.push((llt){e[i].v,dis[e[i].v]});
            }
        }
    }
}
int q[N<<4],head=1,tail=1;
double slope(int i,int j)//斜优板子
{
    if(i==j) return 1000000732.0;
    return (sum[i]+(1ll)*i*i-sum[j]-(1ll)*j*j)*1.0/(i-j);
}
long long mi(long long x,long long y)
{
    return x<y?x:y;
}
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++) scanf("%d%d%lld",&x,&y,&z),add(x,y,z),add(y,x,z);
    memset(dis,0x3f,sizeof(dis));
    p.push((llt){1,0});
    dis[1]=0;
    dij();
    while(k--)//第一点
    {
        head=tail=1;q[1]=0;//清空
        for(int i=1;i<=n;i++) sum[i]=dis[i];//第二点
        for(int i=1;i<=n;i++)
        {
            while(head<tail&&slope(q[tail-1],q[tail])>slope(q[tail-1],i)) --tail;//斜优板子
            q[++tail]=i;
        }
        for(int i=1;i<=n;i++)
        {
            while(head<tail&&slope(q[head],q[head+1])<2.0*i) ++head;//斜优板子
            int j=q[head];
            if(dis[i]>sum[j]+(i-j)*(i-j))
            {
                dis[i]=sum[j]+(1ll)*(i-j)*(i-j);
                p.push((llt){i,dis[i]});//遇到更新了最短路的点，放到队列中去
            }
        }
        dij();
    }
    for(int i=1;i<=n;i++) printf("%lld ",dis[i]);
}
/*
10 0 10

*/
```
对了，有句俗话说得好，不开 long long 见祖宗。


---

## 作者：ExplodingKonjac (赞：9)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1715E)**

## 题目分析

先考虑 $k=1$ 怎么做。

显然走过的路一定是“走路 $\to$ 飞 $\to$ 走路”。不飞或者不走可以认为是原地踏步。

第一步，我们可以跑一遍 dijkstra，得到了只走路的最短路。

第二步，要处理这一次飞，也就是说要处理最后一次是飞的最短路。不难想到这样更新：$dis_u'\gets \min\limits_v\{dis_v+(u-v)^2\}$。把后面的 $(u-v)^2$ 拆开后，整理成 $\min\limits_v\{-2uv+v^2+dis_v\}+u^2$。这是一个典型的问题，可以用李超线段树或者维护凸包解决。我使用了李超线段树，就是把 $\min$ 里面的东西看成直线 $y=-2vx+(v^2+dis_v)$，然后求 $x=u$ 时的最小值。

第三步，最后还要在地上走一段。我们可以把已经得到的 $dis$ 再扔进堆里面跑 dijkstra，就知道最终答案了。

$k=1$ 做完了。$k>1$ 的话，触类旁通地，做完第一步后，再把第二、三步做 $k$ 次即可。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

/* 省略快读快写，即下面的 qin、qout */

int n,m,k;
vector<pair<int,int>> g[100005];

LL dis[100005];
bool vis[100005];
void dijkstra()
{
	priority_queue<pair<LL,int>,vector<pair<LL,int>>,greater<pair<LL,int>>> q;
	for(int i=1;i<=n;i++)
		vis[i]=false,q.emplace(dis[i],i);
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u]=true;
		for(auto &[v,w]: g[u])
			if(dis[u]+w<dis[v])
				q.emplace(dis[v]=dis[u]+w,v);
	}
}

struct Line
{
	LL k,b;
	Line()=default;
	Line(LL _k,LL _b): k(_k),b(_b){}
	inline LL operator ()(const LL x)const
		{ return k*x+b; }
}t[400005];
#define LC (i<<1)
#define RC (i<<1|1)
void build(int l,int r,int i=1)
{
	t[i]=Line(0,INF);
	if(l!=r)
	{
		int mid=(l+r)>>1;
		build(l,mid,LC);
		build(mid+1,r,RC);
	}
}
void modify(const Line &f,int i=1,int l=1,int r=n)
{
	int mid=(l+r)>>1;
	if(f(l)>=t[i](l) && f(r)>=t[i](r)) return;
	else if(f(l)<=t[i](l) && f(r)<=t[i](r)) t[i]=f;
	else modify(f,LC,l,mid),modify(f,RC,mid+1,r);
}
LL query(int p,int i=1,int l=1,int r=n)
{
	if(l==r) return t[i](p);
	LL mid=(l+r)>>1,res=t[i](p);
	if(mid>=p) res=min(res,query(p,LC,l,mid));
	else res=min(res,query(p,RC,mid+1,r));
	return res;
}

int main()
{
	qin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		int u,v,w;
		qin>>u>>v>>w;
		g[u].emplace_back(v,w);
		g[v].emplace_back(u,w);
	}
	for(int i=2;i<=n;i++) dis[i]=INF;
	dijkstra();
	for(int i=1;i<=k;i++)
	{
		build(1,n);
		for(int j=1;j<=n;j++)
			modify(Line(-2*j,(LL)j*j+dis[j]));
		for(int j=1;j<=n;j++)
			dis[j]=min(dis[j],query(j)+(LL)j*j);
		dijkstra();
	}
	for(int i=1;i<=n;i++) qout<<dis[i]<<' ';
	return 0;
}
```


---

## 作者：Register_int (赞：8)

看到航班只能 $k$ 次，代价还带平方，很快啊，就可以想到是个斜率 dp。  
先考虑只能飞一次怎么办。设从起点到点 $i$ 的最短距离为 $dis_i$，飞完的最短距离为 $dp_i$，那么可以得出转移方程：
$$dp_i=\min^n_{i=1}(dis_j+(i-j)^2)$$
把 $\min$ 去掉，然后套路性地推下柿子：
$$
\begin{aligned}
dp_i&=dis_j+(i-j)^2\\
dp_i&=dis_j+i^2-2ij+j^2\\
2ij+dp_i-i^2&=dis_j+j^2\\
K_iX_j+B_i&=Y_j\\
K_i=2i,X_j=j&,B_i=dp_i-i^2,Y_j=dp_j+j^2\\
\end{aligned}
$$
这个斜率优化和普通的不太一样，$j$ 并没有 $\le i$ 的范围限制。所以需要先把所有决策点加进去，再进行转移。  
飞一次就转移一次，那飞 $k$ 次就转移 $k$ 次。每次跑最短路时，如果一个点的距离被更新，那就把这一距离加入 $\text{Dijkstra}$ 算法的优先队列里，就可以更新飞完后的最短距离了。  
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int MAXN = 1e5 + 10;

struct edge {
	int v, w, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v, int w) {
	e[++tot] = { v, w, head[u] }, head[u] = tot;
}

struct node {
	int u; ll dis;
	bool operator < (const node &rhs) const { return dis > rhs.dis; }
};

bool vis[MAXN];

ll dis[MAXN];

priority_queue<node> qn;

void dijkstra() {
	memset(vis, 0, sizeof vis);
	qn.push({ 1, 0 });
	while (!qn.empty()) {
		int u = qn.top().u; qn.pop();
		vis[u] = 1;
		for (int i = head[u], v; i; i = e[i].nxt) {
			v = e[i].v;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				if (!vis[v]) qn.push({ v, dis[v] });
			}
		}
	}
}

ll dp[MAXN];

inline ll k(ll p) { return p << 1; }
inline ll x(ll p) { return p; }
inline ll b(ll p) { return dp[p] - p * p; }
inline ll y(ll p) { return dp[p] + p * p; }
inline db slope(ll p, ll q) { return (db)(y(p) - y(q)) / (x(p) - x(q)); }

deque<int> q;

int n, m, t;

int main() {
	scanf("%d%d%d", &n, &m, &t);
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	dijkstra();
	for (int i = 1; i <= t; i++) {
		for (int j = 1; j <= n; j++) dp[j] = dis[j];
		q.clear(), q.push_back(0);
		for (int j = 1; j <= n; j++) {
			if (x(j) == x(q.back())) {
            	if (y(j) < y(q.back())) q.pop_back();
            	else continue;
        	}
			while (q.size() > 1 && slope(q[q.size() - 2], q.back()) >= slope(q[q.size() - 2], j)) q.pop_back();
			q.push_back(j);
		}
		for (int j = 1, v; j <= n; j++) {
			while (q.size() > 1 && slope(q.front(), q[1]) <= k(j)) q.pop_front();
			v = q.front();
			if (!v) continue;
			if (dis[j] > dp[v] + (ll)(j - v) * (j - v)) {
				dis[j] = dp[v] + (ll)(j - v) * (j - v);
				qn.push({ j, dis[j] });
			}
		}
		dijkstra();
	}
	for (int i = 1; i <= n; i++) printf("%lld ", dis[i]);
}
```

---

## 作者：AbsMatt (赞：3)

### [题目传送器](https://www.luogu.com.cn/problem/CF1715E)

### [更爽的阅读体验](https://www.luogu.com.cn/blog/yaohaoyou/solution-cf1715e)

## 题意
给一个带权无向图，你可以花费 $(u-v)^2$ 的时间从 $u$ 瞬移到 $v$，你最多可以使用 $k$ 次瞬移，问从 $1$ 分别到 $j (j \in[2,n])$ 的最短路。

## 做法
第一种想法就是暴力将每个 $(u,v)$ 建一条长度为 $(u-v)^2$ 的边，但一共会有 $\dfrac{n(n-1)}{2}$ 条边，无法建图。优化也非常困难，于是考虑换种做法。

考虑 dp，这题的 dp 状态定义比较好看出，$dp_i$ 表示从 $1$ 到 $i$ 的最短长度。

既然瞬移比较复杂，就可以考虑先去掉瞬移，那这直接在给的图跑最短路即可。再加上瞬移，可以简单的推出转移方程为 $dp_i=\min_{j=1}^{n}\{dp_j+(i-j)^2\}$，这个明显可以用斜率优化成 $O(n)$。

$$
dp_i=\min_{j=1}^{n}\{dp_j+(i-j)^2\} \\
dp_i=\min_{j=1}^{n}\{dp_j+i^2-2 \times i \times j+j^2\} \\
dp_i=\min_{j=1}^{n}\{dp_j+-2 \times i \times j+j^2\}+i^2 \\
dp_j+j^2=2 \times i \times j + dp_i - i^2
$$

带入 $y=kx+b$ 发现 $y=dp_j+j^2,k=2 \times i,b=dp_i-i^2$。

每次斜率优化时间复杂度为 $O(n)$，对于每个 $i \in [1,k]$，进行一次转移，更新 dp，然后跑最短路就完成了。时间复杂度为 $O(k \times n \times \log_2n)$，感觉卡得还是很紧的，用 SPFA 可能会被卡掉。由于 $(u-v)^2$ 的值最大为 $(n-1)^2$，所以记得要开 long long。单调队列使用的是 STL，dp 数组就是 dijkstra 中的 di，码风比较丑，敬请原谅。

### AC Code

```cpp
#include <bits/stdc++.h>  // 准备开始啦！
#define int long long  // 注意开 long long
using namespace std;
const int maxn = 1e5 + 10;
const int inf = 1e18 + 7;
int n, m, k;
int s[maxn];
namespace Graph  // 建图
{
int cnt = 0, head[maxn << 1];
struct edge
{
    int nxt, to, w;
} e[maxn << 1];
void add(int u, int v, int w)
{
    e[++cnt] = {head[u], v, w};
    head[u] = cnt;
}
}  // namespace Graph
using namespace Graph;
namespace Dijkstra  // 最短路
{
struct Dis
{
    int di  /*dp 数组*/  , i;
    bool operator<(const Dis &tmp) const { return di > tmp.di; }
} d[maxn];
priority_queue<Dis> q;
bool vis[maxn];
void dijkstra(int s)
{
    memset(vis, 0, sizeof(vis));
    d[s].di = 0;
    q.push(d[s]);
    while (!q.empty())
    {
        int t = q.top().i;
        q.pop();
        if (vis[t])
            continue;
        for (int i = head[t]; i; i = e[i].nxt)
        {
            int x = e[i].to;
            if (vis[x])
                continue;
            if (d[x].di > d[t].di + e[i].w)
            {
                d[x].di = d[t].di + e[i].w;
                q.push(d[x]);
            }
        }
        vis[t] = true;
    }
}
}  // namespace Dijkstra
using namespace Dijkstra;
deque<int> dq;  // 维护单调队列
double calc(int x, int y)  // 计算两条直线的交点的横坐标
{
    if (x == y)
        return inf;
    return double(s[x] + x * x - s[y] - y * y) / (x - y);
}
signed main()
{
    for (int i = 1; i < maxn; i++)
    {
        d[i].di = inf;
        d[i].i = i;
    }
    scanf("%lld%lld%lld", &n, &m, &k);
    for (int i = 1; i <= m; i++)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dijkstra(1);
    for (int l = 1; l <= k; l++)  // k 次遍历
    {
        // 斜率优化板子
        while (dq.size()) dq.pop_front();
        for (int i = 1; i <= n; i++) s[i] = d[i].di;
        for (int i = 1; i <= n; i++)
        {
            int j;
            while ((j = dq.size()) > 1 &&
                   calc(dq[j - 2], dq[j - 1]) > calc(dq[j - 1], i))
                dq.pop_back();
            dq.push_back(i);
        }
        for (int i = 1; i <= n; i++)
        {
            while (dq.size() > 1 && calc(dq[0], dq[1]) < 2 * i) dq.pop_front();
            if (!dq.empty() && s[dq.front()] + i * i + dq.front() * dq.front() -
                                       2 * i * dq.front() <
                                   d[i].di)
            {
                d[i].di = s[dq.front()] + i * i + dq.front() * dq.front() -
                          2 * i * dq.front();
                q.push({d[i].di, i});
            }
        }
        dijkstra(1);  // 记得最后也要跑一遍最短路
    }
    for (int i = 1; i <= n; i++)    printf("%lld ", d[i].di);  // 输出
    return 0;  // 再见啦！
}
```


---

## 作者：Tx_Lcy (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1715E)

属于是 $\rm Div2\ E$ 里较水的。

## 思路

发现这个 $k$ 非常小，考虑跟 $k$ 有关的复杂度。

一个想法是枚举 $k$ 次，每次都把 $dis_i$ 与 $dis_j+(i-j)^2$ 取个 $\min$，然后重新跑一遍 $\rm dij$，重新跑一遍 $\rm dij$ 的复杂度是可以接受的，但是这个 $\mathcal O(n^2)$ 枚举复杂度炸了。

考虑优化这个过程，聪明的你肯定一眼看出这个柿子可以决策单调性。

设 $dis_i$ 是由 $j$ 转移过来的，我们需要证明 $dis_{i+1}$ 的转移点 $\ge j$。

假设 $dis_{i+1}$ 的转移点为 $k$ 且 $k<j$，则 $dis_k+(k-(i+1))^2 < dis_j+(j-(i+1))^2$

$dis_k+(k-i)^2-2 \times (k-i)+1^2<dis_j+(j-i)^2-2 \times (j-i)+1^2$

$dis_k+(k-i)^2-2 \times k<dis_j+(j-i)^2-2 \times j$

设 $A=dis_k+(k-i)^2,B=-2 \times k,C=dis_j+(j-i)^2,D=-2 \times j$

显然 $A \ge C,B \ge D$

所以 $A+B \ge C+D$，与 $A+B<C+D$ 矛盾，故 $k \ge j$。

知道了这个就可以斜优了，不过分治好写，那就写分治吧。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face is invincible.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define mid ((l+r)>>1)
#define lowbit(x) (x&-x)
int const N=1e5+10;
int dis[N],s[N],has[N],n;
vector< pair<int,int> >a[N];
inline void solve(){
	priority_queue< pair<int,int>,deque< pair<int,int> >,greater< pair<int,int> > >q;
	memset(has,0,sizeof(has));
	for (int i=1;i<=n;++i) q.push({dis[i],i});
	while (!q.empty()){
		int x=q.top().second;
		q.pop();
		if (has[x]) continue;
		has[x]=1;
		for (auto [v,w]:a[x])
			if (dis[v]>dis[x]+w){
				dis[v]=dis[x]+w;
				q.push({dis[v],v});
			}
	}
}
inline void work(int l,int r,int L,int R){
	// [l,r] [L,R]
	if (l>r) return;
	int res=9e18,resw=0;
	for (int i=L;i<=R;++i){
		int now=dis[i]+sqr(i-mid);
		if (now<res) res=now,resw=i;
	}
	s[mid]=res;
	work(l,mid-1,L,resw);
	work(mid+1,r,resw,R);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int m,k;cin>>n>>m>>k;
	while (m--){int u,v,w;cin>>u>>v>>w;a[u].push_back({v,w}),a[v].push_back({u,w});}
	memset(dis,0x3f,sizeof(dis));dis[1]=0;
	solve();
	while (k--){
		work(1,n,1,n);
		for (int i=1;i<=n;++i) dis[i]=s[i];
		solve();
	}
	for (int i=1;i<=n;++i) cout<<dis[i]<<' ';
	cout<<'\n';
	return 0;
}
```

---

## 作者：Qzong (赞：1)

套路题。

先不考虑额外的边跑一次最短路。

然后考虑一下额外的边，单独拿出来转移一次。

式子为 $dis_u=\min\{olddis_v+(u-v)^2,1\leq v \leq n\}$。

简单的，把凸包建出来，二分最优点转移即可。

也就是做一次斜率优化 $dp$。

然后继续跑最短路，最短路可以同时 $n$ 个节点一起跑。

重复 $k$ 次。

复杂度 $O(k(n\log m+n\log n))$。

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=100010;
#define ll long long
struct node{
	int id;
	ll val;
	bool operator<(const node &A)const {
		return val>A.val;
	}
};
struct heap{
	node st[N<<1];
	int tp;
	void push(node x){
		st[++tp]=x,std::push_heap(st+1,st+tp+1);
	}
	void pop(){
		std::pop_heap(st+1,st+tp+1),tp--;
	}
	node top(){
		return st[1];
	}
}q;
struct edge{
	edge*net;int to,c;
}e[N<<1],*tot=e,*head[N];
int n,m,k;
ll dis[N];
int vis[N];
void dij(){
	memset(vis,0,sizeof vis);
	for(int i=1;i<=n;i++)q.push(node{i,dis[i]});
	while(q.tp){
		int u=q.top().id;q.pop();
		if(vis[u])continue;
		vis[u]=1;
		for(edge*i=head[u];i;i=i->net)if(dis[u]+i->c<dis[i->to]){
			dis[i->to]=dis[u]+i->c;
			q.push(node{i->to,dis[i->to]});
		}
	}
}
long long qx[N],qy[N];
int tp;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v,w;i<=m;i++)scanf("%d%d%d",&u,&v,&w),*++tot={head[u],v,w},head[u]=tot,*++tot={head[v],u,w},head[v]=tot;
	memset(dis,63,sizeof dis),dis[1]=0;
	dij();
	for(int i=1;i<=k;i++){
		tp=0;
		for(int j=1;j<=n;j++){
			long long ox=2*j,oy=dis[j]+1ll*j*j;
			while(tp>1&&(__int128)(oy-qy[tp])*(qx[tp]-qx[tp-1])<=(__int128)(qy[tp]-qy[tp-1])*(ox-qx[tp]))tp--;
			qx[++tp]=ox,qy[tp]=oy;
		}
		for(int j=1;j<=n;j++){
			int l=1,r=tp;
			while(l<r){
				int mid=l+r>>1;
				if(qy[mid+1]-qy[mid]<1ll*j*(qx[mid+1]-qx[mid]))l=mid+1;
				else r=mid;
			}
			dis[j]=1ll*j*j+qy[l]-1ll*j*qx[l];
		}
		dij();
	}
	for(int i=1;i<=n;i++)printf("%lld ",dis[i]);
	return 0;
}
```


---

## 作者：_lxy_ (赞：1)

### CF1715E 题解

[博客食用效果更佳](https://www.cnblogs.com/lxy-2022/p/CF1715E-Solution.html)

#### 题意

一个带边权无向图，可以沿着边走，需要边权的花费或从任意点 $u$ 飞到 $v$，需要 $(u-v)^2$ 的花费。求从点 $1$ 到所有 $i$ 的最少花费。最多飞 $k$ 次。

#### 分析

一眼最短路 + dp。

发现 $k$ 很小，可以枚举飞的次数，对于点 $u$，可以是走到 $u$，这种情况可以用最短路更新答案；也可以是飞到 $u$，此时可以 dp，$dp_i$ 表示从 $1$ 到 $i$ 最小花费，转移方程很显然：
$$
dp_i=\min\limits_{t=1}^n(dis_t+(i-t)^2)
$$
，其中 $dis_i$ 表示上个 $k$ 算出的 $1$ 到 $i$ 最少花费。此时最外层循环 $k$，中层循环 $i$，内层循环 $t$，时间复杂度 $\mathcal{O}(kn^2)$，发现会 T，考虑优化。

发现这个式子是个典型的斜率优化形式，可以变形成：
$$
dp_i=\min\limits_{t=1}^n(dis_t+(i-t)^2) 
=\min\limits_{t=1}^n(dis_t+t^2-2it)+i^2
$$
也就转化成了求 $x=i$ 时所有直线 $y=-2tx+(dis_t+t^2)$ 的最小值加上 $i^2$ 的值。可以用李超线段树方便地求出。

[code](https://codeforc.es/problemset/submission/1715/171185147)



---

## 作者：Un1quAIoid (赞：1)

**洛谷传送门：** [CF1715E Long Way Home](https://www.luogu.com.cn/problem/CF1715E)

-------------------------------

个人感觉不错的一道图论+dp的题目

-------------------------------

首先应当想到从城市 $1$ 到 $i$ 的路程必然可以看作是先走若干条（可能是零条）道路，然后乘坐一次航班，再走若干条道路，然后再次乘坐一次航班……如此循环不超过 $k$ 次得到。其次注意到 $k \le 20$ 的数据范围，不难考虑到可以通过某些算法维护一轮行动，然后直接暴力维护 $k$ 轮即可。

记 $\{dis_i\}$ 为上一轮结束后从 $1$ 到 $i$ 点的最短路，初始 $dis_1=0$，其余全为 $+\infty$。

首先考虑走若干条道路的部分，建立超级源点 $S$，从 $S$ 向点 $i$ 连边权为 $dis_i$ 的有向边，然后跑一遍 $\text{Dijkstra}$ 即可，这是图论中的常见套路，比较显然。

然后考虑 $\text{dp}$ 以维护乘坐航班的部分，我们有：

$$
dis'_i = \min_{1 \le j \le n} \{dis_j+(i-j)^2\}
$$

不妨令 $j \le i$ ，对于 $j > i$ 部分的贡献可以倒着再做一遍 $\text{dp}$，发现这就是经典斜率优化的式子：

$$
2ij+dis'_i-i^2=dis_j+j^2
$$

单调队列维护下凸包即可。

代码：

```cpp
//CF1715E Long Way Home
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;
const ll INF = 0x3fffffffffffffff;

int n, m, k;
ll dis[MAXN], f[MAXN];
bool flag[MAXN];

vector<pair<int, ll> > G[MAXN];
priority_queue<pair<ll, int> > Q;

void dijkstra() {
    memset(dis, 0x3f, sizeof(dis));
    memset(flag, 0, sizeof(flag));
    dis[0] = 0;
    Q.push(make_pair(0, 0));
    while (!Q.empty()) {
        int top = Q.top().second;
        Q.pop();
        if (flag[top]) continue;
        flag[top] = 1;
        for (auto to : G[top])
            if (dis[to.first] > dis[top] + to.second) {
                dis[to.first] = dis[top] + to.second;
                Q.push(make_pair(-dis[to.first], to.first));
            }
    }
}

int Q1[MAXN];
int head, tail;

inline ll X(int x) { return x; }
inline ll Y(int x) { return dis[x] + (ll) x * x; }
inline long double slope(int a, int b) { return (long double) (Y(b) - Y(a)) / (X(b) - X(a)); }

inline void dp() {
    head = 1, tail = 0;
    Q1[++tail] = 1;
    for (int i = 2; i <= n; i++) {
        while (head < tail && slope(Q1[head], Q1[head + 1]) < 2 * i) head++;
        f[i] = min(dis[i], dis[Q1[head]] + (ll) (i - Q1[head]) * (i - Q1[head]));
        while (head < tail && slope(i, Q1[tail]) < slope(i, Q1[tail - 1])) tail--;
        Q1[++tail] = i;
    }

    head = 1, tail = 0;
    Q1[++tail] = n;
    for (int i = n - 1; i; i--) {
        while (head < tail && slope(Q1[head], Q1[head + 1]) > 2 * i) head++;
        f[i] = min(f[i], dis[Q1[head]] + (ll) (i - Q1[head]) * (i - Q1[head]));
        while (head < tail && slope(i, Q1[tail]) > slope(i, Q1[tail - 1])) tail--;
        Q1[++tail] = i;
    }

    for (auto &to : G[0]) to.second = f[to.first];
}

void solve() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        G[u].emplace_back(v, x);
        G[v].emplace_back(u, x);
    }

    G[0].emplace_back(1, 0);
    for (int i = 2; i <= n; i++) G[0].emplace_back(i, INF);
    
    for (int i = 1; i <= k; i++) {
        dijkstra();
        dp();
    }

    dijkstra();

    for (int i = 1; i <= n; i++) printf("%lld ", dis[i]);
}

int main() {
    solve();
    return 0;
}
```

---

## 作者：Luciylove (赞：0)

这个 $k$ 非常小，所以我们考虑全部依次飞这 $k$ 次行程。

这个飞来飞去是一个平方的形式，我们考虑优化这一形式。

首先我们知道从 $u$ 飞到 $v$ 后就可以这样做：

$$dis_u + (u -v)^2 \to dis_v$$

$$dis_u + u^2 + v^2 - 2uv \to dis_v$$

这里我们可以钦定 $u < v$，然后斜率优化做两遍，但是感觉不如直接写李超树维护即可。

但是更新后的点可以在走一些路，然后就会更新到一些城市的答案，所以考虑先进行算完斜率优化，再跑一遍 dijkstra 即可。

时间复杂度 $kn\log (n+ m)$。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ls u << 1
#define rs u << 1 | 1

const int N = 1e5 + 5, MOD = 998244353;

struct NODE {
	int u, w;
	bool operator < (const NODE & x) const {
		return w > x.w;
	} 
};

priority_queue <NODE> q;
vector <pair<int, int>> e[N];

struct line {
	int k, b;
	line (int k = 0, int b = 1e16) : k(k), b(b) {}	
	inline int val (int x) { return k * x + b; }
} ;

struct lichaotree {
	line t[N << 2];
	inline void clear (int u, int l, int r) {
		if (l == r || t[u].k == 0) return ;
		t[u].k = 0, t[u].b = 1e18; 
		int mid = (l + r) >> 1;
		clear(ls, l, mid), clear(rs, mid + 1, r);
	}
	inline void modify (int u, int l, int r, line x) {
		if (l == r) {
			if (x.val(l) < t[u].val(l)) t[u] = x; 
			return ;
		} int mid = (l + r) >> 1;
		if (x.val(mid) < t[u].val(mid)) swap(x, t[u]);
		if (x.val(l) < t[u].val(l)) modify(ls, l, mid, x);
		if (x.val(r) < t[u].val(r)) modify(rs, mid + 1, r, x);
	}
	inline int query (int u, int l, int r, int pos) {
		int res = t[u].val(pos), mid = (l + r) >> 1;
		if (l == r) return res;
		if (pos <= mid) return min(res, query(ls, l, mid, pos));
		else return min(res, query(rs, mid + 1, r, pos));
	}
} lct;

int n, m, k;
int dist[N];

inline void dijkstra () {
	for (int i = 1; i <= n; i ++) q.push({i, dist[i]});
	while (! q.empty()) {
		NODE t = q.top(); q.pop();
		int u = t.u, d = t.w;
		if (d != dist[u]) continue ;
		for (auto & [v, w] : e[u])
			if (dist[v] > d + w) dist[v] = d + w, q.push({v, dist[v]});
	}
}

signed main () {
	ios :: sync_with_stdio(0);
	cin >> n >> m >> k;
	for (int i = 1, u, v, w; i <= m; i ++) {
		cin >> u >> v >> w;
		e[u].emplace_back(v, w), e[v].emplace_back(u, w);
	}
	for (int i = 2; i <= n; i ++) dist[i] = 1e16;
	dijkstra();
	for (int i = 1; i <= k; i ++) {
		lct.clear(1, 1, n);
		for (int j = 1; j <= n; j ++)
			lct.modify(1, 1, n, line(-2 * j, j * j + dist[j]));
		for (int j = 1; j <= n; j ++)
			dist[j] = min(dist[j], lct.query(1, 1, n, j) + j * j);
		dijkstra();
	}
	for (int i = 1; i <= n; i ++) cout << dist[i] << " ";
	return 0;
}
```





---

## 作者：Graphcity (赞：0)

首先可以想到一个非常显然的想法：

- 建立 $k+1$ 层的分层图，第 $i$ 层表示乘坐了 $i$ 次航班。对于每一层按照原图建边，然后让第 $i$ 层的点 $u$ 向第 $i+1$ 层的点 $v$ 建一条 $(u_i,v_{i+1},(u-v)^2)$ 的有向边。

这样显然是 $O(k(n^2+m)\log m)$ 的。它的时间复杂度瓶颈在于不同层之间连的那一条 $(u-v)^2$ 的边，足足有 $n^2$ 条。

但这个边权 $(u-v)^2$ 十分特殊，虽然不能够通过图论模型来表示，但在 DP 中很好维护。

$$
\begin{aligned}
dis_i&=\min_{j=1}^n dis_j+(i-j)^2\\\\
&=dis_j+i^2-2ij+j^2\\
dis_i-i^2&=dis_j+j^2-2ij
\end{aligned}
$$

不妨令 $b=dis_i-i^2,y=dis_j+j^2,k=2i,x=j$，那么就是 $b=y-kx$ 的斜率优化形式。

通过这种斜率优化 DP，我们可以很方便的从第 $i$ 层的 $dis$ 序列推出来第 $i+1$ 层 $dis$ 序列的初始状态。事实上，这就是在优化不同层之间的松弛过程。

对于每一层，先做一次最短路算法，再做一次 DP，最后再统一跑一次最短路即可。时间复杂度 $O(k(n+m\log m))$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;
const ll inf=1e18;

inline int read()
{
    char ch=getchar();
    int f=1,x=0;
    while(ch>'9' || ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

struct Node{int frm,to,nxt,w;} Edge[Maxn*2+5];
int tot,Head[Maxn+5];
inline void Addedge(int x,int y,int z)
{
    Edge[++tot]=(Node){x,y,Head[x],z};
    Head[x]=tot;
}
int n,m,K,Q[Maxn+5],head,tail;
ll dis[Maxn+5],vis[Maxn+5],Y[Maxn+5];
struct Group
{
    int x; ll y;
    inline Group() {}
    inline Group(int _x,ll _y): x(_x),y(_y) {}
};
inline bool operator<(Group a,Group b) {return a.y>b.y;}
priority_queue<Group> q;

inline void Dijkstra()
{
    For(i,1,n) q.push(Group(i,dis[i])),vis[i]=0;
    while(!q.empty())
    {
        int x=q.top().x; q.pop();
        if(vis[x]) continue;
        vis[x]=1;
        for(int i=Head[x];i;i=Edge[i].nxt)
        {
            int y=Edge[i].to;
            if(!vis[y] && dis[x]+Edge[i].w<dis[y])
            {
                dis[y]=dis[x]+Edge[i].w;
                q.push(Group(y,dis[y]));
            }
        }
    }
}
inline double Slope(int a,int b) {return 1.0*(Y[a]-Y[b])/(a-b);}
inline void DP()
{
    head=1,tail=0;
    For(i,1,n) Y[i]=dis[i]+1ll*i*i;
    For(i,1,n)
    {
        while(head<tail && Slope(Q[tail],Q[tail-1])>=Slope(i,Q[tail-1])) tail--;
        Q[++tail]=i;
    }
    For(i,1,n)
    {
        while(head<tail && Slope(Q[head],Q[head+1])<=i*2) head++;
        int j=Q[head];
        dis[i]=Y[j]-2ll*i*j+1ll*i*i;
    }
}

int main()
{
    n=read(),m=read(),K=read();
    For(i,1,n) dis[i]=inf;
    dis[1]=0;
    For(i,1,m)
    {
        int a=read(),b=read(),c=read();
        Addedge(a,b,c),Addedge(b,a,c);
    }
    Dijkstra();
    For(i,1,K) DP(),Dijkstra();
    For(i,1,n) printf("%lld ",dis[i]);
    printf("\n");
    return 0;
}
```

---

## 作者：tangtangpeng (赞：0)

## 题意

给定一张 $n$ 个点，$m$ 条边的无向图，边有边权，可以顺着边走产生大小为边权的代价，也可以从 $u$ 点传送到 $v$ 点并产生 $(u-v)^2$ 的代价，至多传送 $k$ 次，求从 $1$ 号点出发到 $n$ 个点中的每一个点的最小代价。

## 思路

最短路和斜率优化 $dp$。

考虑设计状态，$f[i][u]$ 表示已经传送了 $i$ 次，此时在 $u$ 号点的最小代价。

显然当 $i=0$ 时，直接跑一遍最短路就可以了。

考虑如何转移 $i-1\to i$，先讨论最后一次行动是传送的情况，转移为：

$
\begin{aligned}
f[i][u]=\min_{v}\{f[i-1][v]+(u-v)^2\}
\end{aligned}
$

第一维完全可以不要，优化空间复杂度：

$
\begin{aligned}
f[u]=\min_{v}\{f[v]+(u-v)^2\}
\end{aligned}
$

然后讨论最后一次行动是在边上走的情况，跑一遍最短路即可。

但是这样转移的时间复杂度是 $O(n^2)$ 的，无法接受。

考虑用斜率优化的方式快速求出决策点 $v$，将原式的 $\min$ 去掉，展开移项得到：

$
\begin{aligned}
f[v]+v^2=2u\times v+f[u]-u^2
\end{aligned}
$

转化为一次函数 $y=kx+b$ 的形式得到：

$\left\{
\begin{array}{l}
y=f[v]+v^2 \\
k=2u \\
x=v \\
b=f[u]-u^2
\end{array}
\right.$

对应形成的点的坐标就是 $(v,f[v]+v^2)$，最小化 $f[u]$ 就是最小化截距 $b$，又因为从 $1$ 到 $n$，斜率 $k$ 单调递增，我们维护一个下凸包即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1E5 + 10;
int n, m, k;
int f[N], g[N], ans[N];
bool vis[N];

struct Edge
{
	int nxt, to, val;
}G[N * 4];
int head[N], cnt;

void add(int u, int v, int w)
{
	G[++cnt].nxt = head[u];
	G[cnt].to = v;
	G[cnt].val = w;
	head[u] = cnt;
}

void spfa()
{
	queue<int> Q;
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++)
	{
		Q.push(i);
		vis[i] = 1;
	}
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		vis[u] = 0;
		for(int i = head[u]; i; i = G[i].nxt)
		{
			int v = G[i].to;
			if(f[v] > f[u] + G[i].val)
			{
				f[v] = f[u] + G[i].val;
				if(!vis[v])
				{
					Q.push(v);
					vis[v] = 1;
				}
			}
		}
	}
}

int X(int j){return j;}
int Y(int j){return g[j] + j * j;}
double slope(int i, int j){return (X(i) - X(j)) ? (double)(Y(i) - Y(j)) / (double)(X(i) - X(j)) : 2100000000;}

signed main()
{
	memset(ans, 0x3f, sizeof(ans));
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		add(u, v, w);
		add(v, u, w);
	}
	memset(f, 0x3f, sizeof(f));
	f[1] = 0;
	spfa();
	while(k--)
	{
		int Q[N];
		int h = 1, t = 0;
		memset(Q, 0, sizeof(Q));
		memcpy(g, f, sizeof(g));
		for(int i = 1; i <= n; i++)
		{
			while(h < t && slope(Q[t - 1], Q[t]) >= slope(Q[t], i))
				t--;
			Q[++t] = i;
		}
		for(int i = 1; i <= n; i++)
		{
			while(h < t && slope(Q[h], Q[h + 1]) <= (double)i * 2.0)
				h++;
			f[i] = g[Q[h]] + (i - Q[h]) * (i - Q[h]);
		}
		spfa();
		for(int i = 1; i <= n; i++)
			ans[i] = min(ans[i], f[i]);
	}
	for(int i = 1; i <= n; i++)
		cout << ans[i] << " ";
	return 0;
}
```


---

