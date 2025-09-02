---
title: "Distinct Paths"
layout: "post"
diff: 省选/NOI-
pid: CF293B
tag: ['搜索', '剪枝', '状态合并']
---

# Distinct Paths

## 题目描述

You have a rectangular $ n×m $ -cell board. Some cells are already painted some of $ k $ colors. You need to paint each uncolored cell one of the $ k $ colors so that any path from the upper left square to the lower right one doesn't contain any two cells of the same color. The path can go only along side-adjacent cells and can only go down or right.

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 输入格式

The first line contains three integers $ n,m,k $ $ (1<=n,m<=1000,1<=k<=10) $ . The next $ n $ lines contain $ m $ integers each — the board. The first of them contains $ m $ uppermost cells of the board from the left to the right and the second one contains $ m $ cells from the second uppermost row and so on. If a number in a line equals 0, then the corresponding cell isn't painted. Otherwise, this number represents the initial color of the board cell — an integer from 1 to $ k $ .

Consider all colors numbered from 1 to $ k $ in some manner.

## 输出格式

Print the number of possible paintings modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 样例 #1

### 输入

```
2 2 4
0 0
0 0

```

### 输出

```
48

```

## 样例 #2

### 输入

```
2 2 4
1 2
2 1

```

### 输出

```
0

```

## 样例 #3

### 输入

```
5 6 10
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

```

### 输出

```
3628800

```

## 样例 #4

### 输入

```
2 6 10
1 2 3 4 5 6
0 0 0 0 0 0

```

### 输出

```
4096

```

