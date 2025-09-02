---
title: "Minimum Modular"
layout: "post"
diff: 省选/NOI-
pid: CF303C
tag: []
---

# Minimum Modular

## 题目描述

You have been given $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ . You can remove at most $ k $ of them. Find the minimum modular $ m $ $ (m&gt;0) $ , so that for every pair of the remaining integers $ (a_{i},a_{j}) $ , the following unequality holds: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF303C/e08769ae8f052f7d357ba6c3db7e7cd896370f65.png).

## 输入格式

The first line contains two integers $ n $ and $ k $ ( $ 1<=n<=5000,0<=k<=4 $ ), which we have mentioned above.

The second line contains $ n $ distinct integers $ a_{1},a_{2},...,a_{n} $ $ (0<=a_{i}<=10^{6}) $ .

## 输出格式

Print a single positive integer — the minimum $ m $ .

## 样例 #1

### 输入

```
7 0
0 2 3 6 7 12 18

```

### 输出

```
13

```

## 样例 #2

### 输入

```
7 1
0 2 3 6 7 12 18

```

### 输出

```
7

```

