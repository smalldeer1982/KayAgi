---
title: "Stair, Peak, or Neither?"
layout: "post"
diff: 入门
pid: CF1950A
tag: ['模拟']
---

# Stair, Peak, or Neither?

## 题目描述

You are given three digits $ a $ , $ b $ , and $ c $ . Determine whether they form a stair, a peak, or neither.

- A stair satisfies the condition $ a<b<c $ .
- A peak satisfies the condition $ a<b>c $ .

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \leq t \leq 1000 $ ) — the number of test cases.

The only line of each test case contains three digits $ a $ , $ b $ , $ c $ ( $ 0 \leq a $ , $ b $ , $ c \leq 9 $ ).

## 输出格式

For each test case, output "STAIR" if the digits form a stair, "PEAK" if the digits form a peak, and "NONE" otherwise (output the strings without quotes).

## 样例 #1

### 输入

```
7
1 2 3
3 2 1
1 5 3
3 4 1
0 0 0
4 1 7
4 5 7
```

### 输出

```
STAIR
NONE
PEAK
PEAK
NONE
NONE
STAIR
```

