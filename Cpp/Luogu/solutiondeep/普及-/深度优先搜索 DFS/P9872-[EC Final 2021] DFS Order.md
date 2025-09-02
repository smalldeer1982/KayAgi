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
题目要求计算树中每个节点在DFS序中的最小和最大可能位置。核心思路为：
- **最小位置**：等于节点的深度（必须经过所有祖先节点）。
- **最大位置**：等于总节点数减去该节点子树大小加1（最后遍历该子树）。

### 高分题解推荐

#### 1. 作者：yszkddzyh（★★★★★）
**关键亮点**：
- 代码高效，正确处理多测不清空数组的优化问题（避免`memset`改用动态覆盖）。
- 邻接表双向处理确保树结构正确，DFS同时计算深度和子树大小。
- 注释提示`memset`导致超时的坑点，体现对题目细节的深入理解。

**核心代码**：
```cpp
void dfs(int u, int f) {
    dep[u] = dep[f] + 1; // 深度计算
    siz[u] = 1;          // 初始化子树大小
    for (int v : G[u]) {
        if (v != f) {
            dfs(v, u);
            siz[u] += siz[v]; // 累加子树大小
        }
    }
}
```

#### 2. 作者：Lyrith_with_xQ（★★★★）
**关键亮点**：
- 通过递推公式 `maxt[x] = maxt[f] + (siz[f] - siz[x])` 解释最大位置的计算，与最终结论等价但提供不同视角。
- 代码清晰，两次DFS分别处理子树大小和极值计算，逻辑分明。

**个人心得**：
- 详细图解辅助理解公式推导，强调预处理子树大小的必要性。

#### 3. 作者：BugGod（★★★★）
**关键亮点**：
- 代码极度简洁，变量命名清晰（如`siz`、`dep`），可读性强。
- 快速处理输入输出，适合竞赛场景。

**核心代码**：
```cpp
void dfs(int i, int fa) {
    ss[i] = 1;
    step[i] = step[fa] + 1;
    for (int j : G[i]) {
        if (j != fa) {
            dfs(j, i);
            ss[i] += ss[j];
        }
    }
}
```

### 关键思路总结
- **最小位置**：节点深度，通过单次DFS直接计算。
- **最大位置**：`n - siz[v] + 1`，依赖子树大小的后序遍历统计。
- **实现要点**：邻接表双向构建树，DFS中避免父节点回环，多测时清空邻接表但避免全量重置数组。

### 同类题目推荐
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)（树形DP与子树统计）
2. [P3379 最近公共祖先](https://www.luogu.com.cn/problem/P3379)（树遍历与结构应用）
3. [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)（遍历顺序与极值问题）

---
处理用时：149.71秒