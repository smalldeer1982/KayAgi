---
title: "Symmetric and Transitive"
layout: "post"
diff: 提高+/省选-
pid: CF568B
tag: []
---

# Symmetric and Transitive

## 题目描述

Little Johnny has recently learned about set theory. Now he is studying binary relations. You've probably heard the term "equivalence relation". These relations are very important in many areas of mathematics. For example, the equality of the two numbers is an equivalence relation.

A set $ ρ $ of pairs $ (a,b) $ of elements of some set $ A $ is called a binary relation on set $ A $ . For two elements $ a $ and $ b $ of the set $ A $ we say that they are in relation $ ρ $ , if pair ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/16a5bd0364ee1c2418519b45f507a656a36915fe.png), in this case we use a notation ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png).

Binary relation is equivalence relation, if:

1. It is reflexive (for any $ a $ it is true that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/91e4d3abbed748c18e812b3137edc3c1a1f0e778.png));
2. It is symmetric (for any $ a $ , $ b $ it is true that if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png), then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/b6f938add219491e6c1f894f8e7099b7242c4c5e.png));
3. It is transitive (if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/5fd1e1be872bf420a3d068d47d57fec967b2dcb8.png), than ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/78faa71961e282211efc6cc897539a239b2fbcca.png)).

Little Johnny is not completely a fool and he noticed that the first condition is not necessary! Here is his "proof":

Take any two elements, $ a $ and $ b $ . If ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/ac1017904cc72900e599536210489e5806c7e715.png), then ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/b6f938add219491e6c1f894f8e7099b7242c4c5e.png) (according to property (2)), which means ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/91e4d3abbed748c18e812b3137edc3c1a1f0e778.png) (according to property (3)).

It's very simple, isn't it? However, you noticed that Johnny's "proof" is wrong, and decided to show him a lot of examples that prove him wrong.

Here's your task: count the number of binary relations over a set of size $ n $ such that they are symmetric, transitive, but not an equivalence relations (i.e. they are not reflexive).

Since their number may be very large (not $ 0 $ , according to Little Johnny), print the remainder of integer division of this number by $ 10^{9}+7 $ .

## 输入格式

A single line contains a single integer $ n $ $ (1<=n<=4000) $ .

## 输出格式

In a single line print the answer to the problem modulo $ 10^{9}+7 $ .

## 说明/提示

If $ n=1 $ there is only one such relation — an empty one, i.e. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/519c456ed02b51bdfd523585bf0281cdbd8600fd.png). In other words, for a single element $ x $ of set $ A $ the following is hold: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/3abfc110a65cf385b201a329b8a306e1eb23baef.png).

If $ n=2 $ there are three such relations. Let's assume that set $ A $ consists of two elements, $ x $ and $ y $ . Then the valid relations are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF568B/519c456ed02b51bdfd523585bf0281cdbd8600fd.png), $ ρ={(x,x)} $ , $ ρ={(y,y)} $ . It is easy to see that the three listed binary relations are symmetric and transitive relations, but they are not equivalence relations.

## 样例 #1

### 输入

```
1

```

### 输出

```
1

```

## 样例 #2

### 输入

```
2

```

### 输出

```
3

```

## 样例 #3

### 输入

```
3

```

### 输出

```
10

```

