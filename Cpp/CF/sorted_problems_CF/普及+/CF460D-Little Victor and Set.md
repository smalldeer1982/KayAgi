---
title: "Little Victor and Set"
layout: "post"
diff: 普及+/提高
pid: CF460D
tag: ['贪心', '枚举', '构造']
---

# Little Victor and Set

## 题目描述

Little Victor adores the sets theory. Let us remind you that a set is a group of numbers where all numbers are pairwise distinct. Today Victor wants to find a set of integers $ S $ that has the following properties:

- for all $ x $ ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/26c8948a606517ebae5f50ff9b8fc7d91f76f3df.png) the following inequality holds $ l<=x<=r $ ;
- $ 1<=|S|<=k $ ;
- lets denote the $ i $ -th element of the set $ S $ as $ s_{i} $ ; value ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/7523823a9f324064de1df35c0e0503740f7be786.png) must be as small as possible.

Help Victor find the described set.

## 输入格式

The first line contains three space-separated integers $ l,r,k $ $ (1<=l<=r<=10^{12}; 1<=k<=min(10^{6},r-l+1)) $ .

## 输出格式

Print the minimum possible value of $ f(S) $ . Then print the cardinality of set $ |S| $ . Then print the elements of the set in any order.

If there are multiple optimal sets, you can print any of them.

## 说明/提示

Operation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF460D/a0b0fe9e9428287337c0277ea02ca07fcf0a01a7.png) represents the operation of bitwise exclusive OR. In other words, it is the XOR operation.

## 样例 #1

### 输入

```
8 15 3

```

### 输出

```
1
2
10 11

```

## 样例 #2

### 输入

```
8 30 7

```

### 输出

```
0
5
14 9 28 11 16

```

