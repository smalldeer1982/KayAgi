# 题目信息

# Pokémon Army (easy version)

## 题目描述

This is the easy version of the problem. The difference between the versions is that the easy version has no swap operations. You can make hacks only if all versions of the problem are solved.

Pikachu is a cute and friendly pokémon living in the wild pikachu herd.

But it has become known recently that infamous team R wanted to steal all these pokémon! Pokémon trainer Andrew decided to help Pikachu to build a pokémon army to resist.

First, Andrew counted all the pokémon — there were exactly $ n $ pikachu. The strength of the $ i $ -th pokémon is equal to $ a_i $ , and all these numbers are distinct.

As an army, Andrew can choose any non-empty subsequence of pokemons. In other words, Andrew chooses some array $ b $ from $ k $ indices such that $ 1 \le b_1 < b_2 < \dots < b_k \le n $ , and his army will consist of pokémons with forces $ a_{b_1}, a_{b_2}, \dots, a_{b_k} $ .

The strength of the army is equal to the alternating sum of elements of the subsequence; that is, $ a_{b_1} - a_{b_2} + a_{b_3} - a_{b_4} + \dots $ .

Andrew is experimenting with pokémon order. He performs $ q $ operations. In $ i $ -th operation Andrew swaps $ l_i $ -th and $ r_i $ -th pokémon.

Note: $ q=0 $ in this version of the task.

Andrew wants to know the maximal stregth of the army he can achieve with the initial pokémon placement. He also needs to know the maximal strength after each operation.

Help Andrew and the pokémon, or team R will realize their tricky plan!

## 说明/提示

In third test case we can build an army in such way: \[1 2 5 4 3 6 7\], its strength will be $ 5−3+7=9 $ .

## 样例 #1

### 输入

```
3
3 0
1 3 2
2 0
1 2
7 0
1 2 5 4 3 6 7```

### 输出

```
3
2
9```

# AI分析结果

### 题目内容重写
# Pokémon Army (简单版)

## 题目描述

这是该问题的简单版本。不同版本之间的区别在于，简单版本没有交换操作。只有当所有版本的问题都被解决时，你才能进行hack。

皮卡丘是一种可爱且友好的宝可梦，生活在野外的皮卡丘群中。

但最近，臭名昭著的R团队想要偷走所有这些宝可梦！宝可梦训练师Andrew决定帮助皮卡丘组建一支宝可梦军队来抵抗。

首先，Andrew统计了所有的宝可梦——总共有$n$只皮卡丘。第$i$只宝可梦的强度为$a_i$，且所有这些数字都是不同的。

作为一支军队，Andrew可以选择任何非空的宝可梦子序列。换句话说，Andrew选择一个包含$k$个索引的数组$b$，使得$1 \le b_1 < b_2 < \dots < b_k \le n$，他的军队将由强度为$a_{b_1}, a_{b_2}, \dots, a_{b_k}$的宝可梦组成。

军队的强度等于子序列元素的交替和；即$a_{b_1} - a_{b_2} + a_{b_3} - a_{b_4} + \dots$。

Andrew正在实验宝可梦的顺序。他执行$q$次操作。在第$i$次操作中，Andrew交换第$l_i$和第$r_i$只宝可梦。

注意：在这个版本的任务中，$q=0$。

Andrew想知道在初始宝可梦排列下，他可以达到的最大军队强度。他还需要知道每次操作后的最大强度。

帮助Andrew和宝可梦，否则R团队将实现他们的狡猾计划！

## 说明/提示

在第三个测试用例中，我们可以这样组建军队：[1 2 5 4 3 6 7]，其强度将为$5−3+7=9$。

## 样例 #1

### 输入

```
3
3 0
1 3 2
2 0
1 2
7 0
1 2 5 4 3 6 7```

### 输出

```
3
2
9```

### 算法分类
动态规划

### 题解分析与结论
本题的核心是求一个子序列的交替和的最大值。由于子序列的选择是任意的，且需要交替加减，因此可以通过动态规划来解决。大部分题解都采用了动态规划的思路，定义状态$dp[i][0/1]$表示前$i$个元素中，第$i$个元素被选为减或加时的最大交替和。状态转移方程为：
- $dp[i][0] = \max(dp[i-1][0], dp[i-1][1] - a[i])$
- $dp[i][1] = \max(dp[i-1][1], dp[i-1][0] + a[i])$

最终答案为$\max(dp[n][0], dp[n][1])$。

### 高星题解推荐
1. **作者：Need_No_Name (5星)**
   - **关键亮点**：清晰地定义了状态转移方程，代码简洁且易于理解。作者还提到了记忆化搜索的尝试，虽然最终选择了动态规划，但展示了思考过程。
   - **代码核心**：
     ```cpp
     dp[i][0] = max(dp[i-1][0], dp[i-1][1] - num[i]);
     dp[i][1] = max(dp[i-1][1], dp[i-1][0] + num[i]);
     ```

2. **作者：STDquantum (4星)**
   - **关键亮点**：提供了两种解法，一种是动态规划，另一种是通过波峰波谷的贪心策略。第二种解法虽然与本题不直接相关，但为后续的hard版本提供了思路。
   - **代码核心**：
     ```cpp
     f[0] = max(f[1] - x, f[0]);
     f[1] = max(f[0] + x, f[1]);
     ```

3. **作者：忘怀星 (4星)**
   - **关键亮点**：通过优化状态定义，减少了空间复杂度，使用了类似于滚动数组的技巧，提升了代码效率。
   - **代码核心**：
     ```cpp
     f = max(a_i, f, a_i + g);
     g = max(g, f - a_i);
     ```

### 最优关键思路
动态规划是解决本题的核心方法，通过定义状态$dp[i][0/1]$来表示前$i$个元素中第$i$个元素被选为减或加时的最大交替和，状态转移方程清晰且易于实现。此外，使用滚动数组可以进一步优化空间复杂度。

### 可拓展之处
本题的hard版本涉及到交换操作，可以通过维护波峰波谷的动态信息来解决。类似的问题还可以扩展到其他子序列问题，如最长递增子序列等。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1280 尼克的任务](https://www.luogu.com.cn/problem/P1280)

---
处理用时：40.30秒