---
title: "Strange Game On Matrix"
layout: "post"
diff: 普及/提高-
pid: CF873C
tag: []
---

# Strange Game On Matrix

## 题目描述

Ivan is playing a strange game.

He has a matrix $ a $ with $ n $ rows and $ m $ columns. Each element of the matrix is equal to either $ 0 $ or $ 1 $ . Rows and columns are $ 1 $ -indexed. Ivan can replace any number of ones in this matrix with zeroes. After that, his score in the game will be calculated as follows:

1. Initially Ivan's score is $ 0 $ ;
2. In each column, Ivan will find the topmost $ 1 $ (that is, if the current column is $ j $ , then he will find minimum $ i $ such that $ a_{i,j}=1 $ ). If there are no $ 1 $ 's in the column, this column is skipped;
3. Ivan will look at the next $ min(k,n-i+1) $ elements in this column (starting from the element he found) and count the number of $ 1 $ 's among these elements. This number will be added to his score.

Of course, Ivan wants to maximize his score in this strange game. Also he doesn't want to change many elements, so he will replace the minimum possible number of ones with zeroes. Help him to determine the maximum possible score he can get and the minimum possible number of replacements required to achieve that score.

## 输入格式

The first line contains three integer numbers $ n $ , $ m $ and $ k $ ( $ 1<=k<=n<=100 $ , $ 1<=m<=100 $ ).

Then $ n $ lines follow, $ i $ -th of them contains $ m $ integer numbers — the elements of $ i $ -th row of matrix $ a $ . Each number is either $ 0 $ or $ 1 $ .

## 输出格式

Print two numbers: the maximum possible score Ivan can get and the minimum number of replacements required to get this score.

## 说明/提示

In the first example Ivan will replace the element $ a_{1,2} $ .

## 样例 #1

### 输入

```
4 3 2
0 1 0
1 0 1
0 1 0
1 1 1

```

### 输出

```
4 1

```

## 样例 #2

### 输入

```
3 2 1
1 0
0 1
0 0

```

### 输出

```
2 0

```

