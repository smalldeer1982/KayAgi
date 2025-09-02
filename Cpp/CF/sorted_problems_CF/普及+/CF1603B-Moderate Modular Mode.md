---
title: "Moderate Modular Mode"
layout: "post"
diff: 普及+/提高
pid: CF1603B
tag: []
---

# Moderate Modular Mode

## 题目描述

YouKn0wWho has two even integers $ x $ and $ y $ . Help him to find an integer $ n $ such that $ 1 \le n \le 2 \cdot 10^{18} $ and $ n \bmod x = y \bmod n $ . Here, $ a \bmod b $ denotes the remainder of $ a $ after division by $ b $ . If there are multiple such integers, output any. It can be shown that such an integer always exists under the given constraints.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^5 $ ) — the number of test cases.

The first and only line of each test case contains two integers $ x $ and $ y $ ( $ 2 \le x, y \le 10^9 $ , both are even).

## 输出格式

For each test case, print a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^{18} $ ) that satisfies the condition mentioned in the statement. If there are multiple such integers, output any. It can be shown that such an integer always exists under the given constraints.

## 说明/提示

In the first test case, $ 4 \bmod 4 = 8 \bmod 4 = 0 $ .

In the second test case, $ 10 \bmod 4 = 2 \bmod 10 = 2 $ .

In the third test case, $ 420 \bmod 420 = 420 \bmod 420 = 0 $ .

## 样例 #1

### 输入

```
4
4 8
4 2
420 420
69420 42068
```

### 输出

```
4
10
420
9969128
```

