---
title: "Nene and the Mex Operator"
layout: "post"
diff: 提高+/省选-
pid: CF1956D
tag: ['动态规划 DP', '构造']
---

# Nene and the Mex Operator

## 题目描述

Nene gave you an array of integers $ a_1, a_2, \ldots, a_n $ of length $ n $ .

You can perform the following operation no more than $ 5\cdot 10^5 $ times (possibly zero):

- Choose two integers $ l $ and $ r $ such that $ 1 \le l \le r \le n $ , compute $ x $ as $ \operatorname{MEX}(\{a_l, a_{l+1}, \ldots, a_r\}) $ , and simultaneously set $ a_l:=x, a_{l+1}:=x, \ldots, a_r:=x $ .

Here, $ \operatorname{MEX} $ of a set of integers $ \{c_1, c_2, \ldots, c_k\} $ is defined as the smallest non-negative integer $ m $ which does not occur in the set $ c $ .

Your goal is to maximize the sum of the elements of the array $ a $ . Find the maximum sum and construct a sequence of operations that achieves this sum. Note that you don't need to minimize the number of operations in this sequence, you only should use no more than $ 5\cdot 10^5 $ operations in your solution.

## 输入格式

The first line contains an integer $ n $ ( $ 1 \le n \le 18 $ ) — the length of the array $ a $ .

The second line contains $ n $ integers $ a_1,a_2,\ldots,a_n $ ( $ 0\leq a_i \leq 10^7 $ ) — the array $ a $ .

## 输出格式

In the first line, output two integers $ s $ and $ m $ ( $ 0\le m\le 5\cdot 10^5 $ ) — the maximum sum of elements of the array $ a $ and the number of operations in your solution.

In the $ i $ -th of the following $ m $ lines, output two integers $ l $ and $ r $ ( $ 1 \le l \le r \le n $ ), representing the parameters of the $ i $ -th operation.

It can be shown that the maximum sum of elements of the array $ a $ can always be obtained in no more than $ 5 \cdot 10^5 $ operations.

## 说明/提示

In the first example, after the operation with $ l=1 $ and $ r=2 $ the array $ a $ becomes equal to $ [2,2] $ . It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 4 $ .

In the second example, the initial sum of elements is $ 13 $ which can be shown to be the largest.

In the third example, the array $ a $ changes as follows:

- after the first operation ( $ l=3 $ , $ r=3 $ ), the array $ a $ becomes equal to $ [1,100,0,1] $ ;
- after the second operation ( $ l=3 $ , $ r=4 $ ), the array $ a $ becomes equal to $ [1,100,2,2] $ .

It can be shown that it is impossible to achieve a larger sum of the elements of $ a $ , so the answer is $ 105 $ .

## 样例 #1

### 输入

```
2
0 1
```

### 输出

```
4 1
1 2
```

## 样例 #2

### 输入

```
3
1 3 9
```

### 输出

```
13 0
```

## 样例 #3

### 输入

```
4
1 100 2 1
```

### 输出

```
105 2
3 3
3 4
```

## 样例 #4

### 输入

```
1
0
```

### 输出

```
1 1
1 1
```

