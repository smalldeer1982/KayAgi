# 题目信息

# [GDCPC 2023] Path Planning

## 题目描述

有一个 $n$ 行 $m$ 列的网格。网格里的每个格子都写着一个整数，其中第 $i$ 行第 $j$ 列的格子里写着整数 $a_{i, j}$。从 $0$ 到 $(n \times m - 1)$ 的每个整数（含两端）在网格里都恰好出现一次。

令 $(i, j)$ 表示位于第 $i$ 行第 $j$ 列的格子。您现在需要从 $(1, 1)$ 出发并前往 $(n, m)$。当您位于格子 $(i, j)$ 时，您可以选择走到右方的格子 $(i, j + 1)$（若 $j < m$），也可以选择走到下方的格子 $(i + 1, j)$（若 $i < n$）。

令 $\mathbb{S}$ 表示路径上每个格子里的整数形成的集合，包括 $a_{1, 1}$ 和 $a_{n, m}$。令 $\text{mex}(\mathbb{S})$ 表示不属于 $\mathbb{S}$ 的最小非负整数。请找出一条路径以最大化 $\text{mex}(\mathbb{S})$，并求出这个最大的值。

## 样例 #1

### 输入

```
2
2 3
1 2 4
3 0 5
1 5
1 3 0 4 2```

### 输出

```
3
5```

# AI分析结果

### 综合分析与结论

本题的核心在于如何高效地找到一条从起点到终点的路径，使得路径上的数字集合的 `mex` 最大化。由于网格规模可能很大（$n, m \leq 10^6$），直接使用二维数组或 BFS 等传统方法不可行。大多数题解采用了二分答案的思路，通过 `check` 函数来验证某个 `mex` 值是否可行。不同题解在 `check` 函数的实现上有所差异，但核心思想都是通过检查路径上的点是否满足单调性（即只能向右或向下走）来判断 `mex` 的可行性。

### 所选题解

#### 题解1：作者：2011FYCCCTA (赞：9)
- **星级**：★★★★★
- **关键亮点**：
  - 使用二分答案的思路，代码简洁高效。
  - `check` 函数通过维护一个 `lstx` 变量来确保路径的单调性，逻辑清晰。
  - 代码可读性强，适合初学者理解。
- **核心代码**：
  ```cpp
  bool check(int mina)
  {
      int lstx = 1;
      for (int i = 1 ; i <= n ; i++)
          for (int j = 1 ; j <= m ; j++)
              if (a[(i - 1) * m + j] < mina)
              {
                  if (lstx <= j) lstx = j;
                  else return false;
              }
      return true;
  }
  ```

#### 题解2：作者：zhaohanwen (赞：2)
- **星级**：★★★★
- **关键亮点**：
  - 同样采用二分答案，`check` 函数通过维护 `last` 变量来确保路径的单调性。
  - 代码结构清晰，逻辑简单，适合快速实现。
- **核心代码**：
  ```cpp
  bool check(int mid)
  {
      int last = 0;
      for (int i = 0; i < n; i++)
      {
          for (int j = 0; j < m; j++)
          {
              if (a[i*m+j] < mid)
              {
                  if (last > j) return false;
                  last = j;
              }
          }
      }
      return true;
  }
  ```

#### 题解3：作者：May_Cry_ (赞：1)
- **星级**：★★★★
- **关键亮点**：
  - 使用 `vector` 存储关键点，并通过排序来检查路径的单调性。
  - 代码逻辑较为复杂，但思路清晰，适合对二分答案有一定理解的读者。
- **核心代码**：
  ```cpp
  bool check (int mid) {
      bool f1 = 0 ,f2 = 0;vector <pair <int ,int> > E;
      for (int i = 1;i <= mid;i ++) {
          E.push_back(make_pair(L[i] ,R[i]));
          if (L[i] == 1 && R[i] == 1) f1 = 1;
          if (L[i] == n && R[i] == m) f2 = 1;
      }
      if (!f1) E.push_back(make_pair(1 ,1));
      if (!f2) E.push_back(make_pair(n ,m));
      sort (E.begin(),E.end());
      int last = E[0].second;
      for (int i = 1;i < E.size();i ++) {
          if (last > E[i].second) return 0;
          last = E[i].second;
      }
      return 1;
  }
  ```

### 最优关键思路与技巧

1. **二分答案**：通过二分查找来确定最大的 `mex` 值，结合 `check` 函数验证可行性。
2. **路径单调性检查**：在 `check` 函数中，通过维护一个变量（如 `lstx` 或 `last`）来确保路径上的点满足只能向右或向下走的条件。
3. **空间优化**：由于网格规模大，使用一维数组存储数据，避免二维数组的内存开销。

### 可拓展之处

- **类似题目**：可以考虑其他路径规划问题，如最短路径、最大路径和等，结合二分答案或其他优化方法。
- **数据结构**：可以尝试使用更高级的数据结构（如线段树、平衡树）来优化 `check` 函数的实现。

### 推荐题目

1. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)
2. [P2678 跳石头](https://www.luogu.com.cn/problem/P2678)
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

这些题目都涉及到二分答案的思路，适合进一步巩固和拓展相关知识。

---
处理用时：29.29秒