# 题目信息

# Great Graphs

## 题目描述

Farmer John has a farm that consists of $ n $ pastures connected by one-directional roads. Each road has a weight, representing the time it takes to go from the start to the end of the road. The roads could have negative weight, where the cows go so fast that they go back in time! However, Farmer John guarantees that it is impossible for the cows to get stuck in a time loop, where they can infinitely go back in time by traveling across a sequence of roads. Also, each pair of pastures is connected by at most one road in each direction.

Unfortunately, Farmer John lost the map of the farm. All he remembers is an array $ d $ , where $ d_i $ is the smallest amount of time it took the cows to reach the $ i $ -th pasture from pasture $ 1 $ using a sequence of roads. The cost of his farm is the sum of the weights of each of the roads, and Farmer John needs to know the minimal cost of a farm that is consistent with his memory.

## 说明/提示

In the first test case, you can add roads

- from pasture $ 1 $ to pasture $ 2 $ with a time of $ 2 $ ,
- from pasture $ 2 $ to pasture $ 3 $ with a time of $ 1 $ ,
- from pasture $ 3 $ to pasture $ 1 $ with a time of $ -3 $ ,
- from pasture $ 3 $ to pasture $ 2 $ with a time of $ -1 $ ,
- from pasture $ 2 $ to pasture $ 1 $ with a time of $ -2 $ .

 The total cost is $ 2 + 1 + -3 + -1 + -2 = -3 $ .In the second test case, you can add a road from pasture $ 1 $ to pasture $ 2 $ with cost $ 1000000000 $ and a road from pasture $ 2 $ to pasture $ 1 $ with cost $ -1000000000 $ . The total cost is $ 1000000000 + -1000000000 = 0 $ .

In the third test case, you can't add any roads. The total cost is $ 0 $ .

## 样例 #1

### 输入

```
3
3
0 2 3
2
0 1000000000
1
0```

### 输出

```
-3
0
0```

# AI分析结果

### 题目内容重写
# Great Graphs

## 题目描述

Farmer John 有一个由 $n$ 个牧场组成的有向图，每个牧场之间通过单向道路连接。每条道路都有一个权重，表示从起点到终点所需的时间。道路的权重可能为负数，这意味着奶牛们可以快速移动以至于时间倒流！然而，Farmer John 保证奶牛们不会陷入时间循环，即通过一系列道路无限地回到过去。此外，每对牧场之间最多只有一条单向道路。

不幸的是，Farmer John 丢失了农场的地图。他只记得一个数组 $d$，其中 $d_i$ 表示从牧场 $1$ 到牧场 $i$ 的最短时间。农场的成本是所有道路权重的总和，Farmer John 需要知道与他的记忆一致的最小成本。

## 说明/提示

在第一个测试用例中，你可以添加以下道路：

- 从牧场 $1$ 到牧场 $2$，时间为 $2$，
- 从牧场 $2$ 到牧场 $3$，时间为 $1$，
- 从牧场 $3$ 到牧场 $1$，时间为 $-3$，
- 从牧场 $3$ 到牧场 $2$，时间为 $-1$，
- 从牧场 $2$ 到牧场 $1$，时间为 $-2$。

总成本为 $2 + 1 + -3 + -1 + -2 = -3$。在第二个测试用例中，你可以添加一条从牧场 $1$ 到牧场 $2$ 的道路，成本为 $1000000000$，以及一条从牧场 $2$ 到牧场 $1$ 的道路，成本为 $-1000000000$。总成本为 $1000000000 + -1000000000 = 0$。

在第三个测试用例中，你不能添加任何道路。总成本为 $0$。

## 样例 #1

### 输入

```
3
3
0 2 3
2
0 1000000000
1
0```

### 输出

```
-3
0
0```

### 算法分类
构造、贪心

### 题解分析与结论
本题的核心在于如何构造一个满足给定最短路径条件的有向图，并且使得所有道路的权重总和最小。题解中主要采用了贪心和构造的思路，通过将最短路径数组排序，并利用正权边和负权边的组合来最小化总成本。

### 所选高星题解
#### 题解1：Reobrok_Kk (4星)
**关键亮点**：通过将最短路径数组排序，构造一条链状的正权边，并利用贪心思想计算负权边的贡献，最终通过公式计算总成本。
**个人心得**：作者最初尝试使用前缀和，但发现错误后，通过大佬指点找到了正解，强调了思维的重要性。

**核心代码**：
```cpp
int ans = 0;
for (int i = 2; i <= n; ++i)
    ans += edge[i] * (n - i + 1) * (i - 1) - edge[i];
```

#### 题解2：Kevin_Zhen (4星)
**关键亮点**：通过构造一条链状的正权边，并详细分析了负权边的贡献次数，最终通过公式计算总成本。
**个人心得**：作者通过打表发现负权边的贡献次数呈现规律，进一步简化了计算过程。

**核心代码**：
```cpp
for (int i = 2; i <= n; ++i) {
    int w = d[i] - d[i - 1];
    ans += w + (-1ll) * w * (n - i + 1) * (i - 1);
}
```

#### 题解3：Zheng_iii (4星)
**关键亮点**：通过贪心思想将最短路径数组排序，并利用负权边的贡献次数公式计算总成本。
**个人心得**：作者强调了贪心思想在解决此类问题中的重要性，并提供了简洁的实现。

**核心代码**：
```cpp
for(int i = 2; i <= n; i++){
    e[i] = d[i] - d[i - 1];
    ans += e[i] * (n - i + 1) * (i - 1) - e[i];
}
```

### 最优关键思路
1. **排序与构造链状正权边**：将最短路径数组排序，构造一条链状的正权边，确保正权边的最小化。
2. **负权边的贡献计算**：通过计算每条正权边之后的所有点与之前所有点的负权边贡献，利用公式简化计算。
3. **贪心思想**：通过贪心思想确保总成本最小化，避免复杂的图构造。

### 可拓展之处
类似的问题可以通过贪心和构造的思路来解决，特别是在需要最小化某些成本或最大化某些收益的情况下。例如，最小生成树问题、最短路径问题等。

### 推荐题目
1. [P3371 【模板】单源最短路径（弱化版）](https://www.luogu.com.cn/problem/P3371)
2. [P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)
3. [P3385 【模板】负环](https://www.luogu.com.cn/problem/P3385)

### 个人心得总结
在解决此类问题时，思维的重要性不可忽视。通过排序和贪心思想，可以简化问题的复杂度，避免复杂的图构造和计算。同时，打表和观察规律也是解决问题的有效手段。

---
处理用时：40.01秒