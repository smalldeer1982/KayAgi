---
title: "Factorise N+M"
layout: "post"
diff: 入门
pid: CF1740A
tag: []
---

# Factorise N+M

## 题目描述

Pak Chanek has a prime number $ ^\dagger $ $ n $ . Find a prime number $ m $ such that $ n + m $ is not prime.

 $ ^\dagger $ A prime number is a number with exactly $ 2 $ factors. The first few prime numbers are $ 2,3,5,7,11,13,\ldots $ . In particular, $ 1 $ is not a prime number.

## 输入格式

Each test contains multiple test cases. The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases. The following lines contain the description of each test case.

The only line of each test case contains a prime number $ n $ ( $ 2 \leq n \leq 10^5 $ ).

## 输出格式

For each test case, output a line containing a prime number $ m $ ( $ 2 \leq m \leq 10^5 $ ) such that $ n + m $ is not prime. It can be proven that under the constraints of the problem, such $ m $ always exists.

If there are multiple solutions, you can output any of them.

## 说明/提示

In the first test case, $ m = 2 $ , which is prime, and $ n + m = 7 + 2 = 9 $ , which is not prime.

In the second test case, $ m = 7 $ , which is prime, and $ n + m = 2 + 7 = 9 $ , which is not prime.

In the third test case, $ m = 47837 $ , which is prime, and $ n + m = 75619 + 47837 = 123456 $ , which is not prime.

## 样例 #1

### 输入

```
3
7
2
75619
```

### 输出

```
2
7
47837
```

