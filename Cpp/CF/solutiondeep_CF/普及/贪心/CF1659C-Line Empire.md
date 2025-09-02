# 题目信息

# Line Empire

## 题目描述

You are an ambitious king who wants to be the Emperor of The Reals. But to do that, you must first become Emperor of The Integers.

Consider a number axis. The capital of your empire is initially at $ 0 $ . There are $ n $ unconquered kingdoms at positions $ 0<x_1<x_2<\ldots<x_n $ . You want to conquer all other kingdoms.

There are two actions available to you:

- You can change the location of your capital (let its current position be $ c_1 $ ) to any other conquered kingdom (let its position be $ c_2 $ ) at a cost of $ a\cdot |c_1-c_2| $ .
- From the current capital (let its current position be $ c_1 $ ) you can conquer an unconquered kingdom (let its position be $ c_2 $ ) at a cost of $ b\cdot |c_1-c_2| $ . You cannot conquer a kingdom if there is an unconquered kingdom between the target and your capital.

Note that you cannot place the capital at a point without a kingdom. In other words, at any point, your capital can only be at $ 0 $ or one of $ x_1,x_2,\ldots,x_n $ . Also note that conquering a kingdom does not change the position of your capital.

Find the minimum total cost to conquer all kingdoms. Your capital can be anywhere at the end.

## 说明/提示

Here is an optimal sequence of moves for the second test case:

1. Conquer the kingdom at position $ 1 $ with cost $ 3\cdot(1-0)=3 $ .
2. Move the capital to the kingdom at position $ 1 $ with cost $ 6\cdot(1-0)=6 $ .
3. Conquer the kingdom at position $ 5 $ with cost $ 3\cdot(5-1)=12 $ .
4. Move the capital to the kingdom at position $ 5 $ with cost $ 6\cdot(5-1)=24 $ .
5. Conquer the kingdom at position $ 6 $ with cost $ 3\cdot(6-5)=3 $ .
6. Conquer the kingdom at position $ 21 $ with cost $ 3\cdot(21-5)=48 $ .
7. Conquer the kingdom at position $ 30 $ with cost $ 3\cdot(30-5)=75 $ .

The total cost is $ 3+6+12+24+3+48+75=171 $ . You cannot get a lower cost than this.

## 样例 #1

### 输入

```
4
5 2 7
3 5 12 13 21
5 6 3
1 5 6 21 30
2 9 3
10 15
11 27182 31415
16 18 33 98 874 989 4848 20458 34365 38117 72030```

### 输出

```
173
171
75
3298918744```

# AI分析结果

### 题目内容重写（中文）

你是一位雄心勃勃的国王，想要成为实数领域的皇帝。但在此之前，你必须先成为整数领域的皇帝。

考虑一个数轴。你的帝国首都最初位于 $0$。有 $n$ 个未被征服的王国，位置分别为 $0 < x_1 < x_2 < \ldots < x_n$。你想要征服所有其他王国。

你可以执行以下两种操作：

1. 你可以将首都的位置从当前位置 $c_1$ 迁移到任何已被征服的王国位置 $c_2$，代价为 $a \cdot |c_1 - c_2|$。
2. 从当前首都位置 $c_1$，你可以征服一个未被征服的王国 $c_2$，代价为 $b \cdot |c_1 - c_2|$。你不能征服一个王国，如果目标王国与首都之间有其他未被征服的王国。

注意，你不能将首都放在没有王国的位置。换句话说，任何时候，首都只能位于 $0$ 或 $x_1, x_2, \ldots, x_n$ 中的一个位置。另外，征服一个王国不会改变首都的位置。

找到征服所有王国的最小总代价。最终首都可以位于任意位置。

### 样例

#### 输入

```
4
5 2 7
3 5 12 13 21
5 6 3
1 5 6 21 30
2 9 3
10 15
11 27182 31415
16 18 33 98 874 989 4848 20458 34365 38117 72030
```

#### 输出

```
173
171
75
3298918744
```

### 题解分析与结论

#### 综合分析

该问题的核心在于如何选择是否迁移首都，以最小化征服所有王国的总代价。所有题解都基于贪心策略，即在每一步选择是否迁移首都，以最小化当前和未来的代价。

#### 最优关键思路

1. **贪心策略**：在每一步征服一个王国后，判断是否迁移首都。迁移首都的代价与未来征服其他王国的代价之间存在权衡。
2. **前缀和优化**：通过前缀和快速计算未来征服所有王国的代价，避免重复计算。
3. **动态规划思想**：虽然题解中没有明确使用动态规划，但通过逐步更新当前首都位置和总代价，实际上是一种动态规划的思路。

#### 推荐题解

1. **作者：Engulf (4星)**
   - **关键亮点**：通过前缀和优化计算未来征服代价，代码简洁且高效。
   - **核心代码**：
     ```cpp
     int so1ve() {
         for (int i = 1; i <= n; i ++ ) sum[i] = 0;
         cin >> n >> a >> b;
         for (int i = 1; i <= n; i ++ ) cin >> x[i], sum[i] = sum[i - 1] + x[i];
         int cap = 0, ans = 0;
         for (int i = 1; i <= n; i ++ ) {
             ans += b * (x[i] - cap);
             int t1 = b * (query(i + 1, n) - cap * (n - i));
             int t2 = a * (x[i] - cap) + b * (query(i + 1, n) - x[i] * (n - i));
             if (t2 < t1) ans += a * (x[i] - cap), cap = x[i];
         }
         return ans;
     }
     ```
   - **核心思想**：在每一步征服王国后，计算不迁移和迁移首都的代价，选择代价较小的方案。

2. **作者：rmzls (4星)**
   - **关键亮点**：通过简化条件判断是否迁移首都，代码简洁且易于理解。
   - **核心代码**：
     ```cpp
     for (int i = 1; i <= n; i++) {
         ans += b * (abs(dis - cap));
         if (b * (n - i) > a) {
             ans += a * (abs(dis - cap));
             cap = dis;
         }
     }
     ```
   - **核心思想**：通过判断 $b \times (n - i) > a$ 来决定是否迁移首都，简化了计算。

3. **作者：happy_dengziyue (4星)**
   - **关键亮点**：通过枚举首都位置，计算最小代价，思路清晰。
   - **核心代码**：
     ```cpp
     for (int i = n - 1; i >= 0; --i) ans = mi(ans, (s[0] - s[i]) * (a + b) + s2[i] * b);
     ```
   - **核心思想**：枚举首都位置，计算每种情况下的总代价，取最小值。

### 扩展思路与推荐题目

1. **扩展思路**：该问题可以扩展到多维空间，或者考虑更复杂的迁移和征服代价函数。类似的问题还可以考虑动态规划或图论中的最短路径算法。
2. **推荐题目**：
   - [P1040 加分二叉树](https://www.luogu.com.cn/problem/P1040)
   - [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)
   - [P1541 乌龟棋](https://www.luogu.com.cn/problem/P1541)

---
处理用时：39.18秒