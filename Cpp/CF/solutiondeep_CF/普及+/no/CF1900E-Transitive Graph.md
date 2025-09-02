# 题目信息

# Transitive Graph

## 题目描述

You are given a directed graph $ G $ with $ n $ vertices and $ m $ edges between them.

Initially, graph $ H $ is the same as graph $ G $ . Then you decided to perform the following actions:

- If there exists a triple of vertices $ a $ , $ b $ , $ c $ of $ H $ , such that there is an edge from $ a $ to $ b $ and an edge from $ b $ to $ c $ , but there is no edge from $ a $ to $ c $ , add an edge from $ a $ to $ c $ .
- Repeat the previous step as long as there are such triples.

Note that the number of edges in $ H $ can be up to $ n^2 $ after performing the actions.

You also wrote some values on vertices of graph $ H $ . More precisely, vertex $ i $ has the value of $ a_i $ written on it.

Consider a simple path consisting of $ k $ distinct vertices with indexes $ v_1, v_2, \ldots, v_k $ . The length of such a path is $ k $ . The value of that path is defined as $ \sum_{i = 1}^k a_{v_i} $ .

A simple path is considered the longest if there is no other simple path in the graph with greater length.

Among all the longest simple paths in $ H $ , find the one with the smallest value.

## 说明/提示

In the first test case, the longest path in both graphs is $ 1 \to 3 \to 4 \to 5 \to 2 $ . As the path includes all vertices, the minimal possible value of the longest path is the sum of values on all vertices, which is $ 12 $ .

In the second test case, the longest possible path is $ 1 \to 2 \to 3 \to 4 \to 6 \to 7 $ . As there are no longest paths with vertex $ 5 $ in them, this path has the minimal possible value of $ 5\,999\,999\,995 $ .

In the third test case, it can be proven that there is no path longer than $ 11 $ and that the value of the longest path cannot be less than $ 37 $ . Also, notice that the given graph has both self-loops and multiple edges.

## 样例 #1

### 输入

```
3
5 6
2 2 4 1 3
1 2
1 3
2 4
3 4
4 5
5 2
7 7
999999999 999999999 999999999 999999999 1000000000 999999999 1000000000
1 2
2 3
3 4
4 1
4 5
4 6
6 7
14 22
2 3 5 7 3 4 1 4 3 4 2 2 5 1
1 2
2 3
2 4
3 1
4 4
4 5
5 6
5 6
5 12
6 7
6 8
7 5
7 7
7 9
8 4
9 11
10 9
11 10
11 10
12 13
13 14
14 12```

### 输出

```
5 12
6 5999999995
11 37```

# AI分析结果

### 题目内容重写

#### 题目描述

给定一个有向图 $G$，包含 $n$ 个顶点和 $m$ 条边。初始时，图 $H$ 与图 $G$ 相同。然后执行以下操作：

- 如果存在三个顶点 $a$、$b$、$c$，使得图 $H$ 中存在从 $a$ 到 $b$ 的边和从 $b$ 到 $c$ 的边，但不存在从 $a$ 到 $c$ 的边，则添加一条从 $a$ 到 $c$ 的边。
- 重复上述操作，直到不存在这样的三元组。

注意，执行这些操作后，图 $H$ 中的边数最多可达 $n^2$。

在图 $H$ 的顶点上写有一些值，具体来说，顶点 $i$ 上写有值 $a_i$。

考虑一个由 $k$ 个不同顶点组成的简单路径，顶点索引为 $v_1, v_2, \ldots, v_k$。该路径的长度为 $k$，其值定义为 $\sum_{i = 1}^k a_{v_i}$。

如果一个简单路径是最长的，那么图中不存在其他长度更大的简单路径。

在所有最长的简单路径中，找到值最小的路径。

#### 说明/提示

在第一个测试用例中，两个图中的最长路径都是 $1 \to 3 \to 4 \to 5 \to 2$。由于该路径包含所有顶点，因此最长路径的最小可能值是所有顶点值的总和，即 $12$。

在第二个测试用例中，最长路径是 $1 \to 2 \to 3 \to 4 \to 6 \to 7$。由于没有包含顶点 $5$ 的最长路径，因此该路径的最小可能值为 $5\,999\,999\,995$。

在第三个测试用例中，可以证明没有长度超过 $11$ 的路径，并且最长路径的值不能小于 $37$。此外，给定的图包含自环和多重边。

#### 样例 #1

##### 输入

```
3
5 6
2 2 4 1 3
1 2
1 3
2 4
3 4
4 5
5 2
7 7
999999999 999999999 999999999 999999999 1000000000 999999999 1000000000
1 2
2 3
3 4
4 1
4 5
4 6
6 7
14 22
2 3 5 7 3 4 1 4 3 4 2 2 5 1
1 2
2 3
2 4
3 1
4 4
4 5
5 6
5 6
5 12
6 7
6 8
7 5
7 7
7 9
8 4
9 11
10 9
11 10
11 10
12 13
13 14
14 12
```

##### 输出

```
5 12
6 5999999995
11 37
```

### 算法分类

图论

### 题解分析与结论

该题的核心在于理解图 $H$ 的构造过程，并利用强连通分量（SCC）和拓扑排序来解决问题。所有题解都采用了缩点（将强连通分量缩为一个点）的策略，将原图转化为有向无环图（DAG），然后在 DAG 上进行动态规划（DP）来求解最长路径及其最小权值和。

#### 关键思路与技巧

1. **缩点**：通过 Tarjan 算法找到强连通分量，并将每个强连通分量缩为一个点，转化为 DAG。
2. **拓扑排序 + DP**：在 DAG 上进行拓扑排序，同时进行 DP，记录每个点的最长路径长度及其对应的最小权值和。
3. **优化**：由于缩点后的图是 DAG，可以直接通过拓扑排序进行 DP，避免了复杂的路径搜索。

#### 可拓展之处

该题的解法可以推广到其他涉及强连通分量和 DAG 的问题，例如：
- 求解 DAG 上的最长路径。
- 在 DAG 上进行 DP 求解其他优化问题。

#### 推荐题目

1. [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387)
2. [P2746 [USACO5.3] 校园网Network of Schools](https://www.luogu.com.cn/problem/P2746)
3. [P2863 [USACO06JAN] The Cow Prom](https://www.luogu.com.cn/problem/P2863)

### 精选题解

#### 题解1：作者：_Ink (赞：7)

**星级**：★★★★★  
**关键亮点**：详细分析了缩点后的图结构，并给出了清晰的 DP 转移方程，代码实现简洁高效。

**核心代码**：
```cpp
void tarjan(int x) {
    dfn[x] = low[x] = ++ tim;
    vis[x] = true;
    s.push(x);
    for(int i = e1.head[x]; i; i = e1.nxt[i]){
        int y = e1.to[i];
        if(!dfn[y]){
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        if(vis[y]) low[x] = min(low[x], dfn[y]);
    }
    if(dfn[x] == low[x]){
        ++ kn;
        while(s.size()){
            int y = s.top(); s.pop();
            vis[y] = false;
            belong[y] = kn;
            valk[kn] += val[y];
            valc[kn] ++;
            if(x == y) break;
        }
    }
}
```

#### 题解2：作者：Engulf (赞：3)

**星级**：★★★★  
**关键亮点**：直接指出不需要真正构建新图，通过缩点和拓扑排序 DP 解决问题，思路清晰。

**核心代码**：
```cpp
void tarjan(int u) {
    dfn[u] = low[u] = ++tim;
    stk.push(u), ins[u] = 1;
    for (auto v: g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (dfn[u] == low[u]) {
        int v;
        ++tot;
        do {
            v = stk.top();
            siz[tot]++;
            ins[v] = 0;
            w[tot] += a[v];
            scc[v] = tot;
            stk.pop();
        } while (v != u);
    }
}
```

#### 题解3：作者：BINYU (赞：2)

**星级**：★★★★  
**关键亮点**：详细解释了缩点后的图结构，并给出了清晰的 DP 转移方程，代码实现简洁高效。

**核心代码**：
```cpp
void tarjan(int c) {
    dfn[c] = low[c] = ++dfst; s.push(c);
    for (int to : old[c]) {
        if (!dfn[to]) {tarjan(to); low[c] = min(low[c], low[to]);}
        else if (!col[to]) {low[c] = min(low[c], dfn[to]);}
    } if (low[c] != dfn[c]) return;
    while (1) {
        int tp = s.top(); s.pop(); col[tp] = c;
        if (tp == c) break; 
        val[c] += val[tp]; ind[c]++;
    }
}
```

### 个人心得

- **调试经历**：在实现 Tarjan 算法时，需要注意栈的使用和访问标记的维护，避免重复访问或遗漏。
- **顿悟感想**：缩点后的 DAG 结构使得问题大大简化，拓扑排序和 DP 的结合是解决此类问题的有效方法。

---
处理用时：72.68秒