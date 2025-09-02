# 题目信息

# [USACO10NOV] Visiting Cows G

## 题目描述

After many weeks of hard work, Bessie is finally getting a vacation! After many weeks of hard work, Bessie is finally getting a vacation!  numbered 1..N. The cows have set up quite an unusual road network with exactly N-1 roads connecting pairs of cows C1 and C2 (1 <= C1 <= N; 1 <= C2 <= N; C1 != C2) in such a way that there exists a unique path of roads between any two cows.

FJ wants Bessie to come back to the farm soon; thus, he has instructed Bessie that if two cows are directly connected by a road, she may not visit them both. Of course, Bessie would like her vacation to be as long as possible, so she would like to determine the maximum number of cows she can visit.

经过了几周的辛苦工作,贝茜终于迎来了一个假期.作为奶牛群中最会社交的牛,她希望去拜访N(1<=N<=50000)个朋友.这些朋友被标号为1..N.这些奶牛有一个不同寻常的交通系统,里面有N-1条路,每条路连接了一对编号为C1和C2的奶牛(1 <= C1 <= N; 1 <= C2 <= N; C1<>C2).这样,在每一对奶牛之间都有一条唯一的通路. FJ希望贝茜尽快的回到农场.于是,他就指示贝茜,如果对于一条路直接相连的两个奶牛,贝茜只能拜访其中的一个.当然,贝茜希望她的假期越长越好,所以她想知道她可以拜访的奶牛的最大数目.


## 说明/提示

Bessie knows 7 cows. Cows 6 and 2 are directly connected by a road, as are cows 3 and 4, cows 2 and 3, etc. The illustration below depicts the roads that connect the cows:

1--2--3--4

|
5--6--7


Bessie can visit four cows. The best combinations include two cows on the top row and two on the bottom. She can't visit cow 6 since that would preclude visiting cows 5 and 7; thus she visits 5 and 7. She can also visit two cows on the top row: {1,3}, {1,4}, or {2,4}.


## 样例 #1

### 输入

```
7 
6 2 
3 4 
2 3 
1 2 
7 6 
5 6 
```

### 输出

```
4 
```

# AI分析结果



### 算法分类
动态规划（树形DP）

---

### 题解综合分析
本题是典型的树形DP问题，核心在于定义状态 `dp[u][0/1]` 表示以u为根的子树中不选/选u时的最大访问数。各题解均采用这一思路，区别在于实现细节和初始化方式。网络流解法虽创新但复杂度较高，树形DP是更优解。

---

### 精选题解

#### 1. 作者：x_faraway_x（5星）
- **亮点**：代码简洁规范，正确初始化DP数组，链式前向星高效存储。
- **关键代码**：
  ```cpp
  void dfs(int u, int father) {
      f[u][1] = 1; // 初始化选u的基值
      for(int e = head[u]; e; e = next[e]) {
          int v = adj[e];
          if(v == father) continue;
          dfs(v, u);
          f[u][0] += max(f[v][0], f[v][1]); // 不选u时累加子节点的最大值
          f[u][1] += f[v][0];               // 选u时只能累加不选子节点的值
      }
  }
  ```

#### 2. 作者：vеctorwyx（4星）
- **亮点**：使用vector存储树结构，代码可读性高，适合新手理解。
- **关键思路**：在DFS中动态维护状态转移，避免重复初始化。
  ```cpp
  void dp(int u) {
      f[u][1] = 1; // 初始化选u为1
      for(auto v : son[u]) {
          if(!vis[v]) {
              vis[v] = true;
              dp(v);
              f[u][0] += max(f[v][0], f[v][1]);
              f[u][1] += f[v][0];
          }
      }
  }
  ```

#### 3. 作者：K2sen（4星）
- **个人心得**：通过错误尝试（黑白染色）验证了贪心策略的不足，强调树形DP的必要性。
- **核心代码**：
  ```cpp
  void dfs(int x, int fx) {
      dp[x][1] = 1;
      for(int i = head[x]; i; i = edge[i].next) {
          int to = edge[i].to;
          if(to == fx) continue;
          dfs(to, x);
          dp[x][0] += max(dp[to][0], dp[to][1]);
          dp[x][1] += dp[to][0];
      }
  }
  ```

---

### 关键技巧总结
1. **状态定义**：`dp[u][0/1]` 表示选/不选节点u时的子树最优解。
2. **转移方程**：
   - 选u时，子节点必须不选：`dp[u][1] += ∑ dp[v][0]`
   - 不选u时，子节点可选可不选：`dp[u][0] += ∑ max(dp[v][0], dp[v][1])`
3. **遍历方式**：后序遍历DFS保证子节点状态先计算。

---

### 拓展练习
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)（同类型树形DP）
2. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)（树形DP+背包）
3. [P2585 三色二叉树](https://www.luogu.com.cn/problem/P2585)（多状态树形DP）

---
处理用时：61.56秒