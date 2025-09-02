---
title: "Hero to Zero"
layout: "post"
diff: 省选/NOI-
pid: CF1765J
tag: []
---

# Hero to Zero

## 题目描述

There are no heroes in this problem. I guess we should have named it "To Zero".

You are given two arrays $ a $ and $ b $ , each of these arrays contains $ n $ non-negative integers.

Let $ c $ be a matrix of size $ n \times n $ such that $ c_{i,j} = |a_i - b_j| $ for every $ i \in [1, n] $ and every $ j \in [1, n] $ .

Your goal is to transform the matrix $ c $ so that it becomes the zero matrix, i. e. a matrix where every element is exactly $ 0 $ . In order to do so, you may perform the following operations any number of times, in any order:

- choose an integer $ i $ , then decrease $ c_{i,j} $ by $ 1 $ for every $ j \in [1, n] $ (i. e. decrease all elements in the $ i $ -th row by $ 1 $ ). In order to perform this operation, you pay $ 1 $ coin;
- choose an integer $ j $ , then decrease $ c_{i,j} $ by $ 1 $ for every $ i \in [1, n] $ (i. e. decrease all elements in the $ j $ -th column by $ 1 $ ). In order to perform this operation, you pay $ 1 $ coin;
- choose two integers $ i $ and $ j $ , then decrease $ c_{i,j} $ by $ 1 $ . In order to perform this operation, you pay $ 1 $ coin;
- choose an integer $ i $ , then increase $ c_{i,j} $ by $ 1 $ for every $ j \in [1, n] $ (i. e. increase all elements in the $ i $ -th row by $ 1 $ ). When you perform this operation, you receive $ 1 $ coin;
- choose an integer $ j $ , then increase $ c_{i,j} $ by $ 1 $ for every $ i \in [1, n] $ (i. e. increase all elements in the $ j $ -th column by $ 1 $ ). When you perform this operation, you receive $ 1 $ coin.

You have to calculate the minimum number of coins required to transform the matrix $ c $ into the zero matrix. Note that all elements of $ c $ should be equal to $ 0 $ simultaneously after the operations.

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 0 \le a_i \le 10^8 $ ).

The third line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ 0 \le b_j \le 10^8 $ ).

## 输出格式

Print one integer — the minimum number of coins required to transform the matrix $ c $ into the zero matrix.

## 说明/提示

In the first example, the matrix looks as follows:

 111000111You can turn it into a zero matrix using $ 2 $ coins as follows:

- subtract $ 1 $ from the first row, paying $ 1 $ coin;
- subtract $ 1 $ from the third row, paying $ 1 $ coin.

In the second example, the matrix looks as follows:

 221001221You can turn it into a zero matrix using $ 5 $ coins as follows:

- subtract $ 1 $ from the first row, paying $ 1 $ coin;
- subtract $ 1 $ from the third row, paying $ 1 $ coin;
- subtract $ 1 $ from the third row, paying $ 1 $ coin;
- subtract $ 1 $ from $ a_{2,3} $ , paying $ 1 $ coin;
- add $ 1 $ to the third column, receiving $ 1 $ coin;
- subtract $ 1 $ from the first row, paying $ 1 $ coin;
- subtract $ 1 $ from $ a_{2,3} $ , paying $ 1 $ coin.

## 样例 #1

### 输入

```
3
1 2 3
2 2 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3
3 1 3
1 1 2
```

### 输出

```
5
```

## 样例 #3

### 输入

```
2
1 0
2 1
```

### 输出

```
2
```

## 样例 #4

### 输入

```
2
1 4
2 3
```

### 输出

```
4
```

## 样例 #5

### 输入

```
4
1 3 3 7
6 9 4 2
```

### 输出

```
29
```

