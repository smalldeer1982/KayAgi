---
title: "Distinct Digits"
layout: "post"
diff: 入门
pid: CF1228A
tag: []
---

# Distinct Digits

## 题目描述

You have two integers $ l $ and $ r $ . Find an integer $ x $ which satisfies the conditions below:

- $ l \le x \le r $ .
- All digits of $ x $ are different.

If there are multiple answers, print any of them.

## 输入格式

The first line contains two integers $ l $ and $ r $ ( $ 1 \le l \le r \le 10^{5} $ ).

## 输出格式

If an answer exists, print any of them. Otherwise, print $ -1 $ .

## 说明/提示

In the first example, $ 123 $ is one of the possible answers. However, $ 121 $ can't be the answer, because there are multiple $ 1 $ s on different digits.

In the second example, there is no valid answer.

## 样例 #1

### 输入

```
121 130

```

### 输出

```
123

```

## 样例 #2

### 输入

```
98766 100000

```

### 输出

```
-1

```

