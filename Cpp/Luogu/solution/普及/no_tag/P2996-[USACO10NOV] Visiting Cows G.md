# [USACO10NOV] Visiting Cows G

## 题目描述

After many weeks of hard work, Bessie is finally getting a vacation! After many weeks of hard work, Bessie is finally getting a vacation!  numbered 1..N. The cows have set up quite an unusual road network with exactly N-1 roads connecting pairs of cows C1 and C2 (1 <= C1 <= N; 1 <= C2 <= N; C1 != C2) in such a way that there exists a unique path of roads between any two cows.

FJ wants Bessie to come back to the farm soon; thus, he has instructed Bessie that if two cows are directly connected by a road, she may not visit them both. Of course, Bessie would like her vacation to be as long as possible, so she would like to determine the maximum number of cows she can visit.

经过了几周的辛苦工作,贝茜终于迎来了一个假期.作为奶牛群中最会社交的牛,她希望去拜访N(1<=N<=50000)个朋友.这些朋友被标号为1..N.这些奶牛有一个不同寻常的交通系统,里面有N-1条路,每条路连接了一对编号为C1和C2的奶牛(1 <= C1 <= N; 1 <= C2 <= N; C1<>C2).这样,在每一对奶牛之间都有一条唯一的通路. FJ希望贝茜尽快的回到农场.于是,他就指示贝茜,如果对于一条路直接相连的两个奶牛,贝茜只能拜访其中的一个.当然,贝茜希望她的假期越长越好,所以她想知道她可以拜访的奶牛的最大数目.


## 说明/提示

Bessie knows 7 cows. Cows 6 and 2 are directly connected by a road, as are cows 3 and 4, cows 2 and 3, etc. The illustration below depicts the roads that connect the cows:

1--2--3--4

|
5--6--7


Bessie can visit four cows. The best combinations include two cows on the top row and two on the bottom. She can't visit cow 6 since that would preclude visiting cows 5 and 7; thus she visits 5 and 7. She can also visit two cows on the top row: {1,3}, {1,4}, or {2,4}.


## 样例 #1

### 输入

```
7 
6 2 
3 4 
2 3 
1 2 
7 6 
5 6 
```

### 输出

```
4 
```

# 题解

## 作者：sy_zmq_001 (赞：15)

## 树形DP
##### 在学习树形动归之前，请先储备类似01背包，完全背包的知识；

顾名思义，树形动归就是在树上的动归，树形动归一般是依赖于dfs的，为什么呢，根据动归的后效性，父节点的状态一般都依赖子节点的状态以某种方式转移而来，而每一个父节点的孩子的数量不定，这就很难以寻常的递推式通过几个for解决掉，而大家可以想一下树这种东西它的遍历本身就依赖于dfs，可以说是比较暴力的打法了。

这里有一道很相似的题


没有上司的舞会
[https://www.luogu.org/problemnew/show/P1352；](https://www.luogu.org/problemnew/show/P1352)

#### 这是一道比较基础和经典的树形动归题；

那我们现在来分析一下这道题：
### 因为一个人不可能是他某个父节点的父节点，所以不可能出现环;如果一个点的父节点被访问，那么他的子节点就不会被访问，这样的话，就会出现

1.a（访问）->b（不访问）->c（访问）

2.a（访问）->b（不访问）->c(不访问）

这样我们就不能确定在b一定不去的情况下，是让c去而c的子节点不去而c的孙节点可以去的最终值大，还是c不去而c的子节点可以去的最终值大。这就是一个经典的......动归。

这里因为我们需要判断一个点的子节点是去了还是没去，所以可以加一维，以0为去了，1为没去。

那我们从哪个点开始呢，实际上从哪个点都可以，因为一个点的状态会以往上（父节点）和往下（子节点）的方式递归式传染，哪个点在上面哪个点在下面不重要。

下面给出代码
```
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int n,a,b,f[50003][2],used[50003];
vector <int> son[50003];

void dfs(int nx){
	used[nx]=1;
	for(int i=0;i<son[nx].size();i++){
		int v=son[nx][i];
		if(used[v]==1) continue;
		dfs(v);
		f[nx][1]+=f[v][0];
		f[nx][0]+=max(f[v][0],f[v][1]);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&a,&b);
		son[a].push_back(b);
		son[b].push_back(a);
		f[a][1]=1;//每一个点为一则被访问，f数组记录此状态下可以访问的总人数 
		f[b][1]=1;
	}
	dfs(1);
	printf("%d",max(f[1][1],f[1][0]));
	
	return 0;
}
```
## 后言

裸的树形动归一般是不会考的，树形dp可以与背包的思想相结合就是树形背包

下面给出两道树形背包的题

p2015 二叉苹果树
[https://www.luogu.org/problemnew/show/P2015](https://www.luogu.org/problemnew/show/P2015)

p2014选课

[https://www.luogu.org/problemnew/show/P2014](https://www.luogu.org/problemnew/show/P2014)

---

## 作者：x_faraway_x (赞：6)

一道树形dp。由题意可知，这题是树形结构题。我们设f[i][0]，表示不访问i号节点，f[i][1]表示访问i号节点。因为访问了i号节点，则不能访问i的孩子节点，所以可以得出下面的式子：

f[i][0] += max{f[k][0], f[k][1]}

f[i][1] += f[k][0] + 1

(f[i][0]=0, f[i][1]=1, k是i的孩子)

可以用邻接表存储。同时要注意孩子不能返回访问父亲。

具体请参考代码。

```cpp
#include <cstdio>
const int N = 50005;
int head[N], next[2*N], adj[2*N], tot, n, f[N][2];
inline int mx(int x, int y) {
    return x > y ? x : y;
}
void addedge (int u, int v) {
    next[++tot] = head[u];
    head[u] = tot;
    adj[tot] = v;
}
void dfs(int u, int father) {
    f[u][1] = 1;
    for(int e = head[u]; e; e = next[e]) {
        if(adj[e] == father) continue;
        dfs(adj[e], u);
        f[u][0] += mx(f[adj[e]][0], f[adj[e]][1]);
        f[u][1] += f[adj[e]][0];
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0);
    printf("%d", mx(f[1][0], f[1][1]));
    return 0;
}
```

---

## 作者：哔哩哔哩 (赞：5)

题解好少，我来一个vector存图的

听说NOIP考前RP++哦

[更好的阅读体验](https://www.cnblogs.com/fsy2017/p/9874677.html)

# 思路

## 树形DP

这算是一个树形DP经典题了

设状态f[i][0]为i点不访问，f[i][1]为i点访问

f[u][1] +=  f[y][0];表示u点要访问，(u,y)有连边

f[u][0] +=  max(f[y][0], f[v][1]);表示u点不访问，(u,y)有连边

这样按照树形结构DP下来就可以了

# 代码
```cpp
#include<bits/stdc++.h>//万能头文件
using namespace std;
#define N 50005
int f[N][2];//DP
vector<int>son[N];//存边
bool v[N];//记录是否访问过
inline int read() {
    int f = 1, x = 0; char ch;
    do { ch = getchar(); if (ch == '-')f = -1; } while (ch<'0' || ch>'9');
    do { x = x * 10 + ch - '0'; ch = getchar(); } while (ch >= '0'&&ch <= '9');
    return f * x;
}//读入优化
int dp(int u)//树形dp，表示以u点为根节点root
{
	f[u][1] = 1;//1为访问 初始值1
	for (int i=0;i<son[u].size();i++)//用vector访问每一个边
	{
		int y=son[u][i];//子节点
		if(!v[y]) //如果子节点没访问
		{
			v[y]=true;//标记为访问
			dp(y);//以这个子节点为根节点
			f[u][0]+=max(f[y][0],f[y][1]); //DP方程 上面有解释 每次取max
			f[u][1]+=f[y][0];
		}
	}
}
int main()
{
	int n=read();
	for(int i=1;i<n;i++)
	{
		int x=read(),y=read();
		son[x].push_back(y);//以x为根加入y的子节点
		son[y].push_back(x);//以y为根加入x的子节点
	}
	memset(v,0,sizeof(v));memset(f,0,sizeof(f));
	v[1]=true;//初始值
	dp(1);//从1开始
	printf("%d\n",max(f[1][1],f[1][0])); //输出
	return 0;
}
```
希望对大家有帮助哦

---

## 作者：K2sen (赞：4)

# P2996
[传送门](https://www.luogu.org/problem/P2996)

### 题意：
给你一棵树，每一条边上最多选一个点，问你选的点数.

### 我的思想：
一开始我是想用黑白点染色的思想来做，就是每一条边都选择一个点.

可以跑两边一遍在意的时候染成黑，第二遍染成白,取一个最大值.

就可以得到$30$分的高分.

```cpp
#include <bits/stdc++.h>
#define N 100010
#define M 1010
#define _ 0

using namespace std;
int n, tot, ans, add_edge, color[N], head[N];
struct node {
	int next, to;
}edge[N];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void add(int from, int to) {
	edge[++add_edge].next = head[from];
	edge[add_edge].to = to;
	head[from] = add_edge;
}

void dfs(int x, int fx) {
	if (color[fx] == 0) {
		color[x] = 1;
		tot++;
	}
	for (int i = head[x]; i; i = edge[i].next) {
		int to = edge[i].to;
		if (to == fx) continue;
		dfs(to, x);
	}
}

int main() {
	n = read();
	int point;
	for (int i = 1, x, y; i < n; i++) {
		x = read(), y = read();
		add(x, y), add(y, x);
		point = x;
	}
	dfs(point, 0);
	ans = max(ans, tot);
	memset(color, 0, sizeof (color));
	tot = 0, color[0] = 1;
	dfs(point, 0);
	cout << max(ans, tot);
}
```

很明显这样做是错误的.来看这样一组样例.

![](https://cdn.luogu.com.cn/upload/image_hosting/m6uram1q.png)

按照上述方法跑出来就是$5$，显然答案是$7$.然后我就是这样被学长$hack$了.

然后就问了学长树形$DP$.

### 正确思路:
我们设$dp[i][1/0]$来表示$i$与$i$的子树在$i$选还是不选，时的最大权值.

然后又因为在$dp[i][1]$时他的子节点不能选$dp[to][1]$.

在$dp[i][0]$时都可以选.我们就可以得到这样的转移方程(用$to$来表示$i$的子节点)：

$$dp[x][0] += max(dp[to][1], dp[to][0]);$$
$$	dp[x][1] += dp[to][0]; $$

然后就做完了.

#### code :
```cpp
#include <bits/stdc++.h>
#define N 100010
#define M 50010
#define _ 0

using namespace std;
int n, add_edge, head[N];
int dp[M][2];
struct node {
	int next, to;
}edge[N];

int read() {
	int s = 0, f = 0; char ch = getchar();
	while (!isdigit(ch)) f |= (ch == '-'), ch = getchar();
	while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar();
	return f ? -s : s;
}

void add(int from, int to) {
	edge[++add_edge].next = head[from];
	edge[add_edge].to = to;
	head[from] = add_edge;
}

void dfs(int x, int fx) {
	dp[x][1] = 1;
	for (int i = head[x]; i; i = edge[i].next) {
		int to = edge[i].to;
		if (to == fx) continue;
		dfs(to, x);
		dp[x][0] += max(dp[to][1], dp[to][0]);
		dp[x][1] += dp[to][0];
        //dp[x][1]时不可以选dp[to][1],他没得选qwq
	}
}

int main() {
	n = read();
	for (int i = 1, x, y; i < n; i++) {
		x = read(), y = read();
		add(x, y), add(y, x);
	}
	dfs(1, 0); 
	cout << max(dp[1][0], dp[1][1]);
}
```

---

## 作者：vеctorwyx (赞：3)

## 树形DP~~一眼~~经典题


~~当然你可以理解为[P1352	没有上司的舞会](https://www.luogu.com.cn/problem/P1352)的二倍经验~~

既然相连的两头牛只能选一个，那我们不妨：

   设```dp[i][0]```为在```i```的子树中不取```i```节点时最多可以访问的牛数，
   
   设```dp[i][1]```为在```i```的子树中取```i```节点时最多可以访问的牛数。
   
   那么我们就可以得到以下转移方程(j为i的子节点）：
   
   $dp[i][1]=dp[i][1]+dp[j][0];$
   
   $dp[i][0]=dp[i][0]+\max(dp[j][0],dp[j][1]);$
   
                  ~~~~~~~~~~^
                  注意这里，可以连续两个都不选。
                  
   代码如下：
   
   ```
   #include<iostream>
#include<cstdio>
using namespace std;
int n;
struct node
{
	int to,nxt;
}e[100010];//链式前向星存图
int h[50010],cnt,vis[50010],root;
void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=h[x];
	h[x]=cnt;
}
int f[50010],dp[50010][3];
void dfs(int x)
{
	vis[x]=1;
	for(int i=h[x];i;i=e[i].nxt)
	{
		if(vis[e[i].to])
		continue;
		dfs(e[i].to);
		dp[x][1]+=dp[e[i].to][0];//状态转移
		dp[x][0]+=max(dp[e[i].to][1],dp[e[i].to][0]);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);//看一眼样例就能知道不能只建单向边
	}
	for(int i=1;i<=n;i++)//初始化
	{
		dp[i][0]=0;
		dp[i][1]=1;
	}
	root=1;//无根树
	dfs(root);
	cout<<max(dp[root][1],dp[root][0]);
}
```
然后你~~应该~~就把这道题AC掉了,~~所以为什么不点个赞再走？~~

---

## 作者：RuSun (赞：2)

## Solution P2996

## 网络流最小割做法

由题意可知，这是一个经典的二选一问题，可以考虑最小割。

在题解中，我看到了将树染色获得二分图，然后直接将两种颜色的点数的最大值最为答案的做法，这显然是错误的。但是，在这个基础上可以使用最小割。

由于题意要我们求最大数量，没有权值，所以将左部点向源点连一条流量为 $1$ 的边，右部点向汇点连一条流量为 $1$ 的边，中间，如果两个端点间有一条边，则在网络中连一条流量为 $inf$ 的边，表示不可割，最小割的意思是最少放弃的点的数量，用总点数减去最小割即为答案。

在这道题中，由于树和网络分别需要一张图，建议使用 ``namespace`` 来防止重名。

代码如下

```
#include <cstdio>
#include <queue>
#include <algorithm>
using std::min;
using std::queue;
const int N = 5e4 + 10, M = 2e5 + 10, inf = 1e9;
int n;
namespace tree
{
	int c[N];
	int idx, hd[N], nxt[M], edg[M];
	void color(int x, int k)
	{
		c[x] = k;
		for (int i = hd[x]; ~i; i = nxt[i])
			if (!c[edg[i]])
				color(edg[i], 3 - k);
	}
	void add(int a, int b)
	{
		nxt[++idx] = hd[a];
		hd[a] = idx;
		edg[idx] = b;
	}
}
namespace net
{
	int st, ed, d[N], cur[N];
	int idx = -1, hd[N], nxt[M], edg[M], wt[M];
	bool bfs()
	{
		for (int i = st; i <= ed; i++)
			d[i] = -1;
		d[st] = 0;
		cur[st] = hd[st];
		queue<int> q;
		q.push(st);
		while (!q.empty())
		{
			int t = q.front();
			q.pop();
			for (int i = hd[t]; ~i; i = nxt[i])
				if (d[edg[i]] == -1 && wt[i])
				{
					d[edg[i]] = d[t] + 1;
					cur[edg[i]] = hd[edg[i]];
					if (edg[i] == ed)
						return true;
					q.push(edg[i]);
				}
		}
		return false;
	}
	int exploit(int x, int limit)
	{
		if (x == ed)
			return limit;
		int res = 0;
		for (int i = cur[x]; ~i && res < limit; i = nxt[i])
		{
			cur[x] = i;
			if (d[edg[i]] == d[x] + 1 && wt[i])
			{
				int t = exploit(edg[i], min(wt[i], limit - res));
				if (!t)
					d[edg[i]] = -1;
				wt[i] -= t;
				wt[i ^ 1] += t;
				res += t;
			}
		}
		return res;
	}
	int dinic()
	{
		int res = 0, flow;
		while (bfs())
			while (flow = exploit(st, inf))
				res += flow;
		return res;
	}
	void add(int a, int b, int c)
	{
		nxt[++idx] = hd[a];
		hd[a] = idx;
		edg[idx] = b;
		wt[idx] = c;
	}
}
void build()
{
	using namespace net;
	st = 0;
	ed = n + 1;
	for (int i = st; i <= ed; i++)
		hd[i] = -1;
	for (int i = 1; i <= n; i++)
		if (tree::c[i] == 1)
		{
			add(st, i, 1);
			add(i, st, 0);
			for (int j = tree::hd[i]; ~j; j = tree::nxt[j])
			{
				add(i, tree::edg[j], inf);
				add(tree::edg[j], i, 0);
			}
		}
		else
		{
			add(i, ed, 1);
			add(ed, i, 0);
		}
	printf("%d", n - dinic());
}
int main()
{
	using namespace tree;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		hd[i] = -1;
	for (int i = 1, a, b; i < n; i++)
	{
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	color(1, 1);
	build();
	return 0;
}
```

这道题用最小割仿佛有些杀鸡用牛刀了，题解中，大多都是树形动态规划的做法，但是我看到这道题第一反应就想到了最小割。

CSP-S2 & NOIP RP++

---

## 作者：Aiopr_2378 (赞：1)

# Solution-P2996 [USACO10NOV]Visiting Cows G

## 题目大意：

贝茜要在$n$个点，$n-1$条边组成的树中，到达最多的点，要求：同一条边上的两个点只能任选其一

## 思路：

#### 树形DP

题目要求中，同一条边上的两个点只能任选其一。也就是说，我们要么选择该点，要么选择该点的儿子。

如果我们设数组$dp[i][2]$：$dp[i][0]$表示不选i点的最优解，$dp[i][1]$表示选择i点的最优解。转移方程如下：

$dp[i][0]+=max(dp[son][1],dp[son][0])$，如果不选点i，我们就可以选择i点的儿子节点，当然，也可以不选它的儿子节点。

$dp[i][1]=dp[son][0]$，如果选了i点我们就不能选它的儿子了，因为它和它的儿子在一条边上。

参考代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,r[600005],fa[600005],dp[600005][2],s;
vector <int> v[600005];
void dfs(int x){
	dp[x][0]=0;
	dp[x][1]=r[x];
	for(int i=0;i<v[x].size();i++){
		int son=v[x][i];
		dfs(son);
		dp[x][0]+=max(dp[son][1],dp[son][0]);
		dp[x][1]+=dp[son][0];
	}
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>r[i];
		fa[i]=-1;
	}
	for(int i=1;i<n;i++){
		int a,b;
		cin>>a>>b;
		fa[a]=b;
		v[b].push_back(a);
	}
	for(int i=1;i<=n;i++){
		if(fa[i]==-1){
			s=i;
			break;
		}
	}
	dfs(s);
	cout<<max(dp[s][0],dp[s][1]);
	return 0;
}
```


---

## 作者：D12241R (赞：1)

## 题目大意：
在一棵$N$个点的树中，从根选择，选父亲则不能选儿子，选儿子则不能选父亲，求最大数量。

每个点只有两个选择：**1.选 2.不选。**


------------


1.**选**i号点：

$choose[i]$表示以$i$为根的树中选$i$的最大值。

$choose[i]$= $\sum Not[j](j\epsilon son[i])$

选$i$号点，则不能选$i$的儿子。

------------

2.**不选**i号点：

$Not[i]$表示以$i$为根的树中不选$i$的最大值。

$Not[i]$= $\sum Max \{choose[j],Not[j]\} (j\epsilon son[i])$

不选$i$号点，则可以选$i$的儿子，也可以不选$i$的儿子，故取儿子最大值。



------------
则**答案**为：

$ans=Max(Not[root],choose[root])$

------------

**初始化**：每个节点$choose$为$1$；

------------
**注意：**

因为讨论$i$时，$i$的所有儿子都要讨论，故用$dfs$讨论。

$N<=50000$,用链式前向星存储。

时间复杂度$\Theta(n)$

代码如下：

(int也能过，代码中开了long long)

```
#include<stdio.h>
#define R register
#define I inline
#define maxn 500001
#define LL long long
LL n,x,y,ans;
LL s[maxn],Not[maxn],choose[maxn],Last[maxn],Next[maxn],End[maxn];
bool root[maxn];
I void dfs(LL x)
{
	choose[x]=1;
	for(R LL i=Last[x]; i; i=Next[i])
	{
		if(!choose[End[i]])
		{
			dfs(End[i]);
		}
		choose[x]+=Not[End[i]];
		if(choose[End[i]]<Not[End[i]])
		{
			Not[x]+=Not[End[i]];
		}
		else
		{
			Not[x]+=choose[End[i]];
		}
	}
	return ;
}
int main()
{
	scanf("%lld",&n);
	for(R LL i=1; i<n; i++)
	{
		scanf("%lld%lld",&x,&y);
		End[i]=x;
		Next[i]=Last[y];
		Last[y]=i;
		root[x]=true;
	}
	for(R LL i=1; i<=n; i++)
	{
		if(!root[i])
		{
			dfs(i);
			ans=i;
			break;
		}
	}
	if(Not[ans]>choose[ans])
	{
		ans=Not[ans];
	}
	else
	{
		ans=choose[ans];
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：Yang818 (赞：1)

一道典型的树形$dp$题。
本蒟蒻是刚从[P1352](https://www.luogu.com.cn/problem/P1352)过来的，那是一道比这道题更经典的树形$dp$，经典程度好比区间$dp$中的[石子合并](https://www.luogu.com.cn/problem/P1880)。好了，废话不多说。
### problem：
有$n$个节点，$n-1$条边，每个边连接的两个节点只能走其中的一个，求最多能走几个节点。由于是$dp$题目，所以本蒟蒻待会儿用刚学会的LaTeX来给大家写一遍$dp$方程。
### solution:
首先我们要确定存储树的方法。这边程序里用的是链式前向星。

```cpp
void add_edge(int u,int v){
	g_e[++cnt].v=v;
	g_e[cnt].nxt=head[u];
	head[u]=cnt;
}
```


$dp$方程：

$f(u,0/1)$ 表示从1到u这个点能经过的最多节点。其中第二维如果是1则表示去u这个节点。如果是0就代表不去这个节点。
$f(u,0)=\sum_{k} \max{f(v,0),{f(v,1)}}$

$f(u,1)=a[u]+\sum_{k}  f(v,0)$

其中$k$代表的是$v$要是$u$的子节点。

$dfs$函数如下:
```cpp
void dfs(int u,int fa){
	for(int i=head[u];i;i=g_e[i].nxt){
		if(g_e[i].v==fa)
			continue;
		dfs(g_e[i].v,u);
		g_f[u][1]+=g_f[g_e[i].v][0];
		g_f[u][0]+=max(g_f[g_e[i].v][0],g_f[g_e[i].v][1]);
	}
}
```
### notice：

1.别忘了设置初值

```cpp
	for(int i=1;i<=g_n;i++){
		g_f[i][1]=1;
	}
```

2.链式前向星数组范围要乘以2，别忘了，要不然会有两个测试点过不了

### code

还要看代码吗？

不用了。

算了，我还是给一下吧：
```cpp
#include<bits/stdc++.h>//万能头文件

using namespace std;

const int MAXN=50010;
struct edge{
	int v,nxt;
}g_e[2*MAXN];//链式前向星数组范围要乘以2，别忘了，要不然会有两个测试点过不了
int g_n,cnt,g_f[MAXN][2],head[MAXN];
bool flag[MAXN];

void add_edge(int u,int v){
	g_e[++cnt].v=v;
	g_e[cnt].nxt=head[u];
	head[u]=cnt;
}

void dfs(int u,int fa){
	for(int i=head[u];i;i=g_e[i].nxt){
		if(g_e[i].v==fa)
			continue;
		dfs(g_e[i].v,u);
		g_f[u][1]+=g_f[g_e[i].v][0];
		g_f[u][0]+=max(g_f[g_e[i].v][0],g_f[g_e[i].v][1]);
	}
}

int main(){
	cin>>g_n;
	for(int i=1;i<=g_n;i++){
		g_f[i][1]=1;//初值
	}
	for(int i=1;i<g_n;i++){
		int u,v;
		cin>>v>>u;
		add_edge(u,v);
		add_edge(v,u);//双向图，加两条边
	}
	dfs(1,0);
	cout<<max(g_f[1][1],g_f[1][0])<<endl;
	return 0;
} 
```



---

## 作者：Usada_Pekora (赞：0)

根据题意，得出以下一点：对于当前点$i$，有拜访与不拜访两种情况，若拜访     $ i $，那么便不可以拜访任意$i$的子节点$j$。

设 $ f[i][0] $ 为不取 $ i $ 点时最多可以拜访的牛数，
 $ f[i][1] $ 为取 $ i $ 点时最多可以拜访的牛数。

可得以下两条状态转移方程：

$ f[i][1] = f[i][1] + f[j][0] $

$ f[i][0] = f[i][0] + \max ( f[j][0] , f[j][1] ) $

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int x=0;
    while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    return x;
}
int n,f[50005][2];
vector<int>v[50005];
bool vis[50005];
inline void dfs(int u){
	vis[u]=true;
	for(int i=0;i<v[u].size();i++){
		if(vis[v[u][i]])continue;
		dfs(v[u][i]);
		f[u][1]+=f[v[u][i]][0];
		f[u][0]+=max(f[v[u][i]][0],f[v[u][i]][1]);
	}
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		v[x].push_back(y);
		v[y].push_back(x);
		f[x][1]=f[y][1]=1;
	}
	dfs(1);
	printf("%d",max(f[1][1],f[1][0]));
	return 0;
}
```


---

## 作者：RainFestival (赞：0)

这道题是dp

但是它是树形的

所以叫树形dp

它与没有上司的舞会相近，但那题数据弱，可以贪心过

dp方程：

dp i 0 不选i

dp i 1 选i

dp i 0 =max(dp son 0,dp i son 1)之和

dp i 1 =dp son 0之和

最后输出 dp 1 1 与dp 1 0 的最大值

完工！！！

下面是代码：

```pascal
//uses math;
function max(x,y:longint):longint;
begin
  if x>y then exit(x);
  exit(y);
end;
var
  vv:array[0..50005,0..1] of longint;
  a:array[0..50005,0..505] of longint;
  l,v,b,d:array[0..50005] of longint;
  x,y,n,i,q:longint;
procedure dfs(xx:longint;p:longint);
var i:longint;
begin
  for i:=1 to l[xx] do
    if a[xx][i]<>p then dfs(a[xx][i],xx);
  vv[xx][0]:=0;
  for i:=1 to l[xx] do
    vv[xx][0]:=vv[xx][0]+max(vv[a[xx][i]][0],vv[a[xx][i]][1]);
  vv[xx][1]:=1;
  for i:=1 to l[xx] do
    vv[xx][1]:=vv[xx][1]+vv[a[xx][i]][0];
end;
begin
  readln(n);
  for i:=1 to n do
    b[i]:=i;
  for i:=1 to n-1 do
    begin
      readln(x,y);
      inc(l[y]);
      inc(l[x]);
      a[y][l[y]]:=x;
      a[x][l[x]]:=y;
    end;
  //ddfs(1);
  //d[1]:=1;
  dfs(1,0);
  writeln(max(vv[1][0],vv[1][1]));
end.


```
[评测记录](https://www.luogu.org/recordnew/show/17100583)

谢谢巨佬们的观赏

推荐一下p1352

---

