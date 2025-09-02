---
title: "DIVCNT2 - Counting Divisors (square)"
layout: "post"
diff: NOI/NOI+/CTSC
pid: SP20173
tag: ['莫比乌斯反演', '前缀和', '容斥原理']
---

# DIVCNT2 - Counting Divisors (square)

## 题目描述

Let $ \sigma_0(n) $ be the number of positive divisors of $ n $ .

For example, $ \sigma_0(1) = 1 $ , $ \sigma_0(2) = 2 $ and $ \sigma_0(6) = 4 $ .

Let 

$$ S_2(n) = \sum _{i=1}^n \sigma_0(i^2). $$

Given $ N $ , find $ S_2(N) $ .

## 输入格式

First line contains $ T $ ( $ 1 \le T \le 10000 $ ), the number of test cases.

Each of the next $ T $ lines contains a single integer $ N $ . ( $ 1 \le N \le 10^{12} $ )

## 输出格式

For each number $ N $ , output a single line containing $ S_2(N) $ .

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
4
7
48
1194
```

