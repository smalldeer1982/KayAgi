---
title: "DIVCNT3 - Counting Divisors (cube)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP20174
tag: []
---

# DIVCNT3 - Counting Divisors (cube)

## 题目描述

Let $ \sigma_0(n) $ be the number of positive divisors of $ n $ .

For example, $ \sigma_0(1) = 1 $ , $ \sigma_0(2) = 2 $ and $ \sigma_0(6) = 4 $ .

Let

$$ S_3(n) = \sum _{i=1}^n \sigma_0(i^3). $$

Given $ N $ , find $ S_3(N) $ .

## 输入格式

First line contains $ T $ ( $ 1 \le T \le 10000 $ ), the number of test cases.

Each of the next $ T $ lines contains a single integer $ N $ . ( $ 1 \le N \le 10^{11} $ )

## 输出格式

For each number $ N $ , output a single line containing $ S_3(N) $ .

## 样例 #1

### 输入

```
5
1
2
3
10
100
```

### 输出

```
1
5
9
73
2302
```

