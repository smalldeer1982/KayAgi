---
title: "Cutting the Line"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF594E
tag: []
---

# Cutting the Line

## 题目描述

You are given a non-empty line $ s $ and an integer $ k $ . The following operation is performed with this line exactly once:

- A line is split into at most $ k $ non-empty substrings, i.e. string $ s $ is represented as a concatenation of a set of strings $ s=t_{1}+t_{2}+...+t_{m} $ , $ 1<=m<=k $ .
- Some of strings $ t_{i} $ are replaced by strings $ t_{i}^{r} $ , that is, their record from right to left.
- The lines are concatenated back in the same order, we get string $ s'=t'_{1}t'_{2}...\ t'_{m} $ , where $ t'_{i} $ equals $ t_{i} $ or $ t_{i}^{r} $ .

Your task is to determine the lexicographically smallest string that could be the result of applying the given operation to the string $ s $ .

## 输入格式

The first line of the input contains string $ s $ ( $ 1<=|s|<=5000000 $ ), consisting of lowercase English letters. The second line contains integer $ k $ ( $ 1<=k<=|s| $ ) — the maximum number of parts in the partition.

## 输出格式

In the single line print the lexicographically minimum string $ s' $ which can be obtained as a result of performing the described operation.

## 样例 #1

### 输入

```
aba
2

```

### 输出

```
aab

```

## 样例 #2

### 输入

```
aaaabacaba
2

```

### 输出

```
aaaaabacab

```

## 样例 #3

### 输入

```
bababa
1

```

### 输出

```
ababab

```

## 样例 #4

### 输入

```
abacabadabacaba
4

```

### 输出

```
aababacabacabad

```

