---
title: "Chris and Magic Square"
layout: "post"
diff: 普及/提高-
pid: CF711B
tag: []
---

# Chris and Magic Square

## 题目描述

ZS the Coder and Chris the Baboon arrived at the entrance of Udayland. There is a $ n×n $ magic grid on the entrance which is filled with integers. Chris noticed that exactly one of the cells in the grid is empty, and to enter Udayland, they need to fill a positive integer into the empty cell.

Chris tried filling in random numbers but it didn't work. ZS the Coder realizes that they need to fill in a positive integer such that the numbers in the grid form a magic square. This means that he has to fill in a positive integer so that the sum of the numbers in each row of the grid (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/e9e8af3f495bde6f05bb15fe8a019d478bbc6918.png)), each column of the grid (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/715dbd8d1021ddf349931cbf725fd485f986bf2d.png)), and the two long diagonals of the grid (the main diagonal — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/141aae991a978e02f2d5b71795da24f641569581.png) and the secondary diagonal — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/0aa6adfaeb4cdadf568645c01154f2786989c40b.png)) are equal.

Chris doesn't know what number to fill in. Can you help Chris find the correct positive integer to fill in or determine that it is impossible?

## 输入格式

The first line of the input contains a single integer $ n $ ( $ 1<=n<=500 $ ) — the number of rows and columns of the magic grid.

 $ n $ lines follow, each of them contains $ n $ integers. The $ j $ -th number in the $ i $ -th of them denotes $ a_{i,j} $ ( $ 1<=a_{i,j}<=10^{9} $ or $ a_{i,j}=0 $ ), the number in the $ i $ -th row and $ j $ -th column of the magic grid. If the corresponding cell is empty, $ a_{i,j} $ will be equal to $ 0 $ . Otherwise, $ a_{i,j} $ is positive.

It is guaranteed that there is exactly one pair of integers $ i,j $ $ (1<=i,j<=n) $ such that $ a_{i,j}=0 $ .

## 输出格式

Output a single integer, the positive integer $ x $ ( $ 1<=x<=10^{18} $ ) that should be filled in the empty cell so that the whole grid becomes a magic square. If such positive integer $ x $ does not exist, output $ -1 $ instead.

If there are multiple solutions, you may print any of them.

## 说明/提示

In the first sample case, we can fill in $ 9 $ into the empty cell to make the resulting grid a magic square. Indeed,

The sum of numbers in each row is:

 $ 4+9+2=3+5+7=8+1+6=15 $ .

The sum of numbers in each column is:

 $ 4+3+8=9+5+1=2+7+6=15 $ .

The sum of numbers in the two diagonals is:

 $ 4+5+6=2+5+8=15 $ .

In the third sample case, it is impossible to fill a number in the empty square such that the resulting grid is a magic square.

## 样例 #1

### 输入

```
3
4 0 2
3 5 7
8 1 6

```

### 输出

```
9

```

## 样例 #2

### 输入

```
4
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1

```

### 输出

```
1

```

## 样例 #3

### 输入

```
4
1 1 1 1
1 1 0 1
1 1 2 1
1 1 1 1

```

### 输出

```
-1

```

