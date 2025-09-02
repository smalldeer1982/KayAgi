# Pairs of Pairs

## 题目描述

You have a simple and connected undirected graph consisting of $ n $ nodes and $ m $ edges.

Consider any way to pair some subset of these $ n $ nodes such that no node is present in more than one pair.

This pairing is valid if for every pair of pairs, the induced subgraph containing all $ 4 $ nodes, two from each pair, has at most $ 2 $ edges (out of the $ 6 $ possible edges). More formally, for any two pairs, $ (a,b) $ and $ (c,d) $ , the induced subgraph with nodes $ \{a,b,c,d\} $ should have at most $ 2 $ edges.

Please note that the subgraph induced by a set of nodes contains nodes only from this set and edges which have both of its end points in this set.

Now, do one of the following:

- Find a simple path consisting of at least  $ \lceil \frac{n}{2}         \rceil $  nodes. Here, a path is called simple if it does not visit any node multiple times.
- Find a valid pairing in which at least  $ \lceil \frac{n}{2}         \rceil $  nodes are paired.

It can be shown that it is possible to find at least one of the two in every graph satisfying constraints from the statement.

## 说明/提示

The path outputted in the first case is the following.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1391E/f933cf6d6ef0e9cc1a0c63b340f55f3134190ad2.png)The pairing outputted in the second case is the following.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1391E/59890ffb6cdd4e16453459b36624cbb9160fba8e.png)Here is an invalid pairing for the same graph — the subgraph $ \{1,3,4,5\} $ has $ 3 $ edges.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1391E/b0223477332df3a149bead72097ac4f31989b184.png)Here is the pairing outputted in the third case.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1391E/0962af04db2adbef2cd739703b2984c1b740a073.png)It's valid because —

- The subgraph $ \{1,8,2,5\} $ has edges ( $ 1 $ , $ 2 $ ) and ( $ 1 $ , $ 5 $ ).
- The subgraph $ \{1,8,4,10\} $ has edges ( $ 1 $ , $ 4 $ ) and ( $ 4 $ , $ 10 $ ).
- The subgraph $ \{4,10,2,5\} $ has edges ( $ 2 $ , $ 4 $ ) and ( $ 4 $ , $ 10 $ ).

Here is the pairing outputted in the fourth case.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1391E/f8353fc6acdb818ed4a0a9898469caca904f4fdc.png)

## 样例 #1

### 输入

```
4
6 5
1 4
2 5
3 6
1 5
3 5
6 5
1 4
2 5
3 6
1 5
3 5
12 14
1 2
2 3
3 4
4 1
1 5
1 12
2 6
2 7
3 8
3 9
4 10
4 11
2 4
1 3
12 14
1 2
2 3
3 4
4 1
1 5
1 12
2 6
2 7
3 8
3 9
4 10
4 11
2 4
1 3```

### 输出

```
PATH
4 
1 5 3 6
PAIRING
2
1 6
2 4
PAIRING
3
1 8
2 5
4 10
PAIRING
4
1 7
2 9
3 11
4 5```

# 题解

## 作者：KokiNiwa (赞：21)

首先对这个图构造 $\text{DFS}$ 树。

然后分类讨论：

+ 如果这棵树的深度至少为 $\lceil \frac{n}{2}\rceil$ ，那么直接选择路径即可。
+ 否则在每一层中不断选择点对，使得这一层里最多一个点没有被选上。

第二种情况的正确性：

对于任意两个点对 $a,b$ 与 $c,d$ ，$\text{dep}_a=\text{dep}_b$，$\text{dep}_c=\text{dep}_d$ 。不妨设 $\text{dep}_a<\text{dep}_c$ 。同层结点不会有边，那么对于两个不同层的结点，只有可能是父亲或者返祖边。

+ 如果是返祖边，由于 $a,b$ 每个点只能由一个返祖边，所以最多两条边。
+ 如果是父亲，并且 $a,b$ 有不同的父亲，那么必然一个节点只有一个父亲。
+ 如果是父亲，并且 $a,b$ 的父亲相同，那么必然 $c,d$ 中一个点有两条边，另一个点没边。

所以最多两条边。

另外因为不足 $\lceil\frac{n}{2}\rceil$ 个层，所以一层最多一个点没有被选上。所以点数至少 $\lceil\frac{n}{2}\rceil$ 个。

---

## 作者：tommymio (赞：5)

> 题目简述：
>
>- 给定一个 $n$ 个点 $m$ 条边的无向连通图。
>- 你需要完成以下两个任务中的一个：
>  - 找一条长度至少为 $\left\lceil\frac{n}{2}\right\rceil$ 的简单路径。
>  - 将至少 $\left\lceil\frac{n}{2}\right\rceil$ 个节点两两分组，满足任意两组的四个节点的 **导出子图** 至多有两条边。

题目强调：**至少有一个任务可以被完成**。

对于任务一，可以想到直接在图上 $\texttt{dfs}$。

我们再多想一些，在图上 $\texttt{dfs}$ 的搜索树就是一棵生成树，我们称为 $\texttt{dfs}$ 树。

那么能够完成任务一的 **唯一条件** 即为这棵 $\texttt{dfs}$ 树的最大深度不小于 $\left\lceil\frac{n}{2}\right\rceil$。

由于题目强调，**至少有一个任务可以被完成**，于是我们猜想当这棵 $\texttt{dfs}$ 树的最大深度小于 $\left\lceil\frac{n}{2}\right\rceil$  时，第二个任务一定可以被完成。

我们发现，无向图上的 $\texttt{dfs}$ 树似乎和 $\text{Tarjan}$ 提出的有向图中的 $\texttt{dfs}$ 树十分相似。借用其中的性质，可以得到： **两个点在原图上有边，当且仅当这两个点在 $\texttt{dfs}$ 树上是祖孙关系。**

证明也很简单，假设两个不存在祖孙关系的点 $u,v$ 之间有一条边，不妨设 $u$ 先被访问 ，那么在访问 $u$ 的子树时，一定会访问到 $v$ ，那么 $v$ 与 $fa_v$ 的边就不会出现在树上，并且这条边的两个点存在祖孙关系，得证。

根据上述性质，**如果我们只选两个深度相同的点 $x_1,y_1$ 作为一对，那么出现的两种情况都不会超过 $2$ 条边**：

- 与 $x_1,y_1$ 深度相同的两个点 $x_2,y_2$，这四个点的导出子图上只有 $0$ 条边。
- 与 $x_1,y_1$ 深度不同的 **另两个深度相同的点** $x_2,y_2$，这四个点的导出子图上最多只会有 $2$ 条边。

当这棵 $\texttt{dfs}$ 树的最大深度小于 $\left\lceil\frac{n}{2}\right\rceil$，这样分组会不会不满足将至少 $\left\lceil\frac{n}{2}\right\rceil$ 个点分组的要求呢？

我们发现同一深度最多只会有一个点不能被分组，而当最大深度小于 $\left\lceil\frac{n}{2}\right\rceil$ 时，至少也能将 $\left\lceil\frac{n}{2}\right\rceil$ 个点分组，于是得证。

```cpp
int top=0,maxDep=0;
int st[500005],d[500005];
std::vector<int> vec[500005],mp[500005];
inline void dfs(int x) {
	maxDep=max(maxDep,d[x]);
	vec[d[x]].push_back(x);
	for(register int i=0;i<mp[x].size();++i) {
		int y=mp[x][i];
		if(d[y]) continue;
		d[y]=d[x]+1;
		dfs(y);
	}
}
int main() {
	int T=read();
	while(T--) {
		int n=read(),m=read();maxDep=1;
		for(register int i=1;i<=m;++i) {
			int x=read(),y=read();
			mp[x].push_back(y);
			mp[y].push_back(x);
		}
		d[1]=1;dfs(1);
		if(maxDep>(int)(n*1.00/2+0.5)) {
			printf("PATH\n");
			for(register int i=vec[maxDep][0],dep=maxDep;i!=1&&dep!=1;--dep) {
				for(register int j=0;j<mp[i].size();++j) {
					if(d[mp[i][j]]==dep-1) {st[++top]=i;i=mp[i][j];break;} 
				}
			}
			printf("%d\n",top+1);
			printf("1 ");
			for(;top>=1;--top) printf("%d ",st[top]);printf("\n");
		}
		else {
			printf("PAIRING\n");
			int k=0;
			for(register int i=1;i<=maxDep;++i) k+=vec[i].size()/2;
			printf("%d\n",k);
			for(register int i=1;i<=maxDep;++i) {
				for(register int j=0;j<vec[i].size()-1;j+=2) {
					printf("%d %d\n",vec[i][j],vec[i][j+1]);
				}
			}	
		}
		for(register int i=1;i<=n;++i) mp[i].clear(),d[i]=0;
		for(register int i=1;i<=maxDep;++i) vec[i].clear();
	}
	return 0;
}
```

---

## 作者：墨舞灵纯 (赞：4)

### 题意

请你完成以下两个子问题的任意一个：

1.给至少 $\lceil \frac{n}{2} \rceil$ 个节点两两配对，使得任意两对点的导出子图不多于2条边。

2.找一条长度为 $\lceil \frac{n}{2} \rceil$ 的简单路径。


### 题解

发现任务 2 看起来比较容易：我们构建出图的 dfs 树，求出每个点的深度，如果深度 $\geq\lceil \frac{n}{2}\rceil$ 的点存在，我们就把这个点到根（根直接钦定为 1 ）的路径拎出来输出就行了。

考虑任务 1 怎么做：我们把同一深度的点两两配对，因为同一深度的点之间是不会有连边的。然后由于dfs树有个性质就是非树边连接的两点必然是祖孙关系，所以考虑任意选 $(a1,a2),(b1,b2)$ 这两对点，假设 $deep_{a1}<deep_{b1}$ 那么他们之间的边只有这几种情况：

1. $a1,a2$ 分别是 $b1,b2$ 的父亲，那么各连一条一共两条边。

2. $a1,a2$ 有一个是 $b1,b2$ 的父亲，那么作为父亲的点会有两条边，另一个没边。

3. $a1,a2$ 和 $b1,b2$ 之间是非树边，那么一定具有祖孙关系，最多只有两条边。

所以肯定是符合要求的。

### 代码 

```cpp
#include <cstdio>
#include <vector>
const int N = 1000005;
int h[N], nxt[N << 1], adj[N << 1], n, m, T, t, u, v, fa[N], d[N], o1[N], o2[N], mxd, id;
std::vector<int> g[N];
inline void add() { nxt[++t] = h[u], h[u] = t, adj[t] = v, nxt[++t] = h[v], h[v] = t, adj[t] = u; }
inline void dfs(int x) {
    g[d[x] = d[fa[x]] + 1].push_back(x);
    if (d[x] >= mxd) mxd = d[x], id = x;
    for (int i = h[x], j; i; i = nxt[i])
        if (!d[j = adj[i]])
            fa[j] = x, dfs(j);
}
int main() {
    scanf("%d", &T);
    int i, j, co;
    while (T--) {
        scanf("%d%d", &n, &m),co = mxd = id = t = 0;
        for (i = 1; i <= n; ++i) d[i] = h[i] = fa[i] = 0, g[i].clear();
        while (m--) scanf("%d%d", &u, &v), add();
        dfs(1);
        for (i = 1; i <= mxd; ++i)
            for (j = 0; j + 1 < g[i].size(); j += 2) 
				o1[++co] = g[i][j], o2[co] = g[i][j + 1];
        if ((co << 1) >= (n + 1 >> 1)) {
            puts("PAIRING"), printf("%d\n", co);
            for (i = 1; i <= co; ++i) printf("%d %d\n", o1[i], o2[i]);
            continue;
        }
        puts("PATH"),co = 0;
        while (id) o1[++co] = id, id = fa[id];
        printf("%d\n", co);
        for (i = 1; i <= co; ++i) printf("%d ", o1[i]);
        puts("");
    }
    return 0;
}

---

## 作者：chenxia25 (赞：2)

这是我所看了题解的题目。~~看完题解还厚颜无耻地在vp结束之前写了交上去~~

> ### [洛谷题目页面传送门](https://www.luogu.com.cn/problem/CF1391E) & [CF题目页面传送门](https://codeforces.com/contest/1391/problem/E)

> 给定一个$n$个点$m$条边的连通无向图。你需要做以下两件事中的任意一件：

>1. 找一条长度至少为$\left\lceil\dfrac n2\right\rceil$的简单路径；
>1. 将至少$\left\lceil\dfrac n2\right\rceil$个节点（要求是偶数个）两两分组，满足任意两组的四个节点的导出子图最多有两条边。

>可以证明至少有一件事是可以做的。

>本题多测。

>$\sum n\in\left[2,5\times10^5\right],\sum m\in\left[1,10^6\right]$。

无向连通图有个重要的东西：DFS树。它有一个很重要的性质：两个点之间有边仅当它们是长辈与晚辈的关系。很好证，因为若有非长晚辈关系的点对之间有边，那么当DFS到其中那个时间戳较小的点时，根据深度优先一定可以走到时间戳较大的那个点，从而使得它们是长晚辈关系，与假设矛盾。这与有向图DFS树的横叉边的性质类似。

看到第二件事中有要限制一些边不能出现这种感觉，不难想到DFS树的这个性质。（这个大概是Tarjan求DCC时要用到的，然鹅我还不会，所以没想到）

求出任意DFS树，如果存在深度$\geq\left\lceil\dfrac n2\right\rceil$的点那么显然可以做第一件事，直接输出就行了。否则，

注意到DFS树的这一性质，如何把它用起来。考虑两对深度不同的兄弟节点，兄弟之间显然不会有边，那么只有在不同对中的边。考虑从下往上连，由于只能连向祖先，而上面两个点是兄弟可以推出对于下面每个点最多只有上面的一个点作为它的祖先，于是最多会有两条边。

于是问题就迎刃而解了。接下来同层的尽量分组，每层最多留下一个单身。由于最大深度$<\left\lceil\dfrac n2\right\rceil$，单身的也是小于这么多，可以保证被分组的点的数量。

~~并不能保证下次遇到这样的智商题能做出来哦（~~

**多测`memset`，爆零两行泪。**

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int N=500000;
int n,m;
vector<int> nei[N+1];
bool vis[N+1];
int fa[N+1],dep[N+1];
void dfs(int x=1){//求搜索树 
	vis[x]=true;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];
		if(vis[y])continue;
		fa[y]=x;dep[y]=dep[x]+1;
		dfs(y);
	}
}
vector<int> buc[N+1];
void mian(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)nei[i].clear(),buc[i].clear(),vis[i]=fa[i]=dep[i]=0;
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		nei[x].pb(y);nei[y].pb(x);
	}
	dep[1]=1;
	dfs();
	for(int i=1;i<=n;i++)
		if(dep[i]>=n+1>>1){//可以输出简单路径了 
			puts("PATH");
			printf("%d\n",dep[i]);
			while(i)printf("%d ",i),i=fa[i];
			puts("");
			return;
		}
		else buc[dep[i]].pb(i);
	puts("PAIRING");//不能输出简单路径，那么一定能分组 
	int cnt=0;
	for(int i=1;i<=n;i++)cnt+=buc[i].size()>>1;//统计数量 
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++){//枚举层 
		for(int j=0;j+1<buc[i].size();j+=2)printf("%d %d\n",buc[i][j],buc[i][j+1]);//同层分组 
	}
}
int main(){
	int testnum;
	cin>>testnum;
	while(testnum--)mian();
	return 0;
}
```

---

## 作者：Piwry (赞：1)

时隔近两个月还是来写发题解，毕竟当时我扛这道题扛了整场比赛（

要想到这道题的解法必须得对 dfs 树的性质有很深的印象（我甚至怀疑出题者是看着 dfs 树造的这道题X），不然就很可能想歪了（~~或者仅仅是 wtcl~~）

## 解析

讲解法前，这里先介绍下 dfs 树一个重要的性质及其简要证明

### dfs 树

为了说明方便，这里先对称呼做一些约定：

（另外，由于无向图的边的特性，下面在提到边 $(u, v)$ 时，也有可能同时在指边 $(v, u)$）

1. 树边：是 dfs 树上的边。如果在 dfs 时通过边 $(u, v)$ 第一次发现结点 $v$，则 $(u, v)$ 是一条树边
2. 返祖边（前向/后向边）：若边 $(u, v)$ 连接的是 dfs 树中的一个结点与它的后代，则 $(u, v)$ 是一条返祖边
3. 横向边（横叉边）：指其他所有的边。横向边连接的两个结点不具有父代后代关系
4. 未遍历/已遍历/正在遍历：指结点的状态。其中需要特别说明的是，正在遍历指 dfs 到某个结点，且函数尚未从那个结点**返回**（`return`）

由 dfs 算法的特性我们其实可以得到一个定理

> 定理 1. 在对无向图进行 dfs 时，每条边要么是树边，要么是返祖边

证明：设 $(u, v)$ 是无向图的任意一条边。不失一般性，假定 $u$ 先于 $v$ 被遍历到。我们可以确定，在 $u$ 的 dfs 函数返回前，算法一定会遍历 $(u, v)$ 这条边，至少也会从 $u$ 遍历到。如果 $(u, v)$ 第一次被遍历到的方向是从 $u$ 到 $v$，则 $v$ 在此时是处于未遍历的状态，否则边一定已经从反方向探索过一次了（由于 $v$ 后于 $u$ 被遍历，当程序处于 $u$ 的函数，且 $v$ 已被遍历时，$v$ 的函数一定已经返回），这时边 $(u, v)$ 就会成为一条树边。如果 $(u, v)$ 第一次被遍历到的方向是从 $v$ 到 $u$，那么 $u$ 此时是处于正在遍历的状态（由于 $v$ 后于 $u$ 被遍历，当程序从 $u$ 的函数返回，也一定已经从 $v$ 的函数返回了），这时边 $(u, v)$ 就会成为一条返祖边

### 配对方法

这里直接给出构造方法

先对原图构建 dfs 树。如果树高大于等于 $\left\lceil\frac n 2\right\rceil$，那么直接构造路径即可。如果树高小于 $\left\lceil\frac n 2\right\rceil$，我们只取在 dfs 树上深度相同的结点配对，并尽可能地这样做，则在每层我们至多只会留下 $1$ 个结点没被配对；由于树高小于 $\left\lceil\frac n 2\right\rceil$，没被配对的结点也不会超过 $\left\lceil\frac n 2\right\rceil$，所以配对方案的配对数目一定是合法的

现在只需再证明配对方案的配对之间的导出子图（貌似题目中是这么称呼的...具体定义可见题面原文）合法即可。考虑两个配对 $(a, b), (c, d)$，不失一般性，假定 $a, b$ 的深度小于等于 $c, d$。如果 $a, b$ 的深度等于 $c, d$，由于对无向图进行 dfs 时不可能出现横向边，这两个配对的导出子图实际上是没有边的。如果 $a, b$ 的深度小于 $c, d$，则对于 $c$ 和 $a, b$，$c$ 只能和 $a, b$ 的其中一个存在边，因为无论这条边是树边还是横向边，都表明了 $a$ 或 $b$ 是 $c$ 的父代，而一个结点的两个不同的父代结点之间，也一定存在父代后代关系（某个结点的所有父代结点就相当于该结点到根的一条链），显然 $a, b$ 之间不能有父代后代关系；对于 $d$ 和 $a, b$，这也是相同的

于是在所有情况下，两个不同配对的导出子图至多存在两条边

## CODE

```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <bitset>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast","-funroll-loops","-fdelete-null-pointer-checks")
#pragma GCC target("ssse3","sse3","sse2","sse","avx2","avx")
using std::vector;
using std::bitset;

const int MAXN =5e5+50, MAXM =2e6+50;

/*------------------------------Dfs------------------------------*/

vector<int> E[MAXN];

inline void addedge(int u, int v){ E[u].push_back(v); }

int lim;
bitset<MAXN> vis;
int f[MAXN];
vector<int> out[MAXN];

void dfs(int u, int dep, int fa){
	f[u] =fa;
	out[dep].push_back(u);
	vis[u] =1;
	if(dep == lim)
		return;
	for(int i =0; i < (int)E[u].size(); ++i){
		if(!vis[E[u][i]])
			dfs(E[u][i], dep+1, u);
	}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; register char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	for(int t =0, T =read(); t < T; ++t){
		int n =read(), m =read();
		for(int i =0; i < m; ++i){
			int u =read(), v =read();
			addedge(u, v);
			addedge(v, u);
		}
		lim =(n+1)>>1;
		dfs(1, 1, 0);
		if((int)out[lim].size() != 0){
			puts("PATH");
			printf("%d\n", lim);
			for(int u =out[lim][0]; u; u =f[u])
				printf("%d ", u);
			putchar('\n');
		}
		else{
			puts("PAIRING");
			int k =0;
			for(int i =0; i < lim; ++i)
				k +=out[i].size()>>1;
			printf("%d\n", k);
			for(int i =0; i < lim; ++i)
				for(int j =1; j < (int)out[i].size(); j +=2)
					printf("%d %d\n", out[i][j-1], out[i][j]);
		}
		for(int i =1; i <= n; ++i)
			out[i].clear(), E[i].clear();
		vis.reset();
	}
}
```

---

