---
title: "Copying Data"
layout: "post"
diff: 提高+/省选-
pid: CF292E
tag: []
---

# Copying Data

## 题目描述

We often have to copy large volumes of information. Such operation can take up many computer resources. Therefore, in this problem you are advised to come up with a way to copy some part of a number array into another one, quickly.

More formally, you've got two arrays of integers $ a_{1},a_{2},...,a_{n} $ and $ b_{1},b_{2},...,b_{n} $ of length $ n $ . Also, you've got $ m $ queries of two types:

1. Copy the subsegment of array $ a $ of length $ k $ , starting from position $ x $ , into array $ b $ , starting from position $ y $ , that is, execute $ b_{y+q}=a_{x+q} $ for all integer $ q $ $ (0<=q&lt;k) $ . The given operation is correct — both subsegments do not touch unexistent elements.
2. Determine the value in position $ x $ of array $ b $ , that is, find value $ b_{x} $ .

For each query of the second type print the result — the value of the corresponding element of array $ b $ .

## 输入格式

The first line contains two space-separated integers $ n $ and $ m $ $ (1<=n,m<=10^{5}) $ — the number of elements in the arrays and the number of queries, correspondingly. The second line contains an array of integers $ a_{1},a_{2},...,a_{n} $ $ (|a_{i}|<=10^{9}) $ . The third line contains an array of integers $ b_{1},b_{2},...,b_{n} $ $ (|b_{i}|<=10^{9}) $ .

Next $ m $ lines contain the descriptions of the queries. The $ i $ -th line first contains integer $ t_{i} $ — the type of the $ i $ -th query $ (1<=t_{i}<=2) $ . If $ t_{i}=1 $ , then the $ i $ -th query means the copying operation. If $ t_{i}=2 $ , then the $ i $ -th query means taking the value in array $ b $ . If $ t_{i}=1 $ , then the query type is followed by three integers $ x_{i},y_{i},k_{i} $ $ (1<=x_{i},y_{i},k_{i}<=n) $ — the parameters of the copying query. If $ t_{i}=2 $ , then the query type is followed by integer $ x_{i} $ $ (1<=x_{i}<=n) $ — the position in array $ b $ .

All numbers in the lines are separated with single spaces. It is guaranteed that all the queries are correct, that is, the copying borders fit into the borders of arrays $ a $ and $ b $ .

## 输出格式

For each second type query print the result on a single line.

## 样例 #1

### 输入

```
5 10
1 2 0 -1 3
3 1 5 -2 0
2 5
1 3 3 3
2 5
2 4
2 1
1 2 1 4
2 1
2 4
1 4 2 1
2 2

```

### 输出

```
0
3
-1
3
2
3
-1

```

