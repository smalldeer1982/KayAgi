# [ABC277E] Crystal Switches

## 题目描述

【题面翻译】

给定一张 $n$ 个点 $m$ 条边的无向图。每条边有一个权值 $w \in \{0, 1\}$。$w = 0$ 表示这条边无法通过，$w = 1$ 则可以通过。

有 $k$ 个点上面有按钮 $s_i$。

你现在位于 $1$ 号点。每次，你可以做两件事情中的一件：

1. 移动。移到相邻的一个点上，注意这条边一定是可以通行的。
2. 按开关。此时，全部路的边权取反。即：$w = 0$ 变成 $1$，$w = 1$ 变成 $0$。

请问你是否能够到达 $n$ 号点。如果可以，求出最少移动次数。

translated by @[liangbowen](https://www.luogu.com.cn/user/367488).

## 说明/提示

$2 \le n \le 2 \times 10^5$

$1 \le m \le 2 \times 10^5$

$1 \le k \le n$

保证 $1 \le u_i, v_i \le n$，且 $u_i \ne v_i$。

保证 $1 \le s_1 < s_2 < \cdots < s_k \le n$。

## 样例 #1

### 输入

```
5 5 2
1 3 0
2 3 1
5 4 1
2 1 1
1 4 0
3 4```

### 输出

```
5```

## 样例 #2

### 输入

```
4 4 2
4 3 0
1 2 1
1 2 0
2 1 1
2 4```

### 输出

```
-1```

# 题解

## 作者：liangbowen (赞：33)

## 前言

[题目传送门！](https://www.luogu.com.cn/problem/AT_abc277_e)

[更好的阅读体验？](https://www.cnblogs.com/liangbowen/p/16885496.html)

非常套路的分层图，纪念赛时切掉了。

## 思路

我们以样例来解释。首先，这是最基础的图。

![](https://cdn.luogu.com.cn/upload/image_hosting/ja2h2v7g.png)

我们把图分成两层：第一层是原本 $w = 1$ 的路可以通行，第二层是原本 $w = 0$ 的路可以通行。

连接两层图的边，就是**按钮所在的边**。为什么呢？因为按一下按钮，边权就会全部取反，相当于跑到了不同的层上去。

也就是说，图会变成这个样子：

![](https://cdn.luogu.com.cn/upload/image_hosting/q13xs3cn.png)

此时，边权就是真正的边权了：移动一步的代价为 $1$，所以同一层内，所有边的边权都是 $1$。

按按钮不需要代价，所以切换层的边的代价为 $0$。

然后跑最短路即可。答案就是这张图内的最短路。

由于边权只有 $0$ 与 $1$，所以应该也可以跑 01-bfs，并且时间复杂度是 $O(m)$。

但是为了图方便，我就直接写了 Dijkstra 板子。

## 代码

省去了缺省源。个人认为还是打得很好看的！（自信）

```cpp
const int N = 4e5 + 5; //开2倍
struct Edge {int now, nxt, w;} e[N << 1];
int head[N], cur;
void add(int u, int v, int w)
{
	e[++cur].now = v;
	e[cur].nxt = head[u];
	e[cur].w = w;
	head[u] = cur;
}
void ADD(int u, int v, int w) {add(u, v, w), add(v, u, w);}
 
struct Node {int pos, dis;};
bool operator <(Node y, Node x) {return x.dis < y.dis;}
 
int dis[N];
bool vis[N];
void dijkstra(int s) //完全是 Dijkstra 板子，你甚至可以复制板子的代码
{
	memset(dis, 0x3f, sizeof dis);
	priority_queue <Node> q;
	dis[s] = 0, q.push((Node){s, 0});
	while (!q.empty())
	{
		int u = q.top().pos;
		q.pop();
		if (vis[u]) continue;
		vis[u] = true;
		for (int i = head[u]; i; i = e[i].nxt)
		{
			int v = e[i].now;
			if (dis[u] + e[i].w < dis[v])
			{
				dis[v] = dis[u] + e[i].w;
				q.push((Node){v, dis[v]});
			}
		}
	}
}
void solve()
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	while (m--)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (w == 1) ADD(u, v, 1); //第一层
		else ADD(u + n, v + n, 1); //第二层
	}
	while (k--)
	{
		int u;
		scanf("%d", &u);
		ADD(u, u + n, 0); //切换层
	}
	dijkstra(1);
	//for (int i = 1; i <= (n << 1); i++) printf("from %d to %d is %d\n", 1, i, dis[i]);
	int t = min(dis[n], dis[n + n]);
	if (t == 0x3f3f3f3f) puts("-1");
	else cout << t << '\n';
}
```

希望能帮助到大家！

---

## 作者：Y2y7m (赞：3)

~~最近ABC喜欢考搜索了？？？~~

这种一看就是分层图，广搜基础题。

我们需要改变一下 $vis$ 数组，如果按照原本的定义：是否抵达过这个点是有问题的，例子：

![](https://cdn.luogu.com.cn/upload/image_hosting/60hwspde.png)

只有二号点有按钮，但是你有可能先走的三号点导致二号点按了按钮也走不到四号点导致出错。

我们给 $vis$ 数组多开一维，现在 $vis_{i,j}$ 代表到达第 $i$ 号点是边的状态为 $j$ 的状态是否有过。

正常广搜即可。

最多是道绿题吧。

代码：

```cpp
#include <bits/stdc++.h>

using namespace std;
const int maxn=2e5+10;
int n,m,k;
int s[maxn];
bool vis[maxn][2];
vector<int> edge[maxn],val[maxn];
struct node
{
	int u,step;
	bool stat;
};
void bfs()
{
	queue<node> q;
	q.push({1,0,0});
	vis[1][0]=1;
	if(s[1])
	{
		q.push({1,0,1});
		vis[1][1]=1;
	}
	while(!q.empty())
	{
		node t=q.front();
		int u=t.u,stat=t.stat;
		q.pop();
		for(int i=0;i<edge[u].size();i++)
		{
			int v=edge[u][i],w=val[u][i];
			int tmp=w^stat;
			if(tmp==0) continue;
			if(vis[v][stat]) continue;
			vis[v][stat]=1;
			if(v==n)
			{
				cout<<t.step+1<<endl;
				exit(0);
			}
			q.push({v,t.step+1,stat});
			if(s[v])
			{
				q.push({v,t.step+1,!stat});
			}
		}
	}
	cout<<-1<<endl;
	return ;
}
int main()
{
	cin>>n>>m>>k;
	int u,v,w;
	for(int i=1;i<=m;i++)
	{
		cin>>u>>v>>w;
		edge[u].push_back(v);
		edge[v].push_back(u);
		val[u].push_back(w);
		val[v].push_back(w);
	}
	int x;
	for(int i=1;i<=k;i++)
	{
		cin>>x;
		s[x]=1;
	}
	bfs();
	return 0;
}

```


---

## 作者：MoyunAllgorithm (赞：3)

赛后发现大家做的都是分层图建 $2N$ 个点，但我认为没有必要。

**题意**

给你 $N$ 点 $M$ 边等边权无向图。每个边有两种状态——激活和失活。不能走失活的边。但是在 $K$ 个点（与 $N$ 同阶）上有开关，你走到一个有开关的点后，可以选择让所有失活边激活，让激活边失活。问 $1$ 到 $N$ 的最短路长度。

**分析**

显然是 bfs 啊qwq

其实处理激活失活非常简单，在存边时顺便存一下就行了。但是。但如果你这么直接写的话会错误：

WA CODE:

```cpp
void bfs()
{
	queue<Point>q;
	q.push({1,0,1});
	while(q.size())
	{
		Point p=q.front();
		q.pop();
		int u=p.id,step=p.step,dir=p.opt;
      //dir:当前时刻本来是激活的边现在是否激活
		if(u==N)
		{
			printf("%d\n",step);
			exit(0);
		}
		if(vis[u]) continue;
		vis[u]=1;
		for(auto cur:gra[u])
		{
			int v=cur.first,a=cur.second;
			if(a!=dir) continue;
			if(vis[v]) continue;
			q.push({v,step+1,dir});
		}
		if(swi[u])//u节点有开关
		dir=1-dir;
		for(auto cur:gra[u])
		{
			int v=cur.first,a=cur.second;
			if(a!=dir) continue;
			if(vis[v]) continue;
			q.push({v,step+1,dir});
		}
	}
	puts("-1");
	exit(0);
}
```
为什么呢？我们看这个数据：

```c
4 4 1//N=3,M=3,K=1
3//3这个点有开关
1 2 1//点1和2有激活的边
2 3 1
3 1 0
1 4 0//点1和3有失活的边
```
我们期望的答案是 $4(1 \to 2 \to 3 \to 1 \to 4)$，我们的程序却没有跑到 $N$ 点。因为，我们的程序搜索到 $3$ 点，摁下开关后，本来应该回到 $1$ 点，但因为 $1$ 已被标记，搜索停止了。

因此，我们想到：**一个点应该有两种状态：$vis_{i,1/0}$** 表示在当前各边激活状态下（$1$ 表示原来的激活边现在激活，$0$ 表示原来的激活边现在失活），$i$ 点是否被访问。这样，bfs 能够正常运行。

**AC CODE:**

```cpp
#include <bits/stdc++.h>
#define PII pair<int,int>
using namespace std;
const int MAXN=2*1e5+5;
struct Point
{
	int id,step,opt;
};
int N,M,K;
bool swi[MAXN],vis[MAXN][2];
vector<PII>gra[MAXN];
void bfs()
{
	queue<Point>q;
	q.push({1,0,1});
	while(q.size())
	{
		Point p=q.front();
		q.pop();
		int u=p.id,step=p.step,dir=p.opt;
	//	printf("%d %d %d\n",u,step,dir);
		if(u==N)
		{
			printf("%d\n",step);
			exit(0);
		}
		if(vis[u][dir]) continue;
		vis[u][dir]=1;
		for(auto cur:gra[u])
		{
			int v=cur.first,a=cur.second;
			if(a!=dir) continue;
			if(vis[v][dir]) continue;
			q.push({v,step+1,dir});
		}
		if(swi[u])
		dir=1-dir;
		for(auto cur:gra[u])
		{
			int v=cur.first,a=cur.second;
			if(a!=dir) continue;
			if(vis[v][dir]) continue;
			q.push({v,step+1,dir});
		}
	}
	puts("-1");
	exit(0);
}
int main()
{
	scanf("%d %d %d",&N,&M,&K);
	for(int i=1;i<=M;i++)
	{
		int u,v,a;
		scanf("%d %d %d",&u,&v,&a);
		gra[u].push_back({v,a});
		gra[v].push_back({u,a});
	}
	memset(swi,0,sizeof(swi));
	for(int i=1;i<=K;i++)
	{
		int s;
		scanf("%d",&s);
		swi[s]=1;
	}
	bfs();
	return 0;
}
```



---

## 作者：hcywoi (赞：1)

## $\mathcal Solution$

### 【题意】

给定无向图，当 $a_i = 1$ 时，该条边才能走。在给我们 $k$ 个点，$S_1, S_2, \cdots, S_k$，到了这些点可以**选择**是否取反 $(1 \to 0, 0 \to 1)$ 所有的 $a_i$，求 $1 \to n$ 的最短距离。

### 【解法】

$dist_{i, 0}$ 表示到了 $i$ 这个点且 $a_i = 0$ 的边可以走的最短距离。

$dist_{i, 1}$ 表示到了 $i$ 这个点且 $a_i = 1$ 的边可以走的最短距离。

则 $dist_{i, 0} = \min\limits_{s \in g_i}\{dist_{s, 0}+1, [s \in S]dist_{s, 1} + 1\}$。

则 $dist_{i, 1} = \min\limits_{s \in g_i}\{dist_{s, 1}+1, [s \in S]dist_{s, 0} + 1\}$。

其中 $g_i$ 表示所有 $i$ 的临边，$S$ 表示可以取反的点。

$dist_{i, 0}, dist_{i, 1}$ 都可以用 bfs 求得。

答案 $= \min\{dist_{n, 0}, dist_{n, 1}\}$ 。

## $\mathcal Code$

```cpp
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
#include <sstream>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

#define x first
#define y second
#define IOS ios::sync_with_stdio(false)
#define cit cin.tie(0)
#define cot cout.tie(0)

using namespace std;

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

const int N = 200010, M = 400010, MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const LL LLINF = 0x3f3f3f3f3f3f3f3f;
const double eps = 1e-8;

int n, m, k;
PII q[N * 2];
int dist[N][2];
int h[2][N], e[M], ne[M], idx;
unordered_set<int> S;

void add(int h[], int a, int b)
{
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void bfs(int s)
{
	memset(dist, 0x3f, sizeof dist);

	int hh = 0, tt = -1;
	dist[s][1] = 0, q[ ++ tt] = {s, 1};
	if (S.count(1)) dist[s][0] = 0, q[ ++ tt] = {s, 0}; // 不要忘了判断 1 是否在集合中
	while (hh <= tt)
	{
		PII t = q[hh ++ ];
		int x = t.x, y = t.y;
		for (int i = h[y][x]; ~i; i = ne[i])
		{
			int j = e[i];
			if (dist[j][y] > dist[x][y] + 1) // 不懂的去看上边的思路
			{
				dist[j][y] = dist[x][y] + 1;
				q[ ++ tt] = {j, y};
			}
			if (S.count(j) && dist[j][y ^ 1] > dist[x][y] + 1)
			{
				dist[j][y ^ 1] = dist[x][y] + 1;
				q[ ++ tt] = {j, y ^ 1};
			}
		}
	}
}

void solve()
{
	memset(h, -1, sizeof h);
	
	cin >> n >> m >> k;
	while (m -- )
	{
		int a, b, c;
		cin >> a >> b >> c;
		add(h[c], a, b), add(h[c], b, a);
	}
	for (int i = 1; i <= k; i ++ )
	{
		int t;
		cin >> t;
		S.insert(t);
	}
	bfs(1);
	
	int res = min(dist[n][0], dist[n][1]); // 求答案
	if (res == INF) res = -1; // 判断无解
	cout << res << endl;
}

int main()
{
	IOS;
	cit, cot;
	int T = 1;
//	cin >> T;
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：Xeqwq (赞：1)

简析题目：  
给出一个图，$n$ 个顶点 $m$ 条双向边，给出其中的 $s$ 个可以切换图的状态的顶点。  
这个图有两种状态，所有边只在图处于其中某种状态的时候可以通行。  
求从 $1$ 号点到 $n$ 号点最少需要走多少条边。  

---

根据边的状态，我们可以把整个图上所有的边分为两类——开始的时候可以通行的边和开始的时候不可以通行的边。  
这种问题我们一般用分层图最短路解决。  
$$\text{分层图最短路}$$
前置知识：最短路算法。  
我在这里着重讲分层图，构建完分层图之后直接照常跑最短路即可。  
何为分层？分层，就是把整个图分成好几层，在每一层中都有一些顶点，同一个顶点可以出现在不同层中。  
一层往往表示相同的一个状态。  
这个题的一层，即可表示按按钮的次数。  
按照切换图的状态的次数的奇偶分层，在所有的奇数层上添加开始可以走的边，在所有的偶数层上添加开始的时候不可以走的边。每次切换状态，便可以从第 $t$ 层的顶点 $u$ 通往第 $t+1$ 层的顶点 $u$ ，这里 $t$ 指当前这次切换状态是第几次。  
但是我们也不知道要建多少层图，所以我们要简化。  
显然，这里我们可以从第 $1$ 层图走到第 $2$ 层图，然后再次切换状态的时候再从第 $2$ 层图走回第 $1$ 层图。  
最后再来讲讲如何存分层图:将初始节点（第一层）存为 $1$ 至 $n$ 号节点，第二层节点存为 $n+1$ 至 $2 \times n$ 号节点,第三层节点存为 $2 \times n+1$ 至 $3 \times n$ 号节点（本题只用两层），以此类推。  
本题计算完了第 $1$ 层至各层各节点的距离之后，即可取至第一层的 $n$ 号节点与第二层的 $n$ 号节点中的最小值作为答案。  
code:  
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
const int Maxn=200005;
int n,m,k;
int s;
vector<Edge> adj[Maxn*2];

int d[Maxn*2],vis[Maxn*2];
struct Edge
{
	int v,w;
	Edge(int v,int w):v(v),w(w){};
};
struct Node 
{
    int v;
    int dis;
    Node(int v,int dis):v(v),dis(dis){};
};
bool operator<(Node n1,Node n2)
{
    return n1.dis>n2.dis;
}
priority_queue<Node> q; 
void dijkstra()
{	
	memset(d,0x3f,sizeof(d));
    d[1+n]=0;
    q.push(Node(1+n,0));
    while(!q.empty())
    {
        int u=q.top().v;
        q.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(int j=0,us=adj[u].size();j<us;j++)
        {
            int v=adj[u][j].v;
            if(vis[v]) continue;
            if(d[u]+adj[u][j].w<d[v])
            {
                d[v]=d[u]+adj[u][j].w;
                q.push(Node(v,d[v]));
            }
        }
    }
}

int main()
{
	int u,v,a;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&a);
		if(a)
		{
			adj[u+n].push_back(Edge(v+n,1));
			adj[v+n].push_back(Edge(u+n,1));
		}
		else
		{
			adj[u].push_back(Edge(v,1));
			adj[v].push_back(Edge(u,1));
		}
	}
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&s);
		adj[s].push_back(Edge(s+n,0));
		adj[s+n].push_back(Edge(s,0));//连接两层的边的距离为0
	}
	dijkstra();
	if(d[n]==0x3f3f3f3f&&d[n*2]==0x3f3f3f3f) cout<<-1;
	else cout<<min(d[n],d[2*n]);
}
```  
练习题：   
[P4568 [JLOI2011] 飞行路线](https://www.luogu.com.cn/problem/P4568)  
[P5122 [USACO18DEC]Fine Dining G](https://www.luogu.com.cn/problem/P5122)  （有一篇我的题解 可供参考）  
$$End$$

---

## 作者：Avocadooo (赞：0)

考虑在移动中存在的两种不同的状态：

- 从出发至今按下了偶数次按钮，即 $ w_{now}=w_{origin} $

- 从出发至今按下了奇数次按钮，即 $ w_{now}=1-w_{origin} $

因为状态只有这两种，所以考虑构建分层图，第一层为原边权图，第二层为反边权图，而可以按下按钮的位置作为两层图的连接边（按下按钮即相当于状态的变化）。

起始状态：处在 $ 1 $ 号节点，按下了偶数次按钮（$ 0 $ 次），即原边权图。

终止状态：处在 $ n $ 号节点，不确定按下按钮的次数奇偶性，那么取最优的即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int ll
typedef long long ll;
const int N=1000005;
int n,m,k;
namespace Chain
{
	int h[N],cnt;
	struct Edge{int next,to,v;}e[N<<1];
	void AddEdge(int c,int d,int w){e[++cnt]=(Edge){h[c],d,w};h[c]=cnt;} 
}
using namespace Chain;
int d[N];
bitset<N> vst;
priority_queue< pair<int,int> > q;
void dij()
{
	for(int i=2;i<=(n<<1);i++) d[i]=LLONG_MAX; vst.reset();
	d[1]=0;
	q.push(make_pair(-d[1],1));
	while(!q.empty())
	{
		int r=q.top().second; q.pop();
		if(vst[r]) continue;
		vst.set(r);
		for(int i=h[r];i;i=e[i].next)
		{
			int y=e[i].to;
			if(vst[y]) continue;
			if(e[i].v==2 || e[i].v&&d[y]>d[r]+e[i].v)
			{
				d[y]=d[r]+abs(e[i].v-2);
				q.push(make_pair(-d[y],y));
			}
		}
	}
	int dis=min(d[n],d[n<<1]);
	if(dis!=LLONG_MAX) printf("%lld\n",dis);
	else puts("-1");
}
signed main()
{
	scanf("%lld %lld %lld",&n,&m,&k);
	for(int i=1,x,y,z;i<=m;i++)
	{
		scanf("%lld %lld %lld",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
		AddEdge(x+n,y+n,z^1);
		AddEdge(y+n,x+n,z^1);
	}
	for(int i=1,s;i<=k;i++) scanf("%lld",&s),AddEdge(s,s+n,2),AddEdge(s+n,s,2);
	dij();
}
```

---

## 作者：__vector__ (赞：0)

## 题外话  
此题我赛时没做出来，赛后被别人一句话搞懂。  
## 做法  
我们把题意略微转化一下：  

给定两种类型的边，类型分别为 $1$，$0$。  
你只能行走在你状态对应的边上。 
例如你的状态是 $1$，就只能走在类型为 $1$ 的边上。  
现在有一些节点作为开关。可以在那里切换状态。  
问从 $1$ 走到 $n$ 的最短路。  

看到有两种边，而且这两种边互不兼容。  
而且有开关可以在两种边上切换。  
现在瓶颈就在于如何选择是否切换状态。  
那么是不是可以将这个“选择”变成一条权值为 $0$ 的边，来进行切换。  
而现在有了代表是否选择切换的边，而原图上无法直接从一种边走到另一种边。  
可以考虑把两种边分别建图。  
而这个代表切换状态的边就是两个图之间的连边。  

也就是分层图这个东西。  

对种类为 $1$ 的边，所连节点编号为 $1$ 到 $n$。  
对于种类为 $0$ 的边，所连节点编号为 $n+1$ 到 $2n$。  
对于有开关的节点，设其为 $u$，则连接 $u$ 和 $u+n$。  

节点 $n+1$ 到 $2n$ 可以认为是编号为 $1$ 到 $n$ 节点的另一种状态，只不过由于状态不同，这些节点无法通过普通的边，只能通过代表状态切换的边与编号为 $1$ 到 $n$ 互通。  

建完图之后跑最短路就行了。  

## Code  
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int head[maxn*2];
struct EDGE
{
	int to,val,nxt;
}edge[maxn*4];
int cnt;
void add(int u,int to,int val)
{
	edge[++cnt].to=to;
	edge[cnt].val=val;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,m,k;
bool vis[maxn*2];
int dis[maxn*2];
void dijkstra()
{
	memset(dis,0x3f3f3f3f,sizeof dis);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> que;
	que.push(make_pair(0,1));
	dis[1]=0;
	while(!que.empty())
	{
		int u=que.top().second;
		que.pop();
		if(vis[u])continue;
		vis[u]=1;
//		printf("u: %d\n",u);
		for(int i=head[u];i;i=edge[i].nxt)
		{
			int to=edge[i].to;
			if(dis[to]>dis[u]+edge[i].val)
			{
				dis[to]=dis[u]+edge[i].val;
			//	printf("dis[%d]: %d dis[%d]: %d\n",u,dis[u],to,dis[to]);
				que.push(make_pair(dis[to],to));
			}
		}
	}
	int ans=min(dis[n],dis[n*2]);
	if(ans==0x3f3f3f3f)printf("-1");
	else printf("%d",ans);
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	int u,v,a;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&a);
		if(a)
		{
			add(u,v,1);
			add(v,u,1);
		}
		else
		{
			add(u+n,v+n,1);
			add(v+n,u+n,1);
		}
	}
	int si;
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&si);
		add(si,si+n,0);
		add(si+n,si,0);
	}
	dijkstra();
	return 0;
}
```


---

## 作者：Register_int (赞：0)

拆点，将每个点拆成开关的两种状态。断开的边连在 $(u+n,v+n)$ 上，连着的边连在 $(u,v)$ 上。有开关的点将拆出来的两点连接，边权为 $0$。之后跑最短路即可。这里用的是 $\text{0-1 bfs}$。
# AC 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 4e5 + 10;
const int inf = 0x3f3f3f3f;

struct edge {
	int v, w, nxt;
} e[MAXN << 1];

int head[MAXN], tot;

inline 
void add(int u, int v, int w) {
	e[++tot] = { v, w, head[u] }, head[u] = tot;
}

bool vis[MAXN];

int dis[MAXN];

deque<int> q;

inline 
void bfs(int s) {
	memset(dis, 0x3f, sizeof dis);
	q.push_back(s), dis[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop_front();
		if (vis[u]) continue; vis[u] = 1;
		for (int i = head[u], v; i; i = e[i].nxt) {
			v = e[i].v;
			if (dis[v] > dis[u] + e[i].w) {
				dis[v] = dis[u] + e[i].w;
				e[i].w ? q.push_back(v) : q.push_front(v);
			}
		}
	}
}

int n, m, k, ans;

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1, u, v, w; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &w);
		if (w) add(u, v, 1), add(v, u, 1);
		else add(u + n, v + n, 1), add(v + n, u + n, 1);
	}
	for (int i = 1, x; i <= k; i++) scanf("%d", &x), add(x, x + n, 0), add(x + n, x, 0);
	bfs(1);
	printf("%d", min(dis[n], dis[n << 1]) == inf ? -1 : min(dis[n], dis[n << 1]));
}
```

---

## 作者：what_else (赞：0)

### 题目概要

给定一个无向图，每条边有 $1$ 与 $0$ 两种形式。

若干个点有开关，到达一个有开关的点，可以按下该开关，使所有边的 $1$ 与 $0$ 取反。

每次只能走为 $1$ 的边，求 $1$ 到 $N$ 的最短路。

### Solution

考虑每次反转，图只有两种形式：要么原来是 $1$ 的可走，要么原来是 $0$ 的可走。

不妨把这个图拆成 $2$ 个维度，一个维度是只有形式为 $1$ 的边，一个是只有形式为 $0$ 的边。第一个维度即初始状态，第 $2$ 个即开关后的状态。可以用 $i+n$ 号结点表示第 $i$ 个结点的第二个维度。

这两个维度间有“虫洞”，即开关所在的结点会在两个维度之间同一结点的位置建一条边，注意，打开开关不耗步数，所以边权为 $0$，而其他边都有为 $1$ 的边权。

按照这个方法，跑一边从 $1$ 到 $N$ 的 $\text{Dijkstra}$ 即可。

```cpp
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
#define inf ((1<<31)-1)
int n,m,k,u,v,w,fo,s; 
long long dis[401000];
struct EDGE{
	int to;
	int w;
};
vector <EDGE> f[500100];
bool vis[401000];
int cmp[401000];
struct nod{
	int num,disn;
	friend bool operator < (nod a,nod b){
		return a.disn > b.disn;
	}
}pi;
priority_queue <nod> o;
int main(){
	scanf("%d %d %d",&n,&m,&k);
	for(int i=2;i<=n*2;i++)
	dis[i]=inf;
	dis[1]=0;
	for(int i=1;i<=m;i++){
		scanf("%d %d %d",&u,&v,&w);
		if(w==0){
			f[u+n].push_back( {v+n,1} );
			f[v+n].push_back( {u+n,1} );
		}
		if(w==1){
			f[u].push_back( {v,1} );
			f[v].push_back( {u,1} );
		}//重要的是建边
	} 
	int ret;
	for(int i=1;i<=k;i++){
		cin>>ret;
		f[ret].push_back( {ret+n,0} );
		f[ret+n].push_back( {ret,0} );
	}
	pi.disn=0;
	s=1;
	pi.num=s;
	o.push(pi);
	while(!o.empty()){
		fo=o.top().num;
		o.pop(); 
		if(vis[fo])continue; 
		if(fo==0)break;
		for(int i=0,sz=f[fo].size();i<sz;i++){
			if(dis[fo] + f[fo][i].w < dis[f[fo][i].to])
			dis[f[fo][i].to]=dis[fo] + f[fo][i].w,pi.disn=dis[f[fo][i].to],pi.num=f[fo][i].to,o.push(pi);
		}
		vis[fo]=1;
	}
	if(dis[n]==inf && dis[2*n]==inf) cout<<-1;
	else cout<<min(dis[n],dis[2*n]);
}

```

---

## 作者：EastIsRed (赞：0)

PS：本篇为本蒟蒻第一篇题解，如有差错请见谅。

## 题意简述
- 给定一张有 $N$ 个点，$M$ 条边的无向图。
- 对于第 $i$ 条边，给定一个值 $a_i$。当 $a_i = 0$ 时，第 $i$ 条边在开始时不可通过。反之，当 $a_i = 1$ 时，第 $i$ 条边在开始时可以通过。
- $N$ 个点中的 $K$ 个上装有开关，走到这 $K$ 个点上时可以通过扳动开关使所有边的可通过性发生改变，即原来可以通过的边现在不可通过，反之亦然。
- 问能否从第 $1$ 号点走到 第 $N$ 号点。如果不能，输出 $-1$ ，否则输出从第 $1$ 号点到第 $N$ 号点最少走过的边数。
- $N$,$M$ $\leq$ $2 \times 10^5$，$0 \leq K \leq N$，数据保证不存在自环。

## 题目分析
首先，直接暴力是肯定不行的。

然后，我们需要想到图论中的一个很重要的小技巧：拆点。

我们可以把原图中的每一个点都拆成两个点，原图中第 $i$ 号点拆出来的点的编号分别为 $i$ 和 $i+n$ 。对于给出的第 $i$ 条边，其连接了第 $u_i$ 号点和第 $v_i$ 号点，若 $a_i =0$，则我们在建图时应当在第 $u_i+N$ 号点与第 $v_i+N$ 号点之间连一条边权为 $1$ 的双向边；同理， 若 $a_i =1$，则应当在第 $u_i$ 号点与第 $v_i$ 号点之间连一条边权为 $1$ 的双向边。此外，若给出的第 $s_i$ 号点上有开关，则建图时应当在第 $s_i$ 号点和第 $s_i+N$ 号点之间连一条边权为 $0$ 的双向边。

那么现在问题就很好处理了：我们只需要求出从 $1$ 号点到 $N$ 号点与从 $1$ 号点到 $2N$ 号点的最短距离，再从两者中取较小值即可。于是这题就成了一道简单的最短路板子。

（不会单源最短路的同学，请移步 [P4779 【模板】单源最短路径（标准版）](https://www.luogu.com.cn/problem/P4779) ）

## 代码实现

```cpp
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int MAXN=200000;
int n,m,k;
int tot,head[MAXN*2+86],to[MAXN*4+86],nxt[MAXN*4+86],val[MAXN*4+86];
//邻接表存边，注意点数要乘2，边数要乘4
int dis[400086];
void add_edge(int a,int b,int c)
{
    to[++tot]=b;
    val[tot]=c;
    nxt[tot]=head[a];
    head[a]=tot;
}
struct node{
    int no,dis;
    node(){}
    node(int _no,int _dis):no(_no),dis(_dis){}
    bool operator < (const node& oth)const
    {
        return dis>oth.dis;
    }
};
priority_queue<node>q;
bool mark[400086];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if(!c)//开始时不能通过，边建在a+n和b+n之间
        {
            add_edge(a+n,b+n,1);
            add_edge(b+n,a+n,1);
        }
        else//开始时能通过，边建在a和b之间
        {
            add_edge(a,b,1);
            add_edge(b,a,1);
        }
    }
    while(k--)
    {
        int s;
        scanf("%d",&s);
        add_edge(s,s+n,0);
        add_edge(s+n,s,0);
        //对于开关，连接s与s+n
    }
    memset(dis,0x3f,sizeof(dis));//千万记得给dis数组赋初值
    dis[1]=0;
    q.push(node(1,0));
    while(!q.empty())//Dijkstra堆优化跑最短路
    {
        node now=q.top();
        q.pop();
        if(mark[now.no])
            continue;
        mark[now.no]=true;
        for(int i=head[now.no];i;i=nxt[i])
            if(!mark[to[i]]&&dis[to[i]]>dis[now.no]+val[i])
            {
                dis[to[i]]=dis[now.no]+val[i];
                q.push(node(to[i],dis[to[i]]));
            }
    }
    if(dis[n]==0x3f3f3f3f&&dis[n<<1]==0x3f3f3f3f)
        printf("-1");
    else if(dis[n]<dis[n<<1])
        printf("%d",dis[n]);
    else printf("%d",dis[n<<1]);
    return 0;
}
```

---

## 作者：tuxuanming2024 (赞：0)

## 题意

给定一个 $n$ 个点 $m$ 条边的无向图，每个边有个权值 $a \in \{0,1\}$，如果为 $1$ 表示可通行，否则为不可通行。$k$ 个点上有按钮，到达这些点时可以选择按按钮，那么所有边的 $a$ 值取反。求 $1$ 到 $n$ 的最短路（按按钮代价为 $0$）

## 题解

考虑分层图。

根据边的 $a$ 值分为两层，第一层为 $a=1$ 的边，第二层为 $a=0$ 的边，边权为 $1$。如果点 $x$ 有按钮，那么就将 $x$ 在第一层中的点和第二层中的点连一条边权为 $0$ 的边。最后跑第一层的 $1$ 到 第一层的 $n$ 和第二层的 $n$ 的最短路取较小值即可。

## 代码

```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
#include "txm/debug.h"
#endif
using namespace std;
using ll=long long;
const int N=500005,INF=0x3f3f3f3f;
struct heap
{
	int d,num;
	bool operator < (const heap &x)const {return d>x.d;}
};
int n,m,k,d[N];
bool v[N];
vector<pair<int,int>>e[N];
void dij()
{
	priority_queue<heap>q;
	memset(d,0x3f,sizeof(d));
	d[1]=0,q.push((heap){d[1],1});
	while(!q.empty())
	{
		int x=q.top().num; q.pop();
		if(v[x]) continue;
		v[x]=1;
//		debug(x,d[x]);
		for(auto it:e[x])
		{
			int y=it.first;
			if(!v[y]&&d[x]+it.second<d[y])
			{
				d[y]=d[x]+it.second;
				q.push((heap){d[y],y});
			}
		}
	}
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>k;
	for(int i=1,x,y,z;i<=m;i++)
	{
		cin>>x>>y>>z;
		if(z==1)
		{
			e[x].push_back({y,1});
			e[y].push_back({x,1});
		}
		else
		{
			e[x+n].push_back({y+n,1});
			e[y+n].push_back({x+n,1});
		}
	}
	for(int i=1,x;i<=k;i++)
	{
		cin>>x;
		e[x].push_back({x+n,0});
		e[x+n].push_back({x,0});
	}
	dij();
	int ans=min(d[n],d[2*n]);
	cout<<(ans==INF?-1:ans);
	return 0;
}

```


---

## 作者：Resolute_Faith (赞：0)

这是一个分层图

在最短路的基础上，我们定义 $dis_{i,0/1}$ 表示走到 $i$ 时只能走 $0/1$ 的边的最短路。 

可能会有三种情况：

1. 走到 $x$ 点，发现到 $y$ 的这条边上，我虽然不能走，但是我可以按下按钮继续走。
2. 走到 $x$ 点，发现到 $y$ 的这条边上，我可以继续走。
3. 在 $x$ 点按下按钮，也就是从 $dis_{x,0/1}$ 走到 $dis_{x,1/0}$。

我讨论的可能会比较复杂，时间复杂度 $\mathcal{O}(n\log n)$。用 01bfs 应该会更快。

核心代码：

```cpp
while(!q.empty()){
    int x=q.front().fir,p=q.front().sec;
    q.pop();
    vis[x][p]=false;
    for(register int i=head[x];i;i=a[i].nxt){
        int y=a[i].to;
        if(dis[y][p]>dis[x][p]+1&&a[i].l==p){
            dis[y][p]=dis[x][p]+1;
            if(!vis[y][p]){
                vis[y][p]=true;
                q.push(make_pair(y,p));
            }
        }
        if(dis[y][1-p]>dis[x][p]+1&&a[i].l==!p&&f[x]==true){
            dis[y][1-p]=dis[x][p]+1;
            if(!vis[y][1-p]){
                vis[y][1-p]=true;
                q.push(make_pair(y,1-p));
            }
        }
        if(dis[x][1-p]>dis[x][p]+1&&f[x]==true){
            dis[x][1-p]=dis[x][p]+1;
            if(f[x]==true){
                if(!vis[x][1-p]){
                    vis[x][1-p]=true;
                    q.push(make_pair(x,1-p));
                }
            }
        }
    }
}
```

---

