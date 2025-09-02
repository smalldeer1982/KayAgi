# 题目信息

# Fancy Coins

## 题目描述

Monocarp is going to make a purchase with cost of exactly $ m $ burles.

He has two types of coins, in the following quantities:

- coins worth $ 1 $ burle: $ a_1 $ regular coins and infinitely many fancy coins;
- coins worth $ k $ burles: $ a_k $ regular coins and infinitely many fancy coins.

Monocarp wants to make his purchase in such a way that there's no change — the total worth of provided coins is exactly $ m $ . He can use both regular and fancy coins. However, he wants to spend as little fancy coins as possible.

What's the smallest total number of fancy coins he can use to make a purchase?

## 说明/提示

In the first testcase, there are no regular coins of either type. Monocarp can use $ 2 $ fancy coins worth $ 1 $ burle and $ 3 $ fancy coins worth $ 3 $ (since $ k=3 $ ) burles to get $ 11 $ total burles with $ 5 $ total fancy coins.

In the second testcase, Monocarp has a lot of regular coins of both types. He can use $ 11 $ regular coins worth $ 1 $ burle, for example. Notice that Monocarp doesn't have to minimize the total number of used coins. That way he uses $ 0 $ fancy coins.

In the third testcase, Monocarp can use $ 5 $ regular coins worth $ 1 $ burle and $ 1 $ regular coin worth $ 3 $ burles. That will get him to $ 8 $ total burles when he needs $ 11 $ . So, $ 1 $ fancy coin worth $ 3 $ burles is enough.

## 样例 #1

### 输入

```
4
11 3 0 0
11 3 20 20
11 3 6 1
100000000 2 0 0```

### 输出

```
5
0
1
50000000```

# AI分析结果

### 题目翻译

Monocarp 将要进行一次购买，花费恰好为 $m$ 元。

他有两种类型的硬币，数量如下：

- 价值为 $1$ 元的硬币：$a_1$ 个普通硬币和无限个花色硬币；
- 价值为 $k$ 元的硬币：$a_k$ 个普通硬币和无限个花色硬币。

Monocarp 希望以没有找零的方式完成购买——提供的硬币总价值恰好为 $m$。他可以使用普通硬币和花色硬币。然而，他希望尽可能少地使用花色硬币。

他最少需要使用多少个花色硬币才能完成购买？

### 算法分类
贪心

### 题解分析与结论

该题的核心思路是贪心算法，通过优先使用普通硬币来减少花色硬币的使用。大部分题解都遵循了以下步骤：
1. 尽量使用价值为 $k$ 元的普通硬币。
2. 尽量使用价值为 $1$ 元的普通硬币。
3. 若仍有剩余金额，使用花色硬币。

难点在于如何合理地将剩余的 $1$ 元普通硬币转化为 $k$ 元硬币，以减少花色硬币的使用。部分题解通过将多余的 $1$ 元普通硬币转化为 $k$ 元硬币，进一步优化了结果。

### 精选题解

#### 题解1：作者 I_am_kunzi (5星)
**关键亮点**：
- 清晰地计算了不替代情况下所需的两种花色硬币数。
- 通过将多余的 $1$ 元普通硬币转化为 $k$ 元硬币，进一步优化了结果。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
long long take_1 = m % k; // 不替代情况下所需 1 面值花色硬币
long long take_k = m / k; // 不替代情况下所需 k 面值花色硬币
long long fancy_1 = max((long long) 0 , take_1 - a1); // 替代后所需 1 面值花色硬币
long long drop_1 = max((long long) 0 , a1 - take_1); // 没有用到的 1 面值花色硬币数
long long fancy_k = max((long long) 0 , take_k - ak); // 用 k 面值普通硬币替代后所需 k 面值花色硬币
long long replace = min(drop_1 / k , fancy_k); // 用 1 面值普通硬币替代 k 面值普通硬币数
cout << fancy_1 + fancy_k - replace << endl; // 答案即为计算后两种花色硬币所需数量与替代硬币数作差
```

#### 题解2：作者 Zaku (4星)
**关键亮点**：
- 通过优先使用 $k$ 元硬币，再使用 $1$ 元硬币，简化了问题。
- 通过将多余的 $1$ 元普通硬币转化为 $k$ 元硬币，进一步优化了结果。
- 代码简洁，易于理解。

**核心代码**：
```cpp
int t1 = m % k, tk = m / k;
if (a1 > t1)
    ak += (a1 - t1) / k, a1 = t1;
if (ak > tk) ak = tk;
cout << t1 - a1 + tk - ak << endl;
```

#### 题解3：作者 aCssen (4星)
**关键亮点**：
- 通过优先使用 $k$ 元硬币，再使用 $1$ 元硬币，简化了问题。
- 通过将多余的 $1$ 元普通硬币转化为 $k$ 元硬币，进一步优化了结果。
- 代码简洁，逻辑清晰。

**核心代码**：
```cpp
cnt1 = m % k, cnt2 = m / k;
if (cnt1 > a) {
    ans += (cnt1 - a);
    a = 0;
}
else a -= cnt1;
cnt2 = max(cnt2 - (a / k), 0);
if (cnt2 > b) ans += (cnt2 - b);
printf("%d\n", ans);
```

### 最优关键思路
1. **优先使用 $k$ 元普通硬币**：尽可能多地使用 $k$ 元普通硬币，以减少花色硬币的使用。
2. **合理转化 $1$ 元普通硬币**：将多余的 $1$ 元普通硬币转化为 $k$ 元硬币，进一步减少花色硬币的使用。
3. **贪心策略**：通过贪心算法，优先使用普通硬币，再使用花色硬币，确保花色硬币的使用最少。

### 拓展思路
类似的问题可以出现在其他涉及硬币组合的题目中，如找零问题、最小硬币数问题等。这类问题通常可以通过贪心算法或动态规划来解决。

### 推荐题目
1. [P1049 装箱问题](https://www.luogu.com.cn/problem/P1049)
2. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)
3. [P1164 小A点菜](https://www.luogu.com.cn/problem/P1164)

---
处理用时：31.34秒