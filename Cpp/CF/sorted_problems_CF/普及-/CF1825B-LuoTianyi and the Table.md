---
title: "LuoTianyi and the Table"
layout: "post"
diff: 普及-
pid: CF1825B
tag: []
---

# LuoTianyi and the Table

## 题目描述

LuoTianyi gave an array $ b $ of $ n \cdot m $ integers. She asks you to construct a table $ a $ of size $ n \times m $ , filled with these $ n \cdot m $ numbers, and each element of the array must be used exactly once. Also she asked you to maximize the following value:

  $ \sum\limits_{i=1}^{n}\sum\limits_{j=1}^{m}\left(\max\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}-\min\limits_{1 \le x \le i, 1 \le y \le j}a_{x,y}\right) $ This means that we consider $ n \cdot m $ subtables with the upper left corner in $ (1,1) $ and the bottom right corner in $ (i, j) $ ( $ 1 \le i \le n $ , $ 1 \le j \le m $ ), for each such subtable calculate the difference of the maximum and minimum elements in it, then sum up all these differences. You should maximize the resulting sum.

Help her find the maximal possible value, you don't need to reconstruct the table itself.

## 输入格式

Each test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 200 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains two integers $ n $ and $ m $ ( $ 2 \le n, m \le 100 $ ) — the number of rows and columns of the table.

The second line of each test case contains $ n \cdot m $ integers $ b_1, b_2, \ldots, b_{n\cdot m} $ ( $ -10^5 \le b_{i} \le 10^5 $ ) — the numbers you can put in the table.

Note, that integers in the array $ b $ can be negative.

It is guaranteed that the sum of $ n \cdot m $ over all test cases doesn't exceed $ 2\cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the maximal value, that can be obtained.

## 说明/提示

In the first test case, the table is follows:

4113In the subtable with the bottom right corner in $ (1, 1) $ , the difference of the maximal and minimal elements is $ 4 - 4 = 0 $ .

In the subtable with the bottom right corner in $ (1, 2) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

In the subtable with the bottom right corner in $ (2, 1) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

In the subtable with the bottom right corner in $ (2, 2) $ , the difference of the maximal and minimal elements is $ 4 - 1 = 3 $ .

Then the maximum possible value is $ 0+3+3+3=9 $ .

In the second test case, all elements are equal, so all differences are $ 0 $ , and the answer is $ 0 $ .

## 样例 #1

### 输入

```
5
2 2
1 3 1 4
2 2
-1 -1 -1 -1
2 3
7 8 9 -3 10 8
3 2
4 8 -3 0 -7 1
4 3
-32030 59554 16854 -85927 68060 -64460 -79547 90932 85063 82703 -12001 38762
```

### 输出

```
9
0
64
71
1933711
```

