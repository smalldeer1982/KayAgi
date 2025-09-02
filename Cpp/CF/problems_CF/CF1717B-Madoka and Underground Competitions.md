---
title: "Madoka and Underground Competitions"
layout: "post"
diff: 普及-
pid: CF1717B
tag: ['模拟', '构造']
---

# Madoka and Underground Competitions

## 题目描述

Madoka decided to participate in an underground sports programming competition. And there was exactly one task in it:

A square table of size $ n \times n $ , where  $ n $ is a multiple of $ k $ , is called good if only the characters '.' and 'X' are written in it, as well as in any subtable of size $ 1 \times k $ or $ k \times 1 $ , there is at least one character 'X'. In other words, among any $ k $ consecutive vertical or horizontal cells, there must be at least one containing the character 'X'.

Output any good table that has the minimum possible number of characters 'X', and also the symbol 'X' is written in the cell $ (r, c) $ . Rows are numbered from $ 1 $ to $ n $ from top to bottom, columns are numbered from $ 1 $ to $ n $ from left to right.

## 输入格式

The input consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases. Description of the test cases follows.

The first and the only line of each test case contains four integers $ n $ , $ k $ , $ r $ , $ c $ ( $ 1 \le n \le 500, 1 \le k \le n, 1 \le r, c \le n $ ) — the size of the table, the integer $ k $ and the coordinates of the cell, which must contain the character 'X'. It is guaranteed that $ n $ is a multiple of $ k $ .

It is guaranteed that the sum of $ n $ over all test cases does not exceed $ 500 $ .

## 输出格式

For each test case, output $ n $ lines, each consisting of $ n $ characters '.' and 'X', — the desired table. If there are several answers, then you can output anyone.

## 说明/提示

Let's analyze the first test case.

The following tables can be printed as the correct answer:

 X....X.X. or ..XX...X. It can be proved that there cannot be less than $ 3 $ characters 'X' in the answer.Note that the following table is invalid because cell $ (3, 2) $ does not contain the character 'X':

 X...X...XIn the second test case, the only correct table is:

 XXXX Each subtable of size $ 1 \times 1 $ must contain a 'X' character, so all characters in the table must be equal to 'X'.

## 样例 #1

### 输入

```
3
3 3 3 2
2 1 1 2
6 3 4 2
```

### 输出

```
X..
..X
.X.
XX
XX
.X..X.
X..X..
..X..X
.X..X.
X..X..
..X..X
```

