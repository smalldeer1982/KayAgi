# ROADS - Roads

## 题目描述

题面描述  
有标号为1……n的城市与单行道相连。对于每条道路有两个与之相关的参数：道路的长度以及需要支付的费用（用硬币的数量表示）  
鲍勃和爱丽丝曾经生活在城市1。在注意到爱丽丝在他们喜欢玩的卡牌游戏中作弊后，鲍勃决定与爱丽丝分手并搬走——去城市n。他希望尽快到达那里——越快越好，然而他现在有些现金短缺。
我们希望帮助鲍勃找到从城市1到城市n的一条最短路径——但他必须用他现有的钱支付得起。

## 样例 #1

### 输入

```
2
5
6
7
1 2 2 3
2 4 3 3
3 4 2 4
1 3 4 1
4 6 2 1
3 5 2 0
5 4 3 2
0
4
4
1 4 5 2
1 2 1 0
2 3 1 1
3 4 1 0```

### 输出

```
11
-1```

# 题解

## 作者：lqx_bnu (赞：6)

一道dfs+邻接表存图……  
其实就是一道带有限制的dfs  
上代码带注释  
```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#define mem(a,b) memset(a,b,sizeof(a))//数组初始化
#define inf 0x3f3f3f3f
#define N 100+20
#define M 1000000+10
#define ll long long
using namespace std;
int first[N],vis[N],t;
int k,n,m,len,sum;
struct node//存边
{
    int u,v,w,cost;//编号，左节点,花费
    int next;//下一条边
}g[10200];
void add_edge(int,int,int,int);//建边
void dfs(int,int,int);//搜索
int main()
{
    scanf("%d",&t);
    while(t--)
    {
    	int a,b,c,d;
    	len=0,sum=0;
    	mem(vis,0);
    	mem(first,-1);
    	scanf("%d%d%d",&k,&n,&m);
	    for(int i=0; i<m; i++)
	    {
	        scanf("%d%d%d%d",&a,&b,&c,&d);
	        add_edge(a,b,c,d);
	    }
	    sum=inf;
	    dfs(1,0,0);
	    if(sum==inf)
	        puts("-1");
	    else
	        printf("%d\n",sum);
	}
    return 0;
}
void add_edge(int u,int v,int w,int cost)
{
    g[len].v=v;
    g[len].w=w;
    g[len].cost=cost;
    g[len].next=first[u];
    first[u]=len++;
}
void dfs(int x,int step,int cost)
{
    if(cost>k||step>sum)//剪枝：花费大于要求或长度大于已知
        return;
    if(x==n)
        sum=min(sum,step);//回溯
    for(int i=first[x]; i!=-1; i=g[i].next)//邻接表遍历
    {
        int v=g[i].v;
        if(!vis[v])
        {
            vis[v]=1;
            dfs(v,step+g[i].w,cost+g[i].cost);//下一步
            vis[v]=0;//回溯
        }
    }
}
```

---

## 作者：くろねこ (赞：4)

为什么题解里面全是DFS呢..

这不是一道图论吗?!

蒟蒻献上一篇Dijkstra + 堆优化 题解qwq

------------

```cpp
//不要问我为什么不要vis数组我也不知道! 
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;
#define rg register
template <typename qwq> inline void read(qwq & x)//读优 
{
	x = 0;
	rg int f = 1;
	rg char c = getchar();
	while (c < '0' || c > '9')
	{
		if (c == '-') f = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getchar();
	}
	x *= f;
}
template <typename qaq> inline void print(qaq x)//输优 
{
	if (x < 0)
	{
		putchar('-');
		x = -x;
	}
	if (x > 9) print(x / 10);
	putchar(x % 10 + '0');
}
struct edge//前向星邻接表 
{
	int u,v,w,c,next;
}e[23333];
int head[23333],tot;
inline void add(int x,int y,int z,int c)
{
	++tot;
	e[tot].u = x;
	e[tot].v = y;
	e[tot].w = z;
	e[tot].c = c;
	e[tot].next = head[x];
	head[x] = tot;
}
#define Pair pair<int,int> 
priority_queue<pair<int,Pair>,vector<pair<int,Pair> >,greater<pair<int,Pair> > > heap;
//Dijkstra堆优化 核心:第一位放 起始点到当前点的距离(不然小根堆无法自动维护)
//然后接上pair,里面放上 当前点编号 当前点硬币花费 (顺序不定) 
int maxc,w,x,y,z,ans = -1;
int n,m;
inline void DJ(int st)
{
	while(!heap.empty()) heap.pop();//清空堆 
	heap.push(make_pair(0,make_pair(0,st)));//放进第一个点 
	while(!heap.empty())
	{
		rg int x = heap.top().second.second;//node
		rg int w = heap.top().first;//dist
		rg int c = heap.top().second.first;//cost
		if (x == n)//循环到最后一个点,说明能够到达n,可以直接退出 
		{
			ans = w;//将ans的-1值覆盖 
			return;
		}
		heap.pop();
		for (rg int i = head[x];i;i = e[i].next)//前向星寻找下一个点 
		{
			rg int v = e[i].v;//node
			rg int cc = e[i].c;//cost
			rg int ww = e[i].w;//dist
			if (c + cc <= maxc /*&& dis[v] > dis[x] + ww*/)//如果硬币足够的话可以走到下一点 
			{
//				dis[v] = dis[x] + ww;
				heap.push(make_pair(w + ww,make_pair(cc + c,v)));
			}
		}
	}
}
int t;
int main()
{
	read(t);
	while (t--)
	{
		memset(head,0,sizeof head);
		tot = 0;
		ans = -1;
		read(maxc),read(n),read(m);
		for (rg int i = 1;i <= m;++i)
		{
			read(w),read(x),read(y),read(z);
			add(w,x,y,z);
		}
		DJ(1);
		print(ans),putchar('\n');
	}
	
}
```

---

## 作者：⚡LZSY01_XZY⚡ (赞：2)

~~竟然没有人写SPFA❗~~ ~~关于spfa，它还没有凉透~~  
广告：[$\color{#ff4081}\small\texttt{我的博客}$](http://lzxzy-blog.cnblogs.com)。SPFA告诉我前途在何方...
### web:
- [$\color{#ff4081}POJ$](http://poj.org/problem?id=1724)
- [$\color{#ff4081}LUOGU$](https://www.luogu.org/problemnew/show/SP338)

## SPFA+堆优化
SPFA是一种理论复杂度高，但常数特小的一种算法。SPFA在这题的优越性就显示出来了。  
[$\color{#ff4081}\small\texttt{我的提交记录}$](https://www.luogu.org/recordnew/show/18768682)

因为这题要求到达$n$的最短距离，我们就以距离为权排序。需要注意的是我们压入队列的元素不能是$dis$数组，因为距离和花费会相互限制。具体看代码。另外，注意，尽量使用前向星存图，它比邻接矩阵快多了。

$My~Code:$
```cpp
#include <cstring>
#include <cstdio>
#include <bitset>
#include <queue>
using namespace std;

int read()
{
    int x=0,f=1;char c=getchar();
    while (c<'0' || c>'9'){if (c=='-')f=-1;c=getchar();}
    while (c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-48;c=getchar();}
    return x*f;
}

const int MAXN=105;
const int MAXM=10005;
int d,n,m,id;

struct edge
{
    int v,w,c,nx;
}set[MAXM];
int head[MAXN],dis[MAXN];

struct Qu
{
    int dot,dis,cost;
    bool operator < (const Qu tmp) const
    {
        return dis>tmp.dis;
    }                                             //距离优先
};
priority_queue<Qu> Q;

inline void Addedge(int u,int v,int w,int c)
{
    id++;set[id].v=v;set[id].w=w;set[id].c=c;set[id].nx=head[u];
    head[u]=id;
}

inline void init()
{
    id=0;
    memset(head,-1,sizeof(head));
    memset(dis,0x3f,sizeof(dis));
    while (!Q.empty())Q.pop();
}

inline void make_map()
{
    d=read();n=read();m=read();
    int u,v,w,c;
    for (int i=1;i<=m;i++)
    {
        u=read();v=read();w=read();c=read();
        Addedge(u,v,w,c);
    }                            //建图
}

inline void SPFA()
{
    Q.push((Qu){1,0,0});dis[1]=0;
    int u,v,w,c;
    while (!Q.empty())
    {
        u=Q.top().dot;w=Q.top().dis;c=Q.top().cost;
        Q.pop();if (u==n)return ;
        for (int k=head[u];k>0;k=set[k].nx)
        {
            v=set[k].v;
            if (c+set[k].c<=d)
            {
                if (w+set[k].w<dis[v])dis[v]=w+set[k].w;
                Q.push((Qu){v,w+set[k].w,c+set[k].c});
            }
        }
    }
}                             //求最短路

int main()
{
    int cas;cas=read();
    while (cas--)
    {
        init();
        make_map();
        SPFA();
        printf("%d\n",dis[n]==0x3f3f3f3f?-1:dis[n]);
    }
    return 0;
}
```
另外，题目要求的是单向边。并且，我似乎暂时还是[$\color{#ff4081}\small\texttt{最优解}$](https://www.luogu.org/recordnew/lists?uid=&pid=SP338&status=&sort=1)。在这份代码中，没有用$vis$数组，因为$c$和$w$每个搭配都不会一样。

$Please~give~a~like.$

---

## 作者：MoyunAllgorithm (赞：1)



**题意**

给你 $N$ 边 $M$ 点无向图。每条边有权值 $w$ 和花费 $c$。求出总花费 $\le K$ 的最短路（即最小权路径）。

**分析**

注意到 $w$ 权值的积累过程和 $c$ 花费的积累过程完全一致。因此可以在 Dijkstra 算法的基础上稍加修改解决问题。

定义数组 $dis_{u,i}$ 代表到达点 $u$ 且花费 $i$ 的最短路。

使用堆优化的 Dijkstra。相似地，设立 $vis_{u,i}$ 代表到点 $u$ 且花费 $i$ 这一状态是否已经被用过。

在 Dijkstra 模板中，我们的 `priority_queue` 的内部变量是 `pair<int,int>`，第一维是目前的权值和，第二维是点，按照权值和排序。

在这里，改为 `priority_queue<Point>`。`Point` 结构体有 $dis,u,cost$ 三维，代表目前权值和，点和花费和。**按照 $dis$ 排序，不需要将 $cost$ 作为关键字，因为我们不需要最小化花费，只需要保证其不超过限制即可。**

松弛也有所变化：Dijkstra 的松弛是：$dis_v \leftarrow \text{min}(dis_v,dis_u+w(u,v))$。

配合二维数组，$dis_{v,k+c(u,v)} \leftarrow \text{min}(dis_{v,k+c(u,v)},dis_{u,k}+w(u,v))(k+c(u,v) \le K)$。

**其实，由于很难存在两个花费和相同的路径，所以不加 $vis$ 数组似乎是可以通过的。**

**核心代码**

```cpp
struct Point
{
	int v,w,c;
	bool operator < (const Point &r) const
	{
		return w>r.w;
	}
};
vector<Point>gra[105];
int Dijkstra()
{
	for(int i=1;i<=N;i++)
	{
		for(int j=0;j<=K;j++)
		{
			dis[i][j]=1e9;
			vis[i][j]=0;
		}
	}
	dis[1][0]=0;
	priority_queue<Point>heap;
	heap.push({1,0,0});
	while(heap.size())
	{
		int u=heap.top().v,cost=heap.top().c;
		heap.pop();
		if(u==N) break;
		if(vis[u][cost]) continue;
		vis[u][cost]=1;
		for(Point cur:gra[u])
		{
			int v=cur.v,w=cur.w,c=cur.c;
			if(c+cost>K) continue;
			if(dis[v][c+cost]>dis[u][cost]+w)
			{
				dis[v][c+cost]=dis[u][cost]+w;
				heap.push({v,dis[v][c+cost],c+cost});
			}
		}
	}
	int ans=1e9;
	while(heap.size()) heap.pop();
	for(int i=0;i<=K;i++) ans=min(ans,dis[N][i]);
	return ans==1e9?-1:ans;
}
```


---

## 作者：liupei (赞：0)

## 题意
给定一个有 $n$ 个点 $r$ 条边的带权有向图，其中第 $i$ 条边的起始点是  $s_i$，终点是 $d_i$，长度是 $l_i$，花费是 $t_i$。求在总费用不超过 $k$ 的情况下从 $1$ 到 $n$ 的最短路径长度。

数据范围：$1\leqslant s_i,d_i\leqslant n,2\leqslant n\leqslant 100,1\leqslant r,k\leqslant10000,1\leqslant l_i\leqslant100,1\leqslant t_i\leqslant 100$。

## 题解
两维 dijkstra，有点类似于 DP。

给出以下定义：

$dis_{i,j}$：从点 $1$ 到 $i$，且刚好花费 $j$ 的情况下的最短距离。
$vis_{i,j}$：是否在花费刚好为$j$的情况下经过点 $i$，是为 $1$，否为 $0$。

那我们不难想出这样的方程：$dis_{v,j+cost_{i}}=dis_{i,j}+v_i$（前提：$j+cost_i\leqslant k$，其中：

$cost_i$ 代表经过第 $i$ 条边的花费；
$v_i$ 代表第 $i$ 条边的长度；
$k$ 如题意所述。
具体实现和 dijkstra 类似，注意多组数据要清空数组和队列（如果不使用堆优化则无需考虑该点），特判核心代码中括号内的情况。

非常简明的一道最短路题目，做起来需要多动脑筋。

## 代码
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

int T, n, k, r, s, d, l, t, h[20007], cnt, dis[107][10007], vis[107][10007], ans;
struct edge {
	int v, cost, to, nxt;
}e[20007];
priority_queue<pair<int, pair<int, int> > > q;

inline void a_e(int u, int v, int w, int cost) {
	e[++cnt] = (edge){w, cost, v, h[u]}; h[u] = cnt;
}
inline int read() {
	int f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();	
	}
	return x * f;
}
inline int dijkstra() {
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= k; ++j)
			dis[i][j] = 0x3fffffff;
	dis[1][0] = 0;
	q.push(make_pair(0, make_pair(0, 1)));
	while(!q.empty()) {
		int x1 = q.top().first, x2 = q.top().second.first, x3 = q.top().second.second;
		q.pop();
		if(vis[x3][x2])	continue;
		vis[x3][x2] = 1;
		for(int i = h[x3]; i; i = e[i].nxt) {
			int y = e[i].to, z = e[i].v, ko = e[i].cost;
			if(dis[y][x2 + ko] > dis[x3][x2] + z && x2 + ko <= k) {
				dis[y][x2 + ko] = dis[x3][x2] + z;
				if(!vis[y][x2 + ko])
					q.push(make_pair(-dis[y][x2 + ko], make_pair(x2 + ko, y)));
			}
		}
	}
	int ans = 0x3fffffff; 
	for(int i = 0; i <= k; ++i)
		ans = min(ans, dis[n][i]);
	return ans == 0x3fffffff ? -1 : ans;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		memset(vis, 0, sizeof(vis));
		memset(e, 0, sizeof(e));
		memset(h, 0, sizeof(h));
		cnt = 0, ans = 0x3fffffff;
		while(!q.empty())	q.pop();
		scanf("%d%d%d", &k, &n, &r);
		for(int i = 1; i <= r; ++i) {
			scanf("%d%d%d%d", &s, &d, &l, &t);
			a_e(s, d, l, t);
		}
		printf("%d\n", dijkstra());
	}	
}
```


---

## 作者：Eason_AC (赞：0)

## Update
- $\texttt{2020.11.9}$ 修改了一下公式。

## Content
给定一个有 $n$ 个点 $r$ 条边的带权有向图，其中第 $i$ 条边的起始点是 $s_i$，终点是 $d_i$，长度是 $l_i$，花费是 $t_i$。求在总费用不超过 $k$ 的情况下从 $1$ 到 $n$ 的最短路径长度。

**数据范围：$1\leqslant s_i,d_i\leqslant n,2\leqslant n\leqslant 100,1\leqslant r,k\leqslant10000,1\leqslant l_i\leqslant100,1\leqslant t_i\leqslant 100$。**

## Solution
两维 dijkstra，有点类似于 DP。

给出以下定义：

$dis_{i,j}:$ 从点$1$到$i$，且刚好花费$j$的情况下的最短距离。  
$vis_{i,j}:$ 是否在花费刚好为$j$的情况下经过点$i$，是为$1$，否为$0$。

那我们不难想出这样的方程：$dis_{v,j+cost_{i}}=dis_{i,j}+v_i$（前提：$j+cost_i\leqslant k$）  
其中：
- $cost_i$ 代表经过第 $i$ 条边的花费；
- $v_i$ 代表第 $i$ 条边的长度；
- $k$ 如题意所述。

具体实现和 dijkstra 类似，注意多组数据要清空数组和队列（如果不使用堆优化则无需考虑该点），特判核心代码中括号内的情况。

非常简明的一道最短路题目，做起来需要多动脑筋。

## Code
```cpp
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

int T, n, k, r, s, d, l, t, h[20007], cnt, dis[107][10007], vis[107][10007], ans;
struct edge {
	int v, cost, to, nxt;
}e[20007];
priority_queue<pair<int, pair<int, int> > > q;

inline void a_e(int u, int v, int w, int cost) {
	e[++cnt] = (edge){w, cost, v, h[u]}; h[u] = cnt;
}
inline int read() {
	int f = 1, x = 0;
	char c = getchar();
	while(c < '0' || c > '9') {
		if(c == '-')	f = -1;
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();	
	}
	return x * f;
}
inline int dijkstra() {
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j <= k; ++j)
			dis[i][j] = 0x3fffffff;
	dis[1][0] = 0;
	q.push(make_pair(0, make_pair(0, 1)));
	while(!q.empty()) {
		int x1 = q.top().first, x2 = q.top().second.first, x3 = q.top().second.second;
		q.pop();
		if(vis[x3][x2])	continue;
		vis[x3][x2] = 1;
		for(int i = h[x3]; i; i = e[i].nxt) {
			int y = e[i].to, z = e[i].v, ko = e[i].cost;
			if(dis[y][x2 + ko] > dis[x3][x2] + z && x2 + ko <= k) {
				dis[y][x2 + ko] = dis[x3][x2] + z;
				if(!vis[y][x2 + ko])
					q.push(make_pair(-dis[y][x2 + ko], make_pair(x2 + ko, y)));
			}
		}
	}
	int ans = 0x3fffffff; 
	for(int i = 0; i <= k; ++i)
		ans = min(ans, dis[n][i]);
	return ans == 0x3fffffff ? -1 : ans;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		memset(vis, 0, sizeof(vis));
		memset(e, 0, sizeof(e));
		memset(h, 0, sizeof(h));
		cnt = 0, ans = 0x3fffffff;
		while(!q.empty())	q.pop();
		scanf("%d%d%d", &k, &n, &r);
		for(int i = 1; i <= r; ++i) {
			scanf("%d%d%d%d", &s, &d, &l, &t);
			a_e(s, d, l, t);
		}
		printf("%d\n", dijkstra());
	}	
}
```

---

## 作者：yqkkkkk (赞：0)

### 题目很水，多思考！！！
蒟蒻打了70多行代码，210ms

~~暴力出奇迹~~

### 附上题解：

```cpp
#include<iostream>
#include<limits.h>
#include<stdio.h>
#include<vector>
#include<string.h> 
using namespace std;
inline int read()//快速读入 
{
	int sign=1,num=0;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')sign=-1;ch=getchar();}
	while(isdigit(ch)){num=num*10+(ch-'0');ch=getchar();}
	return sign*num;
}
int x,y,c,k,n,r,book[1010],step[1010],money[1010];
struct data{int l,t;}f;
vector<vector<vector<data > > > v;//邻接立方体了解一下~~~ 
void init()//初始化 
{
	memset(book,0,sizeof(book));
	for(int i=1;i<=n;++i)
		step[i]=INT_MAX;//limits.h 
	for(int i=1;i<=n;++i)
		money[i]=INT_MIN;
		
	v.clear();//多组数据，每次一定要clear 
	
	v.resize(n+1);//申请空间，否则无法在v[x][y]中push_back() 
	for(int i=0;i<=n;++i)
		v[i].resize(n+1);
} 
void dfs(int set,int dis,int spend)//set为当前位置，dis代表现在到达这里的距离，spend代表现在到达这里花费的距离 
{
	if(dis>step[n] || spend>k || (dis>=step[set] && money[set]<=spend))return;//剪枝 
	//注意：此处要保证步数（step）和花费（money）都要是最小 
	money[set]=spend; 
	step[set]=dis;
	//更新money和step的值 
	if(set==n)return;
	for(int i=1;i<=n;++i)//枚举城市 
	{
		if(book[i])continue; 
		for(int j=0;j<v[set][i].size();++j)//枚举道路 
		{
			book[i]=1;//记录城市已被走过 
			dfs(i,dis+v[set][i][j].l,spend+v[set][i][j].t);//尝试到达这个城市 
			book[i]=0;//回溯 
		}
	}
}
int main()
{
	c=read();
	while(c--)
	{
		k=read();
		n=read();
		r=read();
		init();
		for(int i=1;i<=r;++i)
		{
			x=read();
			y=read();
			f.l=read();
			f.t=read();
			v[x][y].push_back(f);//数据是单向边，且城市a到城市b会有多条边 
		}
		book[1]=1;
		dfs(1,0,0);
		if(step[n]==INT_MAX)printf("-1\n");//如果step[n]的值没有被改变，直接输出-1 
		else printf("%d\n",step[n]);//若被改变，输出到达n的最小步数 
	}
}
```

### 纯代码：

```cpp
#include<iostream>
#include<limits.h>
#include<stdio.h>
#include<vector>
#include<string.h> 
using namespace std;
inline int read()
{
	int sign=1,num=0;
	char ch=getchar();
	while(!isdigit(ch)){if(ch=='-')sign=-1;ch=getchar();}
	while(isdigit(ch)){num=num*10+(ch-'0');ch=getchar();}
	return sign*num;
}
int x,y,c,k,n,r,book[1010],step[1010],money[1010];
struct data{int l,t;}f;
vector<vector<vector<data > > > v;
void init()
{
	memset(book,0,sizeof(book));
	for(int i=1;i<=n;++i)
		step[i]=INT_MAX;
	for(int i=1;i<=n;++i)
		money[i]=INT_MIN;
	v.clear();
	v.resize(n+1);
	for(int i=0;i<=n;++i)
		v[i].resize(n+1);
} 
void dfs(int set,int dis,int spend)
{
	if(dis>step[n] || spend>k || (dis>=step[set] && money[set]<=spend))return;
	money[set]=spend; 
	step[set]=dis;
	if(set==n)return;
	for(int i=1;i<=n;++i)
	{
		if(book[i])continue; 
		for(int j=0;j<v[set][i].size();++j)
		{
			book[i]=1;
			dfs(i,dis+v[set][i][j].l,spend+v[set][i][j].t);
			book[i]=0;
		}
	}
}
int main()
{
	c=read();
	while(c--)
	{
		k=read();
		n=read();
		r=read();
		init();
		for(int i=1;i<=r;++i)
		{
			x=read();
			y=read();
			f.l=read();
			f.t=read();
			v[x][y].push_back(f);
		}
		book[1]=1;
		dfs(1,0,0);
		if(step[n]==INT_MAX)printf("-1\n");
		else printf("%d\n",step[n]);
	}
}
```

---

## 作者：EmpyreanCz (赞：0)

思路

dfs（只不过要用邻接表存）

邻接表是由表头结点和表结点两部分组成，其中表头结点存储图的各顶

点，表结点用单向链表存储表头结点所对应顶点的相邻顶点（也就是表

示了图的边）。在有向图里表示表头结点指向其它结点（a->b）,无向图

则表示与表头结点相邻的所有结点（a—b）

----------------------------------------------------------

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 1010;
const int INF = 1e6;

struct node {
	int s,e,len,cost;
	int nxt;
} cc[10*N];

int n,m,num,head[N],vis[N];
int ans;
//插入一条边 
void cr(int a,int b,int c,int d) {
	cc[num].s=a;
	cc[num].e=b;
	cc[num].len=c;
	cc[num].cost=d;
	cc[num].nxt=head[a];//让插入的元素指向下一个 
	head[a]=num++;//让之前的指向插入的 
}
//x表示当前的起点，y表示走过路径的长度，z表示当前的总费用 
void dfs(int x,int y,int z) {
	if(y>ans)return;
	if(x==n && z>=0 && y<ans) ans=y;
	for(int i=head[x]; i!=-1; i=cc[i].nxt) {
		int u=cc[i].e;
		if(!vis[u] && z >= cc[i].cost) {
			vis[u]=1;
			dfs(u,y+cc[i].len,z-cc[i].cost);
			vis[u]=0;
		}
	}
}

int main() {
	int i,a,b,c,d,k;
	int yyy;
	cin>>yyy;
	while(yyy--) {
		cin>>k>>n>>m;
		num=0;
		memset(head,-1,sizeof(head));
		for(i=0; i<m; i++) {
			scanf("%d%d%d%d",&a,&b,&c,&d);
			cr(a,b,c,d);
		}
		ans=INF;
		memset(vis,0,sizeof(vis));
		dfs(1,0,k);
//		printf(ans<INF?"%d\n":"-1\n",ans);
		if(ans<INF)cout<<ans<<endl;
		else cout<<-1<<endl;
	}


	return 0;
}

```

---

