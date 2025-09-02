---
title: "Polo the Penguin and XOR operation"
layout: "post"
diff: 普及+/提高
pid: CF288C
tag: []
---

# Polo the Penguin and XOR operation

## 题目描述

Little penguin Polo likes permutations. But most of all he likes permutations of integers from $ 0 $ to $ n $ , inclusive.

For permutation $ p=p_{0},p_{1},...,p_{n} $ , Polo has defined its beauty — number ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF288C/6024047c9c91de0156ffb9e5c8b6ac649d55fe1e.png).

Expression ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF288C/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) means applying the operation of bitwise excluding "OR" to numbers $ x $ and $ y $ . This operation exists in all modern programming languages, for example, in language C++ and Java it is represented as "^" and in Pascal — as "xor".

Help him find among all permutations of integers from $ 0 $ to $ n $ the permutation with the maximum beauty.

## 输入格式

The single line contains a positive integer $ n $ ( $ 1<=n<=10^{6} $ ).

## 输出格式

In the first line print integer $ m $ the maximum possible beauty. In the second line print any permutation of integers from $ 0 $ to $ n $ with the beauty equal to $ m $ .

If there are several suitable permutations, you are allowed to print any of them.

## 样例 #1

### 输入

```
4

```

### 输出

```
20
0 2 1 4 3

```

