---
title: "Rectangles"
layout: "post"
diff: 普及/提高-
pid: CF844B
tag: []
---

# Rectangles

## 题目描述

You are given $ n×m $ table. Each cell of the table is colored white or black. Find the number of non-empty sets of cells such that:

1. All cells in a set have the same color.
2. Every two cells in a set share row or column.

## 输入格式

The first line of input contains integers $ n $ and $ m $ ( $ 1<=n,m<=50 $ ) — the number of rows and the number of columns correspondingly.

The next $ n $ lines of input contain descriptions of rows. There are $ m $ integers, separated by spaces, in each line. The number equals $ 0 $ if the corresponding cell is colored white and equals $ 1 $ if the corresponding cell is colored black.

## 输出格式

Output single integer — the number of non-empty sets from the problem description.

## 说明/提示

In the second example, there are six one-element sets. Additionally, there are two two-element sets, the first one consists of the first and the third cells of the first row, the second one consists of the first and the third cells of the second row. To sum up, there are $ 8 $ sets.

## 样例 #1

### 输入

```
1 1
0

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2 3
1 0 1
0 1 0

```

### 输出

```
8

```

