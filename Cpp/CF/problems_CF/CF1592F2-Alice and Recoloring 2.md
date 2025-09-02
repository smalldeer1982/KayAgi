---
title: "Alice and Recoloring 2"
layout: "post"
diff: 省选/NOI-
pid: CF1592F2
tag: []
---

# Alice and Recoloring 2

## 题目描述

给定一个 $n$ 行 $m$ 列的目标矩阵，矩阵元素只有 W 或 B ，并且你有一个初始矩阵，元素全为 W 。

现在你可以矩阵实施以下操作：

使用一块钱，选定一个包含 $(1,1)$ 的子矩阵，把矩阵中的元素全部反转（ W 变 B ， B 变 W ）。

使用三块钱，选定一个包含 $(n,1)$ 的子矩阵，把矩阵中的元素全部反转。

使用四块钱，选定一个包含 $(1,m)$ 的子矩阵，把矩阵中的元素全部反转。

使用两块钱，选定一个包含 $(n,m)$ 的子矩阵，把矩阵中的元素全部反转。

现在需要你求出把初始矩阵变为目标矩阵最少需要几块钱。

## 输入格式

第一行两个正整数 $n$ 和 $m (1 \le n,m\le 500)$ ，意义如上文所述。

接下来 $n$ 行，每行 $m$ 个字符 W 或 B 。意义如上文所述。

## 输出格式

一行一个整数，表示把初始矩阵变为目标矩阵所需的最少钱数。

## 样例 #1

### 输入

```
3 3
WWW
WBB
WBB
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 15
WWWBBBWBBBBBWWW
BBBBWWWBBWWWBBB
BBBWWBWBBBWWWBB
BBWBWBBWWWBBWBW
BBBBWWWBBBWWWBB
BWBBWWBBBBBBWWW
WBWWBBBBWWBBBWW
WWBWWWWBBWWBWWW
BWBWWBWWWWWWBWB
BBBWBWBWBBBWWBW
```

### 输出

```
68
```

