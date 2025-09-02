# PT07C - The GbAaY Kingdom

## 题目描述

给定一个 $n$ 个点 $m$ 条边的带权无向图.

现求一生成树,使得任意两结点间最长距离(直径)最短.

## 样例 #1

### 输入

```
3 3
1 2 1
2 3 1
1 3 1```

### 输出

```
2
1 2
1 3```

# 题解

## 作者：james1BadCreeper (赞：1)

我们先介绍[图的绝对中心](https://www.luogu.com.cn/problem/CF266D)。无向图的绝对中心位于图的边上或者节点上，满足该中心到所有点的最短距离的最大值最小。此时对应的最短距离最大值叫做直径。

那么使用 Floyd 算法，绝对中心在点上是好计算的，对于在边 $(u,v,w)$ 上的情况，到点 $i$ 的距离为 $\min\{d_{u,i}+x,d_{v,i}+w-x\}$：

![](https://pic.imgdb.cn/item/65f1a3749f345e8d031ac8a9.png)

因此我们对于一条边 $(u,v,w)$，按照纵坐标枚举 $i$，然后如果最上面那个东西会产生交点的话，就更新最上面那个东西就可以了，此时用 $\dfrac{d_{u,i}+x+d_{v,p}+(w-x)}{2}$ 更新答案。[代码](https://codeforces.com/contest/266/submission/251170029)。

---

对于[最小直径生成树](https://codeforces.com/gym/102391/problem/I)，求出图的绝对中心之后，再求出最短路树即可（注意初始距离），注意对于绝对中心在点上的特判。

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long i64; 
const int N = 505; 

int n, m; 
int u[N * N], v[N * N]; 
int rk[N][N], is[N][N]; 
i64 d[N][N], g[N][N], w[N * N], dis[N]; 
bool vis[N]; 

int main(void) {
    ios::sync_with_stdio(0); 
    cin >> n >> m; memset(d, 0x3f, sizeof d); memset(g, 0x3f, sizeof g); 
    for (int i = 1; i <= n; ++i) d[i][i] = g[i][i] = 0; 
    for (int i = 1; i <= m; ++i) {
        cin >> u[i] >> v[i] >> w[i]; is[u[i]][v[i]] = is[v[i]][u[i]] = 1; 
        w[i] *= 2; 
        d[u[i]][v[i]] = d[v[i]][u[i]] = min(d[u[i]][v[i]], w[i]); 
        g[u[i]][v[i]] = g[v[i]][u[i]] = min(g[u[i]][v[i]], w[i]); 
    }
    for (int k = 1; k <= n; ++k) for (int i = 1; i <= n; ++i) for (int j = 1; j <= n; ++j) d[i][j] = min(d[i][j], d[i][k] + d[k][j]); 
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) rk[i][j] = j; 
        sort(rk[i] + 1, rk[i] + n + 1, [i](int x, int y) { return d[i][x] < d[i][y]; }); 
    }
    int x, y; i64 ans = 1e18, wx = 0; 
    for (int i = 1; i <= n; ++i)
        if (d[i][rk[i][n]] * 2 < ans) ans = d[i][rk[i][n]] * 2, x = y = i; 
    for (int i = 1; i <= m; ++i) {
        int u = ::u[i], v = ::v[i], w = ::w[i]; 
        for (int p = n, i = n - 1; i >= 1; --i)
            if (d[v][rk[u][i]] > d[v][rk[u][p]]) {
                i64 val = d[u][rk[u][i]] + w + d[v][rk[u][p]]; 
                if (val < ans) ans = val, x = u, y = v, wx = (d[v][rk[u][p]] - d[u][rk[u][i]] + w) / 2; 
                p = i; 
            }
    }
    cout << ans / 2 << "\n"; 

    memset(dis, 0x3f, sizeof dis); i64 INF = dis[0]; 
    #define pli pair<i64, int> 
    priority_queue<pli, vector<pli>, greater<pli>> q; 
    q.emplace(dis[x] = wx, x); q.emplace(dis[y] = g[x][y] - wx, y); 
    
    while (!q.empty()) {
        int u = q.top().second; q.pop(); 
        if (vis[u]) continue; vis[u] = 1; 
        for (int v = 1; v <= n; ++v) if (v != u) 
            if (dis[v] > dis[u] + g[u][v]) q.emplace(dis[v] = dis[u] + g[u][v], v); 
    }
    // for (int i = 1; i <= n; ++i) cout << dis[i] << " \n"[i == n]; 

    if (x != y) cout << x << " " << y << "\n"; 
    for (int i = 1; i <= n; ++i) if (i != x && i != y)
        for (int j = 1; j <= n; ++j) if (i != j && dis[i] == dis[j] + g[i][j]) {
            if (i < j) cout << i << " " << j << "\n"; 
            else cout << j << " " << i << "\n"; 
            break; 
        }
    return 0;
}
```

---

