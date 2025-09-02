---
title: "Balanced String"
layout: "post"
diff: 提高+/省选-
pid: CF1860D
tag: []
---

# Balanced String

## 题目描述

You are given a binary string $ s $ (a binary string is a string consisting of characters 0 and/or 1).

Let's call a binary string balanced if the number of subsequences 01 (the number of indices $ i $ and $ j $ such that $ 1 \le i < j \le n $ , $ s_i=0 $ and $ s_j=1 $ ) equals to the number of subsequences 10 (the number of indices $ k $ and $ l $ such that $ 1 \le k < l \le n $ , $ s_k=1 $ and $ s_l=0 $ ) in it.

For example, the string 1000110 is balanced, because both the number of subsequences 01 and the number of subsequences 10 are equal to $ 6 $ . On the other hand, 11010 is not balanced, because the number of subsequences 01 is $ 1 $ , but the number of subsequences 10 is $ 5 $ .

You can perform the following operation any number of times: choose two characters in $ s $ and swap them. Your task is to calculate the minimum number of operations to make the string $ s $ balanced.

## 输入格式

The only line contains the string $ s $ ( $ 3 \le |s| \le 100 $ ) consisting of characters 0 and/or 1.

Additional constraint on the input: the string $ s $ can be made balanced.

## 输出格式

Print a single integer — the minimum number of swap operations to make the string $ s $ balanced.

## 说明/提示

In the first example, the string is already balanced, the number of both 01 and 10 is equal to $ 1 $ .

In the second example, the string is already balanced, the number of both 01 and 10 is equal to $ 6 $ .

In the third example, one of the possible answers is the following one: 11010 $ \rightarrow $ 01110. After that, the number of both 01 and 10 is equal to $ 3 $ .

In the fourth example, one of the possible answers is the following one: 11001100 $ \rightarrow $ 11001010 $ \rightarrow $ 11000011. After that, the number of both 01 and 10 is equal to $ 8 $ .

## 样例 #1

### 输入

```
101
```

### 输出

```
0
```

## 样例 #2

### 输入

```
1000110
```

### 输出

```
0
```

## 样例 #3

### 输入

```
11010
```

### 输出

```
1
```

## 样例 #4

### 输入

```
11001100
```

### 输出

```
2
```

