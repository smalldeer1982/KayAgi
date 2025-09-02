# 题目信息

# Closest Cities

## 题目描述

There are $ n $ cities located on the number line, the $ i $ -th city is in the point $ a_i $ . The coordinates of the cities are given in ascending order, so $ a_1 < a_2 < \dots < a_n $ .

The distance between two cities $ x $ and $ y $ is equal to $ |a_x - a_y| $ .

For each city $ i $ , let's define the closest city $ j $ as the city such that the distance between $ i $ and $ j $ is not greater than the distance between $ i $ and each other city $ k $ . For example, if the cities are located in points $ [0, 8, 12, 15, 20] $ , then:

- the closest city to the city $ 1 $ is the city $ 2 $ ;
- the closest city to the city $ 2 $ is the city $ 3 $ ;
- the closest city to the city $ 3 $ is the city $ 4 $ ;
- the closest city to the city $ 4 $ is the city $ 3 $ ;
- the closest city to the city $ 5 $ is the city $ 4 $ .

The cities are located in such a way that for every city, the closest city is unique. For example, it is impossible for the cities to be situated in points $ [1, 2, 3] $ , since this would mean that the city $ 2 $ has two closest cities ( $ 1 $ and $ 3 $ , both having distance $ 1 $ ).

You can travel between cities. Suppose you are currently in the city $ x $ . Then you can perform one of the following actions:

- travel to any other city $ y $ , paying $ |a_x - a_y| $ coins;
- travel to the city which is the closest to $ x $ , paying $ 1 $ coin.

You are given $ m $ queries. In each query, you will be given two cities, and you have to calculate the minimum number of coins you have to spend to travel from one city to the other city.

## 说明/提示

Let's consider the first two queries in the example from the statement:

- in the first query, you are initially in the city $ 1 $ . You can travel to the closest city (which is the city $ 2 $ ), paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 3 $ ) again, paying $ 1 $ coin. Then you travel to the closest city (which is the city $ 4 $ ) again, paying $ 1 $ coin. In total, you spend $ 3 $ coins to get from the city $ 1 $ to the city $ 4 $ ;
- in the second query, you can use the same way to get from the city $ 1 $ to the city $ 4 $ , and then spend $ 5 $ coins to travel from the city $ 4 $ to the city $ 5 $ .

## 样例 #1

### 输入

```
1
5
0 8 12 15 20
5
1 4
1 5
3 4
3 2
5 1```

### 输出

```
3
8
1
4
14```

# AI分析结果

### 题目内容重写（中文）

有 $n$ 个城市位于数轴上，第 $i$ 个城市的坐标为 $a_i$。城市的坐标按升序给出，即 $a_1 < a_2 < \dots < a_n$。

两个城市 $x$ 和 $y$ 之间的距离等于 $|a_x - a_y|$。

对于每个城市 $i$，定义其最近的城市 $j$ 为满足 $i$ 和 $j$ 之间的距离不大于 $i$ 与其他任何城市 $k$ 之间的距离的城市。例如，如果城市位于 $[0, 8, 12, 15, 20]$，那么：

- 城市 $1$ 的最近城市是城市 $2$；
- 城市 $2$ 的最近城市是城市 $3$；
- 城市 $3$ 的最近城市是城市 $4$；
- 城市 $4$ 的最近城市是城市 $3$；
- 城市 $5$ 的最近城市是城市 $4$。

城市的位置保证每个城市的最近城市是唯一的。例如，不可能有城市位于 $[1, 2, 3]$，因为这意味着城市 $2$ 有两个最近城市（$1$ 和 $3$，距离均为 $1$）。

你可以在城市之间旅行。假设你当前在城市 $x$，那么你可以执行以下操作之一：

- 旅行到任何其他城市 $y$，支付 $|a_x - a_y|$ 个硬币；
- 旅行到 $x$ 的最近城市，支付 $1$ 个硬币。

给定 $m$ 个查询，每个查询给出两个城市，要求计算从一个城市到另一个城市所需的最小硬币数。

### 题解分析与结论

各题解的思路基本一致，核心是通过预处理每个城市的最近城市，然后使用前缀和或后缀和来计算从一个城市到另一个城市的最小花费。难点在于如何高效地预处理最近城市，并在查询时快速计算最小花费。

#### 关键思路与技巧
1. **预处理最近城市**：对于每个城市，比较其与左右相邻城市的距离，确定最近城市。
2. **前缀和与后缀和**：分别从左到右和从右到左计算每个城市的最小花费，使用前缀和和后缀和来快速回答查询。
3. **贪心策略**：在旅行时，优先选择花费最小的路径，即尽可能使用花费为1的旅行方式。

#### 评分较高的题解

1. **作者：__zhuruirong__ (4星)**
   - **关键亮点**：通过预处理最近城市，并使用前缀和和后缀和来快速回答查询，代码简洁且高效。
   - **核心代码**：
     ```cpp
     for(int i = 1; i <= n; i++) {
         if(i == 1) nxt[i] = 2;
         else if(i == n) nxt[i] = n - 1;
         else if(a[i] - a[i - 1] < a[i + 1] - a[i]) nxt[i] = i - 1;
         else nxt[i] = i + 1;
     }
     for(int i = 1; i <= n; i++) {
         if(nxt[i] == i + 1) pre[i + 1] = pre[i] + 1;
         else pre[i + 1] = pre[i] + (a[i + 1] - a[i]);
     }
     for(int i = n; i >= 1; i--) {
         if(nxt[i] == i - 1) suf[i - 1] = suf[i] + 1;
         else suf[i - 1] = suf[i] + (a[i] - a[i - 1]);
     }
     ```

2. **作者：MhxMa (4星)**
   - **关键亮点**：通过预处理最近城市，并使用前缀和和后缀和来快速回答查询，代码结构清晰，易于理解。
   - **核心代码**：
     ```cpp
     pre[0] = 0;
     pre[1] = 1;
     for (int i = 2; i < n; i++) {
         pre[i] = (abs(arr[i - 1] - arr[i - 2]) > abs(arr[i - 1] - arr[i])) ?
                     pre[i - 1] + 1 :
                     pre[i - 1] + abs(arr[i - 1] - arr[i]);
     }
     suff[n - 1] = 0;
     suff[n - 2] = 1;
     for (int i = n - 3; i >= 0; i--) {
         suff[i] = (abs(arr[i + 1] - arr[i]) > abs(arr[i + 1] - arr[i + 2])) ?
                     suff[i + 1] + abs(arr[i + 1] - arr[i]) :
                     suff[i + 1] + 1;
     }
     ```

3. **作者：Crazyouth (4星)**
   - **关键亮点**：通过预处理最近城市，并使用前缀和和后缀和来快速回答查询，代码简洁且高效。
   - **核心代码**：
     ```cpp
     for(int i = 2; i <= n; i++) sum1[i] = sum1[i - 1] + (nc[i - 1] == i ? 1 : abs(a[i - 1] - a[i]));
     for(int i = n - 1; i; i--) sum2[i] = sum2[i + 1] + (nc[i + 1] == i ? 1 : abs(a[i + 1] - a[i]));
     ```

### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 【模板】线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)

这些题目都涉及预处理和前缀和/后缀和的应用，适合进一步巩固相关算法技巧。

---
处理用时：47.29秒