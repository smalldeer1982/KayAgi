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

### 题目内容重写

#### 题目描述

有 $n$ 个城市位于数轴上，第 $i$ 个城市位于点 $a_i$。城市坐标按升序给出，即 $a_1 < a_2 < \dots < a_n$。

两个城市 $x$ 和 $y$ 之间的距离等于 $|a_x - a_y|$。

对于每个城市 $i$，定义其最近城市 $j$ 为与 $i$ 的距离不大于与任何其他城市 $k$ 的距离的城市。例如，如果城市位于点 $[0, 8, 12, 15, 20]$，则：

- 城市 $1$ 的最近城市是城市 $2$；
- 城市 $2$ 的最近城市是城市 $3$；
- 城市 $3$ 的最近城市是城市 $4$；
- 城市 $4$ 的最近城市是城市 $3$；
- 城市 $5$ 的最近城市是城市 $4$。

城市的分布使得每个城市的最近城市是唯一的。例如，城市不可能位于点 $[1, 2, 3]$，因为这意味着城市 $2$ 有两个最近城市（$1$ 和 $3$，距离均为 $1$）。

你可以在城市之间旅行。假设你当前在城市 $x$，则可以执行以下操作之一：

- 旅行到任何其他城市 $y$，支付 $|a_x - a_y|$ 个硬币；
- 旅行到 $x$ 的最近城市，支付 $1$ 个硬币。

给定 $m$ 个查询。在每个查询中，给出两个城市，要求计算从一个城市到另一个城市所需支付的最小硬币数。

#### 说明/提示

考虑样例中的前两个查询：

- 在第一个查询中，你初始位于城市 $1$。你可以旅行到最近城市（城市 $2$），支付 $1$ 个硬币。然后再次旅行到最近城市（城市 $3$），支付 $1$ 个硬币。接着再次旅行到最近城市（城市 $4$），支付 $1$ 个硬币。总共支付 $3$ 个硬币，从城市 $1$ 到城市 $4$；
- 在第二个查询中，你可以使用相同的方式从城市 $1$ 到城市 $4$，然后支付 $5$ 个硬币从城市 $4$ 到城市 $5$。

#### 样例 #1

##### 输入

```
1
5
0 8 12 15 20
5
1 4
1 5
3 4
3 2
5 1
```

##### 输出

```
3
8
1
4
14
```

### 题解分析与结论

#### 题解对比

1. **思路与算法要点**：
   - 所有题解的核心思路都是通过预处理每个城市的最近城市，然后使用前缀和或后缀和来计算从一个城市到另一个城市的最小花费。
   - 大多数题解都采用了从左到右和从右到左两次遍历，分别计算前缀和和后缀和，然后根据查询的起点和终点选择使用哪个数组来计算结果。
   - 难点在于如何高效地预处理每个城市的最近城市，并确保前缀和和后缀和的正确性。

2. **解决难点**：
   - 预处理最近城市时，需要考虑边界条件（如第一个和最后一个城市）。
   - 前缀和和后缀和的计算需要根据最近城市的选择来决定是加1还是加实际距离。

3. **优化程度**：
   - 大多数题解的时间复杂度为 $O(n + m)$，其中 $n$ 是城市数量，$m$ 是查询数量，这是最优的复杂度。
   - 代码实现上，部分题解使用了更简洁的逻辑和更少的变量，提高了代码的可读性。

#### 评分较高的题解

1. **作者：__zhuruirong__ (4星)**
   - **关键亮点**：代码简洁，逻辑清晰，预处理和前缀和的计算都处理得很好。
   - **代码核心**：
     ```cpp
     for(int i = 1; i <= n; i++) {
         if(i == 1)
             nxt[i] = 2;
         else if(i == n)
             nxt[i] = n - 1;
         else
             if(a[i] - a[i - 1] < a[i + 1] - a[i])
                 nxt[i] = i - 1;
             else
                 nxt[i] = i + 1;
     }
     for(int i = 1; i <= n; i++)
         if(nxt[i] == i + 1)
             pre[i + 1] = pre[i] + 1;
         else
             pre[i + 1] = pre[i] + (a[i + 1] - a[i]);
     ```

2. **作者：MhxMa (4星)**
   - **关键亮点**：代码结构清晰，预处理和前缀和的计算逻辑明确，边界条件处理得当。
   - **代码核心**：
     ```cpp
     for(int i = 2; i < n; i++) {
         pre[i] = (abs(arr[i - 1] - arr[i - 2]) > abs(arr[i - 1] - arr[i])) ?
                     pre[i - 1] + 1 :
                     pre[i - 1] + abs(arr[i - 1] - arr[i]);
     }
     for(int i = n - 3; i >= 0; i--) {
         suff[i] = (abs(arr[i + 1] - arr[i]) > abs(arr[i + 1] - arr[i + 2])) ?
                     suff[i + 1] + abs(arr[i + 1] - arr[i]) :
                     suff[i + 1] + 1;
     }
     ```

3. **作者：Crazyouth (4星)**
   - **关键亮点**：代码简洁，预处理和前缀和的计算逻辑清晰，边界条件处理得当。
   - **代码核心**：
     ```cpp
     for(int i = 2; i <= n; i++) sum1[i] = sum1[i - 1] + (nc[i - 1] == i ? 1 : abs(a[i - 1] - a[i]));
     for(int i = n - 1; i; i--) sum2[i] = sum2[i + 1] + (nc[i + 1] == i ? 1 : abs(a[i + 1] - a[i]));
     ```

#### 最优关键思路

- **预处理最近城市**：通过比较左右相邻城市的距离，确定每个城市的最近城市。
- **前缀和与后缀和**：分别从左到右和从右到左计算前缀和和后缀和，根据查询的起点和终点选择使用哪个数组来计算结果。

#### 可拓展之处

- 类似的问题可以扩展到二维或更高维的空间，使用类似的预处理和前缀和技巧。
- 可以结合图论中的最短路径算法，如Dijkstra算法，来解决更复杂的旅行问题。

#### 推荐题目

1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P3372 线段树 1](https://www.luogu.com.cn/problem/P3372)
3. [P3368 树状数组 2](https://www.luogu.com.cn/problem/P3368)

#### 个人心得摘录

- **作者：nyC20**：在实现前缀和时，发现正向和反向的花费并不一样，因此需要两个前缀和数组来分别处理。
- **作者：UncleSam_Died**：贪心策略能走距离最短的城市就一定走，这样可以减少计算量。

### 结论

通过预处理每个城市的最近城市，并使用前缀和与后缀和来计算最小花费，是解决该问题的关键思路。大多数题解都采用了这一方法，并在代码实现上进行了优化，使得算法的时间复杂度达到最优。

---
处理用时：61.89秒