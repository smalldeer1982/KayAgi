---
title: "Little Girl and Maximum XOR"
layout: "post"
diff: 普及/提高-
pid: CF276D
tag: ['位运算']
---

# Little Girl and Maximum XOR

## 题目描述

A little girl loves problems on bitwise operations very much. Here's one of them.

You are given two integers $ l $ and $ r $ . Let's consider the values of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/e4d673f94fffa65030d2edd227a746e3a121dade.png) for all pairs of integers $ a $ and $ b $ $ (l<=a<=b<=r) $ . Your task is to find the maximum value among all considered ones.

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying bitwise excluding or operation to integers $ x $ and $ y $ . The given operation exists in all modern programming languages, for example, in languages $ C $ ++ and $ Java $ it is represented as "^", in $ Pascal $ — as «xor».

## 输入格式

The single line contains space-separated integers $ l $ and $ r $ ( $ 1<=l<=r<=10^{18} $ ).

Please, do not use the %lld specifier to read or write 64-bit integers in С++. It is preferred to use the cin, cout streams or the %I64d specifier.

## 输出格式

In a single line print a single integer — the maximum value of ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF276D/e4d673f94fffa65030d2edd227a746e3a121dade.png) for all pairs of integers $ a $ , $ b $ $ (l<=a<=b<=r) $ .

## 样例 #1

### 输入

```
1 2

```

### 输出

```
3

```

## 样例 #2

### 输入

```
8 16

```

### 输出

```
31

```

## 样例 #3

### 输入

```
1 1

```

### 输出

```
0

```

