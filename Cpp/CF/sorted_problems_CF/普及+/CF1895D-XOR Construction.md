---
title: "XOR Construction"
layout: "post"
diff: 普及+/提高
pid: CF1895D
tag: []
---

# XOR Construction

## 题目描述

You are given $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ .

Your task is to construct an array $ b_1, b_2, \dots, b_n $ such that:

- every integer from $ 0 $ to $ n-1 $ appears in $ b $ exactly once;
- for every $ i $ from $ 1 $ to $ n-1 $ , $ b_i \oplus b_{i+1} = a_i $ (where $ \oplus $ denotes the bitwise XOR operator).

## 输入格式

The first line contains one integer $ n $ ( $ 2 \le n \le 2 \cdot 10^5 $ ).

The second line contains $ n-1 $ integers $ a_1, a_2, \dots, a_{n-1} $ ( $ 0 \le a_i \le 2n $ ).

Additional constraint on the input: it's always possible to construct at least one valid array $ b $ from the given sequence $ a $ .

## 输出格式

Print $ n $ integers $ b_1, b_2, \dots, b_n $ . If there are multiple such arrays, you may print any of them.

## 样例 #1

### 输入

```
4
2 1 2
```

### 输出

```
0 2 3 1
```

## 样例 #2

### 输入

```
6
1 6 1 4 1
```

### 输出

```
2 3 5 4 0 1
```

