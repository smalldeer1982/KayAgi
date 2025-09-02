---
title: "Puzzle Pieces"
layout: "post"
diff: 入门
pid: CF1345A
tag: []
---

# Puzzle Pieces

## 题目描述

You are given a special jigsaw puzzle consisting of $ n\cdot       m $ identical pieces. Every piece has three tabs and one blank, as pictured below.

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345A/60ffcef399717ed0f289e4b31cc0a5ee2dec5407.png)The jigsaw puzzle is considered solved if the following conditions hold:

1. The pieces are arranged into a grid with $ n $ rows and $ m $ columns.
2. For any two pieces that share an edge in the grid, a tab of one piece fits perfectly into a blank of the other piece.

Through rotation and translation of the pieces, determine if it is possible to solve the jigsaw puzzle.

## 输入格式

The test consists of multiple test cases. The first line contains a single integer $ t $ ( $ 1\le t\le 1000 $ ) — the number of test cases. Next $ t $ lines contain descriptions of test cases.

Each test case contains two integers $ n $ and $ m $ ( $ 1       \le n,m \le 10^5 $ ).

## 输出格式

For each test case output a single line containing "YES" if it is possible to solve the jigsaw puzzle, or "NO" otherwise. You can print each letter in any case (upper or lower).

## 说明/提示

For the first test case, this is an example solution:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345A/db67836f1b5a85c330d2922e27048675c71b449b.png)For the second test case, we can show that no solution exists.

For the third test case, this is an example solution:

  ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1345A/c78752b010c38be7f441faf449a63f07f1d71394.png)

## 样例 #1

### 输入

```
3
1 3
100000 100000
2 2
```

### 输出

```
YES
NO
YES
```

