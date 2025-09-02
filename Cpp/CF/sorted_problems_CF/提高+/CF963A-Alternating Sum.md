---
title: "Alternating Sum"
layout: "post"
diff: 提高+/省选-
pid: CF963A
tag: []
---

# Alternating Sum

## 题目描述

You are given two integers $ a $ and $ b $ . Moreover, you are given a sequence $ s_0, s_1, \dots, s_{n} $ . All values in $ s $ are integers $ 1 $ or $ -1 $ . It's known that sequence is $ k $ -periodic and $ k $ divides $ n+1 $ . In other words, for each $ k \leq i \leq n $ it's satisfied that $ s_{i} = s_{i - k} $ .

Find out the non-negative remainder of division of $ \sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i} $ by $ 10^{9} + 9 $ .

Note that the modulo is unusual!

## 输入格式

The first line contains four integers $ n, a, b $ and $ k $ $ (1 \leq n \leq 10^{9}, 1 \leq a, b \leq 10^{9}, 1 \leq k \leq 10^{5}) $ .

The second line contains a sequence of length $ k $ consisting of characters '+' and '-'.

If the $ i $ -th character (0-indexed) is '+', then $ s_{i} = 1 $ , otherwise $ s_{i} = -1 $ .

Note that only the first $ k $ members of the sequence are given, the rest can be obtained using the periodicity property.

## 输出格式

Output a single integer — value of given expression modulo $ 10^{9} + 9 $ .

## 说明/提示

In the first example:

 $ (\sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i}) $ = $ 2^{2} 3^{0} - 2^{1} 3^{1} + 2^{0} 3^{2} $ = 7

In the second example:

 $ (\sum \limits_{i=0}^{n} s_{i} a^{n - i} b^{i}) = -1^{4} 5^{0} - 1^{3} 5^{1} - 1^{2} 5^{2} - 1^{1} 5^{3} - 1^{0} 5^{4} = -781 \equiv 999999228 \pmod{10^{9} + 9} $ .

## 样例 #1

### 输入

```
2 2 3 3
+-+

```

### 输出

```
7

```

## 样例 #2

### 输入

```
4 1 5 1
-

```

### 输出

```
999999228

```

