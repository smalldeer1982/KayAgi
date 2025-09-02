# [USACO09MAR] Earthquake Damage 2 G

## 题目描述

Wisconsin has had an earthquake that has struck Farmer John's farm! The earthquake has damaged some of the pastures so that they are unpassable. Remarkably, none of the cowpaths was damaged.

As usual, the farm is modeled as a set of P (1 <= P <= 3,000) pastures conveniently numbered 1..P which are connected by a set of C (1 <= C <= 20,000) non-directional cowpaths conveniently numbered 1..C. Cowpath i connects pastures a\_i and b\_i (1 <= a\_i <= P; 1 <= b\_i <= P). Cowpaths might connect a\_i to itself or perhaps might connect two pastures more than once.  The barn is located in pasture 1.

A total of N (1 <= N <= P) cows (in different pastures) sequentially contacts Farmer John via moobile phone with an integer message report\_j (2 <= report\_j <= P) that indicates that pasture report\_j is undamaged but that the calling cow is unable to return to the barn from pasture report\_j because she could not find a path that does not go through damaged pastures.

After all the cows report in, determine the minimum number of pastures that are damaged.

地震袭击了威斯康星州，一些牧场被摧毁了。

一共有 $P$ 个牧场。由 $C$ 条双向路连接。两个牧场间可能有多条路。一条路也可能连接相同的牧场。牛棚坐落在牧场 $1$。

$N\ (1 \le N \le P)$ 只奶牛打来了求救电话，说她们的农场没有被摧毁，但是已经无法到达牛棚。求出最少可能有多少牧场被摧毁。


## 说明/提示

Only pasture 2 being damaged gives such a scenario.


## 样例 #1

### 输入

```
5 5 2 
1 2 
2 3 
3 5 
2 4 
4 5 
4 
5 
```

### 输出

```
1 
```

# 题解

## 作者：RiverFun (赞：6)

> 广告：推销[$\texttt{BLOG}$](https://stevebraveman.github.io/)

这道题有个比较相似的题目：[[USACO5.4]奶牛的电信Telecowmunication](https://www.luogu.org/problemnew/show/P1345)

先把这道题装换成人话：有n个点不能割，请问从这n个点到1之间至少得扔掉多少个点使这n个点不能和1号点连通。

直接上最小割。

首先我们进行拆点，把第 $i$ 个点拆成 $i$ 和 $i+n$ 两个点，如果这个点能割，那么就在 $i$ 和 $i + n$ 之间连一条容量为 $1$ 的边，如果不能，则连容量为 $INF$ 的边。

然后我们根据道路连接情况连接正反两条容量为 $INF$ 的边。

之后我们再把超级源点和不能割的点相连，容量为$INF$，把 $1$ 号点定位超级汇点。

最后我们再跑Dinic就行了。

Code：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define MAXN 1000002
#define INF 2000000000
int min(int a, int b) {
    if (a < b) return a;
    else return b;
}
struct Edge {
    int v, nx, w;
} e[MAXN];
std::queue <int> q;
int n, m, head[MAXN], ecnt = 1, x, y, z, r, k, dep[MAXN], cur[MAXN], cnt = 1, totp = 0, tot, xi, yi, c;
bool dest[MAXN];
void add(int f, int t, int w) {
    e[++ecnt] = (Edge) {t, head[f], w};
    head[f] = ecnt;
    e[++ecnt] = (Edge) {f, head[t], 0};
    head[t] = ecnt;
}
bool bfs(int s, int t) {
    memset(dep, 0x7f, sizeof(dep));
    while (!q.empty()) q.pop();
    for (int i = 1; i <= 2 * n + 1; i++) {
        cur[i] = head[i];
    }
    dep[s] = 0;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = head[v]; i; i = e[i].nx) {
            int to = e[i].v;
            if (dep[to] > INF && e[i].w) {
                dep[to] = dep[v] + 1;
                q.push(to);
            }
        }
    }
    if (dep[t] < INF) return 1;
    else return 0;
}
int dfs(int u, int t, int l) {
    if (!l || u == t) return l;
    int fl = 0, f;
    for (int i = cur[u]; i; i = e[i].nx) {
        cur[u] = i;
        int to = e[i].v;
        if (dep[to] == dep[u] + 1 && (f = dfs(to, t, min(l, e[i].w)))) {
            fl += f;
            l -= f;
            e[i ^ 1].w += f;
            e[i].w -= f;
            if (!l) break;
        }
    }
    return fl;
}
int Dinic(int s, int t) {
    int maxf = 0;
    while (bfs(s, t)) {
        maxf += dfs(s, t , INF);
    }
    return maxf;
}
int a[MAXN], b[MAXN];
int main() {
    scanf("%d%d%d", &n, &m, &c);
    r = 2 * n + 1;
    k = 1;
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &x, &y);
        add(x + n, y, INF);
        add(y + n, x, INF);
    }
    for (int i = 1; i <= c; i++) {
        scanf("%d", &x);
        dest[x] = 1;
        add(r, x, INF);
    }
    for (int i = 1; i <= n; i++) {
        if (dest[i] != 1) {
            add(i, i + n, 1);
        }
        else {
            add(i, i + n, INF);
        }
    }
    tot = Dinic(r, k);
    printf("%d\n", tot);
    return 0;
}
```

---

## 作者：tzyt (赞：3)

update：2022/4/17 增加了博客地址

看到题解里面还没有用STL vector做的，所以我就来交一发。

[题目链接](https://www.luogu.com.cn/problem/P2944)

[博客](https://ttzytt.com/2021/08/P2944/)中观看体验更佳

# 1：转化题意
在一张图中，一共有 $p$ 个节点，$c$ 条双向边，有 $n$ 个节点不能删除，求出最少需要删除多少个节点才能使得这 $n$ 个固定点**都到达不了**$1$号节点。

# 2：分析和建模
在完成题意的转化之后，我们发现题目要让我们删除一些点（尽量少），使得整张图变成两个不连通的部分，网络流算法中的最小割（最大流）算法可以处理这这个问题。

【不熟悉最大流算法的同学可以先做一下模板题】
[最大流模板](https://www.luogu.com.cn/problem/P3376)

但是我们又发现，一般的最小割处理的是 “删除图的一部分边使得图的两部分变得不连通” 而这道题目让我们删除的是图中一部分节点。于是我们就需要把节点转换成边。

我使用的方法是把每一个节点拆分成两个节点（出点和入点），具体的做法可以参考 
[P1345 奶牛的电信Telecowmunication](https://www.luogu.com.cn/problem/P1345)
这道题中的题解。

这里来简单解释一下这种做法：首先，我们把图中的每一个点拆分成两个点：出和入点。

并且这两个节点之间有一条单向边连接

![](https://cdn.luogu.com.cn/upload/image_hosting/bwz3xg8l.png)

每条指向这个点的有向边都只能连接这个点的入点。并且从这个节点出发的有向边都只能从它的出点出发。

![](https://cdn.luogu.com.cn/upload/image_hosting/0jw7wfno.png)

那么，把每个节点分成出点和入点之后有什么用呢？在一般的最小割问题中，如果我们想知道要取消掉多少条边，可以使得这张图的汇点和源点不连通，就可以把每条边的权值设置为$1$，并且可以付出$1$的代价删除这条边。

在以割点为基础的最小割问题中，我们可以把每个节点中连接出点和入点的那条边的权值设置为$1$。这样子如果我们想要删除这个节点，就可以付出$1$的代价，把这条边切断，这个点也就被删除了。

那么问题就来了，这道题目中明确的说明了有一些节点是不能删除的，如果都把权值设置成$1$，如何处理不能删除的节点呢？

对于这些关键节点（不能删除的点），我们可以把他们的内部权值设置成 $INF$，这样就不会把这些点删掉了（最小割算法计算的是付出最小的代价使图变得不连通，**而设置成 $INF$ 会让删掉这个点变得很不合算**）。

另外，我们需要注意，除了题目中说的关键点，源点和汇点也是不能删除的，所以在建图的时候需要处理一下。并且题目让我们求的是最少删去多少个节点，所以连接这些节点的边也是不能删除的，需要把容量设置成 $INF$。

解决了边的容量问题后我们再来考虑源点和汇点，我们可以把$1$号节点设置成源点，把所有关键点连接到汇点上，这样子求出的答案就是让所有关键点都到达不了$1$号节点的最小删除节点数（如果任何一个关键点可以到达一号节点，那么汇点也可以到达$1$号节点）。

## 建图步骤总结：
1. 把每个节点拆成入点和出点，中间连一条内部边
2. 对于能删除的点，内部边的容量设置成$1$
3. 对于不能删除的点，内部边容量设置成 $INF$
4. 不能删除的边包括：
	1. 源点的内部边
   2. 汇点的内部边
   3. 连接每个节点的边
   4. 关键点的内部边
5. 源点设置成$1$号节点，汇点连接所有的关键点

# 3：算法
我采用的是dinic算法，因为每次增广可以找到多条增广路，所以算法的速度会比EK算法高一些，不熟悉这个算法的同学可以去看一下之前提到的最大流模板题的题解。

# 4.代码实现及细节
在实现拆分节点这个操作的时候，我们可以把一个节点的入点的编号设置成它本身的编号，而出点的编号就设置成本身的编号 + $p$（节点总数），这样子可以确保不会重复。

在实现dinic算法时，需要进行对反向边的操作，我使用的是STL vector来存边，因此需要在node结构体中加入rev（reverse）变量，记录当前边的反向边的下标。
```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXM = 100000;
const int INF = 0x3f3f3f3f;
struct node
{
    int to, mflow, rev; //to连接的下个节点的编号
                        //mflow(maxflow)记录当前边的容量
                        //rev(reverse)记录当前边的反向边的下标
};
int p, c, n, s, t;
vector<node> edge[MAXM];
int g_farm[MAXM];                            //完好的农场（关键点）
int layer[MAXM];                             //每个节点的层数
node assign_node(int to, int mflow, int rev) //赋值函数
{
    node temp;
    temp.to = to, temp.mflow = mflow, temp.rev = rev;
    return temp;
}

void add_edge(int from, int to, int mflow) //加边
{
    edge[from].push_back(assign_node(to, mflow, edge[to].size()));   //不需要-1是因为edge[to]还没有push过 from这个节点
    edge[to].push_back(assign_node(from, 0, edge[from].size() - 1)); //-1是因为vector的下标是从0开始的，而.size()会返回元素的数量
}

namespace dinic
{
    bool layering() //分层
    {
        bool vis[MAXM];
        memset(vis, false, sizeof(vis));
        memset(layer, 0, sizeof(layer));
        queue<int> q;
        vis[s] = true;
        layer[s] = 1;
        q.push(s);
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (auto nex : edge[cur]) //c++11的新特性，意思是用nex遍历edge[cur]中的所有元素
            {
                if (nex.mflow > 0 && vis[nex.to] == false)
                {
                    layer[nex.to] = layer[cur] + 1;
                    q.push(nex.to);
                    vis[nex.to] = true;
                }
            }
        }
        return (layer[t] != 0); //返回分层操作是否成功（是否能从源点到达汇点）
    }

    int find_aug_path(int cur, int cur_flow) //寻找增广路
    {
        if (cur == t)
        {
            return cur_flow;
        }
        int ans = 0;
        for (int i = 0; i < int(edge[cur].size()); i++)
        {
            if (edge[cur][i].mflow > 0 && layer[edge[cur][i].to] == layer[cur] + 1)
            {
                int nex_flow = find_aug_path(edge[cur][i].to, min(cur_flow, edge[cur][i].mflow));
                edge[cur][i].mflow -= nex_flow;                            //正向边
                edge[edge[cur][i].to][edge[cur][i].rev].mflow += nex_flow; //反向边
                cur_flow -= nex_flow;
                ans += nex_flow;
                if (cur_flow <= 0) //如果当前的容量已经不够了，就直接返回来节省时间
                {
                    return ans;
                }
            }
        }
        return ans;
    }

    int find_maxflow()
    {
        int ans = 0;
        while (layering())
        {
            ans += find_aug_path(s, INF);
        }
        return ans;
    }
}

void input_creat() //输入和建图
{
    scanf("%d%d%d", &p, &c, &n);
    s = 0, t = 2 * p + 1;
    add_edge(0, 1, INF);     //再搞一个点接入源点的入点，容量也要设成INF
    add_edge(1, 1 + p, INF); //源点的入点和出点设置成INF
    for (int i = 1; i <= c; i++)
    {
        int from, to;
        scanf("%d%d", &from, &to);
        add_edge(from + p, to, INF); //from的出点和to的入点相连
        add_edge(to + p, from, INF); //to的出点和from的入点相连
    }
    for (int i = 1; i <= n; i++)
    { //n是不能割的点
        int point;
        scanf("%d", &point);
        add_edge(point + p, t, INF);     //把所有关键点连接到汇点
        add_edge(point, point + p, INF); //所有关键点的内部边的容量都要设成INF
        g_farm[point] = 1;               //标记关键点
    }
    for (int i = 2; i <= p; i++)
    {
        if (!g_farm[i])
        {
            add_edge(i, i + p, 1); //除了关键点的其他点可以删，所以内部边的容量设成1
        }
    }
}

main()
{
    input_creat();
    printf("%d", dinic::find_maxflow());
    system("pause");
}
```

第一次写题解，问题可能比较多，如果看到题解有什么不对的欢迎在评论区提出，或者私信我，有看不懂的地方也欢迎提问。最后，如果这篇题解对你有帮助就点个赞吧，或者在评论区中交流你的看法。

---

## 作者：ker_xyxyxyx_xxs (赞：2)

[P2944 [USACO09MAR]Earthquake Damage 2 G](https://www.luogu.com.cn/problem/P2944)

~~水题解ing~~

题意：$ P $ 个点，$ N $ 个固定点，给出一些双向边，求最少割掉多少点使得 $ 1 $ 号点与其他点不连通。

首先常规套路，割点就一定需要拆点，所以将每个点拆为两个点，如果这个点（设为 $ x $）是固定点（不可割点），连边：$ x \rightarrow x + p $，容量为 $ \infty $，和这个点的出点 $ x + p \rightarrow $ 汇点 $ T $，容量为 $ \infty $。

如果这个点不是固定点，连边：$ x \rightarrow x + p $，容量为 $ 1 $。

接下来考虑边，由于边不可割，所以每条边的起点的出点向终点的入点连边，表示： $ x + p \rightarrow y $，容量为 $ \infty $，记住是双向，所以都要连。

最后考虑源点，直接向 $ 1 $ 号点连容量为 $ \infty $ 即可。

至于这样连边的原理，非常套路。$ \infty $ 表示为不可割，$ 1 $ 表示可以割。

最后利用最小割最大流定理求出最小割。

Code
```cpp
# include <iostream>
# include <cstdio>
# include <cstring>
# include <queue>

using namespace std;
const int N = 1e6 + 5;
const int M = 2e6 + 5;
const int inf = 0x3f3f3f3f;

typedef struct {
	int x , y , z , next;
} Edge;
Edge edge[M];
int elast[N] , E = 1;
void add(int x , int y , int z) {
	E ++;
	edge[E].x = x;
	edge[E].y = y;
	edge[E].z = z;
	edge[E].next = elast[x];
	elast[x] = E;
}
int S , T;
int dis[N] , cnt[N];
void bfs(int start) {
	queue<int> q;
	q.push(start);
	dis[start] = 0;
	cnt[S] = 1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = elast[cur] ; i ; i = edge[i].next) {
			int v = edge[i].y;
			if (dis[v] != -1) continue;
			dis[v] = dis[cur] + 1;
			q.push(v);
			cnt[dis[v]] ++;
		}
	}
}
int cur[N];
int dfs(int u , int flow) {
	if (u == T) return flow;
	int delta = 0;
	for (int i = cur[u] ; i ; i = edge[i].next) {
		cur[u] = i;
		int v = edge[i].y;
		if (edge[i].z > 0 && dis[u] == dis[v] + 1) {
			int temp = dfs(v , min(flow - delta , edge[i].z));
			edge[i].z -= temp;
			edge[i ^ 1].z += temp;
			delta += temp;
			if (delta == flow) return delta;
		}
	}
	if (dis[S] >= T + 1) return delta;
	cur[u] = elast[u];
	if (-- cnt[dis[u]] == 0) dis[S] = T + 1;
	cnt[++ dis[u]] ++;
	return delta;
}
int Isap() {
	int ans = 0;
	memset(cnt , 0 , sizeof cnt);
	memset(dis , -1 , sizeof dis);
	bfs(T);
	for (int i = 0 ; i <= T ; i ++) {
		cur[i] = elast[i];
	}
	while (dis[S] < T + 1) ans += dfs(S , inf);
	return ans;
}
int p , n , m;
int x , y;
bool st[N];
int main() {
	cin >> p >> m >> n;
	S = 0 , T = p << 1 | 1;
	add(S , 1 , inf);
	add(1 , S , 0);
	add(1 , p + 1 , inf);
	add(p + 1 , 1 , 0);
	for (int i = 1 ; i <= m ; i ++) {
		scanf("%d%d" , &x , &y);
		add(x + p , y , inf) , add(y , x + p , 0);
		add(y + p , x , inf) , add(x , y + p , 0);
	}
	for (int i = 1 ; i <= n ; i ++) {
		scanf("%d" , &x);
		st[x] = true;
		add(x , x + p , inf) , add(x + p , x , 0);
		add(x + p , T , inf) , add(T , x + p , 0);
	}
	for (int i = 2 ; i <= p ; i ++) {
		if (!st[i]) add(i , i + p , 1) , add(i + p , i , 0); 
	}
	printf("%d\n" , Isap());
	return 0;
}
```

---

## 作者：Dispwnl (赞：2)

> 11.29 修改排版

问题转化：已确定几个点不割，问最少割几个点使图分成两部分

于是考虑最小割

建图，因为最小割是割边，所以拆点

即把每个点拆为入点和出点

确定的点，入点出点之间连边为$∞$

保证最小割集合中不包含这个点，并且与超汇点连边为$∞$

保证经过确定点

未确定点，入点出点之间连边为$1$

最小割集合中可以包含这个点

注意是双向边，还有$1$点也是确定点

代码：
```cpp
# include<iostream>
# include<cstdio>
# include<cstring>
# include<queue>
using namespace std;
const int t=500000;
struct q{
    int x,y,dis;
}c[6000001];
int p,C,n,num;
int h[600001],d[600001];
bool use[3001];
void add(int x,int y,int dis)
{
    c[num].x=h[x];
    c[num].y=y;
    c[num].dis=dis;
    h[x]=num++;
}
bool bfs()
{
    queue<int> qu;
    qu.push(0);
    memset(d,0,sizeof(d));
    d[0]=1;
    while(!qu.empty())
    {
        int tt=qu.front();
        qu.pop();
        for(int i=h[tt];i;i=c[i].x)
          if(!d[c[i].y]&&c[i].dis)
          {
              d[c[i].y]=d[tt]+1;
              qu.push(c[i].y);
          }
    }
    return d[t];
}
int dfs(int x,int dix)
{
    if(x==t) return dix;
    int sum=0;
    for(int i=h[x];i;i=c[i].x)
      if(d[c[i].y]==d[x]+1&&c[i].dis)
      {
          int dis=dfs(c[i].y,min(dix,c[i].dis));
          if(dis)
          {
              sum+=dis;
              dix-=dis;
              c[i].dis-=dis;
              c[i^1].dis+=dis;
              if(!dix) break;
        }
      }
    return sum;
}
int dinic()
{
    int tot=0;
    while(bfs())
    tot+=dfs(0,1e8);
    return tot;
}
int main()
{
    scanf("%d%d%d",&p,&C,&n);
    add(1,0,0);
    add(0,1,1e8);
    add(1+p,1,0);
    add(1,1+p,1e8);
    for(int i=1;i<=C;i++)
      {
          int x,y;
          scanf("%d%d",&x,&y);
          add(x,y+p,0);
          add(y+p,x,1e8);
          add(y,x+p,0);
          add(x+p,y,1e8);
      }
    for(int i=1;i<=n;i++)
      {
          int x;
          scanf("%d",&x);
          use[x]=1; 
          add(x+p,x,0);
          add(x,x+p,1e8);
        add(t,x+p,0);
          add(x+p,t,1e8);
      }
    for(int i=2;i<=p;i++)
      if(!use[i])
      {
          add(i+p,i,0);
          add(i,i+p,1);
      }
    printf("%d",dinic());
    return 0;
}
```

---

## 作者：Soul_Wanderer (赞：1)

# 题解

## [题目传送门](https://www.luogu.com.cn/problem/P2944)

## 题目大意

给你 $p$ 个点，$c$ 条边，其中有 $n$ 个点是固定的，问最少去掉多少个点可以让 $1$ 和这 $n$ 个点不连通。

## 题目思路

这题一看到“**最少**去掉”和“不连通”，一眼最小割，但是这和普通的最小割不太一样，普通的是割边，本题是割点，所以我们要进行拆点，把一个点拆成入点和出点，拆入点连向出点的边。

## 具体建模

首先我们先将第 $i$ 个点拆成 $i$ 和 $i+p$ 两个点，如果它不是固定的点，也就是说它可以割，就将它的入点和出点一连，边权为 $1$，因为扔一个点会对答案产生 $1$ 的贡献；如果它是固定的点，不可以割，就把边权设为无穷大，因为是最小割，所以设为无穷大可以有效保证这个点不会被割掉，只会割那些边权为 $1$ 的点。

再根据点的连接情况，正反建边，边权设为无穷大，因为这个边只是用于表示点的联通情况，不能被割掉。

我们都知道，最小割**等于**最大流，所以再从超级源点向 $1$ 点连一条边权为无穷大的边，所有固定的点分别向超级汇点连一条边权为无穷大的边，这是最大流（最小割）的基本操作。

再跑一遍最大流的板子，**答案**就是从超源到超汇的最大流（最小割）。

还有个细节要注意，$1$ 点的边权也要设为无穷大，它不能被扔掉！

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
const int inf=1451674940337521ll;
struct n1{
	int to,next;
	int flow;//残量 
}e[N<<2];
int head[N],tot=1;
void add(int from,int to,int flow){
	e[++tot].to=to;
	e[tot].flow=flow;
	e[tot].next=head[from];
	head[from]=tot;
	
	e[++tot].to=from;
	e[tot].flow=0;
	e[tot].next=head[to];
	head[to]=tot;
}
int n,m,s,t;
int sum;
int dep[N];
int cur[N];
int bfs(int s,int t){
	memset(dep,0,sizeof(dep));
	queue<int >que;
	dep[s]=1;que.push(s);
	while(que.size()){
		int x=que.front();que.pop();
		for(int i=head[x];i;i=e[i].next){
			int y=e[i].to;
			if(dep[y]==0&&e[i].flow>0){
				dep[y]=dep[x]+1;
				que.push(y);
				if(y==t) return 1;
			}
		}
	}
	return 0;
}
int dfs(int x,int flow){//x点可以流出多少水 
	if(x==t) return flow;
	int rest=flow;//有多少水还没有流出 
	for(int i=cur[x];i&&rest;i=e[i].next){
		cur[x]=i;
		int y=e[i].to;
		if(dep[y]==dep[x]+1&&e[i].flow>0){
			int k=dfs(y,min(rest,e[i].flow));
			if(k==0) dep[y]=0;//如果流出水为0，则没有贡献
			e[i].flow-=k;
			e[i^1].flow+=k;
			rest-=k;
		}
	}
	return flow-rest;//最后向汇点流了多少水 
}
int dinic(int s,int t){
	int maxflow=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		maxflow+=dfs(s,1145141919810ll);
	}
	return maxflow;
}
int p[N];
signed main()
{
	int pp;
	cin>>n>>m;
	cin>>pp;
	s=n*2+1;t=s+1;
	for(int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		add(a+n,b,inf);
		add(b+n,a,inf);
	}
	int cnt=1;
	for(int i=1;i<=pp;i++) cin>>p[i];
	sort(p+1,p+pp+1);
	add(1,1+n,inf);
	add(s,1,inf);
	for(int i=2;i<=n;i++){
		if(p[cnt]==i) add(i,i+n,inf),++cnt,add(i+n,t,inf);
		else add(i,i+n,1);
	}
	cout<<dinic(s,t);
	return 0;
}
```

---

## 作者：Foreverxxx (赞：1)

再次加深对最小割的理解。

### 思路

首先考虑如何去建模。

对于最少割点的问题，首先肯定要想到用最小割去做，经验告诉我们，必须把每个点拆成两个点，讲最少割点问题转化为最小割边即最小割问题。

不过这道题有一个不同之处：有些点是不能被删除的。
这又该怎么做呢？

考虑最小割模型中，源点向节点 $1$ 连边的方式：

```cpp
add(s,1,INF),add(1,s,0);
```

没错，只要把边权设置为 $\infty$ 就可以代表这个点不能被割掉了。

然后我们来考虑图中的边的问题。既然问题要求的是割点而不是割边，那么我们只需要把图中的边边权同样设置成为 $\infty$ 就可以了，表示这条边只是起到了连接两个节点的作用，注意应该是一个点的出点连向另外一个点的入点。

另外，我们需要注意，节点 $1$、源点以及汇点是不能被割掉的。

### 建图的方式

1. 源点与 $1$ 号节点相连，$1$ 节点的入点向出点连边，边权为 $\infty$，表示节点 $1$ 不能被割掉。
2. 按照图中给定的边，连边权为 $\infty$ 的边。
3. 对于不能割掉的点，从这个节点的入点向出点连边权为 $\infty$ 的边，同时出点向汇点连边权为 $\infty$ 的边。
4. 可以被割掉的边，从入点向出点连一条边权为 $1$ 的边。

### 正确性

我们只将源点和节点 $1$ 连接，只将不能被割掉的点和汇点连接，由于他们之间的边权为 $\infty$，所以说节点 $1$ 和那些不能被割掉的点一定是会被划分在两个不同的集合中的。

Code

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int sss=0,www=1;
	char chh=getchar();
	while(chh<'0'||chh>'9'){
		if(chh=='-') www=-1;
		chh=getchar();
	}
	while(chh>='0'&&chh<='9'){
		sss=sss*10+chh-'0';
		chh=getchar();
	}
	return sss*www;
}
int n,m,q,s,t;
bool iscut[6005];
int depth[6005];
int head[6005],to[1000005],nxt[1000005],val[1000005],tot=1;
void add(int u,int v,int w){
	to[++tot]=v;
	val[tot]=w;
	nxt[tot]=head[u];
	head[u]=tot;
}
bool bfs(){
	memset(depth,0,sizeof depth); depth[s]=1;
	queue<int> q; q.push(s);
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(register int i=head[x];i;i=nxt[i]){
			int u=to[i];
			if(val[i]&&!depth[u]){
				depth[u]=depth[x]+1;
				q.push(u);
			}
		}
	}
	return depth[t];
}
int dfs(int now,int flow){
	if(now==t) return flow;
	int out_flow=0;
	for(register int i=head[now];i&&flow;i=nxt[i]){
		int u=to[i];
		if(val[i]&&depth[u]==depth[now]+1){
			int tmp=dfs(u,min(val[i],flow));
			val[i]-=tmp; val[i^1]+=tmp;
			flow-=tmp; out_flow+=tmp;
		}
	}
	if(out_flow==0) depth[now]=0;
	return out_flow;
}
int Dinic(){
	int ans=0;
	while(bfs()) ans+=dfs(s,1e9);
	return ans;
}
int main(){
	n=read(),m=read(),q=read();
	s=0,t=2*n+1;
	add(s,1,1e9); add(1,s,0);//源点不能被割掉 
	add(1,n+1,1e9); add(n+1,1,0);//1节点不能被割掉 
	int u,v;
	for(register int i=1;i<=m;i++){
		//图中所给的边 
		u=read(),v=read();
		add(u+n,v,1e9); add(v,u+n,0);
		add(v+n,u,1e9); add(u,v+n,0);
	}
	for(register int i=1;i<=q;i++){
		u=read(); iscut[u]=true;
		add(u,u+n,1e9); add(u+n,u,0);
		add(u+n,t,1e9); add(t,u+n,0);
	}
	for(register int i=1;i<=n;i++){
		if(!iscut[i]){//可以被割掉 
			add(i,i+n,1); add(i+n,i,0);
		}
	}
	printf("%d",Dinic());
    return 0;
}
```

---

## 作者：破忆 (赞：1)

## 【题意】

给出图，一些点被摧毁，已知某些点与1号点不联通且没有被摧毁，问最少有几个点被摧毁。

## 【分析】

把 $1$ 号点和失去联系的点看成两个点集。

其实就是求将两个点集分开的最小割。

最小割 $=$ 最大流。

考虑如何建图。

------------

首先，被摧毁的是点，非常套路地，将每个点拆成入点和出点。

入点向出点连边，若该点可以被摧毁，则流量是 $1$，否则是 $\inf$，表示摧毁这个点的代价。

然后根据原图连边，若存在边 $(x,y)$，则连接 $(x_{out},y_{in},\inf)$ 和 $(y_{out},x_{in},\inf)$。

源点 $S$ 设为 $1$ 号点的出点，失联点的出点向汇点 $T$ 连边，流量也都为 $\inf$。

用Dinic跑最大流即可。

## 【算法】

最小割最大流

## 【代码】
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=3005,maxt=maxn*2,maxm=2e4+5,maxe=maxn*2+maxm*4,INF=1<<30;
int p,c,n;
int read(){
	int ret=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9') ret=ret*10+ch-'0',ch=getchar();
	return ret*f;
}
struct Dinic{
    int S,T;
    struct edge{
        int to,nxt,f;
    }e[maxe];
    int tot,lnk[maxt];
    void add_e(int x,int y,int f){
        e[++tot]=(edge){y,lnk[x],f};
        lnk[x]=tot;
    }
    void ADD(int x,int y,int f){
        add_e(x,y,f),add_e(y,x,0);
    }
    int que[maxt],cur[maxt],dep[maxt];
    bool BFS(){
        int hed=0,til=1;
        for(int i=1;i<=T;i++) cur[i]=lnk[i],dep[i]=INF;
        que[1]=S,dep[S]=0;
        while(hed!=til){
            int x=que[++hed];
            for(int j=lnk[x];j;j=e[j].nxt){
                int y=e[j].to;
                if(dep[y]==INF&&e[j].f){
                    dep[y]=dep[x]+1;
                    que[++til]=y;
                }
            }
        }
        return dep[T]!=INF;
    }
    int DFS(int x,int limit){
        if(!limit||x==T) return limit;
        int flow=0,f;
        for(int j=cur[x];j;j=e[j].nxt){
            cur[x]=j;
            int y=e[j].to;
            if(dep[y]==dep[x]+1&&(f=DFS(y,min(limit,e[j].f)))){
                e[j].f-=f;
                e[j^1].f+=f;
                flow+=f;
                limit-=f;
            }
            if(!limit) return flow;
        }
        return flow;
    }
    int calc(){
        int ans=0;
        while(BFS()) ans+=DFS(S,INF);
        return ans;
    }
}D;
bool vis[maxn];
int main(){
 	freopen("P2944.in","r",stdin);
 	freopen("P2944.out","w",stdout);
	p=read(),c=read(),n=read(); //注意n、p
	D.S=1+p,D.T=2*p+1,D.tot=1;
	for(int i=1;i<=c;i++){
		int x=read(),y=read();
		D.ADD(x+p,y,INF),D.ADD(y+p,x,INF);
	}
	for(int i=1;i<=n;i++){
		int x=read();
		D.ADD(x+p,D.T,INF); 
		vis[x]=1;
	}
	for(int i=2;i<=p;i++){
		if(vis[i]) D.ADD(i,i+p,INF);
		else D.ADD(i,i+p,1); 
	}
	printf("%d\n",D.calc());
	return 0;
} 
```


---

## 作者：JK_LOVER (赞：1)

## 题意
给你一个含有 $n$ 个点， $m$ 条边， $num$ 个关键点。然后删去一部分点试节点 $1$ 与这 $num$ 个关键点分成两部分，其中关键点并不可以删去。求最少代价。[QWQ](https://www.luogu.com.cn/blog/xzc/solution-p2944)
## 分析
这个是一张图，并非是树，所以我们这里并不能采用 [这道题](https://www.luogu.com.cn/problem/P3931) 的 $dp$ 方法处理。

- 方法选择

可以考虑最大流最小割定理。让超级汇点连接节点 $1$ ，超级源连接这几个关键点。跑最大流就好了。

- 图形建模

拆点时入点向出点连一条容量为 $1$ 的边。而对于关键点不可以删去，直接在拆点的时候，入点向出点连一条容量为 $inf$ 的边即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int read(){
	int x = 0,f = 0;char ch=getchar();
	while(!isdigit(ch)){if(ch=='0')f=1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-'0';ch=getchar();}
	return f?-x:x;
}
const int N = 101010;
struct Edge{int to,nxt,flow,cap;}e[N<<1];
int head[N],cur[N],S,T,n,m,dis[N],cnt = 1;
queue<int> Q;
void add(int x,int y,int cap)
{
	e[++cnt].cap = cap;e[cnt].flow = 0;e[cnt].nxt = head[x];e[cnt].to = y;head[x] = cnt;
	e[++cnt].cap = 0;  e[cnt].flow = 0;e[cnt].nxt = head[y];e[cnt].to = x;head[y] = cnt;
}
bool Bfs(int s,int t)
{
	while(Q.size()) Q.pop();
	memset(dis,0,sizeof(dis));
	dis[s] = 1;Q.push(s);
	while(Q.size())
	{
		int x = Q.front();Q.pop();
		for(int i = head[x];i;i = e[i].nxt)
		{
			int y = e[i].to;
			if(!dis[y] && e[i].cap > e[i].flow)
			{
				dis[y] = dis[x] + 1;
				Q.push(y);
				if(dis[t]){
					return true;
				}
			}
		}
	}
	return false;
}
int Dfs(int x,int a,int t)
{
	if(x == t || a == 0) return a;
	int flow = 0,f = 0;
	for(int i = cur[x];i;i = e[i].nxt)
	{
		int y = e[i].to;
		if(dis[y] == dis[x] + 1 && ((f = (Dfs(y,min(a,e[i].cap - e[i].flow),t))) > 0))
		{
			a -= f;
			flow += f;
			e[i].flow += f;
			e[i^1].flow -= f;
			if(a == 0) break;
			cur[x] = e[i].nxt;
		}
	}
	return flow;
}
int main()
{
	freopen("P2944_2.in","r",stdin);
	n = read();m = read();
	int num = read();
	T = 1+n;S = n+n+1;
	for(int i = 1;i <= n;i++) 
	{
		if(i != 1) add(i,i+n,1);
		else add(i,i+n,0x3f3f3f3f);
	}
	for(int i = 1;i <= m;i++)
	{
		int a = read(),b = read();
		add(a+n,b,1);
		add(b+n,a,1);
	}
	for(int i = 1;i <= num;i++)
	{
		int a = read();
		add(S,a,0x3f3f3f3f);
		add(a,a+n,0x3f3f3f3f);
	}
	int maxflow = 0;
	while(Bfs(S,T))
	{
		for(int i = 1;i <= S;i++) cur[i] = head[i]; 
		maxflow += Dfs(S,0x3f3f3f3f,T);
	}
	cout<<maxflow<<endl;
	return 0;
}
```



---

## 作者：kakakaka (赞：1)

详见本人博客：<http://www.cnblogs.com/huangdalaofighting/p/6915555.html

一道比较经典的最小割，首先因为每次删除的是一个点，所以要将每个点拆开，将1节点和打电话过来的几个节点残量设为最大值，其余的为1。（为了让割边落在可以去掉的点上）这样就可以将去点转化为割边。

然后根据图的连接方式，若节点x被分为x1和x2，节点y被分为y1和y2。若x和y连接，则将x2连y1，y2连x1，残量都为最大值。

然后跑一遍网络流就可以了。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<ctime>
#include<vector>
#define inf (2e8)
using namespace std;
int n,m,l;
struct node
{
    int next,to,cap;
}edge[200001];
int head[100001],size=1,a[190001];
void putin(int from,int to,int cap)
{
    size++;
    edge[size].next=head[from];
    edge[size].to=to;
    edge[size].cap=cap;
    head[from]=size;
}
void in(int from,int to,int cap)
{
    putin(from,to,cap);
    putin(to,from,0);
}
int dist[100001],numbs[100001];
void bfs(int src,int des)
{
    int i;
    queue<int>mem;
    mem.push(des);
    dist[des]=0;numbs[0]++;
    while(!mem.empty())
    {
        int x=mem.front();mem.pop();
        for(i=head[x];i!=-1;i=edge[i].next)
        {
            int y=edge[i].to;
            if(edge[i].cap==0&&dist[y]==0&&y!=des)
            {
                dist[y]=dist[x]+1;
                numbs[dist[y]]++;
                mem.push(y);
            }
        }
    }
    return;
}
int dfs(int src,int flow,int des)
{
    if(src==des)return flow;
    int i,low=0,mindist=n*2+2;
    for(i=head[src];i!=-1;i=edge[i].next)
    {
        int y=edge[i].to;
        if(edge[i].cap)
        {
            if(dist[y]==dist[src]-1)
            {
                int t=dfs(y,min(flow-low,edge[i].cap),des);
                edge[i].cap-=t;
                edge[i^1].cap+=t;
                low+=t;
                if(dist[src]>=n*2+2)return low;
                if(low==flow)break;
            }
            mindist=min(mindist,dist[y]+1);
        }
    }
    if(!low)
    {
        if(!(--numbs[dist[src]]))dist[0]=n*2+2;
        ++numbs[dist[src]=mindist];
    }
    return low;
}
int ISAP(int src,int des)
{
    int ans=0;
    bfs(src,des);
    while(dist[0]<n*2+2)ans+=dfs(src,2e8,des);
    return ans;
}
int main()
{
    int i,j;
    memset(head,-1,sizeof(head));
    scanf("%d%d%d",&n,&m,&l);
    for(i=1;i<=m;i++)
    {
        int from,to;
        scanf("%d%d",&from,&to);
        in(n+from,to,inf);
        in(n+to,from,inf);
    }
    for(i=1;i<=l;i++){scanf("%d",&j);a[j]=1;}
    in(1,n+1,inf);
    for(i=2;i<=n;i++)
    {
        if(a[i]==1){in(i,n+i,inf);in(n+i,2*n+1,inf);}
        else in(i,n+i,1);
    }
    in(0,1,inf);
    int maxflow=ISAP(0,n*2+1);
    cout<<maxflow;
    return 0;
}
```

---

## 作者：Coffee_zzz (赞：1)

### 分析

$1$ 号节点和 $report_1 \sim report_n$ 之间均无路径连接，即 $1$ 号节点和 $report_1 \sim report_n$ 之间的路径被割开了，要求割开的边的最小数量，自然想到最小割。

考虑如何建模。

我们令 $inf$ 表示一个极大值。

我们把 $report_1 \sim report_n$ 都接到超级汇点上，割开 $report_1 \sim report_n$ 和超级汇点之间的边的费用均为 $inf$。

对于给定的边，我们不能割掉，所以将割开这些边的费用也设为 $inf$。

我们可以割掉给定的点。对于每个点 $u$，如果它不属于 $report$，那就把它拆成 $u$ 和 $u+p$，从 $u$ 向 $u+p$ 连一条割开费用为 $1$ 的边，这样就实现了割点的操作。

要注意，增加了割点的操作，连边会受到影响。将 $report_1 \sim report_n$ 接到超级汇点时，要添加 $report_1+p$ 到超级汇点的边、$report_2+p$ 到超级汇点的边、……、$report_n+p$ 到超级汇点的边。同时，对于给定的边，连接的是 $u+p$ 到 $v$ 和 $v+p$ 到 $u$，而非 $u$ 到 $v$ 或 $v$ 到 $u$。

特殊处理一下源点 $1$，割开 $1$ 到 $1+p$ 之间的边的代价应为 $inf$，因为源点不能被破坏。

### 代码

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e4+5,M=2e5+5,inf=1e18;
int p,c,n,s,t,to[M],nxt[M],cap[M],flow[M],head[N],cur[N],dep[N],cnt=1,mf;
bool liv[N];
queue <int> q;
void add(int u,int v,int w){
	cnt++;
	to[cnt]=v;
	nxt[cnt]=head[u];
	cap[cnt]=w;
	head[u]=cnt;
}
bool bfs(){
	int u,v;
	memset(dep,0,sizeof dep);
	while(!q.empty()) q.pop();
	dep[s]=1;
	q.push(s);
	while(!q.empty()){
		u=q.front(),q.pop();
		for(int i=head[u];i;i=nxt[i]){
			v=to[i];
			if(!dep[v]&&cap[i]>flow[i]){
				dep[v]=dep[u]+1;
				q.push(v);
			}
		}
	}
	return dep[t];
}
int dfs(int u,int f){
	if(u==t||!f) return f;
	int ret=0,v,d;
	for(int &i=cur[u];i;i=nxt[i]){
		v=to[i];
		if(dep[u]+1!=dep[v]) continue;
		d=dfs(v,min(f-ret,cap[i]-flow[i]));
		ret=ret+d;
		flow[i]=flow[i]+d;
		flow[i^1]=flow[i^1]-d;
		if(ret==f) return ret;
	}
	return ret;
}
void dinic(){
	while(bfs()){
		memcpy(cur,head,sizeof cur);
		mf=mf+dfs(s,inf);
	}
}
signed main(){
	int u,v;
	cin>>p>>c>>n;
	s=1,t=0;
	for(int i=1;i<=c;i++) cin>>u>>v,add(u+p,v,inf),add(v,u+p,0),add(v+p,u,inf),add(u,v+p,0);
	for(int i=1;i<=n;i++) cin>>u,liv[u]=1;
	add(s,s+p,inf),add(s+p,s,0);
	for(int i=2;i<=p;i++){
		if(liv[i]==1) add(i,i+p,inf),add(i+p,i,0),add(i+p,t,inf),add(t,i+p,0);
		else add(i,i+p,1),add(i+p,i,0);
	}
	dinic();
	cout<<mf;
	return 0;
}
````

---

## 作者：_qingshu_ (赞：0)

# 题意：

与寻常最小割点问题大抵相同，不做过多赘述（如果没有做过最小割点问题的，可以考虑左拐隔壁 [P1345](https://www.luogu.com.cn/problem/P1345)）。有区别的地方在于本题有 $N$ 个点是无法被割断的（因为她们说她们的农场是没有被摧毁的）。

# 思路：

首先考虑源点汇点，因为汇点已经给出为 $1$ 号点，所以我们只需要建立一个超级源向 $N$ 个打来求救电话的点链接一条边，这个是好操作的。

对于**原图**中每一条边，我们定义流量均为 $inf$，因为我们需要防止混淆究竟割的是什么使该增广路成为非可行流。

考虑如何实现割点，拆点呗。对于有可能被摧毁点入点向出点链接一条流量为 $1$ 的边，如果流量为 $0$ 则表示该点被摧毁。对于不可能被摧毁的点则链接一条流量为 $inf$ 的边，可以无限制经过。

最后套上板子就可以优雅的通过这道题了。

# code：

虽然演示代码使用的 hlpp，但是并不影响理解核心建图思想。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,s,t,ouye;
struct _qingshu_{
	long long to,nxt;
	long long val;
}e[25200010];
long long head[25200010],tot=1; 
long long over[25200010],vist[25200010];
long long gap[25200010],h[25200010];
struct cmp{
	bool operator()(long long x,long long y)const{
		return h[x]<h[y];
	}
};
priority_queue<long long,vector<long long>,cmp>qq;
void add(long long u,long long v,long long w){
	e[++tot].to=v;
	e[tot].nxt=head[u];
	head[u]=tot;
	e[tot].val=w;
	
	e[++tot].to=u;
	e[tot].nxt=head[v];
	head[v]=tot;
	e[tot].val=0;
}
bool bfs(){
	for(long long i=s;i<=t;i++) h[i]=0x3f3f3f3f;
	h[t]=0;
	queue<long long>q;
	q.push(t);
	while(!q.empty()){
		long long x=q.front();
		q.pop();
		for(long long i=head[x];i;i=e[i].nxt){
			long long v=e[i].to;
			if(h[v]>h[x]+1&&e[i^1].val){
				h[v]=h[x]+1;
				q.push(v);
			}
		}
	}
	return (h[s]!=0x3f3f3f3f);
}
void push(long long x){
	for(long long i=head[x];i;i=e[i].nxt){
		long long v=e[i].to;
		if(e[i].val&&h[x]==h[v]+1){
			long long k=min(e[i].val,over[x]);
			e[i].val-=k;
			e[i^1].val+=k;
			over[x]-=k;
			over[v]+=k;
			if(v!=s&&v!=t&&!vist[v]){
				qq.push(v);
				vist[v]=1;
			}
			if(!over[x]){
				return;
			}
		}
	}
}
void relable(long long x){
	h[x]=0x3f3f3f3f;
	for(long long i=head[x];i;i=e[i].nxt){
		long long v=e[i].to;
		if(e[i].val&&h[x]>h[v]+1){
			h[x]=h[v]+1;
		}
	}
}
long long hlpp(){
	if(!bfs()){
		return 0;
	}
	h[s]=2*n+1;
	for(long long i=1;i<=2*n+1;i++){
		if(h[i]!=0x3f3f3f3f){
			gap[h[i]]++;
		}
	}
	for(long long i=head[s];i;i=e[i].nxt){
		long long v=e[i].to;
		if(e[i].val){
			over[v]+=e[i].val;
			e[i^1].val=e[i].val;
			e[i].val=0;
			if(v!=s&&v!=t&&!vist[v]){
				qq.push(v);
				vist[v]=1;
			}
		}
	}
	while(!qq.empty()){
		long long x=qq.top();
		qq.pop();
		vist[x]=0;
		push(x);
		if(over[x]){
			gap[h[x]]--;
			if(!gap[h[x]]){
				for(long long i=1;i<=2*n+1;i++){
					if(i!=s&&i!=t&&h[i]>h[x]&&h[i]<=2*n+1){
						h[i]=2*n+2;
					}
				}
			}
			relable(x);
			gap[h[x]]++;
			vist[x]=1;
			qq.push(x);
		}
	}
	return over[t];
}
long long no[25200010];
int main(){
	cin>>n>>m>>ouye;
	t=1;
	s=2*n+1;
	for(long long i=1,u,v;i<=m;i++){
		cin>>u>>v;
		add(u+n,v,0x3f3f3f3f);
		add(v+n,u,0x3f3f3f3f);
	}	
	for(long long i=1,u;i<=ouye;i++){
		cin>>u;
		no[u]=1;
		add(s,u,0x3f3f3f3f);
	}
	for(long long i=1;i<=n;i++){
		if(no[i]){
			add(i,i+n,0x3f3f3f3f);
		}
		else{
			add(i,i+n,1);
		}
	}
	cout<<hlpp();
}

```

update：

暂无。

---

## 作者：lfxxx (赞：0)

考虑建立最小割模型。

不能到达牛棚说明路径被割断了，对于这样的点 $x$ 建边 $(x,t,inf)$。

由于是牧场被毁，所以考虑拆点 $(in_{u},out_{u},1)$，这条边被割说明牧场被毁。

点与点之间连为 $inf$ 的边，因为路径不会被破坏，跑一遍最小割即可得到答案。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 4e5+114;
const int inf = 1e9+13;
int head[maxn],tot=1;
int dis[maxn];
int In[maxn],Out[maxn],cnt;
int n,m,q;
int S,T;
struct Node{
	int v,nxt,w;
}e[maxn<<2];
void add(int u,int v,int w){
	e[++tot].v=v;
	e[tot].nxt=head[u];
	e[tot].w=w;
	head[u]=tot;
	e[++tot].v=u;
	e[tot].nxt=head[v];
	e[tot].w=0;
	head[v]=tot;
} 
bool bfs(int s){
	for(int i=0;i<=cnt;i++) dis[i]=inf;
	queue<int> q;
	q.push(s);
	dis[s]=1;
	while(q.size()>0){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=e[i].nxt){
			if(e[i].w==0) continue;
			int v=e[i].v;
			if(dis[v]!=inf) continue;
			dis[v]=dis[u]+1;
			if(v==T) return true;
			q.push(v);
		}
	}
	return false;
}
int dinic(int s,int flow){
	if(s==T) return flow;
	int res=flow;
	for(int i=head[s];i;i=e[i].nxt){
		int v=e[i].v;
		if(e[i].w==0||dis[v]!=dis[s]+1) continue;
		int del=dinic(v,min(res,e[i].w));
		res-=del;
		e[i].w-=del;
		e[i^1].w+=del;
		if(res==0) break;
	}
	return flow-res;
}
void build(){
	for(int i=1;i<=n;i++) In[i]=++cnt,Out[i]=++cnt;
	S=++cnt,T=++cnt;
	add(In[1],Out[1],inf);
	for(int i=2;i<=n;i++) add(In[i],Out[i],1);
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		if(u==v) continue; 
		add(Out[u],In[v],inf);
		add(Out[v],In[u],inf);
	}
	for(int i=1;i<=q;i++){
		int x;
		cin>>x;
		add(Out[x],T,inf),add(In[x],Out[x],inf);
	}
	add(S,In[1],inf);
}
signed main(){
	//freopen("T3.in","r",stdin);
	//freopen("T3.out","w",stdout);
	cin>>n>>m>>q;
	build();
	int ans=0;
	while(bfs(S)==true) ans+=dinic(S,inf);
	cout<<ans; 
}
/*
5 5 2
1 2
2 3
3 5
2 4
4 5
4
5
*/
```


---

## 作者：rickyxrc (赞：0)

本文章遵守知识共享协议 CC-BY-NC-SA，同步发表于洛谷题解区，转载时须在文章的任一位置附上原文链接和作者署名（rickyxrc）。推荐在[我的个人博客](https://blog.rickyxrc.cc)阅读。

## 题面大意

在一个无向图中，总共有 $P$ 个点，$C$ 条边。

其中一些点被摧毁了，不过可以确定的是至少 $N(1 \le N \le P)$ 个点没有被摧毁，但是与 $1$ 号点没有连边，请确定可能被摧毁的点的最少数量。

## 解题思路

看到摧毁和多点连通性，我想到了网络流，但是第一个想到的不是网络流而是其它的算法，不过碍于篇幅和正确性，这里就不放出来了。

我们发现，这里的边是不会被摧毁的，只有代表牧场的点可能被摧毁。所以我们先拆点，将每个点套路化地拆成入点和出点，并根据题目信息建图。

而点中间的流量呢？很简单，确定没有被摧毁的点是不能被割掉的，但是它不能到达 $1$ 号点，所以中间是有点要被割掉的，要将源点与其连一条不可割的边，在入点和出点之间连一条不可割的边。

而对于状态不确定的点，都是有可能被割掉的，所以我们要在源点与其连一条不可割的边，在入点和出点之间连一条割代价为 $1$ 的边。

至于汇点，编号显然是 $1$。因为你讨论的是每个点与牛棚的可达性。

核心代码如下：

```cpp
int cut[N];

signed main() {
	scanf("%lld%lld%lld",&n,&m,&k);
	s = 2*n+1;
	while(m--)
		scanf("%lld%lld",&u,&v),
		add(u+n,v,inf),
		add(v+n,u,inf);
	for(int i=1; i<=k; i++)
		scanf("%lld",&tp),
		cut[tp]=1;
	for(int i=1; i<=n; i++)
		if(cut[i])
			add(s,i,inf),
			add(i,i+n,inf);
		else
			add(i,i+n,1);
	t=1;
	printf("%lld",dinic());
	return 0;
}
```

---

## 作者：Z1qqurat (赞：0)

每个呼救的奶牛所在牧场都没有被摧毁，但是已经无法到达牛棚。所以我们可以考虑将无法到达牛棚的牧场看作源点 $s_i$，牛棚看作汇点 $T$，这时候我们只需要跑一个 $S - T$ 割即可。但是这里是多源点！所以我们建立一个超级源点 $S$，向所有源点 $s_i$ 连边。然后求的是最小割点，套路性拆点即可。

连边和拆点倒是有点小坑：

* 牛棚不会被摧毁，所以连 $(1, 1 + n, \infty)$。
* 被确定的没有被摧毁的但是已经无法到达牛棚的点，拆点为边应该连 $(i, i + n, \infty)$，再由超级源点 $S$ 向其连边，$(S, i, \infty)$。
* 还能到达牛棚的点，$(i, i + n, 1)$，容量为 $1$ 表示删去这个点的代价为 $1$。

然后跑一个最大流求 $S - T$ 最小割就可以了！主要还是建边的小细节。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <queue>
#define ll long long
using namespace std;
const int N = 7000, M = 1e6, inf = 1e9;
int n, m, k, s, t, cnt = 1, to[M], limit[M], nxt[M], head[N], cur[N], dis[N];
bool pas[N];
queue <int> q;

void AddEdge(int u, int v, int w) {
    to[++cnt] = v, limit[cnt] = w, nxt[cnt] = head[u], head[u] = cnt;
    to[++cnt] = u, limit[cnt] = 0, nxt[cnt] = head[v], head[v] = cnt;
    return ;
}

int Augmenting(int u, int rest) {
    if(u == t) return rest;
    int ret = 0;
    for (int i = cur[u]; i && rest; i = nxt[i]) {
        cur[u] = i;
        int v = to[i], c = min(rest, limit[i]);
        if(dis[v] == dis[u] + 1 && c) {
            int f = Augmenting(v, c);
            rest -= f, ret += f;
            limit[i] -= f, limit[i ^ 1] += f;
        }
    }
    if(!ret) dis[u] = -1;
    return ret;
}

int MaxFlow(int s, int t) {
    int maxflow = 0;
    while(1) {
        bool bl = 0;
        memset(dis, -1, sizeof(dis));
        memcpy(cur, head, sizeof(head));
        while(!q.empty()) q.pop();
        q.push(s), dis[s] = 0;
        while(!q.empty()) {
            if(bl) break;
            int u = q.front(); q.pop();
            for (int i = head[u]; i; i = nxt[i]) {
                int v = to[i];
                if(limit[i] && dis[v] == -1) {
                    dis[v] = dis[u] + 1;
                    if(v == t) {
                        bl = 1; break;
                    }
                    q.push(v);
                }
            }
        }
        if(dis[t] == -1) return maxflow;
        maxflow += Augmenting(s, 1e9);
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    s = 2 * n + 1, t = 1 + n;
    for (int i = 1; i <= m; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        if(u == v) continue;
        AddEdge(u + n, v, inf), AddEdge(v + n, u, inf);
    }
    for (int i = 1; i <= k; ++i) {
        int a; scanf("%d", &a);
        AddEdge(a, a + n, inf);
        pas[a] = 1;
        AddEdge(s, a, inf);
    }
    AddEdge(1, 1 + n, inf);
    for (int i = 2; i <= n; ++i) {
        if(!pas[i]) AddEdge(i, i + n, 1);
    }
    printf("%d\n", MaxFlow(s, t));
    return 0;
}
```

---

## 作者：Leowang2009 (赞：0)

# 思路

由于是删点，容易想到用拆点的方法。

将一个点拆为两个点——入点和出点。

所有连向该点的边连向该点对应的如点，而从该点连出的边由该点对应的出点连出。

然后连入点和出点。

题目中说明 $1$ 点为终点，所以可以将 $1$ 点的出点向汇点连边权为 $+\infty$ 的边。

而不能到达 $1$ 点的点，则由源点向其入点连边权为 $+\infty$ 的边。

然后所给边连的时候边权为 $+\infty$。

对于可以确定未被摧毁的点，入点与出点间连边权为 $+\infty$ 的边，否则连边权为 $1$ 的边。

这样以来，在求最小割时，割掉的边一定是不确定是否被摧毁的点的出入点间的边，即此时最小割即为答案，此时在建好的图上跑最小割（最大流）即可。

# 代码

因为拆点的原因，空间要开大点。

代码中每一步的作用注释中应该写的挺详细的了。

## AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e4+5,M=1e6+5,inf=0x3f3f3f3f;
int p,c,n,s,t,val,hd[N],ver[M],nxt[M],w[M],idx=1,dis[N],sum;
bool mk[N];
void add(int u,int v,int val){
	ver[++idx]=v,w[idx]=val,nxt[idx]=hd[u],hd[u]=idx;
	ver[++idx]=u,w[idx]=0,nxt[idx]=hd[v],hd[v]=idx;
}
bool bfs(){
	queue<int>q;
	memset(dis,0,sizeof dis),q.push(s),dis[s]=1;
	while(q.size()){
		int p=q.front();
		q.pop();
		for(int i=hd[p];i;i=nxt[i])
			if(!dis[ver[i]]&&w[i])
				dis[ver[i]]=dis[p]+1,q.push(ver[i]);
	}
	return dis[t];
}
int dfs(int pos,int fl){
	if(pos==t||!fl) return fl;
	int used=0;
	for(int i=hd[pos];i;i=nxt[i]){
		int d;
		if(dis[ver[i]]==dis[pos]+1&&w[i]){
			d=dfs(ver[i],min(fl-used,w[i]));
			used+=d,w[i]-=d,w[i^1]+=d;
			if(fl==used) return fl;
		}
	}
	dis[pos]=0;
	return used;
}
int main(){
	scanf("%d%d%d",&p,&c,&n);
	s=0,t=p*2+1;
	add(1,t,inf),add(1+p,1,inf);//1点向汇点连边
	for(int i=1,u,v;i<=c;i++)
		scanf("%d%d",&u,&v),add(u,v+p,inf),add(v,u+p,inf);//连边
	for(int i=1,u;i<=n;i++)
		scanf("%d",&u),add(s,u+p,inf),mk[u]=1;//未被摧毁的点向源点连边，并标记
	for(int i=2;i<=p;i++)
		mk[i]?add(i+p,i,inf):add(i+p,i,1);//判断能否割掉，如果能割掉则连1，否则连inf
	while(bfs())
		sum+=dfs(s,inf);//求最小割
	printf("%d",sum);
	return 0;
}
```

---

## 作者：happybob (赞：0)

## 题意

给定一个无权无向图和 $p$ 个点，需要在图中删去一些点使得这 $p$ 个点和点 $1$ 均不连通且这 $p$ 个点和 $1$ 都没有被删除。问至少删除多少个点。

## 解法

首先先解决这样一个问题：题目要求删点，但是网络流最小割是边权，考虑转化。

对每个点 $u$ 分入点和出点，入点为 $u$，出点为 $u+n$，入点存储入边，出点存储出边。入点和出点之间连边权为 $1$ 的边，表示删除这条边代价为 $1$。删除这条边就意味删除这个点，本身有向图的边都由入点连向出点，边权为 $\inf$，表示边不可删。

考虑和普通最小割的转化。

普通最小割要求 $s$ 和 $t$ 不连通，显然这里 $s=1$，而 $t$ 是这 $p$ 个点的集合，不好直接写。

考虑把这 $p$ 个点都连到一个超级汇点 $t=2n+1$，然后 $p$ 个点的出点都向 $t$ 连接一条边权为 $\inf$，表示 $t$ 和 $p$ 的每个点都连在一起。

注意 $p$ 个点是不能删的，所以 $p$ 个点的入点和出点连边变迁为 $\inf$。

最小割，做完了。

---

## 作者：UperFicial (赞：0)

[传送门](https://www.luogu.com.cn/problem/P2944)。

[更好的阅读体验](https://www.cnblogs.com/UperFicial/p/16034059.html)。

### $\texttt{Description}$

给定一张图，固定一些点，求最小割。

### $\texttt{Solution}$

如果没见过这个套路，分析一下也很容易做出来。

题意已经不是割边，而是割点了，考虑拆点，对于每一个点拆出两个点 $u$ 和 $u'$。，这样就能表示出对于点的限制。

若一个点是固定的，那么连 $u\to u'$，容量为 $\infty$，最小割不会割掉容量为 $\infty$ 的点。$1$ 号点同样也需如此处理，因为 $1$ 不会被割掉。

没固定的点直接连 $u\to u'$，容量为 $1$。

对于原图上的边，是不会被割掉的，连 $u'\to v$，由于是双向边，连 $v'\to u$，容量均为 $\infty$。

然后源点连 $1$，每个点的出点连 $t$，容量同样为 $\infty$。

之后求最大流即可。

---

## 作者：dgdyrkst (赞：0)

# 网络流 最小割

## 思路
拿到题目，先观察，会发现是让我们求出最少要割掉的点的数量。

很容易想到是网络流算法求最小割，dinic 即可。

## 建图
然后开始思考建图。

首先，因为要割去的是点，所以需要运用 __点转边__ 的技巧。

具体地，将一个节点 $x$ 拆成两个节点 $x$ 和 $x+n$，并从 $x+n$ 向 $x$ 连边。

对于一条原图中的有向边 $(x,y)$，我们从 $x$ 向 $y+n$ 连一条边权为原边权的边。

这样一来，只要 $x+n$ 向 $x$ 连的边容量被用尽，从原图中 $x$ 出去的边就再也不能被流过，相当于割去了这个点。

在本题中，由于割掉每个点的贡献都是 $1$,所以从 $x+n$ 向 $x$ 连边边权应当为 $1$。

但要注意一个坑点，题目描述中说打来求救电话的农场 __没有被摧毁__ ，所以对于这些点，连的边权应该改为 $+\infty$，具有防止割掉的意义。

然后对原图中的边 $(x,y)$，由于是无向图，所以应从 $x$ 向 $y+n$ 和 $y$ 向 $x+n$ 都连边，边权也为 $+\infty$，因为割断的是点而不是边。

源点即为题中所给的 $1$ 号点，而由于没有一个汇点，我们应新建一个汇点 $t$，由所有求救的点向 $t$ 连边权为 $+\infty$ 的一条边。

这样一来，当网络流正常结束时，没有一个点能到达 $t$，相当于 $1$ 号点不能到达所有求救的点。

注意不要将 $t$ 和其他点的编号冲突，例如我一开始将其设为 $n+1$，只有 $33$ 分。

## 代码
以下为代码参考。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=6e3+5,M=5e4+5;
const ll inf=1e18;
int n,m,p,s,t,x,y,head[N],now[N],to[M<<1],ne[M<<1],d[N],tot=1;
ll z,w[M<<1],ans;
bool rep[N];
void add(int a,int b,ll c)
{
	tot++;
	ne[tot]=head[a],head[a]=tot,to[tot]=b,w[tot]=c;
}
bool bfs()
{
	queue<int> q;
	memset(d,0,sizeof(d));
	d[s]=1;
	now[s]=head[s];
	q.push(s);
	while (!q.empty())
	{
		int k=q.front();
		q.pop();
		if (k==t)return 1;
		for (int i=head[k];i;i=ne[i])
		{
			if (d[to[i]] || !w[i])continue;
			now[to[i]]=head[to[i]],d[to[i]]=d[k]+1;
			q.push(to[i]); 
		}
	}
	return 0;
}
ll dinic(int k,ll flow)
{
	if (k==t)return flow;
	ll ret=0;
	for (int i=now[k];i && flow>0;i=ne[i])
	{
		now[k]=i;
		if (!w[i] || d[to[i]]!=d[k]+1)continue;
		ll get=dinic(to[i],min(flow,w[i]));
		if (!get)d[to[i]]=0;
		flow-=get,ret+=get;
		w[i]-=get,w[i^1]+=get;
	}
	return ret;
}
int main()
{
	scanf("%d%d%d",&n,&m,&p);
	s=1,t=2*n+1;
	while (m--)
	{
		scanf("%d%d",&x,&y);
		add(x,y+n,inf),add(y+n,x,0),add(y,x+n,inf),add(x+n,y,0);
	}
	while (p--)
	{
		scanf("%d",&x),rep[x]=1;
	}
	for (int i=1;i<=n;i++)
	{
		if (rep[i])add(i+n,i,inf),add(i,i+n,0),add(i,t,inf),add(t,i,0);
		else add(i+n,i,1),add(i,i+n,0);
	}
	while (bfs())
	{
		ans+=dinic(s,inf);
	}
	printf("%lld",ans);
	return 0;
}
```


---

