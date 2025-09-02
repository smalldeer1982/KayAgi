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

---
title: "Best Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF2026E
tag: ['网络流', '二分图']
---

# Best Subsequence

## 题目描述

Given an integer array $ a $ of size $ n $ .

Let's define the value of the array as its size minus the number of set bits in the bitwise OR of all elements of the array.

For example, for the array $ [1, 0, 1, 2] $ , the bitwise OR is $ 3 $ (which contains $ 2 $ set bits), and the value of the array is $ 4-2=2 $ .

Your task is to calculate the maximum possible value of some subsequence of the given array.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 100 $ ) — the number of test cases.

The first line of each test case contains a single integer $ n $ ( $ 1 \le n \le 100 $ ).

The second line of each test case contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i < 2^{60} $ ).

## 输出格式

For each test case, print the maximum possible value of some subsequence of the given array.

## 样例 #1

### 输入

```
4
3
0 0 0
4
1 0 1 2
1
5
8
7 1 48 14 13 8 7 6
```

### 输出

```
3
2
0
3
```



---

---
title: "George and Interesting Graph"
layout: "post"
diff: 提高+/省选-
pid: CF387D
tag: ['网络流', '二分图']
---

# George and Interesting Graph

## 题目描述

- 没有重边；
- 存在结点 $v$（称为中心），使得对于图中的任意结点 $u$，都有边 $(u,v)$ 和 $(v,u)$，注意自环 $(v,v)$ 也应该存在；
- 除去中心外，每个点的入度和出度都恰好为 $2$； 

显然很少有图有趣，但 George 可以把图变得有趣：每次他可以增加一条边或者删除一条已经存在的边。

现在给出图 $G$，George 想知道他最少做多少次操作可以使它变得有趣。

## 输出格式

Translated by @Harry_bh

## 样例 #1

### 输入

```
3 7
1 1
2 2
3 1
1 3
3 2
2 3
3 3

```

### 输出

```
0

```

## 样例 #2

### 输入

```
3 6
1 1
2 2
3 1
3 2
2 3
3 3

```

### 输出

```
1

```

## 样例 #3

### 输入

```
3 1
2 2

```

### 输出

```
6

```



---

