# [USACO19DEC] Bessie's Snow Cow P

## 题目背景

Snow has arrived on the farm, and as she does at the beginning of every winter,
Bessie is building a snow-cow! Most of the time, Bessie strives to make her
sculpture look as much like a real cow as possible.  However, feeling
artistically inspired, this year she decides to pursue a more abstract route and
build a sculpture in the shape of a tree, consisting of $N$ snowballs
$(1\le N\le 10^5)$ connected by  $N-1$ branches, each connecting a pair of
snowballs such that there is a  unique path between every pair of snowballs. 

Bessie has added a nose to one of the snowballs, so it represents the head of
the abstract snow cow.  She designates it as snowball number 1.  To add more
visual interest, she plans to dye some of the snowballs different colors in an
artistic fashion by filling old milk pails with colored dye and splashing them
onto the sculpture.  Colors are identified by integers in the range
$1 \ldots 10^5$, and  Bessie has an unlimited supply of buckets filled with dyes
of every possible color.

When Bessie splashes a snowball with a bucket of dye, all the snowballs in its 
subtree are also splashed with the same dye (snowball $y$ is in the subtree of
snowball $x$ if $x$ lies on the path from $y$ to the head snowball). By
splashing each color with great care, Bessie makes sure that all colors a 
snowball has been splashed with will remain visible. For example, if a snowball
had colors $[1,2,3]$ and Bessie splashes it with color $4$, the snowball will
then have colors $[1,2,3,4]$. 

After splashing the snowballs some number of times, Bessie may also want to know
how colorful a part of her snow-cow is.  The "colorfulness" of a snowball $x$ is
equal to the number of distinct colors $c$ such that snowball $x$ is colored
$c$. If Bessie asks you about snowball $x$, you should reply with the sum of the
colorfulness values of all snowballs in the subtree of $x.$

Please help Bessie find the colorfulness of her snow-cow at certain points in
time.

## 题目描述

农场下雪啦！Bessie 和往年开冬一样在堆雪牛。她之前是个写实派，总是想把她的雪牛堆得和个真牛一样。但今年不一样，受到来自东方的神秘力量的影响，她想来点抽象艺术，因此她想堆成一棵树的样子。这棵树由 $N$ 个雪球，$N-1$ 根树枝构成，每根树枝连接两个雪球，并且每两个雪球之间路径唯一。

Bessie 要给她的雪牛来点细节。因此她给其中一个雪球加了个鼻子，来表示这是他那抽象的牛的头，并且把它称作雪球 $1$。为了让雪牛更好看，她还要给某些雪球来点不同的颜色。于是，她用旧牛奶桶装满了颜料泼到雪牛上。这些颜料分别被编号为 $1,2,\dots 10^5$，且每种颜色都无限量供应。

当 Bessie 把一桶颜料泼到一个雪球上时，这个雪球子树上的所有雪球也会被染色（我们称雪球 $y$ 在雪球 $x$ 的子树里当且仅当雪球 $x$ 处在雪球 $y$ 到雪球 $1$ 的路径上）。Bessie 有着精确的泼颜料技术，因此在泼完一种颜料后，一个雪球上之前被染过的所有颜色依然清晰可见。例如，一个雪球之前显现出来颜色 $\left[ 1,2,3 \right]$，然后 Bessie 把装有 $4$ 号颜色的牛奶桶泼上去，那么这个雪球将显现出来颜色 $\left[ 1,2,3,4 \right]$。 在泼了几桶颜料以后，Bessie 可能想要了解她的雪牛有多五彩斑斓。令雪球 $x$ 的『颜色丰富度』为这个雪球被染上的不同颜色总数 ，当 Bessie 想了解雪球 $x$ 的相关信息时，你应该回答她雪球 $x$ 的子树中所有的雪球的颜色丰富度之和。

救救孩子吧！

## 说明/提示

#### 样例解释
执行完第一个修改后雪球 $4$ 被染上了颜色 $1$。

执行完第二个修改后雪球 $4$ 和雪球 $5$ 被染上了颜色 $2$。

执行完第三个修改后所有雪球都被染上了颜色 $1$。
#### 数据范围
对于测试点 $2,3$，$1\le N\le 10^2,1\le Q\le 2\times 10^2$；

对于测试点 $4-6$，$1\le N\le 10^3,1\le Q\le 2\times 10^3$；

对于 $100\%$ 的数据，$1\le N,\ Q,\ c \le 10^5, 1\le a,\ b,\ x \le N$。

USACO 2019 December 铂金组T2

## 样例 #1

### 输入

```
5 18
1 2
1 3
3 4
3 5
1 4 1
2 1
2 2
2 3
2 4
2 5
1 5 1
2 1
2 2
2 3
2 4
2 5
1 1 1
2 1
2 2
2 3
2 4
2 5
```

### 输出

```
1
0
1
1
0
2
0
2
1
1
5
1
3
1
1
```

# 题解

## 作者：KaisuoShutong (赞：27)

# P5852 [USACO19DEC]Bessie's Snow Cow P

> 给定一棵树，定义一个节点的权值为它染的不同颜色个数（因此一个节点可能有多个颜色）。
>
> 维护两个操作：
> 1.x的子树全染上某种颜色；
> 2.查询想的子树权值之和；

首先对于每个颜色开一个set，维护子树全部都染上同种颜色的点，且保证不会在同一set中有两个点的子树包含同一点。

通俗解释就是不让一个点被同一颜色染两次。
体现在操作中的实际效应就是加入一个染色时要删掉它子树的所有同色染色信息。

此时需要做的就是在修改的时候同步更新答案。

发现答案分为两部分：  
1.祖先的子树染上同种颜色时，附带着我染上了；此时整个子树必定也染上了。  
2.我的某个儿子染了，它带动我的一部分子树染了；此时整个子树不一定染上。

于是想到开两颗树状数组：  
1.区改单查，维护第一种情况：每次给子树加贡献，每次查单个点的情况。这个情况x与它子树中每个点加的都是一样的，所以可以直接查x的，然后乘子树大小。  
2.单改区查，维护第二种情况：每次给单个点加贡献，每次查区间的情况。加的时候我们可以直接把y子树的加的全部加给x那一个点，这样只要查到y那个点就加入了y整个子树的贡献。

这一段的代码如下：

```cpp
void upd(int x,int d)//修改
{
	A.ins(dfn[x],d);
	A.ins(low[x]+1,-d);//第一种情况：祖先来的贡献
	B.ins(dfn[x],(low[x]-dfn[x]+1)*d);//第二种情况：子树的贡献（注意：因为直接把x子树的贡献加给x了，所以要乘子树大小）
}
int que(int x) {return (low[x]-dfn[x]+1)*A.ask(dfn[x])+B.ask(low[x])-B.ask(dfn[x]);}
```

整体代码如下：

```cpp
struct Edge{int to,next;
}a[maxn<<1];
int n,q,dfn[maxn],low[maxn],bc[maxn],h[maxn],dfx,cnt;
void add(int x,int y) {a[++cnt]=(Edge){y,h[x]},h[x]=cnt,a[++cnt]=(Edge){x,h[y]},h[y]=cnt;}
void Dfs(int x)
{
	bc[dfn[x]=++dfx]=x;
	for(int i=h[x];i;i=a[i].next)
		if(!dfn[a[i].to]) Dfs(a[i].to);
	low[x]=dfx;
}
struct Array_Tree{
	int c[maxn];
	void ins(int x,int d) {for(;x<=n;x+=x&-x) c[x]+=d;}
	int ask(int x) {int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
}A,B;
std::set<int> st[maxn];
void upd(int x,int d) {A.ins(dfn[x],d),A.ins(low[x]+1,-d),B.ins(dfn[x],(low[x]-dfn[x]+1)*d);}
signed main()
{
	int x,y;
	n=read(),q=read();
	for(int i=1;i<n;i++) add(read(),read());
	Dfs(1);
	while(q--)
		if(read()==1)
		{
			x=read(),y=read();
			auto it=st[y].upper_bound(dfn[x]);
			if(it!=st[y].begin()&&low[bc[*prev(it)]]>=low[x]) continue;//ancestors
			while(it!=st[y].end()&&(*it)<=low[x]) upd(bc[*it],-1),st[y].erase(it++);
			st[y].insert(dfn[x]),upd(x,1);
		}
		else x=read(),printf("%d\n",(low[x]-dfn[x]+1)*A.ask(dfn[x])+B.ask(low[x])-B.ask(dfn[x]));
	return 0;
}
```

说了这么多，点个赞再走吧。

---

## 作者：DrBit (赞：20)

[题目链接](https://www.luogu.com.cn/problem/P5852)

来一发~~自认为很简单的~~线段树做法。

首先我们还是对树求出 dfs 序，接着我们用线段树维护每个 dfs 序列中每个节点的丰富度（以下统称为“权值”）。

难点在于怎么处理同种颜色的覆盖关系。

我们对于每个颜色建立一个 set，保存被染上这种颜色的节点 dfs 序位置。

假设现在正在进行一个修改操作，将 x 染成 col 色：

1. 找到 set 中 x 的前一个点，判断其是否是 x 的祖先，如果是的话直接 continue 跳过本次操作。

1. 通过 set 找到 x 子树中已经被染上 col 色的节点。

1. 将这些节点的子树权值总体减 1，同时把这些节点移出 set。

1. 将 x 放入对应的 set，同时将 x 子树中的节点权值总体加 1。

解释一下第一步：

第一步在判断 x 的子树是否已经被整体染上了 col 色。如果 x 的祖先节点已经被事先染上了 col 色，那么在 set 中它与 x 之间不应该再有其他节点（中间的点都在修改祖先节点时的 2、3 步被删掉了）。

至于查询就很简单了，直接找线段树中 x 的子树部分的权值区间和就好。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<set>
#define it set<int>::iterator
#define ls (x << 1)
#define rs (x << 1) | 1
#define int long long
using namespace std;
const int MAXN = 2e5 + 50;
set<int> pos[MAXN];
int dfn[MAXN], siz[MAXN], inv[MAXN];
struct edge
{
    int nxt, to, val;
} e[MAXN * 2];
int head[MAXN], edgetot;
struct SegT
{
    int val[MAXN * 4], tag[MAXN * 4];
    void pushdown(int x, int l, int r)
    {
        if (tag[x])
        {
            tag[ls] += tag[x];
            tag[rs] += tag[x];
            int mid = (l + r) >> 1;
            val[ls] += tag[x] * (mid - l + 1);
            val[rs] += tag[x] * (r - mid);
            tag[x] = 0;
        }
    }
    void modify(int x, int l, int r, int tl, int tr, int v)
    {
        if (tl > r || tr < l)
            return;
        if (tl <= l && tr >= r)
        {
            tag[x] += v;
            val[x] += (r - l + 1) * v;
            return;
        }
        pushdown(x, l, r);
        int mid = (l + r) >> 1;
        modify(ls, l, mid, tl, tr, v);
        modify(rs, mid + 1, r, tl, tr, v);
        val[x] = val[ls] + val[rs];
    }
    int query(int x, int l, int r, int tl, int tr)
    {
        if (tl > r || tr < l)
            return 0;
        if (tl <= l && tr >= r)
            return val[x];
        int mid = (l + r) >> 1;
        pushdown(x, l, r);
        return query(ls, l, mid, tl, tr) + query(rs, mid + 1, r, tl, tr);
    }
} T;
int N, timtot, Q;
void add(int x, int y)
{
    e[++edgetot].to = y;
    e[edgetot].nxt = head[x];
    head[x] = edgetot;
}
void dfs(int x, int fa)
{
    dfn[x] = ++timtot;
    inv[timtot] = x;
    siz[x] = 1;
    for (int i = head[x]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        dfs(v, x);
        siz[x] += siz[v];
    }
}
signed main()
{
    scanf("%lld%lld", &N, &Q);
    for (int i = 1; i <= N - 1; ++i)
    {
        int u, v;
        scanf("%lld%lld", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    int cmd = 0;
    int x, col;
    while (Q--)
    {
        scanf("%lld", &cmd);
        if (cmd == 1)
        {
            scanf("%lld%lld", &x, &col);
            int l = dfn[x];
            int r = dfn[x] + siz[x] - 1;
            it t2 = pos[col].upper_bound(dfn[x]);
            if (t2 != pos[col].begin())
            {
                t2--;
                if (dfn[x] >= *t2 && dfn[x] <= *t2 + siz[inv[*t2]] - 1)
                    continue;
            }
            it t1 = pos[col].lower_bound(dfn[x]);
            while (t1 != pos[col].end() && *t1 <= r)
            {
                int now = *t1;
                // cout << "*" << now << endl;
                T.modify(1, 1, N, now, now + siz[inv[now]] - 1, -1);
                pos[col].erase(t1);
                t1 = pos[col].lower_bound(dfn[x]);
            }
            T.modify(1, 1, N, l, r, 1);
            pos[col].insert(dfn[x]);
        }
        else
        {
            scanf("%lld", &x);
            printf("%lld\n", T.query(1, 1, N, dfn[x], dfn[x] + siz[x] - 1));
        }
    }
    return 0;
}
```


---

## 作者：Drifty (赞：8)

### Preface

感觉之前的题解写的都有一些乱，这里从头开始细讲一下这题的做法。

### Solution

一开始拿到这类动态修改以及维护的树上问题，第一个就要考虑转化成序列问题来做。这题正是如此。

我们注意到在学习[树链剖分](https://oi-wiki.org//graph/hld/)的时候，提到了一个所谓的时间戳，就是对于所有的节点 $u$，我们在深度优先遍历它的时候，我们令第 $u$ 个节点被遍历到的顺序为 $\mathrm{dfn}_u$ 这就是时间戳。

然后这个 $\mathrm{dfn}$ 具有一个性质，就是对于一棵以 $x$ 为根的子树 $E_x$，我们记它的大小为 $\mathrm{siz}_x$，那么对于任意的 $u,v\in E$，若 $u\neq v$ 那么 $\mathrm{dfn}_u \neq \mathrm{dfn}_v$ 且 $\mathrm{dfn}_x\le \mathrm{dfn}_u, \mathrm{dfn}_v \le \mathrm{dfn}_x + \mathrm{siz}_x - 1$。这样每一个子树中的节点在 $\mathrm{dfn}$ 上是连续的，那么我们就可以把它拍扁成为一个序列。

那么接下来怎么做？

注意到 $1\le c\le 10^5$，很小，那么我们考虑对于颜色开一个 `set` 来维护。

具体地，对每一种颜色 $c$，我们都开一个 `set`，我们记为 $S_c$，其中 $S_c$ 的元素即为染上 $c$ 颜色的节点的 $\mathrm{dfn}$。

但直接朴素地把每一个询问都加入到 $S$ 中，空间时间都会爆炸，考虑优化。

每一次修改，对于一个以 $x$ 为根的子树 $E_x$，如果 $E_x$ 中的子节点在 $S_c$ 中出现过，我们就把它从 $S_c$ 中删掉，并且抹除该子节点为根的子树对颜色产生的所有贡献，最后再把 $\mathrm{dfn}_x$ 加入 $S_c$，并且在你维护的区间加区间修改的数据结构中把 $E_x$ 在 $\mathrm{dfn}$ 中连续的区间加 $1$ 也就维护了颜色的贡献。注意到每个点最多被删一次，一共只会删 $O(n)$ 次，加上 `set` 自带的 $O(
\log n)$，复杂度 $O(n\log n)$ 可以接受。

区间加的实现用两个树状数组或线段树都可以，本篇给出了两份代码，供参考。

### Code

如果用的 `DevCpp5`，编译参数记得加上 `-std=c++14`。存图用的 `vector` 常数大但好用。

#### Code1

线段树的实现，长度：2,561 byte。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 1e5 + 3;
int n, q, dfn[N], cnt, p[N], siz[N];
vector <int> e[N];
set <int> S[N];
namespace SegmentTree {
    i64 tr[N << 3], tag[N << 3];
    auto ls = [](int x) {return x << 1;};
    auto rs = [](int x) {return x << 1|1;};
    void push_up(int p) {tr[p] = tr[ls(p)] + tr[rs(p)];}
    void addtag (int p, int pl, int pr, i64 d) {
        tag[p] = tag[p] + d;
        tr[p] = (pr - pl + 1) * d + tr[p]; 
    }
    void push_down(int p, int pl, int pr) {
        if (tag[p]) {
            int mid = (pl + pr) >> 1;
            addtag(ls(p), pl, mid, tag[p]);
            addtag(rs(p), mid + 1, pr, tag[p]);
            tag[p] = 0;
        }
    }
    void update(int l, int r, i64 d, int p, int pl, int pr) {
        if (l <= pl && pr <= r) {addtag (p, pl, pr, d); return;}
        push_down(p, pl, pr);
        int mid = (pl + pr) >> 1;
        if (l <= mid) update(l, r, d, ls(p), pl, mid);
        if (r > mid)  update(l, r, d, rs(p), mid + 1, pr);
        push_up(p);
    }
    i64 query(int l, int r, int p, int pl, int pr) {
        push_down(p, pl, pr);
        if (l <= pl && pr <= r) {return tr[p];}
        int mid = (pl + pr) >> 1;
        long long res = 0;
        if (l <= mid) res += query(l, r, ls(p), pl, mid);
        if (r > mid)  res += query(l, r, rs(p), mid + 1, pr);
        return res;
    }
}
void dfs (int u, int fa) {
    dfn[u] = ++ cnt;
    p[dfn[u]] = u;
    siz[u] = 1;
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs (v, u); siz[u] += siz[v];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i < n; i ++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    dfs (1, 0);
    auto calEnd = [&](int u) {return dfn[u] + siz[u] - 1;};
    using namespace SegmentTree;
    for (int op, x, c; q --; ) {
        cin >> op >> x;
        if (op == 1) {
            cin >> c;
            auto it = S[c].upper_bound(dfn[x]);
            if (it != S[c].begin()) 
                if (calEnd(p[*prev(it)]) >= calEnd(x)) continue;
            while (it != S[c].end() && *it <= calEnd(x)) 
                update(*it, calEnd(p[*it]), -1, 1, 1, n), S[c].erase(it ++);
            S[c].insert(dfn[x]);
            update(dfn[x], calEnd(x), 1, 1, 1, n);
        }
        else cout << query(dfn[x], calEnd(x), 1, 1, n) << '\n';
    }
    return 0;
}
```

#### Code2

树状数组的实现，长度：1,844 byte。

```cpp
#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int N = 1e5 + 3;
int n, q, dfn[N], cnt, p[N], siz[N];
vector <int> e[N];
set <int> S[N];
template <size_t Siz>
class Fenwick_Tree {
private :
    i64 c[Siz]; int LowBit (int x) {return x & -x;}
public :
    void update (int x, i64 d) {
        for (; x <= n; x += LowBit(x)) c[x] += d;
    }
    i64 query (int x) {
        i64 res = 0;
        for (; x; x -= LowBit(x)) res += c[x];
        return res;
    }
};
Fenwick_Tree <N> Tr1, Tr2;
void dfs (int u, int fa) {
    dfn[u] = ++ cnt;
    p[dfn[u]] = u;
    siz[u] = 1;
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs (v, u); siz[u] += siz[v];
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> q;
    for (int i = 1; i < n; i ++) {
        int u, v; cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    dfs (1, 0);
    auto calEnd = [&](int u) {return dfn[u] + siz[u] - 1;};
    auto getAns = [&](int u) {
        return siz[u] * Tr1.query(dfn[u]) + 
               Tr2.query(calEnd(u)) - Tr2.query(dfn[u]);
    };
    auto change = [&](int u, i64 d) {
        Tr1.update(dfn[u], d);
        Tr1.update(calEnd(u) + 1, - d);
        Tr2.update(dfn[u], siz[u] * d);
    };
    for (int op, x, c; q --; ) {
        cin >> op >> x;
        if (op == 1) {
            cin >> c;
            auto it = S[c].upper_bound(dfn[x]);
            if (it != S[c].begin()) 
                if (calEnd(p[*prev(it)]) >= calEnd(x)) continue;
            while (it != S[c].end() && *it <= calEnd(x)) 
                change(p[*it], -1), S[c].erase(it ++);
            S[c].insert(dfn[x]), change(x, 1);
        }
        else cout << getAns(x) << '\n';
    }
    return 0;
}
```

---

## 作者：Purple_wzy (赞：8)

#### B Bessie's Snow Cow

题目：http://www.usaco.org/index.php?page=viewproblem2&cpid=973

题目大意：给你一棵树，要求支持两种操作：

1.给定x,c,给x的子树染上颜色c（一个节点可以有多个颜色）

2.给定x,求x的子树的所有节点的所有颜色个数和（每个节点单独算）

题解：

这个题有两个难点：

1.修改时，如何更新其对子树内节点的贡献，以及如何上传对祖先的影响；

2.查询时，如何一次性统计子树内所有节点的贡献

我们发现，如果将一个操作的复杂度变为O(logn)甚至O(1),另一个操作的
复杂度将不可避免地到达O(n)。

考虑统计答案。答案可以分为两个部分：一是x或x的祖先已经染过的颜色，
这些的贡献可以一并计算;二是子树内染色的情况。

对于第一个，我们在每次修改时区间加就行了，当然还要撤销之前子树内
的一些修改操作的贡献。

我们以这棵树的dfs序为下标开一个树状数组，用差分维护每个节点已经染
上的颜色个数，再开1e5个set记录下每个颜色的染色情况，避免重复染色。

每次修改操作步骤如下：

1.判断x的祖先是否已经被染上c色。若已经染色，直接退出；

2.查询x子树内是否有节点染上c色。若已经染色，撤销其影响并在set中
删除此节点；

3.将此次修改加入set,进行区间修改。

那对于第二个，又该怎么求呢？

因为这些贡献是一段dfs序连续区间的单点贡献，我们可以另开一个树状数组

记录这个贡献。每次修改只需要单点+siz[x]即可。

修改操作的步骤同上。每次只需要查询[id[x]+1,id[x]+siz[x]-1]这段区间的

贡献即可（也就是x子树除去x节点的贡献）

设两个查询得到的值是ans1和ans2,那么答案即为：siz[x]*ans1+ans2

复杂度：因为每次修改只会被加入和撤销一次，每次都是O(logn),

查询也是O(logn)的，所以总复杂度即为O(nlogn)。

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register ll
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
typedef long long ll;
#define I inline void
#define IN inline ll
template<class D>I read(D &res){
	res=0;register D g=1;register char ch=getchar();
	while(!isdigit(ch)){
		if(ch=='-')g=-1;
		ch=getchar();
	}
	while(isdigit(ch)){
		res=(res<<3)+(res<<1)+(ch^48);
		ch=getchar();
	}
	res*=g;
}
const ll INF=1e9+7;
struct E{
	ll to,nt;
}e[202000];
#define T e[k].to
ll n,m,tot,sit,X,Y,head[101000],siz[101000],id[101000],p[101000],out[101000];
struct BIT{
	ll tr[101000],res;
	IN lbt(ll x){
		return x&(-x);
	}
	I modi(ll x,ll w){while(x<=n){tr[x]+=w,x+=lbt(x);}}
	IN ques(ll x){res=0;while(x){res+=tr[x],x-=lbt(x);}return res;}
}A,B;
set<ll>s[101000];
I modify(ll x,ll sn){
	A.modi(id[x],sn);
	A.modi(out[x]+1,-1*sn);
	B.modi(id[x],sn*siz[x]);
	//cout<<id[x]<<" "<<out[x]<<" "<<sn<<endl;
}
I D_1(ll x,ll fa){
	id[x]=++tot;siz[x]=1;p[tot]=x;
	for(re k=head[x];k!=-1;k=e[k].nt){
		if(T==fa)continue;
		D_1(T,x);siz[x]+=siz[T];
	}
	out[x]=tot;
}
int main(){
	freopen("snowcow.in","r",stdin);
	freopen("snowcow.out","w",stdout);
	read(n);read(m);
	memset(head,-1,sizeof(head));
	tot=-1;
	F(i,1,n-1){
		read(X);read(Y);
		e[++tot].to=Y;
		e[tot].nt=head[X];
		head[X]=tot;
		e[++tot].to=X;
		e[tot].nt=head[Y];
		head[Y]=tot;
	}
	F(i,0,100000)s[i].insert(INF);
	tot=0;
	D_1(1,0);
	//F(i,1,n)cout<<id[i]<<" "<<siz[i]<<" "<<out[i]<<endl;
	while(m--){
		read(sit);read(X);
		if(sit==1){
			read(Y);
			auto P=s[Y].upper_bound(id[X]);
			if(P!=s[Y].begin()&&out[p[*prev(P)]]>=out[X])continue;
			while(1){
				P=s[Y].upper_bound(id[X]);
				if(*P>out[X])break;
				modify(p[*P],-1);
				s[Y].erase(P);
			}
			s[Y].insert(id[X]);
			modify(X,1);
		}
		else printf("%lld\n",siz[X]*A.ques(id[X])+B.ques(out[X])-B.ques(id[X]));//printf("%d %d %d %d %d %lld\n",id[X],out[X],A.ques(id[X]),B.ques(out[X]),B.ques(id[X]),(ll)siz[X]*A.ques(id[X])+(ll)B.ques(out[X])-(ll)B.ques(id[X]));
	}
	return 0;
}
```
推荐一下我的博客，https://www.cnblogs.com/Purple-wzy/

这里有USACO12月月赛的全部12篇题解~

---

## 作者：activeO (赞：7)

## 题目大意

1 操作：把 x 的子树都染上颜色 c。

2 操作：求 x 子树中每个点的颜色种数和

## 思路

~~首先这题可以写树剖，但是本人太差没写~~

那我们就可以利用时间戳的性质：同个子树内节点编号是连起来的写线段树。
就是要求出 size,查询的就是 $ [dfn_x,dfn_x+sz_x-1] $。

然后维护一个 set，存储每种颜色哪些点染上了。但是点太多了，直接存储肯定是不行的，然后就可以发现：

如果一个点 x 染上 c，那么他的在 set 中的子孙就可以删除了，只用加入祖先就行了。这里只需要暴力删除子孙就可以了，因为每个点最多只会删一次，所以实际上这个复杂度是 $ O(n) $ 的，可以接受。

然后如果点 x 要染上 c，且发现他的祖先已经在 set 中，就是染过了，那么这次修改就可以忽略了。

这里还没完，如果直接这样大概率会 WA 的（亲身经验）。一个巨坑：题目中说的是链，就是说可能会出现 $ r>l $ 的情况，需要特判。

## 代码

```cpp
#include <bits/stdc++.h>//祝大家学习愉快！

#define int long long

#define iterator set<int>::iterator

using namespace std;

const int maxn=1e5+5;
struct edge{
	int to,nxt;
}e[maxn<<1];
int head[maxn],len,tim;
int sz[maxn],dfn[maxn],dfx[maxn];
int sum[maxn<<2],lz[maxn<<2];
set<int> st[maxn];

inline void init(){
	memset(head,-1,sizeof(head));
	tim=len=0;
}
void add(int u,int v){
	e[++len].to=v;
	e[len].nxt=head[u];
	head[u]=len;
}

void pushup(int now){//线段树板子
	sum[now]=sum[now<<1]+sum[now<<1|1];
}
void pushdown(int now,int l,int r){
	if(lz[now]){
		int mid=(l+r)>>1;
		sum[now<<1]+=(mid-l+1)*lz[now];
		lz[now<<1]+=lz[now];
		sum[now<<1|1]+=(r-mid)*lz[now];
		lz[now<<1|1]+=lz[now];
		lz[now]=0;
	}
}
void build(int now,int l,int r){
	sum[now]=lz[now]=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	pushup(now);
}
void update(int now,int l,int r,int ql,int qr,int x){
	if(l>qr||r<ql) return;
	if(ql<=l&&qr>=r){
		sum[now]+=(r-l+1)*x;
		lz[now]+=x;
		return;
	}
	pushdown(now,l,r);
	int mid=(l+r)>>1;
	if(ql<=mid) update(now<<1,l,mid,ql,qr,x);
	if(qr>mid) update(now<<1|1,mid+1,r,ql,qr,x);
	pushup(now);
}
int query(int now,int l,int r,int ql,int qr){
	if(l>qr||r<ql) return 0;
	if(ql<=l&&qr>=r) return sum[now];
	pushdown(now,l,r);
	int mid=(l+r)>>1,res=0;
	if(ql<=mid) res+=query(now<<1,l,mid,ql,qr);
	if(qr>mid) res+=query(now<<1|1,mid+1,r,ql,qr);
	return res;
}

void dfs(int u,int f){//计算 sz 和 dfn
	dfn[u]=++tim;
	dfx[tim]=u;
	sz[u]=1;
	for(int i=head[u];i!=-1;i=e[i].nxt){
		int v=e[i].to;
		if(v==f) continue;
		dfs(v,u);
		sz[u]+=sz[v];
	}
}

signed main(){
	
	init();
	
	int n,q;
	
	scanf("%lld %lld",&n,&q);
	for(int i=1;i<n;i++){
		int u,v;
		scanf("%lld %lld",&u,&v);
		add(u,v);
		add(v,u);
	}
	
	dfs(1,0);
	build(1,1,n);
	
	while(q--){
		int op;
		scanf("%lld",&op);
		if(op==1){
			int x,c;
			scanf("%lld %lld",&x,&c);
			int l=dfn[x],r=dfn[x]+sz[x]-1;
			iterator it=st[c].upper_bound(dfn[x]);
			if(it!=st[c].begin()){
				it--;
				if(dfn[x]>=*it&&dfn[x]<=*it+sz[dfx[*it]]-1) continue;//情况2，可以跳过该操作
			}
			iterator it2=st[c].lower_bound(dfn[x]);
			while(it2!=st[c].end()&&*it2<=r){//暴力删子孙
				int now=*it2;
				update(1,1,n,now,now+sz[dfx[now]]-1,-1);
				st[c].erase(it2);
				it2=st[c].lower_bound(dfn[x]);
			}
			update(1,1,n,l,r,1);
			st[c].insert(dfn[x]);
		}else{//查询
			int x;
			scanf("%lld",&x);
			printf("%lld\n",query(1,1,n,dfn[x],dfn[x]+sz[x]-1));
		}
	}
	
	return 0;
}


```


---

## 作者：我怂了 (赞：3)

### 写在前面
怎么其他的 dalao 都是用的 set 啊，我好菜 qwq 看不懂，所以用了一种很笨的方法，但是本人觉得还是挺易于理解的。

这题校内做过一个类似的，题面已经上传到了[我自己发的一道题里面](https://www.luogu.com.cn/problem/U371549)（看看得了，还没造数据捏 qwq，以后啥时候有时间再说吧）
### 解题思路
先把问题转化到 dfn 序列上。

然后先考虑一个简单的问题：只使用一种颜色染色。此时问题变得异常简单，只需要线段树维护区间推平就好了。

但是为了扩展到这道题，要采用一种比较笨的方法：开两棵线段树，一棵存储 bool 值，维护某个区间内是否已经被染色；另一棵维护区间加和区间和。

在操作的时候，在第一棵线段树上做一个类似查询的操作，一边查一边在第二棵线段树上修改，代码如下（用的动态开点，`Segt` 是区间加线段树）：
```cpp
struct nod{
	signed ls,rs;
	bool tag;//tag不是传统意义上的懒标记，而是标定该区间是否已经被全部染色。
}t[maxn<<2];
int cnt;
void up(int x){
	t[x].tag=t[t[x].ls].tag&&t[t[x].rs].tag;//这个区间全被染色当且仅当其左右儿子都全被染色了。
}
void cha(int x,int l,int r,int ll,int rr){
	if((l>=ll&&r<=rr)||t[x].tag){
		t[x].tag=true;
		return;
	}
	signed mid=(l+r)>>1;
	if(ll<=mid){
		if(!t[x].ls){
			t[x].ls=++cnt;
		}
		cha(t[x].ls,l,mid,ll,rr);
	}
	if(rr>mid){
		if(!t[x].rs){
			t[x].rs=++cnt;
		}
		cha(t[x].rs,mid+1,r,ll,rr);
	}
	up(x);
}
void op(int x,int l,int r,int ll,int rr){
	if(t[x].tag){//这个节点代表的区域全都被染色了，直接返回。
		return;
	}
	if((!t[x].ls)&&(!t[x].rs)&&(ll<=l&&r<=rr)){//此时这个节点是新建的，其中的区域啥也没有。
		Segt.Add(1,1,n,l,r,1);
		return;
	}
	int mid=(l+r)>>1;
	if(ll<=mid){
		if(!t[x].ls){
			t[x].ls=++cnt;
		}
		op(t[x].ls,l,mid,ll,rr);
	}
	if(rr>mid){
		if(!t[x].rs){
			t[x].rs=++cnt;
		}
		op(t[x].rs,mid+1,r,ll,rr);
	}
}
void Op(int l,int r){
	op(1,1,n,l,r);
	cha(1,1,n,l,r);
}
```
#### 复杂度分析
有同志一看：你这不分分钟给你卡成 $O(n^2\log n)$？

但是实际上，如果要使这种方式的复杂度达到上述那个恐怖的级别，必须要构造那种多次在有、无、有、无这种交替的区间上进行修改的数据。

但是，为了构造出一次这种操作，需要现在 $\dfrac{n}{2}$ 次操作中间隔进行修改，然后再一次性修改这些单点所在的区间，进而在单次操作中达到 $O(n\log n)$ 的复杂度。但是之前的 $\dfrac{n}{2}$ 次操作都是 $O(\log n)$ 的，所以总体复杂度依然是 $O(n \log n)$ 一级。
### 扩展到本题
有同志问了：一棵线段树可以维护一个颜色，那么本题有十万个颜色，就需要十万棵线段树？？？

我：是的呢亲！

这空间不炸得死去活来？

但是先别急，还记得动态开点吗？单次的修改操作至多会增加 $O(\log n)$ 个节点，所以最终的空间被控制在了 $O(q\log n)$ 级别，时间复杂度也是 $O(q\log n)$，
吸氧状态下最慢点 86ms，总耗时 651ms。
### 整体代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=1e5+5;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
struct no{
	int val,tag;
};
struct segt{//封装一下线段树，防止与下面那十万棵函数、变量名字冲突。
	no t[maxn<<2];
	void up(int x){
		t[x].val=t[ls(x)].val+t[rs(x)].val;
	}
	void add(int x,int l,int r,int v){
		t[x].val+=(r-l+1)*v;
		t[x].tag+=v;
	}
	void down(int x,int l,int r){
		if(!t[x].tag){
			return;
		}
		int mid=(l+r)>>1;
		add(ls(x),l,mid,t[x].tag),add(rs(x),mid+1,r,t[x].tag);
		t[x].tag=0;
	}
	void Add(int x,int l,int r,int ll,int rr,int v){
		if(l>=ll&&r<=rr){
			add(x,l,r,v);
			return;
		}
		int mid=(l+r)>>1;
		down(x,l,r);
		if(ll<=mid){
			Add(ls(x),l,mid,ll,rr,v);
		}
		if(rr>mid){
			Add(rs(x),mid+1,r,ll,rr,v);
		}
		up(x);
	}
	int query(int x,int l,int r,int ll,int rr){
		if(l>=ll&&r<=rr){
			return t[x].val;
		}
		int mid=(l+r)>>1,ans=0;
		down(x,l,r);
		if(ll<=mid){
			ans+=query(ls(x),l,mid,ll,rr);
		}
		if(rr>mid){
			ans+=query(rs(x),mid+1,r,ll,rr);
		}
		return ans;
	}
}Segt;
struct nod{
	signed ls,rs;
	bool tag;
}t[maxn<<5];
int root[maxn],cnt,n,q;
void up(int x){
	t[x].tag=t[t[x].ls].tag&&t[t[x].rs].tag;
}
void cha(int x,int l,int r,int ll,int rr){
	if((l>=ll&&r<=rr)||t[x].tag){
		t[x].tag=true;
		return;
	}
	signed mid=(l+r)>>1;
	if(ll<=mid){
		if(!t[x].ls){
			t[x].ls=++cnt;
		}
		cha(t[x].ls,l,mid,ll,rr);
	}
	if(rr>mid){
		if(!t[x].rs){
			t[x].rs=++cnt;
		}
		cha(t[x].rs,mid+1,r,ll,rr);
	}
	up(x);
}
void op(int x,int l,int r,int ll,int rr){
	if(t[x].tag){
		return;
	}
	if((!t[x].ls)&&(!t[x].rs)&&(ll<=l&&r<=rr)){
		Segt.Add(1,1,n,l,r,1);
		return;
	}
	int mid=(l+r)>>1;
	if(ll<=mid){
		if(!t[x].ls){
			t[x].ls=++cnt;
		}
		op(t[x].ls,l,mid,ll,rr);
	}
	if(rr>mid){
		if(!t[x].rs){
			t[x].rs=++cnt;
		}
		op(t[x].rs,mid+1,r,ll,rr);
	}
}
void Op(int col,int l,int r){
	if(!root[col]){
		root[col]=++cnt;
		Segt.Add(1,1,n,l,r,1);
	}
	else{
		op(root[col],1,n,l,r);
	}
	cha(root[col],1,n,l,r);
}
struct linestar{//链式前向星
	signed head[maxn<<1],last[maxn],to[maxn<<1],cnt;
	void add(int x,int y){
		head[++cnt]=last[x];
		last[x]=cnt;
		to[cnt]=y;
	}
}edg;
signed siz[maxn],dfn[maxn],tot;
void dfs(int x,int fa){
	dfn[x]=++tot;
	siz[x]=1;
	for(int i=edg.last[x];i;i=edg.head[i]){
		signed to=edg.to[i];
		if(to==fa){
			continue;
		}
		dfs(to,x);
		siz[x]+=siz[to];
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int x,y;
		cin>>x>>y;
		edg.add(x,y);
		edg.add(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=q;i++){
		int op,x,c;
		cin>>op>>x;
		if(op==1){
			cin>>c;
			Op(c,dfn[x],dfn[x]+siz[x]-1);
		}
		else{
			cout<<Segt.query(1,1,n,dfn[x],dfn[x]+siz[x]-1)<<'\n';
		}
	}
}
```
### 感谢阅读！

---

## 作者：dgdyrkst (赞：3)

## 思路
因为总的染色操作数不会很多，而一次染色操作又对应了一棵子树的答案改变，所以考虑用 set 来维护被染色子树的根节点。

而每次操作相当于子树加减，所以我们再用线段树维护 dfs 序列上的值即可。
## 实现
起手预处理，求出每个节点的 dfs 序以及子树中的最大 dfs 序。

这两个值就是每个节点的子树在 dfs 序列上对应的区间。

对于 __每种颜色__ 开一个 set，存被染色子树的根节点。

会发现如果 set 表示的染色区域有重叠的话答案就会多算，也就是说我们要让 set 中每个点都没有它子树中的节点在这个 set 里面。

考虑按 dfs 序排序，然后加入一个点时，我们假设之前的 set __已经维护好了__ ，只要对于这个新点维护性质就可以了。

如果这个点的祖先节点存在，那么这个祖先一定没有祖先和后代在这个 set 里，根据 dfs 序的 __连续性__ ，插入新点之后，它必定在自己这个祖先的下一个位置。

也就是说如果 set 中 它 dfs 序的前驱是它的祖先的话，我们应当不执行此次操作，相当于对全染上某种颜色的子树再染一遍同样的颜色。

判断这个点是不是它的祖先的话，其实只要看这个点 __对应子树的区间__ 是否包含它就可以了。

否则，我们向 set 中插入这个点，会发现其中可能存在一些它的后代，我们应当向后扫描并且删除后面的节点直到 __某个节点不是它的后代__ 。

正确性和上文类似，如何判断也基本相同，这里不多赘述。

维护好了 set，我们还需要一个强力的数据结构来维护答案，这就是 __线段树__ 。

对于每个新加入 set 的点，相当于它整棵子树答案都 $+1$，对于每个被弹出 set 的点，相当于它整棵子树答案都 $-1$。

答案即是对某个子树对应的区间求和，是非常简单的线段树应用。

## 代码
以下为代码参考。
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+5;
int n,m,op,x,y,dfn[N],wei[N],low[N],cnt;
//dfn是每个节点的dfs序，wei是每个dfs序对应的节点，low是该节点子树中最大dfn值
//实现时注意不要将这三个数组搞混
vector<int> v[N];
set<int> st[N];
set<int> :: iterator pos;
struct segment_tree
{
	int l,r,len,sum,lazy;
}t[N<<2];
void dfs(int now,int fa)
{
	dfn[now]=++cnt,wei[cnt]=now;
	for (int i=0;i<v[now].size();i++)
	{
		if (v[now][i]==fa)continue;
		dfs(v[now][i],now);
	}
	low[now]=cnt;
}
void pushup(int p)
{
	t[p].sum=t[p<<1].sum+t[p<<1|1].sum; 
}
void pushdown(int p)
{
	t[p<<1].lazy+=t[p].lazy,t[p<<1|1].lazy+=t[p].lazy;
	t[p<<1].sum+=t[p].lazy*t[p<<1].len,t[p<<1|1].sum+=t[p].lazy*t[p<<1|1].len;
	t[p].lazy=0;
}
void build(int l,int r,int p)
{
	t[p].l=l,t[p].r=r,t[p].len=r-l+1;
	if (l==r)return;
	int mid=l+r>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
}
void add(int l,int r,int d,int p)
{
	if (t[p].l>=l && t[p].r<=r)
	{
		t[p].sum+=d*t[p].len,t[p].lazy+=d;
		return;
	}
	pushdown(p);
	int mid=t[p].l+t[p].r>>1;
	if (l<=mid)add(l,r,d,p<<1);
	if (r>mid)add(l,r,d,p<<1|1);
	pushup(p);
}
int ask(int l,int r,int p)
{
	if (t[p].l>=l && t[p].r<=r)return t[p].sum;
	pushdown(p);
	int mid=t[p].l+t[p].r>>1,ret=0;
	if (l<=mid)ret+=ask(l,r,p<<1);
	if (r>mid)ret+=ask(l,r,p<<1|1);
	return ret;
}
signed main()
{
	scanf("%lld%lld",&n,&m);
	for (int i=1;i<n;i++)
	{
		scanf("%lld%lld",&x,&y);
		v[x].push_back(y),v[y].push_back(x); 
	}
	dfs(1,0);
	build(1,n,1); 
	while (m--)
	{
		scanf("%lld%lld",&op,&x);
		if (op==1)
		{
			scanf("%lld",&y);
			pos=st[y].lower_bound(dfn[x]);
			if (pos!=st[y].begin())
			{
				pos--;
				if (low[wei[*pos]]>=low[x])continue;
				pos++;
			}
			while (pos!=st[y].end() && *pos<=low[x])add(*pos,low[wei[*pos]],-1,1),st[y].erase(pos++);
			st[y].insert(dfn[x]),add(dfn[x],low[x],1,1);
		}
		else
		{
			printf("%lld\n",ask(dfn[x],low[x],1));
		}
	}
	return 0;
}
```

---

## 作者：wf1594937223 (赞：3)

小白教程-从零开始认识这道题。

之前两位大佬已经将思路讲得很完整了，只是有一些具体的实现没有讲得很全，只在其代码中有体现。所以我在此做一篇主攻实现的题解。

**本题的思路**

先用 **DFS序** 将整棵树转化成一个序列(我们用 $dfn[x]$ 表示 $x$ 的DFS序，用 $low[x]$ 表示 $x$ 的子树中(含 $x$ ) $dfn$ 最大的点的 $dfn$)，用颜料数( $10^5$ )个 $set$ 维护被染上每种颜色的 **区间** (为了方便查询，此处存储的区间是反的，即 $set$ 里面的元素的 $first>second$ )，再开两个树状数组 $c1,c2$。查询时分为两部分，即 $x$ (含义如题中所示)祖先对查询的影响(也就是整棵被查询子树都被染上的颜色)与子树内部节点对查询的影响。

**本题的具体实现**

每一个 $set$ 维护的区间要保证不出现包含关系，也就是不会出现一个 $set$ 中出现两个 $pair\ p1,p2$ 满足 $p1.first<p2.first\ \&\ p1.second>p2.second$ ，这样我们在查询时才可以做到不重不漏。关于如何做到这一点，我们可以在每次插入时 $lower\_bound(p),$ 其中 $p.first=dfn[x],p.second=0$ 。如果我们搜出来的区间 **包含** 我们将要插入的区间，那么我们直接略过此次修改；如果我们搜出来的区间 **被包含于** 我们将要插入的区间，那么我们 **撤销** 那次操作的 **所有影响** ，并**继续搜索**直到搜出来的区间与我们将要插入的区间不交为止，并 **插入** 本个区间并添加其影响。

关于影响：

我们用 $c1$ 来 **差分维护** 每个节点的 **总颜色数**(比如第一次染了节点 $x1$ ，那么就在 $c2$ 的 $dfn[x1]$ 节点上加上 $1$ 的数值，在 $low[x1]$ 节点上加上 $-1$ 的数值)，用 $c2$ 来维护(普通维护)每个节点目前所做的 **贡献** (比如第一次染了节点 $x1$ ，那么就在 $c2$ 的 $dfn[x1]$ 节点上加上 $low[x1]-dfn[x1]+1$ 的数值)

查询时，我们只需查询 $c1$ 中 $1-dfn[x]$ 的部分(设为 $ans1$ )与 $c2$ 中 $dfn[x]+1-low[x]$ 的部分(设为 $ans2$ )，那么最终答案就是 $ans1 \times (low[x]-dfn[x]+1)+ans2$ ，**记得取模**。

---

## 作者：Anonymely (赞：1)

考虑对于每种颜色分开处理，一种直接的想法是建立出每种颜色的虚树，修改时若已经被染色就不管，否则相当于把所有子树内已经染色的区域全撤回再加入整个子树染色，由于每个点最多只会染一次和撤回一次，均摊正确。

而对于子树内染色，维护 $dfn$ 序后变为区间加，区间求和，BIT 维护即可。

思路好想但是似乎有一点点难写。

实际上不用这么麻烦，发现本质还是对 $dfn$ 序列操作，每次相当于一段区间推平，每种颜色开一个 ODT 维护即可。

复杂度 $O(n \log n)$。


```cpp
#include <bits/stdc++.h>
using namespace std;

#define QwQ01AwA return 0
#define ll long long
#define look_time cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n'
template <typename T> void ckmax(T &x, const T y) {x = max(x, y);}
template <typename T> void ckmin(T &x, const T y) {x = min(x, y);}

const int N = 1e5 + 5;
int n, m;
ll t[N][2];
void upd(int x, int w) {
    for (int i = x; i <= n; i += i & (-i)) t[i][0] += w, t[i][1] += x * w; 
}
ll query(int x) {
    ll res = 0;
    for (int i = x; i; i -= i & (-i)) res += 1ll * t[i][0] * (x + 1) - t[i][1];
    return res;
}
void upd(int l, int r, int c) {upd(l, c), upd(r + 1, -c);}
ll query(int l, int r) {return query(r) - query(l - 1);}
vector <int> e[N];
int L[N], R[N], tim;
struct Chtholly_Nota_Seniorious {
    map <int, int> mp;
    auto split(int x) {
        auto it = --mp.upper_bound(x);
        mp[x] = it -> second;
        return mp.find(x);
    }
    void cov(int l, int r) {
        auto L = split(l), R = split(r + 1);
        for (auto it = L; it != R; it++) if (it -> second == 2) upd(it -> first, next(it) -> first - 1, -1);
        mp.erase(L, R);
        mp[l] = 2;
        upd(l, r, 1);
    }
} col[N];
void dfs(int u, int fa) {
    L[u] = ++tim;
    for (auto v : e[u]) if (v != fa) dfs(v, u);
    R[u] = tim;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        e[u].push_back(v), e[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= 1e5; i++) col[i].mp[1] = 1, col[i].mp[n + 1] = -1;
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, c;
            cin >> x >> c;
            col[c].cov(L[x], R[x]);
        } else {
            int x;
            cin >> x;
            cout << query(L[x], R[x]) << '\n';
        }
    } 
    QwQ01AwA;
}
```

---

## 作者：Purslane (赞：1)

## Solution

看到子树 , 果断转为 `DFS` 序 .

考虑使用 `set` 来存每种颜色的点 , 来表示这个点的子树全被染上这一种颜色 . 注意 , 这些点不可存在包含关系 , 不然会出现重复 .

考虑如何维护 . 新加入一个点 , 先判断它的祖先是否已经入 . 如果是 , 则退出 .

> 在 set 中二分找到 dfn 小于等于 u 的最大的点 . 如果 u 的祖先已经在里面了 , 则这个点必是 u 的祖先 . 因为祖先的其它后代已经在前面被删掉了 .

然后依次删除它的后代 .

> 在 set 里找 . 有人认为复杂度是 $O(nm \text{log} m)$ 的 , 实际上 , 每个点只会被加入一次删除一次 , 所以复杂度是 $O(m \text{log} m)$ 的 .

对于询问 , 先要知道它的祖先们和后代有多少在各个 `set` 中 . 

可以开 2 个树状数组 . 一个维护祖先的值 , 具体表现在给祖先的子树区间加1 , 询问的时候单点求和 , 就知道它有多少个祖先在 `set` 里 .

另一个维护子树 , 把一个子树的染色集中在根 , 询问时对其子树区间求和 .

注意我们把结点当做自己的祖先 , 所以第二个树状数组询问时不可以算上那个结点本身 .

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=1e5+10;
int n,q,idx,dfn[MAXN],low[MAXN],rev[MAXN];
vector<int> G[MAXN];
set<int> col[MAXN];
int lowbit(int k) {
	return k&-k;
}
struct BIT {
	int n,tr[MAXN];
	void init(int N) {
		return n=N,memset(tr,0,sizeof(tr)),void();
	}
	void update(int pos,int v) {
		while(pos<=n) tr[pos]+=v,pos+=lowbit(pos);
		return ;
	}
	int Query(int pos) {
		int ans=0;
		while(pos) ans+=tr[pos],pos-=lowbit(pos);
		return ans;
	}
	int query(int l,int r) {
		return Query(r)-Query(l-1);
	}
}bit1,bit2; //bit1 用来记录总体修改 bit2 用来记录字数内修改
void dfs(int u,int f) {
	dfn[u]=++idx,rev[idx]=u;
	for(int to:G[u]) {
		if(to==f) continue;
		dfs(to,u);
	}
	low[u]=idx;
	return ;
}
int ancestor(int u,int c) {
	auto it=col[c].upper_bound(dfn[u]);
	if(it==col[c].begin()) return 0;
	it=prev(it);if(low[rev[*it]]>=low[u]) return 1;
	return 0;
}
signed main() {
	scanf("%lld %lld",&n,&q);
	ffor(i,1,n-1) {
		int u,v;
		scanf("%lld %lld",&u,&v);
		G[u].push_back(v),G[v].push_back(u);
	}
	dfs(1,0);
	bit1.init(n),bit2.init(n);
	ffor(i,1,q) {
		int op,x,c;
		scanf("%lld %lld",&op,&x);
		if(op==1) {
			scanf("%lld",&c);
			if(ancestor(x,c)) continue;
			auto it=col[c].upper_bound(dfn[x]);
			while(it!=col[c].end()&&dfn[rev[*it]]<=low[x]) {
				int v=rev[*it];
				bit1.update(dfn[v],-1),bit1.update(low[v]+1,1),bit2.update(dfn[v],-(low[v]-dfn[v]+1));
				col[c].erase(it++);
			}
			bit1.update(dfn[x],1),bit1.update(low[x]+1,-1),bit2.update(dfn[x],low[x]-dfn[x]+1);
			col[c].insert(dfn[x]);
		}
		else printf("%lld\n",bit1.query(1,dfn[x])*(low[x]-dfn[x]+1)+bit2.query(dfn[x]+1,low[x]));
	}
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

本题是一道在树上进行子树修改的并查询的题目，很显然，**我们要将每一颗子树转化成一个数组**，编号即为每个点的深度优先搜索序，这样方便我们进行修改，毕竟也没有树上树状数组嘛。

首先，我们要对这道题分两种情况讨论，**一种是 $u$ 祖先的子树均被染色，则 $u$ 子树也会被染成该颜色，贡献即为 $u$ 子树的大小**。另外一种是**若 $u$ 子树部分已经被染成该颜色，则要加回来**，否则会重复计算。

我们接着可以发现可以用两个树状数组维护两种情况，情况一为区间加，单点查，另外一种情况是区间查，单点加。

注意，我们在统计两种情况的贡献值时会发现有重复计算的地方，我们便可以将每种颜色开一个红黑树来保存每种颜色的情况，若祖先已经染过这种颜色则不管，**若没有则先把新节点的子树中有该颜色的全部删掉，再加上去，防止重复计算**。

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
inline int lowbit(int x)
{
    return x & -x;
}
const int N = 1e5 + 10;
int n, m;
struct bit
{
    int tr[N];
    void add(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
        {
            tr[i] += v;
        }
    }
    int qry(int x)
    {
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
        {
            res += tr[i];
        }
        return res;
    }
} t1, t2;
struct edge
{
    int to, next;
} edge[N << 1];
int head[N], cnt;
void add(int u, int v)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    head[u] = cnt;
}
set<int> s[N];
set<int>::iterator it;
int dfn[N], siz[N], id[N], bh;
void dfs(int x, int fa)
{
    dfn[x] = ++bh, id[bh] = x, siz[x] = 1;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int y = edge[i].to;
        if (y == fa)
        {
            continue;
        }
        dfs(y, x);
        siz[x] += siz[y];
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++)
    {
        int u, v, w;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int op, x, c;
        cin >> op;
        if (op == 1)
        {
            cin >> x >> c;
            it = s[c].lower_bound(dfn[x]);
            if (it != s[c].begin() && dfn[id[*prev(it)]] + siz[id[*prev(it)]] >= dfn[x] + siz[x])
            {
                continue;
            }
            while (it != s[c].end() && *it < dfn[x] + siz[x])
            {
                t1.add(*it, -1);
                t1.add(*it + siz[id[*it]], 1);
                t2.add(*it, -siz[id[*it]]);
                s[c].erase(it++);
            }
            s[c].insert(dfn[x]), t1.add(dfn[x], 1), t1.add(dfn[x] + siz[x], -1), t2.add(dfn[x], siz[x]);
        }
        else
        {
            cin >> x;
            cout << siz[x] * t1.qry(dfn[x]) + t2.qry(dfn[x] + siz[x] - 1) - t2.qry(dfn[x]) << endl;
        }
    }
    return 0;
}

```

---

## 作者：phil071128 (赞：0)

 # [P5852 Bessie's Snow Cow P] 题解
> 给定一棵树，点有颜色（可以叠加）。两种操作：
>
> 1. 将 $x$ 整个子树增加一种颜色 $k$。
> 2. 查询 $x$ 整个子树，每个节点的颜色数量之和。注意不是整个子树的颜色数。
>
> $n,k\le 10^5$。 

我们开 $k$ 个 `std::set` 维护颜色为 $i$ 的 **不交节点区间**，换句话说，存下的是若干棵不交的子树的根节点。体现在操作中的就是每次加入点 $u$，要删除 `set` 内 $u$ 子树的所有点。注意每个点只会被加入一次删除一次，所以复杂度是 $O(n\log n)$。

对于查询的操作，我们仍用线段树，记 $t_u$ 为 $u$ 的不同颜色个数，查询就是子树和。

对于修改的操作，如果 `set` 里已经有其祖先了，直接跳过不管；否则，我们删除 `set` 内一个点时，要将其贡献清除，也就是这个子树区间减一。最后加入 $u$，整个子树区间加一。

代码难点在 `set` 遍历上：

找祖先：如果存在祖先，一定是当前 $u$ 的前一个点（以 `dfn` 为键），否则如果前一个不是祖先，那么就没有祖先，

注意 `set` 的边界问题：指针加减前后要判断和 `begin()` 与 `end()` 是否相等。

（ `set.erase` 后寻址不连续，所以必须用 `lower_bound` 找到下一个点。）

[提交记录](https://www.luogu.com.cn/record/128473066)

---

## 作者：Otomachi_Una_ (赞：0)

## 题目简述

> - 给定以 $1$ 为根的树，维护一下两种操作：
>   - 给 $u$ 为根的树节点染颜色 $col$。
>   - 询问以 $u$ 为根的树中所有节点曾经染过**不同**颜色的数量和。
> - $n,q\leq10^5$。

## 解题思路

看到子树第一步想到 $dfs$ 序转换成区间问题。

我们只需单独考虑每一种颜色。不难发现在进行操作 $1$ 的时候可能有“吞并”的情况。解决此情况，只需要给每一种颜色 $c$ 开一个 `set` 存入现在所有用 $c$ 染期子树的节点，每次不断弹出 $dfs$ 序第一个比 $x$ 的 $dfs$ 序大的元素记为 $y$。如果 $dfs_y\leq dfs_x+size_x$ 也就是 $y$ 在 $x$ 的子树内，就把 $y$ 的贡献先清理掉。我们再找 `set` 当中第一个比 $dfs_x$ 小的元素 $z$，如果 $x$ 在 $z$ 的子树内那 $x$ 的贡献就不用加了。否则给区间 $[ls_x,ls_x+size_x]$ 加 $1$（方便起见，代码中的 `set` 直接存储 $dfs$ 序）。

查询直接查询区间 $[ls_x,ls_x+size_x]$ 的和即可。

不难发现我们把原问题变成了区间加，区间查询，直接用线段树维护即可。

时间复杂度：$O((n+q)\log n)$。

## 参考代码

```cpp
#include<iostream>
#include<set>
#include<vector> 
using namespace std;
#define ll long long
#define IT set<int>::iterator
const int MAXN=1e5+5;
int a[MAXN];
set<int> se[MAXN];
int ls[MAXN],rs[MAXN],dfn[MAXN],tot=0;
int n,q;
vector<int> ve[MAXN];
struct sugtree{
	ll siz,val,laz;
}p[MAXN<<2];
void dfs(int u,int fa){
	ls[u]=++tot,dfn[tot]=u;
	for(int v:ve[u])
		if(v!=fa)
			dfs(v,u);
	rs[u]=tot;
	return;
}
void build(int id=1,int l=1,int r=n){
	p[id].siz=(r-l+1);
	if(l==r) return;
	int mid=l+r>>1;
	build(id<<1,l,mid);
	build(id<<1|1,mid+1,r);
}
void pushdown(int id){
	p[id<<1].val+=p[id<<1].siz*p[id].laz,
	p[id<<1|1].val+=p[id<<1|1].siz*p[id].laz,
	p[id<<1].laz+=p[id].laz,
	p[id<<1|1].laz+=p[id].laz;
	p[id].laz=0; 
	return;
}
void pushup(int id){
	p[id].val=p[id<<1].val+p[id<<1|1].val;
	return;
}
void add(int id,int l,int r,int L,int R,int d){
	if(L<=l&&r<=R){
		p[id].val+=p[id].siz*d;
		p[id].laz+=d;
		return;
	}
	pushdown(id);
	int mid=l+r>>1;
	if(L<=mid) add(id<<1,l,mid,L,R,d);
	if(mid<R) add(id<<1|1,mid+1,r,L,R,d);
	pushup(id);
	return;
}
ll query(int id,int l,int r,int L,int R){
	if(L<=l&&r<=R)
		return p[id].val;
	pushdown(id);
	int mid=l+r>>1;ll ans=0;
	if(L<=mid) ans+=query(id<<1,l,mid,L,R);
	if(mid<R) ans+=query(id<<1|1,mid+1,r,L,R);
	return ans;
}
int main(){
	cin>>n>>q;
	for(int i=1;i<n;i++){
		int u,v;cin>>u>>v;
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	build();
	dfs(1,0);
	while(q--){
		int op;cin>>op;
		if(op==1){
			int x,col;
			cin>>x>>col;
			IT it=se[col].upper_bound(ls[x]);
			while(it!=se[col].end()&&*it<=rs[x]){
				add(1,1,n,*it,rs[dfn[*it]],-1);
				se[col].erase(it);
				it=se[col].upper_bound(ls[x]);
			}
			if(it!=se[col].begin()){
				it--;
				if(ls[x]<=rs[dfn[*it]])//被包含在 *it 中
					continue; 
			}
			se[col].insert(ls[x]);
			add(1,1,n,ls[x],rs[x],1);
		}
		else{
			int x;cin>>x;
			cout<<query(1,1,n,ls[x],rs[x])<<endl;
		}
	}
	return 0;
}
```





---

## 作者：glorious_dream (赞：0)

### 题目分析：

判断是否存在两个集合，使这两个集合的交集不为空，并且一个当中的某些元素也在另一个当中出现过。

### 算法分析：

首先来看暴力：很容易想到根据题目所给的信息来枚举，每次判断两个集合是否能满足条件。期望得分 $40$。

然后来看正解：容易发现，如果按照所给集合的大小从大到小排序，那么前一个集合一定不会是后一个集合的真子集。这时可以用染色法来求解。

考虑某一个集合，把它能到的点(也就是这个人会做的题的编号)给染成一种颜色，一层一层往下覆盖。

那么怎么求答案呢？考虑某一个集合，如果这个集合能覆盖到两种颜色，那么必然说明该集合和某一个覆盖这两种颜色之一的集合是答案。但是具体是哪一个呢？肯定是覆盖的颜色小的那一个集合喽(不明白的话代码里有详解)。

但是，就差最后一步了！如果某一个集合覆盖的点颜色为 $0$ 的话，那么就输出这个集合。

### 代码+注释详解

```cpp
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
#define re register 
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch == '-') f=-1 ; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48) ; ch=getchar();}
    return x*f;
}
const int M = 1e6+10;
vector<int>v[M]; //要用vector才能不爆空间 
int T,n;
int col[M],k[M],rak[M];
bool cmp(int x,int y) {return k[x] > k[y];} //自定义一个比较函数，按照k的值从大到小排序 
void work(){
    n=read();
    memset(col,0,sizeof(col));
    memset(k,0,sizeof(k));
    memset(rak,0,sizeof(rak)); //一定要清空数组，考试的时候我就没清空直接爆零 
    for(re int i(1) ; i<=n ; ++i){
        k[i] = read(); 
        v[i].clear(); //同样需要清空vector 
        for(re int j(1) ; j<=k[i] ; ++j){
            int x=read();
            v[i].push_back(x); //把i这个点会做的题给存入vector 
        }
        rak[i] = i; //i这个点的编号 
    }
    sort(rak+1,rak+n+1,cmp); //按k的大小，从大到小排序 
    int cnt=1;
    for(re int i(0) ; i<v[rak[1]].size() ; ++i) col[v[rak[1]][i]] = rak[1]; //先预处理出最大的集合，放在循环里也行 
    k[0]=1e9; //特殊情况，下面说 
    for(re int i(2) ; i<=n ; ++i){
        cnt++;
        int color = 0,pd = 0;
        for(re int j(0) ; j<v[rak[i]].size() ; ++j){ //核心部分，先遍历这个vector 
            if(color != col[v[rak[i]][j]] && pd == 1){ //说明已经有两种颜色了 
                printf("YES\n%d %d\n",rak[i],k[col[v[rak[i]][j]]]<k[color]?col[v[rak[i]][j]]:color);
		//重点来了：如果color都不是0，那么输出较小的那一个集合
		//如果color所能覆盖是0，也就是上面的特殊情况，那么就输出color 
                return;
            }
            if(pd == 0) pd=1;
            color = col[v[rak[i]][j]]; //把颜色赋值为第一个点下面覆盖的颜色 
            col[v[rak[i]][j]] = rak[i]; //注意，把这些点的颜色标记为rak，后面才能继续做 
        }
    }
    printf("NO\n"); //循环完都没找到的情况 
    return;
}
signed main(){
    //freopen("test.in","r",stdin);
    //freopen("test.out","w",stdout);
    T=read();
    while(T--) work();	//每一次跑就行了 
    return 0;
}
```

如果有什么不懂的，欢迎在下面评论。


---

## 作者：Terac (赞：0)

[$\texttt{link}$](https://www.luogu.com.cn/problem/P5852)

## 题意

给出一颗 $n$ 个点的树，根为 $1$，定义点 $u$ 的权值为 $u$ 上不同的颜色的数量，$m$ 次操作：

1. 将 $u$ 的子树中没有颜色 $c$ 的点加上颜色 $c$。
2. 查询 $u$ 子树的权值和。  

  
数据范围： $n,m,c\le 10^5$。

## 题解

首先可以用 dfs 序把子树转移到区间上去。

发现一个点 $u$ 子树的权值和贡献有两种：

1. $u$ 祖先的子树均被染色，那点 $u$ 子树也会被染色，贡献就是子树大小。

2. $u$ 子树部分被染色，要加回来。

可以用两个 DS，一个维护每个点情况 $1$ 的贡献，区间加，单点查，一个维护该点情况 $2$ 对子树的贡献，单点加，区间查。直接树状数组维护。

发现两种情况会有重复部分，可对每个颜色开一个 set，维护情况 $1$ 中被染色的子树根节点的 dfn，新加入一个节点时，分两种情况：

1. 有祖先的子树被染色，此时不需要再加入。

2. 没有祖先的子树被染色，先把新节点子树中在 set 里的全部减掉，再把该节点加进去。转换到区间上就是把新的子树区间并上已经在 set 里的区间，把被包含的区间全部删掉即可。发现每次操作 set 最多加 $1$ 个节点，总数不会超过 $m$，复杂度有保证。

每次查询寻找 dfn 前驱复杂度 $O(\log n)$，树状数组维护是 $O(\log n)$，所以总复杂度为 $O(n+m\log n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
namespace IO {
	//read and write
} using namespace IO;
const int N = 1e5 + 10;
int n, q;
struct bit {
	int t[N];
	void add(int x, int v) { for(int i = x; i <= n; i += i & -i) t[i] += v; }
	int qry(int x) { int res = 0; for(int i = x; i; i -= i & -i) res += t[i]; return res; }
} t1, t2;
struct edge {
	int to, nxt;
} e[N << 1];
int head[N], cnt;
void add(int u, int v) {
	e[++cnt] = (edge){v, head[u]};
	head[u] = cnt;
}
set<int> s[N];
set<int>::iterator it;
int dfn[N], siz[N], id[N], tim;
void dfs(int u, int fa) {
	dfn[u] = ++tim, id[tim] = u, siz[u] = 1;
	for(int i = head[u], v; i; i = e[i].nxt) {
		v = e[i].to;
		if(v == fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
	}
}
int main() {
	n = read(), q = read();
	for(int i = 1, u, v; i < n; i++) {
		u = read(), v = read();
		add(u, v), add(v, u);
	}
	dfs(1, 0);
	for(int i = 1, opt, u, c; i <= q; i++) {
		opt = read(), u = read();
		if(opt == 1) {
			c = read();
			it = s[c].lower_bound(dfn[u]);
			if(it != s[c].begin() && dfn[id[*prev(it)]] + siz[id[*prev(it)]] >= dfn[u] + siz[u]) continue;
			while(it != s[c].end() && *it < dfn[u] + siz[u])
				t1.add(*it, -1), t1.add(*it + siz[id[*it]], 1), t2.add(*it, -siz[id[*it]]), s[c].erase(it++);
			s[c].insert(dfn[u]), t1.add(dfn[u], 1), t1.add(dfn[u] + siz[u], -1), t2.add(dfn[u], siz[u]);
		}
		else printf("%d\n", siz[u] * t1.qry(dfn[u]) + t2.qry(dfn[u] + siz[u] - 1) - t2.qry(dfn[u]));
	}
	return 0;
}
```


---

