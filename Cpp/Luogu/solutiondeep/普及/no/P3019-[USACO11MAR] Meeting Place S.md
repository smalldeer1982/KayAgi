# 题目信息

# [USACO11MAR] Meeting Place S

## 题目描述

Bessie and Jonell are great friends. Since Farmer John scrambles where the cows graze every day, they are sometimes quite far from each other and can't talk.

The pastures and paths on FJ's farm form a 'tree' structure.  Each pasture has exactly one distinct path to any other pasture, and each pasture (except pasture #1, the 'root') also has a single parent node.

Bessie and Jonell have decided that they will always meet at the closest pasture that that is both an ancestor of Jonell's pasture and of Bessie's pasture.

FJ created a map of his N (1 <= N <= 1,000) pastures (conveniently numbered 1..N) that tells the parent P\_i (1 <= P\_i <= N) of each pasture except pasture 1, which has no parent.

FJ has released his daily grazing schedule for the next M (1 <= M <= 1,000) days, so Bessie and Jonell are deciding where they should meet each day for gossip. On day k, Bessie is in pasture B\_k (1 <= B\_k <= N) and Jonell is in pasture J\_k (1 <= J\_k <= N).

Given a map and schedule, help Bessie and Jonell find their meeting places.

```cpp
Consider, for example, the following farm layout:

                            Pasture      Parent Pasture
             [1]           ---------    ----------------
            / | \              1              ---
           /  |  \             2               1 
         [2] [3] [6]           3               1
         /        | \          4               2
        /         |  \         5               8
      [4]        [8]  [9]      6               1
                /   \          7               8
               /     \         8               6
             [5]     [7]       9               6

Here are the meeting places that Bessie and Jonell would choose
given a six day schedule of their initial grazing locations:

              Bessie      Jonell       Meeting Place
             --------    --------     ---------------
                 2           7               1
                 4           2               2
                 1           1               1
                 4           1               1
                 7           5               8
                 9           5               6
```




## 样例 #1

### 输入

```
9 6 
1 
1 
2 
8 
1 
8 
6 
6 
2 7 
4 2 
3 3 
4 1 
7 5 
9 5 
```

### 输出

```
1 
2 
3 
1 
8 
6 
```

# AI分析结果



### 算法分类
**图论**

---

### 综合分析与结论
题目要求多次查询树中两节点的最近公共祖先（LCA）。核心思路是通过预处理节点路径信息实现快速查询。题解中主要包含以下方法：暴力路径标记、倍增法、树链剖分、Tarjan离线算法。最优解为**倍增法**，其平衡了时间效率与代码复杂度，适用性最广。

---

### 高分题解推荐

#### 1. **hulean（倍增法）** ⭐⭐⭐⭐⭐
**关键亮点**：
- 清晰讲解倍增法原理，预处理节点的2^k级祖先。
- 代码结构规范，使用链式前向星存树，深度与祖先数组分离。
- 时间复杂度 O(n log n + m log n)，适用于较大数据量。
  
**核心代码思路**：
```cpp
// 预处理深度和祖先数组
void getdeep(int now, int father) {
    deep[now] = deep[father] + 1;
    fa[now][0] = father;
    for (int i = 1; (1<<i) <= deep[now]; i++)
        fa[now][i] = fa[fa[now][i-1]][i-1];
    for (int i = head[now]; i; i = edge[i].next)
        if (edge[i].to != father) 
            getdeep(edge[i].to, now);
}

// LCA查询核心逻辑
int lca(int u, int v) {
    if (deep[u] < deep[v]) swap(u, v);
    for (int i = log2n; i >= 0; i--)
        if (deep[fa[u][i]] >= deep[v]) 
            u = fa[u][i];
    if (u == v) return u;
    for (int i = log2n; i >= 0; i--)
        if (fa[u][i] != fa[v][i])
            u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
```

---

#### 2. **meisr（树链剖分）** ⭐⭐⭐⭐
**关键亮点**：
- 使用树链剖分将树转为链式结构，通过跳链快速找LCA。
- 代码简洁，两次DFS预处理重链，查询时沿重链跳跃。
- 时间复杂度 O(n + m log n)，适合高频查询场景。

**核心代码思路**：
```cpp
// 第一次DFS预处理重儿子和父节点
void DFS1(int u, int ff) {
    size[u] = 1; f[u] = ff; dep[u] = dep[ff] + 1;
    for (int v : son[u]) {
        DFS1(v, u);
        if (size[v] > size[hson[u]]) hson[u] = v;
        size[u] += size[v];
    }
}

// 第二次DFS标记重链顶端
void DFS2(int u, int tp) {
    top[u] = tp;
    if (hson[u]) DFS2(hson[u], tp);
    for (int v : son[u])
        if (v != hson[u]) DFS2(v, v);
}

// 查询LCA
int LCA(int x, int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = f[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}
```

---

### 最优思路提炼
**倍增法的核心优化**：
1. **预处理祖先数组**：对每个节点存储2^k级祖先，通过递推式 fa[u][k] = fa[fa[u][k-1]][k-1] 快速填充。
2. **分层跳跃**：将较深节点跳至与另一节点同层后，同步向上倍增跳跃，通过比较祖先避免过度跳跃。
3. **时间复杂度平衡**：预处理 O(n log n)，查询 O(log n)，适合大规模数据。

---

### 拓展与举一反三
- **类似问题**：路径最大值、子树查询等问题可结合LCA与线段树/并查集。
- **推荐题目**：
  1. [P3379【模板】最近公共祖先（LCA）](https://www.luogu.com.cn/problem/P3379)
  2. [P3884 [JLOI2009]二叉树问题](https://www.luogu.com.cn/problem/P3884)
  3. [P1967 货车运输](https://www.luogu.com.cn/problem/P1967)（LCA+最大生成树）

---

### 题解个人心得摘录
- **hulean**：强调从大向小跳跃避免回溯，二进制拆分思想是关键。
- **meisr**：提醒树链剖分代码需注意重链切换逻辑，避免死循环。
- **zhy137036**：在暴力解法中采用路径标记法，适合小数据快速实现。

---
处理用时：61.03秒