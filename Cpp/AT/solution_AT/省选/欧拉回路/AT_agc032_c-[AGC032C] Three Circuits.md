# [AGC032C] Three Circuits

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc032/tasks/agc032_c

$ N $ 頂点 $ M $ 本の辺からなる単純かつ連結な無向グラフが与えられます。 頂点には $ 1 $ から $ N $ の番号が、辺には $ 1 $ から $ M $ の番号がついています。

辺 $ i $ は頂点 $ a_i $ と $ b_i $ を双方向につなぐ辺です。

全ての辺をちょうど $ 1 $ 回ずつ使って $ 3 $ つのサーキットを作ることが可能かどうかを判定してください。

## 说明/提示

### 注釈

サーキットとは辺素だが頂点素とは限らない閉路のことをいう。

### 制約

- 入力はすべて整数である。
- $ 1\ \leq\ N,M\ \leq\ 10^{5} $
- $ 1\ \leq\ a_i,\ b_i\ \leq\ N $
- 与えられるグラフは単純かつ連結。

### Sample Explanation 1

\- 以下の図のように、全ての辺をちょうど $ 1 $ 回ずつ使って $ 3 $ つのサーキットを作ることができます。 !\[b8c8e2245d45a31cf39749b0a49fc2bd.png\](https://img.atcoder.jp/agc031/b8c8e2245d45a31cf39749b0a49fc2bd.png)

### Sample Explanation 2

\- $ 3 $ つのサーキットを作る必要があります。

## 样例 #1

### 输入

```
7 9
1 2
1 3
2 3
1 4
1 5
4 5
1 6
1 7
6 7```

### 输出

```
Yes```

## 样例 #2

### 输入

```
3 3
1 2
2 3
3 1```

### 输出

```
No```

## 样例 #3

### 输入

```
18 27
17 7
12 15
18 17
13 18
13 6
5 7
7 1
14 5
15 11
7 6
1 9
5 4
18 16
4 6
7 2
7 11
6 3
12 14
5 2
10 5
7 8
10 15
3 15
9 8
7 15
5 16
18 15```

### 输出

```
Yes```

# 题解

## 作者：CYJian (赞：15)

这道题我们可以从点的度数入手。

首先不难发现，由于所有点都在环上，所以需要每个点的度数都是偶数。则如果存在一个点的度数是奇数，则一定不合法。

那么这时候我们发现，由于每个点度数都是偶数，则图中一定存在一条欧拉回路，即所有点都在一个大环上。

由于这个题目中的环是可以拼接的，意思是，两个有公共点的环拼起来还是一个环，有了上面一条，可以将原问题变成：是否可以从一个大环中找出三个没有交的小环。

然后再考虑，如果存在一个点的度数 $\ge 6$，那么一定合法。考虑做欧拉回路的过程，每两次走到这个点，就可以分裂出一个环，则这个点就可以分裂出三个以上的环，那么随便选出三个之后，直接拼了剩下所有的边，就可以了。

然后考虑所有点的度数 $\leq 2$，加上连通的条件，那么所有点就连成了一个环。显然不符合题目条件。

这时候，剩下的情况就只剩下了若干个度数为 $4$ 和 $2$ 的点。

讨论度数为 $4$ 的点的个数：

一个点：画画图就能发现，只可能存在两个环套在一个点上的情况。这样只能弄出两个环，弄不出三个。

两个点：考虑这两个点连通的情况下，一定有至少两条不交的链，端点分别为这两个点。然后剩下的两条边就有了两种情况：一种是成了连接两个点的两条链（图一），一种是分别在两个点上挂两个环（图二）。不难发现，满足条件的只有图二。这个用一个 dfs，去掉度数为 $4$ 的两个点之后的四条链，有多少条链的两端原本连接的点是同一个点就能判断。

![图一](https://cdn.luogu.com.cn/upload/image_hosting/0q5jqho9.png)

![图二](https://cdn.luogu.com.cn/upload/image_hosting/nc856yae.png)

三个及以上的点：显然不论如何，都能分出至少 $3$ 个环。

那么经过上面的讨论，我们就可以判断出这个图能不能分成三个环了。

$\rm Code$：

```cpp
template<typename T> inline void chkmax(T&a, T b) { a = a > b ? a : b; }

#define ERROR return puts("No"), 0
#define OK return puts("Yes"), 0

const int MAXN = 100010;

vector<int>to[MAXN];
int vis[MAXN];
int A, B;

inline void dfs(int x) {
	vis[x] = 1;
	for(auto u : to[x])
		if(vis[u] == 2) A ? B = u : A = u;
		else if(!vis[u]) dfs(u);
}

int main() {
	int n = ri, m = ri, mxd = 0, mxc = 0;
	for(int i = 1; i <= m; i++) {
		int u = ri, v = ri;
		to[u].push_back(v);
		to[v].push_back(u);
	}
	for(int i = 1; i <= n; i++)
		if(to[i].size() & 1) ERROR;
		else if(to[i].size() > mxd) mxd = to[i].size(), mxc = 1;
		else mxc += mxd == to[i].size();
	if(mxd >= 6) OK;
	else if(mxd == 2 || mxc == 1) ERROR;
	else if(mxc > 2) OK;
	else {
		int cnt = 0;
		for(int i = 1; i <= n; i++)
			if(to[i].size() == 4)
				vis[i] = 2;
		for(int i = 1; i <= n; i++)
			if(!vis[i]) A = B = 0, dfs(i), cnt += A == B;
		puts(cnt ? "Yes" : "No");
	}
	return 0;
}
```

---

## 作者：myee (赞：4)

### 前言

我的做法和大家好像都不太一样，但是这个做法似乎可以拓展到环数更多的情况。

### 思路

首先这张图必须存在欧拉回路，也即各点度数均为偶数。

然后可以证明，连通图**只要能拆成 $\ge j$ 个环，就可以拆成 $j$ 个环**。

考虑**缩二度点**，缩到图上各点度数均 $\ge4$；一但出现一对重边，立刻用进 $3$ 个环的要求内，然后删去该组重边。

如果某时刻剩下的环数目不做要求，则必然可行。

如果剩下的图上每个点度数均 $\ge4$ 且无重边，考虑操作剩下来的点集。

如果还要求 $1\sim2$ 个环，合法等价于点集大小 $\ge2$。这个是容易证明的。

如果要求 $3$ 个环，合法等价于点集大小 $\ge5$。这个结论的证明细节颇为繁杂，此处略去。

然后就完了。总复杂度 $O(m)$ 或者 $O(m\log m)$，根据找重边的方法来决定。

这个做法似乎确实可以拓展到 $4$ 个甚至更多的环，不过最后的结论推起来可能会更复杂一点。

### Code

代码其实很好写。

```cpp
std::map<std::pair<uint,uint>,uint>M;
std::vector<uint>E[100005];uint Deg[100005];
uint U[2000005],V[2000005],tp;bol Ok[2000005];
int main()
{
#ifdef MYEE
    freopen("QAQ.in","r",stdin);
    freopen("QAQ.out","w",stdout);
#endif
    uint n,m;scanf("%u%u",&n,&m);
    while(m--){
        scanf("%u%u",U+tp,V+tp);
        E[--U[tp]].push_back(tp),E[--V[tp]].push_back(tp);
        if(U[tp]>V[tp])std::swap(U[tp],V[tp]);
        M[{U[tp],V[tp]}]=tp,Deg[U[tp]]++,Deg[V[tp]]++,Ok[tp++]=true;
    }
    uint k=3;
    std::vector<uint>Q;
    for(uint i=0;i<n;i++)
        if(Deg[i]&1)return puts("No"),0;else if(Deg[i]==2)Q.push_back(i);
    while(Q.size()&&k){
        uint p=Q.back();Q.pop_back();if(!Deg[p])continue;
        uint u=-1,v=-1;for(auto e:E[p])if(Ok[e])Ok[(~u?v:u)=e]=false;
        M.erase({U[u],V[u]}),M.erase({U[v],V[v]});
        Deg[p]=0,u=U[u]^V[u]^p,v=U[v]^V[v]^p;
        if(u>v)std::swap(u,v);
        if(M.count({u,v}))
        {
            Ok[M[{u,v}]]=false,M.erase({u,v}),k--;
            if((Deg[u]-=2)==2)Q.push_back(u);
            if((Deg[v]-=2)==2)Q.push_back(v);
        }
        else E[U[tp]=u].push_back(tp),E[V[tp]=v].push_back(tp),Ok[M[{u,v}]=tp++]=true;
    }
    if(!k){puts("Yes");return 0;}
    uint d=0;
    for(uint i=0;i<n;i++)if(Deg[i])d++;
    puts((k<=2?d>=2:d>=5)?"Yes":"No");
    return 0;
}
```



---

## 作者：StudyingFather (赞：4)

首先要想能弄出环，整个图本身就应该是一个欧拉图（存在一条路径能将所有边恰好经过一次，且起点终点相同）。

因此先判断图上是否存在奇度数点，如果有当然不可行。

现在图上只有偶度数点了。

首先有一个显然的结论：经过同一个点的两个环可以合并成一个，当然也可以拆分。这意味着，一个度数为 $d$ 的点可以拆出 $\dfrac{d}{2}$ 个环。

因此我们得到了第一个可行的条件：如果存在一个度数大于 $6$ 的点，则一定可行。

排除这种情况后，图上只有度数为 $4,2$ 的点了。

如果图上只有度数为 $2$ 的点，显然只有一个环。

图上只有一个度数为 $4$ 的点，只有两个环。

两个度数为 $4$ 的点呢？显然这两个点之间至少有两条不相交路径相连。

剩下的可以分两种情况：

1. 两个点之间有四条不相交路径，只能连两个环。
2. 除了两个点之间的两条不相交路径之外，这两个点上各挂一个环，这样两个点上挂的环，加上两个点之间的两条路径，刚好够三个环。

假如有至少三个度数为 $4$ 的点呢？这时候一定是可行的。

考虑按如下方案构造：首先从 4 度点 $A$ 开始连两个回路，如果存在一个点 $B$ 被一个回路访问两次，我们就可以把这个回路拆成两条回路，由于还有一个 4 度点 $C$ 存在，只需在 $C$ 点拆分回路，即可凑足三个回路。

否则，一定存在点 $B,C$ 被两个回路访问恰好各一次，我们还是可以拆环（$A \to B \to A$，$B \to C \to B$，$A \to C \to A$）以形成三条回路。

```cpp
// Problem : C - Three Circuits
// Contest : AtCoder - AtCoder Grand Contest 032
// URL : https://atcoder.jp/contests/agc032/tasks/agc032_c
// Memory Limit : 1024 MB
// Time Limit : 2000 ms
// Powered by CP Editor (https://github.com/cpeditor/cpeditor)

#include <iostream>
#include <vector>
using namespace std;
vector<int> e[100005];
int p,q,vis[100005];
void dfs(int u)
{
 vis[u]=1;
 for(auto v:e[u])
  if(vis[v]==-1)
  {
   if(p)q=v;
   else p=v;
  }
  else if(!vis[v])dfs(v);
}
int main()
{
 ios::sync_with_stdio(false);
 int n,m;
 cin>>n>>m;
 for(int i=1;i<=m;i++)
 {
  int u,v;
  cin>>u>>v;
  e[u].push_back(v);
  e[v].push_back(u);
 }
 int maxd=0,cnt=0;
 for(int i=1;i<=n;i++)
 {
  int t=e[i].size();
  if(t%2)
  {
   cout<<"No"<<endl;
   return 0;
  }
  if(t>maxd)
   maxd=t,cnt=1;
  else if(t==maxd)cnt++;
 }
 if(maxd>=6)
  cout<<"Yes"<<endl;
 else if(maxd==4)
 {
  if(cnt>=3)
   cout<<"Yes"<<endl;
  else if(cnt==1)
   cout<<"No"<<endl;
  else
  {
   for(int i=1;i<=n;i++)
    if(e[i].size()==4)vis[i]=-1;
   for(int i=1;i<=n;i++)
    if(!vis[i])
    {
     p=q=0;
     dfs(i);
     if(p==q)
     {
      cout<<"Yes"<<endl;
      return 0;
     }
    }
   cout<<"No"<<endl;
  }
 }
 else cout<<"No"<<endl;
 return 0;
}
```

---

## 作者：xht (赞：2)

## [Three Circuits](https://atcoder.jp/contests/agc032/tasks/agc032_c)

### 题意

- 给定一张 $n$ 个点 $m$ 条边的无向图，问能否将无向图拆成三个环，使得每条边恰好在一个环中。
- $n,m \le 10^5$。

### 题解

首先要是欧拉回路。

若度数最大值 $\ge 6$ 则有解，$= 2$ 则无解，接下来考虑 $=4$ 的情况。

若度数为 $4$ 的点超过 $3$ 个则有解，$1$ 个则无解，接下来考虑 $2$ 个的情况。

只有两种形态，一种有解一种无解，讨论一下即可。

### 代码

```cpp
const int N = 1e5 + 7;
int n, m, d[N], X, Y;
vi e[N];

void dfs(int x, int f) {
	if (x == Y) return;
	if (x == X) prints("Yes"), exit(0);
	for (int y : e[x])
		if (y != f) dfs(y, x);
}

int main() {
	rd(n, m);
	for (int i = 1, x, y; i <= m; i++)
		rd(x, y), ++d[x], ++d[y], e[x].pb(y), e[y].pb(x);
	for (int i = 1; i <= n; i++) if (d[i] & 1) return prints("No"), 0;
	int mx = *max_element(d + 1, d + n + 1);
	if (mx == 2) return prints("No"), 0;
	if (mx >= 6) return prints("Yes"), 0;
	int cnt = 0;
	for (int i = 1; i <= n; i++) cnt += d[i] == 4;
	if (cnt == 1) return prints("No"), 0;
	if (cnt >= 3) return prints("Yes"), 0;
	for (int i = 1; i <= n; i++)
		if (d[i] == 4) {
			if (X) Y = i;
			else X = i;
		}
	for (int z : e[X]) dfs(z, X);
	prints("No");
	return 0;
}
```

---

## 作者：o51gHaboTei1 (赞：2)

#### C

好题！！1

我还读错题了。

先考虑能拆分成若干个环，显然所有点度数都是偶数，无向图，可以识别出来存在欧拉回路。

然后就开始讨论一波：

- 最大度数 $\geq 6$ 显然有解，设该节点为 $p$，直接拿一个欧拉回路出来，按照每次离开/回到 $p$ 的过程分成一个环，则至少有 $3$ 个，如果有超过 $3$ 个简单环对于最后一个环包揽剩下的所有路径即可。

- 假设度数全为 $2$ 本身是一个简单环，显然无解；

- 则现在必存在度数为 $4$ 的节点。讨论数量：若数量为 $1$，显然是两个环夹一个节点的形状，无解；若数量为 $2$ 则比较困难，我们还是考虑构造出来一个最外层的环。找到两个度数为 $4$ 的节点，剩下只有可能存在两种构造方式：

- 添加两条链在两个节点之间。

- 添加两个环去夹两个节点。

[![xc3mTK.png](https://s1.ax1x.com/2022/10/21/xc3mTK.png)](https://imgse.com/i/xc3mTK)
[![xc3ew6.png](https://s1.ax1x.com/2022/10/21/xc3ew6.png)](https://imgse.com/i/xc3ew6)

- 显然对于第一个情况是至多构造两个环的；对于第二个情况显然存在构造三个简单环的方案。通过 dfs 删除度数为 $4$ 节点的残余图即可特判两个情况。

- 对于数量 $=$ $3$ 的情况，我们显然可以找到形如图中红色边所连接的三个节点：

[![xc3tTf.md.png](https://s1.ax1x.com/2022/10/21/xc3tTf.md.png)](https://imgse.com/i/xc3tTf)

- 设为 $A,B,C$，显然将红色边分别作为三个环的一部分可以构造出来三个环。

- 对于数量 $\geq4$ 的情况，我们还是确定最外层的环，定义环路径为外层大环上两个节点的路径，显然任意两点之间都存在两条环路径。

- 现在度数为 $4$ 的点们除了环上的边两两还连了边（但保证每个点只从外界接受两条边），我们任意找三个节点满足 $A-B,A-C$ 且 $B$ 到 $C$ 的一条环路径上没有**包含剩下的所有度数为 $4$ 的节点**。这样的三个节点一定能被找到，因为假设一条环路径上装了剩下的所有度数为 $4$ 的节点，那么另一条环路径一定一个都没装，用另外一条环路径即可。


- 先通过 $A-C$ 边从 $A$ 走到 $C$ 去，沿环上走到 $B$ 去，然后再由 $A-B$ 边走到 $B$ 去构造出一个环。去掉这些边后原图至少保留一个节点满足度数为 $4$，并且现在原图还满足度数全为偶数，存在欧拉回路等性质，所以**一定可以构造出来至少两个简单环**，显然对于多出来的简单环直接欧拉回路合并了。

- 以度数为 $4$ 的节点数量为 $5$ 为例：

[![xc8wE6.png](https://s1.ax1x.com/2022/10/21/xc8wE6.png)](https://imgse.com/i/xc8wE6)
[![xc8aHx.png](https://s1.ax1x.com/2022/10/21/xc8aHx.png)](https://imgse.com/i/xc8aHx)

比如我们很憨，找到了图示的 $A,B,C$ 节点。还很逊，想在走 $B-C$ 环路径时走橙黄色那一条，发现含了所有的度数为 $4$ 的节点，这时候直接换成绿色那条换路径就好了，生下了 $2$ 个度数为 $4$ 的节点，显然存在至少两个简单环与一个欧拉路径（刨去 A 点后的图）。


一些题外话，我们发现甚至随便选出现了直接把 $A$ 点从原图中割离出去的情况，所以如果真要输出构造方案还是有点烦人的（

时间复杂度线性。

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 4e5 + 5;
int n,m,head[Len],cnt;
struct node
{
	int next,to;
}edge[Len << 1];
inline void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
int t,tt,du[Len],sm[8],mxd,ct,vis[Len];
void dfs(int x)
{
	vis[x] = 1;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(vis[to] == 2){if(t) tt = to;else t = to;}
		if(!vis[to]) dfs(to);
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		add(x , y) , add(y , x);
		du[x] ++ , du[y] ++;
	}
	bool fg = 1;
	for(int i = 1 ; i <= n ; i ++) 
	{
		fg &= (du[i] % 2 == 0);
		mxd = max(mxd , du[i]);
		if(du[i] < 6) sm[du[i]] ++;
	}
	if(!fg) return puts("No") & 0;
	if(mxd >= 6) return puts("Yes") & 0;
	if(mxd == 2 || sm[4] == 1) return puts("No") & 0;
	else if(sm[4] == 2)
	{
		t = tt = 0;
		for(int i = 1 ; i <= n ; i ++) if(du[i] == 4) vis[i] = 2;
		for(int i = 1 ; i <= n ; i ++) if(!vis[i]){t = tt = 0;dfs(i);ct += (t == tt);}
		if(ct) puts("Yes");
		else puts("No");
		return 0;
	}
	puts("Yes");
	return 0;
}
```A

---

## 作者：zerc (赞：2)

先补一张原题面的样例解释：

![b8c8e2245d45a31cf39749b0a49fc2bd.png](https://img.atcoder.jp/agc031/b8c8e2245d45a31cf39749b0a49fc2bd.png)

很明显的，我们发现对于合法的方案，每个点的度一定为偶数，这也提示我们要对度数分类讨论：

1. 对于度 $\ge 6$ 的点，至少可以拆成三个环；

2. 对于度为 $4$ 的点，一定可以拆成两个环；

3. 对于度为 $2$ 的点，只能拆成一个环。

> 其实有一个显然的结论：经过同一个点的两个环可以合并，也可以拆分，一个度数为 $d$ 的点可以拆出 $\dfrac{d}{2}$ 个环。

接下来就是如何判断：

1. 含有奇数度数的点一定不合法；

2. 含有度数 $\ge 6$ 的点一定合法；

3. 含有度数为 $4$ 且不含度数 $\ge 6$的点：

    1. 如果只有一个，一定不合法；

    2. 对于两个点，又可以分成两种情况（如下图），显然左图不合法，右图合法；
 
    3. 有 $\ge 3$ 个一定合法；

4. 只有度数为 $2$ 的点，一定不合法。

![](https://cdn.luogu.com.cn/upload/image_hosting/vatdsysm.png)

唯一麻烦的地方在于有两个度为 $4$ 点时的 check，一种比较简单的实现思路是从其中一个点开始 dfs，如果经过另外一个点 $4$ 次，则认为不合法，经过 $2$ 次，认为合法。

代码实现的话也很简单，`st[]` 记录度为 $4$ 的点，也就是 `dfs()` 中的起点和终点，`cntt` 记录路径数，`vis[]` 记录经过**边**的编号。


```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;

struct edge {int to, nxt;} e[maxn<<1];
int cnt = 1, head[maxn];

int n, m, cnt4, cnt6, cntt, deg[maxn], st[2];
bool vis[maxn<<1];

void add(int u, int v) {
    e[++cnt] = {v, head[u]}, head[u] = cnt, deg[u]++;
}

void dfs(int u) {
    for (int i = head[u]; i; i = e[i].nxt) {
        if (e[i].to == st[1]) return cntt++, void();
        if (vis[i]  == 0)
            vis[i] = vis[i^1] = 1, dfs(e[i].to);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add(u, v), add(v, u);
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] &  1) return puts("No" ),0;
        if (deg[i] == 4) cnt4++, st[cnt4%2]=i;
        if (deg[i] >= 6) cnt6++;
    }
    if (cnt4 == 2) dfs(st[0]);
    if (cnt6 >= 1) return puts("Yes"), 0;
    if (cnt4 <= 1) return puts("No" ), 0;
    if (cnt4 >= 3) return puts("Yes"), 0;
    if (cntt == 2) return puts("Yes"), 0;
    return puts("No"), 0;
}
```

---

## 作者：LastKismet (赞：0)

# Sol
要想分成多个环，那么显然不允许奇数度数节点存在。

首先考虑三个以上环聚合于一点的情况，此时这一点度数不小于 $6$，那么必然有解。

排除这种情况后，图中只剩下度数为 $2$ 和为 $4$ 的节点，且图连通，$2$ 度点有点普通，从 $4$ 度点入手。

倘若四度点数小于 $2$，那么显然不存在 $3$ 个环，故而无法满足条件。

倘若四度点数大于 $2$，那么显然存在至少 $3$ 个环，可以满足条件。这两条自己画一下图就可以得知。

而两个四度点的情况是特殊的，如果这两个四度点同时处于两个环中，那么显然只能分出两个环；否则，就是两个点各存在于一个包括对方的大环与各自的两个小环中，呈糖果状，则有解。

如何判断呢？从任意一个四度点开始遍历其四条链直到到达任意一个四度点停止，倘若能走到自己，就是后者情况，否则为前者情况。

# Code
```cpp
int n,m;
int dg[N];
vec<int> g[N];
int cnt;
bool pd[N];
vec<int> v;
int tim[N];

void dfs(int now,int fa){
    if(pd[now])return ++tim[now],void();
    for(auto y:g[now])if(y!=fa)dfs(y,now);
}

inline void Main(){
    read(n,m);
    rep(i,1,m){
        int a,b;read(a,b);
        g[a].pub(b);g[b].pub(a);
        ++dg[a],++dg[b];
    }
    rep(i,1,n)if(dg[i]&1)return put("No");
    rep(i,1,n){
        if(dg[i]>4)return put("Yes");
        if(dg[i]==4)++cnt,v.pub(i),pd[i]=1;
    }
    if(cnt>2)return put("Yes");
    if(cnt<2)return put("No");
    for(auto i:g[v[0]])dfs(i,v[0]);
    put(tim[v[0]]?"Yes":"No");
}
```

---

## 作者：RainsAFO (赞：0)

由于三环并集包含整个图，所以该图必有欧拉回路。

对点的度数进行讨论：

$1.$有一点度数大于等于$6$，从这个点至少可以拆出三个环，合法。

$2.$所有点度数小于等于$2$，整个图就是一个环，不合法。

$3.$除去前两种情况的图点的度数只能为$2/4$，度数为$2$的仅能在一个环中，于是至少有两个度数为$4$的点，才能合法。

code:

```cpp
int n , m , u , v , ans = 0;

const int N = 1e5 + 5;

int vi[N];

vector <int> e[N];

int f1 , f2;

void dfs(int x){
	vi[x] = 1;
	for(auto y : e[x]){
		if(vi[y] == 2){
			if(f1)
				f2 = y;
			else
				f1 = y;
		}
		else
			if(!vi[y])
				dfs(y);
	}
}

int main(){
	cin >> n >> m;
	for(int i = 1; i <= m; i++){
		cin >> u >> v;
		e[u].push_back(v) , e[v].push_back(u);
	}
	int maxx = 0 , k = 0;
	for(int i = 1; i <= n; i++){
		if(e[i].size() & 1)
			fail;
	 	if(e[i].size() > maxx)
	 		maxx = e[i].size() , k = 1;
	 	else
	 		k += (maxx == e[i].size());
	}
	if(maxx >= 6)
		tru;
	if(maxx == 2 || k == 1)
		fail;
	if(k > 2)
		tru;
	for(int i = 1; i <= n; i++)
		if(e[i].size() == 4)
			vi[i] = 2; 
	for(int i = 1; i <= n; i++)
		if(!vi[i])
			f1 = f2 = 0 , dfs(i) , ans += f1 == f2;
	if(ans)
		tru;
	fail;
```


---

