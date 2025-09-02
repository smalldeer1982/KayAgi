# 题目信息

# RationalLee

## 题目描述

Lee just became Master in Codeforces, and so, he went out to buy some gifts for his friends. He bought $ n $ integers, now it's time to distribute them between his friends rationally...

Lee has $ n $ integers $ a_1, a_2, \ldots, a_n $ in his backpack and he has $ k $ friends. Lee would like to distribute all integers in his backpack between his friends, such that the $ i $ -th friend will get exactly $ w_i $ integers and each integer will be handed over to exactly one friend.

Let's define the happiness of a friend as the sum of the maximum and the minimum integer he'll get.

Lee would like to make his friends as happy as possible, in other words, he'd like to maximize the sum of friends' happiness. Now he asks you to calculate the maximum sum of friends' happiness.

## 说明/提示

In the first test case, Lee should give the greatest integer to the first friend (his happiness will be $ 17 + 17 $ ) and remaining integers to the second friend (his happiness will be $ 13 + 1 $ ).

In the second test case, Lee should give $ \{10, 10, 11\} $ to the first friend and to the second friend, so the total happiness will be equal to $ (11 + 10) + (11 + 10) $

In the third test case, Lee has four friends and four integers, it doesn't matter how he distributes the integers between his friends.

## 样例 #1

### 输入

```
3
4 2
1 13 7 17
1 3
6 2
10 10 10 10 11 11
3 3
4 4
1000000000 1000000000 1000000000 1000000000
1 1 1 1```

### 输出

```
48
42
8000000000```

# AI分析结果

### 题目内容重写

#### 题目描述

Lee 刚刚在 Codeforces 上成为了 Master，于是他决定出去为他的朋友们买一些礼物。他买了 $n$ 个整数，现在需要将这些整数合理地分配给他的朋友们。

Lee 的背包里有 $n$ 个整数 $a_1, a_2, \ldots, a_n$，他有 $k$ 个朋友。Lee 希望将这些整数全部分配给他的朋友们，使得第 $i$ 个朋友恰好得到 $w_i$ 个整数，并且每个整数只能分配给一个朋友。

定义一个朋友的幸福度为他所得到的整数中的最大值与最小值的和。

Lee 希望让他的朋友们尽可能幸福，换句话说，他希望最大化所有朋友的幸福度之和。现在他请你计算这个最大幸福度之和。

#### 说明/提示

在第一个测试用例中，Lee 应该将最大的整数分配给第一个朋友（他的幸福度为 $17 + 17$），并将剩余的整数分配给第二个朋友（他的幸福度为 $13 + 1$）。

在第二个测试用例中，Lee 应该将 $\{10, 10, 11\}$ 分配给第一个朋友，将 $\{10, 10, 11\}$ 分配给第二个朋友，因此总幸福度为 $(11 + 10) + (11 + 10)$。

在第三个测试用例中，Lee 有四个朋友和四个整数，无论他如何分配这些整数，结果都是一样的。

#### 样例 #1

##### 输入

```
3
4 2
1 13 7 17
1 3
6 2
10 10 10 10 11 11
3 3
4 4
1000000000 1000000000 1000000000 1000000000
1 1 1 1
```

##### 输出

```
48
42
8000000000
```

### 算法分类

贪心

### 题解分析与结论

#### 题解对比

1. **budaiyanjing 的题解**
   - **思路**：将前 $k$ 大的数单独分配给每个朋友作为最大值，并尽可能优先分配给 $w_i$ 较小的朋友，这样这些数可能同时作为最大值和最小值，产生双倍贡献。然后从最小值开始分配，优先将小的值分配给 $w_i$ 较大的朋友，以快速跳过较小的值，使后面的朋友的最小值尽可能大。
   - **难点**：如何合理分配最大值和最小值，使得总幸福度最大化。
   - **评分**：4星
   - **关键亮点**：通过排序和贪心策略，合理分配最大值和最小值，确保总幸福度最大化。

2. **JWRuixi 的题解**
   - **思路**：将前 $m$ 大的数作为每个朋友的最大值，然后按 $b_i$ 从大到小分配最小值，每次选择一个长度为 $b_i$ 的连续段。
   - **难点**：如何确保最小值的选择不影响总幸福度。
   - **评分**：3星
   - **关键亮点**：通过排序和贪心策略，确保最大值和最小值的合理分配。

3. **11D_Beyonder 的题解**
   - **思路**：将最大的 $k$ 个数分配给每个朋友作为最大值，然后将最小的 $k$ 个数分配给 $w_i > 1$ 的朋友作为最小值，中间用较小的数填充。
   - **难点**：如何确保最小值的选择不影响总幸福度。
   - **评分**：3星
   - **关键亮点**：通过排序和贪心策略，确保最大值和最小值的合理分配。

#### 最优关键思路

- **排序**：首先对数组 $a$ 和 $w$ 进行排序，确保最大值和最小值的合理分配。
- **贪心策略**：将前 $k$ 大的数分配给每个朋友作为最大值，并尽可能优先分配给 $w_i$ 较小的朋友，以产生双倍贡献。然后从最小值开始分配，优先将小的值分配给 $w_i$ 较大的朋友，以快速跳过较小的值，使后面的朋友的最小值尽可能大。

#### 可拓展之处

- **类似问题**：在分配问题中，如何通过贪心策略最大化或最小化某种指标，如幸福度、成本等。
- **算法套路**：排序 + 贪心策略，适用于许多优化问题。

#### 推荐题目

1. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

### 所选高分题解

#### budaiyanjing 的题解

- **星级**：4星
- **关键亮点**：通过排序和贪心策略，合理分配最大值和最小值，确保总幸福度最大化。
- **核心代码**：
  ```cpp
  i64 ans = 0;
  for (int i = n, j = 1; j <= k; i -- , j ++ ) {
      ans += a[i];
      if (! -- b[j]) ans += a[i];
  } 

  for (int i = k, j = 1; i; i -- ) 
      if (b[i]) ans += a[j], j += b[i];
  ```
  - **实现思想**：首先将前 $k$ 大的数分配给每个朋友作为最大值，并检查是否可以作为最小值。然后从最小值开始分配，优先将小的值分配给 $w_i$ 较大的朋友。

---
处理用时：35.67秒