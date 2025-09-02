---
title: "Simplified Nonogram"
layout: "post"
diff: 提高+/省选-
pid: CF534F
tag: []
---

# Simplified Nonogram

## 题目描述

In this task you have to write a program dealing with nonograms on fields no larger than $ 5×20 $ .

Simplified nonogram is a task where you have to build such field (each cell is either white or black) that satisfies the given information about rows and columns. For each row and each column the number of contiguous black segments is specified.

For example if size of the field is $ n=3,m=5 $ , аnd numbers of contiguous black segments in rows are: $ [2,3,2] $ and in columns are: $ [1,0,1,2,1] $ then the solution may look like:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF534F/6475e8c66c897f247015722a0394e139a91bb231.png)It is guaranteed that on each test in the testset there exists at least one solution.

## 输入格式

In the first line there follow two integers $ n $ , $ m $ ( $ 1<=n<=5,1<=m<=20 $ ) — number of rows and number of columns respectively.

Second line contains $ n $ integers $ a_{1},a_{2},...,a_{n} $ where $ a_{i} $ is the number of contiguous black segments in $ i $ -th row of the field.

Similarly, third line contains $ m $ integers $ b_{1},b_{2},...,b_{m} $ where $ b_{i} $ is the number of contiguous black segments in the $ i $ -th column of the field.

It is guaranteed that there exists at least one solution.

## 输出格式

Output any possible solution. Output should consist of $ n $ lines each containing $ m $ characters. Denote white cell as "." and black cell as "\*".

## 样例 #1

### 输入

```
3 5
2 3 2
1 0 1 2 1

```

### 输出

```
*.**.
*.*.*
*..**
```

## 样例 #2

### 输入

```
3 3
2 1 2
2 1 2

```

### 输出

```
*.*
.*.
*.*

```

## 样例 #3

### 输入

```
3 3
1 0 1
2 2 2

```

### 输出

```
***
...
***

```

