---
title: "Marina and Vasya"
layout: "post"
diff: 普及+/提高
pid: CF584C
tag: []
---

# Marina and Vasya

## 题目描述

Marina loves strings of the same length and Vasya loves when there is a third string, different from them in exactly $ t $ characters. Help Vasya find at least one such string.

More formally, you are given two strings $ s_{1} $ , $ s_{2} $ of length $ n $ and number $ t $ . Let's denote as $ f(a,b) $ the number of characters in which strings $ a $ and $ b $ are different. Then your task will be to find any string $ s_{3} $ of length $ n $ , such that $ f(s_{1},s_{3})=f(s_{2},s_{3})=t $ . If there is no such string, print $ -1 $ .

## 输入格式

The first line contains two integers $ n $ and $ t $ ( $ 1<=n<=10^{5} $ , $ 0<=t<=n $ ).

The second line contains string $ s_{1} $ of length $ n $ , consisting of lowercase English letters.

The third line contain string $ s_{2} $ of length $ n $ , consisting of lowercase English letters.

## 输出格式

Print a string of length $ n $ , differing from string $ s_{1} $ and from $ s_{2} $ in exactly $ t $ characters. Your string should consist only from lowercase English letters. If such string doesn't exist, print -1.

## 样例 #1

### 输入

```
3 2
abc
xyc

```

### 输出

```
ayd
```

## 样例 #2

### 输入

```
1 0
c
b

```

### 输出

```
-1

```

