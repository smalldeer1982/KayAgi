---
title: "Restore a Number"
layout: "post"
diff: 提高+/省选-
pid: CF670F
tag: []
---

# Restore a Number

## 题目描述

Vasya decided to pass a very large integer $ n $ to Kate. First, he wrote that number as a string, then he appended to the right integer $ k $ — the number of digits in $ n $ .

Magically, all the numbers were shuffled in arbitrary order while this note was passed to Kate. The only thing that Vasya remembers, is a non-empty substring of $ n $ (a substring of $ n $ is a sequence of consecutive digits of the number $ n $ ).

Vasya knows that there may be more than one way to restore the number $ n $ . Your task is to find the smallest possible initial integer $ n $ . Note that decimal representation of number $ n $ contained no leading zeroes, except the case the integer $ n $ was equal to zero itself (in this case a single digit 0 was used).

## 输入格式

The first line of the input contains the string received by Kate. The number of digits in this string does not exceed $ 1000000 $ .

The second line contains the substring of $ n $ which Vasya remembers. This string can contain leading zeroes.

It is guaranteed that the input data is correct, and the answer always exists.

## 输出格式

Print the smalles integer $ n $ which Vasya could pass to Kate.

## 样例 #1

### 输入

```
003512
021

```

### 输出

```
30021

```

## 样例 #2

### 输入

```
199966633300
63

```

### 输出

```
3036366999

```

