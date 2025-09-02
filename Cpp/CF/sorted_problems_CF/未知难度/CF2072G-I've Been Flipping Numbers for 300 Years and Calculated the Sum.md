---
title: "I've Been Flipping Numbers for 300 Years and Calculated the Sum"
layout: "post"
diff: 难度0
pid: CF2072G
tag: []
---

# I've Been Flipping Numbers for 300 Years and Calculated the Sum

## 题目描述

After three hundred years of slime farming, Akito finally obtained the magical number $ n $ . Upon reaching the merchant, he wanted to exchange the number for gold, but the merchant gave the hero a quest.

The merchant said that for the quest, the skill $ \text{rev}(n, p) $ would be required, which Akito, by happy coincidence, had recently learned. $ \text{rev}(n, p) $ represents the following procedure:

1. Write the number $ n $ in base $ p $ , let this representation be $ n = \overline{n_{\ell - 1} \ldots n_1 n_0} $ , where $ \ell $ is the length of the base $ p $ representation of the number $ n $ .
2. Reverse the base $ p $ representation, let this be $ m = \overline{n_0 n_1 \ldots n_{\ell - 1}} $ .
3. Convert the number $ m $ back to decimal and return it as the result.

The merchant's quest was to calculate the sum $ x = \sum\limits_{p = 2}^{k} \text{rev}(n, p) $ . Since this number can be quite large, only the remainder of $ x $ when divided by $ 10^9 + 7 $ is required. The merchant also mentioned that the previous traveler had been calculating this sum for three hundred years and had not finished it. But you will help Akito finish it faster, right?

## 输入格式

The first line contains the number $ t $ ( $ 1 \le t \le 5000 $ ) — the number of test cases.

In the only line of each test case, two numbers $ n $ and $ k $ are given ( $ 1 \le n \le 3 \cdot 10^5, 2 \le k \le 10^{18} $ ) — the magical number and the upper limit for summation.

Note that the sum of $ n $ across all test cases is not bounded.

## 输出格式

For each test case, you need to output a single number — the remainder of $ x = \sum\limits_{p = 2}^{k} \text{rev}(n, p) $ when divided by $ 10^9 + 7 $ .

## 说明/提示

In the third test case, $ n = 1 $ . The number one in any numeral system is represented by a single digit, which means $ \text{rev}(1, p) = 1 $ for any $ p \ge 2 $ . Thus, $ x = \sum\limits_{p = 2}^{k} 1 = \sum\limits_{p = 2}^{10} 1 = 10 - 2 + 1 = 9 $ .

In the fourth test case, $ x = \text{rev}(4, 2) + \text{rev}(4, 3) + \text{rev}(4, 4) $ . Let's calculate each term:

- $ 4 = 100_2 \rightarrow \text{rev}(4, 2) = 001_2 = 1 $
- $ 4 = 11_3 \rightarrow \text{rev}(4, 3) = 11_3 = 4 $
- $ 4 = 10_4 \rightarrow \text{rev}(4, 4) = 01_4 = 1 $

 Thus, $ x = 1 + 4 + 1 = 6 $ .In the seventh test case, $ x = \text{rev}(9, 2) + \text{rev}(9, 3) $ . Let's calculate each term:

- $ 9 = 1001_2 \rightarrow \text{rev}(9, 2) = 1001_2 = 9 $
- $ 9 = 100_3 \rightarrow \text{rev}(9, 3) = 001_3 = 1 $

 Thus, $ x = 9 + 1 = 10 $ .

## 样例 #1

### 输入

```
12
3 2
42 52
1 10
4 4
16 2
69 69
9 3
19 84
9982 44353
100000 1000000007
17 30
777 1000000000000000000
```

### 输出

```
3
7594
9
6
1
33471
10
2006
120792461
584502117
775
46058362
```

