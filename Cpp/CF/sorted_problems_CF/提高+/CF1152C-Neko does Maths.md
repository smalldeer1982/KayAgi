---
title: "Neko does Maths"
layout: "post"
diff: 提高+/省选-
pid: CF1152C
tag: []
---

# Neko does Maths

## 题目描述

Neko loves divisors. During the latest number theory lesson, he got an interesting exercise from his math teacher.

Neko has two integers $ a $ and $ b $ . His goal is to find a non-negative integer $ k $ such that the least common multiple of $ a+k $ and $ b+k $ is the smallest possible. If there are multiple optimal integers $ k $ , he needs to choose the smallest one.

Given his mathematical talent, Neko had no trouble getting Wrong Answer on this problem. Can you help him solve it?

## 输入格式

The only line contains two integers $ a $ and $ b $ ( $ 1 \le a, b \le 10^9 $ ).

## 输出格式

Print the smallest non-negative integer $ k $ ( $ k \ge 0 $ ) such that the lowest common multiple of $ a+k $ and $ b+k $ is the smallest possible.

If there are many possible integers $ k $ giving the same value of the least common multiple, print the smallest one.

## 说明/提示

In the first test, one should choose $ k = 2 $ , as the least common multiple of $ 6 + 2 $ and $ 10 + 2 $ is $ 24 $ , which is the smallest least common multiple possible.

## 样例 #1

### 输入

```
6 10

```

### 输出

```
2
```

## 样例 #2

### 输入

```
21 31

```

### 输出

```
9
```

## 样例 #3

### 输入

```
5 10

```

### 输出

```
0
```

