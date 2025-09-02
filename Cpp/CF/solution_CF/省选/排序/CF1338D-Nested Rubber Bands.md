# Nested Rubber Bands

## 题目描述

You have a tree of $ n $ vertices. You are going to convert this tree into $ n $ rubber bands on infinitely large plane. Conversion rule follows:

- For every pair of vertices $ a $ and $ b $ , rubber bands $ a $ and $ b $ should intersect if and only if there is an edge exists between $ a $ and $ b $ in the tree.
- Shape of rubber bands must be a simple loop. In other words, rubber band is a loop which doesn't self-intersect.

Now let's define following things:

- Rubber band $ a $ includes rubber band $ b $ , if and only if rubber band $ b $ is in rubber band $ a $ 's area, and they don't intersect each other.
- Sequence of rubber bands $ a_{1}, a_{2}, \ldots, a_{k} $ ( $ k \ge 2 $ ) are nested, if and only if for all $ i $ ( $ 2 \le i \le k $ ), $ a_{i-1} $ includes $ a_{i} $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338D/4370eb464e1d73dea417ea3868b50e2e406dadfc.png) This is an example of conversion. Note that rubber bands $ 5 $ and $ 6 $ are nested. It can be proved that is it possible to make a conversion and sequence of nested rubber bands under given constraints.

What is the maximum length of sequence of nested rubber bands can be obtained from given tree? Find and print it.

## 说明/提示

In the first sample, you can obtain a nested sequence of $ 4 $ rubber bands( $ 1 $ , $ 2 $ , $ 5 $ , and $ 6 $ ) by the conversion shown below. Of course, there are other conversions exist to make a nested sequence of $ 4 $ rubber bands. However, you cannot make sequence of $ 5 $ or more nested rubber bands with given tree.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338D/27e7091deefbdff67b80fe216bc799841ef8e866.png)You can see one of the possible conversions for the second sample below.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1338D/cdc0a8c1a626e7c24789584a069e78ef02086f92.png)

## 样例 #1

### 输入

```
6
1 3
2 3
3 4
4 5
4 6```

### 输出

```
4```

## 样例 #2

### 输入

```
4
1 2
2 3
3 4```

### 输出

```
2```

# 题解

## 作者：wucstdio (赞：16)

评分还没出，目测难度在 $2800$ 上下？

## 题意

给定一棵 $n$ 个点的树，第 $i$ 条边连接 $u_i$ 和 $v_i$。

你需要将每一个节点画成一个二维平面上闭合几何图形，满足如果 $u$ 和 $v$ 之间有边相连，那么这两个点对应的几何图形边界相交。（注意包含不算边界相交）

我们定义一个序列 $a_1,a_2,\ldots,a_k$ 是好的，当且仅当对于任意的 $2\le i\le k$，$a_{i-1}$ 所对应的几何图形完全包含 $a_i$ 所对应的几何图形。

求好的序列最长可以是多少。

（题面翻译是我写的）

## 题解

### 性质1

如果两个点之间有边相连，那么这两个点对应的图形不可能互相包含。

这一点是显然的。

### 性质2

对于一个序列 $a_1,a_2,\ldots,a_k$，这个序列对于整棵子树合法（所有其它点都能画出来），当且仅当这个序列对于 $a_1,\ldots,a_k$ 所形成的导出子树合法。

#### 证明：

假设我们已经画出来了一个连通子树，我们需要画出来其它所有的点。

在这个连通子树内任意取一个点当根进行 bfs，如果当前点 $x$ 还没有画出来，就画一个圆使得它只和 $x$ 的父节点相交。由于只要求和一个图形相交，所以一定可以画出来。

继续画下去就可以得到整棵树。

### 性质3

**对于任意一个点 $u$，不可能存在三棵子树 $x,y,z$，使得这三棵子树中除了 $x,y,z$ 之外，还有其它点在序列中。**（是不是很绕）

证明：

考虑反证法，设 $x,y,z$ 中分别有三个点 $a,b,c$ 在序列中：

![](https://cdn.luogu.com.cn/upload/image_hosting/saygya0n.png)

考虑 $x$ 和 $z$ 这两棵子树。由于这两棵子树中没有任意一个点和 $b$ 有边相连，所以 $x$ 和 $z$ 一定位于 $b$ 的两边：

![](https://cdn.luogu.com.cn/upload/image_hosting/xw5k6pbv.png)

接下来考虑 $u$ 这个点。它和 $x,z$ 相交，但是却不和 $b$ 相交，这是不可能的。

### 思路

我们考虑不违反上述三条性质的序列。可以发现，这个序列一定满足存在一条链，使得所有点要么在链上要么和链直接相连。因为对任意一个点来说，不和它直接相连的序列中的点至多位于它的两棵子树内。~~大家感性理解一下。~~

这样我们就有了一个暴力思路：枚举一条链，把这条链以及和它相邻的点拿出来，求一个最大独立集。

这个算法显然会 TLE，我们考虑用树形 DP 的思想。

对于一个点 $i$ ，我们设 $f_{i,0}$ 表示在 $i$ 的子树中，$i$ 作为链的一端且不在序列中，能够选择的点最多有多少。

再设 $f_{i,1}$ 表示在 $i$ 的子树中，$i$ 作为链的一端且在序列中，能够选择的点最多有多少。

树形 DP 的经典模型：

![](https://cdn.luogu.com.cn/upload/image_hosting/zlztm3dl.png)

$$f_{v,1}+d_u-2\to f_{u,0}$$

$$f_{v,0}+d_u-2\to f_{u,0}$$

$$f_{v,0}+1\to f_{u,1}$$

初始别忘了让 $f_{u,1}=1,f_{u,0}=d_u-2$（之所以 $-2$ 是因为链头的点选到序列中一定不会更劣，因此所有没有选择的点一定位于链的中间位置，$u$ 的周围有 $d_u-2$ 个点）

在转移的过程中随时更新答案：

$$f_{u,0}+f_{v,0}\to ans$$

$$f_{u,0}+f_{v,1}\to ans$$

$$f_{u,1}+f_{v,0}\to ans$$

$$f_{u,1}\to ans$$

时间复杂度 $O(n)$。

## 代码

比赛的时候 DP 状态略微有些不同，为了写这篇题解专门又改了改：

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
struct Edge
{
	int to;
	int nxt;
}e[200005];
int n,m,edgenum,head[100005],dep[100005],pa[100005],d[100005],ans;
int f[100005][2];
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node)
{
	dep[node]=dep[pa[node]]+1;
	f[node][0]=0,f[node][1]=1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		if(to==pa[node])continue;
		pa[to]=node;
		dfs(to);
		ans=max(ans,f[node][0]+f[to][0]);
		ans=max(ans,f[node][0]+f[to][1]);
		ans=max(ans,f[node][1]+f[to][0]);
		f[node][0]=max(f[node][0],f[to][1]+d[node]-2);
		f[node][0]=max(f[node][0],f[to][0]+d[node]-2);
		f[node][1]=max(f[node][1],f[to][0]+1);
	}
	ans=max(ans,f[node][1]);
}
int main()
{
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		add(u,v);
		add(v,u);
		d[u]++,d[v]++;
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
```

赛时提交记录：[76398535](https://codeforces.com/contest/1338/submission/76398535)

---

## 作者：mulberror (赞：5)

$$\href{http://blog.chhokmah.cn/index.php/archives/94/}{\Large\texttt{My blog}}$$

----
## Description

给定一棵 $n$ 个节点的树，每一个节点都代表了一个封闭区域。

若两个节点 $(a,b)$ 之间有边连接，那么代表 $a$ 所代表的封闭区域和 $b$ 所代表的封闭区域**有交**，如果没有边相连，那么**一定没有交**。

最大化某一个点集，使得其内部的每一个节点代表的封闭区域对于其他的节点代表的封闭区域是**包含**或者**被包含**的关系。

$n\leq 10^5$

## Solution

### 约定

- 以下我们称**特殊独立集**为满足题目条件的独立集。
- **独立集**的大小为独立集内的点数。

### 正文

首先你可以发现一个性质

- 对于一个链 $a\rightarrow b \rightarrow c$，$a$ 和 $b$ 交， $b$ 和 $c$ 交，那么 $a$ 可能包含 $c$。

这就有点像最大独立集的做法。

说的具体一点就是

以下分析结合画图有利于理解。

我们指定一个节点  $u$ **不选择**，那么显然最优的是把与其连接的子节点中最大的一个**特殊独立集**取出作为中心，再把其他和 $u$ 连接的子节点所代表的圆形依次覆盖原来的节点。

为了更加彻底的表述以上的性质，我们需要证明以下结论：

> 对于一个节点 $u$，不会存在两个以上的**子节点**其**本身和子树**对 $u$ 有贡献。
>
> 证明：
>
> 若子节点 $a,b$ 对 $u$ 都有贡献，那么 $a$ 点和 $b$ 点所代表的圆形一定存在包含关系，我们不妨设 $a$ 所代表的区域包含了 $b$
>
> 那么显然 $a$ 的子树和 $b$ 的子树内的所有节点不存在边相连，所以两者之间不存在边相连，所以 $a$ 子树的区域的并一定在 $b$ 代表的区域外，那么 $a$ 的子树对 $u$ 就一定没有贡献。（详细可以画图验证）
>
> 证毕。

大概就是以下这种情况

![illustration_1](http://blog.chhokmah.cn/usr/uploads/2020/04/287598956.png)

红色表示的是选择的**子节点的最大独立集**，紫色的为**根节点**，白色为**其余的子节点**。

我们指定一个节点 $u$ 选择，那么结论和上面相似，即选择一个与其连接的子节点中最大的一个**根节点不选择的特殊独立集**。但是因为 $u$ 选择了，所以其他的子节点不能覆盖在选择的独立集上。

接下来的分析思路就和第一种情况类似，不再赘述。

大概就是以下这种情况

![illustration_2](http://blog.chhokmah.cn/usr/uploads/2020/04/3823793359.png)

于是我们就可以用类似**最大独立集**的树形 DP 来解决这一题。

注意需要在转移的时候随时更新答案，答案的更新和上述转移相同。

时间复杂度 $\Theta(n)$

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;

int n, ans;
vector<int> g[N];
int f[N][2];

void dfs(int u, int fa) {
  f[u][0] = f[u][1] = 0;
  for (auto v : g[u]) {
    if (v ^ fa) {
      dfs(v, u);
      ans = max(ans, f[u][1] + f[v][0] + 1);
      ans = max(ans, f[u][0] + (int)g[u].size() - 2 + max(f[v][0], f[v][1]));
      f[u][0] = max(f[u][0], max(f[v][1], f[v][0]));
      f[u][1] = max(f[u][1], f[v][0]);
    }
  }
  f[u][1]++;
  if (g[u].size() >= 2)
    f[u][0] += g[u].size() - 2;
  ans = max(ans, max(f[u][0], f[u][1]));
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    g[u].push_back(v);
    g[v].push_back(u);
  }
  ans = 0;
  dfs(1, 0);
  printf("%d\n", ans);
  return 0; 
}
```

---

## 作者：wasa855 (赞：4)

首先画几个图玩一下，然后可以发现对答案的贡献是如下这种形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/jskncafp.png)

然后再进一步，他还可以是这种形式：

![](https://cdn.luogu.com.cn/upload/image_hosting/ytkq0eft.png)

然后你试图把他扩展到一般形式，发现他限制非常多。

例如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/9zpfqdm4.png)

这是他的最优解，注意三个三叉子树只有一个能被完全选入。

原理大概是这样的：

![](https://cdn.luogu.com.cn/upload/image_hosting/zxzds4ps.png)

所以一个点只有最多一个子树能被完全计入答案，其他的儿子只有一层有效。

仔细分析一下，发现他答案是**找一条链，只保留一级儿子的最大独立集的大小**，这个可以通过简单的树形 DP 求出。

---

题解部分讲完了，下面是一些题外话。

这道题我在 cf 的现场已经想到了全部的解法，但是因为一些失误，导致我在一个统计答案的地方少了一个 $+1$ ，然后他的 pretest 虽然有 $27$ 个数据点，但没有一个数据点包含了这个细节，于是我 fst 了。而由于前面 A、C 两题的一些高级操作（一场比赛中连着 $2$ 题没开 long long ，分别贡献了一发罚时），而且由于切题顺序的问题 （$A\rightarrow C\rightarrow B$），导致我罚时巨大，最后排在了 rk200+ 的位置。

还好我本来的 rating 很低，所以还是上了一点分，还变成了 IM。

---

这应该是一道好题，他思维难度大，代码难度小（适合我这种不会写代码的人，虽然我还是 fst 了）

Code：

```cpp
#define N 100005
vector<int> G[N];
bool cmp(int x,int y){return x>y;}
int f[N][2],dep[N],maxd[N],n,ans; // not choose , choose 
void dfs(int u,int fa)
{
	int maxn=0,cnt=0;
	vector<int> a,b,c;
	for(int v:G[u])
	{
		if(v==fa) continue;
		dfs(v,u); cnt++;
		a.pb(f[v][0]);
		b.pb(f[v][1]);
		c.pb(max(f[v][0],f[v][1]));
	}
	sort(a.begin(),a.end(),cmp);
	sort(b.begin(),b.end(),cmp);
	sort(c.begin(),c.end(),cmp);
	if(a.size()==0)
	{
		f[u][1]=1; return ;
	}
	if(a.size()==1)
	{
		f[u][1]=1+a[0];
		f[u][0]=max(a[0],b[0]);
		return ;
	}
	if(u==1)
	{
		int R=cnt-2+c[0]+c[1];
		if(R>ans) ans=R;
		R=a[0]+a[1]+1; // 我少了一个 +1 的地方
		if(R>ans) ans=R;
		f[u][0]=cnt-1+c[0];
		f[u][1]=1+a[0];
	}
	else
	{
		int R=cnt-1+c[0]+c[1];
		if(R>ans) ans=R;
		R=a[0]+a[1]+1; // 还有这里
		if(R>ans) ans=R;
		f[u][0]=cnt-1+c[0];
		f[u][1]=1+a[0];
	}
}
signed main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read();
		G[u].pb(v),G[v].pb(u);
	}
	dfs(1,0);
	cout<<max(ans,max(f[1][0],f[1][1]))<<endl;
	return 0;
}
```



---

## 作者：Fuyuki (赞：2)

考虑有三个环 $a,b,c$ 按顺序嵌套在一起在什么时候合法：

1. $a,b,c$ 之间两两不交。

2. 不存在若干个顺次连接的环与 $a,c$ 分别相交，但是与 $b$ 不相交。

对于第一个限制，选出来的点是独立集即可。

对于第二个限制，与 $a,c$ 相交的极小的“顺次连接的环”实际上由 $a$ 到 $c$ 路径上的所有点构成，因此只有当 $b$ 到路径 $(a,c)$ 的距离小于等于 $1$ 的时候才合法。

所以对于合法序列 $a_1,a_2,a_3,\dots a_k$，必有 $a_i$ 到路径 $(a_1,a_k)$ 的距离小于等于 $1$，换言之，这些点一定是树上的一个导出“毛毛虫”的独立集。

那么剩下的就是一个很简单的树形 dp 了，复杂度为 $O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define V inline void
#define FOR(i,a,b) for(int i=a;i<=b;i++)
const int N=2e5+1;
vector<int>e[N];
int n,ans,f[N],g[N];
V add_edge(int x,int y){e[x].push_back(y),e[y].push_back(x);}
V cmax(int&x,int y){if(x-y>>31)x=y;}
V dfs(int u,int fa=0){
	int d=e[u].size();
	for(int v:e[u])if(v!=fa){
		dfs(v,u);
		cmax(ans,max(f[u]+g[v]+1,g[u]+f[v]+d-2));
		cmax(f[u],g[v]),cmax(g[u],f[v]);
	}
	cmax(ans,++f[u]),cmax(ans,g[u]+=d-1-!!fa),cmax(f[u],g[u]);
}
int main(){
	scanf("%d",&n);
	for(int x,y;--n;add_edge(x,y))scanf("%d%d",&x,&y);
	dfs(1),cout<<ans;
	return 0;
}
```

---

## 作者：RockyYue (赞：1)

### 1338D

给定一棵 $n$ 个点的树，第 $i$ 条边连接 $u_i$ 和 $v_i$。

你需要将每一个节点画成一个二维平面上闭合几何图形，当且仅当 $u$ 和 $v$ 之间有边相连，这两个点对应的几何图形边界相交（注意包含不算边界相交）。

我们定义一个序列 $a_1,a_2,\ldots,a_k$ 是好的，当且仅当对于任意的 $2\le i\le k$，$a_{i-1}$ 所对应的几何图形完全包含 $a_i$ 所对应的几何图形。

求好的序列最长可以是多少，要求 $O(n)$。

### Sol

- 将构造出几何图形再找最长序列的过程，转化为选一些点构成序列，要求个数尽量多且合法。
- 分析选点合法的条件，首先相邻点无包含关系，除此之外任意两个点都有方案使其同时在序列中。
- 此时不合法只能是因为已经钦定其他点对应图形包含，加上初始的强制相交/不相交，可以推出这两个点一定不存在包含关系。
  - 两个图形分别在另一个的内部和外部，另一个图形与这两个同时交，则必与另一个交。
  - 强制在外部/内部情况：图形 $A$ 若与 包含 $B$ 的 $C$ 间接交 且 不与 $B$ 间接交。
    - 这里的间接交指的是经过若干次中转，即 $A$ 交 $k_1$，$k_1$ 交 $k_2$，直到 $k_x$ 交 $B$，其中每一次称为直接交。
    - 树的结构下，不可能不交，但可以先不考虑中间一点 $u$，$u$ 强制与 $B$ 外部内部两图形间接交，必直接交 $B$。
  - 树中：$u$ 的三个子树 $x,y,z$ 中三个点 $a,b,c$（与 $x,y,z$ 不重复）同时在序列中（不妨设 $a$ 含 $b$ 含 $c$），$u$ 间接交 $a,c$ 则必直接交 $b$，则 $u,b$ 间需要有边，与 $b,y$ 不重复矛盾。
  - 则每个点的子树中，至多两个子树中可以选非子树根的点。
- 根据结论，对最优序列构造必有一条链，使所有点满足，在链上或者与链上点直接相连。
  - 理解：链的两端分别在两个有非子树根点在序列中的子树中，链中经过根，则其余子树根可以被包含，链两端再分别延伸向下覆盖。若不能覆盖，选择点过于稀疏，必不优。
- 设 $f_{u,1/0}$ 表示仅考虑子树 $u$ 中点，$u$ 是链的一端，且 $u$ 是/否被选择时最多选择的点数。
- 最终答案需要枚举链的中转点，即：$\max\{\max_{u\in V,v\in son_u}\{f_{u,0}+f_{v,0},f_{u,1}+f_{v,0},f_{u,0}+f_{v,1}\},\max_u\{f_{u,1}\}\}$。
- 转移中，可以选一个子节点 $v$ 作为链中下一个点，其余与 $u$ 相邻且非 $u$ 父亲的点选，即：
  - $f_{u,0}=\max_{v\in son_u}\{\max\{f_{v,0},f_{v,1}\}+deg_u-2\}$
  - $f_{u,1}=\max_{v\in son_u}\{f_{v,0}+1\}$
- 实现中注意，答案的更新要在更新 $v$ 对 $f_u$ 贡献之前，原因是这里 $f_u$ 记录状态所对应的链不能向 $v$ 延伸，$f_u$ 更新之前记录的是 $u$ 向前面儿子延伸的最优选择个数，这样可以覆盖所有，选择 $u$ 两个子树，选其中非根点的状态。

---

## 作者：Celtic (赞：1)

考虑答案在树上长什么样子。

首先答案肯定是一个独立集，因为两两之间没有交。

对于相邻两个圆，他一定是经过中间一个点来连接的，画个图容易发现中间的这个点连接的所有点都能加入答案。

也就是说答案应该是树上一条形如毛毛虫一样的独立集，就是树上的一条链加上每个点周围的点。

这个就可以用类似最大独立集的 dp 来维护，在合并父亲和儿子的 dp 以及计算完一个点的 dp 值时统计答案即可。

具体见代码。

```cpp
#include<bits/stdc++.h>
#define N 2001001
#define MAX 3005
#define eps 1e-10
using namespace std;
typedef long long ll;
typedef double db;
const db PI=acos(-1);
const ll mod=998244353,inv2=(mod+1)/2,inf=1e18,inv3=(mod+1)/3;
inline void read(ll &ret)
{
	ret=0;char c=getchar();bool pd=false;
	while(!isdigit(c)){pd|=c=='-';c=getchar();}
	while(isdigit(c)){ret=(ret<<1)+(ret<<3)+(c&15);c=getchar();}
	ret=pd?-ret:ret;
	return;
}
ll n,x,y,ans;
vector<ll>v[N];
ll f[N][2];
inline void dfs(ll ver,ll fa)
{
	f[ver][1]=1;
	for(int i=0;i<v[ver].size();i++)
	{
		ll to=v[ver][i];
		if(to==fa)
			continue;
		dfs(to,ver);
		ans=max(ans,f[ver][1]+f[to][0]);
		ans=max(ans,f[ver][0]+max(f[to][0],f[to][1])+(ll)v[ver].size()-2);
		f[ver][0]=max({f[to][0],f[to][1],f[ver][0]});
		f[ver][1]=max(f[to][0]+1,f[ver][1]);
	}
	ans=max(ans,max(f[ver][0],f[ver][1]));
	f[ver][0]=max(f[ver][0],f[ver][0]+(ll)v[ver].size()-2);
	return;
}
signed main()
{
	read(n);
	for(int i=1;i<n;i++)
	{
		read(x);
		read(y);
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	exit(0);
}
```

---

## 作者：山田リョウ (赞：0)

首先显而易见的是树上相邻两点不能有包含关系（因为它们之间是交叉关系）。

进行手模后可以发现两个树上距离为 2 的点可以成包含关系，进一步的，一个点 $u$ 的所有相邻点 $v$（互相之间距离为 $2$）是可以叠起来形成一条包含关系的链的。

于是考虑枚举 $a_1$ 后以其为根进行树形 dp，我们现在关系同个点不同子树间的关系。

考虑三个点 $u,v1,v2$（不妨取 $u$ 为根）满足 $(u,v1),(u,v2)$ 是树边，此时 $v1,v2$ 只能是包含或分离关系。

+ 是分离关系，由于若 a 与 b 分离且 b 与 c 相交则 a 与 c 分离的传递性，则 $v1$ 与 $v2$ 子树内所有结点分离，同理 $v2$ 与 $v1$ 子树内所有结点分离，故 $v1$ 子树内的包含关系链和 $v2$ 子树内的包含关系链无法连接。
+ 是包含关系，不失一般性地认为 $v1$ 包含 $v2$。取 $v1$ 任意儿子 $w$，则 $w$ 必然与 $v2$ 分离（因为 $w$ 和 $v2$ 不能相交），类似地有 $v1$ 子树内除去 $v1$ 以外均无法连接 $v2$ 子树内的包含关系链。

综上，枚举根 $a_1=root$，设 $f_u$ 表示 $u$ 子树内最长链，$g_u$ 表示 $u$ 子树内除去 $u$ 以外的最长链，容易列出转移方程：
$$\begin{cases}g_u&=\max_{v\in \operatorname{ch}(u)}\left\{f_v+\left|\operatorname{ch}(u)\right|-1\right\}\\f_u&=\max\left\{g_u,1+\max_{v \in \operatorname{ch}(u)}\left\{g_v\right\}\right\}\end{cases}$$

考虑跑换根 dp 就可以做到线性了。

```cpp
#include<stdio.h>
#include<vector>
int f[100001],g[100001],res;
std::vector<int>edge[100001];
int max(int x,int y){return x>y?x:y;}
void dfs1(int u,int fa){
    f[u]=g[u]=0;
    for(const auto&v:edge[u])
        if(v!=fa)
            dfs1(v,u),f[u]=max(f[u],g[v]),g[u]=max(g[u],f[v]+edge[u].size()-(fa>0)-1);
    f[u]=max(f[u]+1,g[u]);
}
void dfs2(int u,int fa){
    res=max(res,f[u]);
    int mxf=0,cmf=0,mxg=0,cmg=0,tmp_f,tmp_g;
    for(const auto&v:edge[u]){
        if(f[v]>mxf)cmf=mxf,mxf=f[v];
        else cmf=max(cmf,f[v]);
        if(g[v]>mxg)cmg=mxg,mxg=g[v];
        else cmg=max(cmg,g[v]);
    }
    for(const auto&v:edge[u])
        if(v!=fa){
            tmp_f=f[v],tmp_g=g[v];
            g[u]=edge[u].size()>1?(f[v]<mxf?mxf:cmf)+edge[u].size()-2:0,
            f[u]=max((g[v]<mxg?mxg:cmg)+1,g[u]);
            g[v]=edge[v].size()>1?max(g[v]+1,f[u]+edge[v].size()-1):f[u],
            f[v]=max(max(f[v],g[v]),g[u]+1);
            dfs2(v,u);
            f[v]=tmp_f,g[v]=tmp_g;
        }
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1,u,v;i<n;++i)scanf("%d%d",&u,&v),edge[u].push_back(v),edge[v].push_back(u);
    dfs1(1,0),dfs2(1,0),printf("%d",res);
    return 0;
}
```

---

## 作者：lyhqwq (赞：0)

# Solution

很妙的思维题。

首先选出的点一定是一个独立集。

考虑三个按顺序嵌套的橡皮筋 $a,b,c$。一定存在一个在 $a$ 到 $c$ 路径上的点 $x$ 与 $b$ 相交，画图证明不难。

最终的独立集一定是在一条链和其外挂节点上选择，考虑树形 dp。

令 $f_{i,0/1}$ 表示以 $i$ 为根的子树内，$i$ 为链的一端且不在（在）独立集中的答案。

注意在转移过程中也需要更新答案。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=100005;
struct edge{
    int v,nxt;
}edge[N<<1];
int head[N],cnt;
int n,ans;
int deg[N],f[N][2];
void addedge(int u,int v){
    edge[++cnt].v=v,edge[cnt].nxt=head[u],head[u]=cnt;
}
void dfs(int u,int fa){
    f[u][1]=1;
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].v;
        if(v==fa) continue;
        dfs(v,u);
        ans=max(ans,f[u][0]+max(f[v][0],f[v][1]));
        ans=max(ans,f[u][1]+f[v][0]);
        f[u][0]=max(f[u][0],max(f[v][0],f[v][1])+deg[u]-2);
        f[u][1]=max(f[u][1],f[v][0]+1);
    }
    ans=max(ans,max(f[u][0],f[u][1]));
}
int main(){
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        addedge(u,v);
        addedge(v,u);
        deg[u]++,deg[v]++;
    }
    dfs(1,0);
    printf("%d\n",ans);
    return 0;
}


```

---

## 作者：daniEl_lElE (赞：0)

人类智慧。

观察一下充要条件。首先最终选出的嵌套序列相邻两个显然不能再原图上连接。其次画一画得出来应该是一条主链，周围一圈点也可以选。这两个条件合在一起就是充要条件了。

感性理解一下，充分性可以由简单构造得到。第一个条件的必要性是显然的，第二个条件考虑钦定一条主链，如果有选出点距离主链至少为 $2$，那么这个点还要嵌套主链后面的点，就必须与它父亲的父亲（也就是离它最近的主链上的点）相交，显然这是不合法的。

然后怎么做是显然的，直接 $O(n)$ dp 一下即可（即，对所有在主链上的点 dp，用 $0/1$ 表示该点选/不选）。

```cpp
#include <bits/stdc++.h>
#define double long double
#define mid ((l+r)>>1)
using namespace std;
int dp[100005][2],sur[100005],maxv;
vector<int> vc[100005];
void dfs(int now,int fa){
	int pre0=0,pre1=0;
	for(auto v:vc[now]){
		if(v==fa) continue;
		dfs(v,now);
		maxv=max(maxv,max(pre1,pre0)+max(dp[v][1],dp[v][0])+sur[now]-2);
		maxv=max(maxv,pre0+dp[v][0]+1);
		dp[now][0]=max(dp[now][0],max(dp[v][0],dp[v][1]));
		dp[now][1]=max(dp[now][1],dp[v][0]);
		pre0=max(pre0,dp[v][0]);
		pre1=max(pre1,dp[v][1]);
	}
	dp[now][1]++;
	dp[now][0]+=sur[now]-2;
	maxv=max(maxv,max(dp[now][1],dp[now][0]));
}
signed main(){
	int n; cin>>n;
	for(int i=1;i<n;i++){
		int u,v; cin>>u>>v;
		vc[u].push_back(v);
		vc[v].push_back(u);
		sur[u]++,sur[v]++;
	}
	dfs(1,0);
	cout<<maxv;
	return 0;
}
```

---

