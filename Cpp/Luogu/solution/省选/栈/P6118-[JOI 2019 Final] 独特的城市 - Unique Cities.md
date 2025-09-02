# [JOI 2019 Final] 独特的城市 / Unique Cities

## 题目背景

JOI 2019 Final T5

由于数据点较多，本题只评测其中的部分数据。

## 题目描述

JOI 国有 $N$ 个城市，城市从 $1$ 到 $N$ 编号。这些城市被 $N-1$ 条双向道路连接，第 $i$ 条路连接两个城市 $A_i$ 和 $B_i$。从任何城市出发，可以到达所有城市。

JOI 国有些特产，每种特产的编号都在 $1$ 到 $M$ 之间（包括 $1$ 和 $M$），但是 $1$ 到 $M$ 的某些整数可能不代表 JOI 国的特产。JOI 国的每个城市都产一种特产。$j$ 城产的特产是 $C_j$。多个城市可能产相同的特产。

我们定义两个城市之间的距离为从一个城市到另一个城市需要经过的最少道路数，对于城市 $x$，我们定义城市 $y$（$y\neq x$）是**独特的城市**当且仅当对于任何一个城市 $z$（$z\neq x,z\neq y$），$x$ 与 $y$ 间的距离不等于 $x$ 与 $z$ 之间的距离。

JOI 国交通部部长 K 先生想知道对于城市 $j$ 的**独特的城市**一共能产多少种特产。

给出 JOI 国的道路信息与每个城市产的特产，写一个程序计算对于每个城市的**独特的城市**，一共能产多少种特产。

## 说明/提示

样例解释 $1$：  

对于城市 $1$，它的独特城市是城市 $2,3$，城市 $2$ 产特产 $2$，城市 $3$ 产特产 $3$，一共产两种特产，因此答案是 $2$；  

对于城市 $2$，没有独特城市，因此输出 $0$；
  
对于城市 $3$，它的独特城市是城市 $1$，城市 $1$ 产特产 ，因此答案是 $1$；  

对于城市 $4$，它的独特城市是城市 $1,3$，城市 $1,3$ 均产特产 $1$，因此答案是 $1$；  

对于城市 $5$，它的独特城市是城市 $1,3$，城市 $1,3$ 均产特产 $1$，因此答案是 $1$。  

注意：没有城市产特产 $3$。  

对于 $4\%$ 的数据，$N\le 2000$。

另有 $32\%$ 的数据，$M=1$。

另有 $32\%$ 的数据，$M=N,C_j=j(1\le j \le N)$。

对于 $100\%$ 的数据，$1\le N \le 2\times 10^5,1\le M,A_i,B_i \le N,A_i \neq B_i,1\le C_j \le M$。

## 样例 #1

### 输入

```
5 4
1 2
2 3
3 4
3 5
1 2 1 2 4```

### 输出

```
2
0
1
1
1```

## 样例 #2

### 输入

```
7 1
1 2
2 3
3 4
4 5
5 6
6 7
1 1 1 1 1 1 1```

### 输出

```
1
1
1
0
1
1
1```

## 样例 #3

### 输入

```
10 10
2 6
5 8
10 8
1 4
10 6
4 5
10 7
6 9
3 7
1 2 3 4 5 6 7 8 9 10```

### 输出

```
4
3
4
2
0
2
2
0
3
2```

## 样例 #4

### 输入

```
22 12
9 6
12 13
4 20
21 22
3 19
2 9
6 18
18 11
18 3
16 2
6 4
3 17
16 10
8 16
22 1
16 14
15 8
9 21
2 12
21 5
12 7
1 1 4 8 4 11 7 6 7 11 6 11 10 4 7 5 3 12 9 6 12 2```

### 输出

```
2
0
1
1
1
1
1
0
0
1
2
0
1
1
2
0
2
1
2
3
0
0```

# 题解

## 作者：随情英 (赞：7)

首先，一个城市的独特城市（下称独特点）， 本质上就是以一个点为根时，深度唯一的点。

然后，有一个显然的性质， 一个城市的独特点， 只会在以该点为根时，向下最长的链上，不然总可以在最长链上找到一个点与它深度相同。

接着，找到这棵树的直径。那么该点向下的最长链在一定是直径两端点到该点较长路径上，也即独特点只会在其中一条路径上。

这时候，我们只要以直径两端点，各 $dfs$ 一次统计答案， 取较大的即可（其中至少一个答案为 $0$)。

考虑如何统计答案，在 $dfs$ 过程中，用一个栈维护根节点到该点的独特点，再用一个桶记录每个特产出现次数，在过程中记录桶的大小。

如何维护栈是关键。

先考虑以一个根节点第一次 dfs，计算每个点向下最长链和次长链长度，并记录最长链所在的儿子，然后第二遍 dfs

过程如下：
1. 将父节点入栈。
2. 将栈中节点到该点距离 $\leq$ 该点向下次长链的弹出，不会对任何点产生影响。（注意到一次 $dfs$ 只考虑当前根节点到该点的独特点）
3. 遍历最长链的儿子。
4. 将栈中节点到该点距离 $\leq$ 该点向下最长链的弹出，不会对除最长链上点外产生影响。
5. 该点答案为桶的不重元素个数
6. 处理其他儿子
7. 回溯，如果该点为叶节点，将父节点弹出。


```cpp
/*
 * @Autor: suiqingying
 * @Date: 2020-11-17 18:38:50
 * @LastEditors: suiqingying
 * @LastEditTime: 2020-11-18 18:59:29
 */
#include <bits/stdc++.h>
inline int read()
{
    register int x = 0, f = 1;
    register char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        x = x * 10 + c - '0', c = getchar();
    }
    return x * f;
}
const int maxn = 2e5 + 10;
int tot, head[maxn], nxt[maxn << 1], ver[maxn << 1];
void add(int u, int v)
{
    ver[++tot] = v;
    nxt[tot] = head[u];
    head[u] = tot;
}
int c[maxn];
int rt1, rt2;
namespace GetDiameter
{
    int maxdep = 0;
    void dfs(int x, int fa, int dep)
    {
        if (dep > maxdep)
        {
            rt2 = x;
            maxdep = dep;
        }
        for (int i = head[x]; i; i = nxt[i])
        {
            register int y = ver[i];
            if (y == fa)
            {
                continue;
            }
            dfs(y, x, dep + 1);
        }
    }
    inline void work()
    {
        dfs(1, 0, 1);
        rt1 = rt2, maxdep = 0;
        dfs(rt1, 0, 1);
    }
} // namespace GetDiameter
int ans[maxn], cnt[maxn];
int depth[maxn], md1[maxn], md2[maxn], son[maxn];
void dfs1(int x, int fa)
{
    depth[x] = depth[fa] + 1;
    md1[x] = md2[x] = son[x] = 0;
    for (register int i = head[x]; i; i = nxt[i])
    {
        register int y = ver[i];
        if (y == fa)
        {
            continue;
        }
        dfs1(y, x);
        if (md1[y] > md1[x])
        {
            md2[x] = md1[x];
            md1[x] = md1[y];
            son[x] = y;
        }
        else if (md1[y] > md2[x])
        {
            md2[x] = md1[y];
        }
    }
    if (!son[x])
    {
        md1[x] = depth[x];
    }
}
inline void addx(register int x)
{
    cnt[c[x]]++;
    if (cnt[c[x]] == 1)
    {
        cnt[0]++;
    }
}
int top, s[maxn];
inline void delx(register int x)
{
    cnt[c[x]]--;
    if (cnt[c[x]] == 0)
    {
        cnt[0]--;
    }
    // if(cnt[c[s.top()]])
    top--;
}
void dfs2(int x, int fa)
{
    if (fa)
    {
        s[++top] = fa;
        addx(fa);
    }
    while (top && depth[x] - depth[s[top]] <= md2[x] - depth[x])
    {
        // <
        delx(s[top]);
    }
    if (son[x])
    {
        dfs2(son[x], x);
    }
    //ans[x] = std::max(ans[x], cnt[0]);
    while (top && depth[x] - depth[s[top]] <= md1[x] - depth[x])
    {
        delx(s[top]);
    }
    ans[x] = std::max(ans[x], cnt[0]);
    for (register int i = head[x]; i; i = nxt[i])
    {
        register int y = ver[i];
        if (y == fa || y == son[x])
        {
            continue;
        }
        dfs2(y, x);
    }
    if (fa && top && s[top] == fa)
    {
        delx(s[top]);
    }
}
inline void solve(register int rt)
{
    dfs1(rt, 0), dfs2(rt, 0);
}
int main()
{
    //    freopen("1.in", " r", stdin);
    register int n = read(), m = read();
    for (register int i = 1; i < n; ++i)
    {
        register int x = read(), y = read();
        add(x, y), add(y, x);
    }
    for (register int i = 1; i <= n; ++i)
    {
        c[i] = read();
    }
    GetDiameter::work();
    solve(rt1), solve(rt2);
    for (register int i = 1; i <= n; ++i)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
}


---

## 作者：RyexAwl (赞：5)

首先，定义“点 $t$ 对点 $u$ 有贡献”等价于 $t$ 是 $u$ 的独特的城市。

钦定点 $u$ 为根，令点集 $L_u$ 表示到所有到点 $u$ 距离最远的叶子节点构成的集合，对点 $u$ 有贡献的点一定在 $L_u$ 中所有点到 $u$ 的路径的交上。

![](https://cdn.luogu.com.cn/upload/image_hosting/6mks5uvn.png)

注意，路径交上的所有点并不都一定对 $u$ 有贡献。

因此一个想法就是考虑找到随便一个点 $v$ 距离点 $u$ 最远，考察 $u,v$ 两点间的路径上的点。

而考虑离点 $u$ 最远的点，可以选一条直径 $s-t$，$s,t$ 两个点中一定存在一个点是距离点 $u$ 最远的点。

进而问题就转化成了：给定一个点 $rt$，以 $rt$ 为根，求出每个点 $u$ 到 $rt$ 路径上所有对点 $u$ 有贡献的点的颜色数。

分别以 $s,t$ 为 $rt$ 求一遍上面的问题即可。 

接下来考虑如何去求解上面转化后的问题。

考虑一个在点 $u$ 到根节点路径上的点 $p$ 不会对点 $u$ 产生贡献的充分必要条件：存在一个点 $t$ 使得 $t$ 与 $u$ 的距离等于 $p$ 与 $u$ 的距离，按照点 $t$ 的位置分类讨论：

* $t$ 在 $u$ 子树内。

* $t$ 在 $u$ 子树外。

考虑维护出一个点集 $T_u$，$\forall x\in T_u$ 满足：

* $x$ 在根节点到 $fa[u]$ 的路径上。

* 不存在一个点 $t$ 在 $u$ 的子树外，使得 $dist(u,t)=dist(u,x)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/tocapdq1.png)

同时考虑点集 $S_u$，$\forall x\in S_u$ 满足：

* $x$ 在根节点到 $u$ 的路径上。

* 不存在一个点 $t$ ，使得 $dist(u,t)=dist(u,x)$。

并且 $S_u\subseteq T_u$，删掉 $T_u$ 中所有满足存在一个点 $t$ 在 $u$ 子树内，使得 $dist(u,x)=dist(u,t)$ 的点 $x$ 即可将 $T_u$ “变成” $S_u$。

考虑 $u$ 的一个儿子 $v$，想要构造出 $T_v$，需要对 $T_u$ 进行哪些 “改造”（或者说点集如何变化）。

$v$ 的子树外等价于 $fa[v]$ 的子树外并上 $v$ 的兄弟子树

* 先令 $T_v\gets T_u\cup \{u\}$。

* 删掉 $T_v$ 中所有满足存在一个点 $t$ 满足 $t$ 属于 $v$ 的兄弟的子树中，$dist(u,t) = dist(u,x)$ 的点 $x$。

而 “删掉 $T_v$ 中所有满足存在一个点 $t$ 满足 $t$ 属于 $v$ 的兄弟的子树中，$dist(u,t) = dist(u,x)$ 的点 $x$”，可以转化成 “删掉 $T_v$ 中所有 $dist(u,x) <= \text{v 的所有兄弟子树的最大深度 + 1} $ 的点 $x$。

考虑对该树做长链剖分，令点 $u$ 的长儿子为 $son[u]$，$\mathrm{maxdist(u)}$ 表示 $u$ 子树内距离 $u$ 距离最远的点与 $u$ 的距离，$ts[u]$ 表示 $u$ 的次长儿子，$\mathrm{len(u)}=\mathrm{maxdist(ts[u])}+1$。

注意到，对于 $u$ 的所有非长儿子，在点集 $T_u\cup\{u\}$ 中要删除的点集都一样。

而对于点 $u$ 的长儿子，要删除的点集为 $T_u\cup\{u\}$ 中所有满足 $dist(u,x)\le \mathrm{len(u)}$ 的点 $x$。

考虑在 DFS 的过程中维护点集 $T_u$，在进入子树 $u$ 前，全局维护的信息应为 $T_u$ 的信息。

进入子树 $u$ 后依次进行以下操作：

* 删除当前全局维护的点集中所有满足 $dist(u,x)\le \mathrm{len(u)}$ 的点 $x$。

* 在当前全局维护的点集中加入点 $u$。

* 递归长子树。

* 删掉当前全局维护的点集中所有满足 $dist(u,x)\le \mathrm{maxdist(u)}$，当前全局维护的点集为 $S_u$，同时也是对于任意轻儿子 $v$ 的 $T_v$。

* 依次递归轻子树,其中在递归轻子树前需要将点 $u$ 加入全局维护的点集中。

* 如果点 $u$ 在全局维护的点集中，删除点 $u$。

这样操作的合法性：

在递归长子树时，在长子树内进行的 “删除操作”影响到的 $u$ 的祖先，至多影响到 $u$ 的 $\mathrm{maxdist(u)}-2$ 级祖先，而这些点在处理轻子树之前本来就需要被删除。

而在递归非长子树 $v$ 时，只会至多影响 $u$ 的 $\mathrm{maxdist(v)}-1$ 级祖先，而这些祖先一定都被删光光了，因此在处理轻子树时一定不会影响到集合中 $u$ 的祖先。

这样，一个元素至多贡献儿子个数次总复杂的为 $O(n)$。

---

## 作者：TBSF_0207 (赞：2)

[建议食用：我的博客](https://www.cnblogs.com/TBSF-0207/p/18849103)

看题解没看太懂，遂写一篇细说一下在信息转移中的感悟。

## 一个结论

一个点 $y$ 对于一个点 $x$ 深度唯一，当且仅当点 $y$ 在点 $x$ 为根的树（注意！不是子树）的最长链上。一个点的最长链必然是它与直径两个端点之一的路径。为什么？考虑一条直径 $AB$，一个节点 $u$ 和 $u$ 在直径上距离最小的点 $v$。根据直径的定义，$v\rightarrow A$ 和 $v\rightarrow B$ 中必定是关于 $v$ 的最长链和次长链，否则一定可以找到更优的链作为直径的两半。由此可知命题成立。

## 一个做法

考虑分别以 $A,B$ 进行 dfs，关于所有点的特殊点就只可能在它们到祖先的路径上。考虑动态维护这些点，用一个栈即可，再加上一个统计颜色的桶与一个维护多少个桶有值的变量。每个点 dfs 时维护以它为根的**子树**中的最长链和次长链。这里其实就默认了当前节点到祖先的链是最长链，维护的两个东西只能说是**次长链**（$mxdep_u$，表示绝对深度，下同）和**次次长链**（$cdep_u$，但是这其实是不严谨的，只是一种假想）。然后对于节点 $u$，$dep_u$ 是到根的节点数即绝对距离，显然统计答案的时候需要把祖先中与之相距 $\le mxdep_u-dep_u$ 的删掉。

为什么我们要先遍历长儿子再遍历其他？

![Graph](https://cdn.luogu.com.cn/upload/image_hosting/npwreoz3.png)

（在该图中，我们遍历到节点 $3$，长儿子是 $4$）

考虑到对儿子的影响，我们不能直接删掉所有 $\le mxdep_u-dep_u$ 的节点。如果对于下一个遍历的节点，如果它是长儿子的话，要考虑的就是所有轻链与到祖先路径上深度重合的点。反之，要考虑的就是除去本条的所有轻链加上**重链**中与根节点路径上深度重合的点。总之你要想象把求答案的那个节点 $u$ 提成绝对树根，然后假定祖先路径是绝对最长链。

考虑到这些路径与根节点的深度重合节点其实本质上只需要找出**这些路径**中的最长链，然后对祖先路径进行去重即可。明显我们要除去的 $\le$ 次长链的限制比 $\le$ 最长链的限制一定要小，是一个被包含的关系。所以我们采用这样的计算答案方式，**先遍历长儿子再遍历其他**，这样删的东西就是递进的而不用加东西回来。

这样我们就得到了一个 $O(n)$ 做法。总结起来，先预处理直径的两个端点（代码里用的是两次 dfs），再分别以这两个端点为根进行 dfs，就像其他题解说的一样，每次进行如下操作：

1. 加入父节点。
2. 删掉祖先路径上距离 $\le$ 次长链的节点。
3. 遍历长儿子。
4. 删掉祖先路径上距离 $\le$ 最长链的节点。
5. 统计答案
6. 遍历其他儿子。
7. 删掉父节点。

具体实现如下：


```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int n,m,c[N],ans[N];
vector<int>G[N];
int st,en,dep[N];
int mxdep[N],cdep[N],son[N];
void dfs0(int u,int fa){
	dep[u]=dep[fa]+1;
	if(dep[u]>dep[en])en=u;
	for(int v:G[u]){
		if(v==fa)continue;
		dfs0(v,u);
	}
}
void merge(int x,int y){
	if(mxdep[y]>mxdep[x])cdep[x]=mxdep[x],mxdep[x]=mxdep[y],son[x]=y;
	else if(mxdep[y]>cdep[x])cdep[x]=mxdep[y];
}
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;
	mxdep[u]=cdep[u]=0;
	son[u]=0;
	for(int v:G[u]){
		if(v==fa)continue;
		dfs1(v,u);
		merge(u,v);
	}
	if(!son[u])mxdep[u]=dep[u];
}
int stk[N],tp,buk[N],ext;
void add(int &u){
	buk[c[u]]++;
	if(buk[c[u]]==1)ext++;
}
void del(int &u){
	buk[c[u]]--;
	if(!buk[c[u]])ext--;
}
void dfs3(int u,int fa){
	if(fa)add(stk[++tp]=fa);
	while(tp&&dep[u]-dep[stk[tp]]<=cdep[u]-dep[u])del(stk[tp--]);
	if(son[u])dfs3(son[u],u);
	while(tp&&dep[u]-dep[stk[tp]]<=mxdep[u]-dep[u])del(stk[tp--]);
	ans[u]=max(ans[u],ext);
	for(int v:G[u]){
		if(v==fa||v==son[u])continue;
		dfs3(v,u);
	}
	if(tp&&stk[tp]==fa)del(stk[tp--]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		int u,v;scanf("%d%d",&u,&v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&c[i]);
	st=1,en=0;dfs0(st,0);
	st=en,en=0;dfs0(st,0);
	dfs1(st,0);dfs3(st,0);
	dfs1(en,0);dfs3(en,0);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

## 作者：ran_qwq (赞：2)

中译中一下，独特的意思是深度唯一。

考虑拉出以 $u$ 为根的最长链，那么对 $u$ 来说独特的点一定在最长链上（否则在最长链上能找到对应深度的点，若不能与最长链的定义矛盾）。

设这条最长链的另一端为 $t$。根据直径的结论，$t$ 为直径的一端。

即上文的结论可转化为：对 $u$ 来说独特的点在任一直径的一端到 $u$ 的路径上。我们已经缩小了范围，不用对每个 $u$ 找最长链来算，只需要以直径的两端为根进行 dfs 即可。在此情况下，只有 $u$ 的祖先才能成为独特点。

在 dfs 的过程中，动态维护独特点的集合，同时用桶维护每种颜色出现次数，以及维护颜色种类数。

预处理每个点 $u$ 的最长链 $fi_u$ 和次长链 $se_u$。

考虑从 $fa$ 移动到 $u$，独特点集合的变化。分两种情况：

1. $v$ 是 $u$ 的长儿子（最长链所在儿子）。那么如果集合中一点 $w$，$\operatorname{dist}(u,w)\le se_u$，可以以 $v$ 为根，取次长链，它的长度都比 $\operatorname{dist}(u,w)$ 大，所以 $w$ 以后都不可能成为独特点（$u$ 有两个分叉，一支是 $w$ 另一支是次长链）。那么我们把这些 $w$ 删掉。
2. $v$ 不是 $u$ 的长儿子。那么如果集合中一点 $w$，$\operatorname{dist}(u,w)\le fi_u$，可以以 $v$ 为根，取最长链，它的长度都比 $\operatorname{dist}(u,w)$ 大，所以 $w$ 以后都不可能成为独特点（$u$ 有两个分叉，一支是 $w$ 另一支是最长链）。那么我们把这些 $w$ 删掉。

这里建议画图好好理解一下。

可以先遍历限制不那么紧的长儿子，再遍历其他儿子。

所以，整个过程是这样子的，就是其他题解所述的七步：

1. 加入父节点。
2. 删除长度 $\le$ 次长链长度的 $w$。
3. 遍历长儿子。
4. 删除长度 $\le$ 最长链长度的 $w$。
5. 记录答案（两次 dfs 取 max）。
6. 遍历其他儿子。
7. 删除父节点，回溯。

由于加入都是在最后加入，删除都是删最近加入的后面一段，后进先出，所以维护集合可以用栈。

```cpp
int n,m,id,mx,s,t,cr,tp,a[N],hd[N],d[N],b[N],st[N],as[N]; pii fi[N],se[N];
struct EDGE {int to,ne;} e[N*2];
il void add(int u,int v) {e[++id]={v,hd[u]},hd[u]=id;}
void dfs1(int u,int fa,int ds,int &rt) {
	if(ds>mx) mx=ds,rt=u;
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa) dfs1(v,u,ds+1,rt);
}
void dfs2(int u,int fa) {
	d[u]=d[fa]+1,fi[u]={d[u],u},se[u]={-INF,0};
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa) {
		dfs2(v,u);
		if(fi[v].fir>fi[u].fir) se[u]=fi[u],fi[u]={fi[v].fir,v};
		else if(fi[v].fir>se[u].fir) se[u]={fi[v].fir,v};
	}
}
il void add(int u) {cr+=!b[a[st[++tp]=u]]++;}
il void del() {cr-=!--b[a[st[tp--]]];}
void dfs3(int u,int fa) {
	if(fa) add(fa);
	for(;tp&&d[st[tp]]>=d[u]*2-se[u].fir;) del();
	if(fi[u].sec!=u) dfs3(fi[u].sec,u);
	for(;tp&&d[st[tp]]>=d[u]*2-fi[u].fir;) del();
	cmax(as[u],cr);
	for(int i=hd[u],v;i;i=e[i].ne) if((v=e[i].to)!=fa&&v!=fi[u].sec) dfs3(v,u);
	if(fa&&st[tp]==fa) del();
}
void QwQ() {
	n=rd(),m=rd();
	for(int i=1,u,v;i<n;i++) u=rd(),v=rd(),add(u,v),add(v,u);
	for(int i=1;i<=n;i++) a[i]=rd();
	dfs1(1,0,1,s),mx=0,dfs1(s,0,1,t),dfs2(s,0),dfs3(s,0);
	dfs2(t,0),dfs3(t,0);
	for(int i=1;i<=n;i++) wr(as[i],"\n");
}
```

---

## 作者：ty_mxzhn (赞：1)

## 题意


JOI 国有 $N$ 个城市，城市从 $1$ 到 $N$ 编号。这些城市被 $N-1$ 条双向道路连接，第 $i$ 条路连接两个城市 $A_i$ 和 $B_i$。从任何城市出发，可以到达所有城市。

JOI 国有些特产，每种特产的编号都在 $1$ 到 $M$ 之间（包括 $1$ 和 $M$），但是 $1$ 到 $M$ 的某些整数可能不代表 JOI 国的特产。JOI 国的每个城市都产一种特产。$j$ 城产的特产是 $C_j$。多个城市可能产相同的特产。

我们定义两个城市之间的距离为从一个城市到另一个城市需要经过的最少道路数，对于城市 $x$，我们定义城市 $y$（$y\neq x$）是**独特的城市**当且仅当对于任何一个城市 $z$（$z\neq x,z\neq y$），$x$ 与 $y$ 间的距离不等于 $x$ 与 $z$ 之间的距离。

JOI 国交通部部长 K 先生想知道对于城市 $j$ 的**独特的城市**一共能产多少种特产。

给出 JOI 国的道路信息与每个城市产的特产，写一个程序计算对于每个城市的**独特的城市**，一共能产多少种特产。

## 题解

**关键性质：到一个点最远的点肯定是直径之一。**

观察到：一个城市独特的城市，一定在这个城市的严格最长链上。

每个城市可以先预处理出他最长链的端点是直径的哪一个端点。问题变成确定了直径的一个端点求答案。

对于每一个点，提前维护其向下最长链和次长链，把到该点距离 $\le$ 次长链的点毙掉。这些点可以给长儿子贡献答案，而剩下的儿子都会因为长儿子过长而毙掉到该点 $\le$ 最长链的点。

实现时使用栈和桶精细维护可以做到 $O(n)$。

---

## 作者：masonpop (赞：1)

首先注意到，能对点 $x$ 造成贡献的点一定位于从 $x$ 出发的最长链上。而你取出直径后，最长链的终点一定是直径两端点之一。我们也不用分类，直接对于每个点，从两端点出发各算一遍，取 $\max$ 即可。容易证明，有效的那一边一定会被保留。

然后就变成了这样一个问题。一棵有根树，求每个点 $x$ 到根的路径上的关于 $x$ 的有效节点个数。因为你注意到，知道了具体是哪些点，题目问的那个东西一个桶就解决了。

首先，我们预处理出每个点出发**向子树内**的最长链和**不在同一个儿子的子树内的**次长链。然后放张图。

![](https://cdn.luogu.com.cn/upload/image_hosting/x4soegdd.png?x-oss-process=image/resize,m_lfit,h_1700,w_2250)

对于点 $x$，一个点不合法的原因可能有两个：存在子树外的点，或子树内的点能把它干掉。对于第一种情况，你会发现这样的点在祖先处就会被弹出。

对于第二类点，我们预处理的最长次长链信息就有用了。我们先走最长链，弹出深度不超过次长链的点，再走次长链。（这个过程有点像长链剖分）。这样做，我们就不需要把弹出去的点再放回来了，因为相同深度的点走过了。

回溯很简单，如果一个点的父亲在栈中，就弹出他。

复杂度 $O(n)$。[代码](https://www.luogu.com.cn/paste/u8p989sd)。

---

## 作者：wwwwwza (赞：1)

### 前置知识：
- 对于一棵树的一个节点 $u$，当点 $v$ 到点 $u$ 的距离比点 $u$ 到其他点的距离都要大，那么点 $v$ 是这棵树上的直径中的一段。

### 思路：
1. 能对点 $u$ 产生贡献的点，一定在关于点 $u$ 的最长链上。

2. 对于直径的两端各算一次答案，取其最大值为答案。

3. 在遍历这棵树时，用一个栈来记录所有可能产生贡献的点，用一个桶来记录答案。

4. 处理到一个点时，先遍历重儿子，把栈中和其距离小于等于深度最大的轻儿子弹出栈，即清除不产生贡献的点。

5. 再遍历所有轻儿子，把栈中和其距离小于等于重儿子的点弹出栈。

6. 时间复杂度 $\mathcal O(n)$。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,m,x,y,val[N],rt=1,dep[N],son[N][2],f[N],ans[N];
int t[N],cnt=0,in[N],tot=0;
vector<int>g[N];
void ins(int x){
	cnt+=!t[x]++;
}
void del(int x){
	cnt-=!--t[x];
}
void dfs1(int u,int fa){
	dep[u]=dep[fa]+1;
	if(dep[u]>dep[rt])rt=u;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dfs1(v,u);
	}
}
void dfs2(int u,int fa){
	dep[u]=dep[fa]+1;
	son[u][0]=son[u][1]=0;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa)continue;
		dfs2(v,u);
		if(f[v]>f[son[u][0]]){
			son[u][1]=son[u][0];
			son[u][0]=v;
		}else if(f[v]>f[son[u][1]]){
			son[u][1]=v;
		}
	}
	f[u]=f[son[u][0]]+1;
}
void dfs3(int u,int fa){
	if(fa){
		ins(val[fa]);
		in[++tot]=fa;
	}
	if(son[u][0]){
		while(tot&&dep[in[tot]]>=dep[u]-f[son[u][1]]){
			del(val[in[tot--]]);
		}
		dfs3(son[u][0],u);
	}
	while(tot&&dep[in[tot]]>=dep[u]-f[son[u][0]]){
		del(val[in[tot--]]);
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa||v==son[u][0])continue;
		dfs3(v,u);
	}
	ans[u]=max(ans[u],cnt);
	if(in[tot]==fa)del(val[in[tot--]]);
}
void solve(int u){
	rt=u;
	dfs1(u,0);
	dfs2(rt,0);
	memset(t,0,sizeof(t));
	tot=cnt=0;
	dfs3(rt,0);
}
int main(){
	cin >>n>>m;
	for(int i=1;i<n;i++){
		cin >>x>>y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		cin >>val[i];
	}
	solve(rt);solve(rt);
	for(int i=1;i<=n;i++){
		cout <<ans[i]<<endl;
	}
	return 0;
}

```

---

## 作者：Anonymely (赞：0)

要求的是对于每个点为根时，距离它相同的点数只有 $1$ 的集合并大小。

考虑每个点出发的最长链，能贡献的点一定在最长链上，而每个点出发的最长链至少有一个在树的直径上，故以直径为起始点考虑，最后取 $\max$ 即可。

对于一个点 $u$，需要维护他到根路径上能产生贡献的点，我们 dfs 一遍整棵树，从节点 $u$ 进入节点 $v$ 时，唯一的变化是计算点 $u$ 不在 $v$ 内的最长链 $l$，然后将距离点 $u$ 小于等于 $l$ 的贡献点删掉。

求最长链和次长链可以类似长链剖分，维护时拿一个栈即可。


```cpp
signed main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector < vector <int> > e(n);
	vector <int> c(n);
	for (int i = 1, u, v; i < n; i++) {
		cin >> u >> v, u--, v--;
		e[u].emplace_back(v), e[v].emplace_back(u);
	}
	for (int i = 0; i < n; i++) cin >> c[i], c[i]--;
	int res = 0;
	vector <int> dep(n), son(n), len(n), cnt(m), ans(n);
	stack <int> stk;
	auto push = [&](int u) {
		stk.emplace(u);
		if (!cnt[c[u]]) res++;
		cnt[c[u]]++;
	};
	auto pop = [&]() {
		cnt[c[stk.top()]]--;
		if (cnt[c[stk.top()]] == 0) res--;
		stk.pop();
	};
	auto dfs = [&](auto self, int u, int fa) -> void {
		dep[u] = (fa == -1 ?  0 : dep[fa]) + 1, len[u] = 0, son[u] = -1;
		for (auto v : e[u]) {
			if (v == fa) continue;
			self(self, v, u);
			if (son[u] == -1 || len[v] > len[son[u]]) son[u] = v;
		}
		len[u] = (son[u] == -1 ? 0 : len[son[u]]) + 1;
	};
	auto work = [&](auto self, int u, int fa) -> void {
		if (son[u] == -1) return ckmax(ans[u], res), void();
		int rl = 0;
		for (auto v : e[u]) if (v != fa && v != son[u]) ckmax(rl, len[v]);
		while (!stk.empty() && dep[stk.top()] >= dep[u] - rl) pop();
		push(u);
		self(self, son[u], u);
		for (auto v : e[u]) if (v != fa && v != son[u]) {
			while (!stk.empty() && dep[stk.top()] >= dep[u] - len[son[u]]) pop();
			push(u);
			self(self, v, u);
		}
		while (!stk.empty() && dep[stk.top()] >= dep[u] - len[son[u]]) pop();
		ckmax(ans[u], res);
	};
	int S = 0, T = 0;
	dfs(dfs, 0, -1);
	for (int i = 0; i < n; i++) if (dep[i] > dep[S]) S = i;
	dfs(dfs, S, -1), work(work, S, -1);
	for (int i = 0; i < n; i++) if (dep[i] > dep[T]) T = i;
	dfs(dfs, T, -1), work(work, T, -1);
	for (auto x : ans) cout << x << '\n';
	QwQ01AwA;
}
```

---

## 作者：Felix72 (赞：0)

这是对 RyexAwl 神犇题解的思路概要和代码实现补充。

首先，我们发现每个点的答案只与从这个点出发最长的路径有关，那么先求直径，再对每个端点分别求一次，取最大值。

求解的过程可以分两步。先对树进行长链剖分，再遍历一遍。遍历时，用一个全局数据结构维护合法的点集。具体的，进入一个子节点前我们先用其父亲的最长链或者次长链删掉不合法节点，进入后，删去自己字树内最长链所对应的不合法节点。此时统计答案。因为可以先遍历最长链，所以每个点进出次数有保证，故复杂度正确。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
typedef pair < int, int > PII;
int n, m, h[N], cnt, a[N];
struct edge {int to, next;} e[N * 2];
inline void add(int x, int y)
{e[++cnt].to = y, e[cnt].next = h[x], h[x] = cnt;}
int p1, p2, bj;
inline void dfs(int now, int prt, int dist, int &cur)
{
	if(dist > bj) bj = dist, cur = now;
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == prt) continue;
		dfs(to, now, dist + 1, cur);
	}
}
priority_queue < PII > q;
int len[N], son[N], sec[N], ans[N], tong[N], num, dep[N];
inline void dfs1(int now, int prt)
{
	dep[now] = dep[prt] + 1;
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == prt) continue;
		dfs1(to, now);
		if(len[to] + 1 >= len[now])
		{
			sec[now] = len[now];
			len[now] = len[to] + 1;
			son[now] = to;
		}
		else if(len[to] + 1 >= sec[now])
			sec[now] = len[to] + 1;
	}
}
inline void refresh(int now, int opt)
{
	tong[a[now]] += opt;
	if(tong[a[now]] == 1 && opt == 1) ++num;
	if(tong[a[now]] == 0 && opt == -1) --num;
}
inline void dfs2(int now, int prt)
{
	while(!q.empty() && q.top().first >= dep[now] - sec[now]) refresh(q.top().second, -1), q.pop();
	q.push({dep[now], now});
	refresh(now, 1);
	if(son[now])
	{
		dfs2(son[now], now);
	}
	while(!q.empty() && q.top().first >= dep[now] - len[now]) refresh(q.top().second, -1), q.pop();
	ans[now] = max(ans[now], num);
	for(int i = h[now]; i; i = e[i].next)
	{
		int to = e[i].to;
		if(to == prt || to == son[now]) continue;
		if(q.empty() || q.top().second != now)
		{
			q.push({dep[now], now});
			refresh(now, 1);
		}
		dfs2(to, now);
	}
	if(q.size() && q.top().second == now) q.pop(), refresh(now, -1);
}
inline void solve(int rt)
{
	while(q.size()) q.pop();
	memset(tong, 0, sizeof(tong)); num = 0;
	memset(len, 0, sizeof(len));
	memset(son, 0, sizeof(son));
	memset(sec, 0, sizeof(sec));
	memset(dep, 0, sizeof(dep));
	dfs1(rt, 0);
	dfs2(rt, 0);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i < n; ++i)
	{
		int x, y; cin >> x >> y;
		add(x, y), add(y, x); 
	}
	for(int i = 1; i <= n; ++i) cin >> a[i];
	dfs(1, 0, 0, p1), bj = 0, dfs(p1, 0, 0, p2);
	solve(p1), solve(p2);
	for(int i = 1; i <= n; ++i) cout << ans[i] << '\n';
	return 0;
}
```

---

## 作者：Feyn (赞：0)

脑子没转过来弯怎么办，启发如果对每个点计算和定点的贡献并且不好计算的话,计算定点对每个点的贡献可能是个好方法。

对于一个点而言，只有它到最远点的链上的节点可能产生贡献。而一个点的最远点是直径的两个端点中的一个，所以以这两个端点为基准分别计算每个点的答案取 $\max$ 就可以了。

转化后的问题变成了每个点到根都有一些点，希望找到该点的距离独特的那些点。一个点不合法意味着其距离不独特，考虑造成其不合法，也就是距离和它相同的点的位置。这个点只可能在当前点的子树内或者子树外。如果这个点在子树外的话，一定会导致在某个祖先处造成损失，所以只需要考虑第一种情况。

考虑维护一个集合 $s$ 表示在祖先处未被淘汰的点集，考虑如何向下转移。对于长儿子，把集合中不大于次长链的元素剔除就可以了；对于短孩子，把集合中不大于长儿子的元素剔除即可，此时还可以统计该点的答案。

需要注意的是完成一个点的遍历之后不需要把剔除的元素再 push，否则复杂度是错误的。正确性考虑不 push 回去只可能在某个祖先的短儿子处造成问题，而如果存在一种方案使得长儿子中不合法，短儿子中也一定可以找到一种方案使之不合法，因为在短儿子处一定可以搓出来一个和长儿子一样的方案使得这个点不合法。

颜色数量简单维护即可。

```cpp
#include<bits/stdc++.h>
// #define feyn
using namespace std;
const int N=200010;
inline void read(int &wh){
    wh=0;int f=1;char w=getchar();
    while(w<'0'||w>'9'){if(w=='-')f=-1;w=getchar();}
    while(w<='9'&&w>='0'){wh=wh*10+w-'0';w=getchar();}
    wh*=f;return;
}

struct edge{
    int t,nxt;
}e[N<<1];
int head[N],esum;
inline void add(int fr,int to){
    e[++esum]=(edge){to,head[fr]};
    head[fr]=esum;
}

int anPl,anData;
void findLen(int wh,int fa,int nowData){
    if(nowData>anData)anData=nowData,anPl=wh;
    for(int i=head[wh],th;i;i=e[i].nxt){
        if((th=e[i].t)==fa)continue;
        findLen(th,wh,nowData+1);
    }
}

int m,n,co[N],an[N];

int coNum[N],coAns;
inline void ch(int wh,int val){
    wh=co[wh];
    if(coNum[wh])coAns--;
    coNum[wh]+=val;
    if(coNum[wh])coAns++;
}

int son[N],dep[N],mxDep[N],cDep[N];
void dfs(int wh,int fa){
    dep[wh]=mxDep[wh]=dep[fa]+1;
    for(int i=head[wh],th;i;i=e[i].nxt){
        if((th=e[i].t)==fa)continue;
        dfs(th,wh);
        if(mxDep[th]>mxDep[son[wh]]){
            son[wh]=th;
            cDep[wh]=mxDep[wh];
            mxDep[wh]=mxDep[th];
        }
        else cDep[wh]=max(cDep[wh],mxDep[th]);
    }
}

int tim=0;

stack<int>sta;
void hanghang(int wh,int fa){
    if(fa){
        sta.push(fa);
        ch(fa,1);
    }
    vector<int>rec;
    if(son[wh]){
        while(!sta.empty()){
            ++tim;
            int now=sta.top();
            if(dep[now]+cDep[wh]>=dep[wh]*2){
                rec.push_back(now);
                sta.pop();ch(now,-1);
            }
            else break;
        }
        hanghang(son[wh],wh);
    }
    while(!sta.empty()){
        ++tim;
        int now=sta.top();
        if(dep[now]+mxDep[wh]>=dep[wh]*2){
            rec.push_back(now);
            sta.pop();ch(now,-1);
        }
        else break;
    }
    an[wh]=max(an[wh],coAns);
    for(int i=head[wh],th;i;i=e[i].nxt){
        if((th=e[i].t)==fa||(th=e[i].t)==son[wh])continue;
        hanghang(th,wh);
    }
    if(sta.empty()==false&&sta.top()==fa){
        sta.pop();ch(fa,-1);
    }
}

void solve(int rt){
    memset(son,0,sizeof(son));
    memset(dep,0,sizeof(dep));
    memset(cDep,0,sizeof(cDep));
    memset(mxDep,0,sizeof(mxDep));
    dfs(rt,0);
    hanghang(rt,0);
}

signed main(){
	
    #ifdef feyn
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif

    read(m);read(n);
    for(int i=1;i<m;i++){
        int s1,s2;read(s1);read(s2);
        add(s1,s2);add(s2,s1);
    }
    for(int i=1;i<=m;i++)read(co[i]);
    anData=0;findLen(1,0,1);
    int ss=anPl;anData=0;
    findLen(ss,0,1);int tt=anPl;

    solve(ss);
    solve(tt);
    for(int i=1;i<=m;i++)printf("%d\n",an[i]);

    return 0;
}
```

---

