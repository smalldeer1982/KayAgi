# 题目信息

# Longest Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/dp/tasks/dp_g

$ N $ 頂点 $ M $ 辺の有向グラフ $ G $ があります。 頂点には $ 1,\ 2,\ \ldots,\ N $ と番号が振られています。 各 $ i $ ($ 1\ \leq\ i\ \leq\ M $) について、$ i $ 番目の有向辺は頂点 $ x_i $ から $ y_i $ へ張られています。 $ G $ は**有向閉路を含みません**。

$ G $ の有向パスのうち、最長のものの長さを求めてください。 ただし、有向パスの長さとは、有向パスに含まれる辺の本数のことです。

## 说明/提示

### 制約

- 入力はすべて整数である。
- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ N $
- ペア $ (x_i,\ y_i) $ はすべて相異なる。
- $ G $ は**有向閉路を含まない**。

### Sample Explanation 1

次図の赤い有向パスが最長です。 ![](https://img.atcoder.jp/dp/longest_0_muffet.png)

### Sample Explanation 2

次図の赤い有向パスが最長です。 ![](https://img.atcoder.jp/dp/longest_1_muffet.png)

### Sample Explanation 3

例えば、次図の赤い有向パスが最長です。 ![](https://img.atcoder.jp/dp/longest_2_muffet.png)

## 样例 #1

### 输入

```
4 5

1 2

1 3

3 2

2 4

3 4```

### 输出

```
3```

## 样例 #2

### 输入

```
6 3

2 3

4 5

5 6```

### 输出

```
2```

## 样例 #3

### 输入

```
5 8

5 3

2 3

2 4

5 2

5 1

1 4

4 3

1 3```

### 输出

```
3```

# AI分析结果



**题目中文重写**

### 最长路径

## 题目描述

给定包含 $N$ 个顶点和 $M$ 条边的有向无环图（DAG），求图中的最长有向路径长度（边数）。

**输入格式**
- 第一行两个整数 $N, M$
- 接下来 $M$ 行每行两个整数 $x_i, y_i$ 表示有向边

**输出格式**
- 最长路径的边数

**样例**
输入：
4 5
1 2
1 3
3 2
2 4
3 4
输出：
3

---

**算法分类**  
动态规划 + 图论（拓扑排序/记忆化搜索）

---

**题解综合分析**

所有题解均基于动态规划思想，核心状态定义为：  
`dp[u]` 表示从节点 u 出发的最长路径长度。状态转移方程为：  
`dp[u] = max(dp[v] + 1) 对所有 u→v 的边`  

主要解法分两类：  
1. **记忆化搜索**（DFS + 缓存）  
2. **拓扑排序**（BFS 分层处理）

---

**优质题解推荐**

### 1. 作者：Phartial（拓扑排序法）  
**评分**：★★★★★  
**亮点**  
- 无递归栈溢出风险  
- 严格线性时间复杂度  
- 逻辑清晰易扩展  

**代码核心**  
```cpp
int main() {
    // 拓扑排序预处理
    for (int i = 1; i <= n; ++i) 
        if (!in_degree[i]) q.push(i);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : edges[u]) {
            dp[v] = max(dp[v], dp[u] + 1); // 状态转移
            if (--in_degree[v] == 0) 
                q.push(v);
        }
    }
    cout << *max_element(dp + 1, dp + n + 1);
}
```

### 2. 作者：lottle1212（记忆化搜索法）  
**评分**：★★★★☆  
**亮点**  
- 代码简洁直观  
- 自顶向下自然实现状态转移  

**代码核心**  
```cpp
void dfs(int u) {
    if (dp[u]) return; // 记忆化
    for (int v : edges[u]) {
        dfs(v);
        dp[u] = max(dp[u], dp[v] + 1);
    }
    ans = max(ans, dp[u]);
}
```

### 3. 作者：chenxia25（记忆化搜索精简版）  
**评分**：★★★★  
**亮点**  
- 使用 vector 邻接表  
- 完整处理多个连通分支  

**关键实现**  
```cpp
void dfs(int x) {
    if (vis[x]) return;
    vis[x] = true;
    for (int v : edges[x]) {
        dfs(v);
        dp[x] = max(dp[x], dp[v] + 1);
    }
    ans = max(ans, dp[x]);
}
```

---

**最优思路总结**  
- **拓扑排序法**更稳定，适合大数据量  
- **记忆化搜索**代码简洁，但需注意递归深度  
- 核心技巧：利用 DAG 的无环特性保证转移顺序  

---

**同类题目推荐**  
1. [P1807 最长路](https://www.luogu.com.cn/problem/P1807)  
2. [P1113 杂务](https://www.luogu.com.cn/problem/P1113)  
3. [P4017 最大食物链计数](https://www.luogu.com.cn/problem/P4017)  

---

**心得摘录**  
> - 调试时发现忘记处理多连通分量，导致部分测试点WA（作者：Lyu_echo）  
> - 最初尝试BFS暴力法TLE，改用拓扑排序后效率提升显著（作者：Phartial）  
> - 记忆化搜索中忘记标记访问状态导致重复计算，引发栈溢出（作者：Elairin176）

---
处理用时：57.14秒