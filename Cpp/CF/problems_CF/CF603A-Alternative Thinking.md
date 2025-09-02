---
title: "Alternative Thinking"
layout: "post"
diff: 普及/提高-
pid: CF603A
tag: []
---

# Alternative Thinking

## 题目描述

Kevin has just recevied his disappointing results on the USA Identification of Cows Olympiad (USAICO) in the form of a binary string of length $ n $ . Each character of Kevin's string represents Kevin's score on one of the $ n $ questions of the olympiad—'1' for a correctly identified cow and '0' otherwise.

However, all is not lost. Kevin is a big proponent of alternative thinking and believes that his score, instead of being the sum of his points, should be the length of the longest alternating subsequence of his string. Here, we define an alternating subsequence of a string as a not-necessarily contiguous subsequence where no two consecutive elements are equal. For example, $ {0,1,0,1} $ , $ {1,0,1} $ , and $ {1,0,1,0} $ are alternating sequences, while $ {1,0,0} $ and $ {0,1,0,1,1} $ are not.

Kevin, being the sneaky little puffball that he is, is willing to hack into the USAICO databases to improve his score. In order to be subtle, he decides that he will flip exactly one substring—that is, take a contiguous non-empty substring of his score and change all '0's in that substring to '1's and vice versa. After such an operation, Kevin wants to know the length of the longest possible alternating subsequence that his string could have.

## 输入格式

The first line contains the number of questions on the olympiad $ n $ ( $ 1<=n<=100000 $ ).

The following line contains a binary string of length $ n $ representing Kevin's results on the USAICO.

## 输出格式

Output a single integer, the length of the longest possible alternating subsequence that Kevin can create in his string after flipping a single substring.

## 说明/提示

In the first sample, Kevin can flip the bolded substring '10000011' and turn his string into '10011011', which has an alternating subsequence of length 5: '10011011'.

In the second sample, Kevin can flip the entire string and still have the same score.

## 样例 #1

### 输入

```
8
10000011

```

### 输出

```
5

```

## 样例 #2

### 输入

```
2
01

```

### 输出

```
2

```

