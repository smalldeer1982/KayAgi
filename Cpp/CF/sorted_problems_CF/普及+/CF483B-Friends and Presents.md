---
title: "Friends and Presents"
layout: "post"
diff: 普及+/提高
pid: CF483B
tag: []
---

# Friends and Presents

## 题目描述

You have two friends. You want to present each of them several positive integers. You want to present $ cnt_{1} $ numbers to the first friend and $ cnt_{2} $ numbers to the second friend. Moreover, you want all presented numbers to be distinct, that also means that no number should be presented to both friends.

In addition, the first friend does not like the numbers that are divisible without remainder by prime number $ x $ . The second one does not like the numbers that are divisible without remainder by prime number $ y $ . Of course, you're not going to present your friends numbers they don't like.

Your task is to find such minimum number $ v $ , that you can form presents using numbers from a set $ 1,2,...,v $ . Of course you may choose not to present some numbers at all.

A positive integer number greater than 1 is called prime if it has no positive divisors other than 1 and itself.

## 输入格式

You have two friends. You want to present each of them several positive integers. You want to present $ cnt_{1} $ numbers to the first friend and $ cnt_{2} $ numbers to the second friend. Moreover, you want all presented numbers to be distinct, that also means that no number should be presented to both friends.

In addition, the first friend does not like the numbers that are divisible without remainder by prime number $ x $ . The second one does not like the numbers that are divisible without remainder by prime number $ y $ . Of course, you're not going to present your friends numbers they don't like.

Your task is to find such minimum number $ v $ , that you can form presents using numbers from a set $ 1,2,...,v $ . Of course you may choose not to present some numbers at all.

A positive integer number greater than 1 is called prime if it has no positive divisors other than 1 and itself.

## 输出格式

Print a single integer — the answer to the problem.

## 说明/提示

In the first sample you give the set of numbers $ {1,3,5} $ to the first friend and the set of numbers $ {2} $ to the second friend. Note that if you give set $ {1,3,5} $ to the first friend, then we cannot give any of the numbers $ 1 $ , $ 3 $ , $ 5 $ to the second friend.

In the second sample you give the set of numbers $ {3} $ to the first friend, and the set of numbers $ {1,2,4} $ to the second friend. Thus, the answer to the problem is $ 4 $ .

## 样例 #1

### 输入

```
3 1 2 3

```

### 输出

```
5

```

## 样例 #2

### 输入

```
1 3 2 3

```

### 输出

```
4

```

