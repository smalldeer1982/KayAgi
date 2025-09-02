---
title: "Dima and Two Sequences"
layout: "post"
diff: 普及/提高-
pid: CF272D
tag: []
---

# Dima and Two Sequences

## 题目描述

Little Dima has two sequences of points with integer coordinates: sequence $ (a_{1},1),(a_{2},2),...,(a_{n},n) $ and sequence $ (b_{1},1),(b_{2},2),...,(b_{n},n) $ .

Now Dima wants to count the number of distinct sequences of points of length $ 2·n $ that can be assembled from these sequences, such that the $ x $ -coordinates of points in the assembled sequence will not decrease. Help him with that. Note that each element of the initial sequences should be used exactly once in the assembled sequence.

Dima considers two assembled sequences $ (p_{1},q_{1}),(p_{2},q_{2}),...,(p_{2·n},q_{2·n}) $ and $ (x_{1},y_{1}),(x_{2},y_{2}),...,(x_{2·n},y_{2·n}) $ distinct, if there is such $ i $ $ (1<=i<=2·n) $ , that $ (p_{i},q_{i})≠(x_{i},y_{i}) $ .

As the answer can be rather large, print the remainder from dividing the answer by number $ m $ .

## 输入格式

The first line contains integer $ n $ $ (1<=n<=10^{5}) $ . The second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ $ (1<=a_{i}<=10^{9}) $ . The third line contains $ n $ integers $ b_{1},b_{2},...,b_{n} $ $ (1<=b_{i}<=10^{9}) $ . The numbers in the lines are separated by spaces.

The last line contains integer $ m $ $ (2<=m<=10^{9}+7) $ .

## 输出格式

In the single line print the remainder after dividing the answer to the problem by number $ m $ .

## 说明/提示

In the first sample you can get only one sequence: $ (1,1),(2,1) $ .

In the second sample you can get such sequences : $ (1,1),(2,2),(2,1),(3,2) $ ; $ (1,1),(2,1),(2,2),(3,2) $ . Thus, the answer is $ 2 $ .

## 样例 #1

### 输入

```
1
1
2
7

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2
1 2
2 3
11

```

### 输出

```
2

```

