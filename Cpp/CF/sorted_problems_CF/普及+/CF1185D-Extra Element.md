---
title: "Extra Element"
layout: "post"
diff: 普及+/提高
pid: CF1185D
tag: []
---

# Extra Element

## 题目描述

A sequence $ a_1, a_2, \dots, a_k $ is called an arithmetic progression if for each $ i $ from $ 1 $ to $ k $ elements satisfy the condition $ a_i = a_1 + c \cdot (i - 1) $ for some fixed $ c $ .

For example, these five sequences are arithmetic progressions: $ [5, 7, 9, 11] $ , $ [101] $ , $ [101, 100, 99] $ , $ [13, 97] $ and $ [5, 5, 5, 5, 5] $ . And these four sequences aren't arithmetic progressions: $ [3, 1, 2] $ , $ [1, 2, 4, 8] $ , $ [1, -1, 1, -1] $ and $ [1, 2, 3, 3, 3] $ .

You are given a sequence of integers $ b_1, b_2, \dots, b_n $ . Find any index $ j $ ( $ 1 \le j \le n $ ), such that if you delete $ b_j $ from the sequence, you can reorder the remaining $ n-1 $ elements, so that you will get an arithmetic progression. If there is no such index, output the number -1.

## 输入格式

The first line of the input contains one integer $ n $ ( $ 2 \le n \le 2\cdot10^5 $ ) — length of the sequence $ b $ . The second line contains $ n $ integers $ b_1, b_2, \dots, b_n $ ( $ -10^9 \le b_i \le 10^9 $ ) — elements of the sequence $ b $ .

## 输出格式

Print such index $ j $ ( $ 1 \le j \le n $ ), so that if you delete the $ j $ -th element from the sequence, you can reorder the remaining elements, so that you will get an arithmetic progression. If there are multiple solutions, you are allowed to print any of them. If there is no such index, print -1.

## 说明/提示

Note to the first example. If you delete the $ 4 $ -th element, you can get the arithmetic progression $ [2, 4, 6, 8] $ .

Note to the second example. The original sequence is already arithmetic progression, so you can delete $ 1 $ -st or last element and you will get an arithmetical progression again.

## 样例 #1

### 输入

```
5
2 6 8 7 4

```

### 输出

```
4
```

## 样例 #2

### 输入

```
8
1 2 3 4 5 6 7 8

```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
1 2 4 8

```

### 输出

```
-1
```

