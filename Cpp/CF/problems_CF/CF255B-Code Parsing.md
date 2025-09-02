---
title: "Code Parsing"
layout: "post"
diff: 普及/提高-
pid: CF255B
tag: []
---

# Code Parsing

## 题目描述

Little Vitaly loves different algorithms. Today he has invented a new algorithm just for you. Vitaly's algorithm works with string $ s $ , consisting of characters "x" and "y", and uses two following operations at runtime:

1. Find two consecutive characters in the string, such that the first of them equals "y", and the second one equals "x" and swap them. If there are several suitable pairs of characters, we choose the pair of characters that is located closer to the beginning of the string.
2. Find in the string two consecutive characters, such that the first of them equals "x" and the second one equals "y". Remove these characters from the string. If there are several suitable pairs of characters, we choose the pair of characters that is located closer to the beginning of the string.

The input for the new algorithm is string $ s $ , and the algorithm works as follows:

1. If you can apply at least one of the described operations to the string, go to step 2 of the algorithm. Otherwise, stop executing the algorithm and print the current string.
2. If you can apply operation 1, then apply it. Otherwise, apply operation 2. After you apply the operation, go to step 1 of the algorithm.

Now Vitaly wonders, what is going to be printed as the result of the algorithm's work, if the input receives string $ s $ .

## 输入格式

The first line contains a non-empty string $ s $ .

It is guaranteed that the string only consists of characters "x" and "y". It is guaranteed that the string consists of at most $ 10^{6} $ characters. It is guaranteed that as the result of the algorithm's execution won't be an empty string.

## 输出格式

In the only line print the string that is printed as the result of the algorithm's work, if the input of the algorithm input receives string $ s $ .

## 说明/提示

In the first test the algorithm will end after the first step of the algorithm, as it is impossible to apply any operation. Thus, the string won't change.

In the second test the transformation will be like this:

1. string "yxyxy" transforms into string "xyyxy";
2. string "xyyxy" transforms into string "xyxyy";
3. string "xyxyy" transforms into string "xxyyy";
4. string "xxyyy" transforms into string "xyy";
5. string "xyy" transforms into string "y".

As a result, we've got string "y".

In the third test case only one transformation will take place: string "xxxxxy" transforms into string "xxxx". Thus, the answer will be string "xxxx".

## 样例 #1

### 输入

```
x

```

### 输出

```
x

```

## 样例 #2

### 输入

```
yxyxy

```

### 输出

```
y

```

## 样例 #3

### 输入

```
xxxxxy

```

### 输出

```
xxxx

```

