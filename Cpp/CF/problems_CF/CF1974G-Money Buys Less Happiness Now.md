---
title: "Money Buys Less Happiness Now"
layout: "post"
diff: 普及+/提高
pid: CF1974G
tag: ['贪心']
---

# Money Buys Less Happiness Now

## 题目描述

You can never buy enough happiness, so here we go again! In this version, you can only buy $ h_i = 1 $ unit of happiness each month, but the number of months is hugely increased. We are in the realm of quantum happiness and time dilation.

Being a physicist, Charlie likes to plan his life in simple and precise terms.

For the next $ m $ months, starting with no money, Charlie will work hard and earn $ x $ pounds per month. For the $ i $ -th month $ (1 \le i \le m) $ , there'll be a single opportunity of paying cost $ c_i $ pounds to obtain one unit of happiness. You cannot buy more than one unit each month.

Borrowing is not allowed. Money earned in the $ i $ -th month can only be spent in a later $ j $ -th month ( $ j>i $ ).

Since physicists don't code, help Charlie find the maximum reachable units of happiness.

## 输入格式

The first line of the input contains $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

The first line of each test case contains two integers, $ m $ and $ x $ ( $ 1 \le m \le 2 \cdot 10^5 $ , $ 1 \le x \le 10^3 $ ) — the total number of months and the monthly salary.

The second line of each test case contains $ m $ integers $ c_1, c_2, \dots, c_m $ ( $ 1 \leq c_i \leq 10^3 $ ) — the cost of one unit of happiness for each month.

It is guaranteed that sum of $ m $ over all test cases does not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output one integer — the maximal amount of happiness Charlie can get.

## 样例 #1

### 输入

```
6
3 3
2 2 2
6 5
2 2 8 2 6 8
6 4
4 10 3 8 6 10
2 1
1 1
4 1
4 1 3 1
4 2
1 3 4 3
```

### 输出

```
2
4
3
1
2
1
```

