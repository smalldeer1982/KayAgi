---
title: "Random Query"
layout: "post"
diff: 普及+/提高
pid: CF846F
tag: []
---

# Random Query

## 题目描述

You are given an array $ a $ consisting of $ n $ positive integers. You pick two integer numbers $ l $ and $ r $ from $ 1 $ to $ n $ , inclusive (numbers are picked randomly, equiprobably and independently). If $ l&gt;r $ , then you swap values of $ l $ and $ r $ . You have to calculate the expected value of the number of unique elements in segment of the array from index $ l $ to index $ r $ , inclusive ( $ 1 $ -indexed).

## 输入格式

The first line contains one integer number $ n $ $ (1<=n<=10^{6}) $ . The second line contains $ n $ integer numbers $ a_{1} $ , $ a_{2} $ , ... $ a_{n} $ $ (1<=a_{i}<=10^{6}) $ — elements of the array.

## 输出格式

Print one number — the expected number of unique elements in chosen segment.

Your answer will be considered correct if its absolute or relative error doesn't exceed $ 10^{-4} $ — formally, the answer is correct if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF846F/1e3a6016727b2f57aeaab3dcbe84256bba31c89a.png), where $ x $ is jury's answer, and $ y $ is your answer.

## 样例 #1

### 输入

```
2
1 2

```

### 输出

```
1.500000

```

## 样例 #2

### 输入

```
2
2 2

```

### 输出

```
1.000000

```

