---
title: "Rare Coins"
layout: "post"
diff: 提高+/省选-
pid: CF1948F
tag: ['排列组合']
---

# Rare Coins

## 题目描述

There are $ n $ bags numbered from $ 1 $ to $ n $ , the $ i $ -th bag contains $ a_i $ golden coins and $ b_i $ silver coins.

The value of a gold coin is $ 1 $ . The value of a silver coin is either $ 0 $ or $ 1 $ , determined for each silver coin independently ( $ 0 $ with probability $ \frac{1}{2} $ , $ 1 $ with probability $ \frac{1}{2} $ ).

You have to answer $ q $ independent queries. Each query is the following:

- $ l $ $ r $ — calculate the probability that the total value of coins in bags from $ l $ to $ r $ is strictly greater than the total value in all other bags.

## 输入格式

The first line contains two integers $ n $ and $ q $ ( $ 1 \le n, q \le 3 \cdot 10^5 $ ) — the number of bags and the number of queries, respectively.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^6 $ ) — the number of gold coins in the $ i $ -th bag.

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 0 \le b_i \le 10^6 $ ) — the number of silver coins in the $ i $ -th bag.

Next $ q $ lines contain queries. The $ j $ -th of the next $ q $ lines contains two integers $ l_j $ and $ r_j $ ( $ 1 \le l_j \le r_j \le n $ ) — the description of the $ j $ -th query.

Additional constraints on the input:

- the sum of the array $ a $ doesn't exceed $ 10^6 $ ;
- the sum of the array $ b $ doesn't exceed $ 10^6 $ .

## 输出格式

For each query, print one integer — the probability that the total value of coins in bags from $ l $ to $ r $ is strictly greater than the total value in all other bags, taken modulo $ 998244353 $ .

Formally, the probability can be expressed as an irreducible fraction $ \frac{x}{y} $ . You have to print the value of $ x \cdot y^{-1} \bmod 998244353 $ , where $ y^{-1} $ is an integer such that $ y \cdot y^{-1} \bmod 998244353 = 1 $ .

## 说明/提示

In both queries from the first example, the answer is $ \frac{1}{4} $ .

## 样例 #1

### 输入

```
2 2
1 0
0 2
2 2
1 1
```

### 输出

```
748683265 748683265
```

## 样例 #2

### 输入

```
4 3
2 3 4 5
1 0 7 3
3 3
2 3
1 4
```

### 输出

```
997756929 273932289 1
```

