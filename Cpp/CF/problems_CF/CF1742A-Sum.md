---
title: "Sum"
layout: "post"
diff: 入门
pid: CF1742A
tag: []
---

# Sum

## 题目描述

You are given three integers $ a $ , $ b $ , and $ c $ . Determine if one of them is the sum of the other two.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 9261 $ ) — the number of test cases.

The description of each test case consists of three integers $ a $ , $ b $ , $ c $ ( $ 0 \leq a, b, c \leq 20 $ ).

## 输出格式

For each test case, output "YES" if one of the numbers is the sum of the other two, and "NO" otherwise.

You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).

## 说明/提示

In the first test case, $ 1 + 3 = 4 $ .

In the second test case, none of the numbers is the sum of the other two.

In the third test case, $ 9 + 11 = 20 $ .

## 样例 #1

### 输入

```
7
1 4 3
2 5 8
9 11 20
0 0 0
20 20 20
4 12 3
15 7 8
```

### 输出

```
YES
NO
YES
YES
NO
NO
YES
```

