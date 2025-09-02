# The Doctor Meets Vader (Hard)

## 题目描述

叛军已经积攒了足够的黄金，准备发动全面进攻。现在局势逆转，叛军将派遣飞船攻击帝国基地！

银河系可以表示为一个无向图，包含 $n$ 个行星（节点）和 $m$ 个虫洞（边），每条边连接两个行星。

共有 $s$ 艘叛军飞船和 $b$ 个帝国基地，分别位于银河系中的不同行星上。

每艘飞船有一个位置 $x$，表示其所在行星的编号，攻击力 $a$，一定量的燃料 $f$，以及操作费用 $p$。

每个基地有一个位置 $x$，防御力 $d$，以及一定数量的黄金 $g$。

如果同时满足以下两个条件，飞船可以攻击基地：

- 飞船的攻击力大于等于基地的防御力；
- 飞船的燃料大于等于飞船所在节点与基地所在节点之间的最短距离（以虫洞数计）。

叛军战士非常自豪。如果一艘飞船无法攻击任何基地，则没有叛军飞行员愿意操作它。

如果一艘飞船被操作，其产生的利润等于其攻击的基地的黄金数量减去操作该飞船的费用。注意，这个值可能为负数。被操作的飞船会选择攻击能使其利润最大的基地。

达斯·维达总是喜欢表现得很富有。因此，每当一个基地被攻击并且黄金被劫走时，他会立即为该基地补充黄金。

因此，对于叛军来说，多艘飞船可以攻击同一个基地，每艘飞船都能获得该基地的全部黄金。

叛军委托 Heidi 和 Doctor 决定应操作哪些飞船，以使总利润最大。

然而，战争持续已久，飞行员们之间建立了牢不可破的友谊，有些飞行员如果朋友不操作飞船，他们也拒绝操作。

他们有 $k$ 条依赖关系，每条为 $s_1, s_2$，表示只有在飞船 $s_2$ 也被操作时，飞船 $s_1$ 才能被操作。

## 说明/提示

最优策略是操作第 1、2、4 号飞船，分别攻击第 1、1、2 号基地。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
6 7
1 2
2 3
3 4
4 6
6 5
4 4
3 6
4 2 2
1 10 2 5
3 8 2 7
5 1 0 2
6 5 4 1
3 7 6
5 2 3
4 2
3 2
```

### 输出

```
2
```

# 题解

## 作者：stntn (赞：1)

没有题解，水~~最后~~一发

首先考虑没有 $k$ 个限制怎么做，显然直接贪心即可，跑个全源点最短路，对于每个船求出最大收益，**如果船不可能运行收益为 $-\infty$**。

现在有限制了，如果要选 $A$ 必须选 $B$，其实就是最大权闭合子图，注意到 $10^5$ 跑网络流不是很现实，但是限制只有 $k$ 个，所以把有限制的挑出来做就行了。

补一个最大权闭合子图做法：

考虑最小割，假设正权点全选，负权点全不选，算出当前的答案，这样显然是不行的，所以建图：对于正权点 $s \to u:cost_u$，负权点 $u \to t:|cost_u|$，其余边照旧边权 $+\infty$。割掉正权的入边表示撤销选择，割掉负权出边表示选择，如果正权点没被割其后继负权一定被割，后继正权不必被割；负权同理。

最后答案减去最小割即可。

代码太丑了，不放了。

---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

一张图有 $n$ 个点 $m$ 条边，边权都是 $1$。

有 $s$ 个宇宙飞船，第 $i$ 个宇宙飞船在 $x_i$ 的位置，有 $a_i$ 的攻击 $f_i$ 的燃料 $p_i$ 的运行代价。

有 $b$ 个基地，第 $j$ 个基地在 $x'_j$ 的位置，有 $d_j$ 的防御和 $g_j$ 的价值。

有 $k$ 条限制，表示如果发动了宇宙飞船 $u$ 则必须发动宇宙飞船 $v$。

一个飞船 $i$ 能攻打到基地 $j$ 需要满足：

- $\operatorname{dis}(i,j)\leq f_i$
- $a_i\geq d_j$

一次宇宙飞船 $i$ 攻打基地 $j$ 的收益为 $g_j-p_i$。

一个基地可以被多次攻打，并且价值不变。

选择若干个飞船并且分别选择攻打的基地，在满足限制的情况下最大化收益之和。**如果一个飞船不能攻打任何基地，那么你不可以选择这个飞船。**

$1\leq n\leq 100$，$0\leq m\leq 1000$，$1\leq s,b\leq 10^5$，$1\leq k\leq 1000$，$1\leq x_i,x'_j,u,v\leq n$，$1\leq a_i,f_i,p_i,d_j,g_j\leq 10^9$。

# 题目思路

最短路可以直接 Floyd 与处理掉。

然后考虑求一个宇宙飞船带来的最大收益。由于点数很少，我们把宇宙飞船和基地标在点上。枚举飞船，枚举点，这里点是原图的点实际只有 $n$ 个，然后点内基地我们可以提前预处理按 $d$ 排序，预处理前缀 $\max$，然后二分找到这个宇宙飞船能打到的最大价值的基地。

打不到任何基地就设为 $-\infty$。

然后我们就是做这样一个问题：选一个点集，点有点权，最大化点权和，但是要求一个点能选择的前提是若干个点也被选择。

这类问题叫做『最大权闭合子图』。建图之后，一个点选择的要求是这个点的后继也全部被选择。

处理这类问题，我们可以转化成最小割。

对于一条限制 $(u,v)$ 表示 $u$ 选择了 $v$ 也必须选择。我们连一条 $u\xrightarrow{+\infty} v$。

之后，对于 $val_u\geq 0$ 的点，我们连 $S\xrightarrow{val_u} u$。对于 $val_v\lt 0$ 的点，我们连 $v\xrightarrow{-val_v} T$。

最后在这张图上求解 $S\to T$ 的最小割。

刻画一下这个的实际意义。首先 $u\to v$ 的边都不会被割掉。而留 $S\to u$ 对应的就是选择这个点（以及他的若干后继），割 $v\to T$ 对应的也是选择这个点（以及他的若干前驱）。

最后这张图的最小割是我们不应该选择的 $val_u$ 之和加上应该选择的 $val_v$ 的相反数的和。

最后答案为 $(\sum\limits_{val_i\geq 0}val_i)-\operatorname{mincut}$。也就是我们初始选上了所有非负权，扔掉我们不选的非负权，减去我们选择了的负权的相反数（把负权点加回来）。

# 完整代码

<https://codeforces.com/contest/1184/submission/306629094>

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
typedef long long ll;
template <typename T>
void chkmn(T &x, T y) { x = min(x, y); }
template <typename T>
void chkmx(T &x, T y) { x = max(x, y); }
const ll inf = 1e18;
int n, m;
int S, B;
int d[105][105];
struct spaceship
{
    int a, f, p, id;
};
vector<spaceship> sv[105];
struct base
{
    int d, g;
};
vector<base> bv[105];
vector<int> pre[105];
ll val[100020];
int s, t;
int tot;
struct edge
{
    int v;
    ll w;
    int inv;
};
vector<edge> a[2020];
int dis[2020];
int cur[2020];
ll min_cut;
void add(int u, int v, ll w)
{
    int Su = a[u].size(), Sv = a[v].size();
    a[u].push_back({v, w, Sv});
    a[v].push_back({u, 0, Su});
}
bool bfs(int s, int t)
{
    memset(dis, -1, sizeof(dis));
    memset(cur, 0, sizeof(cur));
    queue<int> q;
    q.push(s);
    dis[s] = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto [v, w, j] : a[u])
        {
            if (dis[v] < 0 && w > 0)
            {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
        }
    }
    return ~dis[t];
}
ll dfs(int u, int t, ll flow)
{
    if (u == t)
        return flow;
    for (int i = cur[u]; i < a[u].size(); i++)
    {
        auto [v, w, j] = a[u][cur[u] = i];
        if (dis[v] == dis[u] + 1 && w > 0)
        {
            ll tmp = dfs(v, t, min(w, flow));
            if (tmp)
                return a[u][i].w -= tmp, a[v][j].w += tmp, tmp;
            dis[v] = -1;
        }
    }
    return 0;
}
void dinic()
{
    ll flow = 0;
    while (bfs(s, t))
        while (flow = dfs(s, t, inf))
            min_cut += flow;
}
int id[100020];
int F(int u)
{
    if (!id[u])
    {
        id[u] = ++tot;
        if (val[u] >= 0)
            add(s, id[u], val[u]);
        else
            add(id[u], t, -val[u]);
    }
    return id[u];
}
int main()
{
    read(n, m);
    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= n; i++)
        d[i][i] = 0;
    while (m--)
    {
        int u, v;
        read(u, v);
        d[u][v] = d[v][u] = 1;
    }
    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
                chkmn(d[i][j], d[i][k] + d[k][j]);
        }
    }
    read(S, B, m);
    for (int i = 1; i <= S; i++)
    {
        int x, a, f, p;
        read(x, a, f, p);
        sv[x].push_back({a, f, p, i});
    }
    for (int i = 1; i <= B; i++)
    {
        int x, d, g;
        read(x, d, g);
        bv[x].push_back({d, g});
    }
    for (int i = 1; i <= n; i++)
    {
        sort(bv[i].begin(), bv[i].end(), [&](base a, base b)
             { return a.d < b.d; });
        pre[i].resize(bv[i].size());
        for (int j = 0; j < bv[i].size(); j++)
        {
            pre[i][j] = -1;
            if (j)
                pre[i][j] = pre[i][j - 1];
            chkmx(pre[i][j], bv[i][j].g);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        for (auto [a, f, p, id] : sv[i])
        {
            val[id] = -inf;
            for (int j = 1; j <= n; j++)
            {
                if (d[i][j] > f)
                    continue;
                int pos = partition_point(bv[j].begin(), bv[j].end(),
                                          [&](base x)
                                          { return x.d <= a; }) -
                          bv[j].begin() - 1;
                if (pos == -1)
                    continue;
                if (pos >= 0)
                    chkmx(val[id], (ll)pre[j][pos] - p);
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i <= S; i++)
    {
        if (val[i] >= 0)
            ans += val[i];
    }
    s = ++tot, t = ++tot;
    while (m--)
    {
        int u, v;
        read(u, v);
        add(F(u), F(v), inf);
    }
    dinic();
    cout << ans - min_cut << '\n';
    return 0;
}
```

---

