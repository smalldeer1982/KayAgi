# 题目信息

# Paths on the Tree

## 题目描述

You are given a rooted tree consisting of $ n $ vertices. The vertices are numbered from $ 1 $ to $ n $ , and the root is the vertex $ 1 $ . You are also given a score array $ s_1, s_2, \ldots, s_n $ .

A multiset of $ k $ simple paths is called valid if the following two conditions are both true.

- Each path starts from $ 1 $ .
- Let $ c_i $ be the number of paths covering vertex $ i $ . For each pair of vertices $ (u,v) $ ( $ 2\le u,v\le n $ ) that have the same parent, $ |c_u-c_v|\le 1 $ holds.

 The value of the path multiset is defined as $ \sum\limits_{i=1}^n c_i s_i $ .It can be shown that it is always possible to find at least one valid multiset. Find the maximum value among all valid multisets.

## 说明/提示

In the first test case, one of optimal solutions is four paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , $ 1 \to 4 $ , here $ c=[4,2,2,2,2] $ . The value equals to $ 4\cdot 6+ 2\cdot 2+2\cdot 1+2\cdot 5+2\cdot 7=54 $ .

In the second test case, one of optimal solution is three paths $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 2 \to 3 \to 5 $ , $ 1 \to 4 $ , here $ c=[3,2,2,1,2] $ . The value equals to $ 3\cdot 6+ 2\cdot 6+2\cdot 1+1\cdot 4+2\cdot 10=56 $ .

## 样例 #1

### 输入

```
2
5 4
1 2 1 3
6 2 1 5 7
5 3
1 2 1 3
6 6 1 4 10```

### 输出

```
54
56```

# AI分析结果



# Paths on the Tree

## 题目描述

给定一棵包含 $n$ 个顶点的有根树，顶点编号为 $1$ 到 $n$，根为顶点 $1$。同时给定一个分数数组 $s_1, s_2, \ldots, s_n$。

一个包含 $k$ 条简单路径的多重集合被称为有效的，当且仅当满足以下两个条件：
1. 每条路径都从 $1$ 开始。
2. 对于任意两个有相同父节点的顶点对 $(u, v)$（$2 \le u, v \le n$），满足 $|c_u - c_v| \le 1$，其中 $c_i$ 表示顶点 $i$ 被路径覆盖的次数。

路径集合的值定义为 $\sum\limits_{i=1}^n c_i s_i$。请找出所有有效集合中的最大值。

## 输入输出样例

样例 #1 输入：
```
2
5 4
1 2 1 3
6 2 1 5 7
5 3
1 2 1 3
6 6 1 4 10
```
输出：
```
54
56
```

---

### 算法分类：**贪心算法**

---

## 题解分析与核心思路

#### 核心难点
1. **平衡条件约束**：同一父节点的子节点覆盖次数相差不超过1，要求分配路径时必须遵循平均分配原则。
2. **最大化收益**：在平均分配基础上，剩余路径要分配给能带来最大增益的子树。

#### 解决思路
1. **递归贪心分配**：对于每个节点，首先均分路径给子节点，剩余路径优先分配给增益最大的子树。
2. **优先队列优化**：用优先队列维护子树增益差值，快速选出前 $rest$ 大增益项。
3. **记忆化搜索**：通过 DP 存储节点在不同分配次数下的最大收益，避免重复计算。

#### 关键状态转移
设节点 $u$ 有 $m$ 个子节点，分配 $k$ 次路径时：
- 每个子节点基础分配次数为 $\lfloor k/m \rfloor$
- 剩余路径 $rest = k \% m$
- 转移方程：
  ```math
  dp[u][k] = \sum_{v \in sons} dp[v][\lfloor k/m \rfloor] + \text{前rest大}(dp[v][\lceil k/m \rceil] - dp[v][\lfloor k/m \rfloor]) + s_u \cdot k
  ```

---

## 高星题解推荐

### 1. GalwayGirl 的解法（★★★★☆）
- **亮点**：使用两次 DFS 分别计算子树结构和路径分配，通过优先队列动态维护增益差值。
- **代码简析**：
  ```cpp
  long long dfs2(int now, long long k, int fa) {
      ans += k * w[now];
      if (!son[now]) return w[now];
      long long fen = k / son[now], rest = k % son[now];
      priority_queue<long long> q;
      for (子节点 v) 
          q.push(dfs2(v, fen, now));
      if (rest) 
          取前rest大的增益并累加;
      return q.top() + w[now];
  }
  ```

### 2. As_Snow 的解法（★★★★☆）
- **亮点**：记忆化 DP 实现，通过哈希表存储状态，代码简洁高效。
- **代码简析**：
  ```cpp
  ll dfs(int u, int m) {
      if (dp[u].count(m)) return dp[u][m];
      ll res = m * s[u];
      for (子节点 v) 
          res += dfs(v, base);
      用优先队列计算前rest大增益;
      return dp[u][m] = res;
  }
  ```

### 3. xianggl 的解法（★★★★☆）
- **亮点**：明确状态转移方程，动态规划思路清晰。
- **代码简析**：
  ```cpp
  ll dfs(int u, int k) {
      if (dp[u].find(k) != dp[u].end()) return dp[u][k];
      ll res = 1ll * s[u] * k;
      for (子节点 v)
          res += dfs(v, base);
      优先队列处理剩余分配;
      return dp[u][k] = res;
  }
  ```

---

## 关键代码实现

#### GalwayGirl 核心代码片段
```cpp
long long dfs2(int now, long long k, int fa) {
    ans += k * w[now];  
    if (!son[now]) return w[now]; // 叶子节点直接返回
    long long fen = k / son[now], rest = k % son[now];
    priority_queue<long long> q;
    for (遍历子节点 v) {
        q.push(dfs2(v, fen, now)); // 递归处理子节点
    }
    if (rest) {
        while (rest--) { // 选取前rest大增益
            ans += q.top();
            q.pop();
        }
    }
    return q.top() + w[now]; // 返回当前路径贡献
}
```

---

## 可视化设计思路

### 动态规划矩阵动画
1. **网格展示**：每个节点对应一个格子，横向表示分配次数，纵向表示节点编号。
2. **颜色标记**：
   - 绿色：当前正在计算的状态。
   - 黄色：已计算的最优状态。
   - 红色：被更新的状态。
3. **步进控制**：可调节速度观察每个节点如何分配路径次数。

### 复古像素风格
- **8位调色板**：使用经典红白机绿、黄、红三色渲染 DP 矩阵。
- **音效设计**：
  - `状态更新`：8-bit 短促 "滴" 声。
  - `最优解更新`：上升音调提示。
- **自动演示**：AI 自动选择最大增益路径，展示贪心过程。

---

## 相似题目推荐
1. **洛谷 P1272** - 树形DP与路径分配。
2. **洛谷 P2014** - 树形结构上的资源分配问题。
3. **洛谷 P3177** - 树上背包问题的变种。

---
处理用时：82.18秒