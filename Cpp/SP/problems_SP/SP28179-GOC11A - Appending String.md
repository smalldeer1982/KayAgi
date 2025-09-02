---
title: "GOC11A - Appending String"
layout: "post"
diff: 难度0
pid: SP28179
tag: []
---

# GOC11A - Appending String

## 题目描述

You are given a string S, you need to build another string T by expanding S according to the steps below (traversing left to right):

1. If current character is an alphabet, append it to T.
2. If current character is a digit, suppose the digit is N, then do T = N\*T. Here N\*T means appending T N times. See sample for better understanding.
3. Go to next character if exists then restart from step 1.

Upon expanding S, you will be given Q queries. For each query you have to print the i $ _{th} $  character of the string T.

Hint : After expanding the string S=”a3b2c1” T will be = “aaabaaabc”

## 输入格式

The first line will be the test case number(t<=10).

In the first line of each test you will be given a string consisting of lowercase letters and digits. And it is guaranteed that length of T will be no more than 1000.

Next line will contain an integer Q(<=100000) denoting total numbers of queries. Following Q lines each contains an integer X.

Output

For each query X, you have to print the X $ _{th} $  character of T in a line. If X is greater than the length of T, print -1.

## 样例 #1

### 输入

```
1
a3b2c1
2
4
5

```

### 输出

```
b
a

```

