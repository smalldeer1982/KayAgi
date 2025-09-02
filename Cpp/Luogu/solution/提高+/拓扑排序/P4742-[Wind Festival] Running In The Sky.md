# [Wind Festival] Running In The Sky

## 题目背景

$[Night - 20:02$ $P.M.]$

夜空真美啊……但是……快要结束了呢……

## 题目描述

一天的活动过后，所有学生都停下来欣赏夜空下点亮的风筝。$Curtis$ $Nishikino$想要以更近的视角感受一下，所以她跑到空中的风筝上去了(这对于一个妹子来说有点匪夷所思)! 每只风筝上的灯光都有一个亮度 $k_i$. 由于风的作用，一些风筝缠在了一起。但是这并不会破坏美妙的气氛，缠在一起的风筝会将灯光汇聚起来，形成更亮的光源！

$Curtis$ $Nishikino$已经知道了一些风筝间的关系，比如给出一对风筝$(a,b)$, 这意味着她可以从 $a$ 跑到 $b$ 上去，但是不能返回。

现在，请帮她找到一条路径(她可以到达一只风筝多次，但只在第一次到达时她会去感受上面的灯光), 使得她可以感受到最多的光亮。同时请告诉她这条路径上单只风筝的最大亮度，如果有多条符合条件的路径，输出能产生最大单只风筝亮度的答案。

## 说明/提示

对于 $20\%$ 的数据, $0<n \le 5\times10^3, \ 0 < m \le 10^4$.

对于 $80\%$ 的数据, $0 < n \le 10^5, \ 0 < m \le 3\times10^5$.

对于 $100\%$ 的数据, $0<n\le2\times10^5,\ 0<m\le5\times10^5,\ 0<k\le200$.


## 样例 #1

### 输入

```
5 5
8 9 11 6 7
1 2
2 3
2 4
4 5
5 2```

### 输出

```
41 11```

# 题解

## 作者：STrAduts (赞：8)


### 引子

> 果然老师们都只看标签拉题。。。

发现需要处理环，然后通过一些神奇的渠道了解到有个东西叫缩点。

紧接着搜了一下缩点，发现了 Tarjan 算法。

然后又翻了翻算法竞赛，于是一去不复返……
***
### 一些定义

给定一张有向图。对于图中任意两个节点 $x, y$，存在从 $x$ 到 $y$ 的路径，也存在 $y$ 到 $x$ 的路径。则称该有向图为“**强连通图**”。

有向图的强连通子图被称为**强连通分量** $SCC$ $(Strongly$ $Connected$ $Component)$。

显然，环一定是强连通图。因为如果在有向图中存在 $x$ 到 $y$ 的路径，且存在 $y$ 到 $x$ 的路径，那么 $x, y$ 一定在同一个环中。

对于一个有向图，如果从 $root$ 可以到达图中所有的点，则称其为“**流图**”，而 $root$ 为流图的源点。

以 $root$ 为原点对流图深度优先遍历，每个点只访问一次，在过程中，所有发生递归的边 $(x, y)$ 构成的一棵树叫做这个流图的**搜索树**。

在深度优先遍历时，对每个访问到的节点分别进行整数 $1...n$ 标记，该标记被称为**时间戳**，记为 $dfn[x]$。

流图中的每条有向边 $(x, y)$ 必然是以下四种中的一种：

1. 前向边，指搜索树中 $x$ 是 $y$ 的祖先节点

2. 后向边，指搜索树中 $y$ 是 $x$ 的祖先节点

3. 树枝边，指搜索树里的边，满足 $x$ 是 $y$ 的父节点。

4. 其他边（好像也叫横叉边），指除了上面三种情况的边。且一定满足 $dfn[y] < dfn[x]$

***
### Tarjan算法之强连通分量

Tarjan 算法基于有向图的深度优先遍历，能够在线性时间中求出一张有向图的各个强连通分量。

其核心思想就是考虑两点之间是否存在路径可以实现往返。

我们在后文中，都会结合搜索树（本身就是深度优先遍历的产物）来考虑，这样就可以在深度优先遍历的同时完成我们的目标。

对于流图，前向边作用不大，因为当前搜索树中一定存在 $x$ 到 $y$ 的路径。

后向边就很重要了，因为它一定可以和搜索树中 $x$ 到 $y$ 的路径组成环。

横叉边需要判断一下，如果这条横叉边能到达搜索树上 $x$ 的祖先（显然，$x$ 的祖先一定可以到达 $x$）。记这个祖先为 $z$，则这条横叉边一定能和它到 $z$ 的路径，$z$ 到 $x$ 的路径组成环。

为了找到横叉边与后向边组成的环，我们考虑在深度优先遍历的同时维护一个栈。

当遍历到 $i$ 节点时，栈里一定有以下一些点：

1. 搜索树上 $i$ 的所有祖先集合 $j$。若此时存在后向边 $(i, j)$，则 $(i, j)$ 一定与 $j$ 到 $i$ 的路径形成环。
2. 已经访问过的点 $k$，且满足从 $k$ 出发一定能找到到 $j$ 的路径。此时，$(i, k)$，$k$ 到 $j$ 的路径，$j$ 到 $i$ 的路径一定会形成环。

于是我们引入回溯值的概念。回溯值 $low[x]$ 表示以下节点的最小时间戳：

1. 该点在栈中。
2. 存在一条从流图的搜索树中以 $x$ 为根的子树为起点出发的有向边，以该点为终点。（也就是以它为起点能继续往下遍历到的点）

如果当前的 $low[x]$ 表示的最小时间戳代表的点集全是2类点，则易得 $low[x] = dfn[x]$ 时强连通分量存在，且 $x$ 是此强连通分量的根（整个强连通分量中时间戳最小的节点）。

如果表示的点集存在1类点。则当前点一定属于强连通分量，且该强连通分量的根为整个强连通分量中时间戳最小的节点。

当我们判断了存在以当前点为根的强连通分量后，从栈中不断取出点，直到取出的点与当前点相等，我们就得到了整个强连通分量的信息。

整理更新回溯值的方法：

1. 如果当前点第一次被访问，入栈，且 $low[x] = dfn[x]$。
2. 遍历从 $x$ 为起点的每一条边 $(x, y)$。若 $y$ 被访问过，且 $y$ 在栈中，那么 $low[x] = min(low[x], dfn[y])$。若 $y$ 没被访问过，递归访问 $y$，在回溯之后更新 $low[x] = min(low[x], low[y])$。（典型$dp$思想）

### 具体实现

```cpp
int dfn[MAXN], low[MAXN];
// 时间戳及回溯值。
vector <int> scc[MAXN];
// 储存最后求出的各个强连通分量的信息。
int key[MAXN];
// key[i]表示i在编号为key[i]的强连通分量中。

stack<int> st; // 栈。
bool vis[MAXN];
// 记录是否在栈中。
int num = 0, cnt = 0; 
// num 时间戳标记。cnt 强连通分量标记。

void tarjan(int x) {
	num++; 
	dfn[x] = num;
	low[x] = num;
	st.push(x); 
	vis[x] = true;		
    // 第一次遍历到，记录时间戳，入栈，记录当前回溯值		
	for(int i = 0; i < map_first[x].size(); i++) { // 枚举每条边。
		int j = map_first[x][i];
		if(!dfn[j]) { // 如果当前边的终点没被遍历过。
			tarjan(j); // 递归遍历。
			low[x] = min(low[x], low[j]);
            // 维护回溯值。
		}
		else if(vis[j]) // 如果遍历过且在栈中。
			low[x] = min(low[x], dfn[j]);
            // 维护回溯值。
	}
	if(dfn[x] == low[x]) { // 如果存在以当前点为根的强连通分量。			
		cnt++;
		int now = 0;
		while(x != now) { // 找出栈中所有在当前强连通分量中的点。
			now = st.top();
			st.pop();
			vis[now] = false; 
			key[now] = cnt;	// 存所在编号。
			scc[cnt].push_back(now); // 存点。
		}
	}	
}
```
***

### 缩点

缩点。其实就是指的把环看成一个点来进行后面的图论算法。而把环看成的这个点的点权在题目中会具体说明。

比较常见的缩点后的点权是整个环路的所有点的点权和。

如下图：

    1 -> 2 -> 4 -> 5 -> 2 -> 3
显然上图存在环路。在经过缩点后，我们可以将它变成这样：

    1 -> 2(value[2] + value[4] + value[5]) -> 3
思路比较简单，我就直接分析代码了。。。

**具体实现**

```cpp
for(int i = 1; i <= n; i++) 
    for(int j = 0; j < map_first[i].size(); j++) {
        // 枚举原图中的每一条边。
        int v = map_first[i][j];
        if(key[i] == key[v]) 
        // 如果这个边的两端属于同一个强连通分量，则直接放弃这条连边。
            continue;
        map_second[key[i]].push_back(key[v]);
        // 将两个点对应的强连通分量的编号相连，加入新图。
        // 显然，单个点也属于一个强连通分量。
    }
```
***

现在，我们再来看看这道题。。。

### 分析

显然这道题是有环的对吧。

如果我们不考虑环的情况，其实就是一个很板~~白菜~~的题目。

我们可以采用拓扑排序的思路，遍历整个图，然后对于每个路径维护一下到当前点的最大距离，并维护一个这个路径上的最大值。

然后考虑有环，很简单，事先 Tarjan 缩点嘛/xyx

并且这道题是要累加路径上的点的和。所以缩点后的点就是当前强连通分量包含的所有点的点权和。

### AC代码

```cpp
#include <cstdio> 
#include <stack>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
int n, m;
int value[MAXN];

vector<int> map_first[MAXN]; 
// 原图。 
int dfn[MAXN], low[MAXN];

struct data {
	int ma, sum;
	data() {
		ma = 0;
		sum = 0;
	}
	data(int Ma, int S) {
		ma = Ma;
		sum = S;
	}
} scc[MAXN]; 
// Tarjan 求出的强连通分量中，维护两个信息。
// 1.ma 表示整个强连通分量的最大值。 
// 2.sum 表示整个强连通分量的点权和，即缩点后的点权。 
int key[MAXN];

stack<int> st;
bool vis[MAXN];
int num = 0, cnt = 0;

void tarjan(int x) { // tarjan 算法。 
	num++;
	dfn[x] = num;
	low[x] = num;
	st.push(x);
	vis[x] = true;				
	for(int i = 0; i < map_first[x].size(); i++) {
		int j = map_first[x][i];
		if(!dfn[j]) {
			tarjan(j);
			low[x] = min(low[x], low[j]);
		}
		else if(vis[j]) 
			low[x] = min(low[x], dfn[j]);
	}
	if(dfn[x] == low[x]) {			
		cnt++;
		int now = 0;
		while(x != now) {
			now = st.top();
			st.pop();
			vis[now] = false;
			key[now] = cnt;		
			scc[cnt].ma = max(scc[cnt].ma, value[now]);
			scc[cnt].sum += value[now];
			// 维护一下强连通分量的两个信息。 
		}
	}	
}

vector<int> map_second[MAXN]; // 新图。 
int in[MAXN]; // 拓扑排序，统计点的入度。 
int dp[MAXN][2];
// dp[i][0]表示到i点的最长路径。 
// dp[i][1]表示路径上的最大点权。 

void T_Sort() { // 拓扑。 
	queue<int> q;
	for(int i = 1; i <= cnt; i++) {
		dp[i][0] = scc[i].sum;
		dp[i][1] = scc[i].ma;
	}
	for(int i = 1; i <= cnt; i++) 
		if(!in[i]) 
			q.push(i);
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for(int i = 0; i < map_second[x].size(); i++) {
			int v = map_second[x][i];
			in[v]--;
			if(!in[v]) 
				q.push(v);
			if(dp[v][0] < dp[x][0] + scc[v].sum) {
				dp[v][0] = dp[x][0] + scc[v].sum;
				dp[v][1] = max(dp[x][1], scc[v].ma);
				// 更新最长路径及最大点权。 
			}
			if(dp[v][0] == dp[x][0] + scc[v].sum) 
				dp[v][1] = max(dp[v][1], dp[x][1]);
			// 如果有两条最长路径则记录两条路径中的最大值。 
		}
	}
}

int main() {
	scanf ("%d %d", &n, &m);
	for(int i = 1; i <= n; i++) {
		scanf ("%d", &value[i]);
		key[i] = i;
	}
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf ("%d %d", &u, &v);
		map_first[u].push_back(v);
	}
	
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) // 如果当前点没被遍历，则跑一遍 Tarjan。 
			tarjan(i); 
			
	for(int i = 1; i <= n; i++) 
		for(int j = 0; j < map_first[i].size(); j++) {
			int v = map_first[i][j];
			if(key[i] == key[v])
				continue;
			map_second[key[i]].push_back(key[v]);
			in[key[v]]++;
		}
	// 缩点，存新图。 
	
	T_Sort();
	int ans = 1;
	for(int i = 2; i <= cnt; i++) // 统计答案。 
		if(dp[i][0] > dp[ans][0] || (dp[i][0] == dp[ans][0] && dp[i][1] > dp[ans][1])) 
			ans = i;
	printf("%d %d", dp[ans][0], dp[ans][1]);
	return 0;
} 
```


---

## 作者：米奇奇米 (赞：4)

## 这道题目的主要运用到的算法为$tarjan$+重新建图+搜索树——>总体难度不是很大，大概$TGDay1T2$吧。
### 对于此题德第一问与有一道题目是同理的，相当于来说你做出啦这题就成双倍经验了，但说实话很多$tarjan$题都是一模一样的，稍加修改就$AC$啦。
### 两题的题目传送门：[P4742 [Wind Festival]Running In The Sky](https://www.luogu.org/problemnew/show/P4742)
### [P3387 【模板】缩点](https://www.luogu.org/problemnew/show/P3387)
### 言归正题：对于第一问只要爆写一个$tarjan$模板，用$siz[],size[]$数组分别记录该条线路上的权值总和以及该路径上的最大值。真得很简单看一下代码吧：
```cpp
inline void tarjan(int u) {//稍加修改的tarjan模板
	dfn[u]=low[u]=++now;//统计时间戳
	stak[++top]=u;
	for ( re int i=head[u];i;i=e[i].nex ) {
		int v=e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else 
			if(!col[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		col[u]=++sum;
		siz[sum]=val[u];
		size[sum]=max(size[sum],val[u]);
		while(stak[top]!=u) {
			col[stak[top]]=sum;
			siz[sum]+=val[stak[top]];//累加各点权值
			size[sum]=max(size[sum],val[stak[top]]);//取权值的最大值
			top--;
		}
		top--;
	}
}
```
### 对于第二问我们同样也用两个数组$f[],ff[]$，分别记录总和以及最大值，枚举每个强连通分量，进行$dfs$一遍，算出每个强连通分量对答案的贡献，然后就对答案取最大值即可,$ans1$记录第一问，$ans2$记录第二问，只有在第一问答案大于当前时候才更新$ans1,ans2$。然后就撒花啦~~~~~
### 然后就贴代码吧，变量神多啊$QWQ$
```cpp
// luogu-judger-enable-o2
#include <bits/stdc++.h>
#define re register 
#define mem(x) memset(x,0,sizeof(x))
using namespace std;

const int maxn=2e5+5,maxm=5e5+5;
int head[maxn],low[maxn],dfn[maxn];
int stak[maxn],col[maxn],siz[maxn],val[maxn];
int u[maxm],v[maxm],rd[maxn],cd[maxn];
int size[maxn],f[maxn],ff[maxn];//冗杂的变量定义，可把我吓坏了

struct nood {
	int nex,to;
}e[maxm<<1];
int n,m,cnt,top,now,sum;
int res1,res2,MAX1,MAX2;

inline void add_edge(int u,int v) {
	e[++cnt].nex=head[u];
	head[u]=cnt;
	e[cnt].to=v;
}//前向星式连边

inline void tarjan(int u) {//tarjan部分略加修改
	dfn[u]=low[u]=++now;
	stak[++top]=u;
	for ( re int i=head[u];i;i=e[i].nex ) {
		int v=e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else 
			if(!col[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]) {
		col[u]=++sum;
		siz[sum]=val[u];
		size[sum]=max(size[sum],val[u]);
		while(stak[top]!=u) {
			col[stak[top]]=sum;
			siz[sum]+=val[stak[top]];
			size[sum]=max(size[sum],val[stak[top]]);
			top--;
		}
		top--;
	}
}//很模板的啦！

inline void dfs(int u) {
	if(f[u]) return;
	f[u]=siz[u];
	ff[u]=size[u];//初始化部分
	MAX1=MAX2=0;
	for ( re int i=head[u];i;i=e[i].nex ) {
		int v=e[i].to;
		dfs(v);//递归下去
		if(f[v]>MAX1) MAX1=f[v],MAX2=ff[v];
	}
	f[u]=f[u]+MAX1;//累加权值
	ff[u]=max(ff[u],MAX2);//取最大值
}

int main() {
	scanf("%d%d",&n,&m);
	mem(dfn),mem(head);
	for ( re int i=1;i<=n;i++ ) scanf("%d",&val[i]);
	for ( re int i=1;i<=m;i++ ) {
		scanf("%d%d",&u[i],&v[i]);
		add_edge(u[i],v[i]);
	}
	for ( re int i=1;i<=n;i++ ) if(!dfn[i]) tarjan(i);
	cnt=0;mem(head),mem(e);cnt=0;
	for ( re int i=1;i<=m;i++ ) 
		if(col[v[i]]!=col[u[i]]) {
			rd[col[v[i]]]++;
			add_edge(col[u[i]],col[v[i]]);
		}//重新建图部分
	for ( re int i=1;i<=sum;i++ ) {
		if(!f[i]) dfs(i);
		if(f[i]>res1) res1=f[i],res2=ff[i];
        //更新两个值
	}
	printf("%lld %lld\n",res1,res2);
	return 0;
}
	
```
### [戳这里吧(逃](https://www.luogu.org/team/show?teamid=15177)


---

## 作者：Cutest_Junior (赞：3)

## 题解 P4742 【[Wind Festival]Running In The Sky】

### 题意

+ 给出 $n$ 个点 $m$ 条边的有向图；
+ 每个点有一个权值；
+ 找出一条路径，可以重复经过边和点；
+ 求路径经过的所有点的权值和（重复经过的点只计算一次）的最大值，以及当权值和为最大值时，经过的单点权值的最大值；
+ $n\le2\times10^5,m\le5\times10^5$。

### 做法

因为可以重复经过边和点，那我们先 Tarjan 缩点，然后在 DAG 上跑拓扑排序 + DP。

用 $arr1,arr2$ 分别表示新图上每个点的权值和以及最大权值。

用 $dp1,dp2$ 分别表示新图上到达没个点的最大权值和以及最大权值。

对于每条边 $x->to$，修改答案：

```cpp
if (dp1[to] < dp1[x] || dp1[to] == dp1[x] && dp2[to] < dp2[x]) {
	dp1[to] = dp1[x];
	dp2[to] = dp2[x];
}
```

对于每个新入对的点 $to$:

```cpp
if (in[to] == 0) {
	dp1[to] += arr1[to];
	dp2[to] = max(dp2[to], arr2[to]);
	que.push(to);
}
```

这道题细节比较多，附上讨论区的两组 hack 数据。

```cpp
in1:
6 4
4 5 4 1 10 1 
1 2
2 3
4 5
5 6

out1: 
13 5

in2:
6 6
1000 3 2 2 1 999
3 1
4 2
3 2
4 1
1 5
2 6

out2: 
1004 999

```

### 代码

```cpp
#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 2e5 + 5;

int val[N];

vector<int> edge1[N], edge2[N];

void add(vector<int> *edge, int u, int v) {
	edge[u].push_back(v);
}

int dfn[N], dfstot;
int low[N];
int scc[N], scctot;

stack<int> sta;

void tarjan(int x) {
	dfn[x] = low[x] = ++dfstot;
	
	sta.push(x);
	
	for (int i = 0; i < edge1[x].size(); ++i) {
		int to = edge1[x][i];
		
		if (dfn[to] == 0) {
			tarjan(to);
			low[x] = min(low[x], low[to]);
		}
		else if (scc[to] == 0) {
			low[x] = min(low[x], dfn[to]);
		}
	}
	
	if (low[x] == dfn[x]) {
		++scctot;
		
		while (1) {
			int t = sta.top();
			sta.pop();
			
			scc[t] = scctot;
			if (t == x) {
				break;
			}
		}
	}
}

int arr1[N];
int arr2[N];
int in[N];
int dp1[N];
int dp2[N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &val[i]);
	}
	
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		
		add(edge1, u, v);
	}
	
	for (int i = 1; i <= n; ++i) {
		if (dfn[i] == 0) {
			tarjan(i);
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		int si = scc[i];
		arr1[si] += val[i];
		arr2[si] = max(arr2[si], val[i]);
		
		for (int j = 0; j < edge1[i].size(); ++j) {
			int to = edge1[i][j];
			int st = scc[to];
			
			if (si == st) {
				continue;
			}
			
			add(edge2, si, st);
			++in[st];
		}
	}
	
	queue<int> que;
	
	for (int i = 1; i <= scctot; ++i) {
		if (in[i] == 0) {
			que.push(i);
			dp1[i] = arr1[i];
			dp2[i] = arr2[i];
		}
	}
	
	while (!que.empty()) {
		int x = que.front();
		que.pop();
		
		for (int i = 0; i < edge2[x].size(); ++i) {
			int to = edge2[x][i];
			
			if (dp1[to] < dp1[x] || dp1[to] == dp1[x] && dp2[to] < dp2[x]) {
				dp1[to] = dp1[x];
				dp2[to] = dp2[x];
			}
			
			--in[to];
			if (in[to] == 0) {
				dp1[to] += arr1[to];
				dp2[to] = max(dp2[to], arr2[to]);
				que.push(to);
			}
		}
	}
	
	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= scctot; ++i) {
		if (ans1 < dp1[i] || ans1 == dp1[i] && ans2 < dp2[i]) {
			ans1 = dp1[i];
			ans2 = dp2[i];
		}
	}
	printf("%d %d", ans1, ans2);
}
```

---

## 作者：Poetic_Rain (赞：3)

相信来做这道题的人肯定都学过$Tarjan$缩点吧，如果没有建议先去做[P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)，如果你忘了，建议也去看看

满足上面要求后，你会惊奇发现，这两道题基本一样，唯一的差别就是这道题需要记录最大点权，比模板题多一个要求

但其实这很好想，在缩点的时候，我们另开一个数组记录每一个缩点之后的最值，其余部分完全一样。至于程序我就不贴了

然后就是跑最大值，其实就是跑最长路，我们可以使用拓扑，记忆化搜索或者DP，但是之前做的时候用的是拓扑，这里就只说拓扑的做法

我们用$dis$表示到达该点时的最长路，$maxn$表示到达该点的最长路上的最大点权

在拓扑跑最长路的过程中，每更新一次最长路，就意味着这条最长路发生了改变，所以这个时候我们应当把$maxn$清空，重新更新一次最大点权，不然就会出错，在最后更新答案时，也要注意这个地方

```
#include <bits/stdc++.h>
using namespace std;
int n,m,ti,cnt,top,tot,ans=-99999999,sum,a[5000010],q[5000010],in[5000010],dis[5000010],pre[5000010],poi[5000010];
int dfn[5000010],low[5000010],vis[5000010],num[5000010],fir[5000010],head[5000010],heads[5000010],maxn[5000010];
int x[5000010],y[5000010];

struct node {
	int to,net;
} e[5000010],es[5000010];

void add(int u,int v) {
	e[++tot].to=v;
	e[tot].net=head[u];
	head[u]=tot;
}

void adds(int u,int v) {
	es[++tot].to=v;
	es[tot].net=heads[u];
	heads[u]=tot;
}

void tarjan(int x) {
	vis[x]=1;
	q[++top]=x;
	dfn[x]=low[x]=++ti;
	for(int i=head[x];i;i=e[i].net) {
		int v=e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else {
			if(vis[v]) low[x]=min(low[x],dfn[v]);
		}
	}
	if(low[x]==dfn[x]) {
		++cnt;
		while(q[top+1]!=x) {
			vis[q[top]]=0;
			fir[q[top]]=cnt;
			num[cnt]+=a[q[top]];
			poi[cnt]=max(poi[cnt],a[q[top]]); //记录缩完点之后的最大点权 
			top--;
		}
	}
}

inline void topo() {
	queue<int> q;
	for(register int i=1;i<=cnt;i++) {
		dis[i]=num[i];
		maxn[i]=poi[i];
		if(!in[i]) q.push(i);
	} //记得初始化 
	while(!q.empty()) {
		int xx=q.front();
		q.pop();
		for(register int i=heads[xx];i;i=es[i].net) {
			int v=es[i].to;
			if(dis[xx]+num[v]>dis[v]) { //更新最大边权之和
				maxn[v]=0;             //记得清空，因为更换了路径 
				maxn[v]=max(poi[v],maxn[xx]);
				dis[v]=dis[xx]+num[v];
			}else if(dis[xx]+num[v]==dis[v]){
				maxn[v]=max(maxn[v],maxn[xx]);
			}//注意判断边权相同的情况，此时点权可能更大 
			if(--in[v]==0) q.push(v);
		}
	}
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=m;i++) {
		scanf("%d%d",&x[i],&y[i]);
		add(x[i],y[i]);
	}
	for(int i=1;i<=n;i++) {
		if(!dfn[i]) tarjan(i);
	}
	tot=0;
	for(int i=1;i<=m;i++) {
		if(fir[x[i]]!=fir[y[i]]){
			adds(fir[x[i]],fir[y[i]]);
			++in[fir[y[i]]];
		}
	}
	topo();
	for(int i=1;i<=cnt;i++) {
		if(ans<dis[i]) {
			ans=dis[i];
			sum=0;  //这个地方我最开始一直没考虑到（但是边权我却改了），95分调了很久 
			sum=max(sum,maxn[i]);
		}else if(ans==dis[i]){
			ans=dis[i];
			sum=max(sum,maxn[i]);
		}//和上面topo一样的思路 
	}
	printf("%d %d",ans,sum);
	return 0;
}
```


---

## 作者：ZolaWatle (赞：2)

## P4742 题解

题意概述：给一张有向图（可能有环），找一条路径，使这条路径上所有点的点权和最大。若有多条路径的点权和同为最大，则选择这条路径上最大的点权最大的路径作为答案。

两个要素：**可能有环**（一些风筝缠在了一起）、**点权**。

我们可以将一个环看作是一个点，这个点的点权即为所有点的点权和。

那么做这道题要干的第一件事就是**缩点**，可以使用**Tajan**。

另外，我们需要的是**点权和**以及**最大点权**。可以开两个数组。$ sum_i $ 表示第 $ i $ 个强联通分量的权值（和）；$ maxs_i $ 表示第 $ i $ 个强联通分量的最大点权。

很显然，缩点后的点权相当于原图中那几个点的点权和；缩点后的最大点权也是原图中那个最大点权。

Tarjan的板子~~是个人都会~~，明确了我们要求的东西，可以写出如下代码：

```cpp
inline void Tarjan(int x)
{
	low[x]=dfn[x]=++idx;
	s.push(x),ins[x]=true;  //将x入栈，ins为in_stack的简写 
	for(re i=0;i<E[x].size();i++)  //枚举所有x连到的点 
	{
		re y=E[x][i];  //优美的vector 
		if(!dfn[y])
		{
			Tarjan(y);
			low[x]=std::min(low[x],low[y]);
		}
		else if(ins[y])
			low[x]=std::min(low[x],dfn[y]);
	}  //Tarjan传统艺能 
	if(low[x]==dfn[x])
	{
		cnt++;
		re y;
		do
		{
			y=s.top();
			s.pop();
			ins[y]=false;  //取出栈顶 
			qlt[y]=cnt;  //点y在第cnt个强联通分量中（便于到时候重新建图） 
			sum[cnt]+=k[y];  //累加点权和 
			maxs[cnt]=std::max(maxs[cnt],k[y]);  //更新最大值 
		}while(x!=y);  //do_while是个人习惯 
	}
}
```

缩点完毕后，显然我们需要重新建图。对于每一条边，如果其连接的两点处在不同的强联通分量中，就在它们的强联通分量之间连一条边。

```cpp
for(re i=1;i<=m;i++)
{
	re x=a[i],y=b[i];
	if(qlt[x]!=qlt[y])  //如果两点处在不同的强联通分量中 
	{
		e[qlt[x]].push_back(qlt[y]);  //连边 
		in[qlt[y]]++;  //你们或许会问我为什么要统计入度 
	}
}
```

图建好了，那么进入正题：

### 1. ?pts：

~~以下内容及其迷惑。~~

要统计最大点权和，和这条路径上的最大权值最大。于是我们很容易地想到**二分答案**。

为什么这样想？显然，对于最大点权和的最大可能答案，我们是可以求得的，~~所有点权和相加嘛~~~

最大点权呢？~~for循环里求max嘛~~~

如果你照着这样极其优秀的方法做下去，你可以获得 ``100%2`` 分的好成绩。

~~其实这一段是在搞艺术。~~

### 2. 20pts：

使用 $ N $ 次 SPFA 求最长路。在进行松弛操作时记录前驱存路径，即可求出这条路径上的最大点权。

设有一条边，从 $ a $ 连到 $ b $，将 $ sum_b $ 作为边权，但要注意，最后的点权和还要加上起点的点权。

但这样的方法有以下几个非常严重的问题：

- 很显然，太慢了。时间复杂度可以给你卡到 $ O(n^2\cdot m) $。由于 $n∈(0,2e5], m∈(0,5e5] $，就算只是求一遍都要T。这也启发了我们不能使用最短（长）路求解。

- 由于只能存一条最短路的路径，所以无法解决有多条路径都是最大的情况。

直接 PASS 掉。

### 3.100pts：

摆在我们面前的似乎只有一个方法了。那就是被万人厌恶的**Dynamic Programming**。

我们开两个数组：$ dpsum_i $ 表示走到第 $ i $ 个点时的最大点权和；$ dpmax_i $ 表示走到第 $ i $ 个点时的最大点权。

假设有一点 $ x $，可以走到一点 $ y $。显然，如果此时 $ dpsum_x + sum_y < dpsum_y $，我们是不会走上 $ y $ 这个点的，因此，不需要更新 $ dpmax $ 数组。

当 $ dpsum_x + sum_y > dpsum_y $ 时，我们要让这个点纳入路径中，即：

```cpp
if(dp_sum[x]+sum[y]>dp_sum[y])
{
	dp_sum[y]=dp_sum[x]+sum[y];
	dp_max[y]=std::max(dp_max[x],maxs[y]);
}
```

当 $ dpsum_x + sum_y = dpsum_y $ 时，我们便不会将点 $ y $ 纳入路径中了。因此，不再与 $ maxs_y $ 进行比较。状态转移方程如下：

```cpp
else if(dp_sum[x]+sum[y]==dp_sum[y])
	dp_max[y]=std::max(dp_max[y],dp_max[x]);
```

但这样直接 DP 真的就可以了吗？

这是一张有向图，并且这张图中的点不一定是两两相同的。很显然，原图（指缩点之后的图）是不满足动态规划的无后效性的。

怎么解决？来一手 **topo_sort** 不就完事儿了吗？

由于拓扑排序~~是个人都会写~~，我们直接来看代码：

```cpp
inline void topo_sort()
{
	queue <int> q;
	for(re i=1;i<=cnt;i++)
	{
		dp_sum[i]=sum[i];
		dp_max[i]=maxs[i];
	}//初始化，这条路径上至少有一个点 
	for(re i=1;i<=cnt;i++)
		if(in[i]==0)
			q.push(i);  //统计入度为零的点，加入队列 
	while(!q.empty())
	{
		re x=q.front();
		q.pop();  //取出队头 
		in[x]=-1;  //把这个点删了 
		for(re i=0;i<e[x].size();i++)  //枚举每一个连接的点 
		{
			re y=e[x][i];  //优美的vector 
			if(dp_sum[x]+sum[y]>dp_sum[y])
			{
				dp_sum[y]=dp_sum[x]+sum[y];
				dp_max[y]=std::max(dp_max[x],maxs[y]);
			}
			else if(dp_sum[x]+sum[y]==dp_sum[y])
				dp_max[y]=std::max(dp_max[y],dp_max[x]);  //上面讲的dp 
			in[y]--;  //因为把x点删了，所以就少了一个点连向y，因此in[y]-- 
			if(in[y]==0)
				q.push(y);  //如果点y入度为0，进队 
		}
	}
}
```

**共创和谐洛谷，远离抄袭！**

~~难道这就是你不贴完整代码的借口~~~

码字不易，还请看官点赞！

---

## 作者：Priori_Incantatem (赞：2)

### 题目大意
给出一个有向图，每个点有一个权值，一条路径长度为改路径上所有点权之和  
要求求出一条路径，使得在满足路径最长的前提下，满足经过的点的权值最大值最大

其实这题也不算太难，就是多了一个路径最大点权 和 维护强联通分量中的最大点权  

$dis[],dist[]$ 分别维护最长路和最长路上的最大点权  
$c[],maxv[]$ 分别维护强联通分量内点权和和点权最大值
```cpp
#include<cstdio>
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<algorithm>
using namespace std;
const int Maxn=200000+10,inf=0x3f3f3f3f;
vector <int> e[Maxn],g[Maxn];
stack <int> s;
int dfn[Maxn],low[Maxn],f[Maxn];
int dis[Maxn],dist[Maxn],ind[Maxn];
int maxv[Maxn],a[Maxn],c[Maxn];
bool vis[Maxn];
int n,m,timecnt,ans,ma;
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0' && ch<='9')s=(s<<1)+(s<<3)+(ch^48),ch=getchar();
	return s*w;
}
void tarjan(int x)
{
	dfn[x]=low[x]=++timecnt;
	vis[x]=1,s.push(x);
	for(int i=0;i<e[x].size();++i)
	{
		int y=e[x][i];
		if(!dfn[y])
		{
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(vis[y])low[x]=min(low[x],low[y]);
	}
	if(dfn[x]==low[x])
	{
		while(s.size())
		{
			int y=s.top();
			s.pop();
			vis[y]=0,f[y]=x;
			maxv[x]=max(maxv[x],a[y]);
			c[x]+=a[y];
			if(x==y)break;
		}
	}
}
void topo()
{
	queue <int> q;
	fill(dis+1,dis+1+n,-inf);
	fill(dist+1,dist+1+n,-inf);
	for(int i=1;i<=n;++i)
	if(f[i]==i && !ind[i])
	dis[i]=c[i],dist[i]=maxv[i],q.push(i);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=0;i<g[x].size();++i)
		{
			int y=g[x][i];
			if(!ind[y])continue;
			ind[y]--;
			bool tmpflag=(dis[y]==dis[x]+c[y] && dist[y]<max(dist[x],maxv[y]));
			if(dis[y]<dis[x]+c[y] || tmpflag)
			dis[y]=dis[x]+c[y],dist[y]=max(dist[x],maxv[y]);
			if(!ind[y])q.push(y);
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	n=read(),m=read();
	for(int i=1;i<=n;++i)
	a[i]=read();
	for(int i=1;i<=m;++i)
	{
		int x=read(),y=read();
		e[x].push_back(y);
	}
	for(int i=1;i<=n;++i)
	if(!dfn[i])tarjan(i);
	
	for(int i=1;i<=n;++i)
	{
		for(int j=0;j<e[i].size();++j)
		{
			int x=i,y=e[i][j];
			if(f[x]==f[y])continue;
			g[f[x]].push_back(f[y]);
			ind[f[y]]++;
		}
	}
	topo();
	
	for(int i=1;i<=n;++i)
	if(dis[i]>ans)ans=dis[i],ma=dist[i];
	printf("%d %d\n",ans,ma);
	
	return 0;
}
```

---

## 作者：qwerta (赞：2)

tarjan缩点+DAGdp

题目大意： **给定有向图及点权，求最长的一条路径(可重复经过点)上的点权和**

看了数据范围之后选择了非常暴力的解法，688ms

```
首先用tarjan缩点  缩点的同时记录每个强联通分量内部的点权和sum[i] 以及最大值mac[i]

然后重新建图 以拓扑序dp
```

转移方程：

```
//f[x][0]为以x为终点最大的点权和 f[x][1]为此时点权的最大值

if(f[x][0]>f[temp][0]){f[temp][0]=f[x][0];f[temp][1]=f[x][1];}

else if(f[x][0]==f[temp][0]){f[temp][1]=max(f[temp][1],f[x][1]);}
```

然后对于每一个点 在它的入度减到0之后再综合之前求的sum[i]和mac[i]

~~双倍经验指路：[P3387 【模板】缩点](https://www.luogu.org/problemnew/show/P3387)~~

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
inline int read()//快读
{
    char ch=getchar();
    int s=1,x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')s=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-48;ch=getchar();}
    return s*x;
}
//读入原图 ↓ 
int n,m;
int k[200007];//点权
struct emm{
    int to,next;
}a[500007];
int h[200007];//存原图
int tot=0;
inline void add(int x,int y)//原图加边
{
    a[++tot].next=h[x];
    h[x]=tot;
    a[tot].to=y;
    return;
}
inline void scan()//输入
{
    n=read(),m=read();
    for(register int i=1;i<=n;++i)
    k[i]=read();
    for(register int i=1;i<=m;++i)
    {
        int x=read(),y=read();
        add(x,y);//加边
    }
    return;
}
//tarjan缩点 ↓ 
int dfn[200007],low[200007],col[200007],stack[200007];
bool instack[200007];
int sum[200007],mac[200007];//sum记录强联通分量点权和 mac记录分量内最大的点权
int tos=0,tim=0,color=0;//tos记录stack的top tim时间戳 color颜色数
inline int min(int qwq,int qaq){return qwq<qaq?qwq:qaq;}//自己动手丰衣足食
void tarjan(int x)
{
    dfn[x]=low[x]=++tim;
    stack[++tos]=x;
    instack[x]=1;
    for(register int i=h[x];i;i=a[i].next)
    {
        int temp=a[i].to;//temp记录前趋
        if(!low[temp]){tarjan(temp);low[x]=min(low[x],low[temp]);}
        else if(instack[temp]){low[x]=min(low[x],dfn[temp]);}
    }
    if(dfn[x]==low[x])
    {
        color++;
        int j;
        do{j=stack[tos--];instack[j]=0;col[j]=color;
        sum[color]+=k[j];mac[color]=max(mac[color],k[j]);//计算第color个分量的sum和mac
        }while(j!=x);
    }
    return;
}
//建新图 ↓ 
struct ahh{
    int to,next;
}b[500007];
int hh[200007],rd[200007];//rd入度
inline void addd(int x,int y)//加新边
{
    b[++tot].next=hh[x];
    hh[x]=tot;
    b[tot].to=y;
    return;
}
inline void predo()//预处理
{
    for(register int i=1;i<=n;++i)
    if(!low[i])tarjan(i);
    tot=0;//重复利用tot
    for(register int j=1;j<=n;++j)
    for(register int i=h[j];i;i=a[i].next)//遍历原图的每条边
    if(col[j]!=col[a[i].to])//若不在同一个强联通分量里
    {
        addd(col[j],col[a[i].to]);//加边
        rd[col[a[i].to]]++;//temp的入度++
    }
    return;
}
//DAGdp ↓
int f[200007][2];//dp用
queue<int>q;//懒人的队列
inline void dp()
{
    for(register int i=1;i<=color;++i)
    if(!rd[i]){q.push(i);}//把入度为0的点放入队列
    while(!q.empty())
    {
        int x=q.front();q.pop();
        f[x][0]+=sum[x],f[x][1]=max(f[x][1],mac[x]);//加上本分量的sum和mac
        for(register int i=hh[x];i;i=b[i].next)//在新图里找
        {
            int temp=b[i].to;
            rd[temp]--;//前趋--
            if(!rd[temp])q.push(temp);//rd==0则push
            if(f[x][0]>f[temp][0]){f[temp][0]=f[x][0];f[temp][1]=f[x][1];}
            else if(f[x][0]==f[temp][0]){f[temp][1]=max(f[temp][1],f[x][1]);}//转移
        }
    }
    int summ=0,maxx=0;//summ记录最大的点权和 maxx记录此时的最大点权
    for(register int i=1;i<=color;++i)
    if(f[i][0]>summ){summ=f[i][0],maxx=f[i][1];}
    else if(f[i][0]==summ){maxx=max(maxx,f[i][1]);}//类似的转移
    cout<<summ<<" "<<maxx<<endl;//输出
    return;
}
//主程序 ↓ 
int main()
{
    scan();
    predo();
    dp();
    return 0;
}
```
~~标准的蓝题~~

---

## 作者：翼德天尊 (赞：1)

**一道缩点强连通分量的模板题 ~~（我是不会告诉你我调了半天的）~~**。

## Step 0 前置知识

关于缩点以及 $tarjan$ 算法请移步[P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)，另给出[$\color{red}\text{好文章}$](https://blog.csdn.net/hurmishine/article/details/75248876)一篇供各位参考。

这里也简述一下吧：缩点的原理就是将图上的每个强连通分量缩成点，然后建立一张新图，使得新图为 $DAG$。这样我们就可以在有环图上进行动归、拓扑排序等操作。主要用于一个环上可以随便走看成一个整体的情况。

## Step 1 题意简述

给出一个有向有环图，需要求出一条路径，使得该路径在总权值尽可能短的情况下，最大点的权值尽可能大。求最优总权值以及最大权值。

因为每个点是可以走多次的，并且单点权值为正数，可以想到一次选一个环肯定是最优的，所以很自然地就想到将每个强连通分量缩成点然后在新图上进行拓扑和动归，算出答案。

## Step 2 分层解题

### 1. 输入、准备部分

拿到一个图论题，我们显然需要将数据读入并建造图。我选择的是链式前向星建图。

```
struct node{//结构体储存
	int from,to,next;
	node (int from=0,int to=0,int next=0)
		:from(from),to(to),next(next){}
}e[M];

void adde(int u,int v){//建边
	e[++tot]=node(u,v,head[u]);
	head[u]=tot;
}

//主函数内
n=read(),m=read();
for (int i=1;i<=n;i++) s[i]=read();
for (int i=1;i<=m;i++){
	int u=read(),v=read();
	adde(u,v); 
}
```

### 2. ※$tarjan$部分

$tarjan$ 的作用就是将各个强连通分量找出来，以及处理各个强连通分量的最大值和总权值，使得我们可以构建新图，方便日后拓扑排序。

```cpp
void tarjan(int u){
	dfn[u]=low[u]=++t,maxn[u]=h[u]=s[u];
	//初始化第一次的遍历序以及子节点最小遍历序，以及该环的最大值和总权值。
	vis[u]=1,st[++stot]=u;//放入栈中并标记
	for (int i=head[u];i;i=e[i].next){//遍历子节点
		int v=e[i].to;
		if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		//没有走过就走子节点并更新子节点的最小遍历序
		else if (vis[v]) low[u]=min(low[u],dfn[v]);
		//走过就直接更新
	}
	if (dfn[u]==low[u]){//如果子节点的最小遍历序与该节点的遍历序相同，表示这是一个强连通分量的根节点
		int in;
		while (in=st[stot--]){//不断取出栈中元素
			id[in]=u,vis[in]=0;//标记环的根
			if (u==in) break;//如果到根节点了就退出
			s[u]+=s[in];//处理总权值
			maxn[u]=max(maxn[u],s[in]);//处理最大权值	
		} 
	}
}

//主函数内
for (int i=1;i<=n;i++){
	if (!dfn[i]) tarjan(i);//没有遍历到就tarjan
}
```

### 3.建造新图

$tarjan$ 找到各个强连通分量之后，我们就可以建造一个新图。因为我们将所有的环都缩成了一个点，所以新图就保证是一个 $DAG$，可以在上面进行拓扑了。

```cpp
for (int i=1;i<=m;i++){//对于每条边
	int u=id[e[i].from],v=id[e[i].to];//找出它们的节点所在强连通分量的根节点
	if (u!=v){//如果不相等
		ne[++ntot]=node(u,v,nhead[u]);//新图加边
		nhead[u]=ntot;
		++in[v],++out[u];//记录出度、入度
	}
}
for (int i=1;i<=n;i++) if (!out[i]) jl[++jtot]=i;
//记录一下出度为0的点，以后计算最终答案的时候可以用到
```

### 4.拓扑排序

一切的一切都进行完之后，我们就可以进行拓扑排序加简单动规转移了。我们利用 $DAG$ 的优势，很容易就可以动规出最终答案了。

```cpp
void solve(){//拓扑排序
	queue<int> q;
	for (int i=1;i<=n;i++){
		if (id[i]==i&&!in[i]) dis[i]=s[i],maxnn[i]=maxn[i],q.push(i);
		//如果根节点就是自身并且入度为0就放入队列并初始化该点动规状态
	}
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (int i=nhead[u];i;i=ne[i].next){
			int v=ne[i].to;
			if (dis[u]+s[v]>dis[v])
				dis[v]=dis[u]+s[v],maxnn[v]=max(maxn[v],maxnn[u]);
			//如果总权值大就转移总权值和最大值
			else if (dis[u]+s[v]==dis[v])
				maxnn[v]=max(maxnn[u],maxn[v]);
			//如果总权值一样大，就转移最大值。
			--in[v];//减去目标入度
			if (!in[v]) q.push(v);//为0继续放入队列
		}
	}
}
```

### 5.处理最终答案并输出

我们现在已经拓扑完毕，只需要对每一个开始时出度为 $0$ 的点取一个最优解即可。最终输出结果。

```cpp
for (int i=1;i<=jtot;i++){//处理最终答案
	int x=jl[i];
	if (dis[x]>ans1) ans1=dis[x],ans2=maxnn[x];
	else if (dis[x]==ans1&&maxnn[x]>ans2) ans2=maxnn[x]; 
}
printf("%d %d\n",ans1,ans2);//输出
```

## Step 3 总结

再总结一下本题的流程以及思路吧。

首先点权一定为正数，所以就造就了一个强联通分量上的点一定都选了就是最优。所以就考虑用 $tarjan$ 缩点建造新图（或者说因为拓扑必须需要图为 $DAG$）。又因为我们需要算出路径最优解，所以我们就可以考虑拓扑排序+动归来算出最优解。

注意转移的时候不要搞错方程以及各个数组之间不要搞混。

## Step 4 完整代码无注释版

```cpp
#include <bits/stdc++.h>
using namespace std;
#define N 200005
#define M 500005
int n,m,s[N],dfn[N],low[N],st[N],stot,id[N],t;
int nhead[N],ntot,h[N],in[N],out[N],jl[N],jtot;
int head[N],tot,dis[N],maxn[N],maxnn[N],ans1,ans2;
bool vis[N]; 
struct node{
	int from,to,next;
	node (int from=0,int to=0,int next=0)
		:from(from),to(to),next(next){}
}e[M],ne[M];
int read(){
	int w=0,f=1;
	char c=getchar();
	while (c>'9'||c<'0'){
		if (c=='-') f=-1;
		c=getchar();
	}
	while (c>='0'&&c<='9'){
		w=(w<<3)+(w<<1)+(c^48);
		c=getchar();
	}
	return w*f;
}
void adde(int u,int v){
	e[++tot]=node(u,v,head[u]);
	head[u]=tot;
}
void tarjan(int u){
	dfn[u]=low[u]=++t,maxn[u]=h[u]=s[u];
	vis[u]=1,st[++stot]=u;
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].to;
		if (!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if (vis[v]) low[u]=min(low[u],dfn[v]);
	}
	if (dfn[u]==low[u]){
		int in;
		while (in=st[stot--]){
			id[in]=u,vis[in]=0;
			if (u==in) break;
			s[u]+=s[in];
			maxn[u]=max(maxn[u],s[in]);	
		} 
	}
}
void solve(){
	queue<int> q;
	for (int i=1;i<=n;i++){
		if (id[i]==i&&!in[i]) dis[i]=s[i],maxnn[i]=maxn[i],q.push(i);
	}
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (int i=nhead[u];i;i=ne[i].next){
			int v=ne[i].to;
			if (dis[u]+s[v]>dis[v])
				dis[v]=dis[u]+s[v],maxnn[v]=max(maxn[v],maxnn[u]);
			else if (dis[u]+s[v]==dis[v])
				maxnn[v]=max(maxnn[u],maxn[v]);
			--in[v];
			if (!in[v]) q.push(v);
		}
	}
}
int main(){
	n=read(),m=read();
	for (int i=1;i<=n;i++){
		s[i]=read();
	}
	for (int i=1;i<=m;i++){
		int u=read(),v=read();
		adde(u,v); 
	}
	for (int i=1;i<=n;i++){
		if (!dfn[i]) tarjan(i);
	}
	for (int i=1;i<=m;i++){
		int u=id[e[i].from],v=id[e[i].to];
		if (u!=v){
			ne[++ntot]=node(u,v,nhead[u]);
			nhead[u]=ntot;
			++in[v],++out[u];
		}
	}
	for (int i=1;i<=n;i++) if (!out[i]) jl[++jtot]=i;
	solve();
	for (int i=1;i<=jtot;i++){
		int x=jl[i];
		if (dis[x]>ans1) ans1=dis[x],ans2=maxnn[x];
		else if (dis[x]==ans1&&maxnn[x]>ans2) ans2=maxnn[x]; 
	}
	printf("%d %d\n",ans1,ans2);
	return 0;
}
```

完结撒花！如果觉得讲得还不错，欢迎点赞哦！谢谢啦！如果还有什么疑问，就在评论区问我哦！我会及时回复的！

---

## 作者：RedreamMer (赞：1)

### [$\texttt{P4742}$](https://www.luogu.com.cn/problem/P4742)

算法：$tarjan$ 求 $scc$ +缩点，$toposort$

### $\texttt{Meaning}$

给你 $n$ 个点以及点的权值，和 $m$ 条有向边，你要从一个点出发，可以经过一些点多次。请求出一条路径，使它的路径点权值和最大，若有多条权值相等的路径，使它的路径上的最大点权最大，并输出这两个数。

### $\texttt{Solution}$

1. 强联通分量缩点，先用 $tarjan$ 算法求出所有的 $scc$ ，并将它们缩点，保留每个 $scc$ 点权和以及最大点权，再将每个连通分量连接上相应的有向边，显然，最终的出来的图应该是一个无环图，可以进行 $toposort$ 。

2. 进行 $toposort$ ，求出以每个 $scc$ 为路径结尾的最优答案，并且要注意一些 $dp$ 转移的细节。

总体来说本题思路很清晰，没有什么难点，但是码量有点大，细节较多。

### $\texttt{Code}$

```cpp
#include<bits/stdc++.h>
using namespace std;

//#define int long long
const int N=2e5+10;
const int M=5e5+10;

int a,b,dfn[N],low[N],id,s1[N],st[N],r,num,x,y,ans,dp[N][2],c[N],in[N];//num为scc的个数，dp为toposort的状态转移数组，第一维为最大的路径点权和，第二维为路径上的的最大点权，c为原每个点所属的scc，in为每个缩点的入度
bool vis[N];
vector<int> p1[N],p2[N];//p1为一开始的有向图的边，p2为后来缩点后的有向图的边，这里不太适合用前向星存图，因为建的变量和函数太多有点麻烦
struct node {
	int mx,sum;
} scc[N];

inline void tarjan(int n) {
	dfn[n]=low[n]=++id;
	vis[n]=1;
	st[++r]=n;
	for(int i=0; i<p1[n].size(); i++) {
		int v=p1[n][i];
		if(!dfn[v]) {
			tarjan(v);
			low[n]=min(low[n],low[v]);
		} else if(vis[v]) low[n]=min(low[n],dfn[v]);
	}
	if(dfn[n]!=low[n]) return;
	num++;
	int m=-1;
	while(m!=n) {
		m=st[r--];
		c[m]=num;
		vis[m]=0;
		scc[num].mx=max(scc[num].mx,s1[m]);
		scc[num].sum+=s1[m];
	}
//	cout<<scc[num].sum<<endl;
}
inline void ddp() {
	queue<int> sq;
	for(int i=1; i<=num; i++) {
		dp[i][0]=scc[i].sum;
		dp[i][1]=scc[i].mx;
	}
	for(int i=1; i<=num; i++) if(!in[i]) sq.push(i);
	while(!sq.empty()) {
		int u=sq.front();
		sq.pop();
		for(int i=0; i<p2[u].size(); i++) {
			int v=p2[u][i];
			in[v]--;
			if(!in[v]) sq.push(v);
			if(dp[v][0]<dp[u][0]+scc[v].sum) {
				dp[v][0]=dp[u][0]+scc[v].sum;
				dp[v][1]=max(dp[u][1],scc[v].mx);//这里是细节，与下面的转移有点区别，不考虑将当前dp[v][1]也拉入进行去max，小心这个坑
			}
			if(dp[v][0]==dp[u][0]+scc[v].sum) dp[v][1]=max(dp[v][1],dp[u][1]);
		}
	}
}
signed main() {
//	freopen("in.in","r",stdin);
	scanf("%d%d",&a,&b);
	for(int i=1; i<=a; i++) scanf("%d",&s1[i]);
	for(int i=1; i<=b; i++) {
		scanf("%d%d",&x,&y);
		p1[x].push_back(y);
	}
	for(int i=1; i<=a; i++) if(!dfn[i]) tarjan(i);
	for(int i=1; i<=a; i++) for(int j=0; j<p1[i].size(); j++) {
			int u=i,v=p1[i][j];
			if(c[u]==c[v]) continue;
			p2[c[u]].push_back(c[v]);
			in[c[v]]++;
		}
	ddp();//toposort
	ans=1;
	for(int i=2; i<=num; i++) if(dp[i][0]>dp[ans][0]||dp[i][0]==dp[ans][0]&&dp[i][1]>dp[ans][1]) ans=i;
	printf("%d %d",dp[ans][0],dp[ans][1]);
	return 0;
}
```

### [$\color{blue}\texttt{My Blog}$](https://www.luogu.com.cn/blog/184549/)

---

## 作者：XG_Zepto (赞：1)

### 思路

既然可以“到达一支风筝多次”，也就是**可以走回头路**，那么我们可以直接 Tarjan 缩点，在新的 DAG 上以**拓扑排序**的方法 DP。

### 代码
~~比官方短了不少，凑合着看吧~~
同时安利博客：[【Luogu Wind Festival!】解题报告](https://www.xgzepto.cn/post/luogu-wind-festival)

```cpp
#include <bits/stdc++.h>
#define maxn 500010
using namespace std;
struct Edge{
    int from,to,next;
    Edge(int a=0,int b=0,int c=0){
        from=a,to=b,next=c;
    }
}l[maxn];
struct new_Edge{
    int to,next;
    new_Edge(int a=0,int b=0){
        to=a,next=b;
    }
}e[maxn];
int head[maxn],cnt,n,cnt_n,top,m,ind,dfn[maxn],low[maxn],in[maxn],pin[maxn];
int a[maxn],id[maxn],num,siz[maxn],new_head[maxn],sta[maxn],pma[maxn],vis[maxn];
int dp[maxn][2];
void Add(int x,int y){
    l[++cnt]=Edge(x,y,head[x]);
    head[x]=cnt;
}
void new_Add(int x,int y){
    e[++cnt_n]=new_Edge(y,new_head[x]);
    new_head[x]=cnt_n;
}
void dfs(int u){
    low[u]=dfn[u]=++ind;
    in[u]=1,sta[++top]=u;
    for (int i=head[u];i;i=l[i].next){
        int v=l[i].to;
        if (!dfn[v]) dfs(v),low[u]=min(low[u],low[v]);
        else if (in[v]) low[u]=min(low[u],low[v]);
    }
    if (low[u]==dfn[u]){
        int j=-1;num++;
        while(j!=u){
            j=sta[top--];
            id[j]=num;
            siz[num]+=a[j];
            in[j]=0;
            pma[num]=max(pma[num],a[j]);
        }
    } 
}
void tsort(){
    queue<int>q;
    for (int i=1;i<=n;i++) dp[i][0]=siz[i],dp[i][1]=pma[i];
    //dp[i][0] 维护的是走到 i 的点权和，同时 dp[i][1] 维护路径上的点权最大值。
    for (int i=1;i<=n;i++) if (!pin[i]) q.push(i);
    while(!q.empty()){
        int hq=q.front();q.pop();
        for (int i=new_head[hq];i;i=e[i].next){
            int v=e[i].to;
            if (dp[hq][0]+siz[v]>dp[v][0]){
                dp[v][0]=dp[hq][0]+siz[v];
                dp[v][1]=max(dp[hq][1],pma[v]);//注意这句和下面更新方法的差异
            }
            if (dp[hq][0]+siz[v]==dp[v][0])
                dp[v][1]=max(dp[v][1],dp[hq][1]);
            pin[v]--;if (pin[v]<=0) q.push(v);
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin>>n>>m;
    for (int i=1;i<=n;i++)
        cin>>a[i];
    for (int i=1,t1,t2;i<=m;i++){
        cin>>t1>>t2;Add(t1,t2);
    }
    for (int i=1;i<=n;i++)
        if (!dfn[i]) dfs(i);
    for (int i=1;i<=m;i++)
        if (id[l[i].from]!=id[l[i].to]){
            new_Add(id[l[i].from],id[l[i].to]);
            pin[id[l[i].to]]++;
        }
    int res=1;tsort();
    for (int i=2;i<=num;i++)
        if (dp[i][0]>dp[res][0]||dp[i][0]==dp[res][0]&&dp[i][1]>=dp[res][1]) res=i;
    cout<<dp[res][0]<<" "<<dp[res][1]<<endl;
    return 0;
}
```

---

## 作者：Kalium (赞：0)

# P4742 【[Wind Festival]Running In The Sky】题解

反正我做的很烦人，不知道你们怎样？

进入正题

## 题意：

题意还是很好理解的，就是在一张图（可能有环），叫你求经过点权的最大值和这些路（但都是点权最大的路）中的最大点权的值

$P.S$：如果有环，经过的点权只算第一遍走过的

## 思路：

如果光看第一问，还是很好做的

有环，我们第一时间想到的先用缩点将其变为一张 $DAG$，然后在缩点时用 $sum_k$ 记录下第 $k$ 个强连通分量的总的点权，然后将其进行 $topsort$，用 $f_i$ 表示在第 $i$ 个点的点权之和，那么每回只需 $max(f_u,f_v)$ 即可，最后将每个点的答案遍历一遍求出最大值即可

其实这就是[P3387缩点模板](https://www.luogu.com.cn/problem/P3387)了

那么我们看看第二问，叫你求经过最大点权值

其实仔细想想也不难

在缩点过程中，先将每个强连通分量中的最大点权存入 $maxn_k$ （$k$ 为强连通分量个数）中，再用 $fmaxn_i$ 表示在第 $i$ 个点的时候的点权最大值。然而在拓扑的过程中我们要分 $3$ 种情况

### 1. $f_v < f_u + sum_v$ 

此时我们需要更新路程（~~废话~~），那么路线更新了，点权也要更新，那么 $ fmaxn_v$ 即为 $max(maxn_v, fmaxn_u)$ 转移而来

### 2. $f_v == f_u + sum_v$ 

此时就不需要更新了（~~废话~~），但我们需要转移最大点权，要么就是 $u$ 这个点的点权大，要么是 $v$ 这个点点权更大，所以 $fmaxn_v$ 即为$max(fmaxn_u,fmaxn_v)$转移而来

### 2. $f_v > f_u + sum_v$

这个时候路径没得更新，因为不是最大的，而不是最大的，点权也就无法更新了

接下来我们输出的时候，先是遍历一遍存入 $ans1$ 代表经过点权的最大值和

但是接下来，我们只有当 $f_i == ans1 $ 的时候，才能更新最大点权和路径的经过最大点的点权值 $ans2$

接下来就是完美输出

## 代码：

# CODE

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

const int N = 2e5 + 7, M = 5e5 + 7;

using namespace std;

int n, m, u[M], v[M], w[N];

struct Edge {
	int next, to;
} edge[M];

int head[N], cnt;

int dfn[N], low[N], ti;

int stk[N], instk;

bool flag[N];

int belong[N], sum[N], k, in[N], maxn[N];

int f[N], fmaxn[N];

inline int read() {
	int n = 0, f = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-')
			f = -f;
		c = getchar();
	} 
	while (c >= '0' && c <= '9') {
		n = (n << 3) + (n << 1) + (c ^ '0');
		c = getchar();
	} 
	return n * f;
}

inline void ins(int u, int v) {
	edge[++ cnt].to = v;
	edge[cnt].next = head[u];
	head[u] = cnt;
}

inline int mina(int a, int b) {
	if (a < b)
		return a;
	return b;
}

inline int maxa(int a, int b) {
	if (a > b)
		return a;
	return b;
}

void tarjan(int u) {
	dfn[u] = low[u] = ++ ti;
	stk[++ instk] = u;
	flag[u] = 1;
	for (int i = head[u]; ~i; i = edge[i].next) {
		int v = edge[i].to;
		if (! dfn[v]) {
			tarjan(v);
			low[u] = mina(low[u], low[v]);
		} else if (flag[v])
			low[u] = mina(low[u], dfn[v]);
	}
	int cur;
	if (dfn[u] == low[u]) {
		k ++;
		do {
			cur = stk[instk --];
			flag[cur] = 0;
			belong[cur] = k;
			sum[k] += w[cur];
			maxn[k] = maxa(maxn[k], w[cur]);
		} while (cur != u); 
	}
}

inline void topsort() {
	queue <int> q;
	for (int i = 1; i <= k; i ++) {
		if (! in[i])
			q.push(i);
		f[i] = sum[i];
		fmaxn[i] = maxn[i];
	}
	while (! q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; ~i; i = edge[i].next) {
			int v = edge[i].to;
			if (f[v] < f[u] + sum[v]) {
				f[v] = f[u] + sum[v];
				fmaxn[v] = maxa(maxn[v], fmaxn[u]); 
			} else if (f[v] == f[u] + sum[v])
				fmaxn[v] = maxa(fmaxn[u], fmaxn[v]);
			in[v] --;
			if (! in[v])
				q.push(v);
		}
	}
	return ;
}

int main() {
	memset(head, -1, sizeof(head));
	n = read(), m = read();
	for (int i = 1; i <= n; i ++) 
		w[i] = read();
	for (int i = 1; i <= m; i ++) {
		u[i] = read(), v[i] = read();
		ins(u[i], v[i]);
	}
	for (int i = 1; i <= n; i ++) {
		if (! dfn[i])
			tarjan(i);
	}
	memset(edge, 0, sizeof(edge));
	memset(head, -1, sizeof(head));
	cnt = 0;
	for (int i = 1; i <= m; i ++) {
		if (belong[u[i]] != belong[v[i]]) {
			ins(belong[u[i]], belong[v[i]]);
			in[belong[v[i]]] ++;
		}
	}
	topsort();
	int ans1 = 0, ans2 = 0;
	for (int i = 1; i <= n; i ++)
		ans1 = maxa(ans1, f[i]);
	for (int i = 1; i <= n; i ++) {
		if (f[i] == ans1)
			ans2 = maxa(ans2, fmaxn[i]);
	}
	cout << ans1 << " " << ans2 << endl;
	return 0;
} 
```


---

## 作者：Link_Space (赞：0)

题中的有向图，可以重复经过一个点等等条件可以很容易地看出这道题需要用到tarjan缩点，缩点之后又应该怎么做呢？题目需要求一条路径使得这条路径上的光亮最大，同时还要求路径上的最大单点光亮，那我们就可以将缩完点之后的图重新建一遍，然后用拓扑排序来求出需要求的值。

思路就是这样，接下来会在代码里详细讲解

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
int Light[1000000];
int head[1000000];
int ver[1000000];
int nxt[1000000];
int cnt;
int dfn[1000000];
int low[1000000];
int Link[1000000];
int top;
int idx;
int cnsta;
int belong[1000000];
int siz[1000000];
bool aim[1000000];
int hea[1000000];
int val[1000000];
int net[1000000];
int Count[1000000];
int in[1000000];
int dp[1000000][2];
int tot;
void add(int x,int y)
{
    nxt[++cnt]=head[x];
    head[x] = cnt;
    ver[cnt] = y;
}
void add2(int x,int y)
{
    net[++tot]=hea[x];
    hea[x] = tot;
    val[tot] = y;
}
void tarjan(int x)//基础缩点
{
    dfn[x] = low[x] = ++idx;
    aim[x] = 1;
    Link[++top] = x;
    for (int i = head[x]; i;i=nxt[i])
    {
        int v0=ver[i];
        if(!dfn[v0])
        {
            tarjan(v0);
            low[x] = min(low[x], low[v0]) ;
        }
        else if(aim[v0])
        {
            low[x] = min(low[x], dfn[v0]);
        }
    }
    if(dfn[x]==low[x])
    {
        int w;
        cnsta++;
        do{
            w=Link[top--];
            Count[cnsta]=max(Count[cnsta],Light[w]);//存的是这个缩完之后的大点的最大单点亮度
            siz[cnsta]+=Light[w];//siz存的是缩完之后的大点的总亮度
            aim[w] = 0;
            belong[w] = cnsta;
        } while (w != x);
    }
}
void Topo()
{
    queue<int> q;
    for (int i = 1; i <= cnsta;i++)
    {
        dp[i][0]=siz[i];//dp[i][0]的里面存走到i这个点的总光亮最大是多少
        dp[i][1] = Count[i];.//dp[i][0]存走到这个点的总光亮最大的路径上的最大单点光亮是多少
        if(!in[i])
            q.push(i);
    }
    while(!q.empty())
    {
        int temp = q.front();
        q.pop();
        for(int i=hea[temp];i;i=net[i])
        {
            int v0 = val[i];
            in[v0]--;
            if(!in[v0])
                q.push(v0);
            if(dp[v0][0]<dp[temp][0]+siz[v0])//如果遇到更优的路径，则更换
            {
                dp[v0][0] = dp[temp][0] + siz[v0];
                dp[v0][1] = max(dp[temp][1], Count[v0]);
            }
            if(dp[v0][0]==dp[temp][0]+siz[v0])如果碰到相同光亮的路径，但是另一条路径的最大单点光亮更大，也要更新
                dp[v0][1] = max(dp[v0][1], dp[temp][1]);
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1;i<=n;i++)
    {
        scanf("%d", &Light[i]);
    }
    for(int i=1;i<=m;i++)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b);
    }
    for (int i = 1;i<=n;i++)
    {
        if(!dfn[i])
            tarjan(i);//基本缩点
    }
    for (int i = 1; i <= n;i++)
    {
        for (int j = head[i]; j;j=nxt[j])
        {
            int v0 = ver[j];
            if(belong[v0]!=belong[i])
            {
                add2(belong[i], belong[v0]);
                in[belong[v0]]++;//缩完点之后重新建图，标记入度方便拓扑
            }           
        }
    }
    Topo();//拓扑
    int maxn=-1;
    int ans=-1;
    for (int i = 1;i<=cnsta;i++)
    {
        if(dp[i][0]>ans)
        {
            ans=dp[i][0];
            maxn = dp[i][1];
        }
        else if(dp[i][0]==ans)
        {
            maxn = max(maxn, dp[i][1]);
        }//找出最大的那个即可
    }
    printf("%d %d", ans, maxn);
    return 0;
}
```


---

## 作者：那一条变阻器 (赞：0)

tarjan模板题

------------

这道题tarjan加记忆化搜索就行，记忆化搜索中，就可以完美解决最大值和最长路。直接讲比较抽象，上代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n , m , now , tot , ans1 , ans2;
int dfn[200010] , low[200010] , home[200010] , a[200010] , dis[200010] , vis[200010] , kp[200010];
int f[200010] , maxx[200010];
stack<int> s;
vector<int> e[200010];
vector<int> ne[200010];	//存重建的图 
void tarjan(int x){
	dfn[x] = low[x] = ++now;
	s.push(x);
	vis[x] = 1;
	for(int i = 0; i < e[x].size(); i++){
		int nx = e[x][i];
		if(!dfn[nx]){
			tarjan(nx);
			low[x] = min(low[x] , low[nx]);
		}else if(vis[nx]) low[x] = min(low[x] , dfn[nx]); 
	}
	if(dfn[x] == low[x]){
		tot++;
		while(!s.empty()){
			int top = s.top();
			s.pop();
			kp[tot] = max(kp[tot] , a[top]);	//统计下最大值 
			vis[top] = 0;
			dis[tot] += a[top];	//统计点的和 
			home[top] = tot;
			if(top == x) break;
		}
	}
}
void dfs(int x){
	if(f[x]) return;
	f[x] = dis[x];
	int ans = 0 , ansmax = 0;
	for(int i = 0; i < ne[x].size(); i++){
		int nx = ne[x][i];
		dfs(nx);
		if(f[nx] > ans){	//最长路优先，其次最大值 
			ans = f[nx];
			ansmax = maxx[nx];
		}else if(f[nx] == ans){
			if(maxx[nx] > ansmax) ansmax = maxx[nx];
		}
	}
	f[x] += ans;	//选择最长路 
	maxx[x] = max(ansmax , kp[x]);
}
int main(){
	cin >> n >> m;
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++){
		int x , y;
		cin >> x >> y;
		e[x].push_back(y);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= n; i++)
		for(int j = 0; j < e[i].size(); j++){	//重建 
			int nx = e[i][j];
			if(home[nx] != home[i]) ne[home[i]].push_back(home[nx]);
		}
	for(int i = 1; i <= tot; i++) dfs(i);	//记忆化搜索 
	for(int i = 1; i <= tot; i++)	//枚举答案 
		if(f[i] > ans1){
			ans1 = f[i];
			ans2 = maxx[i];
		}else if(f[i] == ans1){
			if(maxx[i] > ans2) ans2 = maxx[i];
		}
	cout << ans1 << " " << ans2;
	return 0;
}
```


---

## 作者：Minakami_Yuki (赞：0)

屑题卡我两天，这可能是我写过的最长的蓝题了。

# 题目链接

[P4742 [Wind Festival]Running In The Sky](<https://www.luogu.org/problemnew/show/P4742>)

# 题意简述

给你一张**有向图**，有点权，一个点的费用可被收取**当仅当第一次**经过该点，求出**最长路**和该路径上**点权最大值**。

# 解题思想

缩点没什么好说的，但是在缩点时我们维护**每个强连通分量**的**两个**信息：

- 点权之和`info[0][i]`
- 点权最大值`info[1][i]`

缩完点后建立新图，就不用多说了。

然后在**新图**上**拓扑排序**的同时**DP**，维护到每个点的最长路，同时**有依赖性地**更新点权最大值。

这个**有依赖性**就是难点。

我们考虑**独立DP极大值**，可以很轻易地被Hack掉，考虑一条路径，上面有**一个**点**权值极大**，其余的点权值**全为0**，再构造另一条路径，每个点的权值**仅**比上条路径**权值极大**点**小1**，这样我们DP出的结果很明显不在**最长路**上。

那要怎么做呢？

考虑**仅在最长路径转移的时候**转移**极大值的状态**，即**单独考虑**两条路**长度相等**的情况。

那么**拓扑排序时**就有**两种情况**：

- 一是**最长路**更新，这时需要更新最大点权，与**新加入的点的权值**进行对比。
- 二是发现**等长路径**，这是也需要更新最大点权，**但是**与**新加入点的状态**进行对比。

很好想通，发现等长路径时，我们需要将**原状态**与**整条路径上的点权**进行对比，这就是新加入点的状态了。

# 参考代码

写的比较工程化，所以很长。

```cpp
#include <cstdio>
#include <cctype>

namespace FastIO {
    inline int read() {
        char ch = getchar(); int r = 0, w = 1;
        while(!isdigit(ch)) {if(ch == '-') w = -1; ch = getchar();}
        while(isdigit(ch)) {r = r * 10 + ch - '0', ch = getchar();}
        return r * w;
    }
    void _write(int x) {
        if(x < 0) putchar('-'), x = -x;
        if(x > 9) _write(x / 10);
        putchar(x % 10 + '0');
    }
    inline void write(int x) {
        _write(x);
        putchar(' ');
    }
}

namespace Data {
    static const int N = 2e5 + 6;
    static const int M = 5e5 + 6;

    template <typename T> T max(T a, T b) {return a > b ? a : b;}
    template <typename T> T min(T a, T b) {return a < b ? a : b;}

    template <typename T>
    class queue {
        private:
            int head, tail;
            T q[N];
        public:
            queue() {head = tail = 0;}
            inline bool empty() {return head >= tail;}
            inline void push(T x) {q[++tail] = x;}
            inline void pop() {if(!empty()) head++;}
            inline T front() {return q[head + 1];}
    };
    
    template <typename T>
    class stack {
        private:
            int stop;
            T s[N];
        public:
            inline bool empty() {return stop == 0;}
            inline void push(T x) {s[++stop] = x;}
            inline void pop() {if(!empty()) stop--;}
            inline T top() {return s[stop];}
    };

    int n, m;
    int head[N], nxt[M], ver[M], k[N], cnt;
    
    int scc[N], low[N], dfn[N], info[2][N], dp[2][N], idx, tot;
    bool v[N];
    stack <int> s;

    int Head[N], Ver[M], Nxt[M], in[N], Cnt;
}

using namespace FastIO;
using namespace Data;

inline void add(int x, int y) {
    ver[++cnt] = y, nxt[cnt] = head[x], head[x] = cnt;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++idx;
    v[x] = 1;
    s.push(x);
    for(register int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(v[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }
    if(low[x] == dfn[x]) {
        tot++;
        while(s.top()) {
            int y = s.top();
            s.pop();
            v[y] = 0;
            scc[y] = tot;
            info[0][tot] += k[y];
            info[1][tot] = max(info[1][tot], k[y]);
            if(x == y) break;
        }
    }
}

inline void Add(int x, int y) {
    Ver[++Cnt] = y, Nxt[Cnt] = Head[x], Head[x] = Cnt, in[y]++;
}

inline void rebuild() {
    for(register int x = 1; x <= n; x++) {
        for(register int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if(scc[y] != scc[x]) Add(scc[x], scc[y]);
        }
    }
}

inline void TopSort() {
    queue <int> q;
    for(register int i = 1; i <= n; i++) {
        dp[0][i] = info[0][i];
        dp[1][i] = info[1][i];
        if(in[i] == 0) q.push(i);
    }
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        for(register int i = Head[x]; i; i = Nxt[i]) {
            int y = Ver[i];
            if(dp[0][y] < dp[0][x] + info[0][y]) {
                dp[0][y] = dp[0][x] + info[0][y];
                dp[1][y] = max(dp[1][x], info[1][y]);
            }
            else if(dp[0][y] == dp[0][x] + info[0][y]) {
                dp[1][y] = max(dp[1][y], dp[1][x]);
            }
            in[y]--;
            if(in[y] == 0) q.push(y);
        }
    }
}

int main() {
    n = read(), m = read();
    for(register int i = 1; i <= n; i++) {
        k[i] = read();
    }
    for(register int i = 1; i <= m; i++) {
        int x = read(), y = read();
        add(x, y);
    }
    for(register int i = 1; i <= n; i++) {
        if(!dfn[i]) tarjan(i);
    }
    rebuild();
    TopSort();
    int las = 1;
    for(register int i = 2; i <= tot; i++) {
        if(dp[0][i] > dp[0][las] || (dp[0][i] == dp[0][las] && dp[1][i] >= dp[1][las])) las = i;
    }
    write(dp[0][las]);
    write(dp[1][las]);
    return 0;
}
```


---

