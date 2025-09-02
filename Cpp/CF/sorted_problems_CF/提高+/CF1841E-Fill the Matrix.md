---
title: "Fill the Matrix"
layout: "post"
diff: 提高+/省选-
pid: CF1841E
tag: []
---

# Fill the Matrix

## 题目描述

There is a square matrix, consisting of $ n $ rows and $ n $ columns of cells, both numbered from $ 1 $ to $ n $ . The cells are colored white or black. Cells from $ 1 $ to $ a_i $ are black, and cells from $ a_i+1 $ to $ n $ are white, in the $ i $ -th column.

You want to place $ m $ integers in the matrix, from $ 1 $ to $ m $ . There are two rules:

- each cell should contain at most one integer;
- black cells should not contain integers.

The beauty of the matrix is the number of such $ j $ that $ j+1 $ is written in the same row, in the next column as $ j $ (in the neighbouring cell to the right).

What's the maximum possible beauty of the matrix?

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of testcases.

The first line of each testcase contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ ) — the size of the matrix.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le n $ ) — the number of black cells in each column.

The third line contains a single integer $ m $ ( $ 0 \le m \le \sum \limits_{i=1}^n n - a_i $ ) — the number of integers you have to write in the matrix. Note that this number might not fit into a 32-bit integer data type.

The sum of $ n $ over all testcases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each testcase, print a single integer — the maximum beauty of the matrix after you write all $ m $ integers in it. Note that there are no more integers than the white cells, so the answer always exists.

## 样例 #1

### 输入

```
6
3
0 0 0
9
4
2 0 3 1
5
4
2 0 3 1
6
4
2 0 3 1
10
10
0 2 2 1 5 10 3 4 1 1
20
1
1
0
```

### 输出

```
6
3
4
4
16
0
```

