---
title: "Replace All"
layout: "post"
diff: NOI/NOI+/CTSC
pid: CF794G
tag: []
---

# Replace All

## 题目描述

Igor the analyst is at work. He learned about a feature in his text editor called "Replace All". Igor is too bored at work and thus he came up with the following problem:

Given two strings $ x $ and $ y $ which consist of the English letters 'A' and 'B' only, a pair of strings $ (s,t) $ is called good if:

- $ s $ and $ t $ consist of the characters '0' and '1' only.
- $ 1<=|s|,|t|<=n $ , where $ |z| $ denotes the length of string $ z $ , and $ n $ is a fixed positive integer.
- If we replace all occurrences of 'A' in $ x $ and $ y $ with the string $ s $ , and replace all occurrences of 'B' in $ x $ and $ y $ with the string $ t $ , then the two obtained from $ x $ and $ y $ strings are equal.

For example, if $ x= $ AAB, $ y= $ BB and $ n=4 $ , then (01, 0101) is one of good pairs of strings, because both obtained after replacing strings are "01010101".

The flexibility of a pair of strings $ x $ and $ y $ is the number of pairs of good strings $ (s,t) $ . The pairs are ordered, for example the pairs $ ( $ 0, 1 $ ) $ and $ ( $ 1, 0 $ ) $ are different.

You're given two strings $ c $ and $ d $ . They consist of characters 'A', 'B' and '?' only. Find the sum of flexibilities of all possible pairs of strings $ (c',d') $ such that $ c' $ and $ d' $ can be obtained from $ c $ and $ d $ respectively by replacing the question marks with either 'A' or 'B', modulo $ 10^{9}+7 $ .

## 输入格式

The first line contains the string $ c $ ( $ 1<=|c|<=3·10^{5} $ ).

The second line contains the string $ d $ ( $ 1<=|d|<=3·10^{5} $ ).

The last line contains a single integer $ n $ ( $ 1<=n<=3·10^{5} $ ).

## 输出格式

Output a single integer: the answer to the problem, modulo $ 10^{9}+7 $ .

## 说明/提示

For the first sample, there are four possible pairs of $ (c',d') $ .

If $ (c',d')=( $ AA $ , $ A $ ) $ , then the flexibility is $ 0 $ .

If $ (c',d')=( $ AB $ , $ A $ ) $ , then the flexibility is $ 0 $ .

If $ (c',d')=( $ AA $ , $ B $ ) $ , then the flexibility is $ 2 $ , as the pairs of binary strings $ ( $ 1 $ , $ 11 $ ) $ , $ ( $ 0 $ , $ 00 $ ) $ are the only good pairs.

If $ (c',d')=( $ AB $ , $ B $ ) $ , then the flexibility is $ 0 $ .

Thus, the total flexibility is $ 2 $ .

For the second sample, there are $ 2^{1}+2^{2}+...+2^{10}=2046 $ possible binary strings of length not greater $ 10 $ , and the set of pairs of good strings is precisely the set of pairs $ (s,s) $ , where $ s $ is a binary string of length not greater than $ 10 $ .

## 样例 #1

### 输入

```
A?
?
3

```

### 输出

```
2

```

## 样例 #2

### 输入

```
A
B
10

```

### 输出

```
2046

```

