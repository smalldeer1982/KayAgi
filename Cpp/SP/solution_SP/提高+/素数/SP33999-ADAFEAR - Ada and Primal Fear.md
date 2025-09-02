# ADAFEAR - Ada and Primal Fear

## 题目描述

As you might already know, Ada the Ladybug is a farmer. She grows many vegetables. During past months, her crop was attacked by colony of parasites. Each vegetable was attacked by **A $ _{i} $**  parasites. Ada has only limited answer for this. She bought a few bottles with **Primal Fear**, which is a mixture agains parasites.

**Primal Fear** works in following way: Each **Primal Fear** bottle has a power assigned to it (which is coincidentally a prime number). If it is applied to a vegetable with  **N**  parasites on it, either the **N** is divisible by its **power**, then the size of colony is reduced to **N/power**, or - if the size is not divisible - then it has no effect. Also, as soon as you apply mixture against a colony, the rest of colony will become immune agains **Primal Fear**.

Ada didn't know what to buy so she bought one bottle of every possible **power**. Can you find out the best strategy to fight agains parasites?

# 题解

## 作者：鳶一折纸 (赞：2)

比较一眼的费用流。

- 源点向序列中的每个数连一条 $(1,0)$ 的边。
- 序列中的每个数向它们的所有质因数和 $1$ 连一条 $(1,a_i/p)$ 的边。
- 值域范围内的所有质数向汇点连一条 $(1,0)$ 的边。
- $1$ 向汇点连一条 $(n,0)$ 的边。

跑一遍费用流即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e3 + 10;
namespace MCMF
{
    const int MCN = 3010, MCE = 1e6 + 10;
    struct node
    {
        int u, v, w, c, nex;
    } e[MCE];
    int cnt = 1, cost;
    int dis[MCN], vis[MCN], ly[MCN], cur[MCN];
    void addedge(int u, int v, int w, int c)
    {
        e[++cnt] = {u, v, w, c, ly[u]};
        ly[u] = cnt;
    }
    void add(int u, int v, int w, int c) { addedge(u, v, w, c), addedge(v, u, 0, -c); }
    bool spfa(int s, int t)
    {
        memset(dis, 127, sizeof(dis));
        memcpy(cur, ly, sizeof(ly));
        int minn = dis[s];
        vis[s] = 1, dis[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size())
        {
            int now = q.front();
            q.pop();
            vis[now] = 0;
            for (int i = ly[now]; i; i = e[i].nex)
            {
                int to = e[i].v;
                if (e[i].w && dis[to] > dis[now] + e[i].c)
                {
                    dis[to] = dis[now] + e[i].c;
                    if (!vis[to])
                        q.push(to), vis[to] = 1;
                }
            }
        }
        return dis[t] != minn;
    }
    int dinic(int now, int t, int flow)
    {
        if (now == t)
            return flow;
        vis[now] = 1;
        int maxn = 0;
        for (int &i = cur[now]; i && maxn < flow; i = e[i].nex)
        {
            int v = e[i].v;
            if (!vis[v] && e[i].w && dis[v] == dis[now] + e[i].c)
            {
                int res = dinic(v, t, min(e[i].w, flow - maxn));
                if (res)
                    cost += res * e[i].c, e[i].w -= res, e[i ^ 1].w += res, maxn += res;
            }
        }
        vis[now] = 0;
        return maxn;
    }
    int mcmf(int s, int t)
    {
        int res = 0;
        while (spfa(s, t))
        {
            int x = dinic(s, t, 1e9);
            while (x)
                res += x, x = dinic(s, t, 1e9);
        }
        return res;
    }
}
using namespace MCMF;
namespace prime
{
    bool visp[N];
    int p[N >> 2];
    void eulur(int n)
    {
        for (int i = 2; i <= n; ++i)
        {
            if (!visp[i])
                p[++p[0]] = i;
            for (int j = 1; j <= p[0] && i * p[j] <= n; ++j)
            {
                visp[i * p[j]] = 1;
                if (i % p[j] == 0)
                    break;
            }
        }
    }
}
using namespace prime;
int n, S, T;
signed main()
{
    ios::sync_with_stdio(0);
    cin >> n, eulur(2000), S = p[0] + n + 2, T = S + 1;
    for (int i = 1; i <= p[0]; ++i)
        add(i + n + 1, T, 1, 0);
    add(n + 1, T, n, 0);
    for (int i = 1, a; i <= n; ++i)
    {
        cin >> a;
        for (int j = 1; j <= p[0]; ++j)
        {
            if (a % p[j])
                continue;
            add(i, n + j + 1, 1, a / p[j]);
        }
        add(S, i, 1, 0), add(i, n + 1, 1, a);
    }
    (void)mcmf(S, T);
    cout << cost << endl;
    return 0;
}
```

---

