---
title: "Young Table"
layout: "post"
diff: 普及-
pid: CF237B
tag: []
---

# Young Table

## 题目描述

You've got table $ a $ , consisting of $ n $ rows, numbered from 1 to $ n $ . The $ i $ -th line of table $ a $ contains $ c_{i} $ cells, at that for all $ i $ $ (1&lt;i<=n) $ holds $ c_{i}<=c_{i-1} $ .

Let's denote $ s $ as the total number of cells of table $ a $ , that is, ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF237B/41032ee9d28de3347d7865d06640fb12d664cefb.png). We know that each cell of the table contains a single integer from $ 1 $ to $ s $ , at that all written integers are distinct.

Let's assume that the cells of the $ i $ -th row of table $ a $ are numbered from 1 to $ c_{i} $ , then let's denote the number written in the $ j $ -th cell of the $ i $ -th row as $ a_{i,j} $ . Your task is to perform several swap operations to rearrange the numbers in the table so as to fulfill the following conditions:

1. for all $ i,j $ $ (1&lt;i<=n; 1<=j<=c_{i}) $ holds $ a_{i,j}&gt;a_{i-1,j} $ ;
2. for all $ i,j $ $ (1<=i<=n; 1&lt;j<=c_{i}) $ holds $ a_{i,j}&gt;a_{i,j-1} $ .

In one swap operation you are allowed to choose two different cells of the table and swap the recorded there numbers, that is the number that was recorded in the first of the selected cells before the swap, is written in the second cell after it. Similarly, the number that was recorded in the second of the selected cells, is written in the first cell after the swap.

Rearrange the numbers in the required manner. Note that you are allowed to perform any number of operations, but not more than $ s $ . You do not have to minimize the number of operations.

## 输入格式

The first line contains a single integer $ n $ $ (1<=n<=50) $ that shows the number of rows in the table. The second line contains $ n $ space-separated integers $ c_{i} $ $ (1<=c_{i}<=50; c_{i}<=c_{i-1}) $ — the numbers of cells on the corresponding rows.

Next $ n $ lines contain table $ а $ . The $ i $ -th of them contains $ c_{i} $ space-separated integers: the $ j $ -th integer in this line represents $ a_{i,j} $ .

It is guaranteed that all the given numbers $ a_{i,j} $ are positive and do not exceed $ s $ . It is guaranteed that all $ a_{i,j} $ are distinct.

## 输出格式

In the first line print a single integer $ m $ $ (0<=m<=s) $ , representing the number of performed swaps.

In the next $ m $ lines print the description of these swap operations. In the $ i $ -th line print four space-separated integers $ x_{i},y_{i},p_{i},q_{i} $ $ (1<=x_{i},p_{i}<=n; 1<=y_{i}<=c_{xi}; 1<=q_{i}<=c_{pi}) $ . The printed numbers denote swapping the contents of cells $ a_{xi},y_{i} $ and $ a_{pi},q_{i} $ . Note that a swap operation can change the contents of distinct table cells. Print the swaps in the order, in which they should be executed.

## 样例 #1

### 输入

```
3
3 2 1
4 3 5
6 1
2

```

### 输出

```
2
1 1 2 2
2 1 3 1

```

## 样例 #2

### 输入

```
1
4
4 3 2 1

```

### 输出

```
2
1 1 1 4
1 2 1 3

```

