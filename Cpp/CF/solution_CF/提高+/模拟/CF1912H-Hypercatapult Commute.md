# Hypercatapult Commute

## 题目描述

A revolutionary new transport system is currently operating in Byteland. This system requires neither roads nor sophisticated mechanisms, only giant catapults.

The system works as follows. There are $ n $ cities in Byteland. In every city there is a catapult, right in the city center. People who want to travel are put in a special capsule, and a catapult throws this capsule to the center of some other city. Every catapult is powerful enough to throw the capsule to any other city, with any number of passengers inside the capsule. The only problem is that it takes a long time to charge the catapult, so it is only possible to use it once a day.

The passenger may need to use the catapults multiple times. For example, if the passenger wants to travel from city A to city B, they can first use one catapult to move from A to C, and then transfer to another catapult to move from C to B.

Today there are $ m $ passengers. Passenger $ i $ wants to travel from city $ a_i $ to city $ b_i $ . Your task is to find the way to deliver all the passengers to their destinations in a single day, using the minimal possible number of catapults, or say that it is impossible.

## 样例 #1

### 输入

```
5 6
1 3
1 2
2 3
4 2
1 5
5 1```

### 输出

```
5
5 1
1 2
4 2
2 3
3 5```

## 样例 #2

### 输入

```
3 6
1 2
1 3
2 1
2 3
3 1
3 2```

### 输出

```
-1```

# 题解

## 作者：xyz105 (赞：2)

$$\begin{Bmatrix}\color{red}\LARGE\bold{Solution}\\\normalsize\texttt{No.012 }\bold{CF1912H}\end{Bmatrix}\times\footnotesize\texttt{ By Xyz105}$$


在某模拟赛中看到这道题，没能场切，寄。

### 题目描述

Byteland 中有 $n$ 座城市。每座城市都有一个弹射胶囊，可通过它将任意数量的乘客弹射到另一座城市，但所有弹射胶囊都只能使用一次。

现有 $m$ 名乘客，第 $i$ 名乘客想要从城市 $a_i$ 到城市 $b_i$ 旅行。当然，有的乘客为了达到目的可能需要使用不止一次弹射胶囊。例如，如果乘客想要从城市 $A$ 到城市 $B$，他们可以先使用一个弹射胶囊从 $A$ 到 $C$，然后转乘另一个弹射胶囊从 $C$ 到 $B$。

试构造出一种弹射方案，使得按顺序执行该方案可以将所有乘客都送到目的地。要求：使用尽可能少的弹射胶囊，并输出每个弹射胶囊的起点和终点；若不可能构造出合法方案，则输出 $-1$。


### 解题思路

首先把相应的图建出来，它应包含所有 $a_i\to b_i$ 的有向边。

- 从简单的情况开始考虑。如果这张图是**有向无环图**，则考虑对它做一遍**拓扑排序**，得到排序后的点的序列 $(u_1,u_2,\ldots,u_n)$。然后让 $u_1$ 的弹射胶囊弹到 $u_2$ 处，$u_2$ 的弹射胶囊弹到 $u_3$ 处，以此类推。  
  
  不难发现这种链式方案必然满足每一名乘客的需求；所需操作数为 $n-1$。

- 比较麻烦的是**有环**的情况（存在强连通性）。考虑一种有些暴力的思路——**枚举**第一次弹射用的是哪一座城市的弹射胶囊，然后跑一遍上述有向无环图的解法，观察是否可行。
  
  具体地，假设第一次弹射用的是城市 $u_0$ 的弹射胶囊，暂时忽略掉所有以 $u_0$ 为出发点的乘客的需求（某种形式的删边）。对剩下的图尝试拓扑排序，若无解那就可能是 $u_0$ 选错了；否则对于得到的排序后的点序列 $(u_1,u_2,\ldots,u_n)$，构造方案：**$\bold{u_0}$ 弹向 $\bold{u_1}$**、$u_1$ 弹向 $u_2$、$u_2$ 弹向 $u_3$ 等等。
  
  不难发现，将 $u_0$ 弹向 $u_1$ 的操作放在最前面，有利于在之后的链式操作中满足所有以 $u_0$ 为出发点的乘客的需求，因为这样实际上是使从 $u_0$ 出发的乘客能够去往其它任何一个城市。此时所需操作数为 $n$。

- 如果整张图不连通，那么对于所有的连通块（此处指弱联通）都单独做一遍上述操作即可。


### 参考代码

[Submission on Codeforces](https://codeforces.com/contest/1912/submission/284141457)。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
#include <vector>
using namespace std;

const int MAXN = 1010, MAXM = 1e5 + 10;

int n, m;

int head[MAXN], from[MAXM], to[MAXM], nxt[MAXM], cnt = 0;

int ans[MAXM][2], ans_cnt = 0;

inline void add_ans(int u, int v)
	{ans[++ans_cnt][0] = u, ans[ans_cnt][1] = v;}

int in_deg[MAXN];

inline void add_edge(int u, int v)
	{in_deg[v]++, to[++cnt] = v, from[cnt] = u, nxt[cnt] = head[u], head[u] = cnt;}

int ffa[MAXN]; vector<int> com[MAXN]; // com = component

inline int find(int x)
	{return x == ffa[x] ? x : ffa[x] = find(ffa[x]);}

int tmp[MAXN]; deque<int> qu;

inline bool topo_sort(vector<int> &nodes, vector<int> &res, int lst = 0)
{
	res.clear(), qu.clear();
	for (auto i : nodes) tmp[i] = in_deg[i];
	for (auto i : nodes) if (!tmp[i]) qu.push_back(i);
	while (qu.size())
	{
		int u = qu.front(); qu.pop_front(), res.push_back(u);
		for (int i = head[u]; i; i = nxt[i])
		{
			if (--tmp[to[i]] == 0 && to[i] != lst) qu.push_back(to[i]);
		}
	}
	if (!lst) return 1;
	if (tmp[lst] == 0) res.push_back(lst);
	return (tmp[lst] == 0);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, i1, i2; i <= m; i++)
		scanf("%d%d", &i1, &i2), add_edge(i1, i2);
	
	for (int i = 1; i <= n; i++) ffa[i] = i;
	for (int i = 1; i <= m; i++) ffa[find(from[i])] = find(to[i]);
	for (int i = 1; i <= n; i++) com[find(i)].push_back(i);
	
	for (int i = 1; i <= n; i++)
	{
		if (!com[i].size()) continue;
		vector<int> res; topo_sort(com[i], res);
		if (res.size() == com[i].size())
		{
			for (int j = 0; j < res.size() - 1; j++) add_ans(res[j], res[j + 1]);
			continue;
		}
		
		bool flag = 0;
		for (auto j : com[i])
		{
			for (int k = head[j]; k; k = nxt[k]) in_deg[to[k]]--;
			if (!topo_sort(com[i], res, j)) goto label;
			if (res.size() < com[i].size()) goto label;
			flag = 1, add_ans(j, res[0]);
			for (int k = 0; k < res.size() - 1; k++) add_ans(res[k], res[k + 1]);
			label:;
			for (int k = head[j]; k; k = nxt[k]) in_deg[to[k]]++;
			if (flag) break;
		}
		if (!flag) return cout << -1, 0;
	}
	printf("%d\n", ans_cnt);
	for (int i = 1; i <= ans_cnt; i++) printf("%d %d\n", ans[i][0], ans[i][1]);
	
	return 0;
}
```

---

## 作者：tyr_04 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1912H)

### 题意

给你 $n$ 个点和 $m$ 个要求。$m$ 个要求表示有一个在点 $a$ 的人想通过一条或者多条图上的边通向目标点 $b$。每个点最多一条通往其它节点，且每条边最多使用一次。边可以通过任意数量的人。问是否有方案使得满足要求，如果有，输出最小边数及方案。

### 思路

将每个条件的 $a$ 点和 $b$ 点连双向边，每个连通块进行的移动操作是不相互影响的（因为连通块 $x$ 的人不需要去往连通块 $y$，连通块 $y$ 的人也不需要去往连通块 $x$），那么我们将移动操作的范围从原图转化为了若干个连通块。

将每个条件的 $a,b$ 从 $a$ 连一条单向边到 $b$，表示 
$a$ 需要通过一些边到达 $b$，如果当前图中没有环（即 DAG），每个 $a$ 都要去往 $b$，显然拓扑排序后前一个点跟后一个点连边就必然可行。

我们将连通里块的每个点都依次作**起始点**，做一个特殊的拓扑排序，大致框架与拓扑排序相同，唯一的区别是**队列里的第一个点为起始点**，并且后来的点要**通向起始点时都不管**。

如果根据拓扑排序的顺序前一个点跟后一个点连边，那么**除了通向起始点**的要求全都满足了（因为拓扑排序，当前点要去往的点的拓扑序一定大于当前点），如果中间有任何点要去往起始点，那么将队尾的点往起始点连边（此时边数要加一），若拓扑排序结束后每个点都进入过队列（也就是当前连通块内所有点的要求都满足了），便找到了一种可行的方案。

如果有多个点做起始点时都能满足要求，则采用消耗边数最小的方案加入最终答案。如果一个连通块内任何点做起始点都不可行则一定无解，因为一个环确定起点后，后面的点最多只能回到起始点，不能再从起始点继续走到环上的其它点了，而每个连通块必须确定一个起始点，故无解。

上一段证明了正确性和无解的情况，接下来证明为什么这样做是最小的。

由于每个点最多连一条边，要使连边满足条件至少要块长 $-1$ 条边（因为要保证图无向时连通），因此连完边后一个连通块解的图要么是链，要么是基环树。

链第二段证过了，不再多说；基环树可以将除基环外的枝条塞进大环里，消耗的边数是相等的。（断开环上当前结点与前一个节点连的边，由于枝条每个点出度最多为一，所以枝条都是链，将环上前一个结点连向链的开头依然成立）

时间复杂度 $O(n^2+m)$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,cnt,bh=0,p=0,head,now,pd,top[1005],d[1005],rd[1005],nrd[1005];
vector<int> v[1005],nv[1005],lt[1005];
bool z[1005][1005],vis[1005];
struct node
{
	int x,y;
}zans[1005],nb[1005],jl[1005];
void dfs(int x)
{
	vis[x]=1;
	cnt++;
	lt[bh].push_back(x);
	for(int i=0;i<nv[x].size();i++)
	{
		int y=nv[x][i];
		if(vis[y]==0)
		{
			dfs(y);
		}
	}
	return;
}
int top_sort(int qs,int bh)
{
	head=1;
	now=1;
	pd=0;
	top[head]=qs;
	cnt=lt[bh].size();
	for(int i=0;i<cnt;i++)
	{
		int x=lt[bh][i];
		rd[x]=nrd[x];
		if(rd[x]==0&&x!=qs)
		{
			head++;
			top[head]=x;
		}
	}
	while(now<=head)
	{
		int x=top[now];
		for(int i=0;i<v[x].size();i++)
		{
			int y=v[x][i];
			if(y==qs)
			{
				pd=1;
				continue;
			}
			rd[y]--;
			if(rd[y]==0)
			{
				head++;
				top[head]=y;
			}
		}
		now++;
	}
	if(head==cnt)
	{
		int o=0;
		for(int i=1;i<=head;i++)
		{
			if(i!=head)
			{
				o++;
				nb[o].x=top[i];
				nb[o].y=top[i+1];
			}
		}
		if(pd==1)
		{
			o++;
			nb[o].x=top[head];
			nb[o].y=qs;
		}
		return o;
	}
	return -1;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y;
		cin>>x>>y;
		if(z[x][y]==1)
		{
			continue;
		}
		else
		{
			z[x][y]=1;
			v[x].push_back(y);
			nrd[y]++;
			nv[x].push_back(y);
			nv[y].push_back(x);
		}
	}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]==0)
		{
			bh++;
			dfs(i);
		}
	}
	for(int i=1;i<=bh;i++)
	{
		int last=INT_MAX;
		for(int j=0;j<lt[i].size();j++)
		{
			int cd=top_sort(lt[i][j],i);
			if(cd==-1)
			{
				continue;
			}
			if(cd<last)
			{
				last=cd;
				for(int u=1;u<=cd;u++)
				{
					jl[u].x=nb[u].x;
					jl[u].y=nb[u].y;
				}
			}
		}
		if(last==INT_MAX)
		{
			cout<<-1;
			return 0;
		}
		for(int u=1;u<=last;u++)
		{
			p++;
			zans[p].x=jl[u].x;
			zans[p].y=jl[u].y;
		}
	}
	cout<<p<<'\n';
	for(int i=1;i<=p;i++)
	{
		cout<<zans[i].x<<' '<<zans[i].y<<'\n';
	}
	return 0;
}
```

---

