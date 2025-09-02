---
title: "Ciel and Flipboard"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF321D
tag: ['枚举']
---

# Ciel and Flipboard

## 题目描述

Fox Ciel has a board with $ n $ rows and $ n $ columns, there is one integer in each cell.

It's known that $ n $ is an odd number, so let's introduce ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321D/6479833d305e8df8be298c6d130b2c56818252f6.png). Fox Ciel can do the following operation many times: she choose a sub-board with size $ x $ rows and $ x $ columns, then all numbers in it will be multiplied by -1.

Return the maximal sum of numbers in the board that she can get by these operations.

## 输入格式

The first line contains an integer $ n $ , ( $ 1<=n<=33 $ , and $ n $ is an odd integer) — the size of the board.

Each of the next $ n $ lines contains $ n $ integers — the numbers in the board. Each number doesn't exceed $ 1000 $ by its absolute value.

## 输出格式

Output a single integer: the maximal sum of numbers in the board that can be accomplished.

## 说明/提示

In the first test, we can apply this operation twice: first on the top left $ 2×2 $ sub-board, then on the bottom right $ 2×2 $ sub-board. Then all numbers will become positive.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF321D/bba86be06e5760920ea393fc6a496f40415e324b.png)

## 样例 #1

### 输入

```
3
-1 -1 1
-1 1 -1
1 -1 -1

```

### 输出

```
9

```

## 样例 #2

### 输入

```
5
-2 0 0 0 -2
0 -2 0 -2 0
0 0 -2 0 0
0 -2 0 -2 0
-2 0 0 0 -2

```

### 输出

```
18

```

