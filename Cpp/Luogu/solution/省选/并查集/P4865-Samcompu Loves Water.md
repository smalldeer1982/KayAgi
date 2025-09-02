# Samcompu Loves Water

## 题目背景

Samcompu拥有大量的**"水"**资源！！

## 题目描述

Samcompu需要制定一个**水**计划。这个计划的主要目的就是为了避开老师监视的时间来水。

老师在中途会离开机房$T$次，第$i$次将会离开$tim_i$秒。Samcompu划水的时候可不是随便乱水的。他可是拥有**"水"**资源的。在他的库存中有$N$个可以水的网站。Samcompu拥有一种黑科技，他可以几乎不耗任何时间在网站与网站之间跳转并且把跳转的网页的信息秒存。也就是说，Samcompu并不需要在每一次跳转的时候花费时间去浏览网页。当然，这只局限于$N$个网站之间的$N-1$个跳转方式(保证每一个网站都可以跳转到另外的所有网站)。对于第$i$种跳转方式，第$u_i$个网站到第$v_i$个网站的跳转存在一个危险程度$w_i$，这个危险值可能会造成电脑卡死，如果Samcompu不能及时处理，那么就会**完美地**被老师发现。

值得一提的是，在被查水表很多次后，Samcompu总结出了一个规律：

老师走得越久，能够保证在被老师发现之前处理好电脑卡死的危险程度的上限就越高。简单来说，两者就是成正比的关系，比例系数为1。

可惜的是，Samcompu的黑科技并不稳定，在老师第$i$次离开的时候，第$K_i$个跳转方式就不可用了。

当然，每一次水都可以从任意一个网站开始，也可以从任意一个网站结束。

现在Samcompu想知道，对于第$i$次老师离开机房时，他能够有多少种不同的安全的水的方案。两种水的方案不同当且仅当这两种水的方案的第一个网站或者最后一个网站不同。

(补充说明: 一个安全的水的方案当且仅当当前是老师第$j$次离开教室时跳转的路径中不存在一个跳转方式$i$使得$tim_j \leqslant w_i$，每一次水完后不可用的跳转方式就会恢复。)

## 说明/提示

![](https://cdn.luogu.com.cn/upload/pic/25960.png)

第一次连接1和2的边不可用，当前能经过的边的危险程度需要<1，并没有合法的方案。

第二次连接1和3的边不可用，当前能经过的边的危险程度需要<2，合法的方案有  (1,2)    (2,1)    (3,4)    (4,3)  共四种。

第三次连接3和4的边不可用，当前能经过的边的危险程度需要<3，合法的方案有  (1,2)    (1,3)    (2,1)    (2,3)    (3,1)    (3,2)  共六种。

提醒:本题计算答案按照点对的方式计算.也就是说,如果起点和终点一样,则只看做同一种方案.特别的,$(x,y)$和$(y,x)\ (x \neq y)$算作两种不同的方案.

数据范围：

Subtask 1(30 pts):

$$ T=1 \qquad 1 \leqslant K_i \leqslant N \leqslant 10^3 \qquad 1 \leqslant tim_i, w_i \leqslant 10^3 $$

Subtask 2(50 pts):

$$ 1 \leqslant T \leqslant 5*10^3 \qquad 1 \leqslant K_i \leqslant N \leqslant 10^4 \qquad 1 \leqslant tim_i, w_i \leqslant 10^3 $$

Subtask 3(20 pts):

$$ 1 \leqslant T \leqslant 10^4 \qquad 1 \leqslant K_i \leqslant N \leqslant 10^4 \qquad 1 \leqslant tim_i, w_i \leqslant 10^3 $$

数据保证不同的$K_i$最多只有$10^3$个。

温馨提醒：由于出题人数据比较毒瘤，所以请尽量卡常。

## 样例 #1

### 输入

```
3 5
1 2 1
1 3 2
3 4 1
3 5 3
1 1
2 2
3 3
```

### 输出

```
0
4
6
```

# 题解

## 作者：CYJian (赞：3)

~~这道题就是一并查集板子题..~~

如果没有失效的跳转方式的话,我们可以直接把所有的跳转方式按照危险程度排个序,然后一个一个按照并查集的方式加边,方案数的话就直接每次拿要合并的联通块的size的乘积加上去就好了..至于答案,先离线按照时间排个序,在加边前如果危险程度大于时间就直接把当前的总方案数*2(因为A->B和B->A算两种答案)当成答案就好了.

加上失效的跳转方式怎么办呢??

出题人非常良心的强调了不同的$K_i$最多只有$10^3$个..

所以就可以把这些可能失效的跳转方式专门拿出来,处理一个询问时就先备份好之前的数组,然后暴力加上需要加上的边,记录答案后就直接恢复原数组就好了..

[代码](https://www.luogu.org/paste/4x9ua5nq)

---

## 作者：cjZYZtcl (赞：0)

给出一个 $O((n + T) \log{n})$ 的做法。

### Solution

首先考虑对于询问的限制离线之后扫描线。

考虑询问没有 $K_i$ 的限制时答案就是每个连通块的 $siz \times (siz - 1)$。

而 $K_i$ 限制影响的是一个连通块的贡献，且设断该边后连通块分成的两个连通块大小分别为 $siz1, siz2$，则贡献的减少量为 $2 \times siz1 \times siz2$。

那么问题转化成了加边，以及查询在某个连通块上断一条边后分裂出的两个连通块的大小（显然此处的连通块都是树）。

考虑对连上所有边的树钦定一个根，那么问题可以转化成查询一个点所在连通块大小以及该点子树内与该点连通的点的个数。

一个朴素的想法是在加边的时候维护，具体地，设加的边的两端点分别为 $x, y$，此处钦定 $dep_x < dep_y$，那么操作就是将 $x$ 所在连通块中 $y$ 的祖先的子树大小加上 $y$ 的子树大小。

先将操作差分一下，变成从根到某个点的修改，由于查询是单点查询，所以可以转化成单点修改，子树查询。

那么接下来就很好做了，扫描线加边的时候维护单点修改，查询的时候查询子树和，并查集 + 树状数组维护即可。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define pr pair<int, int>
#define mid (l + r) / 2
#define ls num << 1
#define rs num << 1 | 1
#define lowbit(x) (x & (-x))

const int N = 1e4 + 5;

vector<pr> upd[N], que[N];
vector<int> v[N];

int dfn[N], siz[N], sz[N], f[N], X[N], Y[N], W[N], dep[N], F[N], ans[N], tr[N];

int n, num = 0, now = 0;

inline int read() {
    int x = 0, mm = 1;
    char ch = getchar();

    while (!isdigit(ch)) {
        if (ch == '-') mm = -1;
        ch = getchar();
    }

    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }

    return x * mm;
}

inline void write(int x) {
    if (x < 0) {
        putchar('-');
        write(-x);
        return;
    }

    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

void add(int x, int k) {
    if (!x) return;
    for (int i = x; i <= n; i += lowbit(i)) {
        tr[i] += k;
    }
}

int query(int x) {
    int y = 0;
    for (int i = x; i; i -= lowbit(i)) {
        y += tr[i];
    }
    return y;
}

int query(int l, int r) {
    return query(r) - query(l - 1);
}

void dfs(int ro, int fa) {
    F[ro] = fa;
    dfn[ro] = ++num;
    siz[ro] = 1;
    dep[ro] = dep[fa] + 1;

    add(dfn[ro], 1);
    add(dfn[F[ro]], -1);

    for (auto u : v[ro]) {
        if (u == fa) continue;
        dfs(u, ro);
        siz[ro] += siz[u];
    }
}

int gf(int x) {
    return (x == f[x]) ? x : (f[x] = gf(f[x]));
}

void merge(int x, int y) {
    x = gf(x), y = gf(y);
    if (dep[x] > dep[y]) swap(x, y);
    add(dfn[F[x]], -sz[y]);
    add(dfn[F[y]], sz[y]);
    now -= sz[x] * (sz[x] - 1) + sz[y] * (sz[y] - 1);
    f[y] = x;
    sz[x] += sz[y];
    now += sz[x] * (sz[x] - 1);
}

int ask(int x) {
    return query(dfn[x], dfn[x] + siz[x] - 1);
}

signed main() {
    int q = read();
    n = read();

    for (int i = 1; i < n; i++) {
        int x = read(), y = read(), w = read();
        v[x].pb(y);
        v[y].pb(x);
        X[i] = x;
        Y[i] = y;
        W[i] = w;
    }

    for (int i = 1; i <= n; i++) f[i] = i, sz[i] = 1;

    dfs(1, 0);

    for (int i = 1; i < n; i++) {
        if (dep[X[i]] > dep[Y[i]]) swap(X[i], Y[i]);
        upd[W[i]].pb({X[i], Y[i]});
    }

    for (int i = 1; i <= q; i++) {
        int x = read(), y = read();
        que[x].pb({y, i});
    }

    for (int i = 1; i <= 1000; i++) {
        for (auto u : que[i]) {
            int x = u.first, id = u.second;
            ans[id] = now;
            if (W[x] < i) {
                int Siz = sz[gf(X[x])], Sz = ask(Y[x]);
                ans[id] -= 2 * Sz * (Siz - Sz);
            }
        }

        for (auto u : upd[i]) {
            int x = u.first, y = u.second;
            merge(x, y);
        }
    }

    for (int i = 1; i <= q; i++) {
        write(ans[i]);
        putchar('\n');
    }
}
```

---

