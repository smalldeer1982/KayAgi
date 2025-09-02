# 题目信息

# Tree XOR

## 题目描述

You are given a tree with $ n $ vertices labeled from $ 1 $ to $ n $ . An integer $ a_{i} $ is written on vertex $ i $ for $ i = 1, 2, \ldots, n $ . You want to make all $ a_{i} $ equal by performing some (possibly, zero) spells.

Suppose you root the tree at some vertex. On each spell, you can select any vertex $ v $ and any non-negative integer $ c $ . Then for all vertices $ i $ in the subtree $ ^{\dagger} $ of $ v $ , replace $ a_{i} $ with $ a_{i} \oplus c $ . The cost of this spell is $ s \cdot c $ , where $ s $ is the number of vertices in the subtree. Here $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR).

Let $ m_r $ be the minimum possible total cost required to make all $ a_i $ equal, if vertex $ r $ is chosen as the root of the tree. Find $ m_{1}, m_{2}, \ldots, m_{n} $ .

 $ ^{\dagger} $ Suppose vertex $ r $ is chosen as the root of the tree. Then vertex $ i $ belongs to the subtree of $ v $ if the simple path from $ i $ to $ r $ contains $ v $ .

## 说明/提示

In the first test case, to find $ m_1 $ we root the tree at vertex $ 1 $ .

1. In the first spell, choose $ v=2 $ and $ c=1 $ . After performing the spell, $ a $ will become $ [3, 3, 0, 1] $ . The cost of this spell is $ 3 $ .
2. In the second spell, choose $ v=3 $ and $ c=3 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 1] $ . The cost of this spell is $ 3 $ .
3. In the third spell, choose $ v=4 $ and $ c=2 $ . After performing the spell, $ a $ will become $ [3, 3, 3, 3] $ . The cost of this spell is $ 2 $ .

Now all the values in array $ a $ are equal, and the total cost is $ 3 + 3 + 2 = 8 $ .

The values $ m_2 $ , $ m_3 $ , $ m_4 $ can be found analogously.

In the second test case, the goal is already achieved because there is only one vertex.

## 样例 #1

### 输入

```
2
4
3 2 1 0
1 2
2 3
2 4
1
100```

### 输出

```
8 6 12 10 
0```

# AI分析结果

### 题目内容
# 树的异或操作

## 题目描述
给定一棵有 $n$ 个顶点的树，顶点编号从 $1$ 到 $n$ 。对于 $i = 1, 2, \ldots, n$ ，顶点 $i$ 上写有整数 $a_{i}$ 。你希望通过执行一些（可能为零）次魔法操作，使所有的 $a_{i}$ 相等。

假设你将树以某个顶点为根。在每次魔法操作中，你可以选择任意一个顶点 $v$ 和任意一个非负整数 $c$ 。然后，对于以 $v$ 为根的子树 $^{\dagger}$ 中的所有顶点 $i$ ，将 $a_{i}$ 替换为 $a_{i} \oplus c$ 。此操作的代价为 $s \cdot c$ ，其中 $s$ 是该子树中的顶点数量。这里的 $\oplus$ 表示 [按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR) 。

设 $m_r$ 为当顶点 $r$ 被选为树的根时，使所有 $a_i$ 相等所需的最小总代价。求 $m_{1}, m_{2}, \ldots, m_{n}$ 。

$^{\dagger}$ 假设顶点 $r$ 被选为树的根。那么，如果从 $i$ 到 $r$ 的简单路径包含 $v$ ，则顶点 $i$ 属于以 $v$ 为根的子树。

## 说明/提示
在第一个测试用例中，为了求 $m_1$ ，我们将树以顶点 $1$ 为根。
1. 在第一次魔法操作中，选择 $v = 2$ 和 $c = 1$ 。执行操作后，$a$ 将变为 $[3, 3, 0, 1]$ 。此操作的代价为 $3$ 。
2. 在第二次魔法操作中，选择 $v = 3$ 和 $c = 3$ 。执行操作后，$a$ 将变为 $[3, 3, 3, 1]$ 。此操作的代价为 $3$ 。
3. 在第三次魔法操作中，选择 $v = 4$ 和 $c = 2$ 。执行操作后，$a$ 将变为 $[3, 3, 3, 3]$ 。此操作的代价为 $2$ 。

现在数组 $a$ 中的所有值都相等，总代价为 $3 + 3 + 2 = 8$ 。

$m_2$ 、 $m_3$ 、 $m_4$ 的值可以类似地求出。

在第二个测试用例中，由于只有一个顶点，目标已经达成。

## 样例 #1
### 输入
```
2
4
3 2 1 0
1 2
2 3
2 4
1
100
```
### 输出
```
8 6 12 10 
0
```

### 综合分析与结论
这些题解主要围绕如何高效求解以每个顶点为根时使树中所有点权相等的最小代价。思路核心多基于贪心策略与换根DP，也有树上差分的方法。贪心策略是将所有点都异或成根的值，这样能保证代价最小。难点在于如何通过合理的数据结构与算法优化，在 $O(n)$ 时间复杂度内完成计算。

### 所选的题解
- **作者：西瓜nd (赞：12)**
  - **星级**：5星
  - **关键亮点**：思路清晰，先证明将所有点异或成根的值更优，基于此设计状态转移方程 `dp[i]` 表示以 `i` 为根的子树操作后权值都等于根的权值的代价，再通过换根DP求解，代码实现简洁明了。
  ```cpp
  void dfs1(int x,int fath){
      siz[x]=1;
      for(int to:g[x]){
          if(to==fath)continue;
          dfs1(to,x);
          siz[x]+=siz[to];
          dp[x]+=dp[to]+siz[to]*(a[x]^a[to]);
      }
      f[x]=dp[x];
  }

  void dfs2(int x,int fath){
      for(int to:g[x]){
          if(to==fath)continue;
          f[to]+=f[x]-(dp[to]+siz[to]*(a[x]^a[to]))+(n-siz[to])*(a[x]^a[to]);
          dfs2(to,x);
      }
  }
  ```
  核心实现思想：`dfs1` 函数计算以某点为根时子树内权值变为根权值的代价，`dfs2` 函数进行换根操作，更新不同根下的代价。

- **作者：xkcdjerry (赞：5)**
  - **星级**：4星
  - **关键亮点**：提出树上差分做法，通过巧妙转换将问题变为计算边的贡献，利用树上差分优化计算，降低代码复杂度，实现较为简洁。
  ```cpp
  void dfs1(int x,int fa)
  {
      sz[x]=1;
      for(auto i:e[x]) if(i!=fa)
      {
          dfs1(i,x);
          sz[x]+=sz[i];
      }
      if(fa)
      {
          ll w=a[x]^a[fa];
          f[1]+=sz[x]*w;
          f[x]-=sz[x]*w;
          f[x]+=(n-sz[x])*w;
      }
  }
  void dfs2(int x,int fa)
  {
      f[x]+=f[fa];
      for(auto i:e[x]) if(i!=fa) dfs2(i,x);
  }
  ```
  核心实现思想：`dfs1` 函数计算边对以 `1` 为根时的贡献，并记录相关信息，`dfs2` 函数通过树上差分求出所有根的答案。

- **作者：Demeanor_Roy (赞：4)**
  - **星级**：4星
  - **关键亮点**：指出不使用换根DP，通过考虑每条边的贡献，利用DFS序和差分维护来求解，思路新颖，代码简洁高效。
  ```cpp
  inline void dfs(int u,int fa)
  {
      sz[u]=1;dfn[u]=++tim;
      for(int i=h[u];~i;i=ne[i])
      {
          if(e[i]==fa) continue;
          dfs(e[i],u);
          sz[u]+=sz[e[i]];
          ans[1]+=1ll*sz[e[i]]*(v[u]^v[e[i]]);
          ans[dfn[e[i]]]+=1ll*(n-sz[e[i]]*2)*(v[u]^v[e[i]]);
          ans[dfn[e[i]]+sz[e[i]]]-=1ll*(n-sz[e[i]]*2)*(v[u]^v[e[i]]);
      }
  }
  ```
  核心实现思想：`dfs` 函数遍历树，计算边的贡献，利用DFS序和差分更新不同根下的答案。

### 最优关键思路或技巧
1. **贪心策略**：将所有点都异或成根的值能保证代价最小，这为后续算法设计提供了方向。
2. **换根DP**：通过两次DFS，一次计算以某点为根时子树内的代价，另一次基于前一次结果进行换根操作，高效求解不同根下的最小代价。
3. **树上差分优化**：将对每个根的计算转化为对边的贡献计算，利用树上差分优化，降低时间复杂度。

### 同类型题或类似算法套路
此类题目通常围绕树结构，结合贪心策略与动态规划求解。类似套路包括：
1. 先分析局部最优策略，如本题将所有点异或成根的值。
2. 设计合适的状态转移方程，结合树的遍历（如DFS）进行计算。
3. 若涉及不同根的情况，考虑换根DP或类似树上差分的优化方法。

### 洛谷相似题目
1. [P3478 [POI2008]STA-Station](https://www.luogu.com.cn/problem/P3478)：同样是树结构上的换根DP问题，求树中到其他点距离之和最大的点。
2. [P2986 [USACO10FEB]Chocolate Buying S](https://www.luogu.com.cn/problem/P2986)：涉及树的遍历与动态规划，结合贪心思想求解最优解。
3. [P4178 Tree](https://www.luogu.com.cn/problem/P4178)：通过换根DP解决树中路径相关的最值问题。 

---
处理用时：39.88秒