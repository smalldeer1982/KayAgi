---
title: "Moving Chips"
layout: "post"
diff: 入门
pid: CF1923A
tag: ['贪心']
---

# Moving Chips

## 题目描述

There is a ribbon divided into $ n $ cells, numbered from $ 1 $ to $ n $ from left to right. Each cell either contains a chip or is free.

You can perform the following operation any number of times (possibly zero): choose a chip and move it to the closest free cell to the left. You can choose any chip that you want, provided that there is at least one free cell to the left of it. When you move the chip, the cell where it was before the operation becomes free.

Your goal is to move the chips in such a way that they form a single block, without any free cells between them. What is the minimum number of operations you have to perform?

## 输入格式

The first line contains one integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases.

Each test case consists of two lines:

- the first line contains one integer $ n $ ( $ 2 \le n \le 50 $ ) — the number of cells;
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 1 $ ); $ a_i = 0 $ means that the $ i $ -th cell is free; $ a_i = 1 $ means that the $ i $ -th cell contains a chip.

Additional constraint on the input: in each test case, at least one cell contains a chip.

## 输出格式

For each test case, print one integer — the minimum number of operations you have to perform so that all chips form a single block without any free cells between them.

## 说明/提示

In the first example, you can perform the operation on the chip in the $ 7 $ -th cell. The closest free cell to the left is the $ 5 $ -th cell, so it moves there. After that, all chips form a single block.

In the second example, all chips are already in a single block. Same for the third example.

## 样例 #1

### 输入

```
5
8
0 1 1 1 0 1 1 0
6
0 1 0 0 0 0
6
1 1 1 1 1 1
5
1 0 1 0 1
9
0 1 1 0 0 0 1 1 0
```

### 输出

```
1
0
0
2
3
```

