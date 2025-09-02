---
title: "Grid Puzzle"
layout: "post"
diff: 普及+/提高
pid: CF1990D
tag: []
---

# Grid Puzzle

## 题目描述

You are given an array $ a $ of size $ n $ .

There is an $ n \times n $ grid. In the $ i $ -th row, the first $ a_i $ cells are black and the other cells are white. In other words, note $ (i,j) $ as the cell in the $ i $ -th row and $ j $ -th column, cells $ (i,1), (i,2), \ldots, (i,a_i) $ are black, and cells $ (i,a_i+1), \ldots, (i,n) $ are white.

You can do the following operations any number of times in any order:

- Dye a $ 2 \times 2 $ subgrid white;
- Dye a whole row white. Note you can not dye a whole column white.

Find the minimum number of operations to dye all cells white.

## 输入格式

The first line contains an integer $ t $ ( $ 1 \leq t \leq 10^4 $ ) — the number of test cases.

For each test case:

- The first line contains an integer $ n $ ( $ 1 \leq n \leq 2 \cdot 10^5 $ ) — the size of the array $ a $ .
- The second line contains $ n $ integers $ a_1, a_2, \ldots, a_n $ ( $ 0 \leq a_i \leq n $ ).

It's guaranteed that the sum of $ n $ over all test cases will not exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, output a single integer — the minimum number of operations to dye all cells white.

## 说明/提示

In the first test case, you don't need to do any operation.

In the second test case, you can do:

- Dye $ (1,1), (1,2), (2,1) $ , and $ (2,2) $ white;
- Dye $ (2,3), (2,4), (3,3) $ , and $ (3,4) $ white;
- Dye $ (3,1), (3,2), (4,1) $ , and $ (4,2) $ white.

It can be proven $ 3 $ is the minimum number of operations.

In the third test case, you can do:

- Dye the first row white;
- Dye $ (2,1), (2,2), (3,1) $ , and $ (3,2) $ white.

It can be proven $ 2 $ is the minimum number of operations.

## 样例 #1

### 输入

```
10
1
0
4
2 4 4 2
4
3 2 1 0
3
0 3 0
3
0 1 3
3
3 1 0
4
3 1 0 3
4
0 2 2 2
6
1 3 4 2 0 4
8
2 2 5 2 3 4 2 4
```

### 输出

```
0
3
2
1
2
2
3
2
4
6
```

