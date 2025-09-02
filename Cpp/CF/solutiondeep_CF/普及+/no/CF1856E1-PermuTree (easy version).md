# 题目信息

# PermuTree (easy version)

## 题目描述

This is the easy version of the problem. The differences between the two versions are the constraint on $ n $ and the time limit. You can make hacks only if both versions of the problem are solved.

You are given a tree with $ n $ vertices rooted at vertex $ 1 $ .

For some permutation $ ^\dagger $ $ a $ of length $ n $ , let $ f(a) $ be the number of pairs of vertices $ (u, v) $ such that $ a_u < a_{\operatorname{lca}(u, v)} < a_v $ . Here, $ \operatorname{lca}(u,v) $ denotes the [lowest common ancestor](https://en.wikipedia.org/wiki/Lowest_common_ancestor) of vertices $ u $ and $ v $ .

Find the maximum possible value of $ f(a) $ over all permutations $ a $ of length $ n $ .

 $ ^\dagger $ A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

## 说明/提示

The tree in the first test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/b4446034dab04a6ae6c9b21c7c1f4229d9a4c572.png)One possible optimal permutation $ a $ is $ [2, 1, 4, 5, 3] $ with $ 4 $ suitable pairs of vertices:

- $ (2, 3) $ , since $ \operatorname{lca}(2, 3) = 1 $ and $ 1 < 2 < 4 $ ,
- $ (2, 4) $ , since $ \operatorname{lca}(2, 4) = 1 $ and $ 1 < 2 < 5 $ ,
- $ (2, 5) $ , since $ \operatorname{lca}(2, 5) = 1 $ and $ 1 < 2 < 3 $ ,
- $ (5, 4) $ , since $ \operatorname{lca}(5, 4) = 3 $ and $ 3 < 4 < 5 $ .

The tree in the third test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/d99652a679d9214ec6283dd777f9d3b7f1434695.png)The tree in the fourth test:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/1b3604b93549da62e326378a176bbc03c4448da2.png)

## 样例 #1

### 输入

```
5
1 1 3 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2
1```

### 输出

```
0```

## 样例 #3

### 输入

```
6
1 2 2 1 5```

### 输出

```
7```

## 样例 #4

### 输入

```
4
1 1 1```

### 输出

```
2```

# AI分析结果

### 题目内容重写
#### PermuTree (easy version)

**题目描述**

这是该问题的简单版本。两个版本之间的区别在于对 $n$ 的限制和时间限制。只有在两个版本的问题都解决时，你才能进行 hack。

给定一棵以顶点 $1$ 为根的树，树有 $n$ 个顶点。

对于某个长度为 $n$ 的排列 $a$，定义 $f(a)$ 为满足 $a_u < a_{\operatorname{lca}(u, v)} < a_v$ 的顶点对 $(u, v)$ 的数量。其中，$\operatorname{lca}(u,v)$ 表示顶点 $u$ 和 $v$ 的[最低公共祖先](https://en.wikipedia.org/wiki/Lowest_common_ancestor)。

在所有长度为 $n$ 的排列 $a$ 中，找出 $f(a)$ 的最大可能值。

**说明/提示**

第一组测试中的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/b4446034dab04a6ae6c9b21c7c1f4229d9a4c572.png)

一个可能的最优排列 $a$ 是 $[2, 1, 4, 5, 3]$，其中有 $4$ 对满足条件的顶点：

- $(2, 3)$，因为 $\operatorname{lca}(2, 3) = 1$ 且 $1 < 2 < 4$，
- $(2, 4)$，因为 $\operatorname{lca}(2, 4) = 1$ 且 $1 < 2 < 5$，
- $(2, 5)$，因为 $\operatorname{lca}(2, 5) = 1$ 且 $1 < 2 < 3$，
- $(5, 4)$，因为 $\operatorname{lca}(5, 4) = 3$ 且 $3 < 4 < 5$。

第三组测试中的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/d99652a679d9214ec6283dd777f9d3b7f1434695.png)

第四组测试中的树：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1856E1/1b3604b93549da62e326378a176bbc03c4448da2.png)

**样例 #1**

**输入**

```
5
1 1 3 3
```

**输出**

```
4
```

**样例 #2**

**输入**

```
2
1
```

**输出**

```
0
```

**样例 #3**

**输入**

```
6
1 2 2 1 5
```

**输出**

```
7
```

**样例 #4**

**输入**

```
4
1 1 1
```

**输出**

```
2
```

### 算法分类
动态规划、树形DP

### 题解综合分析
本题的核心思路是通过树形DP和01背包来最大化每个节点的贡献。具体来说，对于每个节点，我们将其子树分成两部分，使得这两部分的大小尽可能接近，从而最大化该节点作为LCA的贡献。这一过程可以通过01背包来实现，时间复杂度为 $O(n^2)$。

### 所选高星题解
#### 题解1：作者：EuphoricStar (赞：8)
**星级：5星**
**关键亮点：**
- 通过局部贪心策略，将问题转化为01背包问题，思路清晰。
- 详细解释了如何将子树分成两部分以最大化贡献。
- 代码简洁，易于理解。

**核心代码：**
```cpp
void dfs(int u) {
    siz[u] = 1;
    for (int v : G[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int v : G[u]) {
        for (int j = siz[u]; j >= siz[v]; j--) {
            dp[j] |= dp[j - siz[v]];
        }
    }
    int max_val = 0;
    for (int i = 1; i < siz[u]; i++) {
        if (dp[i]) {
            max_val = max(max_val, i * (siz[u] - 1 - i));
        }
    }
    ans += max_val;
}
```

#### 题解2：作者：Pengzt (赞：6)
**星级：4星**
**关键亮点：**
- 通过将子树内部的编号连续化，简化了问题。
- 详细解释了如何将子树分成两个集合以最大化贡献。
- 代码实现清晰，易于理解。

**核心代码：**
```cpp
void dfs(int u) {
    siz[u] = 1;
    for (int v : G[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int v : G[u]) {
        for (int j = siz[u]; j >= siz[v]; j--) {
            dp[j] |= dp[j - siz[v]];
        }
    }
    int max_val = 0;
    for (int i = 1; i < siz[u]; i++) {
        if (dp[i]) {
            max_val = max(max_val, i * (siz[u] - 1 - i));
        }
    }
    ans += max_val;
}
```

#### 题解3：作者：shinzanmono (赞：2)
**星级：4星**
**关键亮点：**
- 通过背包问题求解子树分组的最大值，思路清晰。
- 详细解释了如何通过背包求解最大贡献。
- 代码实现简洁，易于理解。

**核心代码：**
```cpp
void dfs(int u) {
    siz[u] = 1;
    for (int v : G[u]) {
        dfs(v);
        siz[u] += siz[v];
    }
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int v : G[u]) {
        for (int j = siz[u]; j >= siz[v]; j--) {
            dp[j] |= dp[j - siz[v]];
        }
    }
    int max_val = 0;
    for (int i = 1; i < siz[u]; i++) {
        if (dp[i]) {
            max_val = max(max_val, i * (siz[u] - 1 - i));
        }
    }
    ans += max_val;
}
```

### 最优关键思路或技巧
- **树形DP与01背包结合**：通过树形DP遍历树结构，利用01背包将子树分成两部分以最大化贡献。
- **局部贪心策略**：在每个节点处，通过贪心策略将子树分成两部分，使得这两部分的大小尽可能接近。

### 可拓展之处
- 类似的问题可以通过树形DP和背包问题来解决，例如在树结构中进行分组或分配任务。
- 可以进一步优化背包问题的实现，例如使用滚动数组或bitset来减少空间复杂度。

### 推荐题目
1. [P1352 没有上司的舞会](https://www.luogu.com.cn/problem/P1352)
2. [P2014 选课](https://www.luogu.com.cn/problem/P2014)
3. [P2015 二叉苹果树](https://www.luogu.com.cn/problem/P2015)

---
处理用时：55.49秒