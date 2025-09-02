---
title: "Array Product"
layout: "post"
diff: 普及/提高-
pid: CF1042C
tag: []
---

# Array Product

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You can perform the following operations with it:

1. Choose some positions $ i $ and $ j $ ( $ 1 \le i, j \le n, i \ne j $ ), write the value of $ a_i \cdot a_j $ into the $ j $ -th cell and remove the number from the $ i $ -th cell;
2. Choose some position $ i $ and remove the number from the $ i $ -th cell (this operation can be performed no more than once and at any point of time, not necessarily in the beginning).

The number of elements decreases by one after each operation. However, the indexing of positions stays the same. Deleted numbers can't be used in the later operations.

Your task is to perform exactly $ n - 1 $ operations with the array in such a way that the only number that remains in the array is maximum possible. This number can be rather large, so instead of printing it you need to print any sequence of operations which leads to this maximum number. Read the output format to understand what exactly you need to print.

## 输入格式

The first line contains a single integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ) — the number of elements in the array.

The second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ -10^9 \le a_i \le 10^9 $ ) — the elements of the array.

## 输出格式

Print $ n - 1 $ lines. The $ k $ -th line should contain one of the two possible operations.

The operation of the first type should look like this: $ 1~ i_k~ j_k $ , where $ 1 $ is the type of operation, $ i_k $ and $ j_k $ are the positions of the chosen elements.

The operation of the second type should look like this: $ 2~ i_k $ , where $ 2 $ is the type of operation, $ i_k $ is the position of the chosen element. Note that there should be no more than one such operation.

If there are multiple possible sequences of operations leading to the maximum number — print any of them.

## 说明/提示

Let X be the removed number in the array. Let's take a look at all the examples:

The first example has, for example, the following sequence of transformations of the array: $ [5, -2, 0, 1, -3] \to [5, -2, X, 1, -3] \to [X, -10, X, 1, -3] \to $ $ [X, X, X, -10, -3] \to [X, X, X, X, 30] $ . Thus, the maximum answer is $ 30 $ . Note, that other sequences that lead to the answer $ 30 $ are also correct.

The second example has, for example, the following sequence of transformations of the array: $ [5, 2, 0, 4, 0] \to [5, 2, X, 4, 0] \to [5, 2, X, 4, X] \to [X, 10, X, 4, X] \to $ $ [X, X, X, 40, X] $ . The following answer is also allowed:

`<br></br>1 5 3<br></br>1 4 2<br></br>1 2 1<br></br>2 3<br></br>`Then the sequence of transformations of the array will look like this: $ [5, 2, 0, 4, 0] \to [5, 2, 0, 4, X] \to [5, 8, 0, X, X] \to [40, X, 0, X, X] \to $ $ [40, X, X, X, X] $ .

The third example can have the following sequence of transformations of the array: $ [2, -1] \to [2, X] $ .

The fourth example can have the following sequence of transformations of the array: $ [0, -10, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0] $ .

The fifth example can have the following sequence of transformations of the array: $ [0, 0, 0, 0] \to [X, 0, 0, 0] \to [X, X, 0, 0] \to [X, X, X, 0] $ .

## 样例 #1

### 输入

```
5
5 -2 0 1 -3

```

### 输出

```
2 3
1 1 2
1 2 4
1 4 5

```

## 样例 #2

### 输入

```
5
5 2 0 4 0

```

### 输出

```
1 3 5
2 5
1 1 2
1 2 4

```

## 样例 #3

### 输入

```
2
2 -1

```

### 输出

```
2 2

```

## 样例 #4

### 输入

```
4
0 -10 0 0

```

### 输出

```
1 1 2
1 2 3
1 3 4

```

## 样例 #5

### 输入

```
4
0 0 0 0

```

### 输出

```
1 1 2
1 2 3
1 3 4

```

