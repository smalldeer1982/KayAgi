# 题目信息

# K for the Price of One (Easy Version)

## 题目描述

This is the easy version of this problem. The only difference is the constraint on $ k $ — the number of gifts in the offer. In this version: $ k=2 $ .

Vasya came to the store to buy goods for his friends for the New Year. It turned out that he was very lucky — today the offer " $ k $ of goods for the price of one" is held in store. Remember, that in this problem $ k=2 $ .

Using this offer, Vasya can buy exactly $ k $ of any goods, paying only for the most expensive of them. Vasya decided to take this opportunity and buy as many goods as possible for his friends with the money he has.

More formally, for each good, its price is determined by $ a_i $ — the number of coins it costs. Initially, Vasya has $ p $ coins. He wants to buy the maximum number of goods. Vasya can perform one of the following operations as many times as necessary:

- Vasya can buy one good with the index $ i $ if he currently has enough coins (i.e $ p \ge a_i $ ). After buying this good, the number of Vasya's coins will decrease by $ a_i $ , (i.e it becomes $ p := p - a_i $ ).
- Vasya can buy a good with the index $ i $ , and also choose exactly $ k-1 $ goods, the price of which does not exceed $ a_i $ , if he currently has enough coins (i.e $ p \ge a_i $ ). Thus, he buys all these $ k $ goods, and his number of coins decreases by $ a_i $ (i.e it becomes $ p := p - a_i $ ).

Please note that each good can be bought no more than once.

For example, if the store now has $ n=5 $ goods worth $ a_1=2, a_2=4, a_3=3, a_4=5, a_5=7 $ , respectively, $ k=2 $ , and Vasya has $ 6 $ coins, then he can buy $ 3 $ goods. A good with the index $ 1 $ will be bought by Vasya without using the offer and he will pay $ 2 $ coins. Goods with the indices $ 2 $ and $ 3 $ Vasya will buy using the offer and he will pay $ 4 $ coins. It can be proved that Vasya can not buy more goods with six coins.

Help Vasya to find out the maximum number of goods he can buy.

## 样例 #1

### 输入

```
6
5 6 2
2 4 3 5 7
5 11 2
2 4 3 5 7
2 10000 2
10000 10000
2 9999 2
10000 10000
5 13 2
8 2 8 2 5
3 18 2
1 2 3
```

### 输出

```
3
4
2
0
4
3
```

# AI分析结果

### 题目内容重写

#### K for the Price of One (Easy Version)

#### 题目描述

这是该问题的简单版本。唯一的区别是对 $k$ 的约束——即优惠中的商品数量。在这个版本中：$k=2$。

Vasya 来到商店为他的朋友们购买新年礼物。他非常幸运，因为今天商店有一个“买 $k$ 件商品，只需支付其中最贵的一件的价格”的优惠活动。记住，在这个问题中 $k=2$。

利用这个优惠，Vasya 可以购买恰好 $k$ 件商品，只需支付其中最贵的一件的价格。Vasya 决定利用这个机会，用他现有的钱为朋友们购买尽可能多的商品。

更正式地说，每件商品的价格由 $a_i$ 决定，表示它需要花费的硬币数量。最初，Vasya 有 $p$ 枚硬币。他希望购买尽可能多的商品。Vasya 可以根据需要多次执行以下操作之一：

- Vasya 可以购买一件索引为 $i$ 的商品，前提是他当前有足够的硬币（即 $p \ge a_i$）。购买这件商品后，Vasya 的硬币数量将减少 $a_i$（即 $p := p - a_i$）。
- Vasya 可以购买一件索引为 $i$ 的商品，并选择恰好 $k-1$ 件价格不超过 $a_i$ 的商品，前提是他当前有足够的硬币（即 $p \ge a_i$）。因此，他购买了这 $k$ 件商品，他的硬币数量将减少 $a_i$（即 $p := p - a_i$）。

请注意，每件商品最多只能购买一次。

例如，如果商店现在有 $n=5$ 件商品，价格分别为 $a_1=2, a_2=4, a_3=3, a_4=5, a_5=7$，$k=2$，且 Vasya 有 $6$ 枚硬币，那么他可以购买 $3$ 件商品。Vasya 将不使用优惠购买索引为 $1$ 的商品，并支付 $2$ 枚硬币。Vasya 将使用优惠购买索引为 $2$ 和 $3$ 的商品，并支付 $4$ 枚硬币。可以证明，Vasya 无法用 $6$ 枚硬币购买更多的商品。

帮助 Vasya 找出他可以购买的最大商品数量。

### 算法分类
动态规划

### 题解分析与结论

#### 综合分析
本题的核心是通过动态规划来求解在给定预算下，利用优惠购买尽可能多的商品。大多数题解都采用了动态规划的思路，通过定义状态转移方程来计算购买前 $i$ 件商品的最小花费，并最终找到在预算内能购买的最大商品数量。

#### 最优关键思路
1. **排序**：首先对商品价格进行排序，确保优先购买价格较低的商品。
2. **状态转移**：定义 $dp_i$ 为购买前 $i$ 件商品的最小花费。状态转移方程为：
   - 如果 $i \ge k$，则 $dp_i = \min(dp_i, dp_{i-k} + a_i)$。
   - 否则，$dp_i = dp_{i-1} + a_i$。
3. **结果查找**：从后向前遍历 $dp$ 数组，找到第一个 $dp_i \le p$ 的 $i$ 即为最大购买数量。

#### 推荐题解
1. **作者：alan1118**
   - **星级**：4
   - **关键亮点**：思路清晰，代码简洁，直接使用动态规划求解，状态转移方程明确。
   - **代码核心**：
     ```cpp
     for(int i = 1; i <= n; i++) {
         if(i >= 2) dp[i] = min(dp[i], dp[i-2] + a[i]);
         else dp[i] = min(dp[i], dp[i-1] + a[i]);
     }
     ```

2. **作者：SnapYust**
   - **星级**：4
   - **关键亮点**：详细推导了状态转移方程，并进行了空间优化，将二维 DP 优化为一维。
   - **代码核心**：
     ```cpp
     dp[1] = a[1];
     for(int i = 2; i <= n; i++) {
         dp[i] = min(dp[i-1], dp[i-2]) + a[i];
     }
     ```

3. **作者：liuyz11**
   - **星级**：4
   - **关键亮点**：使用了二维 DP 状态，思路清晰，代码可读性强。
   - **代码核心**：
     ```cpp
     dp[i][0] = dp[i-1][1];
     dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + a[i];
     ```

#### 个人心得
- **调试经历**：部分题解提到在初始状态转移时容易忽略边界条件，导致结果错误。通过仔细推导和调试，最终找到了正确的状态转移方程。
- **顿悟感想**：通过排序和动态规划的结合，能够有效地解决这类优化问题，尤其是在涉及优惠活动时，动态规划的状态转移方程设计是关键。

### 推荐题目
1. [CF1282B2 K for the Price of One (Hard Version)](https://www.luogu.com.cn/problem/CF1282B2)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

---
处理用时：40.56秒