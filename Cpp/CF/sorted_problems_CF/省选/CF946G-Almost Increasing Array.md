---
title: "Almost Increasing Array"
layout: "post"
diff: 省选/NOI-
pid: CF946G
tag: []
---

# Almost Increasing Array

## 题目描述

We call an array almost increasing if we can erase not more than one element from it so that the array becomes strictly increasing (that is, every element is striclty greater than every element before it).

You are given an array $ a $ consisting of $ n $ elements. You are allowed to replace any element with any integer number (and you may do so any number of times you need). What is the minimum number of replacements you have to perform in order to make the array almost increasing?

## 输入格式

The first line contains one integer $ n $ ( $ 2<=n<=200000 $ ) — the number of elements in $ a $ .

The second line contains $ n $ integers $ a_{1} $ , $ a_{2} $ , ..., $ a_{n} $ ( $ 1<=a_{i}<=10^{9} $ ) — the array $ a $ .

## 输出格式

Print the minimum number of replaces you have to perform so that $ a $ is almost increasing.

## 样例 #1

### 输入

```
5
5 4 3 2 1

```

### 输出

```
3

```

## 样例 #2

### 输入

```
5
1 2 8 9 5

```

### 输出

```
0

```

