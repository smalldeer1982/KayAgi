# [BalticOI 2002] Bicriterial routing (Day2)

## 题目描述

给定一张 $n$ 个点、$m$ 条边的无向图。边 $e$ 的长度为二元组 $(c_e, t_e)$。

一条途径 $w$ 的长度 $(c_w, t_w) = (\sum_{e \in w} c_e, \sum_{e \in w} t_e)$。

一条途径 $w$ 比另一条途径 $w'$ 短，当且仅当二者长度不同且 $c_w \le c_{w'}, t_w \le t_{w'}$。

显然可能有两条途径无法比较长短，进而两点间可能出现多条长度不同的最短路径。

求 $s$ 至 $e$ 的最短路径的长度取值的种类数。

## 说明/提示

#### 样例说明

![](https://cdn.luogu.com.cn/upload/image_hosting/2x4o606g.png)

考虑其中四条途径：

0. $1 \to 2 \to 4$（长度为 $(4, 5)$）；
1. $1 \to 3 \to 4$（长度为 $(4, 5)$）；
2. $1 \to 2 \to 3 \to 4$（长度为 $(6, 4)$）；
3. $1 \to 3 \to 2 \to 4$（长度为 $(4, 10)$）。

途径 0、途径 1 均短于途径 3。最短路长度共有两种：$(4, 5)$（途径 0、途径 1）、$(6, 4)$（途径 2）。

#### 数据范围

$1 \le s, e, p, r \le n \le 100$，$0 \le m \le 300$，$s \ne e$，$0 \le c, t \le 100$。

#### 提示

[BalticOI](https://boi.cses.fi/contests.php) 2002 Day2 A.

由于自定义计分脚本参数配置，暂不支持 AC WA TLE MLE 外的评测状态显示。如果你得到了此外任何一种评测状态，你将得到 UKE。

Subtask #0 为样例；Subtask #1 为数据。

## 样例 #1

### 输入

```
4 5 1 4 
2 1 2 1 
3 4 3 1 
2 3 1 2 
3 1 1 4 
2 4 2 4 ```

### 输出

```
2 ```

# 题解

## 作者：daiarineko (赞：6)

## 0. 题意简述

有 $m$ 条双向边，每条有两个权值 $c_i,t_i$，求两点之间的最短路长度。

本题最短路定义：没有其他同时满足 $\sum c_i$ 和 $\sum t_i$ **都**不比它小（当然，如果有两个值都相等的两条路径，只计一次贡献）的路径，则这条路径是一条最短路径。

## 1. 题目分析&主要代码

考察点：最短路、分层图最短路

题目难度：提高+/省选-

时间复杂度：$\Theta(k(n+m)\log (km))$，$k$ 为 $\sum{c_i}$。

### 题目分析 & 主要代码

这显然是一道最短路题。

相信翻到这篇题解的读者，要么是在练习分层图最短路，~~要么是在做一本通提高篇~~。

这里不再详细讲解分层图本身，而是重点讲解怎么应用到这道题中。（如果你想了解，可以去找分层图模板题的题解）

#### 存储

首先，我们要把分层图压缩成一维存储。

这里使用一个函数 `_`（使用下划线是为了打起来方便）。

```cpp
inline int _(int u, int c)
{ //u为原图节点编号，c为层数。
    return c * n + u;
}
```

由于 $u$ 的取值范围是 $[1,n]$，范围长度为 $n$，所以使用 $c\times n+u$ 最为节省空间。

于是可以使用正常前向星存图了。

#### 读入 & 加节点

以下代码中，`add(u, v, w)` 为前向星模板。

```cpp
int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &E);
    int p, r, c, t, maxK = 0;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d%d", &p, &r, &c, &t);
        tmp[i].a = p;
        tmp[i].b = r;
        tmp[i].c = c;
        tmp[i].d = t;
        maxK += c;
    }
    for (int i = 1; i <= m; ++i)
    {
        p = tmp[i].a;
        r = tmp[i].b;
        c = tmp[i].c;
        t = tmp[i].d;
        for (int j = 0; j <= maxK; ++j)
        {
            add(_(p, j), _(r, j + c), t);
            add(_(r, j), _(p, j + c), t);
        }
    }
    ... //省略
}
```

采取离线读入，第一次读入不处理，目的是获取 $\sum c_i$（存储到 `maxK` 变量中）。

> Q. 为什么要获取 $\sum c_i$？  
> A. 考虑极端情况，所有边连成一条链，此时路径的 $\sum c_i$ 即为全局的 $\sum c_i$ 即 `maxK`。此时，分层图的层数即为 `maxK`。

这两行中，由于此条**双向**边的权值 $c_i$ 为 `c`，所以此边跨越 `c` 层，即从第 `j` 层跨越到第 `j + c` 层。

```cpp
            add(_(p, j), _(r, j + c), t);
            add(_(r, j), _(p, j + c), t);
```

#### 跑最短路

由于全为正权，可以使用 Dijkstra 或 SPFA 算法。

这里使用 Dijkstra 堆优化。

这一部分写模板即可。

#### 统计答案

考虑枚举 $\sum c_i$。

具体解释：枚举每个 $\sum c_i$ 的路径中 $\sum t_i$ 最小的一个（已经求出）（也就是终点在每一层的节点 $e$ 上的最短路）。

从小到大枚举，同时维护至今为止的 $\max \sum t_i$，记为 $T$。

如果 $\sum t_i\ge T$，就说明之前枚举到了两个权值都不比当前路径大的一条路径，因此当前路径不计入答案。

```cpp
    int ans = 0, mn = 0x3f3f3fff;
    for (int i = 0; i <= maxK; ++i)
    {
        bool isAns = true;
        if (dis[_(E, i)] >= 0x3f3f3f00 || dis[_(E, i)] >= mn)
            isAns = false;
        mn = min(mn, dis[_(E, i)]);
        if (isAns)
        {
            ++ans;
        }
    }
```

## 2. 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 104, maxm = 304, maxk = 104 * maxm;
struct Temp
{
    int a, b, c, d;
} tmp[maxm];
struct Edge
{
    int v, w, next;
} e[maxm * maxk * 2];
int head[maxn * maxk], cnt;
int n, m, s, E;
int dis[maxn * maxk];

inline int _(int u, int c)
{
    return c * n + u;
}
void add(int u, int v, int w)
{
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}
void dij()
{
    memset(dis, 0x3f, sizeof(dis));
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    dis[_(s, 0)] = 0;
    q.push({0, _(s, 0)});
    while (!q.empty())
    {
        auto t = q.top();
        q.pop();
        int u = t.second;
        if (dis[u] < t.first)
            continue;
        for (int i = head[u]; i; i = e[i].next)
        {
            int v = e[i].v;
            if (dis[v] > dis[u] + e[i].w)
            {
                dis[v] = dis[u] + e[i].w;
                q.push({dis[v], v});
            }
        }
    }
    return;
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &E);
    int p, r, c, t, maxK = 0;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%d%d", &p, &r, &c, &t);
        tmp[i].a = p;
        tmp[i].b = r;
        tmp[i].c = c;
        tmp[i].d = t;
        maxK += c;
    }
    for (int i = 1; i <= m; ++i)
    {
        p = tmp[i].a;
        r = tmp[i].b;
        c = tmp[i].c;
        t = tmp[i].d;
        for (int j = 0; j <= maxK; ++j)
        {
            add(_(p, j), _(r, j + c), t);
            add(_(r, j), _(p, j + c), t);
        }
    }
    dij();
    int ans = 0, mn = 0x3f3f3fff;
    for (int i = 0; i <= maxK; ++i)
    {
        bool isAns = true;
        if (dis[_(E, i)] >= 0x3f3f3f00 || dis[_(E, i)] >= mn)
            isAns = false;
        mn = min(mn, dis[_(E, i)]);
        if (isAns)
        {
            ++ans;
        }
    }
    printf("%d\n", ans);
    return 0;
}

```
## 3. Note

1. 本解法时间复杂度较高，需要 O2 优化才能通过此题。此题可能有更优解法。
2. 注意细节：双向边、非严格单调（含取等情况）。
3. 注意开两倍数组，经试验正好能卡进空间限制。
4. 抄题解是不好的习惯。


---

## 作者：Fleeing_loser (赞：4)

比较好的某种~~特别好用~~最短路算法的题目~~其实我只会写 SPFA~~。\
其实一本通提高篇上还有树状数组优化的做法，但我太菜了，只会简单的 SPFA 优化，下面我们来看一下题目。
### 题目大意

有两一个图，图上每条边两个有两个权值 $c_i$ 和 $t_i$，求两个点 $S$ 与 $T$
的路径上，满足 $t$ 比所有 $c$ 更小的路径还要小，或 $c$ 比所有$t$ 更小的
路径还要小的路径总数，然后这个总数即为双调最短路径的数量。

### 做法

双调最短路，同样也是最短路，跑二维的最短路即可。
设 $dis\left[ i,j \right]$ 表示由 $S$ 到 $i$ 点费用为 $j$ 的路径的最小时间，然后跑 SPFA。
对于每一个 $dis\left[ T,i \right]$,如果有 $dis\left[ T,i \right]<dis\left[ T,j \right] (j<i)$ 恒成立，则 $ans++$。(这里要注意一点，题目中说费用时间都相同的两条最小路径只算作一条)

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+1,ml=1e4+1;
int head[maxn],dis[maxn][maxn*10],cnt;
int n,m,s,t,INF;
bool vis[maxn][maxn*10];
struct node
{
	int v,w,t,nxt;
}e[maxn<<1];
void add(int u,int v,int w,int t)
{
	e[++cnt].v=v;
	e[cnt].w=w;
	e[cnt].t=t;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
typedef pair<int,int> pr;
queue<pr> q; 
void spfa()//跑二维的最短路即可
{
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	INF=dis[0][0]; dis[s][0]=0; vis[s][0]=1;
	q.push(make_pair(s,0));
	while(!q.empty())
	{
		pr tmp=q.front(); q.pop();
		int u=tmp.first,us=tmp.second; vis[u][us]=0;
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v,t=e[i].t,vs=us+e[i].w;
			if(vs<=ml)
			{
				if(dis[v][vs]>dis[u][us]+t) 
				{
					dis[v][vs]=dis[u][us]+t;
					if(!vis[v][vs])
					{
						q.push(make_pair(v,vs)),vis[v][vs]=1;			
					}
				}
			}
		}
	}
}
int main()
{
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;++i)
	{
		int u,v,w,tt;
		scanf("%d%d%d%d",&u,&v,&w,&tt);
		add(u,v,w,tt); add(v,u,w,tt);
	}
	spfa();
	int ans=0,minn=INF;
	for(int i=0;i<=ml;++i)
	{
		if(dis[t][i]<minn) ++ans,minn=dis[t][i];
	}
	cout<<ans;
	
	return 0;
} 
```

---

## 作者：Steven_lzx (赞：3)

在博客园食用以获取更好的体验，请点 [这里](https://www.cnblogs.com/2020gyk080/p/luogu_p8068.html)。

## 前置知识

- SPFA（此题解的优化是基于 SPFA 的，跑起来效率惊人，**甚至比官方标程还快**）
- 树状数组

## 题目

有 $m$ 条双向边，每条有两个权值 $c_i$, $t_i$，求两点之间的最短路长度。

本题最短路定义：没有其他同时满足 $\sum c_i$ 和 $\sum t_i$ 都不比它小（当然，如果有两个值都相等的两条路径，只计一次贡献）的路径。

## 思路

由于此题与一般最短路不同，边有两种权值，所以需要在每个节点处增加一维状态。即用 $dp[i][j]$ 表示在 $i$ 点且已用费用为 $j$ 时的最短时间，则有：$$dp[i][j] = \min \left\{ dp[k][i - cost[k][i]] + time[k][i]\ |\ \text{For each }edge(k, i) \right\}$$

由此，我们可以直接用 SPFA 算法求解。期望时间复杂度为 $O(KN^2V)$。~~已经比官方标程跑的快了~~

## 优化

虽然实际算法运行的很快，然而状态会达到 $100^3$ 的级别，优化空间还很大。

在迭代求解过程中，考虑任意一新状态 $dp[i][j]$，如果已经存在一状态 $dp[i][k]$，满足 $k<j$ 且 $dp[i][k]<dp[i][j]$，则显然 $dp[i][j]$ 不是最优解，我们也就没有更新（将其加入队列）的必要。

于是可以加入这样一个剪枝：对于每个新状态 $dp[i][j]$，我们查询 $dp[i][0...j]$ 的最小值 $minTime$，当 $dp[i][j]<minTime$ 时再进行更新。在实现时我们可以使用树状数组维护 $dp[i]$ ，以加快查询速度。

期望时间复杂度 $O(KN^2V \log N)$，而实际效率惊人，是官方标程的十倍快。

## 代码

```cpp
#define lowbit(x) ((x)&(-x))
const int MAXN=1e4+5;
int nxt[605],v[605],w[605],to[605],head[605],q[1000005][2],dis[105][MAXN],tree[105][MAXN],cnt,n,m,s,t,ans;
bool vis[105][MAXN];
void treearr_add(int x,int y,int val)
{
    y++;        //树状数组不支持下标为0，故+1
    while(y<=n*100)
    {
        tree[x][y]=min(tree[x][y],val);
        y+=lowbit(y);
    }
    return;
}
int treearr_sum(int x,int y)
{
    int res=1e7;
    y++;
    while(y)
    {
        res=min(res,tree[x][y]);
        y-=lowbit(y);
    }
    return res;
}
void g_addedge(int a,int b,int c,int d)     //加边！加边！加边！注意有两个边权
{
    nxt[++cnt]=head[a];
    head[a]=cnt;
    to[cnt]=b;
    v[cnt]=c;
    w[cnt]=d;
    return;
}
void g_sp_SPFA()
{
    int x,f1,y,f2;
    memset(dis,0x3f,sizeof(dis));
    memset(tree,0x3f,sizeof(tree));
    dis[s][0]=0;
    q[1][0]=s;
    q[1][1]=0;
    treearr_add(s,0,0);
    for(int h=1,t=1;h<=t;h++)
    {
        x=q[h][0];
        f1=q[h][1];
        vis[x][f1]=false;
        for(int i=head[x];i;i=nxt[i])
        {
            y=to[i];
            f2=f1+w[i];
            if(treearr_sum(y,f2)>dis[x][f1]+v[i])       //若满足条件，则可能对答案有贡献
            {
                dis[y][f2]=dis[x][f1]+v[i];
                treearr_add(y,f2,dis[y][f2]);
                if(!vis[y][f2])
                {
                    vis[y][f2]=true;
                    q[++t][0]=y;
                    q[t][1]=f2;
                }
            }
        }
    }
    return;
}
int main()
{
    int a,b,c,d,mind;
    scanf("%d %d %d %d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        scanf("%d %d %d %d",&a,&b,&c,&d);
        g_addedge(a,b,d,c);
        g_addedge(b,a,d,c);
    }
    g_sp_SPFA();
    mind=dis[0][0];
    for(int i=0;i<=n*100;i++)       //费用递增，时间递减
    {
        if(dis[t][i]<mind)
        {
            mind=dis[t][i];
            ans++;
        }
    }
    printf("%d\n",ans);
    return 0;
}
```


---

## 作者：lrqlrq250 (赞：2)

## 题意简述

对于一个无向图，每一条边有两个权值 $(c_i, t_i)$，要求出图中给定两点间双调最短路径的条数。其中双调最短路径定义为没有其他路径同时满足 $\sum c_i$ 和 $\sum t_i$ 都小于这条路径。（因此可以看出会有很多最短路径）

## 题目分析

因为现在有了两种边权，因此原本单源最短路中的 $dis$ 数组肯定不能是一维的了，这样无法表示一个双调的大小。

于是很容易想到，我们设 $dis[i][j]$ 为从起点到 $i$ 在权值 $c$ 的值为 $j$ 时 $t$ 的最小值。

在松弛的过程中，显然只有满足这条边 $(from_i, to_i, c_i, t_i)$ 有
- $dis[to_i][nowc + c_i] > dis[from_i][nowc] + t_i$

时，才会进行松弛。

最短路直接使用 SPFA 就可以了，最终期望复杂度为 $O(KN)$。不过在这里（貌似）在初始化 $dis$ 数组时不能使用 memset 函数，只能手动二重循环赋值，因此常数很大。

最终提交：$282ms$

## AC Code
```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
struct Edge{int to, c, t, next;}e[1000000];
struct Node{
	int p, c;
	Node(int _p = 0, int _c = 0): p(_p), c(_c){}
};
int n, m, head[1001], tot, st, en;
int dis[101][30001];
bool vis[101][30001];

inline void addedge(int u, int v, int c, int t){
    e[++tot].to = v;
    e[tot].c = c;
    e[tot].t = t;
    e[tot].next = head[u];
    head[u] = tot;
}

queue<Node> q;
inline void SPFA(){
	q.push(Node(st, 0));
	vis[st][0] = 1; dis[st][0] = 0;
	Node now;
    while (!q.empty()){
        now = q.front(); q.pop();
        if (now.c > m * 100) continue;
        vis[now.p][now.c] = 0;
        for (int i=head[now.p]; i; i=e[i].next){
        	int v = e[i].to, c = e[i].c, t = e[i].t; 
            if (dis[v][now.c + c] > dis[now.p][now.c] + t){
                dis[v][now.c + c] = dis[now.p][now.c] + t;
                if (!vis[v][now.c + c]){
                    vis[v][now.c + c] = 1;
                	q.push(Node(v, now.c + c));
                }
            }
        }
    }
}

int main(){
    scanf("%d%d%d%d", &n, &m, &st, &en);
    int u, v, _c, _t, sumt = 0;
    for (int i=1; i<=m; i++){
        scanf("%d%d%d%d", &u, &v, &_c, &_t);
        addedge(u, v, _c, _t); addedge(v, u, _c, _t);
        sumt += _t;
    }
    for (int i=1; i<=n; i++) for (int j=0; j<=sumt; j++) dis[i][j] = 2e9;
    SPFA();
	int ans = 0, last = 2e9;
    for (int i=0; i<=sumt; i++) if (dis[en][i] < last){
        last = dis[en][i];
        ans++;
    }
    printf("%d", ans);
    return 0;
}
 
```


---

## 作者：tian720 (赞：1)

原题链接：[P8068 [BalticOI 2002 Day2] Bicriterial routing](https://www.luogu.com.cn/problem/P8068)。
## 题意简述：
给定一个无向图，$m$ 条双向边，每一条边有两个权值 $c_i$ 和 $t_i$，求 $s$ 到 $e$ 之间最短路径的方案数（同样的最短路只记一次贡献）。

本题最短路的定义为没有其他路径同时满足 $\sum_{i\in\{s\rightarrow e\}} c_i$ 和 $\sum_{i\in\{s\rightarrow e\}} t_i$ 都小于这条路径。
## 题目分析：
本题是一道分层图最短路，这里提供二维 SPFA 的思路，由于数据范围较小，考虑设计如下状态：
 - $dis[i][j]$ 表示从起点 $s$ 到达点 $i$，当前路径的 $\sum_{k\in\{s\rightarrow i\}} c_k$ 为 $j$ 时的最小 $\sum_{k\in\{s\rightarrow i\}} t_k$ 是多少。

那么对于当前点 $u$，我们枚举它所有的相邻点 $v$，设当前边为 $k$。此时的状态转移方程便是：
$$
dis[v][cost[u]+c[k]]=\min(dis[v][cost[u]+c[k]],dis[u][cost[u]]+t[k])
$$
接下来考虑边界问题，如果不限制边界，我们会发现以前访问过的点会不断再次被访问，第二维度 $j$ 也会不断变大直至爆掉，那么我们便可以累加所有的 $c_i$ 记为 $maxc$ ，每次 $j \leq maxc$ 时才访问，这样就能防止溢出了。

对于答案 $ans$，考虑在 $dis[e][i]$ 上枚举统计。手推就能发现答案集合有一个**重要的特性**：当 $i$ 严格递增时，它所对应的 $t_i$ 就严格递减。这是因为当 $t_i$ 大于等于前面的值时，就会出现 $k\leq i$ 且 $t_k\leq t_i$ 的情况，这就与本题最短路的定义矛盾了，路径 $i$ 也不再是答案中的最短路了，$ans$ 统计的就是所有具有双调性的最短路数量。

时间复杂度最坏 $O(KN^2)$，最好 $O(KN)$，最终提交：$109ms$。
## 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
int n,m,s,e,maxc;
int en[610],las[610],nex[610],c[610],t[610],idx;
int dis[110][30010];
bool st[110][30010];
void add(int x,int y,int cc,int tt){
	en[++idx]=y;
	c[idx]=cc,t[idx]=tt;
	nex[idx]=las[x];
	las[x]=idx;
}
struct node{
	int x,cc;
};
queue<node> q;
void spfa(){
	memset(dis,0x3f3f3f3f,sizeof dis);
	dis[s][0]=0,st[s][0]=1;
	q.push({s,0});
	while(!q.empty()){
		node aa=q.front();
		q.pop();
		st[aa.x][aa.cc]=0;
		for(int i=las[aa.x];i;i=nex[i]){//二维SPFA 
			if(aa.cc+c[i]<=maxc){
				if(dis[en[i]][aa.cc+c[i]]>dis[aa.x][aa.cc]+t[i]){
					dis[en[i]][aa.cc+c[i]]=dis[aa.x][aa.cc]+t[i];
					if(!st[en[i]][aa.cc+c[i]]){
						q.push({en[i],aa.cc+c[i]});
						st[en[i]][aa.cc+c[i]]=1;
					}
				}
			}
		}
	}
}
int ans,lasmin=inf;
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&e);
	for(int i=1;i<=m;i++){
		int p,r,cc,tt;
		scanf("%d%d%d%d",&p,&r,&cc,&tt);
		add(p,r,cc,tt),add(r,p,cc,tt);
		maxc+=cc;
	}
	spfa();
	for(int i=0;i<=maxc;i++)//双调性，ci递增，ti递减 
		if(dis[e][i]<lasmin) ans++,lasmin=dis[e][i];
	cout<<ans;
	return 0;
}
```

---

## 作者：Rainsleep (赞：1)

**前置芝士：spfa,dp**

考虑设计如下状态：
+ $dp[i][j]$ 表示从起点 $s$ 出发走到点 $i$，且花费恰好为 $j$ 所需的最小时间。

对于点 $u$ 来说，我们枚举所有与其相邻的点 $v$，设：
+ 一条形如 $<u,v>$ 的通道，其消耗时间为 $t$，费用为 $c$。
+ 走到点 $u$ 时，已花费 $cost$。
+ $nw = cost + c$，即当前状态走到 $v$ 需要的花费。

则有如下转移方程：
$$dp[v][nw] = \min \{dp[u][cost]+t\}$$

对着这个方程打spfa即可。

**考虑结果的统计**：

从前到后枚举花费 $c$，同时维护目前所用时间的最小值 $minv$

我们所枚举的花费一定最小，我们记录下最小时间，如果在花费更多后，所耗时间减少了，则说明出现了一条 **在当前花费内，时间一定最小的** 路径。 

剩下的就是代码啦：

```cpp
#include<bits/stdc++.h>

using namespace std;

const int N = 110, M = 1210, INF = 2139062143;
const int S = 30010;
int n, m, s, e;

struct Edge
{
	int to, nxt;
	int t, c;
} edges[M];

int idx = 0, head[N];
inline void link(int a, int b, int c, int t)
{
	++ idx;
	edges[idx] = {b, head[a], t, c};
	head[a] = idx;
	return ;
}

bool state[N][S];
int dp[N][S]; // 从s走到i,花费为j的最小时间
typedef pair<int, int> PII;

inline void spfa(int s)
{
	memset(dp, 127, sizeof dp);
	dp[s][0] = 0;
	state[s][0] = true;
	queue<PII>q; // {i, j} 表示走到i花费了j元
	q.push({s, 0});
	while(!q.empty())
	{
		int id = q.front().first;
		int cost = q.front().second;
		q.pop();
		state[id][cost] = false;
		for(int i(head[id]);i;i = edges[i].nxt)
		{
			int to = edges[i].to;
			int w = edges[i].c, t = edges[i].t;
			int nw = cost + w;
			if(nw <= 30000 and dp[to][nw] > dp[id][cost] + t)
			{
				dp[to][nw] = dp[id][cost] + t;
				if(!state[to][nw])
				{
					q.push({to, nw});
					state[to][nw] = true;
				}
			}
		}
	} 
	return ;
}

int main()
{
	int sum = 0;
	scanf("%d %d %d %d", &n, &m, &s, &e);
	for(int i(1);i <= m; ++ i)
	{
		int from, to, cost, time;
		scanf("%d %d %d %d", &from, &to, &cost, &time);
		link(from, to, cost, time);
		link(to, from, cost, time);
		sum += cost;
	}
	spfa(s);
	int maxv = INF, res = 0;
	for(int i(0);i <= sum; ++ i)
		if(dp[e][i] < maxv)
		{
			++ res;
			maxv = dp[e][i];
		}
	printf("%d", res);
	return 0;
}
```

---

细心的同学可能会发现，在状态转移中，我添加了这样一条语句：
+ $nw \le 30000$

考虑 $m \le 300,c \le 100$，最坏情况下我们将每条边都走了一遍，即花费了 $100 \times 300 = 30000$，所以如果我们的花费超过了最大上限，是不能被转移的。

**时间复杂度**

spfa的基础时间复杂度为 $O(nm)$，状态扩展数量为 $n^2$，总时间复杂度为 $O(n^3m)$，但是实际运行效率飞快，猜测可能是因为状态数量在大多数时候都是无法扩展到完全 $n^2$ 的。

---

