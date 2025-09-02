---
title: "Matrix Problem"
layout: "post"
diff: 提高+/省选-
pid: CF1913E
tag: ['网络流', '费用流']
---

# Matrix Problem

## 题目描述

You are given a matrix $ a $ , consisting of $ n $ rows by $ m $ columns. Each element of the matrix is equal to $ 0 $ or $ 1 $ .

You can perform the following operation any number of times (possibly zero): choose an element of the matrix and replace it with either $ 0 $ or $ 1 $ .

You are also given two arrays $ A $ and $ B $ (of length $ n $ and $ m $ respectively). After you perform the operations, the matrix should satisfy the following conditions:

1. the number of ones in the $ i $ -th row of the matrix should be exactly $ A_i $ for every $ i \in [1, n] $ .
2. the number of ones in the $ j $ -th column of the matrix should be exactly $ B_j $ for every $ j \in [1, m] $ .

Calculate the minimum number of operations you have to perform.

## 输入格式

The first line contains two integers $ n $ and $ m $ ( $ 2 \le n, m \le 50 $ ).

Then $ n $ lines follow. The $ i $ -th of them contains $ m $ integers $ a_{i,1}, a_{i,2}, \dots, a_{i,m} $ ( $ 0 \le a_{i,j} \le 1 $ ).

The next line contains $ n $ integers $ A_1, A_2, \dots, A_n $ ( $ 0\le A_i\le m $ ).

The next line contains $ m $ integers $ B_1, B_2, \dots, B_m $ ( $ 0\le B_i\le n $ ).

## 输出格式

Print one integer — the minimum number of operations you have to perform, or -1 if it is impossible.

## 样例 #1

### 输入

```
3 3
0 0 0
0 0 0
0 0 0
1 1 1
1 1 1
```

### 输出

```
3
```

## 样例 #2

### 输入

```
3 3
1 1 1
1 1 1
1 1 1
3 2 1
1 2 3
```

### 输出

```
3
```

## 样例 #3

### 输入

```
2 2
0 0
0 0
1 2
0 1
```

### 输出

```
-1
```



---

