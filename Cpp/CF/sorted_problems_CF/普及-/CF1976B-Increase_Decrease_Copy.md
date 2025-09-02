---
title: "Increase/Decrease/Copy"
layout: "post"
diff: 普及-
pid: CF1976B
tag: ['贪心']
---

# Increase/Decrease/Copy

## 题目描述

You are given two integer arrays: array $ a $ of length $ n $ and array $ b $ of length $ n+1 $ .

You can perform the following operations any number of times in any order:

- choose any element of the array $ a $ and increase it by $ 1 $ ;
- choose any element of the array $ a $ and decrease it by $ 1 $ ;
- choose any element of the array $ a $ , copy it and append the copy to the end of the array $ a $ .

Your task is to calculate the minimum number of aforementioned operations (possibly zero) required to transform the array $ a $ into the array $ b $ . It can be shown that under the constraints of the problem, it is always possible.

## 输入格式

The first line contains a single integer $ t $ ( $ 1 \le t \le 10^4 $ ) — the number of test cases.

Each test case consists of three lines:

- the first line contains a single integer $ n $ ( $ 1 \le n \le 2 \cdot 10^5 $ );
- the second line contains $ n $ integers $ a_1, a_2, \dots, a_n $ ( $ 1 \le a_i \le 10^9 $ );
- the third line contains $ n + 1 $ integers $ b_1, b_2, \dots, b_{n + 1} $ ( $ 1 \le b_i \le 10^9 $ ).

Additional constraint on the input: the sum of $ n $ over all test cases doesn't exceed $ 2 \cdot 10^5 $ .

## 输出格式

For each test case, print a single integer — the minimum number of operations (possibly zero) required to transform the array $ a $ into the array $ b $ .

## 说明/提示

In the first example, you can transform $ a $ into $ b $ as follows: $ [2] \rightarrow [2, 2] \rightarrow [1, 2] \rightarrow [1, 3] $ .

## 样例 #1

### 输入

```
3
1
2
1 3
2
3 3
3 3 3
4
4 2 1 2
2 1 5 2 3
```

### 输出

```
3
1
8
```

