# 题目信息

# [ARC061E] すぬけ君の地下鉄旅行

## 题目描述

Snuke的城镇有地铁行驶，地铁线路图包括 $N$ 个站点和 $M$ 个地铁线。站点被从 $1$ 到 $N$ 的整数所标记，每条线路被一个公司所拥有，并且每个公司用彼此不同的整数来表示。

第 $i$ 条线路( $1≤i≤M$ )是直接连接 $p_i$ 与 $q_i$ 的双向铁路，中间不存在其他站点，且这条铁路由 $c_i$ 公司所拥有。

如果乘客只乘坐同一公司的铁路，他只需要花费一元，但如果更换其他公司的铁路需要再花一元。当然，如果你要再换回原来的公司，你还是要花一元。

Snuke在1号站的位置出发，他想通过地铁去第 $N$ 站，请求出最小钱数。如果无法到达第 $N$ 站，输出-1。

## 样例 #1

### 输入

```
3 3

1 2 1

2 3 1

3 1 2```

### 输出

```
1```

## 样例 #2

### 输入

```
8 11

1 3 1

1 4 2

2 3 1

2 5 1

3 4 3

3 6 3

3 7 3

4 8 4

5 6 1

6 7 5

7 8 5```

### 输出

```
2```

## 样例 #3

### 输入

```
2 0```

### 输出

```
-1```

# AI分析结果

### 题目中文重写
# [ARC061E] すぬけ君の地下鉄旅行

## 题目描述

Snuke所在的城镇有地铁运行，地铁线路图包含 $N$ 个站点和 $M$ 条地铁线。站点用从 $1$ 到 $N$ 的整数编号，每条线路由一家公司运营，每家公司用不同的整数表示。

第 $i$ 条线路（$1\leq i\leq M$）是直接连接 $p_i$ 和 $q_i$ 的双向铁路，中间没有其他站点，且该线路由 $c_i$ 公司运营。

如果乘客只乘坐同一家公司的铁路，只需花费 1 元；但如果换乘到其他公司的铁路，则需再花费 1 元。当然，如果再换回原来的公司，仍需花费 1 元。

Snuke 从 1 号站出发，想乘坐地铁前往第 $N$ 站，请求出最小花费。如果无法到达第 $N$ 站，输出 -1。

## 样例 #1

### 输入
```
3 3
1 2 1
2 3 1
3 1 2
```

### 输出
```
1
```

## 样例 #2

### 输入
```
8 11
1 3 1
1 4 2
2 3 1
2 5 1
3 4 3
3 6 3
3 7 3
4 8 4
5 6 1
6 7 5
7 8 5
```

### 输出
```
2
```

## 样例 #3

### 输入
```
2 0
```

### 输出
```
-1
```

### 综合分析与结论
这些题解的核心思路大多围绕建图和最短路算法展开，以解决换乘费用的问题。主要难点在于处理同一公司线路的连通块以及不同公司线路换乘的费用计算，为避免边数过多导致空间和时间复杂度爆炸，多数题解采用了建虚点的优化方法。

### 所选题解
- **封禁用户（5星）**
    - **关键亮点**：思路清晰，详细阐述了建图优化的过程，通过建立虚点将边数从 $\frac{n(n - 1)}{2}$ 优化到不超过 $2m$，并给出了具体的建图和求解流程，代码实现思路明确。
    - **核心代码**：
```cpp
// 建图部分
for (int i = 1; i <= m; i++) {
    int a, b, c;
    a = read(); b = read(); c = read();
    G[c].push_back(make_pair(a, b));
}
int cnt = n;
for (int i = 1; i <= N; i++) {
    if (G[i].empty()) continue;
    for (int j = 0; j < G[i].size(); j++) {
        init(G[i][j].first);
        init(G[i][j].second);
    }
    for (int j = 0; j < G[i].size(); j++) merge(G[i][j].first, G[i][j].second);
    for (int j = 0; j < G[i].size(); j++) {
        if (!use[G[i][j].first]) {
            use[G[i][j].first] = true;
            int X = find(G[i][j].first);
            if (id[X] == -1) id[X] = ++cnt;
            newg[G[i][j].first].push_back(id[X]);
            newg[id[X]].push_back(G[i][j].first);
        }
        if (!use[G[i][j].second]) {
            use[G[i][j].second] = true;
            int X = find(G[i][j].second);
            if (id[X] == -1) id[X] = ++cnt;
            newg[G[i][j].second].push_back(id[X]);
            newg[id[X]].push_back(G[i][j].second);
        }
    }
}
// 最短路部分
q.push(1);
memset(dp, -1, sizeof(dp));
dp[1] = 0;
while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int i = 0; i < newg[v].size(); i++) {
        int to = newg[v][i];
        if (dp[to] == -1) {
            dp[to] = dp[v] + 1;
            q.push(to);
        }
    }
}
```
    - **核心实现思想**：先将每条边按公司存储，然后用并查集维护每个公司线路的连通块，为每个连通块建立虚点，将连通块内的点与虚点相连。最后使用 BFS 求解最短路。

- **__Hacheylight__（4星）**
    - **关键亮点**：提供了多种解法，包括并查集 + BFS、不用并查集的 BFS 以及 Dijkstra 算法，代码实现详细，且对每种解法都有一定的解释。
    - **核心代码（并查集 + BFS）**：
```cpp
// 建图部分
n = read(); m = read();
for (int i = 1; i <= m; i++) {
    int a, b, c;
    a = read(); b = read(); c = read();
    G[c].push_back(make_pair(a, b));
}
int cnt = n;
for (int i = 1; i <= N; i++) {
    if (G[i].empty()) continue;
    for (int j = 0; j < G[i].size(); j++) {
        init(G[i][j].first);
        init(G[i][j].second);
    }
    for (int j = 0; j < G[i].size(); j++) merge(G[i][j].first, G[i][j].second);
    for (int j = 0; j < G[i].size(); j++) {
        if (!use[G[i][j].first]) {
            use[G[i][j].first] = true;
            int X = find(G[i][j].first);
            if (id[X] == -1) id[X] = ++cnt;
            newg[G[i][j].first].push_back(id[X]);
            newg[id[X]].push_back(G[i][j].first);
        }
        if (!use[G[i][j].second]) {
            use[G[i][j].second] = true;
            int X = find(G[i][j].second);
            if (id[X] == -1) id[X] = ++cnt;
            newg[G[i][j].second].push_back(id[X]);
            newg[id[X]].push_back(G[i][j].second);
        }
    }
}
// 最短路部分
q.push(1);
memset(dp, -1, sizeof(dp));
dp[1] = 0;
while (!q.empty()) {
    int v = q.front(); q.pop();
    for (int i = 0; i < newg[v].size(); i++) {
        int to = newg[v][i];
        if (dp[to] == -1) {
            dp[to] = dp[v] + 1;
            q.push(to);
        }
    }
}
```
    - **核心实现思想**：与封禁用户的思路类似，先按公司存储边，用并查集维护连通块，建立虚点建图，最后用 BFS 求最短路。

- **igAC（4星）**
    - **关键亮点**：提出了两种不同的拆点思路，一种是将每个点拆成与每个公司的铁路相连的点，另一种是在最短路转移时考虑更多情况，对问题的分析较为深入。
    - **核心代码（拆点 + BFS）**：
```cpp
// 建图部分
n = read(), m = read();
for (int i = 1; i <= m; ++i) {
    int x = read(), y = read(), z = read();
    mp[x][z].push_back(y);
    mp[y][z].push_back(x);
    col[x].push_back(z);
    col[y].push_back(z);
}
for (int i = 1; i <= n; ++i) col[i].push_back(0);
for (int i = 1; i <= n; ++i) {
    sort(col[i].begin(), col[i].end());
    col[i].erase(unique(col[i].begin(), col[i].end()), col[i].end());
    for (int x : col[i]) {
        p[i].push_back(++tot);
        bel[i][x] = tot;
    }
}
for (int i = 1; i <= n; ++i) {
    for (int j = 1; j < col[i].size(); ++j) {
        add_edge(p[i][j], p[i][0], 0);
        add_edge(p[i][0], p[i][j], 1);
        for (int x : mp[i][col[i][j]]) add_edge(p[i][j], bel[x][col[i][j]], 0);
    }
}
// 最短路部分
BFS(p[1][0]);
```
    - **核心实现思想**：将每个点拆成与不同公司铁路相连的点，为每个点建立一个 0 号节点处理转线问题，建图后使用 BFS 求解最短路。

### 最优关键思路或技巧
- **建虚点优化建图**：通过建立虚点，将原本复杂的边连接关系简化，减少边的数量，降低空间和时间复杂度。
- **拆点思想**：将每个点拆分成与不同公司线路相连的点，方便处理换乘费用。
- **并查集维护连通块**：使用并查集可以高效地维护同一公司线路的连通块。

### 可拓展之处
同类型题如分层图最短路问题，通常会在图中加入额外的条件，如不同层之间的转移代价等。类似算法套路包括拆点、建虚点、分层图等，可用于解决一些具有特殊条件的图论问题。

### 推荐题目
- [P4568 [JLOI2011] 飞行路线](https://www.luogu.com.cn/problem/P4568)：分层图最短路问题，可使用拆点和最短路算法解决。
- [P2939 [USACO09FEB] Revamping Trails G](https://www.luogu.com.cn/problem/P2939)：同样是分层图最短路，有一定的难度。
- [P6822 [PA2012] Tax](https://www.luogu.com.cn/problem/P6822)：涉及边权和点权的转换，可使用建虚点和最短路算法求解。

### 个人心得摘录与总结
- **cjh20090318**：多测时要注意清空数组，用多少清空多少，否则会超时。总结：在处理多组数据时，要合理清空数组，避免不必要的时间开销。
- **CoderCharlie**：考虑问题要全面，一个地铁公司运营的所有线路可能不止在一个联通块内，需要用并查集维护。总结：在分析问题时，要考虑到各种可能的情况，避免算法出现漏洞。 

---
处理用时：65.71秒