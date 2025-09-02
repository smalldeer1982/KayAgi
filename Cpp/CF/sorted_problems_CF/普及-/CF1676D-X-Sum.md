---
title: "X-Sum"
layout: "post"
diff: 普及-
pid: CF1676D
tag: ['模拟']
---

# X-Sum

## 题目描述

Timur's grandfather gifted him a chessboard to practice his chess skills. This chessboard is a grid $ a $ with $ n $ rows and $ m $ columns with each cell having a non-negative integer written on it.

Timur's challenge is to place a bishop on the board such that the sum of all cells attacked by the bishop is maximal. The bishop attacks in all directions diagonally, and there is no limit to the distance which the bishop can attack. Note that the cell on which the bishop is placed is also considered attacked. Help him find the maximal sum he can get.

## 输入格式

The first line of the input contains a single integer $ t $ ( $ 1 \le t \le 1000 $ ) — the number of test cases. The description of test cases follows.

The first line of each test case contains the integers $ n $ and $ m $ ( $ 1 \le n \le 200 $ , $ 1 \leq m \leq 200 $ ).

The following $ n $ lines contain $ m $ integers each, the $ j $ -th element of the $ i $ -th line $ a_{ij} $ is the number written in the $ j $ -th cell of the $ i $ -th row $ (0\leq a_{ij} \leq 10^6) $

It is guaranteed that the sum of $ n\cdot m $ over all test cases does not exceed $ 4\cdot10^4 $ .

## 输出格式

For each test case output a single integer, the maximum sum over all possible placements of the bishop.

## 说明/提示

For the first test case here the best sum is achieved by the bishop being in this position:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

## 样例 #1

### 输入

```
4
4 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4
2 1
1
0
3 3
1 1 1
1 1 1
1 1 1
3 3
0 1 1
1 0 1
1 1 0
```

### 输出

```
20
1
5
3
```

