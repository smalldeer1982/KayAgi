---
title: "Deleting Substrings"
layout: "post"
diff: 省选/NOI-
pid: CF392E
tag: []
---

# Deleting Substrings

## 题目描述

SmallR likes a game called "Deleting Substrings". In the game you are given a sequence of integers $ w $ , you can modify the sequence and get points. The only type of modification you can perform is (unexpected, right?) deleting substrings. More formally, you can choose several contiguous elements of $ w $ and delete them from the sequence. Let's denote the sequence of chosen elements as $ w_{l},w_{l+1},...,w_{r} $ . They must meet the conditions:

- the equality $ |w_{i}-w_{i+1}|=1 $ must hold for all $ i $ $ (l<=i&lt;r) $ ;
- the inequality $ 2·w_{i}-w_{i+1}-w_{i-1}>=0 $ must hold for all $ i $ $ (l&lt;i&lt;r) $ .

After deleting the chosen substring of $ w $ , you gain $ v_{r-l+1} $ points. You can perform the described operation again and again while proper substrings exist. Also you can end the game at any time. Your task is to calculate the maximum total score you can get in the game.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=400) $ — the initial length of $ w $ . The second line contains $ n $ integers $ v_{1},v_{2},...,v_{n} $ $ (0<=|v_{i}|<=2000) $ — the costs of operations. The next line contains $ n $ integers $ w_{1},w_{2},...,w_{n} $ $ (1<=w_{i}<=10^{9}) $ — the initial $ w $ .

## 输出格式

Print a single integer — the maximum total score you can get.

## 样例 #1

### 输入

```
3
0 0 3
1 2 1

```

### 输出

```
3
```

## 样例 #2

### 输入

```
6
1 4 5 6 7 1000
2 1 1 2 2 3

```

### 输出

```
12
```

