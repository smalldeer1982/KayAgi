---
title: "Substring and Subsequence"
layout: "post"
diff: 提高+/省选-
pid: CF163A
tag: []
---

# Substring and Subsequence

## 题目描述

One day Polycarpus got hold of two non-empty strings $ s $ and $ t $ , consisting of lowercase Latin letters. Polycarpus is quite good with strings, so he immediately wondered, how many different pairs of " $ x $ $ y $ " are there, such that $ x $ is a substring of string $ s $ , $ y $ is a subsequence of string $ t $ , and the content of $ x $ and $ y $ is the same. Two pairs are considered different, if they contain different substrings of string $ s $ or different subsequences of string $ t $ . Read the whole statement to understand the definition of different substrings and subsequences.

The length of string $ s $ is the number of characters in it. If we denote the length of the string $ s $ as $ |s| $ , we can write the string as $ s=s_{1}s_{2}...\ s_{|s|} $ .

A substring of $ s $ is a non-empty string $ x=s[a...\ b]=s_{a}s_{a+1}...\ s_{b} $ ( $ 1<=a<=b<=|s| $ ). For example, "code" and "force" are substrings or "codeforces", while "coders" is not. Two substrings $ s[a...\ b] $ and $ s[c...\ d] $ are considered to be different if $ a≠c $ or $ b≠d $ . For example, if $ s $ ="codeforces", $ s[2...2] $ and $ s[6...6] $ are different, though their content is the same.

A subsequence of $ s $ is a non-empty string $ y=s[p_{1}p_{2}...\ p_{|y|}]=s_{p1}s_{p2}...\ s_{p|y|} $ ( $ 1<=p_{1}&lt;p_{2}&lt;...&lt;p_{|y|}<=|s| $ ). For example, "coders" is a subsequence of "codeforces". Two subsequences $ u=s[p_{1}p_{2}...\ p_{|u|}] $ and $ v=s[q_{1}q_{2}...\ q_{|v|}] $ are considered different if the sequences $ p $ and $ q $ are different.

## 输入格式

The input consists of two lines. The first of them contains $ s $ ( $ 1<=|s|<=5000 $ ), and the second one contains $ t $ ( $ 1<=|t|<=5000 $ ). Both strings consist of lowercase Latin letters.

## 输出格式

Print a single number — the number of different pairs " $ x $ $ y $ " such that $ x $ is a substring of string $ s $ , $ y $ is a subsequence of string $ t $ , and the content of $ x $ and $ y $ is the same. As the answer can be rather large, print it modulo $ 1000000007 $ $ (10^{9}+7) $ .

## 说明/提示

Let's write down all pairs " $ x $ $ y $ " that form the answer in the first sample: " $ s[1...1] $ $ t[1] $ ", " $ s[2...2] $ $ t[1] $ ", " $ s[1...1] $ $ t[2] $ "," $ s[2...2] $ $ t[2] $ ", " $ s[1...2] $ $ t[1 2] $ ".

## 样例 #1

### 输入

```
aa
aa

```

### 输出

```
5

```

## 样例 #2

### 输入

```
codeforces
forceofcode

```

### 输出

```
60

```

