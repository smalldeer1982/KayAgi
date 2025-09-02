# 题目信息

# Doremy's City Construction

## 题目描述

Doremy's new city is under construction! The city can be regarded as a simple undirected graph with $ n $ vertices. The $ i $ -th vertex has altitude $ a_i $ . Now Doremy is deciding which pairs of vertices should be connected with edges.

Due to economic reasons, there should be no self-loops or multiple edges in the graph.

Due to safety reasons, there should not be pairwise distinct vertices $ u $ , $ v $ , and $ w $ such that $ a_u \leq a_v \leq a_w $ and the edges $ (u,v) $ and $ (v,w) $ exist.

Under these constraints, Doremy would like to know the maximum possible number of edges in the graph. Can you help her?

Note that the constructed graph is allowed to be disconnected.

## 说明/提示

In the first test case, there can only be at most $ 3 $ edges in the graph. A possible construction is to connect $ (1,3) $ , $ (2,3) $ , $ (3,4) $ . In the picture below the red number above node $ i $ is $ a_i $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/664da7a7b39c78efe9a85191f05318cb0a9df4d9.png)

The following list shows all such $ u $ , $ v $ , $ w $ that the edges $ (u,v) $ and $ (v,w) $ exist.

- $ u=1 $ , $ v=3 $ , $ w=2 $ ;
- $ u=1 $ , $ v=3 $ , $ w=4 $ ;
- $ u=2 $ , $ v=3 $ , $ w=1 $ ;
- $ u=2 $ , $ v=3 $ , $ w=4 $ ;
- $ u=4 $ , $ v=3 $ , $ w=1 $ ;
- $ u=4 $ , $ v=3 $ , $ w=2 $ .

Another possible construction is to connect $ (1,4) $ , $ (2,4) $ , $ (3,4) $ .

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/7d1fc03a74b1366633e41dc227acef23827c0f69.png)

An unacceptable construction is to connect $ (1,3) $ , $ (2,3) $ , $ (2,4) $ , $ (3,4) $ . Because when $ u=4 $ , $ v=2 $ , $ w=3 $ , $ a_u\le a_v \le a_w $ holds, and the respective edges exist.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1764C/02cccee9e8ea3921ef7338c4d1dd72e83e933cbc.png)

## 样例 #1

### 输入

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000```

### 输出

```
3
9
35
2```

# AI分析结果

### 题目内容重写

Doremy的新城市正在建设中！该城市可以看作是一个简单的无向图，包含 $n$ 个顶点。第 $i$ 个顶点的高度为 $a_i$。现在，Doremy正在决定哪些顶点对应该用边连接。

由于经济原因，图中不应存在自环或多重边。

由于安全原因，图中不应存在三个不同的顶点 $u$、$v$ 和 $w$，使得 $a_u \leq a_v \leq a_w$，并且边 $(u,v)$ 和 $(v,w)$ 同时存在。

在这些约束条件下，Doremy想知道图中可能的最大边数。你能帮助她吗？

注意，构造的图允许是不连通的。

### 样例 #1

#### 输入

```
4
4
2 2 3 1
6
5 2 3 1 5 2
12
7 2 4 9 1 4 6 3 7 4 2 3
4
1000000 1000000 1000000 1000000
```

#### 输出

```
3
9
35
2
```

### 题解分析与结论

#### 综合分析

该题的核心在于如何在不违反安全条件的情况下，最大化图中的边数。通过分析，可以发现将顶点分为两组，一组的所有顶点高度小于另一组，然后在两组之间连边，可以避免出现 $a_u \leq a_v \leq a_w$ 的情况。此外，当所有顶点高度相等时，最大边数为 $\lfloor \frac{n}{2} \rfloor$。

#### 关键思路

1. **分组策略**：将顶点按高度排序后，分为两组，一组高度小于等于某个值，另一组高度大于该值，然后在两组之间连边。
2. **特殊情况处理**：当所有顶点高度相等时，最大边数为 $\lfloor \frac{n}{2} \rfloor$。
3. **枚举分界点**：通过枚举不同的分界点，找到使两组顶点数乘积最大的分法。

#### 评分较高的题解

1. **作者：郑朝曦zzx (5星)**
   - **关键亮点**：清晰地解释了分组策略，并通过枚举分界点来最大化边数。代码实现简洁，且考虑了特殊情况。
   - **代码核心思想**：排序后，枚举每个可能的分界点，计算两组顶点数的乘积，取最大值。

   ```cpp
   sort(a + 1, a + n + 2);
   for (int i = 1; i <= n; ++i) {
       int pos = upper_bound(a + 1, a + n + 2, a[i]) - a - 1;
       ans = max(ans, (LL)pos * (LL)(n - pos));
   }
   ```

2. **作者：Yuki__S2OO8 (4星)**
   - **关键亮点**：通过二分图的思想，将顶点分为两类，并在两类之间连边，避免了安全条件的违反。
   - **代码核心思想**：排序后，枚举每个可能的分界点，计算两组顶点数的乘积，取最大值。

   ```cpp
   sort(a + 1, a + n + 1);
   for (int i = 1; i <= n; ++i) {
       int pos = upper_bound(a + 1, a + n + 1, a[i]) - a - 1;
       ans = max(ans, pos * (n - pos));
   }
   ```

3. **作者：aimoyudexianyu (4星)**
   - **关键亮点**：详细解释了二分图的思想，并通过枚举分界点来最大化边数。代码实现清晰，且考虑了特殊情况。
   - **代码核心思想**：排序后，枚举每个可能的分界点，计算两组顶点数的乘积，取最大值。

   ```cpp
   sort(a + 1, a + n + 1);
   for (int i = 1; i <= n; ++i) {
       int pos = upper_bound(a + 1, a + n + 1, a[i]) - a - 1;
       ans = max(ans, pos * (n - pos));
   }
   ```

### 推荐题目

1. **P3386 【模板】二分图匹配** - 考察二分图的基本概念和匹配算法。
2. **P2764 最小路径覆盖问题** - 考察二分图匹配与路径覆盖的结合。
3. **P2774 方格取数问题** - 考察二分图的最大独立集问题。

### 个人心得

- **调试经历**：在处理特殊情况时，容易忽略所有顶点高度相等的情况，导致答案错误。通过仔细分析，发现需要单独处理这种情况。
- **顿悟感想**：通过将问题转化为二分图的最大边数问题，可以简化问题的复杂度，并且更容易找到最优解。

---
处理用时：34.47秒