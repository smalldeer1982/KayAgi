---
title: "Jzzhu and Sequences"
layout: "post"
diff: 普及+/提高
pid: CF450B
tag: []
---

# Jzzhu and Sequences

## 题目描述

Jzzhu has invented a kind of sequences, they meet the following property:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF450B/24eb04dd3b6c3e1abcf8e078661c78665e8d1d86.png)You are given $ x $ and $ y $ , please calculate $ f_{n} $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains two integers $ x $ and $ y $ $ (|x|,|y|<=10^{9}) $ . The second line contains a single integer $ n $ $ (1<=n<=2·10^{9}) $ .

## 输出格式

Output a single integer representing $ f_{n} $ modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

In the first sample, $ f_{2}=f_{1}+f_{3} $ , $ 3=2+f_{3} $ , $ f_{3}=1 $ .

In the second sample, $ f_{2}=-1 $ ; $ -1 $ modulo $ (10^{9}+7) $ equals $ (10^{9}+6) $ .

## 样例 #1

### 输入

```
2 3
3

```

### 输出

```
1

```

## 样例 #2

### 输入

```
0 -1
2

```

### 输出

```
1000000006

```

