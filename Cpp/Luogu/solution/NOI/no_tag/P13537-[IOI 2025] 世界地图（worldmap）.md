# [IOI 2025] 世界地图（worldmap）

## 题目描述

玻利维亚考古学家 Pacha 先生在 Tiwanaku 附近发现了一份古代文献，描述了 Tiwanaku 时期（公元 300–1000 年）的世界。当时有 $N$ 个国家，从 $1$ 到 $N$ 编号。

文献中列出了 $M$ 对不同的相邻国家：

$$(A[0], B[0]), (A[1], B[1]), \ldots, (A[M-1], B[M-1]).$$

对每个 $i$（$0 \leq i < M$），文献指出国家 $A[i]$ 与国家 $B[i]$ 相邻，反之亦然。文献中未列出相邻关系的国家之间是不相邻的。

Pacha 先生希望绘制一幅世界地图，使得各国之间的相邻关系恰好与 Tiwanaku 时期完全一致。为此，他首先选择一个正整数 $K$。然后，他将地图绘制为一个由 $K \times K$ 的方格组成的网格，方格的行从 $0$ 到 $K-1$ 编号（从上到下），列从 $0$ 到 $K-1$ 编号（从左到右）。

Pacha 先生希望用 $N$ 种颜色来为地图的每个方格着色。颜色从 $1$ 到 $N$ 编号，颜色 $j$（$1 \leq j \leq N$）代表国家 $j$。着色方案必须满足以下所有**条件**：
* 对每个 $j$（$1 \leq j \leq N$），至少有一个方格染成了颜色 $j$。
* 对每对相邻国家 $(A[i], B[i])$，至少存在一对相邻的方格，其中一个方格染成了颜色 $A[i]$，另一个染成了颜色 $B[i]$。如果两个方格有一条公共边，则认为它们是相邻的。
* 对于任意一对相邻且颜色不同的方格，它们所代表的国家在 Tiwanaku 时期也必须是相邻的。

例如，若 $N = 3$，$M = 2$，且相邻国家为 $(1,2)$ 和 $(2,3)$，则国家 $1$ 与 $3$ 不相邻。下图是一幅 $K = 3$ 的地图，满足所有条件。

![](https://cdn.luogu.com.cn/upload/image_hosting/6zn2x2ar.png)

特别地，一个国家**不必**在地图上形成连通区域。在上述地图中，国家 3 是连通区域，而国家 1 和国家 2 则不是连通区域。

你的任务是帮助 Pacha 先生选择一个 $K$ 的值，并据此绘制一幅地图。文献保证这样的地图一定存在。由于 Pacha 先生倾向于更小的地图，因此在最后一个子任务中，你的得分取决于 $K$ 的大小。$K$ 越小，可能的得分越高。不过，本题无需找出可能的最小 $K$ 值。

### 实现细节

你要实现以下函数：

```
std::vector<std::vector<int>> create_map(int N, int M,
    std::vector<int> A, std::vector<int> B)
```
  * $N$：国家的数量。
  * $M$：国家之间的相邻关系的数量。
  * $A$ 和 $B$：长度为 $M$ 的数组，描述国家之间的相邻关系。
  * 对每个测试用例，该函数**最多**被调用 **50 次**。

该函数应返回一个数组 $C$，表示地图。
设 $C$ 的长度为 $K$。
  * $C$ 的每个元素都必须是一个长度为 $K$ 的数组，数组的元素为 $1$ 到 $N$ 之间的整数。
  * $C[i][j]$ 表示第 $i$ 行、第 $j$ 列的方格的颜色（对所有满足 $0 \leq i, j < K$ 的 $i$ 和 $j$）。
  * $K$ 必须小于或等于 $240$。

## 说明/提示

### 例子

在 CMS 中，以下两个场景包含在同一个测试用例中。

#### 例 1

考虑以下调用：

```
create_map(3, 2, [1, 2], [2, 3])
```

这是题目描述中的例子，该函数可以返回如下地图。

```
[
[2, 3, 3],
[2, 3, 2],
[1, 2, 1]
]
```

#### 例 2

考虑以下调用：

```
create_map(4, 4, [1, 1, 2, 3], [2, 3, 4, 4])
```

在这个例子中，$N = 4$，$M = 4$，国家 $(1, 2)$、$(1, 3)$、$(2, 4)$ 和 $(3, 4)$ 之间是相邻的。
因此，国家 $(1, 4)$ 和 $(2, 3)$ 之间并不相邻。

该函数可以返回如下 $K = 7$ 的地图，该地图满足所有条件。

```
[
[2, 1, 3, 3, 4, 3, 4],
[2, 1, 3, 3, 3, 3, 3],
[2, 1, 1, 1, 3, 4, 4],
[2, 2, 2, 1, 3, 4, 3],
[1, 1, 1, 2, 4, 4, 4],
[2, 2, 1, 2, 2, 4, 3],
[2, 2, 1, 2, 2, 4, 4]
]
```

不过地图可以更小；例如，该函数也可以返回如下 $K = 2$ 的地图。

```
[
[3, 1],
[4, 2]
]
```

注意，两幅地图都满足 $K/N \leq 2$。

### 约束条件

* $1 \le N \le 40$
* $0 \le M \le \frac{N \cdot (N - 1)}{2}$
* 对每个满足 $0 \le i < M$ 的 $i$，有 $1 \le A[i] < B[i] \le N$。
* 二元组 $(A[0], B[0]), \ldots, (A[M - 1], B[M - 1])$ 互不相同。
* 至少存在一幅地图，能够满足所有条件。

### 子任务与评分规则

| 子任务 | 分数  | 额外的约束条件 |
| :-----: | :----: | ---------------------- |
| 1       | $5$    | $M = N - 1$，对每个 $0 \le i < M$，有 $A[i] = i + 1$，$B[i] = i + 2$。 |
| 2       | $10$   | $M = N - 1$ |
| 3       | $7$    | $M = \frac{N \cdot (N - 1)}{2}$ |
| 4       | $8$    | 国家 $1$ 与所有其他国家相邻。其他国家之间也可能相邻。 |
| 5       | $14$   | $N \leq 15$ |
| 6       | $56$   | 没有额外的约束条件。 |

在子任务 6 中，你的得分取决于 $K$ 的值。
* 如果 `create_map` 返回的任一地图不满足所有条件，则该子任务的得分为 $0$。
* 否则，令 $R$ 为所有对 `create_map` 的调用中 $K / N$ 的**最大值**。根据下表，你将获得**部分得分**：

| 范围           | 分数         |
| :---------------:| :------------:|
| $6 < R$          | $0$           |
| $4 < R \leq 6$   | $14$          |
| $3 < R \leq 4$   | $28$          |
| $2.5 < R \leq 3$ | $42$          |
| $2 < R \leq 2.5$ | $49$          |
| $R \leq 2$       | $56$          |

## 样例 #1

### 输入

```
2
3 2
1 2
2 3
4 4
1 2
1 3
2 4
3 4```

### 输出

```
3
3 3 3
2 3 3
2 3 2
1 2 1
7
7 7 7 7 7 7 7
2 1 3 3 4 3 4
2 1 3 3 3 3 3
2 1 1 1 3 4 4
2 2 2 1 3 4 3
1 1 1 2 4 4 4
2 2 1 2 2 4 3
2 2 1 2 2 4 4
```

# 题解

## 作者：zhoukangyang (赞：42)

[来我的博客里看](https://www.cnblogs.com/zkyJuruo/p/19023079)

### 题意
> 给定 $n$ 个点 $m$ 条边的无向联通图。你需要构造一个 $K\times K$ 的网格，并在每个网格点上标上一个点的标号，使得一条边 $(u,v)$ 在图中出现当且仅当网格中存在相邻的两个点，编号分别为 $u$ 和 $v$。

> 数据范围：$n\le 40$。

> 要求 $K\leq \color{red}{1.5n}$。

### 题解

我们先来看原题的 $2n$ 做法是怎么做的。

首先，找到图的一颗 DFS 树，并根据颗树的 DFS 序斜着放，像这样：

```txt
1232
2324
3242
2421
```

考虑在这样的图中加入其他非树边。对于每个点的最后一次访问，我们把其拓展为 $3$ 条斜线，并在中间那条塞入其向祖先连的边，像这样：

```txt
  1d1
 1c1
1b1
a1
1
```

可以发现，这条斜线的位置到斜线序列开头和末尾的长度都至少是其到祖先的深度，因此总是能够在中间夹住所有要连的点。这样需要 $4n$ 条斜线，完成了 $K=2n$ 的构造。

然而，这样构建夹层非常浪费，考虑优化。

我们发现我们可以同时处理两个点对应的出边，我们处理了 $a,b$ 到 $2$ 的连边、$c,d$ 到 $1,2$ 的连边，$e,f$ 到 $2$ 的连边：

```txt
    1f12
   1e12
  1112
 11d2
12c2
2b2
a2
```

可以发现，夹层大小大约是 $1,2$ 两点处理的出边的并集大小。这样平均每个点只在 DFS 序的基础上多用一条斜线。

考虑在树上对相邻的一些点做匹配，然后对这些匹配做上面的连边优化。从根开始从上到下匹配，每次将一个没匹配的非叶子向其最后一个儿子匹配。这样会连成一些匹配，并剩下一些叶子。

由于这些叶子不会相互连边，因此我们只需要将叶子向祖先连出去的那些边放在祖先处处理，我们不对他们建立夹层。

然后，对于每个向儿子匹配的点 $x$，在其最后一次被访问时（即刚遍历完最后一个儿子时）处理 $x$ 和其最后一个儿子连出去的需要处理的边。需要处理的点只有 $x$ 的祖先和 $x$ 子树内的叶子。我们只需要说明，我们的夹层大小至少能放这么多点，也就是说夹层前面和后面都至少要有这么多点为之。

夹层前面有这么多点是显然的，因为这些点都出现在了夹层的前面；而夹层后面只出现过 $x$ 的祖先。但是我们发现，我们没有给叶子建立夹层，这为我们在最后省下了叶子个数的空位，因此后面也是能放得下的。

这样我们需要用 $3n$ 条斜线，完成了 $K=1.5n$ 的构造。当然，这样的构造也有很多冗余，距离理论最优还有挺大距离。

[aclink](https://qoj.ac/submission/1203272)

---

## 作者：_lmh_ (赞：11)

不难发现一个图有解当且仅当它联通。

一个朴素的想法是，把最终的结果按照列分割成若干块，每块宽 $3$ 格，两边全部放同一种颜色 $x$，中间放与 $x$ 相邻的颜色。

当然为了确保相邻块的 $x$ 之间有连边，需要找一棵生成树并在必要的时候回溯。为了方便实现，使用 dfs 生成树。

这个做法可以做到 $4n$。

现在我们保留生成树，递归地构造答案。如果生成树上一个点 $x$ 有多个儿子，那么是说，这个点是子树中所有点导出子图的一个割点，删掉之后导出子图变成多个联通块。

用 $x$ 将它的不同子树分隔开来，有如下构造：

```
xxxxxxxxx
x1x2x3x4x
xxxxxxxxx
x...x...x
x...x...x
x...x...x
x...x...x
```

其中两个 `.` 的连通块代表 $x$ 的不同子树，数字代表子树中与 $x$ 有边相连的点。

显然这个构造可以做到宽度 $2n-1$，长度 $3n$，尝试进一步优化。

为了保证构造中 `1234` 的位置不和其他东西相邻，需要把与它直接相邻的位置填上 `x`，因而可以挖掉角上的位置得到

```
_x_x_x_x_
x1x2x3x4x
xx.xxx.xx
x...x...x
x...x...x
x...x...x
x...x...x
```

或者

```
x_x_x_x_x
xx1x2x3xx
x.x.x.x.x
x...x...x
x...x...x
x...x...x
x...x...x
```

其中 `_` 为上一层用掉的部分。

相邻层之间交错排列，这样就可以做到 $2n+1$。发现最外面一层的数字上面不需要放东西，可以再省掉一层，做到 $2n$。

显然如果一个子树大小为 $s>1$，那么按照这种构造，上面一层至少会留下 $s-2$ 个位置可以用来填数。子树内至多有 $s-1$ 个与 $x$ 相邻的点，其中又有至少一个是它的儿子，因此 $s-2$ 个是够用的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll int
const ll N=250;
int n,m,k,ans[N][N],ok[N],vis[N],TO[N][N];
vector<int> to[N];
void dfs(int u){
	vis[u]=1;
	for (auto v:to[u]) if (ok[v]&&vis[v]==0) dfs(v);
}
void del(vector<int>& vec,int x){
	if (vec.size()==0) return;
	for (int i=0;i<vec.size();++i) if (vec[i]==x){
		swap(vec[i],vec.back());break;
	}
	if (vec.back()==x) vec.pop_back();
}
void solve(vector<int> vec,int l,int r,int h){
	assert(vec.size());assert(r-l==(vec.size()-1)*2);
	int u=vec[0];
	if (vec.size()==1){
		for (int i=1;i<=h;++i) for (int j=l;j<=r;++j) ans[i][j]=u;
		for (int i=l;i<=r;++i) if (ans[h+1][i]==0) ans[h+1][i]=u;
		return;
	}
	for (auto x:vec) ok[x]=1;
	dfs(u);
	for (auto x:vec) assert(vis[x]);
	for (auto x:vec) vis[x]=0;
	for (int i=1;i<=h;++i) ans[i][l]=ans[i][r]=u;
	for (int i=l;i<=r;++i) ans[h][i]=u;
	if (ans[h+1][l]==0) ans[h+1][l]=u;
	if (ans[h+1][r]==0) ans[h+1][r]=u;
	int d=l+1+(ans[h+1][l+1]!=0);
	for (auto x:to[u]) if (ok[x]){
		assert(d<r);
		assert(ans[h+1][d]==0);
		ans[h+1][d]=ans[h-1][d]=u;
		ans[h][d]=x;
		d+=2;
	}
	while(d<r){
		assert(ans[h+1][d]==0);
		ans[h+1][d]=ans[h][d]=ans[h-1][d]=u;
		d+=2;
	}
	d=l;
	for (int i=1;i<=n;++i) ok[i]=0;
	del(vec,u);
	while(vec.size()){
		int v=0;
		for (auto x:vec) if (TO[u][x]){v=x;break;}
		assert(v);
		vector<int> nxt(1,v);
		for (auto x:vec) ok[x]=1;
		dfs(v);
		for (auto x:vec) if (vis[x]&&x!=v) nxt.emplace_back(x);
		for (auto x:nxt) del(vec,x);
		solve(nxt,d+1,d+2*nxt.size()-1,h-2);
		d+=2*nxt.size();
		for (int i=1;i<=h;++i) ans[i][d]=u;
		for (int i=1;i<=n;++i) ok[i]=vis[i]=0;
	}
	assert(d==r);
}
vector<vector<int> > create_map(int N,int M,vector<int> A,vector<int> B){
	memset(ans,0,sizeof(ans));
	n=N;m=M;
	for (int i=0;i<m;++i){
		to[A[i]].emplace_back(B[i]);
		to[B[i]].emplace_back(A[i]);
		TO[A[i]][B[i]]=TO[B[i]][A[i]]=1;
	}
	m=0;k=2*n;
	vector<int> vec;
	for (int i=1;i<=n;++i) vec.emplace_back(i);
	solve(vec,1,k-1,k);
	vec.clear();
	for (int i=1;i<=n;++i) to[i].clear();
	for (int i=1;i<=n;++i) for (int j=1;j<=n;++j) TO[i][j]=0;
	for (int i=1;i<=k;++i) ans[i][k]=ans[i][k-1];
	vector<vector<int> > ans(k,vector<int>(k,0));
	for (int i=1;i<=k;++i) for (int j=1;j<=k;++j) ans[i-1][j-1]=::ans[i][j];
	return ans;
}
```

---

## 作者：cmk666 (赞：3)

显然有解等价于图连通。

先考虑树怎么做。不难发现一个欧拉序就是合法的，一行对应一个点就行。

现在只要加上非树边。一种简单的方法是，对于每个点 $u$，把它的其中一行变成如下的三行，其中 $a,b,c,d,\cdots$ 等是其非树边的邻居：

```plain
uuu...u
abcd...
uuu...u
```

这样有两个问题：首先，中间的 $a,b$、$b,c$ 等也会被判作相邻。虽然确实可以通过以 $u$ 分隔符的方式解决，但是更重要的问题是，这样一共需要 $4n-1$ 行，远超限制。

我们的目标是构造 $2n\times2n$ 的矩阵。在这个矩阵里，我们惊奇的发现，居然恰好有 $4n-1$ 根对角线！于是不难想到转 $45\degree$，以一根对角线为一行进行上述构造。同时由于对角线的格子是不相邻的，也省去了分隔符的麻烦。

最后的问题是，对角线的长度可能会很短，容纳不下所有非树边邻居，如最角落能填的邻居只有 $2$ 个。不过观察到对于一条非树边 $u,v$，不需要在两边都要出现，只要出现一次即可。因此，可以先预处理一遍求出每个点对应的最多能填的邻居数，然后钦定一条非树边在能填的多的那边填就行。不难证明，即使考虑极端情况，这样做也完全能填的下。

模拟上述过程即可。由于 $n$ 很小怎么写都能过。

---

## 作者：IvanZhang2009 (赞：3)

如果是树的话，其实很难想到直接欧拉序可以做到 $2n$ 小一点，行数是 $1$。~~但是我们可以做到更差！~~ 其实就是人类的思考过程：把每个子树包裹起来变成一个矩形。考虑归纳构造，构造一个子树的矩形，先把根放在最外层，然后把每个儿子的矩形依次放进去，中间用根隔开。例如：

```
111111111
122213331
122213331
122213331
```

其中 `2` 和 `3` 代表两棵儿子子树，$1$ 是根。

这样子的长度是 $2n-1$，高度是树的深度。~~其实最后一行就是欧拉序。~~

考虑能不能取一个生成树，把剩下的边塞进去。既然是任意生成树那就取 dfs 树。很难想到可以把上面的结构弄松一点变成这样：

```
111111111
1?1?1?1?1
111111111
122213331
122213331
122213331
```

这样子就是每个子树的根处扩展成一个中空的包裹，可以用来塞点东西。这个包裹的大小大概是子树大小，所以对于每条返祖边，你把这条边深度大的点放到它祖先的包裹里即可。这样子高度是 $3\times dep$，长度还是 $2n-1$。可以获得 $86$ 分的好成绩。

我们直观地感觉这个三层铺的有点浪费，观察一个例子：

```
11111111111
1?1?1?1?1?1
11111111111
12222222131
12?2?2?2131
12222222131
12444252131
124?4252131
12444252131
12464252131
```

其实可以发现对于相邻的两层（第 $3a+b$ 行和第 $3(a+1)+b$ 行，$b=1,2,3$），它们的 `?` 的间隔开来的。对于如下左边的结构，其实可以变成右边：

```
111    1
1?1   1?1
111    1
```

节约掉四个角的空间之后，可以发现相邻两层解决掉的空间刚好是一奇一偶，正好可以岔开，所以上图就可以变成（只画前两层）：

```
1?1?1?1?1?1   1?1?1?1?1?1
11 1 1 1111   11212121111
1 2 2 2 131   12?2?2?2131
12?2?2?2131
```

这样每个深度就被压缩成了两层。顺便把第一行删掉。最后是 $(2n-1)\times (2n-1)$。

```cpp
#include "worldmap.h"
#include<bits/stdc++.h>
using namespace std;
#define MOD         998244353
#define pii         pair<int,int>
#define all(v)      v.begin(),v.end()
#define pb          push_back
#define REP(i,b,e)  for(int i=(b);i<(int)(e);++i)
#define over(x)     {cout<<(x)<<endl;return;}
#define lowbit(x)   ((x)&(-(x)))
#define cntbit(x)   __builtin_popcount(x)
#define deal(v)     sort(all(v));v.erase(unique(v.begin(),v.end()),v.end())
#define lbound(v,x) lower_bound(all(v),x)-v.begin()
vector<vector<int>>ans;
vector<int>v[50],g[50];
int vis[50],fa[50],sz[50],dep[50];
void dfs(int x,int pre,int d){
	vis[x]=1;dep[x]=d;sz[x]=1;
	for(auto i:v[x])if(i!=pre){
		if(!vis[i]){
			fa[i]=x;
			g[x].pb(i);g[i].pb(x);
			dfs(i,x,d+1);
			sz[x]+=sz[i];
		}
	}
}
pii pos[50];
void color(int x,int pre,int l,int r,int d){
	REP(i,l,r+1)ans[d*2][i]=x;
	REP(i,l,r+1)if((i-l)&1){ans[d*2+1][i]=x;if(d)ans[d*2-1][i]=x;}
	pos[x]={d*2,l+1};
	for(auto i:g[x])if(i!=pre){
		++l;
		color(i,x,l,l+sz[i]*2-2,d+1);
		l+=sz[i]*2-1;
	}
}
vector<vector<int>>create_map(int n,int m,vector<int>U,vector<int>V){
	ans=vector<vector<int>>(n*2-1,vector<int>(n*2-1,0));
	REP(i,1,n+1)v[i].clear(),vis[i]=0,g[i].clear();
	REP(i,0,m)v[U[i]].pb(V[i]),v[V[i]].pb(U[i]);
	dfs(1,0,0);
	color(1,0,0,2*n-2,0);
	REP(i,1,n+1){
		for(auto j:v[i])if(dep[j]>dep[i]&&fa[j]!=i){
			auto &[x,y]=pos[i];
			ans[x][y]=j;
			y+=2;
		}
	}
	REP(i,0,n*2-1){
		REP(j,0,n*2-1)if(!ans[i][j]){
			if(i)ans[i][j]=ans[i-1][j];
			else ans[i][j]=ans[i][j-1];
		}
	}
	return ans;
}

---

## 作者：min_inf (赞：2)

我咋这么唐呢。

首先有一个自然的想法是，取出一个生成树，想一个比较好看的树的构造，然后每个节点额外塞一些非树边。

树的情况考虑这样的构造：

![](data:image/png;base64,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)

如果我们取出的是 DFS 树，那非树边一定是祖孙关系，我们把它放到深度较低的点上，每个点就最多只需要连 $sz_u-2$ 条非树边，而点的宽度是 $2sz_u-1$ 的，也就是非树边可以在每个节点顶上这条一个隔一个地放：

![](data:image/png;base64,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)

这样我们就做到了 $3n\times 2n$，可以获得 $86$ 分。

vp 的时候我注意到放在一侧也可以做到 $3n\times 3n$，考虑平衡一下这两个东西：出栈序前 $\frac 3 4 n$ 个点放在上面，高度不会超过 $2.5n$；其他点放在侧面，宽度不会超过 $2.5n$ 且高度只会对 $2sz+\frac 1 4$ 取 $\max$，可以获得 $93$ 分。[code](https://qoj.ac/submission/1198072)

但是我们观察到一个惊人的性质：题目中说的相邻是有公共边不是有公共点！！！考虑这样的构造：

![](data:image/png;base64,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)

轻松做到 $2n\times 2n$，可以获得 $100$ 分。[code](https://qoj.ac/submission/1208430)

---

## 作者：Mirasycle (赞：2)

$72 \rm pts$ 是整个题的最基本思路，也就是构建一个 $4n\times 2n$（为了形成正方形其实是 $4n\times 4n$）。

这部分的构造就是先考虑树，很容易按照子树来分类，使用父亲来间隔各个儿子，然后递归处理儿子进行就行了。

```
u v1 u v2 u 
u v1 u v2 u
u v1 u v2 u
```


扩展到一般图，同理考虑 dfs 树，会产生返祖边。我们可以单独开一列表示一些能上来的孙子节点，中间用 $u$ 来隔开。这么做是 $4n\times 2n$ 的。

```
u v1 u v2 u c1 u
u v1 u v2 u u  u
u v1 u v2 u c2 u
```

其实信息量是 $8n^2<3n\times 3n$，但是为了凑成正方形不得不变成 $4n\times 4n$。所以考虑均匀分布，返祖边信息还是竖着来，这个时候我们发现儿子信息其实可以并列地放在若干行内。原因是行的高度约束是 $2\times$ 子树大小，而儿子子树大小求和刚好是父亲子树大小量级，所以你可以这么塞进去。这么做的意义是我们把原先列之间的 $u$ 间隔放到了行中，减少了列数。这么做是 $3n\times 2n$ 的，有 $86\rm pts$。

```
u u  u u  u
u c1 u v1 v1
u u  u u  u
u c2 u v1 v1
u u  u u  u
```

略加优化就可以满分了，你会发现下图中的问号位置并不需要填入 $u$，于是你在相邻两层镶嵌插入就可以减少一个 $n$ 的宽度了。

```
? u  ? u  u
u c1 u v1 v1
? u  u u  u
u c2 u v1 v1
? u  ? u  u
```

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int maxn=300;
void cmax(int &x,int y){ x=x>y?x:y; }
void cmin(int &x,int y){ x=x<y?x:y; }
int n,m,dfn[maxn],e[maxn][maxn],sz[maxn],rev[maxn]; 
vector<int> G[maxn],son[maxn]; int tot=0;
vector<vi> emp,ans;
void Clear(){
	for(int i=1;i<=n;i++){
		G[i].clear(); son[i].clear();
		dfn[i]=sz[i]=rev[i]=0;
		for(int j=1;j<=n;j++) e[i][j]=0;
	} tot=0;
}
void dfs(int u){
	sz[u]=1; dfn[u]=++tot; rev[tot]=u;
	for(auto v:G[u]){
		if(dfn[v]) continue;
		dfs(v); sz[u]+=sz[v];
		son[u].pb(v);
	}
}
vi merge(vi L,vi R){ for(auto z:R) L.pb(z); return L; }
vector<vi> solve(int u,int len){
	if(!son[u].size()) return emp;
	vector<vi> res,cur; vi s,tt(1,u);
	for(int i=dfn[u]+1;i<=dfn[u]+sz[u]-1;i++){
		int v=rev[i];
		if(e[u][v]) s.pb(v);
	}
	res.resize(2*s.size());
	if(u==1) for(auto &z:res) z.pb(u);
	for(int i=0;i<s.size();i++){//交替放置 u s[i] 
		res[2*i].pb(u);
		res[2*i+1].pb(s[i]);
	}
	for(auto &z:res)
		if(z.back()!=u) z.pb(u);//外层封住 s[i] 
	int j=1,flag=0;//第一行空着 
	if(u==1) tt.pb(u);
	for(auto v:son[u]){
		cur=solve(v,len-2-(u==1));
		if(!cur.size()) continue;
		flag=1;
		while(j+cur.size()+1>res.size()) res.pb(tt);
		if(res[j+1].size()>=2+(u==1)) j++;
		for(auto z:cur){
			if(res[j].size()<2+(u==1)) res[j].pb(v);
			res[j]=merge(res[j],z); j++;
		}
		res[j++].pb(u);
	}
	flag=1;
	for(auto id:res.back())
		if(id!=u) flag=0;
	if(!flag) res.pb(tt);//封底 
	for(auto &z:res)//补满
		while(z.size()<len) z.pb(z.back());	
	return res;
}
vector<vi> create_map(int N,int M,vi A,vi B){
	n=N; m=M; ans.clear();
	if(n==1){
		vi tmp; tmp.pb(1);
		ans.pb(tmp); return ans;
	}
	for(int i=0;i<m;i++){
		e[A[i]][B[i]]=e[B[i]][A[i]]=1;
		G[A[i]].pb(B[i]),G[B[i]].pb(A[i]);
	}
	dfs(1); ans=solve(1,2*n);
	vi base=ans.back();
	while(ans.size()<2*n) ans.pb(base);
	Clear(); return ans;
}
```

---

