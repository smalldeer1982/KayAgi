# 题目信息

# [POI 2008] STA-Station

## 题目描述

给定一个 $n$ 个点的树，请求出一个结点，使得以这个结点为根时，所有结点的深度之和最大。

一个结点的深度之定义为该节点到根的简单路径上边的数量。

## 说明/提示

#### 样例 1 解释

输出 $7$ 和 $8$ 都是正确答案。

#### 数据规模与约定

对于全部的测试点，保证 $1 \leq n \leq 10^6$，$1 \leq u, v \leq n$，给出的是一棵树。

## 样例 #1

### 输入

```
8
1 4
5 6
4 5
6 7
6 8
2 4
3 4
```

### 输出

```
7
```

# AI分析结果



### 综合分析与结论
本题需通过换根DP在O(n)时间内求解最优根节点。各题解核心思路均为两次DFS：第一次计算子树信息，第二次通过转移方程递推各节点答案。最优解法关键在于正确推导转移方程`f[child] = f[parent] + n - 2*size[child]`，并高效实现两次遍历。

---

### 精选题解列表

#### 1. 作者：nofind (⭐⭐⭐⭐⭐)
**关键亮点**  
- 思路清晰，推导直观，图解辅助理解  
- 代码简洁高效，变量命名规范（size/dep/f数组）  
- 处理long long溢出问题，适合大数据  
**核心代码**  
```cpp
void dfs1(int x, int fa) {
    size[x] = 1;
    for (int y : e[x]) {
        if (y == fa) continue;
        dfs1(y, x);
        size[x] += size[y];
        f[x] += f[y] + size[y]; // 累计子树深度和
    }
}
void dfs2(int x, int fa) {
    for (int y : e[x]) {
        if (y == fa) continue;
        f[y] = f[x] + n - 2 * size[y]; // 换根公式
        dfs2(y, x);
    }
}
```

#### 2. 作者：Huami360 (⭐⭐⭐⭐)
**关键亮点**  
- 公式推导详细，强调思维过程  
- 代码结构清晰，单独封装DFS函数  
- 明确处理多解时取最小编号  
**核心实现**  
```cpp
void dfs2(int u) {
    ans = max(ans, f[u]);
    for (int v : tree[u]) {
        if (v == parent[u]) continue;
        f[v] = f[u] + n - 2 * sz[v];
        dfs2(v);
    }
}
```

#### 3. 作者：Su_Zipei (⭐⭐⭐⭐)
**关键亮点**  
- 代码极简，突出算法核心逻辑  
- 函数命名明确（dfs1/dfs2）  
- 无冗余操作，适合快速理解  
**代码片段**  
```cpp
void dfs(int u, int fa) {
    sz[u] = 1; 
    for (int v : edges[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sz[u] += sz[v];
        dp[u] += dp[v]; 
    }
}
```

---

### 关键思路与技巧
1. **换根DP框架**：两次DFS，先处理子树后全局推导。
2. **子树大小计算**：通过后序遍历累计子树节点数。
3. **转移方程**：`f[child] = f[parent] + n - 2*size[child]`，利用父子关系快速计算。
4. **实现细节**：使用邻接表存树，long long防溢出，处理多解取最小节点。

---

### 拓展练习
1. [HDU2196 Computer](https://vjudge.net/problem/HDU-2196) - 求每个节点的最远距离（换根DP经典）
2. [CF1187E Tree Painting](https://codeforces.com/problemset/problem/1187/E) - 类似换根思路计算得分
3. [洛谷P3047 Nearby Cows](https://www.luogu.com.cn/problem/P3047) - 树形DP+换根预处理

---

### 调试心得摘录
1. **nofind**：*"注:记得开long long"* → 数据规模大时累加易溢出。
2. **览遍千秋**：*"结果数据是要求输出编号最小的那个"* → 更新答案时需比较节点编号。
3. **mot1ve**：*"开始通过一次dfs预处理即可"* → 强调预处理的重要性。

---
处理用时：57.88秒