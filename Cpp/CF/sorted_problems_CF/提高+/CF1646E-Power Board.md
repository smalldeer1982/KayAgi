---
title: "Power Board"
layout: "post"
diff: 提高+/省选-
pid: CF1646E
tag: ['数论']
---

# Power Board

## 题目描述

You have a rectangular board of size $ n\times m $ ( $ n $ rows, $ m $ columns). The $ n $ rows are numbered from $ 1 $ to $ n $ from top to bottom, and the $ m $ columns are numbered from $ 1 $ to $ m $ from left to right.

The cell at the intersection of row $ i $ and column $ j $ contains the number $ i^j $ ( $ i $ raised to the power of $ j $ ). For example, if $ n=3 $ and $ m=3 $ the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/f966495b3fd71da241cb3a79e264d10b59256e95.png)Find the number of distinct integers written on the board.

## 输入格式

The only line contains two integers $ n $ and $ m $ ( $ 1\le n,m\le 10^6 $ ) — the number of rows and columns of the board.

## 输出格式

Print one integer, the number of distinct integers on the board.

## 说明/提示

The statement shows the board for the first test case. In this case there are $ 7 $ distinct integers: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 8 $ , $ 9 $ , and $ 27 $ .

In the second test case, the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/36fd681eff28bb5ca921155ad4010ac8be1c65a1.png)There are $ 5 $ distinct numbers: $ 1 $ , $ 2 $ , $ 4 $ , $ 8 $ and $ 16 $ .

In the third test case, the board is as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1646E/a5987da66d8c80ffc8e49f428e2b3197bf00bc43.png)There are $ 6 $ distinct numbers: $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 9 $ and $ 16 $ .

## 样例 #1

### 输入

```
3 3
```

### 输出

```
7
```

## 样例 #2

### 输入

```
2 4
```

### 输出

```
5
```

## 样例 #3

### 输入

```
4 2
```

### 输出

```
6
```

