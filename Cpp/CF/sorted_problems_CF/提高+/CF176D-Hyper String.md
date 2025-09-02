---
title: "Hyper String"
layout: "post"
diff: 提高+/省选-
pid: CF176D
tag: []
---

# Hyper String

## 题目描述

Paul Erdős's prediction came true. Finally an alien force landed on the Earth. In contrary to our expectation they didn't asked the humans to compute the value of a Ramsey number (maybe they had solved it themselves). They asked another question which seemed as hard as calculating Ramsey numbers. Aliens threatened that if humans don't solve this problem in less than 2 hours they will destroy the Earth.

Before telling the problem they introduced the concept of Hyper Strings. A Hyper String is made by concatenation of some base strings. Suppose you are given a list of base strings $ b_{1},b_{2},...,b_{n} $ . Now the Hyper String made from indices list $ i_{1},i_{2},...,i_{m} $ is concatenation of base strings $ b_{i1},b_{i2},...,b_{im} $ . A Hyper String can be very large and doing operations on it is very costly for computers.

The aliens asked humans to compute the length of the longest common sub-sequence of a Hyper String $ t $ with a string $ s $ .

## 输入格式

The first line of input contains the single integer $ n $ ( $ 1<=n<=2000 $ ) — the number of base strings.

The next $ n $ lines contains values of base strings. Each base string is made of lowercase Latin letters. A base string cannot be empty string and the sum of lengths of all $ n $ base strings doesn't exceed $ 10^{6} $ .

The next line contains the single integer $ m $ ( $ 1<=m<=2000 $ ) — the number of base strings in the given Hyper String $ t $ .

The next line contains $ m $ space-separated integer numbers $ i_{1},i_{2},...,i_{m} $ ( $ 1<=i_{j}<=n $ ) — the indices of base strings in the Hyper String $ t $ .

The last line contains a non-empty string $ s $ . String $ s $ is made of lowercase Latin letters and its length is no more than $ 2000 $ characters.

## 输出格式

Print the length of longest common sub-sequence of Hyper String $ t $ and string $ s $ . If there is no common sub-sequence print 0.

## 说明/提示

The length of string $ s $ is the number of characters in it. If the length of string $ s $ is marked as $ |s| $ , then string $ s $ can be represented as $ s=s_{1}s_{2}...\ s_{|s|} $ .

A non-empty string $ y=s[p_{1}p_{2}...\ p_{|y|}]=s_{p1}s_{p2}...\ s_{p|y|} $ ( $ 1<=p_{1}&lt;p_{2}&lt;...&lt;p_{|y|}<=|s| $ ) is a subsequence of string $ s $ . For example, "coders" is a subsequence of "codeforces".

## 样例 #1

### 输入

```
2
cba
dgh
2
1 2
aedfhr

```

### 输出

```
3

```

## 样例 #2

### 输入

```
2
b
a
5
1 2 1 2 1
aaa

```

### 输出

```
2

```

