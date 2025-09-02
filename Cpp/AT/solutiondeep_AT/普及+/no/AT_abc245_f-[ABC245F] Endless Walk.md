# 题目信息

# [ABC245F] Endless Walk

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc245/tasks/abc245_f

$ N $ 頂点 $ M $ 辺からなる単純な有向グラフ $ G $ があり、頂点には頂点 $ 1 $, 頂点 $ 2 $, $ \ldots $, 頂点 $ N $ と番号がついています。 また、$ i $ $ (1\leq\ i\leq\ M) $ 本目の辺は頂点 $ U_i $ から頂点 $ V_i $ へ張られています。

高橋君がある頂点から始めて、$ G $ の上を有向辺に沿って頂点から頂点へ移動することを繰り返します。 $ G $ の頂点のうち、高橋君がうまく経路を選ぶことで、その頂点から始めていくらでも移動を繰り返すことができるようなものの個数を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ M\ \leq\ \min(N(N-1),\ 2\times\ 10^5) $
- $ 1\ \leq\ U_i,V_i\leq\ N $
- $ U_i\neq\ V_i $
- $ i\neq\ j $ ならば $ (U_i,V_i)\neq\ (U_j,V_j) $
- 入力はすべて整数である。

### Sample Explanation 1

頂点 $ 2 $ を始点とした場合、頂点 $ 2 $ $ \to $ 頂点 $ 3 $ $ \to $ 頂点 $ 4 $ $ \to $ 頂点 $ 2 $ $ \to $ 頂点 $ 3 $ $ \to $ $ \cdots $ と高橋君はいくらでも移動を繰り返す事ができます。 頂点 $ 3 $, 頂点 $ 4 $ を始点とした場合も同様です。 頂点 $ 1 $ からは最初に頂点 $ 2 $ に移動して、以下同様にいくらでも行動を繰り返すことができます。 一方、頂点 $ 5 $ からは一度も移動することができません。 よって、条件を満たすのは頂点 $ 1 $, $ 2 $, $ 3 $, $ 4 $ の $ 4 $ つであるので、 $ 4 $ を出力します。

### Sample Explanation 2

単純な有向グラフにおいて、$ 2 $ つの頂点の間を互いに逆向きに結ぶ辺が、ともに存在する事はあり得ることに注意してください。 また、$ G $ は連結であるとは限りません。

## 样例 #1

### 输入

```
5 5

1 2

2 3

3 4

4 2

4 5```

### 输出

```
4```

## 样例 #2

### 输入

```
3 2

1 2

2 1```

### 输出

```
2```

# AI分析结果

### 题目内容
#### [ABC245F] Endless Walk

**题目描述**

给定一个包含 $N$ 个顶点和 $M$ 条边的有向图 $G$，顶点编号为 $1$ 到 $N$。第 $i$ 条边从顶点 $U_i$ 指向顶点 $V_i$。

高桥君从某个顶点出发，沿着有向边移动。求有多少个顶点，使得高桥君可以从该顶点出发，经过无限次移动。

**说明/提示**

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq M \leq \min(N(N-1), 2 \times 10^5)$
- $1 \leq U_i, V_i \leq N$
- $U_i \neq V_i$
- $i \neq j$ 时，$(U_i, V_i) \neq (U_j, V_j)$
- 输入均为整数

**样例解释**

- 样例1：顶点 $1$, $2$, $3$, $4$ 满足条件，输出 $4$。
- 样例2：顶点 $1$, $2$ 满足条件，输出 $2$。

### 算法分类
图论

### 题解分析与结论

#### 题解1：iiiiiyang (4星)
**关键亮点**：
- 使用Tarjan算法进行强连通分量（SCC）缩点。
- 反向建图后，通过DFS标记可以进入SCC的点。
- 代码结构清晰，注释详细。

**核心实现思想**：
1. 使用Tarjan算法找到所有强连通分量，并记录每个分量的大小。
2. 反向建图，从大小大于1的SCC开始DFS，标记所有可以到达的点。
3. 统计被标记的点的数量。

**核心代码**：
```cpp
void tarjan(int now) {
    dfn[now] = low[now] = ++tot;
    stk[++top] = now;
    vis[now] = 1;
    for(int i = G1.head[now]; i; i = G1.e[i].nex) {
        int to = G1.e[i].to;
        if(!dfn[to]) 
            tarjan(to),
            low[now] = min(low[now], low[to]);
        else    
            if(vis[to])
                low[now] = min(low[now], dfn[to]);
    }
    if(low[now] == dfn[now]) {
        vis[now] = 0;
        col[now] = ++num;
        ++sizcol[num];
        while(stk[top] != now) col[stk[top]] = num, ++sizcol[num], vis[stk[top]] = 0, --top;
        --top;
    }
    return;
}
```

#### 题解2：loser_seele (4星)
**关键亮点**：
- 通过反向建图，将问题转化为拓扑排序。
- 使用队列处理出度为0的点，逐步更新其前驱的出度。
- 时间复杂度为 $O(n+m)$，效率高。

**核心实现思想**：
1. 反向建图，统计每个点的入度。
2. 使用队列处理入度为0的点，标记这些点。
3. 统计未被标记的点的数量。

**核心代码**：
```cpp
queue<int> q;
for(int i = 1; i <= n; i++) {
    if(!in[i]) 
        q.push(i), vis[i] = 1;
}
while(!q.empty()) {
    int t = q.front();
    q.pop();
    for(auto &v : g[t]) {
        in[v]--;
        if(!in[v]) 
            q.push(v), vis[v] = 1;
    }
}
int ans = 0;
for(int i = 1; i <= n; i++) 
    ans += !vis[i];
cout << ans;
```

#### 题解3：AlicX (3星)
**关键亮点**：
- 使用Tarjan算法进行缩点，并结合拓扑排序。
- 通过环去标记可以进入环的点。
- 代码结构较为复杂，但思路清晰。

**核心实现思想**：
1. 使用Tarjan算法找到所有强连通分量，并记录每个分量的大小。
2. 反向建图，进行拓扑排序，标记可以进入环的点。
3. 统计被标记的点的数量。

**核心代码**：
```cpp
void dfs(int u) {
    dfn[u] = low[u] = ++times;
    s[++top] = u; st[u] = true;
    for(int i = h[u]; i != -1; i = tr[i].ne) {
        int to = tr[i].to;
        if(!dfn[to]) dfs(to), low[u] = min(low[u], low[to]);
        else if(st[to]) low[u] = min(low[u], dfn[to]);
    }
    if(dfn[u] == low[u]) {
        int key; cnt++;
        do {
            key = s[top--]; siz[cnt]++;
            id[key] = cnt; st[key] = false;
        } while(key != u);
    }
}
```

### 最优关键思路
- **Tarjan算法**：用于找到强连通分量，缩点后简化图结构。
- **反向建图**：通过反向建图，将问题转化为拓扑排序或DFS遍历，便于处理。
- **拓扑排序**：通过处理出度为0的点，逐步更新其前驱的出度，最终统计满足条件的点。

### 可拓展之处
- 类似问题可以扩展到无向图中，使用并查集或DFS/BFS处理连通性问题。
- 可以结合动态规划，处理更复杂的路径计数问题。

### 推荐题目
1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [P2863 [USACO06JAN]The Cow Prom S](https://www.luogu.com.cn/problem/P2863)
3. [P1262 间谍网络](https://www.luogu.com.cn/problem/P1262)

---
处理用时：42.87秒