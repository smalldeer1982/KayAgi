---
title: "Wonderful Randomized Sum"
layout: "post"
diff: 普及+/提高
pid: CF33C
tag: ['数学', '贪心', '前缀和']
---

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 输入格式

The first line contains integer $ n $ ( $ 1<=n<=10^{5} $ ) — amount of elements in the sequence. The second line contains $ n $ integers $ a_{i} $ ( $ -10^{4}<=a_{i}<=10^{4} $ ) — the sequence itself.

## 输出格式

The first and the only line of the output should contain the answer to the problem.

## 样例 #1

### 输入

```
3
-1 -2 -3

```

### 输出

```
6

```

## 样例 #2

### 输入

```
5
-4 2 0 5 0

```

### 输出

```
11

```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2

```

### 输出

```
18

```

