---
title: "Fun"
layout: "post"
diff: 普及/提高-
pid: CF1996D
tag: ['枚举']
---

# Fun

## 题目描述

Counting is Fun!

— satyam343



Given two integers $ n $ and $ x $ , find the number of triplets ( $ a,b,c $ ) of positive integers such that $ ab + ac + bc \le n $ and $ a + b + c \le x $ .

Note that order matters (e.g. ( $ 1, 1, 2 $ ) and ( $ 1, 2, 1 $ ) are treated as different) and $ a $ , $ b $ , $ c $ must be strictly greater than $ 0 $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

Each test case contains two integers $ n $ and $ x $ ( $ 1 \leq n,x \leq 10^6 $ ).

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 10^6 $ and that the sum of $ x $ over all test cases does not exceed $ 10^6 $ .

## 输出格式

Output a single integer — the number of triplets ( $ a,b,c $ ) of positive integers such that $ ab + ac + bc \le n $ and $ a + b + c \le x $ .

## 说明/提示

In the first test case, the triplets are ( $ 1, 1, 1 $ ), ( $ 1, 1, 2 $ ), ( $ 1, 2, 1 $ ), and ( $ 2, 1, 1 $ ).

In the second test case, the triplets are ( $ 1, 1, 1 $ ), ( $ 1, 1, 2 $ ), ( $ 1, 1, 3 $ ), ( $ 1, 2, 1 $ ), ( $ 1, 2, 2 $ ), ( $ 1, 3, 1 $ ), ( $ 2, 1, 1 $ ), ( $ 2, 1, 2 $ ), ( $ 2, 2, 1 $ ), and ( $ 3, 1, 1 $ ).

## 样例 #1

### 输入

```
4
7 4
10 5
7 1000
900000 400000
```

### 输出

```
4
10
7
1768016938
```

