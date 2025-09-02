# 题目信息

# [EC Final 2021] DFS Order

## 题目描述

Prof. Pang has a rooted tree which is rooted at $1$ with $n$ nodes. These $n$ nodes are numbered from $1$ to $n$.

Now he wants to start the depth-first search at the root. He wonders for each node $v$, what is the minimum and the maximum position it can appear in the $\textbf{depth-first search order}$. The depth-first search order is the order of nodes visited during the depth-first search. A node appears in the $j$-th ($1\le j\le n$) position in this order means it is visited after $j-1$ other nodes. Because sons of a node can be iterated in arbitrary order, multiple possible depth-first orders exist. Prof. Pang wants to know for each node $v$, what are the minimum value and the maximum value of $j$ such that $v$ appears in the $j$-th position.

Following is a pseudo-code for the depth-first search on a rooted tree. After its execution, $\texttt{dfs\_order}$ is the depth-first search order.

```
let dfs_order be an empty list

def dfs(vertex x):
    append x to the end of dfs_order.
    for (each son y of x): // sons can be iterated in arbitrary order.
        dfs(y)

dfs(root)
```

## 样例 #1

### 输入

```
2
4
1 2
2 3
3 4
5
1 2
2 3
2 4
1 5```

### 输出

```
1 1
2 2
3 3
4 4
1 1
2 3
3 5
3 5
2 5```

# AI分析结果



### 综合分析与结论
题目要求计算每个节点在DFS序中的最小和最大位置。所有正确题解均基于以下两个核心观察：
1. **最小位置** = 节点深度（必须沿父节点链访问）
2. **最大位置** = n - 子树大小 + 1（最后访问该子树）

关键实现需通过DFS预处理深度和子树大小。错误题解多因误解最大位置计算（如误用深度而非子树大小）。

---

### 高星题解推荐

#### 1. 作者：yszkddzyh（★★★★★）
**关键亮点**：
- 清晰指出多测不清空数组的优化（避免memset超时）
- 代码简洁高效，正确合并DFS计算深度与子树大小
- 注释提醒常见错误，实用性强

**核心代码**：
```cpp
void dfs(int u, int f) {
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    for (int v : G[u]) {
        if (v != f) {
            dfs(v, u);
            siz[u] += siz[v];
        }
    }
}
```

#### 2. 作者：Lyrith_with_xQ（★★★★☆）
**关键亮点**：
- 公式化推导最大位置：$t_x = t_f + s_f - s_x$
- 图文结合解释子树遍历顺序，直观易懂

**核心思路**：
```cpp
maxt[x] = (x==1 ? 1 : cnt[f] - cnt[x] + maxt[f]);
```

#### 3. 作者：BugGod（★★★★☆）
**关键亮点**：
- 变量命名清晰（siz, step），代码可读性强
- 处理无向图的正确DFS方式，避免循环访问

---

### 关键思路与技巧
1. **子树大小递归计算**：DFS中累加子节点的子树大小。
2. **深度优先遍历优化**：单次DFS同时计算深度和子树大小。
3. **多测优化**：手动清空邻接表而非memset，避免O(n)开销。

---

### 个人心得摘录
- **yszkddzyh**：`memset`会导致超时，改为局部清空邻接表。
- **Lyrith_with_xQ**：最大位置公式需结合父节点信息推导，避免孤立计算。
- **BugGod**：无向图DFS需记录父节点防止回溯。

---

### 推荐相似题目
1. **P1351 [NOIP2014 提高组] 联合权值**（树的遍历与邻接处理）
2. **P3379 [模板] 最近公共祖先（LCA）**（深度与父节点应用）
3. **P1040 [NOIP2003 提高组] 加分二叉树**（子树结构与动态规划）

---
处理用时：49.21秒