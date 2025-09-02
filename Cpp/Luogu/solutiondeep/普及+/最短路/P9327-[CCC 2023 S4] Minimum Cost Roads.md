# 题目信息

# [CCC 2023 S4] Minimum Cost Roads

## 题目描述

As the newly elected mayor of Kitchener, Alanna's first job is to improve the city's road plan.

Kitchener's current road plan can be represented as a collection of $N$ intersections with $M$ roads, where the $i\text{-th}$ road has length $l_i$ meters, costs $c_i$ dollars per year to maintain, and connects intersections $u_i$ and $v_i$. To create a plan, Alanna must select some subset of the $M$ roads to keep and maintain, and that plan's cost is the sum of maintenance costs of all roads in that subset.

To lower the city's annual spending, Alanna would like to minimize the plan's cost. However, the city also requires that she minimizes travel distances between intersections and will reject any plan that does not conform to those rules. Formally, for any pair of intersections $(i, j)$, if there exists a path from $i$ to $j$ taking $l$ meters on the existing road plan, Alanna's plan must also include a path between those intersections that is at most $l$ meters.

## 说明/提示

Explanation of Output for Sample Input：

Here is a diagram of the intersections along with a valid road plan with minimum cost.

![](https://cdn.luogu.com.cn/upload/image_hosting/2astpvkm.png)

Each edge is labeled with a pair $(l, c)$ denoting that it has length $l$ meters and cost $c$ dollars.

Additionally, the roads that are part of the plan are highlighted in blue, with a total cost of $7 + 1 + 6 + 7 + 4 = 25$.

It can be shown that we cannot create a cheaper plan that also respects the city’s requirements.

**本题采用捆绑测试**：

- Subtask 1（3 points）：数据保证 $1\leq N \leq 2000$，$1\leq M \leq 2000$，$l_i = 0$，$1\leq c_i \leq 10^9$。

- Subtask 2（6 points）：数据保证 $1\leq N\leq 2000$，$1\leq M \leq 2000$，$1\leq l_i \leq 10^9$，$1\leq c_i \leq 10^9$，且在任何一对十字路口之间最多只有一条路。

- Subtask 3（6 points）：数据保证 $1\leq N\leq 2000$，$1\leq M \leq 2000$，$0\leq l_i \leq 10^9$，$1\leq c_i \leq 10^9$。

## 样例 #1

### 输入

```
5 7
1 2 15 1
2 4 9 9
5 2 5 6
4 5 4 4
4 3 3 7
1 3 2 7
1 4 2 1```

### 输出

```
25```

# AI分析结果

### 综合分析与结论
这些题解的核心思路都是围绕在满足任意两点间最短路不变的前提下，选取维护代价最小的边集。主要借助排序、并查集和最短路算法（如 Dijkstra）来实现。
- **思路**：先将边按长度为第一关键字、维护代价为第二关键字升序排序，再遍历边，利用并查集判断两点连通性，若不连通则加入边；若连通，通过最短路算法判断加入该边是否能缩短两点间最短路，若能则加入。
- **算法要点**：排序确保优先处理长度短、代价小的边；并查集快速判断连通性；最短路算法判断是否需加入新边。
- **解决难点**：处理重边和判断边是否必要加入，保证最短路不变的同时使维护代价最小。

### 所选题解
- **作者：wgyhm (赞：9)，4星**
    - **关键亮点**：思路清晰，代码注释详细，对算法复杂度有分析。
- **作者：船酱魔王 (赞：3)，4星**
    - **关键亮点**：对算法正确性有详细证明，代码结构清晰。
- **作者：BeTheNorthStar (赞：1)，4星**
    - **关键亮点**：明确指出题目核心要求，提供 SPFA 和 Dijkstra 两种最短路算法实现。

### 重点代码
#### wgyhm 题解核心代码
```cpp
bool check(int s, int t, int d) {
    int i, x;
    for (i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    while (!q.empty()) q.pop();
    q.push(mk(-(dis[s] = 0), s));
    while (!q.empty()) {
        int x = q.top().se; q.pop();
        if (vis[x]) continue; vis[x] = 1;
        for (auto tmp : to[x]) if (!vis[tmp.fi] && dis[tmp.fi] > dis[x] + tmp.se) {
            dis[tmp.fi] = dis[x] + tmp.se;
            q.push(mk(-dis[tmp.fi], tmp.fi));
        }
    }
    return d < dis[t];
}

signed main(void) {
    int i;
    read(n); read(m);
    for (i = 1; i <= m; i++) {
        read(a[i].x), read(a[i].y), read(a[i].l), read(a[i].c);
    }
    for (i = 1; i <= n; i++) fa[i] = i;
    sort(a + 1, a + 1 + m, cmp);
    for (i = 1; i <= m; i++) {
        auto tmp = a[i];
        if (getfa(tmp.x) ^ getfa(tmp.y)) {
            fa[getfa(tmp.x)] = getfa(tmp.y);
            ans += tmp.c;
            to[a[i].x].push_back(mk(a[i].y, a[i].l));
            to[a[i].y].push_back(mk(a[i].x, a[i].l));
        }
        else if (check(tmp.x, tmp.y, tmp.l)) {
            ans += tmp.c;
            to[a[i].x].push_back(mk(a[i].y, a[i].l));
            to[a[i].y].push_back(mk(a[i].x, a[i].l));
        }
    }
    printf("%lld\n", ans);
    return 0;
}
```
**核心实现思想**：`check` 函数用 Dijkstra 算法求两点间最短路，判断当前边长度是否小于已有最短路。主函数中先读入数据，对边排序，再遍历边，根据连通性和最短路判断是否加入边。

#### 船酱魔王题解核心代码
```cpp
int length(int x, int y) {
    for (int i = 1; i <= n; i++) dis[i] = inf, vis[i] = 0;
    dis[x] = 0;
    pq.push((pair<int, int>){0, x});
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        if (vis[u]) continue;
        int v;
        for (int i = 0; i < g[u].size(); i++) {
            v = g[u][i].first;
            int w = g[u][i].second;
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push((pair<int, int>){-dis[v], v});
            }
        }
    }
    return dis[y];
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> a[i].u >> a[i].v >> a[i].l >> a[i].p;
    }
    sort(a + 1, a + m + 1);
    int u, v, l, p;
    long long ans = 0;
    for (int i = 1; i <= m; i++) {
        u = a[i].u, v = a[i].v, l = a[i].l, p = a[i].p;
        if (length(u, v) > l) ans += p, g[u].push_back((pair<int, int>){v, l}),
            g[v].push_back((pair<int, int>){u, l});
    }
    cout << ans << endl;
    return 0;
}
```
**核心实现思想**：`length` 函数用 Dijkstra 算法求两点间最短路。主函数读入数据，对边排序，遍历边，若当前边长度小于已有最短路则加入边并累加代价。

#### BeTheNorthStar 题解核心代码
```cpp
bool DIJ_HEAP(int sx, int sy, int Road) {
    memset(dis, 127, sizeof dis); memset(vis, 0, sizeof vis);
    hep_size = 0, put(dis[sx] = 0, sx);
    while (hep_size) {
        BNS now = get();
        if (vis[now.id]) continue; if (now.id == sy) break;
        vis[now.id] = 1;
        for (int j = lnk[now.id]; j; j = e[j].nxt)
            if (dis[now.id] + e[j].w < dis[e[j].to]) put(dis[e[j].to] = dis[now.id] + e[j].w, e[j].to);
    }
    return Road < dis[sy];
}

signed main() {
    n = read(), m = read();
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= m; i++) a[i] = (EDGE){read(), read(), read(), read()};
    sort(a + 1, a + 1 + m);
    for (int i = 1; i <= m; i++) {
        int fx = Get(a[i].x), fy = Get(a[i].y);
        if (fx != fy) fa[fx] = fy, ans += a[i].c, add_e(a[i].x, a[i].y, a[i].l), add_e(a[i].y, a[i].x, a[i].l); else
            if (DIJ_HEAP(a[i].x, a[i].y, a[i].l)) ans += a[i].c, add_e(a[i].x, a[i].y, a[i].l), add_e(a[i].y, a[i].x, a[i].l);
    }
    printf("%lld\n", ans);
    return 0;
}
```
**核心实现思想**：`DIJ_HEAP` 函数用堆优化的 Dijkstra 算法求两点间最短路。主函数读入数据，对边排序，遍历边，根据连通性和最短路判断是否加入边。

### 最优关键思路或技巧
- **排序策略**：按长度为第一关键字、维护代价为第二关键字升序排序，确保优先处理长度短、代价小的边。
- **并查集**：快速判断两点是否连通，减少不必要的最短路计算。
- **最短路算法**：用 Dijkstra 算法判断加入新边是否能缩短两点间最短路。

### 可拓展之处
同类型题或类似算法套路：
- 最小生成树的变种问题，如边有多种属性，需在满足某些条件下求最小代价。
- 图的删边问题，要求删去部分边后图的某些性质（如连通性、最短路）不变。

### 推荐题目
- P1195 口袋的天空：最小生成树问题，求最小代价的连通块。
- P3366 【模板】最小生成树：经典最小生成树模板题。
- P2872 [USACO07DEC]Building Roads S：最小生成树问题，需先计算边权。

### 个人心得
这些题解中未包含个人心得（调试经历、踩坑教训、顿悟感想等）。 

---
处理用时：48.26秒