---
title: "Runner's Problem"
layout: "post"
diff: 省选/NOI-
pid: CF954F
tag: []
---

# Runner's Problem

## 题目描述

You are running through a rectangular field. This field can be represented as a matrix with $ 3 $ rows and $ m $ columns. $ (i,j) $ denotes a cell belonging to $ i $ -th row and $ j $ -th column.

You start in $ (2,1) $ and have to end your path in $ (2,m) $ . From the cell $ (i,j) $ you may advance to:

- $ (i-1,j+1) $ — only if $ i&gt;1 $ ,
- $ (i,j+1) $ , or
- $ (i+1,j+1) $ — only if $ i&lt;3 $ .

However, there are $ n $ obstacles blocking your path. $ k $ -th obstacle is denoted by three integers $ a_{k} $ , $ l_{k} $ and $ r_{k} $ , and it forbids entering any cell $ (a_{k},j) $ such that $ l_{k}<=j<=r_{k} $ .

You have to calculate the number of different paths from $ (2,1) $ to $ (2,m) $ , and print it modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 1<=n<=10^{4} $ , $ 3<=m<=10^{18} $ ) — the number of obstacles and the number of columns in the matrix, respectively.

Then $ n $ lines follow, each containing three integers $ a_{k} $ , $ l_{k} $ and $ r_{k} $ ( $ 1<=a_{k}<=3 $ , $ 2<=l_{k}<=r_{k}<=m-1 $ ) denoting an obstacle blocking every cell $ (a_{k},j) $ such that $ l_{k}<=j<=r_{k} $ . Some cells may be blocked by multiple obstacles.

## 输出格式

Print the number of different paths from $ (2,1) $ to $ (2,m) $ , taken modulo $ 10^{9}+7 $ . If it is impossible to get from $ (2,1) $ to $ (2,m) $ , then the number of paths is $ 0 $ .

## 样例 #1

### 输入

```
2 5
1 3 4
2 2 3

```

### 输出

```
2

```

