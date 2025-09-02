# 「EVOI-RD1」飞鸟和蝉

## 题目背景

你骄傲地飞远，我栖息的叶片。  
听不见的宣言，重复过很多年。  
沧海月的想念羽化我昨天，  
在我成熟的笑脸，  
你却未看过一眼。

## 题目描述

蝉 Charlie 要去寻找他的好朋友飞鸟了。 

具体来说，Charlie 和他的好朋友生活的地方可以看作一个 $n \times m$ 的网格，左上角为 $(1,1)$，右下角为 $(n,m)$。每个格子 $(i,j)$ 有一个海拔高度 $h_{i,j}$。Charlie 的目标是从他的家 $(x_0,y_0)$ 出发，不重不漏地经过网格中的每个格子**恰好一次**，**最终回到自己的家** $(x_0,y_0)$。Charlie 有两种移动方式：

1. 跳跃。用这种方式，Charlie 可以到达上下左右 $4$ 个相邻格子中**海拔严格低于当前格子**的一个格子。注意跳跃不消耗体力。  
2. 飞行。用这种方式，Charlie 可以从当前格子 $(x,y)$ 到达网格中**任意一个**格子 $(x',y')$，并消耗 $h_{x',y'}-h_{x,y}$ 个单位的体力。**注意飞行所消耗的体力值可以是负数**。  

Charlie 希望用尽量少的飞行次数完成目标，**在此前提下**再令消耗的体力最少。由于网格实在太大了，Charlie 希望你能帮助他。

## 说明/提示

**本题采用捆绑测试**

样例 1 解释：从 $(1,1)$ 飞到 $(2,2)$，再绕一圈即可。

样例 2 解释：一种最佳方案为：$(2,3)-(1,3)-(1,2)-(1,1)=(2,1)-(3,1)=(2,2)=(3,2)=(3,3)=(2,3)$，其中 $=$ 代表飞行。  

- Subtask 1 (10 pts)：满足 $1 \leq n,m \leq 3$。
- Subtask 2 (20 pts)：满足 $1 \leq n,m \leq 5$。
- Subtask 3 (20 pts)：保证至多有两种不同的海拔高度。 
- Subtask 4 (50 pts)：无特殊限制。

对于 $100\%$ 的数据：
- $1 \leq n,m \leq 50$。

- $1 \leq x_0 \leq n,1 \leq y_0 \leq m,1 \leq h_{i,j} \leq 10^9$。  

出题人：[冷月葬T魂](https://www.luogu.com.cn/user/340903)

## 样例 #1

### 输入

```
3 3 1 1
1 2 3
8 9 4
7 6 5```

### 输出

```
1 8```

## 样例 #2

### 输入

```
3 3 2 3
1 2 3
2 2 4
1 2 2```

### 输出

```
5 4```

## 样例 #3

### 输入

```
4 4 2 3
5 9 6 2
4 2 3 6
7 2 5 2
4 2 3 9```

### 输出

```
7 25```

## 样例 #4

### 输入

```
10 10 3 3
9 13 7 7 3 8 6 5 12 8
1 4 10 11 9 10 13 6 2 18
3 3 19 6 14 2 19 10 2 16
3 1 11 14 14 18 8 8 16 14
13 5 7 4 11 17 3 16 10 20
10 16 12 19 14 12 11 20 15 10
10 15 5 1 16 2 7 5 14 5
3 19 12 19 8 13 17 7 10 13
2 10 17 6 8 11 8 7 1 4
3 7 8 1 3 5 4 11 9 17```

### 输出

```
36 254```

# 题解

## 作者：冷月葬T魂 (赞：15)

考虑建模。从每个格子向周围海拔较低的格子连一条有向边，则网格就变成了一个有向无环图。类似于有向路径剖分，再建一个二分图，将每个点 $u$ 拆成 $u$ 和 $u'$ 两个点，对于每条有向边 $(u,v)$，在二分图中连接 $u$ 和 $v'$，于是跳跃的一条路径 $(a_1,a_2,\dots,a_k)$ 就成为了一系列匹配边 $(a_1,a_2'),(a_2,a_3'),\dots,(a_{n-1},a_n')$。  
再回到我们的目标，“飞行次数最少”就是非匹配点数最少，即匹配边数最多，这不就是最大匹配吗！再考虑费用（即体力值）。设一共有 $m$ 条路径，第 $i$ 条路径的起点、终点的海拔分别为 $s_i,t_i$。则消耗的总体力值为（记 $s_{m+1}=s_1$）：

$$ 
\begin{aligned}
 & \sum_{i=1}^m(s_{i+1}-t_i) \\
 = & \sum_{i=1}^ms_{i+1}-\sum_{i=1}^mt_i \\
 = & \sum_{i=1}^ms_{i}-\sum_{i=1}^mt_i \\
 = & \sum_{i=1}^m(s_i-t_i) \\
\end{aligned}
$$  

这是什么？这就是“每条路径的起点与终点海拔之差”的和！  
这又是什么？这就是每条路径上走过的“每条边的海拔之差”之和！——即 $a_1-a_n=(a_1-a_2)+(a_2-a_3)+\dots+(a_{n-1}-a_n)$  
现在思路很清楚了，二分图中每条边设容量为1，费用为“这条边起点与终点海拔之差”，再设一个源一个汇，求最小费用最大流即可。  
附上代码：

```cpp
#include <bits/stdc++.h>
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rev(i,a,b) for(int i=a;i>=b;i--)
#define clr(a,val) memset(a,val,sizeof(a))
#define int long long
using namespace std;

namespace cpdd{
	const int N=2e5+5;

	int n,m,S,T,head[N],nxt[N],to[N],cp[N],cv[N],tot;
	int ans,maxflow;
	
	void add(int x,int y,int z,int w)
	{
		nxt[++tot]=head[x];
		head[x]=tot;
		to[tot]=y;
		cp[tot]=z;
		cv[tot]=w;
		
		nxt[++tot]=head[y];
		head[y]=tot;
		to[tot]=x;
		cp[tot]=0;
		cv[tot]=-w;
	}
	
	int q[N],h,t,dis[N],inq[N],incf[N],prev[N];
	
	bool spfa()
	{
		clr(dis,0x3f);
		
		h=t=0;
		q[t++]=S;
		dis[S]=0;
		inq[S]=1;
		incf[S]=1e9;
		
		while(h<t){
			int u=q[h++];
			inq[u]=0;
			
			for(int e=head[u];e;e=nxt[e]){
				if(!cp[e]) continue;
				
				int v=to[e];
				if(dis[v]>dis[u]+cv[e]){
					dis[v]=dis[u]+cv[e];
					incf[v]=min(incf[u],cp[e]);
					prev[v]=e;
					if(!inq[v]){
						inq[v]=1;
						q[t++]=v;
					}
				}
			}
		}
		
		return dis[T]<dis[0];
	}
	
	void update()
	{
		int p=T,f=incf[T];
		
		while(p!=S){
			int e=prev[p];
			cp[e]-=f;
			cp[e^1]+=f;
			p=to[e^1];
		}
		
		maxflow+=f;
		ans+=f*dis[T];
	}
	
	void solve(int& _maxflow,int& _ans)
	{
		while(spfa()) update();
		
		_maxflow=maxflow;
		_ans=ans;
	}
}

/*
	cin>>n>>m>>S>>T;
	
	tot=1;
	For(i,1,m){
		int x,y,z,w;
		cin>>x>>y>>z>>w;
		add(x,y,z,w);
	}
*/

const int N=205;
const int dx[]={0,1,0,-1},dy[]={1,0,-1,0};

int n,m,h[N][N],pos[N][N];
int x_0,y_0;

signed main()
{
	cin>>n>>m>>x_0>>y_0;
	
	For(i,1,n) For(j,1,m) cin>>h[i][j];
	
	int pc=0;
	For(i,1,n) For(j,1,m) pos[i][j]=++pc;
	
	int S=2*n*m+1,T=2*n*m+2;
	
	cpdd::n=2*n*m+2;
	cpdd::S=S;
	cpdd::T=T;
	cpdd::tot=1;
	
	For(x,1,n){
		For(y,1,m){
			For(i,0,3){
				int tx=x+dx[i],ty=y+dy[i];
				if(tx>=1 && tx<=n && ty>=1 && ty<=m && h[tx][ty]<h[x][y]){
					cpdd::add(pos[x][y],pos[tx][ty]+n*m,1,h[x][y]-h[tx][ty]);
				}
			}
		}
	}
	
	For(x,1,n){
		For(y,1,m){
			cpdd::add(S,pos[x][y],1,0);
			cpdd::add(pos[x][y]+n*m,T,1,0);
		}
	}
	
	int fly,eng;
	
	cpdd::solve(fly,eng);
	
	cout<<n*m-fly<<' '<<eng<<endl;
	
	return 0;
}
```
完结撒花~

---

## 作者：strcmp (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P7863)

题目大意：给定一张 $n \times m$ 的网格图，并且给定一个初始点 $(x_0,y_0)$，要求从初始点出发，不重不漏的经过所有结点且满足飞行次数最小，**在此前提下**满足所花费用最小，求最优方案。

首先，很显然的一点，初始点 $(x_0,y_0)$ 没有任何用处，因为总路径一定是一条回路，在这个回路上的每个点最优方案显然都是一样的，所以初始点不影响最终答案。

因为要最小化飞行次数，所以考虑从每个点向周围高度较低的结点连边，我们发现这张图显然是一个 DAG。如果将整个路线用飞行隔开的话，**我们能发现最小化飞行次数可以规约为一个 DAG 最小路径覆盖问题。**

第一问立马就得出来了，拆点跑网络流，然后用 $n \times m$ 减去总流量即可。

不知道 DAG 最小路径覆盖的可以去看[这道题](https://www.luogu.com.cn/problem/P2764)的题解。

接下来处理第二问，需要一个简单的数学推理。

假设有 $k$ 条路径，设 $s_i$ 为第 $i$ 个路径的起点高度，$t_i$ 为第 $i$ 个路径的终点高度。特别的，由于总路径是一个回路，所以 $s_{k+1}=s_1$。

则每条路径对费用的贡献为：

$$
\begin{aligned}
&\sum^{k}_{i=1}(s_{i+1}-t_i)\\
&=\sum^{k}_{i=1}s_{i+1}-\sum^{k}_{i=1}t_i
\end{aligned}
$$

由于 $s_{k+1}=s_1$，所以 $\sum^{k}_{i=1}s_{i+1}=\sum^{k}_{i=1}s_i$。

原式等于

$$
\begin{aligned}

&\sum^{k}_{i=1}s_i-\sum^{k}_{i=1}t_i \\
&= \sum^{k}_{i=1}{s_i-t_i}

\end{aligned}
$$

显然每条路径经过的结点高度单调递减，所以对每条路径高度 $s_i \leadsto t_i = \{u_1,\,u_2,\,u_3 \dots,\,u_k\},\;s_i = u_1,\,\;t_i=u_k$ 的相邻两项之差求和。

$$
\sum^{k-1}_{i=1}u_{i}-u_{i+1}
$$

裂项相消一下。

$$
\begin{aligned}
&\sum^{k-1}_{i=1}u_{i}-u_{i+1}\\
&=(u_1-u_2)+(u_2-u_3)+(u_3-u_4) \dots + (u_{k-1}-u_k)\\
&=u_1-u_k\\
&=s_i-t_i
\end{aligned}
$$

所以对每个结点，其入点向周围高度较低的出点连容量为 $1$，费用为高度之差的边，然后跑 DAG 最小路径覆盖，费用即为答案。

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define inf 1000000000000000
#define V 100100
#define E 500100
typedef long long int ll;
struct edge {
	int to, next;
	ll capa, cost;
};
int cnt = 0, head[V], n, m; edge node[E];
inline void add(int fir, int nxt, ll w, ll c) {
	node[cnt].to = nxt,
		node[cnt].capa = w,
		node[cnt].cost = c,
		node[cnt].next = head[fir],
		head[fir] = cnt++;
}
int s, t, cur[V]; deque<int>que; ll dep[V], sum = 0, cost = 0;
bool vis[V];
inline bool spfa() {
	for (register int i = 1; i <= t; ++i)dep[i] = inf;
	dep[s] = 0; que.push_back(s); int u, v;
	while (!que.empty()) {
		v = que.front(); que.pop_front();
		for (register int i = head[v]; i != -1; i = node[i].next) {
			u = node[i].to;
			if (dep[v] + node[i].cost < dep[u] && node[i].capa) {
				dep[u] = dep[v] + node[i].cost;
				if (!que.empty() && dep[u] < dep[que.front()])que.push_front(u);
				else que.push_back(u);
			}
		}
	}
	return (dep[t] != inf);
}
ll dfs(register int v, register ll flow) {
	if (flow == 0 || v == t)return flow; ll used = 0, wei = 0;
	vis[v] = true;
	for (register int i = cur[v]; i != -1; i = node[i].next) {
		cur[v] = i;
		if (!vis[node[i].to] && dep[node[i].to] == dep[v] + node[i].cost && node[i].capa) {
			wei = dfs(node[i].to, min(flow - used, node[i].capa));
			if (wei) {
				node[i].capa -= wei,
					node[i ^ 1].capa += wei,
					used += wei,
					cost += node[i].cost * wei;
			}
		}
		if (used == flow)break;
	}
	vis[v] = false;
	return used;
}
inline void Dinic() {
	while (spfa()) {
		memcpy(cur, head, (t + 1) * sizeof(int));
		sum += dfs(s, inf);
	}
}
inline void addE(int u, int v, ll w, ll c) {
	add(u, v, w, c);
	add(v, u, 0, -c);
}
ll h[55][55]; int x, y;
inline int iid(int x, int y) {
	return (x - 1) * m + y;
}
inline int oid(int x, int y) {
	return iid(x, y) + n * m;
}
inline bool isok(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m;
}
int dx[4] = { 1, 0, -1, 0 }, dy[4] = { 0, 1, 0, -1 };
int main() {
	ios::sync_with_stdio(0);
	cin.tie(); cout.tie();
	memset(head, -1, V * sizeof(int));
	cin >> n >> m >> x >> y;
	s = 2 * n * m + 1, t = 2 * n * m + 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> h[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int k = 0; k <= 3; k++) {
				int nx = i + dx[k], ny = j + dy[k];
				if (!isok(nx, ny) || h[nx][ny] >= h[i][j])continue;
				addE(iid(i, j), oid(nx, ny), 1, h[i][j] - h[nx][ny]);
			}
		}
	}
	for (int i = 1; i <= n; i++) { 
		for (int j = 1; j <= m; j++) { 
			addE(s, iid(i, j), 1, 0);
			addE(oid(i, j), t, 1, 0);
		}
	}
	Dinic();
	cout << n * m - sum << " " << cost;
	return 0;
}
```


---

