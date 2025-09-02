# 题目信息

# K for the Price of One (Hard Version)

## 题目描述

This is the hard version of this problem. The only difference is the constraint on $ k $ — the number of gifts in the offer. In this version: $ 2 \le k \le n $ .

Vasya came to the store to buy goods for his friends for the New Year. It turned out that he was very lucky — today the offer " $ k $ of goods for the price of one" is held in store.

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
8
5 6 2
2 4 3 5 7
5 11 2
2 4 3 5 7
3 2 3
4 2 6
5 2 3
10 1 3 9 2
2 10000 2
10000 10000
2 9999 2
10000 10000
4 6 4
3 2 3 2
5 5 3
1 2 2 1 2
```

### 输出

```
3
4
1
1
2
0
4
5
```

# AI分析结果

### 题目内容重写（中文）

#### 题目描述

这是该问题的困难版本。唯一的区别在于对 $k$ 的约束——即优惠中的礼物数量。在这个版本中：$2 \le k \le n$。

Vasya 来到商店为他的朋友们购买新年礼物。他非常幸运——今天商店正在举行“买 $k$ 件商品，只需支付其中最贵的一件的价格”的优惠活动。

利用这个优惠，Vasya 可以购买恰好 $k$ 件任意商品，只需支付其中最贵的一件的价格。Vasya 决定抓住这个机会，用他现有的钱为朋友们购买尽可能多的商品。

更正式地说，每件商品的价格由 $a_i$ 决定——即它需要的硬币数量。最初，Vasya 有 $p$ 枚硬币。他想要购买尽可能多的商品。Vasya 可以根据需要执行以下操作之一：

- Vasya 可以购买一件索引为 $i$ 的商品，前提是他当前有足够的硬币（即 $p \ge a_i$）。购买这件商品后，Vasya 的硬币数量将减少 $a_i$（即 $p := p - a_i$）。
- Vasya 可以购买一件索引为 $i$ 的商品，并选择恰好 $k-1$ 件价格不超过 $a_i$ 的商品，前提是他当前有足够的硬币（即 $p \ge a_i$）。这样，他将购买所有这些 $k$ 件商品，并且他的硬币数量将减少 $a_i$（即 $p := p - a_i$）。

请注意，每件商品最多只能购买一次。

例如，如果商店现在有 $n=5$ 件商品，价格分别为 $a_1=2, a_2=4, a_3=3, a_4=5, a_5=7$，$k=2$，并且 Vasya 有 $6$ 枚硬币，那么他可以购买 $3$ 件商品。索引为 $1$ 的商品将被 Vasya 不使用优惠购买，他将支付 $2$ 枚硬币。索引为 $2$ 和 $3$ 的商品将被 Vasya 使用优惠购买，他将支付 $4$ 枚硬币。可以证明，Vasya 无法用 $6$ 枚硬币购买更多的商品。

请帮助 Vasya 找出他可以购买的最大商品数量。

### 算法分类
贪心、动态规划

### 题解分析与结论

本题的核心在于如何利用优惠策略最大化购买商品的数量。大多数题解采用了贪心+动态规划的思路，具体步骤如下：

1. **排序**：首先将商品按价格从小到大排序，确保优先购买价格较低的商品。
2. **动态规划**：定义 $dp_i$ 表示购买前 $i$ 件商品所需的最小花费。状态转移方程如下：
   - 如果 $i < k$，则 $dp_i = dp_{i-1} + a_i$。
   - 如果 $i \ge k$，则 $dp_i = dp_{i-k} + a_i$。
3. **枚举答案**：从后向前枚举 $dp_i$，找到第一个满足 $dp_i \le p$ 的 $i$，即为最大购买数量。

### 精选题解

#### 题解1：作者：Rex01 (赞：3)
**星级：4.5**
**关键亮点**：
- 代码简洁，逻辑清晰。
- 使用 `min` 函数优化状态转移，确保 $dp_i$ 始终为最小值。
- 通过排序和动态规划的结合，高效解决问题。

**核心代码**：
```cpp
for(int i = 1; i <= n; i++) {
    if(i >= k) z[i] = min(z[i], z[i - k] + a[i]);
    z[i] = min(z[i], z[i - 1] + a[i]);
}
```

#### 题解2：作者：OIerWu_829 (赞：2)
**星级：4**
**关键亮点**：
- 使用倒序枚举，减少不必要的计算。
- 代码结构清晰，易于理解。

**核心代码**：
```cpp
for(int i = 1; i <= n; i++) {
    if(i < k) f[i] = min(f[i], f[i - 1] + a[i]);
    else f[i] = min(f[i], f[i - k] + a[i]);
}
```

#### 题解3：作者：__cheems__ (赞：2)
**星级：4**
**关键亮点**：
- 详细解释了贪心策略的合理性。
- 通过动态规划实现最优解，代码简洁。

**核心代码**：
```cpp
for(int i = 1; i <= n; i++) {
    if(i >= k) dp[i] = min(dp[i], dp[i - k] + a[i]);
    dp[i] = min(dp[i], dp[i - 1] + a[i]);
}
```

### 最优关键思路
1. **排序优先**：通过排序确保优先购买价格较低的商品，最大化购买数量。
2. **动态规划优化**：利用动态规划记录购买前 $i$ 件商品的最小花费，确保每次选择最优策略。
3. **倒序枚举**：从后向前枚举，减少不必要的计算，提高效率。

### 可拓展之处
- 类似问题可以结合贪心和动态规划，通过排序和状态转移方程优化求解。
- 可以扩展到其他优惠策略，如“买 $k$ 件商品，支付其中 $m$ 件的价格”。

### 推荐题目
1. [CF1282B1 K for the Price of One (Easy Version)](https://www.luogu.com.cn/problem/CF1282B1)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1048 采药](https://www.luogu.com.cn/problem/P1048)

---
处理用时：41.55秒